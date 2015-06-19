////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2012, WuHan ChuangYou, All Rights Reserved
// Moudle: GlobalConstDef.h
// Author: ������(Peng Wenqi)
// Created: 2012-11-19
////////////////////////////////////////////////////////////////////////
#ifndef _GLOBAL_CONSTDEF_HEADER_
#define _GLOBAL_CONSTDEF_HEADER_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>

extern int  g_nServerLine;					// ��������·��
extern int  g_nServerGroup;					// ���������
extern int	g_nServerStartTime;				// ����������ʱ�侫ȷ����
extern std::string g_strConstDatabaseName;	// ���������ݿ���
extern std::string g_strGameDatabaseName;	// ��Ϸ�����ݿ���
extern std::string g_strAccountDatabaseName;// �˺ŷ����ݿ���

const int	NAME_SIZE			= 32;							// ��ɫ������
const int	SYN_ANNOUNCE_SIZE	= 256;							// ���ɹ��泤��
const int	MAX_PACKETSIZE		= 1024;							// ������Ϣ���ߴ�
const int	MAX_MESSAGESIZE		= MAX_PACKETSIZE + 40;			// �ڲ���Ϣ���ߴ�
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



const int MAX_NEWCARD_LENGTH		= 19;				// ���ֿ���λ��
const int MAX_NEWCARD_HEADER_LENGTH	= 5;				// ���ֿ�ͷ��λ��
static const char* CONST_XS_NEWCARD_HEADER	= "CSMT-";	// ���ֿ�ͷ
static const char* CONST_MT_NEWCARD_HEADER	= "WSMT-";	// ý�忨ͷ
const int MT_NEWCARD_TYPE_OFFSET	= 1000;				// ý�忨����ƫ����

const int ITEM_TYPE_BEGIN			= 100000;			// ��Ʒ���Ϳ�ʼ

const int MAX_MAIL_ITEM_COUNT       = 6;				// �ʼ��������Ʒ����
const int MAX_MAIL_MONEY_COUNT      = 4;				// �ʼ�������������

const int MAX_LIVENESS_ID			= 50;				// ÿ�ջ�Ծ���ñ��Ծ�����ID

static const char* TALK_SYSTEM_NAME = "System";

const int MAX_USER_LEV = 100;							// �����ߵȼ�

const int SYNDICATE_MEMBER_VAILD_SECOND = 8 * 60 * 60;	// ���ɳ�Ա�б���Чʱ��

const int MAIL_EXIST_TIME		= 20 * 24 * 60 * 60;	// �ʼ�����ʱ��	20��
const int MAX_FIGHT_POKER_NUM	= 5;					// ����ս��������

const int GOOSE_TOWER_MAX_FLOOR = 15;					// ������������
const int GOOSE_TOWER_MAX_PAGE_SIXE = 6;				// ������ÿҳ������
const int GOOSE_TOWER_LEVEL_LIMIT = 20;					// ����������ĵȼ�����

const int MINE_MAX_MEMBER_COUNT = 3;					// ������Ա����

////////////////////////////////////////////////////////////////////////////////////////////////
// ����� start
const int TIME_OF_DAY_LENGTH	= 1000000;				// ÿ��ʱ�䳤��
const int DAY_UTC_SECONDS		= 1 * 24 * 60 * 60;		// һ���UTC��
const int SERVER_AWARD_CONFIG_MIN			= 1;		// �������౶������С����
const int SERVER_AWARD_CONFIG_MAX			= 16;		// �������౶�����������
const int SERVER_DROP_CHANCE_CONFIG_MIN		= 1;		// �������౶���伸����С����
const int SERVER_DROP_CHANCE_CONFIG_MAX		= 16;		// �������౶���伸���������
const int SERVER_DROP_NUM_CONFIG_MIN		= 1;		// �������౶����������С����
const int SERVER_DROP_NUM_CONFIG_MAX		= 16;		// �������౶���������������
/////////////////////////////////////////////////////////////////////////////////////////
// ������ʹ�õĳ������� start
const int		ALL_SERVER_LINE_TYPE	= 99999;				//  ��������·
const int		ALL_SERVER_GROUP_TYPE	= 99999;				//  �����ַ�������

const int DESIGN_VAS_LIMIT = 5000;	// �߻�����Ԫ�������޶�

/////////////////////////////////////////////////////////////////////////////////////////
// ���а�ʹ�õĳ������� start
const int		MAX_RANK_COUNT				= 50;				//  �ϰ�����
const int		MAX_RECORD_RANK_COUNT		= 10000;			//  ���ݿ��м�¼������
const int		MAX_ARENA_RECORD_RANK_COUNT	= 10000;			//  ���������ݿ��м�¼������
const int		OUT_OF_TOPLIST_RANK			= 999999;			//  δ�ϰ�
const int		MASK_TOPLIST_DAILY			= 9999;				// ÿ�հ����ʱ���¼����

//////////////////////////////////////////////////////////////////////////
// ����
const int MAX_SYNDICATE_MEMBER_AMOUNT	= 50;				// ÿ������50��
const int MAX_SYNDICATE_ELDER_AMOUNT	= 5;				// ÿ������5������
const int MAX_APPLY_SYNDICATE_AMOUNT	= 3;				// �����3�����ɷ�����������
const int APPLY_SYNDICATE_VAILD_SECOND	= 8 * 60 * 60;		// ������������Чʱ��
const int QUIT_SYNDICATE_CD_SECOND		= 1 * 60 * 60;		// �˳����ɺ�CDʱ��
const int REJOIN_SYNIDCATE_CD_SECOND	= 2 * 24 * 60 * 60;	// ���½���ԭ����CDʱ��
const int JOIN_SYNDICATE_3TIMES_SECOND	= 7 * 24 * 60 * 60;	// �೤ʱ���ڿ��Լ���3�ΰ���
const int LEADER_LOGOUT_TIME_BE_CHANGE	= 3 * 24 * 60 * 60;	// 3�첻���߾ͱ�����
const int LOG_IN_OUT_SYNDICATE_TIME		= 7 * 24 * 60 * 60;	// ��¼��������ʱ����Чʱ��
const int MAX_SYNDICATE_ANNOUNCE_LEN	= 76;				// �����ɹ��泤��
const int QUERY_SYNDICATE_LIST_COUNT	= 20;				// ��ѯ����ʱ�����б��а�����������
const int SYN_WORSHIP_TOTAL_LIMIT		= 1000000;			// ����Ĥ�ݽ����ۼƺ�����

/////////////////////////////////////////////////////////////////////////////////////////
// ������ʹ�õĳ������� start
const int		VIDEO_PATH_SIZE			= 64;				// ս��¼�񱣴�·������
const int		ARENA_VIDEO_SAVE_COUNT	= 10;				// ������¼����ౣ������ 
const int		ARENA_NO_CD				= 88888888;			// ��������CD
const int		ARENA_BATTLE_TYPE		= 11111;			// ���˾�����ս��type
const int		MULTI_ARENA_BATTLE_TYPE	= 22222;			// ���˾�����ս��type
const int		ARENA_DEFAULT_MAX_RANK	= 5000;				// ������Ĭ���������
const int		ARENA_AWARD_BASE		= 140;				// �������������½���ϵ��
const int		ARENA_AWARD_PER_SECOND	= 10;				// ÿ���ַ��ž��������������ĸ���
const int		ARENA_AWARD_LAST_RANK	= 999999;			// ���������һ��Ĭ������
const int		ARENA_AI_COUNT			= 1000;				// ������AI���� 
const int		ARENA_MULTI_OPEN_COUNT	= 15;				// ��Ӿ�����������Ҫ������

// ������ʹ�õĳ������� end
/////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
// �ɾͳ��� 
const int ACHIEVEMENT_BASE_VALUE		= 10000;			// �ɾ�id�Ļ���ֵ
const int ACHIEVEMENT_BRANCH_FINISHED	= 99999999;			// ��֧�ɾ�ȫ�����
const int ACHIEVEMENT_NOT_OPENED		= 99999998;			// �ɾ�δ����

/////////////////////////////////////////////////////////////////////////////////////////
// ����ϵͳ�ĳ������� start
const int SIGNATURE_MAX_SIZE			= 192;				// ����ǩ������(�ֽ�) 
const int MAX_FRIEND_REQUEST_LOAD		= 50;				// ��ҵ�½���ص��������������
const int MAX_FRIEND_PUSH_COUNT			= 20;				// ����������͸���
const int MAX_FRIEND_REQUEST_COUNT		= 20;				// �������󱣴��������
const int FRIEND_MATCHING_RANGE_LEV1	= 1;				// ����ƥ���һ��ɸѡ�ȼ���Χ
const int FRIEND_MATCHING_RANGE_LEV2	= 5;				// ����ƥ��ڶ���ɸѡ�ȼ���Χ
const int FRIEND_ONLINE					= 1;				// ��������
const int FRIEND_GIFT_GIVEN				= 2;				// ������
const int FRIEND_GIFT_GOT				= 1;				// ��������ȡ
const int FRIEND_GIFT_NONE				= 0;				// û������
const int FRIEND_REQUESTED				= -1;				// �Ѿ��������
const int FRIEND_STRANGER				= 0;				// İ����
const int FRIEND_REQUESTER				= 1;				// ����Ӻ�����
//const int FRIEND_FRIEND				= 2;				// ����
const int FRIEND_MAX_COUNT				= 50;				// ��������
const int FRIEND_PUSH_COUNT				= 10;				// ������������

/////////////////////////////////////////////////////////////////////////////////////////
// �����Ŷ���ϵͳ����
const int CONST_NTM_FIGHT_BATTER_TYPE				= 33333;	// ս������
const int CONST_NTM_FIGHT_FIGHT_PRE_TIME			= 15;		// ս��׼��ʱ��
const int CONST_NTM_FIGHT_PK_DEFEND_TIME			= 10;		// PK����ʱ��
const int CONST_NTM_FIGHT_CONNECT_SEFEND_TIME		= 30;		// ��������ʱ��
const int CONST_NTM_FIGHT_ROOM_MIN_USERNUM			= 5;		// ������������
const int CONST_NTM_FIGHT_RANK_FIRST_AWARD_RULE_ID	= 11;		// ��һ����������ID
const int CONST_NTM_FIGHT_RANK_SECOND_AWARD_RULE_ID	= 12;		// �ڶ�����������ID
const int CONST_NTM_FIGHT_RANK_THREE_AWARD_RULE_ID	= 13;		// ��������������ID
/////////////////////////////////////////////////////////////////////////////////////////
#endif // end of _GLOBAL_CONSTDEF_HEADER_