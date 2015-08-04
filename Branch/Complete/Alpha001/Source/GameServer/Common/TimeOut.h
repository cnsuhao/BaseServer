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
// ��ʱ�࣬�ԡ��롱Ϊ��λ
class CTimeOut
{
public:
	CTimeOut(int nIntervalSecs = 0)
	{ 
		m_nInterval = nIntervalSecs;
		m_tUpdateTime = 0;
	}		

public:
	// ����ʱ���ǩ
	void	Update		()
	{ 
		m_tUpdateTime = ::time(NULL);
	}
	// ����Ƿ�ʱ
	bool	IsTimeOut	()
	{
		bool result= ::time(NULL) >= m_tUpdateTime + m_nInterval;
		return result;
	}
	// ���ڶ�ʱ����������ʱ�ӡ�ÿ�δ���ʱΪtrue��
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
	// ��ʼ��ʱ��Ƭ��(��������)
	void	SetInterval	(int nSecs)
	{ 
		m_nInterval = nSecs;
	}

	// ��ʼ����ʱ��(ͬSetInterval)
	void	Startup		(int nSecs)
	{ 
		m_nInterval = nSecs;
		Update();
	}
	// ʱ���Ƿ񴥷�(ֻ����һ��)����Startup���ʹ�ã���ʵ��ֻ����һ�ε�ʱ�ӡ�
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

	// ����Ƿ�ʱ��ָ��ʱ��Ƭ������ͬһʱ���ǩ�������ͬ��ʱ�¼���(��ʵ��һ��������ƶ��ʱ��)
	bool	IsTimeOut	(int nSecs)
	{
		bool result=::time(NULL) >= m_tUpdateTime + nSecs;
		return result;
	}
	// ���ڱ䳤�ĳ�ʱ�¼���
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
	// ʱ���Ƿ񴥷�(ֻ����һ��)����Startup���ʹ�ã���ʵ��ֻ����һ�ε�ʱ�ӡ�
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
	// ʱ�ӻ���ۣ�������ֵ���������ֵ������ͬToNextTime(...)
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
//06.11.7���,Ϊ��֧���л���ͼ��-����----begin----------------------------------------------------
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
// ��ʱ�࣬�ԡ����롱Ϊ��λ
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
//06.11.7���,Ϊ��֧���л���ͼ��,����-----begin----------------------------------------------------
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
