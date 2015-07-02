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

extern char g_szServerName[64];				// ��������
extern int  g_nServerLine;					// ��������·��
extern int  g_nServerGroup;					// ���������
extern int	g_nServerStartTime;				// ����������ʱ�侫ȷ����
extern std::string g_strConstDatabaseName;	// ���������ݿ���
extern std::string g_strGameDatabaseName;	// ��Ϸ�����ݿ���
extern std::string g_strAccountDatabaseName;// �˺ŷ����ݿ���

UINT	GetNextUpdateTimeOfWeek(UINT unTimeOfDay);
String	DumpBuffer(const char* buf, int nSize);
void	DateTime(char * buf20, time_t tInput = 0);		// 0 : curr time
bool	FormatDateTime(char* buf, const char* szFormat, time_t tInput = 0);		// szFormat: "%04d-%02d-%02d %02d:%02d:%02d"
void	DateTimeStamp(char * buf15, time_t tInput = 0);		// 0 : curr time
int		DateStamp(time_t tTime=0);
int		DateStampPass(int nDate, int nDays);	// return -1: error
bool	IsActiveTime(time_t tCurr, unsigned long nFormat);
bool	IsTimeRange(unsigned long nBegin, unsigned long nEnd, time_t tCurr=0);
char*	StrStrCh(const char* string, const char* strCharSet);
int		CalcNumberAxisIntersection(int x1, int y1, int x2, int y2);

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

///ö���ں������� �ű�Ҫ�õ���
enum TIME_TYPE{
	TIME_BEGIN,
	TIME_MILLISECOND=TIME_BEGIN, 
	TIME_SECOND, 
	TIME_MINUTE, 
	TIME_HOUR,
	TIME_DAY, 
	TIME_DAYTIME, 
	TIME_STAMP,
	TIME_EPOCH_DAY,//20070402:ʱ���.��ǰʱ�����ο�ʱ��������
	MONTH_DAY,//20070402:�õ����µļ���
	YEAR_DAY,//20070402:�õ�һ���еĵڼ���
	WEEK_DAY,//�õ�һ�����ڵĵڼ���
	YEAR_MONTH_DAY,
	TIME_DAYHOUR,//ÿ���ʱ�� ��ȷ��Сʱ
	TIME_DAYMIN,//ÿ���ʱ�� ��ȷ������
	TIME_DAY_START,
	TIME_DAY_END,
	TIME_WEEK_START,
	TIME_WEEK_END,
	TIME_MONTH_START,
	TIME_MONTH_END,
	TIME_END,
};

UINT	UtcSecondConvert(UINT unSecond, TIME_TYPE eType);
DWORD	TimeGet(TIME_TYPE type=TIME_MILLISECOND);
I64		GetUtcMillisecond(void);
int		RandGet		(int nMax, bool bReset=false);
int		RandGetZT(int nMax, double dRangeParamL=3.0, double dRangeParamR=3.0, bool bRest=false);
void	DDALineEx(int x0, int y0, int x1, int y1, vector<POINT>& vctPoint);
//���һ���졢Сʱ�����ӡ��롢����ƴ��������
DWORD GetTimeDayToMiniSecond();

UINT GetNextUpdateTime(UINT unHour, TIME_TYPE type = TIME_SECOND);
UINT GetLog2(UINT nNum);

// ��õ�ǰʱ��������ļ��ʱ�䣬֧��TIME_MINUTE
UINT GetTimeDuring(UINT unLastTime);

bool IsTimeOver(UINT nEndDate);
int GetCurTimeSpan(UINT nDataTime);
int GetNextWeekStartUTC();
int GetYearMonthDayFormUtcSecond(time_t nUtcSecond);

//[��;���� 2009.06.10]�ʲ�������־
//////////////////////////////////////////////////////////////////////////
enum
{
	NONE = 0,
		BOOTH_SALE,//��̯��
		BOOTH_BUY,//��̯����
		BANGPAI_HONGBAO,//�����
		TRADE_ONE,//����1
		TRADE_TWO,//����2
		SHOP_ADDBUY,//��Ӽ�����Ϣ
		SHOP_SALE,//���̹�����Ʒ
		SHOP_ADDSALE,//��ӳ�����Ʒ
		SHOP_BUY,//�����չ�
		SHOP_DEL_SALE,//�˻س�����Ʒ
		SHOP_DEL_BUY,//�˻��չ���Ʒ
		SHOP_PAIMAI_TUIHUI,//�˻�����Ǯ
		SHOP_PAIMAI,//����
		SHOP_XUZU,//��������
		SHOP_TIQU,//������ȡ
		MAIL_YIBAN,//�ʼ���־
		MAIL_JIAOYI,//�ʼ���־
		MAIL_TUIHUI,//�ʼ���־
};

struct STPROPERTYSTREAMLOG
{
	DWORD	idSource;//Դ��ʶ
	DWORD	idSAccount;
	DWORD	dwSVas;//Դ��ǰVAS
	DWORD	dwSMoney;//Դ��ǰ��Ϸ��
	DWORD	idTarget;//Ŀ���ʶ
	DWORD	idTAccount;
	DWORD	dwTVas;//Դ��ǰVAS
	DWORD	dwTMoney;//Դ��ǰ��Ϸ��
	DWORD	dwVas;//����VAS
	DWORD	dwMoney;//��������
	DWORD	idItemType;
	DWORD	idSItem;//������Ʒ��ʶ
	DWORD	dwSNumber;//������Ʒ��ʶ
	DWORD	idTItem;//������Ʒ��ʶ
	DWORD	dwTNumber;//������Ʒ��ʶ
	DWORD	dwSysVas;
	DWORD	dwSysMoney;
	DWORD	dwType;//����
	
	STPROPERTYSTREAMLOG()
	{
		idSource = NULL;//Դ��ʶ
		idSAccount = NULL;
		dwSVas = NULL;//Դ��ǰVAS
		dwSMoney = NULL;//Դ��ǰ��Ϸ��
		idTarget = NULL;//Ŀ���ʶ
		idTAccount = NULL;
		dwTVas = NULL;//Դ��ǰVAS
		dwTMoney = NULL;//Դ��ǰ��Ϸ��
		dwVas = NULL;//����VAS
		dwMoney = NULL;//��������
		idItemType = NULL;
		idSItem = NULL;//������Ʒ��ʶ
		dwSNumber = NULL;//������Ʒ��ʶ
		idTItem = NULL;//������Ʒ��ʶ
		dwTNumber = NULL;//������Ʒ��ʶ
		dwSysVas = NULL;
		dwSysMoney = NULL;
		dwType = NULL;//����
	}
};

void	PropertyStreamLog(STPROPERTYSTREAMLOG &stProStream);

//////////////////////////////////////////////////////////////////////////
//20071212:����ת��.nConvNum:2~9.
//��6����ת��.
//nConvNum = 6
//nTrainPoint = 7
//����ֵΪ11.
int NumConversion(int nTrainPoint,int nConvNum);

BOOL	StringCheck	(const char* pszString, BOOL bNewLineEnable=false);
BOOL	TalkStrCheck(char* pszString, BOOL bNewLineEnable=false);
BOOL	DisableWordCheck(const char* pszString, BOOL bNewLineEnable=false);
bool	StrSqlCheck(const char* pszString);
BOOL	NameStrCheck(const char* pszString);

double	RandomRateGet	(double dRange);
int		Double2Int		(double dValue);

inline int	AddToTop(int nData, int nAdd, int nTop) { int res=nData+nAdd; if(nAdd>0 && res<nData || res>nTop) return nTop; else return res; }

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

/////////////////////////////////////////////////////////////////////////////
template<TYPENAME T>
inline T	CutOverflow(T x, T y) { return (x <= y) ? x : y; }
template<TYPENAME T>
inline T	CutTrail(T x, T y) { return (x >= y) ? x : y; }
template<TYPENAME T>
inline T	CutRange(T n, T min, T max) { return (n<min) ? min : ((n>max) ? max : n); }

/////////////////////////////////////////////////////////////////////////////
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


//////////////////////////////////////////////////////////////////////
inline int pos2index(int x, int y, int cx, int cy) { return (x + y*cx); }
inline int index2x(int idx, int cx, int cy) { return (idx % cy); }
inline int index2y(int idx, int cx, int cy) { return (idx / cy); }
inline void pos2lt(POINT* pTarget, const POINT& pos, int nRange) { pTarget->x = pos.x - nRange; pTarget->y = pos.y - nRange; }
inline void posadd(POINT* pTarget, int nOffsetX, int nOffsetY) { pTarget->x += nOffsetX; pTarget->y += nOffsetY; }
inline void possub(POINT* pTarget, int nOffsetX, int nOffsetY) { pTarget->x -= nOffsetX; pTarget->y -= nOffsetY; }

inline bool ConvertMailText(OUT LPSTR lpstrText, UINT nAction, int nParam1 = 0, int nParam2 = 0, int nParam3 = 0, 
							int nParam4 = 0, int nParam5 = 0, int nParam6 = 0, LPCSTR lpstrParam1 = "", LPCSTR lpstrParam2 = "");

bool MyANSIToUnicode(IN const char* pszStr,		OUT wchar_t* pwszStr,	int nUnicodeStrSize);
bool MyUnicodeToANSI(IN const wchar_t* pwszStr,	OUT char* pszStr,		int nAnsiStrSize);
bool MyUnicodeToUTF8(IN const wchar_t* pwszStr, OUT char* pszStr,		int nUtf8StrSize);
bool MyUTF8ToUnicode(IN const char* pszStr,		OUT wchar_t* pwszStr,	int nUnicodeStrSize);

CMxyString MyUtf8ToANSI(const char* pszString);
CMxyString MyANSIToUtf8(const char* pszString);

int bit_count(int n);//���������е�1�ĸ���
int I64_bit_count(I64 I64Data, int nEndIndex = 64);//���������е�1�ĸ���
UINT GetNextUpdateMonthDate();//����������������ȡ�¸��µ�ÿһ��(YYYYMMDD)��ȷ����

UINT GetItemLifeTimeMinute(int nLifeTimeOffset);

bool IsRightAuthenID(DWORD dwAuthenID, DWORD dwAccount);				// ��֤��½ʱ��Ʊid
bool SafeCopy(char * pTarget, const char * pSource, int nBufLen = 0);	// �ַ�����ȫ����
bool IsObjType(OBJID idObjType, OBJID idUnion);							// �ж϶���type
double SaveTwoDecimal(double dInput);									// double���ͱ�����λС��
DWORD GetPassDay(DWORD dwTimeDay);

////////////////////////////////////////////////////////////////////////
// Description:  ��ֵ�޶��ں���Χ��
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: class T
////////////////////////////////////////////////////////////////////////
template <class T>
T GetValueInRightRange(T value, T minValue, T maxValue)
{
	value = min(value, maxValue);
	value = max(value, minValue);
	return value;
}

LONG WINAPI MyUnhandledExceptionFilter(struct _EXCEPTION_POINTERS* ExceptionInfo);

int GetUTCSecond(int nTimeType, I64 i64Time);
int GetHourUTCSecond(int nHour);
int GetTimeSpanFromDayBeginOfUTC(UINT unUTCTime);

std::string LoadFileToString(const std::string& strFileName);	//���ļ����뵽string��
int ReplaceStdString(IN OUT string& str, const char* pszOld, const char* pszNew, bool bReplaceAll = true);	// �滻std::string�е��ַ�
bool IsExistFile(const char* pszFileName);

std::string GetLocalIpAddr();

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


//////////////////////////////////////////////////////////////////////////
// ͼ��ѧ����
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
