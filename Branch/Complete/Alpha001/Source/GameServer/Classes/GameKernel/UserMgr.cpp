////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan ChuangYou, All Rights Reserved
// Moudle: UserMgr.cpp
// Author: 彭文奇(Peng Wenqi)
// Created: 2014-11-5
////////////////////////////////////////////////////////////////////////
#include "./UserMgr.h"
#include "./User.h"
#include "./GameKernel.h"
#include "./Network/NetMsg.h"

#include "./Network/MsgGameKickReason.h"
#include "./Network/MsgGameUserInfo.h"
#include "./Network/MsgGameUserAttr.h"
#include "./Network/MsgGameUpdateOnlineInfo.h"

CUserMgr* CUserMgr::s_pInstance = NULL;
MYHEAP_IMPLEMENTATION(CUserMgr, s_heap);

//////////////////////////////////////////////////////////////////////////
bool CUserMgr::Init()
{
	return true;
}

//////////////////////////////////////////////////////////////////////////
void CUserMgr::Release()
{
	for (auto iter : m_mapUser)
	{
		this->ReleaseUser(iter.second);
	}
	m_mapSocket.clear();
	m_mapUserName.clear();
	m_mapUser.clear();
}

//////////////////////////////////////////////////////////////////////////
void CUserMgr::OnTimer()
{
	for (auto iter : m_mapUser)
	{
		CUser* pUser = iter.second;
		CHECKC(pUser);
		pUser->OnTimer();
	}
}

//////////////////////////////////////////////////////////////////////////
void CUserMgr::OnTimerRollback()
{
	for (auto iter : m_mapUser)
	{
		CUser* pUser = iter.second;
		CHECKC(pUser);
		pUser->OnTimerRollback();
	}
}

////////////////////////////////////////////////////////////////////////
// Description: 根据角色id发送消息
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool CUserMgr::SendMsg( OBJID idUser, game_kernel::CNetMsg* pMsg )
{
	CHECKF(idUser && pMsg);
	CUser* pUser = this->GetUserByID(idUser);
	if (!pUser)
	{
		tolog4("CUserMgr::SendMsg idUser[%u] is not online! MsgType[%u], MsgSize[%d]", idUser, pMsg->GetType(), pMsg->GetSize());
		return false;
	}
	return pGameKernel->SendMsg(pMsg, pUser->GetSocketID());
}

//////////////////////////////////////////////////////////////////////////
//// Description: 玩家登陆
//// Arguments:
//// Author: 彭文奇(Peng Wenqi)
//// Return Value: bool
//////////////////////////////////////////////////////////////////////////
bool CUserMgr::LoginUser(OBJID idUser, SOCKET_ID idSocket)
{
	DEBUG_TRY;
	CHECKF(idUser && idSocket > SOCKET_NONE);
	CHECKF(m_mapSocket.find(idSocket) == m_mapSocket.end());
	CHECKF(m_mapUser.find(idUser) == m_mapUser.end());
	CUser* pUser = CUser::CreateNew();
	CHECKF(pUser);
	if (!this->InitUser(pUser, idUser, idSocket))
	{
		SAFE_RELEASE(pUser);
		return false;
	}

	m_mapSocket[idSocket] = idUser;
	m_mapUserName[pUser->GetStr(USER_DATA_NAME)] = idUser;
	m_mapUser[idUser]	  = pUser;	

	// 发送UserInfo
	CMsgGameUserInfo msgUserInfo;
	IF_OK (msgUserInfo.CreateUserInfo(pUser))
	{
		this->SendMsg(idUser, &msgUserInfo);
	}

	return true;
	DEBUG_CATCHF2("CUserMgr::LoginUser idUser[%u]!", idUser);
}

////////////////////////////////////////////////////////////////////////
// Description: 客户端告知玩家登陆完成
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool CUserMgr::LoginUserOk(OBJID idUser)
{
	DEBUG_TRY;
	CHECKF(idUser);
	CUser* pUser = this->GetUserByID(idUser);
	CHECKF(pUser);

	// 设置昨日登陆标记和本次登陆时间（年月日）
	//auto nLastExitTime = pUser->GetData(USER_DATA_EXIT_TIME);
	//auto nCurDayStartTime = ::TimeGet(TIME_DAY_START);
	//auto nYesterdayStartTime = nCurDayStartTime - 24 * 60 * 60;
	//if (nLastExitTime < nYesterdayStartTime)
	//{
	//	pUser->SetData(USER_DATA_YESTERDAY_LOGIN, 0);
	//}
	//else if (nLastExitTime < nCurDayStartTime)
	//{
	//	pUser->SetData(USER_DATA_YESTERDAY_LOGIN, 1);
	//}
	//pUser->SetData(USER_DATA_LAST_LOGIN, ::TimeGet(YEAR_MONTH_DAY), true);

	//// 玩家登陆完成处理内容
	//pPokerMgr->LoginUser(idUser);
	//pSyndicateMgr->LoginUser(idUser);
	//pShopMgr->LoginUser(idUser);
	//pMineMgr->LoginUser(idUser);
	//pMercenaryMgr->LoginUser(idUser);
	//pNearFriendMgr->LoginUser(idUser);
	//pSystemSettingsMgr->LoginUser(idUser);
	//pAchievementMgr->LoginUser(idUser);
	//pMarksInfoMgr->LoginUser(idUser);

	//// 登陆完成执行脚本
	//CHECKF(pGameAction->ProcessAction(ACTION_ID_USER_LOGIN_OVER, idUser));

	//// 强制更新玩家共享信息
	//this->RequestUpdateUserOnlineInfo(idUser, true);
	return true;
	DEBUG_CATCHF2("CUserMgr::LoginOverUser idUser[%u]!", idUser);
}

////////////////////////////////////////////////////////////////////////
// Description: 玩家登出
// Arguments:	
// Author: 彭文奇(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool CUserMgr::LogoutUser( OBJID idUser )
{
	DEBUG_TRY;
	CHECKF(idUser);
	CUser* pUser = this->GetUserByID(idUser);
	if (pUser)
	{
		SOCKET_ID idSocket = pUser->GetSocketID();
		CMxyString strName = pUser->GetStr(USER_DATA_NAME);
		OBJID idAccount    = pUser->GetData(USER_DATA_ACCOUNT_ID);
		CHECKF(this->ReleaseUser(pUser));
		m_mapUser.erase(idUser);
		m_mapSocket.erase(idSocket);
		m_mapUserName.erase(strName);
		::LogSaveLoginout("GameKernel Logout idUser[%u], SocketID[%d], AccountID[%u], UserName[%s]", idUser, idSocket, idAccount, strName.c_str());
	}
	
	return true;
	DEBUG_CATCHF2("CUserMgr::LogoutUser idUser[%u]!", idUser);
}

////////////////////////////////////////////////////////////////////////
// Description: 踢出玩家
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool CUserMgr::KickUserByID( OBJID idUser, KICK_REASON eReason /*= KICK_REASON_DEFAULT*/, int nParam /*= 0*/ )
{
	DEBUG_TRY;
	CHECKF(idUser);
	CUser* pUser = this->GetUserByID(idUser);
	IF_NOT (pUser)
	{
		tolog4("CUserMgr::KickUserByUser can not find idUser[%u], eReason[%d], nParam[%d]", idUser, eReason, nParam);
		return false;
	}

	SOCKET_ID idSocket = pUser->GetSocketID();
	::LogSaveLoginout("CUserMgr::KickUserByUser idUser[%u], eReason[%d], nParam[%d]", idUser, eReason, nParam);

	// 发送被踢消息
	CMsgGameKickReason msg;
	IF_OK (msg.CreateInfo(eReason, nParam))
	{
		pGameKernel->SendMsg(&msg, idSocket);
	}

	pGameKernel->CloseSocket(idSocket);
	return true;
	DEBUG_CATCHF4("CUserMgr::KickUserByUser idUser[%u], eReason[%d], nParam[%d]!", idUser, eReason, nParam);
}

////////////////////////////////////////////////////////////////////////
// Description: 踢出玩家
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool CUserMgr::KickUserBySocket( SOCKET_ID idSocket, KICK_REASON eReason /*= KICK_REASON_DEFAULT*/, int nParam /*= 0*/ )
{
	DEBUG_TRY;
	CHECKF(idSocket > SOCKET_NONE);
	::LogSaveLoginout("CUserMgr::KickUserByUser eReason[%d] nParam[%d]", eReason, nParam);

	// 发送被踢消息
	CMsgGameKickReason msg;
	IF_OK (msg.CreateInfo(eReason, nParam))
	{
		pGameKernel->SendMsg(&msg, idSocket);
	}

	pGameKernel->CloseSocket(idSocket);
	return true;
	DEBUG_CATCHF4("CUserMgr::KickUserBySocket idSocket[%d], eRaason[%d], nParam[%d]!", idSocket, eReason, nParam);
}

////////////////////////////////////////////////////////////////////////
// Description: 角色初始化
// Arguments:	不会操作本类容器
// Author: 彭文奇(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool CUserMgr::InitUser( CUser* pUser, OBJID idUser, SOCKET_ID idSocket )
{
	DEBUG_TRY;
	CHECKF(pUser && idUser);
	CHECKF(idSocket > SOCKET_NONE);

	// 初始化CUser类
	CHECKF(pUser->Init(idUser, idSocket));
	
	// 初始化其他角色相关内容
//	//CHECKF(pUserMoneyMgr->InitUser(idUser, pUser->GetData(USER_DATA_ACCOUNT_ID)));
//	//CHECKF(pItemMgr->InitUser(idUser));
//	//CHECKF(pUserTmpDataMgr->InitUser(idUser));
//	//CHECKF(pMaskMgr->InitUser(idUser));
//	//CHECKF(pTalkMgr->InitUser(idUser));
//	//CHECKF(pUserTaskMgr->InitUser(idUser));
//	//CHECKF(pNewCardMgr->InitUser(idUser));
//	//CHECKF(pBlackListMgr->InitUser(idUser));
//	//CHECKF(pPokerMgr->InitUser(idUser));
//	//CHECKF(pFriendMgr->InitUser(idUser));
//	//CHECKF(pShopMgr->InitUser(idUser));
//	//CHECKF(pChallengeBossMgr->InitUser(idUser));
//	//CHECKF(pDelayActionMgr->InitUser(idUser));
//	//CHECKF(pGooseTowerMgr->InitUser(idUser));
//	//CHECKF(pPuzzleMgr->InitUser(idUser));
//	//CHECKF(pMercenaryMgr->InitUser(idUser));
//	//CHECKF(pMineFightPokerMgr->InitUser(idUser));
//	//CHECKF(pArenaMgr->InitUser(idUser));
//	//CHECKF(pWarRoadMgr->InitUser(idUser));
//	//CHECKF(pFriendInviteMgr->InitUser(idUser));
//	//CHECKF(pSynGiftBoxMgr->InitUser(idUser));
//	//CHECKF(pCrossMgr->InitUser(idUser));
//	//CHECKF(pSynWorshipMgr->InitUser(idUser));
//	//CHECKF(pAchievementMgr->InitUser(idUser));
//	//CHECKF(pNearFriendMgr->InitUser(idUser));
//	//CHECKF(pSystemSettingsMgr->InitUser(idUser));
//	//CHECKF(pMineMgr->InitUser(idUser));
//	//CHECKF(pBuffMgr->InitUser(idUser));
//
	return true;
	DEBUG_CATCHF2("CUserMgr::InitUser idUser[%u]!", idUser);
}

////////////////////////////////////////////////////////////////////////
// Description: 角色析构
// Arguments:	不会操作本类容器
// Author: 彭文奇(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool CUserMgr::ReleaseUser( CUser* pUser )
{
	DEBUG_TRY;
	CHECKF(pUser);

//	// 所有内容释放前调用
//	pUser->BeforeRelease();
//	//pSyndicateMgr->LogoutUser(pUser->GetID());
//	//pBattleMgr->LogoutUser(pUser->GetID());
//
//	//// 释放其他角色相关内容
//	//CHECKB(pUserMoneyMgr->ReleaseUser(pUser->GetID()));
//	//CHECKB(pItemMgr->ReleaseUser(pUser->GetID()));
//	//CHECKB(pUserTmpDataMgr->ReleaseUser(pUser->GetID()));
//	//CHECKB(pMaskMgr->ReleaseUser(pUser->GetID()));
//	//CHECKB(pTalkMgr->ReleaseUser(pUser->GetID()));
//	//CHECKB(pUserTaskMgr->ReleaseUser(pUser->GetID()));
//	//CHECKB(pNewCardMgr->ReleaseUser(pUser->GetID()));
//	//CHECKB(pBlackListMgr->ReleaseUser(pUser->GetID()));
//	//CHECKB(pPokerMgr->ReleaseUser(pUser->GetID()));
//	//CHECKB(pFriendMgr->ReleaseUser(pUser->GetID()));
//	//CHECKB(pShopMgr->ReleaseUser(pUser->GetID()));
//	//CHECKB(pAchievementMgr->ReleaseUser(pUser->GetID()));
//	//CHECKB(pChallengeBossMgr->ReleaseUser(pUser->GetID()));
//	//CHECKB(pDelayActionMgr->ReleaseUser(pUser->GetID()));
//	//CHECKB(pGooseTowerMgr->ReleaseUser(pUser->GetID()));
//	//CHECKB(pPuzzleMgr->ReleaseUser(pUser->GetID()));
//	//CHECKB(pArenaMgr->ReleaseUser(pUser->GetID()));
//	//CHECKB(pWarRoadMgr->ReleaseUser(pUser->GetID()));
//	//CHECKB(pMercenaryMgr->ReleaseUser(pUser->GetID()));
//	//CHECKB(pMineFightPokerMgr->ReleaseUser(pUser->GetID()));
//	//CHECKB(pFriendInviteMgr->ReleaseUser(pUser->GetID()));
//	//CHECKB(pSynGiftBoxMgr->ReleaseUser(pUser->GetID()));
//	//CHECKB(pSystemSettingsMgr->ReleaseUser(pUser->GetID()));
//	//CHECKB(pNearFriendMgr->ReleaseUser(pUser->GetID()));
//	//CHECKB(pCrossMgr->ReleaseUser(pUser->GetID()));
//	//CHECKB(pSynWorshipMgr->ReleaseUser(pUser->GetID()));
//	//CHECKB(pMineMgr->ReleaseUser(pUser->GetID()));
//	//CHECKB(pBuffMgr->ReleaseUser(pUser->GetID()));
//	//CHECKB(pMarksInfoMgr->ReleaseUser(pUser->GetID()));

	// 释放CUser类
	SAFE_RELEASE(pUser);
	return true;
	DEBUG_CATCHF("CUserMgr::ReleaseUser Crash!");
}

////////////////////////////////////////////////////////////////////////
// Description: 获得角色指针
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: CUser*
////////////////////////////////////////////////////////////////////////
CUser* CUserMgr::GetUserByID( OBJID idUser ) const
{
	CHECKF(idUser);
	auto iter  = m_mapUser.find(idUser);
	if (iter != m_mapUser.end())
	{
		return iter->second;
	}
	return nullptr;
}

////////////////////////////////////////////////////////////////////////
// Description: 
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: 
////////////////////////////////////////////////////////////////////////
CUser* CUserMgr::GetUserBySocket( SOCKET_ID idSocket ) const
{
	CHECKF_NOLOG(idSocket > SOCKET_NONE);
	auto iter = m_mapSocket.find(idSocket);
	if (iter != m_mapSocket.end())
	{
		return this->GetUserByID(iter->second);
	}
	return nullptr;
}

////////////////////////////////////////////////////////////////////////
// Description: 获得角色指针
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: CUser*
////////////////////////////////////////////////////////////////////////
CUser* CUserMgr::GetUserByName( const char* pszUserName ) const
{
	CHECKF(pszUserName);
	auto iter = m_mapUserName.find(pszUserName);
	if (iter != m_mapUserName.end())
	{
		return this->GetUserByID(iter->second);
	}
	return nullptr;
}

////////////////////////////////////////////////////////////////////////
// Description: 获得角色指针
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: CUser*
////////////////////////////////////////////////////////////////////////
CUser* CUserMgr::GetUserByMsg( game_kernel::CNetMsg* pMsg ) const
{
	CHECKF(pMsg);
	return this->GetUserBySocket(pMsg->GetSocketID());
}

////////////////////////////////////////////////////////////////////////
// Description: 获得角色id
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: OBJID
////////////////////////////////////////////////////////////////////////
OBJID CUserMgr::GetUserIDByMsg( game_kernel::CNetMsg* pMsg ) const
{
	CHECKF(pMsg);
	CUser* pUser = this->GetUserBySocket(pMsg->GetSocketID());
	if (pUser)
	{
		return pUser->GetID();
	}
	return ID_NONE;
}

////////////////////////////////////////////////////////////////////////
// Description: 获得角色id
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: OBJID
////////////////////////////////////////////////////////////////////////
OBJID CUserMgr::GetUserIDByName( const char* pszUserName ) const
{
	CHECKF(pszUserName);
	auto iter = m_mapUserName.find(pszUserName);
	if (iter != m_mapUserName.end())
	{
		return iter->second;
	}
	return ID_NONE;
}

//////////////////////////////////////////////////////////////////////////
//// Description: 正常流程登出
//// Arguments:
//// Author: 彭文奇(Peng Wenqi)
//// Return Value: 
//////////////////////////////////////////////////////////////////////////
//void CUserMgr::KickAllUser()
//{
//	// 通知所有玩家被踢
//	//CMsgGameKickReason msg;
//	//IF_OK(msg.CreateInfo(KICK_REASON_SYSTEM))
//	//{
//	//	for (auto iterSocket : m_mapSocket)
//	//	{
//	//		this->SendMsgBySocket(iterSocket.first, &msg);
//	//	}
//	//}
//	
//	// 断开所有连接
//	pGameKernel->BreakAllUser();
//}
//
//////////////////////////////////////////////////////////////////////////
//// Description: 强制析构所有玩家
//// Arguments:
//// Author: 彭文奇(Peng Wenqi)
//// Return Value: 
//////////////////////////////////////////////////////////////////////////
//// void CUserMgr::LogoutAllUser()
//// {
//// 	ID_VEC vecUserID;
//// 	for (MAP_USER::iterator iter = m_mapUser.begin(); iter != m_mapUser.end(); iter++)
//// 	{
//// 		CUser* pUser = iter->second;
//// 		CHECKC(pUser);
//// 		vecUserID.push_back(pUser->GetID());
//// 	}
//// 
//// 	for (ID_VEC_ITER iter = vecUserID.begin(); iter != vecUserID.end(); iter++)
//// 	{
//// 		this->LogoutUser(*iter);
//// 	}
//// }
//
//////////////////////////////////////////////////////////////////////////
//// Description: 判断玩家是否GM号
//// Arguments:
//// Author: 陈建军(Chen Jianjun)
//// Return Value: bool
//////////////////////////////////////////////////////////////////////////
//bool CUserMgr::IsGM(OBJID idUser)
//{
//	DEBUG_TRY;
//	CHECKF(idUser);
//	CUser* pUser = this->GetUserByID(idUser);
//	if (pUser)
//	{
//		return pUser->IsGM();
//	}
//	return false;
//	DEBUG_CATCHF2("CUserMgr::IsGM idUser[%d]", idUser);
//}
//
//////////////////////////////////////////////////////////////////////////
//// Description: 判断玩家昨日是否登陆过
//// Arguments:
//// Author: 陈建军（Chen Jianjun）
//// Return Value: bool
//////////////////////////////////////////////////////////////////////////
//bool CUserMgr::IsYesterdayLogin(OBJID idUser, bool bForce/* = false*/)
//{
//	DEBUG_TRY;
//	CHECKF(idUser);
//	//auto pUser = this->GetUserByID(idUser);
//	//if (pUser)
//	//{
//	//	if (pUser->GetData(USER_DATA_YESTERDAY_LOGIN) > 0 || (::TimeGet(YEAR_MONTH_DAY) != pUser->GetData(USER_DATA_LAST_LOGIN)))
//	//	{
//	//		return true;
//	//	}
//	//}
//
//	//auto iterUserOnline = m_mapUserOnline.find(idUser);
//	//if (iterUserOnline != m_mapUserOnline.end())
//	//{
//	//	if (iterUserOnline->second.nYesterdayLogin > 0 || (::TimeGet(YEAR_MONTH_DAY) != iterUserOnline->second.nLastLoginTime))
//	//	{
//	//		return true;
//	//	}
//	//}
//	//else if (bForce)
//	//{
//	//	CMxyString strSql("select exit_time, yesterday_login from %s where id = %u limit 1", GAME_DB_NAME_USER, idUser);
//	//	RecordsetPtr pRes = pGameDatabase->CreateNewRecordset(strSql.c_str());
//	//	CHECKF(pRes && pRes->RecordCount() > 0);
//	//	auto nLastExitTime    = pRes->GetInt(0);
//	//	auto nCurDayStartTime = ::TimeGet(TIME_DAY_START);
//	//	if (nLastExitTime >= nCurDayStartTime)
//	//	{
//	//		return (pRes->GetInt(1) > 0);
//	//	}
//	//	else if (nLastExitTime >= nCurDayStartTime - 24 * 60 * 60)
//	//	{
//	//		return true;
//	//	}
//	//}
//	return false;
//	DEBUG_CATCHF2("CUserMgr::IsYesterdayLogin idUser[%d]", idUser);
//}
//
//////////////////////////////////////////////////////////////////////////
//// Description: 获取创建时间
//// Arguments:
//// Author: 陈建军(Chen Jianjun)
//// Return Value: int
//////////////////////////////////////////////////////////////////////////
//int CUserMgr::GetCreateTime(OBJID idUser)
//{
//	DEBUG_TRY;
//	CHECKF(idUser);
//	auto pUser = this->GetUserByID(idUser);
//	CHECKF(pUser);
//	return pUser->GetData(USER_DATA_CREATE_TIME);
//	DEBUG_CATCHF2("CUserMgr::GetCreateTime idUser[%d]", idUser);
//}
//
//////////////////////////////////////////////////////////////////////////
//// Description: 获取创建天数
//// Arguments:
//// Author: 陈建军(Chen Jianjun)
//// Return Value: int
//////////////////////////////////////////////////////////////////////////
//int CUserMgr::GetCreateDay(OBJID idUser)
//{
//	DEBUG_TRY;
//	CHECKF(idUser);
//	auto pUser = this->GetUserByID(idUser);
//	CHECKF(pUser);
//	auto nDay = 1;
//	auto nCreateTime = pUser->GetData(USER_DATA_CREATE_TIME);
//	auto nCurDayStartTime = ::TimeGet(TIME_DAY_START);
//	if (nCreateTime < nCurDayStartTime)
//	{
//		auto nDayTime = 24 * 60 * 60;
//		nDay = (nCurDayStartTime - nCreateTime) / nDayTime + 2;
//	}
//	return nDay;
//	DEBUG_CATCHF2("CUserMgr::GetCreateDay idUser[%d]", idUser);
//}
//
////////////////////////////////////////////////////////////////////////////
////// Description: 是否在线
////// Arguments:
////// Author: 彭文奇(Peng Wenqi)
////// Return Value: bool
////////////////////////////////////////////////////////////////////////////
////bool CUserMgr::IsOnline( OBJID idUser, bool bThisLine /*= true*/ ) const
////{
////	if (this->GetUserByID(idUser) != NULL)
////	{
////		return true;
////	}
////
////	if (bThisLine)
////	{
////		return false;
////	}
////
////	if (m_mapUserOnline.find(idUser) != m_mapUserOnline.end())
////	{
////		return true;
////	}
////
////	return false;
////}
////
////////////////////////////////////////////////////////////////////////////
////// Description: 查询玩家共享在线信息
////// Arguments:
////// Author: 彭文奇(Peng Wenqi)
////// Return Value: const USER_ONLINE_INFO*
////////////////////////////////////////////////////////////////////////////
////const USER_ONLINE_INFO* CUserMgr::GetUserOnlineInfo( OBJID idUser ) const
////{
////	CHECKF(idUser);
////	MAP_USER_ONLINE::const_iterator iter = m_mapUserOnline.find(idUser);
////	if (iter == m_mapUserOnline.end())
////	{
////		return NULL;
////	}
////	return &(iter->second);
////}
////
////////////////////////////////////////////////////////////////////////////
////// Description：根据玩家名字查询玩家共享在线信息
////// Arguments: 
////// Author: 李飞(Li Fei) 
////// Date: 20141119
////// Return Value: 
////////////////////////////////////////////////////////////////////////////
////const USER_ONLINE_INFO* CUserMgr::GetUserOnlineInfo(const char* pszName) const 
////{
////	MAP_USER_ONLINE::const_iterator iterUser = m_mapUserOnline.begin();
////	for (; iterUser != m_mapUserOnline.end(); iterUser++)
////	{
////		const USER_ONLINE_INFO& stUserOnlineInfo = iterUser->second;
////		if (0 == strcmp(pszName, stUserOnlineInfo.szUserName))
////		{
////			return &(iterUser->second);
////		}
////	}
////
////	return NULL;
////}
////////////////////////////////////////////////////////////////////////////
////// Description: 增加玩家共享在线信息
////// Arguments:
////// Author: 彭文奇(Peng Wenqi)
////// Return Value: void
////////////////////////////////////////////////////////////////////////////
////void CUserMgr::AddUserOnlineInfo( const USER_ONLINE_INFO* pInfo )
////{
////	CHECK(pInfo);
////	CHECK(pInfo->idUser);
////
////	// 调试信息
////#ifdef MYDEBUG
////	CMxyString strTextUtf8("AddUserOnline ID[%u],Name[%s],Account[%u],Line[%d]", pInfo->idUser, pInfo->szUserName, pInfo->idAccount, pInfo->nLine);
////	CMxyString strTextAnsi = ::MyUtf8ToANSI(strTextUtf8.c_str());
////	pGameKernel->PrintText(strTextAnsi.c_str());
////#endif
////
////	m_mapUserOnline[pInfo->idUser] = *pInfo;
////
////	// 如果是本线玩家加入, 强制更新
////	if (this->IsOnline(pInfo->idUser, true) && pInfo->nLine == g_nServerLine)
////	{
////		this->RequestUpdateUserOnlineInfo(pInfo->idUser, true);
////	}
////}
////
////////////////////////////////////////////////////////////////////////////
////// Description: 删除玩家共享在线信息
////// Arguments:
////// Author: 彭文奇(Peng Wenqi)
////// Return Value: void
////////////////////////////////////////////////////////////////////////////
////void CUserMgr::DelUserOnlineInfo( OBJID idUser )
////{
////	CHECK(idUser);
////	MAP_USER_ONLINE::iterator iter = m_mapUserOnline.find(idUser);
////	if (iter == m_mapUserOnline.end())
////	{
////		return;
////	}
////
////	// 调试信息
////#ifdef MYDEBUG
////	CMxyString strTextUtf8("DelUserOnline ID[%u],Name[%s],Account[%u],Line[%d]", iter->second.idUser, iter->second.szUserName, iter->second.idAccount, iter->second.nLine);
////	CMxyString strTextAnsi = ::MyUtf8ToANSI(strTextUtf8.c_str());
////	pGameKernel->PrintText(strTextAnsi.c_str());
////#endif
////
////	// 更新好友共享信息
////	CHECKB(pFriendMgr->UpdateFriendOnlineInfo(idUser));
////
////	m_mapUserOnline.erase(iter);
////}
////
////////////////////////////////////////////////////////////////////////////
////// Description: 请求 更新玩家共享在线信息
////// Arguments:	向关系服申请
////// Author: 彭文奇(Peng Wenqi)
////// Return Value: void
////////////////////////////////////////////////////////////////////////////
////void CUserMgr::RequestUpdateUserOnlineInfo( OBJID idUser, bool bForce /*= false*/ )
////{
////	CHECK(idUser);
////	MAP_USER_ONLINE::iterator iter = m_mapUserOnline.find(idUser);
////	CHECK(iter != m_mapUserOnline.end());
////	CUser* pUser = this->GetUserByID(idUser);
////	CHECK(pUser);
////
////	bool bModify = false;
////
////	// 有任意一项属性发生变化, 才发出请求消息
////	if (iter->second.nLev	!= pUser->GetData(USER_DATA_LEV) ||
////		iter->second.nMaxScore	!= pUser->GetData(USER_DATA_MAX_SCORE) ||
////		iter->second.nLookFace != pUser->GetData(USER_DATA_LOOKFACE) ||
////		iter->second.nSex != pUser->GetData(USER_DATA_SEX) ||
////		iter->second.nLookFaceFrame != pUser->GetData(USER_DATA_LOOKFACE_FRAME) ||
////		iter->second.nBirthday != pUser->GetData(USER_DATA_BIRTHDAY) ||
////		iter->second.nGlamour != pUser->GetData(USER_DATA_GLAMOUR))
////	{
////		bModify = true;
////	}
////
////	if (!bModify && !bForce)
////	{
////		return;
////	}
////
////	// 内部修改
////	::SafeCopy(iter->second.szUserName, pUser->GetStr(USER_DATA_NAME), sizeof(iter->second.szUserName));
////	::SafeCopy(iter->second.szSignature, pUser->GetStr(USER_DATA_SIGNATURE), sizeof(iter->second.szSignature));
////	::SafeCopy(iter->second.szAddress, pUser->GetStr(USER_DATA_ADDRESS), sizeof(iter->second.szAddress));
////	iter->second.nLev	= pUser->GetData(USER_DATA_LEV);
////	iter->second.nMaxScore = pUser->GetData(USER_DATA_MAX_SCORE);
////	iter->second.nLookFace = pUser->GetData(USER_DATA_LOOKFACE);
////	iter->second.nSex = pUser->GetData(USER_DATA_SEX);
////	iter->second.nLookFaceFrame = pUser->GetData(USER_DATA_LOOKFACE_FRAME);
////	iter->second.nBirthday = pUser->GetData(USER_DATA_BIRTHDAY);
////	iter->second.nGlamour = pUser->GetData(USER_DATA_GLAMOUR);
////	iter->second.nLastLoginTime  = pUser->GetData(USER_DATA_LAST_LOGIN);
////	iter->second.nYesterdayLogin = pUser->GetData(USER_DATA_YESTERDAY_LOGIN);
////
////	// 发送给关系服
////	CMsgGameUpdateOnlineInfo msg;
////	CHECK(msg.CreateUserInfo(&(iter->second)));
////	pGameKernel->SendRelationMsg(&msg);
////}
////
////////////////////////////////////////////////////////////////////////////
////// Description: 处理 更新玩家共享在线信息
////// Arguments:	关系服通知处理
////// Author: 彭文奇(Peng Wenqi)
////// Return Value: 
////////////////////////////////////////////////////////////////////////////
////void CUserMgr::ProcessUpdateUserOnlineInfo( const USER_ONLINE_INFO* pInfo )
////{
////	CHECK(pInfo);
////	MAP_USER_ONLINE::iterator iter = m_mapUserOnline.find(pInfo->idUser);
////	if (iter == m_mapUserOnline.end())
////	{
////		return;
////	}
////
////	DEBUG_TRY;
////	memcpy(&(iter->second), pInfo, sizeof(USER_ONLINE_INFO));
////	DEBUG_CATCH("CUserMgr::ProcessUpdateUserOnlineInfo memcpy");
////}
//
//////////////////////////////////////////////////////////////////////////
//// Description: 通过角色名获取玩家ID(不在本线通过数据库查询)
//// Arguments：
//// Author: 龚建伟(Gong Jianwei)
//// Return Value: OBJID
//////////////////////////////////////////////////////////////////////////
//OBJID CUserMgr::GetUserIDFromDB(const char* pszUserName) const
//{
//	CHECKF(pszUserName);
//	MAP_USER_NAME::const_iterator iter = m_mapUserName.find(pszUserName);
//	if (iter != m_mapUserName.end())
//	{
//		return iter->second;
//	}
//
//	CMxyString strSql;
//	strSql.Format("select id from %s where name = %s limit 1", GAME_DB_NAME_USER, pszUserName);
//	RecordsetPtr pRes = pGameDatabase->CreateNewRecordset(strSql.c_str());
//	CHECKF(pRes);
//	if (pRes->RecordCount() > 0)
//	{
//		return pRes->GetInt(0);
//	}
//	return ID_NONE;
//}
//
//////////////////////////////////////////////////////////////////////////
//// Description: 获取玩家平台
//// Arguments:
//// Author: 陈建军(Chen Jianjun)
//// Return Value: const char*
//////////////////////////////////////////////////////////////////////////
//const char* CUserMgr::GetUserAccountPlatform(OBJID idUser) const
//{
//	DEBUG_TRY;
//	CHECKF(idUser);
//	auto pUser = this->GetUserByID(idUser);
//	CHECKF(pUser);
//	return pUser->GetAccountPlatform();
//	DEBUG_CATCHF2("CUserMgr::GetUserAccountPlatform idUser[%u]", idUser);
//}
//
//////////////////////////////////////////////////////////////////////////
//// Description: 获取玩家的绑定邀请码
//// Arguments:
//// Author: 陈建军(Chen Jianjun)
//// Return Value: const char*
//////////////////////////////////////////////////////////////////////////
//const char* CUserMgr::GetUserBindInviteCode(OBJID idUser) const
//{
//	DEBUG_TRY;
//	CHECKF(idUser);
//	auto pUser = this->GetUserByID(idUser);
//	CHECKF(pUser);
//	return pUser->GetAccountBindInviteCode();
//	DEBUG_CATCHF2("CUserMgr::GetUserBindInviteCode idUser[%u]", idUser);
//}
//
//////////////////////////////////////////////////////////////////////////
//// Description: 获取玩家等级
//// Arguments:
//// Author: 陈建军(Chen Jianjun)
//// Return Value: UINT
//////////////////////////////////////////////////////////////////////////
////UINT CUserMgr::GetUserLev(OBJID idUser, bool bLoadFromDB/*=false*/) const
////{
////	DEBUG_TRY;
////	CHECKF(idUser);
////	CHECKF(pGameDatabase);
////	auto pUser = this->GetUserByID(idUser);
////	if (pUser)
////	{
////		return pUser->GetData(USER_DATA_LEV);
////	}
////
////	auto iterUserOnline = m_mapUserOnline.find(idUser);
////	if (iterUserOnline != m_mapUserOnline.end())
////	{
////		return iterUserOnline->second.nLev;
////	}
////	else
////	{
////		if (bLoadFromDB)
////		{
////			CMxyString strSql;
////			strSql.Format("select lev from %s where id = %u limit 1", GAME_DB_NAME_USER, idUser);
////			RecordsetPtr pRes = pGameDatabase->CreateNewRecordset(strSql.c_str());
////			CHECKF(pRes && pRes->RecordCount() > 0);
////			return pRes->GetInt(0);
////		}
////	}
////	return 0;
////	DEBUG_CATCHF2("CUserMgr::GetUserLev idUser[%d]", idUser);
////}
////
////////////////////////////////////////////////////////////////////////////
////// Description: 获取角色名
////// Arguments:
////// Author: 丁乐(Ding Le)
////// Return Value: bool
////////////////////////////////////////////////////////////////////////////
////bool CUserMgr::GetUserName(OBJID idUser, OUT char* szUserName, bool bLoadFromDB/*=false*/) const
////{
////	DEBUG_TRY;
////	CHECKF(idUser && szUserName);
////	CHECKF(pGameDatabase);
////	auto pUser = this->GetUserByID(idUser);
////	if (pUser)
////	{
////		SafeCopy(szUserName, pUser->GetStr(USER_DATA_NAME), NAME_SIZE);
////		return true;
////	}
////
////	auto iterUserOnline = m_mapUserOnline.find(idUser);
////	if (iterUserOnline != m_mapUserOnline.end())
////	{
////		SafeCopy(szUserName, iterUserOnline->second.szUserName, NAME_SIZE);
////	}
////	else
////	{
////		if (bLoadFromDB)
////		{
////			CMxyString strSql;
////			strSql.Format("select name from %s where id = %u limit 1", GAME_DB_NAME_USER, idUser);
////			RecordsetPtr pRes = pGameDatabase->CreateNewRecordset(strSql.c_str());
////			CHECKF(pRes && pRes->RecordCount() > 0);
////			SafeCopy(szUserName, pRes->GetStr(0), NAME_SIZE);
////		}
////	}
////	return true;
////	DEBUG_CATCHF2("CUserMgr::GetUserName idUser[%d]", idUser);
////}
////
////////////////////////////////////////////////////////////////////////////
////// Description: 获取玩家头像
////// Arguments:
////// Author: 龚建伟(Gong Jianwei)
////// Return Value: UINT
////////////////////////////////////////////////////////////////////////////
////UINT CUserMgr::GetUserLookFace(OBJID idUser, bool bLoadFromDB/*=false*/) const
////{
////	DEBUG_TRY;
////	CHECKF(idUser);
////	CHECKF(pGameDatabase);
////	auto pUser = this->GetUserByID(idUser);
////	if (pUser)
////	{
////		return pUser->GetData(USER_DATA_LOOKFACE);
////	}
////
////	auto iterUserOnline = m_mapUserOnline.find(idUser);
////	if (iterUserOnline != m_mapUserOnline.end())
////	{
////		return iterUserOnline->second.nLookFace;
////	}
////	else
////	{
////		if (bLoadFromDB)
////		{
////			CMxyString strSql;
////			strSql.Format("select lookface from %s where id = %u limit 1", GAME_DB_NAME_USER, idUser);
////			RecordsetPtr pRes = pGameDatabase->CreateNewRecordset(strSql.c_str());
////			CHECKF(pRes && pRes->RecordCount() > 0);
////			return pRes->GetInt(0);
////		}
////	}
////	return 0;
////	DEBUG_CATCHF2("CUserMgr::GetUserLookFace idUser[%d]", idUser);
////}
////
////////////////////////////////////////////////////////////////////////////
////// Description: 获取玩家最大战斗力
////// Arguments:
////// Author: 龚建伟(Gong Jianwei)
////// Return Value: UINT
////////////////////////////////////////////////////////////////////////////
////UINT CUserMgr::GetUserMaxScore(OBJID idUser, bool bLoadFromDB/*=false*/) const
////{
////	DEBUG_TRY;
////	CHECKF(idUser);
////	CHECKF(pGameDatabase);
////	CUser* pUser = this->GetUserByID(idUser);
////	if (pUser)
////	{
////		return pUser->GetData(USER_DATA_MAX_SCORE);
////	}
////
////	auto iterUserOnline = m_mapUserOnline.find(idUser);
////	if (iterUserOnline != m_mapUserOnline.end())
////	{
////		return iterUserOnline->second.nMaxScore;
////	}
////	else if (bLoadFromDB)
////	{
////		CMxyString strSql;
////		strSql.Format("select max_score from %s where id = %u limit 1", GAME_DB_NAME_USER, idUser);
////		RecordsetPtr pRes = pGameDatabase->CreateNewRecordset(strSql.c_str());
////		CHECKF(pRes && pRes->RecordCount() > 0);
////		return pRes->GetInt(0);
////	}
////	return 0;
////	DEBUG_CATCHF2("CUserMgr::GetUserMaxScore idUser[%d]", idUser);
////}
////
////////////////////////////////////////////////////////////////////////////
////// Description: 设置战队最大战力评分
////// Arguments:	
////// Author: 陈建军(Chen Jianjun)
////// Return Value: void
////////////////////////////////////////////////////////////////////////////
////void CUserMgr::SetUserMaxScore(OBJID idUser, UINT unScore, bool bLoadFromDB/* = false*/)
////{
////	DEBUG_TRY;
////	CHECK(idUser);
////	CHECK(pGameDatabase);
////	CUser* pUser = this->GetUserByID(idUser);
////	if (pUser)
////	{
////		pUser->SetData(USER_DATA_MAX_SCORE, unScore);
////		// 更新在线信息
////		this->RequestUpdateUserOnlineInfo(idUser, true);
////	}
////	else if (bLoadFromDB)
////	{
////		CMxyString strSql;
////		strSql.Format("update %s set max_score = %u where id = %u", GAME_DB_NAME_USER, unScore, idUser);
////		pGameDatabase->ExecuteSQL(strSql.c_str());
////	}
////	DEBUG_CATCH3("CUserMgr::SetUserMaxScore idUser[%d], unScore[%u]", idUser, unScore);
////}
////
////////////////////////////////////////////////////////////////////////////
////// Description: 获取玩家卡牌总星级
////// Arguments:
////// Author: 陈建军(Chen Jianjun)
////// Return Value: UINT
////////////////////////////////////////////////////////////////////////////
////UINT CUserMgr::GetUserMaxPokerStar(OBJID idUser, bool bLoadFromDB /* = false*/) const
////{
////	DEBUG_TRY;
////	CHECKF(idUser);
////	CHECKF(pGameDatabase);
////	CUser* pUser = this->GetUserByID(idUser);
////	if (pUser)
////	{
////		return pUser->GetData(USER_DATA_MAX_POKER_STAR);
////	}
////	else
////	{
////		if (bLoadFromDB)
////		{
////			CMxyString strSql;
////			strSql.Format("select max_poker_star from %s where id = %u limit 1", GAME_DB_NAME_USER, idUser);
////			RecordsetPtr pRes = pGameDatabase->CreateNewRecordset(strSql.c_str());
////			CHECKF(pRes && pRes->RecordCount() > 0);
////			return pRes->GetInt(0);
////		}
////	}
////	return 0;
////	DEBUG_CATCHF2("CUserMgr::GetUserMaxPokerStar idUser[%d]", idUser);
////}
////
////////////////////////////////////////////////////////////////////////////
////// Description: 设置玩家卡牌总星级
////// Arguments:	
////// Author: 陈建军(Chen Jianjun)
////// Return Value: void
////////////////////////////////////////////////////////////////////////////
////void CUserMgr::AddUserMaxPokerStar(OBJID idUser, int nAddStar, bool bLoadFromDB/* = false*/)
////{
////	DEBUG_TRY;
////	CHECK(idUser);
////	CHECK(pGameDatabase);
////	CUser* pUser = this->GetUserByID(idUser);
////	if (pUser)
////	{
////		UINT unOldData = pUser->GetData(USER_DATA_MAX_POKER_STAR);
////		pUser->SetData(USER_DATA_MAX_POKER_STAR, unOldData + nAddStar);
////	}
////	else
////	{
////		if (bLoadFromDB)
////		{
////			CMxyString strSql;
////			strSql.Format("update %s set max_poker_star = max_poker_star + %d where id = %u", GAME_DB_NAME_USER, nAddStar, idUser);
////			pGameDatabase->ExecuteSQL(strSql.c_str());
////		}
////	}
////	DEBUG_CATCH3("CUserMgr::AddUserMaxPokerStar idUser[%d], nAddStar[%u]", idUser, nAddStar);
////}
////
////////////////////////////////////////////////////////////////////////////
////// Description: 增加玩家经验(自动升级)
////// Arguments:
////// Author: 彭文奇(Peng Wenqi)
////// Return Value: bool
////////////////////////////////////////////////////////////////////////////
////bool CUserMgr::AwardExp( OBJID idUser, int nExp )
////{
////	CHECKF(nExp > 0);
////	CUser* pUser = this->GetUserByID(idUser);
////	CHECKF(pUser);
////	CHECKF(pConstTableMgr->GetLevExp());
////
////	int nOldLev = pUser->GetData(USER_DATA_LEV);
////	I64 i64NowExp = pUser->GetData(USER_DATA_EXP) + nExp;
////	I64 i64MaxExp = pConstTableMgr->GetLevExp()->GetData(LEV_EXP_TYPE_USER, nOldLev, LEV_EXP_DATA_EXP);
////	int nMaxUserLev = pUserMgr->GetUserMaxLimitLev();
////
////	bool bUpLev = false;
////	int nCount = 0;
////	int nNowLev = nOldLev;
////	while (i64NowExp >= i64MaxExp && i64MaxExp > 0 && nNowLev < nMaxUserLev)
////	{
////		DEAD_LOOP_BREAK(nCount, 200);	// 一次最多升200级
////		
////		nNowLev++;
////		i64NowExp -= i64MaxExp;
////		i64MaxExp = pConstTableMgr->GetLevExp()->GetData(LEV_EXP_TYPE_USER, nNowLev, LEV_EXP_DATA_EXP);
////		bUpLev = true;
////	}
////
////	// 增加统计量
////	const int nTodayEpochDate = ::TimeGet(TIME_EPOCH_DAY);
////	const int nTodayYMD = ::TimeGet(YEAR_MONTH_DAY);
////	const int nTodayIndex = nTodayEpochDate % 3;
////	if (nTodayEpochDate == pUser->GetData((USER_DATA)(USER_DATA_EXP0_DATE_DAYS + nTodayIndex * 3)))
////	{
////		int nNowValue = pUser->GetData((USER_DATA)(USER_DATA_EXP0_VALUE + nTodayIndex * 3));
////		pUser->SetData((USER_DATA)(USER_DATA_EXP0_VALUE + nTodayIndex * 3), nNowValue + nExp);
////	}
////	else
////	{
////		pUser->SetData((USER_DATA)(USER_DATA_EXP0_DATE_DAYS + nTodayIndex * 3), nTodayEpochDate);
////		pUser->SetData((USER_DATA)(USER_DATA_EXP0_DATE_YMD + nTodayIndex * 3), nTodayYMD);
////		pUser->SetData((USER_DATA)(USER_DATA_EXP0_VALUE + nTodayIndex * 3), nExp);
////	}
////
////	pUser->SetData(USER_DATA_LEV, nNowLev);
////	pUser->SetData(USER_DATA_EXP, i64NowExp, true);
////
////	CMsgGameUserAttr msg;
////	msg.CreateBase();
////	msg.Append(USER_ATTR_TYPE_LEV, nNowLev);
////	msg.Append(USER_ATTR_TYPE_EXP, i64NowExp);
////	msg.Append(USER_ATTR_TYPE_POKER_MAX_LEV, pUserMgr->GetPokerMaxLimitLev(idUser));
////	this->SendMsg(idUser, &msg);
////
////	if (bUpLev)
////	{
////		// 更新在线信息
////		this->RequestUpdateUserOnlineInfo(idUser);
////		this->SyncUserLev(idUser, nNowLev);
////
////		pUserMoneyMgr->RequestAddPowerByUpLev(idUser, nOldLev, nNowLev);	// 增加体力
////		pSynGiftBoxMgr->ProcessCheckAddGiftBox(idUser, SGBT_SHENGJI_BOX);	// 检测礼盒
////		pAchievementMgr->UpdateAchievement(idUser, ACHIEVEMENT_UPDATE_TYPE_USER_LEV, nNowLev);		// 更新成就 
////	}
////
////	return true;
////}
////
////////////////////////////////////////////////////////////////////////////
////// Description：获取所有在线玩家id
////// Arguments: 
////// Author: 李飞(Li Fei) 
////// Date: 20141222
////// Return Value: 
////////////////////////////////////////////////////////////////////////////
////int CUserMgr::GetUserOnlineIDSet(OUT ID_VEC& vecID) 
////{
////	//MAP_USER_ONLINE::iterator it = m_mapUserOnline.begin();
////	//for (; m_mapUserOnline.end() != it; it++)
////	//{
////	//	vecID.push_back(it->first);
////	//}
////	return vecID.size();
////}
//
//////////////////////////////////////////////////////////////////////////
//// Description: 接收玩家ip
//// Arguments:	网络线程发回
//// Author: 彭文奇(Peng Wenqi)
//// Return Value: void
//////////////////////////////////////////////////////////////////////////
//void CUserMgr::RecvUserIP( OBJID idUser, SOCKET_ID idSocket, const char* pszIP )
//{
//	CHECK(idUser && idSocket != SOCKET_NONE && pszIP);
//	CUser* pUser = this->GetUserByID(idUser);
//	CHECK(pUser);
//	if (pUser->GetSocketID() == idSocket)
//	{
//		pUser->SetIP(pszIP);
//	}
//}
//
//////////////////////////////////////////////////////////////////////////
//// Description: 修改角色名
//// Arguments:	
//// Author: 丁乐(Ding Le)
//// Return Value: bool
//////////////////////////////////////////////////////////////////////////
//bool CUserMgr::SetUserName(OBJID idUser, const char* pszNewName)
//{
//	DEBUG_TRY;
//	CHECKF(idUser && pszNewName);
//	//CUser* pUser = this->GetUserByID(idUser);
//	//if (pUser)
//	//{
//	//	if (0 == strcmp(pUser->GetStr(USER_DATA_NAME), pszNewName))
//	//	{
//	//		return false;
//	//	}
//
//	//	char szOldName[NAME_SIZE] = "";
//	//	CHECKF(SafeCopy(szOldName, pUser->GetStr(USER_DATA_NAME), sizeof(szOldName)));
//	//	MAP_USER_NAME::const_iterator iter = m_mapUserName.find(pUser->GetStr(USER_DATA_NAME));
//	//	CHECKF(iter != m_mapUserName.end());
//	//	CHECKF(iter->second == idUser);
//	//	CHECKF(m_mapUserName.find(pszNewName) == m_mapUserName.end());
//	//	CHECKF(pUser->SetStr(USER_DATA_NAME, pszNewName, true));
//	//	m_mapUserName.erase(szOldName);
//	//	m_mapUserName[pszNewName] = idUser;
//
//	//	// 更新在线信息
//	//	this->RequestUpdateUserOnlineInfo(idUser, true);
//	//	this->SyncUserName(idUser, pszNewName);
//	//	return true;
//	//}
//	return false;
//	DEBUG_CATCHF2("CUserMgr::SetUserName UserID[%u]", idUser);
//}
//
//////////////////////////////////////////////////////////////////////////
//// Description: 修改LookFace
//// Arguments:	
//// Author: 丁乐(Ding Le)
//// Return Value: bool
//////////////////////////////////////////////////////////////////////////
//bool CUserMgr::SetLookFace(OBJID idUser, int nNewLookFace)
//{
//	DEBUG_TRY;
//	CHECKF(idUser && nNewLookFace > 0);
//	//CHECKF(pConstTableMgr->GetPokerType()->IsExist(nNewLookFace));
//	//CUser* pUser = this->GetUserByID(idUser);
//	//if (pUser)
//	//{
//	//	if (nNewLookFace == pUser->GetData(USER_DATA_LOOKFACE))
//	//	{
//	//		return false;
//	//	}
//	//	if (pUser->SetData(USER_DATA_LOOKFACE, nNewLookFace, true))
//	//	{
//	//		// 更新在线信息
//	//		this->RequestUpdateUserOnlineInfo(idUser);
//	//		this->SyncUserLookface(idUser, nNewLookFace);
//	//		return true;
//	//	} 
//	//}
//	return false;
//	DEBUG_CATCHF2("CUserMgr::SetUserLookFace UserID[%u]", idUser);
//}
//
//
//////////////////////////////////////////////////////////////////////////
//// Description：获取玩家个性签名
//// Arguments: 
//// Author: 李飞(Li Fei) 
//// Date: 20141229
//// Return Value: 
//////////////////////////////////////////////////////////////////////////
//CMxyString CUserMgr::GetSignature(OBJID idUser, bool bLoadFromDB /* = false */) const
//{
//	DEBUG_TRY;
//	CHECKF(ID_NONE != idUser);
//	CMxyString strSignature;
//	//auto pUser = this->GetUserByID(idUser);
//	//if (pUser)
//	//{
//	//	strSignature = pUser->GetStr(USER_DATA_SIGNATURE);
//	//}
//	//else
//	//{
//	//	const USER_ONLINE_INFO* pUserOnLine = this->GetUserOnlineInfo(idUser);
//	//	if (pUserOnLine)
//	//	{
//	//		strSignature = pUserOnLine->szSignature;
//	//	}
//	//	else if (bLoadFromDB)
//	//	{
//	//		CMxyString strSql;
//	//		strSql.Format("select signature from %s.%s where id=%u limit 1", g_strGameDatabaseName.c_str(), idUser);
//	//		RecordsetPtr pRes = pGameDatabase->CreateNewRecordset(strSql.c_str());
//	//		CHECKF(pRes && pRes->RecordCount() > 0);
//	//		strSignature = pRes->GetStr(0);
//	//	}
//	//}
//	return strSignature;
//	DEBUG_CATCHF2("CUserMgr::SetSignature user[%u] failed!", idUser);
//}
//
//////////////////////////////////////////////////////////////////////////
//// Description：设置玩家个性签名(只能设置在本线玩家的)
//// Arguments: 
//// Author: 李飞(Li Fei) 
//// Date: 20141229
//// Return Value: 
//////////////////////////////////////////////////////////////////////////
//bool CUserMgr::SetSignature(OBJID idUser, const char* pszSignature) 
//{
//	DEBUG_TRY;
//	CHECKF(ID_NONE != idUser);
//	CHECKF(pszSignature);
//	CHECKF(strlen(pszSignature) > 0);
//	CUser* pUser = this->GetUserByID(idUser);
//	CHECKF(pUser);
//	//if (pUser->SetStr(USER_DATA_SIGNATURE, pszSignature, true))
//	//{
//	//	// 更新在线信息
//	//	this->RequestUpdateUserOnlineInfo(idUser, true);
//	//	return true;
//	//}
//	return false;
//	DEBUG_CATCHF2("CUserMgr::SetSignature user[%u] failed!", idUser);
//}
//
//////////////////////////////////////////////////////////////////////////
//// Description: 获取玩家魅力值
//// Arguments:
//// Author: 陈建军(Chen Jianjun)
//// Return Value: UINT
//////////////////////////////////////////////////////////////////////////
//UINT CUserMgr::GetGlamour(OBJID idUser, bool bLoadFromDB/* = false*/) const
//{
//	DEBUG_TRY;
//	CHECKF(idUser);
//	CHECKF(pGameDatabase);
//	//CUser* pUser = this->GetUserByID(idUser);
//	//if (pUser)
//	//{
//	//	return pUser->GetData(USER_DATA_GLAMOUR);
//	//}
//	//else
//	//{
//	//	const USER_ONLINE_INFO* pUserOnLine = this->GetUserOnlineInfo(idUser);
//	//	if (pUserOnLine)
//	//	{
//	//		return pUserOnLine->nGlamour;
//	//	}
//	//	else if (bLoadFromDB)
//	//	{
//	//		CMxyString strSql;
//	//		strSql.Format("select glamour from %s where id = %u limit 1", GAME_DB_NAME_USER, idUser);
//	//		RecordsetPtr pRes = pGameDatabase->CreateNewRecordset(strSql.c_str());
//	//		CHECKF(pRes && pRes->RecordCount() > 0);
//	//		return pRes->GetInt(0);
//	//	}
//	//}
//	return 0;
//	DEBUG_CATCHF2("CUserMgr::GetGlamour idUser[%d]", idUser);
//}
//
//////////////////////////////////////////////////////////////////////////
//// Description: 获取玩家总魅力值
//// Arguments:
//// Author: 陈建军(Chen Jianjun)
//// Return Value: UINT
//////////////////////////////////////////////////////////////////////////
//UINT CUserMgr::GetGlamourTotal(OBJID idUser, bool bLoadFromDB/* = false*/) const
//{
//	DEBUG_TRY;
//	CHECKF(idUser);
//	CHECKF(pGameDatabase);
//	//CUser* pUser = this->GetUserByID(idUser);
//	//if (pUser)
//	//{
//	//	return pUser->GetData(USER_DATA_GLAMOUR_TOTAL);
//	//}
//	//else
//	//{
//	//	if (bLoadFromDB)
//	//	{
//	//		CMxyString strSql;
//	//		strSql.Format("select glamour_total from %s where id = %u limit 1", GAME_DB_NAME_USER, idUser);
//	//		RecordsetPtr pRes = pGameDatabase->CreateNewRecordset(strSql.c_str());
//	//		CHECKF(pRes && pRes->RecordCount() > 0);
//	//		return pRes->GetInt(0);
//	//	}
//	//}
//	return 0;
//	DEBUG_CATCHF2("CUserMgr::GetGlamourTotal idUser[%d]", idUser);
//}
//
//////////////////////////////////////////////////////////////////////////
//// Description: 增加玩家魅力值
//// Arguments:
//// Author: 陈建军(Chen Jianjun)
//// Return Value: bool
//////////////////////////////////////////////////////////////////////////
//bool CUserMgr::AddGlamour(OBJID idUser, int nAdd, bool bLoadFromDB/* = false*/)
//{
//	DEBUG_TRY;
//	CHECKF(idUser);
//	CHECKF(pGameDatabase);
//	//CUser* pUser = this->GetUserByID(idUser);
//	//if (pUser)
//	//{
//	//	auto nGlamour = pUser->GetData(USER_DATA_GLAMOUR);
//	//	auto nTotalGlamour = pUser->GetData(USER_DATA_GLAMOUR_TOTAL);
//	//	pUser->SetData(USER_DATA_GLAMOUR, nGlamour + nAdd);
//	//	pUser->SetData(USER_DATA_GLAMOUR_TOTAL, nTotalGlamour + nAdd);
//
//	//	// 更新在线信息
//	//	this->RequestUpdateUserOnlineInfo(idUser);
//	//}
//	//else if (bLoadFromDB)
//	//{
//	//	CMxyString strSql;
//	//	strSql.Format("update %s set glamour = glamour + %d, glamour_total = glamour_total + %d where id = %u", GAME_DB_NAME_USER, nAdd, nAdd, idUser);
//	//	pGameDatabase->ExecuteSQL(strSql.c_str());
//	//}
//	return true;
//	DEBUG_CATCHF3("CUserMgr::AddGlamour idUser[%d], nAdd[%u]", idUser, nAdd);
//}
//
//////////////////////////////////////////////////////////////////////////
//// Description: 设置玩家魅力值
//// Arguments:
//// Author: 陈建军(Chen Jianjun)
//// Return Value: bool
//////////////////////////////////////////////////////////////////////////
//bool CUserMgr::SetGlamour(OBJID idUser, int nGlamourNum, bool bLoadFromDB/* = false*/)
//{
//	DEBUG_TRY;
//	CHECKF(idUser);
//	CHECKF(pGameDatabase);
//	CUser* pUser = this->GetUserByID(idUser);
//	//if (pUser)
//	//{
//	//	pUser->SetData(USER_DATA_GLAMOUR, nGlamourNum);
//	//	// 更新在线信息
//	//	this->RequestUpdateUserOnlineInfo(idUser);
//	//}
//	//else if (bLoadFromDB)
//	//{
//	//	CMxyString strSql;
//	//	strSql.Format("update %s set glamour = %d where id = %u", GAME_DB_NAME_USER, nGlamourNum, idUser);
//	//	pGameDatabase->ExecuteSQL(strSql.c_str());
//	//}
//	return true;
//	DEBUG_CATCHF3("CUserMgr::SetGlamour idUser[%d], nGlamourNum[%u]", idUser, nGlamourNum);
//}
//
//////////////////////////////////////////////////////////////////////////
//// Description: 获取卡牌最大限制等级
//// Arguments:
//// Author: 陈建军(Chen Jianjun)
//// Return Value: int
//////////////////////////////////////////////////////////////////////////
//int	CUserMgr::GetPokerMaxLimitLev(OBJID idUser)
//{
//	DEBUG_TRY;
//	CHECKF(idUser);
//	//auto pConfigData = pConstTableMgr->GetConfigData();
//	//CHECKF(pConfigData);
//	//auto pUser = this->GetUserByID(idUser);
//	//CHECKF(pUser);
//
//	//// 策划说明： 初始为10  然后玩家等级20级以前每两级涨一点 
//	//int nMaxLimitPokerLev = 0;
//	//int nOpenLimitLev = 20;
//	//CHECKB(pConfigData->GetData(CONFIGTYPE_USER_POKER_CFG2, CONFIGDATA_DATA3, nOpenLimitLev));
//	//auto nUserLev = pUser->GetData(USER_DATA_LEV);
//	//if (nUserLev < nOpenLimitLev)
//	//{
//	//	int nInitLimitLev = 10;
//	//	CHECKB(pConfigData->GetData(CONFIGTYPE_USER_POKER_CFG2, CONFIGDATA_DATA2, nInitLimitLev));
//	//	nMaxLimitPokerLev = nInitLimitLev + (nUserLev - 1) / 2;
//	//}
//	//else
//	//{
//	//	nMaxLimitPokerLev = nUserLev;
//	//}
//
//	return max(nMaxLimitPokerLev, 1);
//	DEBUG_CATCHF2("CUserMgr::GetMaxLimitPokerLev idUser[%d]!", idUser);
//}
//
//////////////////////////////////////////////////////////////////////////
//// Description: 获取玩家最大限制等级
//// Arguments:
//// Author: 陈建军(Chen Jianjun)
//// Return Value: int
//////////////////////////////////////////////////////////////////////////
//int	CUserMgr::GetUserMaxLimitLev(OBJID idUser/*= ID_NONE*/)
//{
//	DEBUG_TRY;
//	//auto pConfigData = pConstTableMgr->GetConfigData();
//	//CHECKF(pConfigData);
//	int nUserMaxLimitLev = 100;
//	//CHECKB(pConfigData->GetData(CONFIGTYPE_USER_CFG, CONFIGDATA_DATA1, nUserMaxLimitLev));
//	//nUserMaxLimitLev = ::GetValueInRightRange(nUserMaxLimitLev, 1, MAX_USER_LEV);
//	return nUserMaxLimitLev;
//	DEBUG_CATCHF2("CUserMgr::GetUserMaxLimitLev idUser[%u]!", idUser);
//}
//
//////////////////////////////////////////////////////////////////////////
//// Description：从数据库获取玩家数据
//// Arguments: 
//// Author: 李飞(Li Fei) 
//// Date: 20141230
//// Return Value: 
//////////////////////////////////////////////////////////////////////////
//const RecordPtr CUserMgr::GetUserRecordByID(OBJID idUser) const 
//{
//	DEBUG_TRY;
//	CHECKF(ID_NONE != idUser);
//	CMxyString strSql;
//	strSql.Format("select * from %s.%s where id=%u limit 1", g_strGameDatabaseName.c_str(), GAME_DB_NAME_USER, idUser);
//	RecordsetPtr pRes = pGameDatabase->CreateNewRecordset(strSql.c_str());
//	CHECKF(pRes);
//	if (0 == pRes->RecordCount())
//	{
//		return NULL;
//	}
//	return pRes->CreateNewRecord();
//	DEBUG_CATCHF2("CUserMgr::GetUserRecordFromDB user[%u] failed!", idUser);
//}
//
//////////////////////////////////////////////////////////////////////////
//// Description：从数据库获取玩家数据
//// Arguments: 
//// Author: 李飞(Li Fei) 
//// Date: 20141230
//// Return Value: 
//////////////////////////////////////////////////////////////////////////
//const RecordPtr CUserMgr::GetUserRecordByName(const char* pszName) const 
//{
//	DEBUG_TRY;
//	CHECKF(pszName);
//	CMxyString strSql;
//	strSql.Format("select * from %s.%s where name='%s' limit 1", g_strGameDatabaseName.c_str(), GAME_DB_NAME_USER, pszName);
//	RecordsetPtr pRes = pGameDatabase->CreateNewRecordset(strSql.c_str());
//	CHECKF(pRes);
//	if (0 == pRes->RecordCount())
//	{
//		return NULL;
//	}
//	return pRes->CreateNewRecord();
//	DEBUG_CATCHF2("CUserMgr::GetUserRecordFromDB user[%s] failed!", pszName);
//}
//
//////////////////////////////////////////////////////////////////////////
//// Description: 获取玩家性别
//// Arguments:	
//// Author: 丁乐(Ding Le)
//// Return Value: int
//////////////////////////////////////////////////////////////////////////
////int	CUserMgr::GetSex(OBJID idUser, bool bLoadFromDB /*= false*/) const
////{
////	DEBUG_TRY;
////	CHECKF(idUser);
////	CHECKF(pGameDatabase);
////	CUser* pUser = this->GetUserByID(idUser);
////	if (pUser)
////	{
////		return pUser->GetData(USER_DATA_SEX);
////	}
////
////	auto iterUserOnline = m_mapUserOnline.find(idUser);
////	if (iterUserOnline != m_mapUserOnline.end())
////	{
////		return iterUserOnline->second.nSex;
////	}
////	else
////	{
////		if (bLoadFromDB)
////		{
////			CMxyString strSql;
////			strSql.Format("select sex from %s where id = %u limit 1", GAME_DB_NAME_USER, idUser);
////			RecordsetPtr pRes = pGameDatabase->CreateNewRecordset(strSql.c_str());
////			CHECKF(pRes && pRes->RecordCount() > 0);
////			return pRes->GetInt(0);
////		}
////	}
////	return 0;
////	DEBUG_CATCHF2("CUserMgr::GetSex idUser[%d]", idUser);
////}
//
//////////////////////////////////////////////////////////////////////////
//// Description: 修改玩家性别
//// Arguments:	
//// Author: 丁乐(Ding Le)
//// Return Value: bool
//////////////////////////////////////////////////////////////////////////
////bool CUserMgr::SetSex(OBJID idUser, SEX_TYPE eNewSex)
////{
////	DEBUG_TRY;
////	CHECKF(idUser);
////	//CHECKF(eNewSex >= SEX_TYPE_BEGIN && eNewSex <SEX_TYPE_END);
////	//CUser* pUser = this->GetUserByID(idUser);
////	//CHECKF(pUser);
////	//if (pUser->SetData(USER_DATA_SEX, eNewSex, true))
////	//{
////	//	// 更新在线信息
////	//	this->RequestUpdateUserOnlineInfo(idUser);
////	//	return true;
////	//}
////	return false;
////	DEBUG_CATCHF2("CUserMgr::SetSex UserID[%u]", idUser);
////}
//
//////////////////////////////////////////////////////////////////////////
//// Description: 获取玩家头像框
//// Arguments:	
//// Author: 丁乐(Ding Le)
//// Return Value: int
//////////////////////////////////////////////////////////////////////////
//int	CUserMgr::GetLookfaceFrame(OBJID idUser, bool bLoadFromDB /*= false*/) const
//{
//	DEBUG_TRY;
//	CHECKF(idUser);
//	CHECKF(pGameDatabase);
//	CUser* pUser = this->GetUserByID(idUser);
//	if (pUser)
//	{
//		return pUser->GetData(USER_DATA_LOOKFACE_FRAME);
//	}
//
//	//auto iterUserOnline = m_mapUserOnline.find(idUser);
//	//if (iterUserOnline != m_mapUserOnline.end())
//	//{
//	//	return iterUserOnline->second.nLookFaceFrame;
//	//}
//	//else
//	//{
//	//	if (bLoadFromDB)
//	//	{
//	//		CMxyString strSql;
//	//		strSql.Format("select lookface_frame from %s where id = %u limit 1", GAME_DB_NAME_USER, idUser);
//	//		RecordsetPtr pRes = pGameDatabase->CreateNewRecordset(strSql.c_str());
//	//		CHECKF(pRes && pRes->RecordCount() > 0);
//	//		return pRes->GetInt(0);
//	//	}
//	//}
//	return 0;
//	DEBUG_CATCHF2("CUserMgr::GetLookfaceFrame idUser[%d]", idUser);
//}
//
//////////////////////////////////////////////////////////////////////////
//// Description: 修改头像框
//// Arguments:	
//// Author: 丁乐(Ding Le)
//// Return Value: bool
//////////////////////////////////////////////////////////////////////////
//bool CUserMgr::SetLookfaceFrame(OBJID idUser, int nNewFrame)
//{
//	DEBUG_TRY;
//	CHECKF(idUser);
//	CUser* pUser = this->GetUserByID(idUser);
//	//if (pUser)
//	//{
//	//	CHECKF(nNewFrame != pUser->GetData(USER_DATA_LOOKFACE_FRAME));
//	//	if (pUser->SetData(USER_DATA_LOOKFACE_FRAME, nNewFrame, true))
//	//	{
//	//		// 更新在线信息
//	//		this->RequestUpdateUserOnlineInfo(idUser);
//	//		this->SyncUserLookfaceFrame(idUser, nNewFrame);
//	//		return true;
//	//	}
//	//}
//	return false;
//	DEBUG_CATCHF2("CUserMgr::SetLookfaceFrame UserID[%u]", idUser);
//}
//
//////////////////////////////////////////////////////////////////////////
//// Description: 获取玩家生日
//// Arguments:	
//// Author: 丁乐(Ding Le)
//// Return Value: int
//////////////////////////////////////////////////////////////////////////
//int CUserMgr::GetBirthday(OBJID idUser, bool bLoadFromDB /*= false*/) const
//{
//	DEBUG_TRY;
//	CHECKF(idUser);
//	CHECKF(pGameDatabase);
//	CUser* pUser = this->GetUserByID(idUser);
//	if (pUser)
//	{
//		return pUser->GetData(USER_DATA_BIRTHDAY);
//	}
//
//	//auto iterUserOnline = m_mapUserOnline.find(idUser);
//	//if (iterUserOnline != m_mapUserOnline.end())
//	//{
//	//	return iterUserOnline->second.nBirthday;
//	//}
//	//else
//	//{
//	//	if (bLoadFromDB)
//	//	{
//	//		CMxyString strSql;
//	//		strSql.Format("select birthday from %s where id = %u limit 1", GAME_DB_NAME_USER, idUser);
//	//		RecordsetPtr pRes = pGameDatabase->CreateNewRecordset(strSql.c_str());
//	//		CHECKF(pRes && pRes->RecordCount() > 0);
//	//		return pRes->GetInt(0);
//	//	}
//	//}
//	return 0;
//	DEBUG_CATCHF2("CUserMgr::GetBirthday idUser[%d]", idUser);
//}
//
//////////////////////////////////////////////////////////////////////////
//// Description: 修改生日
//// Arguments:	
//// Author: 丁乐(Ding Le)
//// Return Value: bool
//////////////////////////////////////////////////////////////////////////
//bool CUserMgr::SetBirthday(OBJID idUser, int nNewBirthDay)
//{
//	DEBUG_TRY;
//	CHECKF(idUser);
//	CUser* pUser = this->GetUserByID(idUser);
//	CHECKF(pUser);
//	//if (pUser->SetData(USER_DATA_BIRTHDAY, nNewBirthDay, true))
//	//{
//	//	// 更新在线信息
//	//	this->RequestUpdateUserOnlineInfo(idUser);
//	//	return true;
//	//}
//	return false;
//	DEBUG_CATCHF2("CUserMgr::SetBirthday UserID[%u]", idUser);
//}
//
//////////////////////////////////////////////////////////////////////////
//// Description: 获取玩家所在地
//// Arguments:	
//// Author: 丁乐(Ding Le)
//// Return Value: bool
//////////////////////////////////////////////////////////////////////////
//bool CUserMgr::GetAddress(OBJID idUser, OUT char* szAddress, bool bLoadFromDB /*= false*/) const
//{
//	DEBUG_TRY;
//	CHECKF(idUser);
//	CHECKF(pGameDatabase);
//	CUser* pUser = this->GetUserByID(idUser);
//	if (pUser)
//	{
//		SafeCopy(szAddress, pUser->GetStr(USER_DATA_ADDRESS), MAX_ADDRESS_SIZE);
//		return true;
//	}
//
//	//auto iterUserOnline = m_mapUserOnline.find(idUser);
//	//if (iterUserOnline != m_mapUserOnline.end())
//	//{
//	//	SafeCopy(szAddress, iterUserOnline->second.szAddress, MAX_ADDRESS_SIZE);
//	//	return true;
//	//}
//	//else
//	//{
//	//	if (bLoadFromDB)
//	//	{
//	//		CMxyString strSql;
//	//		strSql.Format("select address from %s where id = %u limit 1", GAME_DB_NAME_USER, idUser);
//	//		RecordsetPtr pRes = pGameDatabase->CreateNewRecordset(strSql.c_str());
//	//		CHECKF(pRes && pRes->RecordCount() > 0);
//	//		SafeCopy(szAddress, pRes->GetStr(0), MAX_ADDRESS_SIZE);
//	//		return true;
//	//	}
//	//}
//	return false;
//	DEBUG_CATCHF2("CUserMgr::GetAddress idUser[%d]", idUser);
//}
//
//////////////////////////////////////////////////////////////////////////
//// Description: 修改玩家所在地
//// Arguments:	
//// Author: 丁乐(Ding Le)
//// Return Value: bool
//////////////////////////////////////////////////////////////////////////
//bool CUserMgr::SetAddress(OBJID idUser, const char* szAddress)
//{
//	DEBUG_TRY;
//	CHECKF(idUser && szAddress);
//	//CUser* pUser = this->GetUserByID(idUser);
//	//CHECKF(pUser);
//	//if (pUser->SetStr(USER_DATA_ADDRESS, szAddress, true))
//	//{
//	//	// 更新在线信息
//	//	this->RequestUpdateUserOnlineInfo(idUser, true);
//	//	return true;
//	//}
//	//return false;
//	DEBUG_CATCHF2("CUserMgr::SetAddress UserID[%u]", idUser);
//}
//
//////////////////////////////////////////////////////////////////////////
//// Description: 获取玩家IP
//// Arguments:	
//// Author: 丁乐(Ding Le)
//// Return Value: const char*
//////////////////////////////////////////////////////////////////////////
//const char* CUserMgr::GetUserIP(OBJID idUser)
//{
//	DEBUG_TRY;
//	CHECKF(idUser);
//	CUser* pUser = this->GetUserByID(idUser);
//	CHECKF(pUser);
//	return pUser->GetIP();
//	DEBUG_CATCHF2("CUserMgr::GetUserIP UserID[%u]", idUser);
//}
//
//
////////////////////////////////////////////////////////////////////////////
////// Description: 获取玩家共享信息
////// Arguments:	
////// Author: 丁乐(Ding Le)
////// Return Value: bool
////////////////////////////////////////////////////////////////////////////
////bool CUserMgr::GetUserOnlineInfo(OBJID idUser, USER_ONLINE_INFO& userInfo, bool bLoadFromDB/* = false*/) const
////{
////	DEBUG_TRY;
////	CHECKF(idUser);
////	const USER_ONLINE_INFO* pUserOnlineInfo = this->GetUserOnlineInfo(idUser);
////	if (pUserOnlineInfo)
////	{
////		userInfo = *pUserOnlineInfo;
////		return true;
////	}
////	else if (bLoadFromDB)
////	{
////		CMxyString strSql;
////		strSql.Format("select * from %s where id = %u limit 1", GAME_DB_NAME_USER, idUser);
////		RecordsetPtr pRes = pGameDatabase->CreateNewRecordset(strSql.c_str());
////		CHECKF(pRes && pRes->RecordCount() > 0);
////
////		userInfo.idUser			 = idUser;
////		userInfo.idAccount		 = pRes->GetInt(USER_DATA_ID);
////		userInfo.nLine			 = g_nServerLine;
////		userInfo.nAccountType	 = pRes->GetInt(USER_DATA_ACCOUNT_TYPE);
////
////		userInfo.nLev			 = pRes->GetInt(USER_DATA_LEV);
////		userInfo.nMaxScore		 = pRes->GetInt(USER_DATA_MAX_SCORE);
////		userInfo.nLookFace		 = pRes->GetInt(USER_DATA_LOOKFACE);
////		userInfo.nSex			 = pRes->GetInt(USER_DATA_SEX);
////		userInfo.nLookFaceFrame  = pRes->GetInt(USER_DATA_LOOKFACE_FRAME);
////		userInfo.nBirthday		 = pRes->GetInt(USER_DATA_BIRTHDAY);
////
////		SafeCopy(userInfo.szUserName,  pRes->GetStr(USER_DATA_NAME),	  sizeof(userInfo.szUserName));
////		SafeCopy(userInfo.szSignature, pRes->GetStr(USER_DATA_SIGNATURE), sizeof(userInfo.szSignature));
////		SafeCopy(userInfo.szAddress,   pRes->GetStr(USER_DATA_ADDRESS),   sizeof(userInfo.szAddress));
////
////		userInfo.nLastLoginTime  = pRes->GetInt(USER_DATA_LAST_LOGIN);
////		userInfo.nYesterdayLogin = pRes->GetInt(USER_DATA_YESTERDAY_LOGIN);
////		return true;
////	}
////	return false;
////	DEBUG_CATCHF2("!!CUserMgr::GetUserOnLineInfo UserID[%u]", idUser);
////}
//
//////////////////////////////////////////////////////////////////////////
//// Description: 同步其他系统的玩家名
//// Arguments:	
//// Author: 丁乐(Ding Le)
//// Return Value: void
//////////////////////////////////////////////////////////////////////////
//void CUserMgr::SyncUserName(OBJID idUser, const char* pszNewName)
//{
//	CHECK(idUser && pszNewName);
//	//pSyndicateMgr->SyncUserName(idUser, pszNewName);
//	//pMineMgr->SyncUserName(idUser, pszNewName);
//}
//
//////////////////////////////////////////////////////////////////////////
//// Description: 同步其他系统的玩家名
//// Arguments:	
//// Author: 丁乐(Ding Le)
//// Return Value: void
//////////////////////////////////////////////////////////////////////////
//void CUserMgr::SyncUserLev(OBJID idUser,int nNewLev)
//{
//	CHECK(idUser && nNewLev > 0);
//	//pSyndicateMgr->SyncUserLev(idUser, nNewLev);
//	//pMineMgr->SyncUserLev(idUser, nNewLev);
//}
//
//////////////////////////////////////////////////////////////////////////
//// Description: 同步其他系统的玩家头像
//// Arguments:	
//// Author: 丁乐(Ding Le)
//// Return Value: void
//////////////////////////////////////////////////////////////////////////
//void CUserMgr::SyncUserLookface(OBJID idUser, int nNewLookface)
//{
//	CHECK(idUser && nNewLookface > 0);
//	//pSyndicateMgr->SyncUserLookface(idUser, nNewLookface);
//	//pMineMgr->SyncUserLookface(idUser, nNewLookface);
//}
//
//////////////////////////////////////////////////////////////////////////
//// Description: 同步其他系统的玩家头像框
//// Arguments:	
//// Author: 丁乐(Ding Le)
//// Return Value: void
//////////////////////////////////////////////////////////////////////////
//void CUserMgr::SyncUserLookfaceFrame(OBJID idUser, int nNewLookfaceFrame)
//{
//	CHECK(idUser && nNewLookfaceFrame > 0);
//	//pSyndicateMgr->SyncUserLookfaceFrame(idUser, nNewLookfaceFrame);
//	//pMineMgr->SyncUserLookfaceFrame(idUser, nNewLookfaceFrame);
//}