////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2012, WuHan ChuangYou, All Rights Reserved
// Moudle: GlobalEnumDef.h
// Author: ������(Peng Wenqi)
// Created: 2012-11-19
////////////////////////////////////////////////////////////////////////
#ifndef _GLOBAL_ENUMDEF_HEADER_
#define _GLOBAL_ENUMDEF_HEADER_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

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
	_MSG_GAME_LOGIN_QUERY				= 5001,	// ��½��ѯ				C <-> S
	_MSG_GAME_USER_INFO					= 5002,	// UserInfo				C <-- S
	_MSG_GAME_USER_ATTR					= 5003,	// UserAttr				C <-- S
	_MSG_GAME_USER_MONEY				= 5004,	// ����ͬ��				C <-- S
	_MSG_GAME_KICK_REASON				= 5005,	// �߳�ԭ��				C <-- S
	_MSG_GAME_MASK						= 5006,	// ����ͬ��				C <-- S
	_MSG_GAME_TMP_DATA					= 5007,	// UserTmpData			C <-> S
	_MSG_GAME_SMALLACTION				= 5008,	// SmallAction��Ϣ		C <-> S
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



enum GAME_OBJECT_TYPE
{
	GAME_OBJECT_TYPE_NONE	= 0x00000000,	// ��	
	GAME_OBJECT_TYPE_COMMON = 0x00000001,	// ͨ�ö���
	GAME_OBJECT_TYPE_USER	= 0x00000002,	// ��ɫ����
	GAME_OBJECT_TYPE_ITEM	= 0x00000004,	// ��Ʒ����
};

// �˺�����
enum ACCOUNT_TYPE
{
	ACCOUNT_TYPE_NORMAL		= 0,	// �����˺�
	ACCOUNT_TYPE_GM_LOW		= 1,	// GM�ͼ����˺�
	ACCOUNT_TYPE_GM_HI		= 2,	// GM�߼����˺�
};

// �˺�״̬
enum ACCOUNT_STATUS
{
	ACCOUNT_STATUS_NORMAL		= 0,	// ����
	ACCOUNT_STATUS_STOP_BYTIME	= 1,	// ��ʱ��ͣ, ״̬����Ϊ���utcʱ��
	ACCOUNT_STATUS_STOP_FOREVER = 2,	// ���÷�ͣ
};

// �Ա�����
enum SEX_TYPE
{
	SEX_TYPE_BEGIN		= 0,
	SEX_TYPE_GIRL		= 0,	// Ů
	SEX_TYPE_BOY		= 1,	// ��
	SEX_TYPE_END
};

////////////////////////////////////////////////////////////////////////////////////////////////
// ����ö��
// ������������
enum MONEY_FLOW_TYPE
{
	MONEY_FLOW_TYPE_AWARD	= 1,	// ���
	MONEY_FLOW_TYPE_SPEND	= 2,	// ����
};

// ��������ԭ��, ��������itemtype��
enum MONEY_FLOW_REASON_ITEMTYPE
{
	MONEY_FLOW_REASON_ITEMTYPE_NONE				= 0,
	MONEY_FLOW_REASON_ITEMTYPE_LUA				= 900000,	// �ű�����
	MONEY_FLOW_REASON_ITEMTYPE_CREATE_SYN		= 900001,	// ��������
	MONEY_FLOW_REASON_GM_CMD					= 900002,	// gm����
	MONEY_FLOW_REASON_MAGICPOINT				= 900003,	// �����ܵ�
	MONEY_FLOW_REASON_WORLD_TALK				= 900004,	// ��������
	MONEY_FLOW_REASON_AWARDMONEY				= 900005,	// ҡǮ
	MONEY_FLOW_REASON_EQUIP_STAR_EXP			= 900006,	// ����װ����ħ(����)
	MONEY_FLOW_REASON_EQUIP_STAR_ONEKEY			= 900007,	// ����װ��һ����ħ(����)
	MONEY_FLOW_REASON_REFRESH_SHOP				= 900008,	// ˢ���̵�
	MONEY_FLOW_REASON_MAIL						= 900009,	// �ʼ�
	MONEY_FLOW_REASON_BUY_SHOP_GOODS			= 900010,	// �����̵���Ʒ
	MONEY_FLOW_REASON_SKILL_LEV					= 900011,	// ��������
	MONEY_FLOW_REASON_UPDATE_TIME_RECOVER		= 900012,	// ��ʱ�ָ�
	MONEY_FLOW_REASON_ITEMTYPE_SALE				= 900013,	// ������Ʒ
	MONEY_FLOW_REASON_ITEMTYPE_COMPOUND			= 900014,	// �ϳ���Ʒ
	MONEY_FLOW_REASON_CHALLENGE_BOSS			= 900015,	// ��սboss
	MONEY_FLOW_REASON_BATTLE_DROP				= 900016,	// ս������
	MONEY_FLOW_REASON_LOTTERY					= 900017,	// �齱
	MONEY_FLOW_REASON_INSTANCE					= 900018,	// ����
	MONEY_FLOW_REASON_CREATE_SYN				= 900019,	// ��������
	MONEY_FLOW_REASON_CREATE_SYN_ROLLBACK		= 900020,	// �������ɻع�
	MONEY_FLOW_REASON_GOOSE_TOWER				= 900021,	// ������
	MONEY_FLOW_REASON_RESET_ARENA_CD			= 900022,	// ���þ�����CD
	MONEY_FLOW_REASON_GET_CUMULATIVE_AWARD		= 900023,	// ��ȡ�ۻ��Ķ�Ӿ�������
	MONEY_FLOW_REASON_UPDATE_HISTORY_RECORD		= 900024,	// ���¾�������ʷ��������
	MONEY_FLOW_REASON_EMPLOY_MERCENARY			= 900025,	// ��ӶӶ��
	MONEY_FLOW_REASON_MERCENARY_BACK			= 900026,	// �ջ�Ӷ��
	MONEY_FLOW_REASON_PAYVAS					= 900027,	// ��ֵԪ��
	MONEY_FLOW_REASON_FREEVAS					= 900028,	// ����Ԫ��
	MONEY_FLOW_REASON_MONTHVAS					= 900029,	// �¿�Ԫ��
	MONEY_FLOW_REASON_SEARCH_MINE				= 900030,	// ������
	MONEY_FLOW_REASON_CHALLENGE_MINE			= 900031,	// ��ս��
	MONEY_FLOW_REASON_SYN_WORSHIP				= 900032,	// ����Ĥ�ݴ���
	MONEY_FLOW_REASON_COLLECT_MINE				= 900033,	// �ɼ���
	MONEY_FLOW_REASON_WARROAD					= 900034,	// ս����ս
	MONEY_FLOW_REASON_SYN_WORSHIP_ROLLBACK		= 900035,	// ����Ĥ�ݴ���ع�
	MONEY_FLOW_REASON_GET_TERRITORY_MONEY		= 900036,	// ��ȡ�ۻ�����ر�
	MONEY_FLOW_REASON_FRIEND_INVITE				= 900037,	// ��������
	MONEY_FLOW_REASON_WARROAD_DIFFICULTY_RESET	= 900038,	// ���þ�Ӣս�۹ؿ�
	MONEY_FLOW_REASON_WARROAD_QUICK				= 900039,	// ս��ɨ��
	MONEY_FLOW_REASON_WARROAD_AWARD_CUT			= 900040,	// ս��Ʒ���
	MONEY_FLOW_REASON_ALTER_NAME				= 900041,	// �Ľ�ɫ��
	MONEY_FLOW_REASON_ALTER_NAME_CALLBACK		= 900042,	// �Ľ�ɫ���ع�
	MONEY_FLOW_REASON_FSP_MERCENARY				= 900043,	// ��������� ����Ӷ
	MONEY_FLOW_REASON_FRIEND_GIFT				= 900044,	// ��������   ��������
	MONEY_FLOW_REASON_POWER_RECOVER				= 900045,	// �����ָ�
	MONEY_FLOW_REASON_TREASURE_POWER_RECOVER	= 900046,	// Ѱ�������ָ�
	MONEY_FLOW_REASON_SIGN_IN					= 900047,	// ǩ������
	MONEY_FLOW_REASON_SYN_MONTHCARD_VAS			= 900048,	// ���������¿�Ԫ��
	MONEY_FLOW_REASON_ALTER_SEX					= 900049,	// ���Ա�
	MONEY_FLOW_REASON_ALTER_SEX_CALLBACK		= 900050,	// ���Ա�ع�
	MONEY_FLOW_REASON_ALTER_AGE					= 900051,	// ������
	MONEY_FLOW_REASON_ALTER_AGE_CALLBACK		= 900052,	// ������ع�
	MONEY_FLOW_REASON_ALTER_BIRTHDAY			= 900053,	// ������
	MONEY_FLOW_REASON_ALTER_BIRTHDAY_CALLBACK	= 900054,	// �����ջع�
	MONEY_FLOW_REASON_HGS_BATTLE				= 900055,	// ����ɽ����
	MONEY_FLOW_REASON_POWER_BUY					= 900056,	// �������� ����
	MONEY_FLOW_REASON_POWER_USE_ITEM			= 900057,	// �������� ʹ����Ʒ
	MONEY_FLOW_REASON_POWER_UP_LEV				= 900058,	// �������� ��ɫ����
	MONEY_FLOW_REASON_LIVENESS					= 900059,	// ��Ծ
	MONEY_FLOW_REASON_ACHEVEMENT				= 900060,	// �ɾ�
	MONEY_FLOW_REASON_OPEN_SYN_GIFTBOX			= 900061,	// �����������
	MONEY_FLOW_REASON_BUY_ARENA_COUNT			= 900062,	// ������̨��ս����
	MONEY_FLOW_REASON_BUY_MULTI_ARENA_COUNT		= 900063,	// ������̨�����ս����
	MONEY_FLOW_REASON_ITEMHINT_CUSTOM			= 900064,	// ������Ʒ��ʾʱ���,�Զ���ԭ��[%d]
	MONEY_FLOW_REASON_WARROADTEAM_PASS_AWARD	= 900065,	// �Ŷ�ս�۹ؿ����⽱��
};

// ��ֵ��ʵ״̬
enum PAY_VAS_STATUS
{
	PAY_VAS_STATUS_NONE		= 0,	// δ����
	PAY_VAS_STATUS_PASS		= 1,	// ͨ��
	PAY_VAS_STATUS_FAILD	= 2,	// �ܾ�
	PAY_VAS_STATUS_COMPLETE	= 3,	// ���
};
////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////
// ��Ʒ���ö�� start
// ��Ʒ����
enum ITEM_FLOW_TYPE
{
	ITEM_FLOW_TYPE_BEGIN		= 0,
	ITEM_FLOW_TYPE_AWARD		= 1,		// �����Ʒ
	ITEM_FLOW_TYPE_LOSE			= 2,		// ʧȥ��Ʒ
	ITEM_FLOW_TYPE_END,
};

// ��Ʒ����ԭ��
enum ITEM_FLOW_REASON
{
	ITEM_FLOW_REASON_NONE						= 0,
	ITEM_FLOW_REASON_RECHARGE					= 1,		// ��ֵ���
	ITEM_FLOW_REASON_OVERDUE					= 2,		// ��Ʒ����ɾ�� 
	ITEM_FLOW_REASON_TASK_USED_d				= 3,		// ����ʹ��,����id=��%d��
	ITEM_FLOW_REASON_TASK_AWARD_d				= 4,		// ������,����id=��%d��
	ITEM_FLOW_REASON_MAIL_AWARD					= 5,		// ͨ���ʼ���ȡ����Ʒ
	ITEM_FLOW_REASON_LUA_AWARD_d				= 6,		// �ű���ȡ,�ű�id=��%d��
	ITEM_FLOW_REASON_LUA_SPEND_d				= 7,		// �ű�ʹ��,�ű�id=��%d��
	ITEM_FLOW_REASON_GM_CMD_AWARD				= 8,		// GM������
	ITEM_FLOW_REASON_GM_CMD_SPEND				= 9,		// GM����ʹ��
	ITEM_FLOW_REASON_COMPOUND_POKER_SPEND		= 10,		// ���ƺϳ�����
	ITEM_FLOW_REASON_POKER_EXP_SPEND			= 11,		// �����ṩ��������
	ITEM_FLOW_REASON_REPEAT_POKER_AWARD			= 12,		// �ظ����ͬ���Ϳ��Ƹ�����Ʒ
	ITEM_FLOW_REASON_POKER_STAR_SPEND			= 13,		// ������������
	ITEM_FLOW_REASON_POKER_EQUIP_SPEND			= 14,		// ���ƴ���װ��ʹ��
	ITEM_FLOW_REASON_POKER_EQUIP_STAR_SPEND		= 15,		// ����װ������ʹ��
	ITEM_FLOW_REASON_SIGN_AWARD					= 16,		// ǩ���������
	ITEM_FLOW_REASON_ITEMTYPE_SHOP_AWARD		= 17,		// �̵깺����
	ITEM_FLOW_REASON_SALE						= 18,		// ����
	ITEM_FLOW_REASON_DEC						= 19,		// ɾ��
	ITEM_FLOW_REASON_COMPOUND					= 20,		// �ϳ�
	ITEM_FLOW_REASON_BATTLE_DROP_d				= 21,		// ս������, BattleType[%d]
	ITEM_FLOW_REASON_LOTTERY_SPEND				= 22,		// �齱����
	ITEM_FLOW_REASON_LOTTERY_AWARD				= 23,		// �齱���
	ITEM_FLOW_REASON_PUZZLE_INSTANCE			= 24,		// �Թ��������
	ITEM_FLOW_REASON_MINE						= 25,		// ��
	ITEM_FLOW_REASON_WARROAD_QUICK				= 26,		// ս��ɨ��
	ITEM_FLOW_REASON_WARROAD_AWARD_SEND			= 27,		// ս��Ʒ����
	ITEM_FLOW_REASON_CHALLENGE_BOSS				= 28,		// ��սbosss
	ITEM_FLOW_REASON_ADD_POWER_SPEND			= 29,		// ��������ʹ��
	ITEM_FLOW_REASON_SYN_GIFTBOX_OPEN			= 30,		// �����������
	ITEM_FLOW_REASON_ITEMHINT_CUSTOM			= 31,		// ������Ʒ��ʾʱ���,�Զ���ԭ��[%d]
};


// ��Ʒ���ö�� end
/////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////
// �������ö�� start
// ��������
enum POKER_FLOW_TYPE
{
	POKER_FLOW_TYPE_BEGIN			= 0,
	POKER_FLOW_TYPE_POKER_AWARD		= 1,	// ��ÿ���
	POKER_FLOW_TYPE_POKER_LOSE		= 2,	// ʧȥ����
	POKER_FLOW_TYPE_END,
};

// ��������ԭ��
enum POKER_FLOW_REASON
{
	POKER_FLOW_REASON_BEGIN				= 0,
	POKER_FLOW_REASON_NONE				= 1,	// Ĭ��
	POKER_FLOW_REASON_LUA_AWARD			= 2,	// �ű�
	POKER_FLOW_REASON_GM_CMD_AWARD		= 3,	// GM����
	POKER_FLOW_REASON_COMPOSE_AWARD		= 4,	// �ϳ�
	POKER_FLOW_REASON_VIP_AWARD			= 5,	// vip����
	POKER_FLOW_REASON_DROP_AWARD		= 6,	// ����
	POKER_FLOW_REASON_LOTTERY_AWARD		= 7,	// �齱
	POKER_FLOW_REASON_SIGN_IN			= 8,	// ǩ��
	POKER_FLOW_REASON_WARROAD_QUICK		= 9,	// ս��ɨ��
	POKER_FLOW_REASON_ITEMHINT_CUSTOM	= 10,   // ������Ʒ��ʾʱ���,�Զ���ԭ��[%d]
	POKER_FLOW_REASON_END,
};

// ������ɫ
enum POKER_COLOR
{
	POKER_COLOR_BEGIN		= 0,
	POKER_COLOR_WHITE		= 1,	// ��ɫ
	POKER_COLOR_GREEN		= 2,	// ��ɫ
	POKER_COLOR_GREEN1		= 3,	// ��ɫ+1
	POKER_COLOR_BLUE		= 4,	// ��ɫ
	POKER_COLOR_BLUE1		= 5,	// ��ɫ+1
	POKER_COLOR_BLUE2		= 6,	// ��ɫ+2
	POKER_COLOR_PURPLE		= 7,	// ��ɫ
	POKER_COLOR_PURPLE1		= 8,	// ��ɫ+1
	POKER_COLOR_PURPLE2		= 9,	// ��ɫ+2
	POKER_COLOR_PURPLE3		= 10,	// ��ɫ+3
	POKER_COLOR_PURPLE4		= 11,	// ��ɫ+4
	POKER_COLOR_ORANGE		= 12,	// ��ɫ
	POKER_COLOR_ORANGE1		= 13,	// ��ɫ+1
	POKER_COLOR_ORANGE2		= 14,	// ��ɫ+2
	POKER_COLOR_ORANGE3		= 15,	// ��ɫ+3
	POKER_COLOR_ORANGE4		= 16,	// ��ɫ+4
	POKER_COLOR_ORANGE5		= 17,	// ��ɫ+5
	POKER_COLOR_END,
};


// �������ö�� end
/////////////////////////////////////////////////////////////////////////////////////////////////////

// php��������
enum PHP_OPERATION_TYPE
{
	PHP_OPERATION_TYPE_NONE = 0,
	PHP_OPERATION_TYPE_PAY,
	PHP_OPERATION_TYPE_KICK,
};

////////////////////////////////////////////////////////////////////////////////////////////////
// ���ݿ�ö��
// ����������ö��

////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
enum EMSGNEWCARDRESULT			// ���ֿ�ʹ�ý��
{
	EMNCR_SUC					= 0,	// ��ȡ�ɹ�
	EMNCR_DEFAULT				= 1,	// ��������
	EMNCR_TIMEOUT				= 2,	// �������
	EMNCR_ERROCARD				= 3,	// ���Ų���
	EMNCR_HAVEPRIZE				= 4,	// ��ȡ�������Ϳ���
	EMNCR_HAVINGREWARD			= 5,	// �ÿ��ѱ�ʹ��
	EMNCR_CARDINVALID			= 6,	// ���Ѿ�����
	EMNCR_PLATFORM				= 7,	// ƽ̨����ȷ
	EMNCR_SERVER_GROUP			= 8,	// �������鲻��ȷ
	EMNCR_PACKFULL				= 9,	// �����ռ䲻��
	EMNCR_IP_ERROR				= 10,	// IP����
	EMNCR_NEWCARD_SYSERROR		= 11,	// ϵͳ������ѹرգ����Ժ�����

	EMNCR_RESULT_NOT_PROCESS	= 999,	// δ��������ֿ�
};
////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////
// ���ɳ�Ա�ȼ�
enum SYN_RANK_TYPE
{
	RANK_LEADER			= 3,	// ����
	RANK_ELDER			= 2,	// ����
	RANK_NORMAL			= 1,	// ����
	RANK_NONE			= 0,	// 		
};
////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
// ����ϵͳ

	// ���Ѳ���action
enum MSG_FRIEND_ACT_ACTION
{
	MSG_FRIEND_ACT_ACTION_BEGIN,
	MSG_FRIEND_ACT_ACTION_REQUEST		= 1,				// ����Ӻ���			C <-> S
	MSG_FRIEND_ACT_ACTION_REFUSE		= 2,				// �ܾ��Ӻ���			C <-> S
	MSG_FRIEND_ACT_ACTION_ACCEPT		= 3,				// ��Ӻ���				C <-> S
	MSG_FRIEND_ACT_ACTION_DELETE		= 4,				// ɾ������				C <-> S
	MSG_FRIEND_ACT_ACTION_ADD_FSP		= 5,				// �����������			C <-  S
	MSG_FRIEND_ACT_ACTION_GIVE_GIFT		= 6,				// ��������				C <-> S
	MSG_FRIEND_ACT_ACTION_GET_GIFT		= 7,				// ��ȡ����				C <-> S
	MSG_FRIEND_ACT_ACTION_GIVE_GIFT_ALL	= 8,				// һ������				C <-> S
	MSG_FRIEND_ACT_ACTION_GET_GIFT_ALL	= 9,				// һ������				C <-> S
	MSG_FRIEND_ACT_ACTION_GIVE_ROSE		= 10,				// ��õ��				C <-> S
	MSG_FRIEND_ACT_ACTION_CS_END		= 99,

	MSG_FRIEND_ACT_ACTION_SR_BEGIN		= 100,
	MSG_FRIEND_ACT_ACTION_REQUEST_REQ	= 101,				// ����Ӻ���		S -> R
	MSG_FRIEND_ACT_ACTION_REQUEST_ACK	= 102,				// ����Ӻ���		R -> S
	MSG_FRIEND_ACT_ACTION_REFUSE_REQ	= 103,				// �ܾ��Ӻ���		S -> R
	MSG_FRIEND_ACT_ACTION_REFUSE_ACK	= 104,				// �ܾ��Ӻ���		R -> S
	MSG_FRIEND_ACT_ACTION_ACCEPT_REQ	= 105,				// ��Ӻ���			S -> R
	MSG_FRIEND_ACT_ACTION_ACCEPT_ACK	= 106,				// ��Ӻ���			R -> S
	MSG_FRIEND_ACT_ACTION_DELETE_REQ	= 107,				// ɾ������			S -> R
	MSG_FRIEND_ACT_ACTION_DELETE_ACK	= 108,				// ɾ������			R -> S
	MSG_FRIEND_ACT_ACTION_ADD_FSP_REQ	= 109,				// ������߼������ S -> R
	MSG_FRIEND_ACT_ACTION_ADD_FSP_ACK	= 110,				// ������߼������ R -> S
	MSG_FRIEND_ACT_ACTION_GIVE_GIFT_REQ	= 111,				// �����������		S -> R
	MSG_FRIEND_ACT_ACTION_GIVE_GIFT_ACK	= 112,				// �����������		R -> S
	MSG_FRIEND_ACT_ACTION_GIVE_GIFT_ALL_REQ	= 113,			// ����һ������		S -> R
	MSG_FRIEND_ACT_ACTION_GIVE_GIFT_ALL_ACK	= 114,			// Ӧ��һ������		S <- R

	MSG_FRIEND_ACT_ACTION_GIVE_ROSE_REQ		= 115,			// ������õ��		S -> R
	MSG_FRIEND_ACT_ACTION_GIVE_ROSE_ACK		= 116,			// Ӧ����õ��		S <- R

	MSG_FRIEND_ACT_ACTION_SR_END		= 999,

	MSG_FRIEND_ACT_ACTION_END,
};
// ���Ѳ������
enum MSG_FRIEND_RESULT_TYPE
{
	MSG_FRIEND_RESULT_TYPE_BEGIN,
	MSG_FRIEND_RESULT_TYPE_SUCC						= MSG_FRIEND_RESULT_TYPE_BEGIN,	// �����ɹ�
	MSG_FRIEND_RESULT_TYPE_FAIL						= 1,							// ����ʧ��
	MSG_FRIEND_RESULT_TYPE_NOT_EXIST				= 2,							// id������
	MSG_FRIEND_RESULT_TYPE_NOT_FRIEND				= 3,							// ���Ǻ���
	MSG_FRIEND_RESULT_TYPE_OLD_FRIEND				= 4,							// �Ѿ��Ǻ���
	MSG_FRIEND_RESULT_TYPE_OFF_LINE					= 5,							// ������
	MSG_FRIEND_RESULT_TYPE_NOT_EXIST_OR_OFFLINE		= 6,							// �����߻򲻴���
	MSG_FRIEND_RESULT_TYPE_AT_THE_LIMIT				= 7,							// �����������
	MSG_FRIEND_RESULT_TYPE_EXIST_REQUESTER			= 8,							// �Ѿ�������ˣ����������ʱ��
	MSG_FRIEND_RESULT_TYPE_NOT_REQUESTER			= 9,							// ���������б�ɾ��������ʱ��
	MSG_FRIEND_RESULT_TYPE_EMPTY_LIST				= 10,							// �����б�Ϊ��
	MSG_FRIEND_RESULT_TYPE_START_SENDING			= 11,							// ��ʼ����(���ݷָʼ����
	MSG_FRIEND_RESULT_TYPE_SENDING					= 12,							// ���ڷ���(���滹�а���
	MSG_FRIEND_RESULT_TYPE_LAST_PACKAGE				= 13,							// ������
	MSG_FRIEND_RESULT_TYPE_NO_SUITABLE				= 14,							// û�к��ʵ�
	MSG_FRIEND_RESULT_TYPE_NOT_SELF					= 15,							// ��������Լ�
	MSG_FRIEND_RESULT_TYPE_GIFT_GOT					= 16,							// �Ѿ���ȡ��������
	MSG_FRIEND_RESULT_TYPE_NO_GIFT					= 17,							// û������
	MSG_FRIEND_RESULT_TYPE_GAVE_ROSE				= 18,							// �����õ������
	MSG_FRIEND_RESULT_TYPE_NO_GIFT_TO_GIVE			= 19,							// ���������������
	MSG_FRIEND_RESULT_TYPE_NO_GIFT_TO_GET			= 20,							// ���������������
	MSG_FRIEND_RESULT_TYPE_RECEIVE_GIFT				= 21,							// �յ�������
	MSG_FRIEND_RESULT_TYPE_END,
};

// ���������ԭ��ö��
enum FSP_ADD_REASON_TYPE
{
	FSP_ADD_REASON_TYPE_BEGIN,
	FSP_ADD_REASON_TYPE_MERCENARY		= 1,				// 	�����ѹ�Ӷ			
	FSP_ADD_REASON_TYPE_END,
};

// �̵�����
enum SHOP_ENUM
{
	SHOP_ENUM_BEGIN						= 1000,
	SHOP_ENUM_ARENA						= SHOP_ENUM_BEGIN,	// �������̵�
	SHOP_ENUM_TEAMS_ARENA				= 1001,				// ��Ӿ������̵�
	SHOP_ENUM_TOWER						= 1002,				// �������̵�
	SHOP_ENUM_SYN						= 1003,				// �����̵�
	SHOP_ENUM_COMMON					= 1004,				// ��ͨ�̵�
	SHOP_ENUM_BLACK_MARKET				= 1005,				// �����̵�
	SHOP_ENUM_FRIENDSHIP				= 1006,				// ������̵�
	SHOP_ENUM_END,
};

// �̵�ˢ������
enum SHOP_REFRESH_TYPE
{
	SHOP_REFRESH_TYPE_NONE	= 0,
	SHOP_REFRESH_TYPE_HAND	= 1,	// �ֶ�ˢ��
	SHOP_REFRESH_TYPE_AUTO	= 2,	// �Զ�ˢ��
};

////////////////////////////////////////////////////////////////////////////////////////////////
//�ɾ�ϵͳ
// �ɾ͸������ö�� (����ģ���������ʱʹ�ã�
enum ACHIEVEMENT_UPDATE_TYPE
{
	ACHIEVEMENT_UPDATE_TYPE_BEGIN,

	ACHIEVEMENT_UPDATE_TYPE_USER_LEV		= 1,		// ����ȼ�
	ACHIEVEMENT_UPDATE_TYPE_POKER_GET		= 2,		// ��ÿ���
	ACHIEVEMENT_UPDATE_TYPE_POKER_ADVANCED	= 3,		// ���׿���
	ACHIEVEMENT_UPDATE_TYPE_GATE			= 4,		// ��ͼ�ؿ�
	ACHIEVEMENT_UPDATE_TYPE_EQUIPMENT		= 5,		// װ��
	ACHIEVEMENT_UPDATE_TYPE_PIECE			= 6,		// Ӣ����Ƭ��
	ACHIEVEMENT_UPDATE_TYPE_FRIEND_INVITE	= 7,		// ��������
	ACHIEVEMENT_UPDATE_TYPE_END,
};

// �ɾͷ�֧ö��(�߻���Ҫ֪���ģ���Ӧachievement��id�ֶε���λ�ϣ�
enum ACHIEVEMENT_TYPE
{
	ACHIEVEMENT_TYPE_BEGIN					= 0,
	ACHIEVEMENT_TYPE_LEV					= 1,		// ����ȼ����
	ACHIEVEMENT_TYPE_POKER_COUNT			= 2,		// Ӣ�۸���
	ACHIEVEMENT_TYPE_POKER_COLOR			= 3,		// Ӣ����ɫ
	ACHIEVEMENT_TYPE_NORMAL_GATE			= 4,		// ��ͨ��ͼ
	ACHIEVEMENT_TYPE_HERO_GATE				= 5,		// Ӣ����ͼ
	ACHIEVEMENT_TYPE_NORMAL_CLEAR			= 6,		// ��ͨ�ؿ�ͨ�ش���
	ACHIEVEMENT_TYPE_HERO_CLEAR				= 7,		// Ӣ�۹ؿ�ͨ�ش���
	ACHIEVEMENT_TYPE_FRIEND_INVITE			= 8,		// ��������
	ACHIEVEMENT_TYPE_END,
};

// �ɾͿ����������߻���Ҫ֪���ģ���Ӧachievement��open_type�ֶΣ�
enum ACHIEVEMENT_OPEN_TYPE
{
	ACHIEVEMENT_OPEN_TYPE_BEGIN,
	ACHIEVEMENT_OPEN_TYPE_USER_LEV				= ACHIEVEMENT_TYPE_LEV,						// ����ҵȼ�����
	ACHIEVEMENT_OPEN_TYPE_POKER_COUNT			= ACHIEVEMENT_TYPE_POKER_COUNT,				// �ɿ����ռ���������
	ACHIEVEMENT_OPEN_TYPE_POKER_COLOR			= 3,										// ��ָ����ɫ������������
	ACHIEVEMENT_OPEN_TYPE_GATE					= 4,										// �ɹؿ�����
	ACHIEVEMENT_OPEN_TYPE_FRIEND_INVITE			= 5,										// �ɺ������봥��
	ACHIEVEMENT_OPEN_TYPE_OTHER_ACHIEVEMENT		= 9999,										// �������ɾ����ʱ����
	ACHIEVEMENT_OPEN_TYPE_END,
};

// �ɾ�ϵͳ��Ϣö��
enum MSG_ACHIEVEMENT_ACTION
{
	MSG_ACHIEVEMENT_ACTION_BEGIN,

	MSG_ACHIEVEMENT_ACTION_QUERY	= 1,		// ��ѯ��ҵ�ǰ�ɾͽ���			C<->S
	MSG_ACHIEVEMENT_ACTION_AWARDS,				// ��ȡ����						C<->S
	MSG_ACHIEVEMENT_ACTION_PUSH,				// ��ͻ��������Ѿ���ɵĳɾ�	C<- S
	MSG_ACHIEVEMENT_ACTION_INIT_SYNC,			// ���½�߳�ͬ���ɾͳ�ʼ����	G ->L

	MSG_ACHIEVEMENT_ACTION_UPDATE_REQ,			// ���ϵ������ͬ�����³ɾ�     S ->R
	MSG_ACHIEVEMENT_ACTION_UPDATE_ACK,			// ��ϵ����Ӧͬ�����³ɾ�		R ->S

	MSG_ACHIEVEMENT_ACTION_END,
};

enum MSG_ACHIEVEMENT_RESULT_TYPE
{
	MSG_ACHIEVEMENT_RESULT_TYPE_BEGIN			= 0,
	MSG_ACHIEVEMENT_RESULT_TYPE_SUCC			= MSG_ACHIEVEMENT_RESULT_TYPE_BEGIN,			// �����ɹ�
	MSG_ACHIEVEMENT_RESULT_TYPE_FAIL			= 1,											// ����ʧ��
	MSG_ACHIEVEMENT_RESULT_TYPE_NOT_OPENED		= 2,											// �ɾͻ�û����
	MSG_ACHIEVEMENT_RESULT_TYPE_NOT_ACHIEVED	= 3,											// �ɾ�Ҫ��δ�ﵽ
	MSG_ACHIEVEMENT_RESULT_TYPE_ID_NOT_CORRECT	= 4,											// �ɾ�id����
	MSG_ACHIEVEMENT_RESULT_TYPE_END,
};
////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
//���а�ϵͳ
// ���а���Ϣaction

	// ���а� ��ѯ������������Ϣaction
enum MSG_TOPLIST_ARENA_LIST_ACTION
{
	MSG_TOPLIST_ARENA_LIST_ACTION_BEGIN,
	MSG_TOPLIST_ARENA_LIST_ACTION_MULTI_LAST				= 1,	// ��ѯ���ڶ�Ӿ�������������		C<->S
	MSG_TOPLIST_ARENA_LIST_ACTION_MULTI_THIS				= 2,	// ��ѯ���ڶ�Ӿ�������������		C<->S
	MSG_TOPLIST_ARENA_LIST_ACTION_SINGLE_LAST				= 3,	// ��ѯ���ھ�������������			C<->S
	MSG_TOPLIST_ARENA_LIST_ACTION_SINGLE_THIS				= 4,	// ��ѯ���ھ�������������			C<->S
	MSG_TOPLIST_ARENA_LIST_ACTION_END,
};

	// ���а� ��ѯ�����������ϸ��Ϣ��Ϣaction
enum MSG_TOPLIST_ARENA_USER_ACTION
{
	MSG_TOPLIST_ARENA_USER_ACTION_BEGIN,
	MSG_TOPLIST_ARENA_USER_ACTION_MULTI_LAST				= 1,	// ��ѯ���ڶ�Ӿ������������		C<->S
	MSG_TOPLIST_ARENA_USER_ACTION_MULTI_THIS				= 2,	// ��ѯ���ڶ�Ӿ������������		C<->S
	MSG_TOPLIST_ARENA_USER_ACTION_SINGLE_LAST				= 3,	// ��ѯ���ھ������������			C<->S
	MSG_TOPLIST_ARENA_USER_ACTION_SINGLE_THIS				= 4,	// ��ѯ���ھ������������			C<->S
	MSG_TOPLIST_ARENA_USER_ACTION_END,
};

	// ���а�  ս�������а���Ϣaction
enum MSG_TOPLIST_COMMON_ACTION
{
	MSG_TOPLIST_COMMON_ACTION_BEGIN,
	MSG_TOPLIST_COMMON_ACTION_QUERY_ALL_POKER_FC			= 1,	// ��ѯȫ������ս����������			C<->S
	MSG_TOPLIST_COMMON_ACTION_QUERY_MULTI_POKER_FC			= 2,	// ��ѯ��ӿ���ս����������			C<->S
	MSG_TOPLIST_COMMON_ACTION_QUERY_TEAM_POKER_FC			= 3,	// ��ѯС�ӿ���ս����������			C<->S
	MSG_TOPLIST_COMMON_ACTION_QUERY_TOTAL_POKER_STAR		= 4,	// ��ѯ���п����Ǽ��ۺ����а�		C<->S
	MSG_TOPLIST_COMMON_ACTION_RESOURCE_PLUNDER_COUNT		= 5,	// ��ѯ��Դ�Ӷ������������			C<->S
	MSG_TOPLIST_COMMON_ACTION_RESOURCE_GOLD_COLLECTED		= 6,	// ��ѯ��Դ��Ҳɼ���������			C<->S
	MSG_TOPLIST_COMMON_ACTION_RESOURCE_DRUG_COLLECTED		= 7,	// ��ѯ��Դҩ���ɼ���������			C<->S
	MSG_TOPLIST_COMMON_ACTION_GLAMOUR_THIS					= 8,	// ��ѯһ��������������				C<->S
	MSG_TOPLIST_COMMON_ACTION_GLAMOUR_LAST					= 9,	// ��ѯ����������������				C<->S
	MSG_TOPLIST_COMMON_ACTION_GLAMOUR_TOTAL					= 10,	// ��ѯ��������������				C<->S

	MSG_TOPLIST_COMMON_ACTION_UPDATE_RG						= 101,	// ��ϵ��֪ͨ�������������а�		R ->S 

	MSG_TOPLIST_COMMON_ACTION_END,
};

	// ���а� ����������Ϣaction
enum MSG_TOPLIST_SYN_ACTION
{
	MSG_TOPLIST_SYN_ACTION_BEGIN,
	MSG_TOPLIST_SYN_ACTION_THREE_DAYSLIVENESS				= 1,	// ���3��Ծ������					C<->S			
	MSG_TOPLIST_SYN_ACTION_END,
};

// ���а���Ϣ���ö��
enum MSG_TOPLIST_RESULT_TYPE
{
	MSG_TOPLIST_RESULT_TYPE_BEGIN					= 0,
	MSG_TOPLIST_RESULT_TYPE_SUCC					= MSG_TOPLIST_RESULT_TYPE_BEGIN,		// �����ɹ�
	MSG_TOPLIST_RESULT_TYPE_FAIL					= 1,									// ����ʧ�� 
	MSG_TOPLIST_RESULT_TYPE_START_SENDING			= 2,									// ��ʼ����
	MSG_TOPLIST_RESULT_TYPE_SENDING					= 3,									// �м��
	MSG_TOPLIST_RESULT_TYPE_LAST_PACKAGE			= 4,									// ������
	MSG_TOPLIST_RESULT_TYPE_END,
};
// ���а����ö��(�߻���Ҫ֪���ģ�
enum TOPLIST_TYPE
{
	TOPLIST_TYPE_BEGIN,
	TOPLIST_TYPE_MULTI_ARENA_LAST					= 1,	// �������������				
	TOPLIST_TYPE_MULTI_ARENA_THIS					= 2,	// ��������ӱ���
	TOPLIST_TYPE_ARENA_LAST							= 3,	// ��������������
	TOPLIST_TYPE_ARENA_THIS							= 4,	// ���������ӱ���
	TOPLIST_TYPE_ALL_POKER_FC						= 5,	// ���п���ս����
	TOPLIST_TYPE_MULTI_POKER_FC						= 6,	// ��ӿ���ս����
	TOPLIST_TYPE_TEAM_POKER_FC						= 7,	// ���ӿ���ս����
	TOPLIST_TYPE_TOTAL_POKER_STAR					= 8,	// ���п����Ǽ���
	TOPLIST_TYPE_SYNDICATE_LIVENESS					= 9,	// �����Ծ��
	TOPLIST_TYPE_RESOURCE_PLUNDER					= 10,	// ��Դ�������
	TOPLIST_TYPE_RESOURCE_GOLD_COLLECTED			= 11,	// ��Ҳɼ���
	TOPLIST_TYPE_RESOURCE_DRUG_COLLECTED			= 12,	// ҩ���ɼ���

	TOPLIST_TYPE_ALL_POKER_FC_LAST					= 13,	// ���п���ս��������
	TOPLIST_TYPE_MULTI_POKER_FC_LAST				= 14,	// ��ӿ���ս��������
	TOPLIST_TYPE_TEAM_POKER_FC_LAST					= 15,	// ���ӿ���ս��������
	TOPLIST_TYPE_TOTAL_POKER_STAR_LAST				= 16,	// ���п����Ǽ�������
	//TOPLIST_TYPE_RESOURCE_PLUNDER_LAST				= 17,	// ��Դ�����������
	//TOPLIST_TYPE_RESOURCE_GOLD_COLLECTED_LAST		= 18,	// ��Ҳɼ�������
	//TOPLIST_TYPE_RESOURCE_DRUG_COLLECTED_LAST		= 19,	// ҩ���ɼ�������
	
	TOPLIST_TYPE_GLAMOUR_THIS						= 20,	// ����һ������
	TOPLIST_TYPE_GLAMOUR_LAST						= 21,	// ������������
	TOPLIST_TYPE_GLAMOUR_TOTAL						= 22,	// ����������

	TOPLIST_TYPE_THIS								= 1000,	// ʵʱ����
	TOPLIST_TYPE_DAILY								= 1001,	// �����հ�
	TOPLIST_TYPE_WEEKLY								= 1002,	// �����ܰ�
	TOPLIST_TYPE_END,
};
////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
//������ϵͳ
// ������������Ϣaction
enum MSG_ARENA_ACT_ACTION
{
	MSG_ARENA_ACT_ACTION_BEGIN,
	MSG_ARENA_ACT_ACTION_SAVE_DEFENSE_TEAM_INFO				= 1,		// ���浥�ӷ�������					C<->S
	MSG_ARENA_ACT_ACTION_SAVE_ATTACK_TEAM_INFO				= 2,		// ���浥�ӽ�������					C<->S
	MSG_ARENA_ACT_ACTION_RESET_CD							= 3,		// ���õ��Ӿ�������սCD				C<->S
	MSG_ARENA_ACT_ACTION_FIGHT								= 4,		// �������Ӿ�����ս��				C<->S
	MSG_ARENA_ACT_ACTION_QUERY_ATTACK_TEAM_INFO				= 5,		// ��ѯ������ҽ���������Ϣ			C<->S
	MSG_ARENA_ACT_ACTION_MULTI_SAVE_DEFENSE_TEAM_INFO		= 6,		// �����ӷ�������					C<->S
	MSG_ARENA_ACT_ACTION_MULTI_SAVE_ATTACK_TEAM_INFO		= 7,		// �����ӽ�������					C<->S
	MSG_ARENA_ACT_ACTION_MULTI_RESET_CD						= 8,		// ���ö�Ӿ�������սCD				C<->S
	MSG_ARENA_ACT_ACTION_MULTI_FIGHT						= 9,		// ������Ӿ�����ս��				C<->S
	MSG_ARENA_ACT_ACTION_QUERY_MULTI_ATTACK_TEAM_INFO		= 10,		// ��ѯ�����ҽ���������Ϣ			C<->S
	MSG_ARENA_ACT_ACTION_MULTI_GET_CUMULATIVE_AWARD			= 11,		// ��ȡ����ۻ�������				C<->S
	MSG_ARENA_ACT_ACTION_BUY_COUNT							= 12,		// ������ս����						C<->S

	MSG_ARENA_ACT_ACTION_INSERT_RANK_REQ					= 103,		// ���ϵ���������������¼			S ->R
	MSG_ARENA_ACT_ACTION_INSERT_RANK_ACK					= 104,		// ��ϵ��Ӧ�����������¼			R ->S
	MSG_ARENA_ACT_ACTION_END,

};

// ��������־��Ϣaction
enum MSG_ARENA_LOG_ACTION
{
	MSG_ARENA_LOG_ACTION_BEGIN,				
	MSG_ARENA_LOG_ACTION_SINGLE				= 1,		// ��ѯ������־				C<->S
	MSG_ARENA_LOG_ACTION_MULTI				= 2,		// ��ѯ�����־				C<->S
	MSG_ARENA_LOG_ACTION_RESULT				= 3,		// ս�����					S ->C

	MSG_ARENA_LOG_ACTION_SAVE_RESULT_REQ	= 101,		// ���ϵ�����󱣴���		S ->R
	MSG_ARENA_LOG_ACTION_SAVE_RESULT_ACK	= 102,		// ��ϵ��Ӧ�𱣴���		R ->S
	MSG_ARENA_LOG_ACTION_NotifyBeAtk		= 103,		// ������֪ͨ				R ->S

	MSG_ARENA_LOG_ACTION_UPDATE_RANK_INFO	= 104,		// ֪ͨ��Ϸ������������Ϣ	R ->S
	MSG_ARENA_LOG_ACTIONN_END,
};

// ��������Ϣ���ö��
enum MSG_ARENA_RESULT_TYPE
{
	MSG_ARENA_RESULT_TYPE_BEGIN,
	MSG_ARENA_RESULT_TYPE_SUCC								= MSG_ARENA_RESULT_TYPE_BEGIN,		// �����ɹ�
	MSG_ARENA_RESULT_TYPE_FAIL								= 1,								// ����ʧ�� 
	MSG_ARENA_RESULT_TYPE_NO_LOG							= 2,								// û����־
	MSG_ARENA_RESULT_TYPE_START_SENDING						= 3,								// ������͵��װ�
	MSG_ARENA_RESULT_TYPE_SENDING							= 4,								// ������͵��м��
	MSG_ARENA_RESULT_TYPE_LAST_PACKAGE						= 5,								// ������͵�β��
	MSG_ARENA_RESULT_TYPE_ATTACK_TEAM_IS_EMPTY				= 6,								// ��������Ϊ��
	MSG_ARENA_RESULT_TYPE_NO_CD_ALREADY						= 7,								// �Ѿ���CD��
	MSG_ARENA_RESULT_TYPE_NO_ENOUGH_VAS						= 8,								// Ԫ������
	MSG_ARENA_RESULT_TYPE_NO_ENOUGH_AWARD					= 9,								// û���㹻���ۻ�������ȡ
	MSG_ARENA_RESULT_TYPE_NOT_OPEN							= 10,								// ������û����
	MSG_ARENA_RESULT_TYPE_IS_FIGHTING						= 11,								// ��ս��������
	MSG_ARENA_RESULT_TYPE_NOT_ENOUGH_POKER					= 12,								// ���ս������������
	MSG_ARENA_RESULT_TYPE_NOT_ENOUGH_VIP_LEV				= 13,								// VIP�ȼ����� 
	MSG_ARENA_RESULT_TYPE_RUN_OUT_OF_BUY_COUNT				= 14,								// �������������
	MSG_ARENA_RESULT_TYPE_END,
};
// �������ֱ�ö��
enum ARENA_KIND_TYPE
{
	ARENA_KIND_TYPE_BEGIN,
	ARENA_KIND_TYPE_SINGLE_TEAM					= 1,											// ���Ӿ�����
	ARENA_KIND_TYPE_MULTI_TEAM					= 2,											// ��Ӿ�����
	ARENA_KIND_TYPE_END,
};

// ��������������
enum ARENA_POKER_TEAM_TYPE
{
	ARENA_POKER_TEAM_TYPE_BEGIN,
	ARENA_POKER_TEAM_TYPE_SINGLE_ATTACK			= 1,			// ���ӽ�����
	ARENA_POKER_TEAM_TYPE_SINGLE_DEFENSE		= 2,			// ���ӷ��ض�
	ARENA_POKER_TEAM_TYPE_MULTI_ATTACK			= 3,			// ��ӽ�����
	ARENA_POKER_TEAM_TYPE_MULTI_ATTACK_FIRST	= 4,			// ��ӽ���1��
	ARENA_POKER_TEAM_TYPE_MULTI_ATTACK_SECOND	= 5,			// ��ӽ���2��
	ARENA_POKER_TEAM_TYPE_MULTI_ATTACK_THIRD	= 6,			// ��ӽ���3��
	ARENA_POKER_TEAM_TYPE_MULTI_DEFENSE			= 7,			// ��ӷ��ض�
	ARENA_POKER_TEAM_TYPE_MULTI_DEFENSE_FIRST	= 8,			// ��ӷ���1��
	ARENA_POKER_TEAM_TYPE_MULTI_DEFENSE_SECOND	= 9,			// ��ӷ���2��
	ARENA_POKER_TEAM_TYPE_MULTI_DEFENSE_THIRD	= 10,			// ��ӷ���3��
	ARENA_POKER_TEAM_TYPE_END,
};

// ������ս�����
enum ARENA_RESULT_TYPE
{
	ARENA_RESULT_TYPE_BEGIN,
	ARENA_RESULT_TYPE_WIN,
	ARENA_RESULT_TYPE_LOSE,
	ARENA_RESULT_TYPE_END,
};

////////////////////////////////////////////////////////////////////////////////////////////////
// ���ս ս����Ϣaction
enum MSG_TERRITORY_FIGHT_ACTION
{
	MSG_TERRITORY_FIGHT_ACTION_BEGIN,
	MSG_TERRITORY_FIGHT_ACTION_START_FIGHTING_RS				= 101,			// ��ʼս��				R -> S
	MSG_TERRITORY_FIGHT_ACTION_TERRITORY_CAPTURED_SR			= 102,			// ��ر�ռ��			S -> R
	MSG_TERRITORY_FIGHT_ACTION_END,
};

// ���ս��Ϣ���ö��
enum MSG_TERRITORY_RESULT_TYPE
{
	MSG_TERRITORY_RESULT_TYPE_BEGIN,
	MSG_TERRITORY_RESULT_TYPE_SUCC								= MSG_ARENA_RESULT_TYPE_BEGIN,		// �����ɹ�
	MSG_TERRITORY_RESULT_TYPE_FAIL								= 1,								// ����ʧ��
	MSG_TERRITORY_RESULT_TYPE_ACTIVITY_NOT_START				= 2,								// �δ��ʼ
	MSG_TERRITORY_RESULT_TYPE_ACTIVITY_STARTING					= 3,								// ��Ѿ���ʼ
	MSG_TERRITORY_RESULT_TYPE_NOT_JOIN_SYNDICATE				= 4,								// ���û�м��빫��
	MSG_TERRITORY_RESULT_TYPE_START_SENDING						= 5,								// ��ʼ�����������ʱ���ã�
	MSG_TERRITORY_RESULT_TYPE_SENDING							= 6,								// ���ڷ���(���滹�а���
	MSG_TERRITORY_RESULT_TYPE_LAST_PACKAGE						= 7,								// ������
	MSG_TERRITORY_RESULT_TYPE_NO_MONEY_BE_LEFT					= 8,								// û���ۻ��ҿ�����ȡ
	MSG_TERRITORY_RESULT_TYPE_NOT_PREPARE						= 9,								// ����׼���׶β��ܲ�������  
	MSG_TERRITORY_RESULT_TYPE_TERRITORY_NEED_DEFENSE			= 10,								// �������Ҫ���� 
	MSG_TERRITORY_RESULT_TYPE_ACTIVITY_NOT_FIGHTING				= 11,								// �����ս���׶�
	MSG_TERRITORY_RESULT_TYPE_NOT_JOIN_THIS_FIGHTING			= 12,								// û�вμӸ���ص�ս��
	MSG_TERRITORY_RESULT_TYPE_THIS_FIGHTING_OVER				= 13,								// �����ڸ���ص�ս���Ѿ����� 
	MSG_TERRITORY_RESULT_TYPE_END,
};
////////////////////////////////////////////////////////////////////////////////////////////////

// �ʼ��б�Э��Action
enum EMSG_MAIL_LIST_ACTION
{
	EMSG_MAIL_LIST_ACT_QueryMailList	= 1,	// �����ʼ��б�			C --> S
	EMSG_MAIL_LIST_ACT_ReturnMailList	= 2,	// ���������ʼ��б�		C <-- S
	EMSG_MAIL_LIST_ACT_NewMailNotify	= 3,	// ���ʼ�����			C <-- S	S <-> R
};

// �ʼ�״̬
enum EMAIL_STATUS
{
	EMAIL_STATUS_Begin		= 0,
	EMAIL_STATUS_UNREAD		= EMAIL_STATUS_Begin,	// δ��
	EMAIL_STATUS_READ		= 1,					// �Ѷ�
	EMAIL_STATUS_Del		= 2,					// ɾ��
	EMAIL_STATUS_End,
};

// �������ֱ�id����
// ע��: 1. ת���%��಻����ȫ�Ƿ��� 2.�����������Ҫ�ٷֺ�, ��Ҫ��дȫ�ǵİٷֺ�
enum CONFIG_TEXT_ID
{
	CONFIG_TEXT_ID_NONE											= 0,

	// ��������������
	CONFIG_TEXT_ID_USER_NOT_FIND_USER							= 2,		// ��Ҳ����ڻ�����
	CONFIG_TEXT_ID_USER_TO_FAST									= 3,		// ������Ϣ����
	CONFIG_TEXT_ID_USER_INVALID_INFO							= 4,		// ���Ϸ�����Ϣ
	CONFIG_TEXT_ID_USER_LESS_LEV								= 5,		// �ȼ�����
	CONFIG_TEXT_ID_USER_LESS_VAS								= 6,		// Ԫ������
	CONFIG_TEXT_ID_USER_STOP_TALK								= 7,		// ������

	// ����
	CONFIG_TEXT_ID_CREATESYN_ss									= 201,		// %s��������%s
	CONFIG_TEXT_ID_SYN_RANK_LEADER								= 202,      // ����
	CONFIG_TEXT_ID_SYN_RANK_ELDER								= 203,      // ����
	CONFIG_TEXT_ID_SYN_RANK_NORMAL								= 204,      // ����

	// �����ŶӰ������
	CONFIG_TEXT_ID_GROUP_SYN_NOT_EXIST							= 2001,		// ���ɲ�����

	// �ʼ�����������Begin(5001 - 5100)
	CONFIG_TEXT_ID_MAIL_SENDER_SYSTEM							= 5001,		// ϵͳ


	// �ʼ�����Begin(5101 - 5200)
	CONFIG_TEXT_ID_MAIL_TITLE_SYSTEM							= 5101,		// ϵͳ��ʾ
	CONFIG_TEXT_ID_MAIL_TITLE_ARENA_AWARD						= 5102,		// ������ÿ����������
	CONFIG_TEXT_ID_MAIL_TITLE_ARENA_UPDATE_RECORD				= 5103,		// ������������ʷ��¼ ����


	// �ʼ�����Begin(5201 - 5400)
	CONFIG_TEXT_ID_MAIL_CONTENT_SYSTEM							= 5201,		// ϵͳ
	CONFIG_TEXT_ID_MAIL_CONTEXT_NEWCARD							= 5202,		// �װ�����ң���ϲ�����ֿ�ʹ�óɹ���������½������뼰ʱ��ȡŶ��
	CONFIG_TEXT_ID_MAIL_CONTEXT_AERNA_AWARD_d					= 5203,		// ��ϲ���ھ�����������ȡ�á�%d�����ĺóɼ�������������õĽ�����
	CONFIG_TEXT_ID_SYN_REFUSEAPPLY								= 5204,		// ���ź�����%s������ܾ�����ļ������룡
	CONFIG_TEXT_ID_SUN_QUIT										= 5205,		// ���Ѿ��뿪�ˡ�%s�����ᣬ�㽫��1Сʱ���޷������κι��ᣬ����48Сʱ�ڲ��ܻص�ԭ���ᣬ��Щ���������ڹ�����Ķ�����
	CONFIG_TEXT_ID_MAIL_CONTEXT_WORSHIP_AWARD_LEAVE				= 5206,		// ���Ѿ��뿪���᡾%s��,��Щ������֮ǰ���ᱻĤ�����ջ��ͭ��,�����!
	CONFIG_TEXT_ID_MAIL_CONTEXT_WORSHIP_AWARDSYN_DISMISS		= 5207,		// ��Ĺ����ѽ�ɢ,��Щ������֮ǰ���ᱻĤ�����ջ��ͭ��,�����!
	CONFIG_TEXT_ID_MAIL_CONTENT_ARENA_UPDATE_RECORD				= 5208,		// ��ϲ���ڶ���̨������ȡ�á�%d��������óɼ�������������õĽ�����
	CONFIG_TEXT_ID_MAIL_CONTENT_WARROAD_AWARD_GIVE				= 5209,		// ��%s���������һ��ս��Ʒ���뼰ʱ��ȡŶ��
	CONFIG_TEXT_ID_MAIL_CONTENT_WARROAD_AWARD_CUT				= 5210,		// �������ս��Ʒ��%s������%s����ӣ�����������Ĳ������뼰ʱ��ȡŶ��
	CONFIG_TEXT_ID_MAIL_CONTENT_WARROAD_COMPLETE_AWARD			= 5211,		// ��İ���������ŶӸ�����%s������ĵ�������˺�������%d�����%d�ﹱ������
	CONFIG_TEXT_ID_MAIL_CONTENT_WARROAD_COMPLETE_AWARD_EXTRA	= 5212,		// �������޶���ʱ������ɸ����������Ŷӳ�Ա������%d�ﹱ��

	// ������־Begin(5401 - 5450)
	CONFIG_TEXT_ID_SYN_LOG_CREATE_SYN							= 5401,		// ��%s����������
	CONFIG_TEXT_ID_SYN_LOG_DIRECT_JOIN_SYN						= 5402,		// ��%s�����빫��
	CONFIG_TEXT_ID_SYN_LOG_EXIT_SYN								= 5403,		// ��%s���˳�����
	CONFIG_TEXT_ID_SYN_LOG_KICK_SYN								= 5404,		// ����%s��%s������%s���߳��˹���
	CONFIG_TEXT_ID_SYN_LOG_AlTER_NOTICE							= 5405,		// ����%s��%s���޸��˹��ṫ��
	CONFIG_TEXT_ID_SYN_LOG_UP_ELDER								= 5406,		// �᳤��%s������%s������Ϊ����
	CONFIG_TEXT_ID_SYN_LOG_DOWN_MEMBER							= 5407,		// �᳤��%s��ȡ���ˡ�%s���ĳ���ְλ
	CONFIG_TEXT_ID_SYN_LOG_RESET_INSTANCE 						= 5408,		// ����%s��%s���������ŶӸ�������%d��
	CONFIG_TEXT_ID_SYN_LOG_PASS_INSTANCE  						= 5409,		// �ŶӸ���:��%d��ͨ��,���һ���ɡ�%s�����
	CONFIG_TEXT_ID_SYN_LOG_TRANSFER_LEADER						= 5410,		// ��%s�����᳤ְλ�ƽ����ˡ�%s��
	CONFIG_TEXT_ID_SYN_LOG_TROPHY_QUEUE							= 5411,		// ��%s����ս��Ʒ%s�Ķ����в��
	CONFIG_TEXT_ID_SYN_LOG_AGREE_JOIN_SYN						= 5412,		// ����%s��%s����׼�ˡ�%s�����빫��
	CONFIG_TEXT_ID_SYN_LOG_ALTER_LEV_LIMIT						= 5413,		// ����%s��%s���޸��˼��빫����Сս�ӵȼ�Ϊ��%d��
	CONFIG_TEXT_ID_SYN_LOG_SHARE_TROPHY							= 5414,		// ����%s��%s����%s������ˡ�%s��
	CONFIG_TEXT_ID_SYN_LOG_ALTER_NEED_CHECK						= 5415,		// ����%s��%s���޸��˹�������Ϊ������֤
	CONFIG_TEXT_ID_SYN_LOG_ALTER_NO_CHECK						= 5416,		// ����%s��%s���޸��˹�������Ϊ������Ҫ��֤
	CONFIG_TEXT_ID_SYN_LOG_AUTO_TRANSFER_LEADER					= 5417,		// �᳤��%s����ʱ��δ���ߣ��᳤ְλ�Զ����ø���%s��
	// ������־End(5401 - 5450)

	CONFIG_TEXT_ID_ITEM_POWER_NOT_ENOUGH_d						= 10001,	// ��������, ��Ҫ������%d����
	CONFIG_TEXT_ID_ITEM_POWER_DEL_d								= 10002,	// ����-%d
	CONFIG_TEXT_ID_ITEM_POWER_ADD_d								= 10003,	// ����+%d
	CONFIG_TEXT_ID_ITEM_POWER_FULL								= 10004,	// ��������
	CONFIG_TEXT_ID_ITEM_AMOUNT_LIMIT							= 10005,	// ��Ʒ�ѵ��������ޣ��޷���ã�

	CONFIG_TEXT_ID_END,
};

// ���ñ������ֶ�, �����������õ����ݼ�����������, �ǵ�д�������ע�ͺ����ݿ�comment�ֶ�
enum CONFIG_TYPE
{
	CONFIGTYPE_NONE												= 0,
	CONFIGTYPE_USER_CFG											= 1,		// ������ã�DATA1:������ȼ�
	CONFIGTYPE_USER_TALK_TIME_LIMIT								= 2,		// ����ʱ���� DATA1:˽��, DATA2:�������� DATA3:��������
	CONFIGTYPE_USER_POKER_CFG1									= 3,		// �������ã�DATA1:���ܵ㶨ʱ����ʱ����, DATA2:���ܵ㶨ʱ���ӵ���,DATA3:ÿ�ι�����ļ��ܵ��� DATA4:�����ܵ㻨��Ԫ����,
	CONFIGTYPE_USER_POKER_CFG2									= 4,		// �������ã�DATA1:װ����ħ������ҵȼ�, DATA2:���Ƴ�ʼ���Ƶȼ�, DATA3:���ƿ������Ƶȼ�
	CONFIGTYPE_USER_SHOP_BLACK_MARKET							= 5,		// �����̵꣺DATA1�������̵����ʱ������DATA2�������̵���ָ���
	CONFIGTYPE_USER_LOTTERY_CFG1								= 6,		// �齱���ã�DATA1�����ÿ����ѳ������DATA2����ҳ���ȴʱ�䣬DATA3��Ԫ������ȴʱ�䣬DATA4��VIP�ʸ�����Ƶȼ�
	CONFIGTYPE_USER_LOTTERY_CFG2								= 7,		// �齱���ã�DATA1���Ǽ����˳��ָ���, DATA2���Ǽ����˳���ʱ��, DATA3: ��һ�ν�ҳ��ÿ�������, DATA4: ��һ��Ԫ�����ÿ�������
	CONFIGTYPE_MERCENARY_CAMP_CFG								= 8,		// Ӷ�����ã�DATA1��Ӷ������פ��ʱ��, DATA2������Ӷ����Ӷ��ȴʱ��, DATA3��ս��Ӷ����Ӷ��ȴʱ��, DATA4:ʹ��Ӷ����õ��������, DATA5��������Ӷ����Ӷ���Ƶȼ�
	CONFIGTYPE_CROSS_NTM_FIGHT_CFG								= 9,		// �����Ŷ������ã�DATA1��������, DATA2��Ŀ���, DATA3��׼���׶�ʱ�䣬DATA4����ս�׶�ʱ��

	CONFIGTYPE_POKER_LEV_SCORE_CFG								= 10,		// ���Ƶȼ�ս���������ã�DATA1��Ӣ�۵ȼ��ṩ��ս��
	CONFIGTYPE_POKER_SKILL_SCORE_CFG1							= 11,		// ���Ƽ���ս���������ã�DATA1:��ɫ���ܼ���ս����DATA2:��ɫ����ϵ��*100��DATA3:��ɫ���ܼ���ս����DATA4:��ɫ����ϵ��*100
	CONFIGTYPE_POKER_SKILL_SCORE_CFG2							= 12,		// ���Ƽ���ս���������ã�DATA1:��ɫ���ܼ���ս����DATA2:��ɫ����ϵ��*100��DATA3:��ɫ���ܼ���ս����DATA4:��ɫ����ϵ��*100
	CONFIGTYPE_POKER_ATTR_SCORE_CFG1							= 13,		// ��������ս���������ã�DATA1:��Ѫ��DATA2:���У�DATA3:�˺���DATA4:������DATA5:�ٶ�
	CONFIGTYPE_POKER_ATTR_SCORE_CFG2							= 14,		// ��������ս���������ã�DATA1:��ܣ�DATA2:������DATA3:��Ѫ�ظ���DATA4:��ŭ�ظ���DATA5:�ﱬ
	CONFIGTYPE_POKER_ATTR_SCORE_CFG3							= 15,		// ��������ս���������ã�DATA1:������DATA2:��Ѫ�ȼ���DATA3:��ŭ���Ľ���%��DATA4:����Ч�����%��DATA5:�������ֻ���

	CONFIGTYPE_BATTER_DROP_RULE_CFG1							= 16,		// ս������������ã�DATA1:1���ޣ�DATA2:2���ޣ�DATA3:3���ޣ�DATA4:4���ޣ�DATA5:5����
	CONFIGTYPE_BATTER_DROP_RULE_CFG2							= 17,		// ս������������ã�DATA1:6���ޣ�DATA2:7���ޣ�DATA3:8����

	CONFIGTYPE_USER_FRIEND_GIFT									= 101,		// ������������ DATA1������������������
	// CONFIGTYPE_USER_FRIEND_DATA								= 102,		// ������������ DATA1���������ޣ�DATA2���Ѻöȶ�ʱ���ӵ�����DATA3����ʱ����Ƶ��(��λ���ӣ�,DATA4���Ѻö�����,DATA5:���͵���
	// CONFIGTYPE_USER_FRIEND_REQUEST							= 103,		// ������������ DATA1���������뱣��ʱ��(��λСʱ),
	// CONFIGTYPE_USER_FRIEND_PUSH								= 104,		// ������������ DATA1��������������

	CONFIGTYPE_USER_LIVENESS_BOX								= 111,		// ÿ�ջ�Ծ Data1 - Data4:��Ծ�ȴﵽ25, 50, 75, 100�ı��䷢���ű�Action, data5:��ȡ�¿���õĻ�Ծ��

	CONFIGTYPE_SYNDICATE_CREATE_LIMIT							= 201,		// �������� data1��Ҫ��ҵȼ�, data2��ҪԪ��
	CONFIGTYPE_SYNDICATE_ACTIVITY_LIMIT							= 202,		// ���ɻ�Ծ data1����ÿ�ջ�Ծ����, data2��Աÿ�ջ�Ծ����
	CONFIGTYPE_SYNDICATE_TERRITORY								= 203,		// �������ս data1���ÿ�춨ʱ������رҵ�ʱ��(Сʱ0~23��,

	// ����ϵͳ ��¼��־��ֵ����ռ�� 1001~1051
	CONFIGTYPE_MONEY_BEGIN										= 1001,		// DATA1:�������� DATA2:��ֵⷧ(δ����ֵ��д��)��DATA3������������9999���ã�
	CONFIGTYPE_MONEY_TERRITORY									= 1002,		// ��ر� 
	CONFIGTYPE_MONEY_END										= 1051,


	// �������
	CONFIGTYPE_CHALLENGE_BOSS_INFO								= 3001,		// ��սboss data1��ʾͨ����������ֵ, data2��ʾʧ����������ֵ, data3ÿ��������ս����, data4�������ȼ�����
	CONFIGTYPE_INSTANCE_PASS_CFG								= 3002,		// �������ã�DATA1:��Ҹ�����ս������DATA2:���鸱����ս������DATA3:����ʧ����������
	CONFIGTYPE_GOOSE_TOWER										= 3003,		// ������:data1:ÿ���һ�����ÿɻ�õĴ�������, data2:��������Ӧ��ս������, data3:�����������ű�ID
	CONFIGTYPE_PUZZLE_CFG										= 3004,		// �Թ�����:data1:����ÿ����������data2:���ÿ����������data3:ħ��ÿ��������
	CONFIGTYPE_PUZZLE_FLOOR_CFG									= 3005,		// �Թ�����:data1-data5��ʾ1-5��Ĭ��վ������
	CONFIGTYPE_PUZZLE_FLOOR_COUNT_CFG							= 3006,		// �Թ�����:data1:�͵ȼ�������data2:�еȼ�������data3���ߵȼ�����
	CONFIGTYPE_MINE_CFG											= 3007,		// ������:data1:��Ѱ�������ָ�����, data2:ս������Ѱ����������, data3:���������ȼ���ֵ, data4:�󶴱���ս��������, data5:��ս������
	CONFIGTYPE_MINE_RAND_VAS_NUM_CFG							= 3008,		// ������:data1-data5 ��ʾ��ʯ������
	CONFIGTYPE_MINE_RAND_VAS_RATE_CFG							= 3009,		// ������:data1-data5 ��ʾ��ʯ�ļ���
	CONFIGTYPE_WARROAD_CFG1										= 3010,		// ս������:DATA1:��ͨ�;�Ӣģʽʧ����������, DATA2:��Ӣģʽÿ�����ս������DATA3:��ͨ�;�Ӣģʽɨ�����ĵ��ߣ�DATA4:ɨ������������DATA5:ɨ��һ������Ԫ��
	CONFIGTYPE_WARROAD_CFG2										= 3011,		// ս������:DATA1:�Ŷ�ģʽÿ��ر�ʱ�䣬DATA2:�Ŷ�ģʽÿ�쿪��ʱ�䣬DATA3:�Ŷ�ģʽս��Ʒ����ʱ�䣬DATA4:�Ŷ�ģʽս��Ʒ���Ž���ʱ��, DATA5:�Ŷ�ģʽս��Ʒ����ʱ����
	CONFIGTYPE_WARROAD_CFG3										= 3012,		// ս������:DATA1:�Ŷ�ģʽ׼��ʱ��,DATA2:�Ŷ�ģʽս��ʱ��
	CONFIGTYPE_MINE_TREASUREPOWER_CFG							= 3013,		// Ѱ����������:data1:��ʱ�ָ�ʱ��, data2:��ʱ�ָ�����
	CONFIGTYPE_INSTANCE_END										= 3999,		

	// ��־ϵͳ���
	CONFIGTYPE_LOG_BEGIN										= 4000,
	CONFIGTYPE_LOG_END											= 4999,

	// ���а񾺼���ϵͳ���
	CONFIGTYPE_TOPLIST_BEGIN									= 5000,
	CONFIGTYPE_TOPLIST_ARENA									= 5001,		// ���˾�������DATA1�������ս������DATA2����ս��ȴʱ�䣨��λ�룩��DATA3�����÷���,DATA4:�����ȼ�
	CONFIGTYPE_TOPLIST_ARENA_TARGET_RANK1						= 5002,		// ���˾��������������趨��DATA1����һ�����ޣ�DATA2����һ������(��Ϊ��ֱȣ�
	CONFIGTYPE_TOPLIST_ARENA_TARGET_RANK2						= 5003,		// ���˾��������������趨��DATA1���ڶ������ޣ�DATA2���ڶ�������(��Ϊ��ֱȣ�
	CONFIGTYPE_TOPLIST_ARENA_TARGET_RANK3						= 5004,		// ���˾��������������趨��DATA1�����������ޣ�DATA2������������(��Ϊ��ֱȣ�
	CONFIGTYPE_TOPLIST_ARENA_MULIT								= 5011,		// ���˾�������DATA1�������ս����, DATA2����ս��ȴʱ�䣨��λ�룩, DATA3�����÷���,DATA4:�����ȼ�
	CONFIGTYPE_TOPLIST_ARENA_MULTI_TARGET_RANK1					= 5012,		// ���˾��������������趨��DATA1����һ�����ޣ�DATA2����һ������(��Ϊ��ֱȣ�
	CONFIGTYPE_TOPLIST_ARENA_MULTI_TARGET_RANK2					= 5013,		// ���˾��������������趨��DATA1���ڶ������ޣ�DATA2���ڶ�������(��Ϊ��ֱȣ�
	CONFIGTYPE_TOPLIST_ARENA_MULTI_TARGET_RANK3					= 5014,		// ���˾��������������趨��DATA1�����������ޣ�DATA2������������(��Ϊ��ֱȣ�
	CONFIGTYPE_TOPLIST_UPDATE_TIME								= 5015,		// ���а����ʱ�䣺DATA1���հ����ʱ�䣨��λ��Сʱ ��Χ0~23)
	CONFIGTYPE_TOPLIST_ARENA_TIME								= 5016,		// ����������ʱ�䣺DATA1�����Ӿ�����ÿ�ս�������ȡʱ�䣨��λ��Сʱ ��Χ0~23��
	CONFIGTYPE_TOPLIST_ARENA_MULTI_MASK							= 5017,		// ��Ӿ�����������������:DATA1���ڲ�ȫ��������DATA2���ڲصڶ�����������DATA3���ڲص���������
	CONFIGTYPE_TOPLIST_ARENA_OPEN_LEV							= 5018,		// �����������ȼ����ã�DATA1�����ӿ����ȼ���DATA2����ӿ����ȼ�
	CONFIGTYPE_TOPLIST_END										= 5999,
	
	CONFIGTYPE_SYN_WORSHIP_FREE									= 6000,		// ����Ĥ�ݴ��� ���Ĥ�ݣ�data1:Ĥ������, data2:Ĥ�ݻ�õ�����ֵ, data3:��Ĥ�ݽ�������, data4:��Ĥ�ݽ������� 
	CONFIGTYPE_SYN_WORSHIP_GOLD									= 6001,		// ����Ĥ�ݴ��� ���Ĥ�ݣ�data1:Ĥ������, data2:Ĥ�ݻ�õ�����ֵ, data3:��Ĥ�ݽ�������, data4:��Ĥ�ݽ������� 
	CONFIGTYPE_SYN_WORSHIP_VAS									= 6002,		// ����Ĥ�ݴ��� ��ʯĤ�ݣ�data1:Ĥ������, data2:Ĥ�ݻ�õ�����ֵ, data3:��Ĥ�ݽ�������, data4:��Ĥ�ݽ�������
	CONFIGTYPE_FRIEND_INVITE									= 6003,		// �������� data1:�����뽱���ű�Action, data2:����������������ȼ�, data3:������ֱ�(1000��ʾ10%)

	CONFIGTYPE_TALK_RECORD_LIMIT								= 6004,		// ��������:data1:���������¼����; data2:���������¼����; data3:˽�ļ�¼����
	CONFIGTYPE_SYSTEM_SETTINGS									= 6005,		// ϵͳ����:data1:��������Ԫ������, data2:���Ա�����Ԫ������, data3:����������Ԫ������, data4:Ĭ��ͷ��ID, data5:Ĭ��ͷ���
	CONFIGTYPE_SYSTEM_POWER										= 6006,		// ������data1:�����ָ�ʱ������data2��������ʱ�ָ�����, data3��������������
	CONFIGTYPE_HGS_FIGHT_CONFIG1								= 6007,		// ����ɽ��ս����1��data1:�������Я��ˮ������, data2:ÿ��ˢ��ˮ��������, data3:����ɽ��ս��ͼ��(X), data4:����ɽ��ս��ͼ��(Y)
	CONFIGTYPE_BLACK_LIST										= 6008,		// ��������data1:��������
	CONFIGTYPE_TALK_CONFIG										= 6009,		// ���죺data1:�������컨��(Ԫ��)

	
	CONFIGTYPE_END,
};

// ��������
enum USER_MONEY_TYPE
{
	USER_MONEY_TYPE_NONE			= 0,
	USER_MONEY_TYPE_BEGIN			= 100,
	USER_MONEY_TYPE_MONEY			= 101,	// ���
	USER_MONEY_TYPE_POWER			= 102,	// ����
	USER_MONEY_TYPE_SKILL_POINT		= 103,	// ���ܵ�
	USER_MONEY_TYPE_SYN_PROF		= 104,	// �ﹱ
	USER_MONEY_TYPE_CHALLENGE		= 105,	// ������
	USER_MONEY_TYPE_CHALLENGE_TOP	= 106,	// �۷徺����
	USER_MONEY_TYPE_TOWER			= 107,	// ��������
	USER_MONEY_TYPE_TREASURE_POWER	= 108,	// Ѱ������
	USER_MONEY_TYPE_PUZZLE			= 109,	// �Թ���
	USER_MONEY_TYPE_TERRITORY		= 110,	// ��ر�
	USER_MONEY_TYPE_FRIENDSHIP_POINT= 111,	// �������
	USER_MONEY_TYPE_HGS_BATTLE_SCORE= 112,	// ����ɽ��ս����
	USER_MONEY_TYPE_END,

	USER_MONEY_TYPE_VAS				= 998,	// Ԫ��, ʵʱ��д�˺ſ�
};

enum MONTH_CARD_TYPE					// �¿�����
{
	MONTH_CARD_TYPE_NONE		= 0,
	MONTH_CARD_TYPE_NORMAL		= 1,	// ��ͨ�¿�
	MONTH_CARD_TYPE_SYN			= 2,	// ���������¿�
};

// ������
enum MINE_TYPE
{
	MINE_TYPE_Beg		= 0,
	MINE_TYPE_GOLD_MINE = 1,	// ���
	MINE_TYPE_DREAM_BOOK= 2,	// �ؾ���
	MINE_TYPE_End,
};

// ���ģ
enum MINE_SCALE
{
	MINE_SCALE_Beg		= 0,
	MINE_SCALE_SMALL	= 1,	// С��
	MINE_SCALE_MIDDLE	= 3,	// ����
	MINE_SCALE_BIG		= 10,	// ����
	MINE_SCALE_End,
};

// Ĥ�ݴ�����ϢAction
enum MSG_SYN_WORSHIP_ACTION
{
	MSG_SYN_WORSHIP_ACT_QueryWorshipInfo		= 1,	// �����ѯĤ����Ϣ			C --> S
	MSG_SYN_WORSHIP_ACT_ReturnWorshipInfo		= 2,	// ���������ѯĤ����Ϣ		C <-- S
	MSG_SYN_WORSHIP_ACT_ReqWorship				= 3,	// ����Ĥ��					C --> S
	MSG_SYN_WORSHIP_ACT_AckWorship				= 4,	// ��������Ĥ��				C <-- S
	MSG_SYN_WORSHIP_ACT_ReqGainAward			= 5,	// ������ȡ��Ĥ�ݽ���		C --> S
	MSG_SYN_WORSHIP_ACT_AckGainAward			= 6,	// ����������ȡ��Ĥ�ݽ���	C <-- S
	MSG_SYN_WORSHIP_ACT_UpdateBeworshipInfo		= 7,	// ͬ����Ĥ����Ϣ			C <-- S
};

// �������ID������ռ������ö��				�����ʹ��:��λ����ID (0 - 5000) ��������ID(10000 - 20000)
enum E_USER_MASKID_PROGRAM
{
	// ��������ID��ʼ
	// ������ID����

	// ��������ID��ʼ
	EUMIP_GIVE_BIT_LOTTERY					= 1,		// �齱�������
	EUMIP_GIVE_BIT_USER_SYSTEMSETTINGS		= 2,		// ����ϵͳ����޸ı��(λ0������λ1�Ա�)
	// ��������ID����

	// ������ID��ʼ
	EUMIP_DAY_BIT_LiveBoxStatus				= 1,		// ÿ�ջ�Ծ ��Ծ�ȱ���򿪱��(Ŀǰʹ�õ�2����5������λ)
	EUMIP_DAY_BIT_LiveAwardStatus			= 2,		// ÿ�ջ�Ծ ��Ծ�����ȡ���(Ŀǰʹ�õ�1����50������λ)
	EUMIP_DAY_BIT_MsgSwitchReceivePower		= 3,		// ϵͳ������Ϣ���� ÿ�ջ�Ծ������ȡ���ͱ��(�ֱ��ʾ��ͣ���ͣ�ҹ��)
	EUMIP_DAY_BIT_MsgSwitchRefreshShop		= 4,		// ϵͳ������Ϣ���� �̵�ˢ�����ͱ��(�ֱ��ʾˢ��ʱ��1��ˢ��ʱ��5)

	EUMIP_DAY_COUNT_LiveValues				= 10001,	// ÿ�ջ�Ծ ��ǰ��Ծ��
	EUMIP_DAY_COUNT_LiveCountBeg			= 10002,	// ÿ�ջ�Ծ�������ʼ(10002 - 10052)
	EUMIP_DAY_COUNT_LiveCountEnd			= 10052,	// ÿ�ջ�Ծ���������(10002 - 10052)
	EUMIP_DAY_COUNT_LOTTERY_MONEY			= 10053,	// ÿ�ս����ѵ���ʹ�ô���
	EUMIP_DAY_COUNT_INSTANCE_MONEY			= 10054,	// ÿ�ս�Ҹ�����ս����
	EUMIP_DAY_COUNT_INSTANCE_EXP			= 10055,	// ÿ�վ��鸱����ս����
	EUMIP_DAY_COUNT_SYN_MONTH_CARD			= 10056,	// ÿ�հ��������¿���ȡ��¼
	EUMTP_DAY_COUNT_BUY_ARENA_COUNT			= 10058,	// ÿ�վ������������
	EUMTP_DAY_COUNT_BUY_MULTI_ARENA_COUNT	= 10059,	// ÿ�ն�Ӿ������������
	EUMTP_DAY_COUNT_BUFF_QXXL_COUNT			= 10060,	// ÿ��buff����Э�����Ӵ���
	// ������ID����

	// ������ID��ʼ
	// ������ID����

	// ������ID��ʼ
	EUMIP_MONTH_BIT_SIGN					= 1,		// ÿ��ǩ������
	// ������ID����
};

// ������������ID������ռ������ö��			�����ʹ��:��λ����ID (0 - 10000)
enum E_GROUPSERVER_MASKID_PROGRAM
{
	EGSMP_BEN								= 0,
	EGSMP_ARENA_DAILY						= 1,		// ������ÿ�հ�����
	EGSMP_TOPLIST_DAILY						= 2,		// ���а�ÿ�հ�����
	EGSMP_TOPLIST_WEEKLY					= 3,		// ���а�ÿ�ܰ�����
	EGSMP_END								= 10000,
};

// ���������ID������ռ������ö��			�����ʹ��:��λ����ID (0 - 10000)
enum E_WORLDSERVER_MASKID_PROGRAM
{
	EWSMP_BEN								= 0,
	EWSMP_CHALLENGE_BOSS					= 1,		// ��սbossÿ��BosssType����
	EWSMP_END								= 10000,
};

// VIP����ö��
enum VIP_TYPE
{
	VIP_TYPE_Beg								= 1000,
	VIP_TYPE_DAY_CLEAN_ROLL						= 1001,	// ÿ����ȡɨ����
	VIP_TYPE_POWER_BUY							= 1002,	// ������������	
	VIP_TYPE_WAVE_MONEY_COUNT					= 1003,	// ҡǮ������		
	VIP_TYPE_SKILL_POINT_LIMIT					= 1004,	// ���ܵ�����			
	VIP_TYPE_PLANT_FIELD_COUNT					= 1005,	// ����ֲ�����			
	VIP_TYPE_DAY_WORSHIP_BIGGOD_COUNT			= 1006,	// ÿ���Ĥ�ݴ������		
	VIP_TYPE_VAS_CLEAN_BARRIER					= 1007,	// Ԫ��ɨ���ؿ�			
	VIP_TYPE_RESET_ELITE_BARRIER_COUNT			= 1008,	// ���þ�Ӣ�ؿ�����			
	VIP_TYPE_VAS_BUY_SKILL_STREN_POINT			= 1009,	// Ԫ��������ǿ����		
	VIP_TYPE_DAY_BUY_ARENA_COUNT				= 1010,	// ÿ�칺�򾺼�������		
	VIP_TYPE_ARENA_CD_RESET_BYVAS				= 1011,	// ��������սCDԪ����0		
	VIP_TYPE_MANY_ARENA_BUY_COUNT				= 1012,	// ��Ӿ������������		
	VIP_TYPE_MANY_ARENA_CD_RESET_BYVAS			= 1013,	// ��Ӿ�����CDԪ����0		
	VIP_TYPE_ONEKEY_CLEAN_TEN					= 1014,	// һ��ɨ��ʮ��				
	VIP_TYPE_SYNINSTANCE_DAY_PROFFER_ADD		= 1015,	// ���ɸ���ÿ������ﹱ+50%	
	VIP_TYPE_SYNINSTANCE_MONEY_ADD				= 1016,	// ���ɸ������+100%		
	VIP_TYPE_ONEKEY_EQUIP_MAGIC					= 1017,	// һ��װ����ħ				
	VIP_TYPE_RANDOM_MAN_FOREVER_EXIST			= 1018,	// ����������ô���			
	VIP_TYPE_SYN_VAS_WORSHIP					= 1019,	// ����Ԫ��Ĥ��				
	VIP_TYPE_TOWER_DAY_RESET_TWO				= 1020,	// ������ÿ�������2��		
	VIP_TYPE_HIGH_RANDOM_SHOP_FOREVER_EXIST		= 1021,	// �߼�����̵����ô���		
	VIP_TYPE_SPECIFIC_HERO						= 1022,	// V12����Ӣ��				
	VIP_TYPE_TOWER_AWARD						= 1023,	// �����������Һ���Ʒ����+50%	
	VIP_TYPE_MERCENARY_NUM						= 1024,	// �ܹ���ǲ��Ӷ������	
	VIP_TYPE_DAY_TEAM_INS_CHALLENGE_COUNT		= 1025,	// �ŶӸ���ÿ����ս����
	VIP_TYPE_End,
};

// �����
enum ACTIVITY_CONFIG_TYPE
{
	ACTIVITY_CONFIG_TYPE_BEGIN,
	ACTIVITY_CONFIG_TYPE_TERRITORY_FIGHT_PREPARE			= 1,		// �������ս׼���׶�
	ACTIVITY_CONFIG_TYPE_TERRITORY_FIGHT_MARCH				= 2,		// �������ս�о��׶�
	ACTIVITY_CONFIG_TYPE_TERRITORY_FIGHT_FIGHTING			= 3,		// �������սս���׶�
	ACTIVITY_CONFIG_TYPE_NTM_FIGHT							= 4,		// �����Ŷ���

	ACTIVITY_CONFIG_TYPE_EXTRA_Beg							= 100,		// ��Ӫ����Ϳ�ʼ

	ACTIVITY_CONFIG_TYPE_EXTRA_AWARD_UP_LEV					= 101,		// ��Ӫ����:�弶����			*�ͻ���ִ��action	��Ҫ�ȼ�		
	ACTIVITY_CONFIG_TYPE_EXTRA_AWARD_PAY_VAS				= 102,		// ��Ӫ����:��ֵ����			*�ͻ���ִ��action	��Ҫ��ֵ���		

	ACTIVITY_CONFIG_TYPE_EXTRA_LOGIN_MAIL					= 103,		// ��Ӫ����:��½����			*��½�ű�����ִ��

	ACTIVITY_CONFIG_TYPE_EXTRA_AWARD_LOGIN_TOTAL			= 104,		// ��Ӫ����:�ۼƵ�½����		*�ͻ���ִ��action	��Ҫ�ۼƵ�½����
	ACTIVITY_CONFIG_TYPE_EXTRA_AWARD_LOGIN_CONTINUE			= 105,		// ��Ӫ����:������½����		*�ͻ���ִ��action	��Ҫ������½����
	ACTIVITY_CONFIG_TYPE_EXTRA_AWARD_LOTTERY_VAS			= 106,		// ��Ӫ����:Ԫ���鿨����		*�ͻ���ִ��action	��ҪԪ���鿨����

	ACTIVITY_CONFIG_TYPE_EXTRA_MULTI_AWARD_AERNA_RANK		= 107,		// ��Ӫ����:��������������		nParam1��ʾ��������
	ACTIVITY_CONFIG_TYPE_EXTRA_MULTI_AWARD_POWER_TIME		= 108,		// ��Ӫ����:��ʱ����������		nParam1��ʾ��������

	ACTIVITY_CONFIG_TYPE_EXTRA_MULTI_DROP_ITEM				= 109,		// ��Ӫ����:ָ�����߶౶����	nParam1��ʾ�౶���伸��,nParam2��ʾ�౶��������
	ACTIVITY_CONFIG_TYPE_EXTRA_MULTI_DROP_COMMON			= 110,		// ��Ӫ����:��ͨ�ؿ��౶����	nParam1��ʾ�౶���伸��,nParam2��ʾ�౶��������
	ACTIVITY_CONFIG_TYPE_EXTRA_MULTI_DROP_ELITE				= 111,		// ��Ӫ����:��Ӣ�ؿ��౶����	nParam1��ʾ�౶���伸��,nParam2��ʾ�౶��������
	ACTIVITY_CONFIG_TYPE_EXTRA_MULTI_DROP_INSTANCE			= 112,		// ��Ӫ����:�����ؿ��౶����	nParam1��ʾ�౶���伸��,nParam2��ʾ�౶��������

	ACTIVITY_CONFIG_TYPE_EXTRA_SHOP							= 113,		// ��Ӫ����:ָ�������̵��ۿ�    nParam1��ʾ�̵�����,nParam2��ʾ�ۿ�,ȡֵ[1,100],

	ACTIVITY_CONFIG_TYPE_EXTRA_End							= 999,		// ��Ӫ����ͽ���

	ACTIVITY_CONFIG_TYPE_END,
};

// �ʱ������
enum ACTIVITY_CONFIG_TIME_TYPE
{
	ACTIVITY_CONFIG_TIME_TYPE_MINUTE		= 1,		// ͨ��Ψһ��minute����һ����ʱ��					*YYMMDDHHMMʱ���ʽ
	ACTIVITY_CONFIG_TIME_TYPE_EVERYDAY		= 2,		// ÿ��											*HHMMSSʱ���ʽ
	ACTIVITY_CONFIG_TIME_TYPE_FROM_START	= 3,		// �ӿ�������, �����								*��ʼ����ʱ������: ���� - ��ʼΪ���ʱ������λΪ���ӣ�
	ACTIVITY_CONFIG_TIME_TYPE_ACTION		= 4,		// ���ýӿڴ����Ļ
	ACTIVITY_CONFIG_TIME_TYPE_WEEK_MULTIDAY = 5,		// ÿ�ܿ���										*����1103059 ��ʾ ��һ10:30:59, ����λ��ʾ�ܼ���0Ϊ��ĩ��
	ACTIVITY_CONFIG_TIME_TYPE_WEEK_BEGIN	= 10,		// ͨ��ÿ��ÿ���׼����, begin						*TimeType�ĸ�λ����ʾ�ܼ���0-6������ʼ����ʱ�����ø�ʽ HHMMSS
	ACTIVITY_CONFIG_TIME_TYPE_WEEK_END		= 16,		// ͨ��ÿ��ÿ���׼����, end
	ACTIVITY_CONFIG_TIME_TYPE_MONTH_BEGIN	= 101,		// ÿ������ BEGIN									*TimeType��λʮλ��ʾÿ������(1-31),��ʼ����ʱ�����ø�ʽ HHMMSS
	ACTIVITY_CONFIG_TIME_TYPE_MONTH_END		= 131,		// ÿ������ END
};

enum ACTIVITY_GET_SECOND_TYPE
{
	ACTIVITY_GET_SECOND_TYPE_BEGIN	= 1,
	ACTIVITY_GET_SECOND_TYPE_END	= 2,
};

// ����������ö��
enum MINE_TOPLIST_TYPE
{
	MINE_TOPLIST_TYPE_Beg		= 0,
	MINE_TOPLIST_TYPE_ATK_COUNT = 1,	// ��������
	MINE_TOPLIST_TYPE_MONEY		= 2,	// ���
	MINE_TOPLIST_TYPE_DRUG		= 3,	// ҩ��
	MINE_TOPLIST_TYPE_End,
};


// ��Ϣ����ʼ�������
enum MSG_PACKET_FLAG
{
	MSG_PACKET_FLAG_NONE	= 0,
	MSG_PACKET_FLAG_BEGIN	= 1,	// ��ʼ��
	MSG_PACKET_FLAG_END		= 2,	// ������
};

/////////////////////////////////////////////////////////////////////////////////////////
// �󶴷���������Ϣ
enum MSG_MINE_SERVER_ACTION
{
	MSG_MINE_SERVER_ACTION_AckMineEnd	= 1,		// ��ϵ��֪ͨ�󶴽���	R->S
};

enum MSG_MINE_SERVER_RESULT
{
	MSG_MINE_SERVER_RESULT_Succ	 = 0,
	MSG_MINE_SERVER_RESULT_Error = 1,
};

//////////////////////////////////////////////////////////////////////////
enum CROSS_ROOM_TYPE
{
	CROSS_ROOM_TYPE_BEGIN = 0,
	CROSS_ROOM_TYPE_NTM = 1,	// �����Ŷ���
	CROSS_ROOM_TYPE_HGS = 2,	// ����ɽ��ս
	CROSS_ROOM_TYPE_END,
};

// ��������ϵ��
enum POKER_SCORE_PARAM				// ��������ϵ��
{
	PSP_BEGIN = 0,
	PSP_POKER_LEV,					// ���Ƶȼ�ϵ��

	PSP_SKILL_WHITE_ACTIVATE,		// ��ɫ���ܼ���ϵ��
	PSP_SKILL_WHITE_LEV,			// ��ɫ���ܵȼ�ϵ��
	PSP_SKILL_GREEN_ACTIVATE,		// ��ɫ���ܼ���ϵ��
	PSP_SKILL_GREEN_LEV,			// ��ɫ���ܵȼ�ϵ��
	PSP_SKILL_BLUE_ACTIVATE,		// ��ɫ���ܼ���ϵ��
	PSP_SKILL_BLUE_LEV,				// ��ɫ���ܵȼ�ϵ��
	PSP_SKILL_PURPLE_ACTIVATE,		// ��ɫ���ܼ���ϵ��
	PSP_SKILL_PURPLE_LEV,			// ��ɫ���ܵȼ�ϵ��

	PSP_ATTR_HP,					// �������� ��Ѫ
	PSP_ATTR_SP,					// ��������	��ŭ
	PSP_ATTR_HIT,					// ��������	����
	PSP_ATTR_ATK,					// ��������	�˺�
	PSP_ATTR_DEF,					// ��������	����
	PSP_ATTR_SPD,					// ��������	�ٶ�
	PSP_ATTR_DODGE,					// ��������	����
	PSP_ATTR_MAGIC,					// ��������	����
	PSP_ATTR_HP_RECOVER,			// �������� ��Ѫ�ظ�
	PSP_ATTR_SP_RECOVER,			// ��������	��ŭ�ظ�
	PSP_ATTR_PHY_CRIT,				// ��������	�ﱩ
	PSP_ATTR_MAG_CRIT,				// ��������	����
	PSP_ATTR_VAMPIRE_LEV,			// ��������	��Ѫ�ȼ�
	PSP_ATTR_SP_SPEND_DECREASE,		// ��������	��ŭ���Ľ���%
	PSP_ATTR_CURE_INCREASE,			// ��������	���Ƽ���Ч�����%
	PSP_ATTR_BASE,					// �������ֻ���
	PSP_END,
};

enum PROPERTYCALCRANK2				// ���ƶ�������ת��ϵ������
{
	PROPERTYCALCRANK2_NONE	= 0,
	PROPERTYCALCRANK2_XIAN  = 1,	// �ɣ��˴�3����Ӫ����Ҫ�뿨����Ӫ���룩
	PROPERTYCALCRANK2_MO	= 2,	// ħ
	PROPERTYCALCRANK2_FO	= 3,	// ��
	PROPERTYCALCRANK2_MAGIC	= 4,	// ����
	PROPERTYCALCRANK2_SPD	= 5,	// �ٶ�
};

#endif // end of _GLOBAL_ENUMDEF_HEADER_