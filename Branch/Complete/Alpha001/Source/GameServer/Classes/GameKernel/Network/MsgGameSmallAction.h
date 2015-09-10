////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2012, WuHan ChuangYou, All Rights Reserved
// Moudle: MsgSmallAction.h
// Author: ������(Peng Wenqi)
// Created: 2012-10-23
////////////////////////////////////////////////////////////////////////
#ifndef _GAMESERVER_MSG_GAME_SMALL_ACTION_H_
#define _GAMESERVER_MSG_GAME_SMALL_ACTION_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "./NetMsg.h"

// SmallActionö��, ��ӦsAction
enum MSG_SMALL_ACTION
{
	MSG_SMALL_ACTION_NONE = 0,
	MSG_SMALL_ACTION_QUERY_NEWCARDPRIZE_INFO		= 1,	// ��ѯ���ֿ�������Ϣ   	C --> S
	MSG_SMALL_ACTION_RUN_LUA_SCRIPT					= 2,	// ִ��LUA�ű�				C --> S
	MSG_SMALL_ACTION_QUERY_SKILLPOINT_INFO			= 3,	// ��ѯ���ܵ���Ϣ			C <-> S
	MSG_SMALL_ACTION_GET_MONTH_CARD					= 4,	// ��ȡ�¿�					C <-> S
	MSG_SMALL_ACTION_SYN_ACTIVITY_TIME				= 5,	// ͬ���ʣ��ʱ��			C <-- S
	MSG_SMALL_ACTION_QUERY_BUY_POWER				= 6,	// ��ѯ����������Ϣ			C <-> S
	MSG_SMALL_ACTION_REQUEST_BUY_POWER				= 7,	// ����������				C <-> S
	MSG_SMALL_ACTION_QUERY_OTHER_USER_INFO			= 8,	// ��ѯ���������Ϣ			C --> S
	MSG_SMALL_ACTION_QUERY_TREASURE_POWER_INFO		= 9,	// ��ѯѰ��������Ϣ			C <-> S
	MSG_SMALL_ACTION_QUERY_EXITINFO					= 10,	// ��ѯ�˳�ʱ�ĸ������		C <-> S
};

// ������ö��, ��ӦsResult
enum MSG_SMALL_RESULT
{
	MSG_SMALL_RESULT_SUCC							= 0,
	MSG_SMALL_RESULT_ERROR							= 1,
};

typedef std::vector<UINT> VEC_SCORE;
typedef std::vector<UINT> VEC_ONLINEAWARDINFO;
//////////////////////////////////////////////////////////////////////////
//	����Э��Create��Processʱ, �����ÿ��������дһ������, ��Ҫ����, �ɶ��Ի�ܺ� 
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