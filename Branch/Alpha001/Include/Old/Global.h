////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2012, WuHan ChuangYou, All Rights Reserved
// Moudle: Global.h
// Author: ������(Peng Wenqi)
// Created: 2012-11-19
////////////////////////////////////////////////////////////////////////
#ifndef _GLOBAL_HEADER_
#define _GLOBAL_HEADER_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// �ػ�����ֻ��release�汾��Ч, ���release�汾Ҳ����Ҫע�͵�SEIYA_RUN�����
#ifndef MYDEBUG
#define  SEIYA_RUN
#endif 

// ѹ��汾�����
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

// ������ʾ��ʹ�÷���
// #pragma message(PRAGMAMSG(������ʾ��ʾ��))

#endif // end of _GLOBAL_HEADER_