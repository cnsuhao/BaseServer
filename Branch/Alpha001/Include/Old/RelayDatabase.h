////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan ChuangYou, All Rights Reserved
// Moudle: RelayDatabase.h
// Author: ������(Peng Wenqi)
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

// ��ת��
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

// ���������
enum RELAY_OPERATION_TYPE
{
	RELAY_OPERATION_TYPE_UPDATE = 1,			// ����
	RELAY_OPERATION_TYPE_INSERT,				// ����
	RELAY_OPERATION_TYPE_DELETE,				// ɾ��
	RELAY_OPERATION_TYPE_UPDATE_FAILED_SYNC,	// ����ʧ��ͬ��
	RELAY_OPERATION_TYPE_MODIFY_DATA,			// ָ��
};

// ��ת���
enum RELAY_RESULT
{
	RELAY_RESULT_SUCCESS		= 0,	// �ɹ�
	RELAY_RESULT_FAILED			= 1,	// ʧ��
	RELAY_RESULT_UNKNOW_OPERTAION,		// δ֪����
	RELAY_RESULT_UNKNOW_TABLE,			// δ֪���
	RELAY_RESULT_RS_CLOSED,				// δ���ӹ�ϵ��
};

// �Զ���ص�����
enum RELAY_CALLBACK
{
	RELAY_CALLBACK_EMPTY = 0,	// �ջص�

	RELAY_CALLBACK_SYNDICATE_CREATE,			// ��������
	RELAY_CALLBACK_SYNDICATE_CREATE_LEADER,		// ��������
	RELAY_CALLBACK_SYNDICATE_APPLY,				// ����������
	RELAY_CALLBACK_SYNDICATE_AGREE_APPLY,		// ͬ��������
	RELAY_CALLBACK_SYNDICATE_QUIT,				// �˳�����
	RELAY_CALLBACK_SYNDICATE_KICK,				// �߳�����
	RELAY_CALLBACK_SYNDICATE_DISMISS,			// ��ɢ����
	RELAY_CALLBACK_SYNDICATE_MODIFY_RANK,		// ְλ���
	RELAY_CALLBACK_SYNDICATE_CHANGE_LEADER,		// ���ð���
	RELAY_CALLBACK_SYNDICATE_AUTO_CHANGE_LEADER,// �Զ����ð���

	RELAY_CALLBACK_MINE_CREATE,					// ������
	RELAY_CALLBACK_MINE_CREATE_OWNER,			// ��������
	RELAY_CALLBACK_MINE_UPDATE_POKER,			// ��������
	RELAY_CALLBACK_MINE_JOIN,					// �����
	RELAY_CALLBACK_MINE_RECEIVE,				// ��ȡ����Դ
	RELAY_CALLBACK_MERCENARY_CAMP_ADD,			// ���Ӷ��
	RELAY_CALLBACK_MERCENARY_CAMP_DEL,			// ɾ��Ӷ��
	RELAY_CALLBACK_SYN_WORSHIP,					// ��Ĥ��
	RELAY_CALLBACK_TERRITORY_SEND_TROOPS,		// ��ǲ����
	RELAY_CALLBACK_WARROAD_FIGHT_RECORD,		// ս��ս����¼
	RELAY_CALLBACK_WARROAD_TEAM_COMPLETE,		// �Ŷ�ս���½����
	RELAY_CALLBACK_WARROAD_TEAM_RESET,			// �����Ŷ�ս���½�
	RELAY_CALLBACK_WARROAD_TEAM_AWARD_GIVE,		// ս��Ʒ����
	RELAY_CALLBACK_WARROAD_TEAM_AWARD_SYN,		// ս��Ʒ��Ϣͬ��
	RELAY_CALLBACK_SYN_TERRITORY_OCCUPY,		// ռ�����
	RELAY_CALLBACK_SYN_GIFTBOX_AWARD_EXP,		// ������л�ȡ����
	RELAY_CALLBACK_SYN_GIFTBOX_ADD,				// �����������
	RELAY_CALLBACK_SYN_BUFF_UPDATE,				// ����buff����
};

// ��תͷ
struct RELAY_HEADER
{
	short	sTableType;			// ������		RELAY_TABLE
	short	sOperationType;		// ��������		RELAY_OPERATION_TYPE
	short	sResult;			// ���			RELAY_RESULT
	short	sCallback;			// �Զ���ص�	RELAY_CALLBACK
	short	sReqLine;			// ����������·	����ǹ�ϵ��������Ϊ0
	short	sReqGroup;			// ����������·	����ǿ��������Ϊ0
	I64		i64DbKey;			// �ֶ�id
	short	sParam;				// short����
	short	sParam2;			// short����2
	int		nParam;				// int����
	I64		i64Param;			// i64����
};

// ��ת�ֶ�����
enum RELAY_FIELD_TYPE
{
	RELAY_FIELD_TYPE_I64 = 1,
	RELAY_FIELD_TYPE_STRING = 2,
};

const int MAX_RELAY_OFFSET = 1012;		// �����תƫ����
const int MAX_RELAY_STRING_LENGTH = 255;// ����ַ�������
const int INVALID_DB_INDEX = -1;		// ��Чindex

// �����ֶν���������
struct RELAY_INSERT_FIELD
{
	int		nFieldType;
	int		nDataIndex;
	I64		i64Data;
	char	szString[256];
};
typedef std::vector<RELAY_INSERT_FIELD> VEC_RELAY_INSERT_FIELD;

// �����ֶν���������
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

// �ص���Ϣ�ṹ
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
// Description: �����ת����
// Arguments:
// Author: ������(Peng Wenqi)
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
// Description: �����ת�������������sql
// Arguments:
// Author: ������(Peng Wenqi)
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
// Description: �����ת����ص�������sql
// Arguments:
// Author: ������(Peng Wenqi)
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
// Description: �����ת����������index
// Arguments:
// Author: ������(Peng Wenqi)
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
// Description: �����ת��������1 index
// Arguments:
// Author: ������(Peng Wenqi)
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
// Description: �����ת��������2 index
// Arguments:
// Author: ������(Peng Wenqi)
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