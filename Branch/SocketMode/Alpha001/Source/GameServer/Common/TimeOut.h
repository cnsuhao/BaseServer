// TimeOut.h: interface for the CTimeOut class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TIMEOUT_H__059AED43_D21C_4072_A172_20A7D8B6DF52__INCLUDED_)
#define AFX_TIMEOUT_H__059AED43_D21C_4072_A172_20A7D8B6DF52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <time.h>
#include "BaseFunc.h"
#include "MyHeap.h"

//////////////////////////////////////////////////////////////////////
// 超时类，以“秒”为单位
class CTimeOut
{
public:
	CTimeOut(int nIntervalSecs = 0)
	{ 
		m_nInterval = nIntervalSecs;
		m_tUpdateTime = 0;
	}		

public:
	// 设置时间标签
	void	Update		()
	{ 
		m_tUpdateTime = ::time(NULL);
	}
	// 检查是否超时
	bool	IsTimeOut	()
	{
		bool result= ::time(NULL) >= m_tUpdateTime + m_nInterval;
		return result;
	}
	// 用于定时触发的连续时钟。每次触发时为true。
	bool	ToNextTime	()
	{ 
		bool result=IsTimeOut();
		if(result)
		{
			Update();
			return true;
		}
		else 
			return false;
	}
	// 初始化时间片。(但不启动)
	void	SetInterval	(int nSecs)
	{ 
		m_nInterval = nSecs;
	}

	// 开始启动时钟(同SetInterval)
	void	Startup		(int nSecs)
	{ 
		m_nInterval = nSecs;
		Update();
	}
	// 时钟是否触发(只触发一次)，与Startup配合使用，可实现只触发一次的时钟。
	bool	TimeOver	()
	{ 
		if(IsActive() && IsTimeOut())
		{
			Clear();
			return true;
		}
		else
			return false;
	}
	void	Clear		()
	{ 
		m_nInterval = 0;
		m_tUpdateTime = 0;
	}
	bool	IsActive	()
	{ 
		return m_tUpdateTime != 0;
	}
	void	IncInterval	(int nSecs, int nLimit)
	{ 
		m_nInterval = ::CutOverflow(m_nInterval+nSecs, nLimit);
	}
	void	DecInterval	(int nSecs)
	{ 
		m_nInterval = ::CutTrail(m_nInterval-nSecs, 0);
	}

	// 检查是否超时了指定时间片。用于同一时间标签检查多个不同超时事件。(可实现一个对象控制多个时钟)
	bool	IsTimeOut	(int nSecs)
	{
		bool result=::time(NULL) >= m_tUpdateTime + nSecs;
		return result;
	}
	// 用于变长的超时事件。
	bool	ToNextTime	(int nSecs)
	{ 
		bool result=IsTimeOut(nSecs);
		if(result)
		{
			Update();
			return true;
		}
		else 
			return false;
	}
	// 时钟是否触发(只触发一次)，与Startup配合使用，可实现只触发一次的时钟。
	bool	TimeOver	(int nSecs)
	{ 
		if(IsActive() && IsTimeOut(nSecs))
		{
			Clear();
			return true;
		}
		else
			return false;
	}
	// 时钟会积累，但积累值不超过间隔值。其它同ToNextTime(...)
	bool	ToNextTick	(int nSecs);

public: // get
	int		GetRemain()
	{ 
		return m_tUpdateTime ? ::CutRange(m_nInterval - (int)(::time(NULL)-m_tUpdateTime), 0, m_nInterval) : 0;
	}
	int		GetInterval()
	{ 
		return m_nInterval;
	}
//06.11.7添加,为了支持切换地图组-慎用----begin----------------------------------------------------
	time_t	GetUpdateTime()
	{ 
		return m_tUpdateTime;
	}
	void	SetUpdateTime( time_t time )
	{ 
		m_tUpdateTime = time;
	}
//-----------------------------------------end------------------------------------------------------
protected:
	int		m_nInterval;
	time_t	m_tUpdateTime;
public:
	MYHEAP_DECLARATION(s_heap);
};

//////////////////////////////////////////////////////////////////////
// 超时类，以“毫秒”为单位
class CTimeOutMS
{
public:
	CTimeOutMS(I64 i64IntervalSecs = 0i64)
	{ 
		m_i64Interval = i64IntervalSecs;
		m_i64UpdateTime = 0i64;
	}		

public:
	void	Update		()
	{ 
		m_i64UpdateTime = ::GetUtcMillisecond();
	}
	bool	IsTimeOut	()						
	{
		I64 i64NowTime = ::GetUtcMillisecond();
		return i64NowTime >= m_i64UpdateTime + m_i64Interval;
	}
	bool	ToNextTime	()
	{ 
		if(IsTimeOut())
		{
			Update();
			return true;
		}
		else
			return false;
	}
	void	SetInterval	(I64 i64MilliSecs)
	{ 
		m_i64Interval = i64MilliSecs;
	}
	void	Startup		(I64 i64MilliSecs)
	{ 
		m_i64Interval = i64MilliSecs;
		Update();
	}
	bool	TimeOver	()
	{ 
		if(IsActive() && IsTimeOut())
		{
			Clear();
			return true;
		}
		else
			return false;
	}
	void	Clear		()
	{ 
		m_i64Interval = m_i64UpdateTime = 0i64;
	}
	bool	IsActive	()
	{ 
		return m_i64UpdateTime != 0i64;
	}
	void	IncInterval	(I64 i64MilliSecs, I64 i64Limit)
	{ 
		m_i64Interval = ::CutOverflow(m_i64Interval+i64MilliSecs, i64Limit);
	}
	void	DecInterval	(I64 i64MilliSecs)
	{ 
		m_i64Interval = ::CutTrail(m_i64Interval-i64MilliSecs, 0i64);
	}
	bool	IsTimeOut	(I64 i64MilliSecs)
	{ 
		I64 i64NowTime = ::GetUtcMillisecond();
		return i64NowTime >= m_i64UpdateTime+i64MilliSecs;
	}
	I64		LeaveTime()
	{ 
		return ::GetUtcMillisecond() - m_i64UpdateTime - m_i64Interval;
	}
	bool	ToNextTime	(I64 i64MilliSecs)
	{ 
		if(IsTimeOut(i64MilliSecs))
		{
			Update();
			return true;
		}
		else 
			return false;
	}
	bool	TimeOver	(I64 i64MilliSecs)
	{ 
		if(IsActive() && IsTimeOut(i64MilliSecs))
		{
			Clear();
			return true;
		}
		else
			return false;
	}
	bool	ToNextTick	(I64 i64MilliSecs);

public: // get
	I64		GetRemain();							
	I64		GetInterval()
	{ 
		return m_i64Interval;
	}
//06.11.7添加,为了支持切换地图组,慎用-----begin----------------------------------------------------
	I64		GetUpdateTime()
	{ 
		return m_i64UpdateTime;
	}
	void	SetUpdateTime(I64 time)
	{ 
		m_i64UpdateTime = time;
	}
//-----------------------------------------end------------------------------------------------------
protected:
	I64		m_i64Interval;
	I64		m_i64UpdateTime;
public:
	MYHEAP_DECLARATION(s_heap);
};

#endif // !defined(AFX_TIMEOUT_H__059AED43_D21C_4072_A172_20A7D8B6DF52__INCLUDED_)
