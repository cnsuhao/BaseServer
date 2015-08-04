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
			I/O completion阑 皑矫窍绊 贸府窍绰 静饭靛
	@param	param
			IOCP 辑滚狼 器牢磐
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

		// 如果线程强行关机命令
		if( pSession == NULL ) 
		{
			break;
		}

		// GQCS失败处理
		if( !bSuccess )
		{
			DWORD dwLastError = pIoHandler->MyGetSockError(pSession->GetSocket(), (WSAOVERLAPPED*)pOverlappedEx);

			// send投递超时, 修改状态允许send线程进行下次投递
			if (WSAETIMEDOUT == dwLastError && SEND_POSTED == pOverlappedEx->dwOperationType && pSession->GetTimeoutCount() < CLIENT_IOCP_SOCKET_MAX_TIMEOUT_COUNT)
			{
				pSession->AddTimeoutCount();
				pSession->ReleaseOverlappedNum();
				pSession->SetSendFlag(FALSE);
				continue;
			}

			// recv投递超时, 进行下次recv投递
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

		// DISCONNECT_POSTED啊 酒囱单档 IoSize啊 0牢 版快 技记 力芭
		if( pOverlappedEx->dwOperationType != DISCONNECT_POSTED && dwIoSize == 0 )
		{
			pSession->ReleaseOverlappedNum();
			pSession->Remove(REMOVE_REASON_CLIENT_BREAK, "Client Break Connect!");
			continue;
		}

		// Completion 贸府
		switch( pOverlappedEx->dwOperationType )
		{
		case SEND_POSTED:
			pSession->ReleaseOverlappedNum();
			pSession->GetSendBuffer()->Completion( dwIoSize );
			pSession->SetSendFlag(FALSE);
			break;

		case RECV_POSTED:
			//对接受到的数据进行解密
			pSession->ReleaseOverlappedNum();
//			pSession->EncyRecvData(dwIoSize);
			pSession->GetRecvBuffer()->Completion( dwIoSize );
			// 促澜 Recv	
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

	// 妮归 窃荐 器牢磐 蜡瓤己 八荤
//	CHECK( !IsBadReadPtr( lpDesc->fnCreateAcceptedObject, sizeof(lpDesc->fnCreateAcceptedObject) ) );
//	CHECK( !IsBadReadPtr( lpDesc->fnDestroyAcceptedObject, sizeof(lpDesc->fnDestroyAcceptedObject) ) );
//	CHECK( !IsBadReadPtr( lpDesc->fnDestroyConnectedObject, sizeof(lpDesc->fnDestroyConnectedObject) ) );
//	
	// 妮归 窃荐 器牢磐 历厘
//	m_fnCreateAcceptedObject		= lpDesc->fnCreateAcceptedObject;
//	m_fnDestroyAcceptedObject		= lpDesc->fnDestroyAcceptedObject;
//	m_fnDestroyConnectedObject		= lpDesc->fnDestroyConnectedObject;

	m_dwKey				= lpDesc->dwIoHandlerKey;
	
	// 技记 府胶飘 积己
	m_pActiveSessionList	= new SessionList;
	m_pAcceptedSessionList	= new SessionList;
	m_pReuseSessionList		= new SessionList;
	//m_pConnectSuccessList	= new SessionList;
	//m_pConnectFailList		= new SessionList;
	m_pTempList				= new SessionList;
	m_pDeadSessionList		= new SessionList;

	// 弥措 立加 力茄 牢盔
	m_dwMaxAcceptSession	= lpDesc->dwMaxAcceptSession;

	// 技记 钱 积己
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

	
	// 弥措 菩哦 农扁 汲沥
	//CHECK( lpDesc->dwMaxPacketSize > sizeof(PACKET_HEADER) );
	m_dwMaxPacketSize =	lpDesc->dwMaxPacketSize;
  
	// IOCP 积己
	m_hIOCP = CreateIoCompletionPort( INVALID_HANDLE_VALUE, NULL, 0, 0 );

	unsigned threadID;

	// IO 况目 静饭靛 积己
	CHECKB(lpDesc->dwNumberOfIoThreads <= CLIENT_IOCP_MAX_IO_WORKER_THREAD_COUNT);
	m_numIoThreads = lpDesc->dwNumberOfIoThreads;
	for( DWORD i = 0; i < m_numIoThreads; ++i )
	{
		m_hIoThread[i] = (HANDLE)_beginthreadex( NULL, 0, io_thread, (LPVOID)this, 0, &threadID );
	}


// 	m_hUpdateThread = (HANDLE)_beginthreadex( NULL, 0, update_thread, (LPVOID)this, 0, &threadID );

	// 撅剂磐 积己
	m_pAcceptor		= new Acceptor;
	m_pAcceptor->Init( this, lpDesc->dwNumberOfAcceptThreads );

	// 目池磐 积己	
	//m_pConnector	= new Connector;
	//m_pConnector->Init( this, lpDesc->dwNumberOfConnectThreads );
}

//DWORD IoHandler::Connect( NetworkObject *pNetworkObject, char *pszIP, WORD wPort )
//{
//	// 秦寸 NetworkObject狼 家南捞 捞固 目池飘 矫档吝捞搁 府畔茄促.
//	if( pNetworkObject->m_pSession != NULL ) return 0;
//
//	// 家南 积己
//	SOCKET socket = WSASocket( AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED );
//
//	// 林家 悸泼
//	SOCKADDR_IN addr;
//
//	addr.sin_family			= AF_INET;
//	addr.sin_addr.s_addr	= inet_addr( pszIP );
//	addr.sin_port			= htons( wPort );
//
//	// 技记 且寸
//	Session *pSession = AllocConnectSession();
//	CHECKF( pSession != NULL && "技记捞 葛磊扼辑 Connect 且 荐 绝嚼聪促. dwMaxConnectSession 俺荐甫 犬牢秦林技夸" );
//
//	// 技记俊 家南 棺 林家 悸泼
//	pSession->SetSocket( socket );
//	pSession->SetSockAddr( addr );
//
//	// 技记阑 匙飘亏 坷宏璃飘客 官牢爹
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
			府郊 家南阑 积己窍绊 府郊阑 矫累茄促.
	@retval	BOOL
			府郊 家南 积己俊 角菩窍搁 FALSE甫 府畔茄促.
	@param	pIP
			府郊俊 荤侩且 IP
	@param	wPort
			府郊俊 荤侩且 器飘
*/
//=============================================================================================================================
BOOL IoHandler::StartListen( char *pIP, WORD wPort )
{
	CHECKF( m_dwMaxAcceptSession > 0 );

	// 捞固 府郊吝捞扼搁 己傍 贸府
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
		m_sessionListHolder.push_back(pSession);///将会话保存下来以便后面释放掉
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
			荤侩吝捞带 技记甸阑 葛滴 技记钱俊 馆券茄促.
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
			立加俊 己傍茄 技记 府胶飘 贸府
	@par
			ConnectSuccessList俊 乐绰 技记甸阑 IOCP俊 殿废窍绊 OnConnect(TRUE)甫 龋免窍绊 ActiveSessionList俊 眠啊茄促.
*/
//=============================================================================================================================
//VOID IoHandler::ProcessConnectSuccessList()
//{
//	SESSION_LIST_ITER		it;
//	Session					*pSession;
//
//	// 目池飘俊 己傍茄 技记甸阑 烙矫 府胶飘肺 颗辫
//	m_pConnectSuccessList->Lock();
//	m_pTempList->splice( m_pTempList->end(), *m_pConnectSuccessList );
//	m_pConnectSuccessList->Unlock();
//
//	for( it = m_pTempList->begin(); it != m_pTempList->end(); ++it )
//	{
//		pSession = *it;
//
//		// IOCP俊 勤甸 殿废
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
//			// 技记 钱俊 馆券
//			FreeSession( pSession );
//
//			pSession->OnConnect( FALSE );
//		}
//	}
//
//	if( !m_pTempList->empty() )
//	{
//		// 悼立荐 刘啊
//		m_numActiveSessions += (DWORD)m_pTempList->size();
//
//		// 目池飘俊 己傍茄 技记甸阑 ActiveSessionList俊 眠啊茄促.
//		m_pActiveSessionList->Lock();
//		m_pActiveSessionList->splice( m_pActiveSessionList->end(), *m_pTempList );
//		m_pActiveSessionList->Unlock();
//	}
//}

//=============================================================================================================================
/**
	@remarks
			立加俊 角菩茄 技记 府胶飘 贸府
	@par
			ConnectFailList俊 乐绰 技记甸俊 措秦 OnConnect(FALSE)阑 龋免茄促.
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
//		// 技记 钱俊 馆券
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
			TempSessionList俊 乐绰 技记甸阑 IOCP俊 殿废窍绊 ActiveSessionList肺 颗扁绊 OnAccpet()甫 龋免茄促.
*/
//=============================================================================================================================
VOID IoHandler::ProcessAcceptedSessionList()
{
	DEBUG_TRY;
	// 立加俊 己傍茄 技记甸阑 罐酒敌 烙矫 府胶飘肺 颗辫
	m_pAcceptedSessionList->Lock();
	m_pTempList->splice( m_pTempList->end(), *m_pAcceptedSessionList );
	m_pAcceptedSessionList->Unlock();

	// 立加俊 己傍茄 技记俊 措茄 贸府
	bool bIncrement = true;
	Session* pSession = NULL;
	SESSION_LIST_ITER iter = m_pTempList->begin();
	for(; iter != m_pTempList->end();)
	{
		bIncrement = true;
		pSession   = *iter;

		// 弥绊悼立荐甫 檬苞窍绰 版快 角菩
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

		// IOCP俊 勤甸 殿废
		CreateIoCompletionPort( (HANDLE)pSession->GetSocket(), m_hIOCP, (ULONG_PTR)pSession, 0 );

		pSession->SetIoHandler(this);
		pSession->SetClientID(m_pIOCPServer->SetNewClientSocket(pSession));

		// Recv俊 角菩窍绰 版快 贸府
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
		// 己傍利栏肺 立加等 技记 贸府
		//--------------------------------

		// 匙飘亏 坷宏璃飘 积己 夸没
		//NetworkObject *pNetworkObject = m_fnCreateAcceptedObject();
		//CHECKC( pNetworkObject );

		// 匙飘亏 坷宏璃飘 官牢爹
		//pSession->BindNetworkObject( pNetworkObject );

		// 立加矫 檬扁拳 棺 NetworkObject肺 立加 烹瘤
		pSession->OnAccept();

		// 悼立荐 刘啊
		++m_numActiveSessions;

		// 处理迭代器自增
		if (bIncrement)
		{
			iter++;
		}
	}

	if( !m_pTempList->empty() )
	{
		// 立加俊 己傍茄 技记甸阑 ActiveSessionList俊 眠啊
//		m_pActiveSessionList->Lock();
		m_pActiveSessionList->splice( m_pActiveSessionList->begin(), *m_pTempList );
//		m_pActiveSessionList->Unlock();
	}
	DEBUG_CATCH("IoHandler::ProcessAcceptedSessionList crash!")
}

//=============================================================================================================================
/**
	@remarks
			泅犁 accept 肚绰 connect登绢 劝己拳等 技记甸阑 鉴雀窍哥 罐篮 菩哦 殿阑 贸府茄促.
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

		// 检测会话的有效性
		pSession = *iter;
		CHECKC_NOLOG(pSession);
		CHECKC(Session::IsValidPt(pSession));

		// 处理发送
		if(FALSE == pSession->PreSend()) 
		{
			pSession->Remove(REMOVE_REASON_PRESEND_ACTIVELIST);
		}

		// 处理移除会话
		if(pSession->ShouldBeRemoved())
		{
			bIncrement = false;
			iter = m_pActiveSessionList->erase(iter);
			m_pDeadSessionList->push_back( pSession );
			continue;
		}
		
		// 处理接收包
		if(!pSession->ProcessRecvdPacket(m_dwMaxPacketSize))
		{
			pSession->Remove(REMOVE_REASON_RECV_PROCESS);
		}

		// 迭代器自增
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
			老沥 矫埃 捞惑 菩哦 价脚捞 绝绰 技记甸阑 力芭茄促.
*/
//=============================================================================================================================
VOID IoHandler::KickDeadSessions()
{
	const I64 i64NowMS = ::GetUtcMillisecond();
	std::vector<Session*> vecSessionHaveSend;

	// 处理待回收列表
	for(SESSION_LIST_ITER itList = m_pDeadSessionList->begin(); itList != m_pDeadSessionList->end(); ++itList )
	{
		Session* pSession = *itList;
		if (NULL == pSession)
		{
			continue;
		}

		// 非强制性移除(主要源于底层错误, 或者客户端断开连接), 给予一定机会将消息发送完
		if (pSession->GetRemoveReason() > REMOVE_REASON_NONE && pSession->GetRemoveReason() < REMOVE_REASON_FORCE_BEGIN)
		{
			// 如果还有消息没给客户端发完或者正在发送中, 给客户端3秒的机会, 把消息发完, 超时后强行回收
			if ((pSession->GetSendBuffer()->GetLength() > 0 || pSession->GetSendFlag()) && 
				pSession->GetRemoveMS() + FORCE_PROCESS_DEAD_SESSION_MS > i64NowMS)
			{
				pSession->PreSend();
				vecSessionHaveSend.push_back(pSession);
				continue;
			}
		}

		// 回收Session时, 清空其缓冲区
		pSession->GetRecvBuffer()->Clear();
		pSession->GetSendBuffer()->Clear();

		// 活动会话计数
		--m_numActiveSessions;	

		// 通知上层删除并打上break标记
		m_pIOCPServer->ProcessDisconnectClient(pSession->GetClientID());

		// 没有进入shutdown流程的话就回收
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

	// ActiveSessionList狼 技记狼 焊郴扁 欺滚 傈价
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
			葛电 技记甸阑 力芭茄促.
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
			Accept等 技记苞 Connect等 技记甸阑 IOCP俊 殿废窍搁辑 ActiveSessionList肺 颗扁绊
			葛电 技记狼 罐扁 滚欺甫 八荤窍咯 菩哦阑 贸府窍绰 殿狼 累诀阑 茄促.
	@par
			捞 窃荐绰 林扁利栏肺 龋免秦 林绢具 茄促.
*/
//=============================================================================================================================
VOID IoHandler::Update()
{
	m_pActiveSessionList->Lock();///多线程加锁
	ProcessActiveSessionList();
//	CheckMutiConnect();
	m_pActiveSessionList->Unlock();///多线程解锁

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

	// IOCP 静饭靛 辆丰
	for( DWORD i = 0; i < m_numIoThreads; ++i )
	{
		PostQueuedCompletionStatus( m_hIOCP, 0, 0, NULL );
	}

	// IO 况目 静饭靛啊 葛滴 辆丰瞪 锭鳖瘤 扁促赴促.
	WaitForMultipleObjects( m_numIoThreads, m_hIoThread, TRUE, INFINITE );

	///高危代码
	for(int j=0;j<(int)m_sessionListHolder.size();++j)
	{
		Session* pSession=m_sessionListHolder[j];
		if(pSession->GetSocket()!=INVALID_SOCKET)
			FreeSession(pSession);
	}
	m_sessionListHolder.clear();
	///高危代码
}

VOID IoHandler::ProcessReuseSessionList()
{
	DEBUG_TRY;
	bool bIncrement = true;
	SESSION_LIST_ITER iter = m_pReuseSessionList->begin();
	for(;iter != m_pReuseSessionList->end();)
	{
		bIncrement = true;

		// 处理会话重用
 		if((*iter)->CanReuse())
 		{
			Session* pSession = *iter;
			ReuseSession(pSession);
			iter = m_pReuseSessionList->erase(iter);
			bIncrement = false;
		}

		// 处理迭代器自增
		if (bIncrement)
		{
			iter++;
		}
	}
	DEBUG_CATCH("IoHandler::ProcessReuseSessionList crash!")
}

////////////////////////////////////////////////////////////////////////
// Description:  检查多重连接
// Arguments:	 每分钟检查一次 同一个ip超过36个连接, 会自动断开这个ip的全部连接
// Author: 彭文奇(Peng Wenqi)
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

		if(NULL==pSession)///如果为空直接忽略
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

		if(NULL==pSession)///如果为空直接忽略
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
