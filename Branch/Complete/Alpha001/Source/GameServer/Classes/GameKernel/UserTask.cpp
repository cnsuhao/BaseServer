////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan ChuangYou, All Rights Reserved
// Moudle: UserTask.cpp
// Author: ����(Ding Le)
// Created: 2014-11-12
////////////////////////////////////////////////////////////////////////

#include "./UserTask.h"
#include "./GameKernel.h"

MYHEAP_IMPLEMENTATION(CUserTask, s_heap);

CUserTask::CUserTask()
{
	m_idUser = ID_NONE;
	m_pDefaultRes = NULL;
}

CUserTask::~CUserTask()
{
	m_pDefaultRes = NULL;	// ��ָ���ɹ������ͷ�
	this->SaveAll();
	m_mapUserTask.clear();	// ����ָ��ֱ�����
}

////////////////////////////////////////////////////////////////////////
// ��ʼ��
bool CUserTask::Init(OBJID idUser, IRecordset* pDefaultRes)
{
	CHECKF(idUser);
	CHECKF(pDefaultRes);
	CHECKF(pGameDatabase);
	m_idUser = idUser;
	m_pDefaultRes = pDefaultRes;
	m_mapUserTask.clear();

	CMxyString strSql("SELECT * FROM %s WHERE user_id = %u order by type, step", GAME_DB_NAME_USER_TASK, idUser);
	RecordsetPtr pRes = pGameDatabase->CreateNewRecordset(strSql.c_str());
	CHECKF(pRes);

	RecordPtr pRecord = NULL;
	OBJID idTask = ID_NONE;
	for(int i = 0; i < pRes->RecordCount(); i++, pRes->MoveNext())
	{
		pRecord = pRes->CreateNewRecord();
		CHECKC(pRecord);
		idTask = pRecord->GetInt(EUSER_TASK_ID);
		m_mapUserTask[idTask] = pRecord;
	}
	this->CheckTaskStatus();
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description:  �������״̬
void CUserTask::CheckTaskStatus()
{
	for (ITER_TABLE_DATA iter = m_mapUserTask.begin(); iter != m_mapUserTask.end(); iter++)
	{
		RecordPtr pRecord = iter->second;
		CHECKC(pRecord);
		OBJID idTask = pRecord->GetInt(EUSER_TASK_ID);
		int nStatus = pRecord->GetInt(EUSER_TASK_STATUS);
		CHECKC_NOLOG(ETASK_STATUS_Not_Receive != nStatus);
		
		OBJID idTaskType = pRecord->GetInt(EUSER_TASK_TYPE);
		OBJID idStep = pRecord->GetInt(EUSER_TASK_STEP);

		int nCount1 = pRecord->GetInt(EUSER_TASK_COUNT1);
		int nCount2 = pRecord->GetInt(EUSER_TASK_COUNT2);
		int nCount3 = pRecord->GetInt(EUSER_TASK_COUNT3);

		//TASK_CONFIG_DATA taskConfig = {0};
		//CHECK(pConstTableMgr->GetTaskConfigData()->GetData(idTaskType, idStep, taskConfig));
		//int nNeedNum1 = taskConfig.nNeedNum1;
		//int nNeedNum2 = taskConfig.nNeedNum2;
		//int nNeedNum3 = taskConfig.nNeedNum3;

		//// �����ύ����,�޸�����״̬
		//if (nCount1 >= nNeedNum1 && nCount2 >= nNeedNum2 && nCount3 >= nNeedNum3)	
		//{
		//	if (ETASK_STATUS_Finish_Not_Submit != nStatus)
		//	{
		//		this->SetData(idTask, EUSER_TASK_STATUS, ETASK_STATUS_Finish_Not_Submit, true);
		//	}
		//}
		//else
		//{
		//	if (ETASK_STATUS_Finish_Not_Submit == nStatus)	// ״̬����ȷ
		//	{
		//		this->SetData(idTask, EUSER_TASK_STATUS, ETASK_STATUS_Receive, true);
		//	}
		//}
	}
}

////////////////////////////////////////////////////////////////////////
// ����task����
bool CUserTask::SetData(OBJID idTask, EUSER_TASK eUserTask, int nData, int nUpdateType)
{
	CHECKF(idTask);
	CHECKF(eUserTask >= EUSER_TASK_TYPE && eUserTask <= EUSER_TASK_OVER_TIME);
	RecordPtr pRecord = this->GetUserTaskRecord(idTask);
	CHECKF(pRecord);
	pRecord->SetInt(eUserTask, nData);
	if (DBUPDATE_ASYNC == nUpdateType || DBUPDATE_SYNC == nUpdateType)
	{
		pRecord->UpdateRecord(nUpdateType);
	}
	return true;
}

////////////////////////////////////////////////////////////////////////
// ��ȡtask����
int CUserTask::GetData(OBJID idTask, EUSER_TASK eUserTask) const
{
	CHECKF(idTask);
	CHECKF(eUserTask >= EUSER_TASK_ID && eUserTask <= EUSER_TASK_OVER_TIME);
	RecordPtr pRecord = this->GetUserTaskRecord(idTask);
	CHECKF(pRecord);
	return pRecord->GetInt(eUserTask);
}

////////////////////////////////////////////////////////////////////////
// �жϴ���
bool CUserTask::IsExist(OBJID idTask) const
{
	CHECKF(idTask);
	return (m_mapUserTask.end() != m_mapUserTask.find(idTask));
}

////////////////////////////////////////////////////////////////////////
// �жϴ���
bool CUserTask::IsExistByType(OBJID idTaskType) const
{
	CHECKF(idTaskType);
	RecordPtr pRecord = NULL;
	for (CITER_TABLE_DATA iter = m_mapUserTask.begin(); iter != m_mapUserTask.end(); iter++)
	{
		pRecord = iter->second;
		CHECKC(pRecord);
		if (pRecord->GetInt(EUSER_TASK_TYPE) == idTaskType)
		{
			return true;
		}
	}
	return false;
}

////////////////////////////////////////////////////////////////////////
// ����һ��������
bool CUserTask::Add(OBJID idTaskType, OBJID idStep)
{
	CHECKF(m_pDefaultRes);
	CHECKF(m_idUser);
	CHECKF(false == this->IsExistByType(idTaskType));// ͬ�����������ظ�

	RecordPtr pRecord = m_pDefaultRes->CreateNewRecord();
	pRecord->SetInt(EUSER_TASK_USER_ID,		m_idUser);
	pRecord->SetInt(EUSER_TASK_TYPE,		idTaskType);
	pRecord->SetInt(EUSER_TASK_STEP,		idStep);
	pRecord->SetInt(EUSER_TASK_STATUS,		ETASK_STATUS_Not_Receive);
	pRecord->SetInt(EUSER_TASK_COUNT1,		0);
	pRecord->SetInt(EUSER_TASK_COUNT2,		0);
	pRecord->SetInt(EUSER_TASK_COUNT3,		0);
	pRecord->SetInt(EUSER_TASK_BEGIN_TIME,	0);
	pRecord->SetInt(EUSER_TASK_OVER_TIME,	0);

	OBJID idKey = pRecord->InsertRecord();
	CHECKF(idKey);
	m_mapUserTask[idKey] = pRecord;
	return true;
}

////////////////////////////////////////////////////////////////////////
// ɾ��һ������
bool CUserTask::Del(OBJID idTask)
{
	CHECKF(idTask);
	CHECKF(this->IsExist(idTask));

	RecordPtr pRecord = this->GetUserTaskRecord(idTask);
	CHECKF(pRecord);
	CHECKF(pRecord->DeleteRecord(DBUPDATE_ASYNC));
	m_mapUserTask.erase(idTask);	// ����ָ��ֱ��erase()
	return true;
}

////////////////////////////////////////////////////////////////////////
// ��ȡ�����¼��
RecordPtr CUserTask::GetUserTaskRecord(OBJID idTask) const
{
	CITER_TABLE_DATA iter = m_mapUserTask.find(idTask);
	if (iter != m_mapUserTask.end())
	{
		RecordPtr pRecord = iter->second;
		CHECKF(pRecord);
		return pRecord;
	}
	return NULL;
}

////////////////////////////////////////////////////////////////////////
// ��ȡ�����������
bool CUserTask::GetAllTask(VEC_MSG_USER_TASK& vecTask)
{
	RecordPtr pRecord = NULL;
	vecTask.clear();
	for (ITER_TABLE_DATA iter = m_mapUserTask.begin(); iter != m_mapUserTask.end(); iter++)
	{
		pRecord = iter->second;
		CHECKC(pRecord);
		MSG_USER_TASK_DATA task = {0};
		task.nTaskID	= pRecord->GetInt(EUSER_TASK_ID);
		task.nTaskType	= pRecord->GetInt(EUSER_TASK_TYPE);
		task.nStep		= pRecord->GetInt(EUSER_TASK_STEP);
		task.nStatus	= pRecord->GetInt(EUSER_TASK_STATUS);
		task.nCount1	= pRecord->GetInt(EUSER_TASK_COUNT1);
		task.nCount2	= pRecord->GetInt(EUSER_TASK_COUNT2);
		task.nCount3	= pRecord->GetInt(EUSER_TASK_COUNT3);
		task.nBeginTime = pRecord->GetInt(EUSER_TASK_BEGIN_TIME);
		task.nOverTime	= pRecord->GetInt(EUSER_TASK_OVER_TIME);
		vecTask.push_back(task);
	}
	return true;
}

////////////////////////////////////////////////////////////////////////
// ��ȡ�������
bool CUserTask::GetTask(OBJID idTask, MSG_USER_TASK_DATA& task)
{
	CHECKF(idTask);

	RecordPtr pRecord = this->GetUserTaskRecord(idTask);
	CHECKF(pRecord);
	task.nTaskID	= pRecord->GetInt(EUSER_TASK_ID);
	task.nTaskType	= pRecord->GetInt(EUSER_TASK_TYPE);
	task.nStep		= pRecord->GetInt(EUSER_TASK_STEP);
	task.nStatus	= pRecord->GetInt(EUSER_TASK_STATUS);
	task.nCount1	= pRecord->GetInt(EUSER_TASK_COUNT1);
	task.nCount2	= pRecord->GetInt(EUSER_TASK_COUNT2);
	task.nCount3	= pRecord->GetInt(EUSER_TASK_COUNT3);
	task.nBeginTime = pRecord->GetInt(EUSER_TASK_BEGIN_TIME);
	task.nOverTime	= pRecord->GetInt(EUSER_TASK_OVER_TIME);
	return true;
}

////////////////////////////////////////////////////////////////////////
// ��ȡ�������ID
OBJID CUserTask::GetTaskID(OBJID idTaskType) const
{
	CHECKF(idTaskType);
	RecordPtr pRecord = NULL;
	for (CITER_TABLE_DATA iter = m_mapUserTask.begin(); iter != m_mapUserTask.end(); iter++)
	{
		pRecord = iter->second;
		CHECKC(pRecord);
		if (pRecord->GetInt(EUSER_TASK_TYPE) == idTaskType)
		{
			return pRecord->GetInt(EUSER_TASK_ID);
		}
	}
	return ID_NONE;
}


///////////////////////////////////////////////////////////////////////
// ��ȡ�����������
void CUserTask::SaveAll()
{
	RecordPtr pRecord = NULL;
	for (ITER_TABLE_DATA iter = m_mapUserTask.begin(); iter != m_mapUserTask.end(); iter++)
	{
		pRecord = iter->second;
		CHECKC(pRecord);
		pRecord->UpdateRecord();
	}
}