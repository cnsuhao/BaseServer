// ServerSocket.h: interface for the CSocketKernel class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SERVERSOCKET_H__44A9ACE7_FE12_4CDC_9492_F39CD1423D77__INCLUDED_)
#define AFX_SERVERSOCKET_H__44A9ACE7_FE12_4CDC_9492_F39CD1423D77__INCLUDED_

#pragma warning(disable:4786)
#include <time.h>
#include "../MSGSERVER/share/define.h"

//zeng 修改为IOCP



#include <vector>
#include <list>
#include <map>
using namespace std;

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "Session.h"
//#include "IOCPServer.h"

class Session;
class IOCPServer;

class CSocketKernel : ISocketKernel
{
	//friend class IOCPS;
	//friend class CWorkUnit;
public:
	CSocketKernel() {}		// 建议留空
	virtual ~CSocketKernel() {}		// 建议留空

public:
	ISocketKernel*	GetInterface() { return (ISocketKernel*)this; }

public:
	virtual bool	Create(IMessagePort* pPort, int nListenPort);
	virtual bool	ProcessMsg(OBJID idPacket, void* buf, int nType, int nFrom);
	virtual bool	OnTimer();
	virtual bool	Release();

public:
	bool	SendCloseNotify(SOCKET_ID idSocket);
	//? 暂时用于控制只通知核心关闭一次
	bool	IsNetBreakFlag(SOCKET_ID idSocket)			{ return (idSocket>=0 && idSocket<(int)m_setSocket.size() && m_setSocket[idSocket] && m_setNetBreakFlag[idSocket]);}
	void	SetNetBreakFlag(SOCKET_ID idSocket)			{ if(idSocket>=0 && idSocket<(int)m_setSocket.size() && m_setSocket[idSocket]) m_setNetBreakFlag[idSocket] = true; }

public:
	//void			AcceptNewSocket();
	int				SetNewSocket(Session* sNew);
	int				ProcessRecvMsg(const char* pRecvBuf,int nSize,Session* pSession);
	void			ProcessDisconnServer(int i);
protected:
	//IListenSocket*	m_pListen;

	std::vector<Session*>	m_setSocket;			// SOCKET_ID对应索引,以下四个SET同步添加删除!
	CRITICAL_SECTION		m_ReuseIDListLock;		// 同步用的临界区
	list<UINT>				m_ReuseIDList;			// 记录m_setSocket中可以使用的idsocket
	std::vector<PROCESS_ID>	m_setProcessID;			// PROCESS_ID对应MSGPORT号
	std::vector<bool>		m_setNetBreakFlag;
	
	IMessagePort*			m_pMsgPort;
	IOCPServer*				m_piocpServer;
		UINT				m_unOnlineSecond;
		bool				m_bRelease;
};

#endif // !defined(AFX_SERVERSOCKET_H__44A9ACE7_FE12_4CDC_9492_F39CD1423D77__INCLUDED_)
