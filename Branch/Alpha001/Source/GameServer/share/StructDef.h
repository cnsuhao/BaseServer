//////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2012, WuHan ChuangYou, All Rights Reserved
// Moudle: StructDef.h
// Author: ������(Peng Wenqi)
// Created: 2012-10-30
// 
// !!! ע�� !!!
//	���ļ����ڶ�����Ϸ������ȫ�ֽṹ��
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

// ��½ʱ�˺���Ϣ
struct ACCOUNT_INFO
{
	// ������Ϣ
	OBJID		idAccount;
	char		szAccountName[64];
	int			nAccountType;
	int			nAccountStatus;
	int			nAccountStatusParam;

	// �ڴ���Ϣ
	SOCKET_ID	idSocket;
	OBJID		idChoosePlayer;
	int			nKickOtherFlag;		
	int			nLoginFlag;
	int			nUserCount;
	UINT		unStartSecond;
};


// ��Ʒ��־��Ϣ�ṹ
//////////////////////////////////////////////////////////////////////////
typedef struct _ITEMLOGINFO
{
	OBJID	nKind;					// ���
	I64		i64ItemId;				// ��Ʒ��̬id
	OBJID	TypeId;					// ��Ʒtype
	UINT	unItemCount;
} ITEMLOGINFO, *LPITEMLOGINFO;

typedef vector<ITEMLOGINFO>	VEC_ITEM_LOG_DATA;

//////////////////////////////////////////////////////////////////////////
typedef struct _ITEMLOGINFO_LIST
{
	UINT unCostlyCount;						// ������Ʒ����
	VEC_ITEM_LOG_DATA vecList;
} ITEMLOGINFO_LIST, *LPITEMLOGINFO_LIST;

//////////////////////////////////////////////////////////////////////////
struct MSG_POKER_INFO				// ������Ϣ��Ϣ�ṹ
{
	MSG_NUM_8BIT	i64ID;			// id
	MSG_NUM_4BIT	nType;			// Type
	MSG_NUM_4BIT	nLevel;			// �ȼ�
	MSG_NUM_2BIT	sStar;			// �Ǽ�
	MSG_NUM_2BIT	sColor;			// ��ɫ
	MSG_NUM_4BIT	unExp;			// ����
	MSG_NUM_4BIT	unScore;		// ս��

	MSG_NUM_4BIT	unEquip1Type;	// װ����������
	MSG_NUM_4BIT	nEquip1Star;	// װ�������Ǽ�
	MSG_NUM_4BIT	unEquip1Exp;	// װ����������

	MSG_NUM_4BIT	unEquip2Type;	// װ��ͷ������
	MSG_NUM_4BIT	nEquip2Star;	// װ��ͷ���Ǽ�
	MSG_NUM_4BIT	unEquip2Exp;	// װ��ͷ������

	MSG_NUM_4BIT	unEquip3Type;	// װ����������
	MSG_NUM_4BIT	nEquip3Star;	// װ�������Ǽ�
	MSG_NUM_4BIT	unEquip3Exp;	// װ����������

	MSG_NUM_4BIT	unEquip4Type;	// װ����������
	MSG_NUM_4BIT	nEquip4Star;	// װ�������Ǽ�
	MSG_NUM_4BIT	unEquip4Exp;	// װ����������

	MSG_NUM_4BIT	unEquip5Type;	// װ���·�����
	MSG_NUM_4BIT	nEquip5Star;	// װ���·��Ǽ�
	MSG_NUM_4BIT	unEquip5Exp;	// װ���·�����

	MSG_NUM_4BIT	unEquip6Type;	// װ��Ь������
	MSG_NUM_4BIT	nEquip6Star;	// װ��Ь���Ǽ�
	MSG_NUM_4BIT	unEquip6Exp;	// װ��Ь�Ӿ���

	MSG_NUM_4BIT	nSkillSpLev;	// �ؼ��ȼ�
	MSG_NUM_4BIT	nSkillAutoLev1;	// �Զ�����1�ȼ�
	MSG_NUM_4BIT	nSkillAutoLev2;	// �Զ�����2�ȼ�
	MSG_NUM_4BIT	nSkillAutoLev3;	// �Զ�����3�ȼ�
	MSG_NUM_4BIT	nSkillJointLev;	// ��Я���ܵȼ�

	MSG_NUM_4BIT	nState;			// ����״̬
};

struct MERCENARY_INFO				// Ӷ����Ϣ
{
	MSG_NUM_8BIT	i64ID;			// ID
	MSG_NUM_4BIT	unType;			// ����
	MSG_NUM_4BIT	nLev;			// �ȼ�
	MSG_NUM_2BIT	sStar;			// �Ǽ�
	MSG_NUM_2BIT	sColor;			// ��ɫ
	MSG_NUM_4BIT	unScore;		// ս��
	MSG_NUM_4BIT	nData1;			// ����1
	MSG_NUM_4BIT	nData2;			// ����2
	MSG_NUM_4BIT	nData3;			// ����3
	MSG_NUM_4BIT	nData4;			// ����4
	MSG_NUM_4BIT	nData5;			// ����5
	MSG_STR_32BIT	szOwnerName;	// ��������
};

struct POKER_VIEW_INFO				// ���Ʋ鿴��Ϣ
{
	MSG_NUM_8BIT	i64ID;			// ID
	MSG_NUM_4BIT	unType;			// ����
	MSG_NUM_4BIT	nLev;			// �ȼ�
	MSG_NUM_2BIT	sStar;			// �Ǽ�
	MSG_NUM_2BIT	sColor;			// ��ɫ
	MSG_NUM_4BIT	unScore;		// ս��
	MSG_NUM_4BIT	nParam1;		// ����1
	MSG_NUM_4BIT	nParam2;		// ����2
	MSG_NUM_4BIT	nParam3;		// ����3
	MSG_NUM_4BIT	nParam4;		// ����4
	MSG_NUM_8BIT	i64Param5;		// ����5
};
typedef std::vector<POKER_VIEW_INFO>	VEC_POKER_VIEW_INFO;

//////////////////////////////////////////////////////////////////////////
// ����ϵͳ

typedef struct  
{
	OBJID				idFriend;
	MSG_NUM_4BIT		nLev;							// �ȼ�
	MSG_NUM_4BIT		nLookFace;						// ͷ��
	MSG_NUM_4BIT		nFriendShipPoint;				// �����
	MSG_NUM_4BIT		nFigntingCapacity;				// ���п�����ս����
	MSG_NUM_4BIT		nLastLoginTime;					// ���һ�ε�¼ʱ��UTC��

	MSG_STR_32BIT		szFriendName;					// ��������
	MSG_STR_32BIT		szSyndicate;					// ��������
	MSG_STR_192BIT		szSignature;					// ����ǩ�� 
	MSG_NUM_4BIT		nGiveUserGift;					// �������״̬��1��ʾ�Լ��Ѿ���ȡ��0��ʾ�յ��������2��ʾ�����������ȡ��
	MSG_NUM_4BIT		nGiveFriendGift;				// ��������״̬��1��ʾ�����Ѿ���ȡ��0��ʾû�����2��ʾ���������

	MSG_NUM_2BIT		sSex;							// �Ա�
	MSG_NUM_2BIT		sLookFaceFrame;					// ͷ���
	MSG_NUM_4BIT		nBirthday;						// ����	YYYYMMDD
	MSG_STR_64BIT		szAddress;						// ���ڵ�
}Friend_Info;
typedef std::vector<Friend_Info>			VEC_FRIEND_INFO;
typedef VEC_FRIEND_INFO::iterator			ITER_VEC_FRIEND_INFO;

typedef struct  
{
	MSG_NUM_4BIT		idFriend;
	MSG_NUM_4BIT		nRelation;						// ��ϵ��0 İ���ˣ�1���Լ����������������)
	MSG_NUM_4BIT		nLev;							// �ȼ�
	MSG_NUM_4BIT		nLookFace;						// ͷ��
	MSG_NUM_4BIT		nFriendShipPoint;				// �����
	MSG_NUM_4BIT		nFigntingCapacity;				// ���п�����ս����
	MSG_NUM_4BIT		nLastLoginTime;					// ���һ�ε�¼ʱ��UTC��
	MSG_STR_32BIT		szFriendName;					// ��������
	MSG_STR_32BIT		szSyndicate;					// ��������
	MSG_STR_192BIT		szSignature;					// ����ǩ�� 

	MSG_NUM_2BIT		sSex;							// �Ա�
	MSG_NUM_2BIT		sLookFaceFrame;					// ͷ���
	MSG_NUM_4BIT		nBirthday;						// ����	YYYYMMDD
	MSG_STR_64BIT		szAddress;						// ���ڵ�
}Friend_Push_Info;
typedef std::vector<Friend_Push_Info>		VEC_FRIEND_PUSH_INFO;
typedef VEC_FRIEND_PUSH_INFO::iterator		ITER_VEC_FRIEND_PUSH_INFO;

typedef std::map<OBJID, MyFriendInfo>	MAP_MYFRIEND_INFO;
typedef MAP_MYFRIEND_INFO::iterator		ITER_MAP_MYFRIEND_INFO;

typedef std::map<OBJID, MyFriendRequestInfo>	MAP_MYFRIEND_REQUEST_INFO;
typedef MAP_MYFRIEND_REQUEST_INFO::iterator		ITER_MAP_MYFRIEND_REQUEST_INFO;

//////////////////////////////////////////////////////////////////////////

// ��Ʒ��Ϣ
struct ITEM_INFO
{
	I64		i64ID;
	OBJID	idItemType;
	OBJID	idUser;
	int		nAmount;
	UINT	unLiftTime;
};

// װ��������Ϣ
struct EQUIP_ATTR_INFO
{
	int	nAttrType;
	int nAttrData;
};

// װ����Ϣ
struct EQUIP_INFO
{
	ITEM_INFO		stItemInfo;
	int				nStar;
	EQUIP_ATTR_INFO	stBaseAttr[5];
	EQUIP_ATTR_INFO	stStarAttr[5];
};

//////////////////////////////////////////////////////////////////////////
struct ST_ITEMNUMINFO				// ��Ʒ������Ϣ
{
	UINT unItemType;
	UINT unItemNum;
};
typedef std::vector<ST_ITEMNUMINFO>		VEC_ITEMNUMINFO;

struct ST_ITEMNUMINFO_EX			// ��Ʒ������Ϣ��ǿ��
{
	UINT unItemType;				// ����
	UINT unItemNum;					// ����
	UINT unSourceType;				// Դ����
};
typedef std::vector<ST_ITEMNUMINFO_EX>	VEC_ITEMNUMINFO_EX;
//////////////////////////////////////////////////////////////////////////

// ������
struct DROP_RESULT
{
	OBJID	idDropOwner;	// owner id
	OBJID	idDropType;		// type
	int		nDropCount;		// ����
	int		nDropGroup;		// ����
	int		nDropRound;		// ����
	bool	bPass;			// �����ж�
};

// ս��
struct BATTLE_ACTION
{
	OBJID	idFighter;
	OBJID	idAction;
	bool	bPass;
};

// ս����Ա��ʼ����Ϣ
struct FIGHTER_INIT_INFO
{
	OBJID	id;					// λ��id
	char	szName[NAME_SIZE];	// ����
	I64		i64Poker;			// ����id	����ǿ��Ƴ�ʼ��������ս�����д�ֵ
	OBJID	idPokerType;		// ��������	����ǿ��Ƴ�ʼ��������ս�����д�ֵ
	OBJID	idMonsterType;		// ��������	����ǹ����ʼ��������ս�����д�ֵ
	int		nAwardExp;			// ��������	�Լ��Ŀ���, ս��ʤ������Եõ�����

	int		nFightPos;			// ս��λ��
	int		nPosSort;			// ս������
	int		nAngerParam;		// ��ŭת��ϵ��
	int		nLev;				// �ȼ�
	UINT	nExp;				// ����
	int		nStar;				// �Ǽ�
	int		nColor;				// ��ɫ

	UINT	unHpInit;			// ��ʼ��Ѫ��
	UINT	unSpInit;			// ��ʼ����ŭ

	UINT	unLife;				// һ������	����
	UINT	unMana;				// һ������	ħ��
	UINT	unStr;				// һ������	����
	UINT	unSta;				// һ������	����
	UINT	unDex;				// һ������	����

	UINT	unHp;				// �������� ��Ѫ
	UINT	unSp;				// ��������	��ŭ
	UINT	unHit;				// ��������	����
	UINT	unAtk;				// ��������	�˺�
	UINT	unDef;				// ��������	����
	UINT	unSpd;				// ��������	�ٶ� 
	UINT	unDodge;			// ��������	����
	UINT	unMagic;			// ��������	����

	int		nHpAdd;				// ��Ѫ�ӳ� ��ֱ�
	int		nSpAdd;				// ��ŭ�ӳ� ��ֱ�
	int		nHitAdd;			// ���мӳ� ��ֱ�
	int		nAtkAdd;			// �˺��ӳ� ��ֱ�
	int		nDefAdd;			// �����ӳ� ��ֱ�
	int		nSpdAdd;			// �ٶȼӳ� ��ֱ�
	int		nDodgeAdd;			// ���ܼӳ� ��ֱ�
	int		nMagicAdd;			// �����ӳ� ��ֱ�

	UINT	unHpRecover;		// �������� ��Ѫ�ظ�		
	UINT	unSpRecover;		// ��������	��ŭ�ظ�		
	UINT	unPhyCrit;			// ��������	�ﱩ				
	UINT	unMagCrit;			// ��������	����				
	UINT	unVampireLev;		// ��������	��Ѫ�ȼ�			
	UINT	unSpSpendDecrease;	// ��������	��ŭ���Ľ���%		
	UINT	unCureIncrease;		// ��������	���Ƽ���Ч�����%	

	OBJID	idSkillSpType;		// �ؼ�����					
	UINT	unSkillSpLev;		// �ؼ��ȼ�					
	OBJID	idSkillAuto1Type;	// �Զ�����1 ����			
	UINT	unSkillAuto1Lev;	// �Զ�����1 �ȼ�			
	OBJID	idSkillAuto2Type;	// �Զ�����2 ����			
	UINT	unSkillAuto2Lev;	// �Զ�����2 �ȼ�			
	OBJID	idSkillAuto3Type;	// �Զ�����3 ����			
	UINT	unSkillAuto3Lev;	// �Զ�����3 �ȼ�			
	OBJID	idSkillJointType;	// ��Я���� ����			
	UINT	unSkillJointLev;	// ��Я���� �ȼ�		
};

// ս����Ա������Ϣ
struct FIGHTER_END_INFO
{
	OBJID	id;				// λ��id
	UINT	unAtk;			// �ܹ���
	UINT	unRecoverHp;	// �ָܻ�Ѫ��
	UINT	unLeftHp;		// ʣ��Ѫ��
	UINT	unLeftSp;		// ʣ���ŭ
	UINT	unSeedSumKey;	// Ч���Key	����������ֵ�ͼ�ս������, ����10E���ڵ�ֵ, �ټ���Key
};

//////////////////////////////////////////////////////////////////////////
// ������ϵͳ 
	// ��������Ϣ�ṹ
		// ��������
// ��Ϣ��������
typedef struct  
{
	OBJID			idOwner;			// ����id
	OBJID			idPokerType;		// ����typeid
	MSG_NUM_4BIT	nPosition;			// ����λ�ã�1,2,3�ţ�
	MSG_NUM_4BIT	nLev;				// ���Ƶȼ�
	MSG_NUM_4BIT	nStar;				// �����Ǽ�
	MSG_NUM_4BIT	nColor;				// ������ɫ
}Msg_Arena_Poker_Info;

// ��������
typedef struct  
{
	I64		iPokerID;			// ����id
	OBJID	idPokerType;		// ����typeid
	int		nPosition;			// ����λ�ã�1,2,3�ţ�
	int		nLev;				// ���Ƶȼ�
	int		nStar;				// �����Ǽ�
	int		nColor;				// ������ɫ
	int		nFightingCapacity;	// ����ս����
}Arena_Poker_Info;
typedef std::vector<Arena_Poker_Info>			VEC_ARENA_POKER_INFO;
typedef VEC_ARENA_POKER_INFO::iterator			ITER_VEC_ARENA_POKER_INFO;

typedef struct
{
	OBJID				idTarget;				// ����id
	MSG_NUM_4BIT		nLev;					// �ȼ�
	MSG_NUM_4BIT		nLookFace;				// ͷ��
	MSG_NUM_4BIT		nRank;					// ����
	MSG_NUM_4BIT		nFightingCapacity;		// ս����
	MSG_NUM_4BIT		nWinCount;				// ʤ����
	MSG_STR_32BIT		szName;					// ����
	MSG_STR_32BIT		szSyndicate;			// ��������
}Arena_Target_Info;
typedef std::vector<Arena_Target_Info>		VEC_ARENA_TARGET_INFO;
typedef VEC_ARENA_TARGET_INFO::iterator		ITER_VEC_ARENA_TARGET_INFO;

// ����������ս����ʼ������
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
	OBJID	idDropGroupType;	// �������Ͷ�Ӧ DROP_RULE_GROUP_TYPE
	int 	nCount;				// ����
	int		nGroup;				// ��������
};
typedef std::vector<ST_DROP_ITEM>		VEC_DROP_ITEM;
typedef std::map<OBJID, ST_DROP_ITEM>	MAP_DROP_ITEM;

//////////////////////////////////////////////////////////////////////////

// ����
struct MSG_USER_TASK_DATA
{
	MSG_NUM_4BIT nTaskID;		// ���																											
	MSG_NUM_4BIT nTaskType;		// ��������													
	MSG_NUM_4BIT nStep;			// ����														
	MSG_NUM_4BIT nStatus;		// ����״̬(0:δ����,1:����, 2:�ύ, 3:�ﵽ���������δ�ύ)
	MSG_NUM_4BIT nCount1;		// ����1													
	MSG_NUM_4BIT nCount2;		// ����2													
	MSG_NUM_4BIT nCount3;		// ����3
	MSG_NUM_4BIT nBeginTime;	// ��ʼʱ��(��λ��)	
	MSG_NUM_4BIT nOverTime;		// ����ʱ��(0:������, >0:����ʱ�䵥λ��)
};
typedef std::vector<MSG_USER_TASK_DATA>			VEC_MSG_USER_TASK;
typedef VEC_MSG_USER_TASK::iterator				ITER_VEC_MSG_USER_TASK;
typedef VEC_MSG_USER_TASK::const_iterator		CITER_VEC_MSG_USER_TASK;

// �ʼ�����
struct MSG_MAIL_DATA
{
	MSG_NUM_8BIT	i64MailID;	// �ʼ�ID
	MSG_STR_256BIT  szContent;	// ����
	MSG_NUM_4BIT    nOverTime;	// ����ʱ��(������ʱ������)
	MSG_NUM_4BIT    nStatus;	// �ʼ�״̬(0:δ��, 1:�Ѷ�, 2:ɾ��)

	MSG_NUM_4BIT nItemType1;	// ��Ʒ1
	MSG_NUM_4BIT nItemNum1;		// ��Ʒ1����
	MSG_NUM_4BIT nItemType2;	// ��Ʒ2
	MSG_NUM_4BIT nItemNum2;		// ��Ʒ2����
	MSG_NUM_4BIT nItemType3;	// ��Ʒ3
	MSG_NUM_4BIT nItemNum3;		// ��Ʒ3����
	MSG_NUM_4BIT nItemType4;	// ��Ʒ4
	MSG_NUM_4BIT nItemNum4;		// ��Ʒ4����
	MSG_NUM_4BIT nItemType5;	// ��Ʒ5
	MSG_NUM_4BIT nItemNum5;		// ��Ʒ5����
	MSG_NUM_4BIT nItemType6;	// ��Ʒ6
	MSG_NUM_4BIT nItemNum6;		// ��Ʒ6����

	MSG_NUM_4BIT nMoneyType1;	// ����1
	MSG_NUM_4BIT nMoneyNum1;	// ����1����
	MSG_NUM_4BIT nMoneyType2;	// ����2
	MSG_NUM_4BIT nMoneyNum2;	// ����2����
	MSG_NUM_4BIT nMoneyType3;	// ����3
	MSG_NUM_4BIT nMoneyNum3;	// ����3����
	MSG_NUM_4BIT nMoneyType4;	// ����4
	MSG_NUM_4BIT nMoneyNum4;	// ����4����

	MSG_NUM_4BIT nExp;			// ����
};

// ÿ�ջ�Ծ
struct MSG_LIVENESS_DATA
{
	MSG_NUM_4BIT	nLivenessID;	// ��Ծ��ID
	MSG_NUM_4BIT	nCount;			// ��ɼ���
	MSG_NUM_4BIT	nStatus;		// ��Ծ���״̬(0:δ��ȡ, 1:����ȡ)
};

// ������־
struct MSG_SYN_LOG
{
	MSG_NUM_4BIT	nCreateTime;	// ��־����ʱ��(��)
	MSG_NUM_4BIT	nLogType;		// ��־����
	MSG_STR_128BIT	szContent;		// ��־����
};
typedef std::vector<MSG_SYN_LOG> VEC_SYN_LOG;

// Ԫ����Ϣ
struct VAS_INFO
{
	I64		i64Vas; 					// ��ǰԪ��
	I64		i64TotalPayVas;				// �ܳ�ֵԪ��
	
	int		nFirstMask;

	int		nMonthCardID;				// �¿�ID
	short	sMonthCardTodayCanGet;		// �����Ƿ�����ȡ�¿�
	short	sMonthCardLeftCount;		// ��ȡʣ�����

	int		nSynMonthCardID;			// ���������¿�ID
	int		nSynMonthCardTodayCanGet;	// �����Ƿ�����ȡ�����¿�
	int		nSynMonthCardEndTime;		// �����¿�����ʱ��
};

//////////////////////////////////////////////////////////////////////////
// �������սϵͳ 
	// ս���������� 
typedef struct  
{
	I64			iPokerID;		// ����id
	UINT		unHp;			// ����ʵ��Ѫ��(0ΪĬ��Ѫ����
	UINT		unSp;			// ����ʵ�ʷ�ŭ��0ΪĬ�Ϸ�ŭ��
}ST_TERRITORY_FIGHT_POKER;
typedef std::vector<ST_TERRITORY_FIGHT_POKER>				VEC_TERRITORY_FIGHT_POKER;

typedef struct  
{
	I64									iTroopsID;				// ���鷬��
	OBJID								idSyndicate;			// ��������id
	OBJID								idUser;					// �������id
	int									nFightingCapacity;		// ����ս����
	VEC_TERRITORY_FIGHT_POKER			vecPoker;				// ���鿨����Ϣ
}ST_TERRITORY_FIGHT_TROOPS;

	// ��Ϣ�ṹ����
typedef struct  
{
	OBJID			idUser;			// ���id
	MSG_NUM_4BIT	nLev;			// ��ҵȼ�
	MSG_NUM_4BIT	nLookFace;		// ���ͷ��
	MSG_NUM_4BIT	nTroopsCount;	// �ɳ���������
	MSG_NUM_4BIT	nPokerCount;	// �ɳ����ӿ�������
	MSG_STR_32BIT	szName;			// �������
}MSG_TERRITORY_MEMBERS;
typedef std::vector<MSG_TERRITORY_MEMBERS>		VEC_MSG_TERRITORY_SYN_TROOPS;

// ��������Ҫ����
typedef struct  
{
	int			nActivityStage;					// �׶�
	int			nLeftTimes;						// �׶�ʣ��ʱ��
}ST_TERRITORY_MAIN_INTERFACE;

// ��ع�������
typedef struct  
{
	OBJID		idTerritory;					// ���id
	OBJID		idSyndicate;					// ��������id��idΪ0ΪҰ��ռ�죩
	char		szSyndicateName[NAME_SIZE];		// ������������()
}ST_TERRITORY_BELONG_INFO;

// �����ϸ��Ϣ����
typedef struct  
{
	OBJID		idSyndicate;					// ��������id��idΪ0ΪҰ��ռ�죩
	char		szSyndicateName[NAME_SIZE];		// ������������
	int			nEffect;						// ���Ч��
}ST_TERRITORY_LOOK_INFO;

// �������ս������Ϣ
typedef struct  
{
	OBJID	idUser;								// ���id
	int		nLev;								// �ȼ�
	int		nLookFace;							// ͷ��
	int		nTeamCount;							// ��ǲ������
	int		nPokerCount;						// ��ǲ�ܿ�����
	char	szUserName[NAME_SIZE];				// �������
}ST_TERRITORY_SYNDICATE_TROOPS_INFO;

// �������ս���ӿ�����ϸ��Ϣ
typedef struct  
{
	I64		iPokerID;							// ����id
	OBJID	idPokerType;						// ����typeid
	int		nLev;								// �ȼ�
	int		nColor;								// ��ɫ
	int		nStar;								// �Ǽ�
	int		nFightingCapacity;					// ս����
}ST_TERRITORY_POKER_INFO;
typedef std::vector<ST_TERRITORY_POKER_INFO>				VEC_TERRITORY_POKER;
typedef std::map<I64, VEC_TERRITORY_POKER>					MAP_TERRITORY_POKER;
typedef MAP_TERRITORY_POKER::iterator						ITER_MAP_TERRITORY_POKER;

// ���Ჿ�������Ϣ
typedef struct  
{
	int							nFightCapacity;	// ������ս����
	I64							iTroopsID;		// �������ڶ��鷬��
	int							nPokerCount;	// ������
	ST_TERRITORY_POKER_INFO		stPoker[1];		// ������Ϣ
}ST_TERRITORY_SYNDICATE_MEMBER_INFO;
// ��ǲ��������

// ����Ѿ���ǲ�Ĳ�������
typedef struct  
{
	I64		iTroopsID;						// ���ӷ���
	OBJID	idTerritory;					// ���id
	I64		iPokerID;						// ����id
}ST_TERRITORY_USER_SENDED_TROOPS_INFO;
typedef std::vector<ST_TERRITORY_USER_SENDED_TROOPS_INFO>	VEC_TERRITORY_USER_SENDED_TROOPS_INFO;
typedef VEC_TERRITORY_USER_SENDED_TROOPS_INFO::iterator		ITER_VEC_TERRITORY_USER_SENDED_TROOPS_INFO;

// ��������
struct MSG_FRIEND_INVITE
{
	MSG_NUM_4BIT	nFriendID;		// ����ID
	MSG_NUM_2BIT	sSex;			// �Ա�
	MSG_NUM_2BIT    sLev;			// ���ѵȼ�
	MSG_NUM_4BIT    nLookFace;		// ����ͷ��
	MSG_NUM_4BIT    nLookFaceFrame;	// ����ͷ���
	MSG_NUM_4BIT    nScore;			// ����ս��
	MSG_NUM_4BIT	nBirthday;		// ����	YYYYMMDD
	MSG_NUM_4BIT	nLastLoginTime;	// ���һ�ε�¼ʱ��UTC��

	MSG_STR_32BIT	szFriendName;	// ������
	MSG_STR_32BIT	szSyndicate;	// ������
	MSG_STR_192BIT	szSignature;	// ����ǩ�� 
	MSG_STR_64BIT	szAddress;		// ���ڵ�

	MSG_NUM_4BIT    nVas;			// ����ȡ��Ԫ��
};
typedef std::vector<MSG_FRIEND_INVITE>			VEC_FRIEND_INVITE;
//////////////////////////////////////////////////////////////////////////

struct ST_WARROAD_DPS_INFO
{
	OBJID	idUser;				// ���id
	UINT	unDpsValue;			// Dpsֵ
	int		nRankData;			// ��������
};
typedef std::vector<ST_WARROAD_DPS_INFO>	VECWARROADDPSINFO;

struct ST_WARROAD_AWARD_INFO
{
	OBJID	idUser;				// ���id
	UINT	unApplyTime;		// ����ʱ��
	UINT    unCutTime;			// ���ʱ��
};
typedef std::vector<ST_WARROAD_AWARD_INFO>	VECWARROADAWARDINFO;

// �ֶ�ˢ����Ϣ
struct ST_HAND_REFRESH_INFO		
{
	UINT	unMoneyType;		// ��������
	UINT	unMoneyNum;			// ��������
	UINT	unReCount;			// ˢ�´���
};

// ս��������Ϣ
struct BATTLE_SAVE_INFO
{
	int nLeftHP;
	int nLeftSP;
};
typedef std::vector<BATTLE_SAVE_INFO>    VEC_BATTLE_SAVE;

struct ST_POKER_BASE_INFO
{
	MSG_NUM_8BIT	i64PokerID;	// ����ID
	MSG_NUM_4BIT	nType;		// ����
	MSG_NUM_4BIT	nLev;		// �ȼ�
	MSG_NUM_4BIT	nStar;		// �Ǽ�
	MSG_NUM_4BIT	nColor;		// ��ɫ
	MSG_NUM_4BIT	nHP;		// ���Ѫ��
	MSG_NUM_4BIT	nLeftHP;	// ʣ��Ѫ��
	MSG_NUM_4BIT	nSP;		// ����ŭ
	MSG_NUM_4BIT	nLeftSP;	// ʣ���ŭ
};
typedef std::vector<ST_POKER_BASE_INFO>    VEC_POKER_BASE_INFO;

struct ST_MINE_FIGHT_POKER
{
	MSG_NUM_4BIT	idDefUser;	// ���ط�ID
	MSG_NUM_8BIT	i64Poker;	// ����ID
	MSG_NUM_4BIT	nLeftHP;	// ʣ��Ѫ��
	MSG_NUM_4BIT	nLeftSP;	// ʣ���ŭ
	MSG_NUM_4BIT	nPokerCamp;	// ���ƹ���(100:������; 200:���ط�)
};
typedef std::vector<ST_MINE_FIGHT_POKER>	VEC_MINE_FIGHT_POKER;

//////////////////////////////////////////////////////////////////////////
typedef struct				// ������ս���������� 
{
	I64		i64PokerID;		// ����id
	UINT	unHp;			// ����ʵ��Ѫ��
	UINT	unSp;			// ����ʵ�ʷ�ŭ
	int		nLiveFlag;		// �����
}ST_NTM_POKER;
typedef std::vector<ST_NTM_POKER>	VEC_NTM_FIGHT_POKER;

struct ST_ROOM_NTM_INFO		// �����ŷ�����Ϣ
{
	I64		idRoom;			// ����id
	int		nLackMemberNum;	// ȱʡ�������
};
typedef std::vector<ST_ROOM_NTM_INFO>	VEC_ROOM_NTM_INFO;

struct ST_POS				// ������Ϣ
{
	int	  nPosx;			// X
	int	  nPosy;			// Y
	int	  nPosz;			// Z
};

struct ST_ROOM_USER_INFO	// ���������Ϣ
{
	OBJID  idUser;			// ���ID
	int	   nLookFace;		// ģ������
	int    nDir;			// ����
	ST_POS stPos;			// ����
};
typedef std::map<OBJID, ST_ROOM_USER_INFO>	MAP_ROOM_USER_INFO;

struct ST_ROOM_MONSTER_INFO	// ���������Ϣ
{
	short  sMonsterId;		// ����ID
	int	   nMonsterType;	// ��������
	int	   nPosIndex;		// �����������
	int	   nData1;			// ����1
	int	   nData2;			// ����2
	ST_POS stPos;			// ����
};
typedef std::map<short, ST_ROOM_MONSTER_INFO>	MAP_ROOM_MONSTER_INFO;

struct ST_USER_INTEGRAL_INFO
{
	OBJID idUser;
	int	  nIntegral;		// ����
	int	  nPassTime;		// ͨ����ʱ
};
typedef std::vector<ST_USER_INTEGRAL_INFO>		VEC_USER_INTEGRAL_INFO;

struct ST_FIGHT_PRE_INFO
{
	OBJID idUser;			// ���1
	OBJID idTarget;			// ���2
	short sUserFightFlag;	// ���1ս�����
	short sTargetFightFlag;	// ���2ս�����
	UINT  unPreEndTime;		// ׼������ʱ��
};
typedef std::map<int, ST_FIGHT_PRE_INFO>		MAP_FIGHT_PRE_INFO;
//////////////////////////////////////////////////////////////////////////

// ����ɽ��սˢ��ˮ������
struct MSG_ROOM_FRUIT_DATA
{
	MSG_NUM_4BIT nFruitID;		// ˮ�����
	MSG_NUM_4BIT nFruitType;	// ˮ������
	MSG_NUM_4BIT nFruitNum;		// ˮ������
	MSG_NUM_4BIT nPosX;			// ����X
	MSG_NUM_4BIT nPosY;			// ����Y
	MSG_NUM_4BIT nParam1;		// Ԥ��1
	MSG_NUM_4BIT nParam2;		// Ԥ��2
};
typedef std::vector<MSG_ROOM_FRUIT_DATA>			VEC_ROOM_FRUIT_DATA;
typedef std::map<OBJID, MSG_ROOM_FRUIT_DATA>		MAP_ROOM_FRUIT_DATA;

// ����ɽ��ս���ˮ������
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
typedef std::set<MSG_USER_FRUIT_DATA>				SET_USER_FRUIT_DATA;		// ���ˮ����Ϣ
typedef std::map<OBJID, SET_USER_FRUIT_DATA>		MAP_USER_FRUIT_DATA;		// �������ˮ����Ϣ<���ID, ����ˮ������>

// ����ɽ�����Ϣ
struct HGS_USER_INFO
{
	int     nUserID;	// ���ID
	int     nRank;		// ����
	int		nScore;		// ����(����ս���ۼƵĻ���)
	int		nGesture;	// ����(ʯͷ����������)
	int     nMode;		// ����ģ��
	int		nPosX;		// ����X
	int     nPosY;		// ����Y
	int     nDir;		// ����
};
typedef std::vector<HGS_USER_INFO>     VEC_HGS_USER_INFO;

// ����ɽ���а���Ϣ
struct MSG_HGS_USER_INFO
{
	MSG_NUM_4BIT	nUserID;		// ���ID
	MSG_STR_32BIT	szUserName;		// �����
	MSG_NUM_4BIT	nRank;			// ����
	MSG_NUM_4BIT	nScore;			// ����
	MSG_NUM_4BIT	nGesture;		// ����(ʯͷ����������)
	MSG_NUM_4BIT	nMode;			// ����ģ��
	MSG_NUM_4BIT	nPosX;			// ����X
	MSG_NUM_4BIT	nPosY;			// ����Y
	MSG_NUM_4BIT	nDir;			// ����
};
#endif // end of _MAPGROUP_SHARE_STRUCT_DEF_H_