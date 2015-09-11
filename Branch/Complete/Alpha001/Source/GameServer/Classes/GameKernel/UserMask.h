////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan ChuangYou, All Rights Reserved
// Moudle: UserMask.h
// Author: 陈建军(Chen Jianjun)
// Created: 2014-11-6
////////////////////////////////////////////////////////////////////////
#ifndef _GAMEKERNEL_USERMASK_H_
#define _GAMEKERNEL_USERMASK_H_

#if _MSC_VER > 1000
#pragma once
#endif
#include "define.h"

typedef std::map<OBJID, RecordPtr>			MAP_MASKDATA;
typedef std::map<int, MAP_MASKDATA>			MAP_USERMASKDATA;

class CUserMask
{
	// 内存构建方式
public:
	static CUserMask*	CreateNew()	{return new CUserMask;}
	bool				Init(OBJID idUser, IRecordset* pDefaultRes);
	void				Release()		{delete this;}
	MYHEAP_DECLARATION(s_heap);
protected:
	CUserMask() : m_idUser(ID_NONE), m_pDefaultRes(NULL) {}
	virtual ~CUserMask();
	CUserMask(const CUserMask&){}

public:		// 逻辑接口
	bool	IsExist			(EUSERMASKTYPE unMaskType, OBJID idMask);
	bool	Add				(EUSERMASKTYPE unMaskType, OBJID idMask);
	bool	Reset			(EUSERMASKTYPE unMaskType, OBJID idMask, bool bUpdate = true, int nType = DBUPDATE_ASYNC);
	bool	Del				(EUSERMASKTYPE unMaskType, OBJID idMask);

	I64		GetData			(EUSERMASKTYPE unMaskType, OBJID idMask);
	bool	SetData			(EUSERMASKTYPE unMaskType, OBJID idMask, UINT unEndTime, I64 i64Data, bool bUpdate = true, int nType = DBUPDATE_ASYNC);

	UINT	GetMaskClearTime(EUSERMASKTYPE unMaskType, OBJID idMask);
	void	SynAllMaskData	(void);

protected:	// 内部操作函数
	RecordPtr GetMaskRecord	(EUSERMASKTYPE unMaskType, OBJID idMask);
	bool	SaveAll			(void);

protected:
	OBJID				m_idUser;
	IRecordset*			m_pDefaultRes;
	MAP_USERMASKDATA	m_mapUserMaskData;
};

#endif // #ifndef _GAMEKERNEL_USERMASK_H_