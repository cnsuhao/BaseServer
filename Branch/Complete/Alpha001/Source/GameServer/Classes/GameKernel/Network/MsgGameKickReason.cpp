////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan ChuangYou, All Rights Reserved
// Moudle: MsgGameKickReason.cpp
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Created: 2014-11-7
////////////////////////////////////////////////////////////////////////
#include "./MsgGameKickReason.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CMsgGameKickReason::CMsgGameKickReason()
{
	Init();
	m_pInfo	=(MSG_Info *)m_bufMsg;
	m_unMsgType	=_MSG_GAME_KICK_REASON;
}

CMsgGameKickReason::~CMsgGameKickReason()
{
	
}

//////////////////////////////////////////////////////////////////////////
BOOL CMsgGameKickReason::Create(char* pMsgBuf, DWORD dwSize)
{
	if (!game_kernel::CNetMsg::Create(pMsgBuf, dwSize))
		return false;
	
	if(_MSG_GAME_KICK_REASON != this->GetType())
		return false;
	
	return true;
}

////////////////////////////////////////////////////////////////////////
bool CMsgGameKickReason::CreateInfo(int nReason, int nParam /*= 0*/)
{
	this->Init();
	m_unMsgType	= _MSG_GAME_KICK_REASON;
	m_unMsgSize	= sizeof(MSG_Info);
	
	m_pInfo->nReason	= nReason;
	m_pInfo->nParam		= nParam;
	return true;
}
