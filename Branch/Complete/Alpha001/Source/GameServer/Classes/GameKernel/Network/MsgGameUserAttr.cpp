////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan ChuangYou, All Rights Reserved
// Moudle: MsgGameUserAttr.cpp
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Created: 2014-11-10
////////////////////////////////////////////////////////////////////////
#include "./MsgGameUserAttr.h"

//////////////////////////////////////////////////////////////////////////
CMsgGameUserAttr::CMsgGameUserAttr()
{
	Init();
	m_pInfo = (MSG_Info*)m_bufMsg;
	m_unMsgType = _MSG_GAME_USER_ATTR;
	m_unMsgSize = sizeof(MSG_Info);
}

//////////////////////////////////////////////////////////////////////////
CMsgGameUserAttr::~CMsgGameUserAttr()
{

}

//////////////////////////////////////////////////////////////////////////
BOOL CMsgGameUserAttr::Create( char* pMsgBuf, DWORD dwSize )
{
	if (!game_kernel::CNetMsg::Create(pMsgBuf, dwSize))
		return false;

	if(_MSG_GAME_USER_ATTR != this->GetType())
		return false;

	return true;
}

//////////////////////////////////////////////////////////////////////////
void CMsgGameUserAttr::CreateBase()
{
	this->Init();
	m_unMsgType	= _MSG_GAME_USER_ATTR;
	m_unMsgSize	= sizeof(MSG_Info);
}

//////////////////////////////////////////////////////////////////////////
bool CMsgGameUserAttr::Append( int nType, I64 i64Data )
{
	CHECKF(sizeof(MSG_Info) + sizeof(MSG_USER_ATTR_INFO) * m_pInfo->nCount < MAX_PACKETSIZE);
	m_pInfo->stInfo[m_pInfo->nCount].nType = nType;
	m_pInfo->stInfo[m_pInfo->nCount].i64Data = i64Data;
	m_unMsgSize = sizeof(MSG_Info) + sizeof(MSG_USER_ATTR_INFO) * m_pInfo->nCount;
	m_pInfo->nCount++;
	return true;
}
