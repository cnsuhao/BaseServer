#include <iostream>
#include <assert.h>
#include <winsock2.h>
#include <mswsock.h>
#include "Session.h"
#include "SessionPool.h"
#include "SendBuffer.h"
#include "RecvBuffer.h"
#include "NetBase.h"
#include "IoHandler.h"
#include "IOCPServer.h"
#include "MsWinsockUtil.h"
#include <MSTcpIP.h>
#include "../Share/define.h"
#include "../Common/BaseFunc.h"
using namespace std;

MYHEAP_IMPLEMENTATION(Session, s_heap);

Session::Session( DWORD dwSendBufferSize, DWORD dwRecvBufferSize, DWORD dwMaxPacketSize/*, DWORD dwTimeOut*/ )
{
	m_pSendBuffer = new SendBuffer;
	m_pSendBuffer->Create( dwSendBufferSize, dwMaxPacketSize );

	m_pRecvBuffer = new RecvBuffer;
	m_pRecvBuffer->Create( dwRecvBufferSize, dwMaxPacketSize );

	m_socket			= INVALID_SOCKET;
	m_bAcceptSocket		= FALSE;
	m_bRemove			= FALSE;
	m_bSendFlag			= FALSE;
	m_ClientID			= -1;
	m_nTimeoutCount		= 0;
	m_i64RemoveMS		= 0;
	m_lRemoveReason		= REMOVE_REASON_NONE;

	ZeroMemory( &m_sendIoData,		sizeof(OVERLAPPEDEX));
	ZeroMemory( &m_recvIoData,		sizeof(OVERLAPPEDEX));
	ZeroMemory( &m_acceptIoData,	sizeof(OVERLAPPEDEX));
	ZeroMemory( &m_disconnectIoData, sizeof(OVERLAPPEDEX));
}

Session::~Session()
{
	CloseSocket();

	if( m_pSendBuffer )		delete m_pSendBuffer;
	if( m_pRecvBuffer )		delete m_pRecvBuffer;
}

VOID Session::Init()
{
	m_pSendBuffer->Clear();
	m_pRecvBuffer->Clear();

	ResetKillFlag();

	m_bDisconnectOrdered = FALSE;
	m_OverlappedIONum = 0;
}

VOID Session::Reuse( HANDLE hIOCP )
{
	ZeroMemory( &m_disconnectIoData, sizeof(OVERLAPPEDEX) );
	m_disconnectIoData.dwOperationType	= DISCONNECT_POSTED;
		
	PostQueuedCompletionStatus( hIOCP, 0, (ULONG_PTR)this, &m_disconnectIoData );	
}

BOOL Session::Send( BYTE *pMsg, WORD wSize )
{
	if(m_bRemove)
		return FALSE;

	// [发送缓冲区]写入循环队列, 如果溢出则断开
	if(m_pSendBuffer->Write( pMsg, wSize ) == FALSE)
	{
		::MyLogSave("syslog/SessionBuffer", "Send Buffer Overflow! NowSize[%d], SpaceSize[%d], SendSize[%d], ip[%s]", m_pSendBuffer->GetLength(), m_pSendBuffer->GetSpace(), wSize, GetIP());
		Remove(REMOVE_REASON_SEND_BUFFER_OVERFLOW_USER);
		return FALSE;
	}

	return TRUE;
}

BOOL Session::SendNPC( BYTE *pMsg, WORD wSize )
{
	if(m_bRemove)
		return FALSE;

	//发送给npc的消息
	if (m_pSendBuffer->Write( pMsg, wSize ) == FALSE)
	{
		::MyLogSave("syslog/SessionBuffer", "NPC Send Buffer Overflow! NowSize[%d], SpaceSize[%d], SendSize[%d]", m_pSendBuffer->GetLength(), m_pSendBuffer->GetSpace(), wSize);
		Remove(REMOVE_REASON_SEND_BUFFER_OVERFLOW_NPC);
		return FALSE;
	}

	return TRUE;
}

BOOL Session::ProcessRecvdPacket( DWORD dwMaxPacketSize )
{
	BYTE* pPacket = NULL;
	int nRet = 0;
	short header;
	
	if( pPacket = GetRecvBuffer()->GetFirstPacketPtr() )
	{
		header = *((short*)pPacket);
		nRet = m_pIoHandler->GetIOCPServer()->ProcessData((char*)pPacket,header,this);

		if(nRet)
		{
			GetRecvBuffer()->RemoveFirstPacket(nRet);
		}
	}

	return TRUE;
}

BOOL Session::PreSend()
{
	// 正在投递中, 等待下次投递
	if (TRUE == this->GetSendFlag())
	{
		return TRUE;
	}

	WSABUF wsabuf = {0};

	if( GetSendBuffer()->GetSendParam( (BYTE**)&wsabuf.buf, (int&)wsabuf.len ) == FALSE )
	{
		return TRUE;
	}

	this->SetSendFlag(TRUE);
	ZeroMemory( &m_sendIoData, sizeof(OVERLAPPEDEX) );

	m_sendIoData.dwOperationType = SEND_POSTED;
	AddOverlappedNum();
	int ret = WSASend( GetSocket(), &wsabuf, 1, &m_sendIoData.dwIoSize, m_sendIoData.dwFlags, &m_sendIoData, NULL );

	if( ret == SOCKET_ERROR && WSAGetLastError() != WSA_IO_PENDING )
	{
		ReleaseOverlappedNum();
		return FALSE;
		
	}

	return TRUE;
}

BOOL Session::PreRecv()
{
	WSABUF wsabuf = {0};

	m_pRecvBuffer->GetRecvParam( (BYTE**)&wsabuf.buf, (int&)wsabuf.len );

	// 缓冲区满就断开
	if(wsabuf.len == 0)
	{
		::MyLogSave("syslog/SessionBuffer", "Recv Buffer Overflow! Break Connect! ip[%s]", this->GetIP());
		return FALSE;
	}

	ZeroMemory( &m_recvIoData, sizeof(OVERLAPPEDEX) );
	m_recvIoData.dwOperationType = RECV_POSTED;

	AddOverlappedNum();

	int ret = WSARecv( GetSocket(), &wsabuf, 1, &m_recvIoData.dwIoSize, &m_recvIoData.dwFlags, &m_recvIoData, NULL ); 

	if( ret == SOCKET_ERROR && WSAGetLastError() != WSA_IO_PENDING )
	{
		ReleaseOverlappedNum();
		return FALSE;
	}

	return TRUE;
}

BOOL Session::PreAccept( SOCKET listenSocket )
{
	DWORD	dwBytes		= 0;
	int		nLen		= 0;
	BYTE	*pRecvBuf	= NULL;

	if( GetSocket() == INVALID_SOCKET )
	{
		SetSocket( CreateSocket() );
	}

	Init();

	GetRecvBuffer()->GetRecvParam( &pRecvBuf, nLen );

	ZeroMemory( &m_acceptIoData, sizeof(OVERLAPPEDEX) );
	m_acceptIoData.dwOperationType	= ACCEPT_POSTED;
	m_acceptIoData.pSession			= this;

	int nRet = 	MsWinsockUtil::m_lpfnAccepteEx(	listenSocket, 
												GetSocket(), 
												pRecvBuf, 
												0, 
												sizeof(SOCKADDR_IN) + 16,
												sizeof(SOCKADDR_IN) + 16,
												&dwBytes,
												&m_acceptIoData );

	if( nRet == SOCKET_ERROR && WSAGetLastError() != WSA_IO_PENDING ) 
	{
		return FALSE;
	}

	return TRUE;
}

SOCKET Session::CreateSocket() 
{
	int nRet		= 0;
	int nZero		= 0;

	SOCKET newSocket = WSASocket( AF_INET, SOCK_STREAM, IPPROTO_IP, NULL, 0, WSA_FLAG_OVERLAPPED ); 

	if( newSocket == INVALID_SOCKET ) 
	{
		return newSocket;
	}
	::SetClientSockOpt(newSocket);

	return newSocket;
}

VOID Session::OnAccept()
{
	this->ResetKillFlag();
}

VOID Session::Remove(int nReason, const char* pszLogEx/*= "Nothing"*/) 
{ 
	CHECK(pszLogEx);
	if(FALSE == m_bRemove)
	{
		m_i64RemoveMS = ::GetUtcMillisecond();
		InterlockedExchange((LONG*)&m_lRemoveReason, nReason);
		InterlockedExchange((LONG*)&m_bRemove, TRUE);
		MyLogSave("syslog/SessionRemove", "Session::Remove  Socket[%u] Reason[%d] ip[%s] LogEx[%s]", m_ClientID, nReason, GetIP(), pszLogEx);
	}
}

inline VOID Session::ResetKillFlag()
{ 
	InterlockedExchange((LONG*)&m_bRemove, FALSE);
	InterlockedExchange((LONG*)&m_lRemoveReason, REMOVE_REASON_NONE);		
	InterlockedExchange((LONG*)&m_bSendFlag, FALSE);	// 重新发送投递设置标志
	m_nTimeoutCount = 0;
	m_i64RemoveMS = 0;									// 断开计时
	m_dwMsgIndex = 0;
	m_dwMsgTailErrorCount = 0;
}

inline VOID	Session::CloseSocket() 
{ 
	MsWinsockUtil::m_lpfnDisconnectEx(m_socket, NULL, TF_DISCONNECT, 0);
	closesocket( m_socket ); 
	m_socket = INVALID_SOCKET; 
}

void SetClientSockOpt(SOCKET sock)
{
	// 设置SOCKET为KEEPALIVE
	int nKeepAlive = 1;
	struct tcp_keepalive inKeepAlive	= {0};
	struct tcp_keepalive outKeepAlive	= {0};
	unsigned long lInLen				= sizeof(struct tcp_keepalive);
	unsigned long lOutLen				= sizeof(struct tcp_keepalive);
	unsigned long lBytesReturn			= 0;
		
	inKeepAlive.onoff				= 1;
	inKeepAlive.keepaliveinterval	= CLIENT_IOCP_SOCKET_KEEPALIVE_INTERVAL;
	inKeepAlive.keepalivetime		= CLIENT_IOCP_SOCKET_KEEPALIVE_TIME;
		
	int sRet = setsockopt(sock, SOL_SOCKET, SO_KEEPALIVE, (char*)&nKeepAlive, sizeof(nKeepAlive));
		
	sRet = WSAIoctl(sock, _WSAIOW(IOC_VENDOR,4),
					&inKeepAlive,	lInLen,
					&outKeepAlive,	lOutLen,
					&lBytesReturn,	NULL,	NULL);
	
	// 设置SENDBUG
	{
		int nSendBufSize = CLIENT_IOCP_SOCKET_BUF;
		setsockopt(sock, SOL_SOCKET, SO_SNDBUF, (char *) &nSendBufSize, sizeof(nSendBufSize));
	}
	
	// 设置RECVBUG
	{
		int nRecvBufSize = CLIENT_IOCP_SOCKET_BUF;
		setsockopt(sock, SOL_SOCKET, SO_RCVBUF, (char *) &nRecvBufSize, sizeof(nRecvBufSize));
	}

	// 设置SO_SNDTIMEO
	{
		int nNetTimeout = CLIENT_IOCP_SOCKET_TIMOUT;
		setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (char *)&nNetTimeout, sizeof(int));
	}

	// 设置SO_RCVTIMEO
	{
		int nNetTimeout = CLIENT_IOCP_SOCKET_TIMOUT;
		setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char *)&nNetTimeout, sizeof(int));
	}
}

////////////////////////////////////////////////////////////////////////
// Description:  消息尾错误计数增加, 并且超过阀值自动踢号
// Arguments:
// Return Value: void
////////////////////////////////////////////////////////////////////////
void Session::AddTailErrorCountAndAutoBreak( void )
{
	m_dwMsgTailErrorCount++;	// 错误封包计数

	if (m_dwMsgTailErrorCount > FORCE_KICKOUT_ERROR_MSGTAIL_COUNT)
	{
		// 记录日志
		char szLog[512] = "";
		sprintf(szLog, "Our Base is Under Attack! Auto Break Attack! IP[%s], ClientID[%d]", this->GetIP(), this->GetClientID());
		::MyLogSave("syslog/MsgTail", szLog);

		// 发送强踢消息
		struct MY_KICK_REASON
		{
			unsigned short	msgSize;
			unsigned short	msgType;
			int				nReason;
		};
		MY_KICK_REASON stKickInfo = {0};
		stKickInfo.msgSize = sizeof(MY_KICK_REASON);
		stKickInfo.msgType = _MSG_LOGIN_KICK_REASON; // 即 _MSG_KICK_REASON
		stKickInfo.nReason = KICK_REASON_SYSTEM;
		this->Send((BYTE*)&stKickInfo, (WORD)sizeof(stKickInfo));

		// 移除连接
		this->Remove(REMOVE_REASON_UNDER_ATTACK, szLog);
	}
}