////////////////////////////////////////////////////////////////////////
// Import : 共享文件。枚举定义。
// Moudle : EnumDef.h 
// Author : 陈建军(Chen Jianjun)
// Create : 2015-6-19
////////////////////////////////////////////////////////////////////////
#ifndef _SHARE_ENUM_DEF_H_
#define _SHARE_ENUM_DEF_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../common/common.h"

// 线程管道类型
enum ENUM_MSGPORT_TYPE
{
	MSGPORT_SHELL		= 0,		// 对话框
	MSGPORT_SOCKET		= 1,		// 底层通讯
	MSGPORT_LOGIN		= 2,		// 登陆
	MSGPORT_GAME		= 3,		// 游戏逻辑
	MSGPORT_RELATION	= 4,		// 服务器间通信
	MSGPORT_AI			= 5,		// AI通信

	MSGPORT_SIZE,					// 管道数量
	MSGPORT_DEFAULT		= 999,		// 默认线程ID, 此枚举不可作为线程间通信接口使用
};
////////////////////////////////////////////////////////////////////////

// 账号踢出标志
enum ACCOUNT_KICK_FLAG
{
	ACCOUNT_KICK_FLAG_NONE		= 0x0000,
	ACCOUNT_KICK_FLAG_SOCKET	= 0x0001,
	ACCOUNT_KICK_FLAG_GAME		= 0x0002,
	ACCOUNT_KICK_FLAG_RELATION	= 0x0004,
	//ACCOUNT_KICK_FLAG_OK		= ACCOUNT_KICK_FLAG_SOCKET | ACCOUNT_KICK_FLAG_GAME | ACCOUNT_KICK_FLAG_RELATION,
	ACCOUNT_KICK_FLAG_OK		= ACCOUNT_KICK_FLAG_SOCKET,
};

// 登录时账号状态
enum ACCOUNT_LOGIN_STATE
{
	ACCOUNT_LOGIN_STATE_WAIT_KICK,
	ACCOUNT_LOGIN_STATE_WAIT_ENTER,
	ACCOUNT_LOGIN_STATE_WAIT_CHOOSE,
	ACCOUNT_LOGIN_STATE_OK,
};

// 踢出原因
enum KICK_REASON
{
	KICK_REASON_DEFAULT					= 0,	// 踢出默认值, 一般不要用这个值
	KICK_REASON_ACCOUNT_ERROR			= 1,	// 账号不存在
	KICK_REASON_PASSWORD_ERROR			= 2,	// 密码错误
	KICK_REASON_BE_KICK_ANOTHER			= 3,	// 被别人踢
	KICK_REASON_RELATION_SERVER			= 4,	// 关系服务器指示你被踢了
	KICK_REASON_FULL					= 5,	// 人太多
	KICK_REASON_SYSTEM					= 6,	// 服务器控制面板踢人 或 GM踢人	
	KICK_REASON_NOT_ALLOW				= 7,	// 服务器未开启登陆允许
	KICK_REASON_GM_MAC_ERROR			= 8,	// GM工具Mac地址验证错误		
	KICK_REASON_CHECK_SPEED_TOO_FAST	= 9,	// 检测速度过快					**
	KICK_REASON_GMCMD					= 10,	// GM命令踢自己	
	KICK_REASON_LOGIN_TIMEOUT			= 11,	// 登陆过程超时
	KICK_REASON_ACCOUNT_STOP_BYTIME		= 12,	// 账号临时封停
	KICK_REASON_ACCOUNT_STOP_FOREVER	= 13,	// 账号永久封停
};

// user的内存数据枚举
enum MEMORY_DATA_ATTR_USER
{
	mdaUser_BEGIN = 0,

	mdaUser_AccountType,				// 账号类型
	mdaUser_AccountStatus,				// 账号状态
	mdaUser_AccountStatusParam,			// 账号状态参数

	mdaUser_OnlineSecond,				// 在线时间

	mdaUser_OnTimer_EverySecond,		// 每秒心跳
	mdaUser_OnTimer_MinuteSecond,		// 每分钟心跳

	mdaUser_GmMacPass,

	mdaUser_END,
};

// 掩码类型
enum EUSERMASKTYPE
{
	EUMT_Begin					= 0,
	EUMT_TaskMask				= 1,	// 任务掩码
	EUMT_GiveMask				= 2,	// 奖励掩码
	EUMT_DayMask				= 3,	// 天掩码
	EUMT_WeekMask				= 4,	// 周掩码
	EUMT_MonthMask				= 5,	// 月掩码
	EUMT_End,
};

// 玩家掩码ID服务器占用声明枚举				服务端使用:按位掩码ID (0 - 5000) 计数掩码ID(10000 - 20000)
enum E_USER_MASKID_PROGRAM
{
	// 任务掩码ID开始
	// 任务码ID结束

	// 奖励掩码ID开始

	// 奖励掩码ID结束

	// 天掩码ID开始
	EUMIP_DAY_BIT_LiveBoxStatus = 1,		// 每日活跃 活跃度宝箱打开标记(目前使用第2到第5二进制位)

	EUMIP_DAY_COUNT_LiveValues = 10001,		// 每日活跃 当前活跃度
	// 天掩码ID结束

	// 周掩码ID开始
	// 周掩码ID结束

	// 月掩码ID开始
	EUMIP_MONTH_BIT_SIGN = 1,				// 每日签到掩码
	// 月掩码ID结束
};

// 玩家临时数据表
enum EUSER_TEMPDATA_PROGRAM
{
	// 程序是用的TMP_ID从10000开始
	EUTDP_BEGIN = 10000,

	// 10000 - 11000留给客户端使用BEG
	EUTDP_CLIENT_BEGIN = EUTDP_BEGIN,
	EUTDP_CLIENT_END = 11000,
	// 10000 - 11000留给客户端使用END

	// 服务端从11001开始
	EUTDP_SERVER_BEGIN = 11001,
	EUTDP_SERVER_END,
	EUTDP_END,
};

// 邮件状态
enum EMAIL_STATUS
{
	EMAIL_STATUS_Begin	= 0,
	EMAIL_STATUS_UNREAD = EMAIL_STATUS_Begin,	// 未读
	EMAIL_STATUS_READ	= 1,					// 已读
	EMAIL_STATUS_Del	= 2,					// 删除
	EMAIL_STATUS_End,
};

// 任务更新类型枚举
enum EUPDATA_TASK_TYPE
{
	EUPDATA_TASK_TYPE_Beg	= 0,
	EUPDATA_TASK_TYPE_Add	= EUPDATA_TASK_TYPE_Beg,	// 增加任务
	EUPDATA_TASK_TYPE_Del	= 1,						// 删除任务
	EUPDATA_TASK_TYPE_Alter = 2,						// 修改任务
	EUPDATA_TASK_TYPE_End,
};

// 聊天频道
enum TALK_TXTATR
{
	TALK_TXTATR_BEGIN			= 2000,
	TALK_TXTATR_PRIVATE			= 2001,	// 私聊
	TALK_TXTATR_SYNDICATE		= 2002,	// 帮派
	TALK_TXTATR_WORLDSERVER		= 2003,	// 世界(本区)
	TALK_TXTATR_GM_CMD			= 2004,	// GM命令
	TALK_TXTATR_NOTICE			= 2005,	// 公告
	TALK_TXTATR_HINT			= 2006,	// 提示
	TALK_TXTATR_GM_OPERATION	= 2007,	// GM操作(工具)
	TALK_TXTATR_END,
};
/////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // end of _SHARE_ENUM_DEF_H_
