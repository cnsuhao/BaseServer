////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan ChuangYou, All Rights Reserved
// Moudle: MsgLoginKickReason.cpp
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Created: 2014-11-4
////////////////////////////////////////////////////////////////////////
#include "./MsgLoginKickReason.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CMsgLoginKickReason::CMsgLoginKickReason()
{
	Init();
	m_pInfo	=(MSG_Info *)m_bufMsg;
	m_unMsgType	=_MSG_LOGIN_KICK_REASON;
}

CMsgLoginKickReason::~CMsgLoginKickReason()
{
	
}

//////////////////////////////////////////////////////////////////////////
BOOL CMsgLoginKickReason::Create(char* pMsgBuf, DWORD dwSize)
{
	if (!login_kernel::CNetMsg::Create(pMsgBuf, dwSize))
		return false;
	
	if(_MSG_LOGIN_KICK_REASON != this->GetType())
		return false;
	
	return true;
}

////////////////////////////////////////////////////////////////////////
bool CMsgLoginKickReason::CreateInfo(int nReason, int nParam /*= 0*/)
{
	this->Init();
	m_unMsgType	= _MSG_LOGIN_KICK_REASON;
	m_unMsgSize	= sizeof(MSG_Info);
	
	m_pInfo->nReason	= nReason;
	m_pInfo->nParam		= nParam;

	return true;
}
