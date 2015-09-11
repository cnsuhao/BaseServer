////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan ChuangYou, All Rights Reserved
// Moudle: MsgGameMask.h
// Author: �½���(Chen Jianjun)
// Created: 2014-11-6
////////////////////////////////////////////////////////////////////////
#ifndef _GAMEKERNEL_MSG_GAME_MASK_H_
#define _GAMEKERNEL_MSG_GAME_MASK_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "./NetMsg.h"

typedef struct
{
	MSG_NUM_4BIT	unMaskType;		// ��������
	MSG_NUM_4BIT	idMask;			// ����ID
	MSG_NUM_4BIT	unEndTime;		// ����ʱ��
	MSG_NUM_8BIT	i64MaskData;	// ��������
}USERMMASKSTRUCT;

class CMsgGameMask : public game_kernel::CNetMsg  
{
public:
	CMsgGameMask();
	virtual ~CMsgGameMask();

	virtual BOOL Create			(char* pMsgBuf, DWORD dwSize);
	virtual void Process		(void *pInfo);

public:
	virtual bool CreateMsg		(MSG_NUM_4BIT idUser, MSG_NUM_4BIT unMaskType, MSG_NUM_4BIT idMask, MSG_NUM_4BIT unEndTime, MSG_NUM_8BIT i64MaskData);
			bool AppendMsg		(USERMMASKSTRUCT& stInfo);

private:
	typedef struct
	{
		MSG_NUM_4BIT	idUser;			// ���ID

		MSG_NUM_4BIT	nNum;
		USERMMASKSTRUCT	setUserMask[1];	// ������Ϣ(�䳤)
	}MSG_Info;

	MSG_Info* m_pInfo;
};

#endif