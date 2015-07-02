#ifndef _SERVERSOCKET_IOCPSERVER_H_
#define _SERVERSOCKET_IOCPSERVER_H_ 

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma comment( lib, "ws2_32.lib" )
#include "../../../Include/Global.h"
#include <windows.h>
#include <map>

// iocp层基本参数设置
const int	CLIENT_IOCP_SOCKET_KEEPALIVE_INTERVAL	= 60 * 1000;	// 客户端iocp套接字参数		心跳探测间隔	[连接怀疑不正常时]
const int	CLIENT_IOCP_SOCKET_KEEPALIVE_TIME		= 5 * 1000;		// 客户端iocp套接字参数		心跳探测间隔	[连接正常时]
const int	CLIENT_IOCP_SOCKET_BUF					= 32 * 1024;	// 客户端iocp套接字参数		缓冲区大小		[发送/接收]相同
const int	CLIENT_IOCP_SOCKET_TIMOUT				= 10;			// 客户端iocp套接字参数		超时时间限制	[发送/接收]相同
const int	CLIENT_IOCP_SOCKET_MAX_TIMEOUT_COUNT	= 10;			// 客户端iocp套接字参数		超时次数限制	[发送/接收]共用
const int	NPC_IOCP_LIST_SEND_BUF					= 512 * 1024;	// npc的发送缓冲区参数(npc服务器设置的比较大)
const int	NPC_IOCP_LIST_RECV_BUF					= 512 * 1024;	// npc的接收缓冲区参数(npc服务器设置的比较大)
const DWORD CLIENT_IOCP_MIN_IO_WORKER_THREAD_COUNT	= 4;			// 客户端iocp最小工作者线程数
const DWORD CLIENT_IOCP_MAX_IO_WORKER_THREAD_COUNT	= 16;			// 客户端iocp最大工作者线程数
const DWORD NPCSERVER_IOCP_IO_WORKER_THREAD_COUNT	= 2;			// Npc服务器 iocp工作者线程数量
const I64	FORCE_PROCESS_DEAD_SESSION_MS			= 3000;			// 3秒后强制断开, 不管消息有没有发完
const DWORD	FORCE_KICKOUT_ERROR_MSGTAIL_COUNT		= 29;			// 超过指定个数包尾错误, 就会强制踢人

// 会话移除原因
enum REMOVE_REASON
{
	REMOVE_REASON_NONE						= 0,	// 未被移除
	REMOVE_REASON_RECV_PROCESS				= 1,	// 处理接受消息错误
	REMOVE_REASON_KILL_ALL_SESSION			= 2,	// 关服时, 关闭所有会话
	REMOVE_REASON_SETNPCSOCKETID			= 3,	// 设置npc服务器套接字id失败
	REMOVE_REASON_KICK_ONE					= 4,	// 逻辑层(世界核心或地图组) 踢某个人
	REMOVE_REASON_KICK_ALL					= 5,	// 逻辑层(世界核心或地图组) 踢全部人
	REMOVE_REASON_SOCKET_KERNEL_RELEASE		= 6,	// 网络核心析构
	REMOVE_REASON_UNDER_ATTACK				= 7,	// 受到攻击过多断开
	
	//////////////////////////////////////////////////////////////////////////
	REMOVE_REASON_FORCE_BEGIN				= 100,	// 强制移除开始, 这个标志不准程序内使用 

	// 101-199表示io_thread中出错的, 200-299表示缓冲区问题, 300-399表示其他问题
	REMOVE_REASON_GQCS_ERROR				= 101,	// GetQueuedCompletionStatus失败, 并带错误码
	REMOVE_REASON_CLIENT_BREAK				= 102,	// 客户端主动断开连接
	REMOVE_REASON_PRERECV_ERROR				= 103,	// 接收消息投递错误
	REMOVE_REASON_RECV_TIMEOUT				= 104,	// 接收超时

	REMOVE_REASON_PRESEND_ACTIVELIST		= 200,	// 发送消息投递错误, 活动列表处理时
	REMOVE_REASON_PRESEND_ALL				= 201,	// 发送消息投递错误, 全部消息同时投递时, IoHandler::ProcessSend
	REMOVE_REASON_SEND_BUFFER_OVERFLOW_USER	= 202,	// 发送缓冲区溢出(玩家)
	REMOVE_REASON_SEND_BUFFER_OVERFLOW_NPC	= 203,	// 发送缓冲区溢出(npc)

	REMOVE_REASON_TOO_MANY_CONNECT			= 300,	// 同一个ip过多的连接导致断开
	
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
/// I/O 勤甸矾 檬扁拳俊 鞘夸茄 沥焊甫 淬绰 备炼眉
//-------------------------------------------------------------------------------------------------
typedef struct tagIOHANDLER_DESC
{
	DWORD								dwIoHandlerKey;					///< I/O 勤甸矾 虐
	DWORD								dwMaxAcceptSession;				///< 立加罐阑 弥措 技记 荐
	DWORD								dwMaxConnectSession;			///< 促弗 辑滚肺 立加且 弥措 技记 荐
	DWORD								dwSendBufferSize;				///< 焊郴扁 滚欺 农扁
	DWORD								dwRecvBufferSize;				///< 罐扁 滚欺 农扁
	//DWORD								dwTimeOut;						///< 立加 罐篮 技记狼 鸥烙 酒眶 平
	DWORD								dwMaxPacketSize;				///< 茄 菩哦狼 弥措 农扁
	DWORD								dwNumberOfIoThreads;			///< I/O 况目 静饭靛 俺荐
	DWORD								dwNumberOfAcceptThreads;		///< Accept 况目 静饭靛 俺荐
	DWORD								dwNumberOfConnectThreads;		///< Connect 况目 静饭靛 俺荐
	//fnCallBackCreateAcceptedObject		fnCreateAcceptedObject;			///< 立加矫 NetworkObject 积己 妮归
	//fnCallBackDestroyAcceptedObject		fnDestroyAcceptedObject;		///< 立加 秦力矫 NetworkObject 家戈 妮归
	//fnCallBackDestroyConnectedObject	fnDestroyConnectedObject;		///< 促弗 辑滚肺 立加茄 NetworkObject 按眉俊 措茄 家戈 妮归
} IOHANDLER_DESC, *LPIOHANDLER_DESC;

//-------------------------------------------------------------------------------------------------
/// IOCP 辑滚 努贰胶
/**
	@remarks
			- IOCP 辑滚绰 促荐狼 I/O 勤甸矾甫 啊龙 荐 乐促.
			  (2俺 捞惑狼 I/O 勤甸矾甫 檬扁拳且 版快 LPIOHANDLER_DESC甫 硅凯肺 檬扁拳)
			- I/O 勤甸矾绰 窍唱狼 府郊 器飘甫 啊柳促.
			- Update甫 龋免且 锭 葛电 技记狼 罐扁 滚欺甫 八荤窍咯 肯己等 菩哦阑 贸府茄促.
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