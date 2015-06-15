////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2012, WuHan ChuangYou, All Rights Reserved
// Moudle: GlobalStructDef.h
// Author: 彭文奇(Peng Wenqi)
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

// 玩家在线信息
struct USER_ONLINE_INFO
{
	OBJID	idUser;
	OBJID	idAccount;
	int		nLine;
	int		nAccountType;

	// 可以通过bForce参数强制修改
	char	szUserName[NAME_SIZE];
	char	szSignature[SIGNATURE_MAX_SIZE];
	char	szAddress[MAX_ADDRESS_SIZE];

	// 可以通过变化修改, 默认为0
	int		nLev;
	int		nMaxScore;
	int		nLookFace;
	int		nSex;
	int		nLookFaceFrame;
	int		nBirthday;
	int		nGlamour;

	// 连续登陆时间和标记
	int		nLastLoginTime;
	int		nYesterdayLogin;
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

// 黑名单成员信息
struct ST_BLACKLIST_MEMBER_INFO
{
	MSG_NUM_4BIT	idUser;
	MSG_STR_32BIT	szName;
	MSG_NUM_4BIT	nLevel;
	MSG_NUM_4BIT	nLookFace;
	MSG_NUM_4BIT	nLookfaceFrame;
};

// 查看推送玩家面板信息
typedef struct  
{
	OBJID				idTarget;
	MSG_STR_32BIT		szSyndicate;					// 公会名字
	MSG_STR_64BIT		szSignature;					// 个性签名 			
}ST_FRIEND_PUSH_INTERFACE_INFO;

// 搜索玩家信息
typedef struct  
{
	OBJID				idUser;
	MSG_NUM_4BIT		nStatus;						// 推送玩家状态（-1表示已经向他申请添加好友，0表示陌生人玩家，1表示向自己发送添加好友申请的玩家，2已经是好友了)
	MSG_NUM_4BIT		nLev;							// 等级
	MSG_NUM_4BIT		nLookFace;						// 头像
	MSG_NUM_4BIT		nFigntingCapacity;				// 所有卡牌总战斗力
	MSG_NUM_4BIT		nLastLoginTime;					// 最近一次登录时间UTC秒
	MSG_STR_32BIT		szUserName;						// 玩家名字
	MSG_STR_32BIT		szSyndicate;					// 公会名字
	MSG_STR_64BIT		szSignature;					// 个性签名 
}ST_FRIEND_SEARCH_INFO;

typedef struct  
{
	int		nFriendShipPoint;				// 友情点数
	int		nGiveUserGift;					// 玩家的礼物状态
	int		nUserLastGotTime;				// 玩家上次领取其礼物的日期YYMMDD
	int		nGiveFriendGift;				// 好友礼物状态
	int		nFriendLastGotTime;				// 好友领取玩家赠送礼物的日期YYMMDD
	int		nLev;							// 等级
	int		nLookFace;						// 头像
	int		nFigntingCapacity;				// 战力
	int		nExitTime;						// 离线时间UTC
	int		nYesterdayLogin;				// 昨日登陆标记
	char	szFriendName[NAME_SIZE];		// 好友名字
	char	szSignature[SIGNATURE_MAX_SIZE];// 个性签名

	short	sSex;							// 性别
	short	sLookFaceFrame;					// 头像框
	int		nBirthday;						// 生日	YYYYMMDD
	char	szAddress[MAX_ADDRESS_SIZE];	// 所在地
}MyFriendInfo;

typedef struct  
{
	int		nLev;								// 等级
	int		nFigntingCapacity;					// 战力
	int		nLookFace;							// 头像
	int		nRequestTime;						// 请求时间
	int		nLastLogin;							// 最近登录时间
	char	szUserName[NAME_SIZE];				// 玩家名字
	char	szSignatrure[SIGNATURE_MAX_SIZE];	// 个性签名

	short	sSex;							// 性别
	short	sLookFaceFrame;					// 头像框
	int		nBirthday;						// 生日	YYYYMMDD
	char	szAddress[MAX_ADDRESS_SIZE];	// 所在地
} MyFriendRequestInfo;

//////////////////////////////////////////////////////////////////////////

// 商品信息
struct ST_GOODS_INFO
{
	unsigned int	unItemIndex;		// 物品位置(从1开始)
	unsigned int 	unItemType;			// 物品type
	unsigned int 	unItemNum;			// 物品数量
	unsigned int 	unPrice;			// 单价
	unsigned int 	unMoneyType;		// 货币类型
	unsigned int	unCurNum;			// 物品当前数量
	unsigned int	unDiscount;			// 物品折扣
};

//////////////////////////////////////////////////////////////////////////
// 竞技场 保存卡牌数据结构
typedef struct  
{
	MSG_NUM_8BIT	iPokerID;			// 卡牌id
	MSG_NUM_4BIT	nPosition;			// 卡牌位置(1排，2排，3排)
}Arena_Save_Poker;
typedef std::vector<Arena_Save_Poker>		VEC_ARENA_SAVE_POKER;
typedef VEC_ARENA_SAVE_POKER::iterator		ITER_VEC_ARENA_SAVE_POKER;

// 竞技场玩家数据
typedef struct 
{
	OBJID	idUser;					// 玩家id
	int		nLookFace;				// 头像
	int		nLookFaceFrame;			// 头像框
	int		nLev;					// 等级
	int		nRank;					// 排名
	int		nLastRank;				// 上期排名
	int		nWinCount;				// 胜场数
	int		nFightingCapacity;		// 战斗力
	char	szUserName[NAME_SIZE];	// 玩家名字
}TOPLIST_ARENA_USER_INFO;
typedef std::map<int, TOPLIST_ARENA_USER_INFO>		MAP_TOPLIST_ARENA_USER_INFO;
typedef MAP_TOPLIST_ARENA_USER_INFO::iterator		ITER_MAP_TOPLIST_ARENA_USER_INFO;

// 竞技场玩家的卡牌数据
typedef struct  
{
	OBJID	idPokerType;			// 卡牌类型id
	int		nLev;					// 卡牌级别
	int		nColor;					// 卡牌颜色
	int		nStar;					// 卡牌星级
	int		nPosition;				// 位置（第几队）
}TOPLIST_ARENA_POKER_INFO;
typedef std::map<OBJID, TOPLIST_ARENA_POKER_INFO>	MAP_TOPLIST_ARENA_POKER_INFO;
typedef MAP_TOPLIST_ARENA_POKER_INFO::iterator		ITER_MAP_TOPLIST_ARENA_POKER_INFO;

// 玩家id与排名映射
typedef struct  
{
	int nRank;						// 本期排名
	int nLastRank;					// 上期排名
}TOPLIST_RANK_INFO;
typedef std::map<OBJID, TOPLIST_RANK_INFO>			MAP_TARGETER_RANK_INFO;
typedef MAP_TARGETER_RANK_INFO::iterator			ITER_MAP_TARGETER_RANK_INFO;
// 排名与公会id映射
typedef struct
{
	OBJID idSyndicate;				// 排名
	int nData;						// 排名用数据 
}TOPLIST_SYNDICATE_INFO;
typedef std::map<int, TOPLIST_SYNDICATE_INFO>		MAP_TOPLIST_SYNDICATE_INFO;
typedef MAP_TOPLIST_SYNDICATE_INFO::iterator		ITER_MAP_TOPLIST_SYNDICATE_INFO;

// 排行榜玩家通用数据
typedef struct  
{
	OBJID	idUser;					// 玩家id
	int		nLookFace;				// 玩家头像
	int		nLookFaceFrame;			// 头像框
	int		nLev;					// 玩家等级
	int		nData;					// 排行数据
	int		nLastRank;				// 上期排名
	char	szUserName[NAME_SIZE];	// 玩家名字
}TOPLIST_COMMON_USER_INFO;
typedef std::map<int, TOPLIST_COMMON_USER_INFO>		MAP_TOPLIST_COMMON_USER_INFO;
typedef MAP_TOPLIST_COMMON_USER_INFO::iterator		ITER_MAP_TOPLIST_COMMON_USER_INFO;

// 排行榜系统 通用消息信息(战斗力+资源掠夺）
typedef struct  
{
	OBJID			idUser;			// 玩家id
	MSG_NUM_4BIT	nRank;			// 名次
	MSG_NUM_4BIT	nLev;			// 等级
	MSG_NUM_4BIT	nLookFace;		// 头像
	MSG_NUM_4BIT	nLookFaceFrame;	// 头像框
	MSG_NUM_4BIT	nData;			// 排名用数据
	MSG_STR_32BIT	szUserName;		// 玩家名字
	MSG_STR_32BIT	szSyndicate;	// 公会名字
}Msg_TopList_Common_Info;

// 大雁塔
struct MSG_GOOSE_TOWER
{
	MSG_NUM_2BIT	sFloor;					// 层数
	MSG_NUM_2BIT	sGainAward;				// 宝箱领取标记(0:未领取, 1:领取)
	MSG_STR_32BIT	szDefName;				// 防守小队玩家名
	MSG_STR_32BIT	szDefSynName;			// 防守小队帮派名
	MSG_NUM_4BIT	nDefLookFace;			// 防守小队头像
	MSG_NUM_2BIT	sDefLev;				// 防守小队等级
	MSG_NUM_2BIT	sDefUserLookFaceFrame;	// 防守小队头像框
	MSG_NUM_8BIT	i64PokerID1;			// 卡牌1
	MSG_NUM_8BIT	i64PokerID2;			// 卡牌2
	MSG_NUM_8BIT	i64PokerID3;			// 卡牌3
	MSG_NUM_8BIT	i64PokerID4;			// 卡牌4
	MSG_NUM_8BIT	i64PokerID5;			// 卡牌5
};
//////////////////////////////////////////////////////////////////////////

// 迷宫信息
struct ST_PUZZLE_INFO
{
	MSG_NUM_4BIT nPuzzleType;	// 迷宫类型
	MSG_NUM_4BIT nDiffcult;		// 迷宫难度
	MSG_NUM_4BIT nPuzzleFloor;	// 层数
	MSG_NUM_4BIT nFightNo;		// 战斗序列号
	MSG_NUM_4BIT nLastPuzzle;	// 上一个格子
	MSG_NUM_4BIT nCurPuzzle;	// 当前格子
	MSG_NUM_4BIT nProgress;		// 进度
	MSG_NUM_4BIT nBegTime;		// 开始时间(UTC)
	MSG_NUM_8BIT i64PokerID1;	// 卡牌1
	MSG_NUM_8BIT i64PokerID2;	// 卡牌2
	MSG_NUM_8BIT i64PokerID3;	// 卡牌3
	MSG_NUM_8BIT i64PokerID4;	// 卡牌4
	MSG_NUM_8BIT i64PokerID5;	// 卡牌5
};

// 迷宫BUFF信息
struct ST_PUZZLE_BUFF_INFO
{
	MSG_NUM_4BIT nBuffType;		// BUFF类型
	MSG_NUM_4BIT nPuzzleType;	// 副本
	MSG_NUM_4BIT nDifficult;	// 难度
	MSG_NUM_4BIT nPuzzleFloor;	// 层次
	MSG_NUM_4BIT nFightNo;		// 战斗序列号
	MSG_NUM_4BIT nTimeDay;		// 日期
};

struct ST_PUZZLE_BUFF_TYPE_INFO
{
	MSG_NUM_4BIT  nBuffType;			// BUFF类型
	MSG_NUM_4BIT  nBuffValue;			// BUFF值
	MSG_NUM_4BIT  nBuffEffect;			// BUFF生效机制
	MSG_STR_32BIT szBuffName;			// BUFF名字
};

// 竞技场系统
typedef struct  
{
	int		nPosition;					// 位置
	I64		iPokerID;					// 卡牌id

}ARENA_POKER_BATTLE_INFO;

// 对战记录数据
typedef struct  
{
	OBJID				idTarget;					// 对手id
	MSG_NUM_2BIT		nType;						// 竞技场类型（1单队，2多队）
	MSG_NUM_2BIT		nFightType;					// 战斗类型（1挑战，2被挑战）
	MSG_NUM_4BIT		nResult;					// 战斗结果（1赢，2输）
	MSG_NUM_4BIT		nRankChange;				// 名次变动数
	MSG_NUM_4BIT		nTime;						// 战斗时间
	MSG_NUM_4BIT		nLev;						// 等级
	MSG_NUM_4BIT		nLookFace;					// 头像(十万位是边框)
	MSG_STR_32BIT		szTargetName;				// 对手名字
	MSG_STR_64BIT		szVideo;					// 对战记录录像地址 长度 64
}Arena_Log;
typedef std::vector<Arena_Log>					VEC_ARENA_LOG;
typedef VEC_ARENA_LOG::iterator					ITER_VEC_ARENA_LOG;

// 邮件物品
struct MAIL_AWARD_DATA
{
	int		nAwardType;	// 物品Type
	int		nAwardNum;	// 物品数量
};
typedef std::vector<MAIL_AWARD_DATA> VEC_MAIL_AWARD;

// 邮件列表
struct MSG_MAIL_LIST
{
	MSG_NUM_8BIT	i64MailID;	// 邮件ID
	MSG_STR_32BIT	szTitle;	// 邮件标题
	MSG_STR_32BIT	szSender;	// 发件人名字
	MSG_NUM_4BIT	nSendTime;	// 发邮件时间
	MSG_NUM_4BIT	nStatus;	// 邮件状态(0:未读, 1:已读)
};
typedef std::vector<MSG_MAIL_LIST>				VEC_MAIL_LIST;
typedef VEC_MAIL_LIST::iterator					ITER_VEC_MAIL_LIST;
typedef VEC_MAIL_LIST::const_iterator			CITER_VEC_MAIL_LIST;


// 矿洞客户端信息
struct ST_MINE_CLIENT_INFO
{
	OBJID	idMine;								// 矿洞ID
	OBJID   idMember1;							// 矿洞成员1
	OBJID	idMember2;							// 矿洞成员2
	OBJID	idMember3;							// 矿洞成员3
	int		nModel1;							// 模型1(归属成员1)
	int		nModel2;							// 模型2(归属成员2)
	int		nModel3;							// 模型3(归属成员3)
	int		nType;								// 矿洞类型
	int		nScale;								// 矿洞规模
	int		nSpeed;								// 采集速度
	int		nResource;							// 累计资源
	int		nVasTotal;							// 累计钻石
	int		nEndTime;							// 结束时间
	int		nMineReason;						// 矿洞来源
	int		nIsFinish;							// 是否结束
};

// 被膜拜奖励
struct MSG_SYN_WORSHIP_AWARD
{
	MSG_NUM_4BIT nAwardType;
	MSG_NUM_4BIT nAwardTotal;		
};
typedef std::vector<MSG_SYN_WORSHIP_AWARD> VEC_SYN_WORSHIP_AWARD;


// 矿洞日志列表信息
struct MSG_MINE_LOG_LIST_INFO
{
	MSG_NUM_8BIT		i64LogID;						// 日志ID
	MSG_NUM_4BIT		nMineType;						// 矿洞类型
	MSG_NUM_4BIT		nMineScale;						// 矿洞规模
	MSG_NUM_4BIT		nAtkID;							// 攻击者ID
	MSG_STR_32BIT		szAtkName;						// 攻击者角色名
	MSG_NUM_4BIT		nBegTime;						// 掠夺开始时间
	MSG_NUM_4BIT		nVasLost;						// 丢失钻石
	MSG_NUM_4BIT		nResLost;						// 丢失资源
	MSG_NUM_4BIT		nPowerAward;					// 专用体力奖励
	MSG_NUM_4BIT		nDefResult;						// 防守结果(0:输, 1:赢)
	MSG_NUM_4BIT		nEndState;						// 掠夺结束状态(0:没结束, 1:结束)
};
typedef std::vector<MSG_MINE_LOG_LIST_INFO>		VEC_MINE_LOG_LIST_INFO;

struct MSG_MINE_FIGHTER_INFO
{
	MSG_STR_32BIT			szName;			// 战斗者名
	MSG_NUM_4BIT			nLev;			// 战斗者等级
	MSG_NUM_4BIT			nLookface;		// 战斗者头像
	MSG_NUM_4BIT			nLookfaceFrame;	// 战斗者头像框
};
typedef std::vector<MSG_MINE_FIGHTER_INFO>		VEC_MSG_MINE_FIGHTER_INFO;

// 矿洞日志信息
struct MSG_MINE_BATTLE_INFO
{
	MSG_NUM_8BIT		i64BattleID;					// 战斗ID
	MSG_NUM_8BIT		i64DefPoker1;					// 防守方卡牌1
	MSG_NUM_8BIT		i64DefPoker2;					// 
	MSG_NUM_8BIT		i64DefPoker3;					// 
	MSG_NUM_8BIT		i64DefPoker4;					// 
	MSG_NUM_8BIT		i64DefPoker5;					// 防守方卡牌5

	MSG_NUM_4BIT		nDefResult;						// 防守结果(0:输, 1:赢)

	MSG_NUM_8BIT		i64AtkPoker1;					// 攻击方卡牌1
	MSG_NUM_8BIT		i64AtkPoker2;					// 
	MSG_NUM_8BIT		i64AtkPoker3;					// 
	MSG_NUM_8BIT		i64AtkPoker4;					// 
	MSG_NUM_8BIT		i64AtkPoker5;					// 攻击方卡牌5

	MSG_STR_64BIT		szVideoAddr;					// 录像地址
};
typedef std::vector<MSG_MINE_BATTLE_INFO>		VEC_MINE_BATTLE_INFO;

// 正在运行活动信息
struct ACTIVITY_CONFIG_RUNNING_INFO
{
	int nType;			// 活动类型
	int nStartSecond;	// 活动开始时间(utc)
	int nEndSecond;		// 活动结束时间(utc)
	int nBeginAction;	// 活动开始触发脚本
	int nEndAction;		// 活动结束触发脚本
	int nEnterAction;	// 客户端触发进入脚本
	int nExitAction;	// 客户端触发退出脚本
	int nParam1;
	int nParam2;
};

//////////////////////////////////////////////////////////////////////////
// 成就系统 
typedef struct 
{
	OBJID	idAchievement;		// 成就id
	int		nType;				// 成就类型
	int		nProcess;			// 成就进度
	int		nGoal;				// 目标次数 
}USER_ACHIEVEMENT_INFO;
typedef std::map<int, USER_ACHIEVEMENT_INFO>		MAP_USER_ACHIEVEMENT_INFO;
typedef MAP_USER_ACHIEVEMENT_INFO::iterator			ITER_MAP_USER_ACHIEVEMENT_INFO;
typedef MAP_USER_ACHIEVEMENT_INFO::const_iterator	CITER_MAP_USER_ACHIEVEMENT_INFO;

//////////////////////////////////////////////////////////////////////////
// 聊天玩家信息
struct ST_TALK_USER_INFO
{
	OBJID	idUser;					// 玩家ID
	char	szUserName[NAME_SIZE];	// 玩家角色名
	int		nLookface;				// 玩家头像
	int		nLev;					// 玩家等级
};
#endif // end of _GLOBAL_STRUCTDEF_HEADER_
