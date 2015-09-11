////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan ChuangYou, All Rights Reserved
// Moudle: UserTask.h
// Author: ����(Ding Le)
// Created: 2014-11-12
////////////////////////////////////////////////////////////////////////
#ifndef _GAME_KERNER_USER_TASK_H_
#define _GAME_KERNER_USER_TASK_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "./../share/define.h"

// ����״̬ö��
enum ETASK_STATUS
{
	ETASK_STATUS_Begin				= 0,
	ETASK_STATUS_Not_Receive		= ETASK_STATUS_Begin,	// δ����
	ETASK_STATUS_Receive			= 1,					// ����
	ETASK_STATUS_Submit				= 2,					// �ύ
	ETASK_STATUS_Finish_Not_Submit	= 3,					// �����������Ҵﵽ���������δ�ύ
	ETASK_STATUS_End,
};

class CUserTask
{
	// �ڴ湹����ʽ
public:
	static CUserTask*	CreateNew()	{return new CUserTask;}
	bool				Init(OBJID idUser, IRecordset* pDefaultRes);
	void				Release()	{delete this;}
	MYHEAP_DECLARATION(s_heap);

protected:
	CUserTask();
	virtual ~CUserTask();

	// �߼��ӿ�
public:
	bool SetData(OBJID idTask, EUSER_TASK eUserTask, int nData, int nUpdateType);
	int GetData(OBJID idTask, EUSER_TASK eUserTask) const;
	bool IsExist(OBJID idTask) const;
	bool IsExistByType(OBJID idTaskType) const;
	bool Add(OBJID idTaskType, OBJID idStep);
	bool Del(OBJID idTask);
	bool GetAllTask(VEC_MSG_USER_TASK& vecTask);
	bool GetTask(OBJID idTask, MSG_USER_TASK_DATA& task);
	OBJID GetTaskID(OBJID idTaskType) const;

private:
	RecordPtr GetUserTaskRecord(OBJID idTask) const;
	void SaveAll();
	void CheckTaskStatus();

protected:
	MAP_TABLE_DATA	m_mapUserTask;
	OBJID			m_idUser;
	IRecordset*		m_pDefaultRes;
};
#endif // _GAME_KERNER_USER_TASK_H_