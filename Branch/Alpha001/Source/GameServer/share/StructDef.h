////////////////////////////////////////////////////////////////////////
// Import : 共享文件。结构体定义。
// Moudle : StructDef.h 
// Author : 陈建军(Chen Jianjun)
// Create : 2015-6-19
////////////////////////////////////////////////////////////////////////
#ifndef _SHARE_STRUCT_DEF_H_
#define _SHARE_STRUCT_DEF_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "./ConstDef.h"
#include "./EnumDef.h"

////////////////////////////////////////////////////////////////////////
// 通用接口
inline void EmptyFunction(...) {}
#ifdef MULTI_KERNEL_LOG
#define LOGDEBUG	LOGMSG
#else
#define LOGDEBUG	EmptyFunction
#endif
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
// 通用STL容器定义
typedef std::vector<int>			INT_VEC;
typedef INT_VEC::iterator			INT_VEC_ITER;
typedef INT_VEC::const_iterator		INT_VEC_CITER;

typedef std::vector<UINT>			UINT_VEC;
typedef UINT_VEC::iterator			UINT_VEC_ITER;
typedef UINT_VEC::const_iterator	UINT_VEC_CITER;

typedef std::vector<OBJID>			ID_VEC;
typedef ID_VEC::iterator			ID_VEC_ITER;
typedef ID_VEC::const_iterator		ID_VEC_CITER;

typedef std::set<int>				INT_SET;
typedef INT_SET::iterator			INT_SET_ITER;
typedef INT_SET::const_iterator		INT_SET_CITER;

typedef std::set<UINT>				UINT_SET;
typedef UINT_SET::iterator			UINT_SET_ITER;
typedef UINT_SET::const_iterator	UINT_SET_CITER;

typedef std::set<OBJID>				ID_SET;
typedef ID_SET::iterator			ID_SET_ITER;
typedef ID_SET::const_iterator		ID_SET_CITER;

typedef std::map<int, int>			INT_MAP;
typedef INT_MAP::iterator			INT_MAP_ITER;
typedef INT_MAP::const_iterator		INT_MAP_CITER;
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
// 结构体定义

////////////////////////////////////////////////////////////////////////
#endif // end of _SHARE_STRUCT_DEF_H_