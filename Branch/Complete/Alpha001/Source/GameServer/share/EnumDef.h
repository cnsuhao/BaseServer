////////////////////////////////////////////////////////////////////////
// Import : �����ļ���ö�ٶ��塣
// Moudle : EnumDef.h 
// Author : �½���(Chen Jianjun)
// Create : 2015-6-19
////////////////////////////////////////////////////////////////////////
#ifndef _SHARE_ENUM_DEF_H_
#define _SHARE_ENUM_DEF_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../common/common.h"

// �̹߳ܵ�����
enum ENUM_MSGPORT_TYPE
{
	MSGPORT_SHELL		= 0,		// �Ի���
	MSGPORT_SOCKET		= 1,		// �ײ�ͨѶ
	MSGPORT_LOGIN		= 2,		// ��½
	MSGPORT_GAME		= 3,		// ��Ϸ�߼�
	MSGPORT_RELATION	= 4,		// ��������ͨ��
	MSGPORT_AI			= 5,		// AIͨ��

	MSGPORT_SIZE,					// �ܵ�����
	MSGPORT_DEFAULT		= 999,		// Ĭ���߳�ID, ��ö�ٲ�����Ϊ�̼߳�ͨ�Žӿ�ʹ��
};
////////////////////////////////////////////////////////////////////////

// �˺��߳���־
enum ACCOUNT_KICK_FLAG
{
	ACCOUNT_KICK_FLAG_NONE		= 0x0000,
	ACCOUNT_KICK_FLAG_SOCKET	= 0x0001,
	ACCOUNT_KICK_FLAG_GAME		= 0x0002,
	ACCOUNT_KICK_FLAG_RELATION	= 0x0004,
	//ACCOUNT_KICK_FLAG_OK		= ACCOUNT_KICK_FLAG_SOCKET | ACCOUNT_KICK_FLAG_GAME | ACCOUNT_KICK_FLAG_RELATION,
	ACCOUNT_KICK_FLAG_OK		= ACCOUNT_KICK_FLAG_SOCKET,
};

// ��¼ʱ�˺�״̬
enum ACCOUNT_LOGIN_STATE
{
	ACCOUNT_LOGIN_STATE_WAIT_KICK,
	ACCOUNT_LOGIN_STATE_WAIT_ENTER,
	ACCOUNT_LOGIN_STATE_WAIT_CHOOSE,
	ACCOUNT_LOGIN_STATE_OK,
};

// �߳�ԭ��
enum KICK_REASON
{
	KICK_REASON_DEFAULT					= 0,	// �߳�Ĭ��ֵ, һ�㲻Ҫ�����ֵ
	KICK_REASON_ACCOUNT_ERROR			= 1,	// �˺Ų�����
	KICK_REASON_PASSWORD_ERROR			= 2,	// �������
	KICK_REASON_BE_KICK_ANOTHER			= 3,	// ��������
	KICK_REASON_RELATION_SERVER			= 4,	// ��ϵ������ָʾ�㱻����
	KICK_REASON_FULL					= 5,	// ��̫��
	KICK_REASON_SYSTEM					= 6,	// ����������������� �� GM����	
	KICK_REASON_NOT_ALLOW				= 7,	// ������δ������½����
	KICK_REASON_GM_MAC_ERROR			= 8,	// GM����Mac��ַ��֤����		
	KICK_REASON_CHECK_SPEED_TOO_FAST	= 9,	// ����ٶȹ���					**
	KICK_REASON_GMCMD					= 10,	// GM�������Լ�	
	KICK_REASON_LOGIN_TIMEOUT			= 11,	// ��½���̳�ʱ
	KICK_REASON_ACCOUNT_STOP_BYTIME		= 12,	// �˺���ʱ��ͣ
	KICK_REASON_ACCOUNT_STOP_FOREVER	= 13,	// �˺����÷�ͣ
};

// user���ڴ�����ö��
enum MEMORY_DATA_ATTR_USER
{
	mdaUser_BEGIN = 0,

	mdaUser_AccountType,				// �˺�����
	mdaUser_AccountStatus,				// �˺�״̬
	mdaUser_AccountStatusParam,			// �˺�״̬����

	mdaUser_OnlineSecond,				// ����ʱ��

	mdaUser_OnTimer_EverySecond,		// ÿ������
	mdaUser_OnTimer_MinuteSecond,		// ÿ��������

	mdaUser_GmMacPass,

	mdaUser_END,
};

// ��������
enum EUSERMASKTYPE
{
	EUMT_Begin					= 0,
	EUMT_TaskMask				= 1,	// ��������
	EUMT_GiveMask				= 2,	// ��������
	EUMT_DayMask				= 3,	// ������
	EUMT_WeekMask				= 4,	// ������
	EUMT_MonthMask				= 5,	// ������
	EUMT_End,
};

// �������ID������ռ������ö��				�����ʹ��:��λ����ID (0 - 5000) ��������ID(10000 - 20000)
enum E_USER_MASKID_PROGRAM
{
	// ��������ID��ʼ
	// ������ID����

	// ��������ID��ʼ

	// ��������ID����

	// ������ID��ʼ
	EUMIP_DAY_BIT_LiveBoxStatus = 1,		// ÿ�ջ�Ծ ��Ծ�ȱ���򿪱��(Ŀǰʹ�õ�2����5������λ)

	EUMIP_DAY_COUNT_LiveValues = 10001,		// ÿ�ջ�Ծ ��ǰ��Ծ��
	// ������ID����

	// ������ID��ʼ
	// ������ID����

	// ������ID��ʼ
	EUMIP_MONTH_BIT_SIGN = 1,				// ÿ��ǩ������
	// ������ID����
};

// �����ʱ���ݱ�
enum EUSER_TEMPDATA_PROGRAM
{
	// �������õ�TMP_ID��10000��ʼ
	EUTDP_BEGIN = 10000,

	// 10000 - 11000�����ͻ���ʹ��BEG
	EUTDP_CLIENT_BEGIN = EUTDP_BEGIN,
	EUTDP_CLIENT_END = 11000,
	// 10000 - 11000�����ͻ���ʹ��END

	// ����˴�11001��ʼ
	EUTDP_SERVER_BEGIN = 11001,
	EUTDP_SERVER_END,
	EUTDP_END,
};

// �ʼ�״̬
enum EMAIL_STATUS
{
	EMAIL_STATUS_Begin	= 0,
	EMAIL_STATUS_UNREAD = EMAIL_STATUS_Begin,	// δ��
	EMAIL_STATUS_READ	= 1,					// �Ѷ�
	EMAIL_STATUS_Del	= 2,					// ɾ��
	EMAIL_STATUS_End,
};

// �����������ö��
enum EUPDATA_TASK_TYPE
{
	EUPDATA_TASK_TYPE_Beg	= 0,
	EUPDATA_TASK_TYPE_Add	= EUPDATA_TASK_TYPE_Beg,	// ��������
	EUPDATA_TASK_TYPE_Del	= 1,						// ɾ������
	EUPDATA_TASK_TYPE_Alter = 2,						// �޸�����
	EUPDATA_TASK_TYPE_End,
};

// ����Ƶ��
enum TALK_TXTATR
{
	TALK_TXTATR_BEGIN			= 2000,
	TALK_TXTATR_PRIVATE			= 2001,	// ˽��
	TALK_TXTATR_SYNDICATE		= 2002,	// ����
	TALK_TXTATR_WORLDSERVER		= 2003,	// ����(����)
	TALK_TXTATR_GM_CMD			= 2004,	// GM����
	TALK_TXTATR_NOTICE			= 2005,	// ����
	TALK_TXTATR_HINT			= 2006,	// ��ʾ
	TALK_TXTATR_GM_OPERATION	= 2007,	// GM����(����)
	TALK_TXTATR_END,
};
/////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // end of _SHARE_ENUM_DEF_H_
