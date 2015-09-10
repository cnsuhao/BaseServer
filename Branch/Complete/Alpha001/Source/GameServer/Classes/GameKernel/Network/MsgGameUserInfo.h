////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan ChuangYou, All Rights Reserved
// Moudle: MsgGameUserInfo.h
// Author: ������(Peng Wenqi)
// Created: 2014-11-10
////////////////////////////////////////////////////////////////////////
#ifndef _GAMEKERNER_MSG_GAME_USER_INFO_H_
#define _GAMEKERNER_MSG_GAME_USER_INFO_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "./NetMsg.h"

class CUser;
class CMsgGameUserInfo : public game_kernel::CNetMsg
{
public:
	CMsgGameUserInfo();
	virtual ~CMsgGameUserInfo();

	virtual BOOL Create(char* pMsgBuf, DWORD dwSize);
	virtual void Process(void *pInfo){};

public:
	bool CreateUserInfo(CUser* pUser);


private:
	typedef struct  
	{
		MSG_NUM_4BIT	idUser;			// ��ɫid
		MSG_NUM_4BIT	idAccountID;	// �˺�id
		MSG_NUM_4BIT	nAccountType;	// �˺�����
		MSG_NUM_4BIT	nLastLoginTime; // ���һ�ε�¼ʱ��
		MSG_NUM_4BIT	nCreateTime;	// ����ʱ�� utc��
		MSG_NUM_4BIT	nLastExitTime;	// �ϴεǳ�ʱ��

		MSG_NUM_4BIT	nServerGroup;	// ���������
		MSG_NUM_4BIT	nServerLine;	// ��������·��

		MSG_NUM_4BIT	nLev;			// �ȼ�
		MSG_NUM_4BIT	nExp;			// ����
		MSG_STR_32BIT	szUserName;		// ����
		MSG_NUM_4BIT	nCampType;		// ��Ӫ����
		MSG_NUM_4BIT	nFlagShip;		// �콢����

		MSG_NUM_4BIT	fRotation;		// ����Ƕ�
		MSG_NUM_4BIT	fSpeedForm;		// ǰ���ٶ�
		MSG_NUM_4BIT	fSpeedRotation;	// ת���ٶ�
		MSG_NUM_4BIT	fViewRange;		// ���Ӿ���뾶

		MSG_NUM_4BIT	nScore;			// ս����
		MSG_NUM_4BIT	nGalaxy;		// ������ϵ
		MSG_NUM_4BIT	nRest;			// ���ڵص㣨NPC��
		MSG_NUM_4BIT	curPointx;		// ��ǰ����x
		MSG_NUM_4BIT	curPointy;		// ��ǰ����y
		MSG_NUM_4BIT	aimPointx;		// Ŀ������x
		MSG_NUM_4BIT	aimPointy;		// Ŀ������y
	}MSG_Info;

	MSG_Info* m_pInfo;
};


#endif // end of _GAMEKERNER_MSG_GAME_USER_INFO_H_