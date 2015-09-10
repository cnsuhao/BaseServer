////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan ChuangYou, All Rights Reserved
// Moudle: MsgGameUserInfo.h
// Author: 彭文奇(Peng Wenqi)
// Created: 2014-11-10
////////////////////////////////////////////////////////////////////////
#ifndef _GAMEKERNER_MSG_GAME_USER_INFO_H_
#define _GAMEKERNER_MSG_GAME_USER_INFO_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "./NetMsg.h"

class CUser;
class CMsgGameUserInfo : public game_kernel::CNetMsg
{
public:
	CMsgGameUserInfo();
	virtual ~CMsgGameUserInfo();

	virtual BOOL Create(char* pMsgBuf, DWORD dwSize);
	virtual void Process(void *pInfo){};

public:
	bool CreateUserInfo(CUser* pUser);


private:
	typedef struct  
	{
		MSG_NUM_4BIT	idUser;			// 角色id
		MSG_NUM_4BIT	idAccountID;	// 账号id
		MSG_NUM_4BIT	nAccountType;	// 账号类型
		MSG_NUM_4BIT	nLastLoginTime; // 最后一次登录时间
		MSG_NUM_4BIT	nCreateTime;	// 创建时间 utc秒
		MSG_NUM_4BIT	nLastExitTime;	// 上次登出时间

		MSG_NUM_4BIT	nServerGroup;	// 服务器组号
		MSG_NUM_4BIT	nServerLine;	// 服务器线路号

		MSG_NUM_4BIT	nLev;			// 等级
		MSG_NUM_4BIT	nExp;			// 经验
		MSG_STR_32BIT	szUserName;		// 名字
		MSG_NUM_4BIT	nCampType;		// 阵营类型
		MSG_NUM_4BIT	nFlagShip;		// 旗舰类型

		MSG_NUM_4BIT	fRotation;		// 方向角度
		MSG_NUM_4BIT	fSpeedForm;		// 前进速度
		MSG_NUM_4BIT	fSpeedRotation;	// 转向速度
		MSG_NUM_4BIT	fViewRange;		// 可视距离半径

		MSG_NUM_4BIT	nScore;			// 战斗力
		MSG_NUM_4BIT	nGalaxy;		// 所在星系
		MSG_NUM_4BIT	nRest;			// 所在地点（NPC）
		MSG_NUM_4BIT	curPointx;		// 当前坐标x
		MSG_NUM_4BIT	curPointy;		// 当前坐标y
		MSG_NUM_4BIT	aimPointx;		// 目标坐标x
		MSG_NUM_4BIT	aimPointy;		// 目标坐标y
	}MSG_Info;

	MSG_Info* m_pInfo;
};


#endif // end of _GAMEKERNER_MSG_GAME_USER_INFO_H_