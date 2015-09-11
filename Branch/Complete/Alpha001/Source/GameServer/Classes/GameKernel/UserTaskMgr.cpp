////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan ChuangYou, All Rights Reserved
// Moudle: UserTmpDataMgr.cpp
// Author: 丁乐(Ding Le)
// Created: 2014-11-7
////////////////////////////////////////////////////////////////////////
#include "./UserTaskMgr.h"
#include "./GameKernel.h"
#include "./UserTask.h"
#include "./UserMgr.h"
#include "./Network/MsgGameUserTask.h"

CUserTaskMgr* CUserTaskMgr::s_pInstance = NULL;
MYHEAP_IMPLEMENTATION(CUserTaskMgr, s_heap);

bool CUserTaskMgr::Init()
{
	CHECKF(pGameDatabase);
	m_pDefaultres = pGameDatabase->CreateDefaultRecordset(GAME_DB_NAME_USER_TASK);
	CHECKF(m_pDefaultres);
	return true;
}

void CUserTaskMgr::Release()
{
	for (ITER_MAP_USER_TASK iter = m_mapUserTask.begin(); iter != m_mapUserTask.end(); iter++)
	{
		SAFE_RELEASE(iter->second);
	}
	m_mapUserTask.clear();
	SAFE_RELEASE(m_pDefaultres);
}

////////////////////////////////////////////////////////////////////////
// 增加玩家
bool CUserTaskMgr::InitUser(OBJID idUser)
{
	CHECKF(idUser);
	CUserTask* pUserTask = CUserTask::CreateNew();
	CHECKF(pUserTask);
	if (!pUserTask->Init(idUser, m_pDefaultres))
	{
		SAFE_RELEASE(pUserTask);
		return false; 
	}
	if (false == m_mapUserTask.insert(make_pair(idUser, pUserTask)).second)
	{
		SAFE_RELEASE(pUserTask);
		return false;                                                                             
	}
	return true;
}

////////////////////////////////////////////////////////////////////////
// 删除玩家
bool CUserTaskMgr::ReleaseUser(OBJID idUser)
{
	CHECKF(idUser);
	CUserTask* pUserTask = this->GetUserTask(idUser);
	SAFE_RELEASE(pUserTask);
	m_mapUserTask.erase(idUser);
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description:  获取UserTask指针
CUserTask* CUserTaskMgr::GetUserTask(OBJID idUser) const
{
	CHECKF(idUser);
	CITER_MAP_USER_TASK iter = m_mapUserTask.find(idUser);
	if (iter == m_mapUserTask.end())
	{
		return NULL;
	}
	return iter->second;
}

////////////////////////////////////////////////////////////////////////
// 设置玩家任务数据
bool CUserTaskMgr::SetUserTaskData(OBJID idUser, OBJID idTask, EUSER_TASK eUserTask, int nData, int nUpdateType)
{
	CHECKF(idUser);
	CHECKF(idTask);
	CHECKF(eUserTask >= EUSER_TASK_TYPE && eUserTask <= EUSER_TASK_OVER_TIME);

	CUserTask* pUserTask = this->GetUserTask(idUser);
	CHECKF(pUserTask);
	return pUserTask->SetData(idTask, eUserTask, nData, nUpdateType);
}

////////////////////////////////////////////////////////////////////////
// 获取玩家任务数据
int CUserTaskMgr::GetUserTaskData(OBJID idUser, OBJID idTask, EUSER_TASK eUserTask) const
{
	CHECKF(idUser);
	CHECKF(idTask);
	CHECKF(eUserTask >= EUSER_TASK_TYPE && eUserTask <= EUSER_TASK_OVER_TIME);

	CUserTask* pUserTask = this->GetUserTask(idUser);
	CHECKF(pUserTask);
	return pUserTask->GetData(idTask, eUserTask);
}

////////////////////////////////////////////////////////////////////////
// 获取玩家所有任务
bool CUserTaskMgr::GetUserAllTask(OBJID idUser, VEC_MSG_USER_TASK& vecTask) const
{
	CHECKF(idUser);
	CUserTask* pUserTask = this->GetUserTask(idUser);
	CHECKF(pUserTask);
	return pUserTask->GetAllTask(vecTask);
}

////////////////////////////////////////////////////////////////////////
// 获取玩家任务ID
int CUserTaskMgr::GetUserTaskID(OBJID idUser, OBJID idTaskType) const
{
	CHECKF(idUser);
	CHECKF(idTaskType);
	CUserTask* pUserTask = this->GetUserTask(idUser);
	CHECKF(pUserTask);
	return pUserTask->GetTaskID(idTaskType);
}

////////////////////////////////////////////////////////////////////////
// 删除任务
bool CUserTaskMgr::DelTask(OBJID idUser, OBJID idTask)
{
	CHECKF(idUser);
	CUserTask* pUserTask = this->GetUserTask(idUser);
	CHECKF(pUserTask);
	return pUserTask->Del(idTask);
}

////////////////////////////////////////////////////////////////////////
// 增加任务
bool CUserTaskMgr::AddTask(OBJID idUser, OBJID idTaskType, OBJID idStep)
{
	CHECKF(idUser);
	CHECKF(idTaskType);
	CHECKF(idStep);
	//CHECKF(pConstTableMgr->GetTaskConfigData()->IsExist(idTaskType, idStep));
	CUserTask* pUserTask = this->GetUserTask(idUser);
	CHECKF(pUserTask);
	return pUserTask->Add(idTaskType, idStep);
}

////////////////////////////////////////////////////////////////////////
// 检查是否达到完成条件，达到后就更改任务状态
void CUserTaskMgr::CheckFinishCondition(OBJID idUser, OBJID idTask)
{
	CHECK(idUser);
	CHECK(idTask);
	CHECK_NOLOG(this->IsReceiveTask(idUser, idTask));

	OBJID idTaskType = this->GetUserTaskData(idUser, idTask, EUSER_TASK_TYPE);
	OBJID idStep = this->GetUserTaskData(idUser, idTask, EUSER_TASK_STEP);
	CHECK(idTaskType && idStep);

	//TASK_CONFIG_DATA taskConfig = {0};
	//CHECK(pConstTableMgr->GetTaskConfigData()->GetData(idTaskType, idStep, taskConfig));
	//int nNeedNum1 = taskConfig.nNeedNum1;
	//int nNeedNum2 = taskConfig.nNeedNum2;
	//int nNeedNum3 = taskConfig.nNeedNum3;

	//int nCount1 = this->GetUserTaskData(idUser, idTask, EUSER_TASK_COUNT1);
	//int nCount2 = this->GetUserTaskData(idUser, idTask, EUSER_TASK_COUNT2);
	//int nCount3 = this->GetUserTaskData(idUser, idTask, EUSER_TASK_COUNT3);

	//if (nCount1 >= nNeedNum1 && nCount2 >= nNeedNum2 && nCount3 >= nNeedNum3)	// 满足条件,修改任务状态
	//{
	//	if (ETASK_STATUS_Finish_Not_Submit != this->GetUserTaskData(idUser, idTask, EUSER_TASK_STATUS))
	//	{
	//		this->SetUserTaskData(idUser, idTask, EUSER_TASK_STATUS, ETASK_STATUS_Finish_Not_Submit, true);
	//	}
	//}
}

////////////////////////////////////////////////////////////////////////
// 检查需要类型是物品的 任务计数
void CUserTaskMgr::CheckItemTaskCount(OBJID idUser, OBJID idTask)
{
	OBJID idTaskType	= this->GetUserTaskData(idUser, idTask, EUSER_TASK_TYPE);
	OBJID idStep		= this->GetUserTaskData(idUser, idTask, EUSER_TASK_STEP);
	CHECK(idTaskType && idStep);

	//TASK_CONFIG_DATA taskConfig = {0};
	//CHECK(pConstTableMgr->GetTaskConfigData()->GetData(idTaskType, idStep, taskConfig));
	//int nNeedType1 = taskConfig.nNeedType1;
	//int nNeedType2 = taskConfig.nNeedType2;
	//int nNeedType3 = taskConfig.nNeedType3;

	//if (this->NeedTypeIsItem(nNeedType1))
	//{
	//	int nItemCount = pItemMgr->GetItemAmount(idUser, nNeedType1);
	//	this->SetUserTaskData(idUser, idTask, EUSER_TASK_COUNT1, nItemCount, true);
	//}
	//if (this->NeedTypeIsItem(nNeedType2))
	//{
	//	int nItemCount = pItemMgr->GetItemAmount(idUser, nNeedType2);
	//	this->SetUserTaskData(idUser, idTask, EUSER_TASK_COUNT1, nItemCount, true);
	//}
	//if (this->NeedTypeIsItem(nNeedType3))
	//{
	//	int nItemCount = pItemMgr->GetItemAmount(idUser, nNeedType3);
	//	this->SetUserTaskData(idUser, idTask, EUSER_TASK_COUNT1, nItemCount, true);
	//}
	this->CheckFinishCondition(idUser, idTask);
}

////////////////////////////////////////////////////////////////////////
// 任务需要类型是否是物品类型
bool CUserTaskMgr::NeedTypeIsItem(int nNeedType) const
{
	//return nNeedType >= ITEM_TYPE_BEGIN;
	return true;
}

////////////////////////////////////////////////////////////////////////
// 判断玩家任务是否存在 (脚本接口)
bool CUserTaskMgr::IsExistUserTask(OBJID idUser, OBJID idTaskType) const
{
	CHECKF(idUser);
	CHECKF(idTaskType);

	CUserTask* pUserTask = this->GetUserTask(idUser);
	CHECKF(pUserTask);
	return pUserTask->IsExistByType(idTaskType);
}

// 获得任务	(脚本接口)
bool CUserTaskMgr::GainTask(OBJID idUser, OBJID idTaskType, OBJID idStep)
{
	// 配置表没有此类型任务
	//CHECKF(pConstTableMgr->GetTaskConfigData()->IsExist(idTaskType, idStep));

	// 存在此类型任务
	if (IsExistUserTask(idUser, idTaskType))
	{
		return false;
	}

	// 增加任务并通知客户端
	CHECKF(this->AddTask(idUser, idTaskType, idStep));
	OBJID idTask = this->GetUserTaskID(idUser, idTaskType);
	this->NotifyUpdateTask(idUser, idTask, EUPDATA_TASK_TYPE_Add);
	return true;
}

////////////////////////////////////////////////////////////////////////
// 更新任务计数	(脚本接口) (适用于 需要类型为物品:增加/减少，非物品类型的增加)
void CUserTaskMgr::UpdateTaskCount(OBJID idUser, int nNeedType)
{
	CHECK(idUser);
	VEC_MSG_USER_TASK vecTask;
	this->GetUserAllTask(idUser, vecTask);	// 获取玩家的所有任务
	//for (ITER_VEC_MSG_USER_TASK iter = vecTask.begin(); iter != vecTask.end(); iter++)
	//{
	//	OBJID idTask		= iter->nTaskID;
	//	OBJID idTaskType	= iter->nTaskType;
	//	OBJID idStep		= iter->nStep;
	//	int nCount1			= iter->nCount1;
	//	int nCount2			= iter->nCount2;
	//	int nCount3			= iter->nCount3;

	//	CHECKC_NOLOG(this->IsReceiveTask(idUser, idTask));

	//	TASK_CONFIG_DATA taskConfig = {0};
	//	CHECKC(pConstTableMgr->GetTaskConfigData()->GetData(idTaskType, idStep, taskConfig));
	//	int nNeedType1 = taskConfig.nNeedType1;
	//	int nNeedType2 = taskConfig.nNeedType2;
	//	int nNeedType3 = taskConfig.nNeedType3;

	//	bool bUpdata = false;
	//	if (nNeedType1 == nNeedType)
	//	{
	//		int nTaskCount = nCount1 + 1;
	//		if (this->NeedTypeIsItem(nNeedType))	// 需要类型是物品，直接取物品个数
	//		{
	//			nTaskCount = pItemMgr->GetItemAmount(idUser, nNeedType);
	//		}
	//		this->SetUserTaskData(idUser, idTask, EUSER_TASK_COUNT1, nTaskCount, true);
	//		bUpdata = true;
	//	}
	//	if (nNeedType2 == nNeedType)
	//	{
	//		int nTaskCount = nCount2 + 1;
	//		if (this->NeedTypeIsItem(nNeedType))	// 需要类型是物品，直接取物品个数
	//		{
	//			nTaskCount = pItemMgr->GetItemAmount(idUser, nNeedType);
	//		}
	//		this->SetUserTaskData(idUser, idTask, EUSER_TASK_COUNT2, nTaskCount, true);
	//		bUpdata = true;
	//	}
	//	if (nNeedType3 == nNeedType)
	//	{
	//		int nTaskCount = nCount3 + 1;
	//		if (this->NeedTypeIsItem(nNeedType))	// 需要类型是物品，直接取物品个数
	//		{
	//			nTaskCount = pItemMgr->GetItemAmount(idUser, nNeedType);
	//		}
	//		this->SetUserTaskData(idUser, idTask, EUSER_TASK_COUNT3, nTaskCount, true);
	//		bUpdata = true;
	//	}
	//	this->CheckFinishCondition(idUser, idTask);
	//	if (bUpdata)	// 计数改变，通知客户端
	//	{
	//		this->NotifyUpdateTask(idUser, idTask, EUPDATA_TASK_TYPE_Alter);
	//	}
	//}
}

////////////////////////////////////////////////////////////////////////
// 减少任务计数 (适用于任务计数的减少)
void CUserTaskMgr::DelTaskCount(OBJID idUser, OBJID idIgnoreTask, int nNeedType, int nDelNum)
{
	CHECK(idUser);
	//VEC_MSG_USER_TASK vecTask;
	//this->GetUserAllTask(idUser, vecTask);	// 获取玩家的所有任务
	//for (ITER_VEC_MSG_USER_TASK iter = vecTask.begin(); iter != vecTask.end(); iter++)
	//{
	//	OBJID idTask		= iter->nTaskID;
	//	CHECKC_NOLOG(idIgnoreTask != idTask);

	//	OBJID idTaskType	= iter->nTaskType;
	//	OBJID idStep		= iter->nStep;
	//	int nCount1			= iter->nCount1;
	//	int nCount2			= iter->nCount2;
	//	int nCount3			= iter->nCount3;

	//	CHECKC_NOLOG(this->IsReceiveTask(idUser, idTask));

	//	TASK_CONFIG_DATA taskConfig = {0};
	//	CHECKC(pConstTableMgr->GetTaskConfigData()->GetData(idTaskType, idStep, taskConfig));
	//	int nNeedType1 = taskConfig.nNeedType1;
	//	int nNeedType2 = taskConfig.nNeedType2;
	//	int nNeedType3 = taskConfig.nNeedType3;

	//	bool bUpdata = false;
	//	if (nNeedType1 == nNeedType)
	//	{
	//		int nTaskCount = max(0, nCount1 - nDelNum);
	//		this->SetUserTaskData(idUser, idTask, EUSER_TASK_COUNT1, nTaskCount, true);
	//		bUpdata = true;
	//	}
	//	if (nNeedType2 == nNeedType)
	//	{
	//		int nTaskCount = max(0, nCount2 - nDelNum);
	//		this->SetUserTaskData(idUser, idTask, EUSER_TASK_COUNT2, nTaskCount, true);
	//		bUpdata = true;
	//	}
	//	if (nNeedType3 == nNeedType)
	//	{
	//		int nTaskCount = max(0, nCount3 - nDelNum);
	//		this->SetUserTaskData(idUser, idTask, EUSER_TASK_COUNT3, nTaskCount, true);
	//		bUpdata = true;
	//	}
	//	this->CheckFinishCondition(idUser, idTask);
	//	if (bUpdata)	// 计数改变，通知客户端
	//	{
	//		this->NotifyUpdateTask(idUser, idTask, EUPDATA_TASK_TYPE_Alter);
	//	}
	//}
}

////////////////////////////////////////////////////////////////////////
// 是否接受了任务	(脚本接口)
bool CUserTaskMgr::IsReceiveTask(OBJID idUser, OBJID idTask) const
{
	CHECKF(idUser);
	CHECKF(idTask);
	int nStatue = this->GetUserTaskData(idUser, idTask, EUSER_TASK_STATUS);
	return ((ETASK_STATUS_Receive == nStatue) || (ETASK_STATUS_Finish_Not_Submit == nStatue));
}

////////////////////////////////////////////////////////////////////////
// 能否提交		(脚本接口)
bool CUserTaskMgr::IsCanSubmit(OBJID idUser, OBJID idTask) const
{
	CHECKF(idUser);
	CHECKF(idTask);
	return ETASK_STATUS_Finish_Not_Submit == this->GetUserTaskData(idUser, idTask, EUSER_TASK_STATUS);
}

////////////////////////////////////////////////////////////////////////
// 接受任务
int CUserTaskMgr::ProcessReceiveTask(OBJID idUser, OBJID idTask)
{
	if (idUser < 0 || idTask < 0)
	{
		return MSG_USER_TASK_RESULT_Error;
	}

	// 任务已经接受
	if (ETASK_STATUS_Not_Receive != this->GetUserTaskData(idUser, idTask, EUSER_TASK_STATUS))
	{
		return MSG_USER_TASK_RESULT_Error;
	}

	OBJID idTaskType = this->GetUserTaskData(idUser, idTask, EUSER_TASK_TYPE);
	OBJID idStep = this->GetUserTaskData(idUser, idTask, EUSER_TASK_STEP);
	if (idTaskType < 0 || idStep < 0)
	{
		return MSG_USER_TASK_RESULT_Error;
	}

	unsigned int unCurrentTime = ::TimeGet(TIME_SECOND);
	//TASK_CONFIG_DATA taskConfig = {0};	// 任务配置数据
	//if (!pConstTableMgr->GetTaskConfigData()->GetData(idTaskType, idStep, taskConfig))
	//{
	//	return MSG_USER_TASK_RESULT_Error;
	//}
	//int nLimitTime = taskConfig.nLimitTime;
	//if (nLimitTime > 0)	// 限时任务
	//{
	//	this->SetUserTaskData(idUser, idTask, EUSER_TASK_OVER_TIME, unCurrentTime + nLimitTime, false);
	//}
	//this->SetUserTaskData(idUser, idTask, EUSER_TASK_STATUS, ETASK_STATUS_Receive, false);
	//this->SetUserTaskData(idUser, idTask, EUSER_TASK_BEGIN_TIME, unCurrentTime, true);
	//
	//// 如果任务需要类型是物品，要更新任务计数
	//this->CheckItemTaskCount(idUser, idTask);

	//// 通知更新任务
	//this->NotifyUpdateTask(idUser, idTask, EUPDATA_TASK_TYPE_Alter);

	//// 执行接受任务脚本
	//OBJID idReceiveAction = taskConfig.nReceiveAction;
	//pGameAction->ProcessAction(idReceiveAction, idUser, idTask, idTaskType, idStep);

	return MSG_USER_TASK_RESULT_Succ;
}

////////////////////////////////////////////////////////////////////////
// 查询任务列表
void CUserTaskMgr::ProcessQueryAllTask(OBJID idUser)
{
	CHECK(idUser);
	CMsgGameUserTask msg;
	int nResult = MSG_USER_TASK_RESULT_Succ;
	VEC_MSG_USER_TASK vecTask;
	if (!this->GetUserAllTask(idUser, vecTask))
	{
		nResult = MSG_USER_TASK_RESULT_Error;
	}
	msg.CreateMsg(MSG_USER_TASK_ACT_QueryAllTask, nResult);
	for (int i = 0; i < vecTask.size(); i++)
	{
		CHECK(msg.AppendParam(vecTask[i]));
	}
	pUserMgr->SendMsg(idUser, &msg);
}

////////////////////////////////////////////////////////////////////////
// 提交任务
int CUserTaskMgr::ProcessFinishTask(OBJID idUser, OBJID idTask)
{
	if (idUser < 0 || idTask < 0)
	{
		return MSG_USER_TASK_RESULT_Error;
	}

	OBJID idTaskType = this->GetUserTaskData(idUser, idTask, EUSER_TASK_TYPE);
	OBJID idStep = this->GetUserTaskData(idUser, idTask, EUSER_TASK_STEP);
	if (idTaskType < 0 || idStep < 0)
	{
		return MSG_USER_TASK_RESULT_Error;
	}
	//TASK_CONFIG_DATA taskConfig = {0};
	//if (!pConstTableMgr->GetTaskConfigData()->GetData(idTaskType, idStep, taskConfig))
	//{
	//	return MSG_USER_TASK_RESULT_Error;
	//}

	//unsigned int unCurrentTime = ::TimeGet(TIME_SECOND);
	//unsigned int unOverTime = this->GetUserTaskData(idUser, idTask, EUSER_TASK_OVER_TIME);
	//if (unOverTime > 0 && unCurrentTime > unOverTime)	// 任务过期了
	//{
	//	// 删除任务
	//	if (!this->DelTask(idUser, idTask))
	//	{
	//		return MSG_USER_TASK_RESULT_Error;
	//	}
	//	// 通知删除任务
	//	this->NotifyUpdateTask(idUser, idTask, EUPDATA_TASK_TYPE_Del);
	//	return MSG_USER_TASK_RESULT_OverTime;
	//}

	//// 没有达到提交任务的条件
	//if (false == IsCanSubmit(idUser, idTask))
	//{
	//	return MSG_USER_TASK_RESULT_Error;
	//}

	//// 需要类型是物品，删除物品
	//if (this->NeedTypeIsItem(taskConfig.nNeedType1) 
	//	&& !pItemMgr->SpendItem(idUser, taskConfig.nNeedType1, ITEM_FLOW_REASON_TASK_USED_d, idTask, taskConfig.nNeedNum1))
	//{
	//	return MSG_USER_TASK_RESULT_Error;
	//}
	//if (this->NeedTypeIsItem(taskConfig.nNeedType2)
	//	&& !pItemMgr->SpendItem(idUser, taskConfig.nNeedType2, ITEM_FLOW_REASON_TASK_USED_d, idTask, taskConfig.nNeedNum2))
	//{
	//	return MSG_USER_TASK_RESULT_Error;
	//}
	//if (this->NeedTypeIsItem(taskConfig.nNeedType3)
	//	&& pItemMgr->SpendItem(idUser, taskConfig.nNeedType3, ITEM_FLOW_REASON_TASK_USED_d, idTask, taskConfig.nNeedNum3))
	//{
	//	return MSG_USER_TASK_RESULT_Error;
	//}

	//// 减少需要此类型物品的任务计数
	//this->DelTaskCount(idUser, idTask, taskConfig.nNeedType1, taskConfig.nNeedNum1);
	//this->DelTaskCount(idUser, idTask, taskConfig.nNeedType2, taskConfig.nNeedNum2);
	//this->DelTaskCount(idUser, idTask, taskConfig.nNeedType3, taskConfig.nNeedNum3);

	//// 获取下一个任务
	//if (!this->GainNextTask(idUser, idTask))
	//{
	//	return MSG_USER_TASK_RESULT_Error;
	//}

	//// 执行提交任务脚本
	//OBJID idFinishAction = taskConfig.nFinishAction;
	//pGameAction->ProcessAction(idFinishAction, idUser, idTaskType, idStep);

	return MSG_USER_TASK_RESULT_Succ;
}

////////////////////////////////////////////////////////////////////////
// 放弃任务
int CUserTaskMgr::ProcessGiveupTask(OBJID idUser, OBJID idTask)
{
	if (idUser < 0 || idTask < 0)
	{
		return MSG_USER_TASK_RESULT_Error;
	}
	
	OBJID idTaskType = this->GetUserTaskData(idUser, idTask, EUSER_TASK_TYPE);
	OBJID idStep = this->GetUserTaskData(idUser, idTask, EUSER_TASK_STEP);
	if (idTaskType < 0 || idStep < 0)
	{
		return MSG_USER_TASK_RESULT_Error;
	}
	//TASK_CONFIG_DATA taskConfig = {0};	// 任务配置表数据
	//if (!pConstTableMgr->GetTaskConfigData()->GetData(idTaskType, idStep, taskConfig))
	//{
	//	return MSG_USER_TASK_RESULT_Error;
	//}

	//// 删除任务
	//if (!this->DelTask(idUser, idTask))
	//{
	//	return MSG_USER_TASK_RESULT_Error;
	//}

	//// 通知删除任务
	//this->NotifyUpdateTask(idUser, idTask, EUPDATA_TASK_TYPE_Del);

	//// 执行放弃任务脚本
	//OBJID idGiveupAction = taskConfig.nGiveupAction;
	//pGameAction->ProcessAction(idGiveupAction, idUser, idTaskType, idStep);

	return MSG_USER_TASK_RESULT_Succ;
}

////////////////////////////////////////////////////////////////////////
// 通知客户端更新任务
void CUserTaskMgr::NotifyUpdateTask(OBJID idUser, OBJID idTask, EUPDATA_TASK_TYPE eUpdataType)
{
	CHECK(idUser);
	CHECK(idTask);
	CHECK(eUpdataType >= EUPDATA_TASK_TYPE_Beg && eUpdataType < EUPDATA_TASK_TYPE_End);

	CMsgGameUserTask msg;
	msg.CreateMsg(MSG_USER_TASK_ACT_UpdateUserTask, MSG_USER_TASK_RESULT_Succ, eUpdataType);
	MSG_USER_TASK_DATA task = {0};

	// 增加和修改任务
	if (EUPDATA_TASK_TYPE_Add == eUpdataType || EUPDATA_TASK_TYPE_Alter == eUpdataType)
	{
		CUserTask* pUserTask = this->GetUserTask(idUser);
		CHECK(pUserTask);
		CHECK(pUserTask->GetTask(idTask, task));
		CHECK(msg.AppendParam(task));
	}
	else if (EUPDATA_TASK_TYPE_Del == eUpdataType)	// 删除任务(先从CUserTask中删除，再通知删除)
	{
		task.nTaskID = idTask;
		CHECK(msg.AppendParam(task));
	}
	else
	{
		tolog4("Unknow UpdataTaskType UserID:[%d], TaskID:[%d], UpdataTaskType:[%d]!", idUser, idTask, (int)eUpdataType);
	}
	pUserMgr->SendMsg(idUser, &msg);
}

////////////////////////////////////////////////////////////////////////
// 获得下一个任务(不是链式任务就删除)
bool CUserTaskMgr::GainNextTask(OBJID idUser, OBJID idTask)
{
	OBJID idTaskType = this->GetUserTaskData(idUser, idTask, EUSER_TASK_TYPE);
	OBJID idStep = this->GetUserTaskData(idUser, idTask, EUSER_TASK_STEP);

	// 是链式任务且不是最后一个任务
	//if (pConstTableMgr->GetTaskConfigData()->IsTaskChain(idTaskType)
	//	&& !pConstTableMgr->GetTaskConfigData()->IsLastStep(idTaskType, idStep))
	//{
	//	unsigned int unCurrentTime = ::TimeGet(TIME_SECOND);
	//	TASK_CONFIG_DATA taskConfig = {0};	// 任务配置数据
	//	CHECKF(pConstTableMgr->GetTaskConfigData()->GetNextTask(idTaskType, idStep, taskConfig));

	//	int nLimitTime = taskConfig.nLimitTime;
	//	if (nLimitTime > 0)	// 限时任务
	//	{
	//		this->SetUserTaskData(idUser, idTask, EUSER_TASK_OVER_TIME, unCurrentTime + nLimitTime, false);
	//	}
	//	this->SetUserTaskData(idUser, idTask, EUSER_TASK_STEP, taskConfig.idStep, false);
	//	this->SetUserTaskData(idUser, idTask, EUSER_TASK_STATUS, ETASK_STATUS_Receive, false);
	//	this->SetUserTaskData(idUser, idTask, EUSER_TASK_COUNT1, 0, false);
	//	this->SetUserTaskData(idUser, idTask, EUSER_TASK_COUNT2, 0, false);
	//	this->SetUserTaskData(idUser, idTask, EUSER_TASK_COUNT3, 0, false);
	//	this->SetUserTaskData(idUser, idTask, EUSER_TASK_BEGIN_TIME, unCurrentTime, true);

	//	// 通知更新
	//	this->NotifyUpdateTask(idUser, idTask, EUPDATA_TASK_TYPE_Alter);
	//}
	//else	// 不是链式任务 或 是链式任务的最后一步, 就删除原来的任务
	//{
	//	// 删除任务并通知客户端
	//	CHECKF(this->DelTask(idUser, idTask));
	//	this->NotifyUpdateTask(idUser, idTask, EUPDATA_TASK_TYPE_Del);
	//}
	return true;
}



