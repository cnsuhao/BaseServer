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
		///softworms-������Ϸ�����������ݿ�Ͽ����Ӻ��Զ�����-2007-10-31
		mysql_options(m_hdbc, MYSQL_OPT_RECONNECT,"1");	

//		::LogDatabaseSql("[OpenRecordset] %s", szSQL);

		if(pRes->Open(szSQL))
		{
			// û�м�¼Ҳ����, �����ⲿд��
//			if(pRes->RecordCount())
			{
				///����ڴ�й¶
				IncreaseRef((UINT)pRes,szSQL);
				return (IRecordset*)pRes;
			}
		}
	
		delete pRes;
	}

	return NULL;
}


////////////////////////////////////////////////////////////////////////
// Description: ������Ĭ�ϼ�¼��
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: 
////////////////////////////////////////////////////////////////////////
IRecordset* CMyDatabase::CreateDefaultRecordset( const char* szTableName )
{
	CHECKF(szTableName);
	CMyRecordset* pRes = (CMyRecordset::CreateNew(this)); 
	if (pRes)
	{
		CMxyString strSql("CreateDefaultRecordset[%s]", szTableName);

		// ������־
		::LogDatabaseSql(strSql.c_str());

		if (pRes->GetDefauldField(szTableName))
		{
			///����ڴ�й¶
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
	
	// �첽�߳���ز�����ʼ��
	m_bHaveAysncThread	= false;
	m_hdbcAsyncMySql	= NULL;
	m_nAsyncSQLAmount	= 0;
	m_timeoutAysncPing.Clear();
	m_deqAsyncSQL.clear();
}			//�� δ��ʼ�� m_szDBName��m_bIsConnect��m_hstmt

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

	// update���, ��ҪҪ��where����limit�е�һ��
	if (strstr(szCopySql, "UPDATE"))	
	{
		if (!strstr(szCopySql, "WHERE") && !strstr(szCopySql, "LIMIT"))
		{	
			::LogSave("Invalid update SQL [%s], since not found WHERE or LIMIT.", pszSQL);	// ��¼��־�������ԭװsql, �������
			return false;
		}
	}

	// delete���, ������where
	if (strstr(szCopySql, "DELETE"))	
	{
		if (!strstr(szCopySql, "WHERE"))
		{	
			::LogSave("Invalid SQL delete [%s].", pszSQL);	// ��¼��־�������ԭװsql, �������
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

	this->SetCharset(m_hdbc);	// �����ַ���

	//zeng�����������
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

void CMyDatabase::QueryErrorHandler(LPCSTR sql)///��sql��ѯʧ�ܺ���ô���
{
	DEBUG_TRY
	CHECK(sql);
	LPCSTR szErrInfo=mysql_error(m_hdbc);
	UINT   nErr=mysql_errno(m_hdbc);
	tolog4("exec sql err(%d)!%s:%s",nErr,szErrInfo,sql);
	if(2013==nErr || 2003==nErr || 2006==nErr)///ֻ���ڶ�ʧ���Ӻ������Ϸ�����ʱ�ų�������
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
}					//�� δ��� m_nRefCount

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

		// �첽д��, �ڿ����첽�߳�ʱ��Ч
		if (DBUPDATE_ASYNC == nType && m_bHaveAysncThread)
		{
			this->PushAsyncSQL(szSQL);
			return true;
		}

		::LogDatabaseSql("[ExecuteSyncSql] %s", szSQL);

		// ���ݿ�����ͳ��
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
		::MessageBox(NULL, "���ݿ����openʧ�ܡ�", "Error",MB_OK|MB_ICONERROR);
		bResult = false;
	}

	// �����첽д���߳�
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
//  [1/29/2008 ���]	����
BOOL ReconnectDatabase(IDatabase* pDb, const char* szDBServer /*= NULL*/, const char* szLoginName /*= NULL*/, const char* szPassword /*= NULL*/, const char* szDBName /*= NULL*/, const UINT nPort/* = 0*/)
{
	if(!pDb)
		return NULL;

	if(((CMyDatabase*)pDb)->Reconnect(szDBServer, szLoginName, szPassword, szDBName, nPort))
		return TRUE;

	return FALSE;
}

////////////////////////////////////////////////////////////////////////
// Description:  �ر�mysql
// Arguments:
// Author: ������(Peng Wenqi)
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
// Description:  ͨ�õ����Ӻ���
// Arguments:	pszInitStmtΪ��ʼ������������, �����������Ƕ�Ӧmysql api�ӿڲ���
// Author: ������(Peng Wenqi)
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

	this->SetCharset(hdbc);	// �����ַ���
	
	if (!mysql_real_connect(hdbc, szHost, szUser, szPasswd, szDB, uiPort, szSocket , uiFlag))
	{
		tolog2("CDatabase::Connect error:%s.", mysql_error(hdbc));
		
		mysql_close(hdbc);
		tolog("ERROR: db real connect failed.");
		return NULL;
	}
	
	if (pszInitStmt && strlen(pszInitStmt) > 0)
	{
		if (mysql_real_query(hdbc, pszInitStmt, strlen(pszInitStmt))) //����0��ɹ�
		{
			mysql_close(hdbc);
			tolog("ERROR: db initstatement failed.");
			return NULL;
		}
	}
	
	return hdbc;
}

////////////////////////////////////////////////////////////////////////
// Description:  �첽�߳�Process	��ȡ�첽sql��ִ��
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool CMyDatabase::OnProcess()	
{
	DEBUG_TRY;
	// ��������첽�߳�
	if (!this->IsHaveAyscThread())
	{
		return true;
	}

	// ����첽�߳������Ƿ�����, ���Զ�����
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

	Sleep(1);	// �л�ʱ��Ƭ
	return true;
	DEBUG_CATCH("CMyDatabase::OnProcess");
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description:  ��ʼ���첽�߳�
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool CMyDatabase::InitAyscThread		(void)
{
	CHECKF(this->IsHaveAyscThread());	// ��������첽�߳�

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

	m_timeoutAysncPing.Startup(TIMEOUT_ASYNC_PING);	// ��ʼ��������ӳ�ʱ��

	return true;
}

////////////////////////////////////////////////////////////////////////
// Description:  �ر��첽�߳�
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: None
////////////////////////////////////////////////////////////////////////
void CMyDatabase::CloseAyscThread		(void)
{
	CHECK(this->IsHaveAyscThread());	// ��������첽�߳�

	// �ر��߳�, �����߳�30��
	CHECKB(this->CloseThread(30000));

	// ����ʣ���첽sql
	this->ClearAsynSQL();

	// �ر��첽mysql����
	if (NULL != m_hdbcAsyncMySql)
	{
		mysql_close(m_hdbcAsyncMySql);
		m_hdbcAsyncMySql	= NULL;
	}
}

////////////////////////////////////////////////////////////////////////
// Description:  ��������
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool CMyDatabase::ReconnectAsycThread	(void)
{
	CHECKF(this->IsHaveAyscThread());	// ��������첽�߳�

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

	// �رվɵ�, ��ʹ���µ�
	if (NULL != m_hdbcAsyncMySql)
	{
		mysql_close(m_hdbcAsyncMySql);
		m_hdbcAsyncMySql= NULL;
	}
		
	m_hdbcAsyncMySql = hnew_dbc;
	
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description:  ����첽�߳�����, ���Զ�����
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool CMyDatabase::CheckAyscConnect(void)
{
	CHECKF(this->IsHaveAyscThread());	// ��������첽�߳�

	// δ����һ��ʱ�����
	if (!m_timeoutAysncPing.ToNextTime())
	{
		return true;
	}

	// ������������������Ч����0��������ִ��󣬷��ط�0ֵ�����صķ�0ֵ����ʾMySQL�����������Ƿ��ѹرգ����ӿ���������ԭ���նˣ�����������ȡ�
	if (0 == mysql_ping(m_hdbcAsyncMySql))	
	{
		return true;		
	}

	bool bResult = this->ReconnectAsycThread();
	if (bResult)
	{
		tolog("ERROR: Database ReConnect occur Async mysql OK.");

		// �����첽���ݿ�ɹ���, ִ���������Ӳ��ϵ�һ��sql���
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
// Description:  [�̰߳�ȫ]��ȡ�첽ִ��sql���
// Arguments:
// Author: ������(Peng Wenqi)
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
// Description:  [�̰߳�ȫ]ѹ���첽ִ��sql���
// Arguments:
// Author: ������(Peng Wenqi)
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
// Description:  ѹ���첽����ִ��sql���
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: None
////////////////////////////////////////////////////////////////////////
void CMyDatabase::PushReConnectSQL( const char* pszSQL )
{
	CHECK(pszSQL);
	m_deqReConnectSQL.push_back(pszSQL);
}

////////////////////////////////////////////////////////////////////////
// Description:  �����첽��sql���
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: None
////////////////////////////////////////////////////////////////////////
void CMyDatabase::ClearAsynSQL(void)
{
	// ���ݿ�����ͳ��
	int nRunCount = min(this->GetAsyncSQLAmount(), MAX_ASYNC_SQL_AMOUNT);
	CPerformanceStatisticsMS	objPS1(PERFORMANCE_STATISTICS_TYPE_DATABASE_TIME_SUM);
	CPerformanceStatisticsCount objPS2(PERFORMANCE_STATISTICS_TYPE_DATABASE_TIME_COUNT, nRunCount);
	CPerformanceStatisticsMS	objPS3(PERFORMANCE_STATISTICS_TYPE_DATABASE_TIME_SUM_ASYNC);
	CPerformanceStatisticsCount objPS4(PERFORMANCE_STATISTICS_TYPE_DATABASE_TIME_COUNT_ASYNC, nRunCount);

	int	nCount=0;
	//���������첽sql
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
// Description:  ����һ���첽sql
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool CMyDatabase::ProcessAsyncSQL	(void)
{
	DEBUG_TRY;
	std::string strSQL = this->TakeAsyncSQL();
	TimeCostChk("CMyDatabase::ProcessAsyncSQL", strSQL.c_str());

	// ���ݿ�����ͳ��
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

			// �����첽���ݿ�Ͽ����ӵ�ʱ��, ����������ɹ�ִ�ж���, �����������������
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
// Description:  �����ַ���
// Arguments:
// Author: ������(Peng Wenqi)
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