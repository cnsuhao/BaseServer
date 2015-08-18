#include <winsock2.h>
#include <conio.h>
#include <iostream>
#include <assert.h>
#include <map>
#include "IOCPServer.h"
#include "IoHandler.h"
#include "SessionList.h"
#include "EncryptServer.h"
#include "ServerSocket.h"
#include "../Share/I_Shell.h"
#include "../Share/protocol.h"
#include "../Share/define.h"
#include "../Common/basefunc.h"
#include "../Common/MessagePort/I_MessagePort.h"

unsigned __stdcall send_thread( LPVOID param )
{
	IOCPServer *pIOCPServer = (IOCPServer*)param;

	while( !pIOCPServer->m_bShutdown )
	{
		DEBUG_TRY
		pIOCPServer->Update();
		Sleep(1);
		DEBUG_CATCH("send_thread");
	}
	return 0;
}

IOCPServer::IOCPServer()
{
	m_bShutdown				= FALSE;
}

IOCPServer::~IOCPServer()
{
	if( !m_bShutdown )		
		Shutdown();

	WSACleanup();
}

BOOL IOCPServer::Init( LPIOHANDLER_DESC lpDesc, DWORD dwNumberofIoHandlers )
{
	if( !InitWinsock() )	
		return FALSE;

	for( DWORD i = 0; i < dwNumberofIoHandlers; ++i )
	{
		CreateIoHandler( lpDesc + i );
	}
	return TRUE;
}

VOID IOCPServer::CreateIoHandler( LPIOHANDLER_DESC lpDesc )
{
	IoHandler *pIoHandler = new IoHandler;

	pIoHandler->Init( this, lpDesc );

	m_mapIoHandlers.insert( IOHANDLER_MAP_PAIR( pIoHandler->GetKey(), pIoHandler ) );
}

VOID IOCPServer::Shutdown()
{
	m_bShutdown = TRUE;

	IOHANDLER_MAP_ITER		it;
	IoHandler				*pIoHandler;

	for( it = m_mapIoHandlers.begin(); it != m_mapIoHandlers.end(); ++it )
	{
		pIoHandler = it->second;
		pIoHandler->Shutdown();
		delete pIoHandler;
	}
	m_mapIoHandlers.clear();
}

VOID IOCPServer::Update()
{
	IOHANDLER_MAP_ITER it;

	for( it = m_mapIoHandlers.begin(); it != m_mapIoHandlers.end(); ++it )
	{
		it->second->Update();
	}
}

void IOCPServer::ProcessSend()
{
	IOHANDLER_MAP_ITER it;
	
	for( it = m_mapIoHandlers.begin(); it != m_mapIoHandlers.end(); ++it )
	{
		it->second->ProcessSend();
	}
}

BOOL IOCPServer::StartListen( DWORD dwIoHandlerKey, char *pIP, WORD wPort )
{
	IOHANDLER_MAP_ITER it = m_mapIoHandlers.find( dwIoHandlerKey );

	CHECKF( it != m_mapIoHandlers.end() );

	return it->second->StartListen( pIP, wPort );
}

BOOL IOCPServer::StartAllListen( char *pIP, WORD wPort )
{
	IOHANDLER_MAP_ITER it;

	BOOL bSuc = TRUE;
	
	for(it = m_mapIoHandlers.begin();it!=m_mapIoHandlers.end();++it)
		if(!(it->second->StartListen(pIP,wPort)))
		{
			bSuc = FALSE;
		}

	return bSuc;	
}

BOOL IOCPServer::IsListening( DWORD dwIoHandlerKey )
{
	IOHANDLER_MAP_ITER it = m_mapIoHandlers.find( dwIoHandlerKey );

	CHECKF( it != m_mapIoHandlers.end() );

	return it->second->IsListening();
}

DWORD IOCPServer::GetNumberOfConnections( DWORD dwIoHandlerKey )
{
	IOHANDLER_MAP_ITER it = m_mapIoHandlers.find( dwIoHandlerKey );

	CHECKF( it != m_mapIoHandlers.end() );

	return it->second->GetNumberOfConnections();
}

BOOL IOCPServer::InitWinsock()
{
	WSADATA wsaData;

	WSAStartup( MAKEWORD( 2, 2 ), &wsaData );

	if( wsaData.wVersion != MAKEWORD( 2, 2 ) )
	{
		WSACleanup();

		return FALSE;
	}
	
	return TRUE;
}

void IOCPServer::SetKernel(CSocketKernel* pKernel)
{
	m_pSocketKernel = pKernel;
}

int IOCPServer::ProcessData(const char* pRecvBuf,int nSize,Session* pSession)
{
	return m_pSocketKernel->ProcessRecvMsg(pRecvBuf,nSize,pSession);
}

int	IOCPServer::SetNewClientSocket(Session* pSession)
{
	return  m_pSocketKernel->SetNewSocket(pSession);
}

void IOCPServer::ProcessDisconnectClient(int i, bool bSendOtherThread /*= true*/)
{
	m_pSocketKernel->ProcessDisconnServer(i);
}

BOOL IOCPServer::StartSendProcessThread()
{
	unsigned threadID;
	m_hSendThread = (HANDLE)_beginthreadex( NULL, 0, send_thread, (LPVOID)this, 0, &threadID );
	return TRUE;
}