#ifndef _GAME_KERNEL_H_
#define _GAME_KERNEL_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "I_Shell.h"
#include "protocol.h"
#include "I_mydb.h"
#include "Network/NetMsg.h"

#include <time.h>
#include <winsock2.h>

class CGameKernel : IGameKernel
{
	// 单例实现
public:
	static CGameKernel*	GetInstance(void)	{if (NULL == s_pInstance) s_pInstance = new CGameKernel; return s_pInstance;}
	static void			DelInstance(void)	{SAFE_DELETE(s_pInstance);}
	MYHEAP_DECLARATION(s_heap);
private:
	CGameKernel();
	virtual ~CGameKernel() {}
	CGameKernel(const CGameKernel&){}
	static CGameKernel*	s_pInstance;

	// IGameKernel 接口继承
public:
	virtual bool	Create			(IMessagePort* pPort);
	virtual bool	Release			(void);
	virtual bool	ProcessMsg		(OBJID idPacket, void* buf, int nType, int nFrom);
	virtual bool	OnTimer			(void);
	virtual bool	OnTimerRollback	(void);
	virtual void	PrintText		(const char* pszText);
	
public:
	IDatabase*		GetDatabase		(void)	{ return m_pDb; }
	bool			SendMsg			(game_kernel::CNetMsg* pMsg, SOCKET_ID idSocket = SOCKET_NONE);
	bool			BroadcastMsg	(game_kernel::CNetMsg* pMsg);
	void			CloseSocket		(SOCKET_ID idSocket);
	void			BreakAllUser	(void);

private:
	PROCESS_ID		m_idProcess;
	IDatabase*		m_pDb;
	IMessagePort*	m_pMsgPort;

};

#define pGameKernel CGameKernel::GetInstance()
#define pGameDatabase CGameKernel::GetInstance()->GetDatabase()

#endif // end of _GAME_KERNEL_H_