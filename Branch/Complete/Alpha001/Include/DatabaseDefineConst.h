////////////////////////////////////////////////////////////////////////
// Import : ����������ȫ��������
// Moudle : DatabaseDefineConst.h
// Author : �½���(Chen Jianjun)
// Created: 2015-08-27
////////////////////////////////////////////////////////////////////////
#ifndef _DATABASE_DEFINE_CONST_H_
#define _DATABASE_DEFINE_CONST_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//static const char* CONST_DB_NAME_CONFIG = "config";				// �������ñ�
//enum CONFIG_DATA
//{
//	CONFIGDATA_BEGIN = 0,
//	CONFIGDATA_TYPE = CONFIGDATA_BEGIN,			// typeid	uint
//	CONFIGDATA_DATA1,							// ����1	uint
//	CONFIGDATA_DATA2,							// ����2	uint
//	CONFIGDATA_DATA3,							// ����3	uint
//	CONFIGDATA_DATA4,							// ����4	uint
//	CONFIGDATA_DATA5,							// ����5	uint
////	CONFIGDATA_COMMENT,							// ע���ֶ�, �������ڴ�
//	CONFIGDATA_END,
//};
//
//static const char* CONST_DB_NAME_CONFIG_TEXT = "config_text";	// ���������ı���
//enum CONFIG_TEXT_DATA
//{
//	CONFIG_TEXT_DATA_ID		= 0,	// id
//	CONFIG_TEXT_DATA_TEXT	= 1,	// ����������
//};
//
//static const char* CONST_DB_NAME_TASK_CONFIG_DATA = "task";		// �������ñ�
//enum ETASK_CONFIG_DATA
//{
//	ETASK_CONFIG_DATA_ID		= 0,	// ���										uint
//	ETASK_CONFIG_DATA_TYPE,				// ��������									uint
//	ETASK_CONFIG_DATA_STEP,				// ����(����(��1��ʼ������))				uint
//	ETASK_CONFIG_DATA_ISCHAIN,			// �Ƿ���������(0:���ǣ�1:��)				uint
//	ETASK_CONFIG_DATA_LIMIT_TIME,		// ʱ������( 0:������, >0:����ʱ��(��) )	uint
//	ETASK_CONFIG_DATA_NEED_TYPE1,		// ������Ҫ����1							uint
//	ETASK_CONFIG_DATA_NEED_NUM1,		// ����1��Ҫ����							uint
//	ETASK_CONFIG_DATA_NEED_TYPE2,		// ������Ҫ����2							uint
//	ETASK_CONFIG_DATA_NEED_NUM2,		// ����2��Ҫ����							uint
//	ETASK_CONFIG_DATA_NEED_TYPE3,		// ������Ҫ����3							uint
//	ETASK_CONFIG_DATA_NEED_NUM3,		// ����3��Ҫ����							uint
//	ETASK_CONFIG_DATA_RECEIVE_ACTION,	// ��������ű�action						uint
//	ETASK_CONFIG_DATA_FINISH_ACTION,	// �������ű�action						uint
//	ETASK_CONFIG_DATA_GIVEUP_ACTION,	// ��������ű�action						uint
//	ETASK_CONFIG_DATA_NAME,				// ������									varchar128
//};
//
//
//static const char* CONST_DB_NEWCARD_PRIZE = "newcard_prize";	// ���ֿ��������ñ�
//enum NEWCARD_PRIZE_DATA
//{
//	NEWCARD_PRIZE_DATA_ID = 0,		// id		uint
//	NEWCARD_PRIZE_DATA_TYPE,		// ������	uint
//	NEWCARD_PRIZE_DATA_GIVEMASKID,	// ����ID	uint
//	// �����ֶ�Ϊ10������������Ϣ������type uint, �������� uint, �Ƿ�� uint��
//	NEWCARD_PRIZE_DATA_ITEMTYPE1,
//	NEWCARD_PRIZE_DATA_ITEMCOUNT1,
//	NEWCARD_PRIZE_DATA_ITEMTYPE2,
//	NEWCARD_PRIZE_DATA_ITEMCOUNT2,
//	NEWCARD_PRIZE_DATA_ITEMTYPE3,
//	NEWCARD_PRIZE_DATA_ITEMCOUNT3,
//	NEWCARD_PRIZE_DATA_ITEMTYPE4,
//	NEWCARD_PRIZE_DATA_ITEMCOUNT4,
//	NEWCARD_PRIZE_DATA_ITEMTYPE5,
//	NEWCARD_PRIZE_DATA_ITEMCOUNT5,
//	NEWCARD_PRIZE_DATA_ITEMTYPE6,
//	NEWCARD_PRIZE_DATA_ITEMCOUNT6,
//	NEWCARD_PRIZE_DATA_ITEMTYPE7,
//	NEWCARD_PRIZE_DATA_ITEMCOUNT7,
//	NEWCARD_PRIZE_DATA_ITEMTYPE8,
//	NEWCARD_PRIZE_DATA_ITEMCOUNT8,
//	NEWCARD_PRIZE_DATA_ITEMTYPE9,
//	NEWCARD_PRIZE_DATA_ITEMCOUNT9,
//	NEWCARD_PRIZE_DATA_ITEMTYPE10,
//	NEWCARD_PRIZE_DATA_ITEMCOUNT10,
//};
//
//static const char* CONST_DB_NAME_NOTIFY_CONFIG = "notify";		// �������ñ�
//enum NOTIFY_CONFIG
//{
//	NOTIFY_CONFIG_ID = 0,				// ���										bigint
//	NOTIFY_CONFIG_CHANNEL,				// Ƶ��										uint
//	NOTIFY_CONFIG_TIME_TYPE,			// ʱ������									uint
//	NOTIFY_CONFIG_TIME,					// ʱ��										bigint
//	NOTIFY_CONFIG_TEXT,					// ��������									varchar255
//	NOTIFY_CONFIG_GROUP,				// ��������									uint
//};
//static const char* CONST_DB_NAME_ACTIVITY_CONFIG = "activities";	// ���
//enum ACTIVITY_CONFIG_DATA
//{
//	ACTIVITY_CONFIG_DATA_BEGIN = 0,
//	ACTIVITY_CONFIG_DATA_ID	 = ACTIVITY_CONFIG_DATA_BEGIN,	// ������id				uint
//	ACTIVITY_CONFIG_DATA_TYPE,								// typeid				uint
//	ACTIVITY_CONFIG_DATA_TIME_TYPE,							// �ʱ�����			uint
//	ACTIVITY_CONFIG_DATA_BEGIN_TIME,						// ��ʼʱ��				uint
//	ACTIVITY_CONFIG_DATA_END_TIME,							// ����ʱ��				uint
//	ACTIVITY_CONFIG_DATA_BEGIN_ACTION,						// ��ʼ�����ű�			uint
//	ACTIVITY_CONFIG_DATA_END_ACTION,						// ���������ű�			uint
//	ACTIVITY_CONFIG_DATA_ENTER_ACTION,						// �ͻ��˴�������ű�	uint
//	ACTIVITY_CONFIG_DATA_EXIT_ACTION,						// �ͻ��˴����˳��ű�	uint
//	ACTIVITY_CONFIG_DATA_SERVER_GROUP,						// ��������				uint
//	ACTIVITY_CONFIG_DATA_LINE,								// ��·					uint
//	ACTIVITY_CONFIG_DATA_PARAM1,							// ���ò���1			uint
//	ACTIVITY_CONFIG_DATA_PARAM2,							// ���ò���2			uint
////  ACTIVITY_CONFIG_DATA_COMMENT,							// ע���ֶ�, �������ڴ�
//	ACTIVITY_CONFIG_DATA_END,
//};
//
//
//static const char* CONST_DB_ACTION = "action";	// �ű�action��
//enum ACTION_DATA
//{
//	ACTION_DATA_ID = 0,				// id			uint
//	ACTION_DATA_FILE_PATH,			// ·��			varchar128
//	ACTION_DATA_FUNCTION,			// ����			varchar128
//	ACTION_DATA_CLIENT_TRIGGER,		// �ͻ��˴���	uint
//};
//
//
//
//static const char* CONST_DB_POKER_TYPE = "poker_type";	// �������ͱ�
//enum POKER_TYPE_DATA
//{
//	POKER_TYPE_DATA_ID = 0,			// ��������id				uint
//	POKER_TYPE_DATA_NAME,			// ����						varchar32
//	POKER_TYPE_DATA_CAMP,			// ��Ӫ		POKER_CAMP		uint
//	POKER_TYPE_DATA_FIGHT_POS,		// ս��λ��	POKER_FIGHT_POS	uint
//	POKER_TYPE_DATA_POS_SORT,		// վλ����					uint
//	POKER_TYPE_DATA_INIT_LIFE,		// ��ʼ����					uint
//	POKER_TYPE_DATA_INIT_MANA,		// ��ʼħ��					uint
//	POKER_TYPE_DATA_INIT_STR,		// ��ʼ����					uint
//	POKER_TYPE_DATA_INIT_STA,		// ��ʼ����					uint
//	POKER_TYPE_DATA_INIT_DEX,		// ��ʼ����					uint
//	POKER_TYPE_DATA_INIT_HP,		// ��ʼѪ��					uint
//	POKER_TYPE_DATA_INIT_ATK,		// ��ʼ�˺�					uint
//	POKER_TYPE_DATA_INIT_STAR,		// ��ʼ�Ǽ�					uint
//	POKER_TYPE_DATA_SKILL_SP,		// �ؼ�						uint
//	POKER_TYPE_DATA_SKILL_AUTO1,	// �Զ�����1				uint
//	POKER_TYPE_DATA_SKILL_AUTO2,	// �Զ�����2				uint
//	POKER_TYPE_DATA_SKILL_AUTO3,	// �Զ�����3				uint
//	POKER_TYPE_DATA_SKILL_JOINT,	// ��Я����					uint
//	POKER_TYPE_DATA_ANGER_PARAM,	// ��ŭת��ϵ������ֱȣ�	uint
//	POKER_TYPE_DATA_NEED_ITEMTYPE,	// ��Ӧ���ʯ����			uint
//};
//
//static const char* CONST_DB_POKER_STAR_GROW = "poker_star_grow";	// �����Ǽ��ɳ���
//enum POKER_STAR_GROW_DATA
//{
//	POKER_STAR_GROW_DATA_TYPE = 0,	// ��������		uint
//	POKER_STAR_GROW_DATA_STAR,		// �����Ǽ�		uint
//	POKER_STAR_GROW_DATA_LIFE_GROW,	// ���ʳɳ�		uint
//	POKER_STAR_GROW_DATA_MANA_GROW,	// ħ���ɳ�		uint
//	POKER_STAR_GROW_DATA_STR_GROW,	// �����ɳ�		uint
//	POKER_STAR_GROW_DATA_STA_GROW,	// �����ɳ�		uint
//	POKER_STAR_GROW_DATA_DEX_GROW,	// ���ݳɳ�		uint
//};
//
//static const char* CONST_DB_POKER_EQUIP = "poker_equip";	// ����װ�����ñ�
//enum POKER_EQUIP_DATA
//{
//	POKER_EQUIP_DATA_POKER_TYPE = 0,	// ��������			uint
//	POKER_EQUIP_DATA_POKER_COLOR,		// ������ɫ(1-17)	uint
//	POKER_EQUIP_DATA_EQUIP1_TYPE,		// ��������			uint
//	POKER_EQUIP_DATA_EQUIP2_TYPE,		// ͷ������			uint
//	POKER_EQUIP_DATA_EQUIP3_TYPE,		// ��������			uint
//	POKER_EQUIP_DATA_EQUIP4_TYPE,		// ��������			uint
//	POKER_EQUIP_DATA_EQUIP5_TYPE,		// �·�����			uint
//	POKER_EQUIP_DATA_EQUIP6_TYPE,		// Ь������			uint
//};
//
//static const char* CONST_DB_POKER_STAR = "poker_star";	// �����Ǽ����ñ�
//enum POKER_STAR_DATA
//{
//	POKER_STAR_DATA_STAR = 0,			// �Ǽ�								uint
//	POKER_STAR_DATA_COMPOUND_NEED,		// �ϳ�ʱ�������ʯ����				uint
//	POKER_STAR_DATA_RESOLVE_AUTO,		// �Զ��ֽ������ʯ����			uint
//	POKER_STAR_DATA_UPGRADE_NEED,		// ������Ҫ���ʯ, ������0			uint
//};
//
//static const char* CONST_DB_LEV_EXP = "lev_exp"; // �ȼ������
//enum LEV_EXP_DATA
//{
//	LEV_EXP_DATA_TYPE = 0,		// ���� LEV_EXP_TYPE		uint
//	LEV_EXP_DATA_LEV,			// �ȼ�						uint
//	LEV_EXP_DATA_EXP,			// ����						bigint
//};
//
//static const char* CONST_DB_SIGN_PRIZE = "sign_prize";	// ǩ���������ñ�
//enum SIGN_PRIZE_DATA
//{
//	SIGN_PRIZE_DATA_ID = 0,			// id������������ǩ��1000+������uint
//	SIGN_PRIZE_DATA_MUL_PRIZE,		// ��������	uint
//	SIGN_PRIZE_DATA_VIP_LEV,		// ����VIP�ȼ�	uint
//	// �����ֶ�Ϊ4������������Ϣ������type uint, �������� uint, �Ƿ�� uint��
//	SIGN_PRIZE_DATA_ITEMTYPE1,
//	SIGN_PRIZE_DATA_ITEMCOUNT1,
//	SIGN_PRIZE_DATA_ITEMTYPE2,
//	SIGN_PRIZE_DATA_ITEMCOUNT2,
//	SIGN_PRIZE_DATA_ITEMTYPE3,
//	SIGN_PRIZE_DATA_ITEMCOUNT3,
//};
//
//static const char* CONST_DB_AUTO_RELOAD = "auto_reload";	// �Զ��������ñ�
//enum AUTO_RELOAD_DATA
//{
//	AUTO_RELOAD_DATA_TABLE_NAME = 0,	// ����					varchar255
//	AUTO_RELOAD_DATA_GROUP,				// �������� ��0��ʾȫ��	uint
//	AUTO_RELOAD_DATA_LINE,				// �������� ��0��ʾȫ��	uint
//	AUTO_RELOAD_DATA_UTC_TIME,			// ָ��ʱ�� ��0��ʾ��ʱ	uint
//};
//
//static const char* CONST_DB_VIP = "vip";		// VIP���ñ�
//enum VIP_DATA
//{
//	VIP_DATA_TYPE	= 0,		// vip����	uint
//	VIP_DATA_LEV,				// vip�ȼ�	uint
//	VIP_DATA_VALUE,				// Vaule	uint
//};
//
//static const char* CONST_DB_NAME_ITEM_TYPE = "item_type";	// ��Ʒ���ͱ�
//enum ITEM_TYPE_DATA
//{
//	ITEM_TYPE_DATA_ID = 0,			// ����			uint
//	ITEM_TYPE_DATA_NAME,			// ����			uint
//	ITEM_TYPE_DATA_COLOR,			// ��ɫ			uint
//	ITEM_TYPE_DATA_AMOUNT_LIMIT,	// ��������		uint
//	ITEM_TYPE_DATA_CLASSIIFY,		// ����			uint
//	ITEM_TYPE_DATA_SORT,			// ��Ʒ����		uint
//	ITEM_TYPE_DATA_DATA1,			// ����1		uint
//	ITEM_TYPE_DATA_DATA2,			// ����2		uint
//	ITEM_TYPE_DATA_DATA3,			// ����3		uint
//	ITEM_TYPE_DATA_ACTION,			// action		uint
//	ITEM_TYPE_DATA_MONOPOLY,		// monopoly		uint
//	ITEM_TYPE_DATA_SALE_MONEY_TYPE,	// �۳��������� uint
//	ITEM_TYPE_DATA_SALE_PRICE,		// �۳��۸�		uint
//	ITEM_TYPE_DATA_PEIFANG_ID,		// �䷽ID		uint
//	ITEM_TYPE_DATA_LIMIT_LEV,		// ���Ƶȼ�		uint
//	ITEM_TYPE_DATA_END,
//};
//
//static const char* CONST_DB_NAME_ITEM_COLOR = "item_color";	// ��Ʒ��ɫ���ñ�
//enum ITEM_COLOR_DATA
//{
//	ITEM_COLOR_DATA_COLOR = 0,	// ��ɫ			uint
//	ITEM_COLOR_DATA_STAR1,		// 1����������	uint
//	ITEM_COLOR_DATA_STAR2,		// 2����������	uint
//	ITEM_COLOR_DATA_STAR3,		// 3����������	uint
//	ITEM_COLOR_DATA_STAR4,		// 4����������	uint
//	ITEM_COLOR_DATA_STAR5,		// 5����������	uint
//	ITEM_COLOR_DATA_PRICE,		// ÿ��۸�		uint
//};
//
//static const char* CONST_DB_NAME_ITEM_STAR_ATTR = "item_star_attr";	// ��Ʒ�Ǽ�����
//enum ITEM_STAR_ATTR_DATA
//{
//	ITEM_STAR_ATTR_DATA_TYPE = 0,		// ��Ʒ����		uint
//	ITEM_STAR_ATTR_DATA_STAR,			// ��Ʒ�Ǽ�		uint
//	ITEM_STAR_ATTR_DATA_ATTR_TYPE1,		// ��������1	uint
//	ITEM_STAR_ATTR_DATA_ATTR_DATA1,		// ������ֵ1	uint
//	ITEM_STAR_ATTR_DATA_ATTR_TYPE2,		// ��������2	uint
//	ITEM_STAR_ATTR_DATA_ATTR_DATA2,		// ������ֵ2	uint
//	ITEM_STAR_ATTR_DATA_ATTR_TYPE3,		// ��������3	uint
//	ITEM_STAR_ATTR_DATA_ATTR_DATA3,		// ������ֵ3	uint
//	ITEM_STAR_ATTR_DATA_ATTR_TYPE4,		// ��������4	uint
//	ITEM_STAR_ATTR_DATA_ATTR_DATA4,		// ������ֵ4	uint
//	ITEM_STAR_ATTR_DATA_ATTR_TYPE5,		// ��������5	uint
//	ITEM_STAR_ATTR_DATA_ATTR_DATA5,		// ������ֵ5	uint
//};
//
//static const char* CONST_DB_LIVENESS = "liveness";		// ÿ�ջ�Ծ���ñ�
//enum ELIVENESS_CONFIG
//{
//	ELIVENESS_CONFIG_ID = 0,			// ��Ծ��ID					uint		
//	ELIVENESS_CONFIG_LevLimit,			// �ȼ�����					uint
//	ELIVENESS_CONFIG_VipLimit,			// VIP�ȼ�����				uint
//	ELIVENESS_CONFIG_BeginTime,			// ��ʼʱ��					uint
//	ELIVENESS_CONFIG_EndTime,			// ����ʱ��					uint
//	ELIVENESS_CONFIG_Val,				// ��ɻ�Ծ��õĻ�Ծֵ		uint
//	ELIVENESS_CONFIG_NeedType,			// ��Ҫ����					uint
//	ELIVENESS_CONFIG_NeedNum,			// ��Ҫ����					uint
//	ELIVENESS_CONFIG_AwardAction,		// �������ű�Action			uint
//	ELIVENESS_CONFIG_Title,				// ����						varchar32
//	ELIVENESS_CONFIG_Content,			// ���� 					varchar64
//};
//
//static const char* CONST_DB_SHOP_TYPE = "shop_type";	// �̵��������ñ�
//enum SHOP_TYPE
//{
//	SHOP_TYPE_BEGIN = 0,
//	SHOP_TYPE_ID = SHOP_TYPE_BEGIN,		// �̵�����					uint
//	SHOP_TYPE_BLANK_LIMIT,				// ��������					uint
//	SHOP_TYPE_REFRESH_MONEY_TYPE,		// �ֶ�ˢ������Ļ�������	uint
//	SHOP_TYPE_REFRESH_PRICE,			// �ֶ�ˢ�¼۸�				uint
//	SHOP_TYPE_AUTO_REFRESH_TIME1,		// �Զ�ˢ��ʱ��1			uint
//	SHOP_TYPE_AUTO_REFRESH_TIME2,		// �Զ�ˢ��ʱ��2			uint
//	SHOP_TYPE_AUTO_REFRESH_TIME3,		// �Զ�ˢ��ʱ��3			uint
//	SHOP_TYPE_AUTO_REFRESH_TIME4,		// �Զ�ˢ��ʱ��4			uint
//	SHOP_TYPE_AUTO_REFRESH_TIME5,		// �Զ�ˢ��ʱ��5			uint
//	SHOP_TYPE_REFRESH_RULE1,			// ˢ�¹���1				uint
//	SHOP_TYPE_REFRESH_RULE2,			// ˢ�¹���2				uint
//	SHOP_TYPE_REFRESH_RULE3,			// ˢ�¹���3				uint
//	SHOP_TYPE_REFRESH_RULE4,			// ˢ�¹���4				uint
//	SHOP_TYPE_REFRESH_RULE5,			// ˢ�¹���5				uint
//	SHOP_TYPE_REFRESH_RULE6,			// ˢ�¹���6				uint
//	SHOP_TYPE_REFRESH_RULE7,			// ˢ�¹���7				uint
//	SHOP_TYPE_REFRESH_RULE8,			// ˢ�¹���8				uint
//	SHOP_TYPE_REFRESH_RULE9,			// ˢ�¹���9				uint
//	SHOP_TYPE_REFRESH_RULE10,			// ˢ�¹���10				uint
//	SHOP_TYPE_REFRESH_RULE11,			// ˢ�¹���11				uint
//	SHOP_TYPE_REFRESH_RULE12,			// ˢ�¹���12				uint
//	SHOP_TYPE_END,
//};
//
//static const char* CONST_DB_SHOP_RULE = "shop_rule";		// �̵�������ñ�
//enum SHOP_RULE
//{
//	SHOP_RULE_BEGIN = 0,
//	SHOP_RULE_ID = SHOP_RULE_BEGIN,		// ��������					uint
//	SHOP_RULE_ITEM_TYPE,				// ��Ʒ����					uint
//	SHOP_RULE_ITEM_NUM,					// ��Ʒ����					uint
//	SHOP_RULE_ITEM_PRICE,				// ��Ʒ����					uint
//	SHOP_RULE_MONEY_TYPE,				// ��������					uint
//	SHOP_RULE_DISCOUNT,					// ��Ʒ�ۿ�					uint
//	SHOP_RULE_WEIGHT,					// ��ƷȨ��					uint
//	SHOP_RULE_END,
//};
//
//static const char* CONST_DB_NAME_ACHIEVEMENT = "achievement";		// �ɾ����ñ�
//enum ACHIEVEMENT_DATA
//{
//	ACHIEVEMENT_DATA_BEGIN			= 0,
//	ACHIEVEMENT_DATA_ID				= ACHIEVEMENT_DATA_BEGIN,	// �ɾ�id����λ�������λ��ʾ���	uint
//	ACHIEVEMENT_DATA_SUBINDEX,									// ����ɾ����кţ���һ��Ϊ0��		uint
//	ACHIEVEMENT_DATA_BEFOREID,									// ǰ�óɾ�id						uint
//	ACHIEVEMENT_DATA_AFTERID,									// �����ɾ�id						uint
//	ACHIEVEMENT_DATA_ACTIONID,									// �ɾͽ������ýű�action			uint
//	ACHIEVEMENT_DATA_OPEN_TYPE,									// �������							uint
//	ACHIEVEMENT_DATA_OPEN_CONDITION1,							// ��������1						uint
//	ACHIEVEMENT_DATA_OPEN_CONDITION2,							// ��������2						uint
//	ACHIEVEMENT_DATA_COMPLETE_CONDITION1,						// �������1						uint
//	ACHIEVEMENT_DATA_COMPLETE_CONDITION2,						// �������2						uint
//	ACHIEVEMENT_DATA_END,
//};
//
//static const char* CONST_DB_NAME_LUA_TEXT = "lua_text";	// �ű����ֱ�
//enum LUA_TEXT_DATA
//{
//	LUA_TEXT_DATA_ID = 0,	// id		uint
//	LUA_TEXT_DATA_TEXT,		// ����		varchar512
//};
//
//static const char* CONST_DB_NAME_SKILL_TYPE = "skill_type";		// �����������ñ�
//enum SKILL_TYPE_DATA
//{
//	SKILL_TYPE_DATA_ID	= 0,			// ����id			uint
//	SKILL_TYPE_DATA_SORT,				// ���ܷ���			uint
//	SKILL_TYPE_DATA_NEED_LEV,			// ����ȼ�			uint
//	SKILL_TYPE_DATA_COST_MONEY,			// ���ѽ���			uint
//	SKILL_TYPE_DATA_COST_POINT,			// ���Ѽ��ܵ�		uint
//	SKILL_TYPE_DATA_POWER,				// ����				uint
//	SKILL_TYPE_DATA_POWER_ADD,			// ��������			uint
//	SKILL_TYPE_DATA_POWER2,				// ����2			uint
//	SKILL_TYPE_DATA_POWER2_ADD,			// ����2����		uint
//};
//
//static const char* CONST_DB_DROP_RULE = "drop_rule";	// ��������
//enum DROP_RULE_DATA
//{
//	DROP_RULE_DATA_ID		= 0,		// �������id							uint
//	DROP_RULE_DATA_TYPE,				// �����������	DROP_RULE_TYPE			uint
//	DROP_RULE_DATA_COUNT,				// ����, �������ִ��					uint
//	DROP_RULE_DATA_CHANCE,				// �������, ��ֱ�						uint
//
//	DROP_RULE_DATA_GROUP1_TYPE,			// ������1 ����	DROP_RULE_GROUP_TYPE	uint
//	DROP_RULE_DATA_GROUP1_COUNT,		// ������1 ����							uint
//	DROP_RULE_DATA_GROUP1_WEIGHT,		// ������1 Ȩ��							uint
//	DROP_RULE_DATA_GROUP1_GROUP,		// ������1 ��������						uint
//
//	DROP_RULE_DATA_GROUP2_TYPE,			// ������2 ����	DROP_RULE_GROUP_TYPE	uint
//	DROP_RULE_DATA_GROUP2_COUNT,		// ������2 ����							uint
//	DROP_RULE_DATA_GROUP2_WEIGHT,		// ������2 Ȩ��							uint
//	DROP_RULE_DATA_GROUP2_GROUP,		// ������2 ��������						uint
//
//	DROP_RULE_DATA_GROUP3_TYPE,			// ������3 ����	DROP_RULE_GROUP_TYPE	uint
//	DROP_RULE_DATA_GROUP3_COUNT,		// ������3 ����							uint
//	DROP_RULE_DATA_GROUP3_WEIGHT,		// ������3 Ȩ��							uint
//	DROP_RULE_DATA_GROUP3_GROUP,		// ������3 ��������						uint
//
//	DROP_RULE_DATA_GROUP4_TYPE,			// ������4 ����	DROP_RULE_GROUP_TYPE	uint
//	DROP_RULE_DATA_GROUP4_COUNT,		// ������4 ����							uint
//	DROP_RULE_DATA_GROUP4_WEIGHT,		// ������4 Ȩ��							uint
//	DROP_RULE_DATA_GROUP4_GROUP,		// ������4 ��������						uint
//
//	DROP_RULE_DATA_GROUP5_TYPE,			// ������5 ����	DROP_RULE_GROUP_TYPE	uint
//	DROP_RULE_DATA_GROUP5_COUNT,		// ������5 ����							uint
//	DROP_RULE_DATA_GROUP5_WEIGHT,		// ������5 Ȩ��							uint
//	DROP_RULE_DATA_GROUP5_GROUP,		// ������5 ��������						uint
//
//	DROP_RULE_DATA_GROUP6_TYPE,			// ������6 ����	DROP_RULE_GROUP_TYPE	uint
//	DROP_RULE_DATA_GROUP6_COUNT,		// ������6 ����							uint
//	DROP_RULE_DATA_GROUP6_WEIGHT,		// ������6 Ȩ��							uint
//	DROP_RULE_DATA_GROUP6_GROUP,		// ������6 ��������						uint
//
//	DROP_RULE_DATA_GROUP7_TYPE,			// ������7 ����	DROP_RULE_GROUP_TYPE	uint
//	DROP_RULE_DATA_GROUP7_COUNT,		// ������7 ����							uint
//	DROP_RULE_DATA_GROUP7_WEIGHT,		// ������7 Ȩ��							uint
//	DROP_RULE_DATA_GROUP7_GROUP,		// ������7 ��������						uint
//
//	DROP_RULE_DATA_GROUP8_TYPE,			// ������8 ����	DROP_RULE_GROUP_TYPE	uint
//	DROP_RULE_DATA_GROUP8_COUNT,		// ������8 ����							uint
//	DROP_RULE_DATA_GROUP8_WEIGHT,		// ������8 Ȩ��							uint
//	DROP_RULE_DATA_GROUP8_GROUP,		// ������8 ��������						uint
//};
//
//
//static const char* CONST_DB_BATTLE_TYPE = "battle_type";	// ս�����ñ�
//enum BATTLE_TYPE_DATA
//{
//	BATTLE_TYPE_DATA_TYPE = 0,		// ս������					uint
//	BATTLE_TYPE_DATA_SORT,			// ���� ��ӦBATTLE_SORT		uint
//	BATTLE_TYPE_DATA_NAME,			// ����						varchar32
//	BATTLE_TYPE_DATA_ROUND1,		// �ִ�1 id					uint
//	BATTLE_TYPE_DATA_ROUND2,		// �ִ�2 id					uint
//	BATTLE_TYPE_DATA_ROUND3,		// �ִ�3 id					uint
//	BATTLE_TYPE_DATA_DROP_ID,		// ���� id					uint
//	BATTLE_TYPE_DATA_WIN_ACTION,	// ʤ��ִ�нű�				uint
//	BATTLE_TYPE_DATA_TIME_LIMIT,	// ս��ʱ������				uint
//	BATTLE_TYPE_DATA_SAVE_FLAG,		// �浵���					uint
//	BATTLE_TYPE_DATA_EXP,			// �ؿ��ܾ���				uint
//};
//
//static const char* CONST_DB_BATTLE_ROUND = "battle_round";	// ս���ִα�
//enum BATTLE_ROUND_DATA
//{
//	BATTLE_ROUND_DATA_ID = 0,		// �ִ�id		uint
//	BATTLE_ROUND_DATA_MONSTER1_ID,	// ����1 id		uint
//	BATTLE_ROUND_DATA_MONSTER2_ID,	// ����2 id		uint
//	BATTLE_ROUND_DATA_MONSTER3_ID,	// ����3 id		uint
//	BATTLE_ROUND_DATA_MONSTER4_ID,	// ����4 id		uint
//	BATTLE_ROUND_DATA_MONSTER5_ID,	// ����5 id		uint
//	BATTLE_ROUND_DATA_DROP_ID,		// ����  id		uint
//};
//
//static const char* CONST_DB_BATTLE_MONSTER = "battle_monster";	// ս���������ñ�
//enum BATTLE_MONSTER_DATA
//{
//	BATTLE_MONSTER_DATA_TYPE = 0,						// ��������						uint	
//	BATTLE_MONSTER_DATA_NAME,							// ��������						varchar32
//	BATTLE_MONSTER_DATA_FIGHT_POS,						// ս��λ��, ǰ1, ��2, ��3		uint
//	BATTLE_MONSTER_DATA_POS_SORT,						// վλ����						uint
//	BATTLE_MONSTER_DATA_LEV,							// �ȼ�							uint
//	BATTLE_MONSTER_DATA_STAR,							// �Ǽ�							uint
//	BATTLE_MONSTER_DATA_COLOR,							// ��ɫ							uint
//	BATTLE_MONSTER_DATA_HP,								// �������� ��Ѫ				uint
//	BATTLE_MONSTER_DATA_SP,								// ��������	��ŭ				uint
//	BATTLE_MONSTER_DATA_HIT,							// ��������	����				uint
//	BATTLE_MONSTER_DATA_ATK,							// ��������	�˺�				uint
//	BATTLE_MONSTER_DATA_DEF,							// ��������	����				uint
//	BATTLE_MONSTER_DATA_SPD,							// ��������	�ٶ�				uint
//	BATTLE_MONSTER_DATA_DODGE,							// ��������	����				uint
//	BATTLE_MONSTER_DATA_MAGIC,							// ��������	����				uint
//	BATTLE_MONSTER_DATA_HP_RECOVER,						// �������� ��Ѫ�ظ�			uint
//	BATTLE_MONSTER_DATA_SP_RECOVER,						// ��������	��ŭ�ظ�			uint
//	BATTLE_MONSTER_DATA_PHY_CRIT,						// ��������	�ﱩ				uint
//	BATTLE_MONSTER_DATA_MAG_CRIT,						// ��������	����				uint
//	BATTLE_MONSTER_DATA_VAMPIRE_LEV,					// ��������	��Ѫ�ȼ�			uint
//	BATTLE_MONSTER_DATA_SP_SPEND_DECREASE,				// ��������	��ŭ���Ľ���%		uint
//	BATTLE_MONSTER_DATA_CURE_INCREASE,					// ��������	���Ƽ���Ч�����%	uint
//	BATTLE_MONSTER_DATA_SKILL_SP_TYPE,					// �ؼ�����						uint
//	BATTLE_MONSTER_DATA_SKILL_SP_LEV,					// �ؼ��ȼ�						uint
//	BATTLE_MONSTER_DATA_SKILL_AUTO1_TYPE,				// �Զ�����1 ����				uint
//	BATTLE_MONSTER_DATA_SKILL_AUTO1_LEV,				// �Զ�����1 �ȼ�				uint
//	BATTLE_MONSTER_DATA_SKILL_AUTO2_TYPE,				// �Զ�����2 ����				uint
//	BATTLE_MONSTER_DATA_SKILL_AUTO2_LEV,				// �Զ�����2 �ȼ�				uint
//	BATTLE_MONSTER_DATA_SKILL_AUTO3_TYPE,				// �Զ�����3 ����				uint
//	BATTLE_MONSTER_DATA_SKILL_AUTO3_LEV,				// �Զ�����3 �ȼ�				uint
//	BATTLE_MONSTER_DATA_SKILL_SKILL_JOINT_TYPE,			// ��Я���� ����				uint
//	BATTLE_MONSTER_DATA_SKILL_SKILL_JOINT_LEV,			// ��Я���� �ȼ�				uint
//	BATTLE_MONSTER_DATA_ANGER_PARAM,					// ��ŭת��ϵ��%				uint
//	BATTLE_MONSTER_DATA_DROP_ID,						// �������						uint
//	BATTLE_MONSTER_DATA_KILL_ACTION,					// ��ɱaction					uint
//};
//
//static const char* CONST_DB_NAME_PEIFANG_TYPE = "peifang_type";	// �䷽�������ñ�
//enum PEIFANG_TYPE_DATA
//{
//	PEIFANG_TYPE_DATA_ID = 0,			// �䷽id			uint
//	PEIFANG_TYPE_DATA_AWARD_ITEMTYPE,	// �����Ʒ����		uint
//	PEIFANG_TYPE_DATA_AWARD_ITEMNUM,	// �����Ʒ����		uint
//	PEIFANG_TYPE_DATA_SPEND_ITEMTYPE1,	// ������Ʒ����1	uint
//	PEIFANG_TYPE_DATA_SPEND_ITEMNUM1,	// ������Ʒ����1	uint
//	PEIFANG_TYPE_DATA_SPEND_ITEMTYPE2,	// ������Ʒ����2	uint
//	PEIFANG_TYPE_DATA_SPEND_ITEMNUM2,	// ������Ʒ����2	uint
//	PEIFANG_TYPE_DATA_SPEND_ITEMTYPE3,	// ������Ʒ����3	uint
//	PEIFANG_TYPE_DATA_SPEND_ITEMNUM3,	// ������Ʒ����3	uint
//	PEIFANG_TYPE_DATA_SPEND_ITEMTYPE4,	// ������Ʒ����4	uint
//	PEIFANG_TYPE_DATA_SPEND_ITEMNUM4,	// ������Ʒ����4	uint
//	PEIFANG_TYPE_DATA_COST_MONEY_TYPE,	// ���Ļ�������		uint
//	PEIFANG_TYPE_DATA_COST_PRICE,		// ���ļ�Ǯ			uint
//};
//
//static const char* CONST_DB_CHALLENGE_BOSS_CONFIG = "challenge_boss";	// ��սboss���ñ�
//enum CHALLENGE_BOSS_CONFIG
//{
//	CHALLENGE_BOSS_CONFIG_BOSS_TYPE = 0,	// boss����			uint
//	CHALLENGE_BOSS_CONFIG_DEGREE,			// �Ѷ�				uint
//	CHALLENGE_BOSS_CONFIG_BATTLE_TYPE,		// ��Ӧս������		uint
//	CHALLENGE_BOSS_CONFIG_NEED_LEV,			// ��Ҫ�ȼ�			uint
//	CHALLENGE_BOSS_CONFIG_ITEM1,			// �׵���Ʒ1		uint
//	CHALLENGE_BOSS_CONFIG_ITEM1_NUM,		// �׵���Ʒ1����	uint
//	CHALLENGE_BOSS_CONFIG_ITEM2,			// �׵���Ʒ2		uint
//	CHALLENGE_BOSS_CONFIG_ITEM2_NUM,		// �׵���Ʒ2����	uint
//	CHALLENGE_BOSS_CONFIG_ITEM3,			// �׵���Ʒ3		uint
//	CHALLENGE_BOSS_CONFIG_ITEM3_NUM,		// �׵���Ʒ3����	uint
//	CHALLENGE_BOSS_CONFIG_ITEM4,			// �׵���Ʒ4		uint
//	CHALLENGE_BOSS_CONFIG_ITEM5_NUM,		// �׵���Ʒ4����	uint
//	CHALLENGE_BOSS_CONFIG_DROP_ID,			// ���׵�����ID		uint
//	CHALLENGE_BOSS_CONFIG_BOSS_NAME,		// boss��			varchar32
//};
//
//static const char* CONST_DB_NAME_LOTTERY_TYPE = "lottery_type";		// �齱�������ñ�
//enum LOTTERY_TYPE_DATA
//{
//	LOTTERY_TYPE_DATA_TYPE = 0,				// �齱����			uint
//	LOTTERY_TYPE_DATA_AWARD_SUM,			// ��Ʒ����			uint
//	LOTTERY_TYPE_DATA_COST_MONEY_TYPE,		// ���Ļ�������		uint
//	LOTTERY_TYPE_DATA_COST_PRICE,			// ���ļ۸�			uint
//	LOTTERY_TYPE_DATA_BASE_ITEM_TYPE,		// ��û�����Ʒ����	uint
//	LOTTERY_TYPE_DATA_BASE_ITEM_NUM,		// ��û�����Ʒ����	uint
//	LOTTERY_TYPE_DATA_RULE_ID1,				// �齱����1		uint
//	LOTTERY_TYPE_DATA_GIVE_COUNT1,			// ��ȡ����1		uint
//	LOTTERY_TYPE_DATA_GIVE_CHANCE1,			// ��ȡ����1		uint
//	LOTTERY_TYPE_DATA_RULE_ID2,				// �齱����2		uint
//	LOTTERY_TYPE_DATA_GIVE_COUNT2,			// ��ȡ����2		uint
//	LOTTERY_TYPE_DATA_GIVE_CHANCE2,			// ��ȡ����2		uint
//	LOTTERY_TYPE_DATA_RULE_ID3,				// �齱����3		uint
//	LOTTERY_TYPE_DATA_GIVE_COUNT3,			// ��ȡ����3		uint
//	LOTTERY_TYPE_DATA_GIVE_CHANCE3,			// ��ȡ����3		uint
//	LOTTERY_TYPE_DATA_RULE_ID4,				// �齱����4		uint
//	LOTTERY_TYPE_DATA_GIVE_COUNT4,			// ��ȡ����4		uint
//	LOTTERY_TYPE_DATA_GIVE_CHANCE4,			// ��ȡ����4		uint
//};
//
//static const char* CONST_DB_NAME_LOTTERY_RULE = "lottery_rule";	// �齱�������ñ�
//enum LOTTERY_RULE_DATA
//{
//	LOTTERY_RULE_DATA_RULE_ID = 0,			// ����id			uint
//	LOTTERY_RULE_DATA_PRIZE_TYPE,			// ��������			uint
//	LOTTERY_RULE_DATA_WEIGHT,				// ����Ȩ��			uint
//	LOTTERY_RULE_DATA_TIME_TYPE,			// ʱ������(0���ã�1�죬2�ܣ�3��)			uint
//	LOTTERY_RULE_DATA_TIME_INDEX,			// ��������(�ܣ�0-6λ��ʾ����0-31λ��ʾ)	uint
//	LOTTERY_RULE_DATA_BEGIN_TIME,			// ��Ʒ��Чʱ��		uint
//	LOTTERY_RULE_DATA_END_TIME,				// ��ƷʧЧʱ��		uint
//};
//
//static const char* CONST_DB_NAME_PRIZE_TYPE = "prize_type";		// �����������ñ�
//enum PRIZE_TYPE_DATA
//{
//	PRIZE_TYPE_DATA_ID		= 0,			// ����id			uint
//	PRIZE_TYPE_DATA_TYPE,					// ��Ʒ����			uint
//	PRIZE_TYPE_DATA_MIN_NUM,				// ��С��Ʒ����		uint
//	PRIZE_TYPE_DATA_MAX_NUM,				// ���Ʒ����������ֵ�����ȡ������		uint
//};
//
//static const char* CONST_DB_NAME_PROPERTY_CALCRANK2 = "property_calcrank2";	// 2�����Խ������ñ�
//enum PROPERTY_CALCRANK2_DATA
//{
//	PROPERTY_CALCRANK2_DATA_TYPE = 0,	// ������			uint
//	PROPERTY_CALCRANK2_DATA_LIFE,		// ����:��Ѫϵ��	uint
//	PROPERTY_CALCRANK2_DATA_MANA,		// ħ��:����ϵ��	uint
//	PROPERTY_CALCRANK2_DATA_STR_HIT,	// ����:����ϵ��	uint
//	PROPERTY_CALCRANK2_DATA_STR_ATK,	// ����:�˺�ϵ��	uint
//	PROPERTY_CALCRANK2_DATA_STA,		// ����:����ϵ��	uint
//	PROPERTY_CALCRANK2_DATA_DEX,		// ����:���ϵ��	uint
//};
//
//static const char* CONST_DB_NAME_MONEY_AWARD_CHANCE = "money_award_chance";	// ҡǮ���౶�����ͼ������ñ�
//enum MONEY_AWARD_CHANCE_DATA
//{
//	MONEY_AWARD_CHANCE_DATA_COUNT = 0,		// ҡǮ����		uint
//	MONEY_AWARD_CHANCE_DATA_COST,			// ҡǮ����		uint
//	MONEY_AWARD_CHANCE_DATA_MULTIPLE1,		// ��������1	uint
//	MONEY_AWARD_CHANCE_DATA_CRILCHANCE1,	// ��������1	uint
//	MONEY_AWARD_CHANCE_DATA_MULTIPLE2,		// ��������2	uint
//	MONEY_AWARD_CHANCE_DATA_CRILCHANCE2,	// ��������2	uint
//	MONEY_AWARD_CHANCE_DATA_MULTIPLE3,		// ��������3	uint
//	MONEY_AWARD_CHANCE_DATA_CRILCHANCE3,	// ��������3	uint
//	MONEY_AWARD_CHANCE_DATA_MULTIPLE4,		// ��������4	uint
//	MONEY_AWARD_CHANCE_DATA_CRILCHANCE4,	// ��������4	uint
//};
//
//static const char* CONST_DB_NAME_INSTANCE_TYPE = "instance_type";	// �����������ñ�
//enum INSTANCE_TYPE_DATA
//{
//	INSTANCE_TYPE_DATA_TYPE = 0,			// �������ͣ�1��Ҳ�����2���������		uint
//	INSTANCE_TYPE_DATA_DIFFICULTY,			// �����Ѷ�								uint
//	INSTANCE_TYPE_DATA_OPENTIME_TYPE,		// ��������ʱ�����ͣ�1�죬2�ܣ�3�£�	uint
//	INSTANCE_TYPE_DATA_OPENTIME_INDEX,		// ��������ʱ���������죺0���ܡ��£�32λ��������	uint
//	INSTANCE_TYPE_DATA_OPENTIME_BEGIN,		// ��������ʱ�俪ʼ						uint
//	INSTANCE_TYPE_DATA_OPENTIME_END,		// ��������ʱ�����						uint
//	INSTANCE_TYPE_DATA_OPEN_LEV,			// �����ȼ�								uint
//	INSTANCE_TYPE_DATA_COST_POWER,			// ��������								uint
//	INSTANCE_TYPE_DATA_BATTLE_TYPE,			// ս������								uint
//};
//
//static const char* CONST_DB_NAME_POKER_COLOR_ATTR = "poker_color_attr";	// ������ɫ�������ñ�
//enum POKER_COLOR_ATTR_DATA
//{
//	POKER_COLOR_ATTR_DATA_POKER_COLOR = 0,	// ������ɫ		uint
//	POKER_COLOR_ATTR_DATA_LIFE,				// ����			uint
//	POKER_COLOR_ATTR_DATA_MANA,				// ħ��			uint
//	POKER_COLOR_ATTR_DATA_STR,				// ����			uint
//	POKER_COLOR_ATTR_DATA_STA,				// ����			uint
//	POKER_COLOR_ATTR_DATA_DEX,				// ����			uint
//};
//
//static const char* CONST_DB_NAME_PUZZLE = "puzzle";	// �Թ����ñ�
//enum PUZZLE_DATA
//{
//	PUZZLE_DATA_ID = 0,						// �Թ�����id	uint
//	PUZZLE_DATA_LINK_ID1,					// ���Ӹ���id1	uint
//	PUZZLE_DATA_LINK_ID2,					// ���Ӹ���id2	uint
//	PUZZLE_DATA_LINK_ID3,					// ���Ӹ���id3	uint
//	PUZZLE_DATA_LINK_ID4,					// ���Ӹ���id4	uint
//	PUZZLE_DATA_LINK_ID5,					// ���Ӹ���id5	uint
//	PUZZLE_DATA_LINK_ID6,					// ���Ӹ���id6	uint
//	PUZZLE_DATA_TASK_TYPE,					// ��������		uint
//	PUZZLE_DATA_BATTLE_TYPE,				// ս������		uint
//	PUZZLE_DATA_ACTION_ID,					// ִ�еĽű�ID	uint
//	PUZZLE_DATA_PROGRESS_ADD,				// ���ӽ���		uint
//};
//
//static const char* CONST_DB_NAME_PUZZLE_BUFF = "puzzle_buff";	// �Թ�BUFF���ñ�
//enum PUZZLE_BUFF
//{
//	PUZZLE_BUFF_ID = 0,						// BUFF����		uint
//	PUZZLE_BUFF_NAME,						// BUFF����		varchar32
//	PUZZLE_BUFF_VALUE,						// BUFF����ֵ	uint
//	PUZZLE_BUFF_EFFECT,						// BUFF��Ч����	uint
//};
//
//static const char* CONST_DB_NAME_ARENA_AWARD = "arena_award";	// �������������ñ�
//enum ARENA_AWARD
//{
//	ARENA_AWARD_TYPE = 0,					// �������ֱ�	uint
//	ARENA_AWARD_UPPER_LEV,					// ������������	uint
//	ARENA_AWARD_LOWER_LEV,					// ������������	uint
//	ARENA_AWARD_GOLD_COUNT,					// ���������	uint
//	ARENA_AWARD_MONEY_COUNT,				// ������������	uint
//	ARENA_AWARD_VAS_COUNT,					// ����Ԫ��		uint
//	ARENA_AWARD_ITEM_TYPE,					// ������Ʒtype	uint
//	ARENA_AWARD_ITEM_COUNT,					// ������Ʒ��	uint
//	ARENA_AWARD_MONEY_COUNT_PER,			// ��ʱ������	uint
//	ARENA_AWARD_END,
//};
//
//static const char* CONST_DB_NAME_ARENA_AI_POKER = "arena_ai_poker";	// �����������˿������ñ�
//enum ARENA_AI_POKER_DATA
//{
//	ARENA_AI_POKER_DATA_ARENA_TYPE = 0,		// ���������	uint
//	ARENA_AI_POKER_DATA_LOW_RANK,			// ������Χ����	uint
//	ARENA_AI_POKER_DATA_POKER_TYPE,			// ����typeid	uint
//};
//
//static const char* CONST_DB_NAME_PAY_CONFIG = "pay_config";		// ��ֵ���ñ�
//enum PAY_CONFIG_DATA
//{
//	PAY_CONFIG_DATA_ID = 0,				// id(�׳�����)			uint
//	PAY_CONFIG_DATA_RMB,				// �����				uint
//	PAY_CONFIG_DATA_VAS,				// Ԫ��					uint
//	PAY_CONFIG_DATA_FREE_VAS,			// ����Ԫ��				uint
//	PAY_CONFIG_DATA_FREE_VAS_DES,		// ����Ԫ��˵��			uint
//	PAY_CONFIG_DATA_FISRT_FREE_VAS,		// �׳�����Ԫ��			uint
//	PAY_CONFIG_DATA_FISRT_FREE_DES,		// �׳�����Ԫ��˵��		uint
//	PAY_CONFIG_DATA_MONTH_CARD,			// �¿����				uint
//};
//
//static const char* CONST_DB_NAME_WAR_ROAD = "war_road";			// ս�����ñ�
//enum WAR_ROAD_DATA
//{
//	WAR_ROAD_DATA_WAR_KEY = 0,			// ս��key��ģʽ*1000000+�½�*1000+�ؿ�����ģʽ1��ͨ��2��Ӣ��3�Ŷӣ�	uint
//	WAR_ROAD_DATA_OPEN_LEV,				// �����ȼ�						uint
//	WAR_ROAD_DATA_COST_POWER,			// ��������						uint
//	WAR_ROAD_DATA_BATTLE_TYPE,			// ս������						uint
//};
//
//static const char* CONST_DB_NAME_WAR_ROAD_TEAM = "war_road_team";	// �Ŷ�ս�����ñ�
//enum WAR_ROAD_TEAM_DATA
//{
//	WAR_ROAD_TEAM_DATA_CHAPTER = 0,		// �½�							uint
//	WAR_ROAD_TEAM_DATA_CHAPTER_NAME,	// �½�����						varchar
//	WAR_ROAD_TEAM_DATA_OPEN_COST,		// �������ģ���Ծֵ��			uint
//	WAR_ROAD_TEAM_DATA_AWARD_RULE,		// ս��Ʒ��⣨lottery_award�������ã�			uint
//	WAR_ROAD_TEAM_DATA_AWARD_TIME,		// ����ͨ�ؽ���ʱ��				uint
//	WAR_ROAD_TEAM_DATA_AWARD_COUNT,		// ���⽱���ﹱ����				uint
//	WAR_ROAD_TEAM_DATA_PASS_WIN_COUNT,	// �ؿ�ʤ�������ﹱ����			uint
//};
//
//static const char* CONST_DB_NAME_TERRITORY_FIGHT = "territory_fight";		// ���ս���ñ�
//enum TERRITORY_FIGHT_DATA
//{
//	TERRITORY_FIGHT_DATA_ID = 0,				// ���id					uint
//	TERRITORY_FIGHT_DATA_TYPE,					// ���type					uint
//	TERRITORY_FIGHT_DATA_BATTLETYPE,			// ս��type					uint
//	TERRITORY_FIGHT_DATA_EFFECT,				// ���Ч��					uint
//	TERRITORY_FIGHT_DATA_POKER_LEV_LIMIT,		// ���ս��ս���ӵȼ�����	uint
//	TERRITORY_FIGHT_DATA_BOSS_NAME,				// פ��boss����				varchar
//
//};
//
//static const char* CONST_DB_NAME_TERRITORY_FIGHT_MONSTER = "territory_fight_monster";	// ���սĬ��פ�ع�
//enum TERRITORY_FIGHT_MONSTER_DATA
//{
//	TERRITORY_FIGHT_MONSTER_DATA_TROOPS_ID = 0,	// 
//	TERRITORY_FIGHT_MONSTER_DATA_ID,
//	TERRITORY_FIGHT_MONSTER_DATA_POKERID1,
//	TERRITORY_FIGHT_MONSTER_DATA_POKERID2,
//	TERRITORY_FIGHT_MONSTER_DATA_POKERID3,
//	TERRITORY_FIGHT_MONSTER_DATA_POKERID4,
//	TERRITORY_FIGHT_MONSTER_DATA_POKERID5,
//};
//
//static const char* CONST_DB_NAME_DATA_RESET	= "data_reset";		// �����������ñ�
//enum DATA_RESET_DATA
//{
//	DATA_RESET_DATA_TYPE = 0,					// ��������					uint
//	DATA_RESET_DATA_COUNT,						// ���ô���					uint
//	DATA_RESET_DATA_COST_TYPE,					// ��������					uint
//	DATA_RESET_DATA_COST_NUM,					// ��������					uint
//};
//
//static const char* CONST_DB_NAME_SYN_GIFT_BOX	= "syn_giftbox";// ����������ñ�
//enum SYN_GIFT_BOX_DATA
//{
//	SYN_GIFT_BOX_DATA_TYPE = 0,					// �������					uint
//	SYN_GIFT_BOX_DATA_LEV,						// ��еȼ�					uint
//	SYN_GIFT_BOX_DATA_EXP,						// ��о���					uint
//	SYN_GIFT_BOX_DATA_KEEP_TIME,				// ����ʱ��					uint
//	SYN_GIFT_BOX_DATA_DATA1,					// ����1					uint
//	SYN_GIFT_BOX_DATA_DATA2,					// ����2					uint
//	SYN_GIFT_BOX_DATA_RULE_ID,					// ������������id			uint
//};
//
//static const char* CONST_DB_NAME_LOOKFACE_FRAME = "lookface_frame";	// ͷ������ñ�
//enum LOOKFACE_FRAME_DATA
//{
//	LOOKFACE_FRAME_DATA_TYPE = 0,				// ͷ�������			uint
//	LOOKFACE_FRAME_DATA_VIP_LEV,				// vip�ȼ�				uint
//	LOOKFACE_FRAME_DATA_SINGLE_ARENA_RANK,		// ��ǰ���Ӿ���������	uint
//	LOOKFACE_FRAME_DATA_MULTI_ARENA_RANK,		// ��ǰ��Ӿ���������	uint
//	LOOKFACE_FRAME_DATA_TIME_LIMIT,				// ʱ������				uint
//	LOOKFACE_FRAME_DATA_PARAM1,					// Ԥ��1				uint
//	LOOKFACE_FRAME_DATA_PARAM2,					// Ԥ��2				uint
//	LOOKFACE_FRAME_DATA_NAME,					// ����					uint
//};
//
//static const char* CONST_DB_NAME_IP_LIBRARY = "ip_library";		// ip�����ñ�
//enum IP_LIBRARY_DATA
//{
//	IP_LIBRARY_DATA_ID = 0,				// ID							uint
//	IP_LIBRARY_DATA_IP_BEGIN,			// ��ʼIP						varchar16
//	IP_LIBRARY_DATA_IP_END,				// ����IP						varchar16
//	IP_LIBRARY_DATA_IP_BEGIN_INT,		// ��ʼIP(����)					uint
//	IP_LIBRARY_DATA_IP_END_INT,			// ����IP(����)					uint
//	IP_LIBRARY_DATA_ADDRESS1,			// ��ַ1						varchar64
//	IP_LIBRARY_DATA_ADDRESS2,			// ��ַ2						varchar128
//	IP_LIBRARY_DATA_ADDRESS_FINAL,		// ��������						varchar64
//	IP_LIBRARY_DATA_ADDRESS_ID,			// �������						uint
//};
//
//
//static const char* CONST_DB_NAME_ROOM_TYPE = "room_type";
//enum ROOM_TYPE_DATA
//{
//	ROOM_TYPE_DATA_TYPE = 0,		// ��������			uint
//	ROOM_TYPE_DATA_NAME,			// ��������			varchar64
//	ROOM_TYPE_DATA_KEEP_TIME,		// �������ʱ��		uint
//	ROOM_TYPE_DATA_MAX_MEMBER,		// ����Ա����		uint
//	ROOM_TYPE_DATA_MONSTER1,		// ��������1		uint
//	ROOM_TYPE_DATA_MONSTER2,		// ��������2		uint
//	ROOM_TYPE_DATA_MONSTER3,		// ��������3		uint
//	ROOM_TYPE_DATA_MONSTER4,		// ��������4		uint
//	ROOM_TYPE_DATA_MONSTER5,		// ��������5		uint
//	ROOM_TYPE_DATA_MONSTER6,		// ��������6		uint
//	ROOM_TYPE_DATA_MONSTER7,		// ��������7		uint
//	ROOM_TYPE_DATA_MONSTER8,		// ��������8		uint
//	ROOM_TYPE_DATA_MONSTER9,		// ��������9		uint
//	ROOM_TYPE_DATA_MONSTER10,		// ��������10		uint
//	ROOM_TYPE_DATA_MONSTER11,		// ��������11		uint
//	ROOM_TYPE_DATA_MONSTER12,		// ��������12		uint
//	ROOM_TYPE_DATA_MONSTER13,		// ��������13		uint
//	ROOM_TYPE_DATA_MONSTER14,		// ��������14		uint
//	ROOM_TYPE_DATA_MONSTER15,		// ��������15		uint
//};
//
//static const char* CONST_DB_NAME_ROOM_MONSTER = "room_monster";
//enum ROOM_MONSTER_DATA
//{
//	ROOM_MONSTER_DATA_TYPE = 0,			// ��������								uint
//	ROOM_MONSTER_DATA_SORT,				// ������ʽ		1���� 2�ɼ���			uint
//	ROOM_MONSTER_DATA_BATTLE_TYPE,		// ս������		1���ﴥ����ս������		uint
//	ROOM_MONSTER_DATA_REBORN_SECOND,	// ��������		0��ʾ������				uint
//	ROOM_MONSTER_DATA_PICK_SECOND,		// �ɼ�ʱ��								uint
//	ROOM_MONSTER_DATA_PICK_ACTION,		// �ɼ���action							uint
//};
//
//static const char* CONST_DB_NAME_NAME_LIBRARY = "name_library";		// ���ֿ�
//enum NAME_LIBRARY_DATA
//{
//	NAME_LIBRARY_DATA_ID = 0,			// id	uint
//	NAME_LIBRARY_DATA_SURNAME,			// ��	varchar
//	NAME_LIBRARY_DATA_NAME,				// ��	varchar
//};
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// ���������¼�������
//enum RELOAD_CONST_TABLE_TYPE
//{
//	RELOAD_CONST_TABLE_TYPE_SERVER_START_TIME = 0,
//	RELOAD_CONST_TABLE_TYPE_LUA_FILE,
//	RELOAD_CONST_TABLE_TYPE_POKER_COLOR_ATTR_SUM,
//
//	RELOAD_CONST_TABLE_TYPE_CONFIGDATA,
//	RELOAD_CONST_TABLE_TYPE_CONFIGTEXT,
//	RELOAD_CONST_TABLE_TYPE_TASK_DATA,
//	RELOAD_CONST_TABLE_TYPE_NEWCARDPRIZE,
//	RELOAD_CONST_TABLE_TYPE_NOTIFY_CONFIG,
//	RELOAD_CONST_TABLE_TYPE_ACTIVITYCONFIG,
//	RELOAD_CONST_TABLE_TYPE_ACTION,
//	RELOAD_CONST_TABLE_TYPE_POKER_TYPE,
//	RELOAD_CONST_TABLE_TYPE_POKER_STAR_GROW,
//	RELOAD_CONST_TABLE_TYPE_POKER_EQUIP,
//	RELOAD_CONST_TABLE_TYPE_POKER_STAR,
//	RELOAD_CONST_TABLE_TYPE_POKER_COLOR_ATTR,
//	RELOAD_CONST_TABLE_TYPE_LEV_EXP,
//	RELOAD_CONST_TABLE_TYPE_SIGNPRIZE,
//	RELOAD_CONST_TABLE_TYPE_VIP,
//	RELOAD_CONST_TABLE_TYPE_ITEM_TYPE,
//	RELOAD_CONST_TABLE_TYPE_ITEM_COLOR,
//	RELOAD_CONST_TABLE_TYPE_ITEM_STAR_ATTR,
//	RELOAD_CONST_TABLE_TYPE_LIVENESS,
//	RELOAD_CONST_TABLE_TYPE_SHOP_TYPE,
//	RELOAD_CONST_TABLE_TYPE_SHOP_RULE,
//	RELOAD_CONST_TABLE_TYPE_ACHIEVEMENT,
//	RELOAD_CONST_TABLE_TYPE_LUA_TEXT,
//	RELOAD_CONST_TABLE_TYPE_SKILL_TYPE,
//	RELOAD_CONST_TABLE_TYPE_DROP_RULE,
//	RELOAD_CONST_TABLE_TYPE_BATTLE_TYPE,
//	RELOAD_CONST_TABLE_TYPE_BATTLE_ROUND,
//	RELOAD_CONST_TABLE_TYPE_BATTLE_MONSTER,
//	RELOAD_CONST_TABLE_TYPE_PEIFANG,
//	RELOAD_CONST_TABLE_TYPE_CHALLENGE_BOSS,
//	RELOAD_CONST_TABLE_TYPE_LOTTERY_TYPE,
//	RELOAD_CONST_TABLE_TYPE_LOTTERY_RULE,
//	RELOAD_CONST_TABLE_TYPE_PRIZE_TYPE,
//	RELOAD_CONST_TABLE_TYPE_PROPERTY_CALCRANK2,
//	RELOAD_CONST_TABLE_TYPE_MONEY_AWARD_CHANCE,
//	RELOAD_CONST_TABLE_TYPE_INSTANCE_TYPE,
//	RELOAD_CONST_TABLE_TYPE_PUZZLE,
//	RELOAD_CONST_TABLE_TYPE_PUZZLE_BUFF,
//	RELOAD_CONST_TABLE_TYPE_PAY_CONFIG,
//	RELOAD_CONST_TABLE_TYPE_ARENA_AWARD,
//	RELOAD_CONST_TABLE_TYPE_ARENA_AI_POKER,
//	RELOAD_CONST_TABLE_TYPE_WAR_ROAD,
//	RELOAD_CONST_TABLE_TYPE_WAR_ROAD_TEAM,
//	RELOAD_CONST_TABLE_TYPE_TERRITORY_FIGHT,
//	RELOAD_CONST_TABLE_TYPE_TERRITORY_FIGHT_MONSTER,
//	RELOAD_CONST_TABLE_TYPE_DATA_RESET,
//	RELOAD_CONST_TABLE_TYPE_SYN_GIFT_BOX,
//	RELOAD_CONST_TABLE_TYPE_LOOKFACE_FRAME,
//	RELOAD_CONST_TABLE_TYPE_ROOM_TYPE,
//	RELOAD_CONST_TABLE_TYPE_ROOM_MONSTER,
//	RELOAD_CONST_TABLE_TYPE_NAME_LIBRARY,
//	RELOAD_CONST_TABLE_TYPE_END,
//};

#endif // end of _DATABASE_DEFINE_CONST_H_