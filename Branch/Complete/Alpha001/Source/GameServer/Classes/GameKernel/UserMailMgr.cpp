////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan ChuangYou, All Rights Reserved
// Moudle: UserMailMgr.cpp
// Author: 丁乐(Ding Le)
// Created: 2014-11-17
////////////////////////////////////////////////////////////////////////
#include "./UserMailMgr.h"
#include "./GameKernel.h"
#include "./UserMgr.h"
#include "./Network/MsgGameUserMail.h"
#include "./Network/MsgGameUserMailList.h"

CUserMailMgr* CUserMailMgr::s_pInstance = NULL;
MYHEAP_IMPLEMENTATION(CUserMailMgr, s_heap);

////////////////////////////////////////////////////////////////////////
// 初始化
bool CUserMailMgr::Init()
{
	CHECKF(pGameDatabase);
	return true;
}

////////////////////////////////////////////////////////////////////////
// 释放
void CUserMailMgr::Release()
{
}

////////////////////////////////////////////////////////////////////////
// 查询邮件信息
bool CUserMailMgr::QueryMail(I64 i64MailID, OUT MSG_MAIL_DATA& mail)
{
	CHECKF(pGameDatabase);
	CHECKF(i64MailID > 0);

	CMxyString strSql;
	strSql.Format("select * from %s where id = %I64d", GAME_DB_NAME_USER_MAIL, i64MailID);
	RecordsetPtr pRes = pGameDatabase->CreateNewRecordset(strSql.c_str());
	CHECKF(pRes);
	CHECKF(pRes->RecordCount() == 1);

	mail.i64MailID		= pRes->GetInt(EUSER_MAIL_ID);			// 邮件ID
	const char* pszMailContent = pRes->GetStr(EUSER_MAIL_CONTENT);
	CHECKF(pszMailContent);
	::SafeCopy(mail.szContent, pszMailContent, sizeof(mail.szContent)); // 内容
	mail.nOverTime		= pRes->GetInt(EUSER_MAIL_OVER_TIME);	// 存在时间
	mail.nStatus		= pRes->GetInt(EUSER_MAIL_STATUS);		// 邮件状态

	// 邮件状态不能为删除，不能过期
	unsigned int unCurTime = ::TimeGet(TIME_SECOND);
	CHECKF_NOLOG(mail.nStatus != EMAIL_STATUS_Del && mail.nOverTime > unCurTime);

	mail.nItemType1		= pRes->GetInt(EUSER_MAIL_ITEM_TYPE1);	// 物品1
	mail.nItemNum1		= pRes->GetInt(EUSER_MAIL_ITEM_NUM1);	// 物品1数量
	mail.nItemType2		= pRes->GetInt(EUSER_MAIL_ITEM_TYPE2);	// 物品2
	mail.nItemNum2		= pRes->GetInt(EUSER_MAIL_ITEM_NUM2);	// 物品2数量
	mail.nItemType3		= pRes->GetInt(EUSER_MAIL_ITEM_TYPE3);	// 物品3
	mail.nItemNum3		= pRes->GetInt(EUSER_MAIL_ITEM_NUM3);	// 物品3数量
	mail.nItemType4		= pRes->GetInt(EUSER_MAIL_ITEM_TYPE4);	// 物品4
	mail.nItemNum4		= pRes->GetInt(EUSER_MAIL_ITEM_NUM4);	// 物品4数量
	mail.nItemType5		= pRes->GetInt(EUSER_MAIL_ITEM_TYPE5);	
	mail.nItemNum5		= pRes->GetInt(EUSER_MAIL_ITEM_NUM5);	
	mail.nItemType6		= pRes->GetInt(EUSER_MAIL_ITEM_TYPE6);	
	mail.nItemNum6		= pRes->GetInt(EUSER_MAIL_ITEM_NUM6);	

	mail.nMoneyType1	= pRes->GetInt(EUSER_MAIL_MONEY_TYPE1);	// 货币1
	mail.nMoneyNum1		= pRes->GetInt(EUSER_MAIL_MONEY_NUM1);	// 货币1数量
	mail.nMoneyType2	= pRes->GetInt(EUSER_MAIL_MONEY_TYPE2);	// 货币2
	mail.nMoneyNum2		= pRes->GetInt(EUSER_MAIL_MONEY_NUM2);	// 货币2数量
	mail.nMoneyType3	= pRes->GetInt(EUSER_MAIL_MONEY_TYPE3);	// 货币3
	mail.nMoneyNum3		= pRes->GetInt(EUSER_MAIL_MONEY_NUM3);	// 货币3数量
	mail.nMoneyType4	= pRes->GetInt(EUSER_MAIL_MONEY_TYPE4);	// 货币4
	mail.nMoneyNum4		= pRes->GetInt(EUSER_MAIL_MONEY_NUM4);	// 货币4数量
	mail.nExp			= pRes->GetInt(EUSER_MAIL_EXP);			// 经验

	return true;
}

////////////////////////////////////////////////////////////////////////
// 设置邮件状态
bool CUserMailMgr::SetMailStatus(I64 i64MailID, EMAIL_STATUS eMailStatus)
{
	CHECKF(pGameDatabase);
	CHECKF(i64MailID > 0);
	CHECKF(eMailStatus >= EMAIL_STATUS_Begin && eMailStatus < EMAIL_STATUS_End);

	CMxyString strSql;
	strSql.Format("update %s set status = %d where id = %I64d", GAME_DB_NAME_USER_MAIL, eMailStatus, i64MailID);
	return pGameDatabase->ExecuteSQL(strSql.c_str(), DBUPDATE_ASYNC);
}

////////////////////////////////////////////////////////////////////////
// 查询邮件列表
int CUserMailMgr::QueryMailList(OBJID idUser, int nPage, int nPageSize, OUT VEC_MAIL_LIST& vecMail)
{
	if (!pGameDatabase || idUser <= ID_NONE || nPage <= 0 || nPageSize <= 0)
	{
		return EMSG_MAIL_LIST_RESULT_Error;
	}
	vecMail.clear();

	unsigned int unCurTime = ::TimeGet(TIME_SECOND);
	CMxyString strSql;
	strSql.Format("select * from %s where user_id = %u and status != %d and over_time > %d order by id limit %d, %d",
			GAME_DB_NAME_USER_MAIL, idUser, EMAIL_STATUS_Del, unCurTime, (nPage - 1) * nPageSize, nPageSize);
	RecordsetPtr pRes = pGameDatabase->CreateNewRecordset(strSql.c_str());
	if (!pRes)
	{
		return EMSG_MAIL_LIST_RESULT_Succ;
	}

	for (int i = 0; i < pRes->RecordCount(); i++, pRes->MoveNext())
	{
		CHECKC(pRes);
		MSG_MAIL_LIST mailList = {0};
		mailList.i64MailID = pRes->GetInt64(EUSER_MAIL_ID);				// 邮件ID

		// 标题
		const char* pszTitle = pRes->GetStr(EUSER_MAIL_TITLE);
		CHECKC(pszTitle);
		::SafeCopy(mailList.szTitle, pszTitle, sizeof(mailList.szTitle));
		
		// 发件人
		const char* pszSender = pRes->GetStr(EUSER_MAIL_SENDER);
		CHECKC(pszSender);
		::SafeCopy(mailList.szSender, pszSender, sizeof(mailList.szSender));

		mailList.nSendTime = pRes->GetInt(EUSER_MAIL_SEND_TIME);		// 发送时间
		mailList.nStatus = pRes->GetInt(EUSER_MAIL_STATUS);				// 邮件状态

		vecMail.push_back(mailList);
	}

	return EMSG_MAIL_LIST_RESULT_Succ;
}

////////////////////////////////////////////////////////////////////////
// 打开邮件
int CUserMailMgr::ProcessOpenMail(OBJID idUser, I64 i64MailID, OUT MSG_MAIL_DATA& mail)
{
	if (idUser <= 0 || i64MailID <= 0)
	{
		return EMSG_MAIL_RESULT_Error;
	}

	// 获取邮件信息
	if (!this->QueryMail(i64MailID, mail))
	{
		return EMSG_MAIL_RESULT_Error;
	}

	// 第一次打开邮件，改变邮件状态
	if (EMAIL_STATUS_UNREAD == mail.nStatus)	
	{
		if (!this->SetMailStatus(i64MailID, EMAIL_STATUS_READ))
		{
			return EMSG_MAIL_RESULT_Error;
		}
		mail.nStatus = EMAIL_STATUS_READ;

		// 更新邮件推送提示信息
		//pMarksInfoMgr->UpdateUserMarksInfo(idUser, MSG_MARKS_TYPE_MAIL, MARKSDATA_CONTROL_DEC, 1);
	}
	return EMSG_MAIL_RESULT_Succ;
}

////////////////////////////////////////////////////////////////////////
// 获取邮件中的物品(获取后自动删除邮件)
int CUserMailMgr::ProcessGetItem(OBJID idUser, I64 i64MailID, OUT MSG_MAIL_DATA& mail)
{
	if (!pGameDatabase || idUser <= 0 || i64MailID <= 0)
	{
		return EMSG_MAIL_RESULT_Error;
	}

	if (!this->QueryMail(i64MailID, mail))
	{
		return EMSG_MAIL_RESULT_Error;
	}

	// 检查是否有奖励
	CHECKF1(    (mail.nItemType1 > 0 && mail.nItemNum1 > 0) 
		     || (mail.nItemType2 > 0 && mail.nItemNum2 > 0) 
		     || (mail.nItemType3 > 0 && mail.nItemNum3 > 0)
		     || (mail.nItemType4 > 0 && mail.nItemNum4 > 0)
			 || (mail.nItemType5 > 0 && mail.nItemNum5 > 0)
			 || (mail.nItemType6 > 0 && mail.nItemNum6 > 0)
			 || (mail.nMoneyType1 > 0 && mail.nMoneyNum1 > 0) 
			 || (mail.nMoneyType2 > 0 && mail.nMoneyNum2 > 0) 
			 || (mail.nMoneyType3 > 0 && mail.nMoneyNum3 > 0) 
			 || (mail.nMoneyType4 > 0 && mail.nMoneyNum4 > 0) 
		     ||  mail.nExp > 0);

	// 邮件状态为打开才能获取物品
	CHECKF(EMAIL_STATUS_READ == mail.nStatus);
	if (!this->SetMailStatus(i64MailID, EMAIL_STATUS_Del))
	{
		return EMSG_MAIL_RESULT_Error;
	}
	mail.nStatus = EMAIL_STATUS_Del;

	// 给物品
	//if (mail.nItemType1 > 0 && mail.nItemNum1 > 0 
	//	&& !pItemMgr->AwardItem(idUser, mail.nItemType1, mail.nItemNum1, ITEM_FLOW_REASON_MAIL_AWARD))
	//{
	//	tolog4("GetMailItem Error idUser[%u], ItemType1[%d], ItemNum1[%d]", idUser, mail.nItemType1, mail.nItemNum1);
	//}
	//if (mail.nItemType2 > 0 && mail.nItemNum2 > 0 
	//	&& !pItemMgr->AwardItem(idUser, mail.nItemType2, mail.nItemNum2, ITEM_FLOW_REASON_MAIL_AWARD))
	//{
	//	tolog4("GetMailItem Error idUser[%u], ItemType2[%d], ItemNum2[%d]", idUser, mail.nItemType2, mail.nItemNum2);
	//}
	//if (mail.nItemType3 > 0 && mail.nItemNum3 > 0 
	//	&& !pItemMgr->AwardItem(idUser, mail.nItemType3, mail.nItemNum3, ITEM_FLOW_REASON_MAIL_AWARD))
	//{
	//	tolog4("GetMailItem Error idUser[%u], ItemType3[%d], ItemNum3[%d]", idUser, mail.nItemType3, mail.nItemNum3);
	//}
	//if (mail.nItemType4 > 0 && mail.nItemNum4 > 0 
	//	&& !pItemMgr->AwardItem(idUser, mail.nItemType4, mail.nItemNum4, ITEM_FLOW_REASON_MAIL_AWARD))
	//{
	//	tolog4("GetMailItem Error idUser[%u], ItemType4[%d], ItemNum4[%d]", idUser, mail.nItemType4, mail.nItemNum4);
	//}
	//if (mail.nItemType5 > 0 && mail.nItemNum5 > 0 
	//	&& !pItemMgr->AwardItem(idUser, mail.nItemType5, mail.nItemNum5, ITEM_FLOW_REASON_MAIL_AWARD))
	//{
	//	tolog4("GetMailItem Error idUser[%u], ItemType5[%d], ItemNum5[%d]", idUser, mail.nItemType5, mail.nItemNum5);
	//}
	//if (mail.nItemType6 > 0 && mail.nItemNum6 > 0 
	//	&& !pItemMgr->AwardItem(idUser, mail.nItemType6, mail.nItemNum6, ITEM_FLOW_REASON_MAIL_AWARD))
	//{
	//	tolog4("GetMailItem Error idUser[%u], ItemType6[%d], ItemNum6[%d]", idUser, mail.nItemType6, mail.nItemNum6);
	//}

	//// 给金钱
	//if (mail.nMoneyType1 > 0 && mail.nMoneyNum1 > 0
	//	&& !pUserMoneyMgr->Award(idUser, (USER_MONEY_TYPE)mail.nMoneyType1, mail.nMoneyNum1, MONEY_FLOW_REASON_MAIL))
	//{
	//	tolog4("GetMailMoney Error idUser[%u], MoneyType1[%d], MoneyNum1[%d]", idUser, mail.nMoneyType1, mail.nMoneyNum1);
	//}
	//if (mail.nMoneyType2 > 0 && mail.nMoneyNum2 > 0 
	//	&& !pUserMoneyMgr->Award(idUser, (USER_MONEY_TYPE)mail.nMoneyType2, mail.nMoneyNum2, MONEY_FLOW_REASON_MAIL))
	//{
	//	tolog4("GetMailMoney Error idUser[%u], MoneyType2[%d], MoneyNum2[%d]", idUser, mail.nMoneyType2, mail.nMoneyNum2);
	//}
	//if (mail.nMoneyType3 > 0 && mail.nMoneyNum3 > 0 
	//	&& !pUserMoneyMgr->Award(idUser, (USER_MONEY_TYPE)mail.nMoneyType3, mail.nMoneyNum3, MONEY_FLOW_REASON_MAIL))
	//{
	//	tolog4("GetMailMoney Error idUser[%u], MoneyType3[%d], MoneyNum3[%d]", idUser, mail.nMoneyType3, mail.nMoneyNum3);
	//}
	//if (mail.nMoneyType4 > 0 && mail.nMoneyNum4 > 0
	//	&& !pUserMoneyMgr->Award(idUser, (USER_MONEY_TYPE)mail.nMoneyType4, mail.nMoneyNum4, MONEY_FLOW_REASON_MAIL))
	//{
	//	tolog4("GetMailMoney Error idUser[%u], MoneyType4[%d], MoneyNum4[%d]", idUser, mail.nMoneyType4, mail.nMoneyNum4);
	//}

	//// 给经验
	//if (mail.nExp > 0 && !pUserMgr->AwardExp(idUser, mail.nExp))
	//{
	//	tolog3("GetMailExp Error idUser[%u], Exp[%d]", idUser, mail.nExp);
	//}

	// 删除邮件
	CMxyString strSql;
	strSql.Format("delete from %s where id = %I64d", GAME_DB_NAME_USER_MAIL, i64MailID);
	if (!pGameDatabase->ExecuteSQL(strSql.c_str(), DBUPDATE_ASYNC))
	{
		return EMSG_MAIL_RESULT_Error;
	}

	return EMSG_MAIL_RESULT_Succ;
}

////////////////////////////////////////////////////////////////////////
// 查询未读邮件数量
bool CUserMailMgr::GetUnreadMailCount(OBJID idUser, OUT int& nUnreadCount)
{
	CHECKF(pGameDatabase);
	CHECKF(idUser);

	nUnreadCount = 0;
	unsigned int unCurTime = ::TimeGet(TIME_SECOND);
	CMxyString strSql;
	strSql.Format("select count(*) as count from %s where user_id = %u and status = %d and over_time > %u",
		GAME_DB_NAME_USER_MAIL, idUser, EMAIL_STATUS_UNREAD, unCurTime);
	RecordsetPtr pRes = pGameDatabase->CreateNewRecordset(strSql.c_str());
	if (pRes)
	{
		nUnreadCount = pRes->GetInt("count");
	}
	return true;
}

///////////////////////////////////////////////////////////////////////
// 处理查询未读邮件个数
void CUserMailMgr::ProcessUnreadMailCount(OBJID idUser)
{
	CHECK(idUser);
	int nUnreadCount = 0;	// 未读邮件数量
	int nResult = EMSG_MAIL_RESULT_Succ;
	if (!this->GetUnreadMailCount(idUser, nUnreadCount))
	{
		nResult = EMSG_MAIL_RESULT_Error;
	}
	CMsgGameUserMail msg;
	msg.CreateMsg(EMSG_MAIL_ACT_AckUnreadMailCount, nResult, 0i64, nUnreadCount);
	pUserMgr->SendMsg(idUser, &msg);
}

///////////////////////////////////////////////////////////////////////
// 发邮件(邮件标题，内容，发送者名字从config_text配置表获得)
bool CUserMailMgr::SendMail(OBJID idReceiver, EMAIL_TITLE_TYPE eTitleType, EMAIL_CONTENT_TYPE eContentType, EMAIL_SENDER_TYPE eSenderType, IN const VEC_MAIL_AWARD& vecAward, int nExp /*= 0*/)
{
	CHECKF(idReceiver);
	CHECKF(eTitleType >= EMAIL_TITLE_Beg && eTitleType < EMAIL_TITLE_End);
	CHECKF(eContentType >= EMAIL_CONTENT_Beg && eContentType < EMAIL_CONTENT_End);
	CHECKF(eSenderType >= EMAIL_SENDER_Beg && EMAIL_SENDER_End);
	CHECKF(vecAward.size() <= (MAX_MAIL_ITEM_COUNT + MAX_MAIL_MONEY_COUNT));
	char szTitle[MAX_MAIL_TITLE] = "";
	char szContent[MAX_MAIL_TEXT] = "";
	char szSenderName[NAME_SIZE] = "";
	CHECKF(this->GetMailTitleByType(eTitleType, szTitle, MAX_MAIL_TITLE));
	CHECKF(this->GetMailContentByType(eContentType, szContent, MAX_MAIL_TEXT));
	CHECKF(this->GetMailSenderByType(eSenderType, szSenderName, NAME_SIZE));

	return this->SendMail(idReceiver, szTitle, szContent, szSenderName, vecAward, nExp);
}

///////////////////////////////////////////////////////////////////////
// 发邮件(邮件内容需自己拼接)
bool CUserMailMgr::SendMail(OBJID idReceiver, EMAIL_TITLE_TYPE eTitleType, const char* szContent, EMAIL_SENDER_TYPE eSenderType, IN const VEC_MAIL_AWARD& vecAward, int nExp /*= 0*/)
{
	CHECKF(idReceiver);
	CHECKF(eTitleType >= EMAIL_TITLE_Beg && eTitleType < EMAIL_TITLE_End);
	CHECKF(eSenderType >= EMAIL_SENDER_Beg && EMAIL_SENDER_End);
	CHECKF(szContent);
	CHECKF(vecAward.size() <= (MAX_MAIL_ITEM_COUNT + MAX_MAIL_MONEY_COUNT));
	char szTitle[MAX_MAIL_TITLE] = "";
	char szSenderName[NAME_SIZE] = "";

	CHECKF(this->GetMailTitleByType(eTitleType, szTitle, MAX_MAIL_TITLE));
	CHECKF(this->GetMailSenderByType(eSenderType, szSenderName, NAME_SIZE));

	return this->SendMail(idReceiver, szTitle, szContent, szSenderName, vecAward, nExp);
}

///////////////////////////////////////////////////////////////////////
// 发邮件
bool CUserMailMgr::SendMail(OBJID idReceiver, const char* szTitle, const char* szContent, const char* szSender, IN const VEC_MAIL_AWARD& vecAward, int nExp /*= 0*/)
{
	CHECKF(idReceiver);
	CHECKF(szTitle && szContent && szSender);
	CHECKF(vecAward.size() <= (MAX_MAIL_ITEM_COUNT + MAX_MAIL_MONEY_COUNT));

	// 提取邮件中的物品和货币
	char szCmd[MAX_MAIL_TEXT] = "";
	MAIL_AWARD_DATA item[MAX_MAIL_ITEM_COUNT]		= {0};
	MAIL_AWARD_DATA money[MAX_MAIL_MONEY_COUNT]		= {0};
	int nItemCount = 0;
	int nMoneyCount = 0;
	for (int i = 0; i < vecAward.size(); i++)
	{
		//// 是货币
		//if (vecAward[i].nAwardType >= DROP_RULE_GROUP_TYPE_MONEY_BEGIN 
		//	&& vecAward[i].nAwardType <= DROP_RULE_GROUP_TYPE_MONEY_END
		//	&& nMoneyCount < MAX_MAIL_MONEY_COUNT)	
		//{
		//	money[nMoneyCount] = vecAward[i];
		//	nMoneyCount++;
		//}
		//// 是物品
		//else if (vecAward[i].nAwardType >= DROP_RULE_GROUP_TYPE_ITEMTYPE_BEGIN 
		//	&& vecAward[i].nAwardType <= DROP_RULE_GROUP_TYPE_ITEMTYPE_END
		//	&& nItemCount < MAX_MAIL_ITEM_COUNT)	
		//{
		//	item[nItemCount] = vecAward[i];
		//	nItemCount++;
		//}
		//else
		//{
		//	tolog4("CUserMailMgr::SendMail AwardType Error idReceive[%u], AwardType[%d], AwardNum[%d]",
		//		idReceiver, vecAward[i].nAwardType, vecAward[i].nAwardNum);
		//}
	}
	sprintf(szCmd, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",
			item[0].nAwardType, item[0].nAwardNum, item[1].nAwardType, item[1].nAwardNum,
			item[2].nAwardType, item[2].nAwardNum, item[3].nAwardType, item[3].nAwardNum,
			item[4].nAwardType, item[4].nAwardNum, item[5].nAwardType, item[5].nAwardNum,
			money[0].nAwardType, money[0].nAwardNum, money[1].nAwardType, money[1].nAwardNum,
			money[2].nAwardType, money[2].nAwardNum, money[3].nAwardType, money[3].nAwardNum,
			nExp);

	return this->SendMail(idReceiver, szTitle, szContent, szSender, szCmd);
}

////////////////////////////////////////////////////////////////////////
/* 发邮件 (脚本接口)
// idReceiver	-	邮件接收者ID
// szTitle		-	邮件标题,	最长32个字符
// szContent	-	邮件内容,	最长256个字符
// szSender		-	发送者名字, 最长32个字符
// szCmd		-   物品,货币和经验命令格式	"物品类型1 物品1数量 物品类型2 物品2数量
											 物品类型3 物品3数量 物品类型4 物品4数量
											 货币类型1 货币1数量 货币类型2 货币2数量 
											 货币类型3 货币3数量 货币类型4 货币4数量 
											 经验值"
*/
bool CUserMailMgr::SendMail(OBJID idReceiver, const char* szTitle, const char* szContent, const char* szSender, const char* szCmd)
{
	CHECKF(pGameDatabase);
	CHECKF(idReceiver);
	CHECKF(szTitle && strlen(szTitle) < MAX_MAIL_TITLE);
	CHECKF(szContent && strlen(szContent) < MAX_MAIL_TEXT);
	CHECKF(szSender && strlen(szSender) < NAME_SIZE);

	MAIL_AWARD_DATA item[MAX_MAIL_ITEM_COUNT]		= {0};
	MAIL_AWARD_DATA money[MAX_MAIL_MONEY_COUNT]		= {0};
	int nExp = 0;
	
	// 获取物品，货币，经验
	int nResult = sscanf(szCmd, "%d %d %d %d %d %d %d %d \
								 %d %d %d %d \
								 %d %d %d %d %d %d %d %d %d", 
								&item[0].nAwardType, &item[0].nAwardNum,
								&item[1].nAwardType, &item[1].nAwardNum,
								&item[2].nAwardType, &item[2].nAwardNum, 
								&item[3].nAwardType, &item[3].nAwardNum,
								&item[4].nAwardType, &item[4].nAwardNum,
								&item[5].nAwardType, &item[5].nAwardNum,
								&money[0].nAwardType, &money[0].nAwardNum,
								&money[1].nAwardType, &money[1].nAwardNum,
								&money[2].nAwardType, &money[2].nAwardNum, 
								&money[3].nAwardType, &money[3].nAwardNum,
								&nExp);
	if (nResult != 21)
	{
		return false;
	}

	unsigned int unCurTime = ::TimeGet(TIME_SECOND);
	
	SQLBUF strSql = "";
	sprintf(strSql, "insert into %s(user_id, status, title, sender, content, send_time, over_time, \
				itemtype1, itemnum1, itemtype2, itemnum2, itemtype3, itemnum3, itemtype4, itemnum4, \
				itemtype5, itemnum5, itemtype6, itemnum6,\
				moneytype1, moneynum1, moneytype2, moneynum2, moneytype3, moneynum3, moneytype4, moneynum4, exp, server_group) \
				values(%u, %d, \'%s\', \'%s\', \'%s\', %u, %u, \
				%d, %d, %d, %d, %d, %d, %d, %d,\
				%d, %d, %d, %d,\
				%d, %d, %d, %d, %d, %d, %d, %d, %d, %d)",
				GAME_DB_NAME_USER_MAIL, idReceiver, EMAIL_STATUS_UNREAD, szTitle, szSender,
				szContent, unCurTime, unCurTime + MAIL_EXIST_TIME, 
				item[0].nAwardType, item[0].nAwardNum, item[1].nAwardType, item[1].nAwardNum,
				item[2].nAwardType, item[2].nAwardNum, item[3].nAwardType, item[3].nAwardNum,
				item[4].nAwardType, item[4].nAwardNum, item[5].nAwardType, item[5].nAwardNum,
				money[0].nAwardType, money[0].nAwardNum, money[1].nAwardType, money[1].nAwardNum,
				money[2].nAwardType, money[2].nAwardNum, money[3].nAwardType, money[3].nAwardNum, nExp, g_nServerGroup);
	CHECKF(pGameDatabase->ExecuteSQL(strSql, DBUPDATE_ASYNC));

	// 新邮件提醒
	MSG_MAIL_LIST mail = {0};
	::SafeCopy(mail.szTitle, szTitle, sizeof(mail.szTitle));
	::SafeCopy(mail.szSender, szSender, sizeof(mail.szSender));
	mail.nSendTime = unCurTime;
	mail.nStatus = EMAIL_STATUS_UNREAD;
	this->NewMailNotify(idReceiver, mail);


	return true;
}

////////////////////////////////////////////////////////////////////////
// 发送新邮件提醒
void CUserMailMgr::NewMailNotify(OBJID idReceiver, MSG_MAIL_LIST& mail)
{
	CHECK(idReceiver);

	//CMsgGameUserMailList msg;
	//msg.CreateMsg(EMSG_MAIL_LIST_ACT_NewMailNotify, EMSG_MAIL_LIST_RESULT_Succ, 0, 0, idReceiver);	// nParam1保存接受者ID
	//CHECK(msg.AppendParam(mail));
	//// 在本线, 直接发送
	//if (pUserMgr->IsOnline(idReceiver))
	//{
	//	pUserMgr->SendMsg(idReceiver, &msg);
	//}
	//else	// 不在本线, 由关系服转发
	//{
	//	pGameKernel->SendRelationMsg(&msg);
	//}

	//// 更新邮件推送提示信息
	//pMarksInfoMgr->UpdateUserMarksInfo(idReceiver, MSG_MARKS_TYPE_MAIL, MARKSDATA_CONTROL_ADD, 1);
}

////////////////////////////////////////////////////////////////////////
// Description:  根据枚举生成邮件发送者名字
bool CUserMailMgr::GetMailSenderByType(EMAIL_SENDER_TYPE eSenderType, OUT char* pszSenderName, int nSize)
{
	CHECKF(eSenderType >= EMAIL_SENDER_Beg && eSenderType < EMAIL_SENDER_End);
	CHECKF(pszSenderName);
	CHECKF(nSize > 0 && nSize <= NAME_SIZE);

	//CONFIG_TEXT_ID eTextID = CONFIG_TEXT_ID_NONE;
	//switch (eSenderType)
	//{
	//case EMAIL_SENDER_System:	
	//	eTextID = CONFIG_TEXT_ID_MAIL_SENDER_SYSTEM;
	//	break;
	//default:
	//	tolog2("CUserMailMgr::GetMailSenderByType Unknow Mail SenderName Type[%d]", (int)eSenderType);
	//	break;
	//}

	//SZ_CONFIG_TEXT_TYPE szText = "";
	//pConstTableMgr->GetConfigText()->GetText(eTextID, szText);
	//::SafeCopy(pszSenderName, szText, nSize);

	return true;
}

////////////////////////////////////////////////////////////////////////
// Description:  根据枚举生成邮件标题
bool CUserMailMgr::GetMailTitleByType(EMAIL_TITLE_TYPE eTitleType, OUT char* pszTitle, int nSize)
{
	CHECKF(eTitleType >= EMAIL_TITLE_Beg && eTitleType < EMAIL_TITLE_End);
	CHECKF(pszTitle);
	CHECKF(nSize > 0 && nSize <= MAX_MAIL_TITLE);

	//CONFIG_TEXT_ID eTextID = CONFIG_TEXT_ID_NONE;
	//switch (eTitleType)
	//{
	//case EMAIL_TITLE_System:	
	//	eTextID = CONFIG_TEXT_ID_MAIL_TITLE_SYSTEM;
	//	break;
	//case EMAIL_TITLE_Arena_Update_Record:
	//	eTextID = CONFIG_TEXT_ID_MAIL_TITLE_ARENA_UPDATE_RECORD;
	//	break;
	//default:
	//	tolog2("CUserMailMgr::GetMailTitleByType Unknow Mail Title Type[%d]", (int)eTitleType);
	//	break;
	//}

	//SZ_CONFIG_TEXT_TYPE szText = "";
	//pConstTableMgr->GetConfigText()->GetText(eTextID, szText);
	//::SafeCopy(pszTitle, szText, nSize);

	return true;
}

////////////////////////////////////////////////////////////////////////
// Description:  根据枚举生成邮件内容
bool CUserMailMgr::GetMailContentByType(EMAIL_CONTENT_TYPE eContentType, OUT char* pszContent, int nSize)
{
	CHECKF(eContentType >= EMAIL_CONTENT_Beg && eContentType < EMAIL_CONTENT_End);
	CHECKF(pszContent);
	CHECKF(nSize > 0 && nSize <= MAX_MAIL_TEXT);

	//CONFIG_TEXT_ID eTextID = CONFIG_TEXT_ID_NONE;
	//switch (eContentType)
	//{
	//case EMAIL_CONTENT_System:	
	//	eTextID = CONFIG_TEXT_ID_MAIL_CONTENT_SYSTEM;
	//	break;
	//default:
	//	tolog2("CUserMailMgr::GetMailContentByType Unknow Mail Content Type[%d]", (int)eContentType);
	//	break;
	//}

	//SZ_CONFIG_TEXT_TYPE szText = "";
	//pConstTableMgr->GetConfigText()->GetText(eTextID, szText);
	//::SafeCopy(pszContent, szText, nSize);

	return true;
}

