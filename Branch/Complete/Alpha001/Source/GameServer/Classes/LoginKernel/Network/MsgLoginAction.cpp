////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan ChuangYou, All Rights Reserved
// Moudle: MsgLoginAction.cpp
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Created: 2014-11-4
////////////////////////////////////////////////////////////////////////
#include "./MsgLoginAction.h"
#include "./../LoginKernel.h"

//////////////////////////////////////////////////////////////////////////
CMsgLoginAction::CMsgLoginAction()
{
	Init();
	m_pInfo	=(MSG_Info *)m_bufMsg;
	m_unMsgType	= _MSG_LOGIN_CONNECT_ACTION;
	m_unMsgSize	= sizeof(MSG_Info);
}

//////////////////////////////////////////////////////////////////////////
CMsgLoginAction::~CMsgLoginAction()
{

}

//////////////////////////////////////////////////////////////////////////
BOOL CMsgLoginAction::Create( char* pMsgBuf,DWORD dwSize )
{
	if (!login_kernel::CNetMsg::Create(pMsgBuf, dwSize))
		return false;

	if(_MSG_LOGIN_CONNECT_ACTION != this->GetType())
		return false;

	return true;
}

//////////////////////////////////////////////////////////////////////////
void CMsgLoginAction::Process( void* pInfo )
{
	DEBUG_TRY;
	
	//switch (m_pInfo->sAction)
	//{
	//case MSG_LOGIN_ACTION_TYPE_CHOOSE_USER:
	//	{
	//		if (pLoginKernel->ProcessChooseUser(m_idSocket, m_pInfo->nUserID))
	//		{
	//			m_pInfo->sResult = MSG_LOGIN_ACTION_RESULT_SUCCESS;
	//		}
	//		else
	//		{
	//			m_pInfo->sResult = MSG_LOGIN_ACTION_RESULT_FAIL;
	//		}
	//		pLoginKernel->SendMsg(this);
	//	}
	//	break;
	//case MSG_LOGIN_ACTION_TYPE_DELETE_USER:
	//	{
	//		if (pLoginKernel->ProcessDeleteUser(m_idSocket, m_pInfo->nUserID))
	//		{
	//			m_pInfo->sResult = MSG_LOGIN_ACTION_RESULT_SUCCESS;
	//		}
	//		else
	//		{
	//			m_pInfo->sResult = MSG_LOGIN_ACTION_RESULT_FAIL;
	//		}
	//		pLoginKernel->SendMsg(this);
	//	}
	//	break;
	//default:
	//	tolog2("CMsgLoginAction::Process unknow Action[%d]", m_pInfo->sAction);
	//	break;
	//}
	
	DEBUG_CATCH("CMsgLoginAction::Process");
}

