// TimeOut.cpp: implementation of the CTimeOut class.
//
//////////////////////////////////////////////////////////////////////
#ifndef WINVER 
#define WINVER 0x0501
#endif  

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0501
#endif
#pragma warning(disable:4996)

#include "windows.h"
#include "TimeOut.h"

MYHEAP_IMPLEMENTATION(CTimeOut, s_heap);
MYHEAP_IMPLEMENTATION(CTimeOutMS, s_heap);

//////////////////////////////////////////////////////////////////////
// CTimeOut
//////////////////////////////////////////////////////////////////////
// 带时间积累的定时时钟
bool CTimeOut::ToNextTick(int nSecs)
{
	bool result=IsTimeOut(nSecs);
	if(result)
	{
		time_t value=time(NULL);
		if(value >= m_tUpdateTime + nSecs*2)
		{
			Update();
			return true;
		}
		else
		{	
			m_tUpdateTime+=nSecs;
			return true;
		}
	}
	else
		return false;
}

//////////////////////////////////////////////////////////////////////
// CTimeOutMS
//////////////////////////////////////////////////////////////////////
// 带时间积累的定时时钟
bool CTimeOutMS::ToNextTick(I64 i64MilliSecs)
{
	bool result=IsTimeOut(i64MilliSecs);
	if(result)
	{
		if(::GetUtcMillisecond() >= m_i64UpdateTime + i64MilliSecs*2)
		{
			Update();
			return true;
		}
		else
		{
			m_i64UpdateTime+=i64MilliSecs;
			return true;
		}
	}
	else
		return false;
}

I64 CTimeOutMS::GetRemain()  // 单独提出来处理，因为坐骑BUF时间为-1 [陈剑飞8/4/2007]
{
	if(m_i64Interval < 0) 
		return m_i64Interval; 
	else 
		return m_i64UpdateTime ? ::CutRange(m_i64Interval - (::GetUtcMillisecond()-m_i64UpdateTime), 0i64, m_i64Interval) : 0i64; 
}
