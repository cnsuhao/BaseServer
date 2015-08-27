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
			// �Խ��ܵ������ݽ��н���
			pSession->ReleaseOverlappedNum();
			pSession->GetRecvBuffer()->Completion( dwIoSize );
			
			// Recv	
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
	m_pAcceptor					= NULL;
	m_pActiveSessionList		= NULL;
	m_pAcceptedSessionList		= NULL;
	m_pReuseSessionList			= NULL;
	m_pDeadSessionList			= NULL;
	m_pTempList					= NULL;
	m_numActiveSessions			= 0;
	m_bShutdown					= FALSE;
	m_dwKickCheckSecond			= ::TimeGet(TIME_SECOND);

	for( DWORD i = 0; i < CLIENT_IOCP_MAX_IO_WORKER_THREAD_COUNT; ++i ) 
	{
		m_hIoThread[i] = NULL;
	}
}

IoHandler::~IoHandler()
{
	if( !m_bShutdown ) Shutdown();

	for( DWORD i = 0; i < m_numIoThreads; ++i )
	{
		if( m_hIoThread[i] ) CloseHandle( m_hIoThread[i] );
	}

	if( m_pAcceptSessionPool )		delete m_pAcceptSessionPool;
	if( m_pAcceptor )				delete m_pAcceptor;
	if( m_pActiveSessionList )		delete m_pActiveSessionList;
	if( m_pAcceptedSessionList )	delete m_pAcceptedSessionList;
	if( m_pReuseSessionList )		delete m_pReuseSessionList;
	if( m_pTempList )				delete m_pTempList;
	if(m_pDeadSessionList)			delete m_pDeadSessionList;
}

VOID IoHandler::Init( IOCPServer *pIOCPServer, LPIOHANDLER_DESC lpDesc )
{
	m_pIOCPServer			= pIOCPServer;
	m_dwKey					= lpDesc->dwIoHandlerKey;

	m_pActiveSessionList	= new SessionList;
	m_pAcceptedSessionList	= new SessionList;
	m_pReuseSessionList		= new SessionList;
	m_pTempList				= new SessionList;
	m_pDeadSessionList		= new SessionList;

	m_dwMaxAcceptSession	= lpDesc->dwMaxAcceptSession;
	m_pAcceptSessionPool	= new SessionPool( lpDesc->dwMaxAcceptSession,
											   lpDesc->dwSendBufferSize,
											   lpDesc->dwRecvBufferSize,
											   lpDesc->dwMaxPacketSize,
											   1,
											   TRUE );

	m_dwMaxPacketSize =	lpDesc->dwMaxPacketSize;
  
	m_hIOCP = CreateIoCompletionPort( INVALID_HANDLE_VALUE, NULL, 0, 0 );

	unsigned threadID;
	CHECKB(lpDesc->dwNumberOfIoThreads <= CLIENT_IOCP_MAX_IO_WORKER_THREAD_COUNT);
	m_numIoThreads = lpDesc->dwNumberOfIoThreads;
	for( DWORD i = 0; i < m_numIoThreads; ++i )
	{
		m_hIoThread[i] = (HANDLE)_beginthreadex( NULL, 0, io_thread, (LPVOID)this, 0, &threadID );
	}

	m_pAcceptor		= new Acceptor;
	m_pAcceptor->Init( this, lpDesc->dwNumberOfAcceptThreads );
}

BOOL IoHandler::StartListen( char *pIP, WORD wPort )
{
	CHECKF( m_dwMaxAcceptSession > 0 );

	if( IsListening() ) return TRUE;

	if( !m_pAcceptor->StartListen( pIP, wPort ) )
	{
		return FALSE;
	}

	Session *pSession;
	while( pSession = AllocAcceptSession() )
	{
		pSession->PreAccept( m_pAcceptor->GetListenSocket() );
		m_sessionListHolder.push_back(pSession);	// ���Ự���������Ա�����ͷŵ�
	}
	return TRUE;
}

BOOL IoHandler::IsListening()
{
	return m_pAcceptor->IsListening();
}

Session* IoHandler::AllocAcceptSession()
{
	return m_pAcceptSessionPool->Alloc();
}

VOID IoHandler::FreeSession( Session *pSession )
{
	pSession->CloseSocket();
	pSession->Init();
	if( pSession->IsAcceptSocket() )
	{
		m_pAcceptSessionPool->Free( pSession );
	}
}

VOID IoHandler::ReuseSession( Session *pSession )
{
	pSession->Reuse( m_hIOCP );
}

VOID IoHandler::ProcessAcceptedSessionList()
{
	DEBUG_TRY;
	m_pAcceptedSessionList->Lock();
	m_pTempList->splice( m_pTempList->end(), *m_pAcceptedSessionList );
	m_pAcceptedSessionList->Unlock();

	bool bIncrement = true;
	Session* pSession = NULL;
	SESSION_LIST_ITER iter = m_pTempList->begin();
	for(; iter != m_pTempList->end();)
	{
		bIncrement = true;
		pSession   = *iter;

		if( m_numActiveSessions >= m_dwMaxAcceptSession )
		{
			LOGWARNING("connection full! m_numActiveSessions = %u,m_dwMaxAcceptSession = %u",m_numActiveSessions,m_dwMaxAcceptSession);
			bIncrement = false;
			iter = m_pTempList->erase(iter);
			ReuseSession( pSession );
			m_pReuseSessionList->push_back(pSession);
			continue;
		}

		CreateIoCompletionPort( (HANDLE)pSession->GetSocket(), m_hIOCP, (ULONG_PTR)pSession, 0 );

		pSession->SetIoHandler(this);
		pSession->SetClientID(m_pIOCPServer->SetNewClientSocket(pSession));

		if( !pSession->PreRecv() )
		{
			bIncrement = false;
			iter = m_pTempList->erase(iter);
			ReuseSession(pSession);
			m_pReuseSessionList->push_back(pSession);
			continue;
		}

		pSession->OnAccept();

		++m_numActiveSessions;

		if (bIncrement)
		{
			iter++;
		}
	}

	if( !m_pTempList->empty() )
	{
		m_pActiveSessionList->splice( m_pActiveSessionList->begin(), *m_pTempList );
	}
	DEBUG_CATCH("IoHandler::ProcessAcceptedSessionList crash!")
}

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
		bool bSendOtherThread = REMOVE_REASON_KICK_ANOTHER != pSession->GetRemoveReason() ? true : false;
		m_pIOCPServer->ProcessDisconnectClient(pSession->GetClientID(), bSendOtherThread);

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

	m_pActiveSessionList->Lock();
	for( it = m_pActiveSessionList->begin(); it != m_pActiveSessionList->end(); ++it )
	{
		pSession = *it;

		if( pSession->PreSend() == FALSE ) 
		{
			pSession->Remove(REMOVE_REASON_PRESEND_ALL);
		}
	}
	m_pActiveSessionList->Unlock();
}

VOID IoHandler::KickAllSessions()
{
	SESSION_LIST_ITER	it;

	for( it = m_pActiveSessionList->begin(); it != m_pActiveSessionList->end(); ++it )
	{
		(*it)->Remove(REMOVE_REASON_KILL_ALL_SESSION);
	}
}

VOID IoHandler::Update()
{
	m_pActiveSessionList->Lock();	// ���̼߳���
	ProcessActiveSessionList();
	m_pActiveSessionList->Unlock(); // ���߳̽���

	if( !m_pAcceptedSessionList->empty() )
	{
		ProcessAcceptedSessionList();
	}

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

	for( DWORD i = 0; i < m_numIoThreads; ++i )
	{
		PostQueuedCompletionStatus( m_hIOCP, 0, 0, NULL );
	}

	WaitForMultipleObjects( m_numIoThreads, m_hIoThread, TRUE, INFINITE );

	// ��Σ����
	for(int j = 0; j < (int)m_sessionListHolder.size(); ++j)
	{
		Session* pSession=m_sessionListHolder[j];
		if(pSession->GetSocket() != INVALID_SOCKET)
			FreeSession(pSession);
	}
	m_sessionListHolder.clear();
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
	for (SESSION_LIST_ITER it = m_pActiveSessionList->begin(); it != m_pActiveSessionList->end(); ++it )
	{

		Session* pSession = *it;

		if(NULL == pSession)	// ���Ϊ��ֱ�Ӻ���
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

	for (SESSION_LIST_ITER it = m_pActiveSessionList->begin(); it != m_pActiveSessionList->end(); ++it )
	{

		Session* pSession = *it;

		if(NULL == pSession)	// ���Ϊ��ֱ�Ӻ���
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
