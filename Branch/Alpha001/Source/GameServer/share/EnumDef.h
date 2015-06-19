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
/////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // end of _SHARE_ENUM_DEF_H_
