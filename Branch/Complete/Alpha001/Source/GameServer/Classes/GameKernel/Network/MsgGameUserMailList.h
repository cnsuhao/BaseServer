////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan ChuangYou, All Rights Reserved
// Moudle: MsgGameUserMailList.h
// Author: 丁乐(Ding Le)
// Created: 2014-11-18
////////////////////////////////////////////////////////////////////////
#ifndef _GAME_KERNER_MSG_GAME_USER_MAIL_LIST_H
#define _GAME_KERNER_MSG_GAME_USER_MAIL_LIST_H

#if _MSC_VER > 1000
#pragma once
#endif	// _MSC_VER > 1000

#include "./NetMsg.h"

// 邮件列表协议Action
enum EMSG_MAIL_LIST_ACTION
{
	EMSG_MAIL_LIST_ACT_QueryMailList	= 1,	// 请求邮件列表			C --> S
	EMSG_MAIL_LIST_ACT_ReturnMailList	= 2,	// 返回请求邮件列表		C <-- S
	EMSG_MAIL_LIST_ACT_NewMailNotify	= 3,	// 新邮件提醒			C <-- S	S <-> R
};

// 邮件列表协议结果
enum EMSG_MAIL_LIST_RESULT
{
	EMSG_MAIL_LIST_RESULT_Succ	= 0,	// 成功
	EMSG_MAIL_LIST_RESULT_Error	= 1,	// 失败
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

		MSG_NUM_4BIT		nPage;		// 页(从1开始)
		MSG_NUM_4BIT		nPageSize;	// 每页的邮件个数
		MSG_NUM_4BIT		nParam1;
		MSG_NUM_4BIT		nParam2;
		MSG_NUM_2BIT		sEndFlag;	// 结束标记(0:没结束，1:结束)
		MSG_NUM_2BIT		sArrNum;	// 变长
		MSG_MAIL_LIST		arrData[1];
	}MSG_Info;

	MSG_Info* m_pInfo;
};

#endif // _GAME_KERNER_MSG_GAME_USER_MAIL_LIST_H