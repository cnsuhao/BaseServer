// ServerSocket.cpp: implementation of the CSocketKernel class.
//
//////////////////////////////////////////////////////////////////////

#define _WINSOCKAPI_   /* Prevent inclusion of winsock.h in windows.h */
#define FD_SETSIZE      2048				// 限制最多2000个客户端登录
#include <winsock2.h>
#include <windows.h>
#pragma	warning(disable:4786)

#include "Session.h"
#include "IOCPServer.h"
#include "ServerSocket.h"
#include "SendBuffer.h"
#include "RecvBuffer.h"
#include "EncryptServer.h"
#include "../Common/basefunc.h"
#include "../Common/MessagePort/I_MessagePort.h"

#define			HANDLEIONUM					1
#define			MAXPACKETSIZE				1024

ISocketKernel* ISocketKernel::CreateNew()
{
	return (ISocketKernel*)(new CSocketKernel);
}

bool CSocketKernel::Create(IMessagePort* pPort,int nListenPort)
{
	m_pMsgPort = pPort;
	m_pMsgPort->Open();
	
	// TODO: 请在此添加初始化代码
	InitializeCriticalSection(&m_ReuseIDListLock);
	InitializeCriticalSection(&m_csLoginOverSocket);

	m_setSocket.reserve(MAX_GAMESERVER_ACCEPT_SESSION + 2);
	m_setNetBreakFlag.reserve(MAX_GAMESERVER_ACCEPT_SESSION + 2);
	m_bRelease = false;

	m_piocpServer = new IOCPServer;

	m_piocpServer->SetKernel(this);
	
	SYSTEM_INFO si;
	GetSystemInfo(&si);

	IOHANDLER_DESC desc[HANDLEIONUM];
	int i;
	for(i=0; i<HANDLEIONUM; ++i)
	{
		desc[i].dwIoHandlerKey				= i;
		desc[i].dwMaxAcceptSession			= MAX_LOGINSERVER_ACCEPT_SESSION;
		desc[i].dwMaxConnectSession			= 0;
		desc[i].dwSendBufferSize			= CLIENT_IOCP_SOCKET_BUF;
		desc[i].dwRecvBufferSize			= CLIENT_IOCP_SOCKET_BUF;
		desc[i].dwNumberOfAcceptThreads		= 1;
		desc[i].dwNumberOfIoThreads			= ::GetValueInRightRange(si.dwNumberOfProcessors * 2, CLIENT_IOCP_MIN_IO_WORKER_THREAD_COUNT, CLIENT_IOCP_MAX_IO_WORKER_THREAD_COUNT);
		desc[i].dwNumberOfConnectThreads	= 0;
		desc[i].dwMaxPacketSize				= MAXPACKETSIZE;
	}

	m_piocpServer->Init( desc, HANDLEIONUM );

	if(!(m_piocpServer->StartAllListen(NULL,nListenPort)))
		return false;
	m_piocpServer->StartSendProcessThread();

	return true;
}

//////////////////////////////////////////////////////////////////////
bool CSocketKernel::OnTimer()
{
	// TODO: 请在此添加时钟处理代码
	return true;		// return false : 消息处理异常，程序关闭。
}

//////////////////////////////////////////////////////////////////////
bool CSocketKernel::Release()
{
	m_bRelease = true;

	for(int i = m_setSocket.size()-1; i >= 0; i--)
	{
		if(m_setSocket[i])
		{
			m_setSocket[i]->Remove(REMOVE_REASON_SOCKET_KERNEL_RELEASE);
		}
	}

	m_pMsgPort->Close();

	DeleteCriticalSection(&m_ReuseIDListLock);
	DeleteCriticalSection(&m_csLoginOverSocket);
	delete m_piocpServer;

	delete this;
	return true;		// return false : 无意义。
}

//////////////////////////////////////////////////////////////////////
bool CSocketKernel::ProcessMsg(OBJID idPacket, void* buf, int nType, int nFrom)
{
	if (m_bRelease)
	{
		return true;
	}

	switch(idPacket)
	{
	case	SOCKETTHREAD_CLOSESOCKET:
		{
			SOCKET_ID	idSocket	= *(int*)buf;
			if(idSocket >= (int)m_setSocket.size())
				break;

			if(m_setSocket[idSocket])			// readme.txt (1-7)
			{
				::LogSaveLoginout("ServerSocket Recv Close Connect Msg, SOCKET_ID[%u], IP[%s]", idSocket, m_setSocket[idSocket]->GetIP());
				m_setSocket[idSocket]		= NULL;
				m_setNetBreakFlag[idSocket]	= false;

				//把idsocket加入到m_ReuseIDList中供以后使用
				EnterCriticalSection(&m_ReuseIDListLock);
				m_ReuseIDList.push_back(idSocket);
				LeaveCriticalSection(&m_ReuseIDListLock);
			}
			else
			{
				::LogSaveLoginout("ServerSocket Recv Close Connect Msg, SOCKET_ID[%u]", idSocket);
			}
		}
		break;
	case	SOCKETTHREAD_SENDCLIENTMSG:
		{
			int nStep = 0;
			unsigned int nMsgType = 0;
			SOCKET_ID idSocket=ID_NONE;
			char szIP[64]="";
			try
			{
				const CLIENTMSG_PACKET* pPack = (CLIENTMSG_PACKET*)buf;
				if(pPack->idSocket >= (int)m_setSocket.size())
					break;
				idSocket=pPack->idSocket;
				nStep = 1;
				if(m_setSocket[pPack->idSocket])
				{
					SafeCopy(szIP,m_setSocket[pPack->idSocket]->GetIP(),sizeof(szIP));
					static char buf[MAX_PACKETSIZE];
					nStep = 2;
					int	nNetPacketSize = UnitePacket(buf, MAX_PACKETSIZE, pPack->idPacket, pPack->buf, pPack->nSize,nMsgType);
					ASSERT(nNetPacketSize);
					if(nNetPacketSize >= 4)
					{
						nStep = 3;
						CPerformanceStatisticsCount objPS1(PERFORMANCE_STATISTICS_TYPE_NET_CLIENT_SEND_5SECOND, nNetPacketSize);
						m_setSocket[pPack->idSocket]->Send((BYTE*)buf,nNetPacketSize);
					}
				}
			}
			catch(...)
			{
				LogSave("SOCKETTHREAD_SENDCLIENTMSG step = %u MsgType = %u,idSocket=%d,szIP:%s",nStep,nMsgType,idSocket,szIP);
			}
		}
		break;
	case	SOCKETTHREAD_BREAKCONNECT:
		{
			SOCKET_ID	idSocket = *(SOCKET_ID*)buf;
			CHECKF(idSocket>=0 && idSocket < (int)m_setSocket.size());
			::LogSaveLoginout("ServerSocket Kick Socket: SOCKET_ID[%d], FromProcessID[%d], Because[SOCKETTHREAD_BREAKCONNECT]", idSocket, nFrom);
			if(m_setSocket[idSocket] && !IsNetBreakFlag(idSocket))
			{
				m_setSocket[idSocket]->PreSend();
				m_setSocket[idSocket]->Remove(REMOVE_REASON_KICK_ONE);
			}
		}
		break;
	case	SOCKETTHREAD_BREAKALLCONNECT:
		{
			SOCKET_ID	idGmSocket = *(SOCKET_ID*)buf;
			::LogSaveLoginout("ServerSocket Kick All Socket: GmSocket[%d], Because[SOCKETTHREAD_BREAKALLCONNECT]", idGmSocket);
			m_piocpServer->ProcessSend();
			for(int i = m_setSocket.size()-1; i >= 0; i--)
			{
				if(i != idGmSocket && m_setSocket[i])
				{
					m_setSocket[i]->Remove(REMOVE_REASON_KICK_ALL);
				}
			}
		}
		break;
	case SOCKETTHREAD_FORCE_KICK:
		{
			// 处理登陆强踢他人, 并发送回执, 登入流程3.3
			ST_BASE_ID* pLoginForceKick = (ST_BASE_ID*)buf;
			CHECKF(pLoginForceKick);
			CHECKF(pLoginForceKick->idSocket >= 0 && pLoginForceKick->idSocket < (int)m_setSocket.size());
			::LogSaveLoginout("ServerSocket Foce Kick Socket: SOCKET_ID[%d], Account[%u], FromProcessID[%d], Because[SOCKETTHREAD_FORCE_KICK]", pLoginForceKick->idSocket, pLoginForceKick->idAccount, nFrom);
			if(m_setSocket[pLoginForceKick->idSocket])
			{
				m_setSocket[pLoginForceKick->idSocket]->PreSend();
				m_setSocket[pLoginForceKick->idSocket]->Remove(REMOVE_REASON_KICK_ANOTHER);
				pLoginForceKick->nFromProcess = MSGPORT_SOCKET;
				m_pMsgPort->Send(MSGPORT_LOGIN,  LOGINTHREAD_FORCE_KICK_ACK,	STRUCT_TYPE(ST_BASE_ID), pLoginForceKick);
			}
		}
		break;
	case SOCKETTHREAD_BROADCAST_MSG:
		{
			const CLIENTMSG_PACKET* pPack = (CLIENTMSG_PACKET*)buf;
			IF_OK (pPack)
			{
				this->BroadcastMsg(pPack);
			}
		}
		break;
	case SOCKETTHREAD_LOGINOVER:
		{
			SOCKET_ID	idSocket = *(SOCKET_ID*)buf;
			EnterCriticalSection(&m_csLoginOverSocket);
			m_setLoginOverSocket.insert(idSocket);
			LeaveCriticalSection(&m_csLoginOverSocket);
		}
		break;
	case SOCKETTHREAD_GAME_QUERYIP:
		{
			const ST_USER_IP* pUserIP = (ST_USER_IP*)buf;
			IF_OK (pUserIP)
			{
				if (m_setSocket[pUserIP->idSocket])
				{
					ST_USER_IP stUserIP = {0};
					stUserIP.idSocket = pUserIP->idSocket;
					stUserIP.idUser = pUserIP->idUser;
					const char* pszIP = m_setSocket[pUserIP->idSocket]->GetIP();
					::SafeCopy(stUserIP.szIP, pszIP, sizeof(stUserIP.szIP));
					m_pMsgPort->Send(MSGPORT_GAME,  GAMETHREAD_RECV_IP,	STRUCT_TYPE(ST_USER_IP), &stUserIP);
				}
			}
		}
		break;
	default:
		tolog2("CSocketKernel::ProcessMsg unkonw idPacket[%u]", idPacket);
		return false;
	}

	return true;	
}

bool CSocketKernel::CheckMsgTail( Session* pSession, IN OUT CLIENTMSG_PACKET* pPacket )
{
	DEBUG_TRY;
	CHECKF(pSession && pPacket);
	CHECKF(pPacket->nSize >= 8);
	int	nMsgType	= pPacket->idPacket;

	DWORD	dwSessionMsgIndex	= pSession->GetMsgIndex();
	DWORD	dwMsgIndex			= *((DWORD*)(pPacket->buf + pPacket->nSize - 8));

	DWORD	dwRightMsgKey		= ::GetMsgKey(nMsgType, dwMsgIndex);
	DWORD	dwMsgKey			= *((DWORD*)(pPacket->buf + pPacket->nSize - 4));

	// 检查消息序号, 失败返回false, 消息抛弃
	if (dwMsgIndex <= dwSessionMsgIndex)
	{
		::MyLogSave("syslog/MsgTail", "dwMsgIndex[%u] <= dwSessionMsgIndex[%u], MsgType[%d], ClientID[%d], IP[%s]"
			, dwMsgIndex, dwSessionMsgIndex, nMsgType, pSession->GetClientID(), pSession->GetIP());
		return false;
	}

	// 检查验证序号, 失败返回false, 消息抛弃
	if (dwRightMsgKey != dwMsgKey)
	{
		::MyLogSave("syslog/MsgTail", "dwRightMsgKey[%u] != dwMsgKey[%u], MsgType[%d], ClientID[%d], IP[%s]"
			, dwRightMsgKey, dwMsgKey, nMsgType, pSession->GetClientID(), pSession->GetIP());
		return false;
	}

	// 检查成功, 重新设置Session中的消息序号, 并且将消息长度进行修改, 避免尾巴进入逻辑层
	pSession->SetMsgIndex(dwMsgIndex);
	pPacket->nSize = pPacket->nSize - 8;

	return true;
	DEBUG_CATCHF("CSocketKernel::CheckMsgTail");
}

// 处理接受的客户端消息
int CSocketKernel::ProcessRecvMsg(const char* pRecvBuf,int nSize,Session* pSession)
{	
	try
	{
		CHECKF(pRecvBuf && pSession);

		CProtocolMsgStruct*	pMsgHead = (CProtocolMsgStruct*)pRecvBuf;
		if (nSize <= 4 || pMsgHead->nMsgSize != nSize)
		{
			return 0;
		}

		// 处理客户端消息
		CPerformanceStatisticsCount objPS1(PERFORMANCE_STATISTICS_TYPE_NET_CLIENT_RECV_5SECOND, nSize);
		OBJID	idPacket;
		char*	pMsg;
		int		nMsgSize;
		int		nNetPacketSize = 0;
		static char	bufPacket[MAX_MESSAGESIZE];

		// 解包验证并通知给相关线程
		if(( nNetPacketSize = SplitPacket((char*)pRecvBuf, nSize, &idPacket, &pMsg, &nMsgSize) ))
		{
			CLIENTMSG_PACKET* pPacket = (CLIENTMSG_PACKET*)bufPacket;
			pPacket->idSocket	= pSession->GetClientID();
			pPacket->idPacket	= idPacket;
			pPacket->nSize		= nMsgSize;
			memcpy(pPacket->buf, pMsg, nMsgSize);

			// 消息尾巴验证成功, 才会通知给相关线程
			if (this->CheckMsgTail(pSession, pPacket))
			{
				if(idPacket > _MSG_LOGIN_BEGIN && idPacket < _MSG_LOGIN_END)
				{
					m_pMsgPort->Send(MSGPORT_LOGIN, LOGINTHREAD_CLIENT_MSG, STRUCT_TYPE(bufPacket), bufPacket);		
				}
				else if (idPacket > _MSG_GAME_BEGIN && idPacket < _MSG_GAME_END)
				{
					m_pMsgPort->Send(MSGPORT_GAME, GAMETHREAD_CLIENT_MSG, STRUCT_TYPE(bufPacket), bufPacket);		
				}
			}
			else // 验证失败记录错误次数自动断开连接
			{
				pSession->AddTailErrorCountAndAutoBreak();
			}
		}

		return nNetPacketSize;

	}
	catch(...)
	{
		LogSave("CSocketKernel::ProcessRecvMsg");
		return 0;
	}
}

void CSocketKernel::ProcessDisconnServer(int i, bool bSendOtherThread /*= true*/)
{
	if (bSendOtherThread)
	{
		SendCloseNotify(i);
		SetNetBreakFlag(i);
	}
	else
	{
		m_setSocket[i]		 = NULL;
		m_setNetBreakFlag[i] = false;

		//把idsocket加入到m_ReuseIDList中供以后使用
		EnterCriticalSection(&m_ReuseIDListLock);
		m_ReuseIDList.push_back(i);
		LeaveCriticalSection(&m_ReuseIDListLock);
	}

	EnterCriticalSection(&m_csLoginOverSocket);
	m_setLoginOverSocket.erase(i);
	LeaveCriticalSection(&m_csLoginOverSocket);
}

////////////////////////////////////////////////////////////////////////
// Description: 广播消息
// Arguments:	
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool CSocketKernel::BroadcastMsg( const CLIENTMSG_PACKET* pPack )
{
	CHECKF(pPack);
	unsigned int nMsgType = 0;

	DEBUG_TRY;
	static char buf[MAX_PACKETSIZE];
	int	nNetPacketSize = UnitePacket(buf, MAX_PACKETSIZE, pPack->idPacket, pPack->buf, pPack->nSize, nMsgType);
	ASSERT(nNetPacketSize);

	if(nNetPacketSize >= 4)
	{
		int nSendCount = 0;
		for (std::set<SOCKET_ID>::iterator iter = m_setLoginOverSocket.begin(); iter != m_setLoginOverSocket.end(); iter++)
		{
			SOCKET_ID idTargetSocket = *iter;
			CHECKC(m_setSocket[idTargetSocket]);
			m_setSocket[idTargetSocket]->Send((BYTE*)buf,nNetPacketSize);
			nSendCount++;
		}
		CPerformanceStatisticsCount objPS1(PERFORMANCE_STATISTICS_TYPE_NET_CLIENT_SEND_5SECOND, nNetPacketSize * nSendCount);
	}

	return true;
	DEBUG_CATCHF4("CSocketKernel::BroadcastMessage idPacket[%u] MsgType[%u] MsgSize[%d]", pPack->idPacket, nMsgType, pPack->nSize);
}

int CSocketKernel::SetNewSocket(Session* sNew)
{
	int ret = -1;
	if(sNew != NULL)
	{	
		EnterCriticalSection(&m_ReuseIDListLock);

		///玩家重新连上服务器后强制清空缓冲区，避免上次登录的消息残留，彭正帮
		sNew->Init();

		BOOL	bInsertOk = false;
		//判断m_ReuseIDList中有没有socketid

		if(!m_ReuseIDList.empty())
		{
			ret = m_ReuseIDList.front();
			m_ReuseIDList.erase(m_ReuseIDList.begin());

			m_setSocket[ret]		= sNew;
			m_setNetBreakFlag[ret]	= false;
			bInsertOk	= true;	
		}

		if(!bInsertOk)
		{		
			m_setSocket.push_back(sNew);
			m_setNetBreakFlag.push_back(false);
			ret = m_setSocket.size()-1;
		}
		LeaveCriticalSection(&m_ReuseIDListLock);

		if (ret != -1)
		{
			EnterCriticalSection(&m_csLoginOverSocket);
			m_setLoginOverSocket.erase(ret);
			LeaveCriticalSection(&m_csLoginOverSocket);
		}
	}
	return ret;
}

///////////////////////////////////////////////////////////////////////////////////////
bool CSocketKernel::SendCloseNotify(SOCKET_ID idSocket)
{
	LogSaveLoginout("ServerSocket Close! Kick SocketID[%d]", idSocket);

	// 测试用，直接通知回收资源，清理内存
	m_pMsgPort->Send(MSGPORT_SOCKET, SOCKETTHREAD_CLOSESOCKET, VARTYPE_INT, &idSocket);			// readme.txt (1-1)
	return true;
}