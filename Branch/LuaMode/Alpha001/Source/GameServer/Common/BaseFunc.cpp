/*************************************************************************
* 修订记录
* 01 : Create New
* 02 : 2013-3-14 mengsongl : 新增函数可以从UTC秒中获取指定类型的数据
*
**************************************************************************/

#ifdef WIN32
#ifndef WINVER 
#define WINVER 0x0501
#endif  
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0501
#endif
#pragma warning(disable:4996)
#endif

#include "AFXDISP.H"//2007114:COleDateTime
#include "common.h"
#include "BaseFunc.h"
#include "./../../../Include/DbgHelp.h"
#include "PerformanceStatistics.h"

#include <afxmt.h>
#include <windows.h>
#include <mmsystem.h>
#include <winsock.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <time.h>
#include <io.h>
#include <fstream>
#include <sstream>
#include <set>

//20070627:日志开关标志位
BOOL g_bLogSave						= TRUE;		// 是否写日志
BOOL g_bLogWalk						= FALSE;	// 是否记录走路包
BOOL g_bLogDatabaseSql				= TRUE;		// 是否记录sql语句日志
BYTE g_cbEncryptKey					= 0;		// 客户端包加密key

// 全局变量保存服务器名和线路
int g_nServerStartTime = 0;
std::string g_strConstDatabaseName = "const_db";
std::string g_strGameDatabaseName = "game_db";
std::string g_strAccountDatabaseName = "acc_db";

#ifdef _WIN32
	#include <io.h>
	#if ( _MSC_VER >= 1400 )
		#define FILE_ACCESS(path,mode)		_access(path,mode)
	#else
		#define FILE_ACCESS(path,mode)		 access(path,mode)
	#endif	/* _MSC_VER >= 1400 */
#elif
	#define FILE_ACCESS(path,mode)		 access(path,mode)
};
#endif
#define FILE_EXISTS		0x00
#define EXISTENCE_ONLY	0x00

////////////////////////////////////////////////////////////////////////
// Description:  获取指定类型的数据
// Arguments:
// Return Value: DWORD
////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
DWORD TimeGet(TIME_TYPE type/* = TIME_MILLISECOND*/)
{
	DWORD dwTime = 0;
	switch(type)
	{
	case TIME_SECOND:
		dwTime = (DWORD)::time(NULL);
		break;

	case TIME_MINUTE:
		{
			time_t long_time;
			time( &long_time );                /* Get time as long integer. */

			struct tm *pTime;
			pTime = localtime( &long_time ); /* Convert to local time. */

			dwTime	=	pTime->tm_year%100*100000000 +
				(pTime->tm_mon+1)*1000000 +
				pTime->tm_mday*10000 +
				pTime->tm_hour*100 + 
				pTime->tm_min;
		}
		break;
	case TIME_HOUR:
		{
			time_t long_time;
			time( &long_time );                /* Get time as long integer. */

			struct tm *pTime;
			pTime = localtime( &long_time ); /* Convert to local time. */

			dwTime	=	pTime->tm_year%100*1000000 +
				(pTime->tm_mon+1)*10000 +
				pTime->tm_mday*100 +
				pTime->tm_hour; 
		}
		break;

	case TIME_DAY:
		{
			time_t long_time;
			time( &long_time );                /* Get time as long integer. */

			struct tm *pTime;
			pTime = localtime( &long_time ); /* Convert to local time. */

			dwTime	=	pTime->tm_year*10000 +
				(pTime->tm_mon+1)*100 +
				pTime->tm_mday;
		}
		break;

	case TIME_DAYSECOND: 
		{
			time_t long_time;
			time( &long_time );                /* Get time as long integer. */

			struct tm *pTime;
			pTime = localtime( &long_time ); /* Convert to local time. */

			dwTime	=	pTime->tm_hour*10000 + 
				pTime->tm_min *100 +
				pTime->tm_sec;
		}
		break;
	case TIME_DAYMIN: 
		{
			time_t long_time;
			time( &long_time );                /* Get time as long integer. */

			struct tm *pTime;
			pTime = localtime( &long_time ); /* Convert to local time. */

			dwTime = pTime->tm_hour*100 + pTime->tm_min;	
		}
		break;
	case TIME_DAYHOUR: 
		{
			time_t long_time;
			time( &long_time );                /* Get time as long integer. */

			struct tm *pTime;
			pTime = localtime( &long_time );  /* Convert to local time. */

			dwTime	=	pTime->tm_hour;		
		}
		break;
	case TIME_DAY_START:	// 今天的第一秒
		{
			time_t long_time = 0;
			time( &long_time );                /* Get time as long integer. */

			struct tm *pTime = NULL;
			pTime = localtime( &long_time );  /* Convert to local time. */
			pTime->tm_hour	= 0;
			pTime->tm_min	= 0;
			pTime->tm_sec	= 0;

			dwTime = ::mktime(pTime);
		}
		break;
	case TIME_DAY_END:	// 今天最后一秒
		{
			time_t long_time = 0;
			time( &long_time );                /* Get time as long integer. */

			struct tm *pTime = NULL;
			pTime = localtime( &long_time ); /* Convert to local time. */
			pTime->tm_hour	= 23;
			pTime->tm_min	= 59;
			pTime->tm_sec	= 59;

			dwTime = ::mktime(pTime);
		}
		break;
	case TIME_WEEK_DAY:		// 返回一个星期的第几天
		{
			dwTime = COleDateTime::GetCurrentTime().GetDayOfWeek() - 1;
		}
		break;
	case TIME_WEEK_START:	// 本周第一秒
		{
			dwTime = ::GetNextWeekStartUtcTime() - 7 * 24 * 60 * 60;
		}
		break;
	case TIME_WEEK_END:		// 本周最后一秒
		{
			dwTime = ::GetNextWeekStartUtcTime() - 1;
		}
		break;
	case TIME_MONTH_DAY:	// 返回月中天数1~31
		{
			dwTime=COleDateTime::GetCurrentTime().GetDay();
		}
		break;
	case TIME_MONTH_START:	// 本月第一秒
		{
			time_t long_time = 0;
			time( &long_time );                /* Get time as long integer. */

			struct tm *pTime = NULL;
			pTime = localtime( &long_time ); /* Convert to local time. */
			pTime->tm_mday	= 1;
			pTime->tm_hour	= 0;
			pTime->tm_min	= 0;
			pTime->tm_sec	= 0;

			dwTime = ::mktime(pTime);
		}
		break;
	case TIME_MONTH_END:	// 本月最后一秒
		{
			time_t long_time = 0;
			time( &long_time );                /* Get time as long integer. */

			struct tm *pTime = NULL;
			pTime = localtime( &long_time ); /* Convert to local time. */

			switch (pTime->tm_mon)
			{
			case 1:
			case 3:
			case 5:
			case 7:
			case 8:
			case 10:
			case 12:
				{
					pTime->tm_mday	= 31;
				}
				break;
			case 4:
			case 6:
			case 9:
			case 11:
				{
					pTime->tm_mday	= 30;
				}
				break;
			case 2:
				{
					int nYear = pTime->tm_year + 1900;
					if(  ((0 == nYear%4) &&(0 != nYear % 100)) ||(0 == nYear %400) )
					{
						pTime->tm_mday = 29;
					}
					else
					{
						pTime->tm_mday = 28;
					}
				}
				break;
			default:
				break;
			}

			pTime->tm_hour	= 23;
			pTime->tm_min	= 59;
			pTime->tm_sec	= 59;

			dwTime = ::mktime(pTime);
		}
		break;
	case TIME_YEAR_DAY:		// 返回年中天数
		{
			dwTime=COleDateTime::GetCurrentTime().GetDayOfYear();
		}
		break;
	case TIME_YEAR_MONTH_DAY:
		{
			time_t long_time = 0;
			time( &long_time );                /* Get time as long integer. */

			struct tm *pTime = NULL;
			pTime = localtime( &long_time ); /* Convert to local time. */

			dwTime	=	(pTime->tm_year+1900)*10000 +
				(pTime->tm_mon+1)*100 +
				pTime->tm_mday;
		}
		break;
	case TIME_STAMP: 
		{
			time_t long_time;
			time( &long_time );                /* Get time as long integer. */

			struct tm *pTime;
			pTime = localtime( &long_time ); /* Convert to local time. */

			dwTime	=	(pTime->tm_mon+1)*100000000 +
				pTime->tm_mday*1000000 +
				pTime->tm_hour*10000 + 
				pTime->tm_min *100 +
				pTime->tm_sec;
		}
		break;
	case TIME_EPOCH_DAY:	// 20070402:时间点.天数
		{
			//距离1970 1月 1日 0:00:00 的天数
			COleDateTime dt(1970,1,1,0,0,0);
			COleDateTimeSpan dts=COleDateTime::GetCurrentTime()-dt;
			dwTime = dts.GetDays();
		}
		break;
	case TIME_DAYMINISECOND:
		{
			SYSTEMTIME sysTime={0};
			::GetLocalTime(&sysTime);

			dwTime = sysTime.wDay * 100000000 + 
					 sysTime.wHour * 1000000 +
					 sysTime.wMinute * 10000 +
					 sysTime.wSecond * 100 +
					 sysTime.wMilliseconds / 10;
		}
		break;
	default:
		dwTime = ::timeGetTime();
		break;
	}

	return dwTime;
}

////////////////////////////////////////////////////////////////////////
// Description:  将TimeGet接口获得时间转换成UTC秒
// Arguments:
// Return Value: int
////////////////////////////////////////////////////////////////////////
int GetUTCSecond(int nTimeType, I64 i64Time)
{
	CHECKF(nTimeType > TIME_BEGIN && nTimeType < TIME_END);
	time_t tCurTime = ::time(NULL);
	struct tm *pTime = ::localtime(&tCurTime);
	CHECKF(pTime);
	switch (nTimeType)
	{
	case TIME_MINUTE:
		{
			pTime->tm_sec	= 0;
			pTime->tm_min	= i64Time%100;
			pTime->tm_hour	= i64Time%10000/100;
			pTime->tm_mday	= i64Time%1000000/10000;
			pTime->tm_mon	= i64Time%100000000/1000000 - 1;
			pTime->tm_year	= i64Time%10000000000/100000000 + 100;
		}
		break;
	case  TIME_HOUR:
		{
			pTime->tm_sec	= 0;
			pTime->tm_min	= 0;
			pTime->tm_hour	= i64Time%100;
			pTime->tm_mday	= i64Time%10000/100;
			pTime->tm_mon	= i64Time%1000000/10000 - 1;
			pTime->tm_year	= i64Time%100000000/1000000 + 100;
		}
		break;
	case  TIME_DAY:
		{
			pTime->tm_sec	= 0;
			pTime->tm_min	= 0;
			pTime->tm_hour	= 0;
			pTime->tm_mday	= i64Time%100;
			pTime->tm_mon	= i64Time%10000/100 - 1;
			pTime->tm_year	= i64Time/10000;
		}
		break;
	case TIME_DAYSECOND:
		{
			pTime->tm_sec	= i64Time%100;
			pTime->tm_min	= i64Time%10000/100;
			pTime->tm_hour	= i64Time/10000;
		}
		break;
	case TIME_DAY_START:	// 天的第一秒
		{
			pTime->tm_sec	= 0;
			pTime->tm_min	= 0;
			pTime->tm_hour	= 0;
			pTime->tm_mday	= i64Time%1000000/10000;
			pTime->tm_mon	= i64Time%100000000/1000000 - 1;
			pTime->tm_year	= i64Time%10000000000/100000000 + 100;
		}
		break;
	case TIME_DAY_END:		// 天的最后一秒
		{
			pTime->tm_sec	= 59;
			pTime->tm_min	= 59;
			pTime->tm_hour	= 23;
			pTime->tm_mday	= i64Time%1000000/10000;
			pTime->tm_mon	= i64Time%100000000/1000000 - 1;
			pTime->tm_year	= i64Time%10000000000/100000000 + 100;
		}
		break;
	default:
		tolog2("GetUTCSecond need process type:%d",nTimeType);
	}
	int nNeedTime = (int)::mktime(pTime);

	return nNeedTime;
}

int gettimeofday(struct timeval * val, struct timezone *)
{
	if (val)
	{
		SYSTEMTIME wtm;
		GetLocalTime(&wtm);

		struct tm tTm;
		tTm.tm_year     = wtm.wYear - 1900;
		tTm.tm_mon      = wtm.wMonth - 1;
		tTm.tm_mday     = wtm.wDay;
		tTm.tm_hour     = wtm.wHour;
		tTm.tm_min      = wtm.wMinute;
		tTm.tm_sec      = wtm.wSecond;
		tTm.tm_isdst    = -1;

		val->tv_sec     = (long)mktime(&tTm);       // time_t is 64-bit on win32
		val->tv_usec    = wtm.wMilliseconds * 1000;
	}
	return 0;
}

////////////////////////////////////////////////////////////////////////
// Description:  获取高精度utc毫秒时间
// Arguments:
// Return Value: I64
////////////////////////////////////////////////////////////////////////
I64	GetUtcMillisecond(void)
{
	struct timeval tv;     
	gettimeofday(&tv,NULL);     
	return (I64)(tv.tv_sec) * 1000 + (I64)(tv.tv_usec) / 1000;       
}

////////////////////////////////////////////////////////////////////////
// Description:  从UTC秒中获取指定类型的数据 
// Arguments:	 unSecond : UTC秒 
//				 type     : 要获取的数据类型
// Return Value: UINT
////////////////////////////////////////////////////////////////////////
UINT GetUtcTimeConvert(UINT unTimeSecond, TIME_TYPE eType)
{
	UINT unTime = 0;
	time_t tTime = unTimeSecond;
	struct tm *pTime = localtime( &tTime );
	switch(eType)
	{
	case TIME_SECOND:
		{
			unTime = pTime->tm_sec;
		}
		break;
	case TIME_MINUTE:
		{                     
			unTime = pTime->tm_min;
		}
		break;
	case TIME_HOUR:
		{
			unTime = pTime->tm_hour;
		}
		break;
	case TIME_MONTH_DAY:
		{
			unTime = pTime->tm_mday;
		}
		break;
	case TIME_WEEK_DAY:
		{
			unTime = pTime->tm_wday;
		}
		break;
	case TIME_DAY:
	case TIME_YEAR_DAY:
		{
			unTime = pTime->tm_yday;
		}
		break;
	case TIME_YEAR_MONTH_DAY:	// 获取年月日
		{
			unTime = (pTime->tm_year + 1900) * 10000 +
					 (pTime->tm_mon+1) * 100 +
					  pTime->tm_mday;
		}
		break;
	default:
		{
			tolog2("UtcSecondConvert UnKnow Type[%d]", (int)eType);
			unTime = 0;
		}
		break;
	}
	return unTime;
}

////////////////////////////////////////////////////////////////////////
// Description:  取下周一的0时0分0秒
// Arguments:
// Return Value: UINT
////////////////////////////////////////////////////////////////////////
UINT GetNextWeekStartUtcTime(void)
{
	COleDateTime tCur = COleDateTime::GetCurrentTime();
	const int DAYS_OF_WEEK = 7;
	int nCurDayOfWeek = tCur.GetDayOfWeek();	// 星期天为1 星期六为7
	int nSpanDay = 0;
	if (1 == nCurDayOfWeek)						// 如果今天是星期天
	{
		nSpanDay = 1;
	}
	else
	{
		nSpanDay = DAYS_OF_WEEK - nCurDayOfWeek + 2;
	}
	CHECKF(nSpanDay);

	COleDateTimeSpan tSpan(nSpanDay,0,0,0);
	COleDateTime tNeedTime = tCur + tSpan;
	tNeedTime.SetDateTime(tNeedTime.GetYear(), tNeedTime.GetMonth(), tNeedTime.GetDay(),0,0,0);

	time_t tNowTime = ::time(NULL);
	struct tm * pTime = ::localtime(&tNowTime);
	CHECKF(pTime);
	pTime->tm_year = tNeedTime.GetYear()%1000 + 100;
	pTime->tm_mon = tNeedTime.GetMonth() - 1;
	pTime->tm_mday = tNeedTime.GetDay();
	pTime->tm_hour = tNeedTime.GetHour();
	pTime->tm_min = tNeedTime.GetMinute();
	pTime->tm_sec = tNeedTime.GetSecond();

	int nNeedUTC = ::mktime(pTime);
	return nNeedUTC;
}

////////////////////////////////////////////////////////////////////////
// Description:  根据时间类型返回下次更新时间
// Arguments:	 unHour 时
// Return Value: UINT
////////////////////////////////////////////////////////////////////////
UINT GetNextUpdateTime(UINT unHour, TIME_TYPE type/* = TIME_SECOND*/)
{
	COleDateTimeSpan tDaySpan(1,0,0,0);
	COleDateTime tCur = COleDateTime::GetCurrentTime();
	COleDateTime tNext(tCur.GetYear(),tCur.GetMonth(),tCur.GetDay(),unHour,0,0);
	if(tCur.GetHour() >= (int)unHour)
		tNext+=tDaySpan;
	UINT unYear		= tNext.GetYear();
	UINT unMonth	= tNext.GetMonth();
	UINT unDay		= tNext.GetDay();
	UINT unHours	= tNext.GetHour();
	UINT unMinite	= tNext.GetMinute();

	UINT unNextTime = 0;
	switch (type)
	{
	case TIME_SECOND:
		{
			time_t long_time = 0;
			time( &long_time );              /* Get time as long integer. */

			struct tm *pTime = NULL;
			pTime = localtime( &long_time ); /* Convert to local time. */
			pTime->tm_yday  = unYear;
			pTime->tm_mon   = unMonth - 1;
			pTime->tm_mday	= unDay;
			pTime->tm_hour	= unHours;
			pTime->tm_min	= unMinite;
			pTime->tm_sec	= 0;

			unNextTime = ::mktime(pTime);
		}
		break;
	case TIME_MINUTE:		// 保持与TimeGet函数返回的分钟值一致
		{
			unNextTime = unYear%100 * 100000000 + unMonth * 1000000 + unDay * 10000 + unHours * 100 + unMinite;
		}
		break;
	default:
		break;
	}
	return unNextTime;
}

////////////////////////////////////////////////////////////////////////
// Description:  返回下一周的一个时间点 TIME_MINUTE 格式时间
// Arguments:	 unTimeOfDay 一个天时间如2300表示23点，如果为0则取当前时间
// Return Value: UINT
////////////////////////////////////////////////////////////////////////
UINT GetNextUpdateTimeOfWeek(UINT unTimeOfDay)
{
	CHECKF(unTimeOfDay<2400);
	COleDateTime tCur = COleDateTime::GetCurrentTime();
	COleDateTimeSpan tSpan(7,0,0,0);
	COleDateTime tNext;
	if (unTimeOfDay!=0)
	{
		tCur.SetDateTime(tCur.GetYear(),tCur.GetMonth(),tCur.GetDay(),unTimeOfDay/100,unTimeOfDay%100,0);
	}
	tNext = tCur + tSpan;
	UINT unYear = tNext.GetYear();
	UINT unMonth = tNext.GetMonth();
	UINT unDay = tNext.GetDay();
	UINT unHours = tNext.GetHour();
	UINT unMinute = tNext.GetMinute();
	UINT unNextTime = unYear%100 * 100000000 + unMonth*1000000 + unDay*10000+unHours*100+unMinute;
	
	return unNextTime;
}

////////////////////////////////////////////////////////////////////////
// Description:  获取下个月的每一天精确到日
// Arguments:	 
// Return Value: UINT (YYYYMMDD)
////////////////////////////////////////////////////////////////////////
UINT GetNextUpdateMonthDate(void)
{
	COleDateTime tCur = COleDateTime::GetCurrentTime();
	UINT nNextYear = tCur.GetYear();
	UINT nNextMonth = tCur.GetMonth() + 1;
	if (nNextMonth > 12) //是否超过了自然月
	{
		nNextYear += 1;
		nNextMonth = 1;
	}
	COleDateTime tNext = COleDateTime(nNextYear, nNextMonth, 1, 0, 0, 0);
	CHECKF(tNext.GetStatus() == COleDateTime::valid);
	UINT nNextTime = tNext.GetYear()*10000 + tNext.GetMonth()*100 + tNext.GetDay();//YYYYMMDD
	return nNextTime;
}

////////////////////////////////////////////////////////////////////////
// Description:  是否超过指定结束日期
// Arguments:	 nEndDate 结束日期(YYMMDDHHMM)
// Return Value: UINT
////////////////////////////////////////////////////////////////////////
bool IsTimeOver(UINT nEndDate)
{
	int nYear   = 2000 + nEndDate / 100000000;
	int nMounth = (nEndDate % 100000000) / 1000000;
	int nDay    = (nEndDate % 1000000) / 10000;
	int nHour   = (nEndDate % 10000) / 100;
	int nMin    = nEndDate % 100;   
	CTime timeEnd(nYear,nMounth,nDay,nHour,nMin,0);
	CTime& timeNow=CTime::GetCurrentTime();
	CTimeSpan span = timeEnd - timeNow;
	int nTotalMin = (int)span.GetTotalMinutes();
	if (nTotalMin <= 0)
		return true;
	return false;
}

////////////////////////////////////////////////////////////////////////
// Description:  获得当天一个小时数对应的UTC时间
// Arguments:	 
// Return Value: UINT
////////////////////////////////////////////////////////////////////////
int GetHourUTCSecond(int nHour)
{
	CHECKF(nHour >= 0 && nHour < 24);
	time_t curTime = ::time(NULL);
	struct tm * pTimeStruct = ::localtime(&curTime);
	CHECKF(pTimeStruct);
	pTimeStruct->tm_hour = nHour;
	pTimeStruct->tm_min = 0;
	pTimeStruct->tm_sec = 0;

	int nNeedTime = (int)::mktime(pTimeStruct);
	return nNeedTime;
}

////////////////////////////////////////////////////////////////////////
// Description:  获取指定时间（UTC时间所在天）到当前时间的间隔秒数
// Arguments:	 
// Return Value: int
////////////////////////////////////////////////////////////////////////
int GetTimeSpanFromSecond( UINT unUtcTime )
{
	struct tm *pTime;
	time_t tUTCTime = unUtcTime;
	pTime = ::localtime( &tUTCTime ); /* Convert to local time. */
	if (pTime)
	{
		pTime->tm_hour	= 0;
		pTime->tm_min	= 0;
		pTime->tm_sec	= 0;
	}

	int unDayBeginUTC	= (int)::mktime(pTime);
	int unCurTime		= ::TimeGet(TIME_SECOND);
	return unCurTime - unDayBeginUTC;
}

////////////////////////////////////////////////////////////////////////
// Description:  获取当前时间到指定时间的分钟数跨度
// Arguments:	 nDataTime 指定时间(YYMMDDHHMM)
// Return Value: UINT
////////////////////////////////////////////////////////////////////////
int GetTimeSpanToMunite(UINT nDataTime)
{
	int nYear	= nDataTime / 100000000 + 2000;
	int nMonth	= nDataTime % 100000000 / 1000000;
	int nDay	= nDataTime % 1000000 / 10000;
	int nHour	= nDataTime % 10000 / 100;
	int nMunite = nDataTime % 100;
	COleDateTime dt(nYear, nMonth, nDay, nHour, nMunite, 0);
	COleDateTimeSpan dts = COleDateTime::GetCurrentTime() - dt;
	int nTimeSpan = (int)dts.GetTotalMinutes();
	return nTimeSpan;
}

////////////////////////////////////////////////////////////////////////
// Description:  获取当前时间到指定时间的天数跨度
// Arguments:	 dwTimeDay 指定时间(YYYYMMDD)
// Return Value: UINT
////////////////////////////////////////////////////////////////////////
int GetTimeSpanToDay(DWORD dwTimeDay)
{
	CHECKF(dwTimeDay > 10000000 && dwTimeDay < 30000000);
	CTime timecount(dwTimeDay/10000,(dwTimeDay % 10000)/100,dwTimeDay % 100,0,0,0);
	CTime timeCurr = CTime::GetCurrentTime();
	CTimeSpan spanTime =timeCurr - timecount;
	int nPassDay = (int)spanTime.GetTotalHours() / 24;
	return nPassDay;
}

////////////////////////////////////////////////////////////////////////
// Description: 根据剩余时间（分钟）获取真实的时间（精确到分）
// Arguments:	nMuniteOffset 分钟数偏移量
// Return Value: UINT
////////////////////////////////////////////////////////////////////////
UINT GetTimeMinuteFromLeftMunite(int nMuniteOffset)
{
	CHECKF(nMuniteOffset > 0);
	CTime time = CTime::GetCurrentTime();
	CTimeSpan timeSpan(0, 0, nMuniteOffset, 0);
	CTime timeEnd = time + timeSpan;
	UINT unResult = (timeEnd.GetYear() - 2000) * 100000000 +
					timeEnd.GetMonth() * 1000000 +
					timeEnd.GetDay() * 10000 +
					timeEnd.GetHour() * 100 +
					timeEnd.GetMinute();
	return unResult;
}

////////////////////////////////////////////////////////////////////////
// Description:  格式化日期时间串(填入buf20中)
// Arguments:	 szFormat: "%04d-%02d-%02d %02d:%02d:%02d"
// Return Value: None
////////////////////////////////////////////////////////////////////////
void DateTime(char * buf20, time_t tInput /*= 0*/)
{
	if(!buf20)
		return;

	if(tInput == 0)	// 0 : curr time
		tInput = time(NULL);

	tm * pTm = localtime(&tInput);
	if(buf20)
		sprintf(buf20, "%04d-%02d-%02d %02d:%02d:%02d", 
		pTm->tm_year+1900, pTm->tm_mon+1, pTm->tm_mday, pTm->tm_hour, pTm->tm_min, pTm->tm_sec);
}

bool FormatDateTime(char* buf, const char* szFormat, time_t tInput /*= 0*/)
{
	if(!buf || !szFormat)
		return false;

	if(tInput == 0)
		tInput = time(NULL);

	tm * pTm = localtime(&tInput);
	sprintf(buf, szFormat, 
		pTm->tm_year+1900, pTm->tm_mon+1, pTm->tm_mday, pTm->tm_hour, pTm->tm_min, pTm->tm_sec);

	return true;
}

int DateStamp(time_t tTime/* = 0*/)
{
	time_t	tInput;
	if(tTime)
		tInput	= tTime;
	else
		tInput = time(NULL);

	tm * pTm = localtime(&tInput);
	return (pTm->tm_year+1900)	* 10000
		+ (pTm->tm_mon+1) * 100
		+ pTm->tm_mday;
}

void DateTimeStamp(char * buf15, time_t tInput/* = 0*/)
{
	if(!buf15)
		return;

	if(tInput == 0)
		tInput = time(NULL);

	tm * pTm = localtime(&tInput);
	if(buf15)
		sprintf(buf15, "%04d%02d%02d%02d%02d%02d", 
		pTm->tm_year+1900, pTm->tm_mon+1, pTm->tm_mday, pTm->tm_hour, pTm->tm_min, pTm->tm_sec);
}

////////////////////////////////////////////////////////////////////////
// Description:  时间标签nDate加上指定天数nDays
// Arguments:
// Return Value: int (-1: error)
////////////////////////////////////////////////////////////////////////
int DateStampPass(int nDate, int nDays)
{
	time_t	tCurr = time(NULL);
	tm	tmComp;
	memset(&tmComp, 0, sizeof(tm));
	tmComp.tm_year	= nDate/10000 - 1900;
	tmComp.tm_mon	= (nDate/100)%100 - 1;
	tmComp.tm_mday	= nDate%100 + nDays;

	time_t	tComp	= mktime(&tmComp);
	if(tComp == -1)
		return -1;

	return DateStamp(tComp);
}

bool IsActiveTime(time_t tCurr, unsigned long nFormat)		// DDWWHHMMSS
{
	tm* pTm = localtime(&tCurr);
	CHECKF(pTm);

	if(nFormat / 100000000)		// day per month
	{
		if(pTm->tm_mday == int(nFormat/100000000)
			&& pTm->tm_hour == int(nFormat/10000) % 100
			&& pTm->tm_min	== int(nFormat/100) % 100
			&& pTm->tm_sec	== int(nFormat % 100)
			)
			return true;
	}
	else if(nFormat / 1000000)		// day per weak
	{
		if(((pTm->tm_wday+6)%7)+1 == int(nFormat/1000000)
			&& pTm->tm_hour == int(nFormat/10000) % 100
			&& pTm->tm_min	== int(nFormat/100) % 100
			&& pTm->tm_sec	== int(nFormat % 100)
			)
			return true;
	}
	else			// time per day
	{
		if(pTm->tm_hour == int(nFormat/10000) % 100
			&& pTm->tm_min	== int(nFormat/100) % 100
			&& pTm->tm_sec	== int(nFormat % 100)
			)
			return true;
	}
	return false;
}

bool IsBetween(int nCurr, int nBegin, int nEnd)
{
	if(nBegin <= nEnd)
	{
		if(nBegin <= nCurr && nCurr < nEnd)
			return true;
	}
	else // if(nEnd < nBegin)
	{
		if(nCurr < nEnd || nBegin <= nCurr)
			return true;
	}
	return false;
}

bool IsTimeRange(unsigned long nBegin, unsigned long nEnd, time_t tCurr/*=0*/)		// DDWWHHMMSS
{
	if(tCurr == 0)
		tCurr = time(NULL);

	tm* pTm = localtime(&tCurr);
	CHECKF(pTm);

	if(nBegin / 100000000)		// per month
	{
		if(IsBetween(pTm->tm_mday*100*1000000 + pTm->tm_hour*10000 + pTm->tm_min*100 + pTm->tm_sec, nBegin, nEnd))
			return true;
	}
	else		// per weak or day ...
	{
		if(IsBetween(pTm->tm_wday*1000000 + pTm->tm_hour*10000 + pTm->tm_min*100 + pTm->tm_sec, nBegin, nEnd))
			return true;
	}
	return false;
}
//////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
// Description:  获取随机值
// Arguments:    nMax 最大值, bReset 是否重置
// Return Value: 0 <= int < nMax (-1: error)
////////////////////////////////////////////////////////////////////////
int RandGet(int nMax, bool bReset)
{
	static _int64 RandSeed = (unsigned int)TimeGet();
	if (bReset)
		RandSeed = (unsigned int)TimeGet();

	if (RandSeed < 0)
	{
		RandSeed *= (-1);
	}

	_int64 x;
	double i;
	unsigned long final;
	x = 0xffffffff;
	x += 1;

	RandSeed *= ((_int64)134775813);
	RandSeed += 1;
	RandSeed = RandSeed % x;
	i = ((double)RandSeed) / (double)x;
	final = (long) (nMax * i);

	return (int)final;
}

////////////////////////////////////////////////////////////////////////
// Description: 正态分布随机函数 取[0, nMax)的正态分布
//				随机产生μ = 0, σ = 1的标准正态分布, 
//				默认在正负3σ内取值, 其余部分按照平均概率返回RandGet(nMax)
//
// Arguments:	dRangeParam 表示取值范围, 默认3.0. 即正负3σ内取值, 
//				剩余部分均按照平均概率返回RandGet(nMax)返回, 保证正态分布图形不突兀
//				1σ包含68.268949% 概率面积
//				2σ包含95.449974% 概率面积
//				3σ包含99.730020% 概率面积
//				4σ包含99.993666% 概率面积
//				dRangeParam如果小于0.1则取值0.1
//				dRangeParam越小则中位数两边取值越平缓, 越大则陡峭, 所有正态分布均可调整此参数产生, 一般取3.0即可
//
//				数学原理为Box-Muller方法, 即:		
//				产生两个x,y随机数, 服从(0,1]平均分布, 
//				那么 (-2 * log(x))^0.5 * cos(2 * pi * y) 或 (-2 * log(x))^0.5 * sin(2 * pi * y) 均服从(0,1)正态分布
//				代码中采用cos这种方法
// 
// Author: 彭文奇(Peng Wenqi)
// Return Value: INT
////////////////////////////////////////////////////////////////////////
int	RandGetZT(int nMax, double dRangeParamL/*=3.0*/, double dRangeParamR/*=3.0*/, bool bRest/*=false*/)
{
	if (nMax < 0)
	{
		return 0;
	}

	if (dRangeParamL < 0.1)
	{
		dRangeParamL = 0.1;
	}

	if (dRangeParamR < 0.1)
	{
		dRangeParamR = 0.1;
	}

	const double dSigma			= 1.0;						// 不要修改σ, 调整范围用RangeParam
	const double dPi			= 3.1415926535897932;	
	const _int64 i64RandBase	= 0x7fffffff;				// 产生平均分布基数,

	// 让 dRandGet_X, dRandGet_Y 服从(0,1]平均分布, 因为半开半闭区间, 所以有 +1
	_int64 i64RandGet_X = RandGet(i64RandBase, bRest) + 1;
	_int64 i64RandGet_Y = RandGet(i64RandBase, false) + 1;

	double dRandGet_X = (double)i64RandGet_X / (double)i64RandBase;	
	double dRandGet_Y = (double)i64RandGet_Y / (double)i64RandBase;

	double dParam	= -2.0 * ::log(dRandGet_X);
	if (dParam < 0.0)
	{
		return 0;
	}

	double dResultZT = ::sqrt(dParam) * ::cos(2.0 * dPi * dRandGet_Y);

	// 调整中位数为3σ
	dResultZT += (dRangeParamL * dSigma);

	// 将正负3σ以外的数据进行边界处理
	if (dResultZT < 0.0 || dResultZT > (dRangeParamL + dRangeParamR) * dSigma)
	{
		return RandGet(nMax);
	}

	// 调整为0-1之间取值
	dResultZT /= ((dRangeParamL + dRangeParamR) * dSigma);

	int nResultZT = (int)(dResultZT * nMax);

	// 防止越界
	if (nResultZT < 0 || nResultZT >= nMax)
	{
		return RandGet(nMax);
	}

	return nResultZT;
}

////////////////////////////////////////////////////////////////////////
// Description:  随机范围
// Arguments:    
// Return Value: double
////////////////////////////////////////////////////////////////////////
double RandomRateGet(double dRange)
{
	double pi=3.1415926;

	int nRandom	=RandGet(999, false)+1;
	double a	=sin(nRandom*pi/1000);
	double b;
	if (nRandom >= 90)
		b	=(1.0+dRange)-sqrt(sqrt(a))*dRange;
	else
		b	=(1.0-dRange)+sqrt(sqrt(a))*dRange;

	return b;
}

////////////////////////////////////////////////////////////////////////
// Description:  double四舍五入为int
// Arguments:    
// Return Value: int
////////////////////////////////////////////////////////////////////////
int	Double2Int(double dValue)
{
	if((int)(dValue+0.5) >(int)dValue)
		return int(dValue)+1;
	else
		return int(dValue);
}

////////////////////////////////////////////////////////////////////////
// Description:  double类型保留两位小数
// Arguments:
// Return Value: double
////////////////////////////////////////////////////////////////////////
double DoubleSaveTwoDecimal(double dInput)
{
	I64 i64Vaule =  (I64)(100i64 * dInput);
	double dResult = i64Vaule / 100.0;
	return dResult;
}

////////////////////////////////////////////////////////////////////////
// Description:  获取二进制中的1的个数
// Arguments:    
// Return Value: int
////////////////////////////////////////////////////////////////////////
int bit_count(int n)
{
	int nCount = 0;
	for (int i = 0; i < 32; i++)
	{
		if ((n & (1<<i)) != 0)
			nCount++;
	}
	return nCount;
}

////////////////////////////////////////////////////////////////////////
// Description:  获取二进制中的1的个数
// Arguments:    I64Data 64位数值， nEndIndex检测的索引数
// Return Value: int
////////////////////////////////////////////////////////////////////////
int bit_i64_count(I64 i64Data, int nEndIndex/* = 64*/)
{
	int nCount = 0;
	for (int i = 0; i < nEndIndex; i++)
	{
		if ((i64Data & (1i64 << i)) != 0)
		{
			nCount++;
		}
	}
	return nCount;
}

////////////////////////////////////////////////////////////////////////
// Description:  获得2的幂指数，取整
// Arguments:
// Return Value: int
////////////////////////////////////////////////////////////////////////
UINT GetLog2(UINT nNum)
{
	CHECKF(nNum);
	UINT i=0;
	for (i = 0; i < 32; ++i)
	{
		nNum = nNum >> 1;
		if (nNum<=0)
		{
			break;
		}
	}

	return i;
}
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
String	DumpBuffer(const char* buf, int nSize)
{
	IF_NOT(buf && nSize > 0 && nSize <= 256)
		return String();

	String str;
	for(int i = 0; i < nSize; i++)
	{
		char bufChar[255];
		sprintf(bufChar, "%02x", (*(buf++) & 0xFF));
		str	+= bufChar;
		if((i % 16) == 15 && i != nSize-1)
			str += ' ';
		else if((i % 4) == 3 && i != nSize-1)
			str	+= '-';
	}
	return str;
}

char*	StrStrCh(const char* string, const char* strCharSet)
{
	CHECKF(string && strCharSet);
	unsigned int	nLen	= strlen(strCharSet);
	if(nLen == 0 || strlen(string) < nLen)
		return NULL;

	char	head	= *strCharSet;
	const char* ptr = string;
	while(*ptr)
	{
		while(*ptr && *ptr != head)
		{
			unsigned char uch = static_cast<unsigned char>(*ptr);
			if(uch >= 0x81 && uch <= 0xFE && *(ptr+1))
				ptr++;
			ptr++;
		}
		if(*ptr && strncmp(ptr, strCharSet, nLen) == 0)
			return const_cast<char*>(ptr);
		ptr++;
	}

	return NULL;
}

BOOL StringCheck(const char* pszString, BOOL bNewLineEnable)
{
	return true;

	if (!pszString)
		return false;

	int nLen	=strlen(pszString);
	for (int i=0; i < nLen; i++)

	{
		unsigned char c	=(unsigned char)pszString[i];
		if (c >= 0x81 && c <= 0xfe)	
		{
			if (i+1 >= nLen)
				return false;

			unsigned char c2	=(unsigned char)pszString[i+1];
			if (c2 < 0x40 && c2 > 0x7e && c2 < 0x80 && c2 > 0xfe)
				return false;
			else
				i++;
		}
		else
		{
			if (c==0x80)
				return false;
			else
			{
				if(bNewLineEnable)
				{
					if (c < ' ' && c != 0x0A && c != 0x0D)
						return false;
				}
				else
				{
					if (c < ' ')
						return false;
				}
			}
		}
	}

	return true;
}

////////////////////////////////////////////////////////////////////////
// Description:  检查聊天字符串
// Arguments:
// Return Value: bool
////////////////////////////////////////////////////////////////////////
BOOL TalkStrCheck(char* pszString, BOOL bNewLineEnable)
{
	return true;
	if (!pszString)
		return false;

	int nLen	=strlen(pszString);
	for (int i=0; i < nLen; i++)
	{
		unsigned char c	=pszString[i];
		if(c < ' ' && c != 0x0d && c != 0x0a)
			return false;
		switch(c)
		{
		case '\\':
			//case '\''://20090511haocq单双引号不过虑
			//case '"':
			return false;
		}
	}

	return ::DisableWordCheck(pszString, bNewLineEnable);
}

BOOL DisableWordCheck(const char* pszString, BOOL bNewLineEnable)
{
	if (strstr(pszString, "fuck"))
		return false;

	if (strstr(pszString, "FUCK"))
		return false;
	return ::StringCheck(pszString, bNewLineEnable);
}

////////////////////////////////////////////////////////////////////////
// Description:  检查字符串是否包含sql语句
// Arguments:
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool StrSqlCheck(const char* pszString)
{
	if (!pszString)
		return false;

	wchar_t wszTempStr[2048];
	ZeroMemory(wszTempStr, sizeof(wszTempStr));
	::MyUTF8ToUnicode(pszString, wszTempStr, sizeof(wszTempStr) / sizeof(wchar_t));

	int nLen = wcslen(wszTempStr);
	wchar_t c = L'\0';
	for (int i=0; i < nLen; i++)
	{
		c = wszTempStr[i];
		if(c < L' ')
			return false;
		switch(c)
		{
			// 		case L'	'://tab
			// 		case L' ':
		case L';':
		case L',':
		case L'/':
		case L'\\':
		case L'=':
		case L'%':
		case L'@':
		case L'\'':
		case L'"':
		case L'[':
		case L']':
		case L'#':
		case L'?':
		case L'*':
		case L'!':
		case L'<':
		case L'>':
			return false;
		}
	}

	return true;
}

////////////////////////////////////////////////////////////////////////
// Description:  检查名字字符串
// Arguments:
// Return Value: bool
////////////////////////////////////////////////////////////////////////
BOOL NameStrCheck(const char* pszString)
{
	if (!pszString)
		return false;

	if (0 == strlen(pszString))
		return false;

	if (!StrSqlCheck(pszString))
		return false;

	if (strstr(pszString, "　"))
		return false;

	if (strstr(pszString, "GM"))
		return false;

	if (strstr(pszString, "gm"))
		return false;

	if (strstr(pszString, "PM"))
		return false;

	if (strstr(pszString, "pm"))
		return false;

	if (strstr(pszString, "SYSTEM"))
		return false;

	if (strstr(pszString, "system"))
		return false;

	if (strstr(pszString, "NPC"))
		return false;

	if (strstr(pszString, "npc"))
		return false;

	return ::DisableWordCheck(pszString);
}

////////////////////////////////////////////////////////////////////////
// Description:  转换字符串从Ansi到Unicode编码
// Arguments:	 从OUT参数传出, 返回值表示转换是否成功
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool MyANSIToUnicode(IN const char* pszStr, OUT wchar_t* pwszStr, int nUnicodeStrSize)
{
	CHECKF(pszStr && pwszStr && nUnicodeStrSize > 0);
	const int nUnicodeNeedLen = ::MultiByteToWideChar(CP_ACP, 0, pszStr, -1, NULL, 0);
	CHECKF(nUnicodeNeedLen < nUnicodeStrSize);
	ZeroMemory(pwszStr, nUnicodeStrSize);
	::MultiByteToWideChar(CP_ACP, 0, pszStr, -1, pwszStr, nUnicodeNeedLen);  
	return  true;  
}

////////////////////////////////////////////////////////////////////////
// Description:  转换字符串 从Unicode到Ansi编码
// Arguments:
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool MyUnicodeToANSI(IN const wchar_t* pwszStr, OUT char* pszStr, int nAnsiStrSize)
{
	CHECKF(pszStr && pwszStr && nAnsiStrSize > 0);	
	const int nAnsiNeedLen = ::WideCharToMultiByte(CP_ACP, 0, pwszStr, -1, NULL, 0, NULL, NULL);
	CHECKF(nAnsiNeedLen < nAnsiStrSize);
	ZeroMemory(pszStr, nAnsiStrSize);
	::WideCharToMultiByte(CP_ACP, 0, pwszStr, -1, pszStr, nAnsiNeedLen, NULL, NULL);
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description:  转换字符串 从Unicode到UTF8
// Arguments:
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool MyUnicodeToUTF8(IN const wchar_t* pwszStr, OUT char* pszStr, int nUtf8StrSize)
{
	CHECKF(pwszStr && pszStr && nUtf8StrSize > 0);
	const int nNeedLen = ::WideCharToMultiByte(CP_UTF8, NULL, pwszStr, wcslen(pwszStr), NULL, 0, NULL, NULL);
	CHECKF(nNeedLen < nUtf8StrSize);
	ZeroMemory(pszStr, nUtf8StrSize);
	::WideCharToMultiByte(CP_UTF8, NULL, pwszStr, wcslen(pwszStr), pszStr, nNeedLen, NULL, NULL);
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description:  转换字符串 从UTF8到Unicode
// Arguments:
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool MyUTF8ToUnicode(IN const char* pszStr, OUT wchar_t* pwszStr, int nUnicodeStrSize)
{
	CHECKF(pszStr && pwszStr && nUnicodeStrSize > 0);
	const int nNeedLen = ::MultiByteToWideChar(CP_UTF8, NULL, pszStr, strlen(pszStr), NULL, 0);
	CHECKF(nNeedLen < nUnicodeStrSize);
	ZeroMemory(pwszStr, nUnicodeStrSize);
	::MultiByteToWideChar(CP_UTF8, NULL, pszStr, strlen(pszStr), pwszStr, nUnicodeStrSize);
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description:  转换字符串 从UTF8到Ansi编码
// Arguments:
// Return Value: bool
////////////////////////////////////////////////////////////////////////
CMxyString MyUtf8ToANSI( const char* pszString )
{
	CMxyString strResult = "";
	wchar_t wszTempStr[8192];
	char	szAnsiStr[8192];
	if (::MyUTF8ToUnicode(pszString, wszTempStr, sizeof(wszTempStr) / sizeof(wchar_t)) && 
		::MyUnicodeToANSI(wszTempStr, szAnsiStr, sizeof(szAnsiStr) / sizeof(szAnsiStr[0])))
	{
		strResult = szAnsiStr;
	}
	return strResult;
}

////////////////////////////////////////////////////////////////////////
// Description:  转换字符串 从Ansi到UTF8编码
// Arguments:
// Return Value: bool
////////////////////////////////////////////////////////////////////////
CMxyString MyANSIToUtf8( const char* pszString )
{
	CMxyString strResult = "";
	wchar_t wszTempStr[8192];
	char	szAnsiStr[8192];
	if (::MyANSIToUnicode(pszString, wszTempStr, sizeof(wszTempStr) / sizeof(wchar_t)) && 
		::MyUnicodeToUTF8(wszTempStr, szAnsiStr, sizeof(szAnsiStr) / sizeof(szAnsiStr[0])))
	{
		strResult = szAnsiStr;
	}
	return strResult;
}

////////////////////////////////////////////////////////////////////////
// Description:  安全拷贝字符串
// Arguments:
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool	SafeCopy(char * pTarget, const char * pSource, int nBufLen /*= 0*/)
{
	DEBUG_TRY;
	if (pTarget == pSource)
	{
		return true;
	}

	if(pTarget)
	{
		pTarget[0] = 0;
		if(pSource)
		{
			if(nBufLen && (int)strlen(pSource) >= nBufLen)
			{
				strncpy(pTarget, pSource, nBufLen-1);
				pTarget[nBufLen-1] = 0;
				return false;
			}
			strcpy(pTarget, pSource);
			return true;
		}
	}
	DEBUG_CATCH("CATCH: *** SafeCopy() crash! ***\n");
	return false;
}

////////////////////////////////////////////////////////////////////////
// Description:  替换std::string中的字符
// Arguments:
// Return Value: bool
////////////////////////////////////////////////////////////////////////
int ReplaceStdString(IN OUT string& str, const char* pszOld, const char* pszNew, bool bReplaceAll/* = true*/)
{
	CHECKF(pszOld && ::strlen(pszOld) > 0);
	CHECKF(pszNew && ::strlen(pszNew) > 0);
	if (str.empty())
	{
		return 0;
	}

	std::string::size_type unOldSize = ::strlen(pszOld);
	std::string::size_type unNewSize = ::strlen(pszNew);

	int nReplaceCount = 0;
	std::string::size_type unPos = 0;
	while ((unPos = str.find(pszOld, unPos)) != str.npos)
	{
		nReplaceCount++;
		str.replace(unPos, unOldSize, pszNew);
		unPos += unNewSize;
		if (!bReplaceAll)
		{
			break;
		}
	}

	return nReplaceCount;
}
//////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
// Description: 判断文件存在性
// Arguments:
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool IsExistFile( const char* pszFileName )
{
	CHECKF(pszFileName);
	if (FILE_EXISTS == FILE_ACCESS(pszFileName, EXISTENCE_ONLY))
	{
		return true;
	}
	return false;
}


////////////////////////////////////////////////////////////////////////
// Description:  把文件读到string返回
// Arguments:
// Return Value: std::string
////////////////////////////////////////////////////////////////////////
std::string LoadFileToString(const std::string& strFileName)
{
	std::ostringstream buf;
	std::ifstream inFile(strFileName.c_str(), std::ios::in);
	char ch;
	int nCount = 0;
	while(buf && inFile.get(ch))
	{
		if (nCount < 3)
		{
			if (SZ_UTF8_FILE_HEADER[nCount++] == ch)
			{
				continue;
			}
		}
		buf.put(ch);
	}
	inFile.close();
	return buf.str();
}

////////////////////////////////////////////////////////////////////////
// Description:  计算数轴上两个线段的交集数量(线段为开区间)
// Arguments:
// Return Value: int
////////////////////////////////////////////////////////////////////////
int CalcNumberAxisIntersection(int x1, int y1, int x2, int y2)
{
	// 保证每个线段的x比y小
	if (x1 > y1)
		swap(x1, y1);
	if (x2 > y2)
		swap(x2, y2);

	// 保证线段1的起始值比线段2小
	if (x1 > x2)
	{
		swap(x1, x2);
		swap(y1, y2);
	}

	if		(y1 <= x2)	// 无交集情况
		return 0;
	else if (y1 >= y2)	// 线段2被包含
		return y2 - x2;
	else if (y1 >= x2)	// 两个线段交叉
		return y1 - x2;

	return -1;
}

void DDALineEx(int x0, int y0, int x1, int y1, vector<POINT>& vctPoint)
{
	vctPoint.clear();
	if (x0 == x1 && y0 == y1)
		return;

	int dx = x1 - x0;
	int dy = y1 - y0;
	int abs_dx = abs(dx);
	int abs_dy = abs(dy);
	if(abs_dx > abs_dy)
	{
		int _0_5		= abs_dx * (dy>0 ? 1:-1);
		int numerator	= dy * 2;
		int denominator	= abs_dx * 2;
		// x 增益
		if(dx > 0)
		{
			// x0 ++
			for(int i = 1; i <= abs_dx; i ++)
			{
				POINT point;
				point.x = x0 + i;
				point.y = y0 + ((numerator*i + _0_5) / denominator);
				vctPoint.push_back(point);
			}
		}
		else if(dx < 0)
		{
			// x0 --
			for(int i = 1; i <= abs_dx; i ++)
			{
				POINT point;
				point.x = x0 - i;
				point.y = y0 + ((numerator*i + _0_5) / denominator);
				vctPoint.push_back(point);
			}
		}
	}
	else
	{
		int _0_5		= abs_dy * (dx>0 ? 1:-1);
		int numerator	= dx * 2;
		int denominator	= abs_dy * 2;
		// y 增益
		if(dy > 0)
		{
			// y0 ++
			for(int i = 1; i <= abs_dy; i ++)
			{
				POINT point;
				point.y = y0 + i;
				point.x = x0 + ((numerator*i + _0_5) / denominator);
				int nAmount = vctPoint.size();
				vctPoint.push_back(point);
			}
		}
		else if(dy < 0)
		{
			// y0 -- 
			for(int i = 1; i <= abs_dy; i ++)
			{
				POINT point;
				point.y = y0 - i;
				point.x = x0 + ((numerator*i + _0_5) / denominator);
				vctPoint.push_back(point);
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////
// Description:  进制转换(如6进制转换 nConvNum = 6, nTrainPoint = 7 返回值为11.)
// Arguments:	 nTrainPoint 要转换的数值， nConvNum 要转换的进制(2~9)
// Return Value: int
////////////////////////////////////////////////////////////////////////
int NumConversion(int nTrainPoint,int nConvNum)
{
	if(nConvNum<=1 || nConvNum >= 10)
	{
		LOGWARNING("NumConversion()nConvNum[%d], overflow! return 0",nConvNum);
		return 0;
	}

	const int _conversion_num = nConvNum;	// n进制转换

	int nResult = 0;
	for(int i = 0;							// 计位数
		nTrainPoint && i < 9;				// 最高不超过9位
		i++)
	{
		nResult += (int)(pow(10.0, i) * (nTrainPoint % _conversion_num));
		nTrainPoint = nTrainPoint/_conversion_num;
	}
	return nResult;
}

////////////////////////////////////////////////////////////////////////
// Description: 验证认证ID, true通过, false失败
// Arguments:
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool IsRightAuthenID(DWORD dwAuthenID, DWORD dwAccount)
{
	CHECKF(dwAuthenID);
	CHECKF(dwAccount);
	dwAuthenID ^= dwAccount;

	const DWORD AUTHEN_ID_COUNT_KEY[3] = { 0x1c32194, 0x2f9fc2, 0x92d4d5 };
	const DWORD AUTHEN_ID_MOD_KEY = 2749;
	DWORD dwMinute = dwAuthenID / 100;
	DWORD dwResult = dwAuthenID % 100;
	DWORD dwRightResult = 0;
	if (0 == dwMinute % 2)
		dwRightResult = ((dwMinute + AUTHEN_ID_COUNT_KEY[0]) ^ AUTHEN_ID_COUNT_KEY[1]) % AUTHEN_ID_MOD_KEY % 100;
	else
		dwRightResult = ((dwMinute + AUTHEN_ID_COUNT_KEY[1]) ^ AUTHEN_ID_COUNT_KEY[2]) % AUTHEN_ID_MOD_KEY % 100;

	// 验证码验算
	if (dwRightResult != dwResult)
	{
		return false;
	}

	// 调试版本不验证时间
#ifdef MYDEBUG
	return true;
#endif

	// 有效期2分钟
	DWORD dwNowMinute = (DWORD)::time(NULL) / 60;
	if (dwNowMinute > dwMinute + 2)
	{
		return false;
	}

	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: 获取本机IP
// Arguments:
// Return Value: std::string
////////////////////////////////////////////////////////////////////////
std::string GetLocalIpAddr()
{
	const int MAX_HOST_NAME_LEN = 256;	// 主机名最大长度
	char acHostname[MAX_HOST_NAME_LEN] = {0};
	struct hostent* pstHostent;
	struct hostent  stTmpHostent;
	struct sockaddr_in stTmpSockAddrIn;

	std::string tmpLocalIP = "?.?.?.?";

	int nAdapter = 0;
	int iRetVal = gethostname(acHostname, sizeof(acHostname));
	if (iRetVal != 0)
	{
		return tmpLocalIP;
	}

	pstHostent = gethostbyname(acHostname);
	if (pstHostent == NULL) 
	{
		return tmpLocalIP;
	}

	stTmpHostent = *pstHostent;

	if(stTmpHostent.h_addr_list[nAdapter] == NULL)
	{
		return tmpLocalIP;
	}

	memcpy ( &stTmpSockAddrIn.sin_addr.s_addr, stTmpHostent.h_addr_list[nAdapter],stTmpHostent.h_length);
	tmpLocalIP = inet_ntoa(stTmpSockAddrIn.sin_addr);

	return tmpLocalIP;
}

////////////////////////////////////////////////////////////////////////
// Description: 打印dump
// Arguments:
// Return Value: std::string
////////////////////////////////////////////////////////////////////////
LONG WINAPI MyUnhandledExceptionFilter(struct _EXCEPTION_POINTERS* ExceptionInfo)
{
	CHECKF(ExceptionInfo);
	MINIDUMP_EXCEPTION_INFORMATION ExInfo;
	ExInfo.ThreadId = ::GetCurrentThreadId();
	ExInfo.ExceptionPointers = ExceptionInfo;
	ExInfo.ClientPointers = TRUE;

	COleDateTime dt=COleDateTime::GetCurrentTime();
	CString strDumpFileName;
	CString temp=dt.Format("%Y年%m月%d日%H时%M分%S秒");
	strDumpFileName.Format("./dump/%s_%lu.dmp", temp, ::GetTickCount());

	::CreateDirectory("dump", NULL);
	HANDLE lhDumpFile = CreateFile(strDumpFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL ,NULL);
	if (NULL != lhDumpFile)
	{
		MiniDumpWriteDump( GetCurrentProcess(), GetCurrentProcessId(), lhDumpFile, MiniDumpNormal/*MiniDumpWithFullMemory*/, &ExInfo, NULL, NULL);		// 备选项:MiniDumpNormal  不打印内存, 小很多
		CloseHandle(lhDumpFile);
	}

	return EXCEPTION_EXECUTE_HANDLER;
}

////////////////////////////////////////////////////////////////////////
// Description:  加权随机数生成
// Arguments:
// Return Value: void
////////////////////////////////////////////////////////////////////////
void GenWeightRandomVector(const VEC_WEIGHTED_VALUE& rInputVec, OUT VEC_WEIGHT_OUTPUT& rOutputVec, int nCount/* = 1*/)
{
	CHECK(nCount >= 1);
	CHECK(rInputVec.size() > 0);
	rOutputVec.clear();

	// 生成的个数比输入多, 直接返回
	if (nCount >= rInputVec.size())
	{
		for (CITER_WEIGHTED_VALUE iter = rInputVec.begin(); iter != rInputVec.end(); ++iter)
		{
			rOutputVec.push_back(iter->nValue);
		}
		return;
	}

	VEC_WEIGHTED_VALUE vecSrc = rInputVec;

	// 循环生成结果集
	for (int i = 0; i < nCount; i++)
	{
		// 计算本次总权重
		int nTotalWeight = 0;
		for (CITER_WEIGHTED_VALUE iter = vecSrc.begin(); iter != vecSrc.end(); ++iter)
		{
			nTotalWeight += iter->nWeight;
		}
		CHECK(nTotalWeight <= 100000000);


		int nRandomWeight = ::RandGet(nTotalWeight);	// 随机出命中的权重值
		int nNowWeight = 0;								// 当前循环权重求和
		for (ITER_WEIGHTED_VALUE iter = vecSrc.begin(); iter != vecSrc.end(); ++iter)
		{
			int nThisWeight = iter->nWeight;	// 本次权重
			if (nRandomWeight >= nNowWeight && nRandomWeight < nNowWeight + nThisWeight)
			{
				rOutputVec.push_back(iter->nValue);
				vecSrc.erase(iter);
				break;
			}
			else
			{
				nNowWeight += nThisWeight;
			}
		}
	}
}
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
CTimeCostChk::CTimeCostChk(const char* pszReason,const char* pszString, I64 i64CheckMS, const char* pszFileName, int nFileLine) 
{
	m_i64BeginMS	= ::GetUtcMillisecond();
	m_i64CheckMS	= i64CheckMS;
	if (pszReason)
	{
		m_strReason =pszReason;
	}
	else
	{
		m_strReason = "";
	}

	if (pszString)
	{
		m_strString	= pszString;
	}
	else
	{
		m_strString = "";
	}

	if (pszFileName)
	{
		m_strFileName = pszFileName;
	}
	else
	{
		m_strFileName = "";
	}

	m_nFileLine = nFileLine;
}

CTimeCostChk::~CTimeCostChk()
{
	I64 i64UsedMS = ::GetUtcMillisecond() - m_i64BeginMS;
	if (i64UsedMS > m_i64CheckMS)
	{
		::LogTimeOut("%s(%d):CTimeCostChk Overtime (%I64dms>%I64dms) when szReason:%s chk:%s", 
			m_strFileName.c_str(), m_nFileLine, i64UsedMS, m_i64CheckMS, m_strReason.c_str(), m_strString.c_str()); 
	}
}
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
CTimeUseMSLog::CTimeUseMSLog(const char* pszReason, const char* pszFileName, int nFileLine)
{
	m_i64BeginMS	= ::GetUtcMillisecond();
	if (pszReason)
	{
		m_strReason = pszReason;
	}
	else
	{
		m_strReason = "";
	}

	if (pszFileName)
	{
		m_strFileName = pszFileName;
	}
	else
	{
		m_strFileName = "";
	}

	m_nFileLine = nFileLine;
}

CTimeUseMSLog::~CTimeUseMSLog()
{
	I64 i64UsedMS = ::GetUtcMillisecond() - m_i64BeginMS;
	::LogSave("%s(%d):TimeUseLog Reason[%s], Used[%I64d]MS", m_strFileName.c_str(), m_nFileLine, m_strReason.c_str(), i64UsedMS);
}
//////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
// Description:  判断是不是浮点0
// Arguments:
// Return Value: bool
////////////////////////////////////////////////////////////////////////
inline bool gbase::IsDoubleZero(double dParam)
{
	return dParam < 0.0001 && dParam > -0.0001;
}

////////////////////////////////////////////////////////////////////////
// Description:  获得两点间的距离
// Arguments:
// Return Value: double
////////////////////////////////////////////////////////////////////////
double gbase::GetDistance(const gbase::ST_POINT& rPoint1, const gbase::ST_POINT& rPoint2)
{
	int nDisX = rPoint1.nX - rPoint2.nX;
	int nDisY = rPoint1.nY - rPoint2.nY;
	return ::sqrt((double)(nDisX * nDisX + nDisY * nDisY));
}

////////////////////////////////////////////////////////////////////////
// Description:  点是否在线段上
// Arguments:	 算法: AB线段，C为点，只要AC+BC的长度等于AB的长度就是在线段上
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool gbase::IsPointOnLine(const gbase::ST_POINT& rPoint, const gbase::ST_LINE& rLine)
{
	double dDistance = gbase::GetDistance(rPoint, rLine.stPoint[0]) + gbase::GetDistance(rPoint, rLine.stPoint[1]) - gbase::GetDistance(rLine.stPoint[0], rLine.stPoint[1]);
	return gbase::IsDoubleZero(dDistance);
}

////////////////////////////////////////////////////////////////////////
// Description:  获得行列式的值
// Arguments:
// Return Value: double
////////////////////////////////////////////////////////////////////////
inline double gbase::GetDeterminant(double v1, double v2, double v3, double v4)
{
	return (v1*v3-v2*v4);  
}

////////////////////////////////////////////////////////////////////////
// Description:  线段是否相交
// Arguments:	 行列式解法 算法证明: http://dec3.jlu.edu.cn/webcourse/t000096/graphics/chapter5/01_1.html
//				 由于环境需要, 若线段一点与在另一线段上, 也认为线段相交
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool gbase::IsLineOverlapping(const gbase::ST_LINE& rLine1, const gbase::ST_LINE& rLine2)
{
	// 有一点重合确认相交
	if (gbase::IsPointOnLine(rLine1.stPoint[0], rLine2) || 
		gbase::IsPointOnLine(rLine1.stPoint[1], rLine2) ||
		gbase::IsPointOnLine(rLine2.stPoint[0], rLine1) || 
		gbase::IsPointOnLine(rLine2.stPoint[1], rLine1) )
	{
		return true;
	}

	double dDelta = gbase::GetDeterminant(
		rLine1.stPoint[1].nX - rLine1.stPoint[0].nX, 
		rLine2.stPoint[0].nX - rLine2.stPoint[1].nX, 
		rLine1.stPoint[1].nY - rLine1.stPoint[0].nY, 
		rLine2.stPoint[0].nY - rLine2.stPoint[1].nY); 

	// delta=0，表示两线段重合或平行 
	if (gbase::IsDoubleZero(dDelta))
	{
		return false;
	}

	// 求λ
	double dLamda = gbase::GetDeterminant(
		rLine2.stPoint[0].nX - rLine1.stPoint[0].nX, 
		rLine2.stPoint[0].nX - rLine2.stPoint[1].nX, 
		rLine2.stPoint[0].nY - rLine1.stPoint[0].nY, 
		rLine2.stPoint[0].nY - rLine2.stPoint[1].nY) / dDelta;  
	if ( dLamda>=1 || dLamda<=0 )  
	{  
		return false;  
	}  

	// 求μ
	double dMu = gbase::GetDeterminant(
		rLine1.stPoint[1].nX - rLine1.stPoint[0].nX, 
		rLine2.stPoint[0].nX - rLine1.stPoint[0].nX, 
		rLine1.stPoint[1].nY - rLine1.stPoint[0].nY, 
		rLine2.stPoint[0].nY - rLine1.stPoint[0].nY) / dDelta;  
	if ( dMu>=1 || dMu<=0 )  
	{  
		return false;  
	}  

	return true;  
}

////////////////////////////////////////////////////////////////////////
// Description:  点是否在三角形内
// Arguments:	 射线法函数调用
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool gbase::IsPointInTriangle(const gbase::ST_POINT& rPoint, const gbase::ST_TRIANGLE& rTriangle)
{
	return gbase::IsInPolygon(rTriangle.stVertex, 3, rPoint);
}

////////////////////////////////////////////////////////////////////////
// Description:  是否在多边形内
// Arguments:	 射线法
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool gbase::IsInPolygon(const gbase::ST_POINT arr[], size_t len, const gbase::ST_POINT& p)
{
	size_t count = 0;
	const double x = p.nX, y = p.nY;
	gbase::ST_POINT a = arr[len - 1];
	for (const gbase::ST_POINT* b = arr; b < arr + len;  a = *b++) 
	{
		if ((a.nY < y) == (b->nY < y)) 
		{
			if (a.nY == b->nY && y == a.nY &&
				((a.nX >= x && b->nX <= x) || (a.nX <= x && b->nX >= x))) 
			{
				return true;
			}
		} 
		else 
		{
			//水平线PP与线段ab的交点，该交点与点p间的水平相对位置
			double delta = (y - a.nY) * (b->nX - a.nX) / (b->nY - a.nY) + a.nX - x;
			if (delta >= 0.0001)  
			{
				++count;   //水平射线PP与线段相交
			}
			else if (delta > -0.0001) 
			{
				return true;  //点p在线段ab上
			}
		}
	}
	return count & 1;
}

////////////////////////////////////////////////////////////////////////
// Description:  点是否在正方形内
// Arguments:
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool gbase::IsPointInSquare(const gbase::ST_POINT& rPoint, const gbase::ST_SQUARE& rSquare)
{
	if (rPoint.nX >= rSquare.stVertex.nX &&
		rPoint.nY >= rSquare.stVertex.nY &&
		rPoint.nX <= rSquare.stVertex.nX + rSquare.nLength &&
		rPoint.nY <= rSquare.stVertex.nY + rSquare.nLength)
	{
		return true;
	}

	return false;
}

////////////////////////////////////////////////////////////////////////
// Description: 判断点是否在矩形内
// Arguments:
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool gbase::IsPointInRectangle( const ST_POINT& rPoint, const ST_RECTANGLE& rRectangle )
{
	return gbase::IsInPolygon(rRectangle.stVertex, 4, rPoint);
}

////////////////////////////////////////////////////////////////////////
// Description:  三角形和正方形是否相交
// Arguments:	 优先快排除, 互相有点包含直接返回true, 再进行3*4条线段相交测试
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool gbase::IsTriangleSquareOverlapping(const gbase::ST_TRIANGLE& rTriangle, const gbase::ST_SQUARE& rSquare)
{
	// 快速排除法
	gbase::ST_POINT stSquareOtherVertex[3];
	stSquareOtherVertex[0] = rSquare.stVertex;
	stSquareOtherVertex[1] = rSquare.stVertex;
	stSquareOtherVertex[2] = rSquare.stVertex;
	stSquareOtherVertex[0].nX += rSquare.nLength;
	stSquareOtherVertex[1].nY += rSquare.nLength;
	stSquareOtherVertex[2].nX += rSquare.nLength;
	stSquareOtherVertex[2].nY += rSquare.nLength;

	if (gbase::IsPointInSquare(rTriangle.stVertex[0], rSquare) ||
		gbase::IsPointInSquare(rTriangle.stVertex[1], rSquare) ||
		gbase::IsPointInSquare(rTriangle.stVertex[2], rSquare) ||
		gbase::IsPointInTriangle(rSquare.stVertex, rTriangle) ||
		gbase::IsPointInTriangle(stSquareOtherVertex[0], rTriangle) ||
		gbase::IsPointInTriangle(stSquareOtherVertex[1], rTriangle) ||
		gbase::IsPointInTriangle(stSquareOtherVertex[2], rTriangle) )
	{
		return true;
	}

	// 生成线段组
	gbase::ST_LINE stTriangleLine[3];
	stTriangleLine[0].stPoint[0] = rTriangle.stVertex[0];
	stTriangleLine[0].stPoint[1] = rTriangle.stVertex[1];

	stTriangleLine[1].stPoint[0] = rTriangle.stVertex[1];
	stTriangleLine[1].stPoint[1] = rTriangle.stVertex[2];

	stTriangleLine[2].stPoint[0] = rTriangle.stVertex[2];
	stTriangleLine[2].stPoint[1] = rTriangle.stVertex[0];

	gbase::ST_LINE stSquareLine[4];
	stSquareLine[0].stPoint[0] = rSquare.stVertex;
	stSquareLine[0].stPoint[1] = rSquare.stVertex;	stSquareLine[0].stPoint[1].nX += rSquare.nLength;

	stSquareLine[1].stPoint[0] = rSquare.stVertex;	stSquareLine[1].stPoint[0].nX += rSquare.nLength;
	stSquareLine[1].stPoint[1] = rSquare.stVertex;	stSquareLine[1].stPoint[1].nX += rSquare.nLength;	stSquareLine[1].stPoint[1].nY += rSquare.nLength;

	stSquareLine[2].stPoint[0] = rSquare.stVertex;	stSquareLine[2].stPoint[0].nX += rSquare.nLength;	stSquareLine[2].stPoint[0].nY += rSquare.nLength;
	stSquareLine[2].stPoint[1] = rSquare.stVertex;	stSquareLine[2].stPoint[1].nY += rSquare.nLength;

	stSquareLine[3].stPoint[0] = rSquare.stVertex;	stSquareLine[3].stPoint[0].nY += rSquare.nLength;
	stSquareLine[3].stPoint[1] = rSquare.stVertex;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (gbase::IsLineOverlapping(stTriangleLine[i], stSquareLine[j]))
			{
				return true;
			}
		}
	}

	return false;
}

////////////////////////////////////////////////////////////////////////
// Description:  获得两个三角形的关系
// Arguments:
// Return Value: TRIANGLE_RELATION
////////////////////////////////////////////////////////////////////////
gbase::TRIANGLE_RELATION gbase::GetTriangleRelation( const gbase::ST_TRIANGLE& rTriangle1, const gbase::ST_TRIANGLE& rTriangle2 )
{
	std::set<I64> setPoint;

	for (int i = 0; i < 3; i++)
	{
		I64 iPoint = (((I64)rTriangle1.stVertex[i].nX) << 32) + rTriangle1.stVertex[i].nY; 
		if (setPoint.find(iPoint) == setPoint.end())
		{
			setPoint.insert(iPoint);
		}

		iPoint = (((I64)rTriangle2.stVertex[i].nX) << 32) + rTriangle2.stVertex[i].nY; 
		if (setPoint.find(iPoint) == setPoint.end())
		{
			setPoint.insert(iPoint);
		}
	}

	switch (setPoint.size())
	{
	case 3:
		return gbase::TRIANGLE_RELATION_SAME_ALL;
		break;
	case 4:
		return gbase::TRIANGLE_RELATION_SAME_LINE;
		break;
	case 5:
		return gbase::TRIANGLE_RELATION_SAME_POINT;
		break;
	case 6:
		return gbase::TRIANGLE_RELATION_SAME_NOTHING;
		break;
	default:
		return gbase::TRIANGLE_RELATION_SAME_ERROR;
		break;
	}
}

////////////////////////////////////////////////////////////////////////
// Description:  三角形顶点逆时针序列化
// Arguments:
// Return Value: void
////////////////////////////////////////////////////////////////////////
void gbase::ProcessTriangleSeialization( gbase::ST_TRIANGLE& rTriangle )
{
	int nFirstIndex = 0;
	for (int i = 1; i < 3; i++)
	{
		if (rTriangle.stVertex[i].nY > rTriangle.stVertex[nFirstIndex].nY)
		{
			nFirstIndex = i;
		}
		else if (rTriangle.stVertex[i].nY == rTriangle.stVertex[nFirstIndex].nY)
		{
			if (rTriangle.stVertex[i].nX > rTriangle.stVertex[nFirstIndex].nX)
			{
				nFirstIndex = i;
			}
		}
	}

	// 放置第一个点
	if (nFirstIndex != 0)
	{
		std::swap(rTriangle.stVertex[0].nX, rTriangle.stVertex[nFirstIndex].nX);
		std::swap(rTriangle.stVertex[0].nY, rTriangle.stVertex[nFirstIndex].nY);
	}

	// 第二个点比较
	if (rTriangle.stVertex[2].nY > rTriangle.stVertex[1].nY)
	{
		std::swap(rTriangle.stVertex[2].nX, rTriangle.stVertex[1].nX);
		std::swap(rTriangle.stVertex[2].nY, rTriangle.stVertex[1].nY);
	}
	else if (rTriangle.stVertex[2].nY == rTriangle.stVertex[1].nY)
	{
		if (rTriangle.stVertex[2].nX < rTriangle.stVertex[1].nX)
		{
			std::swap(rTriangle.stVertex[2].nX, rTriangle.stVertex[1].nX);
			std::swap(rTriangle.stVertex[2].nY, rTriangle.stVertex[1].nY);
		}
	}
}

////////////////////////////////////////////////////////////////////////
// Description:  根据时间与速度算前进距离
// Arguments:
// Return Value: int
////////////////////////////////////////////////////////////////////////
int gbase::CalcGoDistance(__int64 i64TimeMSStart, __int64 i64TimeMSEnd, int nSpeed)
{
	if (i64TimeMSEnd <= i64TimeMSStart)
	{
		return 0;
	}

	if (nSpeed <= 0)
	{
		return 0;
	}

	__int64 i64Result = 0;
	i64Result = (__int64)nSpeed * (i64TimeMSEnd - i64TimeMSStart) / 1000;
	return (int)i64Result;
}

////////////////////////////////////////////////////////////////////////
// Description:  根据两点和长度算目标点
// Arguments:
// Return Value: gbase::ST_POINT
////////////////////////////////////////////////////////////////////////
gbase::ST_POINT gbase::CalcWalkTarget(const gbase::ST_POINT& rSrcPoint, const gbase::ST_POINT& rTargetPoint, int nLength)
{
	if (0 == nLength)
	{
		return rSrcPoint;
	}

	if (gbase::GetDistance(rSrcPoint, rTargetPoint) < nLength)
	{
		return rTargetPoint;
	}

	gbase::ST_POINT stResult = {0};
	stResult = rSrcPoint;

	// y相同
	if (rTargetPoint.nY == rSrcPoint.nY)
	{
		if (rTargetPoint.nX > rSrcPoint.nX)
		{
			stResult.nX += nLength;
		}
		else
		{
			stResult.nX -= nLength;
		}
		return stResult;
	}

	// x相同
	if (rTargetPoint.nX == rSrcPoint.nX)
	{
		if (rTargetPoint.nY > rSrcPoint.nY)
		{
			stResult.nY += nLength;
		}
		else
		{
			stResult.nY -= nLength;
		}
		return stResult;
	}

	double dAngle = atan2((double)(rTargetPoint.nY - rSrcPoint.nY), (double)(rTargetPoint.nX - rSrcPoint.nX));
	double dDetlaX = cos(dAngle) * nLength;
	double dDetlaY = sin(dAngle) * nLength;

	stResult.nX = rSrcPoint.nX + (int)dDetlaX;
	stResult.nY = rSrcPoint.nY + (int)dDetlaY;
	return stResult;
}

////////////////////////////////////////////////////////////////////////
// Description:  计算客户端角度
// Arguments:	 由x轴正向顺时针计算, 取值范围[0, 359]
// Return Value: int
////////////////////////////////////////////////////////////////////////
int gbase::GetClientAngle( int nX, int nY )
{
	double dAngle = atan2((double)nX, (double)nY);
	int nResult = (int)(dAngle / 3.1415926 * 180);
	if (nResult <= 0)
	{
		nResult = 0 - nResult;
	}
	else 
	{
		nResult = 360 - nResult;
	}
	return nResult;
}

////////////////////////////////////////////////////////////////////////
// Description: 判断是否是正确的矩形描述
// Arguments:	非相邻边不应相交
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool gbase::IsRightRectangle( const gbase::ST_RECTANGLE& rRectangle )
{
	gbase::ST_LINE line[4];
	line[0].stPoint[0] = rRectangle.stVertex[0];
	line[0].stPoint[1] = rRectangle.stVertex[1];

	line[1].stPoint[0] = rRectangle.stVertex[1];
	line[1].stPoint[1] = rRectangle.stVertex[2];

	line[2].stPoint[0] = rRectangle.stVertex[2];
	line[2].stPoint[1] = rRectangle.stVertex[3];

	line[3].stPoint[0] = rRectangle.stVertex[3];
	line[3].stPoint[1] = rRectangle.stVertex[0];

	if (gbase::IsLineOverlapping(line[0], line[2]))
	{
		return false;
	}

	if (gbase::IsLineOverlapping(line[1], line[3]))
	{
		return false;
	}

	return true;
}
