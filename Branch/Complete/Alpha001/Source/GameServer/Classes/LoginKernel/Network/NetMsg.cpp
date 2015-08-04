//NetMsg.cpp: implementation of the CNetMsg class.
//
//////////////////////////////////////////////////////////////////////
#include "basefunc.h"
#include "common.h"
#include "NetMsg.h"
#include "./AllMsg.h"

MYHEAP_IMPLEMENTATION_NICKNAME(login_kernel::CNetMsg, s_heap, CNetMsgL)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
login_kernel::CNetMsg::CNetMsg()
{
	Init();
}

login_kernel::CNetMsg::~CNetMsg()
{

}

//////////////////////////////////////////////////////////////////////
void login_kernel::CNetMsg::Init()
{
	memset(m_bufMsg, 0L, sizeof(m_bufMsg));
	m_unMsgSize	=0;
	m_unMsgType	=_MSG_NONE;
	m_idSocket = SOCKET_NONE;
}

//////////////////////////////////////////////////////////////////////
BOOL login_kernel::CNetMsg::IsValid(void)
{
	if(_MSG_NONE == this->GetType())
		return false;

	return true;
}

void login_kernel::CNetMsg::DumpMsg(const char* szReasion,...)
{
	DEBUG_TRY 
    char buffer[2048]="";
	_vsnprintf(buffer, sizeof(buffer) - 1, szReasion, (char*)((&szReasion)+1));
	::LogSave("login_kernel::CNetMsg::DumpMsg szReasion:%s,msgtype:%d-msgsize:%d,idProcess:%d,idSocket:%d",buffer,m_unMsgType,m_unMsgSize,m_idProcess,m_idSocket);///��־��¼
	DEBUG_CATCH("login_kernel::CNetMsg::DumpMsg crash")
}

//////////////////////////////////////////////////////////////////////
BOOL login_kernel::CNetMsg::Create(char* pbufMsg, DWORD dwMsgSize)
{
	if(!pbufMsg)
		return false;

	memcpy(this->m_bufMsg, pbufMsg, dwMsgSize);
	return true;
}

//////////////////////////////////////////////////////////////////////
void login_kernel::CNetMsg::Process(void *pInfo)
{
	::LogSave("login_kernel::CNetMsg::Process Msg:%d, Size:%d", m_unMsgType, m_unMsgSize);	
}

//////////////////////////////////////////////////////////////////////
// static functions;
//////////////////////////////////////////////////////////////////////
login_kernel::CNetMsg* login_kernel::CNetMsg::CreateClientMsg(PROCESS_ID idProcess, SOCKET_ID idSocket, OBJID idMsg, const char* pbufMsg, DWORD dwMsgSize)
{
	// check it...
	if(idMsg == _MSG_NONE || !pbufMsg || (int)dwMsgSize > _MAX_MSGSIZE)
		return NULL;

	login_kernel::CNetMsg* pMsg = CreateMsg(idMsg, pbufMsg, dwMsgSize);
	if(!pMsg)
		return NULL;

	pMsg->m_idProcess	= idProcess;
	pMsg->m_idSocket	= idSocket;
	pMsg->m_unMsgType	= idMsg;
	pMsg->m_unMsgSize	= dwMsgSize;

	if(!pMsg->Create((char*)pbufMsg, dwMsgSize))
	{
		SAFE_DELETE(pMsg);
		return NULL;
	}
	else
	{
		return pMsg;
	}
}

////////////////////////////////////////////////////////////////////////
// Description:  ǿ��������Ϣͷ
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool login_kernel::CNetMsg::ForceSetMsgHeader(PROCESS_ID idProcess, SOCKET_ID idSocket)
{
	CHECKF(idProcess);
	CHECKF(idSocket >= 0);
	m_idProcess = idProcess;
	m_idSocket	= idSocket;
	return true;
}

//////////////////////////////////////////////////////////////////////////
login_kernel::CNetMsg* login_kernel::CNetMsg::CreateMsg(OBJID idMsg, const char* pbufMsg, DWORD dwMsgSize)
{
	// make it...
	login_kernel::CNetMsg* pMsg	=NULL;
	switch(idMsg)
	{
	case _MSG_LOGIN_CONNECT:
		pMsg = new CMsgLoginConnect;
		break;
	case _MSG_LOGIN_CONNECT_ACTION:
		pMsg = new CMsgLoginAction;
		break;
	case _MSG_LOGIN_USER_LIST:
		pMsg = new CMsgLoginUserList;
		break;
	case _MSG_LOGIN_CREATE_NEW_USER:
		pMsg = new CMsgLoginCreateNewUser;
		break;
	case _MSG_LOGIN_KICK_REASON:
		pMsg = new CMsgLoginKickReason;
		break;
	default:
		break;
	}
	return pMsg;
}
	
