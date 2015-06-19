//////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2012, WuHan ChuangYou, All Rights Reserved
// Moudle: DefineActionID.h	
// Author: 彭文奇(Peng Wenqi)
// Created: 2012-10-24
// 
// !!! 注意 !!!
// 1. 本文件用于定义服务器执行action的id定义, 以后都在此处定义
// 2. 新加action时, 麻烦请按照顺序写, 注释写清楚
//////////////////////////////////////////////////////////////////////////
#ifndef _MAPGROUP_DEFINE_ACTION_ID_H_
#define _MAPGROUP_DEFINE_ACTION_ID_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

const int ACTION_ID_ENTER_SYNDICATE_SAVE_TIME		= 1;	// 进入帮派保存时间
const int ACTION_ID_LEAVE_SYNDICATE_SAVE_TIME		= 2;	// 离开帮派保存时间
const int ACTION_ID_WARROAD_TEAM_CHAPTER_COMPLETE	= 3;	// 完成团队战役章节
const int ACTION_ID_LOTTERY							= 4;	// 抽奖
const int ACTION_ID_NTM_END_GIVE					= 5;	// 南天门结束发奖

const int ACTION_ID_USER_LOGIN_OVER					= 9;	// 玩家登陆完成


#endif // end of _MAPGROUP_DEFINE_ACTION_ID_H_