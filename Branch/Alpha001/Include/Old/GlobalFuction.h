////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2012, WuHan ChuangYou, All Rights Reserved
// Moudle: GlobalFuction.h
// Author: �½���(Chen Jianjun)
// Created: 2014-11-13
////////////////////////////////////////////////////////////////////////
#ifndef _GLOBAL_FUCTION_HEADER_
#define _GLOBAL_FUCTION_HEADER_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "./GlobalEnumDef.h"
#include "./GlobalConstDef.h"
#include "./GlobalStructDef.h"
#include "./DatabaseDefine.h"

////////////////////////////////////////////////////////////////////////
// Description: �ж��Ƿ�Ϊý�忨
// Arguments:
// Author: �½���(Chen Jianjun)
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

#endif // end of _GLOBAL_FUCTION_HEADER_