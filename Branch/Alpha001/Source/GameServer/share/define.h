////////////////////////////////////////////////////////////////////////
// Import : �����ļ���ͷ�ļ�������
// Moudle : define.h 
// Author : �½���(Chen Jianjun)
// Create : 2015-6-19
////////////////////////////////////////////////////////////////////////
#ifndef	_SHARE_DEFINE_H_
#define	_SHARE_DEFINE_H_

#if _MSC_VER > 1000
#pragma once
#endif	// _MSC_VER > 1000

#pragma warning(disable:4786)

// �����ļ�
#include "./DefineActionID.h"
#include "./EnumDef.h"
#include "./ConstDef.h"
#include "./StructDef.h"
#include "./String/MyDDString.h"

// Common���ļ�
#include "./../Common/BaseFunc.h"
#include "./../Common/Myheap.h"
#include "./../Common/TMemoryData.h"
#include "./../Common/MyArray.h"
#include "./../Common/Timeout.h"
#include "./../Common/PerformanceStatistics.h"
#include "./../Common/AutoPtr.h"
#include "./../Common/MxyString.h"

// DataBase���ļ�
#include "./../DataBase/Temple/TConstSingleTable.h"
#include "./../DataBase/Temple/TConstDoubleTable.h"

// ȫ���ļ�
#include "./../../../Include/Global.h"

// ϵͳ�ļ�
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
