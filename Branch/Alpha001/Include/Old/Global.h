////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2012, WuHan ChuangYou, All Rights Reserved
// Moudle: Global.h
// Author: 彭文奇(Peng Wenqi)
// Created: 2012-11-19
////////////////////////////////////////////////////////////////////////
#ifndef _GLOBAL_HEADER_
#define _GLOBAL_HEADER_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// 守护进程只在release版本生效, 如果release版本也不需要注释掉SEIYA_RUN这个宏
#ifndef MYDEBUG
#define  SEIYA_RUN
#endif 

// 压测版本定义宏
// #define __CY_GAME_FULL_TEST__

#include "./GlobalEnumDef.h"
#include "./GlobalConstDef.h"
#include "./GlobalStructDef.h"
#include "./RelationMsgTransform.h"
#include "./MyPubilcKey/MyPublicKey.h"
#include "./DatabaseDefine.h"
#include "./GlobalFuction.h"
#include "./RelayDatabase.h"
#include "./CrossRelayDatabase.h"

// 编译提示宏使用方法
// #pragma message(PRAGMAMSG(编译提示宏示例))

#endif // end of _GLOBAL_HEADER_