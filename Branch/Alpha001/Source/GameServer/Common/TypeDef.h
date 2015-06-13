////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2012, WuHan ChuangYou, All Rights Reserved
// Moudle: TypeDef.h
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Created: 2012-10-23
////////////////////////////////////////////////////////////////////////
#ifndef	_COMMON_TYPEDEF_H_
#define _COMMON_TYPEDEF_H_
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../../Include/Global.h"

class CUser;
namespace login_kernel{class CNetMsg;}
namespace game_kernel{class	CNetMsg;}

class CPoker;
typedef std::map<I64, CPoker*>	MAP_POKER;

#endif // end of _COMMON_TYPEDEF_H_