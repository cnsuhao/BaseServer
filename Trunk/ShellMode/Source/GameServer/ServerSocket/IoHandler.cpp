#include "../MSGSERVER/share/define.h"
#include <winsock2.h>
#include <assert.h>
#include "IoHandler.h"
#include "Acceptor.h"
//#include "Connector.h"
#include "SessionPool.h"
#include "NetBase.h"
#include "Session.h"
#include "SendBuffer.h"
#include "RecvBuffer.h"
#include "IOCPServer.h"
//#include "NetworkObject.h"
/*#include "../share/define.h"*/
#include "./../COMMON/BaseFunc.h"

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
			I/O completion을 감시하고 처리하는 쓰레드
	@param	param
			IOCP 서버의 포인터
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

		// 흔벎窟넋퓻契밑샙츱즈
		if( pSession == NULL ) 
		{
			break;
		}

		// GQCS呵겨뇹잿
		if( !bSuccess )
		{
			DWORD dwLastError = pIoHandler->MyGetSockError(pSession->GetSocket(), (WSAOVERLAPPED*)pOverlappedEx);

			// send尻뒵낚珂, 錦맣榴檄豚冀send窟넋쏵契苟늴尻뒵
			if (WSAETIMEDOUT == dwLastError && SEND_POSTED == pOverlappedEx->dwOperationType && pSession->GetTimeoutCount() < CLIENT_IOCP_SOCKET_MAX_TIMEOUT_COUNT)
			{
				pSession->AddTimeoutCount();
				pSession->ReleaseOverlappedNum();
				pSession->SetSendFlag(FALSE);
				continue;
			}

			// recv尻뒵낚珂, 쏵契苟늴recv尻뒵
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

		// DISCONNECT_POSTED가 아닌데도 IoSize가 0인 경우 세션 제거
		if( pOverlappedEx->dwOperationType != DISCONNECT_POSTED && dwIoSize == 0 )
		{
			pSession->ReleaseOverlappedNum();
			pSession->Remove(REMOVE_REASON_CLIENT_BREAK, "Client Break Connect!");
			continue;
		}

		// Completion 처리
		switch( pOverlappedEx->dwOperationType )
		{
		case SEND_POSTED:
			pSession->ReleaseOverlappedNum();
			pSession->GetSendBuffer()->Completion( dwIoSize );
			pSession->SetSendFlag(FALSE);
			break;

		case RECV_POSTED:
			//뚤쌈肝돕돨鑒앴쏵契썩쵱
			pSession->ReleaseOverlappedNum();
//			pSession->EncyRecvData(dwIoSize);
			pSession->GetRecvBuffer()->Completion( dwIoSize );
			// 다음 Recv	
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

	// 콜백 함수 포인터 유효성 검사
//	CHECK( !IsBadReadPtr( lpDesc->fnCreateAcceptedObject, sizeof(lpDesc->fnCreateAcceptedObject) ) );
//	CHECK( !IsBadReadPtr( lpDesc->fnDestroyAcceptedObject, sizeof(lpDesc->fnDestroyAcceptedObject) ) );
//	CHECK( !IsBadReadPtr( lpDesc->fnDestroyConnectedObject, sizeof(lpDesc->fnDestroyConnectedObject) ) );
//	
	// 콜백 함수 포인터 저장
//	m_fnCreateAcceptedObject		= lpDesc->fnCreateAcceptedObject;
//	m_fnDestroyAcceptedObject		= lpDesc->fnDestroyAcceptedObject;
//	m_fnDestroyConnectedObject		= lpDesc->fnDestroyConnectedObject;

	m_dwKey				= lpDesc->dwIoHandlerKey;
	
	// 세션 리스트 생성
	m_pActiveSessionList	= new SessionList;
	m_pAcceptedSessionList	= new SessionList;
	m_pReuseSessionList		= new SessionList;
	//m_pConnectSuccessList	= new SessionList;
	//m_pConnectFailList		= new SessionList;
	m_pTempList				= new SessionList;
	m_pDeadSessionList		= new SessionList;

	// 최대 접속 제한 인원
	m_dwMaxAcceptSession	= lpDesc->dwMaxAcceptSession;

	// 세션 풀 생성
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

	
	// 최대 패킷 크기 설정
	//CHECK( lpDesc->dwMaxPacketSize > sizeof(PACKET_HEADER) );
	m_dwMaxPacketSize =	lpDesc->dwMaxPacketSize;
  
	// IOCP 생성
	m_hIOCP = CreateIoCompletionPort( INVALID_HANDLE_VALUE, NULL, 0, 0 );

	unsigned threadID;

	// IO 워커 쓰레드 생성
	CHECKB(lpDesc->dwNumberOfIoThreads <= CLIENT_IOCP_MAX_IO_WORKER_THREAD_COUNT);
	m_numIoThreads = lpDesc->dwNumberOfIoThreads;
	for( DWORD i = 0; i < m_numIoThreads; ++i )
	{
		m_hIoThread[i] = (HANDLE)_beginthreadex( NULL, 0, io_thread, (LPVOID)this, 0, &threadID );
	}


// 	m_hUpdateThread = (HANDLE)_beginthreadex( NULL, 0, update_thread, (LPVOID)this, 0, &threadID );

	// 억셉터 생성
	m_pAcceptor		= new Acceptor;
	m_pAcceptor->Init( this, lpDesc->dwNumberOfAcceptThreads );

	// 커넥터 생성	
	//m_pConnector	= new Connector;
	//m_pConnector->Init( this, lpDesc->dwNumberOfConnectThreads );
}

//DWORD IoHandler::Connect( NetworkObject *pNetworkObject, char *pszIP, WORD wPort )
//{
//	// 해당 NetworkObject의 소켓이 이미 커넥트 시도중이면 리턴한다.
//	if( pNetworkObject->m_pSession != NULL ) return 0;
//
//	// 소켓 생성
//	SOCKET socket = WSASocket( AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED );
//
//	// 주소 셋팅
//	SOCKADDR_IN addr;
//
//	addr.sin_family			= AF_INET;
//	addr.sin_addr.s_addr	= inet_addr( pszIP );
//	addr.sin_port			= htons( wPort );
//
//	// 세션 할당
//	Session *pSession = AllocConnectSession();
//	CHECKF( pSession != NULL && "세션이 모자라서 Connect 할 수 없습니다. dwMaxConnectSession 개수를 확인해주세요" );
//
//	// 세션에 소켓 및 주소 셋팅
//	pSession->SetSocket( socket );
//	pSession->SetSockAddr( addr );
//
//	// 세션을 네트웍 오브젝트와 바인딩
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
			리슨 소켓을 생성하고 리슨을 시작한다.
	@retval	BOOL
			리슨 소켓 생성에 실패하면 FALSE를 리턴한다.
	@param	pIP
			리슨에 사용할 IP
	@param	wPort
			리슨에 사용할 포트
*/
//=============================================================================================================================
BOOL IoHandler::StartListen( char *pIP, WORD wPort )
{
	CHECKF( m_dwMaxAcceptSession > 0 );

	// 이미 리슨중이라면 성공 처리
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
		m_sessionListHolder.push_back(pSession);///쉥삔뺐괏닸苟윱鹿긱빈충姦렴딜
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
			사용중이던 세션들을 모두 세션풀에 반환한다.
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
			접속에 성공한 세션 리스트 처리
	@par
			ConnectSuccessList에 있는 세션들을 IOCP에 등록하고 OnConnect(TRUE)를 호출하고 ActiveSessionList에 추가한다.
*/
//=============================================================================================================================
//VOID IoHandler::ProcessConnectSuccessList()
//{
//	SESSION_LIST_ITER		it;
//	Session					*pSession;
//
//	// 커넥트에 성공한 세션들을 임시 리스트로 옮김
//	m_pConnectSuccessList->Lock();
//	m_pTempList->splice( m_pTempList->end(), *m_pConnectSuccessList );
//	m_pConnectSuccessList->Unlock();
//
//	for( it = m_pTempList->begin(); it != m_pTempList->end(); ++it )
//	{
//		pSession = *it;
//
//		// IOCP에 핸들 등록
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
//			// 세션 풀에 반환
//			FreeSession( pSession );
//
//			pSession->OnConnect( FALSE );
//		}
//	}
//
//	if( !m_pTempList->empty() )
//	{
//		// 동접수 증가
//		m_numActiveSessions += (DWORD)m_pTempList->size();
//
//		// 커넥트에 성공한 세션들을 ActiveSessionList에 추가한다.
//		m_pActiveSessionList->Lock();
//		m_pActiveSessionList->splice( m_pActiveSessionList->end(), *m_pTempList );
//		m_pActiveSessionList->Unlock();
//	}
//}

//=============================================================================================================================
/**
	@remarks
			접속에 실패한 세션 리스트 처리
	@par
			ConnectFailList에 있는 세션들에 대해 OnConnect(FALSE)을 호출한다.
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
//		// 세션 풀에 반환
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
			TempSessionList에 있는 세션들을 IOCP에 등록하고 ActiveSessionList로 옮기고 OnAccpet()를 호출한다.
*/
//=============================================================================================================================
VOID IoHandler::ProcessAcceptedSessionList()
{
	SESSION_LIST_ITER		it;
	Session					*pSession;

	// 접속에 성공한 세션들을 받아둔 임시 리스트로 옮김
	m_pAcceptedSessionList->Lock();
	m_pTempList->splice( m_pTempList->end(), *m_pAcceptedSessionList );
	m_pAcceptedSessionList->Unlock();

	// 접속에 성공한 세션에 대한 처리
	for( it = m_pTempList->begin(); it != m_pTempList->end(); ++it )
	{
		pSession = *it;

		// 최고동접수를 초과하는 경우 실패
		if( m_numActiveSessions >= m_dwMaxAcceptSession )
		{
			LOGWARNING("connection full! m_numActiveSessions = %u,m_dwMaxAcceptSession = %u",m_numActiveSessions,m_dwMaxAcceptSession);
			//printf( "connection full! no available accept socket!\n" );
			m_pTempList->erase( it-- );
			ReuseSession( pSession );
			//pSession->CloseSocket();
			m_pReuseSessionList->push_back(pSession);
			continue;
		}

		// IOCP에 핸들 등록
		CreateIoCompletionPort( (HANDLE)pSession->GetSocket(), m_hIOCP, (ULONG_PTR)pSession, 0 );

		pSession->SetIoHandler(this);
		pSession->SetClientID(m_pIOCPServer->SetNewClientSocket(pSession));

		// Recv에 실패하는 경우 처리
		if( !pSession->PreRecv() )
		{
			m_pTempList->erase( it-- );
			//pSession->CloseSocket();
			ReuseSession(pSession);
			m_pReuseSessionList->push_back(pSession);
			//ReuseSession( pSession );
			continue;
		}

		//--------------------------------
		// 성공적으로 접속된 세션 처리
		//--------------------------------

		// 네트웍 오브젝트 생성 요청
		//NetworkObject *pNetworkObject = m_fnCreateAcceptedObject();
		//CHECKC( pNetworkObject );

		// 네트웍 오브젝트 바인딩
		//pSession->BindNetworkObject( pNetworkObject );

		// 접속시 초기화 및 NetworkObject로 접속 통지
		pSession->OnAccept();

		// 동접수 증가
		++m_numActiveSessions;
	}

	if( !m_pTempList->empty() )
	{
		// 접속에 성공한 세션들을 ActiveSessionList에 추가
//		m_pActiveSessionList->Lock();
		m_pActiveSessionList->splice( m_pActiveSessionList->begin(), *m_pTempList );
//		m_pActiveSessionList->Unlock();
	}
}

//=============================================================================================================================
/**
	@remarks
			현재 accept 또는 connect되어 활성화된 세션들을 순회하며 받은 패킷 등을 처리한다.
*/
//=============================================================================================================================
VOID IoHandler::ProcessActiveSessionList()
{
	SESSION_LIST_ITER	it=m_pActiveSessionList->begin();
	Session				*pSession=NULL;
VA_TRY
	for( it = m_pActiveSessionList->begin(); it != m_pActiveSessionList->end(); ++it )
	{
		pSession = *it;

		if(NULL==pSession)///흔벎槨왕殮쌈빔쫠
			continue;
		CHECKC(Session::IsValidPt(pSession));
// 		try
// 		{
// 			///꿎桿寧濾唐槻昑
// 			int nLength=pSession->GetSendBuffer()->GetLength();
// 		}
// 		catch(...)
// 		{
// 			///흔벎끓�駭鵲�,橙�쓸添綬七겔먼�,깻할뇹잿苟寧몸唐槻뚤蹶
// 			tolog("IoHandler::ProcessActiveSessionList crash!m_pActiveSessionList have not vaild point! Force Del it!");
// 			m_pActiveSessionList->erase(it--);
// 			continue;
// 		}

		//뇹잿랙箇
		if( pSession->PreSend() == FALSE ) 
		{
			pSession->Remove(REMOVE_REASON_PRESEND_ACTIVELIST);
		}

		if( pSession->ShouldBeRemoved() )
		{
			m_pActiveSessionList->erase( it-- );
			m_pDeadSessionList->push_back( pSession );
			continue;
		}
		
		// 받기 버퍼 처리
		if( !pSession->ProcessRecvdPacket( m_dwMaxPacketSize ) )
		{
			pSession->Remove(REMOVE_REASON_RECV_PROCESS);
		}
	}
VA_CATCH("IoHandler::ProcessActiveSessionList crash!")

}

//=============================================================================================================================
/**
	@remarks
			일정 시간 이상 패킷 송신이 없는 세션들을 제거한다.
*/
//=============================================================================================================================
VOID IoHandler::KickDeadSessions()
{
	const I64 i64NowMS = ::GetUtcMillisecond();
	std::vector<Session*> vecSessionHaveSend;

	// 뇹잿덤쀼澗죗깊
	for(SESSION_LIST_ITER itList = m_pDeadSessionList->begin(); itList != m_pDeadSessionList->end(); ++itList )
	{
		Session* pSession = *itList;
		if (NULL == pSession)
		{
			continue;
		}

		// 렷퓻齡昑盧뇜(寮狼都黨뒀꿔댄轎, 샀諒와빵똥뙤역젯쌈), 못貸寧땍샙삔쉥句口랙箇供
		if (pSession->GetRemoveReason() > REMOVE_REASON_NONE && pSession->GetRemoveReason() < REMOVE_REASON_FORCE_BEGIN)
		{
			// 흔벎뻘唐句口청못와빵똥랙供샀諒攣瞳랙箇櫓, 못와빵똥3취돨샙삔, 겉句口랙供, 낚珂빈퓻契쀼澗
			if ((pSession->GetSendBuffer()->GetLength() > 0 || pSession->GetSendFlag()) && 
				pSession->GetRemoveMS() + FORCE_PROCESS_DEAD_SESSION_MS > i64NowMS)
			{
				pSession->PreSend();
				vecSessionHaveSend.push_back(pSession);
				continue;
			}
		}

		// 쀼澗Session珂, 헌왕페뻠녑혐
		pSession->GetRecvBuffer()->Clear();
		pSession->GetSendBuffer()->Clear();

		// 삶땡삔뺐셕鑒
		--m_numActiveSessions;	

		// 繫列�毆蓍쓱勛¤振�break깃션
		m_pIOCPServer->ProcessDisconnectClient(pSession->GetClientID());

		// 청唐쏵흙shutdown직넋돨뺐앎쀼澗
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

	// ActiveSessionList의 세션의 보내기 퍼버 전송
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
			모든 세션들을 제거한다.
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
			Accept된 세션과 Connect된 세션들을 IOCP에 등록하면서 ActiveSessionList로 옮기고
			모든 세션의 받기 버퍼를 검사하여 패킷을 처리하는 등의 작업을 한다.
	@par
			이 함수는 주기적으로 호출해 주어야 한다.
*/
//=============================================================================================================================
VOID IoHandler::Update()
{
	m_pActiveSessionList->Lock();///뜩窟넋속傑
	ProcessActiveSessionList();
//	CheckMutiConnect();
	m_pActiveSessionList->Unlock();///뜩窟넋썩傑

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

	// IOCP 쓰레드 종료
	for( DWORD i = 0; i < m_numIoThreads; ++i )
	{
		PostQueuedCompletionStatus( m_hIOCP, 0, 0, NULL );
	}

	// IO 워커 쓰레드가 모두 종료될 때까지 기다린다.
	WaitForMultipleObjects( m_numIoThreads, m_hIoThread, TRUE, INFINITE );

	///멕誇덜쯤
	for(int j=0;j<(int)m_sessionListHolder.size();++j)
	{
		Session* pSession=m_sessionListHolder[j];
		if(pSession->GetSocket()!=INVALID_SOCKET)
			FreeSession(pSession);
	}
	m_sessionListHolder.clear();
	///멕誇덜쯤
}

VOID IoHandler::ProcessReuseSessionList()
{
	SESSION_LIST_ITER	it;

	for( it = m_pReuseSessionList->begin(); it != m_pReuseSessionList->end(); ++it )
	{
 		if((*it)->CanReuse())
 		{
			Session* pSession = *it;
			ReuseSession(pSession);
			m_pReuseSessionList->erase(it--);
		}
	}
}

////////////////////////////////////////////////////////////////////////
// Description:  쇱꿴뜩路젯쌈
// Arguments:	 첼롸爐쇱꿴寧늴 谿寧몸ip낚법36몸젯쌈, 삔菱땡뙤역侶몸ip돨홍꼬젯쌈
// Author: 톼匡펜(Peng Wenqi)
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

		if(NULL==pSession)///흔벎槨왕殮쌈빔쫠
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

		if(NULL==pSession)///흔벎槨왕殮쌈빔쫠
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
