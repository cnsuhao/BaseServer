////////////////////////////////////////////////////////////////////////
// Import : ȫ���ļ���ö�ٶ��塣
// Moudle : GlobalEnumDef.h
// Author : �½���(Chen Jianjun)
// Create : 2015-6-19
////////////////////////////////////////////////////////////////////////
#ifndef _GLOBAL_ENUMDEF_H_
#define _GLOBAL_ENUMDEF_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

////////////////////////////////////////////////////////////////////////////////////////////////
// ��Ϣtype�Ŷ��崦, ����Э���ʱǿ�ƽ�Э�����ʽ����
enum _MSG_TYPE_DEFINE_
{
	_MSG_NONE							= 0,

	_MSG_RL_SERVER_BEGIN				= 100,	// ��ڷ���Ϣ��ʼ
	_MSG_RL_SERVER_REQ_LOGIN			= 101,	// �ͻ��������½
	_MSG_RL_SERVER_QUERY_ONLINE			= 102,	// ��ϵ����ѯ����
	_MSG_RL_SERVER_END					= 200,	// ��ڷ���Ϣ����

	// �ͻ��� ��½�߳� ��Ϣ����
	_MSG_LOGIN_BEGIN					= 1000,
	_MSG_LOGIN_CONNECT					= 1001,	// ����			C --> S
	_MSG_LOGIN_CONNECT_ACTION			= 1002,	// ���Ӳ���		C <-> S
	_MSG_LOGIN_USER_LIST				= 1003,	// ����б�		C <-- S
	_MSG_LOGIN_CREATE_NEW_USER			= 1004,	// �����½�ɫ	C <-> S
	_MSG_LOGIN_KICK_REASON				= 1005,	// �߳�ԭ��		C <-- S
	_MSG_LOGIN_END						= 2000,

	_MSG_GAME_BEGIN						= 5000,
	_MSG_GAME_KICK_REASON				= 5001,	// �߳�ԭ��				C <-- S
	_MSG_GAME_LOGIN_QUERY				= 5002,	// ��½��ѯ				C <-> S
	_MSG_GAME_SMALLACTION				= 5003,	// SmallAction��Ϣ		C <-> S
	_MSG_GAME_USER_INFO					= 5004,	// UserInfo				C <-- S
	_MSG_GAME_USER_ATTR					= 5005,	// UserAttr				C <-- S
	_MSG_GAME_USER_MONEY				= 5006,	// ����ͬ��				C <-- S
	_MSG_GAME_MASK						= 5007,	// ����ͬ��				C <-- S
	_MSG_GAME_TMP_DATA					= 5008,	// UserTmpData			C <-> S
	_MSG_GAME_TALK						= 5009, // ������Ϣ				C <-> S
	_MSG_GAME_NEWCARD					= 5010,	// ���ֿ�				C <-> S
	_MSG_GAME_NEWCARD_PRIZE				= 5011,	// ���ֿ�����			C <-- S
	_MSG_GAME_TASK						= 5012, // ����					C <-> S
	_MSG_GAME_ACTIVITIES				= 5013,	// �					C <-> S
	_MSG_GAME_SIGN						= 5014,	// ǩ��					C <-> S
	_MSG_GAME_BLACK_LIST				= 5015,	// ������				C <-> S
	_MSG_GAME_ONLINE_INFO				= 5016,	// ���������Ϣ			S <-> R
	_MSG_GAME_MAIL_LIST					= 5017,	// �ʼ��б�				C <-> S
	_MSG_GAME_MAIL_OPT					= 5018,	// �ʼ�����				C <-> S
	_MSG_GAME_SYN_SERVER				= 5019,	// ���ɷ���������Ϣ		S <-> R
	_MSG_GAME_SYN_CLIENT				= 5020,	// ���ɿͻ�����Ϣ		C <-> S
	_MSG_GAME_VIP						= 5021,	// VIP��Ϣ				C <-> S
	_MSG_GAME_POKER_ACT					= 5022,	// ���Ʋ���				C <-> S
	_MSG_GAME_POKER_INFO				= 5023,	// ������Ϣ				C <-- S
	_MSG_GAME_POKER_ATTR				= 5024,	// ��������				C <-- S
	_MSG_GAME_USER_QUERY_INFO			= 5025,	// UserQueryInfo		C <-> S
	_MSG_GAME_MONEYTREE					= 5026,	// ҡǮϵͳ				C <-> S
	_MSG_GAME_ACHIEVEMENT				= 5027,	// �ɾ�ϵͳ				C <-> S
	_MSG_GAME_LIVENESS					= 5028,	// ÿ�ջ�Ծ				C <-> S
	_MSG_GAME_SHOP						= 5029,	// �̵�ϵͳ				C <-> S
	_MSG_GAME_LOTTERY					= 5030,	// �齱ϵͳ				C <-> S
	_MSG_GAME_ITEM						= 5031,	// ��Ʒ��Ϣ				C <-> S
	_MSG_GAME_EQUIP						= 5032,	// װ����Ϣ				C <-> S
	_MSG_GAME_ITEM_HINT					= 5033,	// ��Ʒ��ʾ�����Ϣ		C <-- S
	_MSG_GAME_CHALLENGE_BOSS			= 5034,	// ��սboss				C <-> S
	_MSG_GAME_BATTLE_INIT_INFO			= 5035,	// ս����ʼ����Ϣ		C <-- S
	_MSG_GAME_BATTLE_INIT_FIGHTER		= 5036,	// ս����ʼ����ս��		C <-- S
	_MSG_GAME_BATTLE_END_INFO			= 5037,	// ս��������Ϣ			C --> S
	_MSG_GAME_MARKS_INFO				= 5038,	// ��ϵͳ���������Ϣ	C <-- S
	_MSG_GAME_BUFF						= 5039,	// BUFF��Ϣ				C <-- S
	
	_MSG_GAME_INSTANCE_ACT				= 5040, // ��������				C <-> S
	_MSG_GAME_GOOSE_TOWER				= 5043,	// ������				C <-> S
	_MSG_GAME_PUZZLE_BUFF				= 5044,	// �Թ�BUFF				C <-- S
	_MSG_GAME_PUZZLE					= 5045,	// �Թ�����				C <-> S
	_MSG_GAME_SYN_LIST					= 5046,	// �����б�				C <-- S
	_MSG_GAME_SYN_MEMBER_LIST			= 5047,	// ���ɳ�Ա�б�			C <-- S
	_MSG_GAME_SYN_INFO					= 5048,	// ��������				C <-- S
	_MSG_GAME_SELF_SYN_INFO				= 5049,	// �Լ���������			C <-- S
	_MSG_GAME_SYN_LOG					= 5050,	// ������־				C <-> S
	_MSG_GAME_MINE_CLIENT				= 5051,	// ����Ϣ				C <-> S
	_MSG_GAME_MERCENARY					= 5052,	// Ӷ��ϵͳ				C <-> S
	_MSG_GAME_POKER_VIEW				= 5053,	// ���Ʋ鿴��Ϣ			C <-- S
	_MSG_GAME_VAS_INFO					= 5055,	// Ԫ������				C <-- S
	_MSG_GAME_SYN_WORSHIP				= 5056,	// ����Ĥ�ݴ���			C <-> S
	_MSG_GAME_MINE_LOG_LIST				= 5057,	// ����־�б�			C <-> S
	_MSG_GAME_WAR_ROAD_ACT				= 5058,	// ս�۲���				C <-> S
	_MSG_GAME_WAR_ROAD_INFO				= 5059,	// ս����Ϣ				C <-- S
	_MSG_GAME_USER_MAC					= 5060,	// ���mac��ַ			C --> S
	_MSG_GAME_FRIEND_INVITE				= 5062,	// ��������				C <-> S
	_MSG_GAME_TALK_QUERY				= 5063, // ��ѯ����				C <-> S
	_MSG_GAME_WARROAD_TEAM_INFO			= 5064,	// �Ŷ�ս����Ϣ			C <-- S
	_MSG_GAME_WARROAD_TEAM_FIGHT_INFO	= 5065,	// �Ŷ�ս��ս����Ϣ		C <-- S
	_MSG_GAME_WARROAD_TEAM_RANK_INFO	= 5066,	// �Ŷ�ս��������Ϣ		C <-- S
	_MSG_GAME_WARROAD_TEAM_SERVER_RANK	= 5067,	// �Ŷ�ս��ȫ��������Ϣ	C <-- S
	_MSG_GAME_SYSTEM_SETTINGS			= 5068,	// ϵͳ����				C <-> S
	_MSG_GAME_WARROAD_TEAM_AWARD_LOG	= 5069,	// ��սս��Ʒ�����¼	C <-- S
	_MSG_GAME_ARENA_USER_INFO			= 5070,	// �����������Ϣ		C <-> S
	_MSG_GAME_ARENA_TARGET_INFO			= 5071,	// ������������Ϣ		C <-> S
	_MSG_GAME_ARENA_LOG					= 5072,	// ��������־			C <-> S
	_MSG_GAME_ARENA_ACT					= 5073,	// ����������			C <-> S
	_MSG_GAME_FRIEND_INFO				= 5074,	// ���Ѳ�ѯ��Ϣ			C <-> S
	_MSG_GAME_FRIEND_ACT				= 5075,	// ���Ѳ�����Ϣ			C <-> S
	_MSG_GAME_FRIEND_SEARCH				= 5076,	// ���Ѳ�����Ϣ			C <-> S
	_MSG_GAME_FRIEND_PUSH				= 5077,	// ����������Ϣ			C <-> S
	_MSG_GAME_TOPLIST_ARENA_LIST		= 5078,	// ���а񾺼�������		C <-> S
	_MSG_GAME_TOPLIST_ARENA_USER		= 5079,	// ���а񾺼���������� C <-> S
	_MSG_GAME_TOPLIST_COMMON			= 5080,	// ���а�ͨ������		C <-> S
	_MSG_GAME_TOPLIST_SYNLIST			= 5081,	// ���а񹫻�����		C <-> S
	_MSG_GAME_TOPLIST_SYNINFO			= 5082,	// ���а�鿴��������	C <-> S
	_MSG_GAME_TERRITORY_MAININFO		= 5083,	// ���ս��ѯ������		C <-> S
	_MSG_GAME_TERRITORY_TROOPS_LIST		= 5084,	// ���ս�����Ჿ���б�	C <-> S
	_MSG_GAME_TERRITORY_TROOPS_INFO		= 5085,	// ���ս��Ա��������	C <-> S
	_MSG_GAME_TERRITORY_USER_ACT		= 5086,	// �����Ҳ���			C <-> S
	_MSG_GAME_TERRITORY_USER_TROOPS		= 5087,	// ���ս��ѯ��Ҳ���	C <-> S
	_MSG_GAME_TERRITORY_FIGHT			= 5088,	// ���ս����ս��		S <-  R
	_MSG_GAME_TERRITORY_QUERY_FIGHTING  = 5089,	// ���ս�鿴ս��		C <-> S
	_MSG_GAME_SYN_MEMBER_APPLY_LIST		= 5090,	// ���ɳ�Ա�����б�		C <-- S
	_MSG_GAME_MINE_SERVER				= 5091, // �󶴷�������Ϣ		S <-> R
	_MSG_GAME_SYN_GIFT_BOX				= 5092, // ���������Ϣ			C <-> S
	_MSG_GAME_CROSS_NTM_ACT				= 5093, // �����Ŷ�������		C <-> S
	_MSG_GAME_CROSS_NTM_INFO			= 5094, // �����Ŷ�����Ϣ		C <-- S
	_MSG_GAME_CROSS_NTM_TIPS			= 5095, // �����Ŷ���TIPS		C <-- S
	_MSG_GAME_CROSS_NTM_RANK			= 5096, // �����Ŷ�������		C <-- S
	_MSG_GAME_CROSS_INFO				= 5097,	// ���������Ϣ			C <-> S
	_MSG_GAME_RELAY_DATABASE			= 5098, // ������ת���ݿ�		S <-> R
	_MSG_GAME_CROSS_RELAY_DATABASE		= 5099,	// �����ת���ݿ�		S <-> C
	_MSG_GAME_CLEAR_AWARD				= 5100, // ɨ��������Ϣ			C <-- S
	_MSG_GAME_CROSS_HGS_FIGHT			= 5101,	// ����ɽ��ս			C <-> S
	_MSG_GAME_CROSS_HGS_ROOM_FRUIT		= 5102,	// ����ɽ��ս����ˮ��	C <-- S
	_MSG_GAME_CROSS_ROOM_POS_INFO		= 5104, // ����������Ϣ			C <-> S
	_MSG_GAME_MINE_LOG					= 5105,	// ����־				C <-> S

	_MSG_GAME_END						= 7900,


	// php������ ��Ϣ����
	_MSG_PHP_BEGIN						= 7900,
	_MSG_PHP_PAY						= 8000,	// ��ֵ��Ϣ
	_MSG_PHP_KICK						= 8001,	// php����
	_MSG_PHP_END						= 9000,

	// ��ϵ��ȫ����Ϣ��ʼ
	_MSG_RELATION_BEGIN						= 10000,

	// ��ϵ��ֱ��ת��ȫ����Ϣ
	_MSG_RELATION_DIRCET_ALL_BEGIN			= 10000,
	_MSG_RELATION_DIRCET_ALL_END			= 12000,

	// ��ϵ��ֱ��ת����������Ϣ
	_MSG_RELATION_DIRCET_OTHER_BEGIN		= 12000,
	_MSG_RELATION_DIRCET_OTHER_TALK			= 12001,	// ����
	_MSG_RELATION_DIRCET_OTHER_END			= 15000,

	// ��Ҫ��ϵ��������Ϣ
	_MSG_RELATION_PROCESS_BEGIN				= 15000,
	_MSG_RELATION_PROCESS_LOGIN				= 15001,	// ��Ϸ����½����ϵ��
	_MSG_RELATION_PROCESS_ACTION			= 15002,	// ��Ϸ�����ϵ�� ͨ�ò���action
	_MSG_RELATION_PROCESS_NEWCARD			= 15003,	// ���ֿ���Ϣ
	_MSG_RELATION_PROCESS_ONLINE_INFO		= 15004,	// ���½�ɫ������Ϣ
	_MSG_RELATION_PROCESS_SYN_SERVER		= 15005,	// ���ɴ�����Ϣ
	_MSG_RELATION_PROCESS_MAIL				= 15006,	// �ʼ���Ϣ
	_MSG_RELATION_PROCESS_FRIEND			= 15007,	// ���Ѵ�����Ϣ
	_MSG_RELATION_PROCESS_TOPLIST			= 15008,	// ���а�ϵͳ
	_MSG_RELATION_PROCESS_REALY_DATABASE	= 15009,	// ��ת���ݿ�
	_MSG_RELATION_PROCESS_ARENA_ACT			= 15010,	// ������
	_MSG_RELATION_PROCESS_ACHIEVEMENT		= 15011,	// �ɾ�ϵͳ 
	_MSG_RELATION_PROCESS_ARENA_LOG			= 15012,	// ������
	_MSG_RELATION_PROCESS_TERRITORY_FIGHT	= 15013,	// ���ս
	_MSG_RELATION_PROCESS_MINE_SERVER		= 15014,	// �󶴴�����Ϣ
	_MSG_RELATION_PROCESS_MARKSINFO			= 15015,	// ������ʾ��Ϣ
	_MSG_RELATION_PROCESS_END				= 20000,
	
	// ��ϵ��ȫ����Ϣ����
	_MSG_RELATION_END						= 20000,

	// ���������������Ϣ
	_MSG_CROSS_BEGIN						= 20000,
	_MSG_CROSS_LOGIN						= 20001,	// ��ϵ����¼�����������Ϣ
	_MSG_CROSS_ACTION						= 20002,	// action		
	_MSG_CROSS_REALY_DATABASE				= 20003,	// �����ת���ݿ�
	_MSG_CROSS_END							= 30000,
};
////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
// ��ϵ��Action��Ϣ��action
enum MSG_RS_ACTION
{
	MSG_RS_ACTION_NONE = 0,
	MSG_RS_ACTION_USER_LOGIN,				// ��ɫ����			G --> R
	MSG_RS_ACTION_USER_LOGOUT,				// ��ɫ�ǳ�			G --> R
	MSG_RS_ACTION_USER_KICK,				// ��ɫ�߳�			G <-- R
	MSG_RS_ACTION_KICK_OTHER_LINE_ACCOUNT,	// �˺��߳� 		G --> R
	MSG_RS_ACTION_PAY_NOTIFY,				// ��ֵ֪ͨ			G <-- R
	MSG_RS_ACTION_ONLINE,					// ͬ������ 		G --> R
	MSG_RS_ACTION_RELOAD_TABLE,				// ���¼��س�����	G <-- R
	MSG_RS_ACTION_ADD_USER_ONLINE,			// ����������߱�	G <-- R
	MSG_RS_ACTION_DEL_USER_ONLINE,			// ɾ��������߱�	G <-- R
	MSG_RS_ACTION_CLOSE_SERVER,				// �ط�				G <-- R
	MSG_RS_ACTION_CROSS_MIN_ONLINE_LINE,	// ͬ�������������	G <-- R
};

// ���������Action��Ϣ��action
enum MSG_CS_ACTION
{
	MSG_CS_ACTION_NONE = 0,
	MSG_CS_ACTION_ONLINE,					// ͬ������ 		R --> C
	MSG_CS_ACTION_CLOSE_ALL_SERVER,			// �ط�				R <-- C
	MSG_CS_ACTION_CROSS_MIN_ONLINE_LINE,	// ͬ�������������	R <-- C
};

// �������������Ϣaction
enum MSG_SYN_SERVER_ACTION
{
	MSG_SYN_SERVER_ACTION_NONE = 0,
};

// ��ϵ�������ͳһ������
enum MSG_RS_ERR_CODE
{
	MSG_RS_ERR_CODE_SUCC = 0,
	MSG_RS_ERR_CODE_FAIL = 1,
	MSG_RS_ERR_CODE_KICK,				// ����
	MSG_RS_ERR_CODE_KICK_WAIT,			// �����ߵ�����������, �Ժ�����
	MSG_RS_ERR_CODE_LOGIN_GROUP_ERROR,	// ��½�����
	MSG_RS_ERR_CODE_LOGIN_KEY_ERROR,	// ��½key����
	MSG_RS_ERR_CODE_LOGIN_TIMEOUT,		// ��½ʱ�䳬ʱ
};

// ��������ͬһ������
enum MSG_CS_ERR_CODE
{
	MSG_CS_ERR_CODE_SUCCESS		= 0,
	MSG_CS_ERR_CODE_FAIL		= 1,
	MSG_CS_ERR_CODE_KICK,				// ����
	MSG_CS_ERR_CODE_KICK_WAIT,			// �����ߵ�����������, �Ժ�����
	MSG_CS_ERR_CODE_LOGIN_GROUP_ERROR,	// ��½�����
	MSG_CS_ERR_CODE_LOGIN_KEY_ERROR,	// ��½key����
	MSG_CS_ERR_CODE_LOGIN_TIMEOUT,		// ��½ʱ�䳬ʱ
};
////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
// �˺�����
enum ACCOUNT_TYPE
{
	ACCOUNT_TYPE_NORMAL			= 0,	// ����
	ACCOUNT_TYPE_GM				= 1,	// GM
	ACCOUNT_TYPE_VISTOR			= 2,	// �ο�
};

// �˺�״̬
enum ACCOUNT_STATUS
{
	ACCOUNT_STATUS_NORMAL		= 0,	// ����
	ACCOUNT_STATUS_STOP_BYTIME	= 1,	// ��ʱ��ͣ, ״̬����Ϊ���utcʱ��
	ACCOUNT_STATUS_STOP_FOREVER = 2,	// ���÷�ͣ
};

// ��Ӫ����
enum CAMP_TYPE
{
	CAMP_TYPE_BEGIN				= 0,
	CAMP_TYPE_EARTH				= 1,	// ��������
	CAMP_TYPE_SANTI				= 2,	// ��������
	CAMP_TYPE_GZWM				= 3,	// ��������
	CAMP_TYPE_END,
};
////////////////////////////////////////////////////////////////////////////////////////////////

enum GAME_OBJECT_TYPE
{
	GAME_OBJECT_TYPE_NONE	= 0x00000000,	// ��	
	GAME_OBJECT_TYPE_COMMON = 0x00000001,	// ͨ�ö���
	GAME_OBJECT_TYPE_USER	= 0x00000002,	// ��ɫ����
	GAME_OBJECT_TYPE_ITEM	= 0x00000004,	// ��Ʒ����
};

////////////////////////////////////////////////////////////////////////////////////////////////

// php��������
enum PHP_OPERATION_TYPE
{
	PHP_OPERATION_TYPE_NONE = 0,
	PHP_OPERATION_TYPE_PAY,
	PHP_OPERATION_TYPE_KICK,
};

#endif // end of _GLOBAL_ENUMDEF_H_