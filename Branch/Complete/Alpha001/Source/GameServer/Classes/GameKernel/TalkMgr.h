////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan ChuangYou, All Rights Reserved
// Moudle: TalkMgr.h
// Author: 龚建伟(Gong Jianwei)
// Created: 2014-11-11
////////////////////////////////////////////////////////////////////////
#ifndef _GAMESERVER_GAME_Talk_Mgr_H_
#define _GAMESERVER_GAME_Talk_Mgr_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "./../share/define.h"

class CUserTalkData;
typedef std::map<OBJID, CUserTalkData*>		MAP_TALK_DATA;

class CTalkMgr
{
	// 单例实现
public:
	static CTalkMgr*	GetInstance(void)	{if (NULL == s_pInstance) s_pInstance = new CTalkMgr; return s_pInstance;}
	static void			DelInstance(void)	{SAFE_DELETE(s_pInstance);}
	bool   Init();
	void   Release();
	MYHEAP_DECLARATION(s_heap);

private:
	CTalkMgr(){m_bGmCmdNeedMac = true;}
	virtual ~CTalkMgr() {}
	CTalkMgr(const CTalkMgr&){}
	static CTalkMgr*	s_pInstance;

public:
	bool	InitUser				(OBJID idUser);
	bool    ReleaseUser				(OBJID idUser);

public:
	void	RequestQueryWorldTalk(OBJID idUser);
	void	RequestQuerySynTalk(OBJID idUser);
	void	RequestQueryPrivateTalk(OBJID idUser);
	void	RequestQueryUserInfo(OBJID idUser, OBJID idTargeter);
	void	RequestWorldTalk(ST_TALK_USER_INFO& stSenderinfo, int nSendTime, char* pszData, int nDataSize, int nTxtType, int nParam1, int nParam2, int nParam3, int nParam4);
	void	RequestSynTalk(ST_TALK_USER_INFO& stSenderinfo, int nSendTime, OBJID idSyn, char* pszData, int nDataSize, int nTxtType, int nParam1, int nParam2, int nParam3, int nParam4);
	void	RequestPrivateTalk(ST_TALK_USER_INFO& stSenderinfo, int nSendTime, OBJID idReceiverID, const char* pszReceiverName, char* pszData, int nDataSize, int nTxtType, int nParam1, int nParam2, int nParam3, int nParam4);
	void	RequestNotify(const char* pszData, const char* pszReceiverName = NULL, OBJID idSyn = 0);
	void	RequestHint(const char* pszData, const char* pszReceiverName = NULL, OBJID idSyn = 0);
	void	RequestGmCmd(OBJID idUser, char* pszData);
	void	RequestGmOperation(OBJID idUser, const char* pszData);

	// 逻辑接口
public:
	bool	GetGmCmdNeedMacFlag		(void) const {return m_bGmCmdNeedMac;}
	void	SetGmCmdNeedMacFlag		(bool bFlag){m_bGmCmdNeedMac = bFlag;}
	bool	UpdateUserTalkTime		(OBJID idUser, int nTxtAtr);

protected:
	void	ProcessGmCmd			(OBJID idUser, const char* pszData);
	int		GetTalkTimeLimit		(int nTxtAtr) const;
	bool	IsStopTalk				(OBJID idUser) const;
	bool	SetStopTalk				(OBJID idUser, int nKeepSecond);
	bool	DelWorldHistory			();
	bool	DelSynHistory			(OBJID idSyn);
	bool	DelPrivateHistory		(OBJID idReceiver);
	bool	GetLastHistory			(OBJID idReceiver, OUT MAP_TABLE_DATA& mapData);

private:
	CUserTalkData*	GetUserTalkData(OBJID idUser) const;

private:
	MAP_TALK_DATA	m_mapTalkData;
	bool			m_bGmCmdNeedMac;
};

#define pTalkMgr CTalkMgr::GetInstance()

#endif