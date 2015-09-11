////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan ChuangYou, All Rights Reserved
// Moudle: User.h
// Author: 彭文奇(Peng Wenqi)
// Created: 2014-11-5
////////////////////////////////////////////////////////////////////////
#ifndef _GAMESERVER_GAME_USER_H_
#define _GAMESERVER_GAME_USER_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "define.h"

class CUser : public IGameObject
{
	// 内存构建方式
public:
	static CUser*	CreateNew		(void)	{ return new CUser; }
	bool			Init			(OBJID idUser, SOCKET_ID idSocket);
	void			Release			(void)	{ delete this; }
	void			BeforeRelease	(void);
	MYHEAP_DECLARATION(s_heap);
protected:
	CUser();
	virtual ~CUser();

	// 心跳管理
public:
	virtual void	OnTimer			(void);
	virtual void	OnTimerRollback	(void);
protected:
			void	OnTimerSecond	(void);	
			void	OnTimerMinute	(void);		

public:
	//virtual bool		IsGM() const {return this->GetMemoryDataAttr(mdaUser_AccountType) == ACCOUNT_TYPE_GM_LOW || this->GetMemoryDataAttr(mdaUser_AccountType) == ACCOUNT_TYPE_GM_HI;}
	//virtual bool		IsGmHiAccount() const {return this->GetMemoryDataAttr(mdaUser_AccountType) == ACCOUNT_TYPE_GM_HI;}

	// 数据库数据存取
public:
	virtual I64				GetData(USER_DATA eData) const;
	virtual const char*		GetStr (USER_DATA eData) const;
	virtual bool			SetData(USER_DATA eData, I64 i64Data, bool bUpdate = false);
	virtual bool			SetStr (USER_DATA eData, const char* pszStr, bool bUpdate = false);
protected:
	IRecord*	m_pRecord;

	// 账号表读取字符串
public:
	const char* GetAccountName() const				{ return m_strAccountName.c_str(); }
	const char* GetAccountPlatform() const			{ return m_strAccountPlatform.c_str(); }
	const char* GetAccountChannel() const			{ return m_strAccountChannel.c_str(); }
	const char* GetAccountOS() const				{ return m_strAccountOS.c_str(); }
protected:
	CMxyString m_strAccountName;
	CMxyString m_strAccountPlatform;
	CMxyString m_strAccountChannel;
	CMxyString m_strAccountOS;

	// 消息发送
public:
	SOCKET_ID	GetSocketID()const {return m_idSocket;}
	const char* GetIP() const {return m_strIP.c_str();}
	void		SetIP(const char* pszIP);
	const char*	GetMac() const {return m_strMac.c_str();}
	bool		SetMac(const char* pszMac);
	
protected:
	SOCKET_ID	m_idSocket;
	CMxyString  m_strIP;
	CMxyString	m_strMac;

	// mda数据存取
public:
	DEFINE_mda(MEMORY_DATA_ATTR_USER);
};

#endif // end of _GAMESERVER_GAME_USER_H_