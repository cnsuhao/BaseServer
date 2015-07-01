////////////////////////////////////////////////////////////////////////
// Import : ȫ���ļ����ṹ�嶨�塣
// Moudle : GlobalStructDef.h
// Author : �½���(Chen Jianjun)
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

// �����Ϣģ��
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

// ��������Ϣ
struct SERVER_INFO
{
	int		nID;
	char	szAccIP[16];
	int		nPort;
	int		nOnline;
	int		nCloseFlag;
	unsigned int unUpdateSecond;	// ��һ�θ�������
};

// ȫ����Ϸ����ӿ���
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

// �����ڼ����ͨ�Žṹ��
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
