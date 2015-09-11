#include "./TalkMgr.h"
#include "./UserMgr.h"
#include "./User.h"
#include "./GameKernel.h"
#include "./UserTalkData.h"
#include "./UserTmpDataMgr.h"
#include "./UserTaskMgr.h"
#include "./UserMailMgr.h"
#include "./Network/MsgGameUserAttr.h"

CTalkMgr* CTalkMgr::s_pInstance = NULL;
MYHEAP_IMPLEMENTATION(CTalkMgr, s_heap);

////////////////////////////////////////////////////////////////////////
// Description: ��������ʼ��
// Arguments:
// Author: ����ΰ(Gong Jianwei)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool CTalkMgr::Init( )
{
	DEBUG_TRY;
	m_mapTalkData.clear();
	return true;
	DEBUG_CATCHF("CTalkMgr::Init Crash!");
}


////////////////////////////////////////////////////////////////////////
// Description: �������ͷ�
// Arguments:
// Author: ����ΰ(Gong Jianwei)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void CTalkMgr::Release( )
{
	DEBUG_TRY;
	for (MAP_TALK_DATA::iterator iter = m_mapTalkData.begin(); iter != m_mapTalkData.end(); iter++)
	{
		SAFE_RELEASE(iter->second);
	}
	m_mapTalkData.clear();
	DEBUG_CATCH("CTalkMgr::Release Crash!");
}

////////////////////////////////////////////////////////////////////////
// Description: ��ʼ�����
// Arguments:
// Author: ����ΰ(Gong Jianwei)
// Return Value: void
////////////////////////////////////////////////////////////////////////
bool CTalkMgr::InitUser(OBJID idUser)
{
	CHECKF(idUser);
	CUserTalkData* pUserTalkData = CUserTalkData::CreateNew();
	CHECKF(pUserTalkData);
	if (!pUserTalkData->Init())
	{
		SAFE_RELEASE(pUserTalkData);
		return false;
	}
	m_mapTalkData[idUser] = pUserTalkData;
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: �ͷ����
// Arguments:
// Author: ����ΰ(Gong Jianwei)
// Return Value: void
////////////////////////////////////////////////////////////////////////
bool CTalkMgr::ReleaseUser(OBJID idUser)
{
	CHECKF(idUser);
	CUserTalkData* pTalk = this->GetUserTalkData(idUser);
	SAFE_RELEASE(pTalk);
	m_mapTalkData.erase(idUser);
	return true;
}

//===========================================�߼�����Beg=================================================
////////////////////////////////////////////////////////////////////////
// Description: ��ȡ���������
// Arguments:
// Author: ����ΰ(Gong Jianwei)
// Return Value: CUserTalkData
////////////////////////////////////////////////////////////////////////
CUserTalkData*	CTalkMgr::GetUserTalkData(OBJID idUser) const
{
	CHECKF(idUser);
	MAP_TALK_DATA::const_iterator iter = m_mapTalkData.find(idUser);
	CHECKF(iter != m_mapTalkData.end());
	return iter->second;
}

////////////////////////////////////////////////////////////////////////
// Description: ��ȡ����ʱ����
// Arguments:
// Author: ����ΰ(Gong Jianwei)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
int CTalkMgr::GetTalkTimeLimit(int nTxtAtr) const
{
	CHECKF(nTxtAtr > TALK_TXTATR_BEGIN && nTxtAtr < TALK_TXTATR_END);
	//const CConfigData* pConfigData = pConstTableMgr->GetConfigData();
	//CHECKF(pConfigData);
	int nTimeLimit = 0;
	//CONFIG_DATA eIndex = (CONFIG_DATA)(nTxtAtr - TALK_TXTATR_BEGIN);
	//CHECKF(eIndex > CONFIGDATA_BEGIN && eIndex < CONFIGDATA_END);
	//CHECKF(pConfigData->GetData(CONFIGTYPE_USER_TALK_TIME_LIMIT, eIndex, nTimeLimit));
	return nTimeLimit;
}

////////////////////////////////////////////////////////////////////////
// Description: �����������ʱ��
// Arguments:
// Author: ����ΰ(Gong Jianwei)
// Return Value: void
////////////////////////////////////////////////////////////////////////
bool CTalkMgr::UpdateUserTalkTime(OBJID idUser, int nTxtAtr)
{
	CHECKF(idUser);
	CHECKF(nTxtAtr > TALK_TXTATR_BEGIN && nTxtAtr < TALK_TXTATR_END);

	CUserTalkData* pUserTalkData = this->GetUserTalkData(idUser);
	CHECKF(pUserTalkData);
	// �������ڸ�Ƶ���Ƿ��Ĺ���
	if (pUserTalkData->IsExit(nTxtAtr))
	{
		DWORD dwCurTime		 = ::TimeGet(TIME_SECOND);
		DWORD dwLastChatTime = pUserTalkData->GetData(nTxtAtr);
		int	  nTimeLimit	 = this->GetTalkTimeLimit(nTxtAtr);
		if (dwLastChatTime + nTimeLimit > dwCurTime)
		{
			return false;
		}
		CHECKF(pUserTalkData->SetData(nTxtAtr, dwCurTime));
	}
	else
	{
		DWORD dwNowTime = ::TimeGet(TIME_SECOND);
		CHECKF(pUserTalkData->Add(nTxtAtr, dwNowTime));
	}
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: ɾ�������������ʷ��¼
// Arguments:	
// Author: ����ΰ(Gong Jianwei)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool CTalkMgr::DelWorldHistory()
{
	SET_DB_KEY setDbKey;
	//CHECKF(pRelayDbMgr->EnumDbKey(RELAY_TABLE_TALK_WORLD, setDbKey));

	//// �ж���û�г�����¼����
	//int nWorldLimit = 30;
	//CHECKB(pConstTableMgr->GetConfigData()->GetData(CONFIGTYPE_TALK_RECORD_LIMIT, CONFIGDATA_DATA1, nWorldLimit));
	//
	//int nCurCount = setDbKey.size();
	//if (nCurCount <= nWorldLimit)
	//{
	//	return true;
	//}

	//// ɾ����ʷ��¼
	//for (SET_DB_KEY::const_iterator iter = setDbKey.begin(); iter != setDbKey.end(); iter++)
	//{
	//	pRelayDbMgr->CommitDelete(RELAY_TABLE_TALK_WORLD, *iter, RELAY_CALLBACK_EMPTY);
	//	nCurCount -= 1;
	//	if (nCurCount <= nWorldLimit)
	//	{
	//		return true;
	//	}
	//}
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: ɾ�������������ʷ��¼
// Arguments:	
// Author: ����ΰ(Gong Jianwei)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool CTalkMgr::DelSynHistory(OBJID idSyn)
{
	CHECKF(idSyn);
	SET_DB_KEY setDbKey;
	//CHECKF(pRelayDbMgr->EnumKeyByIndex1(RELAY_TABLE_TALK_SYN, idSyn, setDbKey));

	//// �ж���û�г�����¼����
	//int nSynLimit = 30;
	//CHECKB(pConstTableMgr->GetConfigData()->GetData(CONFIGTYPE_TALK_RECORD_LIMIT, CONFIGDATA_DATA2, nSynLimit));
	//
	//int nCurCount = setDbKey.size();
	//if (nCurCount <= nSynLimit)
	//{
	//	return true;
	//}

	//// ɾ����ʷ��¼
	//for (SET_DB_KEY::const_iterator iter = setDbKey.begin(); iter != setDbKey.end(); iter++)
	//{
	//	pRelayDbMgr->CommitDelete(RELAY_TABLE_TALK_SYN, *iter, RELAY_CALLBACK_EMPTY);
	//	nCurCount -= 1;
	//	if (nCurCount <= nSynLimit)
	//	{
	//		return true;
	//	}
	//}
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: ��ȡ˽�ı������ʷ��¼
// Arguments:	
// Author: ����ΰ(Gong Jianwei)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool CTalkMgr::GetLastHistory(OBJID idReceiver, OUT MAP_TABLE_DATA& mapData)
{
	CHECKF(idReceiver);
	mapData.clear();

	int nPrivateLimit = 30;
	//CHECKB(pConstTableMgr->GetConfigData()->GetData(CONFIGTYPE_TALK_RECORD_LIMIT, CONFIGDATA_DATA3, nPrivateLimit));

	//CMxyString strSql("select * from %s where user_id = %u order by id desc limit %d", GAME_DB_NAME_TALK_PRIVATE, idReceiver, nPrivateLimit);
	//RecordsetPtr pRes = pGameDatabase->CreateNewRecordset(strSql.c_str());
	//CHECKF(pRes);

	//RecordPtr pRecord = NULL;
	//OBJID idKey = ID_NONE;
	//for(int i = 0; i < pRes->RecordCount(); i++, pRes->MoveNext())
	//{
	//	pRecord = pRes->CreateNewRecord();
	//	CHECKC(pRecord);
	//	idKey = pRecord->GetInt(TALK_PRIVATE_DATA_ID);
	//	mapData[idKey] = pRecord;
	//}
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: ɾ��˽�ı���ʷ��¼
// Arguments:	
// Author: ����ΰ(Gong Jianwei)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool CTalkMgr::DelPrivateHistory(OBJID idReceiver)
{
	// ɾ�������¼
	int nPrivateLimit = 30;
	//CHECKB(pConstTableMgr->GetConfigData()->GetData(CONFIGTYPE_TALK_RECORD_LIMIT, CONFIGDATA_DATA3, nPrivateLimit));

	//CMxyString strDel("delete from %s where user_id = %u and id not in  (select id from (select id from %s where user_id=%u order by time desc limit %u) as t)",
	//	GAME_DB_NAME_TALK_PRIVATE, idReceiver, GAME_DB_NAME_TALK_PRIVATE, idReceiver, nPrivateLimit);
	//pGameDatabase->ExecuteSQL(strDel.c_str(), DBUPDATE_ASYNC);

	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: �Ƿ����
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool CTalkMgr::IsStopTalk( OBJID idUser ) const
{
	//CHECKF1(idUser);
	//CUser* pUser = pUserMgr->GetUserByID(idUser);
	//CHECKF1(pUser);

	//UINT unNowSecond = ::TimeGet(TIME_SECOND);
	//UINT unStopEndTime = pUser->GetData(USER_DATA_STOP_TALK_END);
	//if (unStopEndTime > unNowSecond)
	//{
	//	return true;
	//}
	return false;
}

////////////////////////////////////////////////////////////////////////
// Description: ���ý���ʱ��
// Arguments:	�����һ��
// Author: ������(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool CTalkMgr::SetStopTalk( OBJID idUser, int nKeepSecond )
{
	CHECKF(nKeepSecond >= 0 && nKeepSecond <= 366 * 24 * 60 * 60);

	CHECKF(idUser);
	CUser* pUser = pUserMgr->GetUserByID(idUser);
	CHECKF(pUser);

	//UINT unNowSecond = ::TimeGet(TIME_SECOND);
	//pUser->SetData(USER_DATA_STOP_TALK_END, unNowSecond + nKeepSecond, true);

	//CMsgGameUserAttr msg;
	//msg.CreateBase();
	//msg.Append(USER_ATTR_TYPE_STOP_TALK_TIME, unNowSecond + nKeepSecond);
	//pUserMgr->SendMsg(idUser, &msg);

	return true;
}

//===========================================�߼�����End=================================================

//===========================================��Ϣ����Beg=================================================
////////////////////////////////////////////////////////////////////////
// Description: �����ѯ���������б�
// Arguments:
// Author: ����ΰ(Gong Jianwei)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void CTalkMgr::RequestQueryWorldTalk(OBJID idUser)
{
	CHECK(idUser);
	CUser* pUser = pUserMgr->GetUserByID(idUser);
	CHECK(pUser);
	this->DelWorldHistory();

	//int nWorldLimit = 30;
	//CHECKB(pConstTableMgr->GetConfigData()->GetData(CONFIGTYPE_TALK_RECORD_LIMIT, CONFIGDATA_DATA1, nWorldLimit));

	//SET_DB_KEY setDbKey;
	//CHECK(pRelayDbMgr->EnumDbKey(RELAY_TABLE_TALK_WORLD, setDbKey));
	//int nCurCount = setDbKey.size();
	//for (SET_DB_KEY::const_iterator iter = setDbKey.begin(); iter != setDbKey.end(); iter++)
	//{
	//	if (nCurCount > nWorldLimit)
	//	{
	//		nCurCount -= 1;
	//		continue;
	//	}
	//	OBJID idSender = pRelayDbMgr->GetData(RELAY_TABLE_TALK_WORLD, *iter, TALK_WORLD_DATA_SENDER_ID);
	//	const char* pszSenderName = pRelayDbMgr->GetDataStr(RELAY_TABLE_TALK_WORLD, *iter, TALK_WORLD_DATA_SENDER_NAME);
	//	UINT unSenderFace = pRelayDbMgr->GetData(RELAY_TABLE_TALK_WORLD, *iter, TALK_WORLD_DATA_SENDER_FACE);
	//	UINT unSenderLev  = pRelayDbMgr->GetData(RELAY_TABLE_TALK_WORLD, *iter, TALK_WORLD_DATA_SENDER_LEV);
	//	const char* pszText = pRelayDbMgr->GetDataStr(RELAY_TABLE_TALK_WORLD, *iter, TALK_WORLD_DATA_TEXT);
	//	UINT unTime = pRelayDbMgr->GetData(RELAY_TABLE_TALK_WORLD, *iter, TALK_WORLD_DATA_TIME);
	//	UINT unType = pRelayDbMgr->GetData(RELAY_TABLE_TALK_WORLD, *iter, TALK_WORLD_DATA_TYPE);
	//	UINT unParam1 = pRelayDbMgr->GetData(RELAY_TABLE_TALK_WORLD, *iter, TALK_WORLD_DATA_PARAM1);
	//	UINT unParam2 = pRelayDbMgr->GetData(RELAY_TABLE_TALK_WORLD, *iter, TALK_WORLD_DATA_PARAM2);
	//	UINT unParam3 = pRelayDbMgr->GetData(RELAY_TABLE_TALK_WORLD, *iter, TALK_WORLD_DATA_PARAM3);
	//	UINT unParam4 = pRelayDbMgr->GetData(RELAY_TABLE_TALK_WORLD, *iter, TALK_WORLD_DATA_PARAM4);

	//	ST_TALK_USER_INFO info;
	//	info.idUser = idSender;
	//	info.nLev	= unSenderLev;
	//	info.nLookface = unSenderFace;
	//	::SafeCopy(info.szUserName, pszSenderName, sizeof(info.szUserName));

	//	CMsgGameQueryTalk msg;
	//	msg.CreateTalk(MSG_GAME_QUERY_TALK_ACTION_QueryWorldTalk, MSG_GAME_QUERY_TALK_RESULT_Succ, pszText, strlen(pszText), unType, unParam1, unParam2, unParam3, unParam4);
	//	msg.SetSenderInfo(info);
	//	msg.SetUtcTime(unTime);
	//	pUserMgr->SendMsg(idUser, &msg);
	//}

	//// ������
	//CMsgGameQueryTalk msg;
	//msg.CreateTalk(MSG_GAME_QUERY_TALK_ACTION_QueryWorldTalk, MSG_GAME_QUERY_TALK_RESULT_Last_Package, "", 0);
	//pUserMgr->SendMsg(idUser, &msg);
}

////////////////////////////////////////////////////////////////////////
// Description: �����ѯ���������б�
// Arguments:
// Author: ����ΰ(Gong Jianwei)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void CTalkMgr::RequestQuerySynTalk(OBJID idUser)
{
	CHECK(idUser);
	CUser* pUser = pUserMgr->GetUserByID(idUser);
	CHECK(pUser);

	//OBJID idSyndicate = pSyndicateMgr->GetSyndicateID(pUser->GetID());
	//if (ID_NONE == idSyndicate)	// ���ɲ�����
	//{
	//	SZ_CONFIG_TEXT_TYPE szText = "";
	//	const CConfigText* pConfigText = pConstTableMgr->GetConfigText();
	//	CHECK(pConfigText);
	//	pConfigText->GetText(CONFIG_TEXT_ID_GROUP_SYN_NOT_EXIST, szText);
	//	pNotifyMgr->SendHint(szText, SEND_RANGE_TYPE_USER, pUser->GetID());
	//	return;
	//}

	//this->DelSynHistory(idSyndicate);
	//
	//int nSynLimit = 30;
	//CHECKB(pConstTableMgr->GetConfigData()->GetData(CONFIGTYPE_TALK_RECORD_LIMIT, CONFIGDATA_DATA2, nSynLimit));

	//SET_DB_KEY setDbKey;
	//pRelayDbMgr->EnumKeyByIndex1(RELAY_TABLE_TALK_SYN, idSyndicate, setDbKey);
	//int nCurCount = setDbKey.size();
	//for (SET_DB_KEY::const_iterator iter = setDbKey.begin(); iter != setDbKey.end(); iter++)
	//{
	//	if (nCurCount > nSynLimit)
	//	{
	//		nCurCount -= 1;
	//		continue;
	//	}
	//	OBJID idSender = pRelayDbMgr->GetData(RELAY_TABLE_TALK_SYN, *iter, TALK_SYN_DATA_SENDER_ID);
	//	const char* pszSenderName = pRelayDbMgr->GetDataStr(RELAY_TABLE_TALK_SYN, *iter, TALK_SYN_DATA_SENDER_NAME);
	//	UINT unSenderFace = pRelayDbMgr->GetData(RELAY_TABLE_TALK_SYN, *iter, TALK_SYN_DATA_SENDER_FACE);
	//	UINT unSenderLev  = pRelayDbMgr->GetData(RELAY_TABLE_TALK_SYN, *iter, TALK_SYN_DATA_SENDER_LEV);
	//	const char* pszText = pRelayDbMgr->GetDataStr(RELAY_TABLE_TALK_SYN, *iter, TALK_SYN_DATA_TEXT);
	//	UINT unTime = pRelayDbMgr->GetData(RELAY_TABLE_TALK_SYN, *iter, TALK_SYN_DATA_TIME);
	//	UINT unType = pRelayDbMgr->GetData(RELAY_TABLE_TALK_SYN, *iter, TALK_SYN_DATA_TYPE);
	//	UINT unParam1 = pRelayDbMgr->GetData(RELAY_TABLE_TALK_SYN, *iter, TALK_SYN_DATA_PARAM1);
	//	UINT unParam2 = pRelayDbMgr->GetData(RELAY_TABLE_TALK_SYN, *iter, TALK_SYN_DATA_PARAM2);
	//	UINT unParam3 = pRelayDbMgr->GetData(RELAY_TABLE_TALK_SYN, *iter, TALK_SYN_DATA_PARAM3);
	//	UINT unParam4 = pRelayDbMgr->GetData(RELAY_TABLE_TALK_SYN, *iter, TALK_SYN_DATA_PARAM4);

	//	ST_TALK_USER_INFO info;
	//	info.idUser = idSender;
	//	info.nLev	= unSenderLev;
	//	info.nLookface = unSenderFace;
	//	::SafeCopy(info.szUserName, pszSenderName, sizeof(info.szUserName));

	//	CMsgGameQueryTalk msg;
	//	msg.CreateTalk(MSG_GAME_QUERY_TALK_ACTION_QuerySynTalk, MSG_GAME_QUERY_TALK_RESULT_Succ, pszText, strlen(pszText), unType, unParam1, unParam2, unParam3, unParam4);
	//	msg.SetSenderInfo(info);
	//	msg.SetUtcTime(unTime);
	//	pUserMgr->SendMsg(idUser, &msg);
	//}

	//// ������
	//CMsgGameQueryTalk msg;
	//msg.CreateTalk(MSG_GAME_QUERY_TALK_ACTION_QuerySynTalk, MSG_GAME_QUERY_TALK_RESULT_Last_Package, "", 0);
	//pUserMgr->SendMsg(idUser, &msg);
}

////////////////////////////////////////////////////////////////////////
// Description: �����ѯ˽���б�
// Arguments:
// Author: ����ΰ(Gong Jianwei)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void CTalkMgr::RequestQueryPrivateTalk(OBJID idUser)
{
	CHECK(idUser);
	CUser* pUser = pUserMgr->GetUserByID(idUser);
	CHECK(pUser);

	//MAP_TABLE_DATA mapData;
	//this->GetLastHistory(idUser, mapData);
	//for (CITER_TABLE_DATA iter = mapData.begin(); iter != mapData.end(); iter++)
	//{
	//	RecordPtr pRecord = iter->second;
	//	CHECKC(pRecord);

	//	OBJID idSender = pRecord->GetInt(TALK_PRIVATE_DATA_SENDER_ID);
	//	const char* pszSenderName = pRecord->GetStr(TALK_PRIVATE_DATA_SENDER_NAME);
	//	UINT unSenderFace = pRecord->GetInt(TALK_PRIVATE_DATA_SENDER_FACE);
	//	UINT unSenderLev  = pRecord->GetInt(TALK_PRIVATE_DATA_SENDER_LEV);
	//	const char* pszText = pRecord->GetStr(TALK_PRIVATE_DATA_TEXT);
	//	UINT unTime = pRecord->GetInt(TALK_PRIVATE_DATA_TIME);
	//	UINT unType = pRecord->GetInt(TALK_PRIVATE_DATA_TYPE);
	//	UINT unParam1 = pRecord->GetInt(TALK_PRIVATE_DATA_PARAM1);
	//	UINT unParam2 = pRecord->GetInt(TALK_PRIVATE_DATA_PARAM2);
	//	UINT unParam3 = pRecord->GetInt(TALK_PRIVATE_DATA_PARAM3);
	//	UINT unParam4 = pRecord->GetInt(TALK_PRIVATE_DATA_PARAM4);

	//	ST_TALK_USER_INFO info;
	//	info.idUser = idSender;
	//	info.nLev	= unSenderLev;
	//	info.nLookface = unSenderFace;
	//	::SafeCopy(info.szUserName, pszSenderName, sizeof(info.szUserName));

	//	CMsgGameQueryTalk msg;
	//	msg.CreateTalk(MSG_GAME_QUERY_TALK_ACTION_ReturnPrivateTalk, MSG_GAME_QUERY_TALK_RESULT_Succ, pszText, strlen(pszText), unType, unParam1, unParam2, unParam3, unParam4);
	//	msg.SetSenderInfo(info);
	//	msg.SetUtcTime(unTime);
	//	pUserMgr->SendMsg(idUser, &msg);
	//}

	//// ������
	//CMsgGameQueryTalk msg;
	//msg.CreateTalk(MSG_GAME_QUERY_TALK_ACTION_ReturnPrivateTalk, MSG_GAME_QUERY_TALK_RESULT_Last_Package, "", 0);
	//pUserMgr->SendMsg(idUser, &msg);

	//if (mapData.size())
	//{
	//	CHECK(this->DelPrivateHistory(idUser));
	//}
}

////////////////////////////////////////////////////////////////////////
// Description: �����ѯ�����Ϣ
// Arguments:
// Author: ����ΰ(Gong Jianwei)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void CTalkMgr::RequestQueryUserInfo(OBJID idUser, OBJID idTargeter)
{
	CHECK(idUser && idTargeter);
	CUser* pUser = pUserMgr->GetUserByID(idUser);
	CHECK(pUser);
	
	//UINT unMaxScore = 0;
	//char szSynName[NAME_SIZE] = "";
	//if (pRelayDbMgr->IsExist(RELAY_TABLE_SYNDICATE_MEMBER, idTargeter))
	//{
	//	OBJID idSyn = pSyndicateMgr->GetSyndicateID(idTargeter);
	//	CHECK(idSyn);
	//	const char* pszSynName = pRelayDbMgr->GetDataStr(RELAY_TABLE_SYNDICATE, idSyn, SYNDICATE_DATA_NAME);
	//	CHECK(pszSynName);
	//	::SafeCopy(szSynName, pszSynName, sizeof(szSynName));
	//}

	//unMaxScore = pUserMgr->GetUserMaxScore(idTargeter, true);

	//CMsgGameQueryTalk msg;
	//msg.CreateTalk(MSG_GAME_QUERY_TALK_ACTION_QueryUserInfo, MSG_GAME_QUERY_TALK_RESULT_Succ, "", 0);
	//msg.SetSynName(szSynName);
	//msg.SetServerParam1(unMaxScore);
	//pUserMgr->SendMsg(idUser, &msg);
}

////////////////////////////////////////////////////////////////////////
// Description: ������������
// Arguments:
// Author: ����ΰ(Gong Jianwei)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void CTalkMgr::RequestWorldTalk(ST_TALK_USER_INFO& stSenderinfo, int nSendTime, char* pszData, int nDataSize, int nTxtType, int nParam1, int nParam2, int nParam3, int nParam4)
{
	CHECK(pszData);
	
	//SZ_CONFIG_TEXT_TYPE szText = "";
	//const CConfigText* pConfigText = pConstTableMgr->GetConfigText();
	//CHECK(pConfigText);

	//CUser* pUser = pUserMgr->GetUserByID(stSenderinfo.idUser);
	//if (pUser)
	//{
	//	// ���ȼ�(�ȼ�����Ϊ40�������ɰ������Ͳ���Ҫ�ȼ�����)
	//	int nNeedUserLev = 40;
	//	if (pSyndicateMgr->GetSyndicateID(pUser->GetID()) && pRelayDbMgr->GetData(RELAY_TABLE_SYNDICATE_MEMBER, pUser->GetID(), SYNDICATE_MEMBER_DATA_RANK) == RANK_LEADER)
	//	{
	//		nNeedUserLev = 0;
	//	}
	//	if (pUser->GetData(USER_DATA_LEV) < nNeedUserLev)
	//	{
	//		pConfigText->GetText(CONFIG_TEXT_ID_USER_LESS_LEV, szText);
	//		pNotifyMgr->SendHint(szText, SEND_RANGE_TYPE_USER, pUser->GetID());
	//		return;
	//	}

	//	// ���SQLע��
	//	if (!pUser->IsGM() && !::StrSqlCheck(pszData))
	//	{
	//		pConfigText->GetText(CONFIG_TEXT_ID_USER_INVALID_INFO, szText);
	//		pNotifyMgr->SendHint(szText, SEND_RANGE_TYPE_USER, pUser->GetID());
	//		return;
	//	}

	//	// ������
	//	if (!pUser->IsGM() && !::TalkStrCheck(pszData, true))
	//	{
	//		pConfigText->GetText(CONFIG_TEXT_ID_USER_INVALID_INFO, szText);
	//		pNotifyMgr->SendHint(szText, SEND_RANGE_TYPE_USER, pUser->GetID());
	//		return;
	//	}

	//	// ����
	//	if (this->IsStopTalk(pUser->GetID()))
	//	{
	//		pConfigText->GetText(CONFIG_TEXT_ID_USER_STOP_TALK, szText);
	//		pNotifyMgr->SendHint(szText, SEND_RANGE_TYPE_USER, pUser->GetID());
	//		return;
	//	}

	//	// ��������ʱ��
	//	if (!this->UpdateUserTalkTime(pUser->GetID(), TALK_TXTATR_WORLDSERVER))
	//	{
	//		pConfigText->GetText(CONFIG_TEXT_ID_USER_TO_FAST, szText);
	//		pNotifyMgr->SendHint(szText, SEND_RANGE_TYPE_USER, pUser->GetID());
	//		return;
	//	}
	//}

	//CMsgGameTalk msgTalk;
	//CHECK(msgTalk.CreateTalk(TALK_TXTATR_WORLDSERVER, pszData, nDataSize, nTxtType, nParam1, nParam2, nParam3, nParam4));
	//msgTalk.SetSenderInfo(stSenderinfo);

	//if (NULL != pUser)	// C->S
	//{
	//	// ��ȡ�����������ã�������ѣ�
	//	int nNeedVas = 0;
	//	CHECKB(pConstTableMgr->GetConfigData()->GetData(CONFIGTYPE_TALK_CONFIG, CONFIGDATA_DATA1, nNeedVas));
	//	if (nNeedVas > 0)
	//	{
	//		// ����Ԫ��
	//		I64 i64Vas = pUserMoneyMgr->Get(pUser->GetID(), USER_MONEY_TYPE_VAS);
	//		if (i64Vas < nNeedVas)
	//		{
	//			pConfigText->GetText(CONFIG_TEXT_ID_USER_LESS_VAS, szText);
	//			pNotifyMgr->SendHint(szText, SEND_RANGE_TYPE_USER, pUser->GetID());
	//			return;
	//		}
	//		CHECK(pUserMoneyMgr->Spend(pUser->GetID(), USER_MONEY_TYPE_VAS, nNeedVas, MONEY_FLOW_REASON_WORLD_TALK));
	//	}
	//	

	//	// ������Ϣ
	//	UINT unCurTime = ::TimeGet(TIME_SECOND);
	//	msgTalk.SetUtcTime(unCurTime);
	//	CHECK(pGameKernel->BroadcastMsg(&msgTalk));
	//	CHECK(pGameKernel->SendRelationMsg(&msgTalk));

	//	// �����¼
	//	pRelayDbMgr->StartInsert(RELAY_TABLE_TALK_WORLD);
	//	pRelayDbMgr->SetInsertData(RELAY_TABLE_TALK_WORLD, TALK_WORLD_DATA_SENDER_ID, stSenderinfo.idUser);
	//	pRelayDbMgr->SetInsertDataStr(RELAY_TABLE_TALK_WORLD, TALK_WORLD_DATA_SENDER_NAME, stSenderinfo.szUserName);
	//	pRelayDbMgr->SetInsertData(RELAY_TABLE_TALK_WORLD, TALK_WORLD_DATA_SENDER_LEV, stSenderinfo.nLev);
	//	pRelayDbMgr->SetInsertData(RELAY_TABLE_TALK_WORLD, TALK_WORLD_DATA_SENDER_FACE, stSenderinfo.nLookface);
	//	pRelayDbMgr->SetInsertDataStr(RELAY_TABLE_TALK_WORLD, TALK_WORLD_DATA_TEXT, pszData);
	//	pRelayDbMgr->SetInsertData(RELAY_TABLE_TALK_WORLD, TALK_WORLD_DATA_TIME, unCurTime);
	//	pRelayDbMgr->SetInsertData(RELAY_TABLE_TALK_WORLD, TALK_WORLD_DATA_TYPE, nTxtType);
	//	pRelayDbMgr->SetInsertData(RELAY_TABLE_TALK_WORLD, TALK_WORLD_DATA_PARAM1, nParam1);
	//	pRelayDbMgr->SetInsertData(RELAY_TABLE_TALK_WORLD, TALK_WORLD_DATA_PARAM2, nParam2);
	//	pRelayDbMgr->SetInsertData(RELAY_TABLE_TALK_WORLD, TALK_WORLD_DATA_PARAM3, nParam3);
	//	pRelayDbMgr->SetInsertData(RELAY_TABLE_TALK_WORLD, TALK_WORLD_DATA_PARAM4, nParam4);
	//	pRelayDbMgr->SetInsertData(RELAY_TABLE_TALK_WORLD, TALK_WORLD_DATA_SERVER_GROUP, g_nServerGroup);
	//	pRelayDbMgr->CommitInsert(RELAY_TABLE_TALK_WORLD, RELAY_CALLBACK_EMPTY);

	//	// ɾ��������ʷ��¼
	//	CHECK(this->DelWorldHistory());
	//}
	//else	// R->S
	//{
	//	msgTalk.SetUtcTime(nSendTime);
	//	CHECK(pGameKernel->BroadcastMsg(&msgTalk));
	//}
}

////////////////////////////////////////////////////////////////////////
// Description: �����������
// Arguments:
// Author: ����ΰ(Gong Jianwei)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void CTalkMgr::RequestSynTalk(ST_TALK_USER_INFO& stSenderinfo, int nSendTime, OBJID idSyn, char* pszData, int nDataSize, int nTxtType, int nParam1, int nParam2, int nParam3, int nParam4)
{
	CHECK(pszData);

	//SZ_CONFIG_TEXT_TYPE szText = "";
	//const CConfigText* pConfigText = pConstTableMgr->GetConfigText();
	//CHECK(pConfigText);
	//
	//CUser* pUser = pUserMgr->GetUserByID(stSenderinfo.idUser);
	//if (pUser)
	//{
	//	OBJID idSyndicate = pSyndicateMgr->GetSyndicateID(pUser->GetID());
	//	if (ID_NONE == idSyndicate)	// ���ɲ�����
	//	{
	//		pConfigText->GetText(CONFIG_TEXT_ID_GROUP_SYN_NOT_EXIST, szText);
	//		pNotifyMgr->SendHint(szText, SEND_RANGE_TYPE_USER, pUser->GetID());
	//		return;
	//	}

	//	// ���SQLע��
	//	if (!pUser->IsGM() && !::StrSqlCheck(pszData))
	//	{
	//		pConfigText->GetText(CONFIG_TEXT_ID_USER_INVALID_INFO, szText);
	//		pNotifyMgr->SendHint(szText, SEND_RANGE_TYPE_USER, pUser->GetID());
	//		return;
	//	}

	//	// ������
	//	if (!pUser->IsGM() && !::TalkStrCheck(pszData, true))
	//	{
	//		pConfigText->GetText(CONFIG_TEXT_ID_USER_INVALID_INFO, szText);
	//		pNotifyMgr->SendHint(szText, SEND_RANGE_TYPE_USER, pUser->GetID());
	//		return;
	//	}

	//	// ��������ʱ��
	//	if (!this->UpdateUserTalkTime(pUser->GetID(), TALK_TXTATR_SYNDICATE))
	//	{
	//		pConfigText->GetText(CONFIG_TEXT_ID_USER_TO_FAST, szText);
	//		pNotifyMgr->SendHint(szText, SEND_RANGE_TYPE_USER, pUser->GetID());
	//		return;
	//	}
	//}

	//CMsgGameTalk msgTalk;
	//CHECK(msgTalk.CreateTalk(TALK_TXTATR_SYNDICATE, pszData, nDataSize, nTxtType, nParam1, nParam2, nParam3, nParam4));
	//msgTalk.SetSenderInfo(stSenderinfo);

	//if (NULL != pUser)
	//{
	//	OBJID idSyndicate = pSyndicateMgr->GetSyndicateID(pUser->GetID());
	//	UINT  unCurTime	  = ::TimeGet(TIME_SECOND);
	//	msgTalk.SetSynID(idSyndicate);
	//	msgTalk.SetUtcTime(unCurTime);
	//	// ���ط�������Լ�
	//	if (nTxtType == ETALK_TYPE_TreasureShare)
	//	{
	//		pSyndicateMgr->BroadcastMsg(idSyndicate, &msgTalk, stSenderinfo.idUser);
	//	}
	//	else
	//	{
	//		pSyndicateMgr->BroadcastMsg(idSyndicate, &msgTalk);
	//	}
	//	pGameKernel->SendRelationMsg(&msgTalk);

	//	// �����¼
	//	pRelayDbMgr->StartInsert(RELAY_TABLE_TALK_SYN);
	//	pRelayDbMgr->SetInsertData(RELAY_TABLE_TALK_SYN, TALK_SYN_DATA_SYN_ID, idSyndicate);
	//	pRelayDbMgr->SetInsertData(RELAY_TABLE_TALK_SYN, TALK_SYN_DATA_SENDER_ID, stSenderinfo.idUser);
	//	pRelayDbMgr->SetInsertDataStr(RELAY_TABLE_TALK_SYN, TALK_SYN_DATA_SENDER_NAME, stSenderinfo.szUserName);
	//	pRelayDbMgr->SetInsertData(RELAY_TABLE_TALK_SYN, TALK_SYN_DATA_SENDER_LEV, stSenderinfo.nLev);
	//	pRelayDbMgr->SetInsertData(RELAY_TABLE_TALK_SYN, TALK_SYN_DATA_SENDER_FACE, stSenderinfo.nLookface);
	//	pRelayDbMgr->SetInsertDataStr(RELAY_TABLE_TALK_SYN, TALK_SYN_DATA_TEXT, pszData);
	//	pRelayDbMgr->SetInsertData(RELAY_TABLE_TALK_SYN, TALK_SYN_DATA_TIME, ::TimeGet(TIME_SECOND));
	//	pRelayDbMgr->SetInsertData(RELAY_TABLE_TALK_SYN, TALK_SYN_DATA_TYPE, nTxtType);
	//	pRelayDbMgr->SetInsertData(RELAY_TABLE_TALK_SYN, TALK_SYN_DATA_PARAM1, nParam1);
	//	pRelayDbMgr->SetInsertData(RELAY_TABLE_TALK_SYN, TALK_SYN_DATA_PARAM2, nParam2);
	//	pRelayDbMgr->SetInsertData(RELAY_TABLE_TALK_SYN, TALK_SYN_DATA_PARAM3, nParam3);
	//	pRelayDbMgr->SetInsertData(RELAY_TABLE_TALK_SYN, TALK_SYN_DATA_PARAM4, nParam4);
	//	pRelayDbMgr->SetInsertData(RELAY_TABLE_TALK_SYN, TALK_SYN_DATA_SERVER_GROUP, g_nServerGroup);
	//	pRelayDbMgr->CommitInsert(RELAY_TABLE_TALK_SYN, RELAY_CALLBACK_EMPTY);

	//	// ɾ��������ʷ��¼
	//	CHECK(this->DelSynHistory(idSyndicate));
	//}
	//else
	//{
	//	msgTalk.SetSynID(idSyn);
	//	msgTalk.SetUtcTime(nSendTime);
	//	pSyndicateMgr->BroadcastMsg(idSyn, &msgTalk);
	//}
}

////////////////////////////////////////////////////////////////////////
// Description: ����˽��
// Arguments:
// Author: ����ΰ(Gong Jianwei)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void CTalkMgr::RequestPrivateTalk(ST_TALK_USER_INFO& stSenderinfo, int nSendTime, OBJID idReceiverID, const char* pszReceiverName, char* pszData, int nDataSize, int nTxtType, int nParam1, int nParam2, int nParam3, int nParam4)
{
	CHECK(pszData);
	CHECK(stSenderinfo.idUser != idReceiverID);

	//SZ_CONFIG_TEXT_TYPE szText = "";
	//const CConfigText* pConfigText = pConstTableMgr->GetConfigText();
	//CHECK(pConfigText);

	//CUser* pUser = pUserMgr->GetUserByID(stSenderinfo.idUser);
	//if (pUser)
	//{
	//	// ���SQLע��
	//	if (!pUser->IsGM() && !::StrSqlCheck(pszData))
	//	{
	//		pConfigText->GetText(CONFIG_TEXT_ID_USER_INVALID_INFO, szText);
	//		pNotifyMgr->SendHint(szText, SEND_RANGE_TYPE_USER, pUser->GetID());
	//		return;
	//	}

	//	// ������
	//	if (!pUser->IsGM() && !::TalkStrCheck(pszData, true))
	//	{
	//		pConfigText->GetText(CONFIG_TEXT_ID_USER_INVALID_INFO, szText);
	//		pNotifyMgr->SendHint(szText, SEND_RANGE_TYPE_USER, pUser->GetID());
	//		return;
	//	}

	//	// ���ط�����CD
	//	if (nTxtType != ETALK_TYPE_TreasureShare)
	//	{
	//		// ��������ʱ��
	//		if (!this->UpdateUserTalkTime(pUser->GetID(), TALK_TXTATR_PRIVATE))
	//		{
	//			pConfigText->GetText(CONFIG_TEXT_ID_USER_TO_FAST, szText);
	//			pNotifyMgr->SendHint(szText, SEND_RANGE_TYPE_USER, pUser->GetID());
	//			return;
	//		}
	//	}
	//}

	//CMsgGameTalk msgTalk;
	//CHECK(msgTalk.CreateTalk(TALK_TXTATR_PRIVATE, pszData, nDataSize, nTxtType, nParam1, nParam2, nParam3, nParam4));
	//msgTalk.SetSenderInfo(stSenderinfo);

	//CUser* pReceiver = NULL;
	//if (idReceiverID)
	//{
	//	pReceiver = pUserMgr->GetUserByID(idReceiverID);
	//}
	//else if (pszReceiverName)
	//{
	//	pReceiver = pUserMgr->GetUserByName(pszReceiverName);
	//}

	//if (pReceiver)
	//{
	//	if (!nSendTime)
	//	{
	//		nSendTime = ::TimeGet(TIME_SECOND);
	//		msgTalk.SetUtcTime(nSendTime);
	//	}
	//	msgTalk.SetUtcTime(nSendTime);
	//	pUserMgr->SendMsg(pReceiver->GetID(), &msgTalk);

	//	// ����˽��֪ͨ
	//	pSystemSettingsMgr->SendMessageNotify(idReceiverID, EMSG_SWITCH_TYPE_PrivateTalk);
	//}
	//else if (pUser)
	//{
	//	nSendTime = ::TimeGet(TIME_SECOND);
	//	msgTalk.SetUtcTime(nSendTime);
	//	msgTalk.SerReceiverID(idReceiverID);
	//	msgTalk.SetReceiverName(pszReceiverName);
	//	pGameKernel->SendRelationMsg(&msgTalk);
	//}

	//if (pUser)
	//{
	//	if (nTxtType != ETALK_TYPE_TreasureShare)
	//	{
	//		// ��������ʾ
	//		msgTalk.SetReceiverName(pszReceiverName);
	//		pUserMgr->SendMsg(pUser->GetID(), &msgTalk);
	//	}

	//	if (idReceiverID < PLAYER_ID_FIRST)
	//	{
	//		return;
	//	}

	//	// �����¼
	//	CHECK(pGameDatabase);
	//	CMxyString strInsert("insert into %s (user_id,sender_id,sender_name,sender_face,sender_lev,text,time,type,param1,param2,param3,param4,server_group) values('%s',%u,'%s',%d,%d,'%s',%u,%d,%d,%d,%d,%d,%d)",
	//		GAME_DB_NAME_TALK_PRIVATE,
	//		idReceiverID, stSenderinfo.idUser, stSenderinfo.szUserName, stSenderinfo.nLookface, stSenderinfo.nLev,
	//		pszData, nSendTime, nTxtType, nParam1, nParam2, nParam3, nParam4, g_nServerGroup);
	//	pGameDatabase->ExecuteSQL(strInsert.c_str(), DBUPDATE_ASYNC);

	//	// ɾ��˽����ʷ��¼
	//	this->DelPrivateHistory(idReceiverID);
	//}
	//return;
}

////////////////////////////////////////////////////////////////////////
// Description: ���󹫸�
// Arguments: idUser>0��ʾ����ҷ�����; idSyn>0��ʾ�����ɷ�����
// Author: ����ΰ(Gong Jianwei)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
void CTalkMgr::RequestNotify(const char* pszData, const char* pszReceiverName/*=NULL*/, OBJID idSyn/*=0*/)
{
	CHECK(pszData);
	int nDataSize = ::strlen(pszData) + 1;
	CHECK(nDataSize);

	//CMsgGameTalk msgTalk;
	//msgTalk.CreateTalk(TALK_TXTATR_NOTICE, pszData, nDataSize);

	//if (pszReceiverName && strlen(pszReceiverName) > 0)
	//{
	//	CUser* pUser = pUserMgr->GetUserByName(pszReceiverName);
	//	if (pUser)
	//	{
	//		pUserMgr->SendMsg(pUser->GetID(), &msgTalk);
	//	}
	//}
	//else if (idSyn)
	//{
	//	if (pRelayDbMgr->IsExist(RELAY_TABLE_SYNDICATE, idSyn))
	//	{
	//		pSyndicateMgr->BroadcastMsg(idSyn, &msgTalk);
	//	}
	//}
	//else
	//{
	//	pUserMgr->BroadcastMsg(&msgTalk);
	//}
	return;
}

////////////////////////////////////////////////////////////////////////
// Description: ������ʾ
// Arguments: idUser>0��ʾ����ҷ���ʾ; idSyn>0��ʾ�����ɷ���ʾ
// Author: ����ΰ(Gong Jianwei)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
void CTalkMgr::RequestHint(const char* pszData, const char* pszReceiverName/*=NULL*/, OBJID idSyn/*=0*/)
{
	CHECK(pszData);
	int nDataSize = ::strlen(pszData) + 1;
	CHECK(nDataSize);

	//CMsgGameTalk msgTalk;
	//msgTalk.CreateTalk(TALK_TXTATR_HINT, pszData, nDataSize);

	//if (pszReceiverName && strlen(pszReceiverName) > 0)
	//{
	//	CUser* pUser = pUserMgr->GetUserByName(pszReceiverName);
	//	if (pUser)
	//	{
	//		pUserMgr->SendMsg(pUser->GetID(), &msgTalk);
	//	}
	//}
	//else if (idSyn)
	//{
	//	if (pRelayDbMgr->IsExist(RELAY_TABLE_SYNDICATE, idSyn))
	//	{
	//		pSyndicateMgr->BroadcastMsg(idSyn, &msgTalk);
	//	}
	//}
	//else
	//{
	//	pUserMgr->BroadcastMsg(&msgTalk);
	//}
	return;
}

////////////////////////////////////////////////////////////////////////
// Description: ����GM����
// Arguments:
// Author: ����ΰ(Gong Jianwei)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void CTalkMgr::RequestGmCmd(OBJID idUser, char* pszData)
{
	CHECK(idUser);
	CHECK(pszData);

	CUser* pUser = pUserMgr->GetUserByID(idUser);
	CHECK(pUser);

	// �ж��Ƿ�GM��
	//CHECK(pUser->IsGmHiAccount());
	//CHECK('!' == pszData[0]);

	//// ��Ҫ��֤mac��ַ
	//if (m_bGmCmdNeedMac)
	//{
	//	if (FALSE == pUser->GetMemoryDataAttr(mdaUser_GmMacPass))
	//	{
	//		CMxyString strErrorCmdLog("GM CMD MacError! [%I64d][%s][%s]", pUser->GetID(), pUser->GetStr(USER_DATA_NAME), pszData);
	//		::GmLogSave(strErrorCmdLog.c_str());
	//		pUserMgr->KickUserByUser(pUser->GetID(), KICK_REASON_GM_MAC_ERROR);
	//		return;
	//	}
	//}

	// ����GM����
	this->ProcessGmCmd(idUser, pszData);

	return;
}

////////////////////////////////////////////////////////////////////////
// Description: ����gm���߷��� GM����
// Arguments:	ֻ��Ҫ�ͼ�gmȨ�޼���
// Author: ������(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
void CTalkMgr::RequestGmOperation( OBJID idUser, const char* pszData )
{
	CHECK(idUser && pszData);
	CUser* pUser = pUserMgr->GetUserByID(idUser);
	CHECK(pUser);
	CHECK(pGameDatabase);

	// �ж��Ƿ�GM��
	//CHECK(pUser->IsGM());
	//CHECK('!' == pszData[0]);

	//// ��Ҫ��֤mac��ַ
	//if (m_bGmCmdNeedMac)
	//{
	//	if (FALSE == pUser->GetMemoryDataAttr(mdaUser_GmMacPass))
	//	{
	//		CMxyString strErrorCmdLog("GM CMD MacError! [%u][%s][%s]", idUser, pUser->GetStr(USER_DATA_NAME), pszData);
	//		::GmLogSave(strErrorCmdLog.c_str());
	//		pUserMgr->KickUserByUser(idUser, KICK_REASON_GM_MAC_ERROR);
	//		return;
	//	}
	//}

	//MSGBUF szCmd   = "";
	//MSGBUF szParam = "";
	//sscanf(pszData + 1, "%s %s", szCmd, szParam);

	//// ��־
	//UINT unNowSecond = ::TimeGet(TIME_SECOND);
	//char szCurrentDateTime[20] = "";
	//::DateTime(szCurrentDateTime, unNowSecond);
	//CMxyString strGmOperationLog("insert into %s.%s (utc_second,date_time,gm_account_id,gm_account_name,gm_user_id,gm_user_name,gm_ip,gm_mac,server_group,server_line,operation_type,operation_info) values(%u,'%s',%u,'%s',%u,'%s','%s','%s',%d,%d,'%s','%s')",
	//	g_strAccountDatabaseName.c_str(), ACC_DB_NAME_GM_OPERATION_LOG,
	//	unNowSecond, szCurrentDateTime,
	//	pUser->GetData(USER_DATA_ACCOUNT_ID), pUser->GetAccountName(),
	//	pUser->GetID(), pUser->GetStr(USER_DATA_NAME),
	//	pUser->GetIP(), pUser->GetMac(),
	//	g_nServerGroup, g_nServerLine, 
	//	szCmd, pszData);
	//pGameDatabase->ExecuteSQL(strGmOperationLog.c_str(), DBUPDATE_ASYNC);

	//// GM���߲���
	//if		(0 == stricmp(szCmd, "stoptalk"))
	//{
	//	char szTargetName[256] = {0};
	//	int nStopSecond = 0;
	//	if (3 == sscanf(pszData + 1, "%s %s %d", szCmd, szTargetName, &nStopSecond))
	//	{
	//		CMxyString strResult = "Failed";
	//		CUser* pTargetUser = pUserMgr->GetUserByName(szTargetName);
	//		if (pTargetUser && this->SetStopTalk(pTargetUser->GetID(), nStopSecond))
	//		{
	//			strResult = "OK";
	//		}

	//		CMxyString strHint("Stop Talk %s! Name[%s] Second[%d]", strResult.c_str(), szTargetName, nStopSecond);
	//		char szUserName[NAME_SIZE] = "";
	//		pUserMgr->GetUserName(idUser, szUserName);
	//		this->RequestHint(strHint.c_str(), szUserName);
	//	}
	//}
	//else if (0 == stricmp(szCmd, "stopaccount"))
	//{
	//	char szTargetName[256] = {0};
	//	int nStopSecond = 0;
	//	if (3 == sscanf(pszData + 1, "%s %s %d", szCmd, szTargetName, &nStopSecond))
	//	{
	//		CMxyString strResult = "Failed";
	//		CUser* pTargetUser = pUserMgr->GetUserByName(szTargetName);
	//		if (pTargetUser)
	//		{
	//			UINT unEndTime = ::TimeGet(TIME_SECOND) + nStopSecond;
	//			OBJID idAccount = pTargetUser->GetData(USER_DATA_ACCOUNT_ID);
	//			CMxyString strSql("update %s.%s set account_status=%d,account_status_param=%u where id=%u limit 1", g_strAccountDatabaseName.c_str(), ACC_DB_NAME_ACCOUNT, ACCOUNT_STATUS_STOP_BYTIME, unEndTime, idAccount);
	//			pGameDatabase->ExecuteSQL(strSql.c_str());
	//			pUserMgr->KickUserByUser(pTargetUser->GetID(), KICK_REASON_SYSTEM);
	//			strResult = "OK";
	//		}

	//		// ����ʾ		
	//		CMxyString strHint("Stop Account %s! Name[%s] Second[%d]", strResult.c_str(), szTargetName, nStopSecond);
	//		char szUserName[NAME_SIZE] = "";
	//		pUserMgr->GetUserName(idUser, szUserName);
	//		this->RequestHint(strHint.c_str(), szUserName);
	//	}
	//}

	return;
}

//===========================================��Ϣ����End=================================================

////////////////////////////////////////////////////////////////////////
// Description: ����GM����
// Arguments:
// Author: ����ΰ(Gong Jianwei)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void CTalkMgr::ProcessGmCmd(OBJID idUser, const char* pszData)
{
	CHECK(idUser);
	CHECK(pszData);
	CUser* pUser = pUserMgr->GetUserByID(idUser);
	CHECK(pUser);
	MSGBUF szCmd   = "";
	MSGBUF szParam = "";
	sscanf(pszData + 1, "%s %s", szCmd, szParam);

	// debugģʽ��Ļ����
#ifdef MYDEBUG
	CMxyString strCmdLog("GM CMD [%u][%s][%s]", idUser, pUser->GetStr(USER_DATA_NAME), pszData);
	CMxyString strTextAnsi = ::MyUtf8ToANSI(strCmdLog.c_str());
	pGameKernel->PrintText(strTextAnsi.c_str());
#endif

	// ��־
	//UINT unNowSecond = ::TimeGet(TIME_SECOND);
	//char szCurrentDateTime[20] = "";
	//::DateTime(szCurrentDateTime, unNowSecond);
	//CMxyString strGmOperationLog("insert into %s.%s (utc_second,date_time,gm_account_id,gm_account_name,gm_user_id,gm_user_name,gm_ip,gm_mac,server_group,server_line,operation_type,operation_info) values(%u,'%s',%u,'%s',%u,'%s','%s','%s',%d,%d,'%s','%s')",
	//	g_strAccountDatabaseName.c_str(), ACC_DB_NAME_GM_OPERATION_LOG,
	//	unNowSecond, szCurrentDateTime,
	//	pUser->GetData(USER_DATA_ACCOUNT_ID), pUser->GetAccountName(),
	//	pUser->GetID(), pUser->GetStr(USER_DATA_NAME),
	//	pUser->GetIP(), pUser->GetMac(),
	//	g_nServerGroup, g_nServerLine, 
	//	"GmCMD", pszData);
	//pGameDatabase->ExecuteSQL(strGmOperationLog.c_str(), DBUPDATE_ASYNC);

	// GM����
	if (0 == stricmp(szCmd, "PrivateChat"))
	{
		//ST_TALK_USER_INFO stInfo;
		//stInfo.idUser = idUser;
		//pUserMgr->GetUserName(idUser, stInfo.szUserName);
		//stInfo.nLev = pUserMgr->GetUserLev(idUser);
		//stInfo.nLookface = pUserMgr->GetUserLookFace(idUser);

		//char szInfo[256] = {0};
		//
		//if (2 == sscanf(pszData + 1, "%s %s", szCmd, szInfo))
		//{
		//	pTalkMgr->RequestPrivateTalk(stInfo, 0, 10000012, NULL, szInfo, strlen(szInfo) + 1, 0, 0, 0, 0, 0);
		//}
	}
	else if (0 == stricmp(szCmd, "WorldChat"))
	{
		//ST_TALK_USER_INFO stInfo;
		//stInfo.idUser = idUser;
		//pUserMgr->GetUserName(idUser, stInfo.szUserName);
		//stInfo.nLev = pUserMgr->GetUserLev(idUser);
		//stInfo.nLookface = pUserMgr->GetUserLookFace(idUser);

		//char szInfo[256] = {0};
		//if (2 == sscanf(pszData + 1, "%s %s", szCmd, szInfo))
		//{
		//	pTalkMgr->RequestWorldTalk(stInfo, 0, szInfo, strlen(szInfo) + 1, 0, 0, 0, 0, 0);
		//}
	}
	else if (0 == stricmp(szCmd, "SynChat"))
	{
		//ST_TALK_USER_INFO stInfo;
		//stInfo.idUser = idUser;
		//pUserMgr->GetUserName(idUser, stInfo.szUserName);
		//stInfo.nLev = pUserMgr->GetUserLev(idUser);
		//stInfo.nLookface = pUserMgr->GetUserLookFace(idUser);

		//char szInfo[256] = {0};
		//if (2 == sscanf(pszData + 1, "%s %s", szCmd, szInfo))
		//{
		//	pTalkMgr->RequestSynTalk(stInfo, 0, 0, szInfo, strlen(szInfo) + 1, 0, 0, 0, 0, 0);
		//}
	}
	else if(0 == stricmp(szCmd, "QueryPrivateChat"))
	{
		pTalkMgr->RequestQueryPrivateTalk(idUser);
	}
	else if (0 == stricmp(szCmd, "QueryWorldChat"))
	{
		pTalkMgr->RequestQueryWorldTalk(idUser);
	}
	else if (0 == stricmp(szCmd, "QuerySynChat"))
	{
		pTalkMgr->RequestQuerySynTalk(idUser);
	}
	else if (0 == stricmp(szCmd, "clienttmpdata"))	// ��ѯ�ͻ����Զ���TmpData
	{
		if (1 == sscanf(pszData + 1, "%s", szCmd))
		{
			pUserTmpDataMgr->ProcessQueryClientTmpData(idUser);
		}
	}
	else if (0 == stricmp(szCmd, "settmpdata"))	// ����UserTmpData
	{
		int nTmpDataID = 0;
		int nIndex = 0;
		int nData = 0;
		if (4 == sscanf(pszData + 1, "%s %d %d %d", szCmd, &nTmpDataID, &nIndex, &nData))
		{
			pUserTmpDataMgr->SetTmpData(idUser, nTmpDataID, (USERTMPDATA_INDEX)nIndex, nData);
		}
	}
	else if (0 == stricmp(szCmd, "gettmpdata"))	// ��ȡUserTmpData
	{
		int  nTmpDataID = 0;
		if (2 == sscanf(pszData + 1, "%s %d", szCmd, &nTmpDataID))
		{
			pUserTmpDataMgr->UpdateUserTmpData(idUser, nTmpDataID);
		}
	}
	else if (0 == stricmp(szCmd, "settmpdatamask"))	// �����뷽ʽ����UserTmpData
	{
		int nTmpDataID = 0;
		int nIndex = 0;
		int nMaskIndex = 0;
		if (4 == sscanf(pszData + 1, "%s %d %d %d", szCmd, &nTmpDataID, &nIndex, &nMaskIndex))
		{
			pUserTmpDataMgr->SetTmpDataMask(idUser, nTmpDataID, (USERTMPDATA_INDEX)nIndex, nMaskIndex, true);
		}
	}
	else if (0 == stricmp(szCmd, "clrtmpdatamask"))	// �����뷽ʽ���UserTmpData
	{
		int nTmpDataID = 0;
		int nIndex = 0;
		int nMaskIndex = 0;
		if (4 == sscanf(pszData + 1, "%s %d %d %d", szCmd, &nTmpDataID, &nIndex, &nMaskIndex))
		{
			pUserTmpDataMgr->ClrTmpDataMask(idUser, nTmpDataID, (USERTMPDATA_INDEX)nIndex, nMaskIndex, true);
		}
	}
	else if (0 == stricmp(szCmd, "chktmpdatamask"))	// �����뷽ʽ���UserTmpData
	{
		int nTmpDataID = 0;
		int nIndex = 0;
		int nMaskIndex = 0;
		if (4 == sscanf(pszData + 1, "%s %d %d %d", szCmd, &nTmpDataID, &nIndex, &nMaskIndex))
		{
			pUserTmpDataMgr->ChkTmpDataMask(idUser, nTmpDataID, (USERTMPDATA_INDEX)nIndex, nMaskIndex);
		}
	}
	else if (0 == stricmp(szCmd, "gaintask"))		// �������
	{
		int nTaskType = 0;
		int nStep = 0;
		if (3 == sscanf(pszData + 1, "%s %d %d", szCmd, &nTaskType, &nStep))
		{
			pUserTaskMgr->GainTask(idUser, nTaskType, nStep);
		}
	}
	else if (0 == stricmp(szCmd, "tasklist"))	// ��ѯ�����б�
	{
		if (1 == sscanf(pszData + 1, "%s", szCmd))
		{
			pUserTaskMgr->ProcessQueryAllTask(idUser);
		}
	}
	else if (0 == stricmp(szCmd, "receivetask"))	// ��������
	{
		int nTaskID = 0;
		if (2 == sscanf(pszData + 1, "%s %d", szCmd, &nTaskID))
		{
			pUserTaskMgr->ProcessReceiveTask(idUser, nTaskID);
		}
	}
	else if (0 == stricmp(szCmd, "finishtask"))	// �������
	{
		int nTaskID = 0;
		if (2 == sscanf(pszData + 1, "%s %d", szCmd, &nTaskID))
		{
			pUserTaskMgr->ProcessFinishTask(idUser, nTaskID);
		}
	}
	else if (0 == stricmp(szCmd, "giveuptask"))	// ��������
	{
		int nTaskID = 0;
		if (2 == sscanf(pszData + 1, "%s %d", szCmd, &nTaskID))
		{
			pUserTaskMgr->ProcessGiveupTask(idUser, nTaskID);
		}
	}
	else if (0 == stricmp(szCmd, "sendmail"))	// ���Լ����ʼ�
	{
		if (1 == sscanf(pszData + 1, "%s %d", szCmd))
		{
			//pUserMailMgr->SendMail(idUser, "title", "content", "sender", "1 1 2 2 3 3 4 4 5 5 6 6 101 11 102 22 103 33 104 44 111");
			VEC_MAIL_AWARD vecMailAward;
			MAIL_AWARD_DATA awardItem1 = {110001, 100};
			MAIL_AWARD_DATA awardMoney1 = {101, 1};
			vecMailAward.push_back(awardItem1);
			vecMailAward.push_back(awardMoney1);
			pUserMailMgr->SendMail(idUser, "title", "content", "sender", vecMailAward);
		}
	}
	else if (0 == stricmp(szCmd, "maillist"))	// ��ѯ�ʼ��б�
	{
		if (1 == sscanf(pszData + 1, "%s", szCmd))
		{
			VEC_MAIL_LIST mailList;
			pUserMailMgr->QueryMailList(idUser, 1, 10, mailList);
		}
	}
	else if (0 == stricmp(szCmd, "openmail"))	// ���ʼ�
	{
		int nMailID = 0;
		if (2 == sscanf(pszData + 1, "%s %d", szCmd, &nMailID))
		{
			MSG_MAIL_DATA mail ={0};
			pUserMailMgr->ProcessOpenMail(idUser, nMailID, mail);
		}
	}
	else if (0 == stricmp(szCmd, "getmailitem"))	// ȡ�ʼ���Ʒ
	{
		int nMailID = 0;
		if (2 == sscanf(pszData + 1, "%s %d", szCmd, &nMailID))
		{
			MSG_MAIL_DATA mail = {0};
			pUserMailMgr->ProcessGetItem(idUser, nMailID, mail);
		}
	}
	else if (0 == stricmp(szCmd, "unreadmailcount"))	// ��ȡδ���ʼ�����
	{
		if (1 == sscanf(pszData + 1, "%s", szCmd))
		{
			int nUnreadCount = 0;
			pUserMailMgr->GetUnreadMailCount(idUser, nUnreadCount);
		}
	}
}