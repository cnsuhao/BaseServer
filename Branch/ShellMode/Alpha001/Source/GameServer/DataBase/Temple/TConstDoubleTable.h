////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2013, WuHan ChuangYou, All Rights Reserved
// Moudle: TConstDoubleTable.h
// Author: 彭文奇(Peng Wenqi)
// Created: 2013-4-17
////////////////////////////////////////////////////////////////////////
#ifndef _GAME_BASECODE_MT_CONST_DOUBLE_TABLE_H_
#define _GAME_BASECODE_MT_CONST_DOUBLE_TABLE_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning(disable:4786)
#include "./../I_mydb.h"

typedef std::vector<int>					VEC_CONST_TABLE_KEY;
typedef VEC_CONST_TABLE_KEY::iterator		ITER_VEC_CONST_TABLE_KEY;
typedef VEC_CONST_TABLE_KEY::const_iterator	CITER_VEC_CONST_TABLE_KEY;

template<class DataEnum>
class TConstDoubleTable
{
public:
	TConstDoubleTable()
	{
		ZeroMemory(m_szTableName, sizeof(m_szTableName));
		ZeroMemory(m_szLoadSql, sizeof(m_szLoadSql));
		m_pDB = NULL;
		m_nKeyIndex1 = -1;
		m_nKeyIndex2 = -1;
	}

	~TConstDoubleTable()	
	{
		this->Release();
	}

public:
	bool		Init		(IDatabase* pDB, const char* pszConstTableName, int nKeyIndex1, int nKeyIndex2);
	bool		InitCustom	(IDatabase* pDB, const char* pszConstTableName, int nKeyIndex1, int nKeyIndex2, const char* pszCustomSql);
	void		Release		(void);
	bool		Reload		(void);
	
public:
	bool		IsExist			(int nKeyValue1, int nKeyValue2) const;
	I64			GetData			(int nKeyValue1, int nKeyValue2, DataEnum eDataEnum) const;
	const char*	GetDataStr		(int nKeyValue1, int nKeyValue2, DataEnum eDataEnum) const;
	void		EnumKey1ByData	(OUT VEC_CONST_TABLE_KEY& rVecKey1, I64 i64Data, DataEnum eDataEnum) const;
	void		EnumKey2ByData	(OUT VEC_CONST_TABLE_KEY& rVecKey2, I64 i64Data, DataEnum eDataEnum) const;
	void		GetDoubleKey	(IN DB_KEY dbKey, OUT int& nKeyValue1, OUT int& nKeyValue2) const;
	bool		EnumKey			(OUT VEC_DB_KEY& rVecKey) const;
	int			GetSize			(void) const;

private:
	DB_KEY		MakeKey		(int nKeyValue1, int nKeyValue2) const;

private:
	char			m_szTableName[64];
	char			m_szLoadSql[256];
	int				m_nKeyIndex1;
	int				m_nKeyIndex2;
	MAP_TABLE_DATA	m_mapData;
	IDatabase*		m_pDB;
};

////////////////////////////////////////////////////////////////////////
// Description:  枚举单键常量表key的vector
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
template<class DataEnum>
bool TConstDoubleTable<DataEnum>::EnumKey( OUT VEC_DB_KEY& rVecKey ) const
{
	DEBUG_TRY;
	rVecKey.clear();
	for (CITER_TABLE_DATA iter = m_mapData.begin(); iter != m_mapData.end(); ++iter)
	{
		DB_KEY dbKey = iter->first;
		rVecKey.push_back(dbKey);
	}
	return true;
	DEBUG_CATCHF4("TConstDoubleTable::EnumKey TableName[%s], KeyIndex1[%d], KeyIndex2[%d]", m_szTableName, m_nKeyIndex1, m_nKeyIndex2);
}

////////////////////////////////////////////////////////////////////////
// Description:  获得双键
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: void
////////////////////////////////////////////////////////////////////////
template<class DataEnum>
void TConstDoubleTable<DataEnum>::GetDoubleKey( IN DB_KEY dbKey, OUT int& nKeyValue1, OUT int& nKeyValue2 ) const
{
	nKeyValue1 = (int)(dbKey >> 32) & 0xFFFFFFFF;
	nKeyValue2 = (int)(dbKey & 0xFFFFFFFF);
}

////////////////////////////////////////////////////////////////////////
// Description:  双键常量表初始化
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
template<class DataEnum>
bool TConstDoubleTable<DataEnum>::Init( IDatabase* pDB, const char* pszConstTableName, int nKeyIndex1, int nKeyIndex2 )
{
	DEBUG_TRY;
	CHECKF(pDB);
	CHECKF(pszConstTableName);
	CHECKF(nKeyIndex1 >= 0);
	CHECKF(nKeyIndex2 >= 0);
	CHECKF(nKeyIndex1 != nKeyIndex2);

	m_pDB = pDB;
	m_nKeyIndex1 = nKeyIndex1;
	m_nKeyIndex2 = nKeyIndex2;
	::SafeCopy(m_szTableName, pszConstTableName, sizeof(m_szTableName));

	SQLBUF szSql = "";
	sprintf(szSql, "SELECT * FROM %s", m_szTableName);
	SafeCopy(m_szLoadSql, szSql);
	RecordsetPtr pRes = m_pDB->CreateNewRecordset(m_szLoadSql);
	CHECKF(pRes);

	RecordPtr pRecord = NULL;
	for(int i = 0; i < pRes->RecordCount(); i++, pRes->MoveNext())
	{
		pRecord = pRes->CreateNewRecord();
		CHECKC(pRecord);

		int nKeyValue1 = pRecord->GetInt(m_nKeyIndex1);
		int nKeyValue2 = pRecord->GetInt(m_nKeyIndex2);
		DB_KEY dbKey = this->MakeKey(nKeyValue1, nKeyValue2);
		if (this->IsExist(nKeyValue1, nKeyValue2))
		{
			tolog6("TConstDoubleTable::Init TableName[%s], KeyIndex[%d,%d], KeyValue[%d,%d] Already Exist! auto Passed!", m_szTableName, m_nKeyIndex1, m_nKeyIndex2, nKeyValue1, nKeyValue2);
			continue;
		}

		m_mapData[dbKey] = pRecord;				
	}

	return true;
	DEBUG_CATCHF4("TConstDoubleTable::Init TableName[%s], KeyIndex[%d,%d]", m_szTableName, m_nKeyIndex1, m_nKeyIndex2);
}

////////////////////////////////////////////////////////////////////////
// Description:  双键常量表初始化(自定义sql)
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
template<class DataEnum>
bool TConstDoubleTable<DataEnum>::InitCustom( IDatabase* pDB, const char* pszConstTableName, int nKeyIndex1, int nKeyIndex2, const char* pszCustomSql )
{
	DEBUG_TRY;
	CHECKF(pDB);
	CHECKF(pszConstTableName);
	CHECKF(pszCustomSql);
	CHECKF(nKeyIndex1 >= 0);
	CHECKF(nKeyIndex2 >= 0);
	CHECKF(nKeyIndex1 != nKeyIndex2);

	m_pDB = pDB;
	m_nKeyIndex1 = nKeyIndex1;
	m_nKeyIndex2 = nKeyIndex2;
	::SafeCopy(m_szTableName, pszConstTableName, sizeof(m_szTableName));

	SafeCopy(m_szLoadSql, pszCustomSql);
	RecordsetPtr pRes = m_pDB->CreateNewRecordset(m_szLoadSql);
	CHECKF(pRes);

	RecordPtr pRecord = NULL;
	for(int i = 0; i < pRes->RecordCount(); i++, pRes->MoveNext())
	{
		pRecord = pRes->CreateNewRecord();
		CHECKC(pRecord);

		int nKeyValue1 = pRecord->GetInt(m_nKeyIndex1);
		int nKeyValue2 = pRecord->GetInt(m_nKeyIndex2);
		DB_KEY dbKey = this->MakeKey(nKeyValue1, nKeyValue2);
		if (this->IsExist(nKeyValue1, nKeyValue2))
		{
			tolog6("TConstDoubleTable::Init TableName[%s], KeyIndex[%d,%d], KeyValue[%d,%d] Already Exist! auto Passed!", m_szTableName, m_nKeyIndex1, m_nKeyIndex2, nKeyValue1, nKeyValue2);
			continue;
		}

		m_mapData[dbKey] = pRecord;				
	}

	return true;
	DEBUG_CATCHF4("TConstDoubleTable::Init TableName[%s], KeyIndex[%d,%d]", m_szTableName, m_nKeyIndex1, m_nKeyIndex2);
}


////////////////////////////////////////////////////////////////////////
// Description:  双键常量表释放
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: void
////////////////////////////////////////////////////////////////////////
template<class DataEnum>
void TConstDoubleTable<DataEnum>::Release( void )
{
	DEBUG_TRY;
	m_mapData.clear();
	DEBUG_CATCH4("TConstSingleTable::Release TableName[%s], KeyIndex[%d,%d]", m_szTableName, m_nKeyIndex1, m_nKeyIndex2);
}

////////////////////////////////////////////////////////////////////////
// Description:  重新加载双键常量表
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
template<class DataEnum>
bool TConstDoubleTable<DataEnum>::Reload( void )
{
	CHECKF(m_pDB);
	CHECKF(m_nKeyIndex1 >= 0);
	CHECKF(m_nKeyIndex2 >= 0);

	char szSaveTableName[64] = "";
	::SafeCopy(szSaveTableName, m_szTableName, sizeof(szSaveTableName));

	this->Release();
	return this->InitCustom(m_pDB, szSaveTableName, m_nKeyIndex1, m_nKeyIndex2, m_szLoadSql);
}

////////////////////////////////////////////////////////////////////////
// Description:  制造双键key
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: DB_KEY
////////////////////////////////////////////////////////////////////////
template<class DataEnum>
DB_KEY TConstDoubleTable<DataEnum>::MakeKey( int nKeyValue1, int nKeyValue2 ) const
{
	return (((DB_KEY)nKeyValue1) << 32) + nKeyValue2; 
}

////////////////////////////////////////////////////////////////////////
// Description:  判断是否存在
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
template<class DataEnum>
bool TConstDoubleTable<DataEnum>::IsExist( int nKeyValue1, int nKeyValue2 ) const
{
	DEBUG_TRY;
	DB_KEY dbKey = this->MakeKey(nKeyValue1, nKeyValue2);
	return m_mapData.find(dbKey) != m_mapData.end();
	DEBUG_CATCHF6("TConstDoubleTable::IsExist TableName[%s], KeyIndex[%d, %d], KeyVaule[%d, %d]", m_szTableName, m_nKeyIndex1, m_nKeyIndex2, nKeyValue1, nKeyValue2);
}

////////////////////////////////////////////////////////////////////////
// Description:  获得双键常量表数据(I64)
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: I64
////////////////////////////////////////////////////////////////////////
template<class DataEnum>
I64 TConstDoubleTable<DataEnum>::GetData( int nKeyValue1, int nKeyValue2, DataEnum eDataEnum ) const
{
	DEBUG_TRY;
	DB_KEY dbKey = this->MakeKey(nKeyValue1, nKeyValue2);
	CITER_TABLE_DATA iter = m_mapData.find(dbKey);
	IF_NOT (iter != m_mapData.end())
	{
		::LogSave("TConstDoubleTable::GetData not config! TableName[%s], KeyIndex[%d, %d], KeyVaule[%d, %d], DataEnum[%d]", m_szTableName, m_nKeyIndex1, m_nKeyIndex2, nKeyValue1, nKeyValue2, (int)eDataEnum);
		return 0;
	}
	return iter->second->GetInt64((int)eDataEnum);
	DEBUG_CATCHF7("TConstDoubleTable::GetData TableName[%s], KeyIndex[%d, %d], KeyVaule[%d, %d], DataEnum[%d]", m_szTableName, m_nKeyIndex1, m_nKeyIndex2, nKeyValue1, nKeyValue2, (int)eDataEnum);
}

////////////////////////////////////////////////////////////////////////
// Description:  获得双键常量表字符串(const char*)
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: const char*
////////////////////////////////////////////////////////////////////////
template<class DataEnum>
const char* TConstDoubleTable<DataEnum>::GetDataStr( int nKeyValue1, int nKeyValue2, DataEnum eDataEnum ) const
{
	DEBUG_TRY;
	DB_KEY dbKey = this->MakeKey(nKeyValue1, nKeyValue2);
	CITER_TABLE_DATA iter = m_mapData.find(dbKey);
	IF_NOT (iter != m_mapData.end())
	{
		::LogSave("TConstDoubleTable::GetDataStr not config! TableName[%s], KeyIndex[%d, %d], KeyVaule[%d, %d], DataEnum[%d]", m_szTableName, m_nKeyIndex1, m_nKeyIndex2, nKeyValue1, nKeyValue2, (int)eDataEnum);
		return NULL;
	}
	return iter->second->GetStr((int)eDataEnum);
	DEBUG_CATCHF7("TConstDoubleTable::GetDataStr TableName[%s], KeyIndex[%d, %d], KeyVaule[%d, %d], DataEnum[%d]", m_szTableName, m_nKeyIndex1, m_nKeyIndex2, nKeyValue1, nKeyValue2, (int)eDataEnum);
}

////////////////////////////////////////////////////////////////////////
// Description:  枚举Key1  按照指定的字段比较
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: void
////////////////////////////////////////////////////////////////////////
template<class DataEnum>
void TConstDoubleTable<DataEnum>::EnumKey1ByData( OUT VEC_CONST_TABLE_KEY& rVecKey1, I64 i64Data, DataEnum eDataEnum ) const
{
	rVecKey1.clear();

	for (CITER_TABLE_DATA iter = m_mapData.begin(); iter != m_mapData.end(); ++iter)
	{
		RecordPtr pRecord = iter->second;
		CHECKC(pRecord);

		if (pRecord->GetInt64(eDataEnum) == i64Data)
		{
			int nKeyValue1 = pRecord->GetInt(m_nKeyIndex1);
			rVecKey1.push_back(nKeyValue1);
		}
	}
}

////////////////////////////////////////////////////////////////////////
// Description:  枚举Key2  按照指定的字段比较
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: void
////////////////////////////////////////////////////////////////////////
template<class DataEnum>
void TConstDoubleTable<DataEnum>::EnumKey2ByData( OUT VEC_CONST_TABLE_KEY& rVecKey2, I64 i64Data, DataEnum eDataEnum ) const
{
	rVecKey2.clear();

	for (CITER_TABLE_DATA iter = m_mapData.begin(); iter != m_mapData.end(); ++iter)
	{
		RecordPtr pRecord = iter->second;
		CHECKC(pRecord);

		if (pRecord->GetInt64(eDataEnum) == i64Data)
		{
			int nKeyValue2 = pRecord->GetInt(m_nKeyIndex2);
			rVecKey2.push_back(nKeyValue2);
		}
	}
}

////////////////////////////////////////////////////////////////////////
// Description:  获得总大小
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: int
////////////////////////////////////////////////////////////////////////
template<class DataEnum>
int TConstDoubleTable<DataEnum>::GetSize( void ) const
{
	return m_mapData.size();
}


#endif // end of _GAME_BASECODE_MT_CONST_DOUBLE_TABLE_H_