////////////////////////////////////////////////////////////////////////
// Import : 全局文件。枚举定义。
// Moudle : GlobalEnumDef.h
// Author : 陈建军(Chen Jianjun)
// Create : 2015-6-19
////////////////////////////////////////////////////////////////////////
#ifndef _GLOBAL_ENUMDEF_H_
#define _GLOBAL_ENUMDEF_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

////////////////////////////////////////////////////////////////////////////////////////////////
// 消息type号定义处, 定义协议号时强制将协议号显式填入
enum _MSG_TYPE_DEFINE_
{
	_MSG_NONE							= 0,

	_MSG_RL_SERVER_BEGIN				= 100,	// 入口服消息开始
	_MSG_RL_SERVER_REQ_LOGIN			= 101,	// 客户端请求登陆
	_MSG_RL_SERVER_QUERY_ONLINE			= 102,	// 关系服查询在线
	_MSG_RL_SERVER_END					= 200,	// 入口服消息结束

	// 客户端 登陆线程 消息区间
	_MSG_LOGIN_BEGIN					= 1000,
	_MSG_LOGIN_CONNECT					= 1001,	// 连接			C --> S
	_MSG_LOGIN_CONNECT_ACTION			= 1002,	// 连接操作		C <-> S
	_MSG_LOGIN_USER_LIST				= 1003,	// 玩家列表		C <-- S
	_MSG_LOGIN_CREATE_NEW_USER			= 1004,	// 建立新角色	C <-> S
	_MSG_LOGIN_KICK_REASON				= 1005,	// 踢出原因		C <-- S
	_MSG_LOGIN_END						= 2000,

	_MSG_GAME_BEGIN						= 5000,
	_MSG_GAME_KICK_REASON				= 5001,	// 踢出原因				C <-- S
	_MSG_GAME_LOGIN_QUERY				= 5002,	// 登陆查询				C <-> S
	_MSG_GAME_SMALLACTION				= 5003,	// SmallAction消息		C <-> S
	_MSG_GAME_USER_INFO					= 5004,	// UserInfo				C <-- S
	_MSG_GAME_USER_ATTR					= 5005,	// UserAttr				C <-- S
	_MSG_GAME_USER_MONEY				= 5006,	// 货币同步				C <-- S
	_MSG_GAME_MASK						= 5007,	// 掩码同步				C <-- S
	_MSG_GAME_TMP_DATA					= 5008,	// UserTmpData			C <-> S
	_MSG_GAME_TALK						= 5009, // 聊天消息				C <-> S
	_MSG_GAME_NEWCARD					= 5010,	// 新手卡				C <-> S
	_MSG_GAME_NEWCARD_PRIZE				= 5011,	// 新手卡奖励			C <-- S
	_MSG_GAME_TASK						= 5012, // 任务					C <-> S
	_MSG_GAME_ACTIVITIES				= 5013,	// 活动					C <-> S
	_MSG_GAME_SIGN						= 5014,	// 签到					C <-> S
	_MSG_GAME_BLACK_LIST				= 5015,	// 黑名单				C <-> S
	_MSG_GAME_ONLINE_INFO				= 5016,	// 在线玩家信息			S <-> R
	_MSG_GAME_MAIL_LIST					= 5017,	// 邮件列表				C <-> S
	_MSG_GAME_MAIL_OPT					= 5018,	// 邮件操作				C <-> S
	_MSG_GAME_SYN_SERVER				= 5019,	// 帮派服务器间消息		S <-> R
	_MSG_GAME_SYN_CLIENT				= 5020,	// 帮派客户端消息		C <-> S
	_MSG_GAME_VIP						= 5021,	// VIP消息				C <-> S
	_MSG_GAME_POKER_ACT					= 5022,	// 卡牌操作				C <-> S
	_MSG_GAME_POKER_INFO				= 5023,	// 卡牌信息				C <-- S
	_MSG_GAME_POKER_ATTR				= 5024,	// 卡牌属性				C <-- S
	_MSG_GAME_USER_QUERY_INFO			= 5025,	// UserQueryInfo		C <-> S
	_MSG_GAME_MONEYTREE					= 5026,	// 摇钱系统				C <-> S
	_MSG_GAME_ACHIEVEMENT				= 5027,	// 成就系统				C <-> S
	_MSG_GAME_LIVENESS					= 5028,	// 每日活跃				C <-> S
	_MSG_GAME_SHOP						= 5029,	// 商店系统				C <-> S
	_MSG_GAME_LOTTERY					= 5030,	// 抽奖系统				C <-> S
	_MSG_GAME_ITEM						= 5031,	// 物品消息				C <-> S
	_MSG_GAME_EQUIP						= 5032,	// 装备消息				C <-> S
	_MSG_GAME_ITEM_HINT					= 5033,	// 物品提示面板信息		C <-- S
	_MSG_GAME_CHALLENGE_BOSS			= 5034,	// 挑战boss				C <-> S
	_MSG_GAME_BATTLE_INIT_INFO			= 5035,	// 战斗初始化信息		C <-- S
	_MSG_GAME_BATTLE_INIT_FIGHTER		= 5036,	// 战斗初始化参战者		C <-- S
	_MSG_GAME_BATTLE_END_INFO			= 5037,	// 战斗结束信息			C --> S
	_MSG_GAME_MARKS_INFO				= 5038,	// 各系统标记推送信息	C <-- S
	_MSG_GAME_BUFF						= 5039,	// BUFF消息				C <-- S
	
	_MSG_GAME_INSTANCE_ACT				= 5040, // 副本操作				C <-> S
	_MSG_GAME_GOOSE_TOWER				= 5043,	// 大雁塔				C <-> S
	_MSG_GAME_PUZZLE_BUFF				= 5044,	// 迷宫BUFF				C <-- S
	_MSG_GAME_PUZZLE					= 5045,	// 迷宫副本				C <-> S
	_MSG_GAME_SYN_LIST					= 5046,	// 帮派列表				C <-- S
	_MSG_GAME_SYN_MEMBER_LIST			= 5047,	// 帮派成员列表			C <-- S
	_MSG_GAME_SYN_INFO					= 5048,	// 帮派详情				C <-- S
	_MSG_GAME_SELF_SYN_INFO				= 5049,	// 自己帮派详情			C <-- S
	_MSG_GAME_SYN_LOG					= 5050,	// 帮派日志				C <-> S
	_MSG_GAME_MINE_CLIENT				= 5051,	// 矿洞消息				C <-> S
	_MSG_GAME_MERCENARY					= 5052,	// 佣兵系统				C <-> S
	_MSG_GAME_POKER_VIEW				= 5053,	// 卡牌查看信息			C <-- S
	_MSG_GAME_VAS_INFO					= 5055,	// 元宝详情				C <-- S
	_MSG_GAME_SYN_WORSHIP				= 5056,	// 帮派膜拜大神			C <-> S
	_MSG_GAME_MINE_LOG_LIST				= 5057,	// 矿洞日志列表			C <-> S
	_MSG_GAME_WAR_ROAD_ACT				= 5058,	// 战役操作				C <-> S
	_MSG_GAME_WAR_ROAD_INFO				= 5059,	// 战役信息				C <-- S
	_MSG_GAME_USER_MAC					= 5060,	// 玩家mac地址			C --> S
	_MSG_GAME_FRIEND_INVITE				= 5062,	// 好友邀请				C <-> S
	_MSG_GAME_TALK_QUERY				= 5063, // 查询聊天				C <-> S
	_MSG_GAME_WARROAD_TEAM_INFO			= 5064,	// 团队战役信息			C <-- S
	_MSG_GAME_WARROAD_TEAM_FIGHT_INFO	= 5065,	// 团队战役战斗信息		C <-- S
	_MSG_GAME_WARROAD_TEAM_RANK_INFO	= 5066,	// 团队战役排名信息		C <-- S
	_MSG_GAME_WARROAD_TEAM_SERVER_RANK	= 5067,	// 团队战役全服排名信息	C <-- S
	_MSG_GAME_SYSTEM_SETTINGS			= 5068,	// 系统设置				C <-> S
	_MSG_GAME_WARROAD_TEAM_AWARD_LOG	= 5069,	// 团战战利品分配记录	C <-- S
	_MSG_GAME_ARENA_USER_INFO			= 5070,	// 竞技场玩家信息		C <-> S
	_MSG_GAME_ARENA_TARGET_INFO			= 5071,	// 竞技场对手信息		C <-> S
	_MSG_GAME_ARENA_LOG					= 5072,	// 竞技场日志			C <-> S
	_MSG_GAME_ARENA_ACT					= 5073,	// 竞技场操作			C <-> S
	_MSG_GAME_FRIEND_INFO				= 5074,	// 好友查询消息			C <-> S
	_MSG_GAME_FRIEND_ACT				= 5075,	// 好友操作消息			C <-> S
	_MSG_GAME_FRIEND_SEARCH				= 5076,	// 好友查找消息			C <-> S
	_MSG_GAME_FRIEND_PUSH				= 5077,	// 好友推送消息			C <-> S
	_MSG_GAME_TOPLIST_ARENA_LIST		= 5078,	// 排行榜竞技场排名		C <-> S
	_MSG_GAME_TOPLIST_ARENA_USER		= 5079,	// 排行榜竞技场玩家数据 C <-> S
	_MSG_GAME_TOPLIST_COMMON			= 5080,	// 排行榜通用排名		C <-> S
	_MSG_GAME_TOPLIST_SYNLIST			= 5081,	// 排行榜公会排名		C <-> S
	_MSG_GAME_TOPLIST_SYNINFO			= 5082,	// 排行榜查看公会数据	C <-> S
	_MSG_GAME_TERRITORY_MAININFO		= 5083,	// 领地战查询主界面		C <-> S
	_MSG_GAME_TERRITORY_TROOPS_LIST		= 5084,	// 领地战本公会部队列表	C <-> S
	_MSG_GAME_TERRITORY_TROOPS_INFO		= 5085,	// 领地战成员部队数据	C <-> S
	_MSG_GAME_TERRITORY_USER_ACT		= 5086,	// 领地玩家操作			C <-> S
	_MSG_GAME_TERRITORY_USER_TROOPS		= 5087,	// 领地战查询玩家部队	C <-> S
	_MSG_GAME_TERRITORY_FIGHT			= 5088,	// 领地战开启战斗		S <-  R
	_MSG_GAME_TERRITORY_QUERY_FIGHTING  = 5089,	// 领地战查看战斗		C <-> S
	_MSG_GAME_SYN_MEMBER_APPLY_LIST		= 5090,	// 帮派成员申请列表		C <-- S
	_MSG_GAME_MINE_SERVER				= 5091, // 矿洞服务器消息		S <-> R
	_MSG_GAME_SYN_GIFT_BOX				= 5092, // 帮派礼盒消息			C <-> S
	_MSG_GAME_CROSS_NTM_ACT				= 5093, // 南天门斗法操作		C <-> S
	_MSG_GAME_CROSS_NTM_INFO			= 5094, // 南天门斗法信息		C <-- S
	_MSG_GAME_CROSS_NTM_TIPS			= 5095, // 南天门斗法TIPS		C <-- S
	_MSG_GAME_CROSS_NTM_RANK			= 5096, // 南天门斗法排名		C <-- S
	_MSG_GAME_CROSS_INFO				= 5097,	// 跨服基础信息			C <-> S
	_MSG_GAME_RELAY_DATABASE			= 5098, // 本服中转数据库		S <-> R
	_MSG_GAME_CROSS_RELAY_DATABASE		= 5099,	// 跨服中转数据库		S <-> C
	_MSG_GAME_CLEAR_AWARD				= 5100, // 扫荡奖励信息			C <-- S
	_MSG_GAME_CROSS_HGS_FIGHT			= 5101,	// 花果山大战			C <-> S
	_MSG_GAME_CROSS_HGS_ROOM_FRUIT		= 5102,	// 花果山大战房间水果	C <-- S
	_MSG_GAME_CROSS_ROOM_POS_INFO		= 5104, // 房间坐标信息			C <-> S
	_MSG_GAME_MINE_LOG					= 5105,	// 矿洞日志				C <-> S

	_MSG_GAME_END						= 7900,


	// php服务器 消息区间
	_MSG_PHP_BEGIN						= 7900,
	_MSG_PHP_PAY						= 8000,	// 充值消息
	_MSG_PHP_KICK						= 8001,	// php踢人
	_MSG_PHP_END						= 9000,

	// 关系服全部消息开始
	_MSG_RELATION_BEGIN						= 10000,

	// 关系服直接转发全服消息
	_MSG_RELATION_DIRCET_ALL_BEGIN			= 10000,
	_MSG_RELATION_DIRCET_ALL_END			= 12000,

	// 关系服直接转发其他服消息
	_MSG_RELATION_DIRCET_OTHER_BEGIN		= 12000,
	_MSG_RELATION_DIRCET_OTHER_TALK			= 12001,	// 聊天
	_MSG_RELATION_DIRCET_OTHER_END			= 15000,

	// 需要关系服处理消息
	_MSG_RELATION_PROCESS_BEGIN				= 15000,
	_MSG_RELATION_PROCESS_LOGIN				= 15001,	// 游戏服登陆到关系服
	_MSG_RELATION_PROCESS_ACTION			= 15002,	// 游戏服与关系服 通用操作action
	_MSG_RELATION_PROCESS_NEWCARD			= 15003,	// 新手卡消息
	_MSG_RELATION_PROCESS_ONLINE_INFO		= 15004,	// 更新角色在线信息
	_MSG_RELATION_PROCESS_SYN_SERVER		= 15005,	// 帮派处理消息
	_MSG_RELATION_PROCESS_MAIL				= 15006,	// 邮件消息
	_MSG_RELATION_PROCESS_FRIEND			= 15007,	// 好友处理消息
	_MSG_RELATION_PROCESS_TOPLIST			= 15008,	// 排行榜系统
	_MSG_RELATION_PROCESS_REALY_DATABASE	= 15009,	// 中转数据库
	_MSG_RELATION_PROCESS_ARENA_ACT			= 15010,	// 竞技场
	_MSG_RELATION_PROCESS_ACHIEVEMENT		= 15011,	// 成就系统 
	_MSG_RELATION_PROCESS_ARENA_LOG			= 15012,	// 竞技场
	_MSG_RELATION_PROCESS_TERRITORY_FIGHT	= 15013,	// 领地战
	_MSG_RELATION_PROCESS_MINE_SERVER		= 15014,	// 矿洞处理消息
	_MSG_RELATION_PROCESS_MARKSINFO			= 15015,	// 推送提示消息
	_MSG_RELATION_PROCESS_END				= 20000,
	
	// 关系服全部消息结束
	_MSG_RELATION_END						= 20000,

	// 跨服服务器处理消息
	_MSG_CROSS_BEGIN						= 20000,
	_MSG_CROSS_LOGIN						= 20001,	// 关系服登录跨服服务器消息
	_MSG_CROSS_ACTION						= 20002,	// action		
	_MSG_CROSS_REALY_DATABASE				= 20003,	// 跨服中转数据库
	_MSG_CROSS_END							= 30000,
};
////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
// 关系服Action消息的action
enum MSG_RS_ACTION
{
	MSG_RS_ACTION_NONE = 0,
	MSG_RS_ACTION_USER_LOGIN,				// 角色登入			G --> R
	MSG_RS_ACTION_USER_LOGOUT,				// 角色登出			G --> R
	MSG_RS_ACTION_USER_KICK,				// 角色踢出			G <-- R
	MSG_RS_ACTION_KICK_OTHER_LINE_ACCOUNT,	// 账号踢出 		G --> R
	MSG_RS_ACTION_PAY_NOTIFY,				// 充值通知			G <-- R
	MSG_RS_ACTION_ONLINE,					// 同步在线 		G --> R
	MSG_RS_ACTION_RELOAD_TABLE,				// 重新加载常量表	G <-- R
	MSG_RS_ACTION_ADD_USER_ONLINE,			// 增加玩家在线表	G <-- R
	MSG_RS_ACTION_DEL_USER_ONLINE,			// 删除玩家在线表	G <-- R
	MSG_RS_ACTION_CLOSE_SERVER,				// 关服				G <-- R
	MSG_RS_ACTION_CROSS_MIN_ONLINE_LINE,	// 同步跨服最少在线	G <-- R
};

// 跨服服务器Action消息的action
enum MSG_CS_ACTION
{
	MSG_CS_ACTION_NONE = 0,
	MSG_CS_ACTION_ONLINE,					// 同步在线 		R --> C
	MSG_CS_ACTION_CLOSE_ALL_SERVER,			// 关服				R <-- C
	MSG_CS_ACTION_CROSS_MIN_ONLINE_LINE,	// 同步跨服最少在线	R <-- C
};

// 服务器间帮派消息action
enum MSG_SYN_SERVER_ACTION
{
	MSG_SYN_SERVER_ACTION_NONE = 0,
};

// 关系服处理后统一错误码
enum MSG_RS_ERR_CODE
{
	MSG_RS_ERR_CODE_SUCC = 0,
	MSG_RS_ERR_CODE_FAIL = 1,
	MSG_RS_ERR_CODE_KICK,				// 被踢
	MSG_RS_ERR_CODE_KICK_WAIT,			// 由于踢掉其他服务器, 稍后重连
	MSG_RS_ERR_CODE_LOGIN_GROUP_ERROR,	// 登陆组错误
	MSG_RS_ERR_CODE_LOGIN_KEY_ERROR,	// 登陆key错误
	MSG_RS_ERR_CODE_LOGIN_TIMEOUT,		// 登陆时间超时
};

// 跨服处理后同一错误码
enum MSG_CS_ERR_CODE
{
	MSG_CS_ERR_CODE_SUCCESS		= 0,
	MSG_CS_ERR_CODE_FAIL		= 1,
	MSG_CS_ERR_CODE_KICK,				// 被踢
	MSG_CS_ERR_CODE_KICK_WAIT,			// 由于踢掉其他服务器, 稍后重连
	MSG_CS_ERR_CODE_LOGIN_GROUP_ERROR,	// 登陆组错误
	MSG_CS_ERR_CODE_LOGIN_KEY_ERROR,	// 登陆key错误
	MSG_CS_ERR_CODE_LOGIN_TIMEOUT,		// 登陆时间超时
};
////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
// 账号类型
enum ACCOUNT_TYPE
{
	ACCOUNT_TYPE_NORMAL			= 0,	// 正常
	ACCOUNT_TYPE_GM				= 1,	// GM
	ACCOUNT_TYPE_VISTOR			= 2,	// 游客
};

// 账号状态
enum ACCOUNT_STATUS
{
	ACCOUNT_STATUS_NORMAL		= 0,	// 正常
	ACCOUNT_STATUS_STOP_BYTIME	= 1,	// 临时封停, 状态参数为解封utc时间
	ACCOUNT_STATUS_STOP_FOREVER = 2,	// 永久封停
};

// 阵营类型
enum CAMP_TYPE
{
	CAMP_TYPE_BEGIN				= 0,
	CAMP_TYPE_EARTH				= 1,	// 地球文明
	CAMP_TYPE_SANTI				= 2,	// 三体文明
	CAMP_TYPE_GZWM				= 3,	// 歌者文明
	CAMP_TYPE_END,
};
////////////////////////////////////////////////////////////////////////////////////////////////

enum GAME_OBJECT_TYPE
{
	GAME_OBJECT_TYPE_NONE	= 0x00000000,	// 空	
	GAME_OBJECT_TYPE_COMMON = 0x00000001,	// 通用对象
	GAME_OBJECT_TYPE_USER	= 0x00000002,	// 角色对象
	GAME_OBJECT_TYPE_ITEM	= 0x00000004,	// 物品对象
};

////////////////////////////////////////////////////////////////////////////////////////////////

// php操作类型
enum PHP_OPERATION_TYPE
{
	PHP_OPERATION_TYPE_NONE = 0,
	PHP_OPERATION_TYPE_PAY,
	PHP_OPERATION_TYPE_KICK,
};

#endif // end of _GLOBAL_ENUMDEF_H_