#ifndef _SESSION_H_
#define _SESSION_H_

#include <windows.h>
#include "EncryptServer.h"
#include "./../Common/BaseFunc.h"
#include "./../Common/MyHeap.h"

#define LOGIN_KEY1				0xa61fce5e	// A = 0x20, B = 0xFD, C = 0x07, first = 0x1F, key = a61fce5e
#define LOGIN_KEY2				0x443ffc04	// A = 0x7A, B = 0xCF, C = 0xE5, first = 0x3F, key = 443ffc04


#define SEND_POSTED			1
#define RECV_POSTED			2
#define ACCEPT_POSTED		3
#define DISCONNECT_POSTED	4

class SendBuffer;
class RecvBuffer;
class SessionPool;
class Session;
class IoHandler;

/// OVERLAPPED
struct OVERLAPPEDEX : public OVERLAPPED
{
	DWORD		dwIoSize;
	DWORD		dwFlags;
	DWORD		dwOperationType;
	Session*	pSession;
};

class Session
{
	friend unsigned __stdcall io_thread( LPVOID param );
	friend class SessionPool;

public:
	Session( DWORD dwSendBufferSize, DWORD dwRecvBufferSize, DWORD dwMaxPacketSize/*, DWORD dwTimeOut*/ );
	virtual ~Session();

	VOID	Init		(void);
	VOID	Reuse		(HANDLE hIOCP);
	BOOL	Send		(BYTE *pMsg, WORD wSize);
	BOOL	SendNPC		(BYTE *pMsg, WORD wSize);
	BOOL	PreSend		(void);
	BOOL	PreRecv		(void);
	BOOL	PreAccept	(SOCKET listenSocket);
	SOCKET	CreateSocket(void);
	BOOL	ProcessRecvdPacket(DWORD dwMaxPacketSize);
	VOID	OnAccept	(void);

	inline VOID			SetSocket	(SOCKET socket)			 { m_socket = socket; }
	inline VOID			SetSockAddr	(SOCKADDR_IN& sockaddr ) { m_sockaddr = sockaddr; }
	inline VOID			CloseSocket	(void) ;

	inline SendBuffer*	GetSendBuffer		(void)	{ return m_pSendBuffer; }
	inline RecvBuffer*	GetRecvBuffer		(void)	{ return m_pRecvBuffer; }
	inline SOCKET		GetSocket			(void)	{ return m_socket; }
	inline SOCKADDR*	GetSockAddr			(void)	{ return (SOCKADDR*)&m_sockaddr; }
	inline char*		GetIP				(void)	{ return inet_ntoa( m_sockaddr.sin_addr ); }
	inline USHORT		GetPort				(void)	{ return ntohs(m_sockaddr.sin_port);}

	inline DWORD		GetIndex			(void)	{ return m_dwIndex; }
	inline BOOL			IsAcceptSocket		(void)	{ return m_bAcceptSocket; }
	inline VOID			SetAcceptSocketFlag	(void)	{ m_bAcceptSocket = TRUE; }

	VOID				Remove				(int nLogFlag, const char* pszLogEx = "Nothing");
	inline BOOL			GetRemoveFlag		(void) const	{ return m_bRemove; }
	inline VOID			ResetKillFlag		(void);

	inline BOOL			ShouldBeRemoved		(void) { return m_bRemove; }
	inline BOOL			HasDisconnectOrdered(void) { return m_bDisconnectOrdered; }

	void	SetSendFlag		(BOOL bFlag)	{ InterlockedExchange((LONG*)&m_bSendFlag, bFlag); }
	BOOL	GetSendFlag		(void) const	{ return m_bSendFlag; }
	I64		GetRemoveMS		(void) const	{ return m_i64RemoveMS; }
	LONG	GetRemoveReason	(void) const	{ return m_lRemoveReason; }

	void	SetIoHandler	(IoHandler* pHandler)	{ m_pIoHandler = pHandler; }
	void	SetClientID		(int nClientID)	{ m_ClientID = nClientID; }
	int		GetClientID		(void)			{ return m_ClientID; }

	void	AddOverlappedNum(void)			{ InterlockedIncrement(&m_OverlappedIONum); }
	void	ReleaseOverlappedNum(void)		{ InterlockedDecrement(&m_OverlappedIONum); }
	BOOL	CanReuse		(void)			{ return m_OverlappedIONum<=0; }

private:
	VOID	SetIndex		(DWORD index) { m_dwIndex = index; }

private:
	IoHandler*		m_pIoHandler;
	SendBuffer*		m_pSendBuffer;
	RecvBuffer*		m_pRecvBuffer;

	SOCKET			m_socket;
	SOCKADDR_IN		m_sockaddr;

	OVERLAPPEDEX	m_sendIoData;
	OVERLAPPEDEX	m_recvIoData;
	OVERLAPPEDEX	m_acceptIoData;
	OVERLAPPEDEX	m_disconnectIoData;
	BOOL			m_bRemove;
	DWORD			m_dwIndex;
	BOOL			m_bAcceptSocket;
	BOOL			m_bDisconnectOrdered;

	int				m_ClientID;

	long			m_OverlappedIONum;

	BOOL			m_bSendFlag;
	I64				m_i64RemoveMS;
	LONG			m_lRemoveReason;

	// 消息序号验证功能
public:
	void	SetMsgIndex	(DWORD dwNew)		{ m_dwMsgIndex = dwNew; }
	DWORD	GetMsgIndex	(void) const		{ return m_dwMsgIndex; }
	void	AddTailErrorCountAndAutoBreak(void);
private:
	DWORD	m_dwMsgIndex;	
	DWORD	m_dwMsgTailErrorCount;

	// 增加一个timeout统计量
public:
	void	AddTimeoutCount	(void)			{ m_nTimeoutCount++; }
	int		GetTimeoutCount	(void) const	{ return m_nTimeoutCount; }
private:
	int		m_nTimeoutCount;

public:
	MYHEAP_DECLARATION(s_heap);
};

void SetClientSockOpt(SOCKET sock);
#endif
