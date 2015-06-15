////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan ChuangYou, All Rights Reserved
// Moudle: RelayDatabase.h
// Author: 彭文奇(Peng Wenqi)
// Created: 2014-12-6
////////////////////////////////////////////////////////////////////////
#ifndef _GLOBAL_RELAY_DATABASE_H_
#define _GLOBAL_RELAY_DATABASE_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "./GlobalConstDef.h"
#include "./GlobalStructDef.h"
#include <vector>
#include <map>

// 中转表
enum RELAY_TABLE
{
	RELAY_TABLE_NONE								= 0,
	RELAY_TABLE_BEGIN								= 1,
	RELAY_TABLE_SYNDICATE							= 1,
	RELAY_TABLE_SYNDICATE_MEMBER					= 2,
	RELAY_TABLE_SYNDICATE_MEMBER_APPLY				= 3,
	RELAY_TABLE_MINE								= 4,
	RELAY_TABLE_MINE_MEMBER							= 5,
	RELAY_TABLE_MERCENARY_CAMP						= 6,
	RELAY_TABLE_SYNDICATE_WORSHIP_AWARD				= 7,
	RELAY_TABLE_SYNDICATE_TERRITORY_TROOPS			= 8,
	RELAY_TABLE_SYNDICATE_TERRITORY					= 9,
	RELAY_TABLE_TALK_WORLD							= 10,
	RELAY_TABLE_TALK_SYN							= 11,
	RELAY_TABLE_WARROAD_FIGHT						= 12,
	RELAY_TABLE_TEAM_WARROAD_LOG					= 13,
	RELAY_TABLE_TEAM_WARROAD_AWARD					= 14,
	RELAY_TABLE_TEAM_WARROAD_AWARD_HISTORY			= 15,
	RELAY_TABLE_TEAM_WARROAD_DPS					= 16,
	RELAY_TABLE_TEAM_WARROAD_DPS_HISTORY			= 17,
	RELAY_TABLE_GAME_HISTORY_COMPLETE				= 18,
	RELAY_TABLE_MINE_COLLECT						= 19,
	RELAY_TABLE_SYNDICATE_TERRITORY_FIGHT_LOG		= 20,
	RELAY_TABLE_SYNDICATE_TERRITORY_FIGHT_STATISTICS= 21,
	RELAY_TABLE_SYNDICATE_TERRITORY_FIGHT_TROOPS	= 22,
	RELAY_TABLE_SYNDICATE_GIFT_BOX_LOG				= 23,
	RELAY_TABLE_ARENA_AI							= 24,
	RELAY_TABLE_SYNDICATE_BUFF						= 25,

	RELAY_TABLE_END,
};

// 表操作类型
enum RELAY_OPERATION_TYPE
{
	RELAY_OPERATION_TYPE_UPDATE = 1,			// 更新
	RELAY_OPERATION_TYPE_INSERT,				// 插入
	RELAY_OPERATION_TYPE_DELETE,				// 删除
	RELAY_OPERATION_TYPE_UPDATE_FAILED_SYNC,	// 更新失败同步
	RELAY_OPERATION_TYPE_MODIFY_DATA,			// 指定
};

// 中转结果
enum RELAY_RESULT
{
	RELAY_RESULT_SUCCESS		= 0,	// 成功
	RELAY_RESULT_FAILED			= 1,	// 失败
	RELAY_RESULT_UNKNOW_OPERTAION,		// 未知操作
	RELAY_RESULT_UNKNOW_TABLE,			// 未知表格
	RELAY_RESULT_RS_CLOSED,				// 未连接关系服
};

// 自定义回调类型
enum RELAY_CALLBACK
{
	RELAY_CALLBACK_EMPTY = 0,	// 空回调

	RELAY_CALLBACK_SYNDICATE_CREATE,			// 创建帮派
	RELAY_CALLBACK_SYNDICATE_CREATE_LEADER,		// 创建帮主
	RELAY_CALLBACK_SYNDICATE_APPLY,				// 申请加入帮派
	RELAY_CALLBACK_SYNDICATE_AGREE_APPLY,		// 同意加入帮派
	RELAY_CALLBACK_SYNDICATE_QUIT,				// 退出帮派
	RELAY_CALLBACK_SYNDICATE_KICK,				// 踢出帮派
	RELAY_CALLBACK_SYNDICATE_DISMISS,			// 解散帮派
	RELAY_CALLBACK_SYNDICATE_MODIFY_RANK,		// 职位变更
	RELAY_CALLBACK_SYNDICATE_CHANGE_LEADER,		// 禅让帮主
	RELAY_CALLBACK_SYNDICATE_AUTO_CHANGE_LEADER,// 自动禅让帮主

	RELAY_CALLBACK_MINE_CREATE,					// 创建矿洞
	RELAY_CALLBACK_MINE_CREATE_OWNER,			// 创建矿主
	RELAY_CALLBACK_MINE_UPDATE_POKER,			// 调整卡牌
	RELAY_CALLBACK_MINE_JOIN,					// 加入矿洞
	RELAY_CALLBACK_MINE_RECEIVE,				// 领取矿洞资源
	RELAY_CALLBACK_MERCENARY_CAMP_ADD,			// 添加佣兵
	RELAY_CALLBACK_MERCENARY_CAMP_DEL,			// 删除佣兵
	RELAY_CALLBACK_SYN_WORSHIP,					// 被膜拜
	RELAY_CALLBACK_TERRITORY_SEND_TROOPS,		// 派遣部队
	RELAY_CALLBACK_WARROAD_FIGHT_RECORD,		// 战役战斗记录
	RELAY_CALLBACK_WARROAD_TEAM_COMPLETE,		// 团队战役章节完成
	RELAY_CALLBACK_WARROAD_TEAM_RESET,			// 重置团队战役章节
	RELAY_CALLBACK_WARROAD_TEAM_AWARD_GIVE,		// 战利品分配
	RELAY_CALLBACK_WARROAD_TEAM_AWARD_SYN,		// 战利品信息同步
	RELAY_CALLBACK_SYN_TERRITORY_OCCUPY,		// 占领领地
	RELAY_CALLBACK_SYN_GIFTBOX_AWARD_EXP,		// 帮派礼盒获取经验
	RELAY_CALLBACK_SYN_GIFTBOX_ADD,				// 新增帮派礼盒
	RELAY_CALLBACK_SYN_BUFF_UPDATE,				// 帮派buff更新
};

// 中转头
struct RELAY_HEADER
{
	short	sTableType;			// 表类型		RELAY_TABLE
	short	sOperationType;		// 操作类型		RELAY_OPERATION_TYPE
	short	sResult;			// 结果			RELAY_RESULT
	short	sCallback;			// 自定义回调	RELAY_CALLBACK
	short	sReqLine;			// 发起请求线路	如果是关系服发起则为0
	short	sReqGroup;			// 发起请求线路	如果是跨服发起则为0
	I64		i64DbKey;			// 字段id
	short	sParam;				// short参数
	short	sParam2;			// short参数2
	int		nParam;				// int参数
	I64		i64Param;			// i64参数
};

// 中转字段类型
enum RELAY_FIELD_TYPE
{
	RELAY_FIELD_TYPE_I64 = 1,
	RELAY_FIELD_TYPE_STRING = 2,
};

const int MAX_RELAY_OFFSET = 1012;		// 最大中转偏移量
const int MAX_RELAY_STRING_LENGTH = 255;// 最大字符串长度
const int INVALID_DB_INDEX = -1;		// 无效index

// 插入字段解析后内容
struct RELAY_INSERT_FIELD
{
	int		nFieldType;
	int		nDataIndex;
	I64		i64Data;
	char	szString[256];
};
typedef std::vector<RELAY_INSERT_FIELD> VEC_RELAY_INSERT_FIELD;

// 更新字段解析后内容
struct RELAY_UPDATE_FIELD
{
	int		nFieldType;
	int		nDataIndex;
	I64		i64OldData;
	I64		i64NewData;
	char	szOldString[256];
	char	szNewString[256];
};
typedef std::vector<RELAY_UPDATE_FIELD> VEC_RELAY_UPDATE_FIELD;
typedef std::map<DB_KEY, VEC_RELAY_UPDATE_FIELD> MAP_VEC_UPDATE_RECORD;

// 回调信息结构
struct RELAY_CALLBACK_INFO
{
	short			sReqLine;
	short			sReqGroup;
	RELAY_RESULT	eResult; 
	int				nCallback;
	DB_KEY			idKey;
	short			sParam;
	short			sParam2;
	int				nParam;
	I64				i64Param;
};

////////////////////////////////////////////////////////////////////////
// Description: 获得中转表名
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: const char*
////////////////////////////////////////////////////////////////////////
inline const char* GetRelayTableName(RELAY_TABLE eTable)
{
	switch (eTable)
	{
	case RELAY_TABLE_SYNDICATE:
		return GAME_DB_NAME_SYNDICATE;
		break;
	case RELAY_TABLE_SYNDICATE_MEMBER:
		return GAME_DB_NAME_SYNDICATE_MEMBER;
		break;
	case RELAY_TABLE_SYNDICATE_MEMBER_APPLY:
		return GAME_DB_NAME_SYNDICATE_MEMBER_APPLY;
		break;
	case RELAY_TABLE_MINE:
		return GAME_DB_NAME_MINE;
		break;
	case RELAY_TABLE_MINE_MEMBER:
		return GAME_DB_NAME_MINE_MEMBER;
		break;
	case RELAY_TABLE_MERCENARY_CAMP:
		return GAME_DB_NAME_MERCENARY_CAMP;
		break;
	case RELAY_TABLE_SYNDICATE_WORSHIP_AWARD:
		return GAME_DB_NAME_SYN_WORSHIP_AWARD;
		break;
	case RELAY_TABLE_SYNDICATE_TERRITORY_TROOPS:
		return GAME_DB_NAME_TERRITORY_MEMBER_TROOPS;
		break;
	case RELAY_TABLE_SYNDICATE_TERRITORY:
		return GAME_DB_NAME_TERRITORY;
		break;
	case RELAY_TABLE_SYNDICATE_TERRITORY_FIGHT_LOG:
		return GAME_DB_NAME_TERRITORY_FIGHT_LOG;
		break;
	case RELAY_TABLE_SYNDICATE_TERRITORY_FIGHT_STATISTICS:
		return GAME_DB_NAME_TERRITORY_FIGHT_STATISTICS;
		break;
	case RELAY_TABLE_SYNDICATE_TERRITORY_FIGHT_TROOPS:
		return GAME_DB_NAME_TERRITORY_FIGHT_TROOPS;
		break;
	case RELAY_TABLE_TALK_WORLD:
		return GAME_DB_NAME_TALK_WORLD;
		break;
	case RELAY_TABLE_TALK_SYN:
		return GAME_DB_NAME_TALK_SYN;
		break;
	case RELAY_TABLE_WARROAD_FIGHT:
		return GAME_DB_NAME_WAR_ROAD_FIGHT;
		break;
	case RELAY_TABLE_TEAM_WARROAD_LOG:
		return GAME_DB_NAME_WAR_ROAD_TEAM_LOG;
		break;
	case RELAY_TABLE_TEAM_WARROAD_AWARD:
		return GAME_DB_NAME_WAR_ROAD_TEAM_AWARD;
		break;
	case RELAY_TABLE_TEAM_WARROAD_AWARD_HISTORY:
		return GAME_DB_NAME_WAR_ROAD_TEAM_AWARD_HISTORY;
		break;
	case RELAY_TABLE_TEAM_WARROAD_DPS:
		return GAME_DB_NAME_WAR_ROAD_TEAM_DPS;
		break;
	case RELAY_TABLE_TEAM_WARROAD_DPS_HISTORY:
		return GAME_DB_NAME_WAR_ROAD_TEAM_DPS_HISTORY;
		break;
	case RELAY_TABLE_GAME_HISTORY_COMPLETE:
		return GAME_DB_NAME_GAME_HISTORY_COMPLETE;
		break;
	case RELAY_TABLE_MINE_COLLECT:
		return GAME_DB_NAME_MINE_COLLECT;
		break;
	case RELAY_TABLE_SYNDICATE_GIFT_BOX_LOG:
		return GAME_DB_NAME_SYN_GIFT_BOX_LOG;
		break;
	case RELAY_TABLE_ARENA_AI:
		return GAME_DB_NAME_ARENA_AI;
		break;
	case RELAY_TABLE_SYNDICATE_BUFF:
		return GAME_DB_NAME_SYN_BUFF;
		break;
	default:
		return NULL;
		break;
	}
}

////////////////////////////////////////////////////////////////////////
// Description: 获得中转表加载所有数据sql
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: const char*
////////////////////////////////////////////////////////////////////////
inline const char* GetRelayTableLoadAllSql(RELAY_TABLE eTable)
{
	static char szResult[2048] = "";
	switch (eTable)
	{
	case RELAY_TABLE_SYNDICATE:
		{
			sprintf_s(szResult, sizeof(szResult), "select * from %s where server_group=%d", GAME_DB_NAME_SYNDICATE, g_nServerGroup);
			return szResult;
		}
		break;
	case RELAY_TABLE_SYNDICATE_MEMBER:
		{
			sprintf_s(szResult, sizeof(szResult), "select * from %s where server_group=%d", GAME_DB_NAME_SYNDICATE_MEMBER, g_nServerGroup);
			return szResult;
		}
		break;
	case RELAY_TABLE_SYNDICATE_MEMBER_APPLY:
		{
			sprintf_s(szResult, sizeof(szResult), "select * from %s where server_group=%d", GAME_DB_NAME_SYNDICATE_MEMBER_APPLY, g_nServerGroup);
			return szResult;
		}
		break;
	case RELAY_TABLE_MINE:
		{
			sprintf_s(szResult, sizeof(szResult), "select * from %s where server_group=%d", GAME_DB_NAME_MINE, g_nServerGroup);
			return szResult;
		}
		break;
	case RELAY_TABLE_MINE_MEMBER:
		{
			sprintf_s(szResult, sizeof(szResult), "select * from %s where server_group=%d", GAME_DB_NAME_MINE_MEMBER, g_nServerGroup);
			return szResult;
		}
		break;
	case RELAY_TABLE_MERCENARY_CAMP:
		{
			sprintf_s(szResult, sizeof(szResult), "select * from %s where server_group=%d", GAME_DB_NAME_MERCENARY_CAMP, g_nServerGroup);
			return szResult;
		}
		break;
	case RELAY_TABLE_SYNDICATE_WORSHIP_AWARD:
		{
			sprintf_s(szResult, sizeof(szResult), "select * from %s where server_group=%d", GAME_DB_NAME_SYN_WORSHIP_AWARD, g_nServerGroup);
			return szResult;
		}
		break;
	case RELAY_TABLE_SYNDICATE_TERRITORY_TROOPS:
		{
			sprintf_s(szResult, sizeof(szResult), "select * from %s where server_group=%d", GAME_DB_NAME_TERRITORY_MEMBER_TROOPS, g_nServerGroup);
			return szResult;
		}
		break;
	case RELAY_TABLE_SYNDICATE_TERRITORY:
		{
			sprintf_s(szResult, sizeof(szResult), "select * from %s where server_group=%d", GAME_DB_NAME_TERRITORY, g_nServerGroup);
			return szResult;
		}
		break;
	case RELAY_TABLE_SYNDICATE_TERRITORY_FIGHT_LOG:
		{
			sprintf_s(szResult, sizeof(szResult), "select * from %s where server_group=%d", GAME_DB_NAME_TERRITORY_FIGHT_LOG, g_nServerGroup);
			return szResult;
		}
		break;
	case RELAY_TABLE_SYNDICATE_TERRITORY_FIGHT_STATISTICS:
		{
			sprintf_s(szResult, sizeof(szResult), "select * from %s where server_group=%d", GAME_DB_NAME_TERRITORY_FIGHT_STATISTICS, g_nServerGroup);
			return szResult;
		}
		break;
	case RELAY_TABLE_SYNDICATE_TERRITORY_FIGHT_TROOPS:
		{
			sprintf_s(szResult, sizeof(szResult), "select * from %s where server_group=%d", GAME_DB_NAME_TERRITORY_FIGHT_TROOPS, g_nServerGroup);
			return szResult;
		}
		break;
	case RELAY_TABLE_TALK_WORLD:
		{
			sprintf_s(szResult, sizeof(szResult), "select * from %s where server_group=%d", GAME_DB_NAME_TALK_WORLD, g_nServerGroup);
			return szResult;
		}
		break;
	case RELAY_TABLE_TALK_SYN:
		{
			sprintf_s(szResult, sizeof(szResult), "select * from %s where server_group=%d", GAME_DB_NAME_TALK_SYN, g_nServerGroup);
			return szResult;
		}
		break;
	case RELAY_TABLE_WARROAD_FIGHT:
		{
			sprintf_s(szResult, sizeof(szResult), "select * from %s where server_group=%d", GAME_DB_NAME_WAR_ROAD_FIGHT, g_nServerGroup);
			return szResult;
		}
		break;
	case RELAY_TABLE_TEAM_WARROAD_LOG:
		{
			sprintf_s(szResult, sizeof(szResult), "select * from %s where server_group=%d", GAME_DB_NAME_WAR_ROAD_TEAM_LOG, g_nServerGroup);
			return szResult;
		}
		break;
	case RELAY_TABLE_TEAM_WARROAD_AWARD:
		{
			sprintf_s(szResult, sizeof(szResult), "select * from %s where server_group=%d", GAME_DB_NAME_WAR_ROAD_TEAM_AWARD, g_nServerGroup);
			return szResult;
		}
		break;
	case RELAY_TABLE_TEAM_WARROAD_AWARD_HISTORY:
		{
			sprintf_s(szResult, sizeof(szResult), "select * from %s where server_group=%d", GAME_DB_NAME_WAR_ROAD_TEAM_AWARD_HISTORY, g_nServerGroup);
			return szResult;
		}
		break;
	case RELAY_TABLE_TEAM_WARROAD_DPS:
		{
			sprintf_s(szResult, sizeof(szResult), "select * from %s where server_group=%d", GAME_DB_NAME_WAR_ROAD_TEAM_DPS, g_nServerGroup);
			return szResult;
		}
		break;
	case RELAY_TABLE_TEAM_WARROAD_DPS_HISTORY:
		{
			sprintf_s(szResult, sizeof(szResult), "select * from %s where server_group=%d", GAME_DB_NAME_WAR_ROAD_TEAM_DPS_HISTORY, g_nServerGroup);
			return szResult;
		}
		break;
	case RELAY_TABLE_GAME_HISTORY_COMPLETE:
		{
			sprintf_s(szResult, sizeof(szResult), "select * from %s where server_group=%d", GAME_DB_NAME_GAME_HISTORY_COMPLETE, g_nServerGroup);
			return szResult;
		}
		break;
	case RELAY_TABLE_MINE_COLLECT:
		{
			sprintf_s(szResult, sizeof(szResult), "select * from %s where server_group=%d", GAME_DB_NAME_MINE_COLLECT, g_nServerGroup);
			return szResult;
		}
		break;
	case RELAY_TABLE_SYNDICATE_GIFT_BOX_LOG:
		{
			sprintf_s(szResult, sizeof(szResult), "select * from %s where server_group=%d", GAME_DB_NAME_SYN_GIFT_BOX_LOG, g_nServerGroup);
			return szResult;
		}
		break;
	case RELAY_TABLE_ARENA_AI:
		{
			sprintf_s(szResult, sizeof(szResult), "select * from %s where server_group=%d", GAME_DB_NAME_ARENA_AI, g_nServerGroup);
			return szResult;
		}
		break;
	case RELAY_TABLE_SYNDICATE_BUFF:
		{
			sprintf_s(szResult, sizeof(szResult), "select * from %s where server_group=%d", GAME_DB_NAME_SYN_BUFF, g_nServerGroup);
			return szResult;
		}
		break;
	default:
		return NULL;
		break;
	}
}

////////////////////////////////////////////////////////////////////////
// Description: 获得中转表加载单个数据sql
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: const char*
////////////////////////////////////////////////////////////////////////
inline const char* GetRelayTableLoadSingleSql(RELAY_TABLE eTable, DB_KEY idKey)
{
	static char szResult[2048] = "";
	switch (eTable)
	{
	case RELAY_TABLE_SYNDICATE:
		{
			sprintf_s(szResult, sizeof(szResult), "select * from %s where id=%I64d limit 1", GAME_DB_NAME_SYNDICATE, idKey);
			return szResult;
		}
		break;
	case RELAY_TABLE_SYNDICATE_MEMBER:
		{
			sprintf_s(szResult, sizeof(szResult), "select * from %s where user_id=%I64d limit 1", GAME_DB_NAME_SYNDICATE_MEMBER, idKey);
			return szResult;
		}
		break;
	case RELAY_TABLE_SYNDICATE_MEMBER_APPLY:
		{
			sprintf_s(szResult, sizeof(szResult), "select * from %s where id=%I64d limit 1", GAME_DB_NAME_SYNDICATE_MEMBER_APPLY, idKey);
			return szResult;
		}
		break;
	case RELAY_TABLE_MINE:
		{
			sprintf_s(szResult, sizeof(szResult), "select * from %s where id=%I64d limit 1", GAME_DB_NAME_MINE, idKey);
			return szResult;
		}
		break;
	case RELAY_TABLE_MINE_MEMBER:
		{
			sprintf_s(szResult, sizeof(szResult), "select * from %s where id=%I64d limit 1", GAME_DB_NAME_MINE_MEMBER, idKey);
			return szResult;
		}
		break;
	case RELAY_TABLE_MERCENARY_CAMP:
		{
			sprintf_s(szResult, sizeof(szResult), "select * from %s where mercenary_id=%I64d limit 1", GAME_DB_NAME_MERCENARY_CAMP, idKey);
			return szResult;
		}
		break;
	case RELAY_TABLE_SYNDICATE_WORSHIP_AWARD:
		{
			sprintf_s(szResult, sizeof(szResult), "select * from %s where id=%I64d limit 1", GAME_DB_NAME_SYN_WORSHIP_AWARD, idKey);
			return szResult;
		}
		break;
	case RELAY_TABLE_SYNDICATE_TERRITORY_TROOPS:
		{
			sprintf_s(szResult, sizeof(szResult), "select * from %s where troopsid=%I64d limit 1", GAME_DB_NAME_TERRITORY_MEMBER_TROOPS, idKey);
			return szResult;
		}
		break;
	case RELAY_TABLE_SYNDICATE_TERRITORY:
		{
			sprintf_s(szResult, sizeof(szResult), "select * from %s where index=%I64d limit 1", GAME_DB_NAME_TERRITORY, idKey);
			return szResult;
		}
		break;
	case RELAY_TABLE_SYNDICATE_TERRITORY_FIGHT_LOG:
		{
			sprintf_s(szResult, sizeof(szResult), "select * from %s where index=%I64d limit 1", GAME_DB_NAME_TERRITORY_FIGHT_LOG, idKey);
			return szResult;
		}
		break;
	case RELAY_TABLE_SYNDICATE_TERRITORY_FIGHT_STATISTICS:
		{
			sprintf_s(szResult, sizeof(szResult), "select * from %s where index=%I64d limit 1", GAME_DB_NAME_TERRITORY_FIGHT_STATISTICS, idKey);
			return szResult;
		}
		break;
	case RELAY_TABLE_SYNDICATE_TERRITORY_FIGHT_TROOPS:
		{
			sprintf_s(szResult, sizeof(szResult), "select * from %s where index=%I64d limit 1", GAME_DB_NAME_TERRITORY_FIGHT_TROOPS, idKey);
			return szResult;
		}
		break;
	case RELAY_TABLE_TALK_WORLD:
		{
			sprintf_s(szResult, sizeof(szResult), "select * from %s where id=%I64d limit 1", GAME_DB_NAME_TALK_WORLD, idKey);
			return szResult;
		}
		break;
	case RELAY_TABLE_TALK_SYN:
		{
			sprintf_s(szResult, sizeof(szResult), "select * from %s where id=%I64d limit 1", GAME_DB_NAME_TALK_SYN, idKey);
			return szResult;
		}
		break;
	case RELAY_TABLE_WARROAD_FIGHT:
		{
			sprintf_s(szResult, sizeof(szResult), "select * from %s where id=%I64d limit 1", GAME_DB_NAME_WAR_ROAD_FIGHT, idKey);
			return szResult;
		}
		break;
	case RELAY_TABLE_TEAM_WARROAD_LOG:
		{
			sprintf_s(szResult, sizeof(szResult), "select * from %s where id=%I64d limit 1", GAME_DB_NAME_WAR_ROAD_TEAM_LOG, idKey);
			return szResult;
		}
		break;
	case RELAY_TABLE_TEAM_WARROAD_AWARD:
		{
			sprintf_s(szResult, sizeof(szResult), "select * from %s where id=%I64d limit 1", GAME_DB_NAME_WAR_ROAD_TEAM_AWARD, idKey);
			return szResult;
		}
		break;
	case RELAY_TABLE_TEAM_WARROAD_AWARD_HISTORY:
		{
			sprintf_s(szResult, sizeof(szResult), "select * from %s where id=%I64d limit 1", GAME_DB_NAME_WAR_ROAD_TEAM_AWARD_HISTORY, idKey);
			return szResult;
		}
		break;
	case RELAY_TABLE_TEAM_WARROAD_DPS:
		{
			sprintf_s(szResult, sizeof(szResult), "select * from %s where id=%I64d limit 1", GAME_DB_NAME_WAR_ROAD_TEAM_DPS, idKey);
			return szResult;
		}
		break;
	case RELAY_TABLE_TEAM_WARROAD_DPS_HISTORY:
		{
			sprintf_s(szResult, sizeof(szResult), "select * from %s where id=%I64d limit 1", GAME_DB_NAME_WAR_ROAD_TEAM_DPS_HISTORY, idKey);
			return szResult;
		}
		break;
	case RELAY_TABLE_GAME_HISTORY_COMPLETE:
		{
			sprintf_s(szResult, sizeof(szResult), "select * from %s where id=%I64d limit 1", GAME_DB_NAME_GAME_HISTORY_COMPLETE, idKey);
			return szResult;
		}
		break;
	case RELAY_TABLE_MINE_COLLECT:
		{
			sprintf_s(szResult, sizeof(szResult), "select * from %s where user_id=%I64d limit 1", GAME_DB_NAME_MINE_COLLECT, idKey);
			return szResult;
		}
		break;
	case RELAY_TABLE_SYNDICATE_GIFT_BOX_LOG:
		{
			sprintf_s(szResult, sizeof(szResult), "select * from %s where id=%I64d limit 1", GAME_DB_NAME_SYN_GIFT_BOX_LOG, idKey);
			return szResult;
		}
		break;
	case RELAY_TABLE_ARENA_AI:
		{
			sprintf_s(szResult, sizeof(szResult), "select * from %s where id=%I64d limit 1", GAME_DB_NAME_ARENA_AI, idKey);
			return szResult;
		}
		break;
	case RELAY_TABLE_SYNDICATE_BUFF:
		{
			sprintf_s(szResult, sizeof(szResult), "select * from %s where id=%I64d limit 1", GAME_DB_NAME_SYN_BUFF, idKey);
			return szResult;
		}
		break;
	default:
		return NULL;
		break;
	}
}

////////////////////////////////////////////////////////////////////////
// Description: 获得中转表主键索引index
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: int
////////////////////////////////////////////////////////////////////////
inline int GetRelayTablePrimary(RELAY_TABLE eTable)
{
	switch (eTable)
	{
	case RELAY_TABLE_SYNDICATE:
		return SYNDICATE_DATA_ID;
		break;
	case RELAY_TABLE_SYNDICATE_MEMBER:
		return SYNDICATE_MEMBER_DATA_USER_ID;
		break;
	case RELAY_TABLE_SYNDICATE_MEMBER_APPLY:
		return SYNDICATE_MEMBER_APPLY_DATA_ID;
		break;
	case RELAY_TABLE_MINE:
		return MINE_DATA_ID;
		break;
	case RELAY_TABLE_MINE_MEMBER:
		return MINE_MEMBER_DATA_ID;
		break;
	case RELAY_TABLE_MERCENARY_CAMP:
		return MERCENARY_CAMP_DATA_MERCENARY_ID;
		break;
	case RELAY_TABLE_SYNDICATE_WORSHIP_AWARD:
		return SYN_WORSHIP_AWARD_ID;
		break;
	case RELAY_TABLE_SYNDICATE_TERRITORY_TROOPS:
		return TERRITORY_MEMBER_TROOPS_DATA_ID;
		break;
	case RELAY_TABLE_SYNDICATE_TERRITORY:
		return TERRITORY_DATA_INDEX;
		break;
	case RELAY_TABLE_SYNDICATE_TERRITORY_FIGHT_LOG:
		return TERRITORY_FIGHT_LOG_DATA_INDEX;
		break;
	case RELAY_TABLE_SYNDICATE_TERRITORY_FIGHT_STATISTICS:
		return TERRITORY_FIGHT_STATISTICS_DATA_INDEX;
		break;
	case RELAY_TABLE_SYNDICATE_TERRITORY_FIGHT_TROOPS:
		return TERRITORY_FIGHT_TROOPS_DATA_INDEX;
		break;
	case RELAY_TABLE_TALK_WORLD:
		return TALK_WORLD_DATA_ID;
		break;
	case RELAY_TABLE_TALK_SYN:
		return TALK_SYN_DATA_ID;
		break;
	case RELAY_TABLE_WARROAD_FIGHT:
		return WAR_ROAD_FIGHT_DATA_ID;
		break;
	case RELAY_TABLE_TEAM_WARROAD_LOG:
		return WAR_ROAD_TEAM_LOG_DATA_ID;
		break;
	case RELAY_TABLE_TEAM_WARROAD_AWARD:
		return WAR_ROAD_TEAM_AWARD_DATA_ID;
		break;
	case RELAY_TABLE_TEAM_WARROAD_AWARD_HISTORY:
		return WAR_ROAD_TEAM_AWARD_HISTORY_DATA_ID;
		break;
	case RELAY_TABLE_TEAM_WARROAD_DPS:
		return WAR_ROAD_TEAM_DPS_DATA_ID;
		break;
	case RELAY_TABLE_TEAM_WARROAD_DPS_HISTORY:
		return WAR_ROAD_TEAM_DPS_HISTORY_DATA_ID;
		break;
	case RELAY_TABLE_GAME_HISTORY_COMPLETE:
		return GAME_HISTORY_COMPLETE_DATA_ID;
		break;
	case RELAY_TABLE_MINE_COLLECT:
		return MINE_COLLECT_DATA_USER_ID;
		break;
	case RELAY_TABLE_SYNDICATE_GIFT_BOX_LOG:
		return SYN_GIFT_BOX_LOG_DATA_ID;
		break;
	case RELAY_TABLE_ARENA_AI:
		return ARENA_AI_DATA_ID;
		break;
	case RELAY_TABLE_SYNDICATE_BUFF:
		return SYN_BUFF_DATA_ID;
		break;
	default:
		return INVALID_DB_INDEX;
		break;
	}
}

////////////////////////////////////////////////////////////////////////
// Description: 获得中转表索引键1 index
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: int
////////////////////////////////////////////////////////////////////////
inline int GetRelayTableKeyIndex1(RELAY_TABLE eTable)
{
	switch (eTable)
	{
	case RELAY_TABLE_SYNDICATE_MEMBER:
		return SYNDICATE_MEMBER_DATA_SYNDICATE_ID;
		break;
	case RELAY_TABLE_SYNDICATE_MEMBER_APPLY:
		return SYNDICATE_MEMBER_APPLY_DATA_USERID;
		break;
	case RELAY_TABLE_MINE_MEMBER:
		return MINE_MEMBER_DATA_USER_ID;
		break;
	case RELAY_TABLE_MERCENARY_CAMP:
		return MERCENARY_CAMP_DATA_OWNER_ID;
		break;
	case RELAY_TABLE_SYNDICATE_WORSHIP_AWARD:
		return SYN_WORSHIP_AWARD_USER_ID;
		break;
	case RELAY_TABLE_SYNDICATE_TERRITORY_TROOPS:
		return TERRITORY_MEMBER_TROOPS_DATA_TERRITORY_ID;
		break;
	case RELAY_TABLE_SYNDICATE_TERRITORY:
		return TERRITORY_DATA_ID;
		break;
	case RELAY_TABLE_SYNDICATE_TERRITORY_FIGHT_LOG:
		return TERRITORY_FIGHT_LOG_DATA_TERRITORY_ID;
		break;
	case RELAY_TABLE_SYNDICATE_TERRITORY_FIGHT_STATISTICS:
		return TERRITORY_FIGHT_STATISTICS_DATA_ID;
		break;
	case RELAY_TABLE_SYNDICATE_TERRITORY_FIGHT_TROOPS:
		return TERRITORY_FIGHT_TROOPS_DATA_TERRITORY_ID;
		break;
	case RELAY_TABLE_TALK_SYN:
		return TALK_SYN_DATA_SYN_ID;
		break;
	case RELAY_TABLE_WARROAD_FIGHT:
		return WAR_ROAD_FIGHT_DATA_WAR_KEY;
		break;
	case RELAY_TABLE_TEAM_WARROAD_LOG:
		return WAR_ROAD_TEAM_LOG_DATA_SYNDICATE_ID;
		break;
	case RELAY_TABLE_TEAM_WARROAD_AWARD:
		return WAR_ROAD_TEAM_AWARD_DATA_SYNDICATE_ID;
		break;
	case RELAY_TABLE_TEAM_WARROAD_AWARD_HISTORY:
		return WAR_ROAD_TEAM_AWARD_HISTORY_DATA_SYNDICATE_ID;
		break;
	case RELAY_TABLE_TEAM_WARROAD_DPS:
		return WAR_ROAD_TEAM_DPS_DATA_LOG_ID;
		break;
	case RELAY_TABLE_TEAM_WARROAD_DPS_HISTORY:
		return WAR_ROAD_TEAM_DPS_HISTORY_DATA_CHAPTER;
		break;
	case RELAY_TABLE_GAME_HISTORY_COMPLETE:
		return GAME_HISTORY_COMPLETE_DATA_TYPE;
		break;
	case RELAY_TABLE_SYNDICATE_GIFT_BOX_LOG:
		return SYN_GIFT_BOX_LOG_DATA_SYNDICATE_ID;
		break;
	case RELAY_TABLE_SYNDICATE_BUFF:
		return SYN_BUFF_DATA_SYNDICATE_ID;
		break;
	default:
		return INVALID_DB_INDEX;
		break;
	}
}

////////////////////////////////////////////////////////////////////////
// Description: 获得中转表索引键2 index
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: int
////////////////////////////////////////////////////////////////////////
inline int GetRelayTableKeyIndex2(RELAY_TABLE eTable)
{
	switch (eTable)
	{
	case RELAY_TABLE_SYNDICATE_MEMBER_APPLY:
		return SYNDICATE_MEMBER_APPLY_DATA_SYNID;
		break;
	case RELAY_TABLE_MINE_MEMBER:
		return MINE_MEMBER_DATA_MINE_ID;
		break;
	case RELAY_TABLE_MERCENARY_CAMP:
		return MERCENARY_CAMP_DATA_SYNDICATE_ID;
		break;
	case RELAY_TABLE_SYNDICATE_WORSHIP_AWARD:
		return SYN_WORSHIP_AWARD_AWARD_TYPE;
		break;
	case RELAY_TABLE_SYNDICATE_TERRITORY_TROOPS:
		return TERRITORY_MEMBER_TROOPS_DATA_SYNDICATE_ID;
		break;
	case RELAY_TABLE_SYNDICATE_TERRITORY:
		return TERRITORY_DATA_OCCUPIER;
		break;
	case RELAY_TABLE_TEAM_WARROAD_AWARD:
		return WAR_ROAD_TEAM_AWARD_DATA_USER_ID;
		break;
	case RELAY_TABLE_TEAM_WARROAD_AWARD_HISTORY:
		return WAR_ROAD_TEAM_AWARD_HISTORY_DATA_USER_ID;
		break;
	case RELAY_TABLE_SYNDICATE_BUFF:
		return SYN_BUFF_DATA_TYPE;
		break;
	default:
		return INVALID_DB_INDEX;
		break;
	}
}

#endif // end of _GLOBAL_RELAY_DATABASE_H_