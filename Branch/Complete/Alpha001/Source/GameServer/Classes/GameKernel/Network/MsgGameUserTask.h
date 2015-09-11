////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan ChuangYou, All Rights Reserved
// Moudle: MsgGameUserTask.h
// Author: 丁乐(Ding Le)
// Created: 2014-11-13
////////////////////////////////////////////////////////////////////////
#ifndef _GAMEKERNER_MSG_GAME_USER_TASK_H_
#define _GAMEKERNER_MSG_GAME_USER_TASK_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "./NetMsg.h"

// 任务消息Action
enum MSG_USER_TASK_ACTION
{
	MSG_USER_TASK_ACT_QueryAllTask		= 1,	// 请求查询玩家任务			C --> S
	MSG_USER_TASK_ACT_ReturnAllTask		= 2,	// 返回请求查询玩家任务		C <-- S
	MSG_USER_TASK_ACT_ReqReceiveTask	= 3,	// 请求接受任务				C --> S
	MSG_USER_TASK_ACT_AckReceiveTask	= 4,	// 返回请求接受任务			C <-- S
	MSG_USER_TASK_ACT_ReqFinishTask		= 5,	// 请求提交任务				C --> S
	MSG_USER_TASK_ACT_AckFinishTask		= 6,	// 返回请求提交任务			C <-- S
	MSG_USER_TASK_ACT_ReqGiveupTask		= 7,	// 请求放弃任务				C --> S	
	MSG_USER_TASK_ACT_AckGiveupTask		= 8,	// 返回请求放弃任务			C <-- S	
	MSG_USER_TASK_ACT_UpdateUserTask	= 9,	// 同步玩家任务				C <-- S
};

// 任务消息结果
enum MSG_USER_TASK_RESULT
{
	MSG_USER_TASK_RESULT_Succ		= 0,	// 成功
	MSG_USER_TASK_RESULT_Error		= 1,	// 失败
	MSG_USER_TASK_RESULT_OverTime   = 2,	// 任务过期了
	MSG_USER_TASK_RESULT_Dissatisfy = 3,	// 没达到完成任务条件

};

class CMsgGameUserTask : public game_kernel::CNetMsg
{
public:
	CMsgGameUserTask();
	virtual ~CMsgGameUserTask();

	virtual BOOL Create(char* pMsgBuf, DWORD dwSize);
	virtual void Process(void *pInfo);

	bool CreateMsg(int nAction, int nResult, int nParam1 = 0, int nParam2 = 0, int nParam3 = 0);
	bool AppendParam(MSG_USER_TASK_DATA& taskData);

private:
	void ProcessReqReceiveTask(OBJID idUser);
	void ProcessReqFinishTask(OBJID idUser);
	void ProcessReqGiveupTask(OBJID idUser);

private:
	typedef struct  
	{
		MSG_NUM_2BIT		sAction;
		MSG_NUM_2BIT		sResult;

		MSG_NUM_4BIT		nParam1;
		MSG_NUM_4BIT		nParam2;
		MSG_NUM_4BIT		nParam3;
		MSG_NUM_4BIT		nTaskNum;	// 变长
		MSG_USER_TASK_DATA	arrTask[1];
	}MSG_Info;

	MSG_Info* m_pInfo;
};

#endif // _GAMEKERNER_MSG_GAME_USER_TASK_H_