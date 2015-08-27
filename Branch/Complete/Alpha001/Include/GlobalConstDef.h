////////////////////////////////////////////////////////////////////////
// Import : 全局文件。常量定义。
// Moudle : GlobalConstDef.h
// Author : 陈建军(Chen Jianjun)
// Create : 2015-6-19
////////////////////////////////////////////////////////////////////////
#ifndef _GLOBAL_CONSTDEF_H_
#define _GLOBAL_CONSTDEF_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>

extern char g_szServerName[64];				// 服务器名
extern int  g_nServerLine;					// 服务器线路号
extern int  g_nServerGroup;					// 服务器组号
extern int	g_nServerStartTime;				// 服务器开启时间精确到天
extern std::string g_strConstDatabaseName;	// 常量表数据库名
extern std::string g_strGameDatabaseName;	// 游戏服数据库名
extern std::string g_strAccountDatabaseName;// 账号服数据库名

const int	MAX_PACKETSIZE		= 1024;							// 网络消息包尺寸
const int	MAX_MESSAGESIZE		= MAX_PACKETSIZE + 40;			// 内部消息包尺寸

const int	NAME_SIZE			= 32;							// 角色名长度
const int	SYN_ANNOUNCE_SIZE	= 256;							// 帮派公告长度
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
const int	MAX_ONLINE_USER_COUNT				= 2000;									// 最大在线人数限制

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

/////////////////////////////////////////////////////////////////////////////////////////
// 常量表使用的常数定义 start
const int		ALL_SERVER_LINE_TYPE	= 99999;				//  不区分线路
const int		ALL_SERVER_GROUP_TYPE	= 99999;				//  不区分服务器组

const int DESIGN_VAS_LIMIT = 5000;	// 策划单笔元宝操作限额

/////////////////////////////////////////////////////////////////////////////////////////
#endif // end of _GLOBAL_CONSTDEF_H_