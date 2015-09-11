////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan ChuangYou, All Rights Reserved
// Moudle: MsgGameUserTmpData.h
// Author: ����(Ding Le)
// Created: 2014-11-10
////////////////////////////////////////////////////////////////////////
#ifndef _GAMEKERNER_MSG_GAME_USER_TMP_DATA_H_
#define _GAMEKERNER_MSG_GAME_USER_TMP_DATA_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "./NetMsg.h"

enum MSG_TMP_DATA_ACTION
{
	MSG_TMP_DATA_ACT_ReqGetTmpData			= 1,	// �����ȡTmpData����			C --> S
	MSG_TMP_DATA_ACT_AckGetTmpData			= 2,	// ���������ȡTmpData����		C <-- S
	MSG_TMP_DATA_ACT_ReqSetTmpData			= 3,	// ��������TmpData����			C --> S
	MSG_TMP_DATA_ACT_AckSetTmpData			= 4,	// ������������TmpData����		C <-- S
	MSG_TMP_DATA_ACT_UpdateTmpData			= 5,	// ͬ��TmpData����				C <-- S
	MSG_TMP_DATA_ACT_AckClientTmpData		= 6,	// ���ؿͻ��������Զ���TmpData	C <-- S
};

enum MSG_TMP_DATA_RESULT
{
	MSG_TMP_DATA_RESULT_Succ		= 0,	// �ɹ�
	MSG_TMP_DATA_RESULT_Error		= 1,	// ʧ��
	MSG_TMP_DATA_RESULT_Beyond		= 2,	// TmpDataID������Χ
};

class CMsgGameUserTmpData : public game_kernel::CNetMsg
{
public:
	CMsgGameUserTmpData();
	virtual ~CMsgGameUserTmpData();

	virtual BOOL Create(char* pMsgBuf, DWORD dwSize);
	virtual void Process(void *pInfo);
	
	bool CreateMsg(int nAction, int nResult, int nTmpDataIndex = 0, int nEndFlag = 0);
	bool AppendParam(int nData);
	bool AppendTmpData(IN INT_VEC& vecInt);
	void SetMsgEnd();

private:
	void ProcessReqGetTmpData(OBJID idUser);
	void ProcessReqSetTmpData(OBJID idUser);

private:
	typedef struct  
	{
		MSG_NUM_2BIT sAction;
		MSG_NUM_2BIT sResult;

		MSG_NUM_4BIT nTmpDataID;	// TmpDataID
		MSG_NUM_4BIT nEndFlag;		// �������(0:û������1:����)
		MSG_NUM_4BIT nDataNum;
		MSG_NUM_4BIT arrData[1];
	}MSG_Info;

	MSG_Info* m_pInfo;
};

#endif // _GAMEKERNER_MSG_GAME_USER_TMP_DATA_H_