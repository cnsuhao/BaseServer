#include "GameKernel.h"
#include "inifile.h"
#include "MessagePort/I_MessagePort.h"
#include "../LuaScriptMachine.h"

#include "User.h"
#include "UserMgr.h"

IGameKernel* IGameKernel::Instance()	{return (IGameKernel*)CGameKernel::GetInstance();}
void		 IGameKernel::DelInstance()	{CGameKernel::DelInstance();}
CGameKernel* CGameKernel::s_pInstance = NULL;
MYHEAP_IMPLEMENTATION(CGameKernel, s_heap);

//////////////////////////////////////////////////////////////////////////
CGameKernel::CGameKernel()
{
	m_idProcess = MSGPORT_DEFAULT;
	m_pDb		= NULL;
	m_pMsgPort	= NULL;
}

//////////////////////////////////////////////////////////////////////////
bool CGameKernel::Create( IMessagePort* pPort )
{
	CHECKF(pPort);
	CHECKF(pPort->GetID() == MSGPORT_GAME);

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
		LOGERROR("GameKernel Database Connect Failed!");
		return false;
	}

	//////////////////////////////////////////////////////////////////////////
	// 初始化脚本机
	CHECKF(pLuaScriptMachine->Init());

	// 各单例管理器初始化
	CHECKF(pUserMgr->Init());

	// 启动时, 需要清理无效的服务器掩码
	//pMaskMgr->ClearInvalidGroupServerMask();
	//pMaskMgr->ClearInvalidWorldServerMask();
	return true;
}

//////////////////////////////////////////////////////////////////////////
bool CGameKernel::Release( void )
{
	SAFE_RELEASE (m_pDb);
	// 各单列管理器释放
	pUserMgr->Release();



	// 各单列管理器删除
	CUserMgr::DelInstance();
	CLuaScriptMachine::DelInstance();
	return true;
}

//////////////////////////////////////////////////////////////////////////
bool CGameKernel::ProcessMsg( OBJID idPacket, void* buf, int nType, int nFrom )
{
	DEBUG_TRY;
	switch (idPacket)
	{
	case GAMETHREAD_CLIENT_MSG:
		{
			CLIENTMSG_PACKET*	pMsg = (CLIENTMSG_PACKET*)buf;
			SOCKET_ID	idSocket= pMsg->idSocket;
			OBJID	idMsg	= pMsg->idPacket;
			char*	pBuf	= pMsg->buf;
			int		nMsgLen	= pMsg->nSize;

			CHECKF(idMsg > _MSG_GAME_BEGIN && idMsg < _MSG_GAME_END);
			CHECKF(pBuf);
			CHECKF(nMsgLen > 0 && nMsgLen <= _MAX_MSGSIZE);
			game_kernel::CNetMsg* pNetMsg = game_kernel::CNetMsg::CreateClientMsg(m_idProcess, idSocket, idMsg, pBuf, nMsgLen);
			if (pNetMsg)
			{
				DEBUG_TRY;
				pNetMsg->Process(this);
				DEBUG_CATCH4("CGameKernel::ProcessMsg Client MsgType[%u], MsgLen[%d], SocketID[%d]", idMsg, nMsgLen, idSocket);
				SAFE_DELETE(pNetMsg);
			}
			else
			{
				tolog3("CGameKernel::ProcessMsg Client idMsg[%u], nMsgLen[%d], not Process!", idMsg, nMsgLen);
			}
		}
		break;
	case GAMETHREAD_FORCE_KICK:
		{
			ST_ACCOUNT_BASE_INFO* pLoginForceKick = (ST_ACCOUNT_BASE_INFO*)buf;
			CHECKF(pLoginForceKick);
			::LogSaveLoginout("GameKernel Foce Kick Socket: SOCKET_ID[%d], Account[%u], FromProcessID[%d], Because[GAMETHREAD_FORCE_KICK]", pLoginForceKick->idSocket, pLoginForceKick->idAccount, nFrom);
			CUser* pUser = pUserMgr->GetUserBySocket(pLoginForceKick->idSocket);
			if (pUser)
			{
				CHECKB(pUserMgr->LogoutUser(pUser->GetID()));
			}

			pLoginForceKick->nFromProcess = MSGPORT_GAME;
			m_pMsgPort->Send(MSGPORT_LOGIN,  LOGINTHREAD_FORCE_KICK_ACK, STRUCT_TYPE(ST_ACCOUNT_BASE_INFO), pLoginForceKick);
		}
		break;
	case GAMETHREAD_USER_LOGIN:
		{
			ST_ACCOUNT_BASE_INFO* pLoginInfo = (ST_ACCOUNT_BASE_INFO*)buf;
			CHECKF(pLoginInfo);

			if (pUserMgr->LoginUser(pLoginInfo->idUser, pLoginInfo->idSocket))
			{
				CUser* pUser = pUserMgr->GetUserByID(pLoginInfo->idUser);
				IF_OK (pUser)
				{
					::SafeCopy(pLoginInfo->szName, pUser->GetStr(USER_DATA_NAME), sizeof(pLoginInfo->szName));
					pLoginInfo->nAccountType = pUser->GetMemoryDataAttr(mdaUser_AccountType);
				}
				::LogSaveLoginout("GameKernel Login User[%u], SocketID[%d], AccountID[%u], UserName[%s]", pLoginInfo->idUser, pLoginInfo->idSocket, pLoginInfo->idAccount, pLoginInfo->szName);
				//m_pMsgPort->Send(MSGPORT_RELATION,  RELATIONTHREAD_USER_LOGIN, STRUCT_TYPE(ST_ACCOUNT_BASE_INFO), pLoginInfo);
			}
			else
			{
				tolog4("GameKernel Login Failed! User[%u], SocketID[%d], AccountID[%u]", pLoginInfo->idUser, pLoginInfo->idSocket, pLoginInfo->idAccount);
				pUserMgr->KickUserByID(pLoginInfo->idUser);
			}
		}
		break;
	case GAMETHREAD_CLOSE_SOCKET:
		{
			SOCKET_ID idSocket = *(SOCKET_ID*)buf;

			// 本线程正常登出流程
			CUser* pUser = pUserMgr->GetUserBySocket(idSocket);
			if (pUser)
			{
				CHECKB(pUserMgr->LogoutUser(pUser->GetID()));
			}

			// 通知下层
			m_pMsgPort->Send(MSGPORT_LOGIN, LOGINTHREAD_CLOSE_SOCKET, VARTYPE_INT, &idSocket);
		}
		break;
	case GAMETHREAD_KICK_ALLUSER:
		{
			pUserMgr->KickAllUser();
		}
		break;
	default:
		tolog2("CGameKernel::ProcessMsg unkonw idPacket[%u]", idPacket);
		break;
	}
	return true;
	DEBUG_CATCHF2("CGameKernel::ProcessMsg idPacket[%u]", idPacket);
}

//////////////////////////////////////////////////////////////////////////
bool CGameKernel::OnTimer( void )
{
	return true;
}

//////////////////////////////////////////////////////////////////////////
bool CGameKernel::OnTimerRollback( void )
{
	return true;
}

//////////////////////////////////////////////////////////////////////////
void CGameKernel::PrintText( const char* pszText )
{
	CHECK(m_pMsgPort && pszText);
	m_pMsgPort->Send(MSGPORT_SHELL, SHELL_PRINTTEXT, STRING_TYPE(pszText), pszText);
}

////////////////////////////////////////////////////////////////////////
// Description: 发送消息
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool CGameKernel::SendMsg( game_kernel::CNetMsg* pMsg, SOCKET_ID idSocket /*= SOCKET_NONE*/ )
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
	DEBUG_CATCHF3("CGameKernel::SendMsg MsgType[%u], MsgLen[%d]", pMsg->GetType(), pMsg->GetSize());

	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: 广播消息
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool CGameKernel::BroadcastMsg( game_kernel::CNetMsg* pMsg )
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

	DEBUG_TRY;
	char	bufPacket[MAX_MESSAGESIZE];
	CLIENTMSG_PACKET* pPacket = (CLIENTMSG_PACKET*)bufPacket;
	pPacket->idSocket	= SOCKET_NONE;
	pPacket->idPacket	= pMsg->GetType();
	pPacket->nSize		= pMsg->GetSize();
	memcpy(pPacket->buf, pMsg->GetBuf(), pMsg->GetSize());
	m_pMsgPort->Send(MSGPORT_SOCKET, SOCKETTHREAD_BROADCAST_MSG, STRUCT_TYPE(bufPacket), &bufPacket);
	DEBUG_CATCHF3("CGameKernel::BroadcastMsg MsgType[%u], MsgLen[%d]", pMsg->GetType(), pMsg->GetSize());
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: 登出流程4.1	
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: 
////////////////////////////////////////////////////////////////////////
void CGameKernel::CloseSocket( SOCKET_ID idSocket )
{
	m_pMsgPort->Send(MSGPORT_SOCKET, SOCKETTHREAD_BREAKCONNECT, VARTYPE_INT, &idSocket);
}

//////////////////////////////////////////////////////////////////////////
void CGameKernel::BreakAllUser( void )
{
	CHECK(m_pMsgPort);
	SOCKET_ID idSocket = SOCKET_NONE;
	m_pMsgPort->Send(MSGPORT_SOCKET, SOCKETTHREAD_BREAKALLCONNECT, VARTYPE_INT, &idSocket);
}