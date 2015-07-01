////////////////////////////////////////////////////////////////////////
// Import : 全局文件。函数定义。
// Moudle : GlobalFuction.h
// Author : 陈建军(Chen Jianjun)
// Create : 2015-6-19
////////////////////////////////////////////////////////////////////////
#ifndef _GLOBAL_FUCTION_H_
#define _GLOBAL_FUCTION_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "./GlobalEnumDef.h"
#include "./GlobalConstDef.h"
#include "./GlobalStructDef.h"
#include "./DatabaseDefine.h"

////////////////////////////////////////////////////////////////////////
// Description: 判断是否为媒体卡
// Arguments:
// Author: 陈建军(Chen Jianjun)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
inline bool IsMtCard(const char* pszCard)
{
	if (!pszCard)
	{
		return false;
	}

	if (strlen(pszCard) != MAX_NEWCARD_LENGTH)
	{
		return false;
	}
	
	if (_strnicmp(pszCard, CONST_MT_NEWCARD_HEADER, MAX_NEWCARD_HEADER_LENGTH) != 0)
	{
		return false;
	}

	return true;
}

#endif // end of _GLOBAL_FUCTION_H_