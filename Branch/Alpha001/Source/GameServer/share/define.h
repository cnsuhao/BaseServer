// define.h 全局类型和常量定义
// 仙剑修，2002.10.29
//////////////////////////////////////////////////////////////////////
#ifndef	ALL_GLOBAL_DEFINE_H
#define	ALL_GLOBAL_DEFINE_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning(disable:4786)

#include "./DefineActionID.h"
#include "./EnumDef.h"
#include "./ConstDef.h"
#include "./StructDef.h"
#include "./String/MyDDString.h"

#include "./../Common/common.h"
#include "./../Common/BaseFunc.h"
#include "./../Common/Myheap.h"
#include "./../Common/TMemoryData.h"
#include "./../Common/MyArray.h"
#include "./../Common/Timeout.h"
#include "./../Common/PerformanceStatistics.h"
#include "./../Common/AutoPtr.h"
#include "./../Common/MxyString.h"
#include "./../DataBase/Temple/TConstSingleTable.h"
#include "./../DataBase/Temple/TConstDoubleTable.h"
#include "./../../../Include/Global.h"

#include <deque>
#include <stack>
#include <list>
#include <set>
#include <map>
#include <vector>
#include <hash_map>
#include <limits>
#include <algorithm>

//////////////////////////////////////////////////////////////////////
// 通用接口
//////////////////////////////////////////////////////////////////////
inline void EmptyFunction(...) {}
#ifdef MULTI_KERNEL_LOG
	#define LOGDEBUG	LOGMSG
#else
	#define LOGDEBUG	EmptyFunction
#endif

typedef std::vector<OBJID>			ID_VEC;
typedef ID_VEC::iterator			ID_VEC_ITER;
typedef ID_VEC::const_iterator		ID_VEC_CITER;
typedef std::vector<int>			INT_VEC;
typedef INT_VEC::iterator			INT_VEC_ITER;
typedef INT_VEC::const_iterator		INT_VEC_CITER;

typedef std::set<OBJID>				ID_SET;
typedef ID_SET::iterator			ID_SET_ITER;
typedef ID_SET::const_iterator		ID_SET_CITER;
typedef std::set<UINT>				UINT_SET;
typedef UINT_SET::iterator			UINT_SET_ITER;
typedef UINT_SET::const_iterator	UINT_SET_CITER;


typedef std::vector<int>			VEC_CONFIGINFO;


typedef std::set<OBJID>				SET_OBJ;

typedef std::map<int, int>			MAP_INT;
typedef MAP_INT::iterator			ITER_MAP_INT;
typedef MAP_INT::const_iterator		CITER_MAP_INT;

////////////////////////////////////////////////////////////////////////////////////////////////
// 常量表define begin
// 活动配置表
typedef CMyArray<int, ACTIVITY_CONFIG_DATA_END - ACTIVITY_CONFIG_DATA_BEGIN>	ARR_ACTIVITY_CONFIG_INFO;
typedef map<OBJID, ARR_ACTIVITY_CONFIG_INFO>									MAP_ACTIVITY_CONFIG_INFO;
typedef MAP_ACTIVITY_CONFIG_INFO::iterator										ITER_MAP_ACTIVITY_CONFIG_INFO;
typedef MAP_ACTIVITY_CONFIG_INFO::const_iterator								CON_ITER_MAP_ACTIVITY_CONFIG_INFO;
typedef std::vector<int>														VEC_ACTIVITY_INFO;
// 常量表define end
////////////////////////////////////////////////////////////////////////////////////////////////

// 装备属性容器
typedef std::map<EQUIP_ATTR_TYPE, I64>	MAP_EQUIP_ATTR;

// 卡牌属性容器
typedef std::map<POKER_ATTR, I64>		MAP_POKER_ATTR;	

// 竞技场战斗卡牌ID容器
typedef std::map<int, I64>				MAP_AREA_FIGHTPOKER_ID;

#endif // ALL_GLOBAL_DEFINE_H
