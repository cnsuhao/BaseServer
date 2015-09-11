////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan ChuangYou, All Rights Reserved
// Moudle: UserTmpData.h
// Author: 丁乐(Ding Le)
// Created: 2014-11-7
////////////////////////////////////////////////////////////////////////
#ifndef _GAMESERVER_GAME_USER_TMP_DATA_H_
#define _GAMESERVER_GAME_USER_TMP_DATA_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "./../share/define.h"

const INT MAX_LOAD_USER_TMP_DATA_COUNT	= 300;	// UserTmpData最多加载条数

class CUserTmpData
{
	// 内存构建方式
public:
	static CUserTmpData*	CreateNew()	{return new CUserTmpData;}
	bool					Init(OBJID idUser, IRecordset* pDefaultRes);
	void					Release()	{delete this;}
	MYHEAP_DECLARATION(s_heap);

protected:
	CUserTmpData();
	virtual ~CUserTmpData();

	// 逻辑接口
public:
	bool	SetData	(OBJID idTmpData, USERTMPDATA_DATA eIndex, int nData, DBUPDATE_TYPE eUpdateType);
	int		GetData	(OBJID idTmpData, USERTMPDATA_DATA eIndex) const;
	bool	SaveAll	(void);
	bool	Save	(OBJID idTmpData);
	bool	IsExist	(OBJID idTmpData) const;
	void	Reset	(OBJID idTmpData, DBUPDATE_TYPE eUpdateType);
	bool	Add		(OBJID idTmpData);
	bool	Del		(OBJID idTmpData);

protected:
	MAP_TABLE_DATA	m_mapTmpData;
	OBJID			m_idUser;
	IRecordset*		m_pDefaultRes;
};
#endif // _GAMESERVER_GAME_USER_TMP_DATA_H_