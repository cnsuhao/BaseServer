////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan ChuangYou, All Rights Reserved
// Moudle: User.cpp
// Author: 彭文奇(Peng Wenqi)
// Created: 2014-11-5
////////////////////////////////////////////////////////////////////////
#include "./User.h"
#include "./GameKernel.h"
MYHEAP_IMPLEMENTATION(CUser, s_heap);

//////////////////////////////////////////////////////////////////////////
CUser::CUser()
{
	m_id = ID_NONE;
	m_eObjectType = GAME_OBJECT_TYPE_USER;
	m_pRecord = NULL;
	m_idSocket = SOCKET_NONE;
}

//////////////////////////////////////////////////////////////////////////
CUser::~CUser()
{
	SAFE_RELEASE(m_pRecord);
}

//////////////////////////////////////////////////////////////////////////
bool CUser::Init( OBJID idUser, SOCKET_ID idSocket )
{
	DEBUG_TRY;
	CHECKF(pGameDatabase);
	CHECKF(idUser >= PLAYER_ID_FIRST);
	CHECKF(!m_pRecord);
	m_id = idUser;
	m_idSocket = idSocket;

	CMxyString strSql("select * from %s where id=%u limit 1", GAME_DB_NAME_USER, idUser);
	RecordsetPtr pRes = pGameDatabase->CreateNewRecordset(strSql.c_str());	
	CHECKF(pRes);
	m_pRecord = pRes->CreateNewRecord();
	CHECKF(m_pRecord);

	//OBJID idAccount = this->GetData(USER_DATA_ACCOUNT_ID);
	//strSql.Format("select * from %s.%s where id=%u limit 1", g_strAccountDatabaseName.c_str(), ACC_DB_NAME_ACCOUNT, idAccount);
	//RecordsetPtr pResAccount = pGameDatabase->CreateNewRecordset(strSql.c_str());	
	//CHECKF(pResAccount);

	//this->SetMemoryDataAttr(mdaUser_AccountType,		pResAccount->GetInt(ACCOUNT_DATA_ACCOUNT_TYPE));
	//this->SetMemoryDataAttr(mdaUser_AccountStatus,		pResAccount->GetInt(ACCOUNT_DATA_ACCOUNT_STATUS));
	//this->SetMemoryDataAttr(mdaUser_AccountStatusParam, pResAccount->GetInt(ACCOUNT_DATA_ACCOUNT_STATUS_PARAM));
	//m_strAccountName = pResAccount->GetStr(ACCOUNT_DATA_NAME);
	//m_strAccountPlatform = pResAccount->GetStr(ACCOUNT_DATA_PLATFORM);
	//m_strAccountChannel = pResAccount->GetStr(ACCOUNT_DATA_CHANNEL);
	//m_strAccountOS = pResAccount->GetStr(ACCOUNT_DATA_OS);
	//m_strBindInviteCode = pResAccount->GetStr(ACCOUNT_DATA_BIND_INVITE_CODE);

	//// 覆盖账号类型到user表
	//if (this->GetData(USER_DATA_ACCOUNT_TYPE) != pResAccount->GetInt(ACCOUNT_DATA_ACCOUNT_TYPE))
	//{
	//	this->SetData(USER_DATA_ACCOUNT_TYPE, pResAccount->GetInt(ACCOUNT_DATA_ACCOUNT_TYPE), true);
	//}

	//this->SetMemoryDataAttr(mdaUser_OnTimer_MinuteSecond, ::TimeGet(TIME_SECOND));
	return true;
	DEBUG_CATCHF2("CUser::Init idUser[%u]!", idUser);
}

////////////////////////////////////////////////////////////////////////
// Description: 所有内容释放前的调用处理
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void CUser::BeforeRelease()
{	
	//auto nCurSecond  = ::TimeGet(TIME_SECOND);
	//this->SetData(USER_DATA_EXIT_TIME, nCurSecond);

	//auto nAllOnlineSecond = this->GetData(USER_DATA_ALL_ONLINE_TIME) + this->GetMemoryDataAttr(mdaUser_OnlineSecond);
	//this->SetData(USER_DATA_ALL_ONLINE_TIME, nAllOnlineSecond);

	//if (::TimeGet(YEAR_MONTH_DAY) != this->GetData(USER_DATA_LAST_LOGIN))
	//{
	//	this->SetData(USER_DATA_YESTERDAY_LOGIN, 1);
	//}

	//if (m_pRecord)
	//{
	//	m_pRecord->UpdateRecord(DBUPDATE_ASYNC);
	//}
}



////////////////////////////////////////////////////////////////////////
// Description: 获得数据库数据
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: I64
////////////////////////////////////////////////////////////////////////
I64 CUser::GetData( USER_DATA eData ) const
{
	CHECKF(m_pRecord);
	//CHECKF(eData >= USER_DATA_BEGIN && eData < USER_DATA_END);
	//CHECKF(eData != USER_DATA_NAME && eData != USER_DATA_SIGNATURE && eData != USER_DATA_ADDRESS);
	return m_pRecord->GetInt64(eData);
}

////////////////////////////////////////////////////////////////////////
// Description: 获得数据库字符串
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: const char*
////////////////////////////////////////////////////////////////////////
const char* CUser::GetStr( USER_DATA eData ) const
{
	CHECKF(m_pRecord);
	//CHECKF(eData == USER_DATA_NAME 
	//	|| eData == USER_DATA_SIGNATURE
	//	|| eData == USER_DATA_ADDRESS);
	return m_pRecord->GetStr(eData);
}

////////////////////////////////////////////////////////////////////////
// Description: 
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: 
////////////////////////////////////////////////////////////////////////
bool CUser::SetData( USER_DATA eData, I64 i64Data, bool bUpdate /*= false*/ )
{
	CHECKF(m_pRecord);
	//CHECKF(eData >= USER_DATA_BEGIN && eData < USER_DATA_END);
	//CHECKF(eData != USER_DATA_NAME && eData != USER_DATA_SIGNATURE && eData != USER_DATA_ADDRESS);
	//m_pRecord->SetInt64(eData, i64Data);
	//m_pRecord->UpdateRecord(bUpdate);
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: 
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: 
////////////////////////////////////////////////////////////////////////
bool CUser::SetStr( USER_DATA eData, const char* pszStr, bool bUpdate /*= false*/ )
{
	CHECKF(m_pRecord);
	//CHECKF(eData == USER_DATA_NAME 
	//	|| eData == USER_DATA_SIGNATURE
	//	|| eData == USER_DATA_ADDRESS);
	//CHECKF(pszStr);
	//m_pRecord->SetStr(eData, pszStr, strlen(pszStr) + 1);
	//m_pRecord->UpdateRecord(bUpdate);
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: 总心跳入口
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: 
////////////////////////////////////////////////////////////////////////
void CUser::OnTimer()
{
	DEBUG_TRY;

	//auto nNowSecond = ::TimeGet(TIME_SECOND);
	//auto nSaveEverySecond = this->GetMemoryDataAttr(mdaUser_OnTimer_EverySecond);
	//if (nNowSecond > nSaveEverySecond)
	//{
	//	this->SetMemoryDataAttr(mdaUser_OnTimer_EverySecond, nNowSecond);
	//	this->OnTimerSecond();
	//}

	//auto nSaveMinuteSecond = this->GetMemoryDataAttr(mdaUser_OnTimer_MinuteSecond);
	//if (nNowSecond >= (nSaveMinuteSecond + 60))
	//{
	//	this->SetMemoryDataAttr(mdaUser_OnTimer_MinuteSecond, nNowSecond);
	//	this->OnTimerMinute();
	//}

	DEBUG_CATCH("CUser::OnTimer");
}

////////////////////////////////////////////////////////////////////////
// Description: 心跳回滚入口
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: 
////////////////////////////////////////////////////////////////////////
void CUser::OnTimerRollback()
{

}

////////////////////////////////////////////////////////////////////////
// Description: 秒级心跳
// Arguments:
// Author: 陈建军(Chen Jianjun)
// Return Value: 
////////////////////////////////////////////////////////////////////////
void CUser::OnTimerSecond()
{
	DEBUG_TRY;
	//pPokerMgr->OnTimerRecoverMagicPoint(m_id);
	//pUserMoneyMgr->OnTimerRecoverPower(m_id);
	//pUserMoneyMgr->OnTimerRecoverTreasurePower(m_id);
	DEBUG_CATCH("CUser::OnTimerSecond");
}

////////////////////////////////////////////////////////////////////////
// Description: 每分钟心跳
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: 
////////////////////////////////////////////////////////////////////////
void CUser::OnTimerMinute()
{
	DEBUG_TRY;
	//this->AddMemoryDataAttr(mdaUser_OnlineSecond, 60);
	//pItemMgr->OnTimer(m_id);
	//pSystemSettingsMgr->OnTimer(m_id);
	//pMarksInfoMgr->OnTimerUser(m_id);
	DEBUG_CATCH("CUser::OnTimerMinute");
}

//////////////////////////////////////////////////////////////////////////
void CUser::SetIP( const char* pszIP )
{
	CHECK(pszIP);
	m_strIP = pszIP;
}

////////////////////////////////////////////////////////////////////////
// Description: 设置mac地址
// Arguments:	通过验证返回true
// Author: 彭文奇(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool CUser::SetMac( const char* pszMac )
{
	//CHECKF(pszMac);
	//CHECKF(pGameDatabase);
	//m_strMac = pszMac;

	//// 在gm_mac表中查找
	//CMxyString strSql("select count(*) from %s.%s where address_mac='%s'", g_strAccountDatabaseName.c_str(), ACC_DB_NAME_GM_MAC, m_strMac.c_str());
	//RecordsetPtr pRes = pGameDatabase->CreateNewRecordset(strSql.c_str());
	//CHECKF(pRes);
	//if (pRes->GetInt(0) > 0)
	//{
	//	this->SetMemoryDataAttr(mdaUser_GmMacPass, TRUE);
	//	return true;
	//}

	return false;
}
