////////////////////////////////////////////////////////////////////////
// Import : 共享文件。头文件包含。
// Moudle : define.h 
// Author : 陈建军(Chen Jianjun)
// Create : 2015-6-19
////////////////////////////////////////////////////////////////////////
#ifndef	_SHARE_DEFINE_H_
#define	_SHARE_DEFINE_H_

#if _MSC_VER > 1000
#pragma once
#endif	// _MSC_VER > 1000

#pragma warning(disable:4786)

// 共享文件
#include "./DefineActionID.h"
#include "./EnumDef.h"
#include "./ConstDef.h"
#include "./StructDef.h"
#include "./String/MyDDString.h"

// Common库文件
#include "./../Common/BaseFunc.h"
#include "./../Common/Myheap.h"
#include "./../Common/TMemoryData.h"
#include "./../Common/MyArray.h"
#include "./../Common/Timeout.h"
#include "./../Common/PerformanceStatistics.h"
#include "./../Common/AutoPtr.h"
#include "./../Common/MxyString.h"

// DataBase库文件
#include "./../DataBase/Temple/TConstSingleTable.h"
#include "./../DataBase/Temple/TConstDoubleTable.h"

// 全局文件
#include "./../../../Include/Global.h"

// 系统文件
#include <deque>
#include <stack>
#include <list>
#include <set>
#include <map>
#include <vector>
#include <hash_map>
#include <limits>
#include <algorithm>
#endif	// _DEFINE_H_
