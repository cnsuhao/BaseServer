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
#include "../Share/I_Shell.h"
#include "../Share/define.h"
#include "../Share/protocol.h"
#include "../Common/basefunc.h"
#include "../Common/MessagePort/I_MessagePort.h"

#define			HANDLEIONUM					1
#define			MAXPACKETSIZE				1024

//////////////////////////////////////////////////////////////////////
// interface
//////////////////////////////////////////////////////////////////////
bool CSocketKernel::Create(IMessagePort* pPort,int nListenPort)
{
	m_unOnlineSecond = 0;
	m_pMsgPort = pPort;
	m_pMsgPort->Open();
	
	// TODO: 请在此添加初始化代码

	InitializeCriticalSection(&m_ReuseIDListLock);

	m_setSocket.reserve(MAX_LOGINSERVER_ACCEPT_SESSION+2);
	m_setProcessID.reserve(MAX_LOGINSERVER_ACCEPT_SESSION+2);
	m_setNetBreakFlag.reserve(MAX_LOGINSERVER_ACCEPT_SESSION+2);
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
bool CSocketKernel::ProcessMsg(OBJID idPacket, void* buf, int nType, int nFrom)
{
	if (m_bRelease)
	{
		return true;
	}

	switch(idPacket)
	{
	//case	SOCKET_CLOSESOCKET:
	//	{
	//		SOCKET_ID	idSocket	= *(int*)buf;
	//		if(idSocket >= (int)m_setSocket.size())
	//			break;

	//		if(m_setSocket[idSocket])			// readme.txt (1-7)
	//		{
	//			::LogSaveLoginout("ServerSocket Recv Close Connect Msg, SOCKET_ID[%u], IP[%s]", idSocket, m_setSocket[idSocket]->GetIP());
	//			m_setSocket[idSocket]		= NULL;
	//			m_setProcessID[idSocket]	= PROCESS_NONE;
	//			m_setNetBreakFlag[idSocket]	= false;

	//			//把idsocket加入到m_ReuseIDList中供以后使用
	//			EnterCriticalSection(&m_ReuseIDListLock);
	//			m_ReuseIDList.push_back(idSocket);
	//			LeaveCriticalSection(&m_ReuseIDListLock);
	//		}
	//		else
	//		{
	//			::LogSaveLoginout("ServerSocket Recv Close Connect Msg, SOCKET_ID[%u]", idSocket);
	//		}
	//	}
	//	break;
	//case	SOCKET_SENDCLIENTMSG:
	//	{
	//		int nStep = 0;
	//		unsigned int nMsgType = 0;
	//		SOCKET_ID idSocket=ID_NONE;
	//		char szIP[64]="";
	//		try
	//		{
	//			const SENDCLIENTMSG_PACKET0* pPack = (SENDCLIENTMSG_PACKET0*)buf;
	//			if(pPack->idSocket >= (int)m_setSocket.size())
	//				break;
	//			idSocket=pPack->idSocket;
	//			nStep = 1;
	//			if(m_setSocket[pPack->idSocket])
	//			{
	//				SafeCopy(szIP,m_setSocket[pPack->idSocket]->GetIP(),sizeof(szIP));
	//				static char buf[MAX_PACKETSIZE];
	//				nStep = 2;
	//				int	nNetPacketSize = UnitePacket(buf, MAX_PACKETSIZE, pPack->idPacket, pPack->buf, pPack->nSize,nMsgType);
	//				ASSERT(nNetPacketSize);
	//				if(nNetPacketSize >= 4)
	//				{
	//					nStep = 3;
	//					CPerformanceStatisticsCount objPS1(PERFORMANCE_STATISTICS_TYPE_NET_CLIENT_SEND_5SECOND, nNetPacketSize);
	//					m_setSocket[pPack->idSocket]->Send((BYTE*)buf,nNetPacketSize);
	//				}
	//			}
	//		}
	//		catch(...)
	//		{
	//			LogSave("SOCKET_SENDCLIENTMSG step = %u MsgType = %u,idSocket=%d,szIP:%s",nStep,nMsgType,idSocket,szIP);
	//		}
	//	}
	//	break;
	//case	SOCKET_CHANGECODE:
	//	{
	//		const CHANGE_USERDATA*	pPack = (CHANGE_USERDATA*)buf;
	//		SOCKET_ID idSocket	= pPack->idSocket;
	//		DWORD	dwData		= pPack->nData;
	//		CHECKF(idSocket>=0 && idSocket < (int)m_setSocket.size());
	//	}
	//	break;
	//case	SOCKET_BREAKCONNECT:
	//	{
	//		SOCKET_ID	idSocket = *(SOCKET_ID*)buf;
 //			CHECKF(idSocket>=0 && idSocket < (int)m_setSocket.size());
	//		::LogSaveLoginout("ServerSocket Kick Socket: SOCKET_ID[%d], FromProcessID[%d], Because[SOCKET_BREAKCONNECT]", idSocket, nFrom);
	//		if(m_setSocket[idSocket] && !IsNetBreakFlag(idSocket))
	//		{
	//			m_setSocket[idSocket]->PreSend();
	//			m_setSocket[idSocket]->Remove(REMOVE_REASON_KICK_ONE);
	//		}
	//	}
	//	break;
	//case	SOCKET_BREAKALLCONNECT:
	//	{
	//		SOCKET_ID	idGmSocket = *(SOCKET_ID*)buf;
	//		::LogSaveLoginout("ServerSocket Kick All Socket: GmSocket[%d], Because[SOCKET_BREAKALLCONNECT]", idGmSocket);
	//		m_piocpServer->ProcessSend();
	//		for(int i = m_setSocket.size()-1; i >= 0; i--)
	//		{
	//			if(i != idGmSocket && m_setSocket[i])
	//			{
	//				m_setSocket[i]->Remove(REMOVE_REASON_KICK_ALL);
	//			}
	//		}
	//	}
	//	break;

	default:
		return false;
	}

	return true;	
}

//还需进一步处理
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

		//处理客户端消息
		CPerformanceStatisticsCount objPS1(PERFORMANCE_STATISTICS_TYPE_NET_CLIENT_RECV_5SECOND, nSize);
		OBJID	idPacket;
		char*	pMsg;
		int		nMsgSize;
		int		nNetPacketSize = 0;
		static char	bufPacket[MAX_MESSAGESIZE];

		if(( nNetPacketSize = SplitPacket((char*)pRecvBuf, nSize, &idPacket, &pMsg, &nMsgSize) ))
		{
			/*			CLIENTMSG_PACKET0* pPacket = (CLIENTMSG_PACKET0*)bufPacket;
			pPacket->idSocket	= pSession->GetClientID();
			pPacket->idPacket	= idPacket;
			pPacket->nSize		= nMsgSize;
			memcpy(pPacket->buf, pMsg, nMsgSize);

			m_pMsgPort->Send(MSGPORT_SHELL, KERNEL_CLIENTMSG, STRUCT_TYPE(bufPacket), bufPacket);	*/	
		}

		return nNetPacketSize;

	}
	catch(...)
	{
		LogSave("CSocketKernel::ProcessRecvMsg");
		return 0;
	}
}


void CSocketKernel::ProcessDisconnServer(int i)
{
	SendCloseNotify(i);
	SetNetBreakFlag(i);
}


//////////////////////////////////////////////////////////////////////
bool CSocketKernel::OnTimer()
{
	// TODO: 请在此添加时钟处理代码
	UINT unNowSecond = ::TimeGet(TIME_SECOND);
	if (unNowSecond >= m_unOnlineSecond + 5)
	{
		m_unOnlineSecond = unNowSecond;

		int nOnline = 0;
		for(int i = m_setSocket.size()-1; i >= 0; i--)
		{
			if(m_setSocket[i] && !IsNetBreakFlag(i))
			{
				nOnline++;
			}
		}
		//int nMaxOnline = max(CPerformanceStatistics::GetInstance()->GetData(PERFORMANCE_STATISTICS_TYPE_MAX_USER_AMOUNT), nOnline);
		//CPerformanceStatisticsData objPS1(PERFORMANCE_STATISTICS_TYPE_MAX_USER_AMOUNT, nMaxOnline);
		//CPerformanceStatisticsData objPS2(PERFORMANCE_STATISTICS_TYPE_NOW_USER_AMOUNT, nOnline);
	}


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
	delete m_piocpServer;

	delete this;
	return true;		// return false : 无意义。
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

			m_setSocket[ret]			= sNew;
			m_setProcessID[ret]		= MSGPORT_SHELL;		// 初始化时指向世界核心
			m_setNetBreakFlag[ret]	= false;
			bInsertOk	= true;	
		}


		if(!bInsertOk)
		{
			
			m_setSocket.push_back(sNew);
			m_setProcessID.push_back(MSGPORT_SHELL);		// 初始化时指向世界核心
			m_setNetBreakFlag.push_back(false);
			ret = m_setSocket.size()-1;
		}
		LeaveCriticalSection(&m_ReuseIDListLock);
	}
	return ret;
}

///////////////////////////////////////////////////////////////////////////////////////
bool CSocketKernel::SendCloseNotify(SOCKET_ID idSocket)
{
	LogSaveLoginout("ServerSocket Close! Kick SocketID[%d]", idSocket);
	//m_pMsgPort->Send(MSGPORT_SHELL, KERNEL_CLOSEKERNEL, VARTYPE_INT, &idSocket);			// readme.txt (1-1)
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////
// global entry
///////////////////////////////////////////////////////////////////////////////////////
ISocketKernel* ISocketKernel::CreateNew()
{
	return (ISocketKernel*)(new CSocketKernel);
}
