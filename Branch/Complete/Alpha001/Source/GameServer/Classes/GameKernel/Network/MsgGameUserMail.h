////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan ChuangYou, All Rights Reserved
// Moudle: MsgGameUserMail.h
// Author: ����(Ding Le)
// Created: 2014-11-18
////////////////////////////////////////////////////////////////////////
#ifndef _GAME_KERNER_MSG_GAME_USER_MAIL_H
#define _GAME_KERNER_MSG_GAME_USER_MAIL_H

#if _MSC_VER > 1000
#pragma once
#endif	// _MSC_VER > 1000

#include "./NetMsg.h"


// �ʼ�����Э��Action
enum EMSG_MAIL_ACTION
{
	EMSG_MAIL_ACT_ReqOpenMail			= 1,	// ������ʼ�			C --> S
	EMSG_MAIL_ACT_AckOpenMail			= 2,	// ����������ʼ�		C <-- S
	EMSG_MAIL_ACT_ReqGetItem			= 3,	// �����ȡ�ʼ���Ʒ		C --> S
	EMSG_MAIL_ACT_AckGetItem			= 4,	// ���������ȡ�ʼ���Ʒ	C <-- S
	EMSG_MAIL_ACT_ReqUnreadMailCount	= 5,	// ����δ���ʼ�����		C --> S
	EMSG_MAIL_ACT_AckUnreadMailCount	= 6,	// ��������δ���ʼ�����	C <-- S
};

// �ʼ�����Э����
enum EMSG_MAIL_RESULT
{
	EMSG_MAIL_RESULT_Succ	= 0,	// �ɹ�
	EMSG_MAIL_RESULT_Error	= 1,	// ʧ��
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

		MSG_NUM_8BIT		i64MailID;	// �ʼ�ID
		MSG_NUM_4BIT		nParam1;
		MSG_NUM_4BIT		nParam2;
		MSG_NUM_4BIT		nArrNum;	// �䳤
		MSG_MAIL_DATA		arrData[1];
	}MSG_Info;

	MSG_Info* m_pInfo;
};

#endif // _GAME_KERNER_MSG_GAME_USER_MAIL_H