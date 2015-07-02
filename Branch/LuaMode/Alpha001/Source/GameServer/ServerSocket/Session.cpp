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

//=============================================================================================================================
/**
	@remarks
			���� ������.\n
			������ ���ۿ� �ޱ� ���۸� �����ϰ� ��� �޸� �ð��� �����Ѵ�.
	@param	dwSendBufferSize
			������ ���� ������
	@param	dwRecvBufferSize
			�ޱ� ���� ������
	@param	dwTimeOut
			�� �ð����� �������� ������ �޼����� ������ ������ ���´�.
			�� ���� 0�̸� �޼��� �۽��� ��� ������ ���� �ʴ´�.
*/
//=============================================================================================================================
Session::Session( DWORD dwSendBufferSize, DWORD dwRecvBufferSize, DWORD dwMaxPacketSize/*, DWORD dwTimeOut*/ )
{
	m_pSendBuffer = new SendBuffer;
	m_pSendBuffer->Create( dwSendBufferSize, dwMaxPacketSize );

	m_pRecvBuffer = new RecvBuffer;
	m_pRecvBuffer->Create( dwRecvBufferSize, dwMaxPacketSize );

	//m_dwTimeOut			= dwTimeOut;
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

//=============================================================================================================================
/**
	@remarks
			������ �ʱ�ȭ�Ѵ�.
	@param	socket
			���ǿ� �Ҵ�� ���� �ڵ�
	@param	sockaddr
			���ǿ� �Ҵ�� ���� �ּ�
	@retval	BOOL
			�־��� ���� �ڵ��� ��ȿ���� ���� ��� FALSE�� �����Ѵ�.
*/
//=============================================================================================================================
VOID Session::Init()
{
	m_pSendBuffer->Clear();
	m_pRecvBuffer->Clear();

	ResetKillFlag();

	m_bDisconnectOrdered = FALSE;

//	m_cEncryptRecv.Init();
//	m_cEncryptSend.Init();

	m_OverlappedIONum = 0;
}

VOID Session::Reuse( HANDLE hIOCP )
{
	//Disconnect�� ovl IO ����
// 	ZeroMemory( &m_disconnectIoData, sizeof(OVERLAPPEDEX) );
// 	m_disconnectIoData.dwOperationType	= DISCONNECT_POSTED;

	// TransmitFile�� �����ϸ� ��� IOCP�� ������ �־��ش�.
// 	if( !MsWinsockUtil::m_lpfnTransmitFile( m_socket, 0, 0, 0, &m_disconnectIoData, 0, TF_DISCONNECT | TF_REUSE_SOCKET )
// 		&& WSAGetLastError() != WSA_IO_PENDING )
// 	{		
// 		CloseSocket();		
// 		PostQueuedCompletionStatus( hIOCP, 0, (ULONG_PTR)this, &m_disconnectIoData );
// 	}


	ZeroMemory( &m_disconnectIoData, sizeof(OVERLAPPEDEX) );
	m_disconnectIoData.dwOperationType	= DISCONNECT_POSTED;

		
	PostQueuedCompletionStatus( hIOCP, 0, (ULONG_PTR)this, &m_disconnectIoData );
	
}

//=============================================================================================================================
/**
	@remarks
			�ش� ��Ŷ�� ������ ���ۿ� ����.
	@param	pMsg
			��Ŷ ������
	@param	wSize
			��� ũ�⸦ ������ ��Ŷ ������
	@retval	BOOL
			���ۿ� ���������� ���⸦ ��ġ�� TRUE�� �����ϰ� ������ ���۰� ���� ��� FALSE�� �����Ѵ�.
*/
//=============================================================================================================================
BOOL Session::Send( BYTE *pMsg, WORD wSize )
{
	if(m_bRemove)
		return FALSE;

	// [���ͻ�����]д��ѭ������, ��������Ͽ�
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

	//���͸�npc����Ϣ
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

//=============================================================================================================================
/**
	@remarks
			IOCP�� send�� �ɾ� ���´�.
	@retval BOOL
			- ������ ���۰� ����ְų� ���� �غ� �ȵ� �����̸� �׳� TRUE�� �����Ѵ�.
			- send�� �����ϸ� FALSE�� �����Ѵ�.
*/
//=============================================================================================================================
BOOL Session::PreSend()
{
	// ����Ͷ����, �ȴ��´�Ͷ��
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

//=============================================================================================================================
/**
	@remarks
			IOCP�� recv�� �ɾ� ���´�.
	@retval BOOL
			recv�� �����ϸ� FALSE�� �����Ѵ�.
*/
//=============================================================================================================================
BOOL Session::PreRecv()
{
	WSABUF wsabuf = {0};

	m_pRecvBuffer->GetRecvParam( (BYTE**)&wsabuf.buf, (int&)wsabuf.len );

	// ���������ͶϿ�
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

	//Session ���� Recv Ptr���� �¾�..
	GetRecvBuffer()->GetRecvParam( &pRecvBuf, nLen );

	//AcceptEx �� ovl IO ����
	ZeroMemory( &m_acceptIoData, sizeof(OVERLAPPEDEX) );
	m_acceptIoData.dwOperationType	= ACCEPT_POSTED;
	m_acceptIoData.pSession			= this;				//�ڽ��� ptr

	//printf("[ACCEPT][%d] Session::PreAccept, m_bRemove=%d\n", (int)GetSocket(), (int)m_bRemove);

	//AcceptEx�� ���� Add
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

	/*
	nZero	= 0;
	nRet	= setsockopt( newSocket, SOL_SOCKET, SO_SNDBUF, (char *)&nZero, sizeof(nZero) );

	if( nRet == SOCKET_ERROR ) 
	{
		return INVALID_SOCKET;
	}
	*/

	return newSocket;
}

//VOID Session::BindNetworkObject( NetworkObject *pNetworkObject )
//{
//	m_pNetworkObject = pNetworkObject;
//	pNetworkObject->SetSession( this );
//}
//
//VOID Session::UnbindNetworkObject()
//{
//	if( m_pNetworkObject == NULL )
//	{
//		return;
//	}
//	m_pNetworkObject->SetSession( NULL );
//
//	m_pNetworkObject = NULL;
//}

VOID Session::OnAccept()
{
	ResetKillFlag();

	//ResetTimeOut();

	//m_pNetworkObject->OnAccept( GetIndex() );

	//printf("[Session::OnAccept][%d] m_bRemove=%d\n", (int)GetSocket(), (int)m_bRemove);
}

//VOID Session::OnConnect( BOOL bSuccess )
//{
//	Init();
//
//	NetworkObject *pNetworkObject = m_pNetworkObject;
//
//	if( !bSuccess )
//	{		
//		UnbindNetworkObject();
//	}
//
//	pNetworkObject->OnConnect( bSuccess, GetIndex() );
//}

//VOID Session::OnLogString( char *pszLog, ... )
//{
//	if( !m_pNetworkObject ) return;
//
//	char		szBuffer[512] = "";
//	va_list		pArguments;
//
//	va_start( pArguments, pszLog );
//	vsprintf( szBuffer, pszLog, pArguments );
//	va_end( pArguments );
//
//	printf( "%s(%s)\n", szBuffer, GetIP() );
//
//	m_pNetworkObject->OnLogString( szBuffer );
//}

// VOID Session::Disconnect( BOOL bGracefulDisconnect )
// { 
// 	if( bGracefulDisconnect ) 
// 	{ 
// 		//printf("[REMOVE][%d] bGracefulDisconnect\n", (int)GetSocket()); 
// 		Remove(12); 
// 	} 
// 	else 
// 	{
// 		m_bDisconnectOrdered = TRUE; 
// 	}
// }


void Session::EncyRecvData(int nSize)
{
	
//	m_cEncryptRecv.Encrypt((unsigned char *)(m_pRecvBuffer->GetWritePtr()),nSize);
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
	InterlockedExchange((LONG*)&m_bSendFlag, FALSE);	// ���·���Ͷ�����ñ�־
	m_nTimeoutCount = 0;
	m_i64RemoveMS = 0;									// �Ͽ���ʱ
}

inline VOID	Session::CloseSocket() 
{ 
//	MyLogSave("syslog/SessionCloseSocket", "SessionCloseSocket socket[%d], ShouldBeRemove[%d]", this->GetClientID(), this->ShouldBeRemoved());
//	shutdown(m_socket, 0x02);
	MsWinsockUtil::m_lpfnDisconnectEx(m_socket, NULL, TF_DISCONNECT, 0);
	closesocket( m_socket ); 
	m_socket = INVALID_SOCKET; 
}

void SetClientSockOpt(SOCKET sock)
{
	// ����SOCKETΪKEEPALIVE
	{
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
	}
	
	// ����SENDBUG
	{
		int nSendBufSize = CLIENT_IOCP_SOCKET_BUF;
		setsockopt(sock, SOL_SOCKET, SO_SNDBUF, (char *) &nSendBufSize, sizeof(nSendBufSize));
	}
	
	// ����RECVBUG
	{
		int nRecvBufSize = CLIENT_IOCP_SOCKET_BUF;
		setsockopt(sock, SOL_SOCKET, SO_RCVBUF, (char *) &nRecvBufSize, sizeof(nRecvBufSize));
	}

	// ����SO_SNDTIMEO
	{
		int nNetTimeout = CLIENT_IOCP_SOCKET_TIMOUT;
		setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (char *)&nNetTimeout, sizeof(int));
	}

	// ����SO_RCVTIMEO
	{
		int nNetTimeout = CLIENT_IOCP_SOCKET_TIMOUT;
		setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char *)&nNetTimeout, sizeof(int));
	}
}