// NetMsg.h: interface for the CNetMsg class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _LOGIN_KERNEL_NETMSG_H
#define _LOGIN_KERNEL_NETMSG_H

#pragma	warning(disable:4786)
#include "basefunc.h"
#include "../../share/define.h"
#include "myheap.h"


namespace login_kernel
{
	class CNetMsg
	{
	public:
		CNetMsg();
		virtual ~CNetMsg();

		void	Init(void);
		void	Reset(void)	{Init();}

		SOCKET_ID	GetSocketID()		{return m_idSocket;}
		OBJID		GetType	(void)		{return m_unMsgType;}
		int			GetSize	(void)		{return m_unMsgSize;}
		char*		GetBuf(void)		{return m_bufMsg;}
		void		Release()			{delete this;}

	public:	
		virtual BOOL			Create		(char* pMsgBuf, DWORD dwSize);
		virtual BOOL			IsValid		(void);
		virtual void			Process		(void *pInfo);
 		virtual	void			DumpMsg		(const char* szReasion,...);///参数为导出这个消息的原因

	public:
		static CNetMsg*	CreateClientMsg	(PROCESS_ID idProcess, SOCKET_ID idSocket,	OBJID idMsg, const char* pbufMsg, DWORD dwMsgSize);
		static CNetMsg*	CreateMsg	(OBJID idMsg, const char* pbufMsg, DWORD dwMsgSize);

		bool	ForceSetMsgHeader(PROCESS_ID idProcess, SOCKET_ID idSocket);

	protected:
		OBJID		m_unMsgType;
		int			m_unMsgSize;
		char		m_bufMsg[_MAX_MSGSIZE];

		PROCESS_ID	m_idProcess;
		SOCKET_ID	m_idSocket;

	public:
		MYHEAP_DECLARATION(s_heap)
	};
}// end of login_kernel

#endif // end of _LOGIN_KERNEL_NETMSG_H
