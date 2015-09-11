////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan ChuangYou, All Rights Reserved
// Moudle: UserTmpDataMgr.h
// Author: ¶¡ÀÖ(Ding Le)
// Created: 2014-11-7
////////////////////////////////////////////////////////////////////////
#ifndef _GAMESERVER_GAME_USER_TMP_DATA_MGR_H_
#define _GAMESERVER_GAME_USER_TMP_DATA_MGR_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "./../share/define.h"

enum USERTMPDATA_INDEX
{
	USERTMPDATA_INDEX_BEG = 0,
	USERTMPDATA_INDEX0 = USERTMPDATA_INDEX_BEG,
	USERTMPDATA_INDEX1,
	USERTMPDATA_INDEX2,
	USERTMPDATA_INDEX3,
	USERTMPDATA_INDEX4,
	USERTMPDATA_INDEX5,
	USERTMPDATA_INDEX6,
	USERTMPDATA_INDEX7,
	USERTMPDATA_INDEX_END,
};


class CUserTmpData;

typedef std::map<OBJID, CUserTmpData*>					MAP_USER_TMP_DATA;
typedef std::map<OBJID, CUserTmpData*>::iterator		ITER_MAP_USER_TMP_DATA;
typedef std::map<OBJID, CUserTmpData*>::const_iterator	CITER_MAP_USER_TMP_DATA;


class CUserTmpDataMgr
{
	// µ¥ÀýÊµÏÖ
public:
	static CUserTmpDataMgr* GetInstance(void)	{ if (NULL == s_pInstance) s_pInstance = new CUserTmpDataMgr; return s_pInstance;}
	static void DelInstance(void)				{ SAFE_DELETE(s_pInstance); }
	bool Init();
	void Release();
	MYHEAP_DECLARATION(s_heap);

private:
	CUserTmpDataMgr() {m_pDefaultres = NULL;}
	virtual ~CUserTmpDataMgr() {}
	CUserTmpDataMgr(CUserTmpDataMgr& ){}
	static CUserTmpDataMgr* s_pInstance;

public:
	bool InitUser(OBJID idUser);
	bool ReleaseUser(OBJID idUser);

public:
	bool	SetTmpData			(OBJID idUser, OBJID idTmpData, USERTMPDATA_INDEX eIndex, int nData, int nUpdateType = DBUPDATE_ASYNC);
	int		GetTmpData			(OBJID idUser, OBJID idTmpData, USERTMPDATA_INDEX eIndex) const;
	bool	DelTmpData			(OBJID idUser, OBJID idTmpData);
	void	SaveAllUserTmpData	(void);
	bool	SaveUserAllTmpData	(OBJID idUser);
	bool	SaveUserTmpData		(OBJID idUser, OBJID idTmpData);
	bool	SetTmpDataMask		(OBJID idUser, OBJID idTmpData, USERTMPDATA_INDEX eIndex, int nMaskIndex, int nUpdateType = DBUPDATE_ASYNC);
	bool	ClrTmpDataMask		(OBJID idUser, OBJID idTmpData, USERTMPDATA_INDEX eIndex, int nMaskIndex, int nUpdateType = DBUPDATE_ASYNC);
	bool	ChkTmpDataMask		(OBJID idUser, OBJID idTmpData, USERTMPDATA_INDEX eIndex, int nMaskIndex) const;
	bool	IsUserTmpDataExist	(OBJID idUser, OBJID idTmpData) const;
	void	Reset				(OBJID idUser, OBJID idTmpData, int nUpdateType);

private:
	CUserTmpData*		GetUserTmpData	(OBJID idUser)	const;
	USERTMPDATA_DATA	GetIndex		(UCHAR ucIndex)	const;

public:
	void UpdateUserTmpData(OBJID idUser, OBJID idTmpData);
	void ProcessQueryClientTmpData(OBJID idUser);

private:
	MAP_USER_TMP_DATA		m_mapUserTmpData;
	IRecordset*				m_pDefaultres;
};

#define pUserTmpDataMgr CUserTmpDataMgr::GetInstance()

#endif // end of _GAMESERVER_GAME_USER_TMP_DATA_MGR_H_