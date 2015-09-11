////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan ChuangYou, All Rights Reserved
// Moudle: MaskMgr.h
// Author: �½���(Chen jIanjun)
// Created: 2014-11-6
////////////////////////////////////////////////////////////////////////
#ifndef _GAMESERVER_GAME_MASK_MGR_H_
#define _GAMESERVER_GAME_MASK_MGR_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "./../share/define.h"

class CUserMask;
typedef std::map<OBJID, CUserMask*>		MAP_USER_MASK;

class CMaskMgr
{
public:		// ����ʵ��
	static CMaskMgr*			GetInstance(void)	{if (NULL == s_pInstance) s_pInstance = new CMaskMgr; return s_pInstance;}
	static void					DelInstance(void)	{SAFE_DELETE(s_pInstance);}
	bool	Init				(void);
	void	Release				(void);
	MYHEAP_DECLARATION(s_heap);
private:
	CMaskMgr() : m_pUserMaskDefaultRes(NULL){}
	virtual ~CMaskMgr() {}
	CMaskMgr(const CMaskMgr&){}
	static CMaskMgr*	s_pInstance;

	//----------------------------- ������������������ -------------------
public:		// �ⲿ�����ӿ�(���ݿ����)
	UINT	GetGroupServerMask			(OBJID idGroup, OBJID idMask);
	bool	SetGroupServerMask			(OBJID idGroup, OBJID idMask, UINT unData, UINT unEndTime);
	void	ClearInvalidGroupServerMask	(void);
		

	UINT	GetWorldServerMask			(OBJID idMask);
	bool	SetWorldServerMask			(OBJID idMask, UINT unData, UINT unEndTime);
	void	ClearInvalidWorldServerMask	(void);

	//----------------------------- �������������� -----------------------------
public:		// ��ɫ�������ͷ�
	bool	InitUser			(OBJID idUser);
	bool	ReleaseUser			(OBJID idUser);

public:		// ���ݲ����ⲿ�ӿ�
	I64		GetUserMaskData		(OBJID idUser, EUSERMASKTYPE unMaskType, OBJID idMask);
	bool	SetUserMaskData		(OBJID idUser, EUSERMASKTYPE unMaskType, OBJID idMask, I64 i64Data, UINT unEndTime);
	bool	ChkUserMaskData		(OBJID idUser, EUSERMASKTYPE unMaskType, OBJID idMask, int nIdx);
	bool	AddUserMaskData		(OBJID idUser, EUSERMASKTYPE unMaskType, OBJID idMask, int nIdx, UINT unEndTime);
	bool	ClrUserMaskData		(OBJID idUser, EUSERMASKTYPE unMaskType, OBJID idMask, int nIdx);

	bool	ResetUserMaskData	(OBJID idUser, EUSERMASKTYPE unMaskType, OBJID idMask);
	bool	DelUserMaskData		(OBJID idUser, EUSERMASKTYPE unMaskType, OBJID idMask);

	void	SynOneMaskDataInfo	(OBJID idUser, EUSERMASKTYPE unMaskType, OBJID idMask);
	void	SynAllUserMaskData	(OBJID idUser);

	int		GetMaskDataBitCount	(OBJID idUser, EUSERMASKTYPE unMaskType, OBJID idMask, int nEndIndex = 64);

private:
	CUserMask*	GetUserMask		(OBJID idUser) const;

private:
	MAP_USER_MASK		m_mapUserMask;				// �����������
	IRecordset*			m_pUserMaskDefaultRes;
};

#define pMaskMgr CMaskMgr::GetInstance()

#endif // end of _GAMESERVER_GAME_MASK_MGR_H_