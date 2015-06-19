////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2012, WuHan ChuangYou, All Rights Reserved
// Moudle: GlobalConstDef.h
// Author: 彭文奇(Peng Wenqi)
// Created: 2012-11-19
////////////////////////////////////////////////////////////////////////
#ifndef _GLOBAL_CONSTDEF_HEADER_
#define _GLOBAL_CONSTDEF_HEADER_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>

extern int  g_nServerLine;					// 服务器线路号
extern int  g_nServerGroup;					// 服务器组号
extern int	g_nServerStartTime;				// 服务器开启时间精确到天
extern std::string g_strConstDatabaseName;	// 常量表数据库名
extern std::string g_strGameDatabaseName;	// 游戏服数据库名
extern std::string g_strAccountDatabaseName;// 账号服数据库名

const int	NAME_SIZE			= 32;							// 角色名长度
const int	SYN_ANNOUNCE_SIZE	= 256;							// 帮派公告长度
const int	MAX_PACKETSIZE		= 1024;							// 网络消息包尺寸
const int	MAX_MESSAGESIZE		= MAX_PACKETSIZE + 40;			// 内部消息包尺寸
const int	MAX_PARAMSIZE		= 256;							// action param space
const int	MAX_TENETSIZE		= 256;							
const int	_MAX_FEELSIZE		= 32;
const int	MAX_TOLOG_MONEY		= 100000;						// 消耗的金钱超过多少需要出日志
const int	MAX_MAIL_TEXT		= 256;							// 最大的邮件正文字符数
const int   MAX_MAIL_TITLE		= 32;							// 最大邮件标题字符数
const int   MAX_ADDRESS_SIZE	= 64;							// 玩家所在地名长度
const int	INVITE_CODE_SIZE	= 16;							// 邀请码长度
const int	_MAX_MSGSIZE		= 1024 ;

#ifdef MYDEBUG
	const int	MAX_GAMESERVER_ACCEPT_SESSION	= 200;									// 游服最大会话数量
#else
	const int	MAX_GAMESERVER_ACCEPT_SESSION	= 5000;									// 游服最大会话数量
#endif
const int	MAX_LOGINSERVER_ACCEPT_SESSION		= 500;									// 入口服最大会话数量
const int	MAX_GAMESERVER_PLAYER_COUNT			= MAX_GAMESERVER_ACCEPT_SESSION - 100;	// 不允许玩家进入游戏阀值
const int	MAX_RELATIONSERVER_ACCEPT_SESSION	= 100;									// 关系服最大会话数量
const int	MAX_CROSSSERVER_ACCEPT_SESSION		= 100;									// 跨服最大会话数量
const int	RELATION_SERVER_SOCKET_BUF			= 512 * 1024;							// 关系服务器套接字参数		缓冲区大小		[发送/接收]相同
const int	CROSS_SERVER_SOCKET_BUF				= 512 * 1024;							// 跨服服务器套接字参数		缓冲区大小		[发送/接收]相同
const int	USER_ONLINE_SYNC_COUNT_PER_SECOND	= 500;									// 每秒玩家的在线信息同步的个数

typedef	unsigned long		OBJID;
typedef	unsigned long		PROCESS_ID;							// 通常与内部消息接口ID相同
typedef	long				SOCKET_ID;							// 玩家对应的SOCKET_ID，通常为SET的索引号
typedef __int64				I64;
typedef __int64				DB_KEY;


typedef	char			SQLBUF[4096];
typedef	char			MSGBUF[1024];
typedef	char			MESSAGESTR[MAX_MESSAGESIZE];

// 新定义的消息结构体只允许以下几种类型变量
typedef char	MSG_NUM_1BIT;
typedef short	MSG_NUM_2BIT;
typedef int		MSG_NUM_4BIT;
typedef __int64 MSG_NUM_8BIT;
typedef char	MSG_STR_16BIT[16];
typedef char	MSG_STR_32BIT[32];
typedef char	MSG_STR_64BIT[64];
typedef char	MSG_STR_128BIT[128];
typedef char	MSG_STR_192BIT[192];
typedef char	MSG_STR_256BIT[256];

const int MAX_ALLOW_AINPC_REACH_DESTPOINT_DISTANCE = 1;

static const char* LOGIN_SERVER_PASSWORD	= "sXd73E4DwS9!5_6";

const double	DOUBLE_PERCENT_BASE = 10000.0;	// 万分比基数(double类型)
const int		INT_PERCENT_BASE	= 10000;	// 万分比基数(int类型)
const I64		I64_PERCENT_BASE	= 10000i64;	// 万分比基数(I64类型)
const I64		I64_MAX_CEIL		= 9223372036854775807i64;	// I64类型数字上限
const int		INT_MAX_CEIL		= 2147483647;				// int类型数字上限
const unsigned int	UINT_MAX_CEIL	= 4294967295;				// uint类型数字上限

const int	ID_NONE			= 0;
const int	ID_AI_PROCESS	= 1;
const int	SOCKET_NONE		= -1;				// 无效的SOCKET索引
const int	SERVER_LISTEN_PORT_DEFAULT = 19999;

const int	CROSS_SERVER_GROUP = 9999;		// 跨服服务器组号



const int MAX_NEWCARD_LENGTH		= 19;				// 新手卡的位数
const int MAX_NEWCARD_HEADER_LENGTH	= 5;				// 新手卡头的位数
static const char* CONST_XS_NEWCARD_HEADER	= "CSMT-";	// 新手卡头
static const char* CONST_MT_NEWCARD_HEADER	= "WSMT-";	// 媒体卡头
const int MT_NEWCARD_TYPE_OFFSET	= 1000;				// 媒体卡类型偏移量

const int ITEM_TYPE_BEGIN			= 100000;			// 物品类型开始

const int MAX_MAIL_ITEM_COUNT       = 6;				// 邮件中最大物品种类
const int MAX_MAIL_MONEY_COUNT      = 4;				// 邮件中最大货币种类

const int MAX_LIVENESS_ID			= 50;				// 每日活跃配置表活跃项最大ID

static const char* TALK_SYSTEM_NAME = "System";

const int MAX_USER_LEV = 100;							// 玩家最高等级

const int SYNDICATE_MEMBER_VAILD_SECOND = 8 * 60 * 60;	// 帮派成员列表有效时间

const int MAIL_EXIST_TIME		= 20 * 24 * 60 * 60;	// 邮件保存时间	20天
const int MAX_FIGHT_POKER_NUM	= 5;					// 最大出战卡牌数量

const int GOOSE_TOWER_MAX_FLOOR = 15;					// 大雁塔最多层数
const int GOOSE_TOWER_MAX_PAGE_SIXE = 6;				// 大雁塔每页最多层数
const int GOOSE_TOWER_LEVEL_LIMIT = 20;					// 进入大雁塔的等级限制

const int MINE_MAX_MEMBER_COUNT = 3;					// 矿洞最大成员数量

////////////////////////////////////////////////////////////////////////////////////////////////
// 活动常量 start
const int TIME_OF_DAY_LENGTH	= 1000000;				// 每天时间长度
const int DAY_UTC_SECONDS		= 1 * 24 * 60 * 60;		// 一天的UTC秒
const int SERVER_AWARD_CONFIG_MIN			= 1;		// 服务器多倍奖励最小配置
const int SERVER_AWARD_CONFIG_MAX			= 16;		// 服务器多倍奖励最大配置
const int SERVER_DROP_CHANCE_CONFIG_MIN		= 1;		// 服务器多倍掉落几率最小配置
const int SERVER_DROP_CHANCE_CONFIG_MAX		= 16;		// 服务器多倍掉落几率最大配置
const int SERVER_DROP_NUM_CONFIG_MIN		= 1;		// 服务器多倍掉落数量最小配置
const int SERVER_DROP_NUM_CONFIG_MAX		= 16;		// 服务器多倍掉落数量最大配置
/////////////////////////////////////////////////////////////////////////////////////////
// 常量表使用的常数定义 start
const int		ALL_SERVER_LINE_TYPE	= 99999;				//  不区分线路
const int		ALL_SERVER_GROUP_TYPE	= 99999;				//  不区分服务器组

const int DESIGN_VAS_LIMIT = 5000;	// 策划单笔元宝操作限额

/////////////////////////////////////////////////////////////////////////////////////////
// 排行榜使用的常数定义 start
const int		MAX_RANK_COUNT				= 50;				//  上榜名次
const int		MAX_RECORD_RANK_COUNT		= 10000;			//  数据库有记录的名次
const int		MAX_ARENA_RECORD_RANK_COUNT	= 10000;			//  竞技场数据库有记录的名次
const int		OUT_OF_TOPLIST_RANK			= 999999;			//  未上榜
const int		MASK_TOPLIST_DAILY			= 9999;				// 每日榜更新时间记录掩码

//////////////////////////////////////////////////////////////////////////
// 帮派
const int MAX_SYNDICATE_MEMBER_AMOUNT	= 50;				// 每个帮派50人
const int MAX_SYNDICATE_ELDER_AMOUNT	= 5;				// 每个帮派5个长老
const int MAX_APPLY_SYNDICATE_AMOUNT	= 3;				// 最多向3个帮派发出加入申请
const int APPLY_SYNDICATE_VAILD_SECOND	= 8 * 60 * 60;		// 申请加入帮派有效时间
const int QUIT_SYNDICATE_CD_SECOND		= 1 * 60 * 60;		// 退出帮派后CD时间
const int REJOIN_SYNIDCATE_CD_SECOND	= 2 * 24 * 60 * 60;	// 重新进入原帮派CD时间
const int JOIN_SYNDICATE_3TIMES_SECOND	= 7 * 24 * 60 * 60;	// 多长时间内可以加入3次帮派
const int LEADER_LOGOUT_TIME_BE_CHANGE	= 3 * 24 * 60 * 60;	// 3天不上线就被换掉
const int LOG_IN_OUT_SYNDICATE_TIME		= 7 * 24 * 60 * 60;	// 记录进出帮派时间有效时间
const int MAX_SYNDICATE_ANNOUNCE_LEN	= 76;				// 最大帮派公告长度
const int QUERY_SYNDICATE_LIST_COUNT	= 20;				// 查询帮派时返回列表中帮派数量上限
const int SYN_WORSHIP_TOTAL_LIMIT		= 1000000;			// 帮派膜拜奖励累计和上限

/////////////////////////////////////////////////////////////////////////////////////////
// 竞技场使用的常数定义 start
const int		VIDEO_PATH_SIZE			= 64;				// 战斗录像保存路径长度
const int		ARENA_VIDEO_SAVE_COUNT	= 10;				// 竞技场录像最多保留条数 
const int		ARENA_NO_CD				= 88888888;			// 竞技场无CD
const int		ARENA_BATTLE_TYPE		= 11111;			// 单人竞技场战斗type
const int		MULTI_ARENA_BATTLE_TYPE	= 22222;			// 多人竞技场战斗type
const int		ARENA_DEFAULT_MAX_RANK	= 5000;				// 竞技场默认最高排名
const int		ARENA_AWARD_BASE		= 140;				// 竞技场排名更新奖励系数
const int		ARENA_AWARD_PER_SECOND	= 10;				// 每秒种发放竞技场排名奖励的个数
const int		ARENA_AWARD_LAST_RANK	= 999999;			// 竞技场最后一名默认设置
const int		ARENA_AI_COUNT			= 1000;				// 竞技场AI数量 
const int		ARENA_MULTI_OPEN_COUNT	= 15;				// 多队竞技场开启需要卡牌数

// 竞技场使用的常数定义 end
/////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
// 成就常量 
const int ACHIEVEMENT_BASE_VALUE		= 10000;			// 成就id的基础值
const int ACHIEVEMENT_BRANCH_FINISHED	= 99999999;			// 分支成就全部完成
const int ACHIEVEMENT_NOT_OPENED		= 99999998;			// 成就未开启

/////////////////////////////////////////////////////////////////////////////////////////
// 好友系统的常数定义 start
const int SIGNATURE_MAX_SIZE			= 192;				// 个性签名长度(字节) 
const int MAX_FRIEND_REQUEST_LOAD		= 50;				// 玩家登陆加载的申请好友最大个数
const int MAX_FRIEND_PUSH_COUNT			= 20;				// 好友最多推送个数
const int MAX_FRIEND_REQUEST_COUNT		= 20;				// 好友请求保存个数上限
const int FRIEND_MATCHING_RANGE_LEV1	= 1;				// 好友匹配第一次筛选等级范围
const int FRIEND_MATCHING_RANGE_LEV2	= 5;				// 好友匹配第二次筛选等级范围
const int FRIEND_ONLINE					= 1;				// 好友在线
const int FRIEND_GIFT_GIVEN				= 2;				// 有礼物
const int FRIEND_GIFT_GOT				= 1;				// 礼物已领取
const int FRIEND_GIFT_NONE				= 0;				// 没有礼物
const int FRIEND_REQUESTED				= -1;				// 已经申请好友
const int FRIEND_STRANGER				= 0;				// 陌生人
const int FRIEND_REQUESTER				= 1;				// 申请加好友者
//const int FRIEND_FRIEND				= 2;				// 好友
const int FRIEND_MAX_COUNT				= 50;				// 好友上限
const int FRIEND_PUSH_COUNT				= 10;				// 好友推送数量

/////////////////////////////////////////////////////////////////////////////////////////
// 南天门斗法系统常量
const int CONST_NTM_FIGHT_BATTER_TYPE				= 33333;	// 战斗类型
const int CONST_NTM_FIGHT_FIGHT_PRE_TIME			= 15;		// 战斗准备时间
const int CONST_NTM_FIGHT_PK_DEFEND_TIME			= 10;		// PK保护时间
const int CONST_NTM_FIGHT_CONNECT_SEFEND_TIME		= 30;		// 重连保护时间
const int CONST_NTM_FIGHT_ROOM_MIN_USERNUM			= 5;		// 房间最少人数
const int CONST_NTM_FIGHT_RANK_FIRST_AWARD_RULE_ID	= 11;		// 第一名奖励规则ID
const int CONST_NTM_FIGHT_RANK_SECOND_AWARD_RULE_ID	= 12;		// 第二名奖励规则ID
const int CONST_NTM_FIGHT_RANK_THREE_AWARD_RULE_ID	= 13;		// 第三名奖励规则ID
/////////////////////////////////////////////////////////////////////////////////////////
#endif // end of _GLOBAL_CONSTDEF_HEADER_