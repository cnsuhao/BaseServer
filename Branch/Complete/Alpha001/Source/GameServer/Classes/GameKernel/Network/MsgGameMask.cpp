////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan ChuangYou, All Rights Reserved
// Moudle: MsgGameMask.cpp
// Author: ³Â½¨¾ü(Chen Jianjun)
// Created: 2014-11-6
////////////////////////////////////////////////////////////////////////
#include "MsgGameMask.h"
#include "../GameKernel.h"

//////////////////////////////////////////////////////////////////////////
CMsgGameMask::CMsgGameMask()
{
	Init();
	m_pInfo		= (MSG_Info *)m_bufMsg;
	m_unMsgType	= _MSG_GAME_MASK;
	m_unMsgSize	= sizeof(MSG_Info) - sizeof(USERMMASKSTRUCT);
}

//////////////////////////////////////////////////////////////////////////
CMsgGameMask::~CMsgGameMask()
{

}

BOOL CMsgGameMask::Create( char* pMsgBuf, DWORD dwSize )
{
	if (!CNetMsg::Create(pMsgBuf, dwSize))
	{
		return false;
	}

	if(_MSG_GAME_MASK != this->GetType())
	{
		return false;
	}

	return true;
}

void CMsgGameMask::Process(void *pInfo)
{

}

bool CMsgGameMask::CreateMsg(MSG_NUM_4BIT idUser, MSG_NUM_4BIT unMaskType, MSG_NUM_4BIT idMask, MSG_NUM_4BIT unEndTime, MSG_NUM_8BIT i64MaskData)
{ 
	CHECKF(m_pInfo);

	this->Init();
	m_unMsgType		= _MSG_GAME_MASK;
	m_unMsgSize		= sizeof(MSG_Info) - sizeof(USERMMASKSTRUCT);

	m_pInfo->idUser	= idUser;
	m_pInfo->nNum	= 0;

	if(unMaskType >= 0)
	{
		m_unMsgSize	+= sizeof(USERMMASKSTRUCT);
		m_pInfo->setUserMask[m_pInfo->nNum].unMaskType	= unMaskType;
		m_pInfo->setUserMask[m_pInfo->nNum].idMask		= idMask;
		m_pInfo->setUserMask[m_pInfo->nNum].unEndTime	= unEndTime;
		m_pInfo->setUserMask[m_pInfo->nNum].i64MaskData	= i64MaskData;
		m_pInfo->nNum++;
	}
	return true;
}

bool CMsgGameMask::AppendMsg(USERMMASKSTRUCT& stInfo)
{
	if (sizeof(MSG_Info) + sizeof(USERMMASKSTRUCT) * m_pInfo->nNum >= MAX_PACKETSIZE)
	{
		return false;
	}

	m_pInfo->setUserMask[m_pInfo->nNum] = stInfo;
	m_unMsgSize = sizeof(MSG_Info) + sizeof(USERMMASKSTRUCT) * m_pInfo->nNum;
	++(m_pInfo->nNum);
	return true;
}