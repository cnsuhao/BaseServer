#include "./LoginKernel.h"
#include "../../Common/inifile.h"
#include "../../Common/MessagePort/I_MessagePort.h"
#include "../LuaScriptMachine.h"

ILoginKernel* ILoginKernel::Instance()		{return (ILoginKernel*)CLoginKernel::GetInstance();}
void		  ILoginKernel::DelInstance()	{CLoginKernel::DelInstance();}
CLoginKernel* CLoginKernel::s_pInstance = NULL;
MYHEAP_IMPLEMENTATION(CLoginKernel, s_heap);

//////////////////////////////////////////////////////////////////////////
CLoginKernel::CLoginKernel()
{
	m_idProcess = MSGPORT_DEFAULT;
	m_pDb		= NULL;
	m_pMsgPort	= NULL;
}

//////////////////////////////////////////////////////////////////////////
bool CLoginKernel::Create( IMessagePort* pPort )
{
	CHECKF(pPort);
	CHECKF(pPort->GetID() == MSGPORT_LOGIN);

	// 通信端口
	m_pMsgPort = pPort;
	m_idProcess = m_pMsgPort->GetID();
	m_pMsgPort->Open();

	// 数据库
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
// Description: 客户端账号登陆
// Arguments:
// Author: 陈建军(Chen Jianjun)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void CLoginKernel::ProcessAccountLogin(SOCKET_ID idSocket, const char* pszAccountName, const char* pszAccountPassword)
{
	CHECK(idSocket >= 0);
	CHECK(pszAccountName && pszAccountPassword);
	CHECK(m_pDb && m_pMsgPort);

	// 检测是否开放登陆
	if (!m_bOpenLogin)
	{
		//this->KickOutBySocket(idSocket, KICK_REASON_NOT_ALLOW);
		return;
	}

	// 检测登陆人数限制
	//if ()
	//{
	//}


	//CMxyString strSql("select * from %s.%s where name='%s'", g_strAccountDatabaseName.c_str(), ACC_DB_NAME_ACCOUNT, pszAccountName);
	//RecordsetPtr pRes = m_pDb->CreateNewRecordset(strSql.c_str());
	//if (NULL == pRes)
	//{
	//	this->KickOutBySocket(idSocket, KICK_REASON_PASSWORD_ERROR);
	//	return;
	//}

	//if (0 != strcmp(pRes->GetStr(ACCOUNT_DATA_PASSWORD), pszAccountPassword))
	//{
	//	this->KickOutBySocket(idSocket, KICK_REASON_PASSWORD_ERROR);
	//	return;
	//}

	//// 临时封停到时间自动解封
	//if (ACCOUNT_STATUS_STOP_BYTIME == pRes->GetInt(ACCOUNT_DATA_ACCOUNT_STATUS))
	//{
	//	UINT unSecond = ::TimeGet(TIME_SECOND);
	//	if (unSecond > pRes->GetInt(ACCOUNT_DATA_ACCOUNT_STATUS_PARAM))
	//	{
	//		pRes->SetInt(ACCOUNT_DATA_ACCOUNT_STATUS,		ACCOUNT_STATUS_NORMAL);
	//		pRes->SetInt(ACCOUNT_DATA_ACCOUNT_STATUS_PARAM, 0);
	//		pRes->UpdateRecord();
	//	}
	//}

	//if (ACCOUNT_STATUS_STOP_BYTIME == pRes->GetInt(ACCOUNT_DATA_ACCOUNT_STATUS))
	//{
	//	this->KickOutBySocket(idSocket, KICK_REASON_ACCOUNT_STOP_BYTIME, pRes->GetInt(ACCOUNT_DATA_ACCOUNT_STATUS_PARAM));
	//	return;
	//}

	//if (ACCOUNT_STATUS_STOP_FOREVER == pRes->GetInt(ACCOUNT_DATA_ACCOUNT_STATUS))
	//{
	//	this->KickOutBySocket(idSocket, KICK_REASON_ACCOUNT_STOP_FOREVER);
	//	return;
	//}

	//OBJID idAccount = pRes->GetInt(ACCOUNT_DATA_ID);
	//CHECK(idAccount);

	//// 容错客户端重复登录并没有处理UserList情况
	//auto iterAccount = m_mapAccount.find(idAccount);
	//if (iterAccount != m_mapAccount.end())
	//{
	//	if (idSocket == iterAccount->second.idSocket && 
	//		ACCOUNT_KICK_FLAG_OK == iterAccount->second.nKickOtherFlag &&
	//		ACCOUNT_LOGIN_FLAG_WAIT_CHOOSE == iterAccount->second.nLoginFlag)
	//	{
	//		this->SendUserList(idAccount);
	//		return;
	//	}
	//}

	//// 强行踢出, 没有强行踢出的, 直接打上ok标记
	//int nKickOtherFlag = ACCOUNT_KICK_FLAG_NONE;
	//if (!this->KickAnotherLogin(idAccount))
	//{
	//	nKickOtherFlag = ACCOUNT_KICK_FLAG_OK;
	//}

	//// 进入容器
	//ACCOUNT_INFO stAccountInfo = {0};
	//stAccountInfo.idAccount = pRes->GetInt(ACCOUNT_DATA_ID);
	//::SafeCopy(stAccountInfo.szAccountName, pszAccountName, sizeof(stAccountInfo.szAccountName));
	//stAccountInfo.nAccountType = pRes->GetInt(ACCOUNT_DATA_ACCOUNT_TYPE);
	//stAccountInfo.nAccountStatus = pRes->GetInt(ACCOUNT_DATA_ACCOUNT_STATUS);
	//stAccountInfo.nAccountStatusParam = pRes->GetInt(ACCOUNT_DATA_ACCOUNT_STATUS_PARAM);

	//stAccountInfo.idChoosePlayer = ID_NONE;
	//stAccountInfo.idSocket = idSocket;
	//stAccountInfo.nKickOtherFlag = nKickOtherFlag;
	//stAccountInfo.nLoginFlag = ACCOUNT_LOGIN_FLAG_WAIT_KICK;
	//stAccountInfo.nUserCount = 0;
	//stAccountInfo.unStartSecond = ::TimeGet(TIME_SECOND);

	//m_mapAccount[idAccount] = stAccountInfo;
	//m_mapSocket[idSocket] = idAccount;

	//if (ACCOUNT_KICK_FLAG_OK == nKickOtherFlag)
	//{
	//	this->SendUserList(idAccount);
	//}
}

int	CLoginKernel::ProcessCreateUser(SOCKET_ID idSocket, const char* pszName, int nFaction, int nMainFly, OUT int& nUserID)
{
	return 0;
}

bool CLoginKernel::ProcessChooseUser(SOCKET_ID idSocket, OBJID idUser)
{
	return true;
}

bool CLoginKernel::ProcessDeleteUser(SOCKET_ID idSocket, OBJID idUser)
{
	return true;
}