// NetMsg.h: interface for the CNetMsg class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _GAME_KERNEL_NETMSG_H
#define _GAME_KERNEL_NETMSG_H

#pragma	warning(disable:4786)
#include "basefunc.h"
#include "define.h"
#include "myheap.h"


namespace game_kernel
{
	class CNetMsg
	{
	public:
		CNetMsg();
		virtual ~CNetMsg();

		void	Init(void);
		void	Reset(void)	{Init();}

		SOCKET_ID	GetSocketID()	{return m_idSocket;}
		OBJID	GetType	(void)		{return m_unMsgType;}
		int		GetSize	(void)		{return m_unMsgSize;}

		char*	GetBuf(void)		{return m_bufMsg;}
		void	Release()			{delete this;}

	public:	
		virtual BOOL	Create		(char* pMsgBuf, DWORD dwSize);
		virtual BOOL	IsValid		(void);
		virtual void	Process		(void *pInfo);
 		virtual	void	DumpMsg		(const char* szReasion,...);///参数为导出这个消息的原因
		virtual bool	IsClientMsg	(void) const;
		virtual void	SetAIProcess(void) {m_bAIProcess = true;}

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
		bool		m_bAIProcess;

	public:
		MYHEAP_DECLARATION(s_heap)
	};
}// end of game_kernel

#endif // end of _GAME_KERNEL_NETMSG_H
