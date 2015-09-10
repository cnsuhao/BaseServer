//NetMsg.cpp: implementation of the CNetMsg class.
//
//////////////////////////////////////////////////////////////////////
#include "basefunc.h"
#include "common.h"
#include "NetMsg.h"
#include "./AllMsg.h"

MYHEAP_IMPLEMENTATION_NICKNAME(game_kernel::CNetMsg, s_heap, CNetMsgG)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
game_kernel::CNetMsg::CNetMsg()
{
	Init();
}

game_kernel::CNetMsg::~CNetMsg()
{

}

//////////////////////////////////////////////////////////////////////
void game_kernel::CNetMsg::Init()
{
	memset(m_bufMsg, 0L, sizeof(m_bufMsg));
	m_unMsgSize	=0;
	m_unMsgType	=_MSG_NONE;
	m_idSocket = SOCKET_NONE;
	m_bAIProcess = false;
}

//////////////////////////////////////////////////////////////////////
BOOL game_kernel::CNetMsg::IsValid(void)
{
	if(_MSG_NONE == this->GetType())
		return false;

	return true;
}

void game_kernel::CNetMsg::DumpMsg(const char* szReasion,...)
{
	DEBUG_TRY 
    char buffer[2048]="";
	_vsnprintf(buffer, sizeof(buffer) - 1, szReasion, (char*)((&szReasion)+1));
	::LogSave("game_kernel::CNetMsg::DumpMsg szReasion:%s,msgtype:%d-msgsize:%d,idProcess:%d,idSocket:%d",buffer,m_unMsgType,m_unMsgSize,m_idProcess,m_idSocket);///日志记录
	DEBUG_CATCH("game_kernel::CNetMsg::DumpMsg crash")
}

//////////////////////////////////////////////////////////////////////
BOOL game_kernel::CNetMsg::Create(char* pbufMsg, DWORD dwMsgSize)
{
	if(!pbufMsg)
		return false;

	memcpy(this->m_bufMsg, pbufMsg, dwMsgSize);
	return true;
}

//////////////////////////////////////////////////////////////////////
void game_kernel::CNetMsg::Process(void *pInfo)
{
	::LogSave("game_kernel::CNetMsg::Process Msg:%d, Size:%d", m_unMsgType, m_unMsgSize);	
}

//////////////////////////////////////////////////////////////////////
// static functions;
//////////////////////////////////////////////////////////////////////
game_kernel::CNetMsg* game_kernel::CNetMsg::CreateClientMsg(PROCESS_ID idProcess, SOCKET_ID idSocket, OBJID idMsg, const char* pbufMsg, DWORD dwMsgSize)
{
	// check it...
	if(idMsg == _MSG_NONE || !pbufMsg || (int)dwMsgSize > _MAX_MSGSIZE)
		return NULL;

	game_kernel::CNetMsg* pMsg = CreateMsg(idMsg, pbufMsg, dwMsgSize);
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
// Description:  强行设置消息头
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool game_kernel::CNetMsg::ForceSetMsgHeader(PROCESS_ID idProcess, SOCKET_ID idSocket)
{
	CHECKF(idProcess);
	CHECKF(idSocket >= 0);
	m_idProcess = idProcess;
	m_idSocket	= idSocket;
	return true;
}

//////////////////////////////////////////////////////////////////////////
game_kernel::CNetMsg* game_kernel::CNetMsg::CreateMsg(OBJID idMsg, const char* pbufMsg, DWORD dwMsgSize)
{
	// make it...
	game_kernel::CNetMsg* pMsg	=NULL;
	switch(idMsg)
	{
	case _MSG_GAME_KICK_REASON:
		pMsg = new CMsgGameKickReason;
		break;
	case _MSG_GAME_SMALLACTION:
		pMsg = new CMsgGameSmallAction;
		break;
	case _MSG_GAME_LOGIN_QUERY:
		pMsg = new CMsgGameLoginQuery;
		break;
	case _MSG_GAME_USER_INFO:
		pMsg = new CMsgGameUserInfo;
		break;
	case _MSG_GAME_USER_ATTR:
		pMsg = new CMsgGameUserAttr;
		break;
	default:
		break;
	}
	return pMsg;
}

//////////////////////////////////////////////////////////////////////////
bool game_kernel::CNetMsg::IsClientMsg( void ) const
{
	return m_idSocket > SOCKET_NONE;
}
