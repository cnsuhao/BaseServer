////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan ChuangYou, All Rights Reserved
// Moudle: RelayDatabase.h
// Author: ������(Peng Wenqi)
// Created: 2014-12-6
////////////////////////////////////////////////////////////////////////
#ifndef _GLOBAL_CROSS_RELAY_DATABASE_H_
#define _GLOBAL_CROSS_RELAY_DATABASE_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "./GlobalConstDef.h"
#include "./GlobalStructDef.h"
#include "./RelayDatabase.h"
#include <vector>
#include <map>
#include "DatabaseDefine.h"

// ��ת��
enum CROSS_RELAY_TABLE
{
	CROSS_RELAY_TABLE_NONE							= 0,
	CROSS_RELAY_TABLE_BEGIN							= 1,
	CROSS_RELAY_TABLE_ROOM							= 1,
	CROSS_RELAY_TABLE_ROOM_MEMBER,
	CROSS_RELAY_TABLE_NTM_FIGHT_LOG,

	CROSS_RELAY_TABLE_END,
};

// �Զ���ص�����
enum CROSS_RELAY_CALLBACK
{
	CROSS_RELAY_CALLBACK_EMPTY = 0,	// �ջص�
	CROSS_RELAY_CALLBACK_CREATE_ROOM,			// ��������
	CROSS_RELAY_CALLBACK_CREATE_ROOM_MEMBER,	// ������Ա
	CROSS_RELAY_CALLBACK_JOIN_ROOM_MEMBER,		// �����Ա
	CROSS_RELAY_CALLBACK_LEAVE_ROOM_MEMBER,		// �뿪��Ա
	CROSS_RELAY_CALLBACK_CHANGE_OWNER,			// ��������
	CROSS_RELAY_CALLBACK_DESTORY_ROOM,			// ���ٷ���
	CROSS_RELAY_CALLBACK_CHANGE_ROOM_MEMBER,	// ��������
};

////////////////////////////////////////////////////////////////////////
// Description: �����ת����
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: const char*
////////////////////////////////////////////////////////////////////////
inline const char* GetRelayTableName(CROSS_RELAY_TABLE eTable)
{
	switch (eTable)
	{
	case CROSS_RELAY_TABLE_ROOM:
		return GAME_DB_NAME_CROSS_ROOM;
		break;
	case CROSS_RELAY_TABLE_ROOM_MEMBER:
		return GAME_DB_NAME_CROSS_ROOM_MEMBER;
		break;
	case CROSS_RELAY_TABLE_NTM_FIGHT_LOG:
		return GAME_DB_NAME_CROSS_NTM_FIGHT_LOG;
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
inline const char* GetRelayTableLoadAllSql(CROSS_RELAY_TABLE eTable)
{
	static char szResult[2048] = "";
	switch (eTable)
	{
	case CROSS_RELAY_TABLE_ROOM:
		{
			sprintf_s(szResult, sizeof(szResult), "select * from %s", GAME_DB_NAME_CROSS_ROOM);
			return szResult;
		}
		break;
	case CROSS_RELAY_TABLE_ROOM_MEMBER:
		{
			sprintf_s(szResult, sizeof(szResult), "select * from %s", GAME_DB_NAME_CROSS_ROOM_MEMBER);
			return szResult;
		}
		break;
	case CROSS_RELAY_TABLE_NTM_FIGHT_LOG:
		{
			sprintf_s(szResult, sizeof(szResult), "select * from %s", GAME_DB_NAME_CROSS_NTM_FIGHT_LOG);
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
inline const char* GetRelayTableLoadSingleSql(CROSS_RELAY_TABLE eTable, DB_KEY idKey)
{
	static char szResult[2048] = "";
	switch (eTable)
	{
	case CROSS_RELAY_TABLE_ROOM:
		{
			sprintf_s(szResult, sizeof(szResult), "select * from %s where line=%I64d limit 1", GAME_DB_NAME_CROSS_ROOM, idKey);
			return szResult;
		}
		break;
	case CROSS_RELAY_TABLE_ROOM_MEMBER:
		{
			sprintf_s(szResult, sizeof(szResult), "select * from %s where line=%I64d limit 1", GAME_DB_NAME_CROSS_ROOM_MEMBER, idKey);
			return szResult;
		}
		break;
	case CROSS_RELAY_TABLE_NTM_FIGHT_LOG:
		{
			sprintf_s(szResult, sizeof(szResult), "select * from %s where line=%I64d limit 1", GAME_DB_NAME_CROSS_NTM_FIGHT_LOG, idKey);
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
inline int GetRelayTablePrimary(CROSS_RELAY_TABLE eTable)
{
	switch (eTable)
	{
	case CROSS_RELAY_TABLE_ROOM:
		return CROSS_ROOM_DATA_ID;
		break;
	case CROSS_RELAY_TABLE_ROOM_MEMBER:
		return CROSS_ROOM_MEMBER_DATA_USER_ID;
		break;
	case CROSS_RELAY_TABLE_NTM_FIGHT_LOG:
		return CROSS_NTM_FIGHT_LOG_DATA_USER_ID;
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
inline int GetRelayTableKeyIndex1(CROSS_RELAY_TABLE eTable)
{
	switch (eTable)
	{
	case CROSS_RELAY_TABLE_ROOM:
		return CROSS_ROOM_DATA_TYPE;
		break;
	case CROSS_RELAY_TABLE_ROOM_MEMBER:
		return CROSS_ROOM_MEMBER_DATA_ROOM_ID;
		break;
	case CROSS_RELAY_TABLE_NTM_FIGHT_LOG:
		return CROSS_NTM_FIGHT_LOG_DATA_RANK;
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
inline int GetRelayTableKeyIndex2(CROSS_RELAY_TABLE eTable)
{
	switch (eTable)
	{
	case CROSS_RELAY_TABLE_ROOM:
		return CROSS_ROOM_DATA_LINE;
		break;
	default:
		return INVALID_DB_INDEX;
		break;
	}
}

#endif // end of _GLOBAL_CROSS_RELAY_DATABASE_H_