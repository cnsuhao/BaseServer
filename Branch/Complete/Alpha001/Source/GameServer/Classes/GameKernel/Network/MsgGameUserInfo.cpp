////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan ChuangYou, All Rights Reserved
// Moudle: MsgGameUserInfo.cpp
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Created: 2014-11-10
////////////////////////////////////////////////////////////////////////
#include "./MsgGameUserInfo.h"
#include "./../User.h"
#include "./../UserMgr.h"

//////////////////////////////////////////////////////////////////////////
CMsgGameUserInfo::CMsgGameUserInfo()
{
	Init();
	m_pInfo = (MSG_Info*)m_bufMsg;
	m_unMsgType = _MSG_GAME_USER_INFO;
	m_unMsgSize = sizeof(MSG_Info);
}

//////////////////////////////////////////////////////////////////////////
CMsgGameUserInfo::~CMsgGameUserInfo()
{

}

//////////////////////////////////////////////////////////////////////////
BOOL CMsgGameUserInfo::Create( char* pMsgBuf, DWORD dwSize )
{
	if (!game_kernel::CNetMsg::Create(pMsgBuf, dwSize))
		return false;

	if(_MSG_GAME_USER_INFO != this->GetType())
		return false;

	return true;
}

//////////////////////////////////////////////////////////////////////////
bool CMsgGameUserInfo::CreateUserInfo( CUser* pUser )
{
	CHECKF(pUser);
	this->Init();

	m_unMsgType	= _MSG_GAME_USER_INFO;
	m_unMsgSize	= sizeof(MSG_Info);

	m_pInfo->idUser			= pUser->GetID();
	m_pInfo->idAccountID	= pUser->GetData(USER_DATA_ACCOUNT_ID);
	m_pInfo->nAccountType	= pUser->GetData(USER_DATA_ACCOUNT_TYPE);
	m_pInfo->nLastLoginTime = pUser->GetData(USER_DATA_LOGIN_TIME);
	m_pInfo->nCreateTime	= pUser->GetData(USER_DATA_CREATE_TIME);
	m_pInfo->nLastExitTime	= pUser->GetData(USER_DATA_EXIT_TIME);
	m_pInfo->nServerGroup	= g_nServerGroup;
	m_pInfo->nServerLine	= g_nServerLine;
	m_pInfo->nLev			= pUser->GetData(USER_DATA_LEV);
	m_pInfo->nExp			= pUser->GetData(USER_DATA_EXP);
	m_pInfo->nCampType		= pUser->GetData(USER_DATA_CAMP);
	m_pInfo->nFlagShip		= pUser->GetData(USER_DATA_FLAGSHIP);
	m_pInfo->fRotation		= 0;
	m_pInfo->fSpeedForm		= 0;
	m_pInfo->fSpeedRotation = 0;
	m_pInfo->fViewRange		= 0;
	m_pInfo->nScore			= pUser->GetData(USER_DATA_SCORE);
	m_pInfo->nGalaxy		= pUser->GetData(USER_DATA_RECORD_GALAXY);
	m_pInfo->nRest			= pUser->GetData(USER_DATA_RECORD_REST);
	m_pInfo->curPointx		= pUser->GetData(USER_DATA_RECORD_X);
	m_pInfo->curPointy		= pUser->GetData(USER_DATA_RECORD_Y);
	m_pInfo->aimPointx		= 0;
	m_pInfo->aimPointy		= 0;
	::SafeCopy(m_pInfo->szUserName, pUser->GetStr(USER_DATA_NAME), sizeof(m_pInfo->szUserName));
	return true;
}
