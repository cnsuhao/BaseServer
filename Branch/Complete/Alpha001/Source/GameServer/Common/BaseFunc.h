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
// ʱ�亯�����
enum TIME_TYPE	// ʱ������ö��
{
	TIME_BEGIN,
	TIME_MILLISECOND=TIME_BEGIN,	// ����					::timeGetTime()
	TIME_SECOND,					// ��					::time(NULL)
	TIME_MINUTE,					// ��					YYMMDDHHMM
	TIME_HOUR,						// ʱ					YYMMDDHH
	TIME_DAY,						// ��					YYMMDD
	TIME_DAYSECOND,					// ÿ���ʱ�� ��ȷ����  HHMMSS
	TIME_DAYMIN,					// ÿ���ʱ�� ��ȷ����  HHMM
	TIME_DAYHOUR,					// ÿ���ʱ�� ��ȷ��ʱ  HH
	TIME_DAY_START,					// ����ĵ�һ��
	TIME_DAY_END,					// �������һ��
	TIME_WEEK_DAY,					// ���ܵڼ���			
	TIME_WEEK_START,				// ���ܵ�һ��
	TIME_WEEK_END,					// �������һ��
	TIME_MONTH_DAY,					// ���µڼ���
	TIME_MONTH_START,				// ���µ�һ��
	TIME_MONTH_END,					// �������һ��
	TIME_YEAR_DAY,					// ���еڼ���
	TIME_YEAR_MONTH_DAY,			// ������				YYYYMMDD
	TIME_STAMP,						// ʱ���				MMDDHHMMSS
	TIME_EPOCH_DAY,					// ʱ���.��ǰʱ�����ο�ʱ��������
	TIME_DAYMINISECOND,				// ƴ���졢Сʱ�����ӡ��롢����	DDHHMMSSss
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
// ��ֵ�������
template<TYPENAME T>
inline T	CutOverflow(T x, T y) { return (x <= y) ? x : y; }
template<TYPENAME T>
inline T	CutTrail(T x, T y) { return (x >= y) ? x : y; }
template<TYPENAME T>
inline T	CutRange(T n, T min, T max) { return (n<min) ? min : ((n>max) ? max : n); }

// ��ֵ�޶��ں���Χ��
template <class T>
T GetValueInRightRange(T value, T minValue, T maxValue)
{
	value = min(value, maxValue);
	value = max(value, minValue);
	return value;
}

// ���ֵ�Ƿ��ں���Χ������������Ĭ��ֵ
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
// �ַ������������
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
// ����һЩ����
// �ж϶���type
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
// ��������ڳ�ʱͳ��, ��ר��TimeOut��־��¼
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
	std::string m_strReason;///ԭ��
	std::string m_strFileName;
	int			m_nFileLine;
};

//////////////////////////////////////////////////////////////////////////
// ���������ÿ��ʱ������ͳ��, ֱ�Ӽ���syslog
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
// ͼ��ѧ����
inline int	index2x(int idx, int cx, int cy) { return (idx % cy); }
inline int	index2y(int idx, int cx, int cy) { return (idx / cy); }
inline int	pos2index(int x, int y, int cx, int cy) { return (x + y*cx); }
inline void pos2lt(POINT* pTarget, const POINT& pos, int nRange) { pTarget->x = pos.x - nRange; pTarget->y = pos.y - nRange; }
inline void posadd(POINT* pTarget, int nOffsetX, int nOffsetY) { pTarget->x += nOffsetX; pTarget->y += nOffsetY; }
inline void possub(POINT* pTarget, int nOffsetX, int nOffsetY) { pTarget->x -= nOffsetX; pTarget->y -= nOffsetY; }

namespace gbase
{
	struct ST_POINT		{int nX;int nY;};					// ������
	struct ST_LINE		{ST_POINT stPoint[2];};				// �߶�
	struct ST_TRIANGLE	{ST_POINT stVertex[3];};			// ������
	struct ST_SQUARE	{ST_POINT stVertex;int nLength;};	// ������
	struct ST_CIRCLE	{ST_POINT stCenter;int nR;};		// Բ��
	struct ST_RECTANGLE	{ST_POINT stVertex[4];};			// ����
	enum TRIANGLE_RELATION
	{
		TRIANGLE_RELATION_SAME_ERROR = 0,	// ����
		TRIANGLE_RELATION_SAME_ALL,			// ͬһ��������
		TRIANGLE_RELATION_SAME_LINE,		// ����ͬ��
		TRIANGLE_RELATION_SAME_POINT,		// ����ͬ����
		TRIANGLE_RELATION_SAME_NOTHING,		// ����ͬ��
	};

	bool				IsDoubleZero(double dParam);																		// �ж��ǲ��Ǹ���0
	double				GetDistance(const gbase::ST_POINT& rPoint1, const gbase::ST_POINT& rPoint2);						// ��������ľ���
	bool				IsPointOnLine(const gbase::ST_POINT& rPoint, const gbase::ST_LINE& rLine);							// ���Ƿ����߶���
	double				GetDeterminant(double v1, double v2, double v3, double v4);											// �������ʽ��ֵ
	bool				IsLineOverlapping(const gbase::ST_LINE& rLine1, const gbase::ST_LINE& rLine2);						// �߶��Ƿ��ཻ
	bool				IsInPolygon(const gbase::ST_POINT arr[], size_t len, const gbase::ST_POINT& p);						// ���Ƿ��ڶ������
	bool				IsPointInTriangle(const gbase::ST_POINT& rPoint, const gbase::ST_TRIANGLE& rTriangle);				// ���Ƿ�����������
	bool				IsPointInSquare(const gbase::ST_POINT& rPoint, const gbase::ST_SQUARE& rSquare);					// ���Ƿ�����������
	bool				IsPointInRectangle(const gbase::ST_POINT& rPoint, const gbase::ST_RECTANGLE& rRectangle);			// ���Ƿ��ھ�����
	bool				IsTriangleSquareOverlapping(const gbase::ST_TRIANGLE& rTriangle, const gbase::ST_SQUARE& rSquare);	// �����κ��������Ƿ��ཻ
	TRIANGLE_RELATION	GetTriangleRelation(const gbase::ST_TRIANGLE& rTriangle1, const gbase::ST_TRIANGLE& rTriangle2);	// ���������εĹ�ϵ
	void				ProcessTriangleSeialization(gbase::ST_TRIANGLE& rTriangle);											// �����ζ�����ʱ�����л�
	int					CalcGoDistance(__int64 i64TimeMSStart, __int64 i64TimeMSEnd, int nSpeed);							// ����ʱ�����ٶ���ǰ������
	ST_POINT			CalcWalkTarget(const ST_POINT& rSrcPoint, const ST_POINT& rTargetPoint, int nLength);				// ��������ͳ�����Ŀ���
	int					GetClientAngle(int nX, int nY);																		// ����ͻ��˽Ƕ�
	bool				IsRightRectangle(const ST_RECTANGLE& rRectangle);													// �ж��Ƿ�����ȷ�ľ�������
}


#endif
