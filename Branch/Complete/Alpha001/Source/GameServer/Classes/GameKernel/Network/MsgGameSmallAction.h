////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2012, WuHan ChuangYou, All Rights Reserved
// Moudle: MsgSmallAction.h
// Author: 彭文奇(Peng Wenqi)
// Created: 2012-10-23
////////////////////////////////////////////////////////////////////////
#ifndef _GAMESERVER_MSG_GAME_SMALL_ACTION_H_
#define _GAMESERVER_MSG_GAME_SMALL_ACTION_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "./NetMsg.h"

// SmallAction枚举, 对应sAction
enum MSG_SMALL_ACTION
{
	MSG_SMALL_ACTION_NONE = 0,
	MSG_SMALL_ACTION_QUERY_NEWCARDPRIZE_INFO		= 1,	// 查询新手卡奖励信息   	C --> S
	MSG_SMALL_ACTION_RUN_LUA_SCRIPT					= 2,	// 执行LUA脚本				C --> S
	MSG_SMALL_ACTION_QUERY_SKILLPOINT_INFO			= 3,	// 查询技能点信息			C <-> S
	MSG_SMALL_ACTION_GET_MONTH_CARD					= 4,	// 领取月卡					C <-> S
	MSG_SMALL_ACTION_SYN_ACTIVITY_TIME				= 5,	// 同步活动剩余时间			C <-- S
	MSG_SMALL_ACTION_QUERY_BUY_POWER				= 6,	// 查询购买体力信息			C <-> S
	MSG_SMALL_ACTION_REQUEST_BUY_POWER				= 7,	// 请求购买体力				C <-> S
	MSG_SMALL_ACTION_QUERY_OTHER_USER_INFO			= 8,	// 查询其他玩家信息			C --> S
	MSG_SMALL_ACTION_QUERY_TREASURE_POWER_INFO		= 9,	// 查询寻宝体力信息			C <-> S
	MSG_SMALL_ACTION_QUERY_EXITINFO					= 10,	// 查询退出时的各项次数		C <-> S
};

// 错误码枚举, 对应sResult
enum MSG_SMALL_RESULT
{
	MSG_SMALL_RESULT_SUCC							= 0,
	MSG_SMALL_RESULT_ERROR							= 1,
};

typedef std::vector<UINT> VEC_SCORE;
typedef std::vector<UINT> VEC_ONLINEAWARDINFO;
//////////////////////////////////////////////////////////////////////////
//	新增协议Create或Process时, 请针对每个东西来写一个函数, 不要重用, 可读性会很好 
class CMsgGameSmallAction : public game_kernel::CNetMsg  
{
public:
	CMsgGameSmallAction();
	virtual ~CMsgGameSmallAction();

	virtual BOOL Create					(char* pMsgBuf, DWORD dwSize);
	virtual void Process				(void *pInfo);


	// Create Func Here...
//public:
//	bool CreateSkillPointInfo			(UINT unLeftPoint, UINT unMaxPoint, UINT unNextRecoverTime, UINT unAllEnergyRecoverTime, int nRecoverInterval, int nBuyCount, int nNeedVas, int nBuyPoint);
//	bool CreateActivityTimeInfo			(int nType, int nState, int nLeftTime);
//
//	// Process Func Here...
//private:
//	void ProcessQueryNewCardPrizeInfo	(void);
//	void ProcessRunLuaScript			(void);
//	void ProcessQuerySkillPointInfo		(void);
//	void ProcessGetMonthCard			(void);
//	void ProcessQueryBuyPowerInfo		(void);
//	void ProcessRequestBuyPower			(void);
//	void ProcessQueryOtherUserInfo		(void);
//	void ProcessQueryTreasurePowerInfo	(void);
//	void ProcessQueryExitInfo			(void);

private:
	bool CreateSmallAction				(MSG_SMALL_ACTION eAction, MSG_SMALL_RESULT eResult);
	bool AppendParam					(int nAddParam);
	int  GetParamVector					(OUT INT_VEC& rVec);

private:
	typedef struct
	{
		MSG_NUM_2BIT	sAction;
		MSG_NUM_2BIT	sResult;

		MSG_NUM_4BIT	nParamNumber;
		MSG_NUM_4BIT	nParam[1];
	}MSG_Info;

	MSG_Info* m_pInfo;

};

#endif // end of _GAMESERVER_MSG_GAME_SMALL_ACTION_H_