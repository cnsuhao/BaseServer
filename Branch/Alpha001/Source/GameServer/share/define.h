// define.h ȫ�����ͺͳ�������
// �ɽ��ޣ�2002.10.29
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
// ͨ�ýӿ�
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

#endif // ALL_GLOBAL_DEFINE_H
