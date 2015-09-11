////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan ChuangYou, All Rights Reserved
// Moudle: MsgGameUserTask.h
// Author: ����(Ding Le)
// Created: 2014-11-13
////////////////////////////////////////////////////////////////////////
#ifndef _GAMEKERNER_MSG_GAME_USER_TASK_H_
#define _GAMEKERNER_MSG_GAME_USER_TASK_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "./NetMsg.h"

// ������ϢAction
enum MSG_USER_TASK_ACTION
{
	MSG_USER_TASK_ACT_QueryAllTask		= 1,	// �����ѯ�������			C --> S
	MSG_USER_TASK_ACT_ReturnAllTask		= 2,	// ���������ѯ�������		C <-- S
	MSG_USER_TASK_ACT_ReqReceiveTask	= 3,	// �����������				C --> S
	MSG_USER_TASK_ACT_AckReceiveTask	= 4,	// ���������������			C <-- S
	MSG_USER_TASK_ACT_ReqFinishTask		= 5,	// �����ύ����				C --> S
	MSG_USER_TASK_ACT_AckFinishTask		= 6,	// ���������ύ����			C <-- S
	MSG_USER_TASK_ACT_ReqGiveupTask		= 7,	// �����������				C --> S	
	MSG_USER_TASK_ACT_AckGiveupTask		= 8,	// ���������������			C <-- S	
	MSG_USER_TASK_ACT_UpdateUserTask	= 9,	// ͬ���������				C <-- S
};

// ������Ϣ���
enum MSG_USER_TASK_RESULT
{
	MSG_USER_TASK_RESULT_Succ		= 0,	// �ɹ�
	MSG_USER_TASK_RESULT_Error		= 1,	// ʧ��
	MSG_USER_TASK_RESULT_OverTime   = 2,	// ���������
	MSG_USER_TASK_RESULT_Dissatisfy = 3,	// û�ﵽ�����������

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
		MSG_NUM_4BIT		nTaskNum;	// �䳤
		MSG_USER_TASK_DATA	arrTask[1];
	}MSG_Info;

	MSG_Info* m_pInfo;
};

#endif // _GAMEKERNER_MSG_GAME_USER_TASK_H_