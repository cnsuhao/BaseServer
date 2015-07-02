
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

const int TIMEOUT_ASYNC_PING		= 15;		// ���һ���첽�߳����ӵ�ʱ����
const int MAX_ASYNC_SQL_AMOUNT		= 20000;	// ���������첽sql���, �������ֵʱ�����־, clearʱ�������ֵ����䲻������
const int MYSQL_SERVER_GONE_ERROR	= 2006;		// MySQL server has gone away
const int MAX_RE_CONNECT_SQL_COUNT	= 2000;		// �����첽���ݿⳬʱ, ���¼������ͷ���2000��

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
	void CrashRebuild(LPCSTR sql);///�����ݿ�ײ����ʱ�����ؽ����ݿ����
	void QueryErrorHandler(LPCSTR sql);///��sql��ѯʧ�ܺ���ô���

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
		///�ظ�key�Ĳ����ǲ������,����ط��Ǿ��Բ����ظ��ģ������㷨������
		SQLDEBUGLIST::iterator it=m_sqlDebugList.find(nKey);
		CHECK(it==m_sqlDebugList.end());
		
		m_sqlDebugList[nKey]=szSQL;
	}
	
	void DecreaseRef(UINT nKey)
	{
		///��鳢��ɾ��һ�������ڵļ�¼,���ﲻӦ�ó���
		SQLDEBUGLIST::iterator it=m_sqlDebugList.find(nKey);
		CHECK(it!=m_sqlDebugList.end());
		
		
		m_sqlDebugList.erase(nKey);
	}
	
	///�����ﵼ������δ�����رյļ�¼��sql���
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
	typedef map<UINT,string> SQLDEBUGLIST;///�����������ݿ��ڴ�й¶����
	SQLDEBUGLIST m_sqlDebugList;///����ÿ��ִ�е�SQL���
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
	int		m_nMySQlErrorCode;	//  [2/22/2008 ���]	�������,ֻ�ڳ�OPEN����mysql_real_connect����ʱ����

	// ����һ��ͨ�õ�Connect����
protected:
	MYSQL*			Connect			(const char* szHost, const char* szUser, const char* szPasswd, const char* szDB, 
									 const char* pszInitStmt = NULL, unsigned int uiPort = MYSQL_PORT, char* szSocket = NULL, unsigned int uiFlag = NULL);

	// ����Ϊ�첽sql�߳��������
protected:
	bool	InitAyscThread		(void);	// ��ʼ���첽�߳�
	void	CloseAyscThread		(void);	// �ر��첽�߳�
	bool	ReconnectAsycThread	(void);	// ��������
	bool	CheckAyscConnect	(void);	// ����첽�߳�����, ���Զ�����


	std::string	TakeAsyncSQL	(void);					// [�̰߳�ȫ]��ȡһ���첽sql
	void		PushAsyncSQL	(const char* pszSQL);	// [�̰߳�ȫ]ѹ��һ���첽sql
	void		PushReConnectSQL(const char* pszSQL);	// [�̰߳�ȫ]ѹ��һ���첽sql(�ڶ���ͷ, ���ݿ����Ӳ����쳣��ʹ��)
	void		ClearAsynSQL	(void);					// ���������첽sql
	bool		ProcessAsyncSQL	(void);					// ����һ���첽sql

	bool	IsHaveAyscThread	(void)	const {return m_bHaveAysncThread;}	// �Ƿ����첽�߳�
	INT		GetAsyncSQLAmount	(void)	const {return m_nAsyncSQLAmount;}	// �첽sql��������ȡ

	// �̳�
protected:
	virtual	void	OnInit()	{}
	virtual bool	OnProcess()	;	// �첽�߳�������
	virtual void	OnDestroy() {}

private:
	bool					m_bHaveAysncThread;	// �Ƿ����첽sql�߳�
	MYSQL*					m_hdbcAsyncMySql;	// �첽�߳�mysqlָ��
	INT						m_nAsyncSQLAmount;	// �첽sql�߳��������
	CSimpleCriticalSection	m_csAsync;			// �첽sql�߳��ٽ���
	std::deque<std::string>	m_deqAsyncSQL;		// �첽sql�߳��������
	std::deque<std::string> m_deqReConnectSQL;	// �첽sql�߳�, �������Ӻ�, ��Ҫ������е�sql
	CTimeOut				m_timeoutAysncPing;	// �첽sql�߳�ping������

public:
	MYHEAP_DECLARATION(s_heap)
};


/////////////////////////////////////////////////////////////////////////////
#endif //__MYDB_H__

