////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan ChuangYou, All Rights Reserved
// Moudle: MsgGameUserMailList.h
// Author: ����(Ding Le)
// Created: 2014-11-18
////////////////////////////////////////////////////////////////////////
#ifndef _GAME_KERNER_MSG_GAME_USER_MAIL_LIST_H
#define _GAME_KERNER_MSG_GAME_USER_MAIL_LIST_H

#if _MSC_VER > 1000
#pragma once
#endif	// _MSC_VER > 1000

#include "./NetMsg.h"

// �ʼ��б�Э��Action
enum EMSG_MAIL_LIST_ACTION
{
	EMSG_MAIL_LIST_ACT_QueryMailList	= 1,	// �����ʼ��б�			C --> S
	EMSG_MAIL_LIST_ACT_ReturnMailList	= 2,	// ���������ʼ��б�		C <-- S
	EMSG_MAIL_LIST_ACT_NewMailNotify	= 3,	// ���ʼ�����			C <-- S	S <-> R
};

// �ʼ��б�Э����
enum EMSG_MAIL_LIST_RESULT
{
	EMSG_MAIL_LIST_RESULT_Succ	= 0,	// �ɹ�
	EMSG_MAIL_LIST_RESULT_Error	= 1,	// ʧ��
};

class CMsgGameUserMailList : public game_kernel::CNetMsg
{
public:
	CMsgGameUserMailList();
	virtual ~CMsgGameUserMailList();

	virtual BOOL Create(char* pMsgBuf, DWORD dwSize);
	virtual void Process(void *pInfo);

	bool CreateMsg(int nAction, int nResult, int nPage, int nPageSize, int nParam1 = 0, int nParam2 = 0);
	bool AppendParam(MSG_MAIL_LIST& mailList);
	void SetMsgEnd() {m_pInfo->sEndFlag = 1;}

private:
	void ProcessQueryMailList();

private:
	typedef struct  
	{
		MSG_NUM_2BIT		sAction;
		MSG_NUM_2BIT		sResult;

		MSG_NUM_4BIT		nPage;		// ҳ(��1��ʼ)
		MSG_NUM_4BIT		nPageSize;	// ÿҳ���ʼ�����
		MSG_NUM_4BIT		nParam1;
		MSG_NUM_4BIT		nParam2;
		MSG_NUM_2BIT		sEndFlag;	// �������(0:û������1:����)
		MSG_NUM_2BIT		sArrNum;	// �䳤
		MSG_MAIL_LIST		arrData[1];
	}MSG_Info;

	MSG_Info* m_pInfo;
};

#endif // _GAME_KERNER_MSG_GAME_USER_MAIL_LIST_H