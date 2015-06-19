////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2012, WuHan ChuangYou, All Rights Reserved
// Moudle: ConstDef.h
// Author: 彭文奇(Peng Wenqi)
// Created: 2012-10-30
// 
// !!! 注意 !!!
//	1. 本文件用于定义游戏服务器全局常量
//  2. 字符串常量统一使用static const char*定义, 只有需要给字符串数组赋初值的才用宏
//////////////////////////////////////////////////////////////////////////
#ifndef _MAPGROUP_SHARE_CONST_DEF_H_
#define _MAPGROUP_SHARE_CONST_DEF_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../../common/common.h"
#include "./EnumDef.h"

static const char* GAMESERVER_TITLE = "[%u] GameServer Name[%s] Line[%d] Group[%d] SVN:[%d]";	// 服务器标题

//////////////////////////////////////////////////////////////////////
// 界面常量
const int	TEXTWINDOW_SIZE		= 15;			// 消息窗行数

//////////////////////////////////////////////////////////////////////
// 控制变量
const int	THREADDELAY_MS							= 400;		// 等待内部消息的最大时间
const int	SOCKETKERNEL_ONTIMER_MS					= 1000;		// 网络线程的ONTIMER频率
const int	LOGINKERNEL_ONTIMER_MS					= 333;		// 登陆线程的ONTIMER频率
const int	GAMEKERNEL_ONTIMER_MS					= 1000;		// 游戏线程的ONTIMER频率
const int	RELATIONKERNEL_ONTIMER_MS				= 1000;		// 关系线程的ONTIMER频率
const int	AIKERNEL_ONTIMER_MS						= 1000;		// AI  线程的ONTIMER频率

const int	ONTIMER_MS_ROLLBACK_MS					= 5000;		// 心跳发生回滚阀值
const int	CLOSETHREAD_MILLISECS					= 30000;	// 等待线程关闭的毫秒数

const int	LOG_TIMEOUT_SOCKET_PROCESS				= 100;		// 网络线程ontimer日志超时时间
const int	LOG_TIMEOUT_LOGIN_PROCESS				= 100;		// 登陆线程ontimer日志超时时间
const int	LOG_TIMEOUT_GAME_PROCESS				= 100;		// 游戏线程ontimer日志超时时间
const int	LOG_TIMEOUT_RELATION_PROCESS			= 100;		// 关系线程ontimer日志超时时间
const int	LOG_TIMEOUT_AI_PROCESS					= 100;		// AI线程  ontimer日志超时时间

const int	ONTIMER_LOGIN_THREAD_ONLINE_STAT		= 5;		// 登陆线程 性能统计 间隔
const int	ONTIMER_LOGIN_THREAD_KICK_DEAD			= 17;		// 登陆线程 踢出死人 间隔
const int	PER_ONTIMER_LOGIN_ENTER_COUNT			= 8;		// 登陆线程 每个心跳间隔8个登陆名额
const int	TIMEOUT_LOGIN_THREAD_KICK_DEAD			= 600;		// 登陆线程 玩家超时秒

static const char* SYSTEM_NAME 			= "SYSTEM";			// 广播消息时代表“系统”的名字串
static const char* CONFIG_FILENAME		= "GameServer.ini";	
const int	DBSTR_SIZE				= 256;				// 数据库INI串长度

const int	REBUILDLISTENDELAYSEC = 60;
const int	IPSTRSIZE = 16;
const int	RECVREPEATTIMES = 3;


//////////////////////////////////////////////////////////////////////
// 核心常量
const OBJID PLAYER_ID_FIRST		= 10000000;			// Player的第一个ID, 1000W起
const OBJID MAX_ID_DEFINE		= (OBJID)-1;

const int	LOGIN_USER_LIST_LIMIT = 5;			// 多角色系统角色个数

const int	MAX_DROP_NUM			= 8;	// 一次掉落最多生成数量
const int	BATTLE_MAX_ROUND		= 3;	// 战斗最大轮次
const int	BATTLE_MAX_FIGHTER		= 5;	// 战斗最大成员数

const int BATTLE_ATK_CAMP = 100;	// 战斗 攻击方
const int BATTLE_DEF_CAMP = 200;	// 战斗 防御方
const int BATTLE_ROUND_BASE = 10;	// 战斗轮次基准

const int BATTLE_FORCE_END_DELAY_SECOND = 60 * 60;	// 战斗强制结束等待时间
const int BATTLE_CHECK_ERROR_DATA = 1;				// 战斗检测最大误差值

static const char* LUA_FILE_PATH	= "script/";
static const char* LUA_LIST_FILE	= "lualist.txt";
static const char* LUA_ERROR_KEY	= "LuaErrorKey";
const int LUA_CUSTOM_ERROR			= 99999;			// 自定义的lua错误返回值

const int MONEY_STORE_THRESHOLD = 999999;	// 货币默认入库阀值
const int SYN_LOG_MAX_COUNT		= 300;		// 帮派日志最大条数
const int SYN_LOG_MAX_PAGE_SIZE = 15;		// 帮派日志一页的最大条数

////////////////////////////////////////////////////////////////////////////////////////////////
// 掩码ID段定义，10000以前表示按位掩码，10000以后表示计数掩码
const int CONST_BIT_MASKID_INTERVAL			= 5000;			// 按位掩码ID区间	服务器使用段(1 - 5000)		策划使用段(5000 - 10000)
const int CONST_COMPUTATION_MASKID_BEGIN	= 10000;		// 计数掩码ID开始
const int CONST_COMPUTATION_MASKID_INTERVAL	= 20000;		// 计数掩码ID区间	服务器使用段(10000 - 20000）策划使用段(20000以后)
const int CONST_DEFULT_MASK_ENDTIME			= 2000000000;	// 掩码默认结束时间(2033年5月18日 11:33:20)

//////////////////////////////////////////////////////////////////////////
const int MAX_PAY_CONFIG_ID = 30;		// 配置充值最大id
const int SERVER_PAY_CONFIG_ID = 999;	// 内部充值配置id

const int CONST_MAX_WARROAD_RECORD_NUM	= 5;				// 战役记录最大数量
const int CONST_MAX_WARROAD_STAR		= 3;				// 战役最大星级
const int CONST_MAX_WARROAD_AWARD_APPLY_NUM		= 1;		// 团队战役战利品最大申请数
const int CONST_MAX_WARROAD_AWARD_HISTORY_NUM	= 40;		// 团队战役战利品历史记录数目
const int CONST_MAX_WARROAD_SERVER_DPS_NUM		= 10;		// 团队战役章节全服排名返回数

const int CONST_WARROAD_ERROR			= 99999;			// 战役错误码

// 好友邀请
const int INVITE_CODE_MAX_LEN			= 12;				// 邀请码的最大长度
const int INVITE_VAS_BASE				= 100;				// 可领取的最小元宝返利
const int LOGIN_AWARD_MAX_POWER			= 100;				// 最大可领取的体力值

//////////////////////////////////////////////////////////////////////////
// 竞技场常量
const int ARENA_MAX_TARGET_COUNT		= 3;				// 竞技场最大对手个数

//////////////////////////////////////////////////////////////////////////
// 公会领地战
const int TERRITORY_MAX_MONSTER_TROOPS_ID			= 1000;				// 默认防守部队最大部队番号
const int TERRITORY_BATTLE_TYPE						= 55555;			// 公会战战斗type

const int VIP_VALUE_UP_LIMIT						= 9999;				// VIP值上限

//////////////////////////////////////////////////////////////////////////
const int MAX_ITEM_HINT_TEXT						= 256;				// 物品提示内容字符数
const int MAX_ITEM_HINT_COUNT						= 50;				// 物品提示信息最大数量

const int CONST_BUFF_DEFAULT_KEEP_TIME				= 999999;			// buff默认持续时间(永久)
const int CONST_SYN_BUFF_VALID_TIME					= 24 * 60 * 60;		// 帮派buff 提供和享受最小入会时间

#endif // end of _MAPGROUP_SHARE_CONST_DEF_H_
