
#ifndef __MYDB_H__
#define __MYDB_H__

#include "I_mydb.h"
#include "MyHeap.h"
#include <iostream>
#include "map"
#include <deque>
#include <string> 
#include "../Common/ThreadBase.h"
#include "../Common/TimeOut.h"

using namespace std;

const int TIMEOUT_ASYNC_PING		= 15;		// 检查一次异步线程连接的时间间隔
const int MAX_ASYNC_SQL_AMOUNT		= 20000;	// 最多多少条异步sql语句, 超过这个值时会出日志, clear时超过这个值的语句不被保存
const int MYSQL_SERVER_GONE_ERROR	= 2006;		// MySQL server has gone away
const int MAX_RE_CONNECT_SQL_COUNT	= 2000;		// 由于异步数据库超时, 重新加入队列头最多2000次

/////////////////////////////////////////////////////////////////////////////
class CMyDatabase : public IDatabase, protected CThreadBase
{
	// Construct
public:
	CMyDatabase();
	virtual ~CMyDatabase();
public:
	static CMyDatabase*	CreateNew()	{ return new CMyDatabase; }		
protected: 
	virtual	void	Release() { delete this; }			
	virtual IRecordset*	CreateNewRecordset(const char* szSQL);
	virtual IRecordset* CreateDefaultRecordset(const char* szTableName);
public: 
	virtual bool	ExecuteSQL(const char* szSQL, INT nType = DBUPDATE_SYNC);
	virtual I64		GetInsertId();
	virtual int		GetAffectedRows();

	virtual int		CountRecord	(const char* szSQL);
			bool	IsOpen()	{return m_bIsOpen;}
public:
	void CrashRebuild(LPCSTR sql);///在数据库底层崩溃时尝试重建数据库组件
	void QueryErrorHandler(LPCSTR sql);///在sql查询失败后调用处理

	IDatabase*	GetInterface() { return (IDatabase*)this; }

	// Init & Final
	BOOL Init		(const char* szDBServer = NULL, const char* szLoginName = NULL, const char* szPassword = NULL, const char* szDBName = NULL, UINT nPort = 0, bool bOpenAyscThread = false);
	void Destroy	(void);

	static	bool CheckSQL	(const char* pszSQL);

private:
			bool Open(char * szHost, char * szUser, char * szPasswd,char * szDB, 
				unsigned int uiPort = MYSQL_PORT, char * szSocket = NULL, 
				unsigned int uiFlag = NULL);
	virtual void Close();
			void SetCharset(MYSQL* hdbc);

#ifdef MYDEBUG
public:
	void IncreaseRef(UINT nKey,const char* szSQL)
	{
		///重复key的插入是不允许的,这个地方是绝对不会重复的，除非算法有问题
		SQLDEBUGLIST::iterator it=m_sqlDebugList.find(nKey);
		CHECK(it==m_sqlDebugList.end());
		
		m_sqlDebugList[nKey]=szSQL;
	}
	
	void DecreaseRef(UINT nKey)
	{
		///检查尝试删除一个不存在的记录,这里不应该出错
		SQLDEBUGLIST::iterator it=m_sqlDebugList.find(nKey);
		CHECK(it!=m_sqlDebugList.end());
		
		
		m_sqlDebugList.erase(nKey);
	}
	
	///在这里导出所有未正常关闭的记录集sql语句
	void DumpRef()
	{
		UINT nDumpCount=0;
		SQLDEBUGLIST::iterator it=m_sqlDebugList.begin();
		LogSave("CMyDatabase::DumpRef size:%d begin!!!!",m_sqlDebugList.size());
		while(it!=m_sqlDebugList.end())
		{
			LogSave("CMyDatabase::DumpRef(%d):%s",++nDumpCount,it->second.c_str());
			++it;
		}
		m_sqlDebugList.clear();
		LogSave("CMyDatabase::DumpRef end!!!!!");
	}
private:
	typedef map<UINT,string> SQLDEBUGLIST;///用来监视数据库内存泄露问题
	SQLDEBUGLIST m_sqlDebugList;///保存每次执行的SQL语句
#else
public:
	inline void IncreaseRef(UINT nKey,const char* szSQL){}
	inline void DecreaseRef(UINT nKey){}
	inline void DumpRef(){}
#endif

protected:
	MYSQL*	m_hdbc;			
	int		m_nRefCount;

	// friend classes that call protected CMyDatabase overridables
	friend class CMyRecordset;
	friend class CMyRecord;

private:				
	bool 		m_bIsOpen;
	char		m_szDBName[32];

public:
	bool Reconnect(const char* pszDBServer, const char* pszDBUser, const char* pszPassword, const char* pszDBName, UINT nPort = 0);
	bool ErrorRecon();

protected:
	int		m_nMySQlErrorCode;	//  [2/22/2008 朱斌]	错误代码,只在出OPEN调用mysql_real_connect出错时有用

	// 增加一个通用的Connect函数
protected:
	MYSQL*			Connect			(const char* szHost, const char* szUser, const char* szPasswd, const char* szDB, 
									 const char* pszInitStmt = NULL, unsigned int uiPort = MYSQL_PORT, char* szSocket = NULL, unsigned int uiFlag = NULL);

	// 以下为异步sql线程相关内容
protected:
	bool	InitAyscThread		(void);	// 初始化异步线程
	void	CloseAyscThread		(void);	// 关闭异步线程
	bool	ReconnectAsycThread	(void);	// 重新连接
	bool	CheckAyscConnect	(void);	// 检查异步线程连接, 并自动重连


	std::string	TakeAsyncSQL	(void);					// [线程安全]提取一条异步sql
	void		PushAsyncSQL	(const char* pszSQL);	// [线程安全]压入一条异步sql
	void		PushReConnectSQL(const char* pszSQL);	// [线程安全]压入一条异步sql(在队列头, 数据库连接不上异常才使用)
	void		ClearAsynSQL	(void);					// 清理所有异步sql
	bool		ProcessAsyncSQL	(void);					// 处理一条异步sql

	bool	IsHaveAyscThread	(void)	const {return m_bHaveAysncThread;}	// 是否有异步线程
	INT		GetAsyncSQLAmount	(void)	const {return m_nAsyncSQLAmount;}	// 异步sql语句个数提取

	// 继承
protected:
	virtual	void	OnInit()	{}
	virtual bool	OnProcess()	;	// 异步线程主函数
	virtual void	OnDestroy() {}

private:
	bool					m_bHaveAysncThread;	// 是否开启异步sql线程
	MYSQL*					m_hdbcAsyncMySql;	// 异步线程mysql指针
	INT						m_nAsyncSQLAmount;	// 异步sql线程语句数量
	CSimpleCriticalSection	m_csAsync;			// 异步sql线程临界区
	std::deque<std::string>	m_deqAsyncSQL;		// 异步sql线程语句容器
	std::deque<std::string> m_deqReConnectSQL;	// 异步sql线程, 重新连接后, 需要加入队列的sql
	CTimeOut				m_timeoutAysncPing;	// 异步sql线程ping命令间隔

public:
	MYHEAP_DECLARATION(s_heap)
};


/////////////////////////////////////////////////////////////////////////////
#endif //__MYDB_H__

