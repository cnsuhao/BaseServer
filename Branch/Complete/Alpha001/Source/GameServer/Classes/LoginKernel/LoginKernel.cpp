#include "./LoginKernel.h"
#include "../../Common/inifile.h"
#include "../../Common/MessagePort/I_MessagePort.h"
#include "../LuaScriptMachine.h"

#include "./Network/MsgLoginAction.h"
#include "./Network/MsgLoginKickReason.h"
#include "./Network/MsgLoginUserList.h"
#include "./Network/MsgLoginCreateNewUser.h"

ILoginKernel* ILoginKernel::Instance()		{return (ILoginKernel*)CLoginKernel::GetInstance();}
void		  ILoginKernel::DelInstance()	{CLoginKernel::DelInstance();}
CLoginKernel* CLoginKernel::s_pInstance = NULL;
MYHEAP_IMPLEMENTATION(CLoginKernel, s_heap);

//////////////////////////////////////////////////////////////////////////
CLoginKernel::CLoginKernel()
{
	m_idProcess  = MSGPORT_DEFAULT;
	m_pDb		 = NULL;
	m_pMsgPort	 = NULL;
	m_bOpenLogin = true;
}

//////////////////////////////////////////////////////////////////////////
bool CLoginKernel::Create( IMessagePort* pPort )
{
	CHECKF(pPort);
	CHECKF(pPort->GetID() == MSGPORT_LOGIN);

	// ͨ�Ŷ˿�
	m_pMsgPort = pPort;
	m_idProcess = m_pMsgPort->GetID();
	m_pMsgPort->Open();

	// ���ݿ�
	char	szIP[DBSTR_SIZE] = "";
	char	szUser[DBSTR_SIZE] = "";
	char	szPassword[DBSTR_SIZE] = "";
	int		nPort = 0;

	CIniFile ini(GAMESERVER_FILENAME, "Database" );
	ini.GetString(szIP,			"DatabaseIP",		DBSTR_SIZE);
	ini.GetString(szUser,		"DatabaseUser",		DBSTR_SIZE);
	ini.GetString(szPassword,	"DatabasePassword",	DBSTR_SIZE);
	nPort = ini.GetInt("DatabasePort");

	m_pDb = ::CreateDatabase(szIP, szUser, szPassword, g_strGameDatabaseName.c_str(), nPort, true);
	if(!m_pDb)
	{
		LOGERROR("CLoginKernel Database Connect Failed!");
		return false;
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////
bool CLoginKernel::Release( void )
{
	SAFE_RELEASE (m_pDb);

	return true;
}

//////////////////////////////////////////////////////////////////////////
bool CLoginKernel::ProcessMsg( OBJID idPacket, void* buf, int nType, int nFrom )
{
	DEBUG_TRY;
	switch (idPacket)
	{
	case LOGINTHREAD_CLIENT_MSG:
		{
			CLIENTMSG_PACKET*	pMsg = (CLIENTMSG_PACKET*)buf;
			SOCKET_ID	idSocket= pMsg->idSocket;
			OBJID	idMsg	= pMsg->idPacket;
			char*	pBuf	= pMsg->buf;
			int		nMsgLen	= pMsg->nSize;

			CHECKF(idMsg > _MSG_LOGIN_BEGIN && idMsg < _MSG_LOGIN_END);
			CHECKF(pBuf);
			CHECKF(nMsgLen > 0 && nMsgLen <= _MAX_MSGSIZE);
			login_kernel::CNetMsg* pNetMsg = login_kernel::CNetMsg::CreateClientMsg(m_idProcess, idSocket, idMsg, pBuf, nMsgLen);
			if (pNetMsg)
			{
				DEBUG_TRY;
				pNetMsg->Process(this);
				DEBUG_CATCH4("CLoginKernel::ProcessMsg MsgType[%u], MsgLen[%d], SocketID[%d]", idMsg, nMsgLen, idSocket);
				SAFE_DELETE(pNetMsg);
			}
			else
			{
				tolog3("CLoginKernel::ProcessMsg idMsg[%u], nMsgLen[%d], not Process!", idMsg, nMsgLen);
			}
		}
		break;
	case LOGINTHREAD_FORCE_KICK_ACK:
		{
			auto pLoginForceKick = (ST_ACCOUNT_BASE_INFO*)buf;
			CHECKF(pLoginForceKick);
			CHECKF(pLoginForceKick->idAccount);
			auto iterAccount = m_mapAccount.find(pLoginForceKick->idAccount);
			CHECKF(iterAccount != m_mapAccount.end());
			CHECKF(ACCOUNT_LOGIN_STATE_WAIT_KICK == iterAccount->second.nLoginState);

			// ���߳�������ɱ��
			switch (pLoginForceKick->nFromProcess)
			{
			case MSGPORT_SOCKET:
				iterAccount->second.nKickOtherFlag |= ACCOUNT_KICK_FLAG_SOCKET;
				break;
			case MSGPORT_GAME:
				iterAccount->second.nKickOtherFlag |= ACCOUNT_KICK_FLAG_GAME;
				break;
			case MSGPORT_RELATION:
				iterAccount->second.nKickOtherFlag |= ACCOUNT_KICK_FLAG_RELATION;
				break;
			default:
				tolog2("Error From Process ID [%d]", pLoginForceKick->nFromProcess);
				return false;
				break;
			}

			// �������ֱ�ӽ���ѡ���ɫ���治�õȴ�
			if (ACCOUNT_KICK_FLAG_OK == iterAccount->second.nKickOtherFlag)
			{
				iterAccount->second.nLoginState = ACCOUNT_LOGIN_STATE_WAIT_CHOOSE;
				this->SendUserList(iterAccount->first);
			}
		}
		break;
	case LOGINTHREAD_CLOSE_SOCKET:
		{
			auto idSocket  = *(SOCKET_ID*)buf;
			auto idAccount = this->GetAccountID(idSocket);
			if (ID_NONE != idAccount)
			{
				m_mapAccount.erase(idAccount);
				m_setAccountEnterOk.erase(idAccount);
			}
			m_mapSocket.erase(idSocket);

			// ��֪������Ļ�����Դ, �ǳ����� 4.5
			m_pMsgPort->Send(MSGPORT_SOCKET, SOCKETTHREAD_CLOSESOCKET, VARTYPE_INT, &idSocket);	
		}
		break;
	case LOGINTHREAD_CLOSE_ENTRANCE:
		{
			m_bOpenLogin = false;
		}
		break;
	default:
		tolog2("CLoginKernel::ProcessMsg unkonw idPacket[%u]", idPacket);
		break;
	}
	return true;
	DEBUG_CATCHF2("CLoginKernel::ProcessMsg idPacket[%u]", idPacket);
}

//////////////////////////////////////////////////////////////////////////
bool CLoginKernel::OnTimer( void )
{
	// ÿ��ontimer����Ҫ�����˺ŵ���
	this->OnTimerAccountEnetr();

	auto unNowSecond = ::TimeGet(TIME_SECOND);

	// �ϴ��������߳�����
	if (unNowSecond >= ONTIMER_LOGIN_THREAD_KICK_DEAD + m_unKickTimeOutSecond)
	{
		m_unKickTimeOutSecond = unNowSecond;
		this->OnTimerKickTimeOut();
	}
	return true;
}

//////////////////////////////////////////////////////////////////////////
bool CLoginKernel::OnTimerRollback( void )
{
	return true;
}

//////////////////////////////////////////////////////////////////////////
void CLoginKernel::PrintText( const char* pszText )
{
	CHECK(m_pMsgPort && pszText);
	m_pMsgPort->Send(MSGPORT_SHELL, SHELL_PRINTTEXT, STRING_TYPE(pszText), pszText);
}

////////////////////////////////////////////////////////////////////////
bool CLoginKernel::SendMsg( login_kernel::CNetMsg* pMsg, SOCKET_ID idSocket /*= SOCKET_NONE*/ )
{
	CHECKF(pMsg && m_pMsgPort);
	IF_NOT (pMsg->GetBuf())
	{
		STACK_TRACE_ONCE;
		return false;
	}

	IF_NOT (pMsg->GetType())
	{
		STACK_TRACE_ONCE;
		return false;
	}

	IF_NOT (pMsg->GetSize() <= MAX_PACKETSIZE)
	{
		STACK_TRACE_ONCE;
		return false;
	}

	if (pMsg->GetSocketID() < 0 && idSocket < 0)
	{
		::LogSave("CLoginKernel::SendMsg not set socket id! MsgType[%u], MsgLen[%d]", pMsg->GetType(), pMsg->GetSize());
		STACK_TRACE_ONCE;
		return false;
	}

	DEBUG_TRY;
	char	bufPacket[MAX_MESSAGESIZE];
	CLIENTMSG_PACKET* pPacket = (CLIENTMSG_PACKET*)bufPacket;
	pPacket->idSocket	= (SOCKET_NONE == idSocket) ? pMsg->GetSocketID() : idSocket;
	pPacket->idPacket	= pMsg->GetType();
	pPacket->nSize		= pMsg->GetSize();
	memcpy(pPacket->buf, pMsg->GetBuf(), pMsg->GetSize());
	m_pMsgPort->Send(MSGPORT_SOCKET, SOCKETTHREAD_SENDCLIENTMSG, STRUCT_TYPE(bufPacket), &bufPacket);
	DEBUG_CATCHF3("CLoginKernel::SendMsg MsgType[%u], MsgLen[%d]", pMsg->GetType(), pMsg->GetSize());

	return true;
}

////////////////////////////////////////////////////////////////////////
// Description:  ������Ϣ
// Arguments:	
// Author:		 �½���(Chen Jianjun)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool CLoginKernel::SendMsg( OBJID idAccount, login_kernel::CNetMsg* pMsg )
{
	CHECKF(idAccount && pMsg);
	auto iterAccount = m_mapAccount.find(idAccount);
	if (iterAccount != m_mapAccount.end())
	{
		this->SendMsg(pMsg, iterAccount->second.idSocket);
	}
	else
	{
		tolog2("Unkonw idAccount[%u]", idAccount);
	}
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: �ͻ����˺ŵ�½
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void CLoginKernel::ProcessAccountLogin(SOCKET_ID idSocket, const char* pszAccountName, const char* pszAccountPassword)
{
	CHECK(idSocket >= 0);
	CHECK(pszAccountName && pszAccountPassword);
	CHECK(m_pDb && m_pMsgPort);

	// ����Ƿ񿪷ŵ�½
	if (!m_bOpenLogin)
	{
		this->KickOutBySocket(idSocket, KICK_REASON_NOT_ALLOW);
		return;
	}

	// ����˺��Ƿ����
	CMxyString strSql("select * from %s.%s where name = '%s'", g_strAccountDatabaseName.c_str(), ACC_DB_NAME_ACCOUNT, pszAccountName);
	RecordsetPtr pRes = m_pDb->CreateNewRecordset(strSql.c_str());
	if (NULL == pRes || 0 == pRes->RecordCount())
	{
		this->KickOutBySocket(idSocket, KICK_REASON_ACCOUNT_ERROR);
		return;
	}

	// ��������Ƿ���ȷ
	if (0 != strcmp(pRes->GetStr(ACCOUNT_DATA_PASSWORD), pszAccountPassword))
	{
		this->KickOutBySocket(idSocket, KICK_REASON_PASSWORD_ERROR);
		return;
	}

	// ����˺ŷ�ͣ״̬
	auto eAccountStatus = (ACCOUNT_STATUS)pRes->GetInt(ACCOUNT_DATA_STATUS);
	if (ACCOUNT_STATUS_STOP_FOREVER == eAccountStatus)
	{
		this->KickOutBySocket(idSocket, KICK_REASON_ACCOUNT_STOP_FOREVER);
		return;
	}

	// ��ʱ��ͣ��ʱ���Զ����
	if (ACCOUNT_STATUS_STOP_BYTIME == eAccountStatus)
	{
		if (::TimeGet(TIME_SECOND) > pRes->GetInt(ACCOUNT_DATA_STATUS_PARAM))
		{
			pRes->SetInt(ACCOUNT_DATA_STATUS,		ACCOUNT_STATUS_NORMAL);
			pRes->SetInt(ACCOUNT_DATA_STATUS_PARAM, 0);
			pRes->UpdateRecord();
		}
		else
		{
			this->KickOutBySocket(idSocket, KICK_REASON_ACCOUNT_STOP_BYTIME, pRes->GetInt(ACCOUNT_DATA_STATUS_PARAM));
			return;
		}
	}

	// ��ʼ����½״̬Ϊ�ȴ�����
	ACCOUNT_LOGIN_STATE eLoginState = ACCOUNT_LOGIN_STATE_WAIT_ENTER;

	// ����Ƿ��ظ���¼
	auto idAccount = (OBJID)pRes->GetInt(ACCOUNT_DATA_ID);
	CHECK(idAccount);
	auto iterAccount = m_mapAccount.find(idAccount);
	if (iterAccount != m_mapAccount.end())
	{
		// �ݴ�ͻ����ظ���¼��û�д���UserList���
		if (idSocket == iterAccount->second.idSocket)
		{
			if (ACCOUNT_KICK_FLAG_OK == iterAccount->second.nKickOtherFlag			// û���κ��߳����
			&&  ACCOUNT_LOGIN_STATE_WAIT_CHOOSE == iterAccount->second.nLoginState)	// ���ڵȴ�ѡ���ɫ
			{
				this->SendUserList(idAccount);
				return;
			}
		}

		// �߳�֮ǰ��¼�Ŀͻ���
		ST_ACCOUNT_BASE_INFO stKickInfo = {0};
		stKickInfo.idSocket		= iterAccount->second.idSocket;
		stKickInfo.idAccount	= iterAccount->second.idAccount;
		stKickInfo.idUser		= iterAccount->second.idChoosePlayer;
		stKickInfo.nFromProcess = m_idProcess;

		CMsgLoginKickReason msg;
		IF_OK (msg.CreateInfo(KICK_REASON_BE_KICK_ANOTHER))
		{
			this->SendMsg(&msg, idSocket);
		}

		// ��Ⲣ�������
		auto iterSocket = m_mapSocket.find(stKickInfo.idSocket);
		if (iterSocket == m_mapSocket.end())
		{
			tolog3("Error! CLoginKernel::KickAnotherLogin Can not Find Socket in m_mapSocket! KickSocket[%d] KickAccount[%u]", stKickInfo.idSocket, stKickInfo.idAccount);
		}
		else if (iterSocket->second != idAccount)
		{
			tolog3("Error! CLoginKernel::KickAnotherLogin Diff idAccount! m_mapSocket.idAccount[%u], idAccount[%u]", iterSocket->second, idAccount);
		}
		m_mapSocket.erase(stKickInfo.idSocket);
		m_mapAccount.erase(stKickInfo.idAccount);
		m_setAccountEnterOk.erase(stKickInfo.idAccount);

		// ��֪������ǿ��, ��������Դ, �������� 3.2
		m_pMsgPort->Send(MSGPORT_RELATION,	RELATIONTHREAD_FORCE_KICK,	STRUCT_TYPE(stKickInfo), &stKickInfo);
		m_pMsgPort->Send(MSGPORT_GAME,		GAMETHREAD_FORCE_KICK,		STRUCT_TYPE(stKickInfo), &stKickInfo);
		m_pMsgPort->Send(MSGPORT_SOCKET,	SOCKETTHREAD_FORCE_KICK,	STRUCT_TYPE(stKickInfo), &stKickInfo);
		
		// ��½״̬��Ϊ�ȴ�����
		eLoginState = ACCOUNT_LOGIN_STATE_WAIT_KICK;
	}

	// ��¼��Ϣ��������
	ACCOUNT_INFO stAccountInfo = {0};
	stAccountInfo.idAccount			  = idAccount;
	::SafeCopy(stAccountInfo.szAccountName, pszAccountName, sizeof(stAccountInfo.szAccountName));
	stAccountInfo.nAccountType		  = pRes->GetInt(ACCOUNT_DATA_TYPE);
	stAccountInfo.nAccountStatus	  = pRes->GetInt(ACCOUNT_DATA_STATUS);
	stAccountInfo.nAccountStatusParam = pRes->GetInt(ACCOUNT_DATA_STATUS_PARAM);

	stAccountInfo.idSocket			  = idSocket;
	stAccountInfo.idChoosePlayer	  = ID_NONE;
	stAccountInfo.nKickOtherFlag	  = ACCOUNT_KICK_FLAG_OK;
	stAccountInfo.nLoginState		  = eLoginState;
	stAccountInfo.nUserCount		  = 0;
	stAccountInfo.unStartSecond		  = ::TimeGet(TIME_SECOND);

	m_mapSocket[idSocket]			  = idAccount;
	m_mapAccount[idAccount]			  = stAccountInfo;

	// ����������������ͷ��͵�¼�Ŷ���Ϣ
	if (ACCOUNT_LOGIN_STATE_WAIT_ENTER == eLoginState)
	{
		m_deqAccountEnter.push_back(idAccount);

		if (m_setAccountEnterOk.size() >= MAX_ONLINE_USER_COUNT)
		{
			CMsgLoginAction msg;
			CHECK(msg.CreateMsg(MSG_LOGIN_ACTION_TYPE_LOGIN_DEQUE, MSG_LOGIN_ACTION_RESULT_SUCCESS, m_deqAccountEnter.size(), m_deqAccountEnter.size()));
			this->SendMsg(&msg, idSocket);
		}
	}
}

////////////////////////////////////////////////////////////////////////
// Description: ���ͽ�ɫ�б�
// Arguments:
// Author:	    �½���(Chen Jianjun)
// Return:		void
////////////////////////////////////////////////////////////////////////
void CLoginKernel::SendUserList(OBJID idAccount)
{
	CHECK(idAccount);
	auto iterAccount = m_mapAccount.find(idAccount);
	CHECK(iterAccount != m_mapAccount.end());

	// ��ɫ�б�, ���յǳ�ʱ����������
	CMxyString strSql;
	if (CROSS_SERVER_GROUP == g_nServerGroup)
	{
		strSql.Format("select * from %s where account_id = %u and del_flag = 0 order by exit_time desc limit %d", GAME_DB_NAME_USER, idAccount, LOGIN_USER_LIST_LIMIT);
	}
	else
	{
		strSql.Format("select * from %s where account_id = %u and server_group = %d and del_flag = 0 order by exit_time desc limit %d", GAME_DB_NAME_USER, idAccount, g_nServerGroup, LOGIN_USER_LIST_LIMIT);
	}
	RecordsetPtr pRes = m_pDb->CreateNewRecordset(strSql.c_str());
	CHECK(pRes);

	CMsgLoginUserList msg;
	CHECK(msg.CreateBase(idAccount));
	for( int i = 0; i < pRes->RecordCount(); i++)
	{
		USER_LOGIN_SNAP stSnap = {0};
		stSnap.nUserID		= pRes->GetInt(USER_DATA_ID);
		::SafeCopy(stSnap.szName, pRes->GetStr(USER_DATA_NAME), sizeof(stSnap.szName));
		stSnap.nLastLogin	= pRes->GetInt(USER_DATA_LOGIN_TIME);
		stSnap.nLev			= pRes->GetInt(USER_DATA_LEV);
		stSnap.nCamp		= pRes->GetInt(USER_DATA_CAMP);
		stSnap.nFlagShip	= pRes->GetInt(USER_DATA_FLAGSHIP);
		CHECKC(msg.AppendInfo(stSnap));
	}
	CHECK(this->SendMsg(idAccount, &msg));

	// �ȴ���Ҵ���/ѡ���ɫ, ��������3.5/3.6
	iterAccount->second.nUserCount = pRes->RecordCount();
}

////////////////////////////////////////////////////////////////////////
// Description:  ����ScoketId����˺�id
// Arguments:
// Author:		 �½���(Chen Jianjun)
// Return Value: OBJID
////////////////////////////////////////////////////////////////////////
OBJID CLoginKernel::GetAccountID(SOCKET_ID idSocket) const
{
	CHECKF(idSocket >= 0);
	auto iterSocket = m_mapSocket.find(idSocket);
	if (iterSocket != m_mapSocket.end())
	{
		return iterSocket->second;
	}
	return ID_NONE;
}

////////////////////////////////////////////////////////////////////////
// Description:  �����˺�id��ȡ�ŶӶ���λ��
// Arguments:
// Author:		 �½���(Chen Jianjun)
// Return Value: OBJID
////////////////////////////////////////////////////////////////////////
int CLoginKernel::GetAccountEnterPos(OBJID idAccount) const
{
	CHECKF(ID_NONE != idAccount);
	int nEnterPos = 0;
	for (auto iterDeq = m_deqAccountEnter.begin(); iterDeq != m_deqAccountEnter.end(); iterDeq++)
	{
		nEnterPos++;
		if (*iterDeq == idAccount)
		{
			break;
		}
	}
	return nEnterPos;
}

////////////////////////////////////////////////////////////////////////
// Description:  �����½�ɫ
// Arguments:
// Author:	     �½���(Chen Jianjun)
// Return Value: int
////////////////////////////////////////////////////////////////////////
int	CLoginKernel::ProcessCreateUser(SOCKET_ID idSocket, const char* pszUserName, int nCamp, int nFlagShip, OUT int& nUserID)
{
	nUserID = ID_NONE;
	CHECKF1(idSocket >= 0);
	CHECKF1(pszUserName);
	CHECKF1(m_pDb && m_pMsgPort);
	CHECKF1(nCamp > CAMP_TYPE_BEGIN && nCamp < CAMP_TYPE_END);

	// ����˺�״̬
	OBJID idAccount  = this->GetAccountID(idSocket);
	CHECKF1(idAccount);
	auto iterAccount = m_mapAccount.find(idAccount);
	CHECKF1(iterAccount != m_mapAccount.end());
	CHECKF1(ACCOUNT_LOGIN_STATE_WAIT_CHOOSE == iterAccount->second.nLoginState);

	// ����ɫ����
	if (iterAccount->second.nUserCount >= LOGIN_USER_LIST_LIMIT)
	{
		return MSG_LOGIN_CREATE_NEW_USER_RESULT_COUNT_FULL;
	}

	// ����ɫ���Ƿ����������
	if(!::NameStrCheck(pszUserName))
	{
		return MSG_LOGIN_CREATE_NEW_USER_RESULT_NAME_CHECK;
	}

	// ����Ƿ�������
	CMxyString strSql("select count(*) from %s where name='%s'", GAME_DB_NAME_USER, pszUserName);
	RecordsetPtr pRes = m_pDb->CreateNewRecordset(strSql.c_str());
	CHECKF1(pRes);
	if (pRes->GetInt(0) > 0)
	{
		return MSG_LOGIN_CREATE_NEW_USER_RESULT_NAME_REPEAT;
	}

	// �����µļ�¼
	strSql.Format("insert into %s set name='%s', account_id=%u, account_type=%d, create_time=%u, server_group=%d, lev=1, exp=0, camp=%d, flagship=%u",
		GAME_DB_NAME_USER, pszUserName, idAccount, iterAccount->second.nAccountType, ::TimeGet(TIME_SECOND), g_nServerGroup, nCamp, nFlagShip);
	CHECKF1(m_pDb->ExecuteSQL(strSql.c_str(), DBUPDATE_SYNC));
	nUserID = m_pDb->GetInsertId();
	CHECKF1(nUserID >= PLAYER_ID_FIRST);

	// ������Ҫ������ɫ����sql.....

	return MSG_LOGIN_CREATE_NEW_USER_RESULT_SUCCESS;
}

////////////////////////////////////////////////////////////////////////
// Description:  ѡ���ɫ����
// Arguments:
// Author:	     �½���(Chen Jianjun)
// Return Value: int
////////////////////////////////////////////////////////////////////////
bool CLoginKernel::ProcessChooseUser(SOCKET_ID idSocket, OBJID idUser)
{
	CHECKF(idSocket >= 0);
	CHECKF(idUser);
	CHECKF(m_pDb && m_pMsgPort);

	OBJID idAccount = this->GetAccountID(idSocket);
	CHECKF(idAccount);

	auto iterAccount = m_mapAccount.find(idAccount);
	CHECKF(iterAccount != m_mapAccount.end());
	CHECKF(ACCOUNT_LOGIN_STATE_WAIT_CHOOSE == iterAccount->second.nLoginState);

	// ��֤��ɫ�ǹ����˺ŵ�
	CMxyString strSql("select count(*) from %s where id=%u and account_id=%u and del_flag=0", GAME_DB_NAME_USER, idUser, idAccount);
	RecordsetPtr pRes = m_pDb->CreateNewRecordset(strSql.c_str());
	CHECKF(pRes && pRes->GetInt(0) > 0);

	// ����˺����뿪�ŶӶ���
	CHECKF(0 == this->GetAccountEnterPos(idAccount));

	// �������������֪ͨ�����̴߳���
	m_setAccountEnterOk.insert(idAccount);
	iterAccount->second.idChoosePlayer = idUser;
	iterAccount->second.nLoginState    = ACCOUNT_LOGIN_STATE_OK;

	ST_ACCOUNT_BASE_INFO stLoginInfo = {0};
	stLoginInfo.idSocket     = iterAccount->second.idSocket;
	stLoginInfo.idAccount    = iterAccount->second.idAccount;
	stLoginInfo.idUser       = iterAccount->second.idChoosePlayer;
	stLoginInfo.nFromProcess = m_idProcess;
	m_pMsgPort->Send(MSGPORT_GAME, GAMETHREAD_USER_LOGIN, STRUCT_TYPE(stLoginInfo), &stLoginInfo);
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description:  ɾ����ɫ
// Arguments:
// Author:	     �½���(Chen Jianjun)
// Return Value: int
////////////////////////////////////////////////////////////////////////
bool CLoginKernel::ProcessDeleteUser(SOCKET_ID idSocket, OBJID idUser)
{
	CHECKF(idSocket >= 0);
	CHECKF(idUser);
	CHECKF(m_pDb);

	// ����˺�״̬
	OBJID idAccount = this->GetAccountID(idSocket);
	CHECKF(idAccount);
	auto iterAccount = m_mapAccount.find(idAccount);
	CHECKF(iterAccount != m_mapAccount.end());
	CHECKF(ACCOUNT_LOGIN_STATE_WAIT_CHOOSE == iterAccount->second.nLoginState);

	// ��֤��ɫ�ǹ����˺ŵ�
	CMxyString strSql("select count(*) from %s where id=%u and account_id=%u and del_flag=0", GAME_DB_NAME_USER, idUser, idAccount);
	RecordsetPtr pRes = m_pDb->CreateNewRecordset(strSql.c_str());
	CHECKF(pRes && pRes->GetInt(0) > 0);

	// ����sql��ɾ�����
	strSql.Format("UPDATE %s set del_flag=1 WHERE id=%u", GAME_DB_NAME_USER, idUser);
	CHECKF(m_pDb->ExecuteSQL(strSql.c_str(), DBUPDATE_SYNC));
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: ��ѯ��½�Ŷ���Ϣ(�Ŷ��������Լ��Ķ���λ��)
// Arguments:
// Author:	    �½���(Chen Jianjun)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void CLoginKernel::ProcessQueryLogin(SOCKET_ID idSocket)
{
	CHECK(idSocket >= 0);

	auto idAccount = this->GetAccountID(idSocket);
	CHECK(idAccount);

	CMsgLoginAction msg;
	IF_OK (msg.CreateMsg(MSG_LOGIN_ACTION_TYPE_LOGIN_DEQUE, MSG_LOGIN_ACTION_RESULT_SUCCESS, m_deqAccountEnter.size(), this->GetAccountEnterPos(idAccount)))
	{
		this->SendMsg(&msg, idSocket);
	}
}

////////////////////////////////////////////////////////////////////////
// Description: ���� �����˺��Ŷӽ���
// Arguments:
// Author:	    �½���(Chen Jianjun)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void CLoginKernel::OnTimerAccountEnetr()
{
	// ����Ƿ񵽴������������
	if (m_setAccountEnterOk.size() >=  MAX_ONLINE_USER_COUNT)
	{
		return;
	}

	// �Ź���¼������
	auto nMaxRunCount = MAX_ONLINE_USER_COUNT - m_setAccountEnterOk.size();
	auto nNowRunCount = m_deqAccountEnter.size() > PER_ONTIMER_LOGIN_ENTER_COUNT ? PER_ONTIMER_LOGIN_ENTER_COUNT : m_deqAccountEnter.size();
	nNowRunCount = nNowRunCount > nMaxRunCount ? nMaxRunCount : nNowRunCount;
	for (int i = 0; i < nNowRunCount; i++)
	{
		auto idAccount = m_deqAccountEnter.front();
		m_deqAccountEnter.pop_front();
		CHECKC(idAccount);
		auto iterAccount = m_mapAccount.find(idAccount);

		// �����Ѿ�����
		if (iterAccount == m_mapAccount.end())
		{
			continue;
		}

		// ״̬�����ڵȴ�����
		if (ACCOUNT_LOGIN_STATE_WAIT_ENTER != iterAccount->second.nLoginState)
		{
			tolog3("CLoginKernel::OnTimerAccountEnetr Error idAccount[%u], nLoginFlag[%d]", idAccount, iterAccount->second.nLoginState);
			continue;
		}

		// ����û��ѡ���ɫ
		if (ID_NONE != iterAccount->second.idChoosePlayer)
		{
			tolog3("CLoginKernel::OnTimerAccountEnetr Error idAccount[%u], idChoosePlayer[%u]", idAccount, iterAccount->second.idChoosePlayer);
			continue;
		}

		// ����ѡ���ɫ
		iterAccount->second.nLoginState = ACCOUNT_LOGIN_STATE_WAIT_CHOOSE;
		this->SendUserList(idAccount);
	}
}

////////////////////////////////////////////////////////////////////////
// Description: ���� �����߳���ʱ
// Arguments:
// Author:	    �½���(Chen Jianjun)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void CLoginKernel::OnTimerKickTimeOut(void)
{
	auto unNowSecond = ::TimeGet(TIME_SECOND);
	for (auto iterAccount : m_mapAccount)
	{
		// ����Ƿ�����ѡ�����
		if (ACCOUNT_LOGIN_STATE_WAIT_CHOOSE != iterAccount.second.nLoginState)
		{
			continue;
		}

		// ���ȴ�ʱ���Ƿ�ʱ
		if (unNowSecond < iterAccount.second.unStartSecond + TIMEOUT_LOGIN_THREAD_KICK_DEAD)
		{
			continue;
		}

		this->KickOutBySocket(iterAccount.second.idSocket, KICK_REASON_LOGIN_TIMEOUT);
	}
}

////////////////////////////////////////////////////////////////////////
// Description: ����SocketID����
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void CLoginKernel::KickOutBySocket( SOCKET_ID idSocket, KICK_REASON eReason /*= KICK_REASON_DEFAULT*/, int nParam /*= 0*/ )
{
	CHECK(m_pMsgPort);
	CMsgLoginKickReason msg;
	IF_OK (msg.CreateInfo(eReason, nParam))
	{
		this->SendMsg(&msg, idSocket);
	}

	::LogSaveLoginout("CLoginKernel::KickOutBySocket idSocket[%d], eReason[%d], nParam[%d]", idSocket, eReason, nParam);

	m_pMsgPort->Send(MSGPORT_SOCKET, SOCKETTHREAD_BREAKCONNECT, VARTYPE_INT, &idSocket);
}