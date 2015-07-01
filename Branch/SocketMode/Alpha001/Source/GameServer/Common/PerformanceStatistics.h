//////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2012, WuHan ChuangYou, All Rights Reserved
// Moudle:	PerformanceStatistics.h
// Author:	������(PengWenqi)
// Create: 	2012/12/29
//		����ͳ��ģ��
//////////////////////////////////////////////////////////////////////////
#ifndef _COMMON_PERFORMANCE_STATISTICS_H_
#define _COMMON_PERFORMANCE_STATISTICS_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "./MyArray.h"
#include "./TimeOut.h"
#include "./ThreadBase.h"

const int PERFORMANCE_STATISTICS_ONTIMER_SECOND = 5;		// ÿ5�����һ������ͳ��
const int PERFORMANCE_STATISTICS_LOGSAVE_SECOND = 5 * 60;	// ÿ5���ӽ�����ͳ�Ƽ�¼��־

enum PERFORMANCE_STATISTICS_TYPE
{
	PERFORMANCE_STATISTICS_TYPE_BEGIN = 0,
	PERFORMANCE_STATISTICS_TYPE_DATABASE_TIME_SUM,							// ���ݿ������ʱ�ܺ�
	PERFORMANCE_STATISTICS_TYPE_DATABASE_TIME_COUNT,						// ���ݿ�����ƴ��ܺ�
	PERFORMANCE_STATISTICS_TYPE_DATABASE_OPEN_TIME,							// ���ݿ�򿪼�¼����ʱ�ܺ�
	PERFORMANCE_STATISTICS_TYPE_DATABASE_OPEN_COUNT,						// ���ݿ�򿪼�¼�������ܺ�
	PERFORMANCE_STATISTICS_TYPE_DATABASE_TIME_SUM_ASYNC,					// ���ݿ������ʱ�ܺ�(�첽)
	PERFORMANCE_STATISTICS_TYPE_DATABASE_TIME_COUNT_ASYNC,					// ���ݿ�����ƴ��ܺ�(�첽)

	PERFORMANCE_STATISTICS_TYPE_SOCKETTHREAD_MSGPORT_RECV_TIME_SUM,			// �����߳�OnProcessʱ, Recv�ܺ�ʱ
	PERFORMANCE_STATISTICS_TYPE_SOCKETTHREAD_ONTIMER_TIME_SUM,				// �����߳�OnProcessʱ, OnTimer�ܺ�ʱ
	PERFORMANCE_STATISTICS_TYPE_SOCKETTHREAD_ONTIMER_TIME_COUNT,			// �����߳�OnProcessʱ, OnTimer�ܴ���
	PERFORMANCE_STATISTICS_TYPE_SOCKETTHREAD_ONPROCESS_TIME_MAX,			// �����߳�OnProcessʱ, ����ʱ

	PERFORMANCE_STATISTICS_TYPE_LOGINTHREAD_MSGPORT_RECV_TIME_SUM,			// ��½�߳�OnProcessʱ, Recv�ܺ�ʱ
	PERFORMANCE_STATISTICS_TYPE_LOGINTHREAD_ONTIMER_TIME_SUM,				// ��½�߳�OnProcessʱ, OnTimer�ܺ�ʱ
	PERFORMANCE_STATISTICS_TYPE_LOGINTHREAD_ONTIMER_TIME_COUNT,				// ��½�߳�OnProcessʱ, OnTimer�ܴ���
	PERFORMANCE_STATISTICS_TYPE_LOGINTHREAD_ONPROCESS_TIME_MAX,				// ��½�߳�OnProcessʱ, ����ʱ

	PERFORMANCE_STATISTICS_TYPE_GAMETHREAD_MSGPORT_RECV_TIME_SUM,			// ��Ϸ�߳�OnProcessʱ, Recv�ܺ�ʱ
	PERFORMANCE_STATISTICS_TYPE_GAMETHREAD_ONTIMER_TIME_SUM,				// ��Ϸ�߳�OnProcessʱ, OnTimer�ܺ�ʱ
	PERFORMANCE_STATISTICS_TYPE_GAMETHREAD_ONTIMER_TIME_COUNT,				// ��Ϸ�߳�OnProcessʱ, OnTimer�ܴ���
	PERFORMANCE_STATISTICS_TYPE_GAMETHREAD_ONPROCESS_TIME_MAX,				// ��Ϸ�߳�OnProcessʱ, ����ʱ

	PERFORMANCE_STATISTICS_TYPE_RELATIONTHREAD_MSGPORT_RECV_TIME_SUM,		// ��ϵ�߳�OnProcessʱ, Recv�ܺ�ʱ
	PERFORMANCE_STATISTICS_TYPE_RELATIONTHREAD_ONTIMER_TIME_SUM,			// ��ϵ�߳�OnProcessʱ, OnTimer�ܺ�ʱ
	PERFORMANCE_STATISTICS_TYPE_RELATIONTHREAD_ONTIMER_TIME_COUNT,			// ��ϵ�߳�OnProcessʱ, OnTimer�ܴ���
	PERFORMANCE_STATISTICS_TYPE_RELATIONTHREAD_ONPROCESS_TIME_MAX,			// ��ϵ�߳�OnProcessʱ, ����ʱ

	PERFORMANCE_STATISTICS_TYPE_AITHREAD_MSGPORT_RECV_TIME_SUM,				// AI�߳�OnProcessʱ, Recv�ܺ�ʱ
	PERFORMANCE_STATISTICS_TYPE_AITHREAD_ONTIMER_TIME_SUM,					// AI�߳�OnProcessʱ, OnTimer�ܺ�ʱ
	PERFORMANCE_STATISTICS_TYPE_AITHREAD_ONTIMER_TIME_COUNT,				// AI�߳�OnProcessʱ, OnTimer�ܴ���
	PERFORMANCE_STATISTICS_TYPE_AITHREAD_ONPROCESS_TIME_MAX,				// AI�߳�OnProcessʱ, ����ʱ

	PERFORMANCE_STATISTICS_TYPE_NOW_CHOOSE_USER_AMOUNT,						// ��ǰ ѡ����� ����
	PERFORMANCE_STATISTICS_TYPE_MAX_CHOOSE_USER_AMOUNT,						// ��� ѡ����� ����
	PERFORMANCE_STATISTICS_TYPE_NOW_ENTER_USER_AMOUNT,						// ��ǰ ������� ����
	PERFORMANCE_STATISTICS_TYPE_MAX_ENTER_USER_AMOUNT,						// ��� ������� ����
	PERFORMANCE_STATISTICS_TYPE_NOW_ONLINE_USER_AMOUNT,						// ��ǰ �Ѿ����� ����
	PERFORMANCE_STATISTICS_TYPE_MAX_ONLINE_USER_AMOUNT,						// ��� �Ѿ����� ����
	PERFORMANCE_STATISTICS_TYPE_NOW_TOTAL_USER_AMOUNT,						// ��ǰ �ܹ���� ����
	PERFORMANCE_STATISTICS_TYPE_MAX_TOTAL_USER_AMOUNT,						// ��� �ܹ���� ����

	PERFORMANCE_STATISTICS_TYPE_NET_CLIENT_SEND_5SECOND,					// �����ڿͻ�������Send Byte
	PERFORMANCE_STATISTICS_TYPE_NET_CLIENT_RECV_5SECOND,					// �����ڿͻ�������Recv Byte
	PERFORMANCE_STATISTICS_TYPE_NET_CLIENT_SEND_5SECOND_MAX,				// �����ڿͻ�������Send Byte Max
	PERFORMANCE_STATISTICS_TYPE_NET_CLIENT_RECV_5SECOND_MAX,				// �����ڿͻ�������Recv Byte Max

	PERFORMANCE_STATISTICS_TYPE_CRASH_COUNT,								// ��������

	PERFORMANCE_STATISTICS_TYPE_END,
};

typedef CMyArray<I64, PERFORMANCE_STATISTICS_TYPE_END - PERFORMANCE_STATISTICS_TYPE_BEGIN>		ARR_PERFORMANCE_STATISTICS;

class CPerformanceStatistics
{
	// ����
public:
	static CPerformanceStatistics*	GetInstance(void);
	static void						DelInstance(void);
private:
	CPerformanceStatistics();
	virtual ~CPerformanceStatistics();
	static CPerformanceStatistics*	s_pInstance;


public:
	I64				GetData (PERFORMANCE_STATISTICS_TYPE eType) const;
	void			SetData	(PERFORMANCE_STATISTICS_TYPE eType, I64 i64NewData);
	void			AddData	(PERFORMANCE_STATISTICS_TYPE eType, I64 i64AddData);
	void			SetMax	(PERFORMANCE_STATISTICS_TYPE eType, I64 i64NewData);
	void			OnTimer (void);
	const char*		GetLogBuffer(void) const {return m_szLogBuffer;};


private:
	ARR_PERFORMANCE_STATISTICS		m_arrData;
	char							m_szLogBuffer[3072];
	CSimpleCriticalSection			m_csAsync;				// �߳��ٽ���
	CTimeOut						m_tmLogTimer;			// ��¼��־��ʱ��
};

// ����ͳ��������
class CPerformanceStatisticsData
{
public:
	CPerformanceStatisticsData(PERFORMANCE_STATISTICS_TYPE eType, I64 i64Data);
	~CPerformanceStatisticsData();
private:
	PERFORMANCE_STATISTICS_TYPE m_eType;
	I64 m_i64Data;
};

// ����ͳ�Ƽ�ʱ��
class CPerformanceStatisticsMS
{
public:
	CPerformanceStatisticsMS(PERFORMANCE_STATISTICS_TYPE eType, bool bMax = false);
	~CPerformanceStatisticsMS();
private:
	PERFORMANCE_STATISTICS_TYPE m_eType;
	I64 m_i64Start;
	bool m_bMax;
};

// ����ͳ�Ƽƴ���
class CPerformanceStatisticsCount
{
public:
	CPerformanceStatisticsCount(PERFORMANCE_STATISTICS_TYPE eType, I64 i64AddCount = 1, bool bMax = false);
	~CPerformanceStatisticsCount();
private:
	PERFORMANCE_STATISTICS_TYPE m_eType;
	I64 m_i64AddCount;
	bool m_bMax;
};

#endif // end of _COMMON_PERFORMANCE_STATISTICS_H_
