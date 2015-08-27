////////////////////////////////////////////////////////////////////////
// Import : ��Ϸ������ȫ��������
// Moudle : DatabaseDefineGame.h
// Author : �½���(Chen Jianjun)
// Created: 2015-08-27
////////////////////////////////////////////////////////////////////////
#ifndef _DATABASE_DEFINE_GAME_H_
#define _DATABASE_DEFINE_GAME_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

static const char* GAME_DB_NAME_USER = "user";	// ��ɫ��
enum USER_DATA
{
	USER_DATA_ID = 0,			// ��ɫid, 1000W��				bigint
	USER_DATA_NAME,				// ��ɫ��						varchar32
	USER_DATA_ACCOUNT_ID,		// �˺�id						uint
	USER_DATA_ACCOUNT_TYPE,		// �˺�����, �˺ű���			uint
	USER_DATA_CREATE_TIME,		// ����ʱ��(utcʱ��)			uint
	USER_DATA_LOGIN_TIME,		// ��½����(YYYYMMDD)			uint
	USER_DATA_EXIT_TIME,		// �˳�ʱ��(utcʱ��)			uint
	USER_DATA_ALL_ONLINE_TIME,	// ������ʱ��(��λ��)			uint
	USER_DATA_DEL_FLAG,			// ��ɾ�����					uint
	USER_DATA_SERVER_GROUP,		// ������������					uint
	USER_DATA_LEV,				// �ȼ�							uint
	USER_DATA_EXP,				// ����							bigint
	USER_DATA_CAMP,				// ��Ӫ							uint
	USER_DATA_FLAGSHIP,			// �콢							uint
	USER_DATA_SCORE,			// ս����						uint
	USER_DATA_RECORD_GALAXY,	// ��¼��ϵ						uint
	USER_DATA_RECORD_X,			// ��¼����X					uint
	USER_DATA_RECORD_Y,			// ��¼����Y					uint
	USER_DATA_RECORD_REST,		// ��¼��ŵ�NPC				uint
	USER_DATA_STOPTALK_ENDTIME,	// ���Խ���ʱ��					uint
};

//static const char* GAME_DB_NAME_USER_MONEY = "user_money";	// ��ɫ��ұ�
//enum USER_MONEY_DATA
//{
//	USER_MONEY_DATA_ID = 0,		// id			bigint
//	USER_MONEY_DATA_USERID,		// ��ɫid		bigint
//	USER_MONEY_DATA_MONEYTYPE,	// ��������		uint
//	USER_MONEY_DATA_MONEYDATA,	// ��������		bigint
//};
//
//static const char* GAME_DB_NAME_USER_VAS = "user_vas";	// ��ɫԪ����
//enum USER_VAS_DATA
//{
//	USER_VAS_DATA_USER_ID = 0,				// ��ɫid			uint
//	USER_VAS_DATA_VAS,						// ��ǰԪ��			bigint
//	USER_VAS_DATA_TOTAL_PAY_VAS,			// �ܳ�ֵԪ��		bigint
//	USER_VAS_DATA_TOTAL_FREE_VAS,			// ������Ԫ��		bigint
//	USER_VAS_DATA_TOTAL_USE_VAS,			// ������Ԫ��		bigint
//	USER_VAS_DATA_FISRT_SPEND_TIME,			// ��һ������ʱ��	uint
//	USER_VAS_DATA_LAST_SPEND_TIME,			// �������ʱ��		uint
//	USER_VAS_DATA_MONTH_CARD_ID,			// �¿�id			uint
//	USER_VAS_DATA_MONTH_CARD_GOT_DATE,		// ��ȡ��������		uint
//	USER_VAS_DATA_MONTH_CARD_END_DATE,		// ���һ����ȡ����	uint
//	USER_VAS_DATA_FISRT_MASK,				// ��һ����ȡ����	uint
//};
//
//static const char* GAME_DB_NAME_USER_MASK = "user_mask";	// ���������
//enum USER_MASK_DATA
//{
//	USER_MASK_DATA_ID = 0,				// id,			int
//	USER_MASK_DATA_USERID,				// ���id,		uint
//	USER_MASK_DATA_MASKTYPE,			// ��������,	uint
//	USER_MASK_DATA_MASKID,				// ����id,		uint
//	USER_MASK_DATA_CLEARTIME,			// ����ʱ��		uint
//	USER_MASK_DATA_MASKDATA,			// ��������		bigint
//};
//
//static const char* GAME_DB_NAME_GROUP_MASK = "group_mask";	// �������
//enum LINE_MASK_DATA
//{
//	LINE_MASK_DATA_ID = 0,				// ����id,		int
//	LINE_MASK_DATA_SERVER_GROUP,		// ��������,	uint
//	LINE_MASK_DATA_DATA,				// ����			uint
//	LINE_MASK_DATA_ENDTIME,				// ����ʱ��		uint
//};
//
//static const char* GAME_DB_NAME_WORLD_MASK = "world_mask";	// ���������
//enum SERVER_MASK_DATA
//{
//	SERVER_MASK_DATA_ID = 0,			// ����id,		int
//	SERVER_MASK_DATA_DATA,				// ����			uint
//	SERVER_MASK_DATA_ENDTIME,			// ����ʱ��		uint
//};
//
//static const char* GAME_DB_NAME_ITEM_LOG = "item_log";	// ��Ʒ�����
//enum LOG_ITEM_FLOW_DATA
//{
//	LOG_ITEM_FLOW_DATA_ID = 0,		// ������id					bigint
//	LOG_ITEM_FLOW_DATA_OWNERID,		// ����id					uint
//	LOG_ITEM_FLOW_DATA_TARGETID,	// ��������id				uint
//	LOG_ITEM_FLOW_DATA_ITEMID,		// ��Ʒid					bigint
//	LOG_ITEM_FLOW_DATA_ITEMTYPE,	// ��Ʒtypeid				uint
//	LOG_ITEM_FLOW_DATA_ITEMCOUNT,	// ��Ʒ����					uint
//	LOG_ITEM_FLOW_DATA_TYPE,		// ��Ʒ����					uint
//	LOG_ITEM_FLOW_DATA_CREATETIME,	// ����ʱ��(utcʱ�䣩		uint
//	LOG_ITEM_FLOW_DATA_SERVERID,	// ��������					uint
//	LOG_ITEM_FLOW_DATA_LINE,		// ��·						uint
//	LOG_ITEM_FLOW_DATA_COMMENT,		// ˵���ֶ�					varchar128
//};
//
//static const char* GAME_DB_NAME_USER_TMP_DATA = "user_tmp_data";	// ��ɫTmpdata��
//enum USERTMPDATA_DATA
//{
//	USERTMPDATA_ERROR = -1,
//	USERTMPDATA_ID = 0,							// id		bigint										
//	USERTMPDATA_USERID,							// ���id	uint
//	USERTMPDATA_TMP_DATA_ID,					// ����id	uint
//
//	USERTMPDATA_DATA_BEGIN,
//	USERTMPDATA_DATA0 = USERTMPDATA_DATA_BEGIN,	// ����0	uint
//	USERTMPDATA_DATA1,							// ����1	uint
//	USERTMPDATA_DATA2,							// ����2	uint
//	USERTMPDATA_DATA3,							// ����3	uint					
//	USERTMPDATA_DATA4,							// ����4	uint
//	USERTMPDATA_DATA5,							// ����5	uint
//	USERTMPDATA_DATA6,							// ����6	uint
//	USERTMPDATA_DATA7,							// ����7	uint
//	USERTMPDATA_DATA_END,
//};
//
//static const char* GAME_DB_NAME_USER_TASK = "user_task";			// ��ɫ�����
//enum EUSER_TASK
//{	
//	EUSER_TASK_ID			= 0,	// ���														uint
//	EUSER_TASK_USER_ID,				// ���id													uint
//	EUSER_TASK_TYPE,				// ��������													uint
//	EUSER_TASK_STEP,				// ����														uint
//	EUSER_TASK_STATUS,				// ����״̬(0:δ����,1:����, 2:�ύ, 3:�ﵽ���������δ�ύ)uint
//	EUSER_TASK_COUNT1,				// ����1													uint
//	EUSER_TASK_COUNT2,				// ����2													uint
//	EUSER_TASK_COUNT3,				// ����3													uint
//	EUSER_TASK_BEGIN_TIME,			// ��ʼʱ��(��λ��)											uint
//	EUSER_TASK_OVER_TIME,			// ����ʱ��(0:������, >0:����ʱ�䵥λ��)					uint
//};
//
//static const char* GAME_DB_NAME_USER_NEWCARD = "user_newcard";		// ��ɫ���ֿ�ʹ����Ϣ��
//enum USER_NEWCARD_DATA
//{
//	USER_NEWCARD_DATA_USERID = 0,	// ���id		uint
//	USER_NEWCARD_DATA_LASTUSETIME,	// �ϴ�ʹ��ʱ��	uint
//	// �����ֶ�Ϊ20������ʹ������	bigint
//	USER_NEWCARD_DATA_MASKDATA1,
//	USER_NEWCARD_DATA_MASKDATA2,
//	USER_NEWCARD_DATA_MASKDATA3,
//	USER_NEWCARD_DATA_MASKDATA4,
//	USER_NEWCARD_DATA_MASKDATA5,
//	USER_NEWCARD_DATA_MASKDATA6,
//	USER_NEWCARD_DATA_MASKDATA7,
//	USER_NEWCARD_DATA_MASKDATA8,
//	USER_NEWCARD_DATA_MASKDATA9,
//	USER_NEWCARD_DATA_MASKDATA10,
//	USER_NEWCARD_DATA_MASKDATA11,
//	USER_NEWCARD_DATA_MASKDATA12,
//	USER_NEWCARD_DATA_MASKDATA13,
//	USER_NEWCARD_DATA_MASKDATA14,
//	USER_NEWCARD_DATA_MASKDATA15,
//	USER_NEWCARD_DATA_MASKDATA16,
//	USER_NEWCARD_DATA_MASKDATA17,
//	USER_NEWCARD_DATA_MASKDATA18,
//	USER_NEWCARD_DATA_MASKDATA19,
//	USER_NEWCARD_DATA_MASKDATA20,
//};
//
//static const char* GAME_DB_NAME_USER_MAIL	= "mail";	// ����ʼ���
//enum EUSER_MAIL
//{
//	EUSER_MAIL_ID		= 0,	// ���									bigint
//	EUSER_MAIL_USER_ID,			// ���ID								uint
//	EUSER_MAIL_STATUS,			// �ʼ�״̬(0:δ��, 1:�Ѷ�, 2:ɾ��)		uint
//	EUSER_MAIL_TITLE,			// ����									varchar32
//	EUSER_MAIL_SENDER,			// ������								varchar32
//	EUSER_MAIL_CONTENT,			// ����									varchar256
//	EUSER_MAIL_SEND_TIME,		// ��������								uint
//	EUSER_MAIL_OVER_TIME,		// ����ʱ��(������ʱ������)				uint
//
//	EUSER_MAIL_ITEM_TYPE1,		// ��Ʒ����1							uint
//	EUSER_MAIL_ITEM_NUM1,		// ��Ʒ����1							uint
//	EUSER_MAIL_ITEM_TYPE2,		// ��Ʒ����2							uint
//	EUSER_MAIL_ITEM_NUM2,		// ��Ʒ����2							uint
//	EUSER_MAIL_ITEM_TYPE3,		// ��Ʒ����3							uint
//	EUSER_MAIL_ITEM_NUM3,		// ��Ʒ����3							uint
//	EUSER_MAIL_ITEM_TYPE4,		// ��Ʒ����4							uint
//	EUSER_MAIL_ITEM_NUM4,		// ��Ʒ����4							uint
//	EUSER_MAIL_ITEM_TYPE5,		// ��Ʒ����5							uint
//	EUSER_MAIL_ITEM_NUM5,		// ��Ʒ����5							uint
//	EUSER_MAIL_ITEM_TYPE6,		// ��Ʒ����6							uint
//	EUSER_MAIL_ITEM_NUM6,		// ��Ʒ����6							uint
//
//	EUSER_MAIL_MONEY_TYPE1,		// ����1								uint
//	EUSER_MAIL_MONEY_NUM1,		// ����1����							uint
//	EUSER_MAIL_MONEY_TYPE2,		// ����2								uint
//	EUSER_MAIL_MONEY_NUM2,		// ����2����							uint
//	EUSER_MAIL_MONEY_TYPE3,		// ����3								uint
//	EUSER_MAIL_MONEY_NUM3,		// ����3����							uint
//	EUSER_MAIL_MONEY_TYPE4,		// ����4								uint
//	EUSER_MAIL_MONEY_NUM4,		// ����4����							uint
//	EUSER_MAIL_EXP,				// ����									uint
//	EUSER_MAIL_SERVER_GROUP,	// ��������								uint
//};
//
//
//static const char* GAME_DB_NAME_POKER = "poker";	// ���Ʊ�
//enum POKER_DATA
//{
//	POKER_DATA_ID = 0,			// id				bigint
//	POKER_DATA_TYPE,			// ����				uint
//	POKER_DATA_OWNER_ID,		// ӵ����id			uint
//	POKER_DATA_LEV,				// �ȼ�				uint
//	POKER_DATA_EXP,				// ����				bigint
//	POKER_DATA_COLOR,			// ��ɫ				uint
//	POKER_DATA_STAR,			// �Ǽ�				uint
//	POKER_DATA_EQUIP1_TYPE,		// ��������			uint
//	POKER_DATA_EQUIP1_STAR,		// �����Ǽ�			uint
//	POKER_DATA_EQUIP1_EXP,		// ��������			uint
//	POKER_DATA_EQUIP2_TYPE,		// ͷ������			uint
//	POKER_DATA_EQUIP2_STAR,		// ͷ���Ǽ�			uint
//	POKER_DATA_EQUIP2_EXP,		// ͷ������			uint
//	POKER_DATA_EQUIP3_TYPE,		// ��������			uint
//	POKER_DATA_EQUIP3_STAR,		// �����Ǽ�			uint
//	POKER_DATA_EQUIP3_EXP,		// ��������			uint
//	POKER_DATA_EQUIP4_TYPE,		// ��������			uint
//	POKER_DATA_EQUIP4_STAR,		// �����Ǽ�			uint
//	POKER_DATA_EQUIP4_EXP,		// ��������			uint
//	POKER_DATA_EQUIP5_TYPE,		// �·�����			uint
//	POKER_DATA_EQUIP5_STAR,		// �·��Ǽ�			uint
//	POKER_DATA_EQUIP5_EXP,		// �·�����			uint
//	POKER_DATA_EQUIP6_TYPE,		// Ь������			uint
//	POKER_DATA_EQUIP6_STAR,		// Ь���Ǽ�			uint
//	POKER_DATA_EQUIP6_EXP,		// Ь�Ӿ���			uint
//	POKER_DATA_SKILL_SP_LEV,	// �ؼ��ȼ�			uint
//	POKER_DATA_SKILL_AUTO1_LEV,	// �Զ�����1�ȼ�	uint
//	POKER_DATA_SKILL_AUTO2_LEV,	// �Զ�����2�ȼ�	uint
//	POKER_DATA_SKILL_AUTO3_LEV,	// �Զ�����3�ȼ�	uint
//	POKER_DATA_SKILL_JOINT_LEV,	// ��Я���ܵȼ�		uint
//	POKER_DATA_STATE,			// ����״̬��0���У�1��Ӫ��2�ڿ�	uint
//};
//
//static const char* GAME_DB_NAME_POKER_LOG = "poker_log";	// ��Ʒ�����
//enum POKER_LOG_DATA
//{
//	POKER_LOG_DATA_ID = 0,		// ������id					bigint
//	POKER_LOG_DATA_OWNERID,		// ����id					uint
//	POKER_LOG_DATA_TARGETID,	// ��������id				uint
//	POKER_LOG_DATA_POKER_ID,	// ����id					bigint
//	POKER_LOG_DATA_POKER_TYPE,	// ����type					uint
//	POKER_LOG_DATA_POKER_COUNT,	// ��������					uint
//	POKER_LOG_DATA_TYPE,		// ��Ʒ����					uint
//	POKER_LOG_DATA_CREATETIME,	// ����ʱ��(utcʱ�䣩		uint
//	POKER_LOG_DATA_SERVERID,	// ��������					uint
//	POKER_LOG_DATA_LINE,		// ��·						uint
//	POKER_LOG_DATA_COMMENT,		// ˵���ֶ�					varchar128
//};
//
//static const char* GAME_DB_NAME_BLACK_LIST = "black_list";	// ������
//enum BLACK_LIST
//{
//	BLACK_LIST_BEG		= 0,
//	BLACK_LIST_ID       = 0,		// ������ID			uint
//	BLACK_LIST_USER_ID,				// ���ID			uint
//	BLACK_LIST_BAD_FRIEND_ID,		// ���������ID		uint
//	BLACK_LIST_END,
//};
//
//static const char* GAME_DB_NAME_SYNDICATE = "syndicate";	// ���ɱ�
//enum SYNDICATE_DATA
//{
//	SYNDICATE_DATA_ID = 0,				// id					uint
//	SYNDICATE_DATA_SERVER_GROUP,		// ��������				uint
//	SYNDICATE_DATA_NAME,				// ������				varchar32
//	SYNDICATE_DATA_ANNOUNCE,			// ����					varchar255
//	SYNDICATE_DATA_LEADER_ID,			// ����id				uint
//	SYNDICATE_DATA_LEADER_NAME,			// ������				varchar32
//	SYNDICATE_DATA_CREATOR_ID,			// ������id				uint
//	SYNDICATE_DATA_CREATOR_NAME,		// ��������				varchar32
//	SYNDICATE_DATA_CREATE_TIME,			// ����ʱ��				uint
//	SYNDICATE_DATA_LEVEL,				// �ȼ�					uint
//	SYNDICATE_DATA_ACTIVITY,			// ��Ծ					bigint
//	SYNDICATE_DATA_ACTIVITY0_VAULE,		// ��Ծ��ֵ-ͳ��ֵ0		bigint
//	SYNDICATE_DATA_ACTIVITY0_DATE,		// ��Ծ������-ͳ��ֵ0	uint
//	SYNDICATE_DATA_ACTIVITY1_VAULE,		// ��Ծ��ֵ-ͳ��ֵ1		bigint
//	SYNDICATE_DATA_ACTIVITY1_DATE,		// ��Ծ������-ͳ��ֵ1	uint
//	SYNDICATE_DATA_ACTIVITY2_VAULE,		// ��Ծ��ֵ-ͳ��ֵ2		bigint
//	SYNDICATE_DATA_ACTIVITY2_DATE,		// ��Ծ������-ͳ��ֵ2	uint
//	SYNDICATE_DATA_JOIN_LEV_LIMIT,		// ����ȼ�����			uint
//	SYNDICATE_DATA_JOIN_APPLY,			// ����������			uint
//	SYNDICATE_DATA_ICON,				// ����ͼ��				uint
//	SYNDICATE_DATA_JUMP_THE_QUEUE,		// ��ӱ��				uint
//	SYNDICATE_DATA_AWARD_SEND_TIME,		// ս��Ʒ����ʱ��		uint
//	SYNDICATE_DATA_GIFTBOX_LEV,			// ��еȼ�				uint
//	SYNDICATE_DATA_GIFTBOX_EXP,			// ��о���				uint
//	SYNDICATE_DATA_MONTHCARD_ID,		// �����¿�ID			uint
//	SYNDICATE_DATA_MONTHCARD_ENDTIME,	// �����¿�����ʱ��		uint
//};
//
//static const char* GAME_DB_NAME_SYNDICATE_MEMBER = "syn_member";	// ���ɳ�Ա��
//enum SYNDICATE_MEMBER_DATA
//{
//	SYNDICATE_MEMBER_DATA_USER_ID = 0,			// ���id				uint
//	SYNDICATE_MEMBER_DATA_SYNDICATE_ID,			// ����id				uint
//	SYNDICATE_MEMBER_DATA_SERVER_GROUP,			// ��������				uint
//	SYNDICATE_MEMBER_DATA_RANK,					// ����ְλ				uint
//	SYNDICATE_MEMBER_DATA_JOIN_TIME,			// ����ʱ��				uint
//	SYNDICATE_MEMBER_DATA_ACTIVITY,				// ��Ծ					bigint
//	SYNDICATE_MEMBER_DATA_ACTIVITY0_VALUE,		// ��Ծ��ֵ-ͳ��ֵ0		bigint
//	SYNDICATE_MEMBER_DATA_ACTIVITY0_DATE,		// ��Ծ������-ͳ��ֵ0	uint
//	SYNDICATE_MEMBER_DATA_ACTIVITY1_VALUE,		// ��Ծ��ֵ-ͳ��ֵ1		bigint
//	SYNDICATE_MEMBER_DATA_ACTIVITY1_DATE,		// ��Ծ������-ͳ��ֵ1	uint
//	SYNDICATE_MEMBER_DATA_ACTIVITY2_VALUE,		// ��Ծ��ֵ-ͳ��ֵ2		bigint
//	SYNDICATE_MEMBER_DATA_ACTIVITY2_DATE,		// ��Ծ������-ͳ��ֵ2	uint
//	SYNDICATE_MEMBER_DATA_PROF,					// �ﹱ					uint
//	SYNDICATE_MEMBER_DATA_LEV,					// ����ȼ�				uint
//	SYNDICATE_MEMBER_DATA_LOOKFACE,				// ͷ��					uint
//	SYNDICATE_MEMBER_DATA_LOOKFACEFRAME,		// ͷ���				uint
//	SYNDICATE_MEMBER_DATA_NAME,					// ����					varchar32
//	SYNDICATE_MEMBER_DATA_LOGOUT_TIME,			// �ǳ�ʱ��				uint
//	SYNDICATE_MEMBER_DATA_TERRITORY_MONEY,		// �ۻ�����ر�			uint
//	SYNDICATE_MEMBER_DATA_WARROAD_TEAM0_COUNT,	// �Ŷ�ս����ս����0	uint
//	SYNDICATE_MEMBER_DATA_WARROAD_TEAM1_COUNT,	// �Ŷ�ս����ս����1	uint
//	SYNDICATE_MEMBER_DATA_WARROAD_TEAM2_COUNT,	// �Ŷ�ս����ս����2	uint
//	SYNDICATE_MEMBER_DATA_END,
//};
//
//static const char* GAME_DB_NAME_SYNDICATE_MEMBER_APPLY = "syn_member_apply";	// ���ɳ�Ա�����
//enum SYNDICATE_MEMBER_APPLY_DATA
//{
//	SYNDICATE_MEMBER_APPLY_DATA_ID	= 0,		// ��������		bigint
//	SYNDICATE_MEMBER_APPLY_DATA_USERID,			// ���id		uint
//	SYNDICATE_MEMBER_APPLY_DATA_SYNID,			// ����id		uint
//	SYNDICATE_MEMBER_APPLY_DATA_SERVER_GROUP,	// ��������		uint
//	SYNDICATE_MEMBER_APPLY_DATA_LEV,			// ��ɫ�ȼ�		uint
//	SYNDICATE_MEMBER_APPLY_DATA_LOOKFACE,		// ��ɫͷ��		uint
//	SYNDICATE_MEMBER_APPLY_DATA_LOOKFACEFRAME,	// ��ɫͷ���	uint
//	SYNDICATE_MEMBER_APPLY_DATA_NAME,			// ��ɫ����		varchar32
//	SYNDICATE_MEMBER_APPLY_DATA_TIME,			// ����ʱ��		uint
//};
//
//static const char* GAME_DB_NAME_FRIEND = "friend";
//enum FRIEND
//{
//	FRIEND_DATA_USER_ID = 0,					// ���id		uint
//	FRIEND_DATA_FRIEND_ID,						// ����id		uint
//	FRIEND_DATA_FRIENDSHIP_POINT,				// �Ѻö�		uint
//	FRIEND_DATA_GIFT,							// ����״̬		uint
//	FRIEND_DATA_LAST_GOTTIME,					// �ϴ���ȡʱ��	uint
//};
//
//static const char* GAME_DB_NAME_FRIEND_REQUEST = "friend_request";
//enum FRIEND_REQUEST
//{
//	FRIEND_REQUEST_DATA_USER_ID = 0,			// ���id	uint
//	FRIEND_REQUEST_DATA_REQUESTER_ID,			// ������id uint
//	FRIEND_REQUEST_DATA_REQUEST_TIME,			// ����ʱ�� uint
//};
//
//static const char* GAME_DB_NAME_ITEM = "item";	// ��Ʒ��
//enum ITEM_DATA
//{
//	ITEM_DATA_ID	= 0,		// ��Ʒid		bigint
//	ITEM_DATA_TYPE,				// ��Ʒ����		uint
//	ITEM_DATA_PLAYER_ID,		// ������id		uint
//	ITEM_DATA_AMOUNT,			// ����			uint
//	ITEM_DATA_LIFE_TIME,		// ����ʱ��		uint
//	ITEM_DATA_END,
//};
//
//static const char* GAME_DB_NAME_SHOP_GOODS = "shop_goods"; // �̵�����
//enum SHOP_GOODS
//{
//	SHOP_GOODS_BEGIN= 0,
//	SHOP_GOODS_ID	= 0,		// ������ID		uint
//	SHOP_GOODS_ITEM_TYPE,		// ��Ʒ����		uint
//	SHOP_GOODS_OWNER_ID,		// �������ID	uint
//	SHOP_GOODS_SHOP_TYPE,		// �����̵�		uint
//	SHOP_GOODS_ITEM_INDEX,		// ��Ʒλ��		uint
//	SHOP_GOODS_CUR_NUM,			// ��ǰʣ������ uint
//	SHOP_GOODS_MONEY_TYPE,		// ��������		uint
//	SHOP_GOODS_PRICE,			// ��Ʒ����		uint
//	SHOP_GOODS_NUM,				// ��Ʒ����		uint
//	SHOP_GOODS_DISCOUNT,		// ��Ʒ�ۿ�		uint
//	SHOP_GOODS_END,
//};
//
//
//static const char* GAME_DB_NAME_USER_ACHIEVEMENT = "user_achievement";	// ��ҳɾ�
//enum USER_ACHIEVEMENT
//{
//	USER_ACHIEVEMENT_USERID = 0,				// ���id			uint
//	USER_ACHIEVEMENT_CHIEVEMENTID,				// ���ڽ��еĳɾ�id	uint
//	USER_ACHIEVEMENT_PROCESS,					// ����				uint
//	USER_ACHIEVEMENT_GOAL,						// Ŀ��				int
//};
//
//static const char* GAME_DB_NAME_BATTLE_SAVE = "battle_save";	// ս���浵
//enum BATTLE_SAVE_DATA
//{
//	BATTLE_SAVE_DATA_ID = 0,			// ս��id		bigint
//	BATTLE_SAVE_DATA_TYPE,				// ս������		uint
//	BATTLE_SAVE_DATA_ROUND,				// �ִ�			uint
//	BATTLE_SAVE_DATA_MONSTER1_HP,		// ����1Ѫ��	uint
//	BATTLE_SAVE_DATA_MONSTER1_SP,		// ����1��ŭ	uint
//	BATTLE_SAVE_DATA_MONSTER2_HP,		// ����2Ѫ��	uint
//	BATTLE_SAVE_DATA_MONSTER2_SP,		// ����2��ŭ	uint
//	BATTLE_SAVE_DATA_MONSTER3_HP,		// ����3Ѫ��	uint
//	BATTLE_SAVE_DATA_MONSTER3_SP,		// ����3��ŭ	uint
//	BATTLE_SAVE_DATA_MONSTER4_HP,		// ����4Ѫ��	uint
//	BATTLE_SAVE_DATA_MONSTER4_SP,		// ����4��ŭ	uint
//	BATTLE_SAVE_DATA_MONSTER5_HP,		// ����5Ѫ��	uint
//	BATTLE_SAVE_DATA_MONSTER5_SP,		// ����5��ŭ	uint
//};
//
//static const char* GAME_DB_NAME_CHALLENGE_BOSS = "challenge_boss";	// ��սboss�����
//enum CHALLENGE_BOSS
//{
//	CHALLENGE_BOSS_ID = 0,				// ���						bigint
//	CHALLENGE_BOSS_USER_ID,				// ���ID					uint
//	CHALLENGE_BOSS_BOSS_TYPE,			// boss����					uint
//	CHALLENGE_BOSS_DEGREE,				// �Ѷ�						uint
//	CHALLENGE_BOSS_EVALUATE,			// ��ս���(0:ʧ��; 1,2,3��)uint
//};
//
//static const char* GAME_DB_NAME_TOPLIST_USER_ATTR = "toplist_user_attr";	//	���������������
//enum TOPLIST_USER_ATTR
//{
//	TOPLIST_USER_ATTR_USER_ID = 0,		// ���id			uint
//	TOPLIST_USER_ATTR_TYPE,				// ���а�����ö��ֵ	uint
//	TOPLIST_USER_ATTR_DATA,				// ����ʹ�õ�����	uint
//	TOPLIST_USER_ATTR_RANK,				// ��������			uint	
//	TOPLIST_USER_ATTR_LAST_RANK,		// ��������			uint
//	TOPLIST_USER_ATTR_SERVER_GROUP,		// ��������id		uint
//};
//
//static const char* GAME_DB_NAME_TOPLIST_SYNDICATE = "toplist_syndicate";	// ���а񹫻�������
//enum TOPLIST_SYNDICATE
//{
//	TOPLIST_SYNDICATE_ID = 0,			// ����id			uint
//	TOPLIST_SYNDICATE_TYPE,				// ���а�����ö��ֵ	uint
//	TOPLIST_SYNDICATE_DATA,				// ����ʹ�õ�����	uint
//	TOPLIST_SYNDICATE_SERVER_GROUP,		// ��������id		uint
//};
//
//static const char* GAME_DB_NAME_DELAYACTION = "delayaction";	// �ӳ�ִ��action��¼��
//enum DELAYACTION_DATA
//{
//	DELAYACTION_DATA_ID = 0,			// ���						bigint
//	DELAYACTION_DATA_ACTION_ID,			// ִ��action				uint
//	DELAYACTION_DATA_USER_ID,			// ���ID					uint
//	DELAYACTION_DATA_EXECUTECOUNT,		// ִ�д���					uint
//	DELAYACTION_DATA_EXECUTETIME,		// ִ��ʱ��					uint
//	DELAYACTION_DATA_INVALIDTIME,		// ʧЧʱ��					uint
//	DELAYACTION_DATA_SERVER_GROUP,		// ��������					uint
//	DELAYACTION_DATA_SERVER_LINE,		// ��������·				uint
//	DELAYACTION_DATA_PARAM1,			// ����1					uint
//	DELAYACTION_DATA_PARAM2,			// ����2					uint
//	DELAYACTION_DATA_PARAM3,			// ����3					uint
//	DELAYACTION_DATA_PARAM4,			// ����4					uint
//	DELAYACTION_DATA_PARAM5,			// ����5					uint
//};
//
//
//static const char* GAME_DB_NAME_GOOSE_TOWER = "goose_tower";	// ������������ݱ�
//enum GOOSE_TOWER_DATA
//{
//	GOOSE_TOWER_DATA_ID = 0,					// id								bigint
//	GOOSE_TOWER_DATA_USER_ID,					// ���id							uint
//	GOOSE_TOWER_DATA_FLOOR,						// ����								uint
//	GOOSE_TOWER_DATA_DEF_USER_ID,				// ����С�����id					uint
//	GOOSE_TOWER_DATA_DEF_USER_NAME,				// ����С�������					varchar32
//	GOOSE_TOWER_DATA_DEF_USER_LEV,				// ����С����ҵȼ�					uint
//	GOOSE_TOWER_DATA_DEF_USER_LOOKFACE,			// ����С�����ͷ��					uint
//	GOOSE_TOWER_DATA_DEF_USER_LOOKFACE_FRAME,	// ����С�����ͷ���				uint
//	GOOSE_TOWER_DATA_POKER_ID1,					// ����ID1							bigint
//	GOOSE_TOWER_DATA_POKER_ID2,					// ����ID2							bigint
//	GOOSE_TOWER_DATA_POKER_ID3,					// ����ID3							bigint
//	GOOSE_TOWER_DATA_POKER_ID4,					// ����ID4							bigint
//	GOOSE_TOWER_DATA_POKER_ID5,					// ����ID5							bigint
//	GOOSE_TOWER_DATA_GAIN_AWARD,				// ������ȡ���(0:û����ȡ, 1:��ȡ)	uint
//	GOOSE_TOWER_DATA_BATTLE_SAVE_ID,			// ս������ID						bigint
//};
//
//static const char* GAME_DB_NAME_GOOSE_FIGHT_POKER = "goose_fight_poker";	// ��������ʷ�����Ƽ�¼��
//enum GOOSE_FIGHT_POKER
//{
//	GOOSE_FIGHT_POKER_ID = 0,			// id			uint
//	GOOSE_FIGHT_POKER_USER_ID,			// ���id		uint
//	GOOSE_FIGHT_POKER_POKER_ID,			// ��������ID	bigint
//	GOOSE_FIGHT_POKER_HP,				// ���Ѫ��		uint
//	GOOSE_FIGHT_POKER_LEFT_HP,			// ʣ��Ѫ��		uint
//	GOOSE_FIGHT_POKER_SP,				// ����ŭ		uint
//	GOOSE_FIGHT_POKER_LEFT_SP,			// ʣ���ŭ		uint
//};
//
//// ��poker����ͬһ��ö��
//static const char* GAME_DB_NAME_GOOSE_DEFENSE_POKER = "goose_defense_poker";		// ����������С�ӿ��Ʊ�
//
//
//static const char* GAME_DB_NAME_PUZZLE_BUFF = "puzzle_buff";	// �Թ�BUFF��
//enum PUZZLE_BUFF_DATA
//{
//	PUZZLE_BUFF_DATA_ID = 0,			// ���						uint
//	PUZZLE_BUFF_DATA_USER_ID,			// ���ID					uint
//	PUZZLE_BUFF_DATA_BUFF_TYPE,			// BUFF����					uint
//	PUZZLE_BUFF_DATA_INS_TYPE,			// ��������					uint
//	PUZZLE_BUFF_DATA_INS_DIFFICULE,		// �����Ѷ�					uint
//	PUZZLE_BUFF_DATA_INS_FLOOR,			// �������					uint
//	PUZZLE_BUFF_DATA_FIGHT_NO,			// ս�����к�				uint
//	PUZZLE_BUFF_DATA_DATE,				// ��������(��)				uint
//};
//static const char* GAME_DB_NAME_ARENA = "arena";			// ���Ӿ�����������
//enum ARENA_DATA
//{
//	ARENA_DATA_USERID,					// ���id					uint
//	ARENA_DATA_RANK = 0,				// ����						uint
//	ARENA_DATA_TOTALWINCOUNT,			// �ܼ�ʤ����				uint
//	ARENA_SERVER_GROUP,					// ��������					uint
//};
//
//static const char* GAME_DB_NAME_ARENA_LOG = "arena_log";			// ������ս����־
//enum ARENA_LOG_DATA
//{
//	ARENA_LOG_DATA_ARENA_TYPE = 0,		// ���������1���ˣ�2���ˣ�	uint
//	ARENA_LOG_DATA_USERID,				// ���id						uint
//	ARENA_LOG_DATA_RESULT,				// ս�����						uint
//	ARENA_LOG_DATA_RANKCHANGE,			// �����仯						uint
//	ARENA_LOG_DATA_TARGETID,			// Ŀ��id						uint
//	ARENA_LOG_DATA_TIME,				// ս��ʱ��						uint
//	ARENA_LOG_DATA_VIDEO,				// ¼��							varchar
//	ARENA_LOG_DATA_SERVER_GROUP,		// ��������						uint
//};
//
//static const char* GAME_DB_NAME_ARENA_MULTI = "arena_multi";		//  ��Ӿ���������
//enum MULTI_ARENA_DATA
//{
//	MULTI_ARENA_DATA_USERID = 0,		// ���id						uint
//	MULTI_ARENA_DATA_RANK,				// ����							uint
//	MULTI_ARENA_DATA_TOTALWINCOUNT,		// �ܼ�ʤ����					uint
//	MULTI_ARENA_DATA_ARENA_MONEY,		// �ۻ�δ��ȡ�ľ�������			uint	
//	MULTI_ARENA_DATA_SERVER_GROUP,		// ��������						uint
//};
//
//static const char* GAME_DB_NAME_ARENA_POKER_TEAM = "arena_poker_team";	// ��������ҿ��ƶ�������
//enum ARENA_POKER_TEAM_DATA
//{
//	ARENA_POKER_TEAM_DATA_ID = 0,		// ������id						uint
//	ARENA_POKER_TEAM_DATA_USERID ,		// ���id						uint
//	ARENA_POKER_TEAM_DATA_TEAMTYPE,		// ��������						uint
//	ARENA_POKER_TEAM_DATA_POKERID1,		// 1�ſ���id					uint
//	ARENA_POKER_TEAM_DATA_POKERID2,		// 2�ſ���id					uint
//	ARENA_POKER_TEAM_DATA_POKERID3,		// 3�ſ���id					uint
//	ARENA_POKER_TEAM_DATA_POKERID4,		// 4�ſ���id					uint
//	ARENA_POKER_TEAM_DATA_POKERID5,		// 5�ſ���id					uint
//	ARENA_POKER_TEAM_DATA_TOTAL_FC,		// ������ս����					uint
//	ARENA_POKER_TEAM_DATA_END,
//};
//
//static const char* GAME_DB_NAME_ARENA_AI = "arena_ai";	// �����������˱�
//enum ARENA_AI_DATA
//{
//	ARENA_AI_DATA_ID = 0,				// id		uint
//	ARENA_AI_DATA_NAME,					// ����		varchar
//	ARENA_AI_DATA_SERVER_GROUP,			// ��������	uint
//};
//
//static const char* GAME_DB_NAME_SYN_LOG	= "syn_log";	// ������־��
//enum SYN_LOG_DATA
//{
//	SYN_LOG_DATA_ID = 0,			// ID				bigint
//	SYN_LOG_DATA_SYN_ID,			// ����ID   		uint
//	SYN_LOG_DATA_TYPE,				// ��־���� 		uint
//	SYN_LOG_DATA_CREATE_USER_ID,	// ��־������ID		uint
//	SYN_LOG_DATA_CREATE_TIME,		// ��־����ʱ��		uint
//	SYN_LOG_DATA_CONTENT,			// ��־����			varchar256
//};
//
//static const char* GAME_DB_NAME_MINE	= "mine";	// �󶴱�
//enum MINE_DATA
//{
//	MINE_DATA_ID	= 0,				// ��ID						uint
//	MINE_DATA_OWNER_ID,					// ����ID						uint
//	MINE_DATA_TYPE,						// ������						uint
//	MINE_DATA_SCALE,					// ���ģ						uint
//	MINE_DATA_CREATE_TIME,				// ����ʱ��						uint
//	MINE_DATA_IS_END,					// �Ƿ����						uint
//	MINE_DATA_BE_ATK_COUNT,				// ����������					uint
//	MINE_DATA_SERVER_GROUP,				// ��������						uint
//};
//
//static const char* GAME_DB_NAME_MINE_MEMBER = "mine_member"; // �󶴳�Ա��
//enum MINE_MEMBER_DATA
//{
//	MINE_MEMBER_DATA_ID		= 0,		// ������ID						bigint
//	MINE_MEMBER_DATA_USER_ID,			// ���ID						uint
//	MINE_MEMBER_DATA_MINE_ID,			// ��ID						uint
//	MINE_MEMBER_DATA_LEV,				// �ȼ�							uint
//	MINE_MEMBER_DATA_LOOK_FACE,			// ͷ��							uint
//	MINE_MEMBER_DATA_LOOK_FACE_FRAME,	// ͷ���						uint
//	MINE_MEMBER_DATA_NAME,				// ��ɫ��						varchar32
//	MINE_MEMBER_DATA_POKER1,			// ��ս��1						bigint
//	MINE_MEMBER_DATA_POKER2,			// ��ս��2						bigint
//	MINE_MEMBER_DATA_POKER3,			// ��ս��3						bigint
//	MINE_MEMBER_DATA_POKER4,			// ��ս��4						bigint
//	MINE_MEMBER_DATA_POKER5,			// ��ս��5						bigint
//	MINE_MEMBER_DATA_JOIN_TIME,			// ����ʱ��						uint
//	MINE_MEMBER_DATA_SPEED,				// ��ǰ�����ٶ�(/Сʱ)			uint
//	MINE_MEMBER_DATA_BEGIN_TIME,		// ��ǰ���ƿ�ʼ�ɼ�ʱ��			uint
//	MINE_MEMBER_DATA_RESOURCE_OLD,		// ������ǰ�ۼ���Դ				uint
//	MINE_MEMBER_DATA_RESOURCE_TOTAL,	// ��Դ�ۼ�						uint
//	MINE_MEMBER_DATA_RESOURCE_LOSE,		// ��Դ��ʧ						uint
//	MINE_MEMBER_DATA_VAS_TOTAL,			// ��ʯ�ۼ�						uint
//	MINE_MEMBER_DATA_IS_POKER_RESET,	// �����Ƿ�����					uint
//	MINE_MEMBER_DATA_SERVER_GROUP,		// ��������						uint
//};
//static const char* GAME_DB_NAME_MERCENARY_POKER = "mercenary_poker";	// Ӷ�����Ʊ� *����һ���ֶ���������poker��ö����ͬ
//enum MERCENARY_POKER_DATA
//{
//	MERCENARY_POKER_DATA_SERVER_GROUP = POKER_DATA_SKILL_JOINT_LEV + 1,	// ��������					uint
//};
//
//static const char* GAME_DB_NAME_MERCENARY_CAMP = "mercenary_camp";		// Ӷ��Ӫ��
//enum MERCENARY_CAMP_DATA
//{
//	MERCENARY_CAMP_DATA_MERCENARY_ID,	// Ӷ��ID					bigint
//	MERCENARY_CAMP_DATA_OWNER_ID,		// Ӷ������ID				uint
//	MERCENARY_CAMP_DATA_EMPLOY_COUNT,	// ����Ӷ����				uint
//	MERCENARY_CAMP_DATA_ENTER_TIME,		// ��ǲʱ��					uint
//	MERCENARY_CAMP_DATA_SYNDICATE_ID,	// ����ID					uint
//	MERCENARY_CAMP_DATA_SERVER_GROUP,	// ��������					uint
//	MERCENARY_CAMP_DATA_MERCENARY_SCORE,// Ӷ��ս����				uint
//};
//
//static const char* GAME_DB_NAME_MERCENARY_FIGHT = "mercenary_fight";	// Ӷ��ս����¼��
//enum MERCENARY_FIGHT_DATA
//{
//	MERCENARY_FIGHT_DATA_ID,						// ID					bigint
//	MERCENARY_FIGHT_DATA_USER_ID,					// ���ID				uint
//	MERCENARY_FIGHT_DATA_MERCENARY_ID,				// Ӷ��ID				bigint
//	MERCENARY_FIGHT_DATA_MERCENARY_TYPE,			// Ӷ������				uint
//	MERCENARY_FIGHT_DATA_MERCENARY_OWNER_ID,		// Ӷ������id			uint
//	MERCENARY_FIGHT_DATA_MERCENARY_LEV,				// Ӷ���ȼ�				uint
//	MERCENARY_FIGHT_DATA_MERCENARY_EXP,				// Ӷ������				bigint
//	MERCENARY_FIGHT_DATA_MERCENARY_COLOR,			// Ӷ����ɫ				uint
//	MERCENARY_FIGHT_DATA_MERCENARY_STAR,			// Ӷ���Ǽ�				uint
//	MERCENARY_FIGHT_DATA_MERCENARY_EQUIP1_TYPE,		// Ӷ����������			uint
//	MERCENARY_FIGHT_DATA_MERCENARY_EQUIP1_STAR,		// Ӷ�������Ǽ�			uint
//	MERCENARY_FIGHT_DATA_MERCENARY_EQUIP1_EXP,		// Ӷ����������			uint
//	MERCENARY_FIGHT_DATA_MERCENARY_EQUIP2_TYPE,		// Ӷ��ͷ������			uint
//	MERCENARY_FIGHT_DATA_MERCENARY_EQUIP2_STAR,		// Ӷ��ͷ���Ǽ�			uint
//	MERCENARY_FIGHT_DATA_MERCENARY_EQUIP2_EXP,		// Ӷ��ͷ������			uint
//	MERCENARY_FIGHT_DATA_MERCENARY_EQUIP3_TYPE,		// Ӷ����������			uint
//	MERCENARY_FIGHT_DATA_MERCENARY_EQUIP3_STAR,		// Ӷ�������Ǽ�			uint
//	MERCENARY_FIGHT_DATA_MERCENARY_EQUIP3_EXP,		// Ӷ����������			uint
//	MERCENARY_FIGHT_DATA_MERCENARY_EQUIP4_TYPE,		// Ӷ����������			uint
//	MERCENARY_FIGHT_DATA_MERCENARY_EQUIP4_STAR,		// Ӷ�������Ǽ�			uint
//	MERCENARY_FIGHT_DATA_MERCENARY_EQUIP4_EXP,		// Ӷ����������			uint
//	MERCENARY_FIGHT_DATA_MERCENARY_EQUIP5_TYPE,		// Ӷ���·�����			uint
//	MERCENARY_FIGHT_DATA_MERCENARY_EQUIP5_STAR,		// Ӷ���·��Ǽ�			uint
//	MERCENARY_FIGHT_DATA_MERCENARY_EQUIP5_EXP,		// Ӷ���·�����			uint
//	MERCENARY_FIGHT_DATA_MERCENARY_EQUIP6_TYPE,		// Ӷ��Ь������			uint
//	MERCENARY_FIGHT_DATA_MERCENARY_EQUIP6_STAR,		// Ӷ��Ь���Ǽ�			uint
//	MERCENARY_FIGHT_DATA_MERCENARY_EQUIP6_EXP,		// Ӷ��Ь�Ӿ���			uint
//	MERCENARY_FIGHT_DATA_MERCENARY_SKILL_SP_LEV,	// Ӷ���ؼ��ȼ�			uint
//	MERCENARY_FIGHT_DATA_MERCENARY_SKILL_AUTO1_LEV,	// Ӷ���Զ�����1�ȼ�	uint
//	MERCENARY_FIGHT_DATA_MERCENARY_SKILL_AUTO2_LEV,	// Ӷ���Զ�����2�ȼ�	uint
//	MERCENARY_FIGHT_DATA_MERCENARY_SKILL_AUTO3_LEV,	// Ӷ���Զ�����3�ȼ�	uint
//	MERCENARY_FIGHT_DATA_MERCENARY_SKILL_JOINT_LEV,	// Ӷ����Я���ܵȼ�		uint
//	MERCENARY_FIGHT_DATA_MERCENARY_SCORE,			// Ӷ��ս��				uint
//	MERCENARY_FIGHT_DATA_EMPLOY_TYPE,				// ��Ӷ����				uint
//	MERCENARY_FIGHT_DATA_EMPLOY_TIME,				// ��Ӷʱ��				uint
//	MERCENARY_FIGHT_DATA_EMPLOY_STATE,				// ��Ӷ״̬(1����ʹ�ã�2���棬3��ȴ)	uint
//};
//
//static const char* GAME_DB_NAME_MINE_LOG = "mine_log";					// ����־��
//enum MINE_LOG_DATA
//{
//	MINE_LOG_DATA_ID = 0,				// ������ID					uint
//	MINE_LOG_DATA_MINE_ID,				// ��ID					uint
//	MINE_LOG_DATA_MINE_TYPE,			// ������					uint
//	MINE_LOG_DATA_MINE_SCALE,			// �󶴹�ģ					uint
//	MINE_LOG_DATA_DEF_ID,				// ������ID					uint
//	MINE_LOG_DATA_DEF_NAME,				// ����������				varchar32
//	MINE_LOG_DATA_DEF_LEV,				// �����ߵȼ�				uint
//	MINE_LOG_DATA_DEF_LOOKFACE,			// ������ͷ��				uint
//	MINE_LOG_DATA_DEF_LOOKFACE_FRAME,	// ������ͷ���				uint
//	MINE_LOG_DATA_ATK_ID,				// ������ID					uint
//	MINE_LOG_DATA_ATK_NAME,				// ����������				varchar32
//	MINE_LOG_DATA_ATK_LEV,				// �����ߵȼ�				uint
//	MINE_LOG_DATA_ATK_LOOKFACE,			// ������ͷ��				uint
//	MINE_LOG_DATA_ATK_LOOKFACE_FRAME,	// ������ͷ���				uint
//	MINE_LOG_DATA_BEGIN_TIME,			// �ӶῪʼʱ��				uint
//	MINE_LOG_DATA_END_TIME,				// �Ӷ����ʱ��				uint
//	MINE_LOG_DATA_VAS_LOST,				// ��ȡ����ʯ				uint
//	MINE_LOG_DATA_RES_LOST,				// ��ȡ����Դ				uint
//	MINE_LOG_DATA_POWER_AWARD,			// ר����������				uint
//	MINE_LOG_DATA_DEF_RESULT,			// ���ؽ��(0:ʧ�ܣ�1:ʤ��)	uint
//	MINE_LOG_DATA_SERVER_GROUP,			// ��������					uint
//	MINE_LOG_DATA_BE_ATK_COUNT,			// ����������				uint
//};
//
//static const char* GAME_DB_NAME_MINE_LOG_BATTLE = "mine_log_battle";	// ����־ս����
//enum MINE_LOG_BATTLE_DATA
//{
//	MINE_LOG_BATTLE_DATA_ID = 0,		// ս��ID				bigint				
//	MINE_LOG_BATTLE_LOG_ID,				// ��־ID				bigint	
//	MINE_LOG_BATTLE_DEF_POKER1,			// ���ط�����1			bigint				
//	MINE_LOG_BATTLE_DEF_POKER2,			// 						bigint				
//	MINE_LOG_BATTLE_DEF_POKER3,			// 						bigint				
//	MINE_LOG_BATTLE_DEF_POKER4,			// 						bigint				
//	MINE_LOG_BATTLE_DEF_POKER5,			// 						bigint
//
//	MINE_LOG_BATTLE_DEF_RESULT,			// ���ؽ��(0:��, 1:Ӯ)	uint
//
//	MINE_LOG_BATTLE_ATK_POKER1,			// ����������1			bigint				
//	MINE_LOG_BATTLE_ATK_POKER2,			// 						bigint				
//	MINE_LOG_BATTLE_ATK_POKER3,			// 						bigint				
//	MINE_LOG_BATTLE_ATK_POKER4,			// 						bigint				
//	MINE_LOG_BATTLE_ATK_POKER5,			// 						bigint
//	MINE_LOG_BATTLE_VIDEO_ID,			// ¼���ַ				varchar64				
//};
//
//static const char* GAME_DB_NAME_MINE_LOG_POKER = "mine_log_poker";	// ����־��ս���Ʊ�
//enum MINE_LOG_POKER_DATA
//{
//	MINE_LOG_POKER_DATA_ID = 0,			// ID					bigint
//	MINE_LOG_POKER_DATA_BATTLE_ID,		// ս��ID				bigint
//	MINE_LOG_POKER_DATA_TYPE,			// ����					uint
//	MINE_LOG_POKER_DATA_LEV,			// �ȼ�					uint
//	MINE_LOG_POKER_DATA_STAR,			// �Ǽ�					uint
//	MINE_LOG_POKER_DATA_COLOR,			// ��ɫ					uint
//	MINE_LOG_POKER_DATA_HP,				// ���Ѫ��				uint
//	MINE_LOG_POKER_DATA_LEFT_HP,		// ʣ��Ѫ��				uint
//	MINE_LOG_POKER_DATA_SP,				// ����ŭ				uint
//	MINE_LOG_POKER_DATA_LEFT_SP,		// ʣ���ŭ				uint
//};
//
//
//static const char* GAME_DB_NAME_TERRITORY = "territory";				// ��ر�
//enum TERRITORY_DATA
//{
//	TERRITORY_DATA_INDEX = 0,			// primary				uint
//	TERRITORY_DATA_ID,					// ���id				uint
//	TERRITORY_DATA_OCCUPIER,			// ռ�칫��id			uint
//	TERRITORY_DATA_OCCUPY_TIME,			// ռ��ʱ��YYMMDD		uint
//	TERRITORY_DATA_OCCUPY_COST,			// ռ���ʱ				uint
//	TERRITORY_DATA_FIRST_OCCUPIER,		// ��ռ����id			uint
//	TERRITORY_DATA_FIRST_TIME,			// ��սʱ��YYMMDD		uint
//	TERRITORY_DATA_FIRST_COST,			// ��ս��ʱ				uint
//	TERRITORY_DATA_FAST_OCCUPIER,		// ��칫��id			uint
//	TERRITORY_DATA_FAST_TIME,			// ��칫��ʱ��YYMMDD	uint
//	TERRITORY_DATA_FAST_COST,			// ���ռ�칫���ʱ		uint
//	TERRITORY_DATA_SERVER_GROUP,		// ��������				uint
//};
//
//static const char* GAME_DB_NAME_TERRITORY_MEMBER_TROOPS = "territory_member_troops";		// ��ع�����Ҳ��ӱ�
//enum TERRITORY_MEMBER_TROOPS_DATA
//{
//	TERRITORY_MEMBER_TROOPS_DATA_ID,				// ����id				uint
//	TERRITORY_MEMBER_TROOPS_DATA_TERRITORY_ID,		// ���id				uint
//	TERRITORY_MEMBER_TROOPS_DATA_CAMP,				// ��Ӫ					uint
//	TERRITORY_MEMBER_TROOPS_DATA_SYNDICATE_ID,		// ��������id			uint
//	TERRITORY_MEMBER_TROOPS_DATA_USER_ID,			// �������id			uint
//	TERRITORY_MEMBER_TROOPS_DATA_POKER_COUNT,		// ��ǰ����ʵ�ʿ�����	uint
//	TERRITORY_MEMBER_TROOPS_DATA_FIGHTINGCAPACITY,	// ��ǰ������ս����		uint
//	TERRITORY_MEMBER_TROOPS_DATA_POKER1_ID,			// ���鿨��1id			uint
//	TERRITORY_MEMBER_TROOPS_DATA_POKER2_ID,			// ���鿨��2id			uint
//	TERRITORY_MEMBER_TROOPS_DATA_POKER3_ID,			// ���鿨��3id			uint
//	TERRITORY_MEMBER_TROOPS_DATA_POKER4_ID,			// ���鿨��4id			uint
//	TERRITORY_MEMBER_TROOPS_DATA_POKER5_ID,			// ���鿨��5id			uint
//	TERRITORY_MEMBER_TROOPS_DATA_SERVER_GROUP,		// ��������				uint
//};
//
//static const char* GAME_DB_NAME_TERRITORY_FIGHT_STATISTICS = "territory_fight_statistics";		// ���սս��ͳ�Ʊ�
//enum TERRITORY_FIGHT_STATISTICS
//{
//	TERRITORY_FIGHT_STATISTICS_DATA_INDEX = 0,			// INDEX				uint
//	TERRITORY_FIGHT_STATISTICS_DATA_ID,					// ���id				uint
//	TERRITORY_FIGHT_STATISTICS_DATA_ATK_SYN_ID,			// ��������id			uint
//	TERRITORY_FIGHT_STATISTICS_DATA_DEF_SYN_ID,			// ���ع���id			uint
//	TERRITORY_FIGHT_STATISTICS_DATA_TOTAL_FIGHTED_TIMES,// ��ս��ʱ��			uint
//	TERRITORY_FIGHT_STATISTICS_DATA_SERVER_GROUP,		// ��������				uint
//};
//
//static const char* GAME_DB_NAME_TERRITORY_FIGHT_LOG		= "territory_fight_log";				// ���սս����־��
//enum TERRITORY_FIGHT_LOG
//{
//	TERRITORY_FIGHT_LOG_DATA_INDEX = 0,					// INDEX							uint
//	TERRITORY_FIGHT_LOG_DATA_TERRITORY_ID,				// ���id							uint
//	TERRITORY_FIGHT_LOG_DATA_ATK_TROOPS_ID,				// ��������id						I64
//	TERRITORY_FIGHT_LOG_DATA_ATK_USER_ID,				// �����������id					uint
//	TERRITORY_FIGHT_LOG_DATA_ATK_SYN_ID,				// �������ӹ���id					uint
//	TERRITORY_FIGHT_LOG_DATA_DEF_TROOPS_ID,				// ���ز���id						I64
//	TERRITORY_FIGHT_LOG_DATA_DEF_USER_ID,				// ���ز������id					uint
//	TERRITORY_FIGHT_LOG_DATA_DEF_SYN_ID,				// ���ز��ӹ���id					uint
//	TERRITORY_FIGHT_LOG_DATA_TIME,						// ������ս��ʼ��ʱ�䣨��λ�룩	uint
//	TERRITORY_FIGHT_LOG_DATA_RESULT,					// ʤ����0����ʤ����1����ʤ����		uint
//	TERRITORY_FIGHT_LOG_DATA_DATE,						// ս������							uint
//	TERRITORY_FIGHT_LOG_DATA_VIDEO,						// ¼��								varchar128
//	TERRITORY_FIGHT_LOG_DATA_SERVER_GROUP,				// ��������							uint
//};
//
//static const char* GAME_DB_NAME_TERRITORY_FIGHT_TROOPS = "territory_fight_troops";				// ���ս�Ѳ�ս����״̬��
//enum TERRITORY_FIGHT_TROOPS
//{
//	TERRITORY_FIGHT_TROOPS_DATA_INDEX = 0,				// INDEX							uint
//	TERRITORY_FIGHT_TROOPS_DATA_TERRITORY_ID,			// ���id							uint
//	TERRITORY_FIGHT_TROOPS_DATA_TROOPS_ID,				// ����id							I64
//	TERRITORY_FIGHT_TROOPS_DATA_SYN_ID,					// ������������id					uint
//	TERRITORY_FIGHT_TROOPS_DATA_OPPONENT_SYN_ID,		// ������������id					uint
//	TERRITORY_FIGHT_TROOPS_DATA_STATUS,					// ״̬��0������1��ʤ��				uint
//	TERRITORY_FIGHT_TROOPS_DATA_POKER1_HP,				// ����1��ǰѪ��					uint
//	TERRITORY_FIGHT_TROOPS_DATA_POKER1_SP,				// ����1��ǰ��ŭ					uint
//	TERRITORY_FIGHT_TROOPS_DATA_POKER2_HP,				// ����2��ǰѪ��					uint
//	TERRITORY_FIGHT_TROOPS_DATA_POKER2_SP,				// ����2��ǰ��ŭ					uint
//	TERRITORY_FIGHT_TROOPS_DATA_POKER3_HP,				// ����3��ǰѪ��					uint
//	TERRITORY_FIGHT_TROOPS_DATA_POKER3_SP,				// ����3��ǰ��ŭ					uint
//	TERRITORY_FIGHT_TROOPS_DATA_POKER4_HP,				// ����4��ǰѪ��					uint
//	TERRITORY_FIGHT_TROOPS_DATA_POKER4_SP,				// ����4��ǰ��ŭ					uint
//	TERRITORY_FIGHT_TROOPS_DATA_POKER5_HP,				// ����5��ǰѪ��					uint
//	TERRITORY_FIGHT_TROOPS_DATA_POKER5_SP,				// ����5��ǰ��ŭ					uint
//};
//
//static const char* GAME_DB_NAME_USER_WAR_ROAD	= "user_war_road";			// ���ս�ۼ�¼��
//enum USER_WAR_ROAD_DATA
//{
//	USER_WAR_ROAD_DATA_ID,					// id						bigint
//	USER_WAR_ROAD_DATA_USER_ID,				// ���ID					uint
//	USER_WAR_ROAD_DATA_MODE,				// ģʽ						int
//	USER_WAR_ROAD_DATA_CHAPTER,				// �½�						int
//	USER_WAR_ROAD_DATA_PASS,				// �ؿ�						int
//	USER_WAR_ROAD_DATA_STAR,				// �Ǽ�						uint
//	USER_WAR_ROAD_DATA_DAY_FIGHT_COUNT,		// ÿ��ս������				uint
//	USER_WAR_ROAD_DATA_DAY_RESET_COUNT,		// ÿ�����ô���				uint
//	USER_WAR_ROAD_DATA_RECORD_TIME,			// ��¼����					uint
//};
//
//static const char* GAME_DB_NAME_WAR_ROAD_FIGHT	= "war_road_fight";			// ս��ս����¼��
//enum WAR_ROAD_FIGHT_DATA
//{
//	WAR_ROAD_FIGHT_DATA_ID = 0,				// ������ID					uint
//	WAR_ROAD_FIGHT_DATA_WAR_KEY,			// ս��key��ģʽ*1000000+�½�*1000+�ؿ���	bigint
//	WAR_ROAD_FIGHT_DATA_RECORD_TIME,		// ��¼ʱ��					uint
//	WAR_ROAD_FIGHT_DATA_REPLYADDRESS,		// ¼���ַ					varchar
//	WAR_ROAD_FIGHT_DATA_SERVER_GROUP,		// ��������					uint
//};
//
//static const char* GAME_DB_NAME_WAR_ROAD_TEAM_LOG	= "war_road_team_log";	// �Ŷ�ս�ۼ�¼��
//enum WAR_ROAD_TEAM_LOG_DATA
//{
//	WAR_ROAD_TEAM_LOG_DATA_ID = 0,			// ������id					bigint
//	WAR_ROAD_TEAM_LOG_DATA_SYNDICATE_ID,	// ����ID					uint
//	WAR_ROAD_TEAM_LOG_DATA_CHAPTER,			// �½�						uint
//	WAR_ROAD_TEAM_LOG_DATA_SERVER_GROUP,	// ��������					uint
//	WAR_ROAD_TEAM_LOG_DATA_OPEN_TIME,		// ����ʱ��					uint
//	WAR_ROAD_TEAM_LOG_DATA_COMPLETE,		// �Ƿ���ɹ�				uint
//	WAR_ROAD_TEAM_LOG_DATA_COMPLETE_TIME,	// ���ʱ��					uint
//	WAR_ROAD_TEAM_LOG_DATA_CHAPTER_DPS,		// �½��˺���				bigint
//	WAR_ROAD_TEAM_LOG_DATA_CHAPTER_PROGRESS,// �½ڽ��ȣ��½��˺���/�½ڹ�����Ѫ���� uint
//	WAR_ROAD_TEAM_LOG_DATA_PASS_FIGHT,		// ս���ؿ�					uint
//	WAR_ROAD_TEAM_LOG_DATA_ROUND_FIGHT,		// ս������					uint
//	WAR_ROAD_TEAM_LOG_DATA_MONSTER1_LEFTHP,	// ����1ʣ��Ѫ������(%)		uint
//	WAR_ROAD_TEAM_LOG_DATA_MONSTER2_LEFTHP,	// ����2ʣ��Ѫ������(%)		uint
//	WAR_ROAD_TEAM_LOG_DATA_MONSTER3_LEFTHP,	// ����3ʣ��Ѫ������(%)		uint
//	WAR_ROAD_TEAM_LOG_DATA_MONSTER4_LEFTHP,	// ����4ʣ��Ѫ������(%)		uint
//	WAR_ROAD_TEAM_LOG_DATA_MONSTER5_LEFTHP,	// ����5ʣ��Ѫ������(%)		uint
//	WAR_ROAD_TEAM_LOG_DATA_PASS_DPS,		// �ؿ��˺���				bigint
//	WAR_ROAD_TEAM_LOG_DATA_PASS_PROGRESS,	// �ؿ����ȣ��ؿ��˺���/�ؿ�������Ѫ���� uint
//	WAR_ROAD_TEAM_LOG_DATA_USER_ID,			// ��ս���ID				uint
//	WAR_ROAD_TEAM_LOG_DATA_FIGHT_STATUS,	// ��ս״̬��1׼����2ս����	uint
//	WAR_ROAD_TEAM_LOG_DATA_FIGHT_TIME,		// ��սʱ�䣨׼����ս����	uint
//};
//
//static const char* GAME_DB_NAME_WAR_ROAD_TEAM_AWARD	= "war_road_team_award";// �Ŷ�ս��ս��Ʒ�����¼��
//enum WAR_ROAD_TEAM_AWARD_DATA
//{
//	WAR_ROAD_TEAM_AWARD_DATA_ID = 0,		// ������id					bigint
//	WAR_ROAD_TEAM_AWARD_DATA_SYNDICATE_ID,	// ����ID					uint
//	WAR_ROAD_TEAM_AWARD_DATA_CHAPTER,		// �½�						uint
//	WAR_ROAD_TEAM_AWARD_DATA_AWARD_TYPE,	// ս��Ʒ����				uint
//	WAR_ROAD_TEAM_AWARD_DATA_USER_ID,		// �������ID				uint
//	WAR_ROAD_TEAM_AWARD_DATA_APPLY_TIME,	// ����ʱ��					uint
//	WAR_ROAD_TEAM_AWARD_DATA_CUT_TIME,		// ���ʱ��					uint
//	WAR_ROAD_TEAM_AWARD_DATA_SERVER_GROUP,	// ��������					uint
//};
//
//static const char* GAME_DB_NAME_WAR_ROAD_TEAM_AWARD_HISTORY	= "war_road_team_award_history";// �Ŷ�ս��ս��Ʒ��ʷ��¼��
//enum WAR_ROAD_TEAM_AWARD_HISTORY_DATA
//{
//	WAR_ROAD_TEAM_AWARD_HISTORY_DATA_ID = 0,		// ������id					bigint
//	WAR_ROAD_TEAM_AWARD_HISTORY_DATA_SYNDICATE_ID,	// ����ID					uint
//	WAR_ROAD_TEAM_AWARD_HISTORY_DATA_CHAPTER,		// �½�						uint
//	WAR_ROAD_TEAM_AWARD_HISTORY_DATA_AWARD_TYPE,	// ս��Ʒ����				uint
//	WAR_ROAD_TEAM_AWARD_HISTORY_DATA_AWARD_NUM,		// ս��Ʒ����				uint
//	WAR_ROAD_TEAM_AWARD_HISTORY_DATA_USER_ID,		// ������ID				uint
//	WAR_ROAD_TEAM_AWARD_HISTORY_DATA_GIVE_TIME,		// ���ʱ�䣨δ����ļ�¼��ʾ�´��Զ�����ʱ�䣩				uint
//	WAR_ROAD_TEAM_AWARD_HISTORY_DATA_SENDER_ID,		// ������ID					uint
//	WAR_ROAD_TEAM_AWARD_HISTORY_DATA_SERVER_GROUP,	// ��������					uint
//};
//
//static const char* GAME_DB_NAME_WAR_ROAD_TEAM_DPS	= "war_road_team_dps";	// �Ŷ�ս���˺���¼��
//enum WAR_ROAD_TEAM_DPS_DATA
//{
//	WAR_ROAD_TEAM_DPS_DATA_ID = 0,			// ������id					bigint
//	WAR_ROAD_TEAM_DPS_DATA_LOG_ID,			// log_id					bigint
//	WAR_ROAD_TEAM_DPS_DATA_USER_ID,			// ���ID					uint
//	WAR_ROAD_TEAM_DPS_DATA_DPS_VALUE,		// dps�˺�ֵ				uint
//	WAR_ROAD_TEAM_DPS_DATA_SERVER_GROUP,	// ��������					uint
//};
//
//static const char* GAME_DB_NAME_WAR_ROAD_TEAM_DPS_HISTORY = "war_road_team_dps_history";	// �Ŷ�ս���˺���¼��
//enum WAR_ROAD_TEAM_DPS_HISTORY_DATA
//{
//	WAR_ROAD_TEAM_DPS_HISTORY_DATA_ID = 0,				// ������id					bigint
//	WAR_ROAD_TEAM_DPS_HISTORY_DATA_CHAPTER,				// �½�						uint
//	WAR_ROAD_TEAM_DPS_HISTORY_DATA_USER_ID,				// ���ID(����������һ�������¼)		uint
//	WAR_ROAD_TEAM_DPS_HISTORY_DATA_SERVER_GROUP,		// ��������					uint
//	WAR_ROAD_TEAM_DPS_HISTORY_DATA_DPS_VALUE,			// dps�˺�ֵ				uint
//	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER1_TYPE,			// ��ս��������1			uint
//	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER1_LEV,			// ��ս���Ƶȼ�1			uint
//	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER1_STAR,			// ��ս�����Ǽ�1			uint
//	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER1_COLOR,		// ��ս������ɫ1			uint
//	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER2_TYPE,			// ��ս��������2			uint
//	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER2_LEV,			// ��ս���Ƶȼ�2			uint
//	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER2_STAR,			// ��ս�����Ǽ�2			uint
//	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER2_COLOR,		// ��ս������ɫ2			uint
//	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER3_TYPE,			// ��ս��������3			uint
//	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER3_LEV,			// ��ս���Ƶȼ�3			uint
//	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER3_STAR,			// ��ս�����Ǽ�3			uint
//	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER3_COLOR,		// ��ս������ɫ3			uint
//	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER4_TYPE,			// ��ս��������4			uint
//	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER4_LEV,			// ��ս���Ƶȼ�4			uint
//	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER4_STAR,			// ��ս�����Ǽ�4			uint
//	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER4_COLOR,		// ��ս������ɫ4			uint
//	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER5_TYPE,			// ��ս��������5			uint
//	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER5_LEV,			// ��ս���Ƶȼ�5			uint
//	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER5_STAR,			// ��ս�����Ǽ�5			uint
//	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER5_COLOR,		// ��ս������ɫ5			uint
//};
//
//static const char* GAME_DB_NAME_GAME_HISTORY_COMPLETE	= "game_history_complete";	// �ɼ������ʷ��¼��
//enum GAME_HISTORY_COMPLETE_DATA
//{
//	GAME_HISTORY_COMPLETE_DATA_ID	= 0,				// ������id					bigint
//	GAME_HISTORY_COMPLETE_DATA_SERVER_GROUP,			// ��������					uint
//	GAME_HISTORY_COMPLETE_DATA_TYPE,					// �������					uint
//	GAME_HISTORY_COMPLETE_DATA_RECORD_ID,				// ��¼ID					uint
//	GAME_HISTORY_COMPLETE_DATA_CREATE_TIME,				// ����ʱ��					uint
//	GAME_HISTORY_COMPLETE_DATA_PARAM1,					// ����1					uint
//	GAME_HISTORY_COMPLETE_DATA_PARAM2,					// ����2					uint
//	GAME_HISTORY_COMPLETE_DATA_PARAM3,					// ����3					uint
//};
//
//static const char* GAME_DB_NAME_SYN_WORSHIP = "syn_worship";	// ����Ĥ�ݼ�¼��
//enum SYN_WORSHIP_DATA
//{
//	SYN_WORSHIP_DATA_ID = 0,					// ID				bigint
//	SYN_WORSHIP_DATA_USER_ID,					// ���ID			uint
//	SYN_WORSHIP_DATA_BEWORSHIP_ID,				// ��Ĥ�����ID		uint
//	SYN_WORSHIP_DATA_TIME,						// Ĥ������			uint
//};
//
//static const char* GAME_DB_NAME_SYN_WORSHIP_AWARD = "syn_worship_award";	// ����Ĥ�ݽ�����
//enum SYN_WORSHIP_AWARD_DATA
//{
//	SYN_WORSHIP_AWARD_ID = 0,					// ID				bigint
//	SYN_WORSHIP_AWARD_USER_ID,					// ���ID			uint
//	SYN_WORSHIP_AWARD_AWARD_TYPE,				// ��������			uint
//	SYN_WORSHIP_AWARD_AWARD_TOTAL,				// �����ۼƺ�		uint
//	SYN_WORSHIP_AWARD_SERVER_GROUP,				// ��������			uint
//};
//
//static const char* GAME_DB_NAME_MINE_FIGHT_POKER = "mine_fight_poker";	// ��ս�����Ʊ�
//enum MINE_FIGHT_POKER
//{
//	MINE_FIGHT_POKER_ID = 0,			// ID				uint
//	MINE_FIGHT_POKER_ATK_USER_ID,		// ���������ID		uint
//	MINE_FIGHT_POKER_DEF_USER_ID,		// ���ط����ID		uint
//	MINE_FIGHT_POKER_POKER_ID,			// ����ID			bigint
//	MINE_FIGHT_POKER_LEFT_HP,			// ʣ��Ѫ��			uint
//	MINE_FIGHT_POKER_LEFT_SP,			// ʣ��ŭ��			uint
//	MINE_FIGHT_POKER_POKER_CAMP,		// ���ƹ���			uint
//};
//
//static const char* GAME_DB_NAME_FRIEND_INVITE = "friend_invite";			//  ���������
//enum FRIEND_INVITE
//{
//	FRIEND_INVITE_ID = 0,				// ID				bigint
//	FRIEND_INVITE_INVITER_ID,			// ������ID			uint
//	FRIEND_INVITE_BE_INVITER_ID,		// ��������ID		uint
//	FRIEND_INVITE_VAS,					// �ۼ�Ԫ��			uint
//	FRIEND_INVITE_SERVER_GROUP,			// ��������			uint
//};
//
//static const char* GAME_DB_NAME_FRIEND_INVITE_CODE = "friend_invite_code";	//  �����������
//enum FRIEND_INVITE_CODE
//{
//	FRIEND_INVITE_CODE_USER_ID,				// ���ID			uint
//	FRIEND_INVITE_CODE_CODE,				// ������			varchar16
//};
//
//static const char* GAME_DB_NAME_TALK_WORLD = "talk_world";	// ���������
//enum TALK_WORLD_DATA
//{
//	TALK_WORLD_DATA_ID = 0,								// ������ID				bigint
//	TALK_WORLD_DATA_SENDER_ID,							// ������ID				uint
//	TALK_WORLD_DATA_SENDER_NAME,						// �����߽�ɫ��			varchar32
//	TALK_WORLD_DATA_SENDER_FACE,						// ������ͷ��			uint
//	TALK_WORLD_DATA_SENDER_LEV,							// �����ߵȼ�			uint
//	TALK_WORLD_DATA_TEXT,								// ��������				varchar256
//	TALK_WORLD_DATA_TIME,								// ����ʱ��				uint
//	TALK_WORLD_DATA_TYPE,								// ����					uint
//	TALK_WORLD_DATA_PARAM1,								// Ԥ��1				uint
//	TALK_WORLD_DATA_PARAM2,								// Ԥ��2				uint
//	TALK_WORLD_DATA_PARAM3,								// Ԥ��3				uint
//	TALK_WORLD_DATA_PARAM4,								// Ԥ��4				uint
//	TALK_WORLD_DATA_SERVER_GROUP,						// ��������				uint
//};
//
//static const char* GAME_DB_NAME_TALK_SYN = "talk_syn";	// ���������
//enum TALK_SYN_DATA
//{
//	TALK_SYN_DATA_ID = 0,								// ������ID				bigint
//	TALK_SYN_DATA_SYN_ID,								// ����ID				bigint
//	TALK_SYN_DATA_SENDER_ID,							// ������ID				uint
//	TALK_SYN_DATA_SENDER_NAME,							// �����߽�ɫ��			varchar32
//	TALK_SYN_DATA_SENDER_FACE,							// ������ͷ��			uint
//	TALK_SYN_DATA_SENDER_LEV,							// �����ߵȼ�			uint
//	TALK_SYN_DATA_TEXT,									// ��������				varchar256
//	TALK_SYN_DATA_TIME,									// ����ʱ��				uint
//	TALK_SYN_DATA_TYPE,									// ����					uint
//	TALK_SYN_DATA_PARAM1,								// Ԥ��1				uint
//	TALK_SYN_DATA_PARAM2,								// Ԥ��2				uint
//	TALK_SYN_DATA_PARAM3,								// Ԥ��3				uint
//	TALK_SYN_DATA_PARAM4,								// Ԥ��4				uint
//	TALK_SYN_DATA_SERVER_GROUP,							// ��������				uint
//};
//
//static const char* GAME_DB_NAME_TALK_PRIVATE = "talk_private";	// ˽�ı�
//enum TALK_PRIVATE_DATA
//{
//	TALK_PRIVATE_DATA_ID = 0,								// ������ID				bigint
//	TALK_PRIVATE_DATA_USER_ID,								// ������ID				uint
//	TALK_PRIVATE_DATA_SENDER_ID,							// ������ID				uint
//	TALK_PRIVATE_DATA_SENDER_NAME,							// �����߽�ɫ��			varchar32
//	TALK_PRIVATE_DATA_SENDER_FACE,							// ������ͷ��			uint
//	TALK_PRIVATE_DATA_SENDER_LEV,							// �����ߵȼ�			uint
//	TALK_PRIVATE_DATA_TEXT,									// ��������				varchar256
//	TALK_PRIVATE_DATA_TIME,									// ����ʱ��				uint
//	TALK_PRIVATE_DATA_TYPE,									// ����					uint
//	TALK_PRIVATE_DATA_PARAM1,								// Ԥ��1				uint
//	TALK_PRIVATE_DATA_PARAM2,								// Ԥ��2				uint
//	TALK_PRIVATE_DATA_PARAM3,								// Ԥ��3				uint
//	TALK_PRIVATE_DATA_PARAM4,								// Ԥ��4				uint
//	TALK_PRIVATE_DATA_SERVER_GROUP,							// ��������		
//};
//
//static const char* GAME_DB_NAME_MINE_COLLECT = "mine_collect";	// �󶴲ɼ���
//enum MINE_COLLECT_DATA
//{
//	MINE_COLLECT_DATA_USER_ID = 0,							// ���ID				uint
//	MINE_COLLECT_DATA_NAME,									// ��ҽ�ɫ��			varchar32
//	MINE_COLLECT_DATA_LEV,									// ��ҵȼ�				uint
//	MINE_COLLECT_DATA_LOOKFACE,								// ���ͷ��				uint
//	MINE_COLLECT_DATA_LOOKFACE_FRAME,						// ���ͷ���			uint
//	MINE_COLLECT_DATA_ATK_COUNT_TOTAL,						// �����󶴴����ܺ�		uint
//	MINE_COLLECT_DATA_MONEY_TOTAL,							// ��ý���ܺ�			uint	
//	MINE_COLLECT_DATA_DRUG_TOTAL,							// ���ҩ���ܺ�			uint
//	MINE_COLLECT_DATA_ATK_COUNT0_VALUE,						// ��������ֵ0			uint
//	MINE_COLLECT_DATA_MONEY0_VALUE,							// ���ֵ0				uint
//	MINE_COLLECT_DATA_DRUG0_VALUE,							// ҩ��ֵ0				uint
//	MINE_COLLECT_DATA_DATE0,								// ����0				uint
//	MINE_COLLECT_DATA_ATK_COUNT1_VALUE,						// ��������ֵ1			uint
//	MINE_COLLECT_DATA_MONEY1_VALUE,							// ���ֵ1				uint
//	MINE_COLLECT_DATA_DRUG1_VALUE,							// ҩ��ֵ1				uint
//	MINE_COLLECT_DATA_DATE1,								// ����1				uint
//	MINE_COLLECT_DATA_ATK_COUNT2_VALUE,						// ��������ֵ2			uint
//	MINE_COLLECT_DATA_MONEY2_VALUE,							// ���ֵ2				uint
//	MINE_COLLECT_DATA_DRUG2_VALUE,							// ҩ��ֵ2				uint
//	MINE_COLLECT_DATA_DATE2,								// ����2				uint
//	MINE_COLLECT_DATA_ATKCOUNT_RANK_LAST,					// ����������������		uint
//	MINE_COLLECT_DATA_MONEY_RANK_LAST,						// ��Ҳɼ���������		uint
//	MINE_COLLECT_DATA_DRUG_RANK_LAST,						// ҩ���ɼ���������		uint
//	MINE_COLLECT_DATA_SERVER_GROUP,							// ��������				uint
//};
//
//static const char* GAME_DB_NAME_SYN_GIFT_BOX_LOG	= "syn_giftbox_log";	// ������м�¼��
//enum SYN_GIFT_BOX_LOG_DATA
//{
//	SYN_GIFT_BOX_LOG_DATA_ID = 0,							// ������ID				bigint
//	SYN_GIFT_BOX_LOG_DATA_SYNDICATE_ID,						// ����ID				uint
//	SYN_GIFT_BOX_LOG_DATA_BOX_TYPE,							// �������				uint
//	SYN_GIFT_BOX_LOG_DATA_INVAILD_TIME,						// ����ʱ��				uint
//	SYN_GIFT_BOX_LOG_DATA_GIVE_USER_ID,						// �������ID			uint	
//	SYN_GIFT_BOX_LOG_DATA_GIVE_USER_NAME,					// �����������			varchar32
//	SYN_GIFT_BOX_LOG_DATA_SERVER_GROUP,						// ��������				uint
//};
//
//static const char* GAME_DB_NAME_USER_SYN_GIFTBOX_AWARD	= "user_syn_giftbox_ward";	// ��Ұ��������ȡ��¼��
//enum USER_SYN_GIFTBOX_AWARD_DATA
//{
//	USER_SYN_GIFTBOX_AWARD_DATA_USER_ID = 0,				// ���ID				uint
//	USER_SYN_GIFTBOX_AWARD_DATA_SYN_GIFTBOX_ID,				// ������м�¼id		uint
//	USER_SYN_GIFTBOX_AWARD_DATA_INVIALDTIME,				// ʧЧʱ��				uint
//};
//
//static const char* GAME_DB_NAME_LOOKFACE_FRAME = "lookface_frame";					// ��һ�õ�ͷ������ݱ�
//enum USER_LOOKFACE_FRAME
//{
//	USER_LOOKFACE_FRAME_ID = 0,								// ID					uint
//	USER_LOOKFACE_FRAME_USER_ID,							// ���ID				uint
//	USER_LOOKFACE_FRAME_FRAME_TYPE,							// ͷ�������			uint
//	USER_LOOKFACE_FRAME_END_TIME,							// ����ʱ��				uint
//};
//
//
//static const char* GAME_DB_NAME_CROSS_ROOM = "cs_room";		// ��������
//enum CROSS_ROOM_DATA
//{
//	CROSS_ROOM_DATA_ID = 0,		// id			uint
//	CROSS_ROOM_DATA_TYPE,		// ����			uint
//	CROSS_ROOM_DATA_LINE,		// ������·		uint
//	CROSS_ROOM_DATA_OWNER_ID,	// ӵ����id		uint
//	CROSS_ROOM_DATA_CREATE_TIME,// ���䴴��ʱ��	uint
//	CROSS_ROOM_DATA_END_TIME,	// ǿ�ƽ�ɢʱ�� uint
//	CROSS_ROOM_DATA_DATA1,		// ����1		uint
//	CROSS_ROOM_DATA_DATA2,		// ����2		uint
//	CROSS_ROOM_DATA_DATA3,		// ����3		uint
//	CROSS_ROOM_DATA_DATA4,		// ����4		uint
//	CROSS_ROOM_DATA_DATA5,		// ����5		uint
//	CROSS_ROOM_DATA_STR1,		// �ִ�1		varchar255
//	CROSS_ROOM_DATA_STR2,		// �ִ�2		varchar255
//};
//
//static const char* GAME_DB_NAME_CROSS_ROOM_MEMBER = "cs_room_member";	// ��������Ա��
//enum CROSS_ROOM_MEMBER_DATA
//{
//	CROSS_ROOM_MEMBER_DATA_USER_ID = 0,		// ��ɫid		uint
//	CROSS_ROOM_MEMBER_DATA_ROOM_ID,			// ����id		uint
//	CROSS_ROOM_MEMBER_DATA_DATA1,			// ����1		uint
//	CROSS_ROOM_MEMBER_DATA_DATA2,			// ����2		uint
//	CROSS_ROOM_MEMBER_DATA_DATA3,			// ����3		uint
//};
//
//static const char* GAME_DB_NAME_CROSS_NTM_FIGHT_LOG = "cs_ntm_fight_log";	// ���������ս����¼��
//enum CROSS_NTM_FIGHT_LOG_DATA
//{
//	CROSS_NTM_FIGHT_LOG_DATA_USER_ID = 0,		// ��ɫid	uint
//	CROSS_NTM_FIGHT_LOG_DATA_INTEGRAL,			// ����		uint
//	CROSS_NTM_FIGHT_LOG_DATA_PASS_TIME,			// ͨ��ʱ��	uint
//	CROSS_NTM_FIGHT_LOG_DATA_RANK,				// ����		uint
//	CROSS_NTM_FIGHT_LOG_DATA_AWARD_TYPE,		// ��������	uint
//	CROSS_NTM_FIGHT_LOG_DATA_AWARD_NUM,			// ��������	uint
//};
//
//static const char* GAME_DB_NAME_SYN_BUFF = "syn_buff";		// ����buff��
//enum SYN_BUFF_DATA
//{
//	SYN_BUFF_DATA_ID = 0,						// id		bigint
//	SYN_BUFF_DATA_SYNDICATE_ID,					// ����id	uint
//	SYN_BUFF_DATA_TYPE,							// buff����	uint
//	SYN_BUFF_DATA_POWER,						// buff����	uint
//	SYN_BUFF_DATA_END_TIME,						// ����ʱ��	uint
//	SYN_BUFF_DATA_ADD_COUNT,					// ���Ӳ���	uint
//	SYN_BUFF_DATA_PARAM1,						// ����1	uint
//	SYN_BUFF_DATA_PARAM2,						// ����2	uint
//	SYN_BUFF_DATA_SERVER_GROUP,					// ��������	uint
//};
//
//static const char* GAME_DB_NAME_USER_BUFF = "user_buff";	// �����buff��
//enum USER_BUFF_DATA
//{
//	USER_BUFF_DATA_ID = 0,						// id		bigint
//	USER_BUFF_DATA_USER_ID,						// ��ɫid	uint
//	USER_BUFF_DATA_TYPE,						// buff����	uint
//	USER_BUFF_DATA_POWER,						// buff����	uint
//	USER_BUFF_DATA_END_TIME,					// ����ʱ��	uint
//	USER_BUFF_DATA_SOURCE_ID,					// ��ԴID	uint
//	USER_BUFF_DATA_ADD_COUNT,					// ���Ӳ���	uint
//	USER_BUFF_DATA_PARAM1,						// ����1	uint
//	USER_BUFF_DATA_PARAM2,						// ����2	uint
//};
//
//static const char* GAME_DB_NAME_USER_MARKS_INFO = "user_marksinfo";	// ���������Ϣ��¼��
//enum USER_MARKSINFO_DATA
//{
//	USER_MARKSINFO_DATA_USER_ID,				// ��ɫid	uint
//	USER_MARKSINFO_DATA_TYPE,					// ��������	uint
//	USER_MARKSINFO_DATA_DATA,					// ��������	uint
//};

#endif // end of _DATABASE_DEFINE_GAME_H_