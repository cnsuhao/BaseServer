////////////////////////////////////////////////////////////////////////
// Import : ȫ���ļ����������塣
// Moudle : GlobalConstDef.h
// Author : �½���(Chen Jianjun)
// Create : 2015-6-19
////////////////////////////////////////////////////////////////////////
#ifndef _GLOBAL_CONSTDEF_H_
#define _GLOBAL_CONSTDEF_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>

extern char g_szServerName[64];				// ��������
extern int  g_nServerLine;					// ��������·��
extern int  g_nServerGroup;					// ���������
extern int	g_nServerStartTime;				// ����������ʱ�侫ȷ����
extern std::string g_strConstDatabaseName;	// ���������ݿ���
extern std::string g_strGameDatabaseName;	// ��Ϸ�����ݿ���
extern std::string g_strAccountDatabaseName;// �˺ŷ����ݿ���

const int	MAX_PACKETSIZE		= 1024;							// ������Ϣ���ߴ�
const int	MAX_MESSAGESIZE		= MAX_PACKETSIZE + 40;			// �ڲ���Ϣ���ߴ�

const int	NAME_SIZE			= 32;							// ��ɫ������
const int	SYN_ANNOUNCE_SIZE	= 256;							// ���ɹ��泤��
const int	MAX_PARAMSIZE		= 256;							// action param space
const int	MAX_TENETSIZE		= 256;							
const int	_MAX_FEELSIZE		= 32;
const int	MAX_TOLOG_MONEY		= 100000;						// ���ĵĽ�Ǯ����������Ҫ����־
const int	MAX_MAIL_TEXT		= 256;							// �����ʼ������ַ���
const int   MAX_MAIL_TITLE		= 32;							// ����ʼ������ַ���
const int   MAX_ADDRESS_SIZE	= 64;							// ������ڵ�������
const int	INVITE_CODE_SIZE	= 16;							// �����볤��
const int	_MAX_MSGSIZE		= 1024 ;

#ifdef MYDEBUG
	const int	MAX_GAMESERVER_ACCEPT_SESSION	= 200;									// �η����Ự����
#else
	const int	MAX_GAMESERVER_ACCEPT_SESSION	= 5000;									// �η����Ự����
#endif
const int	MAX_LOGINSERVER_ACCEPT_SESSION		= 500;									// ��ڷ����Ự����
const int	MAX_GAMESERVER_PLAYER_COUNT			= MAX_GAMESERVER_ACCEPT_SESSION - 100;	// ��������ҽ�����Ϸ��ֵ
const int	MAX_RELATIONSERVER_ACCEPT_SESSION	= 100;									// ��ϵ�����Ự����
const int	MAX_CROSSSERVER_ACCEPT_SESSION		= 100;									// ������Ự����
const int	RELATION_SERVER_SOCKET_BUF			= 512 * 1024;							// ��ϵ�������׽��ֲ���		��������С		[����/����]��ͬ
const int	CROSS_SERVER_SOCKET_BUF				= 512 * 1024;							// ����������׽��ֲ���		��������С		[����/����]��ͬ
const int	USER_ONLINE_SYNC_COUNT_PER_SECOND	= 500;									// ÿ����ҵ�������Ϣͬ���ĸ���
const int	MAX_ONLINE_USER_COUNT				= 2000;									// ���������������

typedef	unsigned long		OBJID;
typedef	unsigned long		PROCESS_ID;							// ͨ�����ڲ���Ϣ�ӿ�ID��ͬ
typedef	long				SOCKET_ID;							// ��Ҷ�Ӧ��SOCKET_ID��ͨ��ΪSET��������
typedef __int64				I64;
typedef __int64				DB_KEY;


typedef	char			SQLBUF[4096];
typedef	char			MSGBUF[1024];
typedef	char			MESSAGESTR[MAX_MESSAGESIZE];

// �¶������Ϣ�ṹ��ֻ�������¼������ͱ���
typedef char	MSG_NUM_1BIT;
typedef short	MSG_NUM_2BIT;
typedef int		MSG_NUM_4BIT;
typedef __int64 MSG_NUM_8BIT;
typedef char	MSG_STR_16BIT[16];
typedef char	MSG_STR_32BIT[32];
typedef char	MSG_STR_64BIT[64];
typedef char	MSG_STR_128BIT[128];
typedef char	MSG_STR_192BIT[192];
typedef char	MSG_STR_256BIT[256];

const int MAX_ALLOW_AINPC_REACH_DESTPOINT_DISTANCE = 1;

static const char* LOGIN_SERVER_PASSWORD	= "sXd73E4DwS9!5_6";

const double	DOUBLE_PERCENT_BASE = 10000.0;	// ��ֱȻ���(double����)
const int		INT_PERCENT_BASE	= 10000;	// ��ֱȻ���(int����)
const I64		I64_PERCENT_BASE	= 10000i64;	// ��ֱȻ���(I64����)
const I64		I64_MAX_CEIL		= 9223372036854775807i64;	// I64������������
const int		INT_MAX_CEIL		= 2147483647;				// int������������
const unsigned int	UINT_MAX_CEIL	= 4294967295;				// uint������������

const int	ID_NONE			= 0;
const int	ID_AI_PROCESS	= 1;
const int	SOCKET_NONE		= -1;				// ��Ч��SOCKET����
const int	SERVER_LISTEN_PORT_DEFAULT = 19999;

const int	CROSS_SERVER_GROUP = 9999;		// ������������

/////////////////////////////////////////////////////////////////////////////////////////
// ������ʹ�õĳ������� start
const int		ALL_SERVER_LINE_TYPE	= 99999;				//  ��������·
const int		ALL_SERVER_GROUP_TYPE	= 99999;				//  �����ַ�������

const int DESIGN_VAS_LIMIT = 5000;	// �߻�����Ԫ�������޶�

/////////////////////////////////////////////////////////////////////////////////////////
#endif // end of _GLOBAL_CONSTDEF_H_