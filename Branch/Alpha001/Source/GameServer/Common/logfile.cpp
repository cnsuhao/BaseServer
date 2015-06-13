// 诊断程序
// 仙剑修, 2001.10.10
#ifdef WIN32
#ifndef WINVER 
#define WINVER 0x0501
#endif  
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0501
#endif
#pragma warning(disable:4996)
#endif

#include "logfile.h"
#include "io.h"
#include "BaseFunc.h"
#include "PerformanceStatistics.h"
#include <sstream>
#include <fstream>

#define		BUFSIZE		1024

char		g_szLogTitle[BUFSIZE]		= "Default LogFile Title";
time_t		g_tLogStartServerTime		= 0;

const int EXISTENCE_ONLY = 0x00;
const int FILE_EXISTS	 = 0x00;


CLogThread* CLogThread::s_pInstance = NULL;
////////////////////////////////////////////////////////////////////////
// Description:  构造
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: None
////////////////////////////////////////////////////////////////////////
CLogThread::CLogThread()
{
	m_bOpenServe = false;
	m_nAsyncLogAmount = 0;

	m_hThread		= NULL;
	m_hCloseThreadEvent	= NULL;
	m_nLastReloadPass = 0;
	m_vecPassString.clear();
}

////////////////////////////////////////////////////////////////////////
// Description:  析构
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: None
////////////////////////////////////////////////////////////////////////
CLogThread::~CLogThread()
{
	CThreadBase::~CThreadBase();
}

////////////////////////////////////////////////////////////////////////
// Description:  获得单例指针
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: CLogThread*
////////////////////////////////////////////////////////////////////////
CLogThread* CLogThread::GetInstance(void)
{
	if (NULL == s_pInstance)
	{
		s_pInstance = new CLogThread;
	}
	
	return s_pInstance;
}

////////////////////////////////////////////////////////////////////////
// Description:  清除单例
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: None
////////////////////////////////////////////////////////////////////////
void CLogThread::DelInstance(void)
{
	LOGFUNC_TRY
	if (s_pInstance)
	{
		delete s_pInstance;
	}
	LOGFUNC_CATCH("CLogThread::DelInstance")
}

////////////////////////////////////////////////////////////////////////
// Description:  日志线程线程触发
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: None
////////////////////////////////////////////////////////////////////////
bool CLogThread::OnProcess()
{
	DEBUG_TRY;
	if (!m_bOpenServe)
	{
		return true;
	}

	// 自动重新加载需要过滤的日志段
	this->AutoReloadPass();

	const int nNowAmount = m_nAsyncLogAmount;
	if (nNowAmount > MAX_ASYNC_LOG_AMOUNT)
	{
		char pszWarningBuffer[1024] = "";
		_snprintf(pszWarningBuffer, 1023, "Async Log deque overflow size:%d.", nNowAmount);
		::LogSaveBase(LOGFILE_FILENAME, pszWarningBuffer);
	}
	
	for(int i = 0; i < nNowAmount; i++)
	{
		this->ProcessOneLog();
	}

	Sleep(1);	// 切换时间片
	return true;
	DEBUG_CATCH("CLogThread::OnProcess");
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description:  对外暴露日志入口
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: None
////////////////////////////////////////////////////////////////////////
void CLogThread::LogPrint(const char* pszLogFile, const char* pszLogInfo)
{
	if (NULL == pszLogFile || NULL == pszLogInfo)
	{
		return;
	}

	if (m_bOpenServe)
	{
		this->PushAsyncLog(pszLogFile, pszLogInfo);
	}
	else
	{
		::LogSaveBase(pszLogFile, pszLogInfo);
	}
}


////////////////////////////////////////////////////////////////////////
// Description:  [线程安全]提取异步日志
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: None
////////////////////////////////////////////////////////////////////////
PAIR_LOGINFO CLogThread::TakeAsyncLog(void)
{
	CMySingleLock xLock(&m_csAsync);
	PAIR_LOGINFO pairLogInfo = m_deqAsyncLog.front();
	m_deqAsyncLog.pop_front();
	m_nAsyncLogAmount--;
	return pairLogInfo;
}

////////////////////////////////////////////////////////////////////////
// Description:  [线程安全]压入异步日志
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: None
////////////////////////////////////////////////////////////////////////
void CLogThread::PushAsyncLog(const char* pszLogFile, const char* pszLogInfo)
{
	if (NULL == pszLogFile || NULL == pszLogInfo)
	{
		return;
	}

	CMySingleLock xLock(&m_csAsync);
	m_deqAsyncLog.push_back(make_pair(pszLogFile, pszLogInfo));
	m_nAsyncLogAmount++;
}

////////////////////////////////////////////////////////////////////////
// Description:  清空队列中的日志
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: None
////////////////////////////////////////////////////////////////////////
void CLogThread::ClearAsynLog(void)
{
	int	nCount=0;
	while(m_nAsyncLogAmount > 0)
	{
		if (++nCount > MAX_ASYNC_LOG_AMOUNT)
		{
			break;
		}

		this->ProcessOneLog();
	}
}

////////////////////////////////////////////////////////////////////////
// Description:  处理一条日志
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: None
////////////////////////////////////////////////////////////////////////
void CLogThread::ProcessOneLog(void)
{
	LOGFUNC_TRY;
	PAIR_LOGINFO pairLogInfo = this->TakeAsyncLog();
	// 不打印需要过滤的日志
	if (this->IsPassLog(pairLogInfo.second.c_str()))
	{
		return;
	}

	::LogSaveBase(pairLogInfo.first.c_str(), pairLogInfo.second.c_str());
	LOGFUNC_CATCH("CLogThread::ProcessOneLog");
}

////////////////////////////////////////////////////////////////////////
// Description:  开启日志线程服务
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool CLogThread::StartLogServe(void)
{
	if (m_bOpenServe)
	{
		return false;
	}

	if (!this->CreateThread())
	{
		return false;
	}

	m_bOpenServe = true;
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description:  关闭日志线程服务
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool CLogThread::CloseLogServe(void)
{
	if (!m_bOpenServe)
	{
		return true;
	}

	// 关闭线程, 阻塞线程30秒
	this->CloseThread(30000);

	m_bOpenServe = false;

	// 清理
	this->ClearAsynLog();

	return true;	
}

////////////////////////////////////////////////////////////////////////
// Description:  自动重新加载日志过滤文件
// Arguments:	 3分钟重新加载一次
// Author: 彭文奇(Peng Wenqi)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void CLogThread::AutoReloadPass( void )
{
	DWORD dwNowSecond = ::TimeGet(TIME_SECOND);
	if (dwNowSecond < m_nLastReloadPass + 3 * 60)
	{
		return;
	}
	m_nLastReloadPass = dwNowSecond; 

	const bool bFileExist = FILE_EXISTS == _access("passlog.txt", EXISTENCE_ONLY);
	if (!bFileExist)
	{
		return;
	}
	m_vecPassString.clear();

	std::ifstream infile("passlog.txt", std::ios::in);
	std::string textline;
	int nCount = 0;
	while (std::getline(infile, textline, '\n'))
	{
		// 至少2个字节
		if (textline.size() < 2)
		{
			continue;
		}

		m_vecPassString.push_back(textline);

		// 暂时只允许过滤10条
		nCount++;
		if (nCount > 10)
		{
			break;
		}
	}
	infile.close();
}

////////////////////////////////////////////////////////////////////////
// Description:  是否需要过滤的日志
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool CLogThread::IsPassLog( const char* pszLogInfo )
{
	if (!pszLogInfo)
	{
		return true;
	}

	if (m_vecPassString.empty())
	{
		return false;
	}

	for (std::vector<std::string>::const_iterator iter = m_vecPassString.begin(); iter != m_vecPassString.end(); ++iter)
	{
		if (strstr(pszLogInfo, iter->c_str()) != NULL)
		{
			return true;
		}
	}

	return false;
}


////////////////////////////////////////////////////////////////////////////
// 初始化LOG文件
void InitLog(const char * pTitle, time_t tStart)
{
	if(pTitle)
	{
		wchar_t szUnicode[1024];
		char szUtf8[1024];
		CHECK(::MyANSIToUnicode(pTitle, szUnicode, sizeof(szUnicode) / sizeof(szUnicode[0])));
		CHECK(::MyUnicodeToUTF8(szUnicode, szUtf8, sizeof(szUtf8) / sizeof(szUtf8[0])));

		SafeCopy(g_szLogTitle, szUtf8, sizeof(g_szLogTitle));
	}

	g_tLogStartServerTime = tStart;
}

////////////////////////////////////////////////////////////////////////
// Description:  为日志头信息, 包括utf8头和基础信息
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: None
////////////////////////////////////////////////////////////////////////
void MakeLogFileHeader(const char* pszFileName)
{
	LOGFUNC_TRY
	if (NULL == pszFileName)
	{
		return;
	}

	const bool bFileExist = FILE_EXISTS == _access(pszFileName, EXISTENCE_ONLY);

	// 只有不存在的文件才会去创建utf8头
	if (true == bFileExist)
	{
		return;
	}

	FILE* fp = fopen(pszFileName,"wb");
	if (NULL == fp)
	{
		return;
	}

	// 写utf8文件头
	fwrite(SZ_UTF8_FILE_HEADER, 3, 1, fp);

	// 写日志文件头
	time_t tCurrTime = time(NULL);
	char szLofFileHeaderBuf[4096] = "";	
	char szStartTimeBuf[20] = "";
	char szCurrTimeBuff[20] = "";
	DateTime(szStartTimeBuf, g_tLogStartServerTime);
	DateTime(szCurrTimeBuff, tCurrTime);
	int	nSec = (int)difftime(tCurrTime, g_tLogStartServerTime);
	_snprintf(szLofFileHeaderBuf,4095,	
								"***************************************************************************************************\r\n"
								"*** %s\r\n"
								"*** Log File Name[%s]\r\n"
								"*** Start server time is %s\r\n"
								"***************************************************************************************************\r\n"
								"*** Current time is %s\r\n"
								"*** Server takes %d days  %02d:%02d:%02d\r\n"
								"***************************************************************************************************\r\n"
								, g_szLogTitle
								, pszFileName
								, szStartTimeBuf
								, szCurrTimeBuff
								, nSec / 86400, (nSec/3600)%24, (nSec/60)%60, nSec%60 );
	fputs(szLofFileHeaderBuf, fp);

	fclose(fp);
	LOGFUNC_CATCH("MakeLogFileHeader");
}

////////////////////////////////////////////////////////////////////////
// Description:  所有记录日志的地方, 统一由此将buffer进行转换
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: None
////////////////////////////////////////////////////////////////////////
void GetLogOutputBuffer(OUT char* pszOutputBuffer, IN const char* pszBuffer)
{
	LOGFUNC_TRY
	if (NULL == pszOutputBuffer || NULL == pszBuffer)
	{
		return;
	}
	
	time_t ltime;
	time(&ltime);
	struct tm *pTime = localtime(&ltime); 
	if (NULL == pTime)
	{
		return;
	}
	_snprintf(pszOutputBuffer, 8191, "%s -- %04d-%02d-%02d %02d:%02d:%02d\n", pszBuffer, pTime->tm_year+1900, pTime->tm_mon+1, pTime->tm_mday, pTime->tm_hour, pTime->tm_min, pTime->tm_sec);
	LOGFUNC_CATCH("GetLogOutputBuffer")
}

////////////////////////////////////////////////////////////////////////
// Description:  日志最底层写文件函数
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: None
////////////////////////////////////////////////////////////////////////
void LogSaveBase(const char* pszLogFileName, const char* pszLogInfo)
{
	LOGFUNC_TRY;
	if (FALSE == g_bLogSave)
	{
		return;
	}

	if (NULL == pszLogFileName || NULL == pszLogInfo)
	{
		return;
	}

	time_t ltime;
	time(&ltime);
	struct tm *pTime = localtime(&ltime); 
	if (NULL == pTime)
	{
		return;
	}

	char szLogFullName[256] = "";
	_snprintf(szLogFullName, 255, "%s %04d-%02d-%02d.log", pszLogFileName, pTime->tm_year + 1900, pTime->tm_mon+1, pTime->tm_mday);

	::MakeLogFileHeader(szLogFullName);
	FILE* fp = fopen(szLogFullName, "a+");
	if(NULL == fp)
	{
		return;
	}

	char szOutputBuffer[8192] = "";
	::GetLogOutputBuffer(szOutputBuffer, pszLogInfo);
	fwrite(szOutputBuffer, strlen(szOutputBuffer), 1, fp);

	const int nLogSize = ::ftell(fp);
	fclose(fp);	

	// 超过阀值, 开始分日志
	if (nLogSize >= MAX_LOGFILESIZE)
	{
		char szBackupFile[256] = "";
		_snprintf(szBackupFile, 255, "%s %04d-%02d-%02d.%06u.log", pszLogFileName, pTime->tm_year + 1900, pTime->tm_mon+1, pTime->tm_mday, TimeGet(TIME_DAYTIME));
		rename(szLogFullName, szBackupFile);
	}
	
#ifdef MYDEBUG
	if (strcmp(pszLogFileName, "syslog/PerformanceStatistics") == 0 ||
		strcmp(pszLogFileName, "syslog/MemMonitor") == 0 )
	{
		return;
	}

	wchar_t wszTempStr[8192];
	char	szAnsiStr[8192];
	CHECK(::MyUTF8ToUnicode(szOutputBuffer, wszTempStr, sizeof(wszTempStr) / sizeof(wchar_t)));
	CHECK(::MyUnicodeToANSI(wszTempStr, szAnsiStr, sizeof(szAnsiStr) / sizeof(szAnsiStr[0])));
	OutputDebugString(szAnsiStr);
#endif

	LOGFUNC_CATCH("LogSaveBase");
}


/////////////////////////////////////////////////////////////////////////////
void LogSave (const char* fmt, ...)
{	
	LOGFUNC_TRY
	char buffer[4096]="";
	_vsnprintf( buffer,4095,fmt, (char*) ((&fmt)+1) );
	CLogThread::GetInstance()->LogPrint(LOGFILE_FILENAME, buffer);
	LOGFUNC_CATCH("LogSave");
}

//////////////////////////////////////////////////////////////////////////
void LogSave2(const char* pszSrcFileName, UINT unSrcFileLine, const char* fmt, ...)
{
	LOGFUNC_TRY
 	char buffer[4096]="";
	char temp[4096]="";
	_snprintf(temp, 4095, "%s(%d):%s",pszSrcFileName,unSrcFileLine,fmt);
	_vsnprintf(buffer,4095,temp,(char*) ((&fmt)+1));
	CLogThread::GetInstance()->LogPrint(LOGFILE_FILENAME, buffer);
	LOGFUNC_CATCH("LogSave2");
}

/////////////////////////////////////////////////////////////////////////////
void MyLogSave (const char* pszName, const char* fmt, ...)
{	
	LOGFUNC_TRY
	if (!pszName || !fmt)
		return;
	
	char buffer[4096] = "";
	_vsnprintf(buffer, 4095,fmt, (char*)((&fmt)+1));
	CLogThread::GetInstance()->LogPrint(pszName, buffer);
	LOGFUNC_CATCH("MyLogSave");
}

//////////////////////////////////////////////////////////////////////////
void MyLogSave2 (const char* pszName, const char* fmt, ...)
{	
	LOGFUNC_TRY
	if (!pszName || !fmt)
		return;

	char buffer[4096] = "";
	_vsnprintf(buffer, 4095,fmt, (char*)((&fmt)+1));
	CLogThread::GetInstance()->LogPrint(pszName, buffer);
	LOGFUNC_CATCH("MyLogSave2");
}

//////////////////////////////////////////////////////////////////////////
void Trace(const char* fmt, ...)
{
	if (NULL == fmt)
	{
		return;
	}

	char buffer[4096]="";
	_vsnprintf(buffer, 4095, fmt, (char*)((&fmt)+1));

	char szOutputBuffer[8192] = "";
	GetLogOutputBuffer(szOutputBuffer, buffer);
	OutputDebugString(szOutputBuffer);
}

//////////////////////////////////////////////////////////////////////
void GmLogSave	(const char* fmt, ...)
{
	LOGFUNC_TRY
	char buffer[4096]="";
	_vsnprintf(buffer, 4095, fmt, (char*)((&fmt)+1));
	MyLogSave2("gmlog/gm", buffer);
	LOGFUNC_CATCH("GmLogSave");
}

//////////////////////////////////////////////////////////////////////
// 登入登出日志
void	LogSaveLoginout(const char* fmt, ...)
{
	LOGFUNC_TRY
	char buffer[4096]="";
	_vsnprintf(buffer, 4095, fmt, (char*)((&fmt)+1));
	MyLogSave2("syslog/loginout", buffer);
	LOGFUNC_CATCH("LogSaveLoginout");
}

////////////////////////////////////////////////////////////////////////
// Description:  记录走路日志
// Arguments:	可以通过对话框修改全局变量关闭, 默认是不记录的
// Author: 彭文奇(Peng Wenqi)
// Return Value: None
////////////////////////////////////////////////////////////////////////
void LogWalk(const char* fmt, ...)
{
	LOGFUNC_TRY
	if (FALSE == g_bLogWalk)
	{
		return;
	}

	char buffer[4096]="";
	_vsnprintf(buffer, 4095, fmt, (char*)((&fmt)+1));
	MyLogSave2("syslog/user_walk", buffer);
	LOGFUNC_CATCH("LogWalk");
}

////////////////////////////////////////////////////////////////////////
// Description:  记录卡牌战斗信息
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void LogPokerBattle( const char* fmt, ... )
{
	LOGFUNC_TRY;
	char buffer[4096]="";
	_vsnprintf(buffer, 4095, fmt, (char*)((&fmt)+1));
	MyLogSave2("syslog/poker_battle", buffer);
	LOGFUNC_CATCH("LogPokerBattle");
}


////////////////////////////////////////////////////////////////////////
// Description:  记录数据库执行sql
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: None
////////////////////////////////////////////////////////////////////////
void LogDatabaseSql(const char* fmt, ...)
{
	LOGFUNC_TRY
	if (FALSE == g_bLogDatabaseSql)
	{
		return;
	}

	char buffer[4096]="";
	_vsnprintf(buffer, 4095, fmt, (char*)((&fmt)+1));
	MyLogSave2(DBLOGFILE_FILENAME, buffer);
	LOGFUNC_CATCH("LogDatabaseSql");
}

////////////////////////////////////////////////////////////////////////
// Description:  记录游戏币流向日志
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: None
////////////////////////////////////////////////////////////////////////
void	LogMoney(const char* fmt, ...)
{
	LOGFUNC_TRY
	char buffer[4096]="";
	_vsnprintf(buffer, 4095, fmt, (char*)((&fmt)+1));
	MyLogSave2("gmlog/money", buffer);
	LOGFUNC_CATCH("LogMoney");
}

////////////////////////////////////////////////////////////////////////
// Description:  打印堆栈日志
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: None
////////////////////////////////////////////////////////////////////////
void LogStack(const char* pszSrcFileName, UINT unSrcFileLine, const char* fmt, ...)
{
	LOGFUNC_TRY
	char buffer[4096]="";
	char temp[4096]="";
	_snprintf(temp,4095,"%s(%d):%s",pszSrcFileName,unSrcFileLine,fmt);
	_vsnprintf(buffer,4095,temp,(char*) ((&fmt)+1));
	CLogThread::GetInstance()->LogPrint(LOGFILE_FILENAME, buffer);
	LOGFUNC_CATCH("LogStack")
}

////////////////////////////////////////////////////////////////////////
// Description:  打印堆栈日志(不带行号)
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: None
////////////////////////////////////////////////////////////////////////
void LogStackWithOutLine(const char* fmt, ...)
{
	LOGFUNC_TRY
	char buffer[4096]="";
	_vsnprintf(buffer, 4095, fmt, (char*)((&fmt)+1));
	CLogThread::GetInstance()->LogPrint(LOGFILE_FILENAME, buffer);
	LOGFUNC_CATCH("LogStack")
}


////////////////////////////////////////////////////////////////////////
// Description:  打印超时日志
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: None
////////////////////////////////////////////////////////////////////////
void LogTimeOut(const char* fmt, ...)
{
	LOGFUNC_TRY
	char buffer[4096]="";
	_vsnprintf(buffer, 4095, fmt, (char*)((&fmt)+1));
	MyLogSave2("syslog/time_out", buffer);
	LOGFUNC_CATCH("LogTimeOut")
}

////////////////////////////////////////////////////////////////////////
// Description:  打印脚本错误日志
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: None
////////////////////////////////////////////////////////////////////////
void LogLuaError(const char* fmt, ...)
{
	LOGFUNC_TRY
	char buffer[4096]="";
	_vsnprintf(buffer, 4095, fmt, (char*)((&fmt)+1));
	MyLogSave2("syslog/lua_error", buffer);
	LOGFUNC_CATCH("LogLuaError")	
}

////////////////////////////////////////////////////////////////////////
// Description:  记录内存监视器日志
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: None
////////////////////////////////////////////////////////////////////////
void LogMemMonitor(const char* fmt, ...)
{
	LOGFUNC_TRY	
	char buffer[4096]="";
	_vsnprintf(buffer, 4095, fmt, (char*)((&fmt)+1));
	MyLogSave2("syslog/MemMonitor", buffer);
	LOGFUNC_CATCH("LogMemMonitor");
}

////////////////////////////////////////////////////////////////////////
// Description:  记录充值活动日志
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: None
////////////////////////////////////////////////////////////////////////
void LogPayAward( const char* fmt, ... )
{
	LOGFUNC_TRY	
	char buffer[4096]="";
	_vsnprintf(buffer, 4095, fmt, (char*)((&fmt)+1));
	MyLogSave2("gmlog/PayAward", buffer);
	LOGFUNC_CATCH("LogPayAward");
}

////////////////////////////////////////////////////////////////////////
// Description:  记录速度检测日志
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void LogCheckSpeed( const char* fmt, ... )
{
	LOGFUNC_TRY;
	char buffer[4096]="";
	_vsnprintf(buffer, 4095, fmt, (char*)((&fmt)+1));
	MyLogSave2("syslog/CheckSpeed", buffer);
	LOGFUNC_CATCH("LogCheckSpeed");
}

////////////////////////////////////////////////////////////////////////
// Description:  记录修改名字
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void LogChangeName( const char* fmt, ... )
{
	LOGFUNC_TRY;
	char buffer[4096]="";
	_vsnprintf(buffer, 4095, fmt, (char*)((&fmt)+1));
	MyLogSave2("gmlog/ChangeName", buffer);
	LOGFUNC_CATCH("LogChangeName");
}

////////////////////////////////////////////////////////////////////////
// Description:  卡牌流向日志
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void LogPoker( const char* fmt, ... )
{
	LOGFUNC_TRY;
	char buffer[4096]="";
	_vsnprintf(buffer, 4095, fmt, (char*)((&fmt)+1));
	MyLogSave2("gmlog/Poker", buffer);
	LOGFUNC_CATCH("LogPoker");
}

////////////////////////////////////////////////////////////////////////
// Description:  玩家地图进出信息
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void LogUserMap( const char* fmt, ... )
{
	LOGFUNC_TRY;
	char buffer[4096]="";
	_vsnprintf(buffer, 4095, fmt, (char*)((&fmt)+1));
	MyLogSave2("gmlog/UserMap", buffer);
	LOGFUNC_CATCH("LogUserMap");
}

////////////////////////////////////////////////////////////////////////
// Description:  记录答题系统日志
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void LogQuiz( const char* fmt, ... )
{
	LOGFUNC_TRY;
	char buffer[4096]="";
	_vsnprintf(buffer, 4095, fmt, (char*)((&fmt)+1));
	MyLogSave2("gmlog/Quiz", buffer);
	LOGFUNC_CATCH("LogQuiz");
}

void LogTopList( const char* fmt, ... )
{
	LOGFUNC_TRY;
	char buffer[4096]="";
	_vsnprintf(buffer, 4095, fmt, (char*)((&fmt)+1));
	MyLogSave2("gmlog/toplist", buffer);
	LOGFUNC_CATCH("LogTopList");
}

void LogActivity( const char* fmt, ... )
{
	LOGFUNC_TRY;
	char buffer[4096]="";
	_vsnprintf(buffer, 4095, fmt, (char*)((&fmt)+1));
	MyLogSave2("gmlog/activity", buffer);
	LOGFUNC_CATCH("LogActivity");
}

void LogDeleteItem( const char* fmt, ... )
{
	LOGFUNC_TRY;
	char buffer[4096]="";
	_vsnprintf(buffer, 4095, fmt, (char*)((&fmt)+1));
	MyLogSave2("gmlog/delete_item", buffer);
	LOGFUNC_CATCH("LogDeleteItem");
}

void LogPayReturnVas( const char* fmt, ... )
{
	LOGFUNC_TRY;
	char buffer[4096]="";
	_vsnprintf(buffer, 4095, fmt, (char*)((&fmt)+1));
	MyLogSave2("syslog/payreturn", buffer);
	LOGFUNC_CATCH("LogPayReturnVas");
}

void LogSavePayLog( const char* fmt, ... )
{
	LOGFUNC_TRY;
	char buffer[4096]="";
	_vsnprintf(buffer, 4095, fmt, (char*)((&fmt)+1));
	MyLogSave("syslog/paylog", buffer);
	LOGFUNC_CATCH("LogSavePayLog");
}

////////////////////////////////////////////////////////////////////////
// Description: 竞技场日志
// Arguments:
// Author: 李飞（Li Fei）
// Return Value: 
////////////////////////////////////////////////////////////////////////
void LogSaveArena(const char* fmt, ...)
{
	LOGFUNC_TRY;
	char buffer[4096] = "";
	_vsnprintf(buffer, 4095, fmt, (char*)((&fmt) + 1));
	MyLogSave("syslog/arenalog", buffer);
	LOGFUNC_CATCH("LogSaveArena");
}

