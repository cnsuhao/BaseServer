////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan ChuangYou, All Rights Reserved
// Moudle: UserTalkData.h
// Author: 龚建伟(Gong Jianwei)
// Created: 2014-11-6
////////////////////////////////////////////////////////////////////////
#ifndef _GAMESERVER_GAME_USER_TALK_DATA_H_
#define _GAMESERVER_GAME_USER_TALK_DATA_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "./../share/define.h"

typedef std::map<int, UINT>		MAP_USER_TALK_DATA;
class CUserTalkData
{
	// 内存构建方式
public:
	static CUserTalkData*	CreateNew()	{return new CUserTalkData;}
	bool					Init();
	void					Release()	{delete this;}
	MYHEAP_DECLARATION(s_heap);

protected:
	CUserTalkData();
	virtual ~CUserTalkData();

	// 逻辑接口
public:
	bool	IsExit(int nTxtAtr) const;
	bool	Add(int nTxtAtr, UINT unSec/*=0*/);
	bool	Del(int nTxtAtr);
	bool	SetData(int nTxtAtr, UINT unSec/*=0*/);
	DWORD	GetData(int nTxtAtr) const;

protected:
	MAP_USER_TALK_DATA		m_mapUserTalkData;
};
#endif