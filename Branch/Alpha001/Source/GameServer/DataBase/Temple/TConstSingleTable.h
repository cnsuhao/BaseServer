////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2013, WuHan ChuangYou, All Rights Reserved
// Moudle: TConstSingleTable.h
// Author: 彭文奇(Peng Wenqi)
// Created: 2013-4-16
////////////////////////////////////////////////////////////////////////
#ifndef _GAME_BASECODE_MT_CONST_SINGLE_TABLE_H_
#define _GAME_BASECODE_MT_CONST_SINGLE_TABLE_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning(disable:4786)
#include "./../I_mydb.h"

template<class DataEnum>
class TConstSingleTable
{
public:
	TConstSingleTable()		
	{
		ZeroMemory(m_szTableName, sizeof(m_szTableName));
		m_pDB = NULL;
		m_nKeyIndex = -1;
		m_keyMin = INT_MAX_CEIL;
		m_keyMax = 0;
	}

	~TConstSingleTable()	
	{
		this->Release();
	}

public:
	bool		Init		(IDatabase* pDB, const char* pszConstTableName, int nKeyIndex);
	bool		InitCustom	(IDatabase* pDB, const char* pszConstTableName, int nKeyIndex, const char* pszCustomSql);
	void		Release		(void);
	bool		Reload		(void);

public:
	bool		IsExist		(DB_KEY nKeyValue) const;
	I64			GetData		(DB_KEY nKeyValue, DataEnum eDataEnum) const;
	const char*	GetDataStr	(DB_KEY nKeyValue, DataEnum eDataEnum) const;
	bool		EnumKey		(OUT VEC_DB_KEY& rVecKey) const;
	DB_KEY		GetMinKey	(void) const;
	DB_KEY		GetMaxKey	(void) const;
	int			GetSize		(void) const;

private:
	char			m_szTableName[64];
	char			m_szLoadSql[256];
	int				m_nKeyIndex;
	MAP_TABLE_DATA	m_mapData;
	IDatabase*		m_pDB;
	DB_KEY			m_keyMin;
	DB_KEY			m_keyMax;
};


////////////////////////////////////////////////////////////////////////
// Description:  单键常量表初始化
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
template<class DataEnum>
bool TConstSingleTable<DataEnum>::Init( IDatabase* pDB, const char* pszConstTableName, int nKeyIndex )
{
	DEBUG_TRY;
	CHECKF(pDB);
	CHECKF(pszConstTableName);
	CHECKF(nKeyIndex >= 0);
	m_pDB = pDB;
	m_nKeyIndex = nKeyIndex;
	::SafeCopy(m_szTableName, pszConstTableName, sizeof(m_szTableName));
	m_keyMin = INT_MAX_CEIL;
	m_keyMax = 0;

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

		DB_KEY dbKey = pRecord->GetInt64(m_nKeyIndex);
		if (this->IsExist(dbKey))
		{
			tolog4("TConstSingleTable::Init TableName[%s], KeyIndex[%d], KeyValue[%I64d] Already Exist! auto Passed!", m_szTableName, m_nKeyIndex, dbKey);
			continue;
		}

		if (dbKey > m_keyMax)
		{
			m_keyMax = dbKey;
		}

		if (dbKey < m_keyMin)
		{
			m_keyMin = dbKey;
		}

		m_mapData[dbKey] = pRecord;				
	}

	return true;
	DEBUG_CATCHF3("TConstSingleTable::Init TableName[%s], KeyIndex[%d]", m_szTableName, nKeyIndex);
}

////////////////////////////////////////////////////////////////////////
// Description:  单键常量表初始化(自定义sql)
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
template<class DataEnum>
bool TConstSingleTable<DataEnum>::InitCustom( IDatabase* pDB, const char* pszConstTableName, int nKeyIndex, const char* pszCustomSql )
{
	DEBUG_TRY;
	CHECKF(pDB);
	CHECKF(pszConstTableName);
	CHECKF(pszCustomSql);
	CHECKF(nKeyIndex >= 0);
	m_pDB = pDB;
	m_nKeyIndex = nKeyIndex;
	::SafeCopy(m_szTableName, pszConstTableName, sizeof(m_szTableName));
	m_keyMin = INT_MAX_CEIL;
	m_keyMax = 0;

	SafeCopy(m_szLoadSql, pszCustomSql);
	RecordsetPtr pRes = m_pDB->CreateNewRecordset(m_szLoadSql);
	CHECKF(pRes);

	RecordPtr pRecord = NULL;
	for(int i = 0; i < pRes->RecordCount(); i++, pRes->MoveNext())
	{
		pRecord = pRes->CreateNewRecord();
		CHECKC(pRecord);

		DB_KEY dbKey = pRecord->GetInt64(m_nKeyIndex);
		if (this->IsExist(dbKey))
		{
			tolog4("TConstSingleTable::Init TableName[%s], KeyIndex[%d], KeyValue[%I64d] Already Exist! auto Passed!", m_szTableName, m_nKeyIndex, dbKey);
			continue;
		}

		if (dbKey > m_keyMax)
		{
			m_keyMax = dbKey;
		}

		if (dbKey < m_keyMin)
		{
			m_keyMin = dbKey;
		}

		m_mapData[dbKey] = pRecord;				
	}

	return true;
	DEBUG_CATCHF4("TConstSingleTable::InitCustom TableName[%s], KeyIndex[%d], CustomSql[%s]", m_szTableName, nKeyIndex, pszCustomSql);
}


////////////////////////////////////////////////////////////////////////
// Description:  单键常量表释放
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: void
////////////////////////////////////////////////////////////////////////
template<class DataEnum>
void TConstSingleTable<DataEnum>::Release( void )
{
	DEBUG_TRY;
	m_mapData.clear();
	DEBUG_CATCH3("TConstSingleTable::Release TableName[%s], KeyIndex[%d]", m_szTableName, m_nKeyIndex);
}


////////////////////////////////////////////////////////////////////////
// Description:  单键常量表重新加载
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: void
////////////////////////////////////////////////////////////////////////
template<class DataEnum>
bool TConstSingleTable<DataEnum>::Reload( void )
{
	CHECKF(m_pDB);
	CHECKF(m_nKeyIndex >= 0);

	char szSaveTableName[64] = "";
	::SafeCopy(szSaveTableName, m_szTableName, sizeof(szSaveTableName));

	this->Release();
	return this->InitCustom(m_pDB, szSaveTableName, m_nKeyIndex, m_szLoadSql);
}

////////////////////////////////////////////////////////////////////////
// Description:  判断是否存在
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
template<class DataEnum>
bool TConstSingleTable<DataEnum>::IsExist( DB_KEY nKeyValue ) const
{
	DEBUG_TRY;
	return m_mapData.find(nKeyValue) != m_mapData.end();
	DEBUG_CATCHF4("TConstSingleTable::IsExist TableName[%s], KeyIndex[%d], KeyVaule[%I64d]", m_szTableName, m_nKeyIndex, nKeyValue);
}

////////////////////////////////////////////////////////////////////////
// Description:  获得单键常量表数据(I64)
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: I64
////////////////////////////////////////////////////////////////////////
template<class DataEnum>
I64 TConstSingleTable<DataEnum>::GetData( DB_KEY nKeyValue, DataEnum eDataEnum ) const
{
	DEBUG_TRY;
	CITER_TABLE_DATA iter = m_mapData.find(nKeyValue);
	IF_NOT (iter != m_mapData.end())
	{
		::LogSave("TConstSingleTable::GetData not config! TableName[%s], KeyIndex[%d], KeyVaule[%I64d], DataEnum[%d]", m_szTableName, m_nKeyIndex, nKeyValue, (int)eDataEnum);
		return 0;
	}
	return iter->second->GetInt64((int)eDataEnum);
	DEBUG_CATCHF5("TConstSingleTable::GetData TableName[%s], KeyIndex[%d], KeyVaule[%I64d], DataEnum[%d]", m_szTableName, m_nKeyIndex, nKeyValue, (int)eDataEnum);
}

////////////////////////////////////////////////////////////////////////
// Description:  获得单键常量表字符串(const char*)
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: const char*
////////////////////////////////////////////////////////////////////////
template<class DataEnum>
const char* TConstSingleTable<DataEnum>::GetDataStr( DB_KEY nKeyValue, DataEnum eDataEnum ) const
{
	DEBUG_TRY;
	CITER_TABLE_DATA iter = m_mapData.find(nKeyValue);
	IF_NOT (iter != m_mapData.end())
	{
		::LogSave("TConstSingleTable::GetDataStr not config! TableName[%s], KeyIndex[%d], KeyVaule[%I64d], DataEnum[%d]", m_szTableName, m_nKeyIndex, nKeyValue, (int)eDataEnum);
		return NULL;
	}
	return iter->second->GetStr((int)eDataEnum);
	DEBUG_CATCHF5("TConstSingleTable::GetDataStr TableName[%s], KeyIndex[%d], KeyVaule[%I64d], DataEnum[%d]", m_szTableName, m_nKeyIndex, nKeyValue, (int)eDataEnum);
}

////////////////////////////////////////////////////////////////////////
// Description:  枚举单键常量表key的vector
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
template<class DataEnum>
bool TConstSingleTable<DataEnum>::EnumKey( OUT VEC_DB_KEY& rVecKey ) const
{
	DEBUG_TRY;
	rVecKey.clear();
	for (CITER_TABLE_DATA iter = m_mapData.begin(); iter != m_mapData.end(); ++iter)
	{
		DB_KEY dbKey = iter->first;
		rVecKey.push_back(dbKey);
	}
	return true;
	DEBUG_CATCHF3("TConstSingleTable::EnumKey TableName[%s], KeyIndex[%d]", m_szTableName, m_nKeyIndex);
}

////////////////////////////////////////////////////////////////////////
// Description:  获得最小key
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: DB_KEY
////////////////////////////////////////////////////////////////////////
template<class DataEnum>
DB_KEY TConstSingleTable<DataEnum>::GetMinKey( void ) const
{
	return m_keyMin;
}

////////////////////////////////////////////////////////////////////////
// Description:  获得最大key
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: DB_KEY
////////////////////////////////////////////////////////////////////////
template<class DataEnum>
DB_KEY TConstSingleTable<DataEnum>::GetMaxKey( void ) const
{
	return m_keyMax;
}

////////////////////////////////////////////////////////////////////////
// Description:  获得总大小
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: int
////////////////////////////////////////////////////////////////////////
template<class DataEnum>
int TConstSingleTable<DataEnum>::GetSize( void ) const
{
	return m_mapData.size();
}

#endif // end of _GAME_BASECODE_MT_CONST_SINGLE_TABLE_H_