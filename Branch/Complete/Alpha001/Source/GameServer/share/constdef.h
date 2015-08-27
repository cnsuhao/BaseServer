////////////////////////////////////////////////////////////////////////
// Import : 共享文件。常量定义。
// Moudle : define.h 
// Author : 陈建军(Chen Jianjun)
// Create : 2015-6-19
// Warning：*字符串常量统一使用static const char*定义, 只有需要给字符串数组赋初值的才用宏
////////////////////////////////////////////////////////////////////////

#ifndef _MAPGROUP_SHARE_CONST_DEF_H_
#define _MAPGROUP_SHARE_CONST_DEF_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "./EnumDef.h"

// 服务器标题
#ifdef MYDEBUG
static const char* GAMESERVER_TITLE = "GameServer:[%s] Group:[%d] Line:[%d] PID:[%u] SVN:[%d] Debug";
#else
static const char* GAMESERVER_TITLE = "GameServer:[%s] Group:[%d] Line:[%d] PID:[%u] SVN:[%d] Release";
#endif

// 服务器配置文件
static const char* GAMESERVER_FILENAME = "GameServer.ini";	

// 对话框消息行数
const int	WINDOW_TEXT_SIZE = 9;
//////////////////////////////////////////////////////////////////////

// 控制变量
const int	CLOSETHREAD_MILLISECS					= 30000;			// 等待线程关闭的毫秒数

//////////////////////////////////////////////////////////////////////
const int	THREADDELAY_MS							= 400;				// 等待内部消息的最大时间
const int	SOCKETKERNEL_ONTIMER_MS					= 1000;				// 网络线程的ONTIMER频率
const int	LOGINKERNEL_ONTIMER_MS					= 333;				// 登陆线程的ONTIMER频率
const int	GAMEKERNEL_ONTIMER_MS					= 1000;				// 游戏线程的ONTIMER频率
const int	RELATIONKERNEL_ONTIMER_MS				= 1000;				// 关系线程的ONTIMER频率
const int	AIKERNEL_ONTIMER_MS						= 1000;				// AI  线程的ONTIMER频率

const int	ONTIMER_MS_ROLLBACK_MS					= 5000;				// 心跳发生回滚阀值


const int	LOG_TIMEOUT_SOCKET_PROCESS				= 100;				// 网络线程ontimer日志超时时间
const int	LOG_TIMEOUT_LOGIN_PROCESS				= 100;				// 登陆线程ontimer日志超时时间
const int	LOG_TIMEOUT_GAME_PROCESS				= 100;				// 游戏线程ontimer日志超时时间
const int	LOG_TIMEOUT_RELATION_PROCESS			= 100;				// 关系线程ontimer日志超时时间
const int	LOG_TIMEOUT_AI_PROCESS					= 100;				// AI线程  ontimer日志超时时间

const int	ONTIMER_LOGIN_THREAD_ONLINE_STAT		= 5;				// 登陆线程 性能统计 间隔
const int	PER_ONTIMER_LOGIN_ENTER_COUNT			= 8;				// 登陆线程 每个心跳间隔8个登陆名额
const int	ONTIMER_LOGIN_THREAD_KICK_DEAD			= 3600;				// 登陆线程 踢出超时 间隔
const int	TIMEOUT_LOGIN_THREAD_KICK_DEAD			= 36000;			// 登陆线程 玩家超时秒（10分钟）

static const char* SYSTEM_NAME 						= "SYSTEM";			// 广播消息时代表“系统”的名字串
const int	DBSTR_SIZE								= 256;				// 数据库INI串长度

//////////////////////////////////////////////////////////////////////
// 核心常量
const OBJID PLAYER_ID_FIRST							= 10000000;			// Player的第一个ID, 1000W起
const OBJID MAX_ID_DEFINE							= (OBJID)-1;

const int	LOGIN_USER_LIST_LIMIT					= 5;				// 多角色系统角色个数

static const char* LUA_FILE_PATH					= "script/";
static const char* LUA_LIST_FILE					= "lualist.txt";
static const char* LUA_ERROR_KEY					= "LuaErrorKey";
const int LUA_CUSTOM_ERROR							= 99999;			// 自定义的lua错误返回值

const int MONEY_STORE_THRESHOLD						= 999999;			// 货币默认入库阀值
const int SYN_LOG_MAX_COUNT							= 300;				// 帮派日志最大条数
const int SYN_LOG_MAX_PAGE_SIZE						= 15;				// 帮派日志一页的最大条数

#endif // end of _MAPGROUP_SHARE_CONST_DEF_H_
