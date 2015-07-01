// MyRecord.cpp: implementation of the CMyRecord class.
// 仙剑修，2002.9.12
//////////////////////////////////////////////////////////////////////
#ifdef WIN32
#ifndef WINVER 
#define WINVER 0x0501
#endif  
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0501
#endif
#pragma warning(disable:4996)
#endif

#include <winsock2.h>

#include "./../../COMMON/PerformanceStatistics.h"
#include <windows.h>
#include <stdio.h>
#include <time.h>

#include "mydb.h"
#include "basefunc.h"
#include "MyRecord.h"
#include "common.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// 构建 UpdateSQLs

MYHEAP_IMPLEMENTATION(CMyRecord,s_heap)
///////////////////////////////////////////////////////////////////////
bool CMyRecord::FormatField(char* szFormat, const CMyField& objField)
{
	switch (objField.m_ulType)
	{
	case FIELD_TYPE_STRING:
	case FIELD_TYPE_VAR_STRING:
		if ((objField.m_Field.flags&NOT_NULL_FLAG)  && strlen(objField.m_szVal) == NULL)			//paled 不能向数据库写入空串!!!
			return false;
		else 
			sprintf(szFormat, "'%s'",objField.m_szVal);
		break;

	case FIELD_TYPE_TINY:
	case FIELD_TYPE_SHORT:
		sprintf(szFormat, "%d",objField.m_iVal);
		break;

	case FIELD_TYPE_FLOAT:
		sprintf(szFormat, "%.2f",objField.m_fVal);
		break;

	case FIELD_TYPE_DOUBLE:
		sprintf(szFormat, "%.2f",objField.m_dVal);
		break;

	case FIELD_TYPE_LONG:
		if ((objField.m_Field.flags & UNSIGNED_FLAG) != 0)
			sprintf(szFormat, "%u", objField.m_ulVal);
		else
			sprintf(szFormat, "%ld", objField.m_lVal);
		break;

		//  [11/15/2007 朱斌]	增加对BIGINT的支持
	case FIELD_TYPE_LONGLONG:
		sprintf(szFormat, "%I64d",objField.m_i64Val);

//		sprintf(szFormat, "%.0f",objField.m_dVal);
		break;

	default:
		::LogSave("Error: unknow type in CMyRecord::FieldToStr()");
		return false;
	}

	return true;
}

///////////////////////////////////////////////////////////////////////
void CMyRecord::BuildUpdateCondition()
{
	switch ( m_nEditMode )
	{	
	case modeEdit:
		sprintf(m_szUpdateCondition, "%s=%s", m_szKey, m_szKeyData);
		break;
	case modeAddNew:
	case modeDelete:
		sprintf(m_szUpdateCondition, "%s=%I64d", m_szKey, m_objFields[m_uiKeyIndex].m_i64Val);
		break;
	}
}

///////////////////////////////////////////////////////////////////////
void CMyRecord::BuildUpdateOpration()
{
	char szFormat[2048] = "";

	m_strUpdateOpration.clear();

	BOOL bFirst = true;
	
	switch ( m_nEditMode )
	{	
	case modeEdit:
	case modeAddNew:
		for (UINT i=0; i<m_uiFieldsCount; i++ )
		{	
			if ( m_pbDirty[i] )
			{
				if (FormatField(szFormat, m_objFields[i]))
				{	
					if (!bFirst)
						m_strUpdateOpration += ",";
					else 
						bFirst = false;

					m_strUpdateOpration += m_Fields[i].name;
					m_strUpdateOpration += "=";
					m_strUpdateOpration += szFormat;
					if (m_strUpdateOpration.size() >= 2048)
					{
						::LogSave("ERROR: BuildUpdateOpration() Overflow!!!");
					}
				}

			} // if ( m_pbDirty[i] )
		} // for ( i=0; i<m_uiFieldsCount; i++ )
		break;
	}
}


///////////////////////////////////////////////////////////////////////
void CMyRecord::BuildUpdateSQL()
{
	if (!m_bCanUpdate) return;

	BuildUpdateOpration();
	BuildUpdateCondition();

	char * psz = NULL;

	switch (m_nEditMode)
	{
	case modeDelete:
		psz = (char * )SQL_STMT_DELETE;
		break;

	case modeEdit:
		psz = (char * )SQL_STMT_UPDATE;
		break;

	case modeAddNew:
		psz = (char * )SQL_STMT_INSERT;
		break;
	}

	char szUpdateSQL[2048] = "";
	sprintf(szUpdateSQL,psz,m_szTableName,					//paled - SQL_STMT_DELETE的第2个参数为空串
		m_strUpdateOpration.c_str(),m_szUpdateCondition);	//paled - SQL_STMT_INSERT只有两个参数，将丢弃第3个参数
	m_strUpdateSQL = szUpdateSQL;
	if (m_strUpdateSQL.size() >= 2048)
	{
		::LogSave("ERROR: BuildUpdateSQL() Overflow!!!");
	}
}


///////////////////////////////////////////////////////////////////////
bool CMyRecord::Update()
{
	if (!m_bIsOpen) 
		return false;

	m_bEdit = false;

	bool ret	=true;
	if (this->UpdateFieldsCount() > 0)
	{
		// build sql
		this->BuildUpdateSQL();

		// need change the local row;
		MYSQL_RES * res;
		ret = Query(m_strUpdateSQL.c_str(), &res);
		if(ret && res)
			mysql_free_result(res);
	}

	// clear edit flag
	this->ClsEditFlag();

	return	ret;
}


///////////////////////////////////////////////////////////////////////
CMyField * CMyRecord::GetFieldRef(UINT uiIndex)
{
	return m_objFields+uiIndex;
}

///////////////////////////////////////////////////////////////////////
CMyRecord::CMyRecord(CMyDatabase  * pMyDatabase )
{	
	///softwors拼死改底层,将所有没有初始化的成员变量初始化,有锅我来背吧-2007-11-12
	m_bCanUpdate=false;
	m_nEditMode=0;
	m_bEdit=false;
	m_Fields=NULL;
	m_objFields=NULL;
	m_pbDirty=NULL;
	m_pMyDatabase=NULL;
	SafeCopy(m_szKey,				"",	sizeof(m_szKey));
	SafeCopy(m_szKeyData,			"",	sizeof(m_szKeyData));
	SafeCopy(m_szTableName,			"",	sizeof(m_szTableName));
	SafeCopy(m_szUpdateCondition,	"",	sizeof(m_szUpdateCondition));
	m_uiFieldsCount=0;
	m_uiKeyIndex=0;
	///-----------------------------------
	

	m_bIsOpen = false;

	m_pMyDatabase = pMyDatabase;
	if (pMyDatabase == NULL ) return;
	
	if (m_pMyDatabase != NULL && m_pMyDatabase->IsOpen())
	{	
		m_pMyDatabase->m_nRefCount++;
	}
}			//★ 未初始化其它成员变量(其它成员变量由open()初始化)

///////////////////////////////////////////////////////////////////////
CMyRecord* CMyRecord::CreateNew(CMyDatabase  * pMyDatabase)
{
	if (NULL == pMyDatabase)
	{
		return NULL;
	}

	if (false == pMyDatabase->IsOpen())
	{
		pMyDatabase->ErrorRecon();
	}

	if (!pMyDatabase->IsOpen())
	{
		return NULL;
	}

	return (new CMyRecord(pMyDatabase));
}

///////////////////////////////////////////////////////////////////////
bool CMyRecord::Open(CMyRecordset  *pMyRecordset, DB_KEY idNewKey /*= NEWKEY_NONE*/)
{
	if (pMyRecordset == NULL ||	!pMyRecordset->IsOpen())
		return NULL;

	if (!m_pMyDatabase->IsOpen())
		return false;
	if (!( pMyRecordset->IsOpen() && (pMyRecordset->RecordCount() > 0 || pMyRecordset->m_bDefaultValue) ))	// m_bDefaultValue : add by paled
		return false;

	m_uiFieldsCount	= pMyRecordset->m_uiFieldsCount;
	strcpy(m_szKey, pMyRecordset->m_szKey);
	m_uiKeyIndex	= pMyRecordset->m_uiKeyIndex;
	m_bEdit			= pMyRecordset->m_bEdit;
	m_bIsOpen			= pMyRecordset->m_bIsOpen;
	m_nEditMode		= pMyRecordset->m_nEditMode;
	strcpy(m_szTableName, pMyRecordset->m_szTableName); 
	m_bCanUpdate		= pMyRecordset->m_bCanUpdate;

	m_pbDirty = new bool[pMyRecordset->m_uiFieldsCount];
	memset(m_pbDirty, 0, (sizeof(bool) * pMyRecordset->m_uiFieldsCount));

	m_Fields = new MYSQL_FIELD[m_uiFieldsCount];
	int i = 0;
	for(i = 0; i < (int)m_uiFieldsCount; i++)
	{
		m_Fields[i]	= pMyRecordset->m_Fields[i];
		m_Fields[i].name = new char[(strlen(pMyRecordset->m_Fields[i].name)+1)];
		strcpy(m_Fields[i].name, pMyRecordset->m_Fields[i].name);		//VVVVV 注意删除。table、def不复制，从未用到过
	}

	m_objFields		= new CMyField [m_uiFieldsCount];
	for( i = 0; i < (int)m_uiFieldsCount; i++)
	{
		m_objFields[i]		= pMyRecordset->m_objFields[i];
		m_objFields[i].m_Field = m_Fields[i];					// 指向本地name串
		if (m_objFields[i].m_ulType == FIELD_TYPE_VAR_STRING 
				|| m_objFields[i].m_ulType == FIELD_TYPE_STRING)
		{
			m_objFields[i].m_szVal = new char[m_Fields[i].length+1];
			ZeroMemory(m_objFields[i].m_szVal, m_Fields[i].length+1);
			strcpy(m_objFields[i].m_szVal, pMyRecordset->m_objFields[i].m_szVal);
		}
	}

	if(idNewKey != NEWKEY_NONE)
	{
		sprintf(m_szKeyData, "%I64d", idNewKey);
		m_objFields[m_uiKeyIndex].m_i64Val	= idNewKey;
	}
	else
		FormatField(m_szKeyData, pMyRecordset->m_objFields[pMyRecordset->m_uiKeyIndex]);

	return true;
}

///////////////////////////////////////////////////////////////////////
bool CMyRecord::Spawn(CMyRecord *pMyRecord, DB_KEY idNewKey /*= NEWKEY_NONE*/)
{
	*this	= *pMyRecord;

	m_pbDirty = new bool[pMyRecord->m_uiFieldsCount];
	memset(m_pbDirty, true, (sizeof(bool) * pMyRecord->m_uiFieldsCount));

	m_Fields = new MYSQL_FIELD[m_uiFieldsCount];
	int i=0;
	for(i = 0; i < (int)m_uiFieldsCount; i++)
	{
		m_Fields[i]	= pMyRecord->m_Fields[i];
		m_Fields[i].name = new char[(strlen(pMyRecord->m_Fields[i].name)+1)];
		strcpy(m_Fields[i].name, pMyRecord->m_Fields[i].name);		//VVVVV 注意删除。table、def不复制，从未用到过
	}

	m_objFields		= new CMyField [m_uiFieldsCount];
	for( i = 0; i < (int)m_uiFieldsCount; i++)
	{
		m_objFields[i]		= pMyRecord->m_objFields[i];
		m_objFields[i].m_Field	= m_Fields[i];					// 指向本地name串
		if (m_objFields[i].m_ulType == FIELD_TYPE_VAR_STRING 
				|| m_objFields[i].m_ulType == FIELD_TYPE_STRING)
		{
			m_objFields[i].m_szVal = new char[m_Fields[i].length+1];
			ZeroMemory(m_objFields[i].m_szVal, m_Fields[i].length+1);
			strcpy(m_objFields[i].m_szVal, pMyRecord->m_objFields[i].m_szVal);
		}
	}

	if(idNewKey != NEWKEY_NONE)
	{
		sprintf(m_szKeyData, "%u", idNewKey);
		m_objFields[m_uiKeyIndex].m_i64Val	= idNewKey;
	}

	return true;
}

///////////////////////////////////////////////////////////////////////
void CMyRecord::Close()
{	
	try {
		if (m_bIsOpen)
		{	
			delete [] m_pbDirty;
			for (unsigned int i=0;i<m_uiFieldsCount;i++)
			{
				if (m_objFields[i].m_ulType == FIELD_TYPE_STRING 
							|| m_objFields[i].m_ulType == FIELD_TYPE_VAR_STRING)
					delete [] m_objFields[i].m_szVal;

				delete [] m_Fields[i].name;
			}
			delete [] m_objFields;
			delete [] m_Fields;
			m_pMyDatabase->m_nRefCount --;
		}
		m_bIsOpen = false;
	}
	catch(...)
	{
		::LogSave("CMyRecord::Close crash! Mysql RecordSet Close Exception error.");
	}
}

///////////////////////////////////////////////////////////////////////
CMyRecord::~CMyRecord()
{
	if (m_bIsOpen) Close();
}


///////////////////////////////////////////////////////////////////////
// 数据集操作
void CMyRecord::Edit()
{	m_bEdit = true;
	if (! m_bIsOpen ) return;
	m_nEditMode = modeEdit;
}

///////////////////////////////////////////////////////////////////////
void CMyRecord::AddNew()
{	m_bEdit = true;
	if (! m_bIsOpen ) return;
	m_nEditMode = modeAddNew;
}

///////////////////////////////////////////////////////////////////////
void CMyRecord::Delete()
{	m_bEdit = true;
	if (! m_bIsOpen ) return;
	m_nEditMode = modeDelete;
}

///////////////////////////////////////////////////////////////////////
// SQL
bool CMyRecord::Query(const char * strSQL, MYSQL_RES * * res)
{
	TimeCostChk("CMyRecord::Query",strSQL);

	if (!CMyDatabase::CheckSQL(strSQL))
	{
		return false;
	}
	::LogDatabaseSql("[CMyRecord::Query] %s", strSQL);
	
	try 
	{
		if (!m_bIsOpen) 
		{
			return false;
		}

		// 数据库性能统计
		CPerformanceStatisticsMS	objPS1(PERFORMANCE_STATISTICS_TYPE_DATABASE_TIME_SUM);
		CPerformanceStatisticsCount objPS2(PERFORMANCE_STATISTICS_TYPE_DATABASE_TIME_COUNT);

		MYSQL* hdbc = m_pMyDatabase->m_hdbc;
		CHECKF(hdbc);
		if (mysql_query(hdbc, strSQL) != NULL)
		{
			m_pMyDatabase->QueryErrorHandler(strSQL);
			return false;
		}
		else
		{
			*res=mysql_store_result(hdbc);			//paled - 当仅有INSERT、DELETE、UPDATE等查询时，可使用 mysql_affected_rows() 检查是否成功
			if (*res == NULL)
			{
				if (mysql_field_count(hdbc) >0 )
				{
					return false;
				}
				else
				{
					return true;		
				}
			}
			else
			{
				return true;
			}
		}
	}
	catch(...)
	{
		m_pMyDatabase->CrashRebuild(strSQL);
		return false;
	}
}

///////////////////////////////////////////////////////////////////////
bool CMyRecord::IsOpen()
{
	return (m_bIsOpen);
}

///////////////////////////////////////////////////////////////////////
int CMyRecord::FieldsCount()
{
	if (m_bIsOpen)
		return m_uiFieldsCount;
	else 
		return -1;

}

///////////////////////////////////////////////////////////////////////
bool CMyRecord::CanUpdate() const     // Can Edit/AddNew/Delete be called?
{	
	if (!m_bIsOpen ) return false; 
	return m_bCanUpdate; 
}

///////////////////////////////////////////////////////////////////////
// 
CMyField CMyRecord::Fields(UINT uiIndex)
{	
	if (uiIndex >= m_uiFieldsCount) 
	{
		::LogSave("*DATABASE* ERROR: Illegal Fields() parameter[%u].", uiIndex);
		uiIndex=0;			//★ 0号对象是非法对象么?
	}
	
	if (m_bEdit)
	{	m_pbDirty[uiIndex] = true;
		CMyField MyField = m_objFields[uiIndex];
		MyField.m_pMyField = &m_objFields[uiIndex];	//paled
		MyField.m_nIndex = uiIndex;
		MyField.m_szVal = m_objFields[uiIndex].m_szVal;
		return MyField;				//★ BUG: 没有初始化 m_Field 成员变量。没有初始化数值类成员变量
	}

	return m_objFields[uiIndex];
}

///////////////////////////////////////////////////////////////////////
CMyField CMyRecord::Fields(char * szField)
{
	int nIndex = -1 ;
	for (UINT i=0; i < m_uiFieldsCount; i++)
	{	
		if ( stricmp(szField, m_Fields[i].name) == 0)
		{	
			nIndex = i;
			break;
		}
	}

	if (nIndex != -1)	
		return Fields(nIndex);
	else 
	{
		::LogSave("Error: field %s not found in CMyRecord::Fields", szField);
		return Fields((unsigned int)0);				// ★★★ : BUG, 如果是SET调用，会修改第一个字段!!!
	}
}

///////////////////////////////////////////////////////////////////////
void CMyRecord::ClsEditFlag()
{
	for ( int i=0; i<(int)m_uiFieldsCount; i++ )
		m_pbDirty[i] = false;
}

///////////////////////////////////////////////////////////////////////
int CMyRecord::UpdateFieldsCount()
{
	int nCount	=0;
	for ( int i=0; i<(int)m_uiFieldsCount; i++ )
	{
		if (m_pbDirty[i])
			nCount++;
	}

	return nCount;
}

///////////////////////////////////////////////////////////////////////
bool CMyRecord::SetTableName(const char* szName, DB_KEY idNewKey /*= 0*/)
{
	if(!szName || strlen(szName) == 0 || strlen(szName) >= 32)
		return false;

	strcpy(m_szTableName, szName);

	if(idNewKey != 0)
	{
		sprintf(m_szKeyData, "%I64d", idNewKey);
		m_objFields[m_uiKeyIndex].m_i64Val = idNewKey;
	}

	return true;
}

///////////////////////////////////////////////////////////////////////
// record
///////////////////////////////////////////////////////////////////////
IRecord* CMyRecord::CreateNewRecord(DB_KEY idNewKey /*= NEWKEY_NONE*/) 
{
	CMyRecord* pRecord = CMyRecord::CreateNew(m_pMyDatabase);		//VVVVVVVVVVVVVV
	if(pRecord)
	{
		if(pRecord->Spawn(this, idNewKey))
			return (IRecord*)pRecord;

		delete pRecord;
	}

	return NULL;
}

///////////////////////////////////////////////////////////////////////
DB_KEY CMyRecord::InsertRecord(INT nType/* = DBUPDATE_SYNC*/)
{
	if (DBUPDATE_FALSE == nType)
	{
		return 0;
	}

	if (!m_bIsOpen || !m_bCanUpdate)
		return false;

	m_bEdit		= false;
	m_nEditMode	= modeAddNew;

	bool ret	=true;
	if (this->UpdateFieldsCount() > 0)
	{
		// build sql
		this->BuildUpdateSQL();

		// need change the local row;
		MYSQL_RES * res;
		ret = Query(m_strUpdateSQL.c_str(), &res);
		if(ret && res)
			mysql_free_result(res);
	}

	// clear edit flag
	this->ClsEditFlag();

	if(ret)
	{
		I64 key = m_pMyDatabase->GetInsertId();
		if(key != 0)
		{
			m_objFields[m_uiKeyIndex].m_i64Val = key;
		}

		FormatField(m_szKeyData, m_objFields[m_uiKeyIndex]);
		::LogDatabaseSql("CMyRecord::InsertRecord uiKeyIndex[%d], InsertID[%I64d]", m_uiKeyIndex, m_objFields[m_uiKeyIndex].m_i64Val);
		return m_objFields[m_uiKeyIndex].m_i64Val;
	}
	else
		return 0;
}

///////////////////////////////////////////////////////////////////////
bool CMyRecord::UpdateRecord(INT nType/* = DBUPDATE_ASYNC*/)
{
	if (DBUPDATE_FALSE == nType)
	{
		return true;
	}

	if (!m_bIsOpen || !m_bCanUpdate)
		return false;

	m_bEdit		= false;
	m_nEditMode	= modeEdit;

	bool ret	=true;
	if (this->UpdateFieldsCount() > 0)
	{
		// build sql
		this->BuildUpdateSQL();

		// need change the local row;
		if (DBUPDATE_ASYNC == nType)
		{
			ret = m_pMyDatabase->ExecuteSQL(m_strUpdateSQL.c_str(), DBUPDATE_ASYNC);
		}
		else
		{
			MYSQL_RES * res;
			ret = Query(m_strUpdateSQL.c_str(), &res);
			if(ret && res)
				mysql_free_result(res);
		}
	}

	// clear edit flag
	this->ClsEditFlag();

	return	ret;
}

///////////////////////////////////////////////////////////////////////
bool CMyRecord::DeleteRecord(INT nType/* = DBUPDATE_SYNC*/)
{
	if (DBUPDATE_FALSE == nType)
	{
		return false;
	}

	if (!m_bIsOpen || !m_bCanUpdate)
		return false;

	m_bEdit		= false;
	m_nEditMode	= modeDelete;

	bool ret	=true;

	// build sql
	this->BuildUpdateSQL();

	// need change the local row;
	if (DBUPDATE_ASYNC == nType)
	{
		ret = m_pMyDatabase->ExecuteSQL(m_strUpdateSQL.c_str(), DBUPDATE_ASYNC);
	}
	else
	{
		MYSQL_RES * res;
		ret = Query(m_strUpdateSQL.c_str(), &res);
		if(ret && res)
			mysql_free_result(res);
	}

	// clear edit flag
	this->ClsEditFlag();

	return	ret;
}

///////////////////////////////////////////////////////////////////////
void CMyRecord::SetInt		(const char* szField, int nData)
{
	IF_NOT(szField)
		return;

	for (UINT i=0; i < m_uiFieldsCount; i++)
	{	
		if (stricmp(szField, m_Fields[i].name) == 0)
		{
			SetInt(i, nData);
			return;
		}
	}
}

///////////////////////////////////////////////////////////////////////
int CMyRecord::GetInt		(int idx)							
{
	IF_NOT(idx>=0 && idx<(int)m_uiFieldsCount)
	{
		LOGERROR("invalid index[%d] in table [%s].", idx, m_szTableName);
		return INT_NONE;
	}

	if (!m_objFields[idx].m_szVal)			// 非串类型
		return m_objFields[idx].m_iVal;
	else 
		return INT_NONE; 
}

int CMyRecord::GetInt(const char* szField)
{
	IF_NOT(szField)
		return INT_NONE;

	for (UINT i=0; i < m_uiFieldsCount; i++)
	{	
		if (stricmp(szField, m_Fields[i].name) == 0)
		{
			return GetInt(i);
		}
	}

	return INT_NONE;
}

const char* CMyRecord::GetStr(const char* szField)
{
	IF_NOT(szField)
		return STR_NONE;

	for (UINT i=0; i < m_uiFieldsCount; i++)
	{	
		if (stricmp(szField, m_Fields[i].name) == 0)
		{
			return GetStr(i);
		}
	}

	return STR_NONE;
}


void CMyRecord::SetStr(const char* szField,const char* szData, int nSize)
{
	CHECK(szField);

	for (UINT i=0; i < m_uiFieldsCount; i++)
	{	
		if (stricmp(szField, m_Fields[i].name) == 0)
		{
			SetStr(i,szData,nSize);
			break;
		}
	}
}

///////////////////////////////////////////////////////////////////////
const char* CMyRecord::GetStr		(int idx)							
{
	IF_NOT(idx>=0 && idx<(int)m_uiFieldsCount) 
	{
		LOGERROR("invalid index[%d] in table [%s].", idx, m_szTableName);
		return STR_NONE;
	}

	if (m_objFields[idx].m_szVal)			// 串类型
		return (m_objFields[idx].m_szVal);
	else 
		return STR_NONE;
}

///////////////////////////////////////////////////////////////////////
void CMyRecord::SetInt		(int idx, int nData)				
{
	IF_NOT(idx>=0 && idx<(int)m_uiFieldsCount) 
	{
		LOGERROR("Invalid index[%d] in table [%s]", idx, m_szTableName);
		return;
	}

	m_pbDirty[idx] = true;
	if (!m_objFields[idx].m_szVal)			// 非串类型
		m_objFields[idx].m_iVal = nData;

	return;
}

///////////////////////////////////////////////////////////////////////
void CMyRecord::SetStr		(int idx, const char* szData, int nSize)
{
	IF_NOT(idx>=0 && idx<(int)m_uiFieldsCount) 
	{
		LOGERROR("Invalid index[%d] in table [%s]", idx, m_szTableName);
		return;
	}

	IF_NOT(nSize <= (int)m_Fields[idx].length+1)
	{
		LOGERROR("Invalid size[%d] in field[%s] of table [%s]", nSize, m_Fields[idx].name, m_szTableName);
		return;
	}

	m_pbDirty[idx] = true;
	if (m_objFields[idx].m_szVal)			// 串类型
		SafeCopy(m_objFields[idx].m_szVal, szData, nSize);

	return;
}

I64 CMyRecord::GetInt64	(int idx)
{
	IF_NOT(idx>=0 && idx<(int)m_uiFieldsCount)
	{
		LOGERROR("invalid index[%d] in table [%s].", idx, m_szTableName);
		return INT_NONE;
	}

	if (!m_objFields[idx].m_szVal)			// 非串类型
		return m_objFields[idx].m_i64Val;
	else 
		return INT_NONE; 
}

I64	CMyRecord::GetInt64	(const char* szField)
{
	IF_NOT(szField)
		return INT_NONE;

	for (UINT i=0; i < m_uiFieldsCount; i++)
	{	
		if (stricmp(szField, m_Fields[i].name) == 0)
		{
			return GetInt64(i);
		}
	}

	return INT_NONE;
}

DB_KEY CMyRecord::GetKey()
{
	CHECKF(m_uiKeyIndex>=0 && m_uiKeyIndex<m_uiFieldsCount);
	return m_objFields[m_uiKeyIndex].m_i64Val;
}

void	CMyRecord::SetInt64	(int idx, I64 i64Data)
{
	IF_NOT(idx>=0 && idx<(int)m_uiFieldsCount) 
	{
		LOGERROR("Invalid index[%d] in table [%s]", idx, m_szTableName);
		return;
	}

	m_pbDirty[idx] = true;
	if (!m_objFields[idx].m_szVal)			// 非串类型
		m_objFields[idx].m_i64Val = i64Data;

	return;
}

void	CMyRecord::SetInt64	(const char* szField, I64 i64Data)
{
	IF_NOT(szField)
		return;

	for (UINT i=0; i < m_uiFieldsCount; i++)
	{	
		if (stricmp(szField, m_Fields[i].name) == 0)
		{
			SetInt64(i, i64Data);
			return;
		}
	}
}

////////////////////////////////////////////////////////////////////////
// Description: 判断是不是字符串类型字段
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: 
////////////////////////////////////////////////////////////////////////
bool CMyRecord::IsString( int idx )
{
	IF_NOT (idx>=0 && idx<(int)m_uiFieldsCount) 
	{
		tolog3("Invalid index[%d] in table [%s]", idx, m_szTableName);
		return false;
	}

	if (m_objFields[idx].m_szVal)	
	{
		return true;
	}
	else
	{
		return false;
	}
}

double CMyRecord::GetDouble( int idx )
{
	IF_NOT(idx>=0 && idx<(int)m_uiFieldsCount) 
		return INT_NONE;

	if (!m_objFields[idx].m_szVal)			// 非串类型
		return m_objFields[idx].m_dVal;
	else 
		return DOUBLE_NONE; 
}











