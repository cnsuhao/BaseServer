////////////////////////////////////////////////////////////////////////
// Import : 全局文件。结构体定义。
// Moudle : GlobalStructDef.h
// Author : 陈建军(Chen Jianjun)
// Create : 2015-6-19
////////////////////////////////////////////////////////////////////////
#ifndef _GLOBAL_STRUCTDEF_H_
#define _GLOBAL_STRUCTDEF_H_

#include "GlobalEnumDef.h"
#include "GlobalConstDef.h"

#include <map>
#include <vector>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct MSG_BASE
{
	unsigned short	unMsgSize;
	unsigned short	unMsgType;
	char buffer[MAX_PACKETSIZE];
};

// 跨服消息模块
const int MSG_CROSS_HEAD_SIZE = sizeof(SOCKET_ID) + sizeof(int);
struct MSG_CROSS
{
	SOCKET_ID	idGameServerSocket;
	int			nServerGroup;

	union Data
	{
		struct Connect
		{
			MSG_NUM_4BIT	nResult;
			MSG_NUM_8BIT	i64Time;
			MSG_NUM_4BIT	nGroup;
			MSG_STR_64BIT	szKey;
		}connect;

		struct Action
		{
			MSG_NUM_2BIT	sAction;
			MSG_NUM_2BIT	sData;
			MSG_NUM_4BIT	nData1;
			MSG_NUM_4BIT	nData2;
		}action;

		struct Table
		{
			MSG_NUM_1BIT	buf[1];
		}table;
	} data;
};

// 服务器信息
struct SERVER_INFO
{
	int		nID;
	char	szAccIP[16];
	int		nPort;
	int		nOnline;
	int		nCloseFlag;
	unsigned int unUpdateSecond;	// 上一次更新秒数
};

// 全局游戏对象接口类
class IGameObject
{
public:
	virtual DB_KEY				GetID(void)	const							{return m_id;}
	virtual GAME_OBJECT_TYPE	GetObjectType(void) const					{return m_eObjectType;}
	virtual bool				IsObjectType(GAME_OBJECT_TYPE eType) const	{return ((eType & m_eObjectType) != GAME_OBJECT_TYPE_NONE);}
protected:
	DB_KEY				m_id;
	GAME_OBJECT_TYPE	m_eObjectType;
};

// 服务期间帮派通信结构体
struct ST_SERVER_SYNDICATE_MSG
{
	short sAction;
	short sResult;

	OBJID idSyndicate;
	OBJID idActor;
	OBJID idTarget;

	union
	{
		struct  
		{
			char 	szSyndicateName[NAME_SIZE];
			char 	szAnnounce[SYN_ANNOUNCE_SIZE];
		}ReqCreateSyndicate;

	};
};
#endif // end of _GLOBAL_STRUCTDEF_H_
