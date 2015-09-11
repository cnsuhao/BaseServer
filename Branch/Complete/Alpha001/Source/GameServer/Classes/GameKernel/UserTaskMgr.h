////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan ChuangYou, All Rights Reserved
// Moudle: UserTmpDataMgr.h
// Author: 丁乐(Ding Le)
// Created: 2014-11-7
////////////////////////////////////////////////////////////////////////
#ifndef _GAME_KERNER_USER_TASK_MGR_H_
#define _GAME_KERNER_USER_TASK_MGR_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "./../share/define.h"

class CUserTask;

typedef std::map<OBJID, CUserTask*>					MAP_USER_TASK;
typedef std::map<OBJID, CUserTask*>::iterator		ITER_MAP_USER_TASK;
typedef std::map<OBJID, CUserTask*>::const_iterator	CITER_MAP_USER_TASK;


class CUserTaskMgr
{
	// 单例实现
public:
	static CUserTaskMgr* GetInstance(void)	{ if (NULL == s_pInstance) s_pInstance = new CUserTaskMgr; return s_pInstance;}
	static void DelInstance(void)			{ SAFE_DELETE(s_pInstance); }
	bool Init();
	void Release();
	MYHEAP_DECLARATION(s_heap);

private:
	CUserTaskMgr() {m_pDefaultres = NULL;}
	virtual ~CUserTaskMgr() {}
	CUserTaskMgr(CUserTaskMgr& ){}
	static CUserTaskMgr* s_pInstance;

public:
	bool InitUser(OBJID idUser);
	bool ReleaseUser(OBJID idUser);

private:
	CUserTask*	GetUserTask(OBJID idUser)	const;

// 获取/修改任务数据接口
public:
	bool SetUserTaskData(OBJID idUser, OBJID idTask, EUSER_TASK eUserTask, int nData, int nUpdateType);
	int GetUserTaskData(OBJID idUser, OBJID idTask, EUSER_TASK eUserTask) const;
	bool GetUserAllTask(OBJID idUser, VEC_MSG_USER_TASK& vecTask) const;
	int GetUserTaskID(OBJID idUser, OBJID idTaskType) const;
	bool DelTask(OBJID idUser, OBJID idTask);
	bool AddTask(OBJID idUser, OBJID idTaskType, OBJID idStep);

// 内部处理函数
private:
	void CheckFinishCondition(OBJID idUser, OBJID idTask);
	void CheckItemTaskCount(OBJID idUser, OBJID idTask);
	bool NeedTypeIsItem(int nNeedType) const;
	void DelTaskCount(OBJID idUser, OBJID idIgnoreTask, int nNeedType, int nDelNum);

// 脚本接口
public:
	bool IsExistUserTask(OBJID idUser, OBJID idTaskType) const;
	bool GainTask(OBJID idUser, OBJID idTaskType, OBJID idStep);
	void UpdateTaskCount(OBJID idUser, int nNeedType);
	bool IsReceiveTask(OBJID idUser, OBJID idTask) const;
	bool IsCanSubmit(OBJID idUser, OBJID idTask) const;

// 处理消息函数
public:
	void ProcessQueryAllTask(OBJID idUser);
	int ProcessReceiveTask(OBJID idUser, OBJID idTask);
	int ProcessFinishTask(OBJID idUser, OBJID idTask);
	int ProcessGiveupTask(OBJID idUser, OBJID idTask);
	bool GainNextTask(OBJID idUser, OBJID idTask);
	void NotifyUpdateTask(OBJID idUser, OBJID idTask, EUPDATA_TASK_TYPE eUpdataType);

private:
	MAP_USER_TASK		m_mapUserTask;
	IRecordset*			m_pDefaultres;
};

#define pUserTaskMgr CUserTaskMgr::GetInstance()

#endif // end of _GAME_KERNER_USER_TASK_MGR_H_