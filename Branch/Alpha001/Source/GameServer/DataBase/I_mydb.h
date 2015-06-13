// 数据库底层的通用接口
// 仙剑修, 2002.9.27
//////////////////////////////////////////////////////////////////


#ifndef	I_MYDB_H
#define	I_MYDB_H

#include "./../COMMON/common.h"
#include "./../COMMON/AutoPtr.h"
#include <vector>
#include <map>
#include <set>

#define PURE_VIRTUAL_DECLARATION_DB		PURE_VIRTUAL_FUNCTION
#define PURE_VIRTUAL_DECLARATION_DB_0	PURE_VIRTUAL_FUNCTION_0

/*
	说明：为兼容旧系统，函数参数尽量与旧系统相同。
*/
enum DBUPDATE_TYPE
{
	DBUPDATE_FALSE = 0,		// 不写库
	DBUPDATE_ASYNC,			// 异步写库
	DBUPDATE_SYNC			// 同步写库
};

class	CMyRecordset;
class	CMyRecord;
class	IRecordset;
class	IDatabase
{
protected:
	virtual ~IDatabase() {}
public:
	virtual IRecordset*	CreateNewRecordset(const char* szSQL)						PURE_VIRTUAL_DECLARATION_DB_0;
	virtual IRecordset* CreateDefaultRecordset(const char* szTableName)				PURE_VIRTUAL_DECLARATION_DB_0;
	virtual	void		Release()													PURE_VIRTUAL_DECLARATION_DB;
public:
	virtual bool	ExecuteSQL	(const char* szSQL, INT nType = DBUPDATE_SYNC)		PURE_VIRTUAL_DECLARATION_DB_0;
	virtual I64		GetInsertId	()													PURE_VIRTUAL_DECLARATION_DB_0;
	virtual int		GetAffectedRows()												PURE_VIRTUAL_DECLARATION_DB_0;
	virtual int		CountRecord	(const char* szSQL)									PURE_VIRTUAL_DECLARATION_DB_0;
	virtual bool	IsOpen()														PURE_VIRTUAL_DECLARATION_DB_0;
	virtual bool    ErrorRecon()													PURE_VIRTUAL_DECLARATION_DB_0;
};

const I64	NEWKEY_NONE	= 9223372036854775807i64;
class	IRecord
{
protected:
	virtual ~IRecord() {}
public:
	virtual IRecord*	CreateNewRecord(DB_KEY idNewKey = NEWKEY_NONE)					PURE_VIRTUAL_DECLARATION_DB_0;
	virtual	void		Release()														PURE_VIRTUAL_DECLARATION_DB;

	virtual DB_KEY		InsertRecord(INT nType = DBUPDATE_SYNC)							PURE_VIRTUAL_DECLARATION_DB_0;
	virtual bool		UpdateRecord(INT nType = DBUPDATE_ASYNC)						PURE_VIRTUAL_DECLARATION_DB_0;
	virtual bool		DeleteRecord(INT nType = DBUPDATE_SYNC)							PURE_VIRTUAL_DECLARATION_DB_0;

	virtual bool		IsString	(int idx)											PURE_VIRTUAL_DECLARATION_DB_0;
	virtual int			GetFieldCount(void)												PURE_VIRTUAL_DECLARATION_DB_0;
	virtual void		ClearUpdateFlags	()											PURE_VIRTUAL_DECLARATION_DB;
	virtual DB_KEY  	GetKey		()													PURE_VIRTUAL_DECLARATION_DB_0;

public:
	virtual	I64			GetInt64	(int idx)											PURE_VIRTUAL_DECLARATION_DB_0;
	virtual I64			GetInt64	(const char* szField)								PURE_VIRTUAL_DECLARATION_DB_0;
	virtual void		SetInt64	(int nIdx,			I64 i64Data)					PURE_VIRTUAL_DECLARATION_DB;
	virtual void		SetInt64	(const char* szField,	I64 i64Data)				PURE_VIRTUAL_DECLARATION_DB;
	virtual double		GetDouble	(int nIdx)											PURE_VIRTUAL_DECLARATION_DB_0;
	virtual int			GetInt		(int nIdx)											PURE_VIRTUAL_DECLARATION_DB_0;
	virtual int     	GetInt		(const char* szField)								PURE_VIRTUAL_DECLARATION_DB_0; 
	virtual	const char*	GetStr		(const char* szField)								PURE_VIRTUAL_DECLARATION_DB_0; 
	virtual const char*	GetStr		(int nIdx)											PURE_VIRTUAL_DECLARATION_DB_0;
	virtual void		SetInt		(int nIdx, int nData)								PURE_VIRTUAL_DECLARATION_DB;
	virtual void		SetInt		(const char* szField, int nData)					PURE_VIRTUAL_DECLARATION_DB;
	virtual void		SetStr		(int nIdx, const char* szData, int nSize)			PURE_VIRTUAL_DECLARATION_DB;
	virtual	void		SetStr		(const char* szField,const char* szData, int nSize)	PURE_VIRTUAL_DECLARATION_DB;
};

class	IRecordset : public IRecord
{
protected:
	virtual ~IRecordset() {}
public:
	virtual UINT		RecordCount()												PURE_VIRTUAL_DECLARATION_DB_0;		// return -1: error
	virtual bool		MoveNext()													PURE_VIRTUAL_DECLARATION_DB_0;		// return false: no more data
	virtual void		MoveFirst()													PURE_VIRTUAL_DECLARATION_DB;		// 
};

typedef TSmartPtr<IRecord>				RecordPtr;
typedef CMyAutoPtr<IRecordset>			RecordsetPtr;

typedef std::vector<DB_KEY>				VEC_DB_KEY;
typedef std::set<DB_KEY>				SET_DB_KEY;
typedef std::deque<DB_KEY>				DEQ_DB_KEY;
typedef std::map<DB_KEY, RecordPtr>		MAP_TABLE_DATA;
typedef MAP_TABLE_DATA::iterator		ITER_TABLE_DATA;
typedef MAP_TABLE_DATA::const_iterator	CITER_TABLE_DATA;

//////////////////////////////////////////////////////////////////////////
extern IDatabase*	CreateDatabase(const char* szDBServer = NULL, const char* szLoginName = NULL, const char* szPassword = NULL, const char* szDBName = NULL/*,const char* szDBCharset = "CHS"*/, const UINT nPort = 0, bool bOpenAyscThread = false);
extern BOOL			ReconnectDatabase(IDatabase* pDb, const char* szDBServer /*= NULL*/, const char* szLoginName /*= NULL*/, const char* szPassword /*= NULL*/, const char* szDBName /*= NULL*/, const UINT nPort = 0);
extern void			CloseDatabaseServer(void);

#endif // I_MYDB_H
