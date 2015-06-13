// MyRecordset.cpp: implementation of the CMyRecordset class.
//
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
#include "common.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// 构建 UpdateSQLs

MYHEAP_IMPLEMENTATION(CMyRecordset,s_heap)
///////////////////////////////////////////////////////////////////////
void CMyRecordset::BuildUpdateCondition()
{
	switch ( m_nEditMode )
	{	
	case modeEdit:
		sprintf(m_szUpdateCondition, "%s=%s", m_szKey, m_Row[m_uiKeyIndex]);
		break;
	case modeAddNew:
	case modeDelete:
		sprintf(m_szUpdateCondition, "%s=%I64d", m_szKey, m_objFields[m_uiKeyIndex].m_i64Val);
		break;
	}
}

///////////////////////////////////////////////////////////////////////
void CMyRecordset::BuildUpdateOpration()
{
	char szFormat[2048] = "";

	m_strUpdateOpration.clear();

	BOOL bFirst = true;
	BOOL bFlag = true;
	
	switch ( m_nEditMode )
	{	
	case modeEdit:
	case modeAddNew:
		for (UINT i=0; i<m_uiFieldsCount; i++ )
		{	
			if ( m_pbDirty[i] )
			{
				switch (m_objFields[i].m_ulType)
				{
				case FIELD_TYPE_STRING:
				case FIELD_TYPE_VAR_STRING:
					if ((m_Fields[i].flags&NOT_NULL_FLAG)  && strlen(m_objFields[i].m_szVal) == NULL) 
						bFlag = false;
					else 
						sprintf(szFormat, "='%s'",m_objFields[i].m_szVal);
					break;

				case FIELD_TYPE_TINY:
				case FIELD_TYPE_SHORT:
					sprintf(szFormat, "=%d",m_objFields[i].m_iVal);
					break;

				case FIELD_TYPE_FLOAT:
					sprintf(szFormat, "=%.2f",m_objFields[i].m_fVal);
					break;

				case FIELD_TYPE_DOUBLE:
					sprintf(szFormat, "=%.2f",m_objFields[i].m_dVal);
					break;

				case FIELD_TYPE_LONG:
					if ((m_Fields[i].flags&UNSIGNED_FLAG) != 0)
						sprintf(szFormat, "=%u", m_objFields[i].m_ulVal);
					else
						sprintf(szFormat, "=%ld", m_objFields[i].m_lVal);
					break;

				case FIELD_TYPE_LONGLONG:
					if ((m_Fields[i].flags&UNSIGNED_FLAG) != 0)
						sprintf(szFormat, "=%I64u", m_objFields[i].m_ulVal);
					else
						sprintf(szFormat, "=%I64d", m_objFields[i].m_lVal);
					break;

				default:
					sprintf(szFormat, "=error");
					::LogSave("Error: unknow type in CMyRecordset::BuildUpdateOpration()");
					break;
				}

				if (bFlag)
				{	
					if (!bFirst)
						m_strUpdateOpration += ",";
					else 
						bFirst = false;

					m_strUpdateOpration += m_Fields[i].name;
					m_strUpdateOpration += szFormat;
					if(m_strUpdateOpration.size() >= 2048)
					{
						::LogSave("ERROR: BuildUpdateOpration() Overflow!!!");
					}
				}
				else
					bFlag	=true;

			} // if ( m_pbDirty[i] )
		} // for ( i=0; i<m_uiFieldsCount; i++ )
		break;
	}
}


///////////////////////////////////////////////////////////////////////
void CMyRecordset::BuildUpdateSQL()
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
	sprintf(szUpdateSQL,psz,m_szTableName,						//paled - SQL_STMT_DELETE的第2个参数为空串
		m_strUpdateOpration.c_str(),m_szUpdateCondition);		//paled - SQL_STMT_INSERT只有两个参数，将丢弃第3个参数
	m_strUpdateSQL = szUpdateSQL;
	if (m_strUpdateSQL.size() >= 2048)
	{
		::LogSave("ERROR: BuildUpdateSQL() Overflow!!!");
	}
}

///////////////////////////////////////////////////////////////////////
bool CMyRecordset::Update()
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
CMyField * CMyRecordset::GetFieldRef(UINT uiIndex)
{
	return m_objFields+uiIndex;
}

///////////////////////////////////////////////////////////////////////
void CMyRecordset::GetAllField()		//paled - 将ROW中的串转换为数，并填入objField的VAL联合中。
{
	if(m_Row)
	{
		for(int i = 0; i < FieldsCount(); i++)
		{
			if ( m_ulRowsCount ==0) return;
			if (m_Row[i] == 0)
			{	
				m_objFields[i].m_lVal = 0;
				tolog3("*****the column %s of talbe %s is null!*****", m_objFields[i].m_Field.name, m_objFields[i].m_Field.table);
				return;
			}
			switch (m_objFields[i].m_ulType)
			{	
			case	FIELD_TYPE_TINY:
			case	FIELD_TYPE_SHORT:
				m_objFields[i].m_iVal = atoi(m_Row[i]);
				break;
			case	FIELD_TYPE_LONG:
				m_objFields[i].m_lVal = atol(m_Row[i]);
				break;
			case	FIELD_TYPE_FLOAT:
				{
					m_objFields[i].m_fVal = (float)atof(m_Row[i]);
				}
				break;
			case	FIELD_TYPE_DOUBLE:
				{
					m_objFields[i].m_dVal = atof(m_Row[i]);
				}
				break;
			case	FIELD_TYPE_LONGLONG:
				{
					m_objFields[i].m_i64Val = _atoi64(m_Row[i]);
				}
				break;
			case	FIELD_TYPE_DECIMAL:
			case	FIELD_TYPE_NEWDECIMAL:
				{
					m_objFields[i].m_iVal = atoi(m_Row[i]);
				}
				break;
				//////////////////////////////////////////////////////////////////////////
			case	FIELD_TYPE_STRING:
			case	FIELD_TYPE_VAR_STRING:
				strcpy(m_objFields[i].m_szVal,m_Row[i]);
				break;
			}
		}
	}

	ClsEditFlag();
}

///////////////////////////////////////////////////////////////////////
bool CMyRecordset::GetDefauldField(const char* pszTableName)		//paled - 取缺省域值，并填入objField的VAL联合中。
{
	CHECKF(pszTableName);
	CHECKF(SafeCopy(m_szTableName, pszTableName, sizeof(m_szTableName)));
	m_Recordset = mysql_list_fields(m_pMyDatabase->m_hdbc, m_szTableName, NULL);
	if(!m_Recordset)
		return false;

	m_uiFieldsCount = mysql_num_fields(m_Recordset);//返回查询结果中的纪录总数//  [7/23/2007]
	m_ulRowsCount = mysql_num_rows(m_Recordset);//返回查询结果里的纪录总数//  [7/23/2007]
	m_Fields = mysql_fetch_field(m_Recordset);//返回一个MYSQL_FIELD结构：结果字段（数据列）的数据类型。

	m_bIsOpen = true;
	m_objFields = new CMyField [m_uiFieldsCount];
	m_pbDirty = new bool[m_uiFieldsCount];
	ZeroMemory(m_pbDirty, sizeof(bool) * m_uiFieldsCount);



	for(int i = 0; i < FieldsCount(); i++)
	{
		if (m_Fields[i].flags & PRI_KEY_FLAG ||	m_Fields[i].flags & AUTO_INCREMENT_FLAG) 
		{	
			m_bCanUpdate = true;
			strcpy(m_szKey,m_Fields[i].name);
			m_uiKeyIndex = i;
		}

		m_objFields[i].m_Field = m_Fields[i];
		m_objFields[i].m_ulType = m_Fields[i].type;
		char* pszDef = m_objFields[i].m_Field.def;

		switch (m_objFields[i].m_ulType)
		{
		case	FIELD_TYPE_TINY:
		case	FIELD_TYPE_SHORT:
			if(pszDef)
				m_objFields[i].m_iVal = atoi(pszDef);
			else
				m_objFields[i].m_iVal = 0;
			break;
		case	FIELD_TYPE_LONG:
			if(pszDef)
				m_objFields[i].m_lVal = atol(pszDef);
			else
				m_objFields[i].m_lVal = 0;
			break;
		case	FIELD_TYPE_FLOAT:
			if(pszDef)
				m_objFields[i].m_fVal = (float)atof(pszDef);
			else
				m_objFields[i].m_fVal = 0;
			break;
		case	FIELD_TYPE_DOUBLE:
			if(pszDef)
				m_objFields[i].m_dVal = atof(pszDef);
			else
				m_objFields[i].m_dVal = 0;			
			break;
		case	FIELD_TYPE_LONGLONG:// 支持BIGINT字段 [7/23/2007]
			if(pszDef)
				m_objFields[i].m_i64Val = _atoi64(pszDef);
			else
				m_objFields[i].m_i64Val = 0;			
			break;
		case	FIELD_TYPE_DECIMAL:
		case	FIELD_TYPE_NEWDECIMAL:// 支持精度数学DECIMAL或NUMERIC字段 [7/23/2007]
			if(pszDef)
			{
				m_objFields[i].m_dVal = atof(pszDef);
			}
			else
			{
				m_objFields[i].m_dVal = 0;
			}
			break;
		case	FIELD_TYPE_STRING:
		case	FIELD_TYPE_VAR_STRING:
			{
				m_objFields[i].m_szVal = new char[m_Fields[i].length+1];
				ZeroMemory(m_objFields[i].m_szVal, m_Fields[i].length+1);
				if(pszDef)
					strcpy(m_objFields[i].m_szVal, pszDef);
				else
					strcpy(m_objFields[i].m_szVal, "");
			}
			break;
		}
	}

	ClsEditFlag();	
	m_bDefaultValue	= true;
	m_bCanUpdate = true;

	return true;
}	

// 基本操作

///////////////////////////////////////////////////////////////////////
CMyRecordset::CMyRecordset(CMyDatabase  * pMyDatabase )
{
	m_bCanUpdate=false;
	m_nEditMode=0;
	m_bEdit=false;
	m_Fields=NULL;
	m_objFields=NULL;
	m_pbDirty=NULL;
	m_pMyDatabase=NULL;
	SafeCopy(m_szKey,				"", sizeof(m_szKey));
	SafeCopy(m_szTableName,			"", sizeof(m_szTableName));
	SafeCopy(m_szUpdateCondition,	"", sizeof(m_szUpdateCondition));
	m_ulRowsCount=0;
	m_ulCursor=0;
	m_uiFieldsCount=0;
	m_uiKeyIndex=0;
	m_bBOF=false;
	m_bDefaultValue=0;
	m_bEOF=0;
	m_Recordset=NULL;
	m_Row=NULL;
	///-----------------------------------

	m_bIsOpen = false;
	m_bEdit	  = false;

	m_pMyDatabase = pMyDatabase;
	if (pMyDatabase == NULL ) return;
	m_Recordset = NULL;
	
	if (m_pMyDatabase != NULL && m_pMyDatabase->IsOpen())
	{	m_pMyDatabase->m_nRefCount++;
	}
}			//★ 未初始化其它成员变量(其它成员变量由open()初始化)

///////////////////////////////////////////////////////////////////////
CMyRecordset* CMyRecordset::CreateNew(CMyDatabase  * pMyDatabase)
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

	return (new CMyRecordset(pMyDatabase));
}

///////////////////////////////////////////////////////////////////////
bool CMyRecordset::Open(const char * szSQL)
{	
	TimeCostChk("CMyRecordset::Open",szSQL);
	int nstep = 0;
	try 
	{
		if(!m_pMyDatabase)
			return false;
		
		int nLen = strlen(szSQL);
		char * p,* sz= strstr((char*)szSQL, "FROM");
		int nSize = 0;
		if(sz == NULL)
			sz= strstr((char*)szSQL, "from");
		
		if (!m_pMyDatabase->IsOpen())  
		{
			return false;
		}

		MYSQL * hdbc = m_pMyDatabase->m_hdbc;

		if (m_bIsOpen) 
		{	
			Close();
			return false;
		}

		// 数据库性能统计
		CPerformanceStatisticsMS	objPS1(PERFORMANCE_STATISTICS_TYPE_DATABASE_TIME_SUM);
		CPerformanceStatisticsCount objPS2(PERFORMANCE_STATISTICS_TYPE_DATABASE_TIME_COUNT);
		CPerformanceStatisticsMS	objPS3(PERFORMANCE_STATISTICS_TYPE_DATABASE_OPEN_TIME);
		CPerformanceStatisticsCount objPS4(PERFORMANCE_STATISTICS_TYPE_DATABASE_OPEN_COUNT);

		//20070523
		nstep = 1;
		if (mysql_query(hdbc, szSQL)!=NULL)
		{	
			m_pMyDatabase->QueryErrorHandler(szSQL);
			return false;
		}
		else 
		{	
			m_Recordset=mysql_store_result(hdbc);//把所有的结果纪律一次性地全部保存在一个MYSQL_RES结果里//  [7/23/2007]
			if (m_Recordset == NULL)
			{
//				g_nMyDBError = 2002;
				return false;
			}
			else 
			{	
				m_bBOF = false;
				m_bEOF = false;
				m_bIsOpen = true;
				m_bDefaultValue	= false;		// paled

				m_uiFieldsCount = mysql_num_fields(m_Recordset);//返回查询结果中的纪录总数//  [7/23/2007]
				m_ulRowsCount = mysql_num_rows(m_Recordset);//返回查询结果里的纪录总数//  [7/23/2007]
				m_Fields = mysql_fetch_field(m_Recordset);//返回一个MYSQL_FIELD结构：结果字段（数据列）的数据类型。
				
				m_objFields = new CMyField [m_uiFieldsCount];
				m_pbDirty = new bool[m_uiFieldsCount];
				ZeroMemory(m_pbDirty, sizeof(bool) * m_uiFieldsCount);
				

				m_bCanUpdate = false;
				for (UINT i =0; i< m_uiFieldsCount; i++)
				{
					m_objFields[i].m_Field = m_Fields[i];
					m_objFields[i].m_ulType = m_Fields[i].type;

					if (m_objFields[i].m_ulType == FIELD_TYPE_VAR_STRING || m_objFields[i].m_ulType == FIELD_TYPE_STRING )
					{
						m_objFields[i].m_szVal = new char[m_Fields[i].length+1];
						ZeroMemory(m_objFields[i].m_szVal, m_Fields[i].length+1);
						strcpy(m_objFields[i].m_szVal, "");
					}
					
					m_objFields[i].m_pMyField = &m_objFields[i];	//paled
					m_objFields[i].m_nIndex = i;
					if (
						!m_bCanUpdate && (
						m_Fields[i].flags & PRI_KEY_FLAG ||
						m_Fields[i].flags & AUTO_INCREMENT_FLAG ) )
					{	
						m_bCanUpdate = true;
						strcpy(m_szKey,m_Fields[i].name);
						m_uiKeyIndex = i;
					}
				}
				MoveFirst();
				if (sz !=NULL) 
				{	sz = strstr(sz+1," ");
					if ( sz !=NULL )  
					{	p=sz+1;
						sz = strstr(sz+1," ");
						if ( sz == NULL) nSize = nLen -(p-szSQL);
						else nSize = sz - p;
					}
				}
				strncpy(m_szTableName,p,nSize);
				m_szTableName[nSize]='\0';
			}
		}
		return true;
	}
	catch(...)
	{
		m_pMyDatabase->CrashRebuild(szSQL);
		return false;
	}
}

///////////////////////////////////////////////////////////////////////
void CMyRecordset::Close()
{	
	try {
		if (m_bIsOpen)
		{	
			delete [] m_pbDirty;
			for (unsigned int i=0;i<m_uiFieldsCount;i++)
			if (m_objFields[i].m_ulType == FIELD_TYPE_STRING || m_objFields[i].m_ulType == FIELD_TYPE_VAR_STRING)
				delete [] m_objFields[i].m_szVal;

			delete [] m_objFields;
			m_pMyDatabase->m_nRefCount --;
			m_pMyDatabase->DecreaseRef((UINT)this);
		}
		m_bIsOpen = false;
		m_ulRowsCount = 0;
		if (m_Recordset !=NULL)
			mysql_free_result(m_Recordset);
		m_Recordset = NULL;
	}
	catch(...)
	{
		::LogSave("Mysql RecordSet Close Exception Error.");
	}
}

///////////////////////////////////////////////////////////////////////
CMyRecordset::~CMyRecordset()
{
	if (m_bIsOpen) Close();
}


///////////////////////////////////////////////////////////////////////
// 数据集操作
void CMyRecordset::Edit()
{	m_bEdit = true;
	if (! m_bIsOpen ) return;
	m_nEditMode = modeEdit;

}

///////////////////////////////////////////////////////////////////////
void CMyRecordset::AddNew()
{	m_bEdit = true;
	if (! m_bIsOpen ) return;
	m_nEditMode = modeAddNew;
}

///////////////////////////////////////////////////////////////////////
void CMyRecordset::Delete()
{	m_bEdit = true;
	if (! m_bIsOpen ) return;
	m_nEditMode = modeDelete;
}

///////////////////////////////////////////////////////////////////////
// 数据集游标移动
void CMyRecordset::MoveFirst()
{	
	if(m_bEdit)
		::OutputDebugString("*DATABASE* warning: MoveFirst() in edit state.");

	m_bEdit = false;				//★ 有没有先存盘呀？下同
	if (! m_bIsOpen ) return;
	if (!m_bBOF) 
	{	
		m_ulCursor = 0;
		m_bBOF = true;
		CHECK( m_bIsOpen );
		mysql_data_seek(m_Recordset,0);
		m_Row=mysql_fetch_row( m_Recordset );
		GetAllField();
	}
	m_bEOF = false;		//paled - 数据库必须至少有一行数据，下同
}

///////////////////////////////////////////////////////////////////////
void CMyRecordset::MovePrev()
{
	if(m_bEdit)
		::OutputDebugString("*DATABASE* warning: MovePrev() in edit state.");

	m_bEdit = false;
	if (! m_bIsOpen ) return;
	m_bEOF=false;
	if (m_ulCursor > 0)
	{	m_ulCursor -- ;
		mysql_data_seek(m_Recordset,m_ulCursor);
		m_Row=mysql_fetch_row( m_Recordset );
		GetAllField();
	}
	else 
		m_bBOF = true;
}

///////////////////////////////////////////////////////////////////////
void CMyRecordset::MoveLast()
{	
	if(m_bEdit)
		::OutputDebugString("*DATABASE* warning: MoveLast() in edit state.");

	m_bEdit = false;
	if (! m_bIsOpen ) return;
	if (!m_bEOF)
	{	m_ulCursor = m_ulRowsCount-1;
		mysql_data_seek(m_Recordset,m_ulCursor);
		m_Row=mysql_fetch_row( m_Recordset );
		GetAllField();
		m_bBOF = false;
		m_bEOF = true;
	}
}

///////////////////////////////////////////////////////////////////////
void CMyRecordset::Move(ULONG ulIndex)
{	
	if(m_bEdit)
		::OutputDebugString("*DATABASE* warning: Move() in edit state.");

	m_bEdit = false;
	if (! m_bIsOpen ) return;
	if (ulIndex < m_ulRowsCount ) 
	{	mysql_data_seek(m_Recordset,ulIndex);
		m_ulCursor = ulIndex;
		m_Row=mysql_fetch_row( m_Recordset );
		GetAllField();
	}

	m_bBOF = (m_ulCursor == 0);
	m_bEOF = (m_ulCursor == m_ulRowsCount-1);
}


///////////////////////////////////////////////////////////////////////
// SQL
bool CMyRecordset::Query(const char * strSQL, MYSQL_RES * * res)
{
	TimeCostChk("CMyRecordset::Query",strSQL);

	if (!CMyDatabase::CheckSQL(strSQL))
		return false;

	::LogDatabaseSql("[CMyRecordset::Query] %s", strSQL);

	try 
	{
		if (!m_bIsOpen) 
		{
			return false;
		}

		// 数据库性能统计
		CPerformanceStatisticsMS	objPS1(PERFORMANCE_STATISTICS_TYPE_DATABASE_TIME_SUM);
		CPerformanceStatisticsCount objPS2(PERFORMANCE_STATISTICS_TYPE_DATABASE_TIME_COUNT);

		//20070523
		DWORD dwWaitResult = WAIT_OBJECT_0;
		if( WAIT_OBJECT_0 == dwWaitResult)
		{
			MYSQL * hdbc = m_pMyDatabase->m_hdbc;
			if (mysql_query(hdbc, strSQL)!=NULL)
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
		else
		{
			return false;
		}
	}
	catch(...)
	{
		m_pMyDatabase->CrashRebuild(strSQL);
		return false;
	}
}

// 基本属性
///////////////////////////////////////////////////////////////////////
bool CMyRecordset::IsBOF()
{	return m_bBOF;
}

///////////////////////////////////////////////////////////////////////
bool CMyRecordset::IsEOF()
{	return m_bEOF;
}

///////////////////////////////////////////////////////////////////////
bool CMyRecordset::IsOpen()
{
	//CHECKF(this);
	return (m_bIsOpen);
}

///////////////////////////////////////////////////////////////////////
int CMyRecordset::FieldsCount()
{
	if (m_bIsOpen)
		return m_uiFieldsCount;
	else 
		return -1;

}

///////////////////////////////////////////////////////////////////////
bool CMyRecordset::CanUpdate() const     // Can Edit/AddNew/Delete be called?
{	
	if (!m_bIsOpen ) return false; 
	return m_bCanUpdate; 
}

///////////////////////////////////////////////////////////////////////
// 
CMyField CMyRecordset::Fields(UINT uiIndex)
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
CMyField CMyRecordset::Fields(char * szField)
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
		::LogSave("Error: field %s not found in CMyRecordset::Fields", szField);
		return Fields((unsigned int)0);
	}
}

///////////////////////////////////////////////////////////////////////
void CMyRecordset::ClsEditFlag()
{
	for ( int i=0; i<(int)m_uiFieldsCount; i++ )
		m_pbDirty[i] = false;
}

///////////////////////////////////////////////////////////////////////
int CMyRecordset::UpdateFieldsCount()
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
// recordset
///////////////////////////////////////////////////////////////////////
UINT CMyRecordset::RecordCount()		// return -1: error
{
	if (!m_bIsOpen)  return -1;
	return (UINT)m_ulRowsCount;
}

DB_KEY CMyRecordset::GetKey()
{
	CHECKF(m_uiKeyIndex>=0 && m_uiKeyIndex<m_uiFieldsCount);
	return m_objFields[m_uiKeyIndex].m_i64Val;
}

///////////////////////////////////////////////////////////////////////
bool CMyRecordset::MoveNext()
{
	m_bEdit = false;
	if(! m_bIsOpen )
		return false;

	if ( m_ulCursor < m_ulRowsCount-1 )
	{
		m_bBOF = false;

		m_ulCursor ++ ;
		m_Row=mysql_fetch_row( m_Recordset );			//paled - 不必调用 mysql_data_seek()
		GetAllField();

		return true;
	}
	else 
	{
		m_bEOF = true;
		return false;
	}

}

///////////////////////////////////////////////////////////////////////
// record
///////////////////////////////////////////////////////////////////////
IRecord* CMyRecordset::CreateNewRecord(DB_KEY idNewKey /*= NEWKEY_NONE*/) 
{
	CMyRecord* pRecord = CMyRecord::CreateNew(m_pMyDatabase);		//VVVVVVVVVVVVVV
	if(pRecord)
	{
		if(pRecord->Open(this, idNewKey))
			return (IRecord*)pRecord;

		delete pRecord;
	}

	return NULL;
}

///////////////////////////////////////////////////////////////////////
DB_KEY CMyRecordset::InsertRecord(INT nType/* = DBUPDATE_SYNC*/)
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
		::LogDatabaseSql("CMyRecordset::InsertRecord InsertID[%I64d]", key);
		return key;
	}
	else
		return 0;
}

///////////////////////////////////////////////////////////////////////
bool CMyRecordset::UpdateRecord(INT nType/* = DBUPDATE_ASYNC*/)
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
bool CMyRecordset::DeleteRecord(INT nType/* = DBUPDATE_SYNC*/)
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
void CMyRecordset::SetInt		(const char* szField, int nData)
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
int CMyRecordset::GetInt		(int idx)							
{
	IF_NOT(idx>=0 && idx<(int)m_uiFieldsCount) 
	{
		STACK_TRACE_ONCE;
		LogSave("CMyRecordset::GetInt idx[%d] m_uiFieldsCount[%u] tableName[%s]", idx, m_uiFieldsCount, m_szTableName);
		return INT_NONE;
	}

	if (!m_objFields[idx].m_szVal)			// 非串类型
		return m_objFields[idx].m_iVal;
	else 
		return INT_NONE; 
}

int CMyRecordset::GetInt( const char* szField )
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


//----------2007/05/15-----得到DOUBLE型的数据
double CMyRecordset::GetDouble		( int idx )
{
	IF_NOT(idx>=0 && idx<(int)m_uiFieldsCount) 
		return INT_NONE;

	if (!m_objFields[idx].m_szVal)			// 非串类型
		return m_objFields[idx].m_dVal;
	else 
		return DOUBLE_NONE; 
}

I64 CMyRecordset::GetInt64	(int idx)
{
	IF_NOT(idx>=0 && idx<(int)m_uiFieldsCount) 
	return INT_NONE;

	if (!m_objFields[idx].m_szVal)			// 非串类型
		return m_objFields[idx].m_i64Val;
	else 
		return INT64_NONE; 
}

I64 CMyRecordset::GetInt64( const char* szField )
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

	return INT64_NONE;
}

///////////////////////////////////////////////////////////////////////
const char* CMyRecordset::GetStr		(int idx)							
{
	IF_NOT(idx>=0 && idx<(int)m_uiFieldsCount) 
		return STR_NONE;

	if (m_objFields[idx].m_szVal)			// 串类型
		return (m_objFields[idx].m_szVal);
	else 
		return STR_NONE;
}

const char* CMyRecordset::GetStr( const char* szField )
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

///////////////////////////////////////////////////////////////////////
void CMyRecordset::SetInt		(int idx, int nData)				
{
	IF_NOT(idx>=0 && idx<(int)m_uiFieldsCount) 
		return;

	m_pbDirty[idx] = true;
	if (!m_objFields[idx].m_szVal)			// 非串类型
		m_objFields[idx].m_iVal = nData;

	return;
}

///////////////////////////////////////////////////////////////////////
void CMyRecordset::SetStr		(int idx, const char* szData, int nSize)
{
	IF_NOT(idx>=0 && idx<(int)m_uiFieldsCount) 
		return;
	IF_NOT(nSize <= (int)m_Fields[idx].length+1)
		return;

	m_pbDirty[idx] = true;
	if (m_objFields[idx].m_szVal)			// 串类型
		SafeCopy(m_objFields[idx].m_szVal, szData, nSize);

	return;
}

void CMyRecordset::SetStr( const char* szField,const char* szData, int nSize )
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

void CMyRecordset::SetInt64( int idx, I64 i64Data )
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

void CMyRecordset::SetInt64( const char* szField, I64 i64Data )
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

//////////////////////////////////////////////////////////////////////////
bool CMyRecordset::IsString( int idx )
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




