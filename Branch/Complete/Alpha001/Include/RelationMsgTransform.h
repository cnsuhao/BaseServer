////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan ChuangYou, All Rights Reserved
// Moudle: RelationMsgTransform.h
//		   将游戏服客户端消息与关系服处理消息协议号进行转换
// Author: 彭文奇(Peng Wenqi)
// Created: 2014-11-12
////////////////////////////////////////////////////////////////////////
#ifndef _GLOBAL_RELATION_MSG_TRANSFORM_H_
#define _GLOBAL_RELATION_MSG_TRANSFORM_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "./GlobalEnumDef.h"

////////////////////////////////////////////////////////////////////////
// Description: 游戏服消息向关系服消息转换
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: int
////////////////////////////////////////////////////////////////////////
inline int TransformMsgTypeGameToRelation(int nGameMsgType)
{
	switch (nGameMsgType)
	{
	case _MSG_GAME_RELAY_DATABASE:			return _MSG_RELATION_PROCESS_REALY_DATABASE; break;
	case _MSG_GAME_CROSS_RELAY_DATABASE:	return _MSG_CROSS_REALY_DATABASE; break;

	case _MSG_GAME_TALK:					return _MSG_RELATION_DIRCET_OTHER_TALK; break;
	case _MSG_GAME_NEWCARD:					return _MSG_RELATION_PROCESS_NEWCARD; break;
	case _MSG_GAME_ONLINE_INFO:				return _MSG_RELATION_PROCESS_ONLINE_INFO; break;
	case _MSG_GAME_SYN_SERVER:				return _MSG_RELATION_PROCESS_SYN_SERVER; break;
	case _MSG_GAME_MAIL_LIST:				return _MSG_RELATION_PROCESS_MAIL; break;
	case _MSG_GAME_FRIEND_ACT:				return _MSG_RELATION_PROCESS_FRIEND; break;	
	case _MSG_GAME_TOPLIST_COMMON:			return _MSG_RELATION_PROCESS_TOPLIST; break;
	case _MSG_GAME_ARENA_ACT:				return _MSG_RELATION_PROCESS_ARENA_ACT; break;
	case _MSG_GAME_ACHIEVEMENT:				return _MSG_RELATION_PROCESS_ACHIEVEMENT; break;
	case _MSG_GAME_ARENA_LOG:				return _MSG_RELATION_PROCESS_ARENA_LOG; break;
	case _MSG_GAME_TERRITORY_FIGHT:			return _MSG_RELATION_PROCESS_TERRITORY_FIGHT;break;
	case _MSG_GAME_MINE_SERVER:				return _MSG_RELATION_PROCESS_MINE_SERVER; break;
	case _MSG_GAME_MARKS_INFO:				return _MSG_RELATION_PROCESS_MARKSINFO; break;
	default:								return nGameMsgType;break;
	}
}

////////////////////////////////////////////////////////////////////////
// Description: 关系服消息向游戏服消息转换
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: int
////////////////////////////////////////////////////////////////////////
inline int TransformMsgTypeRelationToGame(int nRelationMsgType)
{
	switch (nRelationMsgType)
	{
	case _MSG_RELATION_PROCESS_REALY_DATABASE:		return _MSG_GAME_RELAY_DATABASE; break;
	case _MSG_CROSS_REALY_DATABASE:					return _MSG_GAME_CROSS_RELAY_DATABASE; break;

	case _MSG_RELATION_DIRCET_OTHER_TALK:			return _MSG_GAME_TALK; break;
	case _MSG_RELATION_PROCESS_NEWCARD:				return _MSG_GAME_NEWCARD; break;
	case _MSG_RELATION_PROCESS_ONLINE_INFO:			return _MSG_GAME_ONLINE_INFO; break;
	case _MSG_RELATION_PROCESS_SYN_SERVER:			return _MSG_GAME_SYN_SERVER; break;
	case _MSG_RELATION_PROCESS_MAIL:				return _MSG_GAME_MAIL_LIST; break;
	case _MSG_RELATION_PROCESS_FRIEND:				return _MSG_GAME_FRIEND_ACT; break;
	case _MSG_RELATION_PROCESS_TOPLIST:				return _MSG_GAME_TOPLIST_COMMON; break;
	case _MSG_RELATION_PROCESS_ARENA_ACT:			return _MSG_GAME_ARENA_ACT; break;
	case _MSG_RELATION_PROCESS_ARENA_LOG:			return _MSG_GAME_ARENA_LOG; break;
	case _MSG_RELATION_PROCESS_ACHIEVEMENT:			return _MSG_GAME_ACHIEVEMENT; break;
	case _MSG_RELATION_PROCESS_TERRITORY_FIGHT:		return _MSG_GAME_TERRITORY_FIGHT; break;
	case _MSG_RELATION_PROCESS_MINE_SERVER:			return _MSG_GAME_MINE_SERVER; break;
	case _MSG_RELATION_PROCESS_MARKSINFO:			return _MSG_GAME_MARKS_INFO; break;
	default:										return nRelationMsgType; break;
	}
}

#endif // end of _GLOBAL_RELATION_MSG_TRANSFORM_H_

