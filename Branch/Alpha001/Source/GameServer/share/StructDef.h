//////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2012, WuHan ChuangYou, All Rights Reserved
// Moudle: StructDef.h
// Author: 彭文奇(Peng Wenqi)
// Created: 2012-10-30
// 
// !!! 注意 !!!
//	本文件用于定义游戏服务器全局结构体
//////////////////////////////////////////////////////////////////////////
#ifndef _MAPGROUP_SHARE_STRUCT_DEF_H_
#define _MAPGROUP_SHARE_STRUCT_DEF_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../../common/common.h"
#include "./EnumDef.h"
#include "./ConstDef.h"
#include "../../../Include/GlobalStructDef.h"

// 登陆时账号信息
struct ACCOUNT_INFO
{
	// 读表信息
	OBJID		idAccount;
	char		szAccountName[64];
	int			nAccountType;
	int			nAccountStatus;
	int			nAccountStatusParam;

	// 内存信息
	SOCKET_ID	idSocket;
	OBJID		idChoosePlayer;
	int			nKickOtherFlag;		
	int			nLoginFlag;
	int			nUserCount;
	UINT		unStartSecond;
};


// 物品日志信息结构
//////////////////////////////////////////////////////////////////////////
typedef struct _ITEMLOGINFO
{
	OBJID	nKind;					// 类别（
	I64		i64ItemId;				// 物品动态id
	OBJID	TypeId;					// 物品type
	UINT	unItemCount;
} ITEMLOGINFO, *LPITEMLOGINFO;

typedef vector<ITEMLOGINFO>	VEC_ITEM_LOG_DATA;

//////////////////////////////////////////////////////////////////////////
typedef struct _ITEMLOGINFO_LIST
{
	UINT unCostlyCount;						// 贵重物品计数
	VEC_ITEM_LOG_DATA vecList;
} ITEMLOGINFO_LIST, *LPITEMLOGINFO_LIST;

//////////////////////////////////////////////////////////////////////////
struct MSG_POKER_INFO				// 卡牌信息消息结构
{
	MSG_NUM_8BIT	i64ID;			// id
	MSG_NUM_4BIT	nType;			// Type
	MSG_NUM_4BIT	nLevel;			// 等级
	MSG_NUM_2BIT	sStar;			// 星级
	MSG_NUM_2BIT	sColor;			// 颜色
	MSG_NUM_4BIT	unExp;			// 经验
	MSG_NUM_4BIT	unScore;		// 战力

	MSG_NUM_4BIT	unEquip1Type;	// 装备武器类型
	MSG_NUM_4BIT	nEquip1Star;	// 装备武器星级
	MSG_NUM_4BIT	unEquip1Exp;	// 装备武器经验

	MSG_NUM_4BIT	unEquip2Type;	// 装备头盔类型
	MSG_NUM_4BIT	nEquip2Star;	// 装备头盔星级
	MSG_NUM_4BIT	unEquip2Exp;	// 装备头盔经验

	MSG_NUM_4BIT	unEquip3Type;	// 装备项链类型
	MSG_NUM_4BIT	nEquip3Star;	// 装备项链星级
	MSG_NUM_4BIT	unEquip3Exp;	// 装备项链经验

	MSG_NUM_4BIT	unEquip4Type;	// 装备腰带类型
	MSG_NUM_4BIT	nEquip4Star;	// 装备腰带星级
	MSG_NUM_4BIT	unEquip4Exp;	// 装备腰带经验

	MSG_NUM_4BIT	unEquip5Type;	// 装备衣服类型
	MSG_NUM_4BIT	nEquip5Star;	// 装备衣服星级
	MSG_NUM_4BIT	unEquip5Exp;	// 装备衣服经验

	MSG_NUM_4BIT	unEquip6Type;	// 装备鞋子类型
	MSG_NUM_4BIT	nEquip6Star;	// 装备鞋子星级
	MSG_NUM_4BIT	unEquip6Exp;	// 装备鞋子经验

	MSG_NUM_4BIT	nSkillSpLev;	// 特技等级
	MSG_NUM_4BIT	nSkillAutoLev1;	// 自动技能1等级
	MSG_NUM_4BIT	nSkillAutoLev2;	// 自动技能2等级
	MSG_NUM_4BIT	nSkillAutoLev3;	// 自动技能3等级
	MSG_NUM_4BIT	nSkillJointLev;	// 连携技能等级

	MSG_NUM_4BIT	nState;			// 卡牌状态
};

struct MERCENARY_INFO				// 佣兵信息
{
	MSG_NUM_8BIT	i64ID;			// ID
	MSG_NUM_4BIT	unType;			// 类型
	MSG_NUM_4BIT	nLev;			// 等级
	MSG_NUM_2BIT	sStar;			// 星级
	MSG_NUM_2BIT	sColor;			// 颜色
	MSG_NUM_4BIT	unScore;		// 战力
	MSG_NUM_4BIT	nData1;			// 参数1
	MSG_NUM_4BIT	nData2;			// 参数2
	MSG_NUM_4BIT	nData3;			// 参数3
	MSG_NUM_4BIT	nData4;			// 参数4
	MSG_NUM_4BIT	nData5;			// 参数5
	MSG_STR_32BIT	szOwnerName;	// 主人名字
};

struct POKER_VIEW_INFO				// 卡牌查看信息
{
	MSG_NUM_8BIT	i64ID;			// ID
	MSG_NUM_4BIT	unType;			// 类型
	MSG_NUM_4BIT	nLev;			// 等级
	MSG_NUM_2BIT	sStar;			// 星级
	MSG_NUM_2BIT	sColor;			// 颜色
	MSG_NUM_4BIT	unScore;		// 战力
	MSG_NUM_4BIT	nParam1;		// 参数1
	MSG_NUM_4BIT	nParam2;		// 参数2
	MSG_NUM_4BIT	nParam3;		// 参数3
	MSG_NUM_4BIT	nParam4;		// 参数4
	MSG_NUM_8BIT	i64Param5;		// 参数5
};
typedef std::vector<POKER_VIEW_INFO>	VEC_POKER_VIEW_INFO;

//////////////////////////////////////////////////////////////////////////
// 好友系统

typedef struct  
{
	OBJID				idFriend;
	MSG_NUM_4BIT		nLev;							// 等级
	MSG_NUM_4BIT		nLookFace;						// 头像
	MSG_NUM_4BIT		nFriendShipPoint;				// 友情点
	MSG_NUM_4BIT		nFigntingCapacity;				// 所有卡牌总战斗力
	MSG_NUM_4BIT		nLastLoginTime;					// 最近一次登录时间UTC秒

	MSG_STR_32BIT		szFriendName;					// 好友名字
	MSG_STR_32BIT		szSyndicate;					// 公会名字
	MSG_STR_192BIT		szSignature;					// 个性签名 
	MSG_NUM_4BIT		nGiveUserGift;					// 玩家礼物状态（1表示自己已经领取，0表示收到好友礼物，2表示有礼物可以收取）
	MSG_NUM_4BIT		nGiveFriendGift;				// 好友礼物状态（1表示好友已经领取，0表示没有礼物，2表示已赠送礼物）

	MSG_NUM_2BIT		sSex;							// 性别
	MSG_NUM_2BIT		sLookFaceFrame;					// 头像框
	MSG_NUM_4BIT		nBirthday;						// 生日	YYYYMMDD
	MSG_STR_64BIT		szAddress;						// 所在地
}Friend_Info;
typedef std::vector<Friend_Info>			VEC_FRIEND_INFO;
typedef VEC_FRIEND_INFO::iterator			ITER_VEC_FRIEND_INFO;

typedef struct  
{
	MSG_NUM_4BIT		idFriend;
	MSG_NUM_4BIT		nRelation;						// 关系（0 陌生人，1向自己发起好友请求的玩家)
	MSG_NUM_4BIT		nLev;							// 等级
	MSG_NUM_4BIT		nLookFace;						// 头像
	MSG_NUM_4BIT		nFriendShipPoint;				// 友情点
	MSG_NUM_4BIT		nFigntingCapacity;				// 所有卡牌总战斗力
	MSG_NUM_4BIT		nLastLoginTime;					// 最近一次登录时间UTC秒
	MSG_STR_32BIT		szFriendName;					// 好友名字
	MSG_STR_32BIT		szSyndicate;					// 公会名字
	MSG_STR_192BIT		szSignature;					// 个性签名 

	MSG_NUM_2BIT		sSex;							// 性别
	MSG_NUM_2BIT		sLookFaceFrame;					// 头像框
	MSG_NUM_4BIT		nBirthday;						// 生日	YYYYMMDD
	MSG_STR_64BIT		szAddress;						// 所在地
}Friend_Push_Info;
typedef std::vector<Friend_Push_Info>		VEC_FRIEND_PUSH_INFO;
typedef VEC_FRIEND_PUSH_INFO::iterator		ITER_VEC_FRIEND_PUSH_INFO;

typedef std::map<OBJID, MyFriendInfo>	MAP_MYFRIEND_INFO;
typedef MAP_MYFRIEND_INFO::iterator		ITER_MAP_MYFRIEND_INFO;

typedef std::map<OBJID, MyFriendRequestInfo>	MAP_MYFRIEND_REQUEST_INFO;
typedef MAP_MYFRIEND_REQUEST_INFO::iterator		ITER_MAP_MYFRIEND_REQUEST_INFO;

//////////////////////////////////////////////////////////////////////////

// 物品信息
struct ITEM_INFO
{
	I64		i64ID;
	OBJID	idItemType;
	OBJID	idUser;
	int		nAmount;
	UINT	unLiftTime;
};

// 装备属性信息
struct EQUIP_ATTR_INFO
{
	int	nAttrType;
	int nAttrData;
};

// 装备信息
struct EQUIP_INFO
{
	ITEM_INFO		stItemInfo;
	int				nStar;
	EQUIP_ATTR_INFO	stBaseAttr[5];
	EQUIP_ATTR_INFO	stStarAttr[5];
};

//////////////////////////////////////////////////////////////////////////
struct ST_ITEMNUMINFO				// 物品数量信息
{
	UINT unItemType;
	UINT unItemNum;
};
typedef std::vector<ST_ITEMNUMINFO>		VEC_ITEMNUMINFO;

struct ST_ITEMNUMINFO_EX			// 物品数量信息加强版
{
	UINT unItemType;				// 类型
	UINT unItemNum;					// 数量
	UINT unSourceType;				// 源类型
};
typedef std::vector<ST_ITEMNUMINFO_EX>	VEC_ITEMNUMINFO_EX;
//////////////////////////////////////////////////////////////////////////

// 掉落结果
struct DROP_RESULT
{
	OBJID	idDropOwner;	// owner id
	OBJID	idDropType;		// type
	int		nDropCount;		// 数量
	int		nDropGroup;		// 归属
	int		nDropRound;		// 波次
	bool	bPass;			// 跳过判断
};

// 战斗
struct BATTLE_ACTION
{
	OBJID	idFighter;
	OBJID	idAction;
	bool	bPass;
};

// 战斗成员初始化信息
struct FIGHTER_INIT_INFO
{
	OBJID	id;					// 位置id
	char	szName[NAME_SIZE];	// 名字
	I64		i64Poker;			// 卡牌id	如果是卡牌初始化出来的战斗者有此值
	OBJID	idPokerType;		// 卡牌类型	如果是卡牌初始化出来的战斗者有此值
	OBJID	idMonsterType;		// 怪物类型	如果是怪物初始化出来的战斗者有此值
	int		nAwardExp;			// 奖励经验	自己的卡牌, 战斗胜利后可以得到经验

	int		nFightPos;			// 战斗位置
	int		nPosSort;			// 战斗排序
	int		nAngerParam;		// 愤怒转化系数
	int		nLev;				// 等级
	UINT	nExp;				// 经验
	int		nStar;				// 星级
	int		nColor;				// 颜色

	UINT	unHpInit;			// 初始化血量
	UINT	unSpInit;			// 初始化愤怒

	UINT	unLife;				// 一级属性	体质
	UINT	unMana;				// 一级属性	魔力
	UINT	unStr;				// 一级属性	力量
	UINT	unSta;				// 一级属性	耐力
	UINT	unDex;				// 一级属性	敏捷

	UINT	unHp;				// 二级属性 气血
	UINT	unSp;				// 二级属性	愤怒
	UINT	unHit;				// 二级属性	命中
	UINT	unAtk;				// 二级属性	伤害
	UINT	unDef;				// 二级属性	防御
	UINT	unSpd;				// 二级属性	速度 
	UINT	unDodge;			// 二级属性	闪避
	UINT	unMagic;			// 二级属性	灵力

	int		nHpAdd;				// 气血加成 万分比
	int		nSpAdd;				// 愤怒加成 万分比
	int		nHitAdd;			// 命中加成 万分比
	int		nAtkAdd;			// 伤害加成 万分比
	int		nDefAdd;			// 防御加成 万分比
	int		nSpdAdd;			// 速度加成 万分比
	int		nDodgeAdd;			// 闪避加成 万分比
	int		nMagicAdd;			// 灵力加成 万分比

	UINT	unHpRecover;		// 特殊属性 气血回复		
	UINT	unSpRecover;		// 特殊属性	愤怒回复		
	UINT	unPhyCrit;			// 特殊属性	物暴				
	UINT	unMagCrit;			// 特殊属性	法爆				
	UINT	unVampireLev;		// 特殊属性	吸血等级			
	UINT	unSpSpendDecrease;	// 特殊属性	愤怒消耗降低%		
	UINT	unCureIncrease;		// 特殊属性	治疗技能效果提高%	

	OBJID	idSkillSpType;		// 特技类型					
	UINT	unSkillSpLev;		// 特技等级					
	OBJID	idSkillAuto1Type;	// 自动技能1 类型			
	UINT	unSkillAuto1Lev;	// 自动技能1 等级			
	OBJID	idSkillAuto2Type;	// 自动技能2 类型			
	UINT	unSkillAuto2Lev;	// 自动技能2 等级			
	OBJID	idSkillAuto3Type;	// 自动技能3 类型			
	UINT	unSkillAuto3Lev;	// 自动技能3 等级			
	OBJID	idSkillJointType;	// 连携技能 类型			
	UINT	unSkillJointLev;	// 连携技能 等级		
};

// 战斗成员结束信息
struct FIGHTER_END_INFO
{
	OBJID	id;				// 位置id
	UINT	unAtk;			// 总攻击
	UINT	unRecoverHp;	// 总恢复血量
	UINT	unLeftHp;		// 剩余血量
	UINT	unLeftSp;		// 剩余愤怒
	UINT	unSeedSumKey;	// 效验和Key	以上所有数值和加战斗种子, 保留10E以内的值, 再计算Key
};

//////////////////////////////////////////////////////////////////////////
// 竞技场系统 
	// 竞技场消息结构
		// 卡牌数据
// 消息对手数据
typedef struct  
{
	OBJID			idOwner;			// 主人id
	OBJID			idPokerType;		// 卡牌typeid
	MSG_NUM_4BIT	nPosition;			// 卡牌位置（1,2,3排）
	MSG_NUM_4BIT	nLev;				// 卡牌等级
	MSG_NUM_4BIT	nStar;				// 卡牌星级
	MSG_NUM_4BIT	nColor;				// 卡牌颜色
}Msg_Arena_Poker_Info;

// 对手数据
typedef struct  
{
	I64		iPokerID;			// 卡牌id
	OBJID	idPokerType;		// 卡牌typeid
	int		nPosition;			// 卡牌位置（1,2,3排）
	int		nLev;				// 卡牌等级
	int		nStar;				// 卡牌星级
	int		nColor;				// 卡牌颜色
	int		nFightingCapacity;	// 卡牌战斗力
}Arena_Poker_Info;
typedef std::vector<Arena_Poker_Info>			VEC_ARENA_POKER_INFO;
typedef VEC_ARENA_POKER_INFO::iterator			ITER_VEC_ARENA_POKER_INFO;

typedef struct
{
	OBJID				idTarget;				// 对手id
	MSG_NUM_4BIT		nLev;					// 等级
	MSG_NUM_4BIT		nLookFace;				// 头像
	MSG_NUM_4BIT		nRank;					// 级别
	MSG_NUM_4BIT		nFightingCapacity;		// 战斗力
	MSG_NUM_4BIT		nWinCount;				// 胜场数
	MSG_STR_32BIT		szName;					// 名字
	MSG_STR_32BIT		szSyndicate;			// 公会名字
}Arena_Target_Info;
typedef std::vector<Arena_Target_Info>		VEC_ARENA_TARGET_INFO;
typedef VEC_ARENA_TARGET_INFO::iterator		ITER_VEC_ARENA_TARGET_INFO;

// 竞技场卡牌战斗初始化数据
typedef std::vector<ARENA_POKER_BATTLE_INFO>			VEC_ARENA_POKER_BATTLE_INFO;
typedef VEC_ARENA_POKER_BATTLE_INFO::const_iterator		ITER_CON_VEC_ARENA_POKER_BATTLE_INFO;

typedef struct
{
	int		nSingleRank;
	int		nMultiRank;
	int		nHistoryRank;
	int		nRemainFightCount;
	int		nTotalFightcount;
	int		nCDTime;
	int		nResetCost;
	int		nFightingCapacity;
}ST_ARENA_COMMON_DATA;

struct ST_DROP_ITEM
{
	OBJID	idDropGroupType;	// 掉落类型对应 DROP_RULE_GROUP_TYPE
	int 	nCount;				// 数量
	int		nGroup;				// 归属分类
};
typedef std::vector<ST_DROP_ITEM>		VEC_DROP_ITEM;
typedef std::map<OBJID, ST_DROP_ITEM>	MAP_DROP_ITEM;

//////////////////////////////////////////////////////////////////////////

// 任务
struct MSG_USER_TASK_DATA
{
	MSG_NUM_4BIT nTaskID;		// 编号																											
	MSG_NUM_4BIT nTaskType;		// 任务类型													
	MSG_NUM_4BIT nStep;			// 步骤														
	MSG_NUM_4BIT nStatus;		// 任务状态(0:未接受,1:接受, 2:提交, 3:达到完成条件但未提交)
	MSG_NUM_4BIT nCount1;		// 计数1													
	MSG_NUM_4BIT nCount2;		// 计数2													
	MSG_NUM_4BIT nCount3;		// 计数3
	MSG_NUM_4BIT nBeginTime;	// 开始时间(单位秒)	
	MSG_NUM_4BIT nOverTime;		// 过期时间(0:无限制, >0:过期时间单位秒)
};
typedef std::vector<MSG_USER_TASK_DATA>			VEC_MSG_USER_TASK;
typedef VEC_MSG_USER_TASK::iterator				ITER_VEC_MSG_USER_TASK;
typedef VEC_MSG_USER_TASK::const_iterator		CITER_VEC_MSG_USER_TASK;

// 邮件内容
struct MSG_MAIL_DATA
{
	MSG_NUM_8BIT	i64MailID;	// 邮件ID
	MSG_STR_256BIT  szContent;	// 内容
	MSG_NUM_4BIT    nOverTime;	// 过期时间(必须有时间限制)
	MSG_NUM_4BIT    nStatus;	// 邮件状态(0:未读, 1:已读, 2:删除)

	MSG_NUM_4BIT nItemType1;	// 物品1
	MSG_NUM_4BIT nItemNum1;		// 物品1数量
	MSG_NUM_4BIT nItemType2;	// 物品2
	MSG_NUM_4BIT nItemNum2;		// 物品2数量
	MSG_NUM_4BIT nItemType3;	// 物品3
	MSG_NUM_4BIT nItemNum3;		// 物品3数量
	MSG_NUM_4BIT nItemType4;	// 物品4
	MSG_NUM_4BIT nItemNum4;		// 物品4数量
	MSG_NUM_4BIT nItemType5;	// 物品5
	MSG_NUM_4BIT nItemNum5;		// 物品5数量
	MSG_NUM_4BIT nItemType6;	// 物品6
	MSG_NUM_4BIT nItemNum6;		// 物品6数量

	MSG_NUM_4BIT nMoneyType1;	// 货币1
	MSG_NUM_4BIT nMoneyNum1;	// 货币1数量
	MSG_NUM_4BIT nMoneyType2;	// 货币2
	MSG_NUM_4BIT nMoneyNum2;	// 货币2数量
	MSG_NUM_4BIT nMoneyType3;	// 货币3
	MSG_NUM_4BIT nMoneyNum3;	// 货币3数量
	MSG_NUM_4BIT nMoneyType4;	// 货币4
	MSG_NUM_4BIT nMoneyNum4;	// 货币4数量

	MSG_NUM_4BIT nExp;			// 经验
};

// 每日活跃
struct MSG_LIVENESS_DATA
{
	MSG_NUM_4BIT	nLivenessID;	// 活跃项ID
	MSG_NUM_4BIT	nCount;			// 完成计数
	MSG_NUM_4BIT	nStatus;		// 活跃项奖励状态(0:未领取, 1:已领取)
};

// 帮派日志
struct MSG_SYN_LOG
{
	MSG_NUM_4BIT	nCreateTime;	// 日志产生时间(秒)
	MSG_NUM_4BIT	nLogType;		// 日志类型
	MSG_STR_128BIT	szContent;		// 日志内容
};
typedef std::vector<MSG_SYN_LOG> VEC_SYN_LOG;

// 元宝信息
struct VAS_INFO
{
	I64		i64Vas; 					// 当前元宝
	I64		i64TotalPayVas;				// 总充值元宝
	
	int		nFirstMask;

	int		nMonthCardID;				// 月卡ID
	short	sMonthCardTodayCanGet;		// 今天是否能领取月卡
	short	sMonthCardLeftCount;		// 领取剩余次数

	int		nSynMonthCardID;			// 帮派任性月卡ID
	int		nSynMonthCardTodayCanGet;	// 今天是否能领取帮派月卡
	int		nSynMonthCardEndTime;		// 帮派月卡结束时间
};

//////////////////////////////////////////////////////////////////////////
// 公会领地战系统 
	// 战斗卡牌数据 
typedef struct  
{
	I64			iPokerID;		// 卡牌id
	UINT		unHp;			// 卡牌实际血量(0为默认血量）
	UINT		unSp;			// 卡牌实际愤怒（0为默认愤怒）
}ST_TERRITORY_FIGHT_POKER;
typedef std::vector<ST_TERRITORY_FIGHT_POKER>				VEC_TERRITORY_FIGHT_POKER;

typedef struct  
{
	I64									iTroopsID;				// 队伍番号
	OBJID								idSyndicate;			// 所属公会id
	OBJID								idUser;					// 所属玩家id
	int									nFightingCapacity;		// 队伍战斗力
	VEC_TERRITORY_FIGHT_POKER			vecPoker;				// 队伍卡牌信息
}ST_TERRITORY_FIGHT_TROOPS;

	// 消息结构定义
typedef struct  
{
	OBJID			idUser;			// 玩家id
	MSG_NUM_4BIT	nLev;			// 玩家等级
	MSG_NUM_4BIT	nLookFace;		// 玩家头像
	MSG_NUM_4BIT	nTroopsCount;	// 派出部队总数
	MSG_NUM_4BIT	nPokerCount;	// 派出部队卡牌总数
	MSG_STR_32BIT	szName;			// 玩家名字
}MSG_TERRITORY_MEMBERS;
typedef std::vector<MSG_TERRITORY_MEMBERS>		VEC_MSG_TERRITORY_SYN_TROOPS;

// 主界面主要数据
typedef struct  
{
	int			nActivityStage;					// 阶段
	int			nLeftTimes;						// 阶段剩余时间
}ST_TERRITORY_MAIN_INTERFACE;

// 领地归属数据
typedef struct  
{
	OBJID		idTerritory;					// 领地id
	OBJID		idSyndicate;					// 所属公会id（id为0为野怪占领）
	char		szSyndicateName[NAME_SIZE];		// 所属公会名字()
}ST_TERRITORY_BELONG_INFO;

// 领地详细信息数据
typedef struct  
{
	OBJID		idSyndicate;					// 所属公会id（id为0为野怪占领）
	char		szSyndicateName[NAME_SIZE];		// 所属公会名字
	int			nEffect;						// 领地效果
}ST_TERRITORY_LOOK_INFO;

// 公会领地战部队信息
typedef struct  
{
	OBJID	idUser;								// 玩家id
	int		nLev;								// 等级
	int		nLookFace;							// 头像
	int		nTeamCount;							// 派遣队伍数
	int		nPokerCount;						// 派遣总卡牌数
	char	szUserName[NAME_SIZE];				// 玩家名字
}ST_TERRITORY_SYNDICATE_TROOPS_INFO;

// 公会领地战部队卡牌详细信息
typedef struct  
{
	I64		iPokerID;							// 卡牌id
	OBJID	idPokerType;						// 卡牌typeid
	int		nLev;								// 等级
	int		nColor;								// 颜色
	int		nStar;								// 星级
	int		nFightingCapacity;					// 战斗力
}ST_TERRITORY_POKER_INFO;
typedef std::vector<ST_TERRITORY_POKER_INFO>				VEC_TERRITORY_POKER;
typedef std::map<I64, VEC_TERRITORY_POKER>					MAP_TERRITORY_POKER;
typedef MAP_TERRITORY_POKER::iterator						ITER_MAP_TERRITORY_POKER;

// 公会部队玩家信息
typedef struct  
{
	int							nFightCapacity;	// 队伍总战斗力
	I64							iTroopsID;		// 卡牌所在队伍番号
	int							nPokerCount;	// 卡牌数
	ST_TERRITORY_POKER_INFO		stPoker[1];		// 卡牌信息
}ST_TERRITORY_SYNDICATE_MEMBER_INFO;
// 派遣部队数据

// 玩家已经派遣的部队数据
typedef struct  
{
	I64		iTroopsID;						// 部队番号
	OBJID	idTerritory;					// 领地id
	I64		iPokerID;						// 卡牌id
}ST_TERRITORY_USER_SENDED_TROOPS_INFO;
typedef std::vector<ST_TERRITORY_USER_SENDED_TROOPS_INFO>	VEC_TERRITORY_USER_SENDED_TROOPS_INFO;
typedef VEC_TERRITORY_USER_SENDED_TROOPS_INFO::iterator		ITER_VEC_TERRITORY_USER_SENDED_TROOPS_INFO;

// 好友邀请
struct MSG_FRIEND_INVITE
{
	MSG_NUM_4BIT	nFriendID;		// 好友ID
	MSG_NUM_2BIT	sSex;			// 性别
	MSG_NUM_2BIT    sLev;			// 好友等级
	MSG_NUM_4BIT    nLookFace;		// 好友头像
	MSG_NUM_4BIT    nLookFaceFrame;	// 好友头像框
	MSG_NUM_4BIT    nScore;			// 好友战力
	MSG_NUM_4BIT	nBirthday;		// 生日	YYYYMMDD
	MSG_NUM_4BIT	nLastLoginTime;	// 最近一次登录时间UTC秒

	MSG_STR_32BIT	szFriendName;	// 好友名
	MSG_STR_32BIT	szSyndicate;	// 公会名
	MSG_STR_192BIT	szSignature;	// 个性签名 
	MSG_STR_64BIT	szAddress;		// 所在地

	MSG_NUM_4BIT    nVas;			// 可领取的元宝
};
typedef std::vector<MSG_FRIEND_INVITE>			VEC_FRIEND_INVITE;
//////////////////////////////////////////////////////////////////////////

struct ST_WARROAD_DPS_INFO
{
	OBJID	idUser;				// 玩家id
	UINT	unDpsValue;			// Dps值
	int		nRankData;			// 排名参数
};
typedef std::vector<ST_WARROAD_DPS_INFO>	VECWARROADDPSINFO;

struct ST_WARROAD_AWARD_INFO
{
	OBJID	idUser;				// 玩家id
	UINT	unApplyTime;		// 申请时间
	UINT    unCutTime;			// 插队时间
};
typedef std::vector<ST_WARROAD_AWARD_INFO>	VECWARROADAWARDINFO;

// 手动刷新信息
struct ST_HAND_REFRESH_INFO		
{
	UINT	unMoneyType;		// 货币类型
	UINT	unMoneyNum;			// 货币数量
	UINT	unReCount;			// 刷新次数
};

// 战斗保存信息
struct BATTLE_SAVE_INFO
{
	int nLeftHP;
	int nLeftSP;
};
typedef std::vector<BATTLE_SAVE_INFO>    VEC_BATTLE_SAVE;

struct ST_POKER_BASE_INFO
{
	MSG_NUM_8BIT	i64PokerID;	// 卡牌ID
	MSG_NUM_4BIT	nType;		// 类型
	MSG_NUM_4BIT	nLev;		// 等级
	MSG_NUM_4BIT	nStar;		// 星级
	MSG_NUM_4BIT	nColor;		// 颜色
	MSG_NUM_4BIT	nHP;		// 最大血量
	MSG_NUM_4BIT	nLeftHP;	// 剩余血量
	MSG_NUM_4BIT	nSP;		// 最大愤怒
	MSG_NUM_4BIT	nLeftSP;	// 剩余愤怒
};
typedef std::vector<ST_POKER_BASE_INFO>    VEC_POKER_BASE_INFO;

struct ST_MINE_FIGHT_POKER
{
	MSG_NUM_4BIT	idDefUser;	// 防守方ID
	MSG_NUM_8BIT	i64Poker;	// 卡牌ID
	MSG_NUM_4BIT	nLeftHP;	// 剩余血量
	MSG_NUM_4BIT	nLeftSP;	// 剩余愤怒
	MSG_NUM_4BIT	nPokerCamp;	// 卡牌归属(100:攻击方; 200:防守方)
};
typedef std::vector<ST_MINE_FIGHT_POKER>	VEC_MINE_FIGHT_POKER;

//////////////////////////////////////////////////////////////////////////
typedef struct				// 南天门战斗卡牌数据 
{
	I64		i64PokerID;		// 卡牌id
	UINT	unHp;			// 卡牌实际血量
	UINT	unSp;			// 卡牌实际愤怒
	int		nLiveFlag;		// 存活标记
}ST_NTM_POKER;
typedef std::vector<ST_NTM_POKER>	VEC_NTM_FIGHT_POKER;

struct ST_ROOM_NTM_INFO		// 南天门房间信息
{
	I64		idRoom;			// 房间id
	int		nLackMemberNum;	// 缺省玩家人数
};
typedef std::vector<ST_ROOM_NTM_INFO>	VEC_ROOM_NTM_INFO;

struct ST_POS				// 坐标信息
{
	int	  nPosx;			// X
	int	  nPosy;			// Y
	int	  nPosz;			// Z
};

struct ST_ROOM_USER_INFO	// 房间玩家信息
{
	OBJID  idUser;			// 玩家ID
	int	   nLookFace;		// 模型类型
	int    nDir;			// 方向
	ST_POS stPos;			// 坐标
};
typedef std::map<OBJID, ST_ROOM_USER_INFO>	MAP_ROOM_USER_INFO;

struct ST_ROOM_MONSTER_INFO	// 房间怪物信息
{
	short  sMonsterId;		// 怪物ID
	int	   nMonsterType;	// 怪物类型
	int	   nPosIndex;		// 随机坐标索引
	int	   nData1;			// 参数1
	int	   nData2;			// 参数2
	ST_POS stPos;			// 坐标
};
typedef std::map<short, ST_ROOM_MONSTER_INFO>	MAP_ROOM_MONSTER_INFO;

struct ST_USER_INTEGRAL_INFO
{
	OBJID idUser;
	int	  nIntegral;		// 积分
	int	  nPassTime;		// 通关用时
};
typedef std::vector<ST_USER_INTEGRAL_INFO>		VEC_USER_INTEGRAL_INFO;

struct ST_FIGHT_PRE_INFO
{
	OBJID idUser;			// 玩家1
	OBJID idTarget;			// 玩家2
	short sUserFightFlag;	// 玩家1战斗标记
	short sTargetFightFlag;	// 玩家2战斗标记
	UINT  unPreEndTime;		// 准备结束时间
};
typedef std::map<int, ST_FIGHT_PRE_INFO>		MAP_FIGHT_PRE_INFO;
//////////////////////////////////////////////////////////////////////////

// 花果山大战刷新水果数据
struct MSG_ROOM_FRUIT_DATA
{
	MSG_NUM_4BIT nFruitID;		// 水果编号
	MSG_NUM_4BIT nFruitType;	// 水果类型
	MSG_NUM_4BIT nFruitNum;		// 水果数量
	MSG_NUM_4BIT nPosX;			// 坐标X
	MSG_NUM_4BIT nPosY;			// 坐标Y
	MSG_NUM_4BIT nParam1;		// 预留1
	MSG_NUM_4BIT nParam2;		// 预留2
};
typedef std::vector<MSG_ROOM_FRUIT_DATA>			VEC_ROOM_FRUIT_DATA;
typedef std::map<OBJID, MSG_ROOM_FRUIT_DATA>		MAP_ROOM_FRUIT_DATA;

// 花果山大战玩家水果数据
struct MSG_USER_FRUIT_DATA
{
	MSG_NUM_4BIT		nFruitType;
	MSG_NUM_4BIT		nFruitNum;

	bool operator<(const MSG_USER_FRUIT_DATA& stKey) const
	{
		if (nFruitType != stKey.nFruitType)
		{
			return nFruitType < stKey.nFruitType;
		}
		else
		{
			return nFruitNum < stKey.nFruitNum;
		}
	}

	bool operator==(const MSG_USER_FRUIT_DATA& stKey) const
	{
		return ((nFruitNum == stKey.nFruitNum));
	}
};
typedef std::set<MSG_USER_FRUIT_DATA>				SET_USER_FRUIT_DATA;		// 玩家水果信息
typedef std::map<OBJID, SET_USER_FRUIT_DATA>		MAP_USER_FRUIT_DATA;		// 所有玩家水果信息<玩家ID, 个人水果数据>

// 花果山玩家信息
struct HGS_USER_INFO
{
	int     nUserID;	// 玩家ID
	int     nRank;		// 名次
	int		nScore;		// 积分(本次战斗累计的积分)
	int		nGesture;	// 手势(石头，剪刀，布)
	int     nMode;		// 人物模型
	int		nPosX;		// 坐标X
	int     nPosY;		// 坐标Y
	int     nDir;		// 方向
};
typedef std::vector<HGS_USER_INFO>     VEC_HGS_USER_INFO;

// 花果山排行榜信息
struct MSG_HGS_USER_INFO
{
	MSG_NUM_4BIT	nUserID;		// 玩家ID
	MSG_STR_32BIT	szUserName;		// 玩家名
	MSG_NUM_4BIT	nRank;			// 名次
	MSG_NUM_4BIT	nScore;			// 积分
	MSG_NUM_4BIT	nGesture;		// 手势(石头，剪刀，布)
	MSG_NUM_4BIT	nMode;			// 人物模型
	MSG_NUM_4BIT	nPosX;			// 坐标X
	MSG_NUM_4BIT	nPosY;			// 坐标Y
	MSG_NUM_4BIT	nDir;			// 方向
};
#endif // end of _MAPGROUP_SHARE_STRUCT_DEF_H_