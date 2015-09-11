////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan ChuangYou, All Rights Reserved
// Moudle: MsgGameUserTask.cpp
// Author: 丁乐(Ding Le)
// Created: 2014-11-13
////////////////////////////////////////////////////////////////////////
#include "./MsgGameUserTask.h"
#include "../UserMgr.h"
#include "../User.h"
#include "../UserTaskMgr.h"

CMsgGameUserTask::CMsgGameUserTask()
{
	Init();
	m_pInfo = (MSG_Info*)m_bufMsg;
	m_unMsgType = _MSG_GAME_TASK;
	m_unMsgSize = sizeof(MSG_Info);
}

CMsgGameUserTask::~CMsgGameUserTask()
{

}

BOOL CMsgGameUserTask::Create(char* pMsgBuf, DWORD dwSize)
{
	if (!CNetMsg::Create(pMsgBuf, dwSize))
	{
		return false;
	}
	if (_MSG_GAME_TASK != this->GetType())
	{
		return false;
	}
	return true;
}

bool CMsgGameUserTask::CreateMsg(int nAction, int nResult, int nParam1 /*= 0*/, int nParam2 /*= 0*/, int nParam3 /*= 0*/)
{
	this->Init();
	m_unMsgType	= _MSG_GAME_TASK;
	m_unMsgSize	= sizeof(MSG_Info) - sizeof(MSG_USER_TASK_DATA);

	m_pInfo->sAction = nAction;
	m_pInfo->sResult = nResult;
	m_pInfo->nParam1 = nParam1;
	m_pInfo->nParam2 = nParam2;
	m_pInfo->nParam3 = nParam3;
	m_pInfo->nTaskNum = 0;

	return true;
}

bool CMsgGameUserTask::AppendParam(MSG_USER_TASK_DATA& taskData)
{
	CHECKF(sizeof(MSG_Info) + sizeof(MSG_USER_TASK_DATA) * m_pInfo->nTaskNum < MAX_PACKETSIZE);
	m_pInfo->arrTask[m_pInfo->nTaskNum] = taskData;
	m_unMsgSize = sizeof(MSG_Info) + sizeof(MSG_USER_TASK_DATA) * m_pInfo->nTaskNum;
	m_pInfo->nTaskNum++;
	return true;
}

void CMsgGameUserTask::Process(void *pInfo)
{
	DEBUG_TRY;
	OBJID idUser = pUserMgr->GetUserIDByMsg(this);
	CHECK(idUser);

	switch (m_pInfo->sAction)
	{
	case MSG_USER_TASK_ACT_QueryAllTask:
		{
			pUserTaskMgr->ProcessQueryAllTask(idUser);
		}
		break;
	case MSG_USER_TASK_ACT_ReqReceiveTask:
		{
			this->ProcessReqReceiveTask(idUser);
		}
		break;
	case MSG_USER_TASK_ACT_ReqFinishTask:
		{
			this->ProcessReqFinishTask(idUser);
		}
		break;
	case MSG_USER_TASK_ACT_ReqGiveupTask:
		{
			this->ProcessReqGiveupTask(idUser);
		}
		break;
	default:
		{
			tolog3("CMsgGameUserTask::Process unkonw action[%d], idUser[%u]", m_pInfo->sAction, idUser);
		}
		break;
	}
	DEBUG_CATCH("CMsgGameUserTask::Process()");
}

// 请求接受任务
void CMsgGameUserTask::ProcessReqReceiveTask(OBJID idUser)
{
	CMsgGameUserTask msg;
	OBJID idTask = m_pInfo->nParam1;
	int nResult = pUserTaskMgr->ProcessReceiveTask(idUser, idTask);
	msg.CreateMsg(MSG_USER_TASK_ACT_AckReceiveTask, nResult);
	pUserMgr->SendMsg(idUser, &msg);
}

// 请求提交任务
void CMsgGameUserTask::ProcessReqFinishTask(OBJID idUser)
{
	CMsgGameUserTask msg;
	OBJID idTask = m_pInfo->nParam1;
	int nResult = pUserTaskMgr->ProcessFinishTask(idUser, idTask);
	msg.CreateMsg(MSG_USER_TASK_ACT_AckFinishTask, nResult);
	pUserMgr->SendMsg(idUser, &msg);
}

// 请求放弃任务
void CMsgGameUserTask::ProcessReqGiveupTask(OBJID idUser)
{
	CMsgGameUserTask msg;
	OBJID idTask = m_pInfo->nParam1;
	int nResult = pUserTaskMgr->ProcessGiveupTask(idUser, idTask);
	msg.CreateMsg(MSG_USER_TASK_ACT_AckGiveupTask, nResult);
	pUserMgr->SendMsg(idUser, &msg);
}