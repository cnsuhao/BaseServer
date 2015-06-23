#ifdef WIN32
#ifndef WINVER 
#define WINVER 0x0501
#endif  
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0501
#endif
#pragma warning(disable:4996)
#endif

#include <windows.h>
#include <stdio.h>

#include "mydb.h"
#include "BaseFunc.h"

MYHEAP_IMPLEMENTATION(CMyField,s_heap)
//////////////////////////////////////////////////////////////////////////////
// Implementation of CMyField

CMyField::CMyField()
{
	// Initialize type and value
	m_ulType = FIELD_TYPE_NULL;
	m_szVal = NULL;
	m_i64Val=0;///softworms-对该变量进行初始化,以便让联合变量为0
}		//★ 未初始化 m_Field,m_nIndex,m_pMyRecordset,m_nNumAllocsInHeap
		//paled - m_pMyRecordset为回指指针，由OWNER对象初始化。m_Field、m_nIndex也是。m_szVal的空间也由OWNER分配.。

void CMyField::Clear()
{

}

CMyField::~CMyField()
{
	//Clear();
}

//////////////////////////////////////////////////////////////////
//	Operator 

CMyField& CMyField::operator = (unsigned char chOp)
{
	if (m_pMyField->m_ulType == FIELD_TYPE_TINY)
		m_pMyField->m_ucVal = chOp;
	return *this;
}

CMyField& CMyField::operator = (char chOp)
{
	if (m_pMyField->m_ulType == FIELD_TYPE_TINY)
		m_pMyField->m_cVal = chOp;
	return *this;
}

CMyField& CMyField::operator = ( int nOp)
{	
	if (m_pMyField->m_ulType == FIELD_TYPE_LONG
			|| m_pMyField->m_ulType == FIELD_TYPE_TINY
			|| m_pMyField->m_ulType == FIELD_TYPE_SHORT
			)
		m_pMyField->m_iVal = nOp;
	return *this;
}

CMyField& CMyField::operator = ( long lOp)
{	
	if (m_pMyField->m_ulType == FIELD_TYPE_LONG
			|| m_pMyField->m_ulType == FIELD_TYPE_TINY
			|| m_pMyField->m_ulType == FIELD_TYPE_SHORT )
		m_pMyField->m_lVal = lOp;
	return *this;
}

CMyField& CMyField::operator = ( float fltOp )
{
	if (m_pMyField->m_ulType == FIELD_TYPE_FLOAT)
		m_pMyField->m_fVal = fltOp;
	return *this;
}

CMyField& CMyField::operator = ( double dbOp )
{
	if (m_pMyField->m_ulType == FIELD_TYPE_DOUBLE) 
		m_pMyField->m_dVal = dbOp;
	return *this;
}

CMyField& CMyField::operator=( _int64 i64Op )
{
	if (m_pMyField->m_ulType == FIELD_TYPE_LONG
		|| m_pMyField->m_ulType == FIELD_TYPE_TINY
		|| m_pMyField->m_ulType == FIELD_TYPE_SHORT 
		|| m_pMyField->m_ulType == FIELD_TYPE_LONGLONG)
		m_pMyField->m_i64Val = i64Op;
	return *this;
}

CMyField& CMyField::operator = ( unsigned long lOp )
{
	if (m_pMyField->m_ulType == FIELD_TYPE_LONG
			|| m_pMyField->m_ulType == FIELD_TYPE_TINY
			|| m_pMyField->m_ulType == FIELD_TYPE_SHORT )
		m_pMyField->m_lVal = lOp;
	return *this;
}


void CMyField::FieldName(char * szFileName)
{	
	strcpy(szFileName, m_Field.name);
}

unsigned int CMyField::FieldLen() const
{	return m_Field.length;
}

unsigned int CMyField::FieldAttr() const
{	return m_Field.flags;
}


void CMyField::CopyFrom(const char * szField, int nLen)			//★ 不应该操作本地变量(结果：字符串指针已回指到CMyRecordset)
{	
	try
	{
		CHECK(szField != NULL);
		memset(m_szVal,0,nLen);
		strncpy(m_szVal, szField, nLen-1);		//★★ 没检查长度超长。丢失了尾0，暂未解决
	}catch(...){ LogSave("*DATABASE* ERROR: CMyField::CopyFrom() illegal access."); }	//paled debug
}

void CMyField::CopyTo(char * szField, int nLen)			//★ 不应该操作本地变量(结果：字符串指针已回指到CMyRecordset)
{	
	try
	{
		CHECK(szField != NULL);
		memset(szField,0,nLen);
		strncpy(szField, m_szVal, nLen-1);		//★★ 没检查长度超长。丢失了尾0，暂未解决
	}catch(...){ LogSave("*DATABASE* ERROR: CMyField::CopyTo() illegal access."); }	//paled debug
}


	CMyField& CMyField::operator = (const char* szVal)
	{	
		try{
			if (m_pMyField->m_ulType == FIELD_TYPE_STRING)		//paled debug
				strcpy(m_pMyField->m_szVal ,szVal);		//★★ BUG: 长度可能溢出，暂未解决
		}catch(...){				//paled debug
			LogSave("*DATABASE* ERROR: CMyField::operator char*() illegal access."); 
		}
		return *this;
	}




