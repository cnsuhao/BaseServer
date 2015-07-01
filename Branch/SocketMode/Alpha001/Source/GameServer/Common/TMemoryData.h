////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2012, WuHan ChuangYou, All Rights Reserved
// Moudle: TMemoryData.h
// Author: 彭文奇(Peng Wenqi)
// Created: 2012-10-29
////////////////////////////////////////////////////////////////////////

#ifndef	_COMMON_T_MEMORY_DATA_H_
#define _COMMON_T_MEMORY_DATA_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning(disable:4786)
#include <map>
#include "common.h"

template <class T>
class TMemoryData
{
	typedef std::map<T, I64> MAP_DATA_TYPE;
public:
	//////////////////////////////////////////////////////////////////////////
	bool IsExist(T eAttr) const
	{
		MAP_DATA_TYPE::const_iterator iter = m_mapData.find(eAttr);
		if (iter == m_mapData.end())
		{
			return false;
		}
		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	I64 GetAttr(T eAttr) const
	{
		MAP_DATA_TYPE::const_iterator iter = m_mapData.find(eAttr);
		if (iter != m_mapData.end())
		{
			return iter->second;
		}
		return 0i64;
	}

	//////////////////////////////////////////////////////////////////////////
	bool SetAttr(T eAttr, I64 iNewData)
	{
		// 对于不存在的0值, 不必插入, 节约内存
		if (0i64 == iNewData && !this->IsExist(eAttr))
		{
			return true;
		}

		m_mapData[eAttr] = iNewData;
		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	bool AddAttr(T eAttr, I64 iAddData)
	{
		I64 iOldData = this->GetAttr(eAttr);
		m_mapData[eAttr] = iOldData + iAddData;
		return true;
	}

private:
	MAP_DATA_TYPE m_mapData;
};

#define DEFINE_mda(ENUM_ATTR)																									\
		virtual bool	IsExistMemoryData(ENUM_ATTR eAttr) const			{return m_memoryData.IsExist(eAttr);}				\
		virtual I64		GetMemoryDataAttr(ENUM_ATTR eAttr) const			{return m_memoryData.GetAttr(eAttr);}				\
		virtual bool	SetMemoryDataAttr(ENUM_ATTR eAttr, I64 iNewData)	{return m_memoryData.SetAttr(eAttr, iNewData);}		\
		virtual bool	AddMemoryDataAttr(ENUM_ATTR eAttr, I64 iAddData)	{return m_memoryData.AddAttr(eAttr, iAddData);}		\
	protected:																													\
		TMemoryData<ENUM_ATTR> m_memoryData;

#endif // end of _COMMON_T_MEMORY_DATA_H_