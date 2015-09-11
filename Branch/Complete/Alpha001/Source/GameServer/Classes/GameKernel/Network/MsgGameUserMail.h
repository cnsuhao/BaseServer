////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan ChuangYou, All Rights Reserved
// Moudle: MsgGameUserMail.h
// Author: 丁乐(Ding Le)
// Created: 2014-11-18
////////////////////////////////////////////////////////////////////////
#ifndef _GAME_KERNER_MSG_GAME_USER_MAIL_H
#define _GAME_KERNER_MSG_GAME_USER_MAIL_H

#if _MSC_VER > 1000
#pragma once
#endif	// _MSC_VER > 1000

#include "./NetMsg.h"


// 邮件操作协议Action
enum EMSG_MAIL_ACTION
{
	EMSG_MAIL_ACT_ReqOpenMail			= 1,	// 请求打开邮件			C --> S
	EMSG_MAIL_ACT_AckOpenMail			= 2,	// 返回请求打开邮件		C <-- S
	EMSG_MAIL_ACT_ReqGetItem			= 3,	// 请求获取邮件物品		C --> S
	EMSG_MAIL_ACT_AckGetItem			= 4,	// 返回请求获取邮件物品	C <-- S
	EMSG_MAIL_ACT_ReqUnreadMailCount	= 5,	// 请求未读邮件数量		C --> S
	EMSG_MAIL_ACT_AckUnreadMailCount	= 6,	// 返回请求未读邮件数量	C <-- S
};

// 邮件操作协议结果
enum EMSG_MAIL_RESULT
{
	EMSG_MAIL_RESULT_Succ	= 0,	// 成功
	EMSG_MAIL_RESULT_Error	= 1,	// 失败
};

class CMsgGameUserMail : public game_kernel::CNetMsg
{
public:
	CMsgGameUserMail();
	virtual ~CMsgGameUserMail();

	virtual BOOL Create(char* pMsgBuf, DWORD dwSize);
	virtual void Process(void *pInfo);

	bool CreateMsg(int nAction, int nResult, I64 i64MailID = 0i64, int nParam1 = 0, int nParam2 = 0);
	bool AppendParam(MSG_MAIL_DATA& mail);

private:
	void ProcessReqOpenMail(OBJID idUser);
	void ProcessGetItem(OBJID idUser);

private:
	typedef struct  
	{
		MSG_NUM_2BIT		sAction;
		MSG_NUM_2BIT		sResult;

		MSG_NUM_8BIT		i64MailID;	// 邮件ID
		MSG_NUM_4BIT		nParam1;
		MSG_NUM_4BIT		nParam2;
		MSG_NUM_4BIT		nArrNum;	// 变长
		MSG_MAIL_DATA		arrData[1];
	}MSG_Info;

	MSG_Info* m_pInfo;
};

#endif // _GAME_KERNER_MSG_GAME_USER_MAIL_H