////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan ChuangYou, All Rights Reserved
// Moudle: UserTmpDataMgr.cpp
// Author: ����(Ding Le)
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
// �������
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
// ɾ�����
bool CUserTaskMgr::ReleaseUser(OBJID idUser)
{
	CHECKF(idUser);
	CUserTask* pUserTask = this->GetUserTask(idUser);
	SAFE_RELEASE(pUserTask);
	m_mapUserTask.erase(idUser);
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description:  ��ȡUserTaskָ��
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
// ���������������
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
// ��ȡ�����������
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
// ��ȡ�����������
bool CUserTaskMgr::GetUserAllTask(OBJID idUser, VEC_MSG_USER_TASK& vecTask) const
{
	CHECKF(idUser);
	CUserTask* pUserTask = this->GetUserTask(idUser);
	CHECKF(pUserTask);
	return pUserTask->GetAllTask(vecTask);
}

////////////////////////////////////////////////////////////////////////
// ��ȡ�������ID
int CUserTaskMgr::GetUserTaskID(OBJID idUser, OBJID idTaskType) const
{
	CHECKF(idUser);
	CHECKF(idTaskType);
	CUserTask* pUserTask = this->GetUserTask(idUser);
	CHECKF(pUserTask);
	return pUserTask->GetTaskID(idTaskType);
}

////////////////////////////////////////////////////////////////////////
// ɾ������
bool CUserTaskMgr::DelTask(OBJID idUser, OBJID idTask)
{
	CHECKF(idUser);
	CUserTask* pUserTask = this->GetUserTask(idUser);
	CHECKF(pUserTask);
	return pUserTask->Del(idTask);
}

////////////////////////////////////////////////////////////////////////
// ��������
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
// ����Ƿ�ﵽ����������ﵽ��͸�������״̬
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

	//if (nCount1 >= nNeedNum1 && nCount2 >= nNeedNum2 && nCount3 >= nNeedNum3)	// ��������,�޸�����״̬
	//{
	//	if (ETASK_STATUS_Finish_Not_Submit != this->GetUserTaskData(idUser, idTask, EUSER_TASK_STATUS))
	//	{
	//		this->SetUserTaskData(idUser, idTask, EUSER_TASK_STATUS, ETASK_STATUS_Finish_Not_Submit, true);
	//	}
	//}
}

////////////////////////////////////////////////////////////////////////
// �����Ҫ��������Ʒ�� �������
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
// ������Ҫ�����Ƿ�����Ʒ����
bool CUserTaskMgr::NeedTypeIsItem(int nNeedType) const
{
	//return nNeedType >= ITEM_TYPE_BEGIN;
	return true;
}

////////////////////////////////////////////////////////////////////////
// �ж���������Ƿ���� (�ű��ӿ�)
bool CUserTaskMgr::IsExistUserTask(OBJID idUser, OBJID idTaskType) const
{
	CHECKF(idUser);
	CHECKF(idTaskType);

	CUserTask* pUserTask = this->GetUserTask(idUser);
	CHECKF(pUserTask);
	return pUserTask->IsExistByType(idTaskType);
}

// �������	(�ű��ӿ�)
bool CUserTaskMgr::GainTask(OBJID idUser, OBJID idTaskType, OBJID idStep)
{
	// ���ñ�û�д���������
	//CHECKF(pConstTableMgr->GetTaskConfigData()->IsExist(idTaskType, idStep));

	// ���ڴ���������
	if (IsExistUserTask(idUser, idTaskType))
	{
		return false;
	}

	// ��������֪ͨ�ͻ���
	CHECKF(this->AddTask(idUser, idTaskType, idStep));
	OBJID idTask = this->GetUserTaskID(idUser, idTaskType);
	this->NotifyUpdateTask(idUser, idTask, EUPDATA_TASK_TYPE_Add);
	return true;
}

////////////////////////////////////////////////////////////////////////
// �����������	(�ű��ӿ�) (������ ��Ҫ����Ϊ��Ʒ:����/���٣�����Ʒ���͵�����)
void CUserTaskMgr::UpdateTaskCount(OBJID idUser, int nNeedType)
{
	CHECK(idUser);
	VEC_MSG_USER_TASK vecTask;
	this->GetUserAllTask(idUser, vecTask);	// ��ȡ��ҵ���������
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
	//		if (this->NeedTypeIsItem(nNeedType))	// ��Ҫ��������Ʒ��ֱ��ȡ��Ʒ����
	//		{
	//			nTaskCount = pItemMgr->GetItemAmount(idUser, nNeedType);
	//		}
	//		this->SetUserTaskData(idUser, idTask, EUSER_TASK_COUNT1, nTaskCount, true);
	//		bUpdata = true;
	//	}
	//	if (nNeedType2 == nNeedType)
	//	{
	//		int nTaskCount = nCount2 + 1;
	//		if (this->NeedTypeIsItem(nNeedType))	// ��Ҫ��������Ʒ��ֱ��ȡ��Ʒ����
	//		{
	//			nTaskCount = pItemMgr->GetItemAmount(idUser, nNeedType);
	//		}
	//		this->SetUserTaskData(idUser, idTask, EUSER_TASK_COUNT2, nTaskCount, true);
	//		bUpdata = true;
	//	}
	//	if (nNeedType3 == nNeedType)
	//	{
	//		int nTaskCount = nCount3 + 1;
	//		if (this->NeedTypeIsItem(nNeedType))	// ��Ҫ��������Ʒ��ֱ��ȡ��Ʒ����
	//		{
	//			nTaskCount = pItemMgr->GetItemAmount(idUser, nNeedType);
	//		}
	//		this->SetUserTaskData(idUser, idTask, EUSER_TASK_COUNT3, nTaskCount, true);
	//		bUpdata = true;
	//	}
	//	this->CheckFinishCondition(idUser, idTask);
	//	if (bUpdata)	// �����ı䣬֪ͨ�ͻ���
	//	{
	//		this->NotifyUpdateTask(idUser, idTask, EUPDATA_TASK_TYPE_Alter);
	//	}
	//}
}

////////////////////////////////////////////////////////////////////////
// ����������� (��������������ļ���)
void CUserTaskMgr::DelTaskCount(OBJID idUser, OBJID idIgnoreTask, int nNeedType, int nDelNum)
{
	CHECK(idUser);
	//VEC_MSG_USER_TASK vecTask;
	//this->GetUserAllTask(idUser, vecTask);	// ��ȡ��ҵ���������
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
	//	if (bUpdata)	// �����ı䣬֪ͨ�ͻ���
	//	{
	//		this->NotifyUpdateTask(idUser, idTask, EUPDATA_TASK_TYPE_Alter);
	//	}
	//}
}

////////////////////////////////////////////////////////////////////////
// �Ƿ����������	(�ű��ӿ�)
bool CUserTaskMgr::IsReceiveTask(OBJID idUser, OBJID idTask) const
{
	CHECKF(idUser);
	CHECKF(idTask);
	int nStatue = this->GetUserTaskData(idUser, idTask, EUSER_TASK_STATUS);
	return ((ETASK_STATUS_Receive == nStatue) || (ETASK_STATUS_Finish_Not_Submit == nStatue));
}

////////////////////////////////////////////////////////////////////////
// �ܷ��ύ		(�ű��ӿ�)
bool CUserTaskMgr::IsCanSubmit(OBJID idUser, OBJID idTask) const
{
	CHECKF(idUser);
	CHECKF(idTask);
	return ETASK_STATUS_Finish_Not_Submit == this->GetUserTaskData(idUser, idTask, EUSER_TASK_STATUS);
}

////////////////////////////////////////////////////////////////////////
// ��������
int CUserTaskMgr::ProcessReceiveTask(OBJID idUser, OBJID idTask)
{
	if (idUser < 0 || idTask < 0)
	{
		return MSG_USER_TASK_RESULT_Error;
	}

	// �����Ѿ�����
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
	//TASK_CONFIG_DATA taskConfig = {0};	// ������������
	//if (!pConstTableMgr->GetTaskConfigData()->GetData(idTaskType, idStep, taskConfig))
	//{
	//	return MSG_USER_TASK_RESULT_Error;
	//}
	//int nLimitTime = taskConfig.nLimitTime;
	//if (nLimitTime > 0)	// ��ʱ����
	//{
	//	this->SetUserTaskData(idUser, idTask, EUSER_TASK_OVER_TIME, unCurrentTime + nLimitTime, false);
	//}
	//this->SetUserTaskData(idUser, idTask, EUSER_TASK_STATUS, ETASK_STATUS_Receive, false);
	//this->SetUserTaskData(idUser, idTask, EUSER_TASK_BEGIN_TIME, unCurrentTime, true);
	//
	//// ���������Ҫ��������Ʒ��Ҫ�����������
	//this->CheckItemTaskCount(idUser, idTask);

	//// ֪ͨ��������
	//this->NotifyUpdateTask(idUser, idTask, EUPDATA_TASK_TYPE_Alter);

	//// ִ�н�������ű�
	//OBJID idReceiveAction = taskConfig.nReceiveAction;
	//pGameAction->ProcessAction(idReceiveAction, idUser, idTask, idTaskType, idStep);

	return MSG_USER_TASK_RESULT_Succ;
}

////////////////////////////////////////////////////////////////////////
// ��ѯ�����б�
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
// �ύ����
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
	//if (unOverTime > 0 && unCurrentTime > unOverTime)	// ���������
	//{
	//	// ɾ������
	//	if (!this->DelTask(idUser, idTask))
	//	{
	//		return MSG_USER_TASK_RESULT_Error;
	//	}
	//	// ֪ͨɾ������
	//	this->NotifyUpdateTask(idUser, idTask, EUPDATA_TASK_TYPE_Del);
	//	return MSG_USER_TASK_RESULT_OverTime;
	//}

	//// û�дﵽ�ύ���������
	//if (false == IsCanSubmit(idUser, idTask))
	//{
	//	return MSG_USER_TASK_RESULT_Error;
	//}

	//// ��Ҫ��������Ʒ��ɾ����Ʒ
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

	//// ������Ҫ��������Ʒ���������
	//this->DelTaskCount(idUser, idTask, taskConfig.nNeedType1, taskConfig.nNeedNum1);
	//this->DelTaskCount(idUser, idTask, taskConfig.nNeedType2, taskConfig.nNeedNum2);
	//this->DelTaskCount(idUser, idTask, taskConfig.nNeedType3, taskConfig.nNeedNum3);

	//// ��ȡ��һ������
	//if (!this->GainNextTask(idUser, idTask))
	//{
	//	return MSG_USER_TASK_RESULT_Error;
	//}

	//// ִ���ύ����ű�
	//OBJID idFinishAction = taskConfig.nFinishAction;
	//pGameAction->ProcessAction(idFinishAction, idUser, idTaskType, idStep);

	return MSG_USER_TASK_RESULT_Succ;
}

////////////////////////////////////////////////////////////////////////
// ��������
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
	//TASK_CONFIG_DATA taskConfig = {0};	// �������ñ�����
	//if (!pConstTableMgr->GetTaskConfigData()->GetData(idTaskType, idStep, taskConfig))
	//{
	//	return MSG_USER_TASK_RESULT_Error;
	//}

	//// ɾ������
	//if (!this->DelTask(idUser, idTask))
	//{
	//	return MSG_USER_TASK_RESULT_Error;
	//}

	//// ֪ͨɾ������
	//this->NotifyUpdateTask(idUser, idTask, EUPDATA_TASK_TYPE_Del);

	//// ִ�з�������ű�
	//OBJID idGiveupAction = taskConfig.nGiveupAction;
	//pGameAction->ProcessAction(idGiveupAction, idUser, idTaskType, idStep);

	return MSG_USER_TASK_RESULT_Succ;
}

////////////////////////////////////////////////////////////////////////
// ֪ͨ�ͻ��˸�������
void CUserTaskMgr::NotifyUpdateTask(OBJID idUser, OBJID idTask, EUPDATA_TASK_TYPE eUpdataType)
{
	CHECK(idUser);
	CHECK(idTask);
	CHECK(eUpdataType >= EUPDATA_TASK_TYPE_Beg && eUpdataType < EUPDATA_TASK_TYPE_End);

	CMsgGameUserTask msg;
	msg.CreateMsg(MSG_USER_TASK_ACT_UpdateUserTask, MSG_USER_TASK_RESULT_Succ, eUpdataType);
	MSG_USER_TASK_DATA task = {0};

	// ���Ӻ��޸�����
	if (EUPDATA_TASK_TYPE_Add == eUpdataType || EUPDATA_TASK_TYPE_Alter == eUpdataType)
	{
		CUserTask* pUserTask = this->GetUserTask(idUser);
		CHECK(pUserTask);
		CHECK(pUserTask->GetTask(idTask, task));
		CHECK(msg.AppendParam(task));
	}
	else if (EUPDATA_TASK_TYPE_Del == eUpdataType)	// ɾ������(�ȴ�CUserTask��ɾ������֪ͨɾ��)
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
// �����һ������(������ʽ�����ɾ��)
bool CUserTaskMgr::GainNextTask(OBJID idUser, OBJID idTask)
{
	OBJID idTaskType = this->GetUserTaskData(idUser, idTask, EUSER_TASK_TYPE);
	OBJID idStep = this->GetUserTaskData(idUser, idTask, EUSER_TASK_STEP);

	// ����ʽ�����Ҳ������һ������
	//if (pConstTableMgr->GetTaskConfigData()->IsTaskChain(idTaskType)
	//	&& !pConstTableMgr->GetTaskConfigData()->IsLastStep(idTaskType, idStep))
	//{
	//	unsigned int unCurrentTime = ::TimeGet(TIME_SECOND);
	//	TASK_CONFIG_DATA taskConfig = {0};	// ������������
	//	CHECKF(pConstTableMgr->GetTaskConfigData()->GetNextTask(idTaskType, idStep, taskConfig));

	//	int nLimitTime = taskConfig.nLimitTime;
	//	if (nLimitTime > 0)	// ��ʱ����
	//	{
	//		this->SetUserTaskData(idUser, idTask, EUSER_TASK_OVER_TIME, unCurrentTime + nLimitTime, false);
	//	}
	//	this->SetUserTaskData(idUser, idTask, EUSER_TASK_STEP, taskConfig.idStep, false);
	//	this->SetUserTaskData(idUser, idTask, EUSER_TASK_STATUS, ETASK_STATUS_Receive, false);
	//	this->SetUserTaskData(idUser, idTask, EUSER_TASK_COUNT1, 0, false);
	//	this->SetUserTaskData(idUser, idTask, EUSER_TASK_COUNT2, 0, false);
	//	this->SetUserTaskData(idUser, idTask, EUSER_TASK_COUNT3, 0, false);
	//	this->SetUserTaskData(idUser, idTask, EUSER_TASK_BEGIN_TIME, unCurrentTime, true);

	//	// ֪ͨ����
	//	this->NotifyUpdateTask(idUser, idTask, EUPDATA_TASK_TYPE_Alter);
	//}
	//else	// ������ʽ���� �� ����ʽ��������һ��, ��ɾ��ԭ��������
	//{
	//	// ɾ������֪ͨ�ͻ���
	//	CHECKF(this->DelTask(idUser, idTask));
	//	this->NotifyUpdateTask(idUser, idTask, EUPDATA_TASK_TYPE_Del);
	//}
	return true;
}



