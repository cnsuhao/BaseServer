////////////////////////////////////////////////////////////////////////
// Import : ȫ���ļ��������ļ���
// Moudle : Global.h
// Author : �½���(Chen Jianjun)
// Create : 2015-6-19
////////////////////////////////////////////////////////////////////////
#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// �ػ�����ֻ��release�汾��Ч, ���release�汾Ҳ����Ҫע�͵�SEIYA_RUN�����
#ifndef MYDEBUG
#define SEIYA_RUN
#endif 

// ѹ��汾�����
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

// ������ʾ��ʹ�÷���
// #pragma message(PRAGMAMSG(������ʾ��ʾ��))

#endif // end of _GLOBAL_H_