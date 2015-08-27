////////////////////////////////////////////////////////////////////////
// Import : 全局文件。包含文件。
// Moudle : Global.h
// Author : 陈建军(Chen Jianjun)
// Create : 2015-6-19
////////////////////////////////////////////////////////////////////////
#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// 守护进程只在release版本生效, 如果release版本也不需要注释掉SEIYA_RUN这个宏
#ifndef MYDEBUG
#define SEIYA_RUN
#endif 

// 压测版本定义宏
// #define __CY_GAME_FULL_TEST__

#include "./GlobalEnumDef.h"
#include "./GlobalConstDef.h"
#include "./GlobalStructDef.h"
#include "./GlobalFuction.h"

#include "./RelationMsgTransform.h"
#include "./DatabaseDefineAcc.h"
#include "./DatabaseDefineConst.h"
#include "./DatabaseDefineGame.h"

#include "./../Common/common.h"
#include "./../Common/MyPubilcKey/MyPublicKey.h"

// 编译提示宏使用方法
// #pragma message(PRAGMAMSG(编译提示宏示例))

#endif // end of _GLOBAL_H_