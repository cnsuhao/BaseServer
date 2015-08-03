// 诊断程序
// 仙剑修, 2001.10.10

#ifndef	LOGFILE_H
#define LOGFILE_H
#pragma	warning(disable:4786)

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "windows.h"
#include "time.h"
#include <vector>
#include <deque>
#include <list>
#include <string> 
#include "./ThreadBase.h"

#define		LOGFUNC_TRY			try{
#define		LOGFUNC_CATCH(x)	}catch(...){ OutputDebugString("GameServer Log Crash! [" x "]"); }

const INT MAX_ASYNC_LOG_AMOUNT	= 10000;	// 最多多少条异步log, 超过这个值时会出警告, clear时超过这个值的不被保存到文件
const int MAX_LOGFILESIZE = 10*1024*1024;	// 日志每10M分一个文件
extern BOOL g_bLogSave;						// 日志开关标志位
extern BOOL g_bLogWalk;						// 走路日志开关
extern BOOL g_bLogDatabaseSql;				// sql日志开关
const char SZ_UTF8_FILE_HEADER[3] = {(char)0xEF, (char)0xBB, (char)0xBF};	// utf8文件头

#define		LOGFILE_DIR				"syslog"
#define		GMLOG_DIR				"gmlog"
#define		DBLOGFILE_DIR			"dblog"

#define		DBLOGFILE_FILENAME		"dblog/db_execute_sql"
#define		LOGFILE_FILENAME		"syslog/sys"
#define		VALUABLESLOG_FILENAME	"gmlog/valueables"

// 日志线程
typedef std::pair<std::string, std::string> PAIR_LOGINFO;
class CLogThread : protected CThreadBase
{
	// 继承
protected:
	virtual	void	OnInit()	{}
	virtual bool	OnProcess()	;	// 异步线程主函数
	virtual void	OnDestroy() {}

	// 逻辑函数
public:
	void			LogPrint		(const char* pszLogFile, const char* pszLogInfo);	// 对外暴露接口
	bool			StartLogServe	(void);												// 开启日志线程服务
	bool			CloseLogServe	(void);												// 关闭日志线程服务
private:
	PAIR_LOGINFO	TakeAsyncLog	(void);												// [线程安全]提取异步日志
	void			PushAsyncLog	(const char* pszLogFile, const char* pszLogInfo);	// [线程安全]压入异步日志
	void			ClearAsynLog	(void);												// 清空队列中的日志
	void			ProcessOneLog	(void);												// 处理一条日志
	void			AutoReloadPass	(void);												// 自动重新加载过滤文件
	bool			IsPassLog		(const char* pszLogInfo);							// 这条日志是否需要过滤
	
	// 标记量
private:
	CSimpleCriticalSection		m_csAsync;			// 异步线程临界区
	std::deque<PAIR_LOGINFO>	m_deqAsyncLog;		// 异步线程日志容器
	std::list<PAIR_LOGINFO>		m_listAsyncLog;		// 异步线程日志容器
	int							m_nAsyncLogAmount;	// 异步线程日志数量
	bool						m_bOpenServe;		// 是否开启线程服务

	std::vector<std::string>	m_vecPassString;	// 需要过滤的字符串
	int							m_nLastReloadPass;	// 上次加载过滤文件时间
	

	// 单例
public:
	static CLogThread*	GetInstance(void);
	static void			DelInstance(void);
private:
	CLogThread();
	virtual ~CLogThread();
	static CLogThread*	s_pInstance;
};

// 使用前需要调用 InitLog()
void InitLog(const char * pTitle, time_t tStart);

#define LOGWARNING		::LogSave
#define LOGMSG			::LogSave
#define LOGERROR		::LogSave
#define LOGCHEAT		::LogSave


void	MakeLogFileHeader	(const char* pszFileName);
void	GetLogOutputBuffer	(OUT char* pszOutputBuffer, IN const char* pszBuffer);
void	LogSaveBase			(const char* pszLogFileName, const char* pszLogInfo);
void	LogSave				(const char* fmt, ...);
void	LogSave2			(const char* pszSrcFileName, UINT unSrcFileLine, const char* fmt, ...);
void	MyLogSave			(const char* pszName, const char* fmt, ...);
void	MyLogSave2			(const char* pszName, const char* fmt, ...);
void	Trace				(const char* fmt, ...);
void	GmLogSave			(const char* fmt, ...);
void	LogSaveLoginout		(const char* fmt, ...);
void	LogWalk				(const char* fmt, ...);
void	LogPokerBattle		(const char* fmt, ...);
void	LogDatabaseSql		(const char* fmt, ...);
void	LogMoney			(const char* fmt, ...);
void	LogStack			(const char* pszSrcFileName, UINT unSrcFileLine, const char* fmt, ...);
void	LogStackWithOutLine	(const char* fmt, ...);
void	LogTimeOut			(const char* fmt, ...);
void	LogLuaError			(const char* fmt, ...);
void	LogMemMonitor		(const char* fmt, ...);
void	LogPayAward			(const char* fmt, ...);
void	LogCheckSpeed		(const char* fmt, ...);
void	LogChangeName		(const char* fmt, ...);
void	LogPoker			(const char* fmt, ...);
void	LogUserMap			(const char* fmt, ...);
void	LogQuiz				(const char* fmt, ...);
void	LogTopList			(const char* fmt, ...);
void	LogActivity			(const char* fmt, ...);
void	LogDeleteItem		(const char* fmt, ...);
void	LogPayReturnVas		(const char* fmt, ...);
void	LogSavePayLog		(const char* fmt, ...);
void	LogSaveArena		(const char* fmt, ...);

#define tolog(a)  LogSave2(__FILE__, __LINE__,a);
#define tolog2(a,b)  LogSave2(__FILE__, __LINE__,a,b);
#define tolog3(a,b,c)  LogSave2(__FILE__, __LINE__,a,b,c);
#define tolog4(a,b,c,d)  LogSave2(__FILE__, __LINE__,a,b,c,d);
#define tolog5(a,b,c,d,e)  LogSave2(__FILE__, __LINE__,a,b,c,d,e);
#define tolog6(a,b,c,d,e,f)	 LogSave2(__FILE__, __LINE__,a,b,c,d,e,f);
#define tolog7(a,b,c,d,e,f,g)  LogSave2(__FILE__, __LINE__,a,b,c,d,e,f,g);
#define tolog8(a,b,c,d,e,f,g,h)  LogSave2(__FILE__, __LINE__,a,b,c,d,e,f,g,h);
#define tolog9(a,b,c,d,e,f,g,h,i)  LogSave2(__FILE__, __LINE__,a,b,c,d,e,f,g,h,i);

#define iflog(a,b,c) if(a)LogSave2(__FILE__, __LINE__,b,c);
#define iflog2(a,b,c,d) if(a)LogSave2(__FILE__, __LINE__,b,c,d);
#define iflog3(a,b,c,d,e) if(a)LogSave2(__FILE__, __LINE__,b,c,d,e);
#define iflog4(a,b,c,d,e,f) if(a)LogSave2(__FILE__, __LINE__,b,c,d,e,f);
#define iflog5(a,b,c,d,e,f,g) if(a)LogSave2(__FILE__, __LINE__,b,c,d,e,f,g);

#define ifcheck(a,b,c) if(a){LogSave2(__FILE__, __LINE__,b,c);return;}
#define ifcheck2(a,b,c,d) if(a){LogSave2(__FILE__, __LINE__,b,c,d);return;}
#define ifcheck3(a,b,c,d,e) if(a){LogSave2(__FILE__, __LINE__,b,c,d,e);return;}
#define ifcheck4(a,b,c,d,e,f) if(a){LogSave2(__FILE__, __LINE__,b,c,d,e,f);return;}
#define ifcheck5(a,b,c,d,e,f,g) if(a){LogSave2(__FILE__, __LINE__,b,c,d,e,f,g);return;}

#define ifcheckf(a,b,c) if(a){LogSave2(__FILE__, __LINE__,b,c);return 0;}
#define ifcheckf2(a,b,c,d) if(a){LogSave2(__FILE__, __LINE__,b,c,d);return 0;}
#define ifcheckf3(a,b,c,d,e) if(a){LogSave2(__FILE__, __LINE__,b,c,d,e);return 0;}
#define ifcheckf4(a,b,c,d,e,f) if(a){LogSave2(__FILE__, __LINE__,b,c,d,e,f);return 0;}
#define ifcheckf5(a,b,c,d,e,f,g) if(a){LogSave2(__FILE__, __LINE__,b,c,d,e,f,g);return 0;}


#define ifchkfail(a,b,c) if(!(a)){LogSave2(__FILE__, __LINE__,b,c);return;}
#define ifchkfail2(a,b,c,d) if(!(a)){LogSave2(__FILE__, __LINE__,b,c,d);return;}
#define ifchkfail3(a,b,c,d,e) if(!(a)){LogSave2(__FILE__, __LINE__,b,c,d,e);return;}
#define ifchkfail4(a,b,c,d,e,f) if(!(a)){LogSave2(__FILE__, __LINE__,b,c,d,e,f);return;}
#define ifchkfail5(a,b,c,d,e,f,g) if(!(a)){LogSave2(__FILE__, __LINE__,b,c,d,e,f,g);return;}
#define ifchkfail6(a,b,c,d,e,f,g,h) if(!(a)){LogSave2(__FILE__, __LINE__,b,c,d,e,f,g,h);return;}
#define ifchkfail7(a,b,c,d,e,f,g,h,i) if(!(a)){LogSave2(__FILE__, __LINE__,b,c,d,e,f,g,h,i);return;}

#define ifchkfailf(a,b,c) if(!(a)){LogSave2(__FILE__, __LINE__,b,c);return 0;}
#define ifchkfailf2(a,b,c,d) if(!(a)){LogSave2(__FILE__, __LINE__,b,c,d);return 0;}
#define ifchkfailf3(a,b,c,d,e) if(!(a)){LogSave2(__FILE__, __LINE__,b,c,d,e);return 0;}
#define ifchkfailf4(a,b,c,d,e,f) if(!(a)){LogSave2(__FILE__, __LINE__,b,c,d,e,f);return 0;}
#define ifchkfailf5(a,b,c,d,e,f,g) if(!(a)){LogSave2(__FILE__, __LINE__,b,c,d,e,f,g);return 0;}
#define ifchkfailf6(a,b,c,d,e,f,g,h) if(!(a)){LogSave2(__FILE__, __LINE__,b,c,d,e,f,g,h);return 0;}
#define ifchkfailf7(a,b,c,d,e,f,g,h,i) if(!(a)){LogSave2(__FILE__, __LINE__,b,c,d,e,f,g,h,i);return 0;}


#endif	// LOGFILE_H
