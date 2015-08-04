#include <winsock2.h>
#include <assert.h>
#include "IoHandler.h"
#include "Acceptor.h"
#include "SessionPool.h"
#include "NetBase.h"
#include "Session.h"
#include "SendBuffer.h"
#include "RecvBuffer.h"
#include "IOCPServer.h"
#include "../Share/Define.h"
#include "../Common/BaseFunc.h"

//unsigned __stdcall update_thread(LPVOID param)
//{
//	IoHandler* pIoHandler = (IoHandler*)param;
//
//	while(!(pIoHandler->m_bShutdown))
//	{
//		pIoHandler->Update();
//
//		Sleep(10);
//	}
//
//	return 0;
//}

int IoHandler::MyGetSockError( IN SOCKET s, WSAOVERLAPPED* pWSAOVERLAPPED)
{
	if (NULL == pWSAOVERLAPPED)
	{
		return ERROR_NETNAME_DELETED;
	}

	DWORD dwTrans = 0;
	DWORD dwFlags = 0;
	if(FALSE == WSAGetOverlappedResult(s, pWSAOVERLAPPED, &dwTrans, FALSE, &dwFlags))
		return WSAGetLastError();
	else
		return ERROR_SUCCESS;
}

//=============================================================================================================================
/**
	@remarks
			I/O completion�� �����ϰ� ó���ϴ� ������
	@param	param
			IOCP ������ ������
*/
//=============================================================================================================================
unsigned __stdcall io_thread( LPVOID param )
{
	IoHandler *pIoHandler = (IoHandler*)param;

	BOOL			bSuccess = FALSE;
	DWORD			dwIoSize = 0;

	Session			*pSession = NULL;
	OVERLAPPEDEX	*pOverlappedEx = NULL;

	while( 1 )
	{
		DEBUG_TRY;
		bSuccess = GetQueuedCompletionStatus( pIoHandler->m_hIOCP, &dwIoSize, (LPDWORD)&pSession,
											  (LPOVERLAPPED*)&pOverlappedEx, INFINITE );

		// ����߳�ǿ�йػ�����
		if( pSession == NULL ) 
		{
			break;
		}

		// GQCSʧ�ܴ���
		if( !bSuccess )
		{
			DWORD dwLastError = pIoHandler->MyGetSockError(pSession->GetSocket(), (WSAOVERLAPPED*)pOverlappedEx);

			// sendͶ�ݳ�ʱ, �޸�״̬����send�߳̽����´�Ͷ��
			if (WSAETIMEDOUT == dwLastError && SEND_POSTED == pOverlappedEx->dwOperationType && pSession->GetTimeoutCount() < CLIENT_IOCP_SOCKET_MAX_TIMEOUT_COUNT)
			{
				pSession->AddTimeoutCount();
				pSession->ReleaseOverlappedNum();
				pSession->SetSendFlag(FALSE);
				continue;
			}

			// recvͶ�ݳ�ʱ, �����´�recvͶ��
			if (WSAETIMEDOUT == dwLastError && RECV_POSTED == pOverlappedEx->dwOperationType && pSession->GetTimeoutCount() < CLIENT_IOCP_SOCKET_MAX_TIMEOUT_COUNT)
			{
				pSession->AddTimeoutCount();
				pSession->ReleaseOverlappedNum();
				if( !pSession->PreRecv() )	
				{
					pSession->ReleaseOverlappedNum();
					pSession->Remove(REMOVE_REASON_RECV_TIMEOUT);
				}
				continue;
			}

			char szBuf[128] = "";
			sprintf(szBuf, "ErrorCode[%u] OperationType[%u]", dwLastError, pOverlappedEx->dwOperationType);
			pSession->ReleaseOverlappedNum();
			pSession->Remove(REMOVE_REASON_GQCS_ERROR, szBuf);

			continue;
		}

		// DISCONNECT_POSTED�� �ƴѵ��� IoSize�� 0�� ��� ���� ����
		if( pOverlappedEx->dwOperationType != DISCONNECT_POSTED && dwIoSize == 0 )
		{
			pSession->ReleaseOverlappedNum();
			pSession->Remove(REMOVE_REASON_CLIENT_BREAK, "Client Break Connect!");
			continue;
		}

		// Completion ó��
		switch( pOverlappedEx->dwOperationType )
		{
		case SEND_POSTED:
			pSession->ReleaseOverlappedNum();
			pSession->GetSendBuffer()->Completion( dwIoSize );
			pSession->SetSendFlag(FALSE);
			break;

		case RECV_POSTED:
			//�Խ��ܵ������ݽ��н���
			pSession->ReleaseOverlappedNum();
//			pSession->EncyRecvData(dwIoSize);
			pSession->GetRecvBuffer()->Completion( dwIoSize );
			// ���� Recv	
			if( !pSession->PreRecv() )	
			{
				pSession->ReleaseOverlappedNum();
				pSession->Remove(REMOVE_REASON_PRERECV_ERROR);
			}
			break;

		case DISCONNECT_POSTED:
			pSession->PreAccept( pIoHandler->m_pAcceptor->GetListenSocket() );
			break;
		}
		DEBUG_CATCH("io_thread");
	}

	return 0;
}

IoHandler::IoHandler()
{
	m_pAcceptSessionPool		= NULL;
	//m_pConnectSessionPool		= NULL;
	m_pAcceptor					= NULL;
	//m_pConnector				= NULL;
	m_pActiveSessionList		= NULL;
	m_pAcceptedSessionList		= NULL;
	m_pReuseSessionList			= NULL;
	m_pDeadSessionList			= NULL;
	//m_pConnectSuccessList		= NULL;
	//m_pConnectFailList			= NULL;
	m_pTempList					= NULL;
	m_numActiveSessions			= 0;
	m_bShutdown					= FALSE;
	m_dwKickCheckSecond			= ::TimeGet(TIME_SECOND);

	for( DWORD i = 0; i < CLIENT_IOCP_MAX_IO_WORKER_THREAD_COUNT; ++i ) 
	{
		m_hIoThread[i] = NULL;
	}

	// m_hUpdateThread = NULL;
	//m_fnCreateAcceptedObject	= NULL;
	//m_fnDestroyAcceptedObject	= NULL;
	//m_fnDestroyConnectedObject	= NULL;
}

IoHandler::~IoHandler()
{
	if( !m_bShutdown ) Shutdown();

	for( DWORD i = 0; i < m_numIoThreads; ++i )
	{
		if( m_hIoThread[i] ) CloseHandle( m_hIoThread[i] );
	}

//	if(m_hUpdateThread)
//		CloseHandle(m_hUpdateThread);

	if( m_pAcceptSessionPool )		delete m_pAcceptSessionPool;
	//if( m_pConnectSessionPool )		delete m_pConnectSessionPool;
	if( m_pAcceptor )				delete m_pAcceptor;
	//if( m_pConnector )				delete m_pConnector;
	if( m_pActiveSessionList )		delete m_pActiveSessionList;
	if( m_pAcceptedSessionList )	delete m_pAcceptedSessionList;
	if( m_pReuseSessionList )		delete m_pReuseSessionList;
	//if( m_pConnectSuccessList )		delete m_pConnectSuccessList;
	//if( m_pConnectFailList )		delete m_pConnectFailList;
	if( m_pTempList )				delete m_pTempList;
	if(m_pDeadSessionList)			delete m_pDeadSessionList;
}

VOID IoHandler::Init( IOCPServer *pIOCPServer, LPIOHANDLER_DESC lpDesc )
{
	m_pIOCPServer	= pIOCPServer;

	// �ݹ� �Լ� ������ ��ȿ�� �˻�
//	CHECK( !IsBadReadPtr( lpDesc->fnCreateAcceptedObject, sizeof(lpDesc->fnCreateAcceptedObject) ) );
//	CHECK( !IsBadReadPtr( lpDesc->fnDestroyAcceptedObject, sizeof(lpDesc->fnDestroyAcceptedObject) ) );
//	CHECK( !IsBadReadPtr( lpDesc->fnDestroyConnectedObject, sizeof(lpDesc->fnDestroyConnectedObject) ) );
//	
	// �ݹ� �Լ� ������ ����
//	m_fnCreateAcceptedObject		= lpDesc->fnCreateAcceptedObject;
//	m_fnDestroyAcceptedObject		= lpDesc->fnDestroyAcceptedObject;
//	m_fnDestroyConnectedObject		= lpDesc->fnDestroyConnectedObject;

	m_dwKey				= lpDesc->dwIoHandlerKey;
	
	// ���� ����Ʈ ����
	m_pActiveSessionList	= new SessionList;
	m_pAcceptedSessionList	= new SessionList;
	m_pReuseSessionList		= new SessionList;
	//m_pConnectSuccessList	= new SessionList;
	//m_pConnectFailList		= new SessionList;
	m_pTempList				= new SessionList;
	m_pDeadSessionList		= new SessionList;

	// �ִ� ���� ���� �ο�
	m_dwMaxAcceptSession	= lpDesc->dwMaxAcceptSession;

	// ���� Ǯ ����
	m_pAcceptSessionPool	= new SessionPool( lpDesc->dwMaxAcceptSession,
											   lpDesc->dwSendBufferSize,
											   lpDesc->dwRecvBufferSize,
											   lpDesc->dwMaxPacketSize,
											   /*lpDesc->dwTimeOut,*/
											   1,
											   TRUE );

//	m_pConnectSessionPool	= new SessionPool( lpDesc->dwMaxConnectSession,
//											   lpDesc->dwSendBufferSize,
//											   lpDesc->dwRecvBufferSize,
//											   lpDesc->dwMaxPacketSize,
//											   lpDesc->dwTimeOut,
//											   m_pAcceptSessionPool->GetLength() + 1,
//											   FALSE );

	
	// �ִ� ��Ŷ ũ�� ����
	//CHECK( lpDesc->dwMaxPacketSize > sizeof(PACKET_HEADER) );
	m_dwMaxPacketSize =	lpDesc->dwMaxPacketSize;
  
	// IOCP ����
	m_hIOCP = CreateIoCompletionPort( INVALID_HANDLE_VALUE, NULL, 0, 0 );

	unsigned threadID;

	// IO ��Ŀ ������ ����
	CHECKB(lpDesc->dwNumberOfIoThreads <= CLIENT_IOCP_MAX_IO_WORKER_THREAD_COUNT);
	m_numIoThreads = lpDesc->dwNumberOfIoThreads;
	for( DWORD i = 0; i < m_numIoThreads; ++i )
	{
		m_hIoThread[i] = (HANDLE)_beginthreadex( NULL, 0, io_thread, (LPVOID)this, 0, &threadID );
	}


// 	m_hUpdateThread = (HANDLE)_beginthreadex( NULL, 0, update_thread, (LPVOID)this, 0, &threadID );

	// ����� ����
	m_pAcceptor		= new Acceptor;
	m_pAcceptor->Init( this, lpDesc->dwNumberOfAcceptThreads );

	// Ŀ���� ����	
	//m_pConnector	= new Connector;
	//m_pConnector->Init( this, lpDesc->dwNumberOfConnectThreads );
}

//DWORD IoHandler::Connect( NetworkObject *pNetworkObject, char *pszIP, WORD wPort )
//{
//	// �ش� NetworkObject�� ������ �̹� Ŀ��Ʈ �õ����̸� �����Ѵ�.
//	if( pNetworkObject->m_pSession != NULL ) return 0;
//
//	// ���� ����
//	SOCKET socket = WSASocket( AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED );
//
//	// �ּ� ����
//	SOCKADDR_IN addr;
//
//	addr.sin_family			= AF_INET;
//	addr.sin_addr.s_addr	= inet_addr( pszIP );
//	addr.sin_port			= htons( wPort );
//
//	// ���� �Ҵ�
//	Session *pSession = AllocConnectSession();
//	CHECKF( pSession != NULL && "������ ���ڶ� Connect �� �� �����ϴ�. dwMaxConnectSession ������ Ȯ�����ּ���" );
//
//	// ���ǿ� ���� �� �ּ� ����
//	pSession->SetSocket( socket );
//	pSession->SetSockAddr( addr );
//
//	// ������ ��Ʈ�� ������Ʈ�� ���ε�
//	CHECKF( pNetworkObject != NULL );
//	pSession->BindNetworkObject( pNetworkObject );
//
//	m_pConnector->Connect( pSession );
//
//	return pSession->GetIndex();
//}

//=============================================================================================================================
/**
	@remarks
			���� ������ �����ϰ� ������ �����Ѵ�.
	@retval	BOOL
			���� ���� ������ �����ϸ� FALSE�� �����Ѵ�.
	@param	pIP
			������ ����� IP
	@param	wPort
			������ ����� ��Ʈ
*/
//=============================================================================================================================
BOOL IoHandler::StartListen( char *pIP, WORD wPort )
{
	CHECKF( m_dwMaxAcceptSession > 0 );

	// �̹� �������̶�� ���� ó��
	if( IsListening() ) return TRUE;

	if( !m_pAcceptor->StartListen( pIP, wPort ) )
	{
		//printf( "Listen socket creation failed.\n" );
		return FALSE;
	}

	Session *pSession;
	while( pSession = AllocAcceptSession() )
	{
		pSession->PreAccept( m_pAcceptor->GetListenSocket() );
		m_sessionListHolder.push_back(pSession);///���Ự���������Ա�����ͷŵ�
	}

	return TRUE;
}

BOOL IoHandler::IsListening()
{
	return m_pAcceptor->IsListening();
}

//=============================================================================================================================
/**
	@remarks
			������̴� ���ǵ��� ��� ����Ǯ�� ��ȯ�Ѵ�.
*/
//=============================================================================================================================

Session* IoHandler::AllocAcceptSession()
{
	return m_pAcceptSessionPool->Alloc();
}

//Session* IoHandler::AllocConnectSession()
//{
//	return m_pConnectSessionPool->Alloc();
//}

VOID IoHandler::FreeSession( Session *pSession )
{
	//printf("[FreeSession][%d]\n", (int)pSession->GetSocket());
	pSession->CloseSocket();
	pSession->Init();
	if( pSession->IsAcceptSocket() )
	{
		m_pAcceptSessionPool->Free( pSession );
	}
//	else
//	{
//		m_pConnectSessionPool->Free( pSession );
//	}
}

VOID IoHandler::ReuseSession( Session *pSession )
{
	//printf("[ReuseSession][%d]\n", (int)pSession->GetSocket());
	pSession->Reuse( m_hIOCP );
}

//=============================================================================================================================
/**
	@remarks
			���ӿ� ������ ���� ����Ʈ ó��
	@par
			ConnectSuccessList�� �ִ� ���ǵ��� IOCP�� ����ϰ� OnConnect(TRUE)�� ȣ���ϰ� ActiveSessionList�� �߰��Ѵ�.
*/
//=============================================================================================================================
//VOID IoHandler::ProcessConnectSuccessList()
//{
//	SESSION_LIST_ITER		it;
//	Session					*pSession;
//
//	// Ŀ��Ʈ�� ������ ���ǵ��� �ӽ� ����Ʈ�� �ű�
//	m_pConnectSuccessList->Lock();
//	m_pTempList->splice( m_pTempList->end(), *m_pConnectSuccessList );
//	m_pConnectSuccessList->Unlock();
//
//	for( it = m_pTempList->begin(); it != m_pTempList->end(); ++it )
//	{
//		pSession = *it;
//
//		// IOCP�� �ڵ� ���
//		CreateIoCompletionPort( (HANDLE)pSession->GetSocket(), m_hIOCP, (ULONG_PTR)pSession, 0 );
//
//		if( pSession->PreRecv() )
//		{
//			pSession->OnConnect( TRUE );
//		}
//		else
//		{
//			m_pTempList->erase( it-- );
//
//			// ���� Ǯ�� ��ȯ
//			FreeSession( pSession );
//
//			pSession->OnConnect( FALSE );
//		}
//	}
//
//	if( !m_pTempList->empty() )
//	{
//		// ������ ����
//		m_numActiveSessions += (DWORD)m_pTempList->size();
//
//		// Ŀ��Ʈ�� ������ ���ǵ��� ActiveSessionList�� �߰��Ѵ�.
//		m_pActiveSessionList->Lock();
//		m_pActiveSessionList->splice( m_pActiveSessionList->end(), *m_pTempList );
//		m_pActiveSessionList->Unlock();
//	}
//}

//=============================================================================================================================
/**
	@remarks
			���ӿ� ������ ���� ����Ʈ ó��
	@par
			ConnectFailList�� �ִ� ���ǵ鿡 ���� OnConnect(FALSE)�� ȣ���Ѵ�.
*/
//=============================================================================================================================
//VOID IoHandler::ProcessConnectFailList()
//{
//	SESSION_LIST_ITER		it;
//	Session					*pSession;
//
//	m_pConnectFailList->Lock();
//
//	for( it = m_pConnectFailList->begin(); it != m_pConnectFailList->end(); ++it )
//	{
//		pSession = *it;
//
//		// ���� Ǯ�� ��ȯ
//		FreeSession( pSession );
//
//		pSession->OnConnect( FALSE );
//	}
//
//	m_pConnectFailList->clear();
//	m_pConnectFailList->Unlock();
//}

//=============================================================================================================================
/**
	@remarks
			TempSessionList�� �ִ� ���ǵ��� IOCP�� ����ϰ� ActiveSessionList�� �ű�� OnAccpet()�� ȣ���Ѵ�.
*/
//=============================================================================================================================
VOID IoHandler::ProcessAcceptedSessionList()
{
	DEBUG_TRY;
	// ���ӿ� ������ ���ǵ��� �޾Ƶ� �ӽ� ����Ʈ�� �ű�
	m_pAcceptedSessionList->Lock();
	m_pTempList->splice( m_pTempList->end(), *m_pAcceptedSessionList );
	m_pAcceptedSessionList->Unlock();

	// ���ӿ� ������ ���ǿ� ���� ó��
	bool bIncrement = true;
	Session* pSession = NULL;
	SESSION_LIST_ITER iter = m_pTempList->begin();
	for(; iter != m_pTempList->end();)
	{
		bIncrement = true;
		pSession   = *iter;

		// �ְ������� �ʰ��ϴ� ��� ����
		if( m_numActiveSessions >= m_dwMaxAcceptSession )
		{
			LOGWARNING("connection full! m_numActiveSessions = %u,m_dwMaxAcceptSession = %u",m_numActiveSessions,m_dwMaxAcceptSession);
			//printf( "connection full! no available accept socket!\n" );
			bIncrement = false;
			iter = m_pTempList->erase(iter);
			ReuseSession( pSession );
			//pSession->CloseSocket();
			m_pReuseSessionList->push_back(pSession);
			continue;
		}

		// IOCP�� �ڵ� ���
		CreateIoCompletionPort( (HANDLE)pSession->GetSocket(), m_hIOCP, (ULONG_PTR)pSession, 0 );

		pSession->SetIoHandler(this);
		pSession->SetClientID(m_pIOCPServer->SetNewClientSocket(pSession));

		// Recv�� �����ϴ� ��� ó��
		if( !pSession->PreRecv() )
		{
			bIncrement = false;
			iter = m_pTempList->erase(iter);
			//pSession->CloseSocket();
			ReuseSession(pSession);
			m_pReuseSessionList->push_back(pSession);
			//ReuseSession( pSession );
			continue;
		}

		//--------------------------------
		// ���������� ���ӵ� ���� ó��
		//--------------------------------

		// ��Ʈ�� ������Ʈ ���� ��û
		//NetworkObject *pNetworkObject = m_fnCreateAcceptedObject();
		//CHECKC( pNetworkObject );

		// ��Ʈ�� ������Ʈ ���ε�
		//pSession->BindNetworkObject( pNetworkObject );

		// ���ӽ� �ʱ�ȭ �� NetworkObject�� ���� ����
		pSession->OnAccept();

		// ������ ����
		++m_numActiveSessions;

		// �������������
		if (bIncrement)
		{
			iter++;
		}
	}

	if( !m_pTempList->empty() )
	{
		// ���ӿ� ������ ���ǵ��� ActiveSessionList�� �߰�
//		m_pActiveSessionList->Lock();
		m_pActiveSessionList->splice( m_pActiveSessionList->begin(), *m_pTempList );
//		m_pActiveSessionList->Unlock();
	}
	DEBUG_CATCH("IoHandler::ProcessAcceptedSessionList crash!")
}

//=============================================================================================================================
/**
	@remarks
			���� accept �Ǵ� connect�Ǿ� Ȱ��ȭ�� ���ǵ��� ��ȸ�ϸ� ���� ��Ŷ ���� ó���Ѵ�.
*/
//=============================================================================================================================
VOID IoHandler::ProcessActiveSessionList()
{
	DEBUG_TRY;
	bool bIncrement = true;
	Session* pSession = NULL;
	SESSION_LIST_ITER iter = m_pActiveSessionList->begin();
	for(;iter != m_pActiveSessionList->end();)
	{
		bIncrement = true;

		// ���Ự����Ч��
		pSession = *iter;
		CHECKC_NOLOG(pSession);
		CHECKC(Session::IsValidPt(pSession));

		// ������
		if(FALSE == pSession->PreSend()) 
		{
			pSession->Remove(REMOVE_REASON_PRESEND_ACTIVELIST);
		}

		// �����Ƴ��Ự
		if(pSession->ShouldBeRemoved())
		{
			bIncrement = false;
			iter = m_pActiveSessionList->erase(iter);
			m_pDeadSessionList->push_back( pSession );
			continue;
		}
		
		// ������հ�
		if(!pSession->ProcessRecvdPacket(m_dwMaxPacketSize))
		{
			pSession->Remove(REMOVE_REASON_RECV_PROCESS);
		}

		// ����������
		if (bIncrement)
		{
			iter++;
		}
	}
	DEBUG_CATCH("IoHandler::ProcessActiveSessionList crash!")
}

//=============================================================================================================================
/**
	@remarks
			���� �ð� �̻� ��Ŷ �۽��� ���� ���ǵ��� �����Ѵ�.
*/
//=============================================================================================================================
VOID IoHandler::KickDeadSessions()
{
	const I64 i64NowMS = ::GetUtcMillisecond();
	std::vector<Session*> vecSessionHaveSend;

	// ����������б�
	for(SESSION_LIST_ITER itList = m_pDeadSessionList->begin(); itList != m_pDeadSessionList->end(); ++itList )
	{
		Session* pSession = *itList;
		if (NULL == pSession)
		{
			continue;
		}

		// ��ǿ�����Ƴ�(��ҪԴ�ڵײ����, ���߿ͻ��˶Ͽ�����), ����һ�����Ὣ��Ϣ������
		if (pSession->GetRemoveReason() > REMOVE_REASON_NONE && pSession->GetRemoveReason() < REMOVE_REASON_FORCE_BEGIN)
		{
			// ���������Ϣû���ͻ��˷���������ڷ�����, ���ͻ���3��Ļ���, ����Ϣ����, ��ʱ��ǿ�л���
			if ((pSession->GetSendBuffer()->GetLength() > 0 || pSession->GetSendFlag()) && 
				pSession->GetRemoveMS() + FORCE_PROCESS_DEAD_SESSION_MS > i64NowMS)
			{
				pSession->PreSend();
				vecSessionHaveSend.push_back(pSession);
				continue;
			}
		}

		// ����Sessionʱ, ����仺����
		pSession->GetRecvBuffer()->Clear();
		pSession->GetSendBuffer()->Clear();

		// ��Ự����
		--m_numActiveSessions;	

		// ֪ͨ�ϲ�ɾ��������break���
		m_pIOCPServer->ProcessDisconnectClient(pSession->GetClientID());

		// û�н���shutdown���̵Ļ��ͻ���
		if( pSession->IsAcceptSocket() && !m_bShutdown )
		{
			pSession->CloseSocket();
			m_pReuseSessionList->push_back(pSession);
		}
		else											
		{
			FreeSession( pSession );
		} 
	}

	m_pDeadSessionList->clear();
	for (std::vector<Session*>::iterator itVec = vecSessionHaveSend.begin(); itVec != vecSessionHaveSend.end(); itVec++)
	{
		Session* pSession = *itVec;
		CHECKC(pSession);
		CHECKC(Session::IsValidPt(pSession));
		m_pDeadSessionList->push_back(pSession);
	}
}

VOID IoHandler::ProcessSend()
{
	SESSION_LIST_ITER	it;
	Session				*pSession;

	// ActiveSessionList�� ������ ������ �۹� ����
	m_pActiveSessionList->Lock();
	for( it = m_pActiveSessionList->begin(); it != m_pActiveSessionList->end(); ++it )
	{
		pSession = *it;

		if( pSession->PreSend() == FALSE ) 
		{
			//printf("[REMOVE][%d] pSession->PreSend() == FALSE\n", (int)pSession->GetSocket());
			pSession->Remove(REMOVE_REASON_PRESEND_ALL);
		}
	}
	m_pActiveSessionList->Unlock();
}

//=============================================================================================================================
/**
	@remarks
			��� ���ǵ��� �����Ѵ�.
*/
//=============================================================================================================================
VOID IoHandler::KickAllSessions()
{
	SESSION_LIST_ITER	it;

	for( it = m_pActiveSessionList->begin(); it != m_pActiveSessionList->end(); ++it )
	{
		(*it)->Remove(REMOVE_REASON_KILL_ALL_SESSION);
	}
}

//=============================================================================================================================
/**
	@remarks
			Accept�� ���ǰ� Connect�� ���ǵ��� IOCP�� ����ϸ鼭 ActiveSessionList�� �ű��
			��� ������ �ޱ� ���۸� �˻��Ͽ� ��Ŷ�� ó���ϴ� ���� �۾��� �Ѵ�.
	@par
			�� �Լ��� �ֱ������� ȣ���� �־�� �Ѵ�.
*/
//=============================================================================================================================
VOID IoHandler::Update()
{
	m_pActiveSessionList->Lock();///���̼߳���
	ProcessActiveSessionList();
//	CheckMutiConnect();
	m_pActiveSessionList->Unlock();///���߳̽���

	if( !m_pAcceptedSessionList->empty() )
	{
		ProcessAcceptedSessionList();
	}

//	if( !m_pConnectSuccessList->empty() )
//	{
//		ProcessConnectSuccessList();
//	}
//
//	if( !m_pConnectFailList->empty() )
//	{
//		ProcessConnectFailList();
//	}

	KickDeadSessions();

	ProcessReuseSessionList();
}


VOID IoHandler::Shutdown()
{
	m_bShutdown = TRUE;

	KickAllSessions();

	ProcessActiveSessionList();

	KickDeadSessions();

	m_pAcceptor->Shutdown();


	//m_pConnector->Shutdown();

	// IOCP ������ ����
	for( DWORD i = 0; i < m_numIoThreads; ++i )
	{
		PostQueuedCompletionStatus( m_hIOCP, 0, 0, NULL );
	}

	// IO ��Ŀ �����尡 ��� ����� ������ ��ٸ���.
	WaitForMultipleObjects( m_numIoThreads, m_hIoThread, TRUE, INFINITE );

	///��Σ����
	for(int j=0;j<(int)m_sessionListHolder.size();++j)
	{
		Session* pSession=m_sessionListHolder[j];
		if(pSession->GetSocket()!=INVALID_SOCKET)
			FreeSession(pSession);
	}
	m_sessionListHolder.clear();
	///��Σ����
}

VOID IoHandler::ProcessReuseSessionList()
{
	DEBUG_TRY;
	bool bIncrement = true;
	SESSION_LIST_ITER iter = m_pReuseSessionList->begin();
	for(;iter != m_pReuseSessionList->end();)
	{
		bIncrement = true;

		// ����Ự����
 		if((*iter)->CanReuse())
 		{
			Session* pSession = *iter;
			ReuseSession(pSession);
			iter = m_pReuseSessionList->erase(iter);
			bIncrement = false;
		}

		// �������������
		if (bIncrement)
		{
			iter++;
		}
	}
	DEBUG_CATCH("IoHandler::ProcessReuseSessionList crash!")
}

////////////////////////////////////////////////////////////////////////
// Description:  ����������
// Arguments:	 ÿ���Ӽ��һ�� ͬһ��ip����36������, ���Զ��Ͽ����ip��ȫ������
// Author: ������(Peng Wenqi)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void IoHandler::CheckMutiConnect()
{
	DWORD dwNowSecond = ::TimeGet(TIME_SECOND);
	if (dwNowSecond < m_dwKickCheckSecond + 60)
	{
		return;
	}
	m_dwKickCheckSecond = dwNowSecond;

	typedef std::map<std::string, int> MAP_IP_COUNT;
	MAP_IP_COUNT mapIpCount;
	
	DEBUG_TRY;
	for (SESSION_LIST_ITER it=m_pActiveSessionList->begin(); it != m_pActiveSessionList->end(); ++it )
	{

		Session*	pSession = *it;

		if(NULL==pSession)///���Ϊ��ֱ�Ӻ���
			continue;
		CHECKC(Session::IsValidPt(pSession));

		if (pSession->ShouldBeRemoved())
			continue;

		std::string strIP = pSession->GetIP();
		if (mapIpCount.find(strIP) == mapIpCount.end())
		{
			mapIpCount[strIP] = 1;
		}
		else
		{
			mapIpCount[strIP] += 1;
		}
	}

	for (SESSION_LIST_ITER it=m_pActiveSessionList->begin(); it != m_pActiveSessionList->end(); ++it )
	{

		Session*	pSession = *it;

		if(NULL==pSession)///���Ϊ��ֱ�Ӻ���
			continue;
		CHECKC(Session::IsValidPt(pSession));

		if (pSession->ShouldBeRemoved())
			continue;

		std::string strIP = pSession->GetIP();
		if (mapIpCount.find(strIP) == mapIpCount.end())
		{
			continue;
		}
		else
		{
			if (mapIpCount[strIP] > 36)
			{
				char szReason[128] = "";
				sprintf(szReason, "Too many connect! ip[%s]", strIP.c_str());
				pSession->Remove(REMOVE_REASON_TOO_MANY_CONNECT, szReason);
			}
		}
	}

	DEBUG_CATCH("IoHandler::CheckMutiConnect crash!")
}
