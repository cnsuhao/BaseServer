#include "./MsgGameTalk.h"
#include "../User.h"
#include "../UserMgr.h"
#include "../TalkMgr.h"
#include "../GameKernel.h"

CMsgGameTalk::CMsgGameTalk( )
{
	Init();
	m_pInfo		=(MSG_Info *)m_bufMsg;
	m_unMsgType	= _MSG_GAME_TALK;
	m_unMsgSize	= sizeof(MSG_Info);
}

CMsgGameTalk::~CMsgGameTalk( )
{

}

BOOL CMsgGameTalk::Create(char* pbufMsg, DWORD dwMsgSize)
{
	if (!game_kernel::CNetMsg::Create(pbufMsg, dwMsgSize))
		return false;

	if(_MSG_GAME_TALK != this->GetType())
		return false;

	return true;
}

bool CMsgGameTalk::CreateTalk(TALK_TXTATR eTxtAtr, const char* pszText, int nDataSize, int nTxtType/*=0*/, int nClientParam1/*=0*/, int nClientParam2/*=0*/, int nClientParam3/*=0*/, int nClientParam4/*=0*/)
{
	CHECKF(pszText);
	CHECKF(nDataSize >= 0 && nDataSize < MAX_PACKETSIZE - sizeof(MSG_Info) + 1);

	this->Init();
	m_pInfo->nTxtAtr = eTxtAtr;

	// 客户端参数(不得修改)
	m_pInfo->nTxtType		= nTxtType;
	m_pInfo->nClientParam1	= nClientParam1;
	m_pInfo->nClientParam2	= nClientParam2;
	m_pInfo->nClientParam3	= nClientParam3;
	m_pInfo->nClientParam4	= nClientParam4;

	m_pInfo->nDataSize	   = nDataSize;
	::memcpy(m_pInfo->szData, pszText, nDataSize);

	m_unMsgSize = sizeof(MSG_Info) - sizeof(char) + nDataSize;
	m_unMsgType = _MSG_GAME_TALK;
	return true;
}

void CMsgGameTalk::SetSenderInfo(IN const ST_TALK_USER_INFO& info)
{
	CHECK(info.idUser);
	m_pInfo->stSenderInfo.idUser	= info.idUser;
	m_pInfo->stSenderInfo.nLev		= info.nLev;
	m_pInfo->stSenderInfo.nLookface = info.nLookface;
	::SafeCopy(m_pInfo->stSenderInfo.szUserName, info.szUserName, sizeof(m_pInfo->stSenderInfo.szUserName));
}

void CMsgGameTalk::SetReceiverName(const char* pszName)
{
	CHECK(pszName);
	::SafeCopy(m_pInfo->szReceiverName, pszName, sizeof(m_pInfo->szReceiverName));
}

void CMsgGameTalk::SerReceiverID(OBJID idUser)
{
	CHECK(idUser);
	m_pInfo->nReceiverID = idUser;
}

void CMsgGameTalk::SetSynID(OBJID idSyn)
{
	CHECK(idSyn);
	m_pInfo->nSynID = idSyn;
}

void CMsgGameTalk::SetUtcTime(UINT unTime)
{
	CHECK(unTime);
	m_pInfo->nServerUtcTime = unTime;
}

void CMsgGameTalk::SetServerParam1(int nParam)
{
	m_pInfo->nServerParam1 = nParam;
}

void CMsgGameTalk::SetServerParam2(int nParam)
{
	m_pInfo->nServerParam2 = nParam;
}

void CMsgGameTalk::SetServerParam3(int nParam)
{
	m_pInfo->nServerParam3 = nParam;
}

void CMsgGameTalk::SetServerParam4(int nParam)
{
	m_pInfo->nServerParam4 = nParam;
}


// 处理消息
void CMsgGameTalk::Process(void *pInfo)
{
	DEBUG_TRY;

	CUser* pUser = CUserMgr::GetInstance()->GetUserByMsg(this);
	if (pUser)
	{
		//m_pInfo->stSenderInfo.idUser = pUser->GetID();
		//m_pInfo->stSenderInfo.nLev = pUser->GetData(USER_DATA_LEV);
		//m_pInfo->stSenderInfo.nLookface = pUser->GetData(USER_DATA_LOOKFACE);
		//::SafeCopy(m_pInfo->stSenderInfo.szUserName, pUser->GetStr(USER_DATA_NAME), sizeof(m_pInfo->stSenderInfo.szUserName));
	}

	switch(m_pInfo->nTxtAtr)
	{
	case TALK_TXTATR_WORLDSERVER:	
		{
			pTalkMgr->RequestWorldTalk(m_pInfo->stSenderInfo, m_pInfo->nServerUtcTime, m_pInfo->szData, m_pInfo->nDataSize, 
				m_pInfo->nTxtType, m_pInfo->nClientParam1, m_pInfo->nClientParam2, m_pInfo->nClientParam3, m_pInfo->nClientParam4);
		}
		break;

	case TALK_TXTATR_SYNDICATE:
		{
			pTalkMgr->RequestSynTalk(m_pInfo->stSenderInfo, m_pInfo->nServerUtcTime, m_pInfo->nSynID, m_pInfo->szData, m_pInfo->nDataSize,
				m_pInfo->nTxtType, m_pInfo->nClientParam1, m_pInfo->nClientParam2, m_pInfo->nClientParam3, m_pInfo->nClientParam4);
		}
		break;
	
	case TALK_TXTATR_PRIVATE:
		{
			pTalkMgr->RequestPrivateTalk(m_pInfo->stSenderInfo, m_pInfo->nServerUtcTime, m_pInfo->nReceiverID, m_pInfo->szReceiverName, m_pInfo->szData, m_pInfo->nDataSize, 
				m_pInfo->nTxtType, m_pInfo->nClientParam1, m_pInfo->nClientParam2, m_pInfo->nClientParam3, m_pInfo->nClientParam4);
		}
		break;

	case TALK_TXTATR_NOTICE:
		{
			//if (pUser && pUser->IsGM())	// GM玩家可以发公告
			//{
			//	pTalkMgr->RequestNotify(m_pInfo->szData, m_pInfo->szReceiverName, m_pInfo->nSynID);
			//}
			//else if (!pUser)
			//{
			//	pTalkMgr->RequestNotify(m_pInfo->szData, m_pInfo->szReceiverName, m_pInfo->nSynID);
			//}
		}
		break;

	case TALK_TXTATR_HINT:
		{
			//if (pUser && pUser->IsGM())	// GM玩家可以发提示
			//{
			//	pTalkMgr->RequestHint(m_pInfo->szData, m_pInfo->szReceiverName, m_pInfo->nSynID);
			//}
			//else if (!pUser)
			//{
			//	pTalkMgr->RequestHint(m_pInfo->szData, m_pInfo->szReceiverName, m_pInfo->nSynID);
			//}
		}
		break;

	case TALK_TXTATR_GM_CMD:		// GM命令
		{
			if (pUser)
			{
				pTalkMgr->RequestGmCmd(pUser->GetID(), m_pInfo->szData);
			}
		}
		break;

	case TALK_TXTATR_GM_OPERATION:	// gm操作
		{
			if (pUser)
			{
				pTalkMgr->RequestGmOperation(pUser->GetID(), m_pInfo->szData);
			}
		}
		break;

	default:
		{
			::tolog2("CMsgTalk::Process Unknow TxtAttribute[%d]", m_pInfo->nTxtAtr);
		}
		break;
	}
	DEBUG_CATCH2("CMsgTalk::Process Crash! Action[%d].", m_pInfo->nTxtAtr);
}