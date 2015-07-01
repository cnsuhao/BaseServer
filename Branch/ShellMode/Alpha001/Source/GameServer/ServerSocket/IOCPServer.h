#ifndef _SERVERSOCKET_IOCPSERVER_H_
#define _SERVERSOCKET_IOCPSERVER_H_ 

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma comment( lib, "ws2_32.lib" )
#include "../../../Include/Global.h"
#include <windows.h>
#include <map>

// iocp�������������
const int	CLIENT_IOCP_SOCKET_KEEPALIVE_INTERVAL	= 60 * 1000;	// �ͻ���iocp�׽��ֲ���		����̽����	[���ӻ��ɲ�����ʱ]
const int	CLIENT_IOCP_SOCKET_KEEPALIVE_TIME		= 5 * 1000;		// �ͻ���iocp�׽��ֲ���		����̽����	[��������ʱ]
const int	CLIENT_IOCP_SOCKET_BUF					= 32 * 1024;	// �ͻ���iocp�׽��ֲ���		��������С		[����/����]��ͬ
const int	CLIENT_IOCP_SOCKET_TIMOUT				= 10;			// �ͻ���iocp�׽��ֲ���		��ʱʱ������	[����/����]��ͬ
const int	CLIENT_IOCP_SOCKET_MAX_TIMEOUT_COUNT	= 10;			// �ͻ���iocp�׽��ֲ���		��ʱ��������	[����/����]����
const int	NPC_IOCP_LIST_SEND_BUF					= 512 * 1024;	// npc�ķ��ͻ���������(npc���������õıȽϴ�)
const int	NPC_IOCP_LIST_RECV_BUF					= 512 * 1024;	// npc�Ľ��ջ���������(npc���������õıȽϴ�)
const DWORD CLIENT_IOCP_MIN_IO_WORKER_THREAD_COUNT	= 4;			// �ͻ���iocp��С�������߳���
const DWORD CLIENT_IOCP_MAX_IO_WORKER_THREAD_COUNT	= 16;			// �ͻ���iocp��������߳���
const DWORD NPCSERVER_IOCP_IO_WORKER_THREAD_COUNT	= 2;			// Npc������ iocp�������߳�����
const I64	FORCE_PROCESS_DEAD_SESSION_MS			= 3000;			// 3���ǿ�ƶϿ�, ������Ϣ��û�з���
const DWORD	FORCE_KICKOUT_ERROR_MSGTAIL_COUNT		= 29;			// ����ָ��������β����, �ͻ�ǿ������

// �Ự�Ƴ�ԭ��
enum REMOVE_REASON
{
	REMOVE_REASON_NONE						= 0,	// δ���Ƴ�
	REMOVE_REASON_RECV_PROCESS				= 1,	// ���������Ϣ����
	REMOVE_REASON_KILL_ALL_SESSION			= 2,	// �ط�ʱ, �ر����лỰ
	REMOVE_REASON_SETNPCSOCKETID			= 3,	// ����npc�������׽���idʧ��
	REMOVE_REASON_KICK_ONE					= 4,	// �߼���(������Ļ��ͼ��) ��ĳ����
	REMOVE_REASON_KICK_ALL					= 5,	// �߼���(������Ļ��ͼ��) ��ȫ����
	REMOVE_REASON_SOCKET_KERNEL_RELEASE		= 6,	// �����������
	REMOVE_REASON_UNDER_ATTACK				= 7,	// �ܵ���������Ͽ�
	
	//////////////////////////////////////////////////////////////////////////
	REMOVE_REASON_FORCE_BEGIN				= 100,	// ǿ���Ƴ���ʼ, �����־��׼������ʹ�� 

	// 101-199��ʾio_thread�г����, 200-299��ʾ����������, 300-399��ʾ��������
	REMOVE_REASON_GQCS_ERROR				= 101,	// GetQueuedCompletionStatusʧ��, ����������
	REMOVE_REASON_CLIENT_BREAK				= 102,	// �ͻ��������Ͽ�����
	REMOVE_REASON_PRERECV_ERROR				= 103,	// ������ϢͶ�ݴ���
	REMOVE_REASON_RECV_TIMEOUT				= 104,	// ���ճ�ʱ

	REMOVE_REASON_PRESEND_ACTIVELIST		= 200,	// ������ϢͶ�ݴ���, ��б���ʱ
	REMOVE_REASON_PRESEND_ALL				= 201,	// ������ϢͶ�ݴ���, ȫ����ϢͬʱͶ��ʱ, IoHandler::ProcessSend
	REMOVE_REASON_SEND_BUFFER_OVERFLOW_USER	= 202,	// ���ͻ��������(���)
	REMOVE_REASON_SEND_BUFFER_OVERFLOW_NPC	= 203,	// ���ͻ��������(npc)

	REMOVE_REASON_TOO_MANY_CONNECT			= 300,	// ͬһ��ip��������ӵ��¶Ͽ�
	
};

class CSocketKernel;
class Session;
class IoHandler;

typedef std::map<DWORD, IoHandler*>		IOHANDLER_MAP;
typedef std::pair<DWORD, IoHandler*>	IOHANDLER_MAP_PAIR;
typedef IOHANDLER_MAP::iterator			IOHANDLER_MAP_ITER;

//typedef NetworkObject* (*fnCallBackCreateAcceptedObject)();
//typedef VOID (*fnCallBackDestroyAcceptedObject)( NetworkObject *pNetworkObject );
//typedef VOID (*fnCallBackDestroyConnectedObject)( NetworkObject *pNetworkObject );

//-------------------------------------------------------------------------------------------------
/// I/O �ڵ鷯 �ʱ�ȭ�� �ʿ��� ������ ��� ����ü
//-------------------------------------------------------------------------------------------------
typedef struct tagIOHANDLER_DESC
{
	DWORD								dwIoHandlerKey;					///< I/O �ڵ鷯 Ű
	DWORD								dwMaxAcceptSession;				///< ���ӹ��� �ִ� ���� ��
	DWORD								dwMaxConnectSession;			///< �ٸ� ������ ������ �ִ� ���� ��
	DWORD								dwSendBufferSize;				///< ������ ���� ũ��
	DWORD								dwRecvBufferSize;				///< �ޱ� ���� ũ��
	//DWORD								dwTimeOut;						///< ���� ���� ������ Ÿ�� �ƿ� ƽ
	DWORD								dwMaxPacketSize;				///< �� ��Ŷ�� �ִ� ũ��
	DWORD								dwNumberOfIoThreads;			///< I/O ��Ŀ ������ ����
	DWORD								dwNumberOfAcceptThreads;		///< Accept ��Ŀ ������ ����
	DWORD								dwNumberOfConnectThreads;		///< Connect ��Ŀ ������ ����
	//fnCallBackCreateAcceptedObject		fnCreateAcceptedObject;			///< ���ӽ� NetworkObject ���� �ݹ�
	//fnCallBackDestroyAcceptedObject		fnDestroyAcceptedObject;		///< ���� ������ NetworkObject �Ҹ� �ݹ�
	//fnCallBackDestroyConnectedObject	fnDestroyConnectedObject;		///< �ٸ� ������ ������ NetworkObject ��ü�� ���� �Ҹ� �ݹ�
} IOHANDLER_DESC, *LPIOHANDLER_DESC;

//-------------------------------------------------------------------------------------------------
/// IOCP ���� Ŭ����
/**
	@remarks
			- IOCP ������ �ټ��� I/O �ڵ鷯�� ���� �� �ִ�.
			  (2�� �̻��� I/O �ڵ鷯�� �ʱ�ȭ�� ��� LPIOHANDLER_DESC�� �迭�� �ʱ�ȭ)
			- I/O �ڵ鷯�� �ϳ��� ���� ��Ʈ�� ������.
			- Update�� ȣ���� �� ��� ������ �ޱ� ���۸� �˻��Ͽ� �ϼ��� ��Ŷ�� ó���Ѵ�.
	@see
			IoHandler
			tagIOHANDLER_DESC
*/
//-------------------------------------------------------------------------------------------------
class IOCPServer
{
	friend unsigned __stdcall send_thread( LPVOID param );

public:
	IOCPServer();
	virtual ~IOCPServer();

	BOOL				Init( LPIOHANDLER_DESC lpDesc, DWORD dwNumberofIoHandlers );
	BOOL				StartListen( DWORD dwIoHandlerKey, char *pIP, WORD wPort );
	BOOL				StartAllListen( char *pIP, WORD wPort );
	BOOL				StartSendProcessThread();
	VOID				Update();
	VOID				Shutdown();
	//DWORD				Connect( DWORD dwIoHandlerKey, NetworkObject *pNetworkObject, char *pszIP, WORD wPort );
	BOOL				IsListening( DWORD dwIoHandlerKey );
	DWORD				GetNumberOfConnections( DWORD dwIoHandlerKey );

	void				SetKernel(CSocketKernel* pKernel);

	int					SetNewClientSocket(Session* pSession);

	int					ProcessData(const char* pRecvBuf,int nSize,Session* pSession);
	void				ProcessDisconnectClient(int i);
	void				ProcessSend();
private:
	BOOL				InitWinsock();
	VOID				CreateIoHandler( LPIOHANDLER_DESC lpDesc );

	HANDLE				m_hSendThread;
	BOOL				m_bShutdown;
	IOHANDLER_MAP		m_mapIoHandlers;

	CSocketKernel*		m_pSocketKernel;
};
#endif	// end of _SERVERSOCKET_IOCPSERVER_H_