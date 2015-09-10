//////////////////////////////////////////////////////////////////////////
//// Copyright(c) 2011-2014, WuHan ChuangYou, All Rights Reserved
//// Moudle: MsgGameUpdateOnlineInfo.cpp
//// Author: 彭文奇(Peng Wenqi)
//// Created: 2014-11-19
//////////////////////////////////////////////////////////////////////////
//#include "./MsgGameUpdateOnlineInfo.h"
//#include "./../UserMgr.h"
//
////////////////////////////////////////////////////////////////////////////
//CMsgGameUpdateOnlineInfo::CMsgGameUpdateOnlineInfo()
//{
//	Init();
//	m_pInfo = (MSG_Info*)m_bufMsg;
//	m_unMsgType = _MSG_GAME_ONLINE_INFO;
//	m_unMsgSize = sizeof(MSG_Info);
//}
//
////////////////////////////////////////////////////////////////////////////
//CMsgGameUpdateOnlineInfo::~CMsgGameUpdateOnlineInfo()
//{
//
//}
//
////////////////////////////////////////////////////////////////////////////
//BOOL CMsgGameUpdateOnlineInfo::Create( char* pMsgBuf, DWORD dwSize )
//{
//	if (!game_kernel::CNetMsg::Create(pMsgBuf, dwSize))
//		return false;
//
//	if(_MSG_GAME_ONLINE_INFO != this->GetType())
//		return false;
//
//	return true;
//}
//
////////////////////////////////////////////////////////////////////////////
//void CMsgGameUpdateOnlineInfo::Process( void *pInfo )
//{
//	DEBUG_TRY;
//	CHECK(!this->IsClientMsg());	// 不接受玩家发包
//	pUserMgr->ProcessUpdateUserOnlineInfo(&(m_pInfo->stOnlineInfo));
//	DEBUG_CATCH("CMsgGameUpdateOnlineInfo::Process");
//}
//
////////////////////////////////////////////////////////////////////////////
//bool CMsgGameUpdateOnlineInfo::CreateUserInfo( const USER_ONLINE_INFO* pOnlineInfo )
//{
//	CHECKF(pOnlineInfo);
//	this->Init();
//	m_unMsgType	= _MSG_GAME_ONLINE_INFO;
//	m_unMsgSize	= sizeof(MSG_Info);
//	memcpy(&(m_pInfo->stOnlineInfo), pOnlineInfo, sizeof(USER_ONLINE_INFO));
//	return true;
//}
