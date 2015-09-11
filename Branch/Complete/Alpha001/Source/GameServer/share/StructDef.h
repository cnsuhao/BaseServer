////////////////////////////////////////////////////////////////////////
// Import : 共享文件。结构体定义。
// Moudle : StructDef.h 
// Author : 陈建军(Chen Jianjun)
// Create : 2015-6-19
////////////////////////////////////////////////////////////////////////
#ifndef _SHARE_STRUCT_DEF_H_
#define _SHARE_STRUCT_DEF_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "./ConstDef.h"
#include "./EnumDef.h"

#include <set>
#include <map>
#include <vector>

////////////////////////////////////////////////////////////////////////
// 通用接口
inline void EmptyFunction(...) {}
#ifdef MULTI_KERNEL_LOG
#define LOGDEBUG	LOGMSG
#else
#define LOGDEBUG	EmptyFunction
#endif
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
// 通用STL容器定义
typedef std::vector<int>			INT_VEC;
typedef INT_VEC::iterator			INT_VEC_ITER;
typedef INT_VEC::const_iterator		INT_VEC_CITER;

typedef std::vector<UINT>			UINT_VEC;
typedef UINT_VEC::iterator			UINT_VEC_ITER;
typedef UINT_VEC::const_iterator	UINT_VEC_CITER;

typedef std::vector<OBJID>			ID_VEC;
typedef ID_VEC::iterator			ID_VEC_ITER;
typedef ID_VEC::const_iterator		ID_VEC_CITER;

typedef std::set<int>				INT_SET;
typedef INT_SET::iterator			INT_SET_ITER;
typedef INT_SET::const_iterator		INT_SET_CITER;

typedef std::set<UINT>				UINT_SET;
typedef UINT_SET::iterator			UINT_SET_ITER;
typedef UINT_SET::const_iterator	UINT_SET_CITER;

typedef std::set<OBJID>				ID_SET;
typedef ID_SET::iterator			ID_SET_ITER;
typedef ID_SET::const_iterator		ID_SET_CITER;

typedef std::map<int, int>			INT_MAP;
typedef INT_MAP::iterator			INT_MAP_ITER;
typedef INT_MAP::const_iterator		INT_MAP_CITER;
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
// 结构体定义
// 登陆时账号信息
struct ACCOUNT_INFO
{
	// 读表信息
	OBJID		idAccount;
	char		szAccountName[64];
	int			nAccountType;
	int			nAccountStatus;
	int			nAccountStatusParam;

	// 内存信息
	SOCKET_ID	idSocket;
	OBJID		idChoosePlayer;
	int			nKickOtherFlag;
	int			nLoginState;
	int			nUserCount;
	UINT		unStartSecond;
};

// 任务数据
struct MSG_USER_TASK_DATA
{
	MSG_NUM_4BIT nTaskID;		// 编号																											
	MSG_NUM_4BIT nTaskType;		// 任务类型													
	MSG_NUM_4BIT nStep;			// 步骤														
	MSG_NUM_4BIT nStatus;		// 任务状态(0:未接受,1:接受, 2:提交, 3:达到完成条件但未提交)
	MSG_NUM_4BIT nCount1;		// 计数1													
	MSG_NUM_4BIT nCount2;		// 计数2													
	MSG_NUM_4BIT nCount3;		// 计数3
	MSG_NUM_4BIT nBeginTime;	// 开始时间(单位秒)	
	MSG_NUM_4BIT nOverTime;		// 过期时间(0:无限制, >0:过期时间单位秒)
};
typedef std::vector<MSG_USER_TASK_DATA>			VEC_MSG_USER_TASK;
typedef VEC_MSG_USER_TASK::iterator				ITER_VEC_MSG_USER_TASK;
typedef VEC_MSG_USER_TASK::const_iterator		CITER_VEC_MSG_USER_TASK;

// 邮件内容
struct MSG_MAIL_DATA
{
	MSG_NUM_8BIT	i64MailID;	// 邮件ID
	MSG_STR_256BIT  szContent;	// 内容
	MSG_NUM_4BIT    nOverTime;	// 过期时间(必须有时间限制)
	MSG_NUM_4BIT    nStatus;	// 邮件状态(0:未读, 1:已读, 2:删除)

	MSG_NUM_4BIT nItemType1;	// 物品1
	MSG_NUM_4BIT nItemNum1;		// 物品1数量
	MSG_NUM_4BIT nItemType2;	// 物品2
	MSG_NUM_4BIT nItemNum2;		// 物品2数量
	MSG_NUM_4BIT nItemType3;	// 物品3
	MSG_NUM_4BIT nItemNum3;		// 物品3数量
	MSG_NUM_4BIT nItemType4;	// 物品4
	MSG_NUM_4BIT nItemNum4;		// 物品4数量
	MSG_NUM_4BIT nItemType5;	// 物品5
	MSG_NUM_4BIT nItemNum5;		// 物品5数量
	MSG_NUM_4BIT nItemType6;	// 物品6
	MSG_NUM_4BIT nItemNum6;		// 物品6数量

	MSG_NUM_4BIT nMoneyType1;	// 货币1
	MSG_NUM_4BIT nMoneyNum1;	// 货币1数量
	MSG_NUM_4BIT nMoneyType2;	// 货币2
	MSG_NUM_4BIT nMoneyNum2;	// 货币2数量
	MSG_NUM_4BIT nMoneyType3;	// 货币3
	MSG_NUM_4BIT nMoneyNum3;	// 货币3数量
	MSG_NUM_4BIT nMoneyType4;	// 货币4
	MSG_NUM_4BIT nMoneyNum4;	// 货币4数量

	MSG_NUM_4BIT nExp;			// 经验
};

// 邮件列表
struct MSG_MAIL_LIST
{
	MSG_NUM_8BIT	i64MailID;	// 邮件ID
	MSG_STR_32BIT	szTitle;	// 邮件标题
	MSG_STR_32BIT	szSender;	// 发件人名字
	MSG_NUM_4BIT	nSendTime;	// 发邮件时间
	MSG_NUM_4BIT	nStatus;	// 邮件状态(0:未读, 1:已读)
};
typedef std::vector<MSG_MAIL_LIST>				VEC_MAIL_LIST;
typedef VEC_MAIL_LIST::iterator					ITER_VEC_MAIL_LIST;
typedef VEC_MAIL_LIST::const_iterator			CITER_VEC_MAIL_LIST;

// 邮件物品
struct MAIL_AWARD_DATA
{
	int		nAwardType;	// 物品Type
	int		nAwardNum;	// 物品数量
};
typedef std::vector<MAIL_AWARD_DATA> VEC_MAIL_AWARD;

// 聊天玩家信息
struct ST_TALK_USER_INFO
{
	OBJID	idUser;					// 玩家ID
	char	szUserName[NAME_SIZE];	// 玩家角色名
	int		nLookface;				// 玩家头像
	int		nLev;					// 玩家等级
};
////////////////////////////////////////////////////////////////////////
#endif // end of _SHARE_STRUCT_DEF_H_