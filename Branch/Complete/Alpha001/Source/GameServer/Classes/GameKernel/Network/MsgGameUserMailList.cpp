////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan ChuangYou, All Rights Reserved
// Moudle: MsgGameUserMailList.cpp
// Author: 丁乐(Ding Le)
// Created: 2014-11-18
////////////////////////////////////////////////////////////////////////

#include "./MsgGameUserMailList.h"
#include "./../User.h"
#include "./../UserMgr.h"
#include "./../UserMailMgr.h"

CMsgGameUserMailList::CMsgGameUserMailList()
{
	Init();
	m_pInfo = (MSG_Info*)m_bufMsg;
	m_unMsgType = _MSG_GAME_MAIL_LIST;
	m_unMsgSize = sizeof(MSG_Info);
}

CMsgGameUserMailList::~CMsgGameUserMailList()
{

}

BOOL CMsgGameUserMailList::Create(char* pMsgBuf, DWORD dwSize)
{
	if (!CNetMsg::Create(pMsgBuf, dwSize))
	{
		return false;
	}
	if (_MSG_GAME_MAIL_LIST != this->GetType())
	{
		return false;
	}
	return true;
}

bool CMsgGameUserMailList::CreateMsg(int nAction, int nResult, int nPage, int nPageSize, int nParam1 /*= 0*/, int nParam2 /*= 0*/)
{
	this->Init();
	m_unMsgType	= _MSG_GAME_MAIL_LIST;
	m_unMsgSize	= sizeof(MSG_Info) - sizeof(MSG_MAIL_LIST);

	m_pInfo->sAction = nAction;
	m_pInfo->sResult = nResult;
	m_pInfo->nPage   = nPage;
	m_pInfo->nPageSize = nPageSize;
	m_pInfo->nParam1 = nParam1;
	m_pInfo->nParam2 = nParam2;
	m_pInfo->sEndFlag = 0;
	m_pInfo->sArrNum = 0;

	return true;
}

bool CMsgGameUserMailList::AppendParam(MSG_MAIL_LIST& mailList)
{
	CHECKF_NOLOG(sizeof(MSG_Info) + sizeof(MSG_MAIL_LIST) * m_pInfo->sArrNum < MAX_PACKETSIZE);
	m_pInfo->arrData[m_pInfo->sArrNum] = mailList;
	m_unMsgSize = sizeof(MSG_Info) + sizeof(MSG_MAIL_LIST) * m_pInfo->sArrNum;
	m_pInfo->sArrNum++;
	return true;
}

void CMsgGameUserMailList::Process(void *pInfo)
{
	DEBUG_TRY;
	switch (m_pInfo->sAction)
	{
	case EMSG_MAIL_LIST_ACT_QueryMailList:
		{
			this->ProcessQueryMailList();
		}
		break;
	case EMSG_MAIL_LIST_ACT_NewMailNotify:	// 关系服 --> 游服(直接转发给客户端)
		{
			CHECK(!this->IsClientMsg());	// 不接受玩家发包
			OBJID idReceiver = m_pInfo->nParam1;
			pUserMgr->SendMsg(idReceiver, this);
		}
		break;
	default:
		{
			tolog2("CMsgGameUserMailList::Process unkonw action[%d]", m_pInfo->sAction);
		}
		break;
	}
	DEBUG_CATCH("CMsgGameUserMailList::Process()");
}

////////////////////////////////////////////////////////////////////////
// 请求邮件列表
void CMsgGameUserMailList::ProcessQueryMailList()
{
	OBJID idUser = pUserMgr->GetUserIDByMsg(this);
	CHECK(idUser);

	int nPage = m_pInfo->nPage;
	int nPageSize = m_pInfo->nPageSize;
	CHECK(nPage > 0 && nPageSize > 0);

	VEC_MAIL_LIST mailList;
	int nResult = pUserMailMgr->QueryMailList(idUser, nPage, nPageSize, mailList);
	CMsgGameUserMailList msg;
	msg.CreateMsg(EMSG_MAIL_LIST_ACT_ReturnMailList, nResult, nPage, nPageSize);
	for (int i = 0; i < mailList.size(); i++)
	{
		if (!msg.AppendParam(mailList[i]))
		{
			pUserMgr->SendMsg(idUser, &msg);
			msg.CreateMsg(EMSG_MAIL_LIST_ACT_ReturnMailList, nResult, nPage, nPageSize);
			CHECK(msg.AppendParam(mailList[i]));
		}
	}
	msg.SetMsgEnd();
	pUserMgr->SendMsg(idUser, &msg);
}