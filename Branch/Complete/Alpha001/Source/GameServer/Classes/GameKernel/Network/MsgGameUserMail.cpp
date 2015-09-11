////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan ChuangYou, All Rights Reserved
// Moudle: MsgGameUserMail.cpp
// Author: 丁乐(Ding Le)
// Created: 2014-11-18
////////////////////////////////////////////////////////////////////////

#include "./MsgGameUserMail.h"
#include "./../User.h"
#include "./../UserMgr.h"
#include "./../UserMailMgr.h"

CMsgGameUserMail::CMsgGameUserMail()
{
	Init();
	m_pInfo = (MSG_Info*)m_bufMsg;
	m_unMsgType = _MSG_GAME_MAIL_OPT;
	m_unMsgSize = sizeof(MSG_Info);
}

CMsgGameUserMail::~CMsgGameUserMail()
{

}

BOOL CMsgGameUserMail::Create(char* pMsgBuf, DWORD dwSize)
{
	if (!CNetMsg::Create(pMsgBuf, dwSize))
	{
		return false;
	}
	if (_MSG_GAME_MAIL_OPT != this->GetType())
	{
		return false;
	}
	return true;
}

bool CMsgGameUserMail::CreateMsg(int nAction, int nResult, I64 i64MailID /*= 0i64*/, int nParam1 /*= 0*/, int nParam2 /*= 0*/)
{
	this->Init();
	m_unMsgType	= _MSG_GAME_MAIL_OPT;
	m_unMsgSize	= sizeof(MSG_Info) - sizeof(MSG_MAIL_DATA);

	m_pInfo->sAction = nAction;
	m_pInfo->sResult = nResult;
	m_pInfo->i64MailID = i64MailID;
	m_pInfo->nParam1 = nParam1;
	m_pInfo->nParam2 = nParam2;
	
	m_pInfo->nArrNum = 0;

	return true;
}

bool CMsgGameUserMail::AppendParam(MSG_MAIL_DATA& mail)
{
	CHECKF(sizeof(MSG_Info) + sizeof(MSG_MAIL_DATA) * m_pInfo->nArrNum < MAX_PACKETSIZE);
	m_pInfo->arrData[m_pInfo->nArrNum] = mail;
	m_unMsgSize = sizeof(MSG_Info) + sizeof(MSG_MAIL_DATA) * m_pInfo->nArrNum;
	m_pInfo->nArrNum++;
	return true;
}

void CMsgGameUserMail::Process(void *pInfo)
{
	DEBUG_TRY;
	OBJID idUser = pUserMgr->GetUserIDByMsg(this);
	CHECK(idUser);

	switch (m_pInfo->sAction)
	{
	case EMSG_MAIL_ACT_ReqOpenMail:
		{
			this->ProcessReqOpenMail(idUser);
		}
		break;
	case EMSG_MAIL_ACT_ReqGetItem:
		{
			this->ProcessGetItem(idUser);
		}
		break;
	case EMSG_MAIL_ACT_ReqUnreadMailCount:
		{
			pUserMailMgr->ProcessUnreadMailCount(idUser);
		}
		break;
	default:
		{
			tolog3("CMsgGameUserMail::Process unkonw action[%d], idUser[%u]", m_pInfo->sAction, idUser);
		}
		break;
	}
	DEBUG_CATCH("CMsgGameUserMail::Process()");
}

////////////////////////////////////////////////////////////////////////
// 请求打开邮件
void  CMsgGameUserMail::ProcessReqOpenMail(OBJID idUser)
{
	CHECK(idUser);
	I64 i64MailID = m_pInfo->i64MailID;
	CHECK(i64MailID);

	MSG_MAIL_DATA mail = {0};
	int nResult = pUserMailMgr->ProcessOpenMail(idUser, i64MailID, mail);
	CMsgGameUserMail msg;
	msg.CreateMsg(EMSG_MAIL_ACT_AckOpenMail, nResult, i64MailID);
	if (EMSG_MAIL_RESULT_Succ == nResult)
	{
		CHECK(msg.AppendParam(mail));
	}
	pUserMgr->SendMsg(idUser, &msg);
}

////////////////////////////////////////////////////////////////////////
// 请求获取邮件中的物品
void  CMsgGameUserMail::ProcessGetItem(OBJID idUser)
{
	CHECK(idUser);
	I64 i64MailID = m_pInfo->i64MailID;
	CHECK(i64MailID);

	MSG_MAIL_DATA mail = {0};
	int nResult = pUserMailMgr->ProcessGetItem(idUser, i64MailID, mail);
	CMsgGameUserMail msg;
	msg.CreateMsg(EMSG_MAIL_ACT_AckGetItem, nResult, i64MailID, mail.nStatus);
	pUserMgr->SendMsg(idUser, &msg);
}