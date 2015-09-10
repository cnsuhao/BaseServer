////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan ChuangYou, All Rights Reserved
// Moudle: MsgGameUserAttr.h
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Created: 2014-11-10
////////////////////////////////////////////////////////////////////////
#ifndef _GAMEKERNER_MSG_GAME_USER_ATTR_H_
#define _GAMEKERNER_MSG_GAME_USER_ATTR_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "./NetMsg.h"


struct MSG_USER_ATTR_INFO
{
	int nType;
	I64	i64Data;
};

class CMsgGameUserAttr : public game_kernel::CNetMsg
{
public:
	CMsgGameUserAttr();
	virtual ~CMsgGameUserAttr();

	virtual BOOL Create(char* pMsgBuf, DWORD dwSize);
	virtual void Process(void *pInfo){};

public:
	void CreateBase();
	bool Append(int nType, I64 nData);

private:
	typedef struct  
	{
		MSG_NUM_4BIT		nCount;
		MSG_USER_ATTR_INFO	stInfo[1];
	}MSG_Info;

	MSG_Info* m_pInfo;
};


#endif // end of _GAMEKERNER_MSG_GAME_USER_ATTR_H_