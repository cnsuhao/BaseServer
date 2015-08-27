////////////////////////////////////////////////////////////////////////
// Import : �˺ſ�����ȫ��������
// Moudle : DatabaseDefineAcc.h
// Author : �½���(Chen Jianjun)
// Created: 2015-08-27
////////////////////////////////////////////////////////////////////////
#ifndef _DATABASE_DEFINE_ACC_H_
#define _DATABASE_DEFINE_ACC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

static const char* ACC_DB_NAME_ACCOUNT = "account";		// �˺ű�
enum ACCOUNT_DATA
{
	ACCOUNT_DATA_ID = 0,			// �˺�id								uint
	ACCOUNT_DATA_NAME,				// �˺���								varchar64
	ACCOUNT_DATA_PASSWORD,			// �˺�����								varchar64
	ACCOUNT_DATA_REG_TIME,			// ע��utcʱ��							uint
	ACCOUNT_DATA_TYPE,				// �˺�����(0��ͨ, 1GM��2�ο�)			uint
	ACCOUNT_DATA_STATUS,			// �˺�״̬(0������1��ʱ�⣬2���÷�)	uint
	ACCOUNT_DATA_STATUS_PARAM,		// ��ʱ�����ʱ��						uint
	ACCOUNT_DATA_PLATFORM,			// ƽ̨									varchar32
	ACCOUNT_DATA_CHANNEL,			// ����									varchar32
	ACCOUNT_DATA_OS,				// ����ϵͳ								varchar32
};

//static const char* ACC_DB_VAS_LOG = "vas_log";	// Ԫ����־��
//enum VAS_LOG_DATA
//{
//	VAS_LOG_DATA_ID = 0,			// id			bigint
//	VAS_LOG_DATA_ACCOUNT_ID,		// �˺�id		uint
//	VAS_LOG_DATA_USER_ID,			// ��ɫid		uint
//	VAS_LOG_DATA_SERVER_GROUP,		// ��������		uint
//	VAS_LOG_DATA_SERVER_LINE,		// ��������		uint
//	VAS_LOG_DATA_FLOW_TYPE,			// ��������		uint
//	VAS_LOG_DATA_TIME,				// ʱ��, utc��	uint
//	VAS_LOG_DATA_ITEMTYPE_ID,		// itemtype		uint
//	VAS_LOG_DATA_ITEMTYPE_AMOUNT,	// ����			uint
//	VAS_LOG_DATA_POINT,				// ��������		bigint
//	VAS_LOG_DATA_AFTER_POINT,		// ���������	bigint
//	VAS_LOG_DATA_EXTRA_TEXT,		// ��������˵�� varchar128
//};
//
//static const char* ACC_DB_MONEY_LOG = "money_log";	// ��Ǯ��־��
//enum MONEY_LOG_DATA
//{
//	MONEY_LOG_DATA_ID = 0,			// id			bigint
//	MONEY_LOG_DATA_ACCOUNT_ID,		// �˺�id		uint
//	MONEY_LOG_DATA_USER_ID,			// ��ɫid		uint
//	MONEY_LOG_DATA_SERVER_GROUP,	// ��������		uint
//	MONEY_LOG_DATA_SERVER_LINE,		// ��������		uint
//	MONEY_LOG_DATA_FLOW_TYPE,		// ��������		uint
//	MONEY_LOG_DATA_TIME,			// ʱ��, utc��	uint
//	MONEY_LOG_DATA_ITEMTYPE_ID,		// itemtype		uint
//	MONEY_LOG_DATA_ITEMTYPE_AMOUNT,	// ����			uint
//	MONEY_LOG_DATA_MONEY_TYPE,		// �������		uint
//	MONEY_LOG_DATA_POINT,			// ��������		bigint
//	MONEY_LOG_DATA_AFTER_POINT,		// ���������	bigint
//	MONEY_LOG_DATA_EXTRA_TEXT,		// ��������˵�� varchar128
//};
//
//static const char* ACC_DB_SERVER_LIST = "server_list";	// �������б�, ά����Ա���õ�
//enum SERVER_LIST_DATA
//{
//	SERVER_LIST_DATA_GROUP = 0,			// ��id			uint
//	SERVER_LIST_DATA_LINE,				// ��id			uint
//	SERVER_LIST_DATA_CLIENT_IP,			// �ͻ���ip		varchar50
//	SERVER_LIST_DATA_CLIENT_PORT,		// �ͻ��˶˿�	uint 
//	SERVER_LIST_DATA_CLOSE,				// �رձ��		uint
//};
//
//static const char* ACC_DB_NEWCARD = "newcard";	// ���ֿ������
//enum NEWCARD_DATA
//{
//	NEWCARD_DATA_ID = 0,			// id			bigint
//	NEWCARD_DATA_CARD,				// ����			char64
//	NEWCARD_DATA_PICKED,			// ʹ�ñ��		uint
//	NEWCARD_DATA_PLATFORM,			// ƽ̨			varchar10
//	NEWCARD_DATA_SERVER_GROUP,		// ��������		uint
//};
//
//static const char* ACC_DB_PAYLOG = "paylog";	// ��ֵ��¼��
//enum PAYLOG_DATA
//{
//	PAYLOG_DATA_LOGID = 0,		// id			bigint
//	PAYLOG_DATA_PAYNUM,			// ��ˮ��		varchar255
//	PAYLOG_DATA_LOGDATE,		// ��ֵutcʱ��	uint
//	PAYLOG_DATA_ACCOUNT_ID,		// �˺�id		uint
//	PAYLOG_DATA_USER_ID,		// ��ɫid		uint
//	PAYLOG_DATA_IP,				// ip			varchar20
//	PAYLOG_DATA_PAYGOLD,		// ��ֵԪ��		uint
//	PAYLOG_DATA_FREEGOLD,		// ����Ԫ��		uint
//	PAYLOG_DATA_PAYMONEY,		// �����		DECIMAL
//	PAYLOG_DATA_CHANNEL,		// channel		varchar20
//	PAYLOG_DATA_CHANNEL_FEE,	// channel_fee	float
//	PAYLOG_DATA_SERVER_GROUP,	// ���������	uint
//	PAYLOG_DATA_CONFIG_ID,		// ����id		uint
//	PAYLOG_DATA_STATUS,			// ���״̬��0 �����У� 1 ͨ���� 2 �ܾ�, 3 ��ᣩ	uint
//};
//
//static const char* ACC_DB_ONLINE_LOG = "online_log";	// ������־��
//enum ONLINE_LOG_DATA
//{
//	ONLINE_LOG_DATA_ID = 0,
//	ONLINE_LOG_DATA_TIME,
//	ONLINE_LOG_DATA_COUNT_ONLINE,
//	ONLINE_LOG_DATA_SERVER_GROUP,
//};
//
//static const char* ACC_DB_NOTIFY_PHP = "notify_php";	// ƽ̨�����
//enum NOTIFY_PHP_DATA
//{
//	NOTIFY_PHP_DATA_ID = 0,				// ������id	uint
//	NOTIFY_PHP_DATA_BEGIN_TIME,			// ��ʼʱ�� uint
//	NOTIFY_PHP_DATA_INTERVAL_SECOND,	// ���ʱ�� uint
//	NOTIFY_PHP_DATA_COUNT,				// ���Ŵ��� uint
//	NOTIFY_PHP_DATA_CHANNEL,			// Ƶ��		uint
//	NOTIFY_PHP_DATA_TEXT,				// �������� varchar512
//	NOTIFY_PHP_DATA_SERVER_GROUP,		// �������� uint
//};
//
//static const char* ACC_DB_NAME_GM_MAC = "gm_mac";	// gm Mac��ַ����
//enum GM_MAC_DATA
//{
//	GM_MAC_DATA_ADDRESS_MAC = 0,		// mac��ַ�ַ���	varchar32
//	GM_MAC_DATA_PARAM_STRING,			// ע���ַ���		varchar64
//};
//
//static const char* ACC_DB_NAME_GM_OPERATION_LOG = "gm_operation_log";	// gm ������־
//enum GM_OPERATION_LOG_DATA
//{
//	GM_OPERATION_LOG_DATA_ID = 0,				// id				uint
//	GM_OPERATION_LOG_DATA_UTC_SECOND,			// ��¼ʱ��, utc��	uint
//	GM_OPERATION_LOG_DATA_DATE_TIME,			// ����ʱ��			varchar24
//	GM_OPERATION_LOG_DATA_GM_ACCOUNT_ID,		// gm�˺�id			uint
//	GM_OPERATION_LOG_DATA_GM_ACCOUNT_NAME,		// gm�˺���			varchar32
//	GM_OPERATION_LOG_DATA_GM_USER_ID,			// gm��ɫid			uint
//	GM_OPERATION_LOG_DATA_GM_USER_NAME,			// gm��ɫ��			varchar32
//	GM_OPERATION_LOG_DATA_GM_IP,				// gm����ʱip		varchar32
//	GM_OPERATION_LOG_DATA_GM_MAC,				// gm����ʱmac��ַ	varchar32
//	GM_OPERATION_LOG_DATA_SERVER_GROUP,			// ��������			uint
//	GM_OPERATION_LOG_DATA_SERVER_LINE,			// ��������			uint
//	GM_OPERATION_LOG_DATA_OPERATION_TYPE_STR,	// ���������ַ���	varchar16
//	GM_OPERATION_LOG_DATA_OPERATION_INFO,		// ��������			varchar128
//};

#endif // end of _DATABASE_DEFINE_ACC_H_