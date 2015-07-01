#ifndef _SOCKET_THREAD_H_
#define _SOCKET_THREAD_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../Share/protocol.h"
#include "../share/I_Shell.h"
#include "../Common/ThreadBase.h"
#include "../Common/TimeOut.h"
#include "../Common/MessagePort/MessagePort.h"

class IMessagePort;
class CSocketThread : public CThreadBase  
{
public:
	CSocketThread(IMessagePort* pPort);
	virtual ~CSocketThread();

public: // overload
	virtual	bool	CreateThread(bool bRun = true,int SERVER_LISTEN_PORT=SERVER_LISTEN_PORT_DEFAULT);		// false: �ݲ����У��� ResumeThread() ����

	/////////////////////////////////////////////////////////////////////
protected:	// ������
	//overrideable
	virtual	void	OnInit();
	virtual bool	OnProcess();		// ����Ҫ����DWORD
	virtual void	OnDestroy();

protected: // ���Ķ��󼰽ӿ�
	CTimeOutMS		m_tCnt;

	I64 m_i64LastOnTimerMS;
	ISocketKernel*	m_pServerSocket;
	IMessagePort*	m_pMsgPort;

protected: // ctrl
	HANDLE	m_hMutexThread;
};

#endif // _SOCKET_THREAD_H_
