////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan ChuangYou, All Rights Reserved
// Moudle: MsgGameLoginQuery.cpp
// Author: 彭文奇(Peng Wenqi)
// Created: 2014-11-10
////////////////////////////////////////////////////////////////////////
#include "./MsgGameLoginQuery.h"
#include "./../UserMgr.h"

//////////////////////////////////////////////////////////////////////////
CMsgGameLoginQuery::CMsgGameLoginQuery()
{
	Init();
	m_pInfo = (MSG_Info*)m_bufMsg;
	m_unMsgType = _MSG_GAME_LOGIN_QUERY;
	m_unMsgSize = sizeof(MSG_Info);
}

//////////////////////////////////////////////////////////////////////////
CMsgGameLoginQuery::~CMsgGameLoginQuery()
{

}

//////////////////////////////////////////////////////////////////////////
BOOL CMsgGameLoginQuery::Create( char* pMsgBuf, DWORD dwSize )
{
	if (!game_kernel::CNetMsg::Create(pMsgBuf, dwSize))
		return false;

	if(_MSG_GAME_LOGIN_QUERY != this->GetType())
		return false;

	return true;
}



//////////////////////////////////////////////////////////////////////////
void CMsgGameLoginQuery::Process( void *pInfo )
{
	DEBUG_TRY;
	OBJID idUser = pUserMgr->GetUserIDByMsg(this);
	CHECK(idUser);

	switch (m_pInfo->sAction)
	{
	case MSG_LOGIN_QUERY_ACTION_HEARTBEAT:
		{
			this->CreateLoginQuery(MSG_LOGIN_QUERY_ACTION_HEARTBEAT, MSG_LOGIN_QUERY_RESULT_SUCC, ::TimeGet(TIME_SECOND));
			pUserMgr->SendMsg(idUser, this);
		}
		break;
	default:
		tolog3("CMsgGameLoginQuery::Process unkonw action[%d], idUser[%u]", m_pInfo->sAction, idUser);
		break;
	}

	// 自动回包确认
	if (m_pInfo->sAction >= MSG_LOGIN_QUERY_ACTION_AUTOBACK_BEGIN)
	{
		pUserMgr->SendMsg(idUser, this);
	}

	DEBUG_CATCH("CMsgGameLoginQuery::Process");
}

//////////////////////////////////////////////////////////////////////////
bool CMsgGameLoginQuery::CreateLoginQuery( MSG_LOGIN_QUERY_ACTION eAction, MSG_LOGIN_QUERY_RESULT eResult, int nParam1 /*= 0*/, int nParam2 /*= 0*/ )
{
	this->Init();
	m_unMsgType	= _MSG_GAME_LOGIN_QUERY;
	m_unMsgSize	= sizeof(MSG_Info);

	m_pInfo->sAction = (MSG_NUM_2BIT)eAction;
	m_pInfo->sResult = (MSG_NUM_2BIT)eResult;
	m_pInfo->nParam1 = nParam1;
	m_pInfo->nParam2 = nParam2;

	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: 心跳包
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: 
////////////////////////////////////////////////////////////////////////
void CMsgGameLoginQuery::ProcessHeartbeat( void )
{

}


