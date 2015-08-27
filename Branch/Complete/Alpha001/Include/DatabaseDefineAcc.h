////////////////////////////////////////////////////////////////////////
// Import : 账号库内容全局声明处
// Moudle : DatabaseDefineAcc.h
// Author : 陈建军(Chen Jianjun)
// Created: 2015-08-27
////////////////////////////////////////////////////////////////////////
#ifndef _DATABASE_DEFINE_ACC_H_
#define _DATABASE_DEFINE_ACC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

static const char* ACC_DB_NAME_ACCOUNT = "account";		// 账号表
enum ACCOUNT_DATA
{
	ACCOUNT_DATA_ID = 0,			// 账号id								uint
	ACCOUNT_DATA_NAME,				// 账号名								varchar64
	ACCOUNT_DATA_PASSWORD,			// 账号密码								varchar64
	ACCOUNT_DATA_REG_TIME,			// 注册utc时间							uint
	ACCOUNT_DATA_TYPE,				// 账号类型(0普通, 1GM，2游客)			uint
	ACCOUNT_DATA_STATUS,			// 账号状态(0正常，1临时封，2永久封)	uint
	ACCOUNT_DATA_STATUS_PARAM,		// 临时封结束时间						uint
	ACCOUNT_DATA_PLATFORM,			// 平台									varchar32
	ACCOUNT_DATA_CHANNEL,			// 渠道									varchar32
	ACCOUNT_DATA_OS,				// 操作系统								varchar32
};

//static const char* ACC_DB_VAS_LOG = "vas_log";	// 元宝日志表
//enum VAS_LOG_DATA
//{
//	VAS_LOG_DATA_ID = 0,			// id			bigint
//	VAS_LOG_DATA_ACCOUNT_ID,		// 账号id		uint
//	VAS_LOG_DATA_USER_ID,			// 角色id		uint
//	VAS_LOG_DATA_SERVER_GROUP,		// 服务器组		uint
//	VAS_LOG_DATA_SERVER_LINE,		// 服务器线		uint
//	VAS_LOG_DATA_FLOW_TYPE,			// 流向类型		uint
//	VAS_LOG_DATA_TIME,				// 时间, utc秒	uint
//	VAS_LOG_DATA_ITEMTYPE_ID,		// itemtype		uint
//	VAS_LOG_DATA_ITEMTYPE_AMOUNT,	// 数量			uint
//	VAS_LOG_DATA_POINT,				// 操作点数		bigint
//	VAS_LOG_DATA_AFTER_POINT,		// 操作后点数	bigint
//	VAS_LOG_DATA_EXTRA_TEXT,		// 额外文字说明 varchar128
//};
//
//static const char* ACC_DB_MONEY_LOG = "money_log";	// 金钱日志表
//enum MONEY_LOG_DATA
//{
//	MONEY_LOG_DATA_ID = 0,			// id			bigint
//	MONEY_LOG_DATA_ACCOUNT_ID,		// 账号id		uint
//	MONEY_LOG_DATA_USER_ID,			// 角色id		uint
//	MONEY_LOG_DATA_SERVER_GROUP,	// 服务器组		uint
//	MONEY_LOG_DATA_SERVER_LINE,		// 服务器线		uint
//	MONEY_LOG_DATA_FLOW_TYPE,		// 流向类型		uint
//	MONEY_LOG_DATA_TIME,			// 时间, utc秒	uint
//	MONEY_LOG_DATA_ITEMTYPE_ID,		// itemtype		uint
//	MONEY_LOG_DATA_ITEMTYPE_AMOUNT,	// 数量			uint
//	MONEY_LOG_DATA_MONEY_TYPE,		// 金币类型		uint
//	MONEY_LOG_DATA_POINT,			// 操作点数		bigint
//	MONEY_LOG_DATA_AFTER_POINT,		// 操作后点数	bigint
//	MONEY_LOG_DATA_EXTRA_TEXT,		// 额外文字说明 varchar128
//};
//
//static const char* ACC_DB_SERVER_LIST = "server_list";	// 服务器列表, 维护人员配置的
//enum SERVER_LIST_DATA
//{
//	SERVER_LIST_DATA_GROUP = 0,			// 组id			uint
//	SERVER_LIST_DATA_LINE,				// 线id			uint
//	SERVER_LIST_DATA_CLIENT_IP,			// 客户端ip		varchar50
//	SERVER_LIST_DATA_CLIENT_PORT,		// 客户端端口	uint 
//	SERVER_LIST_DATA_CLOSE,				// 关闭标记		uint
//};
//
//static const char* ACC_DB_NEWCARD = "newcard";	// 新手卡号码表
//enum NEWCARD_DATA
//{
//	NEWCARD_DATA_ID = 0,			// id			bigint
//	NEWCARD_DATA_CARD,				// 卡号			char64
//	NEWCARD_DATA_PICKED,			// 使用标记		uint
//	NEWCARD_DATA_PLATFORM,			// 平台			varchar10
//	NEWCARD_DATA_SERVER_GROUP,		// 服务器组		uint
//};
//
//static const char* ACC_DB_PAYLOG = "paylog";	// 充值记录表
//enum PAYLOG_DATA
//{
//	PAYLOG_DATA_LOGID = 0,		// id			bigint
//	PAYLOG_DATA_PAYNUM,			// 流水号		varchar255
//	PAYLOG_DATA_LOGDATE,		// 充值utc时间	uint
//	PAYLOG_DATA_ACCOUNT_ID,		// 账号id		uint
//	PAYLOG_DATA_USER_ID,		// 角色id		uint
//	PAYLOG_DATA_IP,				// ip			varchar20
//	PAYLOG_DATA_PAYGOLD,		// 充值元宝		uint
//	PAYLOG_DATA_FREEGOLD,		// 赠送元宝		uint
//	PAYLOG_DATA_PAYMONEY,		// 人民币		DECIMAL
//	PAYLOG_DATA_CHANNEL,		// channel		varchar20
//	PAYLOG_DATA_CHANNEL_FEE,	// channel_fee	float
//	PAYLOG_DATA_SERVER_GROUP,	// 服务器组号	uint
//	PAYLOG_DATA_CONFIG_ID,		// 配置id		uint
//	PAYLOG_DATA_STATUS,			// 审核状态（0 审批中， 1 通过， 2 拒绝, 3 完结）	uint
//};
//
//static const char* ACC_DB_ONLINE_LOG = "online_log";	// 在线日志表
//enum ONLINE_LOG_DATA
//{
//	ONLINE_LOG_DATA_ID = 0,
//	ONLINE_LOG_DATA_TIME,
//	ONLINE_LOG_DATA_COUNT_ONLINE,
//	ONLINE_LOG_DATA_SERVER_GROUP,
//};
//
//static const char* ACC_DB_NOTIFY_PHP = "notify_php";	// 平台公告表
//enum NOTIFY_PHP_DATA
//{
//	NOTIFY_PHP_DATA_ID = 0,				// 自增长id	uint
//	NOTIFY_PHP_DATA_BEGIN_TIME,			// 开始时间 uint
//	NOTIFY_PHP_DATA_INTERVAL_SECOND,	// 间隔时间 uint
//	NOTIFY_PHP_DATA_COUNT,				// 播放次数 uint
//	NOTIFY_PHP_DATA_CHANNEL,			// 频道		uint
//	NOTIFY_PHP_DATA_TEXT,				// 公告内容 varchar512
//	NOTIFY_PHP_DATA_SERVER_GROUP,		// 服务器组 uint
//};
//
//static const char* ACC_DB_NAME_GM_MAC = "gm_mac";	// gm Mac地址配置
//enum GM_MAC_DATA
//{
//	GM_MAC_DATA_ADDRESS_MAC = 0,		// mac地址字符串	varchar32
//	GM_MAC_DATA_PARAM_STRING,			// 注释字符长		varchar64
//};
//
//static const char* ACC_DB_NAME_GM_OPERATION_LOG = "gm_operation_log";	// gm 操作日志
//enum GM_OPERATION_LOG_DATA
//{
//	GM_OPERATION_LOG_DATA_ID = 0,				// id				uint
//	GM_OPERATION_LOG_DATA_UTC_SECOND,			// 记录时间, utc秒	uint
//	GM_OPERATION_LOG_DATA_DATE_TIME,			// 日期时间			varchar24
//	GM_OPERATION_LOG_DATA_GM_ACCOUNT_ID,		// gm账号id			uint
//	GM_OPERATION_LOG_DATA_GM_ACCOUNT_NAME,		// gm账号名			varchar32
//	GM_OPERATION_LOG_DATA_GM_USER_ID,			// gm角色id			uint
//	GM_OPERATION_LOG_DATA_GM_USER_NAME,			// gm角色名			varchar32
//	GM_OPERATION_LOG_DATA_GM_IP,				// gm操作时ip		varchar32
//	GM_OPERATION_LOG_DATA_GM_MAC,				// gm操作时mac地址	varchar32
//	GM_OPERATION_LOG_DATA_SERVER_GROUP,			// 服务器组			uint
//	GM_OPERATION_LOG_DATA_SERVER_LINE,			// 服务器线			uint
//	GM_OPERATION_LOG_DATA_OPERATION_TYPE_STR,	// 操作类型字符串	varchar16
//	GM_OPERATION_LOG_DATA_OPERATION_INFO,		// 操作详情			varchar128
//};

#endif // end of _DATABASE_DEFINE_ACC_H_