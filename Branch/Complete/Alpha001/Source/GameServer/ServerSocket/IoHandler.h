#ifndef _IOHANDLER_H_
#define _IOHANDLER_H_

#include <windows.h>
#include <process.h>
#include <vector>
#include "SessionList.h"
#include "IOCPServer.h"

using namespace std;

class Session;
class SessionPool;
class Acceptor;
class Connector;
class SessionList;
class IOCPServer;
class NetworkObject;
struct tagIOHANDLER_DESC;

typedef tagIOHANDLER_DESC IOHANDLER_DESC, *LPIOHANDLER_DESC;

class IoHandler
{
	friend unsigned __stdcall io_thread( LPVOID param );
	friend unsigned __stdcall send_thread( LPVOID param );
	friend unsigned __stdcall accept_thread( LPVOID param );
	friend unsigned __stdcall connect_thread( LPVOID param );
	friend unsigned __stdcall update_thread(LPVOID param);
public:
	IoHandler();
	~IoHandler();

	VOID	Init			(IOCPServer *pIOCPServer, LPIOHANDLER_DESC lpDesc);
	BOOL	StartListen		(char *pIP, WORD wPort);
	VOID	Update			(void);
	VOID	Shutdown		(void);
	BOOL	IsListening		(void);
	inline DWORD	GetNumberOfConnections	(void)	{ return m_numActiveSessions; }
	inline DWORD	GetKey	(void)					{ return m_dwKey; }
	IOCPServer*		GetIOCPServer			(void)	{ return m_pIOCPServer; }
	VOID	ProcessSend		(void);
	int		MyGetSockError	(IN SOCKET s, WSAOVERLAPPED* pWSAOVERLAPPED);

private:
	Session*	AllocAcceptSession		(void);
	VOID	FreeSession					(Session *pSession);
	VOID	ReuseSession				(Session *pSession);
	VOID	ProcessAcceptedSessionList	(void);
	VOID	ProcessActiveSessionList	(void);
	VOID	KickDeadSessions			(void);

	VOID	KickAllSessions				(void);
	VOID	ProcessReuseSessionList		(void);
	void	CheckMutiConnect			(void);

private:
	IOCPServer*			m_pIOCPServer;
	SessionPool*		m_pAcceptSessionPool;
	Acceptor*			m_pAcceptor;
	SessionList*		m_pActiveSessionList;
	SessionList*		m_pAcceptedSessionList;
	SessionList*		m_pReuseSessionList;
	SessionList*		m_pTempList;
	SessionList*		m_pDeadSessionList;
	vector<Session*>	m_sessionListHolder;	// 保存所有预分配的会话对象

	BOOL				m_bShutdown;

	DWORD				m_dwKey;
	HANDLE				m_hIOCP;
	DWORD				m_numIoThreads;
	HANDLE				m_hIoThread[CLIENT_IOCP_MAX_IO_WORKER_THREAD_COUNT];
	DWORD				m_dwMaxPacketSize;
	DWORD				m_numActiveSessions;
	DWORD				m_dwMaxAcceptSession;
	DWORD				m_dwKickCheckSecond;
};

#endif


