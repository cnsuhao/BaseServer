////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan ChuangYou, All Rights Reserved
// Moudle: MsgLoginConnect.cpp
// Author: 彭文奇(Peng Wenqi)
// Created: 2014-11-3
////////////////////////////////////////////////////////////////////////
#include "./MsgLoginConnect.h"
#include "./../LoginKernel.h"

//////////////////////////////////////////////////////////////////////////
CMsgLoginConnect::CMsgLoginConnect()
{
	Init();
	m_pInfo	=(MSG_Info *)m_bufMsg;
	m_unMsgType	= _MSG_LOGIN_CONNECT;
	m_unMsgSize	= sizeof(MSG_Info);
}

//////////////////////////////////////////////////////////////////////////
CMsgLoginConnect::~CMsgLoginConnect()
{

}

//////////////////////////////////////////////////////////////////////////
BOOL CMsgLoginConnect::Create( char* pMsgBuf,DWORD dwSize )
{
	if (!login_kernel::CNetMsg::Create(pMsgBuf, dwSize))
		return false;

	if(_MSG_LOGIN_CONNECT != this->GetType())
		return false;

	return true;
}

//////////////////////////////////////////////////////////////////////////
void CMsgLoginConnect::Process( void* pInfo )
{
	// 登入流程3.1
	DEBUG_TRY;
	pLoginKernel->ProcessAccountLogin(m_idSocket, m_pInfo->szAccountName, m_pInfo->szAccountPassword);
	pLoginKernel->SendMsg(this);
	DEBUG_CATCH("CMsgLoginConnect::Process");
}

