////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2012, WuHan ChuangYou, All Rights Reserved
// Moudle: GlobalStructDef.h
// Author: ������(Peng Wenqi)
// Created: 2012-11-19
////////////////////////////////////////////////////////////////////////
#ifndef _GLOBAL_STRUCTDEF_HEADER_
#define _GLOBAL_STRUCTDEF_HEADER_

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

// ���������Ϣ
struct USER_ONLINE_INFO
{
	OBJID	idUser;
	OBJID	idAccount;
	int		nLine;
	int		nAccountType;

	// ����ͨ��bForce����ǿ���޸�
	char	szUserName[NAME_SIZE];
	char	szSignature[SIGNATURE_MAX_SIZE];
	char	szAddress[MAX_ADDRESS_SIZE];

	// ����ͨ���仯�޸�, Ĭ��Ϊ0
	int		nLev;
	int		nMaxScore;
	int		nLookFace;
	int		nSex;
	int		nLookFaceFrame;
	int		nBirthday;
	int		nGlamour;

	// ������½ʱ��ͱ��
	int		nLastLoginTime;
	int		nYesterdayLogin;
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

// ��������Ա��Ϣ
struct ST_BLACKLIST_MEMBER_INFO
{
	MSG_NUM_4BIT	idUser;
	MSG_STR_32BIT	szName;
	MSG_NUM_4BIT	nLevel;
	MSG_NUM_4BIT	nLookFace;
	MSG_NUM_4BIT	nLookfaceFrame;
};

// �鿴������������Ϣ
typedef struct  
{
	OBJID				idTarget;
	MSG_STR_32BIT		szSyndicate;					// ��������
	MSG_STR_64BIT		szSignature;					// ����ǩ�� 			
}ST_FRIEND_PUSH_INTERFACE_INFO;

// ���������Ϣ
typedef struct  
{
	OBJID				idUser;
	MSG_NUM_4BIT		nStatus;						// �������״̬��-1��ʾ�Ѿ�����������Ӻ��ѣ�0��ʾİ������ң�1��ʾ���Լ�������Ӻ����������ң�2�Ѿ��Ǻ�����)
	MSG_NUM_4BIT		nLev;							// �ȼ�
	MSG_NUM_4BIT		nLookFace;						// ͷ��
	MSG_NUM_4BIT		nFigntingCapacity;				// ���п�����ս����
	MSG_NUM_4BIT		nLastLoginTime;					// ���һ�ε�¼ʱ��UTC��
	MSG_STR_32BIT		szUserName;						// �������
	MSG_STR_32BIT		szSyndicate;					// ��������
	MSG_STR_64BIT		szSignature;					// ����ǩ�� 
}ST_FRIEND_SEARCH_INFO;

typedef struct  
{
	int		nFriendShipPoint;				// �������
	int		nGiveUserGift;					// ��ҵ�����״̬
	int		nUserLastGotTime;				// ����ϴ���ȡ�����������YYMMDD
	int		nGiveFriendGift;				// ��������״̬
	int		nFriendLastGotTime;				// ������ȡ����������������YYMMDD
	int		nLev;							// �ȼ�
	int		nLookFace;						// ͷ��
	int		nFigntingCapacity;				// ս��
	int		nExitTime;						// ����ʱ��UTC
	int		nYesterdayLogin;				// ���յ�½���
	char	szFriendName[NAME_SIZE];		// ��������
	char	szSignature[SIGNATURE_MAX_SIZE];// ����ǩ��

	short	sSex;							// �Ա�
	short	sLookFaceFrame;					// ͷ���
	int		nBirthday;						// ����	YYYYMMDD
	char	szAddress[MAX_ADDRESS_SIZE];	// ���ڵ�
}MyFriendInfo;

typedef struct  
{
	int		nLev;								// �ȼ�
	int		nFigntingCapacity;					// ս��
	int		nLookFace;							// ͷ��
	int		nRequestTime;						// ����ʱ��
	int		nLastLogin;							// �����¼ʱ��
	char	szUserName[NAME_SIZE];				// �������
	char	szSignatrure[SIGNATURE_MAX_SIZE];	// ����ǩ��

	short	sSex;							// �Ա�
	short	sLookFaceFrame;					// ͷ���
	int		nBirthday;						// ����	YYYYMMDD
	char	szAddress[MAX_ADDRESS_SIZE];	// ���ڵ�
} MyFriendRequestInfo;

//////////////////////////////////////////////////////////////////////////

// ��Ʒ��Ϣ
struct ST_GOODS_INFO
{
	unsigned int	unItemIndex;		// ��Ʒλ��(��1��ʼ)
	unsigned int 	unItemType;			// ��Ʒtype
	unsigned int 	unItemNum;			// ��Ʒ����
	unsigned int 	unPrice;			// ����
	unsigned int 	unMoneyType;		// ��������
	unsigned int	unCurNum;			// ��Ʒ��ǰ����
	unsigned int	unDiscount;			// ��Ʒ�ۿ�
};

//////////////////////////////////////////////////////////////////////////
// ������ ���濨�����ݽṹ
typedef struct  
{
	MSG_NUM_8BIT	iPokerID;			// ����id
	MSG_NUM_4BIT	nPosition;			// ����λ��(1�ţ�2�ţ�3��)
}Arena_Save_Poker;
typedef std::vector<Arena_Save_Poker>		VEC_ARENA_SAVE_POKER;
typedef VEC_ARENA_SAVE_POKER::iterator		ITER_VEC_ARENA_SAVE_POKER;

// �������������
typedef struct 
{
	OBJID	idUser;					// ���id
	int		nLookFace;				// ͷ��
	int		nLookFaceFrame;			// ͷ���
	int		nLev;					// �ȼ�
	int		nRank;					// ����
	int		nLastRank;				// ��������
	int		nWinCount;				// ʤ����
	int		nFightingCapacity;		// ս����
	char	szUserName[NAME_SIZE];	// �������
}TOPLIST_ARENA_USER_INFO;
typedef std::map<int, TOPLIST_ARENA_USER_INFO>		MAP_TOPLIST_ARENA_USER_INFO;
typedef MAP_TOPLIST_ARENA_USER_INFO::iterator		ITER_MAP_TOPLIST_ARENA_USER_INFO;

// ��������ҵĿ�������
typedef struct  
{
	OBJID	idPokerType;			// ��������id
	int		nLev;					// ���Ƽ���
	int		nColor;					// ������ɫ
	int		nStar;					// �����Ǽ�
	int		nPosition;				// λ�ã��ڼ��ӣ�
}TOPLIST_ARENA_POKER_INFO;
typedef std::map<OBJID, TOPLIST_ARENA_POKER_INFO>	MAP_TOPLIST_ARENA_POKER_INFO;
typedef MAP_TOPLIST_ARENA_POKER_INFO::iterator		ITER_MAP_TOPLIST_ARENA_POKER_INFO;

// ���id������ӳ��
typedef struct  
{
	int nRank;						// ��������
	int nLastRank;					// ��������
}TOPLIST_RANK_INFO;
typedef std::map<OBJID, TOPLIST_RANK_INFO>			MAP_TARGETER_RANK_INFO;
typedef MAP_TARGETER_RANK_INFO::iterator			ITER_MAP_TARGETER_RANK_INFO;
// �����빫��idӳ��
typedef struct
{
	OBJID idSyndicate;				// ����
	int nData;						// ���������� 
}TOPLIST_SYNDICATE_INFO;
typedef std::map<int, TOPLIST_SYNDICATE_INFO>		MAP_TOPLIST_SYNDICATE_INFO;
typedef MAP_TOPLIST_SYNDICATE_INFO::iterator		ITER_MAP_TOPLIST_SYNDICATE_INFO;

// ���а����ͨ������
typedef struct  
{
	OBJID	idUser;					// ���id
	int		nLookFace;				// ���ͷ��
	int		nLookFaceFrame;			// ͷ���
	int		nLev;					// ��ҵȼ�
	int		nData;					// ��������
	int		nLastRank;				// ��������
	char	szUserName[NAME_SIZE];	// �������
}TOPLIST_COMMON_USER_INFO;
typedef std::map<int, TOPLIST_COMMON_USER_INFO>		MAP_TOPLIST_COMMON_USER_INFO;
typedef MAP_TOPLIST_COMMON_USER_INFO::iterator		ITER_MAP_TOPLIST_COMMON_USER_INFO;

// ���а�ϵͳ ͨ����Ϣ��Ϣ(ս����+��Դ�Ӷᣩ
typedef struct  
{
	OBJID			idUser;			// ���id
	MSG_NUM_4BIT	nRank;			// ����
	MSG_NUM_4BIT	nLev;			// �ȼ�
	MSG_NUM_4BIT	nLookFace;		// ͷ��
	MSG_NUM_4BIT	nLookFaceFrame;	// ͷ���
	MSG_NUM_4BIT	nData;			// ����������
	MSG_STR_32BIT	szUserName;		// �������
	MSG_STR_32BIT	szSyndicate;	// ��������
}Msg_TopList_Common_Info;

// ������
struct MSG_GOOSE_TOWER
{
	MSG_NUM_2BIT	sFloor;					// ����
	MSG_NUM_2BIT	sGainAward;				// ������ȡ���(0:δ��ȡ, 1:��ȡ)
	MSG_STR_32BIT	szDefName;				// ����С�������
	MSG_STR_32BIT	szDefSynName;			// ����С�Ӱ�����
	MSG_NUM_4BIT	nDefLookFace;			// ����С��ͷ��
	MSG_NUM_2BIT	sDefLev;				// ����С�ӵȼ�
	MSG_NUM_2BIT	sDefUserLookFaceFrame;	// ����С��ͷ���
	MSG_NUM_8BIT	i64PokerID1;			// ����1
	MSG_NUM_8BIT	i64PokerID2;			// ����2
	MSG_NUM_8BIT	i64PokerID3;			// ����3
	MSG_NUM_8BIT	i64PokerID4;			// ����4
	MSG_NUM_8BIT	i64PokerID5;			// ����5
};
//////////////////////////////////////////////////////////////////////////

// �Թ���Ϣ
struct ST_PUZZLE_INFO
{
	MSG_NUM_4BIT nPuzzleType;	// �Թ�����
	MSG_NUM_4BIT nDiffcult;		// �Թ��Ѷ�
	MSG_NUM_4BIT nPuzzleFloor;	// ����
	MSG_NUM_4BIT nFightNo;		// ս�����к�
	MSG_NUM_4BIT nLastPuzzle;	// ��һ������
	MSG_NUM_4BIT nCurPuzzle;	// ��ǰ����
	MSG_NUM_4BIT nProgress;		// ����
	MSG_NUM_4BIT nBegTime;		// ��ʼʱ��(UTC)
	MSG_NUM_8BIT i64PokerID1;	// ����1
	MSG_NUM_8BIT i64PokerID2;	// ����2
	MSG_NUM_8BIT i64PokerID3;	// ����3
	MSG_NUM_8BIT i64PokerID4;	// ����4
	MSG_NUM_8BIT i64PokerID5;	// ����5
};

// �Թ�BUFF��Ϣ
struct ST_PUZZLE_BUFF_INFO
{
	MSG_NUM_4BIT nBuffType;		// BUFF����
	MSG_NUM_4BIT nPuzzleType;	// ����
	MSG_NUM_4BIT nDifficult;	// �Ѷ�
	MSG_NUM_4BIT nPuzzleFloor;	// ���
	MSG_NUM_4BIT nFightNo;		// ս�����к�
	MSG_NUM_4BIT nTimeDay;		// ����
};

struct ST_PUZZLE_BUFF_TYPE_INFO
{
	MSG_NUM_4BIT  nBuffType;			// BUFF����
	MSG_NUM_4BIT  nBuffValue;			// BUFFֵ
	MSG_NUM_4BIT  nBuffEffect;			// BUFF��Ч����
	MSG_STR_32BIT szBuffName;			// BUFF����
};

// ������ϵͳ
typedef struct  
{
	int		nPosition;					// λ��
	I64		iPokerID;					// ����id

}ARENA_POKER_BATTLE_INFO;

// ��ս��¼����
typedef struct  
{
	OBJID				idTarget;					// ����id
	MSG_NUM_2BIT		nType;						// ���������ͣ�1���ӣ�2��ӣ�
	MSG_NUM_2BIT		nFightType;					// ս�����ͣ�1��ս��2����ս��
	MSG_NUM_4BIT		nResult;					// ս�������1Ӯ��2�䣩
	MSG_NUM_4BIT		nRankChange;				// ���α䶯��
	MSG_NUM_4BIT		nTime;						// ս��ʱ��
	MSG_NUM_4BIT		nLev;						// �ȼ�
	MSG_NUM_4BIT		nLookFace;					// ͷ��(ʮ��λ�Ǳ߿�)
	MSG_STR_32BIT		szTargetName;				// ��������
	MSG_STR_64BIT		szVideo;					// ��ս��¼¼���ַ ���� 64
}Arena_Log;
typedef std::vector<Arena_Log>					VEC_ARENA_LOG;
typedef VEC_ARENA_LOG::iterator					ITER_VEC_ARENA_LOG;

// �ʼ���Ʒ
struct MAIL_AWARD_DATA
{
	int		nAwardType;	// ��ƷType
	int		nAwardNum;	// ��Ʒ����
};
typedef std::vector<MAIL_AWARD_DATA> VEC_MAIL_AWARD;

// �ʼ��б�
struct MSG_MAIL_LIST
{
	MSG_NUM_8BIT	i64MailID;	// �ʼ�ID
	MSG_STR_32BIT	szTitle;	// �ʼ�����
	MSG_STR_32BIT	szSender;	// ����������
	MSG_NUM_4BIT	nSendTime;	// ���ʼ�ʱ��
	MSG_NUM_4BIT	nStatus;	// �ʼ�״̬(0:δ��, 1:�Ѷ�)
};
typedef std::vector<MSG_MAIL_LIST>				VEC_MAIL_LIST;
typedef VEC_MAIL_LIST::iterator					ITER_VEC_MAIL_LIST;
typedef VEC_MAIL_LIST::const_iterator			CITER_VEC_MAIL_LIST;


// �󶴿ͻ�����Ϣ
struct ST_MINE_CLIENT_INFO
{
	OBJID	idMine;								// ��ID
	OBJID   idMember1;							// �󶴳�Ա1
	OBJID	idMember2;							// �󶴳�Ա2
	OBJID	idMember3;							// �󶴳�Ա3
	int		nModel1;							// ģ��1(������Ա1)
	int		nModel2;							// ģ��2(������Ա2)
	int		nModel3;							// ģ��3(������Ա3)
	int		nType;								// ������
	int		nScale;								// �󶴹�ģ
	int		nSpeed;								// �ɼ��ٶ�
	int		nResource;							// �ۼ���Դ
	int		nVasTotal;							// �ۼ���ʯ
	int		nEndTime;							// ����ʱ��
	int		nMineReason;						// ����Դ
	int		nIsFinish;							// �Ƿ����
};

// ��Ĥ�ݽ���
struct MSG_SYN_WORSHIP_AWARD
{
	MSG_NUM_4BIT nAwardType;
	MSG_NUM_4BIT nAwardTotal;		
};
typedef std::vector<MSG_SYN_WORSHIP_AWARD> VEC_SYN_WORSHIP_AWARD;


// ����־�б���Ϣ
struct MSG_MINE_LOG_LIST_INFO
{
	MSG_NUM_8BIT		i64LogID;						// ��־ID
	MSG_NUM_4BIT		nMineType;						// ������
	MSG_NUM_4BIT		nMineScale;						// �󶴹�ģ
	MSG_NUM_4BIT		nAtkID;							// ������ID
	MSG_STR_32BIT		szAtkName;						// �����߽�ɫ��
	MSG_NUM_4BIT		nBegTime;						// �ӶῪʼʱ��
	MSG_NUM_4BIT		nVasLost;						// ��ʧ��ʯ
	MSG_NUM_4BIT		nResLost;						// ��ʧ��Դ
	MSG_NUM_4BIT		nPowerAward;					// ר����������
	MSG_NUM_4BIT		nDefResult;						// ���ؽ��(0:��, 1:Ӯ)
	MSG_NUM_4BIT		nEndState;						// �Ӷ����״̬(0:û����, 1:����)
};
typedef std::vector<MSG_MINE_LOG_LIST_INFO>		VEC_MINE_LOG_LIST_INFO;

struct MSG_MINE_FIGHTER_INFO
{
	MSG_STR_32BIT			szName;			// ս������
	MSG_NUM_4BIT			nLev;			// ս���ߵȼ�
	MSG_NUM_4BIT			nLookface;		// ս����ͷ��
	MSG_NUM_4BIT			nLookfaceFrame;	// ս����ͷ���
};
typedef std::vector<MSG_MINE_FIGHTER_INFO>		VEC_MSG_MINE_FIGHTER_INFO;

// ����־��Ϣ
struct MSG_MINE_BATTLE_INFO
{
	MSG_NUM_8BIT		i64BattleID;					// ս��ID
	MSG_NUM_8BIT		i64DefPoker1;					// ���ط�����1
	MSG_NUM_8BIT		i64DefPoker2;					// 
	MSG_NUM_8BIT		i64DefPoker3;					// 
	MSG_NUM_8BIT		i64DefPoker4;					// 
	MSG_NUM_8BIT		i64DefPoker5;					// ���ط�����5

	MSG_NUM_4BIT		nDefResult;						// ���ؽ��(0:��, 1:Ӯ)

	MSG_NUM_8BIT		i64AtkPoker1;					// ����������1
	MSG_NUM_8BIT		i64AtkPoker2;					// 
	MSG_NUM_8BIT		i64AtkPoker3;					// 
	MSG_NUM_8BIT		i64AtkPoker4;					// 
	MSG_NUM_8BIT		i64AtkPoker5;					// ����������5

	MSG_STR_64BIT		szVideoAddr;					// ¼���ַ
};
typedef std::vector<MSG_MINE_BATTLE_INFO>		VEC_MINE_BATTLE_INFO;

// �������л��Ϣ
struct ACTIVITY_CONFIG_RUNNING_INFO
{
	int nType;			// �����
	int nStartSecond;	// ���ʼʱ��(utc)
	int nEndSecond;		// �����ʱ��(utc)
	int nBeginAction;	// ���ʼ�����ű�
	int nEndAction;		// ����������ű�
	int nEnterAction;	// �ͻ��˴�������ű�
	int nExitAction;	// �ͻ��˴����˳��ű�
	int nParam1;
	int nParam2;
};

//////////////////////////////////////////////////////////////////////////
// �ɾ�ϵͳ 
typedef struct 
{
	OBJID	idAchievement;		// �ɾ�id
	int		nType;				// �ɾ�����
	int		nProcess;			// �ɾͽ���
	int		nGoal;				// Ŀ����� 
}USER_ACHIEVEMENT_INFO;
typedef std::map<int, USER_ACHIEVEMENT_INFO>		MAP_USER_ACHIEVEMENT_INFO;
typedef MAP_USER_ACHIEVEMENT_INFO::iterator			ITER_MAP_USER_ACHIEVEMENT_INFO;
typedef MAP_USER_ACHIEVEMENT_INFO::const_iterator	CITER_MAP_USER_ACHIEVEMENT_INFO;

//////////////////////////////////////////////////////////////////////////
// ���������Ϣ
struct ST_TALK_USER_INFO
{
	OBJID	idUser;					// ���ID
	char	szUserName[NAME_SIZE];	// ��ҽ�ɫ��
	int		nLookface;				// ���ͷ��
	int		nLev;					// ��ҵȼ�
};
#endif // end of _GLOBAL_STRUCTDEF_HEADER_
