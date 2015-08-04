#include "stdafx.h"
#include "MyServer.h"
#include "LoginThread.h"

//////////////////////////////////////////////////////////////////////////
CLoginThread::CLoginThread( IMessagePort* pPort )
{
	ASSERT(pPort);
	m_pMsgPort			= pPort;
	m_pLoginKernel		= NULL;
	m_i64LastOnTimerMS	= 0i64;
}

//////////////////////////////////////////////////////////////////////////
CLoginThread::~CLoginThread()
{

}

//////////////////////////////////////////////////////////////////////////
bool CLoginThread::CreateThread( bool bRun /*= true*/ )
{
	if(!CThreadBase::CreateThread(bRun))
		return false;

	m_pLoginKernel = ILoginKernel::Instance();
	return m_pLoginKernel->Create(m_pMsgPort);
}

//////////////////////////////////////////////////////////////////////////
void CLoginThread::OnInit()
{
	m_i64LastOnTimerMS = ::GetUtcMillisecond(); 
	char	szText[1024] = "";
	sprintf(szText, "#%u: GameKernel thread running", m_pMsgPort->GetID());
	m_pMsgPort->Send(MSGPORT_SHELL, SHELL_PRINTTEXT, STRING_TYPE(szText), szText);
}

//////////////////////////////////////////////////////////////////////////
bool CLoginThread::OnProcess()
{
	Sleep(1);
	CPerformanceStatisticsMS objPSMax(PERFORMANCE_STATISTICS_TYPE_LOGINTHREAD_ONPROCESS_TIME_MAX, true);
	char	szMsgBuf[MAX_MESSAGESIZE] = "";
	CMessageStatus	cStatus = {0};

	DEBUG_TRY;
	CPerformanceStatisticsMS objPS1(PERFORMANCE_STATISTICS_TYPE_LOGINTHREAD_MSGPORT_RECV_TIME_SUM);
	int nWhileCount = 0;
	while (m_pMsgPort->Recv(PORT_ANY, PACKET_ANY, STRUCT_TYPE(szMsgBuf), szMsgBuf, &cStatus))
	{
		const I64 i64Start = ::GetUtcMillisecond();
		if(!m_pLoginKernel->ProcessMsg(cStatus.m_nPacket, szMsgBuf, cStatus.m_nVarType, cStatus.m_nPortFrom))
		{
			tolog4("m_pLoginKernel->ProcessMsg Error! nPacket[%d], nVarType[%d], nPortFrom[%d]", cStatus.m_nPacket, cStatus.m_nVarType, cStatus.m_nPortFrom);
		}
		const I64 i64Used = ::GetUtcMillisecond() - i64Start;
		if(i64Used > LOG_TIMEOUT_LOGIN_PROCESS)	// 超时记录
		{
			if( LOGINTHREAD_CLIENT_MSG == cStatus.m_nPacket )
			{
				const CLIENTMSG_PACKET* pPack = (CLIENTMSG_PACKET*)szMsgBuf;
				if (pPack)
				{
					::LogTimeOut("[TimeOut] CGameThread::OnProcess MsgID[%d], Len[%d], Time[%I64d], nPacket[%d], nVarType[%d], nPortFrom[%d]", pPack->idPacket, pPack->nSize, i64Used, cStatus.m_nPacket, cStatus.m_nVarType, cStatus.m_nPortFrom);
				}
			}
		}
		nWhileCount++;
	}
	DEBUG_CATCH2("CLoginThread::OnProcess() cStatus.m_nPacket[%d]", cStatus.m_nPacket);


	const I64 i64NowMS = ::GetUtcMillisecond();

	// 时钟回滚检测
	if (i64NowMS < m_i64LastOnTimerMS - ONTIMER_MS_ROLLBACK_MS)
	{
		DEBUG_TRY;
		tolog4("CLoginThread Timer Rollback! m_i64LastOnTimerMS[%I64d], i64NowMS[%I64d], Diff[%I64d]", m_i64LastOnTimerMS, i64NowMS, m_i64LastOnTimerMS - i64NowMS);
		m_i64LastOnTimerMS = i64NowMS;
		m_pLoginKernel->OnTimerRollback();
		DEBUG_CATCH("m_pLoginKernel->OnTimerRollback()")
	}

	// 心跳处理
	if(i64NowMS >= m_i64LastOnTimerMS + GAMEKERNEL_ONTIMER_MS)
	{
		DEBUG_TRY;
		CPerformanceStatisticsMS	objPS3(PERFORMANCE_STATISTICS_TYPE_LOGINTHREAD_ONTIMER_TIME_SUM);
		CPerformanceStatisticsCount	objPS4(PERFORMANCE_STATISTICS_TYPE_LOGINTHREAD_ONTIMER_TIME_COUNT);
		m_i64LastOnTimerMS = i64NowMS;
		m_pLoginKernel->OnTimer();
		DEBUG_CATCH("m_pLoginKernel->OnTimer()")
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////
void CLoginThread::OnDestroy()
{
	SAFE_RELEASE(m_pLoginKernel);
	ILoginKernel::DelInstance();
}
