#ifndef _BASEFUNC_H
#define _BASEFUNC_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma	warning(disable:4786)

#include "common.h"
#include "BaseType.h"
#include "logfile.h"
#include "AutoPtr.h"
#include "MxyString.h"
#include <time.h>
#include <math.h>
#include <vector>
using namespace std;

//////////////////////////////////////////////////////////////////////////
// 时间函数相关
enum TIME_TYPE	// 时间类型枚举
{
	TIME_BEGIN,
	TIME_MILLISECOND=TIME_BEGIN,	// 毫秒					::timeGetTime()
	TIME_SECOND,					// 秒					::time(NULL)
	TIME_MINUTE,					// 分					YYMMDDHHMM
	TIME_HOUR,						// 时					YYMMDDHH
	TIME_DAY,						// 天					YYMMDD
	TIME_DAYSECOND,					// 每天的时间 精确到秒  HHMMSS
	TIME_DAYMIN,					// 每天的时间 精确到分  HHMM
	TIME_DAYHOUR,					// 每天的时间 精确到时  HH
	TIME_DAY_START,					// 今天的第一秒
	TIME_DAY_END,					// 今天最后一秒
	TIME_WEEK_DAY,					// 本周第几天			
	TIME_WEEK_START,				// 本周第一秒
	TIME_WEEK_END,					// 本周最后一秒
	TIME_MONTH_DAY,					// 本月第几号
	TIME_MONTH_START,				// 本月第一秒
	TIME_MONTH_END,					// 本月最后一秒
	TIME_YEAR_DAY,					// 年中第几天
	TIME_YEAR_MONTH_DAY,			// 年月日				YYYYMMDD
	TIME_STAMP,						// 时间戳				MMDDHHMMSS
	TIME_EPOCH_DAY,					// 时间点.当前时间距离参考时间点的天数
	TIME_DAYMINISECOND,				// 拼接天、小时、分钟、秒、毫秒	DDHHMMSSss
	TIME_END,
};
DWORD	TimeGet(TIME_TYPE type = TIME_MILLISECOND);
int     GetUTCSecond(int nTimeType, I64 i64Time);
I64		GetUtcMillisecond(void);
UINT	GetUtcTimeConvert(UINT unTimeSecond, TIME_TYPE eType);

UINT	GetNextWeekStartUtcTime(void);
UINT    GetNextUpdateTime(UINT unHour, TIME_TYPE type = TIME_SECOND);
UINT	GetNextUpdateTimeOfWeek(UINT unTimeOfDay);
UINT	GetNextUpdateMonthDate(void);

bool	IsTimeOver(UINT nEndDate);
int		GetHourUTCSecond(int nHour);
int		GetTimeSpanFromSecond(UINT unUtcTime);
int     GetTimeSpanToMunite(UINT nDataTime);
int		GetTimeSpanToDay(DWORD dwTimeDay);
UINT    GetTimeMinuteFromLeftMunite(int nMuniteOffset);

void	DateTime(char * buf20, time_t tInput = 0);
bool	FormatDateTime(char* buf, const char* szFormat, time_t tInput = 0);
int		DateStamp(time_t tTime = 0);
void	DateTimeStamp(char * buf15, time_t tInput = 0);
int		DateStampPass(int nDate, int nDays);
bool	IsActiveTime(time_t tCurr, unsigned long nFormat);
bool	IsTimeRange(unsigned long nBegin, unsigned long nEnd, time_t tCurr=0);
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// 数值函数相关
template<TYPENAME T>
inline T	CutOverflow(T x, T y) { return (x <= y) ? x : y; }
template<TYPENAME T>
inline T	CutTrail(T x, T y) { return (x >= y) ? x : y; }
template<TYPENAME T>
inline T	CutRange(T n, T min, T max) { return (n<min) ? min : ((n>max) ? max : n); }

// 将值限定在合理范围内
template <class T>
T GetValueInRightRange(T value, T minValue, T maxValue)
{
	value = min(value, maxValue);
	value = max(value, minValue);
	return value;
}

// 检测值是否在合理范围，不合理就输出默认值
template<class T>
bool CheckBetween(IN OUT T& nowVaule, T minVaule, T maxVaule, T defaultValue)
{
	bool bResult = false;
	if (nowVaule >= minVaule && nowVaule <= maxVaule)
	{
		bResult = true;
	}
	else
	{
		nowVaule = defaultValue;
	}

	return bResult;
}

inline unsigned int	ExchangeShortBits(unsigned long nData, int nBits)
{
	ASSERT(nBits >= 0 && nBits < 16);
	nData	&= 0xFFFF;
	return ((nData>>nBits) | (nData<<(16-nBits))) & 0xFFFF;
}

inline unsigned int	ExchangeLongBits(unsigned long nData, int nBits)
{
	ASSERT(nBits >= 0 && nBits < 32);
	return (nData>>nBits) | (nData<<(32-nBits));
}

inline double CalculationRatio(DWORD dwData, DWORD dwRatio)
{
	double dValue = ceil(dwData*dwRatio/10000.0);
	return dValue;
}

inline int	AddToTop(int nData, int nAdd, int nTop) 
{ 
	int res = nData + nAdd;
	if (nAdd > 0 && res < nData || res > nTop)
		return nTop;
	else 
		return res; 
}

int		RandGet(int nMax, bool bReset=false);
int		RandGetZT(int nMax, double dRangeParamL = 3.0, double dRangeParamR = 3.0, bool bRest = false);
double	RandomRateGet(double dRange);

int		Double2Int(double dValue);
double  DoubleSaveTwoDecimal(double dInput);

int		bit_count(int n);
int		bit_i64_count(I64 i64Data, int nEndIndex = 64);

UINT	GetLog2(UINT nNum);
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// 字符串整理函数相关
String	DumpBuffer(const char* buf, int nSize);
char*	StrStrCh(const char* string, const char* strCharSet);

BOOL	StringCheck	(const char* pszString, BOOL bNewLineEnable=false);
BOOL	TalkStrCheck(char* pszString, BOOL bNewLineEnable=false);
BOOL	DisableWordCheck(const char* pszString, BOOL bNewLineEnable=false);
bool	StrSqlCheck(const char* pszString);
BOOL	NameStrCheck(const char* pszString);

bool	MyANSIToUnicode(IN const char* pszStr,		OUT wchar_t* pwszStr,	int nUnicodeStrSize);
bool	MyUnicodeToANSI(IN const wchar_t* pwszStr,	OUT char* pszStr,		int nAnsiStrSize);
bool	MyUnicodeToUTF8(IN const wchar_t* pwszStr,  OUT char* pszStr,		int nUtf8StrSize);
bool	MyUTF8ToUnicode(IN const char* pszStr,		OUT wchar_t* pwszStr,	int nUnicodeStrSize);

CMxyString MyUtf8ToANSI(const char* pszString);
CMxyString MyANSIToUtf8(const char* pszString);

bool	SafeCopy(char * pTarget, const char * pSource, int nBufLen = 0);
int		ReplaceStdString(IN OUT string& str, const char* pszOld, const char* pszNew, bool bReplaceAll = true);
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// 其他一些函数
// 判断对象type
inline bool	IsObjType(OBJID idObjType, OBJID idUnion)
{
	return (idObjType & idUnion & 0x0FFF) != 0; 
}

bool	IsExistFile(const char* pszFileName);
std::string LoadFileToString(const std::string& strFileName);

int		CalcNumberAxisIntersection(int x1, int y1, int x2, int y2);
void	DDALineEx(int x0, int y0, int x1, int y1, vector<POINT>& vctPoint);

int		NumConversion(int nTrainPoint,int nConvNum);

bool	IsRightAuthenID(DWORD dwAuthenID, DWORD dwAccount);

std::string GetLocalIpAddr();

LONG WINAPI MyUnhandledExceptionFilter(struct _EXCEPTION_POINTERS* ExceptionInfo);

struct WEIGHTED_VALUE
{
	int nWeight;
	int nValue;
};
typedef std::vector<WEIGHTED_VALUE>			VEC_WEIGHTED_VALUE;
typedef VEC_WEIGHTED_VALUE::iterator		ITER_WEIGHTED_VALUE;
typedef VEC_WEIGHTED_VALUE::const_iterator	CITER_WEIGHTED_VALUE;
typedef std::vector<int>					VEC_WEIGHT_OUTPUT;
typedef VEC_WEIGHT_OUTPUT::iterator			ITER_WEIGHT_OUTPUT;
typedef VEC_WEIGHT_OUTPUT::const_iterator	CITER_WEIGHT_OUTPUT;
void GenWeightRandomVector(const VEC_WEIGHTED_VALUE& rInputVec, OUT VEC_WEIGHT_OUTPUT& rOutputVec, int nCount = 1);
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// 这个类用于超时统计, 有专用TimeOut日志记录
#define TimeCostChk(pszReason, pszString) CTimeCostChk objCostChk(pszReason, pszString, 80, __FILE__, __LINE__);
class CTimeCostChk
{
public:
	CTimeCostChk(const char* pszReason,const char* pszString, I64 i64CheckMS, const char* pszFileName, int nFileLine);
	~CTimeCostChk();

private:
	I64 m_i64CheckMS;
	I64 m_i64BeginMS;
	std::string m_strString;
	std::string m_strReason;///原因
	std::string m_strFileName;
	int			m_nFileLine;
};

//////////////////////////////////////////////////////////////////////////
// 这个类用于每次时间消耗统计, 直接记入syslog
#define TimeUseMSLog(x) CTimeUseMSLog objTimeUse(x, __FILE__, __LINE__);
class CTimeUseMSLog
{
public:
	CTimeUseMSLog(const char* pszReason, const char* pszFileName, int nFileLine);
	~CTimeUseMSLog();

private:
	I64 m_i64BeginMS;
	std::string m_strReason;
	std::string m_strFileName;
	int			m_nFileLine;
};

//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// 图形学函数
inline int	index2x(int idx, int cx, int cy) { return (idx % cy); }
inline int	index2y(int idx, int cx, int cy) { return (idx / cy); }
inline int	pos2index(int x, int y, int cx, int cy) { return (x + y*cx); }
inline void pos2lt(POINT* pTarget, const POINT& pos, int nRange) { pTarget->x = pos.x - nRange; pTarget->y = pos.y - nRange; }
inline void posadd(POINT* pTarget, int nOffsetX, int nOffsetY) { pTarget->x += nOffsetX; pTarget->y += nOffsetY; }
inline void possub(POINT* pTarget, int nOffsetX, int nOffsetY) { pTarget->x -= nOffsetX; pTarget->y -= nOffsetY; }

namespace gbase
{
	struct ST_POINT		{int nX;int nY;};					// 点坐标
	struct ST_LINE		{ST_POINT stPoint[2];};				// 线段
	struct ST_TRIANGLE	{ST_POINT stVertex[3];};			// 三角形
	struct ST_SQUARE	{ST_POINT stVertex;int nLength;};	// 正方形
	struct ST_CIRCLE	{ST_POINT stCenter;int nR;};		// 圆形
	struct ST_RECTANGLE	{ST_POINT stVertex[4];};			// 矩形
	enum TRIANGLE_RELATION
	{
		TRIANGLE_RELATION_SAME_ERROR = 0,	// 错误
		TRIANGLE_RELATION_SAME_ALL,			// 同一个三角形
		TRIANGLE_RELATION_SAME_LINE,		// 有相同边
		TRIANGLE_RELATION_SAME_POINT,		// 有相同交点
		TRIANGLE_RELATION_SAME_NOTHING,		// 无相同点
	};

	bool				IsDoubleZero(double dParam);																		// 判断是不是浮点0
	double				GetDistance(const gbase::ST_POINT& rPoint1, const gbase::ST_POINT& rPoint2);						// 获得两点间的距离
	bool				IsPointOnLine(const gbase::ST_POINT& rPoint, const gbase::ST_LINE& rLine);							// 点是否在线段上
	double				GetDeterminant(double v1, double v2, double v3, double v4);											// 获得行列式的值
	bool				IsLineOverlapping(const gbase::ST_LINE& rLine1, const gbase::ST_LINE& rLine2);						// 线段是否相交
	bool				IsInPolygon(const gbase::ST_POINT arr[], size_t len, const gbase::ST_POINT& p);						// 点是否在多边形内
	bool				IsPointInTriangle(const gbase::ST_POINT& rPoint, const gbase::ST_TRIANGLE& rTriangle);				// 点是否在三角形内
	bool				IsPointInSquare(const gbase::ST_POINT& rPoint, const gbase::ST_SQUARE& rSquare);					// 点是否在正方形内
	bool				IsPointInRectangle(const gbase::ST_POINT& rPoint, const gbase::ST_RECTANGLE& rRectangle);			// 点是否在矩形内
	bool				IsTriangleSquareOverlapping(const gbase::ST_TRIANGLE& rTriangle, const gbase::ST_SQUARE& rSquare);	// 三角形和正方形是否相交
	TRIANGLE_RELATION	GetTriangleRelation(const gbase::ST_TRIANGLE& rTriangle1, const gbase::ST_TRIANGLE& rTriangle2);	// 两个三角形的关系
	void				ProcessTriangleSeialization(gbase::ST_TRIANGLE& rTriangle);											// 三角形顶点逆时针序列化
	int					CalcGoDistance(__int64 i64TimeMSStart, __int64 i64TimeMSEnd, int nSpeed);							// 根据时间与速度算前进距离
	ST_POINT			CalcWalkTarget(const ST_POINT& rSrcPoint, const ST_POINT& rTargetPoint, int nLength);				// 根据两点和长度算目标点
	int					GetClientAngle(int nX, int nY);																		// 计算客户端角度
	bool				IsRightRectangle(const ST_RECTANGLE& rRectangle);													// 判断是否是正确的矩形描述
}


#endif
