////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan ChuangYou, All Rights Reserved
// Moudle: DatabaseDefine.h
//		���ݿ��������ȫ��������
// Author: ������(Peng Wenqi)
// Created: 2014-11-3
////////////////////////////////////////////////////////////////////////
#ifndef _CARD_SERVER_DATABASE_DEFINE_
#define _CARD_SERVER_DATABASE_DEFINE_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �˺ſ�
static const char* ACC_DB_NAME_ACCOUNT = "account";		// �˺ű�
enum ACCOUNT_DATA
{
	ACCOUNT_DATA_ID = 0,				// id,			uint
	ACCOUNT_DATA_NAME,					// �˺���,		varchar64
	ACCOUNT_DATA_PASSWORD,				// ����,		varchar64
	ACCOUNT_DATA_REG_TIME,				// ע��utcʱ��, uint
	ACCOUNT_DATA_ACCOUNT_TYPE,			// �˺�����		uint
	ACCOUNT_DATA_ACCOUNT_STATUS,		// �˺�״̬		uint
	ACCOUNT_DATA_ACCOUNT_STATUS_PARAM,	// �˺�״̬����	uint
	ACCOUNT_DATA_PLATFORM,				// ƽ̨			varchar32
	ACCOUNT_DATA_CHANNEL,				// ����			varchar32
	ACCOUNT_DATA_OS,					// os			varchar32
	ACCOUNT_DATA_BIND_INVITE_CODE,		// ��������	varchar32
};

static const char* ACC_DB_VAS_LOG = "vas_log";	// Ԫ����־��
enum VAS_LOG_DATA
{
	VAS_LOG_DATA_ID = 0,			// id			bigint
	VAS_LOG_DATA_ACCOUNT_ID,		// �˺�id		uint
	VAS_LOG_DATA_USER_ID,			// ��ɫid		uint
	VAS_LOG_DATA_SERVER_GROUP,		// ��������		uint
	VAS_LOG_DATA_SERVER_LINE,		// ��������		uint
	VAS_LOG_DATA_FLOW_TYPE,			// ��������		uint
	VAS_LOG_DATA_TIME,				// ʱ��, utc��	uint
	VAS_LOG_DATA_ITEMTYPE_ID,		// itemtype		uint
	VAS_LOG_DATA_ITEMTYPE_AMOUNT,	// ����			uint
	VAS_LOG_DATA_POINT,				// ��������		bigint
	VAS_LOG_DATA_AFTER_POINT,		// ���������	bigint
	VAS_LOG_DATA_EXTRA_TEXT,		// ��������˵�� varchar128
};

static const char* ACC_DB_MONEY_LOG = "money_log";	// ��Ǯ��־��
enum MONEY_LOG_DATA
{
	MONEY_LOG_DATA_ID = 0,			// id			bigint
	MONEY_LOG_DATA_ACCOUNT_ID,		// �˺�id		uint
	MONEY_LOG_DATA_USER_ID,			// ��ɫid		uint
	MONEY_LOG_DATA_SERVER_GROUP,	// ��������		uint
	MONEY_LOG_DATA_SERVER_LINE,		// ��������		uint
	MONEY_LOG_DATA_FLOW_TYPE,		// ��������		uint
	MONEY_LOG_DATA_TIME,			// ʱ��, utc��	uint
	MONEY_LOG_DATA_ITEMTYPE_ID,		// itemtype		uint
	MONEY_LOG_DATA_ITEMTYPE_AMOUNT,	// ����			uint
	MONEY_LOG_DATA_MONEY_TYPE,		// �������		uint
	MONEY_LOG_DATA_POINT,			// ��������		bigint
	MONEY_LOG_DATA_AFTER_POINT,		// ���������	bigint
	MONEY_LOG_DATA_EXTRA_TEXT,		// ��������˵�� varchar128
};

static const char* ACC_DB_SERVER_LIST = "server_list";	// �������б�, ά����Ա���õ�
enum SERVER_LIST_DATA
{
	SERVER_LIST_DATA_GROUP = 0,			// ��id			uint
	SERVER_LIST_DATA_LINE,				// ��id			uint
	SERVER_LIST_DATA_CLIENT_IP,			// �ͻ���ip		varchar50
	SERVER_LIST_DATA_CLIENT_PORT,		// �ͻ��˶˿�	uint 
	SERVER_LIST_DATA_CLOSE,				// �رձ��		uint
};

static const char* ACC_DB_NEWCARD = "newcard";	// ���ֿ������
enum NEWCARD_DATA
{
	NEWCARD_DATA_ID = 0,			// id			bigint
	NEWCARD_DATA_CARD,				// ����			char64
	NEWCARD_DATA_PICKED,			// ʹ�ñ��		uint
	NEWCARD_DATA_PLATFORM,			// ƽ̨			varchar10
	NEWCARD_DATA_SERVER_GROUP,		// ��������		uint
};

static const char* ACC_DB_PAYLOG = "paylog";	// ��ֵ��¼��
enum PAYLOG_DATA
{
	PAYLOG_DATA_LOGID = 0,		// id			bigint
	PAYLOG_DATA_PAYNUM,			// ��ˮ��		varchar255
	PAYLOG_DATA_LOGDATE,		// ��ֵutcʱ��	uint
	PAYLOG_DATA_ACCOUNT_ID,		// �˺�id		uint
	PAYLOG_DATA_USER_ID,		// ��ɫid		uint
	PAYLOG_DATA_IP,				// ip			varchar20
	PAYLOG_DATA_PAYGOLD,		// ��ֵԪ��		uint
	PAYLOG_DATA_FREEGOLD,		// ����Ԫ��		uint
	PAYLOG_DATA_PAYMONEY,		// �����		DECIMAL
	PAYLOG_DATA_CHANNEL,		// channel		varchar20
	PAYLOG_DATA_CHANNEL_FEE,	// channel_fee	float
	PAYLOG_DATA_SERVER_GROUP,	// ���������	uint
	PAYLOG_DATA_CONFIG_ID,		// ����id		uint
	PAYLOG_DATA_STATUS,			// ���״̬��0 �����У� 1 ͨ���� 2 �ܾ�, 3 ��ᣩ	uint
};

static const char* ACC_DB_ONLINE_LOG = "online_log";	// ������־��
enum ONLINE_LOG_DATA
{
	ONLINE_LOG_DATA_ID = 0,
	ONLINE_LOG_DATA_TIME,
	ONLINE_LOG_DATA_COUNT_ONLINE,
	ONLINE_LOG_DATA_SERVER_GROUP,
};

static const char* ACC_DB_NOTIFY_PHP = "notify_php";	// ƽ̨�����
enum NOTIFY_PHP_DATA
{
	NOTIFY_PHP_DATA_ID = 0,				// ������id	uint
	NOTIFY_PHP_DATA_BEGIN_TIME,			// ��ʼʱ�� uint
	NOTIFY_PHP_DATA_INTERVAL_SECOND,	// ���ʱ�� uint
	NOTIFY_PHP_DATA_COUNT,				// ���Ŵ��� uint
	NOTIFY_PHP_DATA_CHANNEL,			// Ƶ��		uint
	NOTIFY_PHP_DATA_TEXT,				// �������� varchar512
	NOTIFY_PHP_DATA_SERVER_GROUP,		// �������� uint
};

static const char* ACC_DB_NAME_GM_MAC = "gm_mac";	// gm Mac��ַ����
enum GM_MAC_DATA
{
	GM_MAC_DATA_ADDRESS_MAC = 0,		// mac��ַ�ַ���	varchar32
	GM_MAC_DATA_PARAM_STRING,			// ע���ַ���		varchar64
};

static const char* ACC_DB_NAME_GM_OPERATION_LOG = "gm_operation_log";	// gm ������־
enum GM_OPERATION_LOG_DATA
{
	GM_OPERATION_LOG_DATA_ID = 0,				// id				uint
	GM_OPERATION_LOG_DATA_UTC_SECOND,			// ��¼ʱ��, utc��	uint
	GM_OPERATION_LOG_DATA_DATE_TIME,			// ����ʱ��			varchar24
	GM_OPERATION_LOG_DATA_GM_ACCOUNT_ID,		// gm�˺�id			uint
	GM_OPERATION_LOG_DATA_GM_ACCOUNT_NAME,		// gm�˺���			varchar32
	GM_OPERATION_LOG_DATA_GM_USER_ID,			// gm��ɫid			uint
	GM_OPERATION_LOG_DATA_GM_USER_NAME,			// gm��ɫ��			varchar32
	GM_OPERATION_LOG_DATA_GM_IP,				// gm����ʱip		varchar32
	GM_OPERATION_LOG_DATA_GM_MAC,				// gm����ʱmac��ַ	varchar32
	GM_OPERATION_LOG_DATA_SERVER_GROUP,			// ��������			uint
	GM_OPERATION_LOG_DATA_SERVER_LINE,			// ��������			uint
	GM_OPERATION_LOG_DATA_OPERATION_TYPE_STR,	// ���������ַ���	varchar16
	GM_OPERATION_LOG_DATA_OPERATION_INFO,		// ��������			varchar128
};

//////////////////////////////////////////////////////////////////////////
// ��Ϸ��
static const char* GAME_DB_NAME_USER = "user";	// ��ɫ��
enum USER_DATA
{
	USER_DATA_BEGIN = 0,		// �ڱ�ͷ
	USER_DATA_ID = 0,			// ��ɫid, 1000W��				uint
	USER_DATA_ACCOUNT_ID,		// �˺�id						uint
	USER_DATA_NAME,				// ��ɫ��						varchar32
	USER_DATA_LAST_LOGIN,		// ���һ�ε�½����(YYYYMMDD)	uint
	USER_DATA_CREATE_TIME,		// ����ʱ��(utcʱ��)			uint
	USER_DATA_EXIT_TIME,		// �˳�ʱ��(utcʱ��)			uint
	USER_DATA_YESTERDAY_LOGIN,	// ���յ�½���					uint
	USER_DATA_ALL_ONLINE_TIME,	// ������ʱ��(��λ��)			uint
	USER_DATA_SERVER_GROUP,		// ������������					uint
	USER_DATA_LEV,				// �ȼ�							uint
	USER_DATA_EXP,				// ����							bigint
	USER_DATA_SEX,				// �Ա�							uint
	USER_DATA_LOOKFACE,			// ͷ��							uint
	USER_DATA_DEL_FLAG,			// ɾ�����						uint
	USER_DATA_ACCOUNT_TYPE,		// �˺�����, �˺ű���			uint
	USER_DATA_MAX_SCORE,		// ���ս����					uint
	USER_DATA_MAX_POKER_STAR,	// �������Ǽ�					uint
	USER_DATA_INIT_POKER,		// ��ʼ������ѡ��				uint
	USER_DATA_STOP_TALK_END,	// ���Խ���ʱ��					uint
	USER_DATA_EXP0_DATE_DAYS,	// ����ͳ����0 EPOCH DAY		uint
	USER_DATA_EXP0_DATE_YMD,	// ����ͳ����0 YYYYMMDD			uint
	USER_DATA_EXP0_VALUE,		// ����ͳ����0 ����ֵ			uint
	USER_DATA_EXP1_DATE_DAYS,	// ����ͳ����1 EPOCH DAY		uint
	USER_DATA_EXP1_DATE_YMD,	// ����ͳ����1 YYYYMMDD			uint
	USER_DATA_EXP1_VALUE,		// ����ͳ����1 ����ֵ			uint
	USER_DATA_EXP2_DATE_DAYS,	// ����ͳ����2 EPOCH DAY		uint
	USER_DATA_EXP2_DATE_YMD,	// ����ͳ����2 YYYYMMDD			uint
	USER_DATA_EXP2_VALUE,		// ����ͳ����2 ����ֵ			uint
	USER_DATA_SIGNATURE,		// ����ǩ��						varchar256
	USER_DATA_LOOKFACE_FRAME,	// ͷ���                       uint
	USER_DATA_BIRTHDAY,			// ����		   YYYYMMDD         uint
	USER_DATA_ADDRESS,			// ���ڵ�						varchar64
	USER_DATA_GLAMOUR,			// ����ֵ						uint
	USER_DATA_GLAMOUR_TOTAL,	// ������ֵ						uint
	USER_DATA_END,				// �ڱ�β
};

static const char* GAME_DB_NAME_USER_MONEY = "user_money";	// ��ɫ��ұ�
enum USER_MONEY_DATA
{
	USER_MONEY_DATA_ID = 0,		// id			bigint
	USER_MONEY_DATA_USERID,		// ��ɫid		bigint
	USER_MONEY_DATA_MONEYTYPE,	// ��������		uint
	USER_MONEY_DATA_MONEYDATA,	// ��������		bigint
};

static const char* GAME_DB_NAME_USER_VAS = "user_vas";	// ��ɫԪ����
enum USER_VAS_DATA
{
	USER_VAS_DATA_USER_ID = 0,				// ��ɫid			uint
	USER_VAS_DATA_VAS,						// ��ǰԪ��			bigint
	USER_VAS_DATA_TOTAL_PAY_VAS,			// �ܳ�ֵԪ��		bigint
	USER_VAS_DATA_TOTAL_FREE_VAS,			// ������Ԫ��		bigint
	USER_VAS_DATA_TOTAL_USE_VAS,			// ������Ԫ��		bigint
	USER_VAS_DATA_FISRT_SPEND_TIME,			// ��һ������ʱ��	uint
	USER_VAS_DATA_LAST_SPEND_TIME,			// �������ʱ��		uint
	USER_VAS_DATA_MONTH_CARD_ID,			// �¿�id			uint
	USER_VAS_DATA_MONTH_CARD_GOT_DATE,		// ��ȡ��������		uint
	USER_VAS_DATA_MONTH_CARD_END_DATE,		// ���һ����ȡ����	uint
	USER_VAS_DATA_FISRT_MASK,				// ��һ����ȡ����	uint
};

static const char* GAME_DB_NAME_USER_MASK = "user_mask";	// ���������
enum USER_MASK_DATA
{
	USER_MASK_DATA_ID = 0,				// id,			int
	USER_MASK_DATA_USERID,				// ���id,		uint
	USER_MASK_DATA_MASKTYPE,			// ��������,	uint
	USER_MASK_DATA_MASKID,				// ����id,		uint
	USER_MASK_DATA_CLEARTIME,			// ����ʱ��		uint
	USER_MASK_DATA_MASKDATA,			// ��������		bigint
};

static const char* GAME_DB_NAME_GROUP_MASK = "group_mask";	// �������
enum LINE_MASK_DATA
{
	LINE_MASK_DATA_ID = 0,				// ����id,		int
	LINE_MASK_DATA_SERVER_GROUP,		// ��������,	uint
	LINE_MASK_DATA_DATA,				// ����			uint
	LINE_MASK_DATA_ENDTIME,				// ����ʱ��		uint
};

static const char* GAME_DB_NAME_WORLD_MASK = "world_mask";	// ���������
enum SERVER_MASK_DATA
{
	SERVER_MASK_DATA_ID = 0,			// ����id,		int
	SERVER_MASK_DATA_DATA,				// ����			uint
	SERVER_MASK_DATA_ENDTIME,			// ����ʱ��		uint
};

static const char* GAME_DB_NAME_ITEM_LOG = "item_log";	// ��Ʒ�����
enum LOG_ITEM_FLOW_DATA
{
	LOG_ITEM_FLOW_DATA_ID = 0,		// ������id					bigint
	LOG_ITEM_FLOW_DATA_OWNERID,		// ����id					uint
	LOG_ITEM_FLOW_DATA_TARGETID,	// ��������id				uint
	LOG_ITEM_FLOW_DATA_ITEMID,		// ��Ʒid					bigint
	LOG_ITEM_FLOW_DATA_ITEMTYPE,	// ��Ʒtypeid				uint
	LOG_ITEM_FLOW_DATA_ITEMCOUNT,	// ��Ʒ����					uint
	LOG_ITEM_FLOW_DATA_TYPE,		// ��Ʒ����					uint
	LOG_ITEM_FLOW_DATA_CREATETIME,	// ����ʱ��(utcʱ�䣩		uint
	LOG_ITEM_FLOW_DATA_SERVERID,	// ��������					uint
	LOG_ITEM_FLOW_DATA_LINE,		// ��·						uint
	LOG_ITEM_FLOW_DATA_COMMENT,		// ˵���ֶ�					varchar128
};

static const char* GAME_DB_NAME_USER_TMP_DATA = "user_tmp_data";	// ��ɫTmpdata��
enum USERTMPDATA_DATA
{
	USERTMPDATA_ERROR = -1,
	USERTMPDATA_ID = 0,							// id		bigint										
	USERTMPDATA_USERID,							// ���id	uint
	USERTMPDATA_TMP_DATA_ID,					// ����id	uint

	USERTMPDATA_DATA_BEGIN,
	USERTMPDATA_DATA0 = USERTMPDATA_DATA_BEGIN,	// ����0	uint
	USERTMPDATA_DATA1,							// ����1	uint
	USERTMPDATA_DATA2,							// ����2	uint
	USERTMPDATA_DATA3,							// ����3	uint					
	USERTMPDATA_DATA4,							// ����4	uint
	USERTMPDATA_DATA5,							// ����5	uint
	USERTMPDATA_DATA6,							// ����6	uint
	USERTMPDATA_DATA7,							// ����7	uint
	USERTMPDATA_DATA_END,
};

static const char* GAME_DB_NAME_USER_TASK = "user_task";			// ��ɫ�����
enum EUSER_TASK
{	
	EUSER_TASK_ID			= 0,	// ���														uint
	EUSER_TASK_USER_ID,				// ���id													uint
	EUSER_TASK_TYPE,				// ��������													uint
	EUSER_TASK_STEP,				// ����														uint
	EUSER_TASK_STATUS,				// ����״̬(0:δ����,1:����, 2:�ύ, 3:�ﵽ���������δ�ύ)uint
	EUSER_TASK_COUNT1,				// ����1													uint
	EUSER_TASK_COUNT2,				// ����2													uint
	EUSER_TASK_COUNT3,				// ����3													uint
	EUSER_TASK_BEGIN_TIME,			// ��ʼʱ��(��λ��)											uint
	EUSER_TASK_OVER_TIME,			// ����ʱ��(0:������, >0:����ʱ�䵥λ��)					uint
};

static const char* GAME_DB_NAME_USER_NEWCARD = "user_newcard";		// ��ɫ���ֿ�ʹ����Ϣ��
enum USER_NEWCARD_DATA
{
	USER_NEWCARD_DATA_USERID = 0,	// ���id		uint
	USER_NEWCARD_DATA_LASTUSETIME,	// �ϴ�ʹ��ʱ��	uint
	// �����ֶ�Ϊ20������ʹ������	bigint
	USER_NEWCARD_DATA_MASKDATA1,
	USER_NEWCARD_DATA_MASKDATA2,
	USER_NEWCARD_DATA_MASKDATA3,
	USER_NEWCARD_DATA_MASKDATA4,
	USER_NEWCARD_DATA_MASKDATA5,
	USER_NEWCARD_DATA_MASKDATA6,
	USER_NEWCARD_DATA_MASKDATA7,
	USER_NEWCARD_DATA_MASKDATA8,
	USER_NEWCARD_DATA_MASKDATA9,
	USER_NEWCARD_DATA_MASKDATA10,
	USER_NEWCARD_DATA_MASKDATA11,
	USER_NEWCARD_DATA_MASKDATA12,
	USER_NEWCARD_DATA_MASKDATA13,
	USER_NEWCARD_DATA_MASKDATA14,
	USER_NEWCARD_DATA_MASKDATA15,
	USER_NEWCARD_DATA_MASKDATA16,
	USER_NEWCARD_DATA_MASKDATA17,
	USER_NEWCARD_DATA_MASKDATA18,
	USER_NEWCARD_DATA_MASKDATA19,
	USER_NEWCARD_DATA_MASKDATA20,
};

static const char* GAME_DB_NAME_USER_MAIL	= "mail";	// ����ʼ���
enum EUSER_MAIL
{
	EUSER_MAIL_ID		= 0,	// ���									bigint
	EUSER_MAIL_USER_ID,			// ���ID								uint
	EUSER_MAIL_STATUS,			// �ʼ�״̬(0:δ��, 1:�Ѷ�, 2:ɾ��)		uint
	EUSER_MAIL_TITLE,			// ����									varchar32
	EUSER_MAIL_SENDER,			// ������								varchar32
	EUSER_MAIL_CONTENT,			// ����									varchar256
	EUSER_MAIL_SEND_TIME,		// ��������								uint
	EUSER_MAIL_OVER_TIME,		// ����ʱ��(������ʱ������)				uint

	EUSER_MAIL_ITEM_TYPE1,		// ��Ʒ����1							uint
	EUSER_MAIL_ITEM_NUM1,		// ��Ʒ����1							uint
	EUSER_MAIL_ITEM_TYPE2,		// ��Ʒ����2							uint
	EUSER_MAIL_ITEM_NUM2,		// ��Ʒ����2							uint
	EUSER_MAIL_ITEM_TYPE3,		// ��Ʒ����3							uint
	EUSER_MAIL_ITEM_NUM3,		// ��Ʒ����3							uint
	EUSER_MAIL_ITEM_TYPE4,		// ��Ʒ����4							uint
	EUSER_MAIL_ITEM_NUM4,		// ��Ʒ����4							uint
	EUSER_MAIL_ITEM_TYPE5,		// ��Ʒ����5							uint
	EUSER_MAIL_ITEM_NUM5,		// ��Ʒ����5							uint
	EUSER_MAIL_ITEM_TYPE6,		// ��Ʒ����6							uint
	EUSER_MAIL_ITEM_NUM6,		// ��Ʒ����6							uint

	EUSER_MAIL_MONEY_TYPE1,		// ����1								uint
	EUSER_MAIL_MONEY_NUM1,		// ����1����							uint
	EUSER_MAIL_MONEY_TYPE2,		// ����2								uint
	EUSER_MAIL_MONEY_NUM2,		// ����2����							uint
	EUSER_MAIL_MONEY_TYPE3,		// ����3								uint
	EUSER_MAIL_MONEY_NUM3,		// ����3����							uint
	EUSER_MAIL_MONEY_TYPE4,		// ����4								uint
	EUSER_MAIL_MONEY_NUM4,		// ����4����							uint
	EUSER_MAIL_EXP,				// ����									uint
	EUSER_MAIL_SERVER_GROUP,	// ��������								uint
};


static const char* GAME_DB_NAME_POKER = "poker";	// ���Ʊ�
enum POKER_DATA
{
	POKER_DATA_ID = 0,			// id				bigint
	POKER_DATA_TYPE,			// ����				uint
	POKER_DATA_OWNER_ID,		// ӵ����id			uint
	POKER_DATA_LEV,				// �ȼ�				uint
	POKER_DATA_EXP,				// ����				bigint
	POKER_DATA_COLOR,			// ��ɫ				uint
	POKER_DATA_STAR,			// �Ǽ�				uint
	POKER_DATA_EQUIP1_TYPE,		// ��������			uint
	POKER_DATA_EQUIP1_STAR,		// �����Ǽ�			uint
	POKER_DATA_EQUIP1_EXP,		// ��������			uint
	POKER_DATA_EQUIP2_TYPE,		// ͷ������			uint
	POKER_DATA_EQUIP2_STAR,		// ͷ���Ǽ�			uint
	POKER_DATA_EQUIP2_EXP,		// ͷ������			uint
	POKER_DATA_EQUIP3_TYPE,		// ��������			uint
	POKER_DATA_EQUIP3_STAR,		// �����Ǽ�			uint
	POKER_DATA_EQUIP3_EXP,		// ��������			uint
	POKER_DATA_EQUIP4_TYPE,		// ��������			uint
	POKER_DATA_EQUIP4_STAR,		// �����Ǽ�			uint
	POKER_DATA_EQUIP4_EXP,		// ��������			uint
	POKER_DATA_EQUIP5_TYPE,		// �·�����			uint
	POKER_DATA_EQUIP5_STAR,		// �·��Ǽ�			uint
	POKER_DATA_EQUIP5_EXP,		// �·�����			uint
	POKER_DATA_EQUIP6_TYPE,		// Ь������			uint
	POKER_DATA_EQUIP6_STAR,		// Ь���Ǽ�			uint
	POKER_DATA_EQUIP6_EXP,		// Ь�Ӿ���			uint
	POKER_DATA_SKILL_SP_LEV,	// �ؼ��ȼ�			uint
	POKER_DATA_SKILL_AUTO1_LEV,	// �Զ�����1�ȼ�	uint
	POKER_DATA_SKILL_AUTO2_LEV,	// �Զ�����2�ȼ�	uint
	POKER_DATA_SKILL_AUTO3_LEV,	// �Զ�����3�ȼ�	uint
	POKER_DATA_SKILL_JOINT_LEV,	// ��Я���ܵȼ�		uint
	POKER_DATA_STATE,			// ����״̬��0���У�1��Ӫ��2�ڿ�	uint
};

static const char* GAME_DB_NAME_POKER_LOG = "poker_log";	// ��Ʒ�����
enum POKER_LOG_DATA
{
	POKER_LOG_DATA_ID = 0,		// ������id					bigint
	POKER_LOG_DATA_OWNERID,		// ����id					uint
	POKER_LOG_DATA_TARGETID,	// ��������id				uint
	POKER_LOG_DATA_POKER_ID,	// ����id					bigint
	POKER_LOG_DATA_POKER_TYPE,	// ����type					uint
	POKER_LOG_DATA_POKER_COUNT,	// ��������					uint
	POKER_LOG_DATA_TYPE,		// ��Ʒ����					uint
	POKER_LOG_DATA_CREATETIME,	// ����ʱ��(utcʱ�䣩		uint
	POKER_LOG_DATA_SERVERID,	// ��������					uint
	POKER_LOG_DATA_LINE,		// ��·						uint
	POKER_LOG_DATA_COMMENT,		// ˵���ֶ�					varchar128
};

static const char* GAME_DB_NAME_BLACK_LIST = "black_list";	// ������
enum BLACK_LIST
{
	BLACK_LIST_BEG		= 0,
	BLACK_LIST_ID       = 0,		// ������ID			uint
	BLACK_LIST_USER_ID,				// ���ID			uint
	BLACK_LIST_BAD_FRIEND_ID,		// ���������ID		uint
	BLACK_LIST_END,
};

static const char* GAME_DB_NAME_SYNDICATE = "syndicate";	// ���ɱ�
enum SYNDICATE_DATA
{
	SYNDICATE_DATA_ID = 0,				// id					uint
	SYNDICATE_DATA_SERVER_GROUP,		// ��������				uint
	SYNDICATE_DATA_NAME,				// ������				varchar32
	SYNDICATE_DATA_ANNOUNCE,			// ����					varchar255
	SYNDICATE_DATA_LEADER_ID,			// ����id				uint
	SYNDICATE_DATA_LEADER_NAME,			// ������				varchar32
	SYNDICATE_DATA_CREATOR_ID,			// ������id				uint
	SYNDICATE_DATA_CREATOR_NAME,		// ��������				varchar32
	SYNDICATE_DATA_CREATE_TIME,			// ����ʱ��				uint
	SYNDICATE_DATA_LEVEL,				// �ȼ�					uint
	SYNDICATE_DATA_ACTIVITY,			// ��Ծ					bigint
	SYNDICATE_DATA_ACTIVITY0_VAULE,		// ��Ծ��ֵ-ͳ��ֵ0		bigint
	SYNDICATE_DATA_ACTIVITY0_DATE,		// ��Ծ������-ͳ��ֵ0	uint
	SYNDICATE_DATA_ACTIVITY1_VAULE,		// ��Ծ��ֵ-ͳ��ֵ1		bigint
	SYNDICATE_DATA_ACTIVITY1_DATE,		// ��Ծ������-ͳ��ֵ1	uint
	SYNDICATE_DATA_ACTIVITY2_VAULE,		// ��Ծ��ֵ-ͳ��ֵ2		bigint
	SYNDICATE_DATA_ACTIVITY2_DATE,		// ��Ծ������-ͳ��ֵ2	uint
	SYNDICATE_DATA_JOIN_LEV_LIMIT,		// ����ȼ�����			uint
	SYNDICATE_DATA_JOIN_APPLY,			// ����������			uint
	SYNDICATE_DATA_ICON,				// ����ͼ��				uint
	SYNDICATE_DATA_JUMP_THE_QUEUE,		// ��ӱ��				uint
	SYNDICATE_DATA_AWARD_SEND_TIME,		// ս��Ʒ����ʱ��		uint
	SYNDICATE_DATA_GIFTBOX_LEV,			// ��еȼ�				uint
	SYNDICATE_DATA_GIFTBOX_EXP,			// ��о���				uint
	SYNDICATE_DATA_MONTHCARD_ID,		// �����¿�ID			uint
	SYNDICATE_DATA_MONTHCARD_ENDTIME,	// �����¿�����ʱ��		uint
};

static const char* GAME_DB_NAME_SYNDICATE_MEMBER = "syn_member";	// ���ɳ�Ա��
enum SYNDICATE_MEMBER_DATA
{
	SYNDICATE_MEMBER_DATA_USER_ID = 0,			// ���id				uint
	SYNDICATE_MEMBER_DATA_SYNDICATE_ID,			// ����id				uint
	SYNDICATE_MEMBER_DATA_SERVER_GROUP,			// ��������				uint
	SYNDICATE_MEMBER_DATA_RANK,					// ����ְλ				uint
	SYNDICATE_MEMBER_DATA_JOIN_TIME,			// ����ʱ��				uint
	SYNDICATE_MEMBER_DATA_ACTIVITY,				// ��Ծ					bigint
	SYNDICATE_MEMBER_DATA_ACTIVITY0_VALUE,		// ��Ծ��ֵ-ͳ��ֵ0		bigint
	SYNDICATE_MEMBER_DATA_ACTIVITY0_DATE,		// ��Ծ������-ͳ��ֵ0	uint
	SYNDICATE_MEMBER_DATA_ACTIVITY1_VALUE,		// ��Ծ��ֵ-ͳ��ֵ1		bigint
	SYNDICATE_MEMBER_DATA_ACTIVITY1_DATE,		// ��Ծ������-ͳ��ֵ1	uint
	SYNDICATE_MEMBER_DATA_ACTIVITY2_VALUE,		// ��Ծ��ֵ-ͳ��ֵ2		bigint
	SYNDICATE_MEMBER_DATA_ACTIVITY2_DATE,		// ��Ծ������-ͳ��ֵ2	uint
	SYNDICATE_MEMBER_DATA_PROF,					// �ﹱ					uint
	SYNDICATE_MEMBER_DATA_LEV,					// ����ȼ�				uint
	SYNDICATE_MEMBER_DATA_LOOKFACE,				// ͷ��					uint
	SYNDICATE_MEMBER_DATA_LOOKFACEFRAME,		// ͷ���				uint
	SYNDICATE_MEMBER_DATA_NAME,					// ����					varchar32
	SYNDICATE_MEMBER_DATA_LOGOUT_TIME,			// �ǳ�ʱ��				uint
	SYNDICATE_MEMBER_DATA_TERRITORY_MONEY,		// �ۻ�����ر�			uint
	SYNDICATE_MEMBER_DATA_WARROAD_TEAM0_COUNT,	// �Ŷ�ս����ս����0	uint
	SYNDICATE_MEMBER_DATA_WARROAD_TEAM1_COUNT,	// �Ŷ�ս����ս����1	uint
	SYNDICATE_MEMBER_DATA_WARROAD_TEAM2_COUNT,	// �Ŷ�ս����ս����2	uint
	SYNDICATE_MEMBER_DATA_END,
};

static const char* GAME_DB_NAME_SYNDICATE_MEMBER_APPLY = "syn_member_apply";	// ���ɳ�Ա�����
enum SYNDICATE_MEMBER_APPLY_DATA
{
	SYNDICATE_MEMBER_APPLY_DATA_ID	= 0,		// ��������		bigint
	SYNDICATE_MEMBER_APPLY_DATA_USERID,			// ���id		uint
	SYNDICATE_MEMBER_APPLY_DATA_SYNID,			// ����id		uint
	SYNDICATE_MEMBER_APPLY_DATA_SERVER_GROUP,	// ��������		uint
	SYNDICATE_MEMBER_APPLY_DATA_LEV,			// ��ɫ�ȼ�		uint
	SYNDICATE_MEMBER_APPLY_DATA_LOOKFACE,		// ��ɫͷ��		uint
	SYNDICATE_MEMBER_APPLY_DATA_LOOKFACEFRAME,	// ��ɫͷ���	uint
	SYNDICATE_MEMBER_APPLY_DATA_NAME,			// ��ɫ����		varchar32
	SYNDICATE_MEMBER_APPLY_DATA_TIME,			// ����ʱ��		uint
};

static const char* GAME_DB_NAME_FRIEND = "friend";
enum FRIEND
{
	FRIEND_DATA_USER_ID = 0,					// ���id		uint
	FRIEND_DATA_FRIEND_ID,						// ����id		uint
	FRIEND_DATA_FRIENDSHIP_POINT,				// �Ѻö�		uint
	FRIEND_DATA_GIFT,							// ����״̬		uint
	FRIEND_DATA_LAST_GOTTIME,					// �ϴ���ȡʱ��	uint
};

static const char* GAME_DB_NAME_FRIEND_REQUEST = "friend_request";
enum FRIEND_REQUEST
{
	FRIEND_REQUEST_DATA_USER_ID = 0,			// ���id	uint
	FRIEND_REQUEST_DATA_REQUESTER_ID,			// ������id uint
	FRIEND_REQUEST_DATA_REQUEST_TIME,			// ����ʱ�� uint
};

static const char* GAME_DB_NAME_ITEM = "item";	// ��Ʒ��
enum ITEM_DATA
{
	ITEM_DATA_ID	= 0,		// ��Ʒid		bigint
	ITEM_DATA_TYPE,				// ��Ʒ����		uint
	ITEM_DATA_PLAYER_ID,		// ������id		uint
	ITEM_DATA_AMOUNT,			// ����			uint
	ITEM_DATA_LIFE_TIME,		// ����ʱ��		uint
	ITEM_DATA_END,
};

static const char* GAME_DB_NAME_SHOP_GOODS = "shop_goods"; // �̵�����
enum SHOP_GOODS
{
	SHOP_GOODS_BEGIN= 0,
	SHOP_GOODS_ID	= 0,		// ������ID		uint
	SHOP_GOODS_ITEM_TYPE,		// ��Ʒ����		uint
	SHOP_GOODS_OWNER_ID,		// �������ID	uint
	SHOP_GOODS_SHOP_TYPE,		// �����̵�		uint
	SHOP_GOODS_ITEM_INDEX,		// ��Ʒλ��		uint
	SHOP_GOODS_CUR_NUM,			// ��ǰʣ������ uint
	SHOP_GOODS_MONEY_TYPE,		// ��������		uint
	SHOP_GOODS_PRICE,			// ��Ʒ����		uint
	SHOP_GOODS_NUM,				// ��Ʒ����		uint
	SHOP_GOODS_DISCOUNT,		// ��Ʒ�ۿ�		uint
	SHOP_GOODS_END,
};


static const char* GAME_DB_NAME_USER_ACHIEVEMENT = "user_achievement";	// ��ҳɾ�
enum USER_ACHIEVEMENT
{
	USER_ACHIEVEMENT_USERID = 0,				// ���id			uint
	USER_ACHIEVEMENT_CHIEVEMENTID,				// ���ڽ��еĳɾ�id	uint
	USER_ACHIEVEMENT_PROCESS,					// ����				uint
	USER_ACHIEVEMENT_GOAL,						// Ŀ��				int
};

static const char* GAME_DB_NAME_BATTLE_SAVE = "battle_save";	// ս���浵
enum BATTLE_SAVE_DATA
{
	BATTLE_SAVE_DATA_ID = 0,			// ս��id		bigint
	BATTLE_SAVE_DATA_TYPE,				// ս������		uint
	BATTLE_SAVE_DATA_ROUND,				// �ִ�			uint
	BATTLE_SAVE_DATA_MONSTER1_HP,		// ����1Ѫ��	uint
	BATTLE_SAVE_DATA_MONSTER1_SP,		// ����1��ŭ	uint
	BATTLE_SAVE_DATA_MONSTER2_HP,		// ����2Ѫ��	uint
	BATTLE_SAVE_DATA_MONSTER2_SP,		// ����2��ŭ	uint
	BATTLE_SAVE_DATA_MONSTER3_HP,		// ����3Ѫ��	uint
	BATTLE_SAVE_DATA_MONSTER3_SP,		// ����3��ŭ	uint
	BATTLE_SAVE_DATA_MONSTER4_HP,		// ����4Ѫ��	uint
	BATTLE_SAVE_DATA_MONSTER4_SP,		// ����4��ŭ	uint
	BATTLE_SAVE_DATA_MONSTER5_HP,		// ����5Ѫ��	uint
	BATTLE_SAVE_DATA_MONSTER5_SP,		// ����5��ŭ	uint
};

static const char* GAME_DB_NAME_CHALLENGE_BOSS = "challenge_boss";	// ��սboss�����
enum CHALLENGE_BOSS
{
	CHALLENGE_BOSS_ID = 0,				// ���						bigint
	CHALLENGE_BOSS_USER_ID,				// ���ID					uint
	CHALLENGE_BOSS_BOSS_TYPE,			// boss����					uint
	CHALLENGE_BOSS_DEGREE,				// �Ѷ�						uint
	CHALLENGE_BOSS_EVALUATE,			// ��ս���(0:ʧ��; 1,2,3��)uint
};

static const char* GAME_DB_NAME_TOPLIST_USER_ATTR = "toplist_user_attr";	//	���������������
enum TOPLIST_USER_ATTR
{
	TOPLIST_USER_ATTR_USER_ID = 0,		// ���id			uint
	TOPLIST_USER_ATTR_TYPE,				// ���а�����ö��ֵ	uint
	TOPLIST_USER_ATTR_DATA,				// ����ʹ�õ�����	uint
	TOPLIST_USER_ATTR_RANK,				// ��������			uint	
	TOPLIST_USER_ATTR_LAST_RANK,		// ��������			uint
	TOPLIST_USER_ATTR_SERVER_GROUP,		// ��������id		uint
};

static const char* GAME_DB_NAME_TOPLIST_SYNDICATE = "toplist_syndicate";	// ���а񹫻�������
enum TOPLIST_SYNDICATE
{
	TOPLIST_SYNDICATE_ID = 0,			// ����id			uint
	TOPLIST_SYNDICATE_TYPE,				// ���а�����ö��ֵ	uint
	TOPLIST_SYNDICATE_DATA,				// ����ʹ�õ�����	uint
	TOPLIST_SYNDICATE_SERVER_GROUP,		// ��������id		uint
};

static const char* GAME_DB_NAME_DELAYACTION = "delayaction";	// �ӳ�ִ��action��¼��
enum DELAYACTION_DATA
{
	DELAYACTION_DATA_ID = 0,			// ���						bigint
	DELAYACTION_DATA_ACTION_ID,			// ִ��action				uint
	DELAYACTION_DATA_USER_ID,			// ���ID					uint
	DELAYACTION_DATA_EXECUTECOUNT,		// ִ�д���					uint
	DELAYACTION_DATA_EXECUTETIME,		// ִ��ʱ��					uint
	DELAYACTION_DATA_INVALIDTIME,		// ʧЧʱ��					uint
	DELAYACTION_DATA_SERVER_GROUP,		// ��������					uint
	DELAYACTION_DATA_SERVER_LINE,		// ��������·				uint
	DELAYACTION_DATA_PARAM1,			// ����1					uint
	DELAYACTION_DATA_PARAM2,			// ����2					uint
	DELAYACTION_DATA_PARAM3,			// ����3					uint
	DELAYACTION_DATA_PARAM4,			// ����4					uint
	DELAYACTION_DATA_PARAM5,			// ����5					uint
};


static const char* GAME_DB_NAME_GOOSE_TOWER = "goose_tower";	// ������������ݱ�
enum GOOSE_TOWER_DATA
{
	GOOSE_TOWER_DATA_ID = 0,					// id								bigint
	GOOSE_TOWER_DATA_USER_ID,					// ���id							uint
	GOOSE_TOWER_DATA_FLOOR,						// ����								uint
	GOOSE_TOWER_DATA_DEF_USER_ID,				// ����С�����id					uint
	GOOSE_TOWER_DATA_DEF_USER_NAME,				// ����С�������					varchar32
	GOOSE_TOWER_DATA_DEF_USER_LEV,				// ����С����ҵȼ�					uint
	GOOSE_TOWER_DATA_DEF_USER_LOOKFACE,			// ����С�����ͷ��					uint
	GOOSE_TOWER_DATA_DEF_USER_LOOKFACE_FRAME,	// ����С�����ͷ���				uint
	GOOSE_TOWER_DATA_POKER_ID1,					// ����ID1							bigint
	GOOSE_TOWER_DATA_POKER_ID2,					// ����ID2							bigint
	GOOSE_TOWER_DATA_POKER_ID3,					// ����ID3							bigint
	GOOSE_TOWER_DATA_POKER_ID4,					// ����ID4							bigint
	GOOSE_TOWER_DATA_POKER_ID5,					// ����ID5							bigint
	GOOSE_TOWER_DATA_GAIN_AWARD,				// ������ȡ���(0:û����ȡ, 1:��ȡ)	uint
	GOOSE_TOWER_DATA_BATTLE_SAVE_ID,			// ս������ID						bigint
};

static const char* GAME_DB_NAME_GOOSE_FIGHT_POKER = "goose_fight_poker";	// ��������ʷ�����Ƽ�¼��
enum GOOSE_FIGHT_POKER
{
	GOOSE_FIGHT_POKER_ID = 0,			// id			uint
	GOOSE_FIGHT_POKER_USER_ID,			// ���id		uint
	GOOSE_FIGHT_POKER_POKER_ID,			// ��������ID	bigint
	GOOSE_FIGHT_POKER_HP,				// ���Ѫ��		uint
	GOOSE_FIGHT_POKER_LEFT_HP,			// ʣ��Ѫ��		uint
	GOOSE_FIGHT_POKER_SP,				// ����ŭ		uint
	GOOSE_FIGHT_POKER_LEFT_SP,			// ʣ���ŭ		uint
};

// ��poker����ͬһ��ö��
static const char* GAME_DB_NAME_GOOSE_DEFENSE_POKER = "goose_defense_poker";		// ����������С�ӿ��Ʊ�


static const char* GAME_DB_NAME_PUZZLE_BUFF = "puzzle_buff";	// �Թ�BUFF��
enum PUZZLE_BUFF_DATA
{
	PUZZLE_BUFF_DATA_ID = 0,			// ���						uint
	PUZZLE_BUFF_DATA_USER_ID,			// ���ID					uint
	PUZZLE_BUFF_DATA_BUFF_TYPE,			// BUFF����					uint
	PUZZLE_BUFF_DATA_INS_TYPE,			// ��������					uint
	PUZZLE_BUFF_DATA_INS_DIFFICULE,		// �����Ѷ�					uint
	PUZZLE_BUFF_DATA_INS_FLOOR,			// �������					uint
	PUZZLE_BUFF_DATA_FIGHT_NO,			// ս�����к�				uint
	PUZZLE_BUFF_DATA_DATE,				// ��������(��)				uint
};
static const char* GAME_DB_NAME_ARENA = "arena";			// ���Ӿ�����������
enum ARENA_DATA
{
	ARENA_DATA_USERID,					// ���id					uint
	ARENA_DATA_RANK = 0,				// ����						uint
	ARENA_DATA_TOTALWINCOUNT,			// �ܼ�ʤ����				uint
	ARENA_SERVER_GROUP,					// ��������					uint
};

static const char* GAME_DB_NAME_ARENA_LOG = "arena_log";			// ������ս����־
enum ARENA_LOG_DATA
{
	ARENA_LOG_DATA_ARENA_TYPE = 0,		// ���������1���ˣ�2���ˣ�	uint
	ARENA_LOG_DATA_USERID,				// ���id						uint
	ARENA_LOG_DATA_RESULT,				// ս�����						uint
	ARENA_LOG_DATA_RANKCHANGE,			// �����仯						uint
	ARENA_LOG_DATA_TARGETID,			// Ŀ��id						uint
	ARENA_LOG_DATA_TIME,				// ս��ʱ��						uint
	ARENA_LOG_DATA_VIDEO,				// ¼��							varchar
	ARENA_LOG_DATA_SERVER_GROUP,		// ��������						uint
};

static const char* GAME_DB_NAME_ARENA_MULTI = "arena_multi";		//  ��Ӿ���������
enum MULTI_ARENA_DATA
{
	MULTI_ARENA_DATA_USERID = 0,		// ���id						uint
	MULTI_ARENA_DATA_RANK,				// ����							uint
	MULTI_ARENA_DATA_TOTALWINCOUNT,		// �ܼ�ʤ����					uint
	MULTI_ARENA_DATA_ARENA_MONEY,		// �ۻ�δ��ȡ�ľ�������			uint	
	MULTI_ARENA_DATA_SERVER_GROUP,		// ��������						uint
};

static const char* GAME_DB_NAME_ARENA_POKER_TEAM = "arena_poker_team";	// ��������ҿ��ƶ�������
enum ARENA_POKER_TEAM_DATA
{
	ARENA_POKER_TEAM_DATA_ID = 0,		// ������id						uint
	ARENA_POKER_TEAM_DATA_USERID ,		// ���id						uint
	ARENA_POKER_TEAM_DATA_TEAMTYPE,		// ��������						uint
	ARENA_POKER_TEAM_DATA_POKERID1,		// 1�ſ���id					uint
	ARENA_POKER_TEAM_DATA_POKERID2,		// 2�ſ���id					uint
	ARENA_POKER_TEAM_DATA_POKERID3,		// 3�ſ���id					uint
	ARENA_POKER_TEAM_DATA_POKERID4,		// 4�ſ���id					uint
	ARENA_POKER_TEAM_DATA_POKERID5,		// 5�ſ���id					uint
	ARENA_POKER_TEAM_DATA_TOTAL_FC,		// ������ս����					uint
	ARENA_POKER_TEAM_DATA_END,
};

static const char* GAME_DB_NAME_ARENA_AI = "arena_ai";	// �����������˱�
enum ARENA_AI_DATA
{
	ARENA_AI_DATA_ID = 0,				// id		uint
	ARENA_AI_DATA_NAME,					// ����		varchar
	ARENA_AI_DATA_SERVER_GROUP,			// ��������	uint
};

static const char* GAME_DB_NAME_SYN_LOG	= "syn_log";	// ������־��
enum SYN_LOG_DATA
{
	SYN_LOG_DATA_ID = 0,			// ID				bigint
	SYN_LOG_DATA_SYN_ID,			// ����ID   		uint
	SYN_LOG_DATA_TYPE,				// ��־���� 		uint
	SYN_LOG_DATA_CREATE_USER_ID,	// ��־������ID		uint
	SYN_LOG_DATA_CREATE_TIME,		// ��־����ʱ��		uint
	SYN_LOG_DATA_CONTENT,			// ��־����			varchar256
};

static const char* GAME_DB_NAME_MINE	= "mine";	// �󶴱�
enum MINE_DATA
{
	MINE_DATA_ID	= 0,				// ��ID						uint
	MINE_DATA_OWNER_ID,					// ����ID						uint
	MINE_DATA_TYPE,						// ������						uint
	MINE_DATA_SCALE,					// ���ģ						uint
	MINE_DATA_CREATE_TIME,				// ����ʱ��						uint
	MINE_DATA_IS_END,					// �Ƿ����						uint
	MINE_DATA_BE_ATK_COUNT,				// ����������					uint
	MINE_DATA_SERVER_GROUP,				// ��������						uint
};

static const char* GAME_DB_NAME_MINE_MEMBER = "mine_member"; // �󶴳�Ա��
enum MINE_MEMBER_DATA
{
	MINE_MEMBER_DATA_ID		= 0,		// ������ID						bigint
	MINE_MEMBER_DATA_USER_ID,			// ���ID						uint
	MINE_MEMBER_DATA_MINE_ID,			// ��ID						uint
	MINE_MEMBER_DATA_LEV,				// �ȼ�							uint
	MINE_MEMBER_DATA_LOOK_FACE,			// ͷ��							uint
	MINE_MEMBER_DATA_LOOK_FACE_FRAME,	// ͷ���						uint
	MINE_MEMBER_DATA_NAME,				// ��ɫ��						varchar32
	MINE_MEMBER_DATA_POKER1,			// ��ս��1						bigint
	MINE_MEMBER_DATA_POKER2,			// ��ս��2						bigint
	MINE_MEMBER_DATA_POKER3,			// ��ս��3						bigint
	MINE_MEMBER_DATA_POKER4,			// ��ս��4						bigint
	MINE_MEMBER_DATA_POKER5,			// ��ս��5						bigint
	MINE_MEMBER_DATA_JOIN_TIME,			// ����ʱ��						uint
	MINE_MEMBER_DATA_SPEED,				// ��ǰ�����ٶ�(/Сʱ)			uint
	MINE_MEMBER_DATA_BEGIN_TIME,		// ��ǰ���ƿ�ʼ�ɼ�ʱ��			uint
	MINE_MEMBER_DATA_RESOURCE_OLD,		// ������ǰ�ۼ���Դ				uint
	MINE_MEMBER_DATA_RESOURCE_TOTAL,	// ��Դ�ۼ�						uint
	MINE_MEMBER_DATA_RESOURCE_LOSE,		// ��Դ��ʧ						uint
	MINE_MEMBER_DATA_VAS_TOTAL,			// ��ʯ�ۼ�						uint
	MINE_MEMBER_DATA_IS_POKER_RESET,	// �����Ƿ�����					uint
	MINE_MEMBER_DATA_SERVER_GROUP,		// ��������						uint
};
static const char* GAME_DB_NAME_MERCENARY_POKER = "mercenary_poker";	// Ӷ�����Ʊ� *����һ���ֶ���������poker��ö����ͬ
enum MERCENARY_POKER_DATA
{
	MERCENARY_POKER_DATA_SERVER_GROUP = POKER_DATA_SKILL_JOINT_LEV + 1,	// ��������					uint
};

static const char* GAME_DB_NAME_MERCENARY_CAMP = "mercenary_camp";		// Ӷ��Ӫ��
enum MERCENARY_CAMP_DATA
{
	MERCENARY_CAMP_DATA_MERCENARY_ID,	// Ӷ��ID					bigint
	MERCENARY_CAMP_DATA_OWNER_ID,		// Ӷ������ID				uint
	MERCENARY_CAMP_DATA_EMPLOY_COUNT,	// ����Ӷ����				uint
	MERCENARY_CAMP_DATA_ENTER_TIME,		// ��ǲʱ��					uint
	MERCENARY_CAMP_DATA_SYNDICATE_ID,	// ����ID					uint
	MERCENARY_CAMP_DATA_SERVER_GROUP,	// ��������					uint
	MERCENARY_CAMP_DATA_MERCENARY_SCORE,// Ӷ��ս����				uint
};

static const char* GAME_DB_NAME_MERCENARY_FIGHT = "mercenary_fight";	// Ӷ��ս����¼��
enum MERCENARY_FIGHT_DATA
{
	MERCENARY_FIGHT_DATA_ID,						// ID					bigint
	MERCENARY_FIGHT_DATA_USER_ID,					// ���ID				uint
	MERCENARY_FIGHT_DATA_MERCENARY_ID,				// Ӷ��ID				bigint
	MERCENARY_FIGHT_DATA_MERCENARY_TYPE,			// Ӷ������				uint
	MERCENARY_FIGHT_DATA_MERCENARY_OWNER_ID,		// Ӷ������id			uint
	MERCENARY_FIGHT_DATA_MERCENARY_LEV,				// Ӷ���ȼ�				uint
	MERCENARY_FIGHT_DATA_MERCENARY_EXP,				// Ӷ������				bigint
	MERCENARY_FIGHT_DATA_MERCENARY_COLOR,			// Ӷ����ɫ				uint
	MERCENARY_FIGHT_DATA_MERCENARY_STAR,			// Ӷ���Ǽ�				uint
	MERCENARY_FIGHT_DATA_MERCENARY_EQUIP1_TYPE,		// Ӷ����������			uint
	MERCENARY_FIGHT_DATA_MERCENARY_EQUIP1_STAR,		// Ӷ�������Ǽ�			uint
	MERCENARY_FIGHT_DATA_MERCENARY_EQUIP1_EXP,		// Ӷ����������			uint
	MERCENARY_FIGHT_DATA_MERCENARY_EQUIP2_TYPE,		// Ӷ��ͷ������			uint
	MERCENARY_FIGHT_DATA_MERCENARY_EQUIP2_STAR,		// Ӷ��ͷ���Ǽ�			uint
	MERCENARY_FIGHT_DATA_MERCENARY_EQUIP2_EXP,		// Ӷ��ͷ������			uint
	MERCENARY_FIGHT_DATA_MERCENARY_EQUIP3_TYPE,		// Ӷ����������			uint
	MERCENARY_FIGHT_DATA_MERCENARY_EQUIP3_STAR,		// Ӷ�������Ǽ�			uint
	MERCENARY_FIGHT_DATA_MERCENARY_EQUIP3_EXP,		// Ӷ����������			uint
	MERCENARY_FIGHT_DATA_MERCENARY_EQUIP4_TYPE,		// Ӷ����������			uint
	MERCENARY_FIGHT_DATA_MERCENARY_EQUIP4_STAR,		// Ӷ�������Ǽ�			uint
	MERCENARY_FIGHT_DATA_MERCENARY_EQUIP4_EXP,		// Ӷ����������			uint
	MERCENARY_FIGHT_DATA_MERCENARY_EQUIP5_TYPE,		// Ӷ���·�����			uint
	MERCENARY_FIGHT_DATA_MERCENARY_EQUIP5_STAR,		// Ӷ���·��Ǽ�			uint
	MERCENARY_FIGHT_DATA_MERCENARY_EQUIP5_EXP,		// Ӷ���·�����			uint
	MERCENARY_FIGHT_DATA_MERCENARY_EQUIP6_TYPE,		// Ӷ��Ь������			uint
	MERCENARY_FIGHT_DATA_MERCENARY_EQUIP6_STAR,		// Ӷ��Ь���Ǽ�			uint
	MERCENARY_FIGHT_DATA_MERCENARY_EQUIP6_EXP,		// Ӷ��Ь�Ӿ���			uint
	MERCENARY_FIGHT_DATA_MERCENARY_SKILL_SP_LEV,	// Ӷ���ؼ��ȼ�			uint
	MERCENARY_FIGHT_DATA_MERCENARY_SKILL_AUTO1_LEV,	// Ӷ���Զ�����1�ȼ�	uint
	MERCENARY_FIGHT_DATA_MERCENARY_SKILL_AUTO2_LEV,	// Ӷ���Զ�����2�ȼ�	uint
	MERCENARY_FIGHT_DATA_MERCENARY_SKILL_AUTO3_LEV,	// Ӷ���Զ�����3�ȼ�	uint
	MERCENARY_FIGHT_DATA_MERCENARY_SKILL_JOINT_LEV,	// Ӷ����Я���ܵȼ�		uint
	MERCENARY_FIGHT_DATA_MERCENARY_SCORE,			// Ӷ��ս��				uint
	MERCENARY_FIGHT_DATA_EMPLOY_TYPE,				// ��Ӷ����				uint
	MERCENARY_FIGHT_DATA_EMPLOY_TIME,				// ��Ӷʱ��				uint
	MERCENARY_FIGHT_DATA_EMPLOY_STATE,				// ��Ӷ״̬(1����ʹ�ã�2���棬3��ȴ)	uint
};

static const char* GAME_DB_NAME_MINE_LOG = "mine_log";					// ����־��
enum MINE_LOG_DATA
{
	MINE_LOG_DATA_ID = 0,				// ������ID					uint
	MINE_LOG_DATA_MINE_ID,				// ��ID					uint
	MINE_LOG_DATA_MINE_TYPE,			// ������					uint
	MINE_LOG_DATA_MINE_SCALE,			// �󶴹�ģ					uint
	MINE_LOG_DATA_DEF_ID,				// ������ID					uint
	MINE_LOG_DATA_DEF_NAME,				// ����������				varchar32
	MINE_LOG_DATA_DEF_LEV,				// �����ߵȼ�				uint
	MINE_LOG_DATA_DEF_LOOKFACE,			// ������ͷ��				uint
	MINE_LOG_DATA_DEF_LOOKFACE_FRAME,	// ������ͷ���				uint
	MINE_LOG_DATA_ATK_ID,				// ������ID					uint
	MINE_LOG_DATA_ATK_NAME,				// ����������				varchar32
	MINE_LOG_DATA_ATK_LEV,				// �����ߵȼ�				uint
	MINE_LOG_DATA_ATK_LOOKFACE,			// ������ͷ��				uint
	MINE_LOG_DATA_ATK_LOOKFACE_FRAME,	// ������ͷ���				uint
	MINE_LOG_DATA_BEGIN_TIME,			// �ӶῪʼʱ��				uint
	MINE_LOG_DATA_END_TIME,				// �Ӷ����ʱ��				uint
	MINE_LOG_DATA_VAS_LOST,				// ��ȡ����ʯ				uint
	MINE_LOG_DATA_RES_LOST,				// ��ȡ����Դ				uint
	MINE_LOG_DATA_POWER_AWARD,			// ר����������				uint
	MINE_LOG_DATA_DEF_RESULT,			// ���ؽ��(0:ʧ�ܣ�1:ʤ��)	uint
	MINE_LOG_DATA_SERVER_GROUP,			// ��������					uint
	MINE_LOG_DATA_BE_ATK_COUNT,			// ����������				uint
};

static const char* GAME_DB_NAME_MINE_LOG_BATTLE = "mine_log_battle";	// ����־ս����
enum MINE_LOG_BATTLE_DATA
{
	MINE_LOG_BATTLE_DATA_ID = 0,		// ս��ID				bigint				
	MINE_LOG_BATTLE_LOG_ID,				// ��־ID				bigint	
	MINE_LOG_BATTLE_DEF_POKER1,			// ���ط�����1			bigint				
	MINE_LOG_BATTLE_DEF_POKER2,			// 						bigint				
	MINE_LOG_BATTLE_DEF_POKER3,			// 						bigint				
	MINE_LOG_BATTLE_DEF_POKER4,			// 						bigint				
	MINE_LOG_BATTLE_DEF_POKER5,			// 						bigint

	MINE_LOG_BATTLE_DEF_RESULT,			// ���ؽ��(0:��, 1:Ӯ)	uint

	MINE_LOG_BATTLE_ATK_POKER1,			// ����������1			bigint				
	MINE_LOG_BATTLE_ATK_POKER2,			// 						bigint				
	MINE_LOG_BATTLE_ATK_POKER3,			// 						bigint				
	MINE_LOG_BATTLE_ATK_POKER4,			// 						bigint				
	MINE_LOG_BATTLE_ATK_POKER5,			// 						bigint
	MINE_LOG_BATTLE_VIDEO_ID,			// ¼���ַ				varchar64				
};

static const char* GAME_DB_NAME_MINE_LOG_POKER = "mine_log_poker";	// ����־��ս���Ʊ�
enum MINE_LOG_POKER_DATA
{
	MINE_LOG_POKER_DATA_ID = 0,			// ID					bigint
	MINE_LOG_POKER_DATA_BATTLE_ID,		// ս��ID				bigint
	MINE_LOG_POKER_DATA_TYPE,			// ����					uint
	MINE_LOG_POKER_DATA_LEV,			// �ȼ�					uint
	MINE_LOG_POKER_DATA_STAR,			// �Ǽ�					uint
	MINE_LOG_POKER_DATA_COLOR,			// ��ɫ					uint
	MINE_LOG_POKER_DATA_HP,				// ���Ѫ��				uint
	MINE_LOG_POKER_DATA_LEFT_HP,		// ʣ��Ѫ��				uint
	MINE_LOG_POKER_DATA_SP,				// ����ŭ				uint
	MINE_LOG_POKER_DATA_LEFT_SP,		// ʣ���ŭ				uint
};


static const char* GAME_DB_NAME_TERRITORY = "territory";				// ��ر�
enum TERRITORY_DATA
{
	TERRITORY_DATA_INDEX = 0,			// primary				uint
	TERRITORY_DATA_ID,					// ���id				uint
	TERRITORY_DATA_OCCUPIER,			// ռ�칫��id			uint
	TERRITORY_DATA_OCCUPY_TIME,			// ռ��ʱ��YYMMDD		uint
	TERRITORY_DATA_OCCUPY_COST,			// ռ���ʱ				uint
	TERRITORY_DATA_FIRST_OCCUPIER,		// ��ռ����id			uint
	TERRITORY_DATA_FIRST_TIME,			// ��սʱ��YYMMDD		uint
	TERRITORY_DATA_FIRST_COST,			// ��ս��ʱ				uint
	TERRITORY_DATA_FAST_OCCUPIER,		// ��칫��id			uint
	TERRITORY_DATA_FAST_TIME,			// ��칫��ʱ��YYMMDD	uint
	TERRITORY_DATA_FAST_COST,			// ���ռ�칫���ʱ		uint
	TERRITORY_DATA_SERVER_GROUP,		// ��������				uint
};

static const char* GAME_DB_NAME_TERRITORY_MEMBER_TROOPS = "territory_member_troops";		// ��ع�����Ҳ��ӱ�
enum TERRITORY_MEMBER_TROOPS_DATA
{
	TERRITORY_MEMBER_TROOPS_DATA_ID,				// ����id				uint
	TERRITORY_MEMBER_TROOPS_DATA_TERRITORY_ID,		// ���id				uint
	TERRITORY_MEMBER_TROOPS_DATA_CAMP,				// ��Ӫ					uint
	TERRITORY_MEMBER_TROOPS_DATA_SYNDICATE_ID,		// ��������id			uint
	TERRITORY_MEMBER_TROOPS_DATA_USER_ID,			// �������id			uint
	TERRITORY_MEMBER_TROOPS_DATA_POKER_COUNT,		// ��ǰ����ʵ�ʿ�����	uint
	TERRITORY_MEMBER_TROOPS_DATA_FIGHTINGCAPACITY,	// ��ǰ������ս����		uint
	TERRITORY_MEMBER_TROOPS_DATA_POKER1_ID,			// ���鿨��1id			uint
	TERRITORY_MEMBER_TROOPS_DATA_POKER2_ID,			// ���鿨��2id			uint
	TERRITORY_MEMBER_TROOPS_DATA_POKER3_ID,			// ���鿨��3id			uint
	TERRITORY_MEMBER_TROOPS_DATA_POKER4_ID,			// ���鿨��4id			uint
	TERRITORY_MEMBER_TROOPS_DATA_POKER5_ID,			// ���鿨��5id			uint
	TERRITORY_MEMBER_TROOPS_DATA_SERVER_GROUP,		// ��������				uint
};

static const char* GAME_DB_NAME_TERRITORY_FIGHT_STATISTICS = "territory_fight_statistics";		// ���սս��ͳ�Ʊ�
enum TERRITORY_FIGHT_STATISTICS
{
	TERRITORY_FIGHT_STATISTICS_DATA_INDEX = 0,			// INDEX				uint
	TERRITORY_FIGHT_STATISTICS_DATA_ID,					// ���id				uint
	TERRITORY_FIGHT_STATISTICS_DATA_ATK_SYN_ID,			// ��������id			uint
	TERRITORY_FIGHT_STATISTICS_DATA_DEF_SYN_ID,			// ���ع���id			uint
	TERRITORY_FIGHT_STATISTICS_DATA_TOTAL_FIGHTED_TIMES,// ��ս��ʱ��			uint
	TERRITORY_FIGHT_STATISTICS_DATA_SERVER_GROUP,		// ��������				uint
};

static const char* GAME_DB_NAME_TERRITORY_FIGHT_LOG		= "territory_fight_log";				// ���սս����־��
enum TERRITORY_FIGHT_LOG
{
	TERRITORY_FIGHT_LOG_DATA_INDEX = 0,					// INDEX							uint
	TERRITORY_FIGHT_LOG_DATA_TERRITORY_ID,				// ���id							uint
	TERRITORY_FIGHT_LOG_DATA_ATK_TROOPS_ID,				// ��������id						I64
	TERRITORY_FIGHT_LOG_DATA_ATK_USER_ID,				// �����������id					uint
	TERRITORY_FIGHT_LOG_DATA_ATK_SYN_ID,				// �������ӹ���id					uint
	TERRITORY_FIGHT_LOG_DATA_DEF_TROOPS_ID,				// ���ز���id						I64
	TERRITORY_FIGHT_LOG_DATA_DEF_USER_ID,				// ���ز������id					uint
	TERRITORY_FIGHT_LOG_DATA_DEF_SYN_ID,				// ���ز��ӹ���id					uint
	TERRITORY_FIGHT_LOG_DATA_TIME,						// ������ս��ʼ��ʱ�䣨��λ�룩	uint
	TERRITORY_FIGHT_LOG_DATA_RESULT,					// ʤ����0����ʤ����1����ʤ����		uint
	TERRITORY_FIGHT_LOG_DATA_DATE,						// ս������							uint
	TERRITORY_FIGHT_LOG_DATA_VIDEO,						// ¼��								varchar128
	TERRITORY_FIGHT_LOG_DATA_SERVER_GROUP,				// ��������							uint
};

static const char* GAME_DB_NAME_TERRITORY_FIGHT_TROOPS = "territory_fight_troops";				// ���ս�Ѳ�ս����״̬��
enum TERRITORY_FIGHT_TROOPS
{
	TERRITORY_FIGHT_TROOPS_DATA_INDEX = 0,				// INDEX							uint
	TERRITORY_FIGHT_TROOPS_DATA_TERRITORY_ID,			// ���id							uint
	TERRITORY_FIGHT_TROOPS_DATA_TROOPS_ID,				// ����id							I64
	TERRITORY_FIGHT_TROOPS_DATA_SYN_ID,					// ������������id					uint
	TERRITORY_FIGHT_TROOPS_DATA_OPPONENT_SYN_ID,		// ������������id					uint
	TERRITORY_FIGHT_TROOPS_DATA_STATUS,					// ״̬��0������1��ʤ��				uint
	TERRITORY_FIGHT_TROOPS_DATA_POKER1_HP,				// ����1��ǰѪ��					uint
	TERRITORY_FIGHT_TROOPS_DATA_POKER1_SP,				// ����1��ǰ��ŭ					uint
	TERRITORY_FIGHT_TROOPS_DATA_POKER2_HP,				// ����2��ǰѪ��					uint
	TERRITORY_FIGHT_TROOPS_DATA_POKER2_SP,				// ����2��ǰ��ŭ					uint
	TERRITORY_FIGHT_TROOPS_DATA_POKER3_HP,				// ����3��ǰѪ��					uint
	TERRITORY_FIGHT_TROOPS_DATA_POKER3_SP,				// ����3��ǰ��ŭ					uint
	TERRITORY_FIGHT_TROOPS_DATA_POKER4_HP,				// ����4��ǰѪ��					uint
	TERRITORY_FIGHT_TROOPS_DATA_POKER4_SP,				// ����4��ǰ��ŭ					uint
	TERRITORY_FIGHT_TROOPS_DATA_POKER5_HP,				// ����5��ǰѪ��					uint
	TERRITORY_FIGHT_TROOPS_DATA_POKER5_SP,				// ����5��ǰ��ŭ					uint
};

static const char* GAME_DB_NAME_USER_WAR_ROAD	= "user_war_road";			// ���ս�ۼ�¼��
enum USER_WAR_ROAD_DATA
{
	USER_WAR_ROAD_DATA_ID,					// id						bigint
	USER_WAR_ROAD_DATA_USER_ID,				// ���ID					uint
	USER_WAR_ROAD_DATA_MODE,				// ģʽ						int
	USER_WAR_ROAD_DATA_CHAPTER,				// �½�						int
	USER_WAR_ROAD_DATA_PASS,				// �ؿ�						int
	USER_WAR_ROAD_DATA_STAR,				// �Ǽ�						uint
	USER_WAR_ROAD_DATA_DAY_FIGHT_COUNT,		// ÿ��ս������				uint
	USER_WAR_ROAD_DATA_DAY_RESET_COUNT,		// ÿ�����ô���				uint
	USER_WAR_ROAD_DATA_RECORD_TIME,			// ��¼����					uint
};

static const char* GAME_DB_NAME_WAR_ROAD_FIGHT	= "war_road_fight";			// ս��ս����¼��
enum WAR_ROAD_FIGHT_DATA
{
	WAR_ROAD_FIGHT_DATA_ID = 0,				// ������ID					uint
	WAR_ROAD_FIGHT_DATA_WAR_KEY,			// ս��key��ģʽ*1000000+�½�*1000+�ؿ���	bigint
	WAR_ROAD_FIGHT_DATA_RECORD_TIME,		// ��¼ʱ��					uint
	WAR_ROAD_FIGHT_DATA_REPLYADDRESS,		// ¼���ַ					varchar
	WAR_ROAD_FIGHT_DATA_SERVER_GROUP,		// ��������					uint
};

static const char* GAME_DB_NAME_WAR_ROAD_TEAM_LOG	= "war_road_team_log";	// �Ŷ�ս�ۼ�¼��
enum WAR_ROAD_TEAM_LOG_DATA
{
	WAR_ROAD_TEAM_LOG_DATA_ID = 0,			// ������id					bigint
	WAR_ROAD_TEAM_LOG_DATA_SYNDICATE_ID,	// ����ID					uint
	WAR_ROAD_TEAM_LOG_DATA_CHAPTER,			// �½�						uint
	WAR_ROAD_TEAM_LOG_DATA_SERVER_GROUP,	// ��������					uint
	WAR_ROAD_TEAM_LOG_DATA_OPEN_TIME,		// ����ʱ��					uint
	WAR_ROAD_TEAM_LOG_DATA_COMPLETE,		// �Ƿ���ɹ�				uint
	WAR_ROAD_TEAM_LOG_DATA_COMPLETE_TIME,	// ���ʱ��					uint
	WAR_ROAD_TEAM_LOG_DATA_CHAPTER_DPS,		// �½��˺���				bigint
	WAR_ROAD_TEAM_LOG_DATA_CHAPTER_PROGRESS,// �½ڽ��ȣ��½��˺���/�½ڹ�����Ѫ���� uint
	WAR_ROAD_TEAM_LOG_DATA_PASS_FIGHT,		// ս���ؿ�					uint
	WAR_ROAD_TEAM_LOG_DATA_ROUND_FIGHT,		// ս������					uint
	WAR_ROAD_TEAM_LOG_DATA_MONSTER1_LEFTHP,	// ����1ʣ��Ѫ������(%)		uint
	WAR_ROAD_TEAM_LOG_DATA_MONSTER2_LEFTHP,	// ����2ʣ��Ѫ������(%)		uint
	WAR_ROAD_TEAM_LOG_DATA_MONSTER3_LEFTHP,	// ����3ʣ��Ѫ������(%)		uint
	WAR_ROAD_TEAM_LOG_DATA_MONSTER4_LEFTHP,	// ����4ʣ��Ѫ������(%)		uint
	WAR_ROAD_TEAM_LOG_DATA_MONSTER5_LEFTHP,	// ����5ʣ��Ѫ������(%)		uint
	WAR_ROAD_TEAM_LOG_DATA_PASS_DPS,		// �ؿ��˺���				bigint
	WAR_ROAD_TEAM_LOG_DATA_PASS_PROGRESS,	// �ؿ����ȣ��ؿ��˺���/�ؿ�������Ѫ���� uint
	WAR_ROAD_TEAM_LOG_DATA_USER_ID,			// ��ս���ID				uint
	WAR_ROAD_TEAM_LOG_DATA_FIGHT_STATUS,	// ��ս״̬��1׼����2ս����	uint
	WAR_ROAD_TEAM_LOG_DATA_FIGHT_TIME,		// ��սʱ�䣨׼����ս����	uint
};

static const char* GAME_DB_NAME_WAR_ROAD_TEAM_AWARD	= "war_road_team_award";// �Ŷ�ս��ս��Ʒ�����¼��
enum WAR_ROAD_TEAM_AWARD_DATA
{
	WAR_ROAD_TEAM_AWARD_DATA_ID = 0,		// ������id					bigint
	WAR_ROAD_TEAM_AWARD_DATA_SYNDICATE_ID,	// ����ID					uint
	WAR_ROAD_TEAM_AWARD_DATA_CHAPTER,		// �½�						uint
	WAR_ROAD_TEAM_AWARD_DATA_AWARD_TYPE,	// ս��Ʒ����				uint
	WAR_ROAD_TEAM_AWARD_DATA_USER_ID,		// �������ID				uint
	WAR_ROAD_TEAM_AWARD_DATA_APPLY_TIME,	// ����ʱ��					uint
	WAR_ROAD_TEAM_AWARD_DATA_CUT_TIME,		// ���ʱ��					uint
	WAR_ROAD_TEAM_AWARD_DATA_SERVER_GROUP,	// ��������					uint
};

static const char* GAME_DB_NAME_WAR_ROAD_TEAM_AWARD_HISTORY	= "war_road_team_award_history";// �Ŷ�ս��ս��Ʒ��ʷ��¼��
enum WAR_ROAD_TEAM_AWARD_HISTORY_DATA
{
	WAR_ROAD_TEAM_AWARD_HISTORY_DATA_ID = 0,		// ������id					bigint
	WAR_ROAD_TEAM_AWARD_HISTORY_DATA_SYNDICATE_ID,	// ����ID					uint
	WAR_ROAD_TEAM_AWARD_HISTORY_DATA_CHAPTER,		// �½�						uint
	WAR_ROAD_TEAM_AWARD_HISTORY_DATA_AWARD_TYPE,	// ս��Ʒ����				uint
	WAR_ROAD_TEAM_AWARD_HISTORY_DATA_AWARD_NUM,		// ս��Ʒ����				uint
	WAR_ROAD_TEAM_AWARD_HISTORY_DATA_USER_ID,		// ������ID				uint
	WAR_ROAD_TEAM_AWARD_HISTORY_DATA_GIVE_TIME,		// ���ʱ�䣨δ����ļ�¼��ʾ�´��Զ�����ʱ�䣩				uint
	WAR_ROAD_TEAM_AWARD_HISTORY_DATA_SENDER_ID,		// ������ID					uint
	WAR_ROAD_TEAM_AWARD_HISTORY_DATA_SERVER_GROUP,	// ��������					uint
};

static const char* GAME_DB_NAME_WAR_ROAD_TEAM_DPS	= "war_road_team_dps";	// �Ŷ�ս���˺���¼��
enum WAR_ROAD_TEAM_DPS_DATA
{
	WAR_ROAD_TEAM_DPS_DATA_ID = 0,			// ������id					bigint
	WAR_ROAD_TEAM_DPS_DATA_LOG_ID,			// log_id					bigint
	WAR_ROAD_TEAM_DPS_DATA_USER_ID,			// ���ID					uint
	WAR_ROAD_TEAM_DPS_DATA_DPS_VALUE,		// dps�˺�ֵ				uint
	WAR_ROAD_TEAM_DPS_DATA_SERVER_GROUP,	// ��������					uint
};

static const char* GAME_DB_NAME_WAR_ROAD_TEAM_DPS_HISTORY = "war_road_team_dps_history";	// �Ŷ�ս���˺���¼��
enum WAR_ROAD_TEAM_DPS_HISTORY_DATA
{
	WAR_ROAD_TEAM_DPS_HISTORY_DATA_ID = 0,				// ������id					bigint
	WAR_ROAD_TEAM_DPS_HISTORY_DATA_CHAPTER,				// �½�						uint
	WAR_ROAD_TEAM_DPS_HISTORY_DATA_USER_ID,				// ���ID(����������һ�������¼)		uint
	WAR_ROAD_TEAM_DPS_HISTORY_DATA_SERVER_GROUP,		// ��������					uint
	WAR_ROAD_TEAM_DPS_HISTORY_DATA_DPS_VALUE,			// dps�˺�ֵ				uint
	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER1_TYPE,			// ��ս��������1			uint
	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER1_LEV,			// ��ս���Ƶȼ�1			uint
	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER1_STAR,			// ��ս�����Ǽ�1			uint
	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER1_COLOR,		// ��ս������ɫ1			uint
	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER2_TYPE,			// ��ս��������2			uint
	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER2_LEV,			// ��ս���Ƶȼ�2			uint
	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER2_STAR,			// ��ս�����Ǽ�2			uint
	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER2_COLOR,		// ��ս������ɫ2			uint
	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER3_TYPE,			// ��ս��������3			uint
	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER3_LEV,			// ��ս���Ƶȼ�3			uint
	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER3_STAR,			// ��ս�����Ǽ�3			uint
	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER3_COLOR,		// ��ս������ɫ3			uint
	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER4_TYPE,			// ��ս��������4			uint
	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER4_LEV,			// ��ս���Ƶȼ�4			uint
	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER4_STAR,			// ��ս�����Ǽ�4			uint
	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER4_COLOR,		// ��ս������ɫ4			uint
	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER5_TYPE,			// ��ս��������5			uint
	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER5_LEV,			// ��ս���Ƶȼ�5			uint
	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER5_STAR,			// ��ս�����Ǽ�5			uint
	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER5_COLOR,		// ��ս������ɫ5			uint
};

static const char* GAME_DB_NAME_GAME_HISTORY_COMPLETE	= "game_history_complete";	// �ɼ������ʷ��¼��
enum GAME_HISTORY_COMPLETE_DATA
{
	GAME_HISTORY_COMPLETE_DATA_ID	= 0,				// ������id					bigint
	GAME_HISTORY_COMPLETE_DATA_SERVER_GROUP,			// ��������					uint
	GAME_HISTORY_COMPLETE_DATA_TYPE,					// �������					uint
	GAME_HISTORY_COMPLETE_DATA_RECORD_ID,				// ��¼ID					uint
	GAME_HISTORY_COMPLETE_DATA_CREATE_TIME,				// ����ʱ��					uint
	GAME_HISTORY_COMPLETE_DATA_PARAM1,					// ����1					uint
	GAME_HISTORY_COMPLETE_DATA_PARAM2,					// ����2					uint
	GAME_HISTORY_COMPLETE_DATA_PARAM3,					// ����3					uint
};

static const char* GAME_DB_NAME_SYN_WORSHIP = "syn_worship";	// ����Ĥ�ݼ�¼��
enum SYN_WORSHIP_DATA
{
	SYN_WORSHIP_DATA_ID = 0,					// ID				bigint
	SYN_WORSHIP_DATA_USER_ID,					// ���ID			uint
	SYN_WORSHIP_DATA_BEWORSHIP_ID,				// ��Ĥ�����ID		uint
	SYN_WORSHIP_DATA_TIME,						// Ĥ������			uint
};

static const char* GAME_DB_NAME_SYN_WORSHIP_AWARD = "syn_worship_award";	// ����Ĥ�ݽ�����
enum SYN_WORSHIP_AWARD_DATA
{
	SYN_WORSHIP_AWARD_ID = 0,					// ID				bigint
	SYN_WORSHIP_AWARD_USER_ID,					// ���ID			uint
	SYN_WORSHIP_AWARD_AWARD_TYPE,				// ��������			uint
	SYN_WORSHIP_AWARD_AWARD_TOTAL,				// �����ۼƺ�		uint
	SYN_WORSHIP_AWARD_SERVER_GROUP,				// ��������			uint
};

static const char* GAME_DB_NAME_MINE_FIGHT_POKER = "mine_fight_poker";	// ��ս�����Ʊ�
enum MINE_FIGHT_POKER
{
	MINE_FIGHT_POKER_ID = 0,			// ID				uint
	MINE_FIGHT_POKER_ATK_USER_ID,		// ���������ID		uint
	MINE_FIGHT_POKER_DEF_USER_ID,		// ���ط����ID		uint
	MINE_FIGHT_POKER_POKER_ID,			// ����ID			bigint
	MINE_FIGHT_POKER_LEFT_HP,			// ʣ��Ѫ��			uint
	MINE_FIGHT_POKER_LEFT_SP,			// ʣ��ŭ��			uint
	MINE_FIGHT_POKER_POKER_CAMP,		// ���ƹ���			uint
};

static const char* GAME_DB_NAME_FRIEND_INVITE = "friend_invite";			//  ���������
enum FRIEND_INVITE
{
	FRIEND_INVITE_ID = 0,				// ID				bigint
	FRIEND_INVITE_INVITER_ID,			// ������ID			uint
	FRIEND_INVITE_BE_INVITER_ID,		// ��������ID		uint
	FRIEND_INVITE_VAS,					// �ۼ�Ԫ��			uint
	FRIEND_INVITE_SERVER_GROUP,			// ��������			uint
};

static const char* GAME_DB_NAME_FRIEND_INVITE_CODE = "friend_invite_code";	//  �����������
enum FRIEND_INVITE_CODE
{
	FRIEND_INVITE_CODE_USER_ID,				// ���ID			uint
	FRIEND_INVITE_CODE_CODE,				// ������			varchar16
};

static const char* GAME_DB_NAME_TALK_WORLD = "talk_world";	// ���������
enum TALK_WORLD_DATA
{
	TALK_WORLD_DATA_ID = 0,								// ������ID				bigint
	TALK_WORLD_DATA_SENDER_ID,							// ������ID				uint
	TALK_WORLD_DATA_SENDER_NAME,						// �����߽�ɫ��			varchar32
	TALK_WORLD_DATA_SENDER_FACE,						// ������ͷ��			uint
	TALK_WORLD_DATA_SENDER_LEV,							// �����ߵȼ�			uint
	TALK_WORLD_DATA_TEXT,								// ��������				varchar256
	TALK_WORLD_DATA_TIME,								// ����ʱ��				uint
	TALK_WORLD_DATA_TYPE,								// ����					uint
	TALK_WORLD_DATA_PARAM1,								// Ԥ��1				uint
	TALK_WORLD_DATA_PARAM2,								// Ԥ��2				uint
	TALK_WORLD_DATA_PARAM3,								// Ԥ��3				uint
	TALK_WORLD_DATA_PARAM4,								// Ԥ��4				uint
	TALK_WORLD_DATA_SERVER_GROUP,						// ��������				uint
};

static const char* GAME_DB_NAME_TALK_SYN = "talk_syn";	// ���������
enum TALK_SYN_DATA
{
	TALK_SYN_DATA_ID = 0,								// ������ID				bigint
	TALK_SYN_DATA_SYN_ID,								// ����ID				bigint
	TALK_SYN_DATA_SENDER_ID,							// ������ID				uint
	TALK_SYN_DATA_SENDER_NAME,							// �����߽�ɫ��			varchar32
	TALK_SYN_DATA_SENDER_FACE,							// ������ͷ��			uint
	TALK_SYN_DATA_SENDER_LEV,							// �����ߵȼ�			uint
	TALK_SYN_DATA_TEXT,									// ��������				varchar256
	TALK_SYN_DATA_TIME,									// ����ʱ��				uint
	TALK_SYN_DATA_TYPE,									// ����					uint
	TALK_SYN_DATA_PARAM1,								// Ԥ��1				uint
	TALK_SYN_DATA_PARAM2,								// Ԥ��2				uint
	TALK_SYN_DATA_PARAM3,								// Ԥ��3				uint
	TALK_SYN_DATA_PARAM4,								// Ԥ��4				uint
	TALK_SYN_DATA_SERVER_GROUP,							// ��������				uint
};

static const char* GAME_DB_NAME_TALK_PRIVATE = "talk_private";	// ˽�ı�
enum TALK_PRIVATE_DATA
{
	TALK_PRIVATE_DATA_ID = 0,								// ������ID				bigint
	TALK_PRIVATE_DATA_USER_ID,								// ������ID				uint
	TALK_PRIVATE_DATA_SENDER_ID,							// ������ID				uint
	TALK_PRIVATE_DATA_SENDER_NAME,							// �����߽�ɫ��			varchar32
	TALK_PRIVATE_DATA_SENDER_FACE,							// ������ͷ��			uint
	TALK_PRIVATE_DATA_SENDER_LEV,							// �����ߵȼ�			uint
	TALK_PRIVATE_DATA_TEXT,									// ��������				varchar256
	TALK_PRIVATE_DATA_TIME,									// ����ʱ��				uint
	TALK_PRIVATE_DATA_TYPE,									// ����					uint
	TALK_PRIVATE_DATA_PARAM1,								// Ԥ��1				uint
	TALK_PRIVATE_DATA_PARAM2,								// Ԥ��2				uint
	TALK_PRIVATE_DATA_PARAM3,								// Ԥ��3				uint
	TALK_PRIVATE_DATA_PARAM4,								// Ԥ��4				uint
	TALK_PRIVATE_DATA_SERVER_GROUP,							// ��������		
};

static const char* GAME_DB_NAME_MINE_COLLECT = "mine_collect";	// �󶴲ɼ���
enum MINE_COLLECT_DATA
{
	MINE_COLLECT_DATA_USER_ID = 0,							// ���ID				uint
	MINE_COLLECT_DATA_NAME,									// ��ҽ�ɫ��			varchar32
	MINE_COLLECT_DATA_LEV,									// ��ҵȼ�				uint
	MINE_COLLECT_DATA_LOOKFACE,								// ���ͷ��				uint
	MINE_COLLECT_DATA_LOOKFACE_FRAME,						// ���ͷ���			uint
	MINE_COLLECT_DATA_ATK_COUNT_TOTAL,						// �����󶴴����ܺ�		uint
	MINE_COLLECT_DATA_MONEY_TOTAL,							// ��ý���ܺ�			uint	
	MINE_COLLECT_DATA_DRUG_TOTAL,							// ���ҩ���ܺ�			uint
	MINE_COLLECT_DATA_ATK_COUNT0_VALUE,						// ��������ֵ0			uint
	MINE_COLLECT_DATA_MONEY0_VALUE,							// ���ֵ0				uint
	MINE_COLLECT_DATA_DRUG0_VALUE,							// ҩ��ֵ0				uint
	MINE_COLLECT_DATA_DATE0,								// ����0				uint
	MINE_COLLECT_DATA_ATK_COUNT1_VALUE,						// ��������ֵ1			uint
	MINE_COLLECT_DATA_MONEY1_VALUE,							// ���ֵ1				uint
	MINE_COLLECT_DATA_DRUG1_VALUE,							// ҩ��ֵ1				uint
	MINE_COLLECT_DATA_DATE1,								// ����1				uint
	MINE_COLLECT_DATA_ATK_COUNT2_VALUE,						// ��������ֵ2			uint
	MINE_COLLECT_DATA_MONEY2_VALUE,							// ���ֵ2				uint
	MINE_COLLECT_DATA_DRUG2_VALUE,							// ҩ��ֵ2				uint
	MINE_COLLECT_DATA_DATE2,								// ����2				uint
	MINE_COLLECT_DATA_ATKCOUNT_RANK_LAST,					// ����������������		uint
	MINE_COLLECT_DATA_MONEY_RANK_LAST,						// ��Ҳɼ���������		uint
	MINE_COLLECT_DATA_DRUG_RANK_LAST,						// ҩ���ɼ���������		uint
	MINE_COLLECT_DATA_SERVER_GROUP,							// ��������				uint
};

static const char* GAME_DB_NAME_SYN_GIFT_BOX_LOG	= "syn_giftbox_log";	// ������м�¼��
enum SYN_GIFT_BOX_LOG_DATA
{
	SYN_GIFT_BOX_LOG_DATA_ID = 0,							// ������ID				bigint
	SYN_GIFT_BOX_LOG_DATA_SYNDICATE_ID,						// ����ID				uint
	SYN_GIFT_BOX_LOG_DATA_BOX_TYPE,							// �������				uint
	SYN_GIFT_BOX_LOG_DATA_INVAILD_TIME,						// ����ʱ��				uint
	SYN_GIFT_BOX_LOG_DATA_GIVE_USER_ID,						// �������ID			uint	
	SYN_GIFT_BOX_LOG_DATA_GIVE_USER_NAME,					// �����������			varchar32
	SYN_GIFT_BOX_LOG_DATA_SERVER_GROUP,						// ��������				uint
};

static const char* GAME_DB_NAME_USER_SYN_GIFTBOX_AWARD	= "user_syn_giftbox_ward";	// ��Ұ��������ȡ��¼��
enum USER_SYN_GIFTBOX_AWARD_DATA
{
	USER_SYN_GIFTBOX_AWARD_DATA_USER_ID = 0,				// ���ID				uint
	USER_SYN_GIFTBOX_AWARD_DATA_SYN_GIFTBOX_ID,				// ������м�¼id		uint
	USER_SYN_GIFTBOX_AWARD_DATA_INVIALDTIME,				// ʧЧʱ��				uint
};

static const char* GAME_DB_NAME_LOOKFACE_FRAME = "lookface_frame";					// ��һ�õ�ͷ������ݱ�
enum USER_LOOKFACE_FRAME
{
	USER_LOOKFACE_FRAME_ID = 0,								// ID					uint
	USER_LOOKFACE_FRAME_USER_ID,							// ���ID				uint
	USER_LOOKFACE_FRAME_FRAME_TYPE,							// ͷ�������			uint
	USER_LOOKFACE_FRAME_END_TIME,							// ����ʱ��				uint
};


static const char* GAME_DB_NAME_CROSS_ROOM = "cs_room";		// ��������
enum CROSS_ROOM_DATA
{
	CROSS_ROOM_DATA_ID = 0,		// id			uint
	CROSS_ROOM_DATA_TYPE,		// ����			uint
	CROSS_ROOM_DATA_LINE,		// ������·		uint
	CROSS_ROOM_DATA_OWNER_ID,	// ӵ����id		uint
	CROSS_ROOM_DATA_CREATE_TIME,// ���䴴��ʱ��	uint
	CROSS_ROOM_DATA_END_TIME,	// ǿ�ƽ�ɢʱ�� uint
	CROSS_ROOM_DATA_DATA1,		// ����1		uint
	CROSS_ROOM_DATA_DATA2,		// ����2		uint
	CROSS_ROOM_DATA_DATA3,		// ����3		uint
	CROSS_ROOM_DATA_DATA4,		// ����4		uint
	CROSS_ROOM_DATA_DATA5,		// ����5		uint
	CROSS_ROOM_DATA_STR1,		// �ִ�1		varchar255
	CROSS_ROOM_DATA_STR2,		// �ִ�2		varchar255
};

static const char* GAME_DB_NAME_CROSS_ROOM_MEMBER = "cs_room_member";	// ��������Ա��
enum CROSS_ROOM_MEMBER_DATA
{
	CROSS_ROOM_MEMBER_DATA_USER_ID = 0,		// ��ɫid		uint
	CROSS_ROOM_MEMBER_DATA_ROOM_ID,			// ����id		uint
	CROSS_ROOM_MEMBER_DATA_DATA1,			// ����1		uint
	CROSS_ROOM_MEMBER_DATA_DATA2,			// ����2		uint
	CROSS_ROOM_MEMBER_DATA_DATA3,			// ����3		uint
};

static const char* GAME_DB_NAME_CROSS_NTM_FIGHT_LOG = "cs_ntm_fight_log";	// ���������ս����¼��
enum CROSS_NTM_FIGHT_LOG_DATA
{
	CROSS_NTM_FIGHT_LOG_DATA_USER_ID = 0,		// ��ɫid	uint
	CROSS_NTM_FIGHT_LOG_DATA_INTEGRAL,			// ����		uint
	CROSS_NTM_FIGHT_LOG_DATA_PASS_TIME,			// ͨ��ʱ��	uint
	CROSS_NTM_FIGHT_LOG_DATA_RANK,				// ����		uint
	CROSS_NTM_FIGHT_LOG_DATA_AWARD_TYPE,		// ��������	uint
	CROSS_NTM_FIGHT_LOG_DATA_AWARD_NUM,			// ��������	uint
};

static const char* GAME_DB_NAME_SYN_BUFF = "syn_buff";		// ����buff��
enum SYN_BUFF_DATA
{
	SYN_BUFF_DATA_ID = 0,						// id		bigint
	SYN_BUFF_DATA_SYNDICATE_ID,					// ����id	uint
	SYN_BUFF_DATA_TYPE,							// buff����	uint
	SYN_BUFF_DATA_POWER,						// buff����	uint
	SYN_BUFF_DATA_END_TIME,						// ����ʱ��	uint
	SYN_BUFF_DATA_ADD_COUNT,					// ���Ӳ���	uint
	SYN_BUFF_DATA_PARAM1,						// ����1	uint
	SYN_BUFF_DATA_PARAM2,						// ����2	uint
	SYN_BUFF_DATA_SERVER_GROUP,					// ��������	uint
};

static const char* GAME_DB_NAME_USER_BUFF = "user_buff";	// �����buff��
enum USER_BUFF_DATA
{
	USER_BUFF_DATA_ID = 0,						// id		bigint
	USER_BUFF_DATA_USER_ID,						// ��ɫid	uint
	USER_BUFF_DATA_TYPE,						// buff����	uint
	USER_BUFF_DATA_POWER,						// buff����	uint
	USER_BUFF_DATA_END_TIME,					// ����ʱ��	uint
	USER_BUFF_DATA_SOURCE_ID,					// ��ԴID	uint
	USER_BUFF_DATA_ADD_COUNT,					// ���Ӳ���	uint
	USER_BUFF_DATA_PARAM1,						// ����1	uint
	USER_BUFF_DATA_PARAM2,						// ����2	uint
};

static const char* GAME_DB_NAME_USER_MARKS_INFO = "user_marksinfo";	// ���������Ϣ��¼��
enum USER_MARKSINFO_DATA
{
	USER_MARKSINFO_DATA_USER_ID,				// ��ɫid	uint
	USER_MARKSINFO_DATA_TYPE,					// ��������	uint
	USER_MARKSINFO_DATA_DATA,					// ��������	uint
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ������
static const char* CONST_DB_NAME_CONFIG = "config";				// �������ñ�
enum CONFIG_DATA
{
	CONFIGDATA_BEGIN = 0,
	CONFIGDATA_TYPE = CONFIGDATA_BEGIN,			// typeid	uint
	CONFIGDATA_DATA1,							// ����1	uint
	CONFIGDATA_DATA2,							// ����2	uint
	CONFIGDATA_DATA3,							// ����3	uint
	CONFIGDATA_DATA4,							// ����4	uint
	CONFIGDATA_DATA5,							// ����5	uint
//	CONFIGDATA_COMMENT,							// ע���ֶ�, �������ڴ�
	CONFIGDATA_END,
};

static const char* CONST_DB_NAME_CONFIG_TEXT = "config_text";	// ���������ı���
enum CONFIG_TEXT_DATA
{
	CONFIG_TEXT_DATA_ID		= 0,	// id
	CONFIG_TEXT_DATA_TEXT	= 1,	// ����������
};

static const char* CONST_DB_NAME_TASK_CONFIG_DATA = "task";		// �������ñ�
enum ETASK_CONFIG_DATA
{
	ETASK_CONFIG_DATA_ID		= 0,	// ���										uint
	ETASK_CONFIG_DATA_TYPE,				// ��������									uint
	ETASK_CONFIG_DATA_STEP,				// ����(����(��1��ʼ������))				uint
	ETASK_CONFIG_DATA_ISCHAIN,			// �Ƿ���������(0:���ǣ�1:��)				uint
	ETASK_CONFIG_DATA_LIMIT_TIME,		// ʱ������( 0:������, >0:����ʱ��(��) )	uint
	ETASK_CONFIG_DATA_NEED_TYPE1,		// ������Ҫ����1							uint
	ETASK_CONFIG_DATA_NEED_NUM1,		// ����1��Ҫ����							uint
	ETASK_CONFIG_DATA_NEED_TYPE2,		// ������Ҫ����2							uint
	ETASK_CONFIG_DATA_NEED_NUM2,		// ����2��Ҫ����							uint
	ETASK_CONFIG_DATA_NEED_TYPE3,		// ������Ҫ����3							uint
	ETASK_CONFIG_DATA_NEED_NUM3,		// ����3��Ҫ����							uint
	ETASK_CONFIG_DATA_RECEIVE_ACTION,	// ��������ű�action						uint
	ETASK_CONFIG_DATA_FINISH_ACTION,	// �������ű�action						uint
	ETASK_CONFIG_DATA_GIVEUP_ACTION,	// ��������ű�action						uint
	ETASK_CONFIG_DATA_NAME,				// ������									varchar128
};


static const char* CONST_DB_NEWCARD_PRIZE = "newcard_prize";	// ���ֿ��������ñ�
enum NEWCARD_PRIZE_DATA
{
	NEWCARD_PRIZE_DATA_ID = 0,		// id		uint
	NEWCARD_PRIZE_DATA_TYPE,		// ������	uint
	NEWCARD_PRIZE_DATA_GIVEMASKID,	// ����ID	uint
	// �����ֶ�Ϊ10������������Ϣ������type uint, �������� uint, �Ƿ�� uint��
	NEWCARD_PRIZE_DATA_ITEMTYPE1,
	NEWCARD_PRIZE_DATA_ITEMCOUNT1,
	NEWCARD_PRIZE_DATA_ITEMTYPE2,
	NEWCARD_PRIZE_DATA_ITEMCOUNT2,
	NEWCARD_PRIZE_DATA_ITEMTYPE3,
	NEWCARD_PRIZE_DATA_ITEMCOUNT3,
	NEWCARD_PRIZE_DATA_ITEMTYPE4,
	NEWCARD_PRIZE_DATA_ITEMCOUNT4,
	NEWCARD_PRIZE_DATA_ITEMTYPE5,
	NEWCARD_PRIZE_DATA_ITEMCOUNT5,
	NEWCARD_PRIZE_DATA_ITEMTYPE6,
	NEWCARD_PRIZE_DATA_ITEMCOUNT6,
	NEWCARD_PRIZE_DATA_ITEMTYPE7,
	NEWCARD_PRIZE_DATA_ITEMCOUNT7,
	NEWCARD_PRIZE_DATA_ITEMTYPE8,
	NEWCARD_PRIZE_DATA_ITEMCOUNT8,
	NEWCARD_PRIZE_DATA_ITEMTYPE9,
	NEWCARD_PRIZE_DATA_ITEMCOUNT9,
	NEWCARD_PRIZE_DATA_ITEMTYPE10,
	NEWCARD_PRIZE_DATA_ITEMCOUNT10,
};

static const char* CONST_DB_NAME_NOTIFY_CONFIG = "notify";		// �������ñ�
enum NOTIFY_CONFIG
{
	NOTIFY_CONFIG_ID = 0,				// ���										bigint
	NOTIFY_CONFIG_CHANNEL,				// Ƶ��										uint
	NOTIFY_CONFIG_TIME_TYPE,			// ʱ������									uint
	NOTIFY_CONFIG_TIME,					// ʱ��										bigint
	NOTIFY_CONFIG_TEXT,					// ��������									varchar255
	NOTIFY_CONFIG_GROUP,				// ��������									uint
};
static const char* CONST_DB_NAME_ACTIVITY_CONFIG = "activities";	// ���
enum ACTIVITY_CONFIG_DATA
{
	ACTIVITY_CONFIG_DATA_BEGIN = 0,
	ACTIVITY_CONFIG_DATA_ID	 = ACTIVITY_CONFIG_DATA_BEGIN,	// ������id				uint
	ACTIVITY_CONFIG_DATA_TYPE,								// typeid				uint
	ACTIVITY_CONFIG_DATA_TIME_TYPE,							// �ʱ�����			uint
	ACTIVITY_CONFIG_DATA_BEGIN_TIME,						// ��ʼʱ��				uint
	ACTIVITY_CONFIG_DATA_END_TIME,							// ����ʱ��				uint
	ACTIVITY_CONFIG_DATA_BEGIN_ACTION,						// ��ʼ�����ű�			uint
	ACTIVITY_CONFIG_DATA_END_ACTION,						// ���������ű�			uint
	ACTIVITY_CONFIG_DATA_ENTER_ACTION,						// �ͻ��˴�������ű�	uint
	ACTIVITY_CONFIG_DATA_EXIT_ACTION,						// �ͻ��˴����˳��ű�	uint
	ACTIVITY_CONFIG_DATA_SERVER_GROUP,						// ��������				uint
	ACTIVITY_CONFIG_DATA_LINE,								// ��·					uint
	ACTIVITY_CONFIG_DATA_PARAM1,							// ���ò���1			uint
	ACTIVITY_CONFIG_DATA_PARAM2,							// ���ò���2			uint
//  ACTIVITY_CONFIG_DATA_COMMENT,							// ע���ֶ�, �������ڴ�
	ACTIVITY_CONFIG_DATA_END,
};


static const char* CONST_DB_ACTION = "action";	// �ű�action��
enum ACTION_DATA
{
	ACTION_DATA_ID = 0,				// id			uint
	ACTION_DATA_FILE_PATH,			// ·��			varchar128
	ACTION_DATA_FUNCTION,			// ����			varchar128
	ACTION_DATA_CLIENT_TRIGGER,		// �ͻ��˴���	uint
};



static const char* CONST_DB_POKER_TYPE = "poker_type";	// �������ͱ�
enum POKER_TYPE_DATA
{
	POKER_TYPE_DATA_ID = 0,			// ��������id				uint
	POKER_TYPE_DATA_NAME,			// ����						varchar32
	POKER_TYPE_DATA_CAMP,			// ��Ӫ		POKER_CAMP		uint
	POKER_TYPE_DATA_FIGHT_POS,		// ս��λ��	POKER_FIGHT_POS	uint
	POKER_TYPE_DATA_POS_SORT,		// վλ����					uint
	POKER_TYPE_DATA_INIT_LIFE,		// ��ʼ����					uint
	POKER_TYPE_DATA_INIT_MANA,		// ��ʼħ��					uint
	POKER_TYPE_DATA_INIT_STR,		// ��ʼ����					uint
	POKER_TYPE_DATA_INIT_STA,		// ��ʼ����					uint
	POKER_TYPE_DATA_INIT_DEX,		// ��ʼ����					uint
	POKER_TYPE_DATA_INIT_HP,		// ��ʼѪ��					uint
	POKER_TYPE_DATA_INIT_ATK,		// ��ʼ�˺�					uint
	POKER_TYPE_DATA_INIT_STAR,		// ��ʼ�Ǽ�					uint
	POKER_TYPE_DATA_SKILL_SP,		// �ؼ�						uint
	POKER_TYPE_DATA_SKILL_AUTO1,	// �Զ�����1				uint
	POKER_TYPE_DATA_SKILL_AUTO2,	// �Զ�����2				uint
	POKER_TYPE_DATA_SKILL_AUTO3,	// �Զ�����3				uint
	POKER_TYPE_DATA_SKILL_JOINT,	// ��Я����					uint
	POKER_TYPE_DATA_ANGER_PARAM,	// ��ŭת��ϵ������ֱȣ�	uint
	POKER_TYPE_DATA_NEED_ITEMTYPE,	// ��Ӧ���ʯ����			uint
};

static const char* CONST_DB_POKER_STAR_GROW = "poker_star_grow";	// �����Ǽ��ɳ���
enum POKER_STAR_GROW_DATA
{
	POKER_STAR_GROW_DATA_TYPE = 0,	// ��������		uint
	POKER_STAR_GROW_DATA_STAR,		// �����Ǽ�		uint
	POKER_STAR_GROW_DATA_LIFE_GROW,	// ���ʳɳ�		uint
	POKER_STAR_GROW_DATA_MANA_GROW,	// ħ���ɳ�		uint
	POKER_STAR_GROW_DATA_STR_GROW,	// �����ɳ�		uint
	POKER_STAR_GROW_DATA_STA_GROW,	// �����ɳ�		uint
	POKER_STAR_GROW_DATA_DEX_GROW,	// ���ݳɳ�		uint
};

static const char* CONST_DB_POKER_EQUIP = "poker_equip";	// ����װ�����ñ�
enum POKER_EQUIP_DATA
{
	POKER_EQUIP_DATA_POKER_TYPE = 0,	// ��������			uint
	POKER_EQUIP_DATA_POKER_COLOR,		// ������ɫ(1-17)	uint
	POKER_EQUIP_DATA_EQUIP1_TYPE,		// ��������			uint
	POKER_EQUIP_DATA_EQUIP2_TYPE,		// ͷ������			uint
	POKER_EQUIP_DATA_EQUIP3_TYPE,		// ��������			uint
	POKER_EQUIP_DATA_EQUIP4_TYPE,		// ��������			uint
	POKER_EQUIP_DATA_EQUIP5_TYPE,		// �·�����			uint
	POKER_EQUIP_DATA_EQUIP6_TYPE,		// Ь������			uint
};

static const char* CONST_DB_POKER_STAR = "poker_star";	// �����Ǽ����ñ�
enum POKER_STAR_DATA
{
	POKER_STAR_DATA_STAR = 0,			// �Ǽ�								uint
	POKER_STAR_DATA_COMPOUND_NEED,		// �ϳ�ʱ�������ʯ����				uint
	POKER_STAR_DATA_RESOLVE_AUTO,		// �Զ��ֽ������ʯ����			uint
	POKER_STAR_DATA_UPGRADE_NEED,		// ������Ҫ���ʯ, ������0			uint
};

static const char* CONST_DB_LEV_EXP = "lev_exp"; // �ȼ������
enum LEV_EXP_DATA
{
	LEV_EXP_DATA_TYPE = 0,		// ���� LEV_EXP_TYPE		uint
	LEV_EXP_DATA_LEV,			// �ȼ�						uint
	LEV_EXP_DATA_EXP,			// ����						bigint
};

static const char* CONST_DB_SIGN_PRIZE = "sign_prize";	// ǩ���������ñ�
enum SIGN_PRIZE_DATA
{
	SIGN_PRIZE_DATA_ID = 0,			// id������������ǩ��1000+������uint
	SIGN_PRIZE_DATA_MUL_PRIZE,		// ��������	uint
	SIGN_PRIZE_DATA_VIP_LEV,		// ����VIP�ȼ�	uint
	// �����ֶ�Ϊ4������������Ϣ������type uint, �������� uint, �Ƿ�� uint��
	SIGN_PRIZE_DATA_ITEMTYPE1,
	SIGN_PRIZE_DATA_ITEMCOUNT1,
	SIGN_PRIZE_DATA_ITEMTYPE2,
	SIGN_PRIZE_DATA_ITEMCOUNT2,
	SIGN_PRIZE_DATA_ITEMTYPE3,
	SIGN_PRIZE_DATA_ITEMCOUNT3,
};

static const char* CONST_DB_AUTO_RELOAD = "auto_reload";	// �Զ��������ñ�
enum AUTO_RELOAD_DATA
{
	AUTO_RELOAD_DATA_TABLE_NAME = 0,	// ����					varchar255
	AUTO_RELOAD_DATA_GROUP,				// �������� ��0��ʾȫ��	uint
	AUTO_RELOAD_DATA_LINE,				// �������� ��0��ʾȫ��	uint
	AUTO_RELOAD_DATA_UTC_TIME,			// ָ��ʱ�� ��0��ʾ��ʱ	uint
};

static const char* CONST_DB_VIP = "vip";		// VIP���ñ�
enum VIP_DATA
{
	VIP_DATA_TYPE	= 0,		// vip����	uint
	VIP_DATA_LEV,				// vip�ȼ�	uint
	VIP_DATA_VALUE,				// Vaule	uint
};

static const char* CONST_DB_NAME_ITEM_TYPE = "item_type";	// ��Ʒ���ͱ�
enum ITEM_TYPE_DATA
{
	ITEM_TYPE_DATA_ID = 0,			// ����			uint
	ITEM_TYPE_DATA_NAME,			// ����			uint
	ITEM_TYPE_DATA_COLOR,			// ��ɫ			uint
	ITEM_TYPE_DATA_AMOUNT_LIMIT,	// ��������		uint
	ITEM_TYPE_DATA_CLASSIIFY,		// ����			uint
	ITEM_TYPE_DATA_SORT,			// ��Ʒ����		uint
	ITEM_TYPE_DATA_DATA1,			// ����1		uint
	ITEM_TYPE_DATA_DATA2,			// ����2		uint
	ITEM_TYPE_DATA_DATA3,			// ����3		uint
	ITEM_TYPE_DATA_ACTION,			// action		uint
	ITEM_TYPE_DATA_MONOPOLY,		// monopoly		uint
	ITEM_TYPE_DATA_SALE_MONEY_TYPE,	// �۳��������� uint
	ITEM_TYPE_DATA_SALE_PRICE,		// �۳��۸�		uint
	ITEM_TYPE_DATA_PEIFANG_ID,		// �䷽ID		uint
	ITEM_TYPE_DATA_LIMIT_LEV,		// ���Ƶȼ�		uint
	ITEM_TYPE_DATA_END,
};

static const char* CONST_DB_NAME_ITEM_COLOR = "item_color";	// ��Ʒ��ɫ���ñ�
enum ITEM_COLOR_DATA
{
	ITEM_COLOR_DATA_COLOR = 0,	// ��ɫ			uint
	ITEM_COLOR_DATA_STAR1,		// 1����������	uint
	ITEM_COLOR_DATA_STAR2,		// 2����������	uint
	ITEM_COLOR_DATA_STAR3,		// 3����������	uint
	ITEM_COLOR_DATA_STAR4,		// 4����������	uint
	ITEM_COLOR_DATA_STAR5,		// 5����������	uint
	ITEM_COLOR_DATA_PRICE,		// ÿ��۸�		uint
};

static const char* CONST_DB_NAME_ITEM_STAR_ATTR = "item_star_attr";	// ��Ʒ�Ǽ�����
enum ITEM_STAR_ATTR_DATA
{
	ITEM_STAR_ATTR_DATA_TYPE = 0,		// ��Ʒ����		uint
	ITEM_STAR_ATTR_DATA_STAR,			// ��Ʒ�Ǽ�		uint
	ITEM_STAR_ATTR_DATA_ATTR_TYPE1,		// ��������1	uint
	ITEM_STAR_ATTR_DATA_ATTR_DATA1,		// ������ֵ1	uint
	ITEM_STAR_ATTR_DATA_ATTR_TYPE2,		// ��������2	uint
	ITEM_STAR_ATTR_DATA_ATTR_DATA2,		// ������ֵ2	uint
	ITEM_STAR_ATTR_DATA_ATTR_TYPE3,		// ��������3	uint
	ITEM_STAR_ATTR_DATA_ATTR_DATA3,		// ������ֵ3	uint
	ITEM_STAR_ATTR_DATA_ATTR_TYPE4,		// ��������4	uint
	ITEM_STAR_ATTR_DATA_ATTR_DATA4,		// ������ֵ4	uint
	ITEM_STAR_ATTR_DATA_ATTR_TYPE5,		// ��������5	uint
	ITEM_STAR_ATTR_DATA_ATTR_DATA5,		// ������ֵ5	uint
};

static const char* CONST_DB_LIVENESS = "liveness";		// ÿ�ջ�Ծ���ñ�
enum ELIVENESS_CONFIG
{
	ELIVENESS_CONFIG_ID = 0,			// ��Ծ��ID					uint		
	ELIVENESS_CONFIG_LevLimit,			// �ȼ�����					uint
	ELIVENESS_CONFIG_VipLimit,			// VIP�ȼ�����				uint
	ELIVENESS_CONFIG_BeginTime,			// ��ʼʱ��					uint
	ELIVENESS_CONFIG_EndTime,			// ����ʱ��					uint
	ELIVENESS_CONFIG_Val,				// ��ɻ�Ծ��õĻ�Ծֵ		uint
	ELIVENESS_CONFIG_NeedType,			// ��Ҫ����					uint
	ELIVENESS_CONFIG_NeedNum,			// ��Ҫ����					uint
	ELIVENESS_CONFIG_AwardAction,		// �������ű�Action			uint
	ELIVENESS_CONFIG_Title,				// ����						varchar32
	ELIVENESS_CONFIG_Content,			// ���� 					varchar64
};

static const char* CONST_DB_SHOP_TYPE = "shop_type";	// �̵��������ñ�
enum SHOP_TYPE
{
	SHOP_TYPE_BEGIN = 0,
	SHOP_TYPE_ID = SHOP_TYPE_BEGIN,		// �̵�����					uint
	SHOP_TYPE_BLANK_LIMIT,				// ��������					uint
	SHOP_TYPE_REFRESH_MONEY_TYPE,		// �ֶ�ˢ������Ļ�������	uint
	SHOP_TYPE_REFRESH_PRICE,			// �ֶ�ˢ�¼۸�				uint
	SHOP_TYPE_AUTO_REFRESH_TIME1,		// �Զ�ˢ��ʱ��1			uint
	SHOP_TYPE_AUTO_REFRESH_TIME2,		// �Զ�ˢ��ʱ��2			uint
	SHOP_TYPE_AUTO_REFRESH_TIME3,		// �Զ�ˢ��ʱ��3			uint
	SHOP_TYPE_AUTO_REFRESH_TIME4,		// �Զ�ˢ��ʱ��4			uint
	SHOP_TYPE_AUTO_REFRESH_TIME5,		// �Զ�ˢ��ʱ��5			uint
	SHOP_TYPE_REFRESH_RULE1,			// ˢ�¹���1				uint
	SHOP_TYPE_REFRESH_RULE2,			// ˢ�¹���2				uint
	SHOP_TYPE_REFRESH_RULE3,			// ˢ�¹���3				uint
	SHOP_TYPE_REFRESH_RULE4,			// ˢ�¹���4				uint
	SHOP_TYPE_REFRESH_RULE5,			// ˢ�¹���5				uint
	SHOP_TYPE_REFRESH_RULE6,			// ˢ�¹���6				uint
	SHOP_TYPE_REFRESH_RULE7,			// ˢ�¹���7				uint
	SHOP_TYPE_REFRESH_RULE8,			// ˢ�¹���8				uint
	SHOP_TYPE_REFRESH_RULE9,			// ˢ�¹���9				uint
	SHOP_TYPE_REFRESH_RULE10,			// ˢ�¹���10				uint
	SHOP_TYPE_REFRESH_RULE11,			// ˢ�¹���11				uint
	SHOP_TYPE_REFRESH_RULE12,			// ˢ�¹���12				uint
	SHOP_TYPE_END,
};

static const char* CONST_DB_SHOP_RULE = "shop_rule";		// �̵�������ñ�
enum SHOP_RULE
{
	SHOP_RULE_BEGIN = 0,
	SHOP_RULE_ID = SHOP_RULE_BEGIN,		// ��������					uint
	SHOP_RULE_ITEM_TYPE,				// ��Ʒ����					uint
	SHOP_RULE_ITEM_NUM,					// ��Ʒ����					uint
	SHOP_RULE_ITEM_PRICE,				// ��Ʒ����					uint
	SHOP_RULE_MONEY_TYPE,				// ��������					uint
	SHOP_RULE_DISCOUNT,					// ��Ʒ�ۿ�					uint
	SHOP_RULE_WEIGHT,					// ��ƷȨ��					uint
	SHOP_RULE_END,
};

static const char* CONST_DB_NAME_ACHIEVEMENT = "achievement";		// �ɾ����ñ�
enum ACHIEVEMENT_DATA
{
	ACHIEVEMENT_DATA_BEGIN			= 0,
	ACHIEVEMENT_DATA_ID				= ACHIEVEMENT_DATA_BEGIN,	// �ɾ�id����λ�������λ��ʾ���	uint
	ACHIEVEMENT_DATA_SUBINDEX,									// ����ɾ����кţ���һ��Ϊ0��		uint
	ACHIEVEMENT_DATA_BEFOREID,									// ǰ�óɾ�id						uint
	ACHIEVEMENT_DATA_AFTERID,									// �����ɾ�id						uint
	ACHIEVEMENT_DATA_ACTIONID,									// �ɾͽ������ýű�action			uint
	ACHIEVEMENT_DATA_OPEN_TYPE,									// �������							uint
	ACHIEVEMENT_DATA_OPEN_CONDITION1,							// ��������1						uint
	ACHIEVEMENT_DATA_OPEN_CONDITION2,							// ��������2						uint
	ACHIEVEMENT_DATA_COMPLETE_CONDITION1,						// �������1						uint
	ACHIEVEMENT_DATA_COMPLETE_CONDITION2,						// �������2						uint
	ACHIEVEMENT_DATA_END,
};

static const char* CONST_DB_NAME_LUA_TEXT = "lua_text";	// �ű����ֱ�
enum LUA_TEXT_DATA
{
	LUA_TEXT_DATA_ID = 0,	// id		uint
	LUA_TEXT_DATA_TEXT,		// ����		varchar512
};

static const char* CONST_DB_NAME_SKILL_TYPE = "skill_type";		// �����������ñ�
enum SKILL_TYPE_DATA
{
	SKILL_TYPE_DATA_ID	= 0,			// ����id			uint
	SKILL_TYPE_DATA_SORT,				// ���ܷ���			uint
	SKILL_TYPE_DATA_NEED_LEV,			// ����ȼ�			uint
	SKILL_TYPE_DATA_COST_MONEY,			// ���ѽ���			uint
	SKILL_TYPE_DATA_COST_POINT,			// ���Ѽ��ܵ�		uint
	SKILL_TYPE_DATA_POWER,				// ����				uint
	SKILL_TYPE_DATA_POWER_ADD,			// ��������			uint
	SKILL_TYPE_DATA_POWER2,				// ����2			uint
	SKILL_TYPE_DATA_POWER2_ADD,			// ����2����		uint
};

static const char* CONST_DB_DROP_RULE = "drop_rule";	// ��������
enum DROP_RULE_DATA
{
	DROP_RULE_DATA_ID		= 0,		// �������id							uint
	DROP_RULE_DATA_TYPE,				// �����������	DROP_RULE_TYPE			uint
	DROP_RULE_DATA_COUNT,				// ����, �������ִ��					uint
	DROP_RULE_DATA_CHANCE,				// �������, ��ֱ�						uint

	DROP_RULE_DATA_GROUP1_TYPE,			// ������1 ����	DROP_RULE_GROUP_TYPE	uint
	DROP_RULE_DATA_GROUP1_COUNT,		// ������1 ����							uint
	DROP_RULE_DATA_GROUP1_WEIGHT,		// ������1 Ȩ��							uint
	DROP_RULE_DATA_GROUP1_GROUP,		// ������1 ��������						uint

	DROP_RULE_DATA_GROUP2_TYPE,			// ������2 ����	DROP_RULE_GROUP_TYPE	uint
	DROP_RULE_DATA_GROUP2_COUNT,		// ������2 ����							uint
	DROP_RULE_DATA_GROUP2_WEIGHT,		// ������2 Ȩ��							uint
	DROP_RULE_DATA_GROUP2_GROUP,		// ������2 ��������						uint

	DROP_RULE_DATA_GROUP3_TYPE,			// ������3 ����	DROP_RULE_GROUP_TYPE	uint
	DROP_RULE_DATA_GROUP3_COUNT,		// ������3 ����							uint
	DROP_RULE_DATA_GROUP3_WEIGHT,		// ������3 Ȩ��							uint
	DROP_RULE_DATA_GROUP3_GROUP,		// ������3 ��������						uint

	DROP_RULE_DATA_GROUP4_TYPE,			// ������4 ����	DROP_RULE_GROUP_TYPE	uint
	DROP_RULE_DATA_GROUP4_COUNT,		// ������4 ����							uint
	DROP_RULE_DATA_GROUP4_WEIGHT,		// ������4 Ȩ��							uint
	DROP_RULE_DATA_GROUP4_GROUP,		// ������4 ��������						uint

	DROP_RULE_DATA_GROUP5_TYPE,			// ������5 ����	DROP_RULE_GROUP_TYPE	uint
	DROP_RULE_DATA_GROUP5_COUNT,		// ������5 ����							uint
	DROP_RULE_DATA_GROUP5_WEIGHT,		// ������5 Ȩ��							uint
	DROP_RULE_DATA_GROUP5_GROUP,		// ������5 ��������						uint

	DROP_RULE_DATA_GROUP6_TYPE,			// ������6 ����	DROP_RULE_GROUP_TYPE	uint
	DROP_RULE_DATA_GROUP6_COUNT,		// ������6 ����							uint
	DROP_RULE_DATA_GROUP6_WEIGHT,		// ������6 Ȩ��							uint
	DROP_RULE_DATA_GROUP6_GROUP,		// ������6 ��������						uint

	DROP_RULE_DATA_GROUP7_TYPE,			// ������7 ����	DROP_RULE_GROUP_TYPE	uint
	DROP_RULE_DATA_GROUP7_COUNT,		// ������7 ����							uint
	DROP_RULE_DATA_GROUP7_WEIGHT,		// ������7 Ȩ��							uint
	DROP_RULE_DATA_GROUP7_GROUP,		// ������7 ��������						uint

	DROP_RULE_DATA_GROUP8_TYPE,			// ������8 ����	DROP_RULE_GROUP_TYPE	uint
	DROP_RULE_DATA_GROUP8_COUNT,		// ������8 ����							uint
	DROP_RULE_DATA_GROUP8_WEIGHT,		// ������8 Ȩ��							uint
	DROP_RULE_DATA_GROUP8_GROUP,		// ������8 ��������						uint
};


static const char* CONST_DB_BATTLE_TYPE = "battle_type";	// ս�����ñ�
enum BATTLE_TYPE_DATA
{
	BATTLE_TYPE_DATA_TYPE = 0,		// ս������					uint
	BATTLE_TYPE_DATA_SORT,			// ���� ��ӦBATTLE_SORT		uint
	BATTLE_TYPE_DATA_NAME,			// ����						varchar32
	BATTLE_TYPE_DATA_ROUND1,		// �ִ�1 id					uint
	BATTLE_TYPE_DATA_ROUND2,		// �ִ�2 id					uint
	BATTLE_TYPE_DATA_ROUND3,		// �ִ�3 id					uint
	BATTLE_TYPE_DATA_DROP_ID,		// ���� id					uint
	BATTLE_TYPE_DATA_WIN_ACTION,	// ʤ��ִ�нű�				uint
	BATTLE_TYPE_DATA_TIME_LIMIT,	// ս��ʱ������				uint
	BATTLE_TYPE_DATA_SAVE_FLAG,		// �浵���					uint
	BATTLE_TYPE_DATA_EXP,			// �ؿ��ܾ���				uint
};

static const char* CONST_DB_BATTLE_ROUND = "battle_round";	// ս���ִα�
enum BATTLE_ROUND_DATA
{
	BATTLE_ROUND_DATA_ID = 0,		// �ִ�id		uint
	BATTLE_ROUND_DATA_MONSTER1_ID,	// ����1 id		uint
	BATTLE_ROUND_DATA_MONSTER2_ID,	// ����2 id		uint
	BATTLE_ROUND_DATA_MONSTER3_ID,	// ����3 id		uint
	BATTLE_ROUND_DATA_MONSTER4_ID,	// ����4 id		uint
	BATTLE_ROUND_DATA_MONSTER5_ID,	// ����5 id		uint
	BATTLE_ROUND_DATA_DROP_ID,		// ����  id		uint
};

static const char* CONST_DB_BATTLE_MONSTER = "battle_monster";	// ս���������ñ�
enum BATTLE_MONSTER_DATA
{
	BATTLE_MONSTER_DATA_TYPE = 0,						// ��������						uint	
	BATTLE_MONSTER_DATA_NAME,							// ��������						varchar32
	BATTLE_MONSTER_DATA_FIGHT_POS,						// ս��λ��, ǰ1, ��2, ��3		uint
	BATTLE_MONSTER_DATA_POS_SORT,						// վλ����						uint
	BATTLE_MONSTER_DATA_LEV,							// �ȼ�							uint
	BATTLE_MONSTER_DATA_STAR,							// �Ǽ�							uint
	BATTLE_MONSTER_DATA_COLOR,							// ��ɫ							uint
	BATTLE_MONSTER_DATA_HP,								// �������� ��Ѫ				uint
	BATTLE_MONSTER_DATA_SP,								// ��������	��ŭ				uint
	BATTLE_MONSTER_DATA_HIT,							// ��������	����				uint
	BATTLE_MONSTER_DATA_ATK,							// ��������	�˺�				uint
	BATTLE_MONSTER_DATA_DEF,							// ��������	����				uint
	BATTLE_MONSTER_DATA_SPD,							// ��������	�ٶ�				uint
	BATTLE_MONSTER_DATA_DODGE,							// ��������	����				uint
	BATTLE_MONSTER_DATA_MAGIC,							// ��������	����				uint
	BATTLE_MONSTER_DATA_HP_RECOVER,						// �������� ��Ѫ�ظ�			uint
	BATTLE_MONSTER_DATA_SP_RECOVER,						// ��������	��ŭ�ظ�			uint
	BATTLE_MONSTER_DATA_PHY_CRIT,						// ��������	�ﱩ				uint
	BATTLE_MONSTER_DATA_MAG_CRIT,						// ��������	����				uint
	BATTLE_MONSTER_DATA_VAMPIRE_LEV,					// ��������	��Ѫ�ȼ�			uint
	BATTLE_MONSTER_DATA_SP_SPEND_DECREASE,				// ��������	��ŭ���Ľ���%		uint
	BATTLE_MONSTER_DATA_CURE_INCREASE,					// ��������	���Ƽ���Ч�����%	uint
	BATTLE_MONSTER_DATA_SKILL_SP_TYPE,					// �ؼ�����						uint
	BATTLE_MONSTER_DATA_SKILL_SP_LEV,					// �ؼ��ȼ�						uint
	BATTLE_MONSTER_DATA_SKILL_AUTO1_TYPE,				// �Զ�����1 ����				uint
	BATTLE_MONSTER_DATA_SKILL_AUTO1_LEV,				// �Զ�����1 �ȼ�				uint
	BATTLE_MONSTER_DATA_SKILL_AUTO2_TYPE,				// �Զ�����2 ����				uint
	BATTLE_MONSTER_DATA_SKILL_AUTO2_LEV,				// �Զ�����2 �ȼ�				uint
	BATTLE_MONSTER_DATA_SKILL_AUTO3_TYPE,				// �Զ�����3 ����				uint
	BATTLE_MONSTER_DATA_SKILL_AUTO3_LEV,				// �Զ�����3 �ȼ�				uint
	BATTLE_MONSTER_DATA_SKILL_SKILL_JOINT_TYPE,			// ��Я���� ����				uint
	BATTLE_MONSTER_DATA_SKILL_SKILL_JOINT_LEV,			// ��Я���� �ȼ�				uint
	BATTLE_MONSTER_DATA_ANGER_PARAM,					// ��ŭת��ϵ��%				uint
	BATTLE_MONSTER_DATA_DROP_ID,						// �������						uint
	BATTLE_MONSTER_DATA_KILL_ACTION,					// ��ɱaction					uint
};

static const char* CONST_DB_NAME_PEIFANG_TYPE = "peifang_type";	// �䷽�������ñ�
enum PEIFANG_TYPE_DATA
{
	PEIFANG_TYPE_DATA_ID = 0,			// �䷽id			uint
	PEIFANG_TYPE_DATA_AWARD_ITEMTYPE,	// �����Ʒ����		uint
	PEIFANG_TYPE_DATA_AWARD_ITEMNUM,	// �����Ʒ����		uint
	PEIFANG_TYPE_DATA_SPEND_ITEMTYPE1,	// ������Ʒ����1	uint
	PEIFANG_TYPE_DATA_SPEND_ITEMNUM1,	// ������Ʒ����1	uint
	PEIFANG_TYPE_DATA_SPEND_ITEMTYPE2,	// ������Ʒ����2	uint
	PEIFANG_TYPE_DATA_SPEND_ITEMNUM2,	// ������Ʒ����2	uint
	PEIFANG_TYPE_DATA_SPEND_ITEMTYPE3,	// ������Ʒ����3	uint
	PEIFANG_TYPE_DATA_SPEND_ITEMNUM3,	// ������Ʒ����3	uint
	PEIFANG_TYPE_DATA_SPEND_ITEMTYPE4,	// ������Ʒ����4	uint
	PEIFANG_TYPE_DATA_SPEND_ITEMNUM4,	// ������Ʒ����4	uint
	PEIFANG_TYPE_DATA_COST_MONEY_TYPE,	// ���Ļ�������		uint
	PEIFANG_TYPE_DATA_COST_PRICE,		// ���ļ�Ǯ			uint
};

static const char* CONST_DB_CHALLENGE_BOSS_CONFIG = "challenge_boss";	// ��սboss���ñ�
enum CHALLENGE_BOSS_CONFIG
{
	CHALLENGE_BOSS_CONFIG_BOSS_TYPE = 0,	// boss����			uint
	CHALLENGE_BOSS_CONFIG_DEGREE,			// �Ѷ�				uint
	CHALLENGE_BOSS_CONFIG_BATTLE_TYPE,		// ��Ӧս������		uint
	CHALLENGE_BOSS_CONFIG_NEED_LEV,			// ��Ҫ�ȼ�			uint
	CHALLENGE_BOSS_CONFIG_ITEM1,			// �׵���Ʒ1		uint
	CHALLENGE_BOSS_CONFIG_ITEM1_NUM,		// �׵���Ʒ1����	uint
	CHALLENGE_BOSS_CONFIG_ITEM2,			// �׵���Ʒ2		uint
	CHALLENGE_BOSS_CONFIG_ITEM2_NUM,		// �׵���Ʒ2����	uint
	CHALLENGE_BOSS_CONFIG_ITEM3,			// �׵���Ʒ3		uint
	CHALLENGE_BOSS_CONFIG_ITEM3_NUM,		// �׵���Ʒ3����	uint
	CHALLENGE_BOSS_CONFIG_ITEM4,			// �׵���Ʒ4		uint
	CHALLENGE_BOSS_CONFIG_ITEM5_NUM,		// �׵���Ʒ4����	uint
	CHALLENGE_BOSS_CONFIG_DROP_ID,			// ���׵�����ID		uint
	CHALLENGE_BOSS_CONFIG_BOSS_NAME,		// boss��			varchar32
};

static const char* CONST_DB_NAME_LOTTERY_TYPE = "lottery_type";		// �齱�������ñ�
enum LOTTERY_TYPE_DATA
{
	LOTTERY_TYPE_DATA_TYPE = 0,				// �齱����			uint
	LOTTERY_TYPE_DATA_AWARD_SUM,			// ��Ʒ����			uint
	LOTTERY_TYPE_DATA_COST_MONEY_TYPE,		// ���Ļ�������		uint
	LOTTERY_TYPE_DATA_COST_PRICE,			// ���ļ۸�			uint
	LOTTERY_TYPE_DATA_BASE_ITEM_TYPE,		// ��û�����Ʒ����	uint
	LOTTERY_TYPE_DATA_BASE_ITEM_NUM,		// ��û�����Ʒ����	uint
	LOTTERY_TYPE_DATA_RULE_ID1,				// �齱����1		uint
	LOTTERY_TYPE_DATA_GIVE_COUNT1,			// ��ȡ����1		uint
	LOTTERY_TYPE_DATA_GIVE_CHANCE1,			// ��ȡ����1		uint
	LOTTERY_TYPE_DATA_RULE_ID2,				// �齱����2		uint
	LOTTERY_TYPE_DATA_GIVE_COUNT2,			// ��ȡ����2		uint
	LOTTERY_TYPE_DATA_GIVE_CHANCE2,			// ��ȡ����2		uint
	LOTTERY_TYPE_DATA_RULE_ID3,				// �齱����3		uint
	LOTTERY_TYPE_DATA_GIVE_COUNT3,			// ��ȡ����3		uint
	LOTTERY_TYPE_DATA_GIVE_CHANCE3,			// ��ȡ����3		uint
	LOTTERY_TYPE_DATA_RULE_ID4,				// �齱����4		uint
	LOTTERY_TYPE_DATA_GIVE_COUNT4,			// ��ȡ����4		uint
	LOTTERY_TYPE_DATA_GIVE_CHANCE4,			// ��ȡ����4		uint
};

static const char* CONST_DB_NAME_LOTTERY_RULE = "lottery_rule";	// �齱�������ñ�
enum LOTTERY_RULE_DATA
{
	LOTTERY_RULE_DATA_RULE_ID = 0,			// ����id			uint
	LOTTERY_RULE_DATA_PRIZE_TYPE,			// ��������			uint
	LOTTERY_RULE_DATA_WEIGHT,				// ����Ȩ��			uint
	LOTTERY_RULE_DATA_TIME_TYPE,			// ʱ������(0���ã�1�죬2�ܣ�3��)			uint
	LOTTERY_RULE_DATA_TIME_INDEX,			// ��������(�ܣ�0-6λ��ʾ����0-31λ��ʾ)	uint
	LOTTERY_RULE_DATA_BEGIN_TIME,			// ��Ʒ��Чʱ��		uint
	LOTTERY_RULE_DATA_END_TIME,				// ��ƷʧЧʱ��		uint
};

static const char* CONST_DB_NAME_PRIZE_TYPE = "prize_type";		// �����������ñ�
enum PRIZE_TYPE_DATA
{
	PRIZE_TYPE_DATA_ID		= 0,			// ����id			uint
	PRIZE_TYPE_DATA_TYPE,					// ��Ʒ����			uint
	PRIZE_TYPE_DATA_MIN_NUM,				// ��С��Ʒ����		uint
	PRIZE_TYPE_DATA_MAX_NUM,				// ���Ʒ����������ֵ�����ȡ������		uint
};

static const char* CONST_DB_NAME_PROPERTY_CALCRANK2 = "property_calcrank2";	// 2�����Խ������ñ�
enum PROPERTY_CALCRANK2_DATA
{
	PROPERTY_CALCRANK2_DATA_TYPE = 0,	// ������			uint
	PROPERTY_CALCRANK2_DATA_LIFE,		// ����:��Ѫϵ��	uint
	PROPERTY_CALCRANK2_DATA_MANA,		// ħ��:����ϵ��	uint
	PROPERTY_CALCRANK2_DATA_STR_HIT,	// ����:����ϵ��	uint
	PROPERTY_CALCRANK2_DATA_STR_ATK,	// ����:�˺�ϵ��	uint
	PROPERTY_CALCRANK2_DATA_STA,		// ����:����ϵ��	uint
	PROPERTY_CALCRANK2_DATA_DEX,		// ����:���ϵ��	uint
};

static const char* CONST_DB_NAME_MONEY_AWARD_CHANCE = "money_award_chance";	// ҡǮ���౶�����ͼ������ñ�
enum MONEY_AWARD_CHANCE_DATA
{
	MONEY_AWARD_CHANCE_DATA_COUNT = 0,		// ҡǮ����		uint
	MONEY_AWARD_CHANCE_DATA_COST,			// ҡǮ����		uint
	MONEY_AWARD_CHANCE_DATA_MULTIPLE1,		// ��������1	uint
	MONEY_AWARD_CHANCE_DATA_CRILCHANCE1,	// ��������1	uint
	MONEY_AWARD_CHANCE_DATA_MULTIPLE2,		// ��������2	uint
	MONEY_AWARD_CHANCE_DATA_CRILCHANCE2,	// ��������2	uint
	MONEY_AWARD_CHANCE_DATA_MULTIPLE3,		// ��������3	uint
	MONEY_AWARD_CHANCE_DATA_CRILCHANCE3,	// ��������3	uint
	MONEY_AWARD_CHANCE_DATA_MULTIPLE4,		// ��������4	uint
	MONEY_AWARD_CHANCE_DATA_CRILCHANCE4,	// ��������4	uint
};

static const char* CONST_DB_NAME_INSTANCE_TYPE = "instance_type";	// �����������ñ�
enum INSTANCE_TYPE_DATA
{
	INSTANCE_TYPE_DATA_TYPE = 0,			// �������ͣ�1��Ҳ�����2���������		uint
	INSTANCE_TYPE_DATA_DIFFICULTY,			// �����Ѷ�								uint
	INSTANCE_TYPE_DATA_OPENTIME_TYPE,		// ��������ʱ�����ͣ�1�죬2�ܣ�3�£�	uint
	INSTANCE_TYPE_DATA_OPENTIME_INDEX,		// ��������ʱ���������죺0���ܡ��£�32λ��������	uint
	INSTANCE_TYPE_DATA_OPENTIME_BEGIN,		// ��������ʱ�俪ʼ						uint
	INSTANCE_TYPE_DATA_OPENTIME_END,		// ��������ʱ�����						uint
	INSTANCE_TYPE_DATA_OPEN_LEV,			// �����ȼ�								uint
	INSTANCE_TYPE_DATA_COST_POWER,			// ��������								uint
	INSTANCE_TYPE_DATA_BATTLE_TYPE,			// ս������								uint
};

static const char* CONST_DB_NAME_POKER_COLOR_ATTR = "poker_color_attr";	// ������ɫ�������ñ�
enum POKER_COLOR_ATTR_DATA
{
	POKER_COLOR_ATTR_DATA_POKER_COLOR = 0,	// ������ɫ		uint
	POKER_COLOR_ATTR_DATA_LIFE,				// ����			uint
	POKER_COLOR_ATTR_DATA_MANA,				// ħ��			uint
	POKER_COLOR_ATTR_DATA_STR,				// ����			uint
	POKER_COLOR_ATTR_DATA_STA,				// ����			uint
	POKER_COLOR_ATTR_DATA_DEX,				// ����			uint
};

static const char* CONST_DB_NAME_PUZZLE = "puzzle";	// �Թ����ñ�
enum PUZZLE_DATA
{
	PUZZLE_DATA_ID = 0,						// �Թ�����id	uint
	PUZZLE_DATA_LINK_ID1,					// ���Ӹ���id1	uint
	PUZZLE_DATA_LINK_ID2,					// ���Ӹ���id2	uint
	PUZZLE_DATA_LINK_ID3,					// ���Ӹ���id3	uint
	PUZZLE_DATA_LINK_ID4,					// ���Ӹ���id4	uint
	PUZZLE_DATA_LINK_ID5,					// ���Ӹ���id5	uint
	PUZZLE_DATA_LINK_ID6,					// ���Ӹ���id6	uint
	PUZZLE_DATA_TASK_TYPE,					// ��������		uint
	PUZZLE_DATA_BATTLE_TYPE,				// ս������		uint
	PUZZLE_DATA_ACTION_ID,					// ִ�еĽű�ID	uint
	PUZZLE_DATA_PROGRESS_ADD,				// ���ӽ���		uint
};

static const char* CONST_DB_NAME_PUZZLE_BUFF = "puzzle_buff";	// �Թ�BUFF���ñ�
enum PUZZLE_BUFF
{
	PUZZLE_BUFF_ID = 0,						// BUFF����		uint
	PUZZLE_BUFF_NAME,						// BUFF����		varchar32
	PUZZLE_BUFF_VALUE,						// BUFF����ֵ	uint
	PUZZLE_BUFF_EFFECT,						// BUFF��Ч����	uint
};

static const char* CONST_DB_NAME_ARENA_AWARD = "arena_award";	// �������������ñ�
enum ARENA_AWARD
{
	ARENA_AWARD_TYPE = 0,					// �������ֱ�	uint
	ARENA_AWARD_UPPER_LEV,					// ������������	uint
	ARENA_AWARD_LOWER_LEV,					// ������������	uint
	ARENA_AWARD_GOLD_COUNT,					// ���������	uint
	ARENA_AWARD_MONEY_COUNT,				// ������������	uint
	ARENA_AWARD_VAS_COUNT,					// ����Ԫ��		uint
	ARENA_AWARD_ITEM_TYPE,					// ������Ʒtype	uint
	ARENA_AWARD_ITEM_COUNT,					// ������Ʒ��	uint
	ARENA_AWARD_MONEY_COUNT_PER,			// ��ʱ������	uint
	ARENA_AWARD_END,
};

static const char* CONST_DB_NAME_ARENA_AI_POKER = "arena_ai_poker";	// �����������˿������ñ�
enum ARENA_AI_POKER_DATA
{
	ARENA_AI_POKER_DATA_ARENA_TYPE = 0,		// ���������	uint
	ARENA_AI_POKER_DATA_LOW_RANK,			// ������Χ����	uint
	ARENA_AI_POKER_DATA_POKER_TYPE,			// ����typeid	uint
};

static const char* CONST_DB_NAME_PAY_CONFIG = "pay_config";		// ��ֵ���ñ�
enum PAY_CONFIG_DATA
{
	PAY_CONFIG_DATA_ID = 0,				// id(�׳�����)			uint
	PAY_CONFIG_DATA_RMB,				// �����				uint
	PAY_CONFIG_DATA_VAS,				// Ԫ��					uint
	PAY_CONFIG_DATA_FREE_VAS,			// ����Ԫ��				uint
	PAY_CONFIG_DATA_FREE_VAS_DES,		// ����Ԫ��˵��			uint
	PAY_CONFIG_DATA_FISRT_FREE_VAS,		// �׳�����Ԫ��			uint
	PAY_CONFIG_DATA_FISRT_FREE_DES,		// �׳�����Ԫ��˵��		uint
	PAY_CONFIG_DATA_MONTH_CARD,			// �¿����				uint
};

static const char* CONST_DB_NAME_WAR_ROAD = "war_road";			// ս�����ñ�
enum WAR_ROAD_DATA
{
	WAR_ROAD_DATA_WAR_KEY = 0,			// ս��key��ģʽ*1000000+�½�*1000+�ؿ�����ģʽ1��ͨ��2��Ӣ��3�Ŷӣ�	uint
	WAR_ROAD_DATA_OPEN_LEV,				// �����ȼ�						uint
	WAR_ROAD_DATA_COST_POWER,			// ��������						uint
	WAR_ROAD_DATA_BATTLE_TYPE,			// ս������						uint
};

static const char* CONST_DB_NAME_WAR_ROAD_TEAM = "war_road_team";	// �Ŷ�ս�����ñ�
enum WAR_ROAD_TEAM_DATA
{
	WAR_ROAD_TEAM_DATA_CHAPTER = 0,		// �½�							uint
	WAR_ROAD_TEAM_DATA_CHAPTER_NAME,	// �½�����						varchar
	WAR_ROAD_TEAM_DATA_OPEN_COST,		// �������ģ���Ծֵ��			uint
	WAR_ROAD_TEAM_DATA_AWARD_RULE,		// ս��Ʒ��⣨lottery_award�������ã�			uint
	WAR_ROAD_TEAM_DATA_AWARD_TIME,		// ����ͨ�ؽ���ʱ��				uint
	WAR_ROAD_TEAM_DATA_AWARD_COUNT,		// ���⽱���ﹱ����				uint
	WAR_ROAD_TEAM_DATA_PASS_WIN_COUNT,	// �ؿ�ʤ�������ﹱ����			uint
};

static const char* CONST_DB_NAME_TERRITORY_FIGHT = "territory_fight";		// ���ս���ñ�
enum TERRITORY_FIGHT_DATA
{
	TERRITORY_FIGHT_DATA_ID = 0,				// ���id					uint
	TERRITORY_FIGHT_DATA_TYPE,					// ���type					uint
	TERRITORY_FIGHT_DATA_BATTLETYPE,			// ս��type					uint
	TERRITORY_FIGHT_DATA_EFFECT,				// ���Ч��					uint
	TERRITORY_FIGHT_DATA_POKER_LEV_LIMIT,		// ���ս��ս���ӵȼ�����	uint
	TERRITORY_FIGHT_DATA_BOSS_NAME,				// פ��boss����				varchar

};

static const char* CONST_DB_NAME_TERRITORY_FIGHT_MONSTER = "territory_fight_monster";	// ���սĬ��פ�ع�
enum TERRITORY_FIGHT_MONSTER_DATA
{
	TERRITORY_FIGHT_MONSTER_DATA_TROOPS_ID = 0,	// 
	TERRITORY_FIGHT_MONSTER_DATA_ID,
	TERRITORY_FIGHT_MONSTER_DATA_POKERID1,
	TERRITORY_FIGHT_MONSTER_DATA_POKERID2,
	TERRITORY_FIGHT_MONSTER_DATA_POKERID3,
	TERRITORY_FIGHT_MONSTER_DATA_POKERID4,
	TERRITORY_FIGHT_MONSTER_DATA_POKERID5,
};

static const char* CONST_DB_NAME_DATA_RESET	= "data_reset";		// �����������ñ�
enum DATA_RESET_DATA
{
	DATA_RESET_DATA_TYPE = 0,					// ��������					uint
	DATA_RESET_DATA_COUNT,						// ���ô���					uint
	DATA_RESET_DATA_COST_TYPE,					// ��������					uint
	DATA_RESET_DATA_COST_NUM,					// ��������					uint
};

static const char* CONST_DB_NAME_SYN_GIFT_BOX	= "syn_giftbox";// ����������ñ�
enum SYN_GIFT_BOX_DATA
{
	SYN_GIFT_BOX_DATA_TYPE = 0,					// �������					uint
	SYN_GIFT_BOX_DATA_LEV,						// ��еȼ�					uint
	SYN_GIFT_BOX_DATA_EXP,						// ��о���					uint
	SYN_GIFT_BOX_DATA_KEEP_TIME,				// ����ʱ��					uint
	SYN_GIFT_BOX_DATA_DATA1,					// ����1					uint
	SYN_GIFT_BOX_DATA_DATA2,					// ����2					uint
	SYN_GIFT_BOX_DATA_RULE_ID,					// ������������id			uint
};

static const char* CONST_DB_NAME_LOOKFACE_FRAME = "lookface_frame";	// ͷ������ñ�
enum LOOKFACE_FRAME_DATA
{
	LOOKFACE_FRAME_DATA_TYPE = 0,				// ͷ�������			uint
	LOOKFACE_FRAME_DATA_VIP_LEV,				// vip�ȼ�				uint
	LOOKFACE_FRAME_DATA_SINGLE_ARENA_RANK,		// ��ǰ���Ӿ���������	uint
	LOOKFACE_FRAME_DATA_MULTI_ARENA_RANK,		// ��ǰ��Ӿ���������	uint
	LOOKFACE_FRAME_DATA_TIME_LIMIT,				// ʱ������				uint
	LOOKFACE_FRAME_DATA_PARAM1,					// Ԥ��1				uint
	LOOKFACE_FRAME_DATA_PARAM2,					// Ԥ��2				uint
	LOOKFACE_FRAME_DATA_NAME,					// ����					uint
};

static const char* CONST_DB_NAME_IP_LIBRARY = "ip_library";		// ip�����ñ�
enum IP_LIBRARY_DATA
{
	IP_LIBRARY_DATA_ID = 0,				// ID							uint
	IP_LIBRARY_DATA_IP_BEGIN,			// ��ʼIP						varchar16
	IP_LIBRARY_DATA_IP_END,				// ����IP						varchar16
	IP_LIBRARY_DATA_IP_BEGIN_INT,		// ��ʼIP(����)					uint
	IP_LIBRARY_DATA_IP_END_INT,			// ����IP(����)					uint
	IP_LIBRARY_DATA_ADDRESS1,			// ��ַ1						varchar64
	IP_LIBRARY_DATA_ADDRESS2,			// ��ַ2						varchar128
	IP_LIBRARY_DATA_ADDRESS_FINAL,		// ��������						varchar64
	IP_LIBRARY_DATA_ADDRESS_ID,			// �������						uint
};


static const char* CONST_DB_NAME_ROOM_TYPE = "room_type";
enum ROOM_TYPE_DATA
{
	ROOM_TYPE_DATA_TYPE = 0,		// ��������			uint
	ROOM_TYPE_DATA_NAME,			// ��������			varchar64
	ROOM_TYPE_DATA_KEEP_TIME,		// �������ʱ��		uint
	ROOM_TYPE_DATA_MAX_MEMBER,		// ����Ա����		uint
	ROOM_TYPE_DATA_MONSTER1,		// ��������1		uint
	ROOM_TYPE_DATA_MONSTER2,		// ��������2		uint
	ROOM_TYPE_DATA_MONSTER3,		// ��������3		uint
	ROOM_TYPE_DATA_MONSTER4,		// ��������4		uint
	ROOM_TYPE_DATA_MONSTER5,		// ��������5		uint
	ROOM_TYPE_DATA_MONSTER6,		// ��������6		uint
	ROOM_TYPE_DATA_MONSTER7,		// ��������7		uint
	ROOM_TYPE_DATA_MONSTER8,		// ��������8		uint
	ROOM_TYPE_DATA_MONSTER9,		// ��������9		uint
	ROOM_TYPE_DATA_MONSTER10,		// ��������10		uint
	ROOM_TYPE_DATA_MONSTER11,		// ��������11		uint
	ROOM_TYPE_DATA_MONSTER12,		// ��������12		uint
	ROOM_TYPE_DATA_MONSTER13,		// ��������13		uint
	ROOM_TYPE_DATA_MONSTER14,		// ��������14		uint
	ROOM_TYPE_DATA_MONSTER15,		// ��������15		uint
};

static const char* CONST_DB_NAME_ROOM_MONSTER = "room_monster";
enum ROOM_MONSTER_DATA
{
	ROOM_MONSTER_DATA_TYPE = 0,			// ��������								uint
	ROOM_MONSTER_DATA_SORT,				// ������ʽ		1���� 2�ɼ���			uint
	ROOM_MONSTER_DATA_BATTLE_TYPE,		// ս������		1���ﴥ����ս������		uint
	ROOM_MONSTER_DATA_REBORN_SECOND,	// ��������		0��ʾ������				uint
	ROOM_MONSTER_DATA_PICK_SECOND,		// �ɼ�ʱ��								uint
	ROOM_MONSTER_DATA_PICK_ACTION,		// �ɼ���action							uint
};

static const char* CONST_DB_NAME_NAME_LIBRARY = "name_library";		// ���ֿ�
enum NAME_LIBRARY_DATA
{
	NAME_LIBRARY_DATA_ID = 0,			// id	uint
	NAME_LIBRARY_DATA_SURNAME,			// ��	varchar
	NAME_LIBRARY_DATA_NAME,				// ��	varchar
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���������¼�������
enum RELOAD_CONST_TABLE_TYPE
{
	RELOAD_CONST_TABLE_TYPE_SERVER_START_TIME = 0,
	RELOAD_CONST_TABLE_TYPE_LUA_FILE,
	RELOAD_CONST_TABLE_TYPE_POKER_COLOR_ATTR_SUM,

	RELOAD_CONST_TABLE_TYPE_CONFIGDATA,
	RELOAD_CONST_TABLE_TYPE_CONFIGTEXT,
	RELOAD_CONST_TABLE_TYPE_TASK_DATA,
	RELOAD_CONST_TABLE_TYPE_NEWCARDPRIZE,
	RELOAD_CONST_TABLE_TYPE_NOTIFY_CONFIG,
	RELOAD_CONST_TABLE_TYPE_ACTIVITYCONFIG,
	RELOAD_CONST_TABLE_TYPE_ACTION,
	RELOAD_CONST_TABLE_TYPE_POKER_TYPE,
	RELOAD_CONST_TABLE_TYPE_POKER_STAR_GROW,
	RELOAD_CONST_TABLE_TYPE_POKER_EQUIP,
	RELOAD_CONST_TABLE_TYPE_POKER_STAR,
	RELOAD_CONST_TABLE_TYPE_POKER_COLOR_ATTR,
	RELOAD_CONST_TABLE_TYPE_LEV_EXP,
	RELOAD_CONST_TABLE_TYPE_SIGNPRIZE,
	RELOAD_CONST_TABLE_TYPE_VIP,
	RELOAD_CONST_TABLE_TYPE_ITEM_TYPE,
	RELOAD_CONST_TABLE_TYPE_ITEM_COLOR,
	RELOAD_CONST_TABLE_TYPE_ITEM_STAR_ATTR,
	RELOAD_CONST_TABLE_TYPE_LIVENESS,
	RELOAD_CONST_TABLE_TYPE_SHOP_TYPE,
	RELOAD_CONST_TABLE_TYPE_SHOP_RULE,
	RELOAD_CONST_TABLE_TYPE_ACHIEVEMENT,
	RELOAD_CONST_TABLE_TYPE_LUA_TEXT,
	RELOAD_CONST_TABLE_TYPE_SKILL_TYPE,
	RELOAD_CONST_TABLE_TYPE_DROP_RULE,
	RELOAD_CONST_TABLE_TYPE_BATTLE_TYPE,
	RELOAD_CONST_TABLE_TYPE_BATTLE_ROUND,
	RELOAD_CONST_TABLE_TYPE_BATTLE_MONSTER,
	RELOAD_CONST_TABLE_TYPE_PEIFANG,
	RELOAD_CONST_TABLE_TYPE_CHALLENGE_BOSS,
	RELOAD_CONST_TABLE_TYPE_LOTTERY_TYPE,
	RELOAD_CONST_TABLE_TYPE_LOTTERY_RULE,
	RELOAD_CONST_TABLE_TYPE_PRIZE_TYPE,
	RELOAD_CONST_TABLE_TYPE_PROPERTY_CALCRANK2,
	RELOAD_CONST_TABLE_TYPE_MONEY_AWARD_CHANCE,
	RELOAD_CONST_TABLE_TYPE_INSTANCE_TYPE,
	RELOAD_CONST_TABLE_TYPE_PUZZLE,
	RELOAD_CONST_TABLE_TYPE_PUZZLE_BUFF,
	RELOAD_CONST_TABLE_TYPE_PAY_CONFIG,
	RELOAD_CONST_TABLE_TYPE_ARENA_AWARD,
	RELOAD_CONST_TABLE_TYPE_ARENA_AI_POKER,
	RELOAD_CONST_TABLE_TYPE_WAR_ROAD,
	RELOAD_CONST_TABLE_TYPE_WAR_ROAD_TEAM,
	RELOAD_CONST_TABLE_TYPE_TERRITORY_FIGHT,
	RELOAD_CONST_TABLE_TYPE_TERRITORY_FIGHT_MONSTER,
	RELOAD_CONST_TABLE_TYPE_DATA_RESET,
	RELOAD_CONST_TABLE_TYPE_SYN_GIFT_BOX,
	RELOAD_CONST_TABLE_TYPE_LOOKFACE_FRAME,
	RELOAD_CONST_TABLE_TYPE_ROOM_TYPE,
	RELOAD_CONST_TABLE_TYPE_ROOM_MONSTER,
	RELOAD_CONST_TABLE_TYPE_NAME_LIBRARY,
	RELOAD_CONST_TABLE_TYPE_END,
};


#endif // end of _CARD_SERVER_DATABASE_DEFINE_
