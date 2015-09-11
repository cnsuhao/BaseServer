////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan ChuangYou, All Rights Reserved
// Moudle: UserMailMgr.h
// Author: ����(Ding Le)
// Created: 2014-11-17
////////////////////////////////////////////////////////////////////////
#ifndef _GAME_KERNER_USER_MAIL_MGR_H_
#define _GAME_KERNER_USER_MAIL_MGR_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "./../share/define.h"

// �ʼ�����������
enum EMAIL_SENDER_TYPE
{
	EMAIL_SENDER_Beg	= 0,
	EMAIL_SENDER_System = EMAIL_SENDER_Beg,			// ϵͳ
	EMAIL_SENDER_End,
};

// �ʼ�����
enum EMAIL_TITLE_TYPE
{
	EMAIL_TITLE_Beg	= 0,
	EMAIL_TITLE_System = EMAIL_TITLE_Beg,			// ϵͳ
	EMAIL_TITLE_Arena_Update_Record		= 1,		// �����������Ƽ�¼
	EMAIL_TITLE_End,
};

// �ʼ�����
enum EMAIL_CONTENT_TYPE
{
	EMAIL_CONTENT_Beg					= 0,
	EMAIL_CONTENT_System				= EMAIL_CONTENT_Beg,		// ϵͳ
	EMAIL_CONTENT_End,
};

const int CONST_MAIL_SEND_ITEM_NUM			= 4;	// �ʼ�������Ʒ�������

class CUserMailMgr
{
	// ����ʵ��
public:
	static CUserMailMgr* GetInstance(void)	{ if (NULL == s_pInstance) s_pInstance = new CUserMailMgr; return s_pInstance;}
	static void DelInstance(void)			{ SAFE_DELETE(s_pInstance); }
	bool Init();
	void Release();
	MYHEAP_DECLARATION(s_heap);

private:
	CUserMailMgr(){ }
	virtual ~CUserMailMgr() {}
	CUserMailMgr(CUserMailMgr&) {}
	static CUserMailMgr* s_pInstance;

private:
	bool QueryMail(I64 i64MailID, OUT MSG_MAIL_DATA& mail);
	bool SetMailStatus(I64 i64MailID, EMAIL_STATUS eMailStatus);
	void NewMailNotify(OBJID idReceiver, MSG_MAIL_LIST& mail);
	bool GetMailTitleByType(EMAIL_TITLE_TYPE eTitleType, OUT char* pszTitle, int nSize);
	bool GetMailContentByType(EMAIL_CONTENT_TYPE eContentType, OUT char* pszContent, int nSize);
	bool GetMailSenderByType(EMAIL_SENDER_TYPE eSenderType, OUT char* pszSenderName, int nSize);


// ��Ϣ����
public:
	int QueryMailList(OBJID idUser, int nPage, int nPageSize, OUT VEC_MAIL_LIST& vecMail);
	int ProcessOpenMail(OBJID idUser, I64 i64MailID, OUT MSG_MAIL_DATA& mail);
	int ProcessGetItem(OBJID idUser, I64 i64MailID, OUT MSG_MAIL_DATA& mail);
	bool GetUnreadMailCount(OBJID idUser, OUT int& nUnreadCount);
	void ProcessUnreadMailCount(OBJID idUser);

public:
	bool SendMail(OBJID idReceiver, EMAIL_TITLE_TYPE eTitleType, EMAIL_CONTENT_TYPE eContentType, EMAIL_SENDER_TYPE eSenderType, IN const VEC_MAIL_AWARD& vecAward, int nExp = 0);
	bool SendMail(OBJID idReceiver, EMAIL_TITLE_TYPE eTitleType, const char* szContent, EMAIL_SENDER_TYPE eSenderType, IN const VEC_MAIL_AWARD& vecAward, int nExp = 0);
	bool SendMail(OBJID idReceiver, const char* szTitle, const char* szContent, const char* szSender, IN const VEC_MAIL_AWARD& vecAward, int nExp = 0);

	// �ű��ӿ�
public:
	bool SendMail(OBJID idReceiver, const char* szTitle, const char* szContent, const char* szSender, const char* szCmd);
};

#define pUserMailMgr CUserMailMgr::GetInstance()

#endif // _GAME_KERNER_USER_MAIL_MGR_H_