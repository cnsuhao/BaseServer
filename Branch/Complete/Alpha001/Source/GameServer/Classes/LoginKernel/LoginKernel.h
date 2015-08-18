#ifndef _LOGIN_KERNEL_H_
#define _LOGIN_KERNEL_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../../Share/I_Shell.h"
#include "../../Share/protocol.h"
#include "../../DataBase/I_mydb.h"
#include "./Network/NetMsg.h"

#include <time.h>
#include <winsock2.h>

class CLoginKernel : ILoginKernel
{
	// 单例实现
public:
	static CLoginKernel* GetInstance(void)	{if (NULL == s_pInstance) s_pInstance = new CLoginKernel; return s_pInstance;}
	static void			 DelInstance(void)	{SAFE_DELETE(s_pInstance);}
	MYHEAP_DECLARATION(s_heap);
private:
	CLoginKernel();
	virtual ~CLoginKernel() {}
	CLoginKernel(const CLoginKernel&){}
	static CLoginKernel*	s_pInstance;

	// IGameKernel 接口继承
public:
	virtual bool	Create			(IMessagePort* pPort);
	virtual bool	Release			(void);
	virtual bool	ProcessMsg		(OBJID idPacket, void* buf, int nType, int nFrom);
	virtual bool	OnTimer			(void);
	virtual bool	OnTimerRollback	(void);
	virtual void	PrintText(const char* pszText);

public:
	IDatabase*		GetDatabase(){return m_pDb;}

public:
	void			ProcessAccountLogin (SOCKET_ID idSocket, const char* pszAccountName, const char* pszAccountPassword);
	int				ProcessCreateUser	(SOCKET_ID idSocket, const char* pszName, int nFaction, int nMainFly, OUT int& nUserID);
	bool			ProcessChooseUser	(SOCKET_ID idSocket, OBJID idUser);
	bool			ProcessDeleteUser	(SOCKET_ID idSocket, OBJID idUser);

private:
	PROCESS_ID		m_idProcess;
	IDatabase*		m_pDb;
	IMessagePort*	m_pMsgPort;

	bool			m_bOpenLogin;		// 是否开放登陆

};

#define pLoginKernel CLoginKernel::GetInstance()
#define pLoginDatabase CLoginKernel::GetInstance()->GetDatabase()

#endif // end of _LOGIN_KERNEL_H_