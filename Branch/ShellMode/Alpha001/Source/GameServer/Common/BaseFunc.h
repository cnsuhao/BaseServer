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

extern char g_szServerName[64];				// 服务器名
extern int  g_nServerLine;					// 服务器线路号
extern int  g_nServerGroup;					// 服务器组号
extern int	g_nServerStartTime;				// 服务器开启时间精确到天
extern std::string g_strConstDatabaseName;	// 常量表数据库名
extern std::string g_strGameDatabaseName;	// 游戏服数据库名
extern std::string g_strAccountDatabaseName;// 账号服数据库名

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

///枚请在后面增加 脚本要用到举
enum TIME_TYPE{
	TIME_BEGIN,
	TIME_MILLISECOND=TIME_BEGIN, 
	TIME_SECOND, 
	TIME_MINUTE, 
	TIME_HOUR,
	TIME_DAY, 
	TIME_DAYTIME, 
	TIME_STAMP,
	TIME_EPOCH_DAY,//20070402:时间点.当前时间距离参考时间点的天数
	MONTH_DAY,//20070402:得到当月的几号
	YEAR_DAY,//20070402:得到一年中的第几天
	WEEK_DAY,//得到一个星期的第几天
	YEAR_MONTH_DAY,
	TIME_DAYHOUR,//每天的时间 精确到小时
	TIME_DAYMIN,//每天的时间 精确到分钟
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
//获得一个天、小时、分钟、秒、毫秒拼接在数字
DWORD GetTimeDayToMiniSecond();

UINT GetNextUpdateTime(UINT unHour, TIME_TYPE type = TIME_SECOND);
UINT GetLog2(UINT nNum);

// 获得当前时间与参数的间隔时间，支持TIME_MINUTE
UINT GetTimeDuring(UINT unLastTime);

bool IsTimeOver(UINT nEndDate);
int GetCurTimeSpan(UINT nDataTime);
int GetNextWeekStartUTC();
int GetYearMonthDayFormUtcSecond(time_t nUtcSecond);

//[游途道标 2009.06.10]资产流向日志
//////////////////////////////////////////////////////////////////////////
enum
{
	NONE = 0,
		BOOTH_SALE,//摆摊卖
		BOOTH_BUY,//摆摊购买
		BANGPAI_HONGBAO,//发红包
		TRADE_ONE,//交易1
		TRADE_TWO,//交易2
		SHOP_ADDBUY,//添加寄售信息
		SHOP_SALE,//店铺购买物品
		SHOP_ADDSALE,//添加出售物品
		SHOP_BUY,//店铺收购
		SHOP_DEL_SALE,//退回出售物品
		SHOP_DEL_BUY,//退回收购物品
		SHOP_PAIMAI_TUIHUI,//退回拍卖钱
		SHOP_PAIMAI,//拍卖
		SHOP_XUZU,//店铺续租
		SHOP_TIQU,//店铺提取
		MAIL_YIBAN,//邮件日志
		MAIL_JIAOYI,//邮件日志
		MAIL_TUIHUI,//邮件日志
};

struct STPROPERTYSTREAMLOG
{
	DWORD	idSource;//源标识
	DWORD	idSAccount;
	DWORD	dwSVas;//源当前VAS
	DWORD	dwSMoney;//源当前游戏币
	DWORD	idTarget;//目标标识
	DWORD	idTAccount;
	DWORD	dwTVas;//源当前VAS
	DWORD	dwTMoney;//源当前游戏币
	DWORD	dwVas;//流动VAS
	DWORD	dwMoney;//流动货币
	DWORD	idItemType;
	DWORD	idSItem;//流动物品标识
	DWORD	dwSNumber;//流动物品标识
	DWORD	idTItem;//流动物品标识
	DWORD	dwTNumber;//流动物品标识
	DWORD	dwSysVas;
	DWORD	dwSysMoney;
	DWORD	dwType;//类型
	
	STPROPERTYSTREAMLOG()
	{
		idSource = NULL;//源标识
		idSAccount = NULL;
		dwSVas = NULL;//源当前VAS
		dwSMoney = NULL;//源当前游戏币
		idTarget = NULL;//目标标识
		idTAccount = NULL;
		dwTVas = NULL;//源当前VAS
		dwTMoney = NULL;//源当前游戏币
		dwVas = NULL;//流动VAS
		dwMoney = NULL;//流动货币
		idItemType = NULL;
		idSItem = NULL;//流动物品标识
		dwSNumber = NULL;//流动物品标识
		idTItem = NULL;//流动物品标识
		dwTNumber = NULL;//流动物品标识
		dwSysVas = NULL;
		dwSysMoney = NULL;
		dwType = NULL;//类型
	}
};

void	PropertyStreamLog(STPROPERTYSTREAMLOG &stProStream);

//////////////////////////////////////////////////////////////////////////
//20071212:进制转换.nConvNum:2~9.
//如6进制转换.
//nConvNum = 6
//nTrainPoint = 7
//返回值为11.
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

int bit_count(int n);//检测二进制中的1的个数
int I64_bit_count(I64 I64Data, int nEndIndex = 64);//检测二进制中的1的个数
UINT GetNextUpdateMonthDate();//用于月掩码清理，获取下个月的每一天(YYYYMMDD)精确到日

UINT GetItemLifeTimeMinute(int nLifeTimeOffset);

bool IsRightAuthenID(DWORD dwAuthenID, DWORD dwAccount);				// 验证登陆时的票id
bool SafeCopy(char * pTarget, const char * pSource, int nBufLen = 0);	// 字符串安全拷贝
bool IsObjType(OBJID idObjType, OBJID idUnion);							// 判断对象type
double SaveTwoDecimal(double dInput);									// double类型保留两位小数
DWORD GetPassDay(DWORD dwTimeDay);

////////////////////////////////////////////////////////////////////////
// Description:  将值限定在合理范围内
// Arguments:
// Author: 彭文奇(Peng Wenqi)
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

std::string LoadFileToString(const std::string& strFileName);	//从文件读入到string里
int ReplaceStdString(IN OUT string& str, const char* pszOld, const char* pszNew, bool bReplaceAll = true);	// 替换std::string中的字符
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
// 图形学函数
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
