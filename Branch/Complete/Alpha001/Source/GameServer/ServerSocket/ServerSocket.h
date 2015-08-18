// ServerSocket.h: interface for the CSocketKernel class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SERVERSOCKET_H__44A9ACE7_FE12_4CDC_9492_F39CD1423D77__INCLUDED_)
#define AFX_SERVERSOCKET_H__44A9ACE7_FE12_4CDC_9492_F39CD1423D77__INCLUDED_

#pragma warning(disable:4786)
#include "../Share/define.h"
#include "../Share/protocol.h"
#include "../Share/I_Shell.h"
#include <time.h>
#include <vector>
#include <list>
#include <map>
using namespace std;

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Session;
class IOCPServer;
class CSocketKernel : ISocketKernel
{
public:
	CSocketKernel() {}
	virtual ~CSocketKernel() {}

public:
	ISocketKernel*	GetInterface(void) { return (ISocketKernel*)this; }

public:
	virtual bool	Create		(IMessagePort* pPort, int nListenPort);
	virtual bool	ProcessMsg	(OBJID idPacket, void* buf, int nType, int nFrom);
	virtual bool	OnTimer		(void);
	virtual bool	Release		(void);

public:
	bool	CheckMsgTail		(Session* pSession, IN OUT CLIENTMSG_PACKET* pPacket);
	int		ProcessRecvMsg		(const char* pRecvBuf,int nSize,Session* pSession);

	int		SetNewSocket		(Session* sNew);
	void	ProcessDisconnServer(int i, bool bSendOtherThread = true);
private:
	bool	BroadcastMsg		(const CLIENTMSG_PACKET* pPack);

public:
	bool	SendCloseNotify		(SOCKET_ID idSocket);

	// ��ʱ���ڿ���ֻ֪ͨ���Ĺر�һ��
	bool	IsNetBreakFlag		(SOCKET_ID idSocket)	{ return (idSocket>=0 && idSocket<(int)m_setSocket.size() && m_setSocket[idSocket] && m_setNetBreakFlag[idSocket]);}
	void	SetNetBreakFlag		(SOCKET_ID idSocket)	{ if(idSocket>=0 && idSocket<(int)m_setSocket.size() && m_setSocket[idSocket]) m_setNetBreakFlag[idSocket] = true; }

protected:
	std::vector<Session*>	m_setSocket;				// SOCKET_ID��Ӧ����,�����ĸ�SETͬ�����ɾ��!
	CRITICAL_SECTION		m_ReuseIDListLock;			// ͬ���õ��ٽ���
	list<UINT>				m_ReuseIDList;				// ��¼m_setSocket�п���ʹ�õ�idsocket
	std::vector<bool>		m_setNetBreakFlag;
	
	IMessagePort*			m_pMsgPort;
	IOCPServer*				m_piocpServer;
	bool					m_bRelease;

	std::set<SOCKET_ID>		m_setLoginOverSocket;		// ͨ������ɵ�½socket
	CRITICAL_SECTION		m_csLoginOverSocket;		// ͬ���õ��ٽ���
};

#endif // !defined(AFX_SERVERSOCKET_H__44A9ACE7_FE12_4CDC_9492_F39CD1423D77__INCLUDED_)
