#include "stdafx.h"
#include "SocketThread.h"
#include "MyServer.h"

CSocketThread::CSocketThread(IMessagePort* pPort)
{
	ASSERT(pPort);
	m_pMsgPort		= pPort;
	m_pServerSocket	= NULL;
	m_i64LastOnTimerMS	= 0i64;

	m_hMutexThread	= NULL;
}

CSocketThread::~CSocketThread()
{
}

//////////////////////////////////////////////////////////////////////
// overload
//////////////////////////////////////////////////////////////////////
bool CSocketThread::CreateThread(bool bRun /*= true*/,int nServerListenPort)
{
	if(!CThreadBase::CreateThread(bRun))
		return false;

	m_pServerSocket	= ISocketKernel::CreateNew();
	return m_pServerSocket->Create(m_pMsgPort, nServerListenPort);
}

//////////////////////////////////////////////////////////////////////
void CSocketThread::OnDestroy()
{
	if(m_pServerSocket)
		m_pServerSocket->Release();
	m_pServerSocket = NULL;
}

//////////////////////////////////////////////////////////////////////
void CSocketThread::OnInit()	
{ 
	m_i64LastOnTimerMS = ::GetUtcMillisecond(); 
	char	szText[1024];
	sprintf(szText, "#%u: Socket kernel thread running", m_pMsgPort->GetID());
	m_pMsgPort->Send(MSGPORT_SHELL, SHELL_PRINTTEXT, STRING_TYPE(szText), szText);
}

//////////////////////////////////////////////////////////////////////
bool CSocketThread::OnProcess()
{
	CPerformanceStatisticsMS objPSMax(PERFORMANCE_STATISTICS_TYPE_SOCKETTHREAD_ONPROCESS_TIME_MAX, true);
	char	szMsgBuffer[MAX_MESSAGESIZE] = "";
	CMessageStatus	cStatus = {0};

	/////////////////////////////////////////////////////////////////////	
	// 内部消息处理
	try
	{
		int nWhileCount = 0;
		CPerformanceStatisticsMS objPS1(PERFORMANCE_STATISTICS_TYPE_SOCKETTHREAD_MSGPORT_RECV_TIME_SUM);
		while(m_pMsgPort->Recv(PORT_ANY, PACKET_ANY, STRUCT_TYPE(szMsgBuffer), szMsgBuffer, &cStatus))
		{
			const I64 i64Start = ::GetUtcMillisecond();
			if(!m_pServerSocket->ProcessMsg(cStatus.m_nPacket, szMsgBuffer, cStatus.m_nVarType, cStatus.m_nPortFrom))
			{
				tolog4("m_pServerSocket->ProcessMsg Error! nPacket[%d], nVarType[%d], nPortFrom[%d]", cStatus.m_nPacket, cStatus.m_nVarType, cStatus.m_nPortFrom);
			}

			const I64 i64Used = ::GetUtcMillisecond() - i64Start;
			if(i64Used > LOG_TIMEOUT_SOCKET_PROCESS)	// 超时记录
			{ 
				::LogTimeOut("[TimeOut] CSocketThread::OnProcess Other Msg: FromPort[%d], Packet[%d], time[%I64d]", cStatus.m_nPortFrom, cStatus.m_nPacket, i64Used);
			}
			nWhileCount++;
		}
	}
	catch(...)
	{
		LOGERROR("CSocketThread::OnProcess crash! nPacket:%d,nVarType:%d,nPortFrom:%d",cStatus.m_nPacket,cStatus.m_nVarType,cStatus.m_nPortFrom);
	}



	const I64 i64NowMS = ::GetUtcMillisecond();

	// 时钟回滚检测
	if (i64NowMS < m_i64LastOnTimerMS - ONTIMER_MS_ROLLBACK_MS)
	{
		DEBUG_TRY;
		tolog4("SocketThread Timer Rollback! m_i64LastOnTimerMS[%I64d], i64NowMS[%I64d], Diff[%I64d]", m_i64LastOnTimerMS, i64NowMS, m_i64LastOnTimerMS - i64NowMS);
		m_i64LastOnTimerMS = i64NowMS;
		DEBUG_CATCH("m_pServerSocket->OnTimerRollback()")
	}

	// 时钟处理
	if(i64NowMS >= m_i64LastOnTimerMS + SOCKETKERNEL_ONTIMER_MS)
	{
		DEBUG_TRY
			CPerformanceStatisticsMS	objPS1(PERFORMANCE_STATISTICS_TYPE_SOCKETTHREAD_ONTIMER_TIME_SUM);
		CPerformanceStatisticsCount objPS2(PERFORMANCE_STATISTICS_TYPE_SOCKETTHREAD_ONTIMER_TIME_COUNT);
		m_i64LastOnTimerMS = i64NowMS;
		m_pServerSocket->OnTimer();
		DEBUG_CATCH("m_pServerSocket->OnTimer()")
	}

	Sleep(1);
	return true;
}




