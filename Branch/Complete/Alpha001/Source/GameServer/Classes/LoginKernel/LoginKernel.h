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
	// ����ʵ��
public:
	static CLoginKernel* GetInstance(void)	{if (NULL == s_pInstance) s_pInstance = new CLoginKernel; return s_pInstance;}
	static void			 DelInstance(void)	{SAFE_DELETE(s_pInstance);}
	MYHEAP_DECLARATION(s_heap);
private:
	CLoginKernel();
	virtual ~CLoginKernel() {}
	CLoginKernel(const CLoginKernel&){}
	static CLoginKernel*	s_pInstance;

	// IGameKernel �ӿڼ̳�
public:
	virtual bool	Create				(IMessagePort* pPort);
	virtual bool	Release				(void);
	virtual bool	ProcessMsg			(OBJID idPacket, void* buf, int nType, int nFrom);
	virtual bool	OnTimer				(void);
	virtual bool	OnTimerRollback		(void);
	virtual void	PrintText			(const char* pszText);

	bool			SendMsg				(login_kernel::CNetMsg* pMsg, SOCKET_ID idSocket = SOCKET_NONE);
	bool			SendMsg				(OBJID idAccount, login_kernel::CNetMsg* pMsg);
	IDatabase*		GetDatabase			(void)	{ return m_pDb; }

public:
	void			ProcessAccountLogin (SOCKET_ID idSocket, const char* pszAccountName, const char* pszAccountPassword);
	int				ProcessCreateUser	(SOCKET_ID idSocket, const char* pszUserName, int nCamp, int nFlagShip, OUT int& nUserID);
	bool			ProcessChooseUser	(SOCKET_ID idSocket, OBJID idUser);
	bool			ProcessDeleteUser	(SOCKET_ID idSocket, OBJID idUser);
	void			ProcessQueryLogin	(SOCKET_ID idSocket);

protected:
	OBJID			GetAccountID		(SOCKET_ID idSocket) const;
	int				GetAccountEnterPos	(OBJID idAccount) const;

	void			SendUserList		(OBJID idAccount);

	void			KickOutBySocket		(SOCKET_ID idSocket, KICK_REASON eReason = KICK_REASON_DEFAULT, int nParam = 0);

	void			OnTimerAccountEnetr	(void);
	void			OnTimerKickTimeOut	(void);

private:
	INT_MAP								m_mapSocket;		 // Ψһ��Ӧ���˺�Socket��Ϣ��SocketIDΪfisrt,  idAccountΪsecond��
	std::map<OBJID, ACCOUNT_INFO>		m_mapAccount;		 // �˺���Ϣ(idAccountΪfisrt, AccountInfoΪsecond)
	std::deque<OBJID>					m_deqAccountEnter;	 // �Ŷӽ����idAccount
	ID_SET								m_setAccountEnterOk; // �Ѿ������idAccount

	PROCESS_ID			m_idProcess;			// �߳�ͨ�Źܵ�ID
	IMessagePort*		m_pMsgPort;				// �߳�ͨ�Źܵ�

	IDatabase*			m_pDb;					// ���ݿ����

	bool				m_bOpenLogin;			// �Ƿ񿪷ŵ�½
	UINT				m_unKickTimeOutSecond;	// �߳���ʱ	�������
};

#define pLoginKernel	CLoginKernel::GetInstance()
#define pLoginDatabase	CLoginKernel::GetInstance()->GetDatabase()

#endif // end of _LOGIN_KERNEL_H_