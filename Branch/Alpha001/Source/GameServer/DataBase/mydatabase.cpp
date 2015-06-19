#include <windows.h>
#include <stdio.h>
#include <time.h>
#include "mydb.h"
#include "basefunc.h"
#include "myrecordset.h"
#include "myrecord.h"
#include "IniFile.h"
#include "./../share/define.h"
#include "./../Common//PerformanceStatistics.h"

MYHEAP_IMPLEMENTATION(CMyDatabase, s_heap)
//////////////////////////////////////////////////////////////////////
IRecordset* CMyDatabase::CreateNewRecordset(const char* szSQL) 
{ 
	CMyRecordset* pRes = (CMyRecordset::CreateNew(this)); 
	if(pRes)
	{
		///softworms-加上游戏服务器和数据库断开连接后自动重连-2007-10-31
		mysql_options(m_hdbc, MYSQL_OPT_RECONNECT,"1");	

//		::LogDatabaseSql("[OpenRecordset] %s", szSQL);

		if(pRes->Open(szSQL))
		{
			// 没有记录也返回, 兼容外部写法
//			if(pRes->RecordCount())
			{
				///检查内存泄露
				IncreaseRef((UINT)pRes,szSQL);
				return (IRecordset*)pRes;
			}
		}
	
		delete pRes;
	}

	return NULL;
}


////////////////////////////////////////////////////////////////////////
// Description: 创建表默认记录集
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: 
////////////////////////////////////////////////////////////////////////
IRecordset* CMyDatabase::CreateDefaultRecordset( const char* szTableName )
{
	CHECKF(szTableName);
	CMyRecordset* pRes = (CMyRecordset::CreateNew(this)); 
	if (pRes)
	{
		CMxyString strSql("CreateDefaultRecordset[%s]", szTableName);

		// 读库日志
		::LogDatabaseSql(strSql.c_str());

		if (pRes->GetDefauldField(szTableName))
		{
			///检查内存泄露
			IncreaseRef((UINT)pRes, strSql.c_str());
			return pRes;
		}

		SAFE_DELETE(pRes);
	}
	return NULL;
}


//////////////////////////////////////////////////////////////////////
CMyDatabase::CMyDatabase()
{	
	m_nMySQlErrorCode = 0;
	m_hdbc = NULL;
	m_bIsOpen = FALSE;
	m_nRefCount = 0;
	
	// 异步线程相关参数初始化
	m_bHaveAysncThread	= false;
	m_hdbcAsyncMySql	= NULL;
	m_nAsyncSQLAmount	= 0;
	m_timeoutAysncPing.Clear();
	m_deqAsyncSQL.clear();
}			//★ 未初始化 m_szDBName、m_bIsConnect、m_hstmt

CMyDatabase::~CMyDatabase()
{	
	Destroy();
}

///////////////////////////////////////////////////////////////////////
bool CMyDatabase::CheckSQL(const char* pszSQL)
{
	if (!pszSQL)
		return false;

	char szCopySql[2048] = "";
	::SafeCopy(szCopySql, pszSQL, sizeof(szCopySql));
	::strupr(szCopySql);

// 	if ( !(::strstr(szCopySql, "SELECT") 
// 		|| ::strstr(szCopySql, "UPDATE") 
// 		|| ::strstr(szCopySql, "INSERT") 
// 		|| ::strstr(szCopySql, "DELETE")) )
// 		return false;

	// update语句, 必要要有where或者limit中的一种
	if (strstr(szCopySql, "UPDATE"))	
	{
		if (!strstr(szCopySql, "WHERE") && !strstr(szCopySql, "LIMIT"))
		{	
			::LogSave("Invalid update SQL [%s], since not found WHERE or LIMIT.", pszSQL);	// 记录日志还是输出原装sql, 方便查找
			return false;
		}
	}

	// delete语句, 必须有where
	if (strstr(szCopySql, "DELETE"))	
	{
		if (!strstr(szCopySql, "WHERE"))
		{	
			::LogSave("Invalid SQL delete [%s].", pszSQL);	// 记录日志还是输出原装sql, 方便查找
			return false;
		}
	}

	return true;
}

//////////////////////////////////////////////////////////////////////
bool CMyDatabase::Open(char * szHost, char * szUser, char * szPasswd,char * szDB, 
			unsigned int uiPort, char * szSocket, unsigned int uiFlag )
{	
	if (m_bIsOpen)
	{	
		if (m_nRefCount == 0 )
		{
			Close();
		}
		else 
		{	
			return FALSE;
		}
	}

	m_hdbc = mysql_init(NULL);
	if (m_hdbc == NULL) 
	{
		return FALSE;
	}

	this->SetCharset(m_hdbc);	// 设置字符集

	//zeng添加重连机制
	mysql_options(m_hdbc, MYSQL_OPT_RECONNECT,"1");
	if ( mysql_real_connect(m_hdbc, szHost, szUser, szPasswd, 
			szDB, uiPort, szSocket , uiFlag) == NULL )
	{
		m_nMySQlErrorCode = mysql_errno(m_hdbc);
		LPCSTR szError=mysql_error(m_hdbc);
		return FALSE;
	}
	m_nMySQlErrorCode = 0;
	m_bIsOpen = TRUE;
	return TRUE;
}

void CMyDatabase::QueryErrorHandler(LPCSTR sql)///在sql查询失败后调用处理
{
	DEBUG_TRY
	CHECK(sql);
	LPCSTR szErrInfo=mysql_error(m_hdbc);
	UINT   nErr=mysql_errno(m_hdbc);
	tolog4("exec sql err(%d)!%s:%s",nErr,szErrInfo,sql);
	if(2013==nErr || 2003==nErr || 2006==nErr)///只有在丢失连接和连不上服务器时才尝试重连
	{
		ErrorRecon();
	}
	DEBUG_CATCH("CMyDatabase::QueryErrorHandler() crash!")
}

void CMyDatabase::CrashRebuild(LPCSTR sql)
{
	DEBUG_TRY
	CHECK(sql);
	tolog("mysql crash!we will try to ErrorRecon!")
	m_hdbc=mysql_init(NULL);
	ErrorRecon();
	DEBUG_CATCH("CMyDatabase::Rebuild crash!")
}

//////////////////////////////////////////////////////////////////////
void CMyDatabase::Close()
{	
	if ( m_hdbc != NULL )	
		mysql_close( m_hdbc );
	m_bIsOpen = false;
	m_hdbc = NULL;

	//paled debug
	if(m_nRefCount)
	{
		LogSave("*DATABASE* warning: Found unclosed CRecordset.m_nRefCount:%d",m_nRefCount);
		DumpRef();
	}
}					//★ 未检查 m_nRefCount

//////////////////////////////////////////////////////////////////////
bool CMyDatabase::ExecuteSQL(const char * szSQL, INT nType/* = DBUPDATE_SYNC*/)		//, MYSQL_RES ** pRes
{	
	TimeCostChk("CMyDatabase::ExecuteSQL",szSQL);

	if (!CMyDatabase::CheckSQL(szSQL))
		return false;

	try 
	{
		if (m_hdbc == NULL) 
		{	
			return false;
		}

		// 异步写库, 在开启异步线程时有效
		if (DBUPDATE_ASYNC == nType && m_bHaveAysncThread)
		{
			this->PushAsyncSQL(szSQL);
			return true;
		}

		::LogDatabaseSql("[ExecuteSyncSql] %s", szSQL);

		// 数据库性能统计
		CPerformanceStatisticsMS	objPS1(PERFORMANCE_STATISTICS_TYPE_DATABASE_TIME_SUM);
		CPerformanceStatisticsCount objPS2(PERFORMANCE_STATISTICS_TYPE_DATABASE_TIME_COUNT);
		
		if (mysql_query(m_hdbc, szSQL) != NULL) 
		{	
			this->QueryErrorHandler(szSQL);
			return false;
		}
		else
		{
			MYSQL_RES * pRes=mysql_store_result(m_hdbc);
			if (pRes) 
			{
				mysql_free_result(pRes);	
				::MyLogSave2("syslog/DbError", "CMyDatabase::ExecuteSQL-%s:Have Recordset, Here Release it!",szSQL);
			}
			
			return true;
		}
	}
	catch (...)
	{
		CrashRebuild(szSQL);
		return false;
	}
}

//////////////////////////////////////////////////////////////////////
int	CMyDatabase::CountRecord (const char* szSQL)
{
	if (!szSQL)
		return -1;

	TimeCostChk("CMyDatabase::CountRecord",szSQL);

	if (NULL == strstr(szSQL, "SELECT"))
	{
		::LogSave("Error: invalid count record Sql: %s", szSQL);
		return -1;
	}

	if (m_hdbc == NULL) 
	{	
		return -1;
	}

	char szLog[2048] = "";
	sprintf(szLog,"CMyDatabase::CountRecord:%s",szSQL);

	if (mysql_query(m_hdbc, szSQL) != NULL) 
	{	
		QueryErrorHandler(szSQL);
		return -1;
	}

	MYSQL_RES* res = mysql_store_result(m_hdbc);

	if (res == NULL)
		return -1;
	else
	{
		int rval = (int)mysql_num_rows(res);
		mysql_free_result(res);
		return rval;
	}
}

int CMyDatabase::GetAffectedRows()
{
	if (m_hdbc)
		return (int)mysql_affected_rows(m_hdbc);
	else
		return 0;
}

//////////////////////////////////////////////////////////////////////
I64 CMyDatabase::GetInsertId()
{	
	if (m_hdbc)
		return (I64)mysql_insert_id(m_hdbc);
	else
		return 0;
}

//-----------------------------------------------------end---------------------------------------
BOOL CMyDatabase::Init(const char* pszDBServer, const char* pszDBUser, const char* pszPassword, const char* pszDBName, UINT nPort/* = 0*/, bool bOpenAyscThread/* = false*/)
{
	m_bHaveAysncThread = bOpenAyscThread;
	// init db
	char szDBServer[256], szDBName[256], szDBUser[256], szPassword[256];

	if (pszDBServer)
		strcpy(szDBServer, pszDBServer);
	else
		strcpy(szDBServer,	"127.0.0.1");

	if (pszDBName)
		strcpy(szDBName, pszDBName);
	else
		strcpy(szDBName,	"sk");

	if (pszDBUser)
		strcpy(szDBUser, pszDBUser);
	else
		strcpy(szDBUser,	"wyb");

	if (pszPassword)
		strcpy(szPassword, pszPassword);
	else
		strcpy(szPassword,	"11password22");

	if (0 == nPort)
		nPort = 3306;

	bool bResult = false;
	if(Open(szDBServer, szDBUser, szPassword, szDBName, nPort))
	{
		bResult = true;
	}
	else
	{
		::MessageBox(NULL, "数据库对象open失败。", "Error",MB_OK|MB_ICONERROR);
		bResult = false;
	}

	// 开启异步写库线程
	if (this->IsHaveAyscThread())
	{
		bResult &= this->InitAyscThread();
	}
	
	return bResult;
}

//////////////////////////////////////////////////////////////////////
void CMyDatabase::Destroy	(void)
{
	Close();

	if (this->IsHaveAyscThread())
	{
		this->CloseAyscThread();
	}
}

//////////////////////////////////////////////////////////////////////
IDatabase* CreateDatabase(const char* szDBServer /*= NULL*/, const char* szLoginName /*= NULL*/, const char* szPassword /*= NULL*/, const char* szDBName /*= NULL*/, const UINT nPort/* = 0*/, bool bOpenAyscThread/* = false*/)
{
	CMyDatabase* pDb = CMyDatabase::CreateNew();
	if(!pDb)
		return NULL;;


	if(pDb->Init(szDBServer, szLoginName, szPassword, szDBName, nPort, bOpenAyscThread))
		return pDb->GetInterface();

	delete pDb;
	return NULL;
}


//////////////////////////////////////////////////////////////////////////
//  [1/29/2008 朱斌]	重连
BOOL ReconnectDatabase(IDatabase* pDb, const char* szDBServer /*= NULL*/, const char* szLoginName /*= NULL*/, const char* szPassword /*= NULL*/, const char* szDBName /*= NULL*/, const UINT nPort/* = 0*/)
{
	if(!pDb)
		return NULL;

	if(((CMyDatabase*)pDb)->Reconnect(szDBServer, szLoginName, szPassword, szDBName, nPort))
		return TRUE;

	return FALSE;
}

////////////////////////////////////////////////////////////////////////
// Description:  关闭mysql
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: None
////////////////////////////////////////////////////////////////////////
extern void CloseDatabaseServer( void )
{
	mysql_server_end();
}


bool CMyDatabase::ErrorRecon()
{
	char	szIP[DBSTR_SIZE] = "";
	char	szUser[DBSTR_SIZE] = "";
	char	szPassword[DBSTR_SIZE] = "";
	int		nPort = 0;
	CIniFile	ini(CONFIG_FILENAME, "Database" );
	ini.GetString(szIP,			"DatabaseIP",		DBSTR_SIZE);
	ini.GetString(szUser,		"DatabaseUser",		DBSTR_SIZE);
	ini.GetString(szPassword,	"DatabasePassword",	DBSTR_SIZE);
	nPort = ini.GetInt("DatabasePort");

	BOOL bSuccess	= ::ReconnectDatabase(this, szIP, szUser, szPassword, g_strGameDatabaseName.c_str(), nPort);
	
	if (!bSuccess)
	{
		LOGERROR("Database ReConnect Failed!");
		return false;
	}
	
	return true;
}

bool CMyDatabase::Reconnect(const char* pszDBServer, const char* pszDBUser, const char* pszPassword, const char* pszDBName, UINT nPort/* = 0*/)
{
	// init db
	char szDBServer[256], szDBName[256], szDBUser[256], szPassword[256];

	if (pszDBServer)
		strcpy(szDBServer, pszDBServer);
	else
		strcpy(szDBServer,	"127.0.0.1");

	if (pszDBName)
		strcpy(szDBName, pszDBName);
	else
		strcpy(szDBName,	"wangpudb");

	if (pszDBUser)
		strcpy(szDBUser, pszDBUser);
	else
		strcpy(szDBUser,	"root");

	if (pszPassword)
		strcpy(szPassword, pszPassword);
	else
		strcpy(szPassword,	"test");

	if (0 == nPort)
		nPort = 3306;

	Close();

	if(Open(szDBServer, szDBUser, szPassword, szDBName, nPort))
	{
		return true;
	}
	else
	{
		return false;
	}
}


////////////////////////////////////////////////////////////////////////
// Description:  通用的连接函数
// Arguments:	pszInitStmt为初始化测试语句参数, 其他参数都是对应mysql api接口参数
// Author: 彭文奇(Peng Wenqi)
// Return Value: MYSQL* 
////////////////////////////////////////////////////////////////////////
MYSQL* 
CMyDatabase::Connect(const char* szHost, const char* szUser, const char* szPasswd, const char* szDB, 
				   const char* pszInitStmt, unsigned int uiPort, char* szSocket, unsigned int uiFlag)
{	
	MYSQL* hdbc = mysql_init(NULL);
	if (hdbc == NULL) 
	{	
		tolog("ERROR: db init error.");
		return NULL;
	}

	this->SetCharset(hdbc);	// 设置字符集
	
	if (!mysql_real_connect(hdbc, szHost, szUser, szPasswd, szDB, uiPort, szSocket , uiFlag))
	{
		tolog2("CDatabase::Connect error:%s.", mysql_error(hdbc));
		
		mysql_close(hdbc);
		tolog("ERROR: db real connect failed.");
		return NULL;
	}
	
	if (pszInitStmt && strlen(pszInitStmt) > 0)
	{
		if (mysql_real_query(hdbc, pszInitStmt, strlen(pszInitStmt))) //返回0表成功
		{
			mysql_close(hdbc);
			tolog("ERROR: db initstatement failed.");
			return NULL;
		}
	}
	
	return hdbc;
}

////////////////////////////////////////////////////////////////////////
// Description:  异步线程Process	提取异步sql并执行
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool CMyDatabase::OnProcess()	
{
	DEBUG_TRY;
	// 检查有无异步线程
	if (!this->IsHaveAyscThread())
	{
		return true;
	}

	// 检查异步线程连接是否正常, 并自动重连
	if (!this->CheckAyscConnect())
	{
		return true;
	}

	int nCount = this->GetAsyncSQLAmount();
	if (nCount > MAX_ASYNC_SQL_AMOUNT)
	{
		tolog2("Async db AsyncSQL deque overflow size:%d.", nCount);
	}

	for(int i = 0; i < nCount; i++)
	{
		if(false == this->ProcessAsyncSQL())
		{
			return true;
		}
	}

	Sleep(1);	// 切换时间片
	return true;
	DEBUG_CATCH("CMyDatabase::OnProcess");
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description:  初始化异步线程
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool CMyDatabase::InitAyscThread		(void)
{
	CHECKF(this->IsHaveAyscThread());	// 检查有无异步线程

	char	szIP[DBSTR_SIZE] = "";
	char	szUser[DBSTR_SIZE] = "";
	char	szPassword[DBSTR_SIZE] = "";
	int		nPort = 0;
	CIniFile	ini(CONFIG_FILENAME, "Database" );
	ini.GetString(szIP,			"DatabaseIP",		DBSTR_SIZE);
	ini.GetString(szUser,		"DatabaseUser",		DBSTR_SIZE);
	ini.GetString(szPassword,	"DatabasePassword",	DBSTR_SIZE);
	nPort = ini.GetInt("DatabasePort");

	if (NULL == m_hdbcAsyncMySql)
	{
		m_hdbcAsyncMySql = this->Connect(szIP, szUser, szPassword, g_strGameDatabaseName.c_str(), NULL, nPort);
	}
	CHECKF(m_hdbcAsyncMySql);
	CHECKF(this->CreateThread());

	m_timeoutAysncPing.Startup(TIMEOUT_ASYNC_PING);	// 初始化检查连接超时器

	return true;
}

////////////////////////////////////////////////////////////////////////
// Description:  关闭异步线程
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: None
////////////////////////////////////////////////////////////////////////
void CMyDatabase::CloseAyscThread		(void)
{
	CHECK(this->IsHaveAyscThread());	// 检查有无异步线程

	// 关闭线程, 阻塞线程30秒
	CHECKB(this->CloseThread(30000));

	// 清理剩余异步sql
	this->ClearAsynSQL();

	// 关闭异步mysql连接
	if (NULL != m_hdbcAsyncMySql)
	{
		mysql_close(m_hdbcAsyncMySql);
		m_hdbcAsyncMySql	= NULL;
	}
}

////////////////////////////////////////////////////////////////////////
// Description:  重新连接
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool CMyDatabase::ReconnectAsycThread	(void)
{
	CHECKF(this->IsHaveAyscThread());	// 检查有无异步线程

	char	szIP[DBSTR_SIZE] = "";
	char	szUser[DBSTR_SIZE] = "";
	char	szPassword[DBSTR_SIZE] = "";
	int		nPort = 0;
	CIniFile	ini(CONFIG_FILENAME, "Database" );
	ini.GetString(szIP,			"DatabaseIP",		DBSTR_SIZE);
	ini.GetString(szUser,		"DatabaseUser",		DBSTR_SIZE);
	ini.GetString(szPassword,	"DatabasePassword",	DBSTR_SIZE);
	nPort = ini.GetInt("DatabasePort");

	MYSQL* hnew_dbc = this->Connect(szIP, szUser, szPassword, g_strGameDatabaseName.c_str(), NULL, nPort);
	CHECKF(hnew_dbc);

	// 关闭旧的, 并使用新的
	if (NULL != m_hdbcAsyncMySql)
	{
		mysql_close(m_hdbcAsyncMySql);
		m_hdbcAsyncMySql= NULL;
	}
		
	m_hdbcAsyncMySql = hnew_dbc;
	
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description:  检查异步线程连接, 并自动重连
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool CMyDatabase::CheckAyscConnect(void)
{
	CHECKF(this->IsHaveAyscThread());	// 检查有无异步线程

	// 未到下一个时间检查点
	if (!m_timeoutAysncPing.ToNextTime())
	{
		return true;
	}

	// 如果与服务器的连接有效返回0。如果出现错误，返回非0值。返回的非0值不表示MySQL服务器本身是否已关闭，连接可能因其他原因终端，如网络问题等。
	if (0 == mysql_ping(m_hdbcAsyncMySql))	
	{
		return true;		
	}

	bool bResult = this->ReconnectAsycThread();
	if (bResult)
	{
		tolog("ERROR: Database ReConnect occur Async mysql OK.");

		// 重连异步数据库成功后, 执行由于连接不上的一组sql语句
		if (!m_deqReConnectSQL.empty())
		{
			int nProcessSuccCount = 0;
			for(std::deque<std::string>::const_iterator iter = m_deqReConnectSQL.begin();iter != m_deqReConnectSQL.end(); iter++)
			{
				const std::string& strSQL = *iter;
				if (!strSQL.empty() && this->CheckSQL(strSQL.c_str()))
				{
					if (mysql_real_query(m_hdbcAsyncMySql, strSQL.c_str(), ::strlen(strSQL.c_str())) != 0)
					{
						tolog3("CMyDatabase::CheckAyscConnect Reconnect OK Process SQL error:%s when execute:%s.", mysql_error(m_hdbcAsyncMySql), strSQL.c_str());
					}
					else
					{
						::LogDatabaseSql("[ExecuteReConnectSql] %s", strSQL.c_str());
						nProcessSuccCount++;
					}
				}
			}

			tolog2("CMyDatabase::CheckAyscConnect Reconnect OK Process SQL Success Count[%d]", nProcessSuccCount);
			m_deqReConnectSQL.clear();
		}
		
	}
	else
	{
		tolog("ERROR: Database ReConnect occur Async mysql error.");
	}

	return bResult;
}

////////////////////////////////////////////////////////////////////////
// Description:  [线程安全]提取异步执行sql语句
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: std::string
////////////////////////////////////////////////////////////////////////
std::string	CMyDatabase::TakeAsyncSQL	(void)
{
	CMySingleLock xLock(&m_csAsync);
	
	std::string strSQL;
	strSQL = m_deqAsyncSQL.front();
	m_deqAsyncSQL.pop_front();
	m_nAsyncSQLAmount--;

	return strSQL;
}

////////////////////////////////////////////////////////////////////////
// Description:  [线程安全]压入异步执行sql语句
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: None
////////////////////////////////////////////////////////////////////////
void CMyDatabase::PushAsyncSQL	(const char* pszSQL)
{
	CMySingleLock xLock(&m_csAsync);
	CHECK(pszSQL);
	
	m_deqAsyncSQL.push_back(pszSQL);
	m_nAsyncSQLAmount++;
}

////////////////////////////////////////////////////////////////////////
// Description:  压入异步重连执行sql语句
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: None
////////////////////////////////////////////////////////////////////////
void CMyDatabase::PushReConnectSQL( const char* pszSQL )
{
	CHECK(pszSQL);
	m_deqReConnectSQL.push_back(pszSQL);
}

////////////////////////////////////////////////////////////////////////
// Description:  清理异步的sql语句
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: None
////////////////////////////////////////////////////////////////////////
void CMyDatabase::ClearAsynSQL(void)
{
	// 数据库性能统计
	int nRunCount = min(this->GetAsyncSQLAmount(), MAX_ASYNC_SQL_AMOUNT);
	CPerformanceStatisticsMS	objPS1(PERFORMANCE_STATISTICS_TYPE_DATABASE_TIME_SUM);
	CPerformanceStatisticsCount objPS2(PERFORMANCE_STATISTICS_TYPE_DATABASE_TIME_COUNT, nRunCount);
	CPerformanceStatisticsMS	objPS3(PERFORMANCE_STATISTICS_TYPE_DATABASE_TIME_SUM_ASYNC);
	CPerformanceStatisticsCount objPS4(PERFORMANCE_STATISTICS_TYPE_DATABASE_TIME_COUNT_ASYNC, nRunCount);

	int	nCount=0;
	//处理所有异步sql
	while(this->GetAsyncSQLAmount() > 0)
	{
		DEAD_LOOP_BREAK(nCount, MAX_ASYNC_SQL_AMOUNT);

		std::string strSQL = this->TakeAsyncSQL();	
		if (!strSQL.empty() && this->CheckSQL(strSQL.c_str()))
		{
			if (mysql_real_query(m_hdbcAsyncMySql, strSQL.c_str(), ::strlen(strSQL.c_str())) != 0)
			{
				tolog3("Async db error:%s when execute:%s.", mysql_error(m_hdbcAsyncMySql), strSQL.c_str());
			}
		}
	}
}


////////////////////////////////////////////////////////////////////////
// Description:  处理一条异步sql
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool CMyDatabase::ProcessAsyncSQL	(void)
{
	DEBUG_TRY;
	std::string strSQL = this->TakeAsyncSQL();
	TimeCostChk("CMyDatabase::ProcessAsyncSQL", strSQL.c_str());

	// 数据库性能统计
	CPerformanceStatisticsMS	objPS1(PERFORMANCE_STATISTICS_TYPE_DATABASE_TIME_SUM);
	CPerformanceStatisticsCount objPS2(PERFORMANCE_STATISTICS_TYPE_DATABASE_TIME_COUNT);
	CPerformanceStatisticsMS	objPS3(PERFORMANCE_STATISTICS_TYPE_DATABASE_TIME_SUM_ASYNC);
	CPerformanceStatisticsCount objPS4(PERFORMANCE_STATISTICS_TYPE_DATABASE_TIME_COUNT_ASYNC);
	
	// exe sql
	if (!strSQL.empty() && this->CheckSQL(strSQL.c_str()))
	{
		if (mysql_real_query(m_hdbcAsyncMySql, strSQL.c_str(), ::strlen(strSQL.c_str())) != 0)
		{
			tolog3("CMyDatabase::ProcessAsyncSQL Async db error:%s when execute:%s.", mysql_error(m_hdbcAsyncMySql), strSQL.c_str());

			// 由于异步数据库断开连接的时候, 会加入重连成功执行队列, 超过次数限制则忽略
			const int nReConnectSqlSize = m_deqReConnectSQL.size();
			if (MYSQL_SERVER_GONE_ERROR == mysql_errno(m_hdbcAsyncMySql) && nReConnectSqlSize < MAX_RE_CONNECT_SQL_COUNT)
			{
				this->PushReConnectSQL(strSQL.c_str());
				tolog2("CMyDatabase::ProcessAsyncSQL Async db error:MySQL server has gone away PushReConnectSQL OK! ReConnectSQL Size[%d]", nReConnectSqlSize + 1);
			}
		}
		else
		{
			::LogDatabaseSql("[ExecuteAsyncSql] %s", strSQL.c_str());
		}
	}
	else
	{
		tolog2("CMyDatabase::ProcessAsyncSQL error: strSQL:%s.", strSQL.c_str());
	}
	return true;
	DEBUG_CATCHF("CMyDatabase::ProcessAsyncSQL")
}

////////////////////////////////////////////////////////////////////////
// Description:  设置字符集
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: None
////////////////////////////////////////////////////////////////////////
void CMyDatabase::SetCharset(MYSQL* hdbc)
{
	CHECK(hdbc);
	char	DB_CHARSET[DBSTR_SIZE] = "";
	CIniFile	ini(CONFIG_FILENAME, "Database");
	ini.GetString(DB_CHARSET,	"DatabaseCharset",	DBSTR_SIZE);
	if (!stricmp(DB_CHARSET,"CHT"))
	{
		SafeCopy(DB_CHARSET,"big5", DBSTR_SIZE);
	}
	else if (!stricmp(DB_CHARSET,"ENU"))
	{
		SafeCopy(DB_CHARSET,"latin1", DBSTR_SIZE);
	}
	else if (!stricmp(DB_CHARSET,"UTF8"))
	{
		SafeCopy(DB_CHARSET,"utf8", DBSTR_SIZE);
	}
	else
	{
		SafeCopy(DB_CHARSET,"gbk", DBSTR_SIZE);
	}

	mysql_options(hdbc, MYSQL_SET_CHARSET_NAME, DB_CHARSET);
}