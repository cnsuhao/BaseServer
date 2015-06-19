//////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2012, WuHan ChuangYou, All Rights Reserved
// Moudle: EnumDef.h
// Author: ������(Peng Wenqi)
// Created: 2012-10-30
// 
// !!! ע�� !!!
//	���ļ����ڶ�����Ϸ������ȫ��ö��
//////////////////////////////////////////////////////////////////////////
#ifndef _MAPGROUP_SHARE_ENUM_DEF_H_
#define _MAPGROUP_SHARE_ENUM_DEF_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../../common/common.h"

enum ENUM_MSGPORT_TYPE
{
	MSGPORT_SHELL		= 0,	// �Ի���
	MSGPORT_SOCKET		= 1,	// �ײ�ͨѶ
	MSGPORT_LOGIN		= 2,	// ��½
	MSGPORT_GAME		= 3,	// ��Ϸ�߼�
	MSGPORT_RELATION	= 4,	// ��������ͨ��
	MSGPORT_AI			= 5,	// AIͨ��

	MSGPORT_SIZE,				// �ܵ�����
	MSGPORT_DEFAULT		= 999,	// Ĭ���߳�ID, ��ö�ٲ�����Ϊ�̼߳�ͨ�Žӿ�ʹ��
};

// �˺��߳���־
enum ACCOUNT_KICK_FLAG
{
	ACCOUNT_KICK_FLAG_NONE		= 0x0000,
	ACCOUNT_KICK_FLAG_SOCKET	= 0x0001,
	ACCOUNT_KICK_FLAG_GAME		= 0x0002,
	ACCOUNT_KICK_FLAG_RELATION	= 0x0004,
	ACCOUNT_KICK_FLAG_OK		= ACCOUNT_KICK_FLAG_SOCKET | ACCOUNT_KICK_FLAG_GAME | ACCOUNT_KICK_FLAG_RELATION,
};

// ��¼ʱ�˺�״̬
enum ACCOUNT_LOGIN_FLAG
{
	ACCOUNT_LOGIN_FLAG_WAIT_KICK,
	ACCOUNT_LOGIN_FLAG_WAIT_CHOOSE,
	ACCOUNT_LOGIN_FLAG_WAIT_ENTER,
	ACCOUNT_LOGIN_FLAG_OK,
};

// �߳�ԭ��
enum KICK_REASON
{
	KICK_REASON_DEFAULT					= 0,	// �߳�Ĭ��ֵ, һ�㲻Ҫ�����ֵ
	KICK_REASON_PASSWORD_ERROR			= 1,	// �������
	KICK_REASON_BE_KICK_ANOTHER			= 2,	// ��������
	KICK_REASON_RELATION_SERVER			= 3,	// ��ϵ������ָʾ�㱻����
	KICK_REASON_FULL					= 4,	// ��̫��
	KICK_REASON_SYSTEM					= 5,	// ����������������� �� GM����	
	KICK_REASON_NOT_ALLOW				= 6,	// ������δ������½����
	KICK_REASON_GM_MAC_ERROR			= 7,	// GM����Mac��ַ��֤����		
	KICK_REASON_CHECK_SPEED_TOO_FAST	= 8,	// ����ٶȹ���					**
	KICK_REASON_GMCMD					= 9,	// GM�������Լ�	
	KICK_REASON_LOGIN_TIMEOUT			= 10,	// ��½���̳�ʱ
	KICK_REASON_ACCOUNT_STOP_BYTIME		= 11,	// �˺���ʱ��ͣ
	KICK_REASON_ACCOUNT_STOP_FOREVER	= 12,	// �˺����÷�ͣ

};

// user���ڴ�����ö��
enum MEMORY_DATA_ATTR_USER
{
	mdaUser_BEGIN = 0,

	mdaUser_AccountType,
	mdaUser_AccountStatus,
	mdaUser_AccountStatusParam,

	mdaUser_OnTimer_EverySecond,
	mdaUser_OnTimer_MinuteSecond,

	mdaUser_OnlineSecond,

	mdaUser_GmMacPass,

	mdaUser_END,
};

// UserAttr
enum USER_ATTR_TYPE
{
	USER_ATTR_TYPE_LEV			  = 1,	// ��ɫ�ȼ�
	USER_ATTR_TYPE_EXP			  = 2,	// ��ɫ����
	USER_ATTR_TYPE_STOP_TALK_TIME = 3,	// ����ʱ��
	USER_ATTR_TYPE_POKER_MAX_LEV  = 4,	// �������ȼ�
};

// ��Ϣ���ͷ�Χ
enum SEND_RANGE_TYPE
{
	SEND_RANGE_TYPE_BEGIN			= 0,
	SEND_RANGE_TYPE_USER			= 1,	// ���
	SEND_RANGE_TYPE_SYNDICATE		= 2,	// ����
	SEND_RANGE_TYPE_SERVER_GROUP	= 3,	// ��������
	SEND_RANGE_TYPE_END,
};

// ������Ӫ
enum POKER_CAMP
{
	POKER_CAMP_XIAN = 1,	// ��
	POKER_CAMP_MO	= 2,	// ħ
	POKER_CAMP_FO	= 3,	// ��
};

// ����վλ
enum POKER_FIGHT_POS
{
	POKER_FIGHT_POS_1ST = 1,	// ǰ��
	POKER_FIGHT_POS_2ND = 2,	// ����
	POKER_FIGHT_POS_3RD = 3,	// ����
};

// ����ȼ�����
enum LEV_EXP_TYPE
{
	LEV_EXP_TYPE_USER			= 1,	// ��ɫ
	LEV_EXP_TYPE_POKER			= 2,	// ����
	LEV_EXP_TYPE_VIP			= 3,	// VIP
	LEV_EXP_TYPE_SYN_GIFTBOX	= 4,	// �������
};

// ����װ��λ��
enum EQUIP_POS
{
	EQUIP_POS_BEGIN			= 0,
	EQUIP_POS_WEAPON		= 1,	// ����
	EQUIP_POS_HELMET		= 2,	// ͷ��
	EQUIP_POS_NECKLACE		= 3,	// ����
	EQUIP_POS_WAISTBAND		= 4,	// ����
	EQUIP_POS_CLOTHES		= 5,	// �·�
	EQUIP_POS_SHOES			= 6,	// Ь��
	EQUIP_POS_END,
};

// ����λ��
enum MAGIC_POS
{
	MAGIC_POS_BEGIN			= 0,
	MAGIC_POS_SP			= 1,	// �ؼ�
	MAGIC_POS_AUTO1			= 2,	// �Զ�����1
	MAGIC_POS_AUTO2			= 3,	// �Զ�����2
	MAGIC_POS_AUTO3			= 4,	// �Զ�����3
	MAGIC_POS_JOINT			= 5,	// ��Я����
	MAGIC_POS_END,
};

// װ����������
enum EQUIP_ATTR_TYPE
{
	EQUIP_ATTR_TYPE_BEGIN			= 1,
	EQUIP_ATTR_TYPE_LEV1_LIFE		= EQUIP_ATTR_TYPE_BEGIN,// һ������	����
	EQUIP_ATTR_TYPE_LEV1_MANA		= 2,					// һ������	ħ��
	EQUIP_ATTR_TYPE_LEV1_STR		= 3,					// һ������	����
	EQUIP_ATTR_TYPE_LEV1_STA		= 4,					// һ������	����
	EQUIP_ATTR_TYPE_LEV1_DEX		= 5,					// һ������	����

	EQUIP_ATTR_TYPE_LEV2_HP			= 6,					// �������� ��Ѫ
	EQUIP_ATTR_TYPE_LEV2_SP			= 7,					// ��������	��ŭ
	EQUIP_ATTR_TYPE_LEV2_HIT		= 8,					// ��������	����
	EQUIP_ATTR_TYPE_LEV2_ATK		= 9,					// ��������	�˺�
	EQUIP_ATTR_TYPE_LEV2_DEF		= 10,					// ��������	����
	EQUIP_ATTR_TYPE_LEV2_SPD		= 11,					// ��������	�ٶ�
	EQUIP_ATTR_TYPE_LEV2_DODGE		= 12,					// ��������	����
	EQUIP_ATTR_TYPE_LEV2_MAGIC		= 13,					// ��������	����

	EQUIP_ATTR_TYPE_SPECIAL_HP_RECOVER			= 14,	// �������� ��Ѫ�ظ�
	EQUIP_ATTR_TYPE_SPECIAL_SP_RECOVER			= 15,	// ��������	��ŭ�ظ�
	EQUIP_ATTR_TYPE_SPECIAL_PHY_CRIT			= 16,	// ��������	�ﱩ
	EQUIP_ATTR_TYPE_SPECIAL_MAG_CRIT			= 17,	// ��������	����
	EQUIP_ATTR_TYPE_SPECIAL_VAMPIRE_LEV			= 18,	// ��������	��Ѫ�ȼ�
	EQUIP_ATTR_TYPE_SPECIAL_SP_SPEND_DECREASE	= 19,	// ��������	��ŭ���Ľ���%
	EQUIP_ATTR_TYPE_SPECIAL_CURE_INCREASE		= 20,	// ��������	���Ƽ���Ч�����%

	EQUIP_ATTR_TYPE_BASE_ALL		= 21,					// һ��ȫ���ԣ�ת��һ�����ԣ�

	EQUIP_ATTR_TYPE_END,
};

enum POKER_ATTR								// �����ڴ�����
{
	POKER_ATTR_BEGIN = 0,
	
	POKER_ATTR_SCORE,						// ս��
	POKER_ATTR_LEV1_LIFE,					// һ������	����
	POKER_ATTR_LEV1_MANA,					// һ������	ħ��
	POKER_ATTR_LEV1_STR,					// һ������	����
	POKER_ATTR_LEV1_STA,					// һ������	����
	POKER_ATTR_LEV1_DEX,					// һ������	����

	POKER_ATTR_LEV2_HP,						// �������� ��Ѫ
	POKER_ATTR_LEV2_SP,						// ��������	��ŭ
	POKER_ATTR_LEV2_HIT,					// ��������	����
	POKER_ATTR_LEV2_ATK,					// ��������	�˺�
	POKER_ATTR_LEV2_DEF,					// ��������	����
	POKER_ATTR_LEV2_SPD,					// ��������	�ٶ�
	POKER_ATTR_LEV2_DODGE,					// ��������	����
	POKER_ATTR_LEV2_MAGIC,					// ��������	����

	POKER_ATTR_SPECIAL_HP_RECOVER,			// �������� ��Ѫ�ظ�
	POKER_ATTR_SPECIAL_SP_RECOVER,			// ��������	��ŭ�ظ�
	POKER_ATTR_SPECIAL_PHY_CRIT,			// ��������	�ﱩ
	POKER_ATTR_SPECIAL_MAG_CRIT,			// ��������	����
	POKER_ATTR_SPECIAL_VAMPIRE_LEV,			// ��������	��Ѫ�ȼ�
	POKER_ATTR_SPECIAL_SP_SPEND_DECREASE,	// ��������	��ŭ���Ľ���%
	POKER_ATTR_SPECIAL_CURE_INCREASE,		// ��������	���Ƽ���Ч�����%

	POKER_ATTR_BASE_ALL,					// һ��ȫ���ԣ�ת��һ�����ԣ�
	POKER_ATTR_END,

	// ���������������¼���½�ɫ��ǰ�Ŀ�����������, ��Ҫ������һ��ͬ��, 
	POKER_OLD_ATTR_BEGIN = POKER_ATTR_END,
	POKER_OLD_ATTR_SCORE,

	POKER_OLD_ATTR_LEV1_LIFE,
	POKER_OLD_ATTR_LEV1_MANA,
	POKER_OLD_ATTR_LEV1_STR,
	POKER_OLD_ATTR_LEV1_STA,
	POKER_OLD_ATTR_LEV1_DEX,

	POKER_OLD_ATTR_LEV2_HP,
	POKER_OLD_ATTR_LEV2_SP,
	POKER_OLD_ATTR_LEV2_HIT,
	POKER_OLD_ATTR_LEV2_ATK,
	POKER_OLD_ATTR_LEV2_DEF,
	POKER_OLD_ATTR_LEV2_SPD,
	POKER_OLD_ATTR_LEV2_DODGE,
	POKER_OLD_ATTR_LEV2_MAGIC,

	POKER_OLD_ATTR_SPECIAL_HP_RECOVER,
	POKER_OLD_ATTR_SPECIAL_SP_RECOVER,
	POKER_OLD_ATTR_SPECIAL_PHY_CRIT,
	POKER_OLD_ATTR_SPECIAL_MAG_CRIT,
	POKER_OLD_ATTR_SPECIAL_VAMPIRE_LEV,
	POKER_OLD_ATTR_SPECIAL_SP_SPEND_DECREASE,
	POKER_OLD_ATTR_SPECIAL_CURE_INCREASE,

	POKER_OLD_ATTR_BASE_ALL,
	POKER_OLD_ATTR_END,

	// ���������������¼װ���ӳ����ԣ����ս����ڿ������ԣ�������Ҫͬ�����ͻ���
	POKER_EQUIP_ADD_ATTR_BEGIN,
	POKER_EQUIP_ADD_ATTR_STAR_SCORE,				// װ���Ǽ��ӳ�ս��

	POKER_EQUIP_ADD_ATTR_LEV1_LIFE,					// ��װ���ӳɣ�һ������	����
	POKER_EQUIP_ADD_ATTR_LEV1_MANA,					// ��װ���ӳɣ�һ������	ħ��
	POKER_EQUIP_ADD_ATTR_LEV1_STR,					// ��װ���ӳɣ�һ������	����
	POKER_EQUIP_ADD_ATTR_LEV1_STA,					// ��װ���ӳɣ�һ������	����
	POKER_EQUIP_ADD_ATTR_LEV1_DEX,					// ��װ���ӳɣ�һ������	����

	POKER_EQUIP_ADD_ATTR_LEV2_HP,					// ��װ���ӳɣ��������� ��Ѫ
	POKER_EQUIP_ADD_ATTR_LEV2_SP,					// ��װ���ӳɣ���������	��ŭ
	POKER_EQUIP_ADD_ATTR_LEV2_HIT,					// ��װ���ӳɣ���������	����
	POKER_EQUIP_ADD_ATTR_LEV2_ATK,					// ��װ���ӳɣ���������	�˺�
	POKER_EQUIP_ADD_ATTR_LEV2_DEF,					// ��װ���ӳɣ���������	����
	POKER_EQUIP_ADD_ATTR_LEV2_SPD,					// ��װ���ӳɣ���������	�ٶ�
	POKER_EQUIP_ADD_ATTR_LEV2_DODGE,				// ��װ���ӳɣ���������	����
	POKER_EQUIP_ADD_ATTR_LEV2_MAGIC,				// ��װ���ӳɣ���������	����

	POKER_EQUIP_ADD_ATTR_SPECIAL_HP_RECOVER,		// ��װ���ӳɣ��������� ��Ѫ�ظ�
	POKER_EQUIP_ADD_ATTR_SPECIAL_SP_RECOVER,		// ��װ���ӳɣ���������	��ŭ�ظ�
	POKER_EQUIP_ADD_ATTR_SPECIAL_PHY_CRIT,			// ��װ���ӳɣ���������	�ﱩ
	POKER_EQUIP_ADD_ATTR_SPECIAL_MAG_CRIT,			// ��װ���ӳɣ���������	����
	POKER_EQUIP_ADD_ATTR_SPECIAL_VAMPIRE_LEV,		// ��װ���ӳɣ���������	��Ѫ�ȼ�
	POKER_EQUIP_ADD_ATTR_SPECIAL_SP_SPEND_DECREASE,	// ��װ���ӳɣ���������	��ŭ���Ľ���%
	POKER_EQUIP_ADD_ATTR_SPECIAL_CURE_INCREASE,		// ��װ���ӳɣ���������	���Ƽ���Ч�����%

	POKER_EQUIP_ADD_ATTR_BASE_ALL,					// ��װ���ӳɣ�һ��ȫ���ԣ�ת��һ�����ԣ�
	POKER_EQUIP_ADD_ATTR_END,
};

enum MSG_POKER_ATTR_TYPE				// ��������ͬ����Ϣ����
{
	MSG_POKERATTR_BEGIN					= 0,

	MSG_POKERATTR_LIFE					= 1,	// һ������	����
	MSG_POKERATTR_MANA					= 2,	// һ������	ħ��
	MSG_POKERATTR_STR					= 3,	// һ������	����
	MSG_POKERATTR_STA					= 4,	// һ������	����
	MSG_POKERATTR_DEX					= 5,	// һ������	����

	MSG_POKERATTR_HP					= 6,	// �������� ��Ѫ
	MSG_POKERATTR_SP					= 7,	// ��������	��ŭ
	MSG_POKERATTR_HIT					= 8,	// ��������	����
	MSG_POKERATTR_ATK					= 9,	// ��������	�˺�
	MSG_POKERATTR_DEF					= 10,	// ��������	����
	MSG_POKERATTR_SPD					= 11,	// ��������	�ٶ�
	MSG_POKERATTR_DODGE					= 12,	// ��������	����
	MSG_POKERATTR_MAGIC					= 13,	// ��������	����

	MSG_POKERATTR_HP_RECOVER			= 14,	// �������� ��Ѫ�ظ�
	MSG_POKERATTR_SP_RECOVER			= 15,	// ��������	��ŭ�ظ�
	MSG_POKERATTR_PHY_CRIT				= 16,	// ��������	�ﱩ
	MSG_POKERATTR_MAG_CRIT				= 17,	// ��������	����
	MSG_POKERATTR_VAMPIRE_LEV			= 18,	// ��������	��Ѫ�ȼ�
	MSG_POKERATTR_SP_SPEND_DECREASE		= 19,	// ��������	��ŭ���Ľ���%
	MSG_POKERATTR_CURE_INCREASE			= 20,	// ��������	���Ƽ���Ч�����%

	MSG_POKERATTR_BASE_ALL				= 21,	// һ��ȫ����

	MSG_POKERATTR_EQUIP_STAR_ADD_SCORE	= 99,	// װ���Ǽ��ӳ�ս��
	MSG_POKERATTR_SCORE					= 100,	// ��ս��

	MSG_POKERATTR_LEV					= 101,	// �ȼ�		
	MSG_POKERATTR_EXP					= 102,	// ����
	MSG_POKERATTR_STAR					= 103,	// �Ǽ�
	MSG_POKERATTR_COLOR					= 104,	// ��ɫ

	MSG_POKERATTR_LIFE_GROW				= 105,	// ���ʳɳ�
	MSG_POKERATTR_MANA_GROW				= 106,	// ħ���ɳ�
	MSG_POKERATTR_STR_GROW				= 107,	// �����ɳ�
	MSG_POKERATTR_STA_GROW				= 108,	// �����ɳ�
	MSG_POKERATTR_DEX_GROW				= 109,	// ���ݳɳ�

	MSG_POKERATTR_STATE					= 110,	// ״̬

	MSG_POKERATTR_END,
};

enum UPDATEATTRSYNTYPE				// ���Ƹ���ͬ������
{
	UAST_ALL,						// Ĭ��
	UAST_ALL_SYNC,					// ǿ��ȫ������ͬ�����ͻ���
	UAST_ALL_NOT_SYNC,				// ȫ������, ���ǲ�ͬ���ͻ���
	UAST_ALL_SYNC_CLEAN_OLD,		// ǿ����������Բ�ͬ��
	UAST_ALL_UP_LEV,				// ����
	UAST_ALL_UP_STAR,				// ����
	UAST_ALL_UP_COLOR,				// ����
	UAST_ALL_UP_MAGIC,				// ����
	UAST_ALL_EQUIP,					// װ��
	UAST_ALL_UP_EQUIP_STAR,			// װ�����ǣ���ħ��
};

enum POKER_STATE						// ����״̬
{
	POKER_STATE_NONE					= 0,	// ����
	POKER_STATE_MINE					= 1,	// �ڿ�
	POKER_STATE_MERCENARY				= 2,	// ��Ӫ
};

enum SKILL_SORT							// ���ܷ���
{
	SKILL_SORT_ACTIVE					= 1,	// ��������
	SKILL_SORT_PASSIVE					= 2,	// ��������
	SKILL_SORT_JOINT					= 3,	// ��Я����
};

enum SKILLPROPERTY_CONTROL				// �������Կ��Ʒ���
{
	SKILLPROPERTY_CONTROL_BEGIN			= 0,
	SKILLPROPERTY_CONTROL_ADD			= 1,	// ����
	SKILLPROPERTY_CONTROL_DEC			= 2,	// ����
	SKILLPROPERTY_CONTROL_ADD_DECIMALS	= 3,	// �ۼӾ�ȷ��0.01��С��
	SKILLPROPERTY_CONTROL_END,
};

enum LOTTERY_TYPE							// �齱����
{
	LOTTERY_TYPE_BEGIN						= 0,
	LOTTERY_TYPE_MONEY						= 1,	// ��ҳ齱
	LOTTERY_TYPE_MONEY_SERIES				= 2,	// �������
	LOTTERY_TYPE_VAS						= 3,	// Ԫ���齱
	LOTTERY_TYPE_VAS_SERIES					= 4,	// Ԫ������
	LOTTERY_TYPE_VIP						= 5,	// VIP�ʸ�齱
	LOTTERY_TYPE_CHAPMAN_SMALL				= 6,	// �Ǽ���������С��
	LOTTERY_TYPE_CHAPMAN_MIDDLE				= 7,	// �Ǽ����������г�
	LOTTERY_TYPE_CHAPMAN_BIG				= 8,	// �Ǽ��������˴��

	LOTTERY_TYPE_VAS_FIXED					= 9,	// Ԫ���齱(��һ�λ�������)
	LOTTERY_TYPE_VAS_SERIES_FIXED			= 10,	// Ԫ������(��һ�λ�������)
	LOTTERY_TYPE_MONEY_FIXED				= 11,	// ��ҳ齱(��һ�λ�������)
	LOTTERY_TYPE_MONEY_SERIES_FIXED			= 12,	// �������(��һ�λ�������)
	LOTTERY_TYPE_END,
};

enum EUSERMASKTYPE					// ��������
{
	EUMT_Begin				= 0,
	EUMT_TaskMask			= 1,	// ��������
	EUMT_GiveMask			= 2,	// ��������
	EUMT_DayMask			= 3,	// ������
	EUMT_WeekMask			= 4,	// ������
	EUMT_MonthMask			= 5,	// ������
	EUMT_End,
};

// ��Ʒǰ׺����, ���λ
enum ITEMTYPE_HEADER
{
	ITEMTYPE_HEADER_NONE		= 0,
	ITEMTYPE_HEADER_EQUIP		= 1,	// װ��
	ITEMTYPE_HEADER_EQUIP_CHIP	= 2,	// װ����Ƭ				��װ��ֻ����λ��ͬ

	ITEMTYPE_HEADER_ONLYLOG		= 9,	// ������¼��־��Ʒ		�����ɸ�������Ʒ
};

// ��Ʒ����
enum ITEMTYPE_SORT
{
	ITEMTYPE_SORT_NONE			= 0,
	ITEMTYPE_SORT_UPSTAR		= 1,	// ���ǲ���				data1��ʾ �����ṩ���ǵ���
	ITEMTYPE_SORT_HERO_EXP		= 2,	// Ӣ�۾���				data1��ʾ �������Ӣ�۾���
	ITEMTYPE_SORT_GHOST_STONE	= 3,	// ���ʯ			
	ITEMTYPE_SORT_CLEANSCROLL	= 4,	// ɨ������
	ITEMTYPE_SORT_CHIP			= 5,	// ��Ʒ��Ƭ
	ITEMTYPE_SORT_POWER			= 6,	// ������Ʒ				data1��ʾ ����������������
};

// ��Ʒ��ɫ
enum ITEMCOLOR
{
	ITEMCOLOR_NONE		= 0,
	ITEMCOLOR_WHITE 	= 1,	// ��
	ITEMCOLOR_GREEN		= 2,	// ��
	ITEMCOLOR_BLUE		= 3,	// ��
	ITEMCOLOR_VIOLET	= 4,	// ��
	ITEMCOLOR_ORANGE	= 5,	// ��
};

// ��Ʒmonopoly ����
enum ITEMTYPE_MONOPOLY
{
	ITEMTYPE_MONOPOLY_NONE				= 0x0000,
	ITEMTYPE_MONOPOLY_NEED_RECORD		= 0x0001,				// ��Ҫд���¼����

};

// ��������
enum DROP_RULE_TYPE
{
	DROP_RULE_TYPE_ONCE			= 1,	// һ�ι���, ���Ȩ�ط���
	DROP_RULE_TYPE_MORE			= 2,	// ��ι���, ÿ�ζ�����Ȩ�ط���
	DROP_RULE_TYPE_NOT_REPEAT	= 3,	// ���ظ�����
};

// ����������
enum DROP_RULE_GROUP_TYPE
{
	DROP_RULE_GROUP_TYPE_NONE			= 0,
	DROP_RULE_GROUP_TYPE_MONEY_BEGIN	= 100,		// ���� begin
	DROP_RULE_GROUP_TYPE_MONEY_END		= 999,		// ���� end
	DROP_RULE_GROUP_TYPE_POKER_BEGIN	= 10000,	// ���� begin
	DROP_RULE_GROUP_TYPE_POKER_END		= 99999,	// ���� end
	DROP_RULE_GROUP_TYPE_ITEMTYPE_BEGIN	= 100000,	// itemtype begin
	DROP_RULE_GROUP_TYPE_ITEMTYPE_END	= 999999,	// itemtype end
};

// �����������, Ĭ��0����ֱ�Ӹ����
enum DROP_RULE_GROUP_GROUP
{
	DROP_RULE_GROUP_GROUP_USER = 0,
	DROP_RULE_GROUP_GROUP_WARROAD_AWARD = 1,	// �Ŷ�ս��ս��Ʒ
};

// ս���������
enum BATTLE_RESULT_TYPE
{
	BATTLE_RESULT_TYPE_SUC			= 0,	// ��������
	BATTLE_RESULT_TYPE_GIVE_UP		= 1,	// ��;�˳�
	BATTLE_RESULT_TYPE_TIME_OUT		= 2,	// ս����ʱ
};

// ս������
enum BATTLE_SORT
{
	BATTLE_SORT_NONE				= 0,
	BATTLE_SORT_NORMAL				= 1,	// ����
	BATTLE_SORT_BOSS				= 2,	// bossս��
	BATTLE_SORT_PVP					= 3,	// pvp
	BATTLE_SORT_INSTANCE			= 4,	// ����
	BATTLE_SORT_GOOSE_TOWER			= 5,	// ������
	BATTLE_SORT_ARENA				= 6,	// ������
	BATTLE_SORT_TERRITORY			= 7,	// ���ս
	BATTLE_SORT_PUZZLE				= 8,	// �Թ�ս��
	BATTLE_SORT_MINE				= 9,	// ��ս��
	BATTLE_SORT_WARROAD_NORMAL		= 10,	// ��ͨս��
	BATTLE_SORT_WARROAD_DIFFICULTY	= 11,	// ��Ӣս��
	BATTLE_SORT_WARROAD_TEAM		= 12,	// �Ŷ�ս��
	BATTLE_SORT_NTM_FIGHT			= 13,	// �����Ŷ���
	BATTLE_SORT_NTM_MONSTER			= 14,	// �����Ź���
};

// ��սboss ͨ������
enum CHALLENGE_BOSS_RESULT
{
	CHALLENGE_BOSS_RESULT_Beg		= 0,
	CHALLENGE_BOSS_RESULT_FAIL		= CHALLENGE_BOSS_RESULT_Beg,	// ��սʧ��
	CHALLENGE_BOSS_RESULT_START1	= 1,							// 1��
	CHALLENGE_BOSS_RESULT_START2	= 2,							// 2��
	CHALLENGE_BOSS_RESULT_START3	= 3,							// 3��
	CHALLENGE_BOSS_RESULT_End,
};

enum EUSER_TEMPDATA_PROGRAM
{
	EUTDP_BEGIN							= 10000,	// �������õ�TMP_ID��10000��ʼ
	// 10000 - 10100�����ͻ���ʹ��BEG
	EUTDP_CLIENT_BEGIN					= EUTDP_BEGIN,
	EUTDP_CLIENT_END					= 10100,
	// 10000 - 10100�����ͻ���ʹ��END

	// ����˴�10101��ʼ
	EUTDP_SERVER_BEGIN					= 10101,
	EUTDP_SERVER_POKER_MAGICPOINT_INFO	= 10102,	// ���Ƽ��ܵ���Ϣ��data0��ʾ�ϴλָ����ܵ�utcʱ�䣬data1��ʾ���칺���ܵ������data2��ʾ�ϴι����ܵ�����
	EUTDP_SERVER_MONEYTREE_INFO			= 10103,	// ҡǮ���ݣ�data0��ʾ����ҡǮ������data1��ʾ�ϴ�ҡǮ����
	EUTDP_SERVER_SIGN_INFO				= 10104,	// ǩ�����ݣ�data0��ʾ����ǩ��������data1��ʾ�����Ƿ�ǩ����data2��ʾ�����Ƿ���ȡVIPǩ��������data3��ʾǩ��ʱ��
	EUTDP_SERVER_LOTTERY_INFO			= 10105,	// �齱���ݣ�data0��ʾ����´γ齱ʱ�䣬data1��ʾԪ���´γ齱ʱ�䣬data2��ʾ�齱���˳���ʱ�䣬data3��ʾ���������������
	EUTDP_SERVER_MERCENARY_INFO			= 10106,	// Ӷ�����ݣ�data0��ʾ���չ�Ӷ�����룬data1��ʾ������Ӫ������
	EUTDP_SERVER_CROSS_NTM_INFO			= 10107,	// �����Ŷ������ݣ�data0��ʾ�ϴν���ķ���id��data1��ʾ�ϴ��뿪ʱ��,data2��ʾ��ս���Ի�õĻ���
	EUTDP_SERVER_POWER_INFO				= 10108,	// ��������:data0��ʾ�ϴλָ�����ʱ��(utc), data1��ʾ���칺�������data2��ʾ�ϴι�������

	EUTDP_SERVER_SHOP_BEGIN				= 10111,
	EUTDP_SERVER_SHOP_ARENA				= 10111,	// �������̵�����: data0��ʾ�Ƿ�ˢ�¹����̵�(1�ǣ�0��)��data1��ʾ�����ֶ�ˢ�´�����data2��ʾ�ϴ��ֶ�ˢ�����ڣ�data3��ʾ��һ���Զ�ˢ��ʱ��(utc),data4��ʾ��һ���Զ�ˢ��ʱ��(utc)
	EUTDP_SERVER_SHOP_TEAMS_ARENA		= 10112,	// ��Ӿ������̵�����: data0��ʾ�Ƿ�ˢ�¹����̵�(1�ǣ�0��)��data1��ʾ�����ֶ�ˢ�´�����data2��ʾ�ϴ��ֶ�ˢ�����ڣ�data3��ʾ��һ���Զ�ˢ��ʱ��(utc),data4��ʾ��һ���Զ�ˢ��ʱ��(utc)
	EUTDP_SERVER_SHOP_TOWER				= 10113,	// �������̵�����: data0��ʾ�Ƿ�ˢ�¹����̵�(1�ǣ�0��)��data1��ʾ�����ֶ�ˢ�´�����data2��ʾ�ϴ��ֶ�ˢ�����ڣ�data3��ʾ��һ���Զ�ˢ��ʱ��(utc),data4��ʾ��һ���Զ�ˢ��ʱ��(utc)
	EUTDP_SERVER_SHOP_SYN				= 10114,	// �����̵�����: data0��ʾ�Ƿ�ˢ�¹����̵�(1�ǣ�0��)��data1��ʾ�����ֶ�ˢ�´�����data2��ʾ�ϴ��ֶ�ˢ�����ڣ�data3��ʾ��һ���Զ�ˢ��ʱ��(utc),data4��ʾ��һ���Զ�ˢ��ʱ��(utc)
	EUTDP_SERVER_SHOP_REFRESH			= 10115,	// ˢ���̵�����: data0��ʾ�Ƿ�ˢ�¹����̵�(1�ǣ�0��)��data1��ʾ�����ֶ�ˢ�´�����data2��ʾ�ϴ��ֶ�ˢ�����ڣ�data3��ʾ��һ���Զ�ˢ��ʱ��(utc),data4��ʾ��һ���Զ�ˢ��ʱ��(utc)
	EUTDP_SERVER_SHOP_BLACK_MARKET		= 10116,	// �����̵�����: data0��ʾ�Ƿ�ˢ�¹����̵�(1�ǣ�0��)��data1��ʾ�����ֶ�ˢ�´�����data2��ʾ�ϴ��ֶ�ˢ������,data3��ʾ��һ���Զ�ˢ��ʱ��(utc),data4��ʾ��һ���Զ�ˢ��ʱ��(utc),data5��ʾ�̵����ʱ��(utc)
	EUTDP_SERVER_SHOP_FRIENDSHIP		= 10117,	// ������̵�����: data0��ʾ�Ƿ�ˢ�¹����̵�(1�ǣ�0��)��data1��ʾ�����ֶ�ˢ�´�����data2��ʾ�ϴ��ֶ�ˢ������,data3��ʾ��һ���Զ�ˢ��ʱ��(utc),data4��ʾ��һ���Զ�ˢ��ʱ��(utc),data5��ʾ�̵����ʱ��(utc)
	EUTDP_SERVER_SHOP_END				= 10131,

	EUTDP_SERVER_CHALLENGE_BOSS			= 10132,	// ��սboss: data0��ʾ����ս�ɹ�����, data1:��ʾˢ����ս��������, data2:��ʾ��ս����(���ܳɹ�ʧ��)
	EUTDP_SERVER_GOOSE_TOWER			= 10133,	// ������:   data0��ʾ��ǰ����ս����, data1��ʾ���������ô���, data2��ʾ����ʱ��
	EUTDP_SERVER_JOIN_SYNDICATE			= 10134,	// ������ɼ�¼����, data0-5��¼����������������ʱ����id
	EUTDP_SERVER_QUIT_SYNDICATE			= 10135,	// �뿪���ɼ�¼����, data0-5��¼����뿪���������ʱ����id
	EUTDP_SERVET_PUZZLE_DATA			= 10136,	// �Թ�:data0��ʾ�Թ����ͣ�data1��ʾ�Թ��Ѷȣ�data2��ʾ�Թ���Σ�data3��ʾս�����кţ�data4��ʾ��һ���ӣ�data5��ʾ��ǰ���ӣ�data6��ʾ�ܽ��ȣ�data7��ʾutcʱ��
	EUTDP_SERVER_PUZZLE_POKER			= 10137,	// �Թ�:data0��ʾ�Թ����ͣ�data1-data5��ʾ5�ų�ս����ID
	EUTDP_SERVER_PUZZLE_YAO				= 10138,	// �Թ�(��): data0��ʾ��ǰ������data1��ʾ�ϴν�������
	EUTDP_SERVER_PUZZLE_GUI				= 10139,	// �Թ�(��): data0��ʾ��ǰ������data1��ʾ�ϴν�������
	EUTDP_SERVER_PUZZLE_MO				= 10140,	// �Թ�(ħ): data0��ʾ��ǰ������data1��ʾ�ϴν�������
	EUTDP_SERVER_TOPLIST_BEGIN			= 10141,
	EUTDP_SERVER_TOPLIST_ARENA			= 10141,	// ���Ӿ��������ݣ�data0��������ս������data1�ϴ���սʱ��utc, data2�ϴ���ս����, data3��սCD���ñ�ʶ(0Ĭ����CD��1��CD��,data4��ʷ�������
	EUTDP_SERVER_TOPLIST_MULTI_ARENA	= 10142,	// ��Ӿ��������ݣ�data0��������ս������data1�ϴ���սʱ��utc, data2�ϴ���ս���ڣ�data3��սCD���ñ�ʶ(0Ĭ����CD��1��CD)
	EUTDP_SERVER_INSTANCE_INFO			= 10143,	// ������ս��Ϣ: data0��ʾ��ǰ���ͣ�data1��ʾ��ǰ�Ѷȣ�data2��ʾ��ʼʱ��
	EUTDP_SERVER_WAR_ROAD_INFO			= 10144,	// ս����ս��Ϣ: data0��ʾ��ǰģʽ��data1��ʾ��ǰ�½ڣ�data2��ʾ��ǰ�ؿ���data3��ʾ��ʼʱ��

	EUTDP_SERVER_MINE_INFO				= 10151,	// ��:data0��ʾ��һ���������Ŀ�ID��data1��ʾÿ����������, data2��ʾ�ϴ���������, data3��ʾ�ϴλָ�Ѱ������ʱ��(utc)
	EUTDP_SERVER_MINE_FIGHT				= 10152,	// ��:data0:��ʼ��սʱ��,data1:��ǰ����ս��,data2:��ǰ����ս��Ա,data3��ʾսʤ����,data4:��սʤ��ԱID1��data5:��սʤ��ԱID2��data6����սʤ��ԱID3
	EUTDP_SERVER_SYN_WORSHIP			= 10154,	// ����Ĥ�ݴ���: data0:������Ĥ�ݴ���, data1:ˢ��Ĥ�ݴ�������
	EUTDP_SERVER_FRIEND_INVITE			= 10155,	// ��������: data0:������ID, data1:��ȡ���պ��ѵ�½����ʱ��, data2:�����½���Ѹ���, data3:����������ʱ��
	EUTDP_SERVER_MINE_FIGHT_RES			= 10156,	// ��ս��������Դ:data0:�Ƿ���ȡ(1��ʾ��ȡ),data1:��Ա1��Դ����,data2:��Ա1��ʯ����,data3:��Ա2��Դ����,data4:��Ա2��ʯ����,data5:��Ա3��Դ����,data6:��Ա3��ʯ����,data7:��Դ����
	EUTDP_SERVER_MSG_SWITCH				= 10157,	// ��Ϣ���Ϳ���: data0�Ķ�����λ0��31��ʾ:0:��ȡ����, 1:ˢ���̵�, 2:�����ظ���, 3:���ܵ�ظ���, 4:������������, 5:˽����Ϣ֪ͨ, 6,���Ѳ���֪ͨ[0:��, 1:��]; data1��ʾ�Ƿ��ʼ��
	EUTDP_SERVER_FRIEND					= 10157,	// ����: data0: ���ͺ���õ������

	EUTDP_END,
};

// ��������
enum EINSTANCETYPE
{
	EINSTANCETYPE_NONE		= 0,
	EINSTANCETYPE_MONEY		= 1,	// ��Ҹ���
	EINSTANCETYPE_EXP		= 2,	// ���鸱��
	EINSTANCETYPE_YAO		= 3,	// ������
	EINSTANCETYPE_GUI		= 4,	// ����
	EINSTANCETYPE_MO		= 5,	// ħ����
};

// �Թ�����
enum PUZZLE_TYPE_ENUM
{
	PUZZLE_TYPE_ENUM_Beg	= 2,
	PUZZLE_TYPE_ENUM_YAO	= 3,	// ��
	PUZZLE_TYPE_ENUM_GUI	= 4,	// ��
	PUZZLE_TYPE_ENUM_MO		= 5,	// ħ
	PUZZLE_TYPE_ENUM_End,
};

// �Թ��Ѷ�
enum PUZZLE_DIFFICULT_ENUM
{
	PUZZLE_DIFFICULT_Beg	= 0,
	PUZZLE_DIFFICULT_Low	= 1,	// �͵ȼ�
	PUZZLE_DIFFICULT_Middle = 2,	// �еȼ�
	PUZZLE_DIFFICULT_High	= 3,	// �ߵȼ�
	PUZZLE_DIFFICULT_End,
};

// �Թ�BUFF����
enum PUZZLE_BUFF_TYPE_ENUM
{
	PUZZLE_BUFF_Beg										= 0,
	// ����BUFF
	PUZZLE_ADDBUFF_Beg									= 1000,	
	PUZZLE_ADDBUFF_ATK_ADD_IN_FLOOR						= 1001,	// �ӹ���(������Ч)
	PUZZLE_ADDBUFF_ATK_ADD_IN_INSTANCE					= 1002,	// �ӹ���(������Ч)
	PUZZLE_ADDBUFF_DEF_ADD_IN_FLOOR						= 1003,	// �ӷ���(������Ч)
	PUZZLE_ADDBUFF_DEF_ADD_IN_INSTANCE					= 1004,	// �ӷ���(������Ч)
	PUZZLE_ADDBUFF_HP_ADD_IN_NEXT_FIGHT					= 1005,	// ��Ѫ(��һ��ս����Ч)
	PUZZLE_ADDBUFF_SP_ADD_IN_NEXT_FIGHT					= 1006,	// ��ŭ��(��һ��ս����Ч)
	PUZZLE_ADDBUFF_DEF_SUB_IN_FLOOR						= 1007,	// ���ͶԷ�����(������Ч)
	PUZZLE_ADDBUFF_DEF_SUB_IN_INSTANCE					= 1008,	// ���ͶԷ�����(������Ч)
	PUZZLE_ADDBUFF_ATK_SUB_IN_FLOOR						= 1009,	// ���ͶԷ�����(������Ч)
	PUZZLE_ADDBUFF_ATK_SUB_IN_INSTANCE					= 1010,	// ���ͶԷ�����(������Ч)
	PUZZLE_ADDBUFF_RECOVER_ADD_IN_FLOOR					= 1011,	// ÿ��ս����ָ�Ч���ӱ�(������Ч)
	PUZZLE_ADDBUFF_RECOVER_ADD_IN_INSTANCE				= 1012,	// ÿ��ս����ָ�Ч���ӱ�(������Ч)
	PUZZLE_ADDBUFF_End,
	
	// ����BUFF
	PUZZLE_SUBBUFF_Beg									= 2000,
	PUZZLE_SUBBUFF_HP_SUB_THIRTY_PERCENT_IN_NEXT_FIGHT	= 2001,	// Ѫ������30%(��һ��ս��)
	PUZZLE_SUBBUFF_SUB_ALL_ATK_AND_DEF_IN_NEXT_FIGHT	= 2002,	// ȫ�幥������(��һ��ս��)
	PUZZLE_SUBBUFF_SUB_ALL_ATK_AND_DEF_IN_FLOOR			= 2003,	// ȫ�幥������(������Ч)
	PUZZLE_SUBBUFF_CLEAR_ALL_SP_IN_NEXT_FIGHT			= 2004,	// �������ŭ��(��һ��ս��)
	PUZZLE_SUBBUFF_End,

	// ����BUFF
	PUZZLE_OTHERBUFF_Beg								= 3000,
	PUZZLE_OTHERBUFF_SHOW_TREASURE_IN_FLOOR				= 3001,	// ��ʾ���㱦��λ��(������Ч)
	PUZZLE_OTHERBUFF_SHOW_TREASURE_IN_INSTANCE			= 3002,	// ��ʾ���㱦��λ��(������Ч)
	PUZZLE_OTHERBUFF_SHOW_GIN_IN_FLOOR					= 3003,	// ��ʾ����(������Ч)
	PUZZLE_OTHERBUFF_SHOW_GIN_IN_INSTANCE				= 3004,	// ��ʾ����(������Ч)
	PUZZLE_OTHERBUFF_CLEAR_ONE_SUB_BUFF_AT_ONCE			= 3007,	// ���һ������BUFF(��ʱ)
	PUZZLE_OTHERBUFF_CLEAR_ALL_SUB_BUFF_AT_ONCE			= 3008,	// ������м���BUFF(��ʱ)
	PUZZLE_OTHERBUFF_CLEAR_ONE_ADD_BUFF_AT_ONCE			= 3009,	// ���һ������BUFF(��ʱ)
	PUZZLE_OTHERBUFF_End,

	PUZZLE_BUFF_End,
};

// �Թ���������
enum PUZZLE_INSTANCE
{
	PUZZLE_INSTANCE_BEGIN						= 0,
	PUZZLE_INSTANCE_TYPE						= 1,		// ��������	
	PUZZLE_INSTANCE_DIFFICULT					= 2,		// �����Ѷ�		
	PUZZLE_INSTANCE_FLOOR						= 3,		// �������
	PUZZLE_INSTANCE_FIGHT_NO					= 4,		// ս�����к�
	PUZZLE_INSTANCE_LAST_PUZZLE_ID				= 5,		// �ϴθ���				
	PUZZLE_INSTANCE_PUZZLE_ID					= 6 ,		// ��ǰ����			
	PUZZLE_INSTANCE_POKER1						= 7,		// ��ս��1				
	PUZZLE_INSTANCE_POKER2						= 8,		// ��ս��2					
	PUZZLE_INSTANCE_POKER3						= 9,		// ��ս��3				
	PUZZLE_INSTANCE_POKER4						= 10,		// ��ս��4					
	PUZZLE_INSTANCE_POKER5						= 11,		// ��ս��5				
	PUZZLE_INSTANCE_PROGRESS_TOTAL				= 12,		// ��������				
	PUZZLE_INSTANCE_BEG_TIME					= 13,		// ��ʼʱ��
	PUZZLE_INSTANCE_END,
};

// �Թ�������Ч����
enum PUZZLE_BUFF_EFFECT
{
	PUZZLE_BUFF_EFFECT_NONE						= 0,		
	PUZZLE_BUFF_EFFECT_AT_ONCE					= 1,		// ����
	PUZZLE_BUFF_EFFECT_NEXT_FIGHT				= 2,		// ��һ��ս��
	PUZZLE_BUFF_EFFECT_THIS_FLOOR				= 3,		// ����
	PUZZLE_BUFF_EFFECT_THIS_INSTANCE			= 4,		// ������
};

// �Թ���������
enum PUZZLE_TASK_TYPE
{
	PUZZLE_TASK_TYPE_NONE				= 0,
	PUZZLE_TASK_TYPE_MONSTER			= 1,	// ��
	PUZZLE_TASK_TYPE_TREASURE			= 2,	// ����
	PUZZLE_TASK_TYPE_TRANS_THIS_FLOOR	= 3,	// ���㴫��
	PUZZLE_TASK_TYPE_TRANS_NEXT_FLOOR	= 4,	// ��һ�㴫��
	PUZZLE_TASK_TYPE_BUFF				= 5,	// BUFF
	PUZZLE_TASK_TYPE_GIN				= 6,	// ����
};

// ���ɼ�����
enum SYNDICATE_JOIN_FLAG
{
	SYNDICATE_JOIN_FLAG_BEGIN = 0,
	SYNDICATE_JOIN_FLAG_OPEN = 0,		// ����, �����˿ɼ���
	SYNDICATE_JOIN_FLAG_APPLY = 1,		// ��Ҫ��֤
	SYNDICATE_JOIN_FLAG_CLOSED = 2,		// ���ܼ���
	SYNDICATE_JOIN_FLAG_END,
};


// �����������ö��
enum EUPDATA_TASK_TYPE
{
	EUPDATA_TASK_TYPE_Beg   = 0,
	EUPDATA_TASK_TYPE_Add	= EUPDATA_TASK_TYPE_Beg,	// ��������
	EUPDATA_TASK_TYPE_Del	= 1,						// ɾ������
	EUPDATA_TASK_TYPE_Alter = 2,						// �޸�����
	EUPDATA_TASK_TYPE_End,
};

// ����������λ��
enum ARENA_TEAM_POSITION
{
	ARENA_TEAM_POSITION_BEGIN,
	ARENA_TEAM_POSITION_FIRST	= 1,					// ��һ��
	ARENA_TEAM_POSITION_SECOND	= 2,					// �ڶ���
	ARENA_TEAM_POSITION_THIRD	= 3,					// ������
	ARENA_TEAM_POSITION_END		= 9999,
};

// ������־����
enum SYN_LOG_TYPE
{
	SYN_LOG_TYPE_BEGIN					= 0,
	SYN_LOG_TYPE_CREATE_SYN				= SYN_LOG_TYPE_BEGIN,	// ��������
	SYN_LOG_TYPE_DIRECT_JOIN_SYN		= 1,					// ֱ�Ӽ��빫��
	SYN_LOG_TYPE_EXIT_SYN				= 2,					// �˳�����
	SYN_LOG_TYPE_KICK_SYN				= 3,					// �߳�����
	SYN_LOG_TYPE_AlTER_NOTICE			= 4,					// �޸Ĺ���
	SYN_LOG_TYPE_UP_ELDER				= 5,					// ����Ϊ����
	SYN_LOG_TYPE_DOWN_MEMBER			= 6,					// ��ְΪ��Ա
	SYN_LOG_TYPE_RESET_INSTANCE 		= 7,					// �ŶӸ�������
	SYN_LOG_TYPE_PASS_INSTANCE  		= 8,					// �ŶӸ���ͨ��
	SYN_LOG_TYPE_TRANSFER_LEADER		= 9,					// �ƽ��᳤
	SYN_LOG_TYPE_TROPHY_QUEUE			= 10,					// ս��Ʒ���
	SYN_LOG_TYPE_AGREE_JOIN_SYN			= 11,					// ��׼���빫��
	SYN_LOG_TYPE_ALTER_LEV_LIMIT		= 12,					// �޸ļ��빫��ȼ�����
	SYN_LOG_TYPE_SHARE_TROPHY			= 13,					// �ֶ�����ս��Ʒ
	SYN_LOG_TYPE_ALTER_LIMIT_TYPE		= 14,					// �޸Ĺ����������(��Ҫ/����Ҫ��֤)
	SYN_LOG_TYPE_AUTO_TRANSFER_LEADER	= 15,					// �Զ��ƽ��᳤ 
	SYN_LOG_TYPE_END,
};
/////////////////////////////////////////////////////////////////////////////////////////////////////
// �������սϵͳ���ö�� 
// ���ս������Ӫ
enum TERRITORY_FIGHT_CAMP
{
	TERRITORY_FIGHT_CAMP_BEGIN,			
	TERRITORY_FIGHT_CAMP_ATTACK,								// ������
	TERRITORY_FIGHT_CAMP_DEFENSE,								// ���ط�
	TERRITORY_FIGHT_CAMP_END,
};
// ���ս�׶�ö��
enum TERRITORY_STAGE_TYPE
{
	TERRITORY_STAGE_TYPE_BEGIN,
	TERRITORY_STAGE_TYPE_NOT_START,								// �δ��ʼ
	TERRITORY_STAGE_TYPE_PREPARE,								// ׼���׶�			
	TERRITORY_STAGE_TYPE_MARCH,									// �о��׶�
	TERRITORY_STAGE_TYPE_FIGHTING,								// ս���׶�
	TERRITORY_STAGE_TYPE_END,
};

// ���սս������
enum TERRITORY_FIGHT_TYPE
{
	TERRITORY_FIGHT_TYPE_BEGIN,
	TERRITORY_FIGHT_TYPE_MONSTER,								// ���
	TERRITORY_FIGHT_TYPE_USER,									// ����
	TERRITORY_FIGHT_TYPE_END,
};
/////////////////////////////////////////////////////////////////////////////////////////////////////

// Ĥ������
enum SYN_WORSHIP_TYPE
{
	SYN_WORSHIP_TYPE_NONE		= 0,
	SYN_WORSHIP_TYPE_FREE		= 1,	// ���
	SYN_WORSHIP_TYPE_GOLD		= 2,	// ���
	SYN_WORSHIP_TYPE_VAS		= 3,	// ��ʯ
};

enum EMPLOY_MERCENARY					// Ӷ����Ӷ����
{
	EMPLOY_MERCENARY_NONE		= 0,
	EMPLOY_MERCENARY_INSTANCE	= 1,	// ������Ӷ
	EMPLOY_MERCENARY_WARROAD	= 2,	// ս�۹�Ӷ
	EMPLOY_MERCENARY_GOOSETOWER	= 3,	// ��������Ӷ
};

enum EMPLOY_STATE						// Ӷ����Ӷ״̬
{
	EMPLOY_STATE_NONE			= 0,
	EMPLOY_STATE_USE			= 1,	// ʹ����
	EMPLOY_STATE_SAVE			= 2,	// ����
	EMPLOY_STATE_COOL			= 3,	// ��ȴ
};

enum EWARROAD_MODE_TYPE					// ս��ģʽ����
{
	EWARROAD_MODE_TYPE_NONE				= 0,
	EWARROAD_MODE_TYPE_NORMAL			= 1,	// ��ͨ
	EWARROAD_MODE_TYPE_DIFFICULTY		= 2,	// ��Ӣ
	EWARROAD_MODE_TYPE_TEAM				= 3,	// �Ŷ�
};

enum EWARROAD_TEAM_FIGHT_TYPE			// �Ŷ�ս����ս״̬����
{
	EWARROAD_TEAM_FIGHT_TYPE_NONE		= 0,
	EWARROAD_TEAM_FIGHT_TYPE_PRE		= 1,	// ׼��
	EWARROAD_TEAM_FIGHT_TYPE_FIGHT		= 2,	// ս��
};

enum EGAME_HISTORY_COMPLETE_TYPE		// ��ʷ�ɼ��������
{
	EGHCT_NONE							= 0,
	EGHCT_WARROAD_TEAM_CHAPTER_QUICK	= 1,	// �Ŷ�ս���½����ͨ��
	EGHCT_WARROAD_TEAM_CHAPTER_FIRST	= 2,	// �Ŷ�ս���½��״�ͨ��
};

enum EDATA_RESET_TYPE			// ��������
{
	EDRT_NONE					= 0,
	EDRT_WAR_ROAD_DIFFICULTY	= 1,	// ս�۾�Ӣ�ؿ�����
	EDRT_WAR_ROAD_TEAM			= 2,	// �Ŷ�ս���½����ã�cout�������½ڣ�
	EDRT_POWER					= 3,	// ��������
	EDRT_ARENA					= 4,	// ��������ս��������
	EDRT_MULTI_ARENA			= 5,	// ��Ӿ�������ս��������
};

enum EGOOSE_FIGHT_POKER
{
	EGOOSE_FIGHT_POKER_Begin	= 0,
	EGOOSE_FIGHT_POKER_Self,			// �Լ��Ŀ���
	EGOOSE_FIGHT_POKER_Mercenary,		// Ӷ��
	EGOOSE_FIGHT_POKER_All,				// ����
	EGOOSE_FIGHT_POKER_End,
};

enum ETALK_TYPE
{
	ETALK_TYPE_Begin = 0,
	ETALK_TYPE_Common,					// ��ͨ
	ETALK_TYPE_TreasureShare,			// ���ط���
	ETALK_TYPE_End,
};

enum SYN_GIFT_BOX_TYPE						// �����������
{
	SGBT_BEGIN			= 0,
	SGBT_SERVER_BEGIN	= SGBT_BEGIN,		// *�������Զ�����п�ʼ*
	SGBT_RX_JIN_BOX		= 1,				// ���Խ����
	SGBT_RX_YIN_BOX		= 2,				// ���������
	SGBT_RX_TONG_BOX	= 3,				// ����ͭ���
	
	SGBT_TENGYUN_BOX	= 4,				// �������
	SGBT_YUEGONG_BOX	= 5,				// �¹����
	SGBT_CHUYAO_BOX		= 6,				// �������
	SGBT_TUANBEN_BOX	= 7,				// �ű����
	SGBT_DOUSHEN_BOX	= 8,				// �������
	SGBT_DAYAN_BOX		= 9,				// �������
	SGBT_HULU_BOX		= 10,				// ��«���
	SGBT_HUOYUE_BOX		= 11,				// ��Ծ���
	SGBT_SHENGJI_BOX	= 12,				// �������
	SGBT_SERVER_END		= 100,				// *�������Զ�����н���*

	SGBT_MONTH_CARD_BEGIN			= 1000,					// �¿�������Ϳ�ʼ
	SGBT_MONTH_CARD_SERVER_BEGIN	= SGBT_MONTH_CARD_BEGIN,// *�������Զ����¿���п�ʼ*
	SGBT_MONTH_CARD_SERVER_END		= 1099,					// *�������Զ����¿���н���*

	SGBT_MONTH_CARD_END				= 2000,					// �¿�������ͽ���
	SGBT_END,
};

// ��������ϢAction
enum MSG_GOOSE_TOWER_ACTION
{
	MSG_GOOSE_TOWER_ACT_QueryTowerList		= 1,		// �����ѯ�������б�		C --> S
	MSG_GOOSE_TOWER_ACT_ReturnTowerList		= 2,		// ���������ѯ�������б�	C <-- S
	MSG_GOOSE_TOWER_ACT_ReqChallenge		= 3,		// ������ս					C --> S
	MSG_GOOSE_TOWER_ACT_AckChallenge		= 4,		// ����������ս				C <-- S
	MSG_GOOSE_TOWER_ACT_ReqGainAward		= 5,		// ������ȡ����				C --> S
	MSG_GOOSE_TOWER_ACT_AckGainAward		= 6,		// ����������ȡ����			C <-- S
	MSG_GOOSE_TOWER_ACT_ReqResetTower		= 7,		// �������ô�����			C --> S
	MSG_GOOSE_TOWER_ACT_AckResetTower		= 8,		// �����������ô�����		C <-- S
	MSG_GOOSE_TOWER_ACT_NotifyClearTower    = 9,		// ֪ͨ��մ���������		C <-- S
	MSG_GOOSE_TOWER_ACT_ReqFightPokerInfo	= 10,		// �����������ʷ��������ϢC --> S
};

// ��������Ϣ���
enum MSG_GOOSE_TOWER_RESULT
{
	MSG_GOOSE_TOWER_RESULT_Succ			= 0,	// �ɹ�
	MSG_GOOSE_TOWER_RESULT_Error		= 1,	// ʧ��
	MSG_GOOSE_TOWER_RESULT_NoFloorInfo	= 2,	// ����Ϣ������
};

// ����ɽ��սˮ������
enum FRUIT_TYPE
{
	FRUIT_TYPE_Begin  = 0,
	FRUIT_TYPE_None   = 0,
	FRUIT_TYPE_Banana = 1,		// �㽶
	FRUIT_TYPE_Apple,			// ƻ��
	FRUIT_TYPE_Peach,			// ����
	FRUIT_TYPE_Pineapple,		// ����
	FRUIT_TYPE_Grape,			// ����
	FRUIT_TYPE_Watermelon,		// ����
	FRUIT_TYPE_End,
};

// ����ɽ��ս����
enum GESTURE_TYPE
{
	GESTURE_TYPE_BEGIN	= 0,
	GESTURE_TYPE_STONE	= GESTURE_TYPE_BEGIN,	// ʯͷ
	GESTURE_TYPE_SCISSORS,						// ����
	GESTURE_TYPE_CLOTH,							// ��
	GESTURE_TYPE_END,
};

// ����ɽ��ս�׶�
enum HGS_FIGHT_STATUS
{
	HGS_FIGHT_STATUS_Begin = 0,
	HGS_FIGHT_STATUS_Prepare,		// ׼���׶�
	HGS_FIGHT_STATUS_Collect,		// �ɼ��׶�
	HGS_FIGHT_STATUS_End,
};

/////////////////////////////////////////////////////////////////////////////////////////////////////
enum NTM_USER_TYPE			// ���������ģ������
{
	NTM_USER_TYPE_BEGIN	= 0,
	NTM_USER_TYPE_ELS	= 1,		// �������У�
	NTM_USER_TYPE_TTTW,				// �����������У�
	NTM_USER_TYPE_LG,				// �׹����У�
		
	NTM_USER_TYPE_DM	= 101,		// ��ĸ��Ů��
	NTM_USER_TYPE_BLN,				// ����Ů��Ů��
	NTM_USER_TYPE_CE,				// �϶�Ů��
	NTM_USER_TYPE_END,
};

enum E_USER_STATE_FLAG		// �����Ż״̬���
{
	EUSF_NONE				= 0,	
	EUSF_FIGHT				= 1,	// ս����
	EUSF_PK_DEFEND			= 2,	// PK����״̬
	EUSF_CONNECT_DEFEND		= 3,	// ��������״̬
};

enum E_POKER_LIVE_FLAG		// �����ſ��ƴ����
{
	EPLF_LIVE				= 0,	// ���
	EPLF_DEAD				= 1,	// ����
	EPLF_RECOVER			= 2,	// Ѫ������
	EPLF_REBORN				= 3,	// ����
};
/////////////////////////////////////////////////////////////////////////////////////////////////////

// ����ɽ��ս����ģ��
enum HGS_USER_MODE
{
	HGS_USER_MODE_BEGIN = 0,
	HGS_USER_MODE_CBY = 1,	// ����Գ
	HGS_USER_MODE_SWK = 2,	// �����
	HGS_USER_MODE_END,
};

// ��Ϣ���Ϳ�������
enum EMSG_SWITCH_TYPE
{
	EMSG_SWITCH_TYPE_Begin = 0,
	EMSG_SWITCH_TYPE_ReceivePower	= 1,	// ��ȡ����
	EMSG_SWITCH_TYPE_RefreshShop	= 2,	// ˢ���̵�
	EMSG_SWITCH_TYPE_PowerFull		= 3,	// �����ظ���
	EMSG_SWITCH_TYPE_SkillFull		= 4,	// ���ܵ�ظ���
	EMSG_SWITCH_TYPE_ArenaBeAtk		= 5,	// ������������
	EMSG_SWITCH_TYPE_PrivateTalk	= 6,	// ˽����Ϣ֪ͨ
	EMSG_SWITCH_TYPE_MineFinish		= 7,	// ���Ѳ���֪ͨ
	EMSG_SWITCH_TYPE_End,
};

// ��Ϣ���Ϳ���״̬
enum EMSG_SWITCH_STATUS
{
	EMSG_SWITCH_STATUS_Begin = 0,
	EMSG_SWITCH_STATUS_Close = 0,	// ��
	EMSG_SWITCH_STATUS_Open  = 1,	// ��
	EMSG_SWITCH_STATUS_End,
};

// ÿ�ջ�Ծ��������ö��
enum ELIVENESS_BOX_TYPE
{
	ELIVENESS_BOX_TYPE_Beg		= 1,
	ELIVENESS_BOX_TYPE_Box25	= ELIVENESS_BOX_TYPE_Beg,	// ��Ծ�ȴﵽ25��Ӧ����	
	ELIVENESS_BOX_TYPE_Box50	= 2,						// ��Ծ�ȴﵽ50��Ӧ����
	ELIVENESS_BOX_TYPE_Box75	= 3,						// ��Ծ�ȴﵽ75��Ӧ����
	ELIVENESS_BOX_TYPE_Box100	= 4,						// ��Ծ�ȴﵽ100��Ӧ����
	ELIVENESS_BOX_TYPE_End,
};

// ÿ�ջ�Ծ����״̬ö��
enum ELIVENESS_BOX_STATUS
{
	ELIVENESS_BOX_STATUS_Beg	= 0,
	ELIVENESS_BOX_STATUS_Unopen = ELIVENESS_BOX_STATUS_Beg,	// δ��
	ELIVENESS_BOX_STATUS_Open	= 1,						// ��
	ELIVENESS_BOX_STATUS_End,
};

// ÿ�ջ�Ծ�����ȡ״̬
enum ELIVENESS_STATUS
{
	ELIVENESS_STATUS_Beg		= 0,
	ELIVENESS_STATUS_NotGain	= ELIVENESS_STATUS_Beg,	// δ��ȡ
	ELIVENESS_STATUS_Gain		= 1,					// ��ȡ
	ELIVENESS_STATUS_End,
};

// ÿ�ջ�ԾID
enum LIVENESS_TYPE
{
	LIVENESS_TYPE_Begin			= 0,
	LIVENESS_TYPE_Lunch			= 1,		// �������
	LIVENESS_TYPE_Dinner		= 2,		// �������
	LIVENESS_TYPE_NightFood		= 3,		// ������ҹ
	LIVENESS_TYPE_MonthCard		= 4,		// �¿�
	LIVENESS_TYPE_UpSkill		= 5,		// ��������
	LIVENESS_TYPE_EquipMagic	= 6,		// װ����ħ
	LIVENESS_TYPE_Lottery		= 7,		// �鿨
	LIVENESS_TYPE_NormalGate	= 8,		// ��ͨ��ͼ
	LIVENESS_TYPE_HeroGate		= 9,		// ��Ӣ��ͼ
	LIVENESS_TYPE_GooseTower	= 10,		// ������
	LIVENESS_TYPE_Instance		= 11,		// �㺮��
	LIVENESS_TYPE_ChallengeBoss	= 12,		// ������(��սbosss)
	LIVENESS_TYPE_Arena			= 13,		// ������
	LIVENESS_TYPE_Mine			= 14,		// ���Ӷ�
	LIVENESS_TYPE_Wroship		= 15,		// Ĥ��
	LIVENESS_TYPE_MoneyTree		= 16,		// �۱���(ҡǮ��)
	LIVENESS_TYPE_WarRoad		= 17,		// �ŶӸ���
	LIVENESS_TYPE_GiveRose		= 18,		// ����õ��
	LIVENESS_TYPE_GainClearBook	= 19,		// ��ȡɨ����
	LIVENESS_TYPE_End,
};

// ��ɻ�Ծ����Ҫ����
enum LIVENESS_NEED_TYPE
{
	LIVE_NEED_TYPE_Begin			= 0,
	LIVE_NEED_TYPE_Feast			= 1,		// ���
	LIVE_NEED_TYPE_MonthCard		= 2,		// �¿�
	LIVE_NEED_TYPE_UpSkill			= 3,		// ��������
	LIVE_NEED_TYPE_EquipMagic		= 4,		// װ����ħ
	LIVE_NEED_TYPE_Lottery			= 5,		// �鿨
	LIVE_NEED_TYPE_NormalGate		= 6,		// ��ͨ��ͼ
	LIVE_NEED_TYPE_HeroGate			= 7,		// ��Ӣ��ͼ
	LIVE_NEED_TYPE_GooseTower		= 8,		// ������
	LIVE_NEED_TYPE_Instance			= 9,		// �㺮��
	LIVE_NEED_TYPE_ChallengeBoss	= 10,		// ������(��սbosss)
	LIVE_NEED_TYPE_Arena			= 11,		// ������
	LIVE_NEED_TYPE_Mine				= 12,		// ���Ӷ�
	LIVE_NEED_TYPE_Wroship			= 13,		// Ĥ��
	LIVE_NEED_TYPE_MoneyTree		= 14,		// ҡǮ
	LIVE_NEED_TYPE_WarRoad			= 15,		// �ŶӸ���
	LIVE_NEED_TYPE_GiveRose			= 16,		// ����õ��
	LIVE_NEED_TYPE_GainClearBook	= 17,		// ��ȡɨ����
	LIVE_NEED_TYPE_End,
};

// ��Ҫ���͵���ʾ��Ϣ����
enum MSG_MARKS_TYPE
{
	MSG_MARKS_TYPE_BEGIN						= 0,
	MSG_MARKS_TYPE_POKER_EQUIP					= 1,	// Ӣ��		*�ͻ����Զ����Ӣ�ۺͱ���			����Ӣ�ۿ��Դ����������װ�����߿��Ժϳɺ󴩴���
	MSG_MARKS_TYPE_ACHIEVEMENT					= 2,	// �ɾ�		��ɵĳɾ�����						���п����콱��
	MSG_MARKS_TYPE_FRIEND_GIFT					= 3,	// ����		����������������					���к������������
	MSG_MARKS_TYPE_FRIEND_CHARGEAWARD			= 4,	// ����		���ѳ�ֵ������������				���������������н���������ȡ, ��ֵ������
	MSG_MARKS_TYPE_FRIEND_LOGINAWARD			= 5,	// ����		�������յ�½��������				���������������н���������ȡ, ��½������
	MSG_MARKS_TYPE_FRIEND_APPLY					= 6,	// ����		������������						��������Ӻ�������ʱ����Ҫ��ʾ�����������ť����ʾ��ʧ��
	MSG_MARKS_TYPE_LIVENESS						= 7,	// ÿ�ջ�Ծ �ɿ��ı����� + �����콱�Ļ�Ծ����	�����콱�Ļ��߱�����Կ����ģ�
	MSG_MARKS_TYPE_LOTTERY						= 8,	// ������	�Ƿ������ѳ齱					������ѳ齱ʱ�����������ְ�ť����Ϣ��ʾ����ѳ�ȡ����Ϣ��ʾ��ʧ����ѳ齱����CD����Ҫ��Ϣ��ʾ����
	MSG_MARKS_TYPE_MAIL							= 9,	// ����		δ���ʼ�����						����δ���ʼ�ʱ���������ְ�ť����Ϣ��ʾ����ȡ������δ���ʼ�����Ϣ��ʾ��ʧ��
	MSG_MARKS_TYPE_ARENA_NORMAL					= 10,	// ����̨	����ͨģʽ���Ƿ񱻴����			���������һ����ˣ�����̨���ְ�ť����Ϣ��ʾ��
	MSG_MARKS_TYPE_SYNDICATE_APPLY				= 11,	// ����		������������						���������ó�����Ҫ��ע���������������ʱ����Ȩ�޵���ң������ͳ��ϣ���Ҫ����Ϣ��ʾ��
	MSG_MARKS_TYPE_SYNDICATE_GIFTBOX			= 12,	// ����		����ȡ�İ����������				����������п�����ȡʱ��ʾ)
	MSG_MARKS_TYPE_MINE_COMPLETE				= 13,	// Ǭ����«	���콱���Ŀ���					���Ѿ������꣬��Ҫ����Ϣ��ʾ��
	MSG_MARKS_TYPE_MINE_BE_CHALLENGE			= 14,	// Ǭ����«	�Ƿ񱻱����Ӷ���					���������Ӷ��ˣ���Ҫ����Ϣ��ʾ��
	MSG_MARKS_TYPE_SIGN							= 15,	// ǩ��		�Ƿ�ǩ����							�����컹δǩ����ǩ����ť������Ϣ��ʾ��ǩ������Ϣ��ʾ��ʧ��
	MSG_MARKS_TYPE_ARENA_SPETIAL				= 16,	// ����̨	������ģʽ���Ƿ񱻴����			���������һ����ˣ�����̨���ְ�ť����Ϣ��ʾ��
	
	MSG_MARKS_TYPE_END,
};

/////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // end of _MAPGROUP_SHARE_ENUM_DEF_H_
