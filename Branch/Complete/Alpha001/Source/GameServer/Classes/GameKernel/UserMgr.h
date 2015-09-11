///////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan ChuangYou, All Rights Reserved
// Moudle: UserMgr.h
// Author: 彭文奇(Peng Wenqi)
// Created: 2014-11-5
////////////////////////////////////////////////////////////////////////
#ifndef _GAMESERVER_GAME_USER_MGR_H_
#define _GAMESERVER_GAME_USER_MGR_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "define.h"

class CUser;
namespace game_kernel{ class CNetMsg; }
//typedef std::map<OBJID, USER_ONLINE_INFO>	MAP_USER_ONLINE;
class CUserMgr
{
	// 单例实现
public:
	static CUserMgr*	GetInstance	(void)	{ if (NULL == s_pInstance) s_pInstance = new CUserMgr; return s_pInstance; }
	static void			DelInstance	(void)	{ SAFE_DELETE(s_pInstance); }
	bool		Init				(void);
	void		Release				(void);
	MYHEAP_DECLARATION(s_heap);
private:
	CUserMgr(){};
	virtual ~CUserMgr() {}
	CUserMgr(const CUserMgr&){}
	static CUserMgr*	s_pInstance;

public:
	void		OnTimer				(void);
	void		OnTimerRollback		(void);
	
	bool		SendMsg				(OBJID idUser, game_kernel::CNetMsg* pMsg);

public:
	bool		LoginUser			(OBJID idUser, SOCKET_ID idSocket);
	bool		LoginUserOk			(OBJID idUser);
	bool		LogoutUser			(OBJID idUser);
	bool		KickUserByID		(OBJID idUser, KICK_REASON eReason = KICK_REASON_DEFAULT, int nParam = 0);
	bool		KickUserBySocket	(SOCKET_ID idSocket, KICK_REASON eReason = KICK_REASON_DEFAULT, int nParam = 0);
 	void		KickAllUser			(void);
//	void		RecvUserIP(OBJID idUser, SOCKET_ID idSocket, const char* pszIP);
// 	void		LogoutAllUser(); 该类Release已有相同功能, 暂时注释

private:
	bool		InitUser			(CUser* pUser, OBJID idUser, SOCKET_ID idSocket);
	bool		ReleaseUser			(CUser* pUser);

public:
	CUser*		GetUserByID			(OBJID idUser) const;
	CUser*		GetUserBySocket		(SOCKET_ID idSocket) const;
	CUser*		GetUserByName		(const char* pszUserName) const;
	CUser*		GetUserByMsg		(game_kernel::CNetMsg* pMsg) const;
	OBJID		GetUserIDByMsg		(game_kernel::CNetMsg* pMsg) const;
	OBJID		GetUserIDByName		(const char* pszUserName) const;
	//OBJID		GetUserIDFromDB		(const char* pszUserName) const;
//
//	bool		IsUser(OBJID idUser)	{ return idUser >= PLAYER_ID_FIRST; }
//	//bool		IsArenaAI(OBJID idUser) { return (idUser <= g_nServerGroup * ARENA_AI_COUNT); }	// 机器人的id最大不会超过1000w
//	bool		IsGM(OBJID idUser);
//	bool		IsYesterdayLogin(OBJID idUser, bool bForce = false);
//
//	int			GetCreateTime(OBJID idUser);
//	int			GetCreateDay(OBJID idUser);
//	const char* GetUserAccountPlatform(OBJID idUser) const;
//	const char* GetUserBindInviteCode(OBJID idUser) const;
//	UINT		GetUserLev(OBJID idUser, bool bLoadFromDB = false) const;
//	bool		GetUserName(OBJID idUser, OUT char* szUserName, bool bLoadFromDB = false) const;
//	UINT		GetUserLookFace(OBJID idUser, bool bLoadFromDB = false) const;
//	UINT		GetUserMaxScore(OBJID idUser, bool bLoadFromDB = false) const;
//	void		SetUserMaxScore(OBJID idUser, UINT unScore, bool bLoadFromDB = false);
//	UINT		GetUserMaxPokerStar(OBJID idUser, bool bLoadFromDB = false) const;
//	void		AddUserMaxPokerStar(OBJID idUser, int nAddStar, bool bLoadFromDB = false);
//	bool		SetUserName(OBJID idUser, const char* pszNewName);
//	bool		SetLookFace(OBJID idUser, int nNewLookFace);
//	CMxyString	GetSignature(OBJID idUser, bool bLoadFromDB = false) const ;
//	bool		SetSignature(OBJID idUser, const char* pszSignature);
//	UINT		GetGlamour(OBJID idUser, bool bLoadFromDB = false) const;
//	UINT		GetGlamourTotal(OBJID idUser, bool bLoadFromDB = false) const;
//	bool		AddGlamour(OBJID idUser, int nAdd, bool bLoadFromDB = false);
//	bool		SetGlamour(OBJID idUser, int nGlamourNum, bool bLoadFromDB = false);
//	int			GetPokerMaxLimitLev(OBJID idUser);
//	int			GetUserMaxLimitLev(OBJID idUser = ID_NONE);
//
//
//	//bool					IsOnline(OBJID idUser, bool bThisLine = true) const;
//	//int						GetThisLineOnlineCount(void) const {return m_mapUser.size();}
//	//const USER_ONLINE_INFO*	GetUserOnlineInfo(OBJID idUser) const;
//	//const USER_ONLINE_INFO* GetUserOnlineInfo(const char* pszName) const;
//	//void					AddUserOnlineInfo(const USER_ONLINE_INFO* pInfo);
//	//void					DelUserOnlineInfo(OBJID idUser);
//	//void					RequestUpdateUserOnlineInfo(OBJID idUser, bool bForce = false);
//	//void					ProcessUpdateUserOnlineInfo(const USER_ONLINE_INFO* pInfo);
//	//int						GetUserOnlineCount(){ return m_mapUserOnline.size();}
//	//int						GetUserOnlineIDSet(OUT ID_VEC& vecID);
//	bool					AwardExp(OBJID idUser, int nExp);
//	const RecordPtr			GetUserRecordByID(OBJID idUser) const;
//	const RecordPtr			GetUserRecordByName(const char* pszName) const;
//
//	//int			GetSex(OBJID idUser, bool bLoadFromDB = false) const;
//	//bool		SetSex(OBJID idUser, SEX_TYPE eNewSex);
//	int			GetLookfaceFrame(OBJID idUser, bool bLoadFromDB = false) const;
//	bool		SetLookfaceFrame(OBJID idUser, int nNewFrame);
//	int			GetBirthday(OBJID idUser, bool bLoadFromDB = false) const;
//	bool		SetBirthday(OBJID idUser, int nNewBirthDay);
//	bool		GetAddress(OBJID idUser, OUT char* szAddress, bool bLoadFromDB = false) const;
//	bool		SetAddress(OBJID idUser, const char* szAddress);
//	const char* GetUserIP(OBJID idUser);
//
//	//bool		GetUserOnlineInfo(OBJID idUser, USER_ONLINE_INFO& userInfo, bool bLoadFromDB = false) const;
//
//private:
//	void		SyncUserName(OBJID idUser, const char* pszNewName);
//	void		SyncUserLev(OBJID idUser,int nNewLev);
//	void		SyncUserLookface(OBJID idUser, int nNewLookface);
//	void		SyncUserLookfaceFrame(OBJID idUser, int nNewLookfaceFrame);
//
private:
	INT_MAP							m_mapSocket;	// SocketID为fisrt, idUser为second
	std::map<CMxyString, OBJID>		m_mapUserName;	// strName为first, idUser为second
	std::map<OBJID, CUser*>			m_mapUser;		// idUser为fisrt, CUser*为second
//	//MAP_USER_ONLINE	m_mapUserOnline;

};
#define pUserMgr CUserMgr::GetInstance()

#endif // end of _GAMESERVER_GAME_USER_MGR_H_