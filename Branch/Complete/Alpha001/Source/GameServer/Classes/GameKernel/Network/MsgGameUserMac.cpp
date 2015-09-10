////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan ChuangYou, All Rights Reserved
// Moudle: MsgGameUserMac.cpp
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Created: 2014-12-20
////////////////////////////////////////////////////////////////////////
#include "./MsgGameUserMac.h"
#include "./../UserMgr.h"
#include "./../User.h"

//////////////////////////////////////////////////////////////////////////
CMsgGameUserMac::CMsgGameUserMac()
{
	Init();
	m_pInfo = (MSG_Info*)m_bufMsg;
	m_unMsgType = _MSG_GAME_USER_MAC;
	m_unMsgSize = sizeof(MSG_Info);
}

//////////////////////////////////////////////////////////////////////////
CMsgGameUserMac::~CMsgGameUserMac()
{

}

//////////////////////////////////////////////////////////////////////////
BOOL CMsgGameUserMac::Create( char* pMsgBuf, DWORD dwSize )
{
	if (!game_kernel::CNetMsg::Create(pMsgBuf, dwSize))
		return false;

	if(_MSG_GAME_USER_MAC != this->GetType())
		return false;

	return true;
}

//////////////////////////////////////////////////////////////////////////
void CMsgGameUserMac::Process( void *pInfo )
{
	DEBUG_TRY;
	//CUser* pUser = pUserMgr->GetUserByMsg(this);
	//CHECK(pUser);
	//if (pUser->SetMac(m_pInfo->szMac))
	//{
	//	return;
	//}

	//if (pTalkMgr->GetGmCmdNeedMacFlag())
	//{
	//	pUserMgr->KickUserByUser(pUser->GetID(), KICK_REASON_GM_MAC_ERROR);
	//}
			
	DEBUG_CATCH("CMsgGameUserMac::Process");
}
