////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2012, WuHan ChuangYou, All Rights Reserved
// Moudle: GlobalEnumDef.h
// Author: 彭文奇(Peng Wenqi)
// Created: 2012-11-19
////////////////////////////////////////////////////////////////////////
#ifndef _GLOBAL_ENUMDEF_HEADER_
#define _GLOBAL_ENUMDEF_HEADER_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

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
	_MSG_GAME_LOGIN_QUERY				= 5001,	// 登陆查询				C <-> S
	_MSG_GAME_USER_INFO					= 5002,	// UserInfo				C <-- S
	_MSG_GAME_USER_ATTR					= 5003,	// UserAttr				C <-- S
	_MSG_GAME_USER_MONEY				= 5004,	// 货币同步				C <-- S
	_MSG_GAME_KICK_REASON				= 5005,	// 踢出原因				C <-- S
	_MSG_GAME_MASK						= 5006,	// 掩码同步				C <-- S
	_MSG_GAME_TMP_DATA					= 5007,	// UserTmpData			C <-> S
	_MSG_GAME_SMALLACTION				= 5008,	// SmallAction消息		C <-> S
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



enum GAME_OBJECT_TYPE
{
	GAME_OBJECT_TYPE_NONE	= 0x00000000,	// 空	
	GAME_OBJECT_TYPE_COMMON = 0x00000001,	// 通用对象
	GAME_OBJECT_TYPE_USER	= 0x00000002,	// 角色对象
	GAME_OBJECT_TYPE_ITEM	= 0x00000004,	// 物品对象
};

// 账号类型
enum ACCOUNT_TYPE
{
	ACCOUNT_TYPE_NORMAL		= 0,	// 正常账号
	ACCOUNT_TYPE_GM_LOW		= 1,	// GM低级别账号
	ACCOUNT_TYPE_GM_HI		= 2,	// GM高级别账号
};

// 账号状态
enum ACCOUNT_STATUS
{
	ACCOUNT_STATUS_NORMAL		= 0,	// 正常
	ACCOUNT_STATUS_STOP_BYTIME	= 1,	// 临时封停, 状态参数为解封utc时间
	ACCOUNT_STATUS_STOP_FOREVER = 2,	// 永久封停
};

// 性别类型
enum SEX_TYPE
{
	SEX_TYPE_BEGIN		= 0,
	SEX_TYPE_GIRL		= 0,	// 女
	SEX_TYPE_BOY		= 1,	// 男
	SEX_TYPE_END
};

////////////////////////////////////////////////////////////////////////////////////////////////
// 货币枚举
// 货币流向类型
enum MONEY_FLOW_TYPE
{
	MONEY_FLOW_TYPE_AWARD	= 1,	// 获得
	MONEY_FLOW_TYPE_SPEND	= 2,	// 消费
};

// 货币流向原因, 名字配在itemtype表
enum MONEY_FLOW_REASON_ITEMTYPE
{
	MONEY_FLOW_REASON_ITEMTYPE_NONE				= 0,
	MONEY_FLOW_REASON_ITEMTYPE_LUA				= 900000,	// 脚本操作
	MONEY_FLOW_REASON_ITEMTYPE_CREATE_SYN		= 900001,	// 创建帮派
	MONEY_FLOW_REASON_GM_CMD					= 900002,	// gm命令
	MONEY_FLOW_REASON_MAGICPOINT				= 900003,	// 购买技能点
	MONEY_FLOW_REASON_WORLD_TALK				= 900004,	// 世界聊天
	MONEY_FLOW_REASON_AWARDMONEY				= 900005,	// 摇钱
	MONEY_FLOW_REASON_EQUIP_STAR_EXP			= 900006,	// 卡牌装备附魔(升星)
	MONEY_FLOW_REASON_EQUIP_STAR_ONEKEY			= 900007,	// 卡牌装备一键附魔(升星)
	MONEY_FLOW_REASON_REFRESH_SHOP				= 900008,	// 刷新商店
	MONEY_FLOW_REASON_MAIL						= 900009,	// 邮件
	MONEY_FLOW_REASON_BUY_SHOP_GOODS			= 900010,	// 购买商店物品
	MONEY_FLOW_REASON_SKILL_LEV					= 900011,	// 技能升级
	MONEY_FLOW_REASON_UPDATE_TIME_RECOVER		= 900012,	// 定时恢复
	MONEY_FLOW_REASON_ITEMTYPE_SALE				= 900013,	// 出售物品
	MONEY_FLOW_REASON_ITEMTYPE_COMPOUND			= 900014,	// 合成物品
	MONEY_FLOW_REASON_CHALLENGE_BOSS			= 900015,	// 挑战boss
	MONEY_FLOW_REASON_BATTLE_DROP				= 900016,	// 战斗掉落
	MONEY_FLOW_REASON_LOTTERY					= 900017,	// 抽奖
	MONEY_FLOW_REASON_INSTANCE					= 900018,	// 副本
	MONEY_FLOW_REASON_CREATE_SYN				= 900019,	// 创建帮派
	MONEY_FLOW_REASON_CREATE_SYN_ROLLBACK		= 900020,	// 创建帮派回滚
	MONEY_FLOW_REASON_GOOSE_TOWER				= 900021,	// 大雁塔
	MONEY_FLOW_REASON_RESET_ARENA_CD			= 900022,	// 重置竞技场CD
	MONEY_FLOW_REASON_GET_CUMULATIVE_AWARD		= 900023,	// 领取累积的多队竞技场币
	MONEY_FLOW_REASON_UPDATE_HISTORY_RECORD		= 900024,	// 更新竞技场历史排名奖励
	MONEY_FLOW_REASON_EMPLOY_MERCENARY			= 900025,	// 雇佣佣兵
	MONEY_FLOW_REASON_MERCENARY_BACK			= 900026,	// 收回佣兵
	MONEY_FLOW_REASON_PAYVAS					= 900027,	// 充值元宝
	MONEY_FLOW_REASON_FREEVAS					= 900028,	// 赠送元宝
	MONEY_FLOW_REASON_MONTHVAS					= 900029,	// 月卡元宝
	MONEY_FLOW_REASON_SEARCH_MINE				= 900030,	// 搜索矿洞
	MONEY_FLOW_REASON_CHALLENGE_MINE			= 900031,	// 挑战矿洞
	MONEY_FLOW_REASON_SYN_WORSHIP				= 900032,	// 帮派膜拜大神
	MONEY_FLOW_REASON_COLLECT_MINE				= 900033,	// 采集矿洞
	MONEY_FLOW_REASON_WARROAD					= 900034,	// 战役挑战
	MONEY_FLOW_REASON_SYN_WORSHIP_ROLLBACK		= 900035,	// 帮派膜拜大神回滚
	MONEY_FLOW_REASON_GET_TERRITORY_MONEY		= 900036,	// 领取累积的领地币
	MONEY_FLOW_REASON_FRIEND_INVITE				= 900037,	// 好友邀请
	MONEY_FLOW_REASON_WARROAD_DIFFICULTY_RESET	= 900038,	// 重置精英战役关卡
	MONEY_FLOW_REASON_WARROAD_QUICK				= 900039,	// 战役扫荡
	MONEY_FLOW_REASON_WARROAD_AWARD_CUT			= 900040,	// 战利品插队
	MONEY_FLOW_REASON_ALTER_NAME				= 900041,	// 改角色名
	MONEY_FLOW_REASON_ALTER_NAME_CALLBACK		= 900042,	// 改角色名回滚
	MONEY_FLOW_REASON_FSP_MERCENARY				= 900043,	// 增加友情点 被雇佣
	MONEY_FLOW_REASON_FRIEND_GIFT				= 900044,	// 增加体力   好友礼物
	MONEY_FLOW_REASON_POWER_RECOVER				= 900045,	// 体力恢复
	MONEY_FLOW_REASON_TREASURE_POWER_RECOVER	= 900046,	// 寻宝体力恢复
	MONEY_FLOW_REASON_SIGN_IN					= 900047,	// 签到奖励
	MONEY_FLOW_REASON_SYN_MONTHCARD_VAS			= 900048,	// 帮派任性月卡元宝
	MONEY_FLOW_REASON_ALTER_SEX					= 900049,	// 改性别
	MONEY_FLOW_REASON_ALTER_SEX_CALLBACK		= 900050,	// 改性别回滚
	MONEY_FLOW_REASON_ALTER_AGE					= 900051,	// 改年龄
	MONEY_FLOW_REASON_ALTER_AGE_CALLBACK		= 900052,	// 改年龄回滚
	MONEY_FLOW_REASON_ALTER_BIRTHDAY			= 900053,	// 改生日
	MONEY_FLOW_REASON_ALTER_BIRTHDAY_CALLBACK	= 900054,	// 改生日回滚
	MONEY_FLOW_REASON_HGS_BATTLE				= 900055,	// 花果山积分
	MONEY_FLOW_REASON_POWER_BUY					= 900056,	// 增加体力 购买
	MONEY_FLOW_REASON_POWER_USE_ITEM			= 900057,	// 增加体力 使用物品
	MONEY_FLOW_REASON_POWER_UP_LEV				= 900058,	// 增加体力 角色升级
	MONEY_FLOW_REASON_LIVENESS					= 900059,	// 活跃
	MONEY_FLOW_REASON_ACHEVEMENT				= 900060,	// 成就
	MONEY_FLOW_REASON_OPEN_SYN_GIFTBOX			= 900061,	// 开启帮派礼盒
	MONEY_FLOW_REASON_BUY_ARENA_COUNT			= 900062,	// 购买斗神台挑战次数
	MONEY_FLOW_REASON_BUY_MULTI_ARENA_COUNT		= 900063,	// 购买斗神台多队挑战次数
	MONEY_FLOW_REASON_ITEMHINT_CUSTOM			= 900064,	// 发送物品提示时获得,自定义原因[%d]
	MONEY_FLOW_REASON_WARROADTEAM_PASS_AWARD	= 900065,	// 团队战役关卡额外奖励
};

// 充值真实状态
enum PAY_VAS_STATUS
{
	PAY_VAS_STATUS_NONE		= 0,	// 未处理
	PAY_VAS_STATUS_PASS		= 1,	// 通过
	PAY_VAS_STATUS_FAILD	= 2,	// 拒绝
	PAY_VAS_STATUS_COMPLETE	= 3,	// 完结
};
////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////
// 物品相关枚举 start
// 物品流向
enum ITEM_FLOW_TYPE
{
	ITEM_FLOW_TYPE_BEGIN		= 0,
	ITEM_FLOW_TYPE_AWARD		= 1,		// 获得物品
	ITEM_FLOW_TYPE_LOSE			= 2,		// 失去物品
	ITEM_FLOW_TYPE_END,
};

// 物品流向原因
enum ITEM_FLOW_REASON
{
	ITEM_FLOW_REASON_NONE						= 0,
	ITEM_FLOW_REASON_RECHARGE					= 1,		// 充值获得
	ITEM_FLOW_REASON_OVERDUE					= 2,		// 物品过期删除 
	ITEM_FLOW_REASON_TASK_USED_d				= 3,		// 任务使用,任务id=【%d】
	ITEM_FLOW_REASON_TASK_AWARD_d				= 4,		// 任务获得,任务id=【%d】
	ITEM_FLOW_REASON_MAIL_AWARD					= 5,		// 通过邮件获取的物品
	ITEM_FLOW_REASON_LUA_AWARD_d				= 6,		// 脚本获取,脚本id=【%d】
	ITEM_FLOW_REASON_LUA_SPEND_d				= 7,		// 脚本使用,脚本id=【%d】
	ITEM_FLOW_REASON_GM_CMD_AWARD				= 8,		// GM命令获得
	ITEM_FLOW_REASON_GM_CMD_SPEND				= 9,		// GM命令使用
	ITEM_FLOW_REASON_COMPOUND_POKER_SPEND		= 10,		// 卡牌合成消耗
	ITEM_FLOW_REASON_POKER_EXP_SPEND			= 11,		// 卡牌提供经验消耗
	ITEM_FLOW_REASON_REPEAT_POKER_AWARD			= 12,		// 重复获得同类型卡牌给的物品
	ITEM_FLOW_REASON_POKER_STAR_SPEND			= 13,		// 卡牌升星消耗
	ITEM_FLOW_REASON_POKER_EQUIP_SPEND			= 14,		// 卡牌穿上装备使用
	ITEM_FLOW_REASON_POKER_EQUIP_STAR_SPEND		= 15,		// 卡牌装备升星使用
	ITEM_FLOW_REASON_SIGN_AWARD					= 16,		// 签到奖励获得
	ITEM_FLOW_REASON_ITEMTYPE_SHOP_AWARD		= 17,		// 商店购买获得
	ITEM_FLOW_REASON_SALE						= 18,		// 出售
	ITEM_FLOW_REASON_DEC						= 19,		// 删除
	ITEM_FLOW_REASON_COMPOUND					= 20,		// 合成
	ITEM_FLOW_REASON_BATTLE_DROP_d				= 21,		// 战斗掉落, BattleType[%d]
	ITEM_FLOW_REASON_LOTTERY_SPEND				= 22,		// 抽奖消耗
	ITEM_FLOW_REASON_LOTTERY_AWARD				= 23,		// 抽奖获得
	ITEM_FLOW_REASON_PUZZLE_INSTANCE			= 24,		// 迷宫副本获得
	ITEM_FLOW_REASON_MINE						= 25,		// 矿洞
	ITEM_FLOW_REASON_WARROAD_QUICK				= 26,		// 战役扫荡
	ITEM_FLOW_REASON_WARROAD_AWARD_SEND			= 27,		// 战利品分配
	ITEM_FLOW_REASON_CHALLENGE_BOSS				= 28,		// 挑战bosss
	ITEM_FLOW_REASON_ADD_POWER_SPEND			= 29,		// 增加体力使用
	ITEM_FLOW_REASON_SYN_GIFTBOX_OPEN			= 30,		// 开启帮派礼盒
	ITEM_FLOW_REASON_ITEMHINT_CUSTOM			= 31,		// 发送物品提示时获得,自定义原因[%d]
};


// 物品相关枚举 end
/////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////
// 卡牌相关枚举 start
// 卡牌流向
enum POKER_FLOW_TYPE
{
	POKER_FLOW_TYPE_BEGIN			= 0,
	POKER_FLOW_TYPE_POKER_AWARD		= 1,	// 获得卡牌
	POKER_FLOW_TYPE_POKER_LOSE		= 2,	// 失去卡牌
	POKER_FLOW_TYPE_END,
};

// 卡牌流向原因
enum POKER_FLOW_REASON
{
	POKER_FLOW_REASON_BEGIN				= 0,
	POKER_FLOW_REASON_NONE				= 1,	// 默认
	POKER_FLOW_REASON_LUA_AWARD			= 2,	// 脚本
	POKER_FLOW_REASON_GM_CMD_AWARD		= 3,	// GM命令
	POKER_FLOW_REASON_COMPOSE_AWARD		= 4,	// 合成
	POKER_FLOW_REASON_VIP_AWARD			= 5,	// vip赠送
	POKER_FLOW_REASON_DROP_AWARD		= 6,	// 掉落
	POKER_FLOW_REASON_LOTTERY_AWARD		= 7,	// 抽奖
	POKER_FLOW_REASON_SIGN_IN			= 8,	// 签到
	POKER_FLOW_REASON_WARROAD_QUICK		= 9,	// 战役扫荡
	POKER_FLOW_REASON_ITEMHINT_CUSTOM	= 10,   // 发送物品提示时获得,自定义原因[%d]
	POKER_FLOW_REASON_END,
};

// 卡牌颜色
enum POKER_COLOR
{
	POKER_COLOR_BEGIN		= 0,
	POKER_COLOR_WHITE		= 1,	// 白色
	POKER_COLOR_GREEN		= 2,	// 绿色
	POKER_COLOR_GREEN1		= 3,	// 绿色+1
	POKER_COLOR_BLUE		= 4,	// 蓝色
	POKER_COLOR_BLUE1		= 5,	// 蓝色+1
	POKER_COLOR_BLUE2		= 6,	// 蓝色+2
	POKER_COLOR_PURPLE		= 7,	// 紫色
	POKER_COLOR_PURPLE1		= 8,	// 紫色+1
	POKER_COLOR_PURPLE2		= 9,	// 紫色+2
	POKER_COLOR_PURPLE3		= 10,	// 紫色+3
	POKER_COLOR_PURPLE4		= 11,	// 紫色+4
	POKER_COLOR_ORANGE		= 12,	// 橙色
	POKER_COLOR_ORANGE1		= 13,	// 橙色+1
	POKER_COLOR_ORANGE2		= 14,	// 橙色+2
	POKER_COLOR_ORANGE3		= 15,	// 橙色+3
	POKER_COLOR_ORANGE4		= 16,	// 橙色+4
	POKER_COLOR_ORANGE5		= 17,	// 橙色+5
	POKER_COLOR_END,
};


// 卡牌相关枚举 end
/////////////////////////////////////////////////////////////////////////////////////////////////////

// php操作类型
enum PHP_OPERATION_TYPE
{
	PHP_OPERATION_TYPE_NONE = 0,
	PHP_OPERATION_TYPE_PAY,
	PHP_OPERATION_TYPE_KICK,
};

////////////////////////////////////////////////////////////////////////////////////////////////
// 数据库枚举
// 常量表名称枚举

////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
enum EMSGNEWCARDRESULT			// 新手卡使用结果
{
	EMNCR_SUC					= 0,	// 领取成功
	EMNCR_DEFAULT				= 1,	// 参数错误
	EMNCR_TIMEOUT				= 2,	// 点击过快
	EMNCR_ERROCARD				= 3,	// 卡号不对
	EMNCR_HAVEPRIZE				= 4,	// 领取过该类型卡号
	EMNCR_HAVINGREWARD			= 5,	// 该卡已被使用
	EMNCR_CARDINVALID			= 6,	// 卡已经过期
	EMNCR_PLATFORM				= 7,	// 平台不正确
	EMNCR_SERVER_GROUP			= 8,	// 服务器组不正确
	EMNCR_PACKFULL				= 9,	// 背包空间不足
	EMNCR_IP_ERROR				= 10,	// IP受限
	EMNCR_NEWCARD_SYSERROR		= 11,	// 系统错误或已关闭，请稍后再试

	EMNCR_RESULT_NOT_PROCESS	= 999,	// 未处理的新手卡
};
////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
// 聊天频道
enum TALK_TXTATR
{
	TALK_TXTATR_BEGIN			= 2000,
	TALK_TXTATR_PRIVATE			= 2001,	// 私聊
	TALK_TXTATR_SYNDICATE		= 2002,	// 帮派
	TALK_TXTATR_WORLDSERVER		= 2003,	// 世界(本区)
	TALK_TXTATR_GM_CMD			= 2004,	// GM命令
	TALK_TXTATR_NOTICE			= 2005,	// 公告
	TALK_TXTATR_HINT			= 2006,	// 提示
	TALK_TXTATR_GM_OPERATION	= 2007,	// GM操作(工具)
	TALK_TXTATR_END,
};
////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////
// 帮派成员等级
enum SYN_RANK_TYPE
{
	RANK_LEADER			= 3,	// 帮主
	RANK_ELDER			= 2,	// 长老
	RANK_NORMAL			= 1,	// 帮众
	RANK_NONE			= 0,	// 		
};
////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
// 好友系统

	// 好友操作action
enum MSG_FRIEND_ACT_ACTION
{
	MSG_FRIEND_ACT_ACTION_BEGIN,
	MSG_FRIEND_ACT_ACTION_REQUEST		= 1,				// 请求加好友			C <-> S
	MSG_FRIEND_ACT_ACTION_REFUSE		= 2,				// 拒绝加好友			C <-> S
	MSG_FRIEND_ACT_ACTION_ACCEPT		= 3,				// 添加好友				C <-> S
	MSG_FRIEND_ACT_ACTION_DELETE		= 4,				// 删除好友				C <-> S
	MSG_FRIEND_ACT_ACTION_ADD_FSP		= 5,				// 增加友情点数			C <-  S
	MSG_FRIEND_ACT_ACTION_GIVE_GIFT		= 6,				// 赠送礼物				C <-> S
	MSG_FRIEND_ACT_ACTION_GET_GIFT		= 7,				// 领取礼物				C <-> S
	MSG_FRIEND_ACT_ACTION_GIVE_GIFT_ALL	= 8,				// 一键送礼				C <-> S
	MSG_FRIEND_ACT_ACTION_GET_GIFT_ALL	= 9,				// 一键收礼				C <-> S
	MSG_FRIEND_ACT_ACTION_GIVE_ROSE		= 10,				// 送玫瑰				C <-> S
	MSG_FRIEND_ACT_ACTION_CS_END		= 99,

	MSG_FRIEND_ACT_ACTION_SR_BEGIN		= 100,
	MSG_FRIEND_ACT_ACTION_REQUEST_REQ	= 101,				// 请求加好友		S -> R
	MSG_FRIEND_ACT_ACTION_REQUEST_ACK	= 102,				// 请求加好友		R -> S
	MSG_FRIEND_ACT_ACTION_REFUSE_REQ	= 103,				// 拒绝加好友		S -> R
	MSG_FRIEND_ACT_ACTION_REFUSE_ACK	= 104,				// 拒绝加好友		R -> S
	MSG_FRIEND_ACT_ACTION_ACCEPT_REQ	= 105,				// 添加好友			S -> R
	MSG_FRIEND_ACT_ACTION_ACCEPT_ACK	= 106,				// 添加好友			R -> S
	MSG_FRIEND_ACT_ACTION_DELETE_REQ	= 107,				// 删除好友			S -> R
	MSG_FRIEND_ACT_ACTION_DELETE_ACK	= 108,				// 删除好友			R -> S
	MSG_FRIEND_ACT_ACTION_ADD_FSP_REQ	= 109,				// 请求跨线加友情点 S -> R
	MSG_FRIEND_ACT_ACTION_ADD_FSP_ACK	= 110,				// 请求跨线加友情点 R -> S
	MSG_FRIEND_ACT_ACTION_GIVE_GIFT_REQ	= 111,				// 请求跨线送礼		S -> R
	MSG_FRIEND_ACT_ACTION_GIVE_GIFT_ACK	= 112,				// 请求跨线送礼		R -> S
	MSG_FRIEND_ACT_ACTION_GIVE_GIFT_ALL_REQ	= 113,			// 请求一键送礼		S -> R
	MSG_FRIEND_ACT_ACTION_GIVE_GIFT_ALL_ACK	= 114,			// 应答一键送礼		S <- R

	MSG_FRIEND_ACT_ACTION_GIVE_ROSE_REQ		= 115,			// 请求送玫瑰		S -> R
	MSG_FRIEND_ACT_ACTION_GIVE_ROSE_ACK		= 116,			// 应答送玫瑰		S <- R

	MSG_FRIEND_ACT_ACTION_SR_END		= 999,

	MSG_FRIEND_ACT_ACTION_END,
};
// 好友操作结果
enum MSG_FRIEND_RESULT_TYPE
{
	MSG_FRIEND_RESULT_TYPE_BEGIN,
	MSG_FRIEND_RESULT_TYPE_SUCC						= MSG_FRIEND_RESULT_TYPE_BEGIN,	// 操作成功
	MSG_FRIEND_RESULT_TYPE_FAIL						= 1,							// 操作失败
	MSG_FRIEND_RESULT_TYPE_NOT_EXIST				= 2,							// id不存在
	MSG_FRIEND_RESULT_TYPE_NOT_FRIEND				= 3,							// 不是好友
	MSG_FRIEND_RESULT_TYPE_OLD_FRIEND				= 4,							// 已经是好友
	MSG_FRIEND_RESULT_TYPE_OFF_LINE					= 5,							// 不在线
	MSG_FRIEND_RESULT_TYPE_NOT_EXIST_OR_OFFLINE		= 6,							// 不在线或不存在
	MSG_FRIEND_RESULT_TYPE_AT_THE_LIMIT				= 7,							// 到达好友上限
	MSG_FRIEND_RESULT_TYPE_EXIST_REQUESTER			= 8,							// 已经请求过了（添加请求者时）
	MSG_FRIEND_RESULT_TYPE_NOT_REQUESTER			= 9,							// 不在请求列表（删除请求者时）
	MSG_FRIEND_RESULT_TYPE_EMPTY_LIST				= 10,							// 好友列表为空
	MSG_FRIEND_RESULT_TYPE_START_SENDING			= 11,							// 开始发包(数据分割开始包）
	MSG_FRIEND_RESULT_TYPE_SENDING					= 12,							// 正在发包(后面还有包）
	MSG_FRIEND_RESULT_TYPE_LAST_PACKAGE				= 13,							// 结束包
	MSG_FRIEND_RESULT_TYPE_NO_SUITABLE				= 14,							// 没有合适的
	MSG_FRIEND_RESULT_TYPE_NOT_SELF					= 15,							// 不能添加自己
	MSG_FRIEND_RESULT_TYPE_GIFT_GOT					= 16,							// 已经领取过礼物了
	MSG_FRIEND_RESULT_TYPE_NO_GIFT					= 17,							// 没有礼物
	MSG_FRIEND_RESULT_TYPE_GAVE_ROSE				= 18,							// 今天的玫瑰已送
	MSG_FRIEND_RESULT_TYPE_NO_GIFT_TO_GIVE			= 19,							// 今天的礼物送完了
	MSG_FRIEND_RESULT_TYPE_NO_GIFT_TO_GET			= 20,							// 今天的礼物收完了
	MSG_FRIEND_RESULT_TYPE_RECEIVE_GIFT				= 21,							// 收到礼物了
	MSG_FRIEND_RESULT_TYPE_END,
};

// 增加友情点原因枚举
enum FSP_ADD_REASON_TYPE
{
	FSP_ADD_REASON_TYPE_BEGIN,
	FSP_ADD_REASON_TYPE_MERCENARY		= 1,				// 	被好友雇佣			
	FSP_ADD_REASON_TYPE_END,
};

// 商店类型
enum SHOP_ENUM
{
	SHOP_ENUM_BEGIN						= 1000,
	SHOP_ENUM_ARENA						= SHOP_ENUM_BEGIN,	// 竞技场商店
	SHOP_ENUM_TEAMS_ARENA				= 1001,				// 多队竞技场商店
	SHOP_ENUM_TOWER						= 1002,				// 大雁塔商店
	SHOP_ENUM_SYN						= 1003,				// 帮派商店
	SHOP_ENUM_COMMON					= 1004,				// 普通商店
	SHOP_ENUM_BLACK_MARKET				= 1005,				// 黑市商店
	SHOP_ENUM_FRIENDSHIP				= 1006,				// 友情点商店
	SHOP_ENUM_END,
};

// 商店刷新类型
enum SHOP_REFRESH_TYPE
{
	SHOP_REFRESH_TYPE_NONE	= 0,
	SHOP_REFRESH_TYPE_HAND	= 1,	// 手动刷新
	SHOP_REFRESH_TYPE_AUTO	= 2,	// 自动刷新
};

////////////////////////////////////////////////////////////////////////////////////////////////
//成就系统
// 成就更新类别枚举 (其他模块更新数据时使用）
enum ACHIEVEMENT_UPDATE_TYPE
{
	ACHIEVEMENT_UPDATE_TYPE_BEGIN,

	ACHIEVEMENT_UPDATE_TYPE_USER_LEV		= 1,		// 人物等级
	ACHIEVEMENT_UPDATE_TYPE_POKER_GET		= 2,		// 获得卡牌
	ACHIEVEMENT_UPDATE_TYPE_POKER_ADVANCED	= 3,		// 进阶卡牌
	ACHIEVEMENT_UPDATE_TYPE_GATE			= 4,		// 推图关卡
	ACHIEVEMENT_UPDATE_TYPE_EQUIPMENT		= 5,		// 装备
	ACHIEVEMENT_UPDATE_TYPE_PIECE			= 6,		// 英雄碎片？
	ACHIEVEMENT_UPDATE_TYPE_FRIEND_INVITE	= 7,		// 好友邀请
	ACHIEVEMENT_UPDATE_TYPE_END,
};

// 成就分支枚举(策划需要知道的，对应achievement表id字段的万位上）
enum ACHIEVEMENT_TYPE
{
	ACHIEVEMENT_TYPE_BEGIN					= 0,
	ACHIEVEMENT_TYPE_LEV					= 1,		// 人物等级相关
	ACHIEVEMENT_TYPE_POKER_COUNT			= 2,		// 英雄个数
	ACHIEVEMENT_TYPE_POKER_COLOR			= 3,		// 英雄颜色
	ACHIEVEMENT_TYPE_NORMAL_GATE			= 4,		// 普通推图
	ACHIEVEMENT_TYPE_HERO_GATE				= 5,		// 英雄推图
	ACHIEVEMENT_TYPE_NORMAL_CLEAR			= 6,		// 普通关卡通关次数
	ACHIEVEMENT_TYPE_HERO_CLEAR				= 7,		// 英雄关卡通关次数
	ACHIEVEMENT_TYPE_FRIEND_INVITE			= 8,		// 好友邀请
	ACHIEVEMENT_TYPE_END,
};

// 成就开启条件（策划需要知道的，对应achievement表open_type字段）
enum ACHIEVEMENT_OPEN_TYPE
{
	ACHIEVEMENT_OPEN_TYPE_BEGIN,
	ACHIEVEMENT_OPEN_TYPE_USER_LEV				= ACHIEVEMENT_TYPE_LEV,						// 由玩家等级触发
	ACHIEVEMENT_OPEN_TYPE_POKER_COUNT			= ACHIEVEMENT_TYPE_POKER_COUNT,				// 由卡牌收集数量触发
	ACHIEVEMENT_OPEN_TYPE_POKER_COLOR			= 3,										// 由指定颜色卡牌数量触发
	ACHIEVEMENT_OPEN_TYPE_GATE					= 4,										// 由关卡触发
	ACHIEVEMENT_OPEN_TYPE_FRIEND_INVITE			= 5,										// 由好友邀请触发
	ACHIEVEMENT_OPEN_TYPE_OTHER_ACHIEVEMENT		= 9999,										// 由其他成就完成时触发
	ACHIEVEMENT_OPEN_TYPE_END,
};

// 成就系统消息枚举
enum MSG_ACHIEVEMENT_ACTION
{
	MSG_ACHIEVEMENT_ACTION_BEGIN,

	MSG_ACHIEVEMENT_ACTION_QUERY	= 1,		// 查询玩家当前成就进度			C<->S
	MSG_ACHIEVEMENT_ACTION_AWARDS,				// 领取奖励						C<->S
	MSG_ACHIEVEMENT_ACTION_PUSH,				// 向客户端推送已经达成的成就	C<- S
	MSG_ACHIEVEMENT_ACTION_INIT_SYNC,			// 与登陆线程同步成就初始数据	G ->L

	MSG_ACHIEVEMENT_ACTION_UPDATE_REQ,			// 向关系服请求同步更新成就     S ->R
	MSG_ACHIEVEMENT_ACTION_UPDATE_ACK,			// 关系服回应同步更新成就		R ->S

	MSG_ACHIEVEMENT_ACTION_END,
};

enum MSG_ACHIEVEMENT_RESULT_TYPE
{
	MSG_ACHIEVEMENT_RESULT_TYPE_BEGIN			= 0,
	MSG_ACHIEVEMENT_RESULT_TYPE_SUCC			= MSG_ACHIEVEMENT_RESULT_TYPE_BEGIN,			// 操作成功
	MSG_ACHIEVEMENT_RESULT_TYPE_FAIL			= 1,											// 操作失败
	MSG_ACHIEVEMENT_RESULT_TYPE_NOT_OPENED		= 2,											// 成就还没开启
	MSG_ACHIEVEMENT_RESULT_TYPE_NOT_ACHIEVED	= 3,											// 成就要求未达到
	MSG_ACHIEVEMENT_RESULT_TYPE_ID_NOT_CORRECT	= 4,											// 成就id不对
	MSG_ACHIEVEMENT_RESULT_TYPE_END,
};
////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
//排行榜系统
// 排行榜消息action

	// 排行榜 查询竞技场排名消息action
enum MSG_TOPLIST_ARENA_LIST_ACTION
{
	MSG_TOPLIST_ARENA_LIST_ACTION_BEGIN,
	MSG_TOPLIST_ARENA_LIST_ACTION_MULTI_LAST				= 1,	// 查询上期多队竞技场排名数据		C<->S
	MSG_TOPLIST_ARENA_LIST_ACTION_MULTI_THIS				= 2,	// 查询本期多队竞技场排名数据		C<->S
	MSG_TOPLIST_ARENA_LIST_ACTION_SINGLE_LAST				= 3,	// 查询上期竞技场排名数据			C<->S
	MSG_TOPLIST_ARENA_LIST_ACTION_SINGLE_THIS				= 4,	// 查询本期竞技场排名数据			C<->S
	MSG_TOPLIST_ARENA_LIST_ACTION_END,
};

	// 排行榜 查询竞技场玩家详细信息消息action
enum MSG_TOPLIST_ARENA_USER_ACTION
{
	MSG_TOPLIST_ARENA_USER_ACTION_BEGIN,
	MSG_TOPLIST_ARENA_USER_ACTION_MULTI_LAST				= 1,	// 查询上期多队竞技场玩家数据		C<->S
	MSG_TOPLIST_ARENA_USER_ACTION_MULTI_THIS				= 2,	// 查询本期多队竞技场玩家数据		C<->S
	MSG_TOPLIST_ARENA_USER_ACTION_SINGLE_LAST				= 3,	// 查询上期竞技场玩家数据			C<->S
	MSG_TOPLIST_ARENA_USER_ACTION_SINGLE_THIS				= 4,	// 查询本期竞技场玩家数据			C<->S
	MSG_TOPLIST_ARENA_USER_ACTION_END,
};

	// 排行榜  战斗力排行榜消息action
enum MSG_TOPLIST_COMMON_ACTION
{
	MSG_TOPLIST_COMMON_ACTION_BEGIN,
	MSG_TOPLIST_COMMON_ACTION_QUERY_ALL_POKER_FC			= 1,	// 查询全部卡牌战力排名数据			C<->S
	MSG_TOPLIST_COMMON_ACTION_QUERY_MULTI_POKER_FC			= 2,	// 查询多队卡牌战力排名数据			C<->S
	MSG_TOPLIST_COMMON_ACTION_QUERY_TEAM_POKER_FC			= 3,	// 查询小队卡牌战力排名数据			C<->S
	MSG_TOPLIST_COMMON_ACTION_QUERY_TOTAL_POKER_STAR		= 4,	// 查询所有卡牌星级综合排行榜		C<->S
	MSG_TOPLIST_COMMON_ACTION_RESOURCE_PLUNDER_COUNT		= 5,	// 查询资源掠夺次数排名数据			C<->S
	MSG_TOPLIST_COMMON_ACTION_RESOURCE_GOLD_COLLECTED		= 6,	// 查询资源金币采集排名数据			C<->S
	MSG_TOPLIST_COMMON_ACTION_RESOURCE_DRUG_COLLECTED		= 7,	// 查询资源药剂采集数量排名			C<->S
	MSG_TOPLIST_COMMON_ACTION_GLAMOUR_THIS					= 8,	// 查询一周魅力排名数据				C<->S
	MSG_TOPLIST_COMMON_ACTION_GLAMOUR_LAST					= 9,	// 查询上周魅力排名数据				C<->S
	MSG_TOPLIST_COMMON_ACTION_GLAMOUR_TOTAL					= 10,	// 查询总魅力排名数据				C<->S

	MSG_TOPLIST_COMMON_ACTION_UPDATE_RG						= 101,	// 关系服通知服务器更新排行榜		R ->S 

	MSG_TOPLIST_COMMON_ACTION_END,
};

	// 排行榜 公会排行消息action
enum MSG_TOPLIST_SYN_ACTION
{
	MSG_TOPLIST_SYN_ACTION_BEGIN,
	MSG_TOPLIST_SYN_ACTION_THREE_DAYSLIVENESS				= 1,	// 最近3活跃度排名					C<->S			
	MSG_TOPLIST_SYN_ACTION_END,
};

// 排行榜消息结果枚举
enum MSG_TOPLIST_RESULT_TYPE
{
	MSG_TOPLIST_RESULT_TYPE_BEGIN					= 0,
	MSG_TOPLIST_RESULT_TYPE_SUCC					= MSG_TOPLIST_RESULT_TYPE_BEGIN,		// 操作成功
	MSG_TOPLIST_RESULT_TYPE_FAIL					= 1,									// 操作失败 
	MSG_TOPLIST_RESULT_TYPE_START_SENDING			= 2,									// 开始发包
	MSG_TOPLIST_RESULT_TYPE_SENDING					= 3,									// 中间包
	MSG_TOPLIST_RESULT_TYPE_LAST_PACKAGE			= 4,									// 结束包
	MSG_TOPLIST_RESULT_TYPE_END,
};
// 排行榜类别枚举(策划需要知道的）
enum TOPLIST_TYPE
{
	TOPLIST_TYPE_BEGIN,
	TOPLIST_TYPE_MULTI_ARENA_LAST					= 1,	// 竞技场多队上期				
	TOPLIST_TYPE_MULTI_ARENA_THIS					= 2,	// 竞技场多队本期
	TOPLIST_TYPE_ARENA_LAST							= 3,	// 竞技场单队上期
	TOPLIST_TYPE_ARENA_THIS							= 4,	// 竞技场单队本期
	TOPLIST_TYPE_ALL_POKER_FC						= 5,	// 所有卡牌战力和
	TOPLIST_TYPE_MULTI_POKER_FC						= 6,	// 多队卡牌战力和
	TOPLIST_TYPE_TEAM_POKER_FC						= 7,	// 单队卡牌战力和
	TOPLIST_TYPE_TOTAL_POKER_STAR					= 8,	// 所有卡牌星级和
	TOPLIST_TYPE_SYNDICATE_LIVENESS					= 9,	// 公会活跃度
	TOPLIST_TYPE_RESOURCE_PLUNDER					= 10,	// 资源抢夺次数
	TOPLIST_TYPE_RESOURCE_GOLD_COLLECTED			= 11,	// 金币采集量
	TOPLIST_TYPE_RESOURCE_DRUG_COLLECTED			= 12,	// 药剂采集量

	TOPLIST_TYPE_ALL_POKER_FC_LAST					= 13,	// 所有卡牌战力和上期
	TOPLIST_TYPE_MULTI_POKER_FC_LAST				= 14,	// 多队卡牌战力和上期
	TOPLIST_TYPE_TEAM_POKER_FC_LAST					= 15,	// 单队卡牌战力和上期
	TOPLIST_TYPE_TOTAL_POKER_STAR_LAST				= 16,	// 所有卡牌星级和上期
	//TOPLIST_TYPE_RESOURCE_PLUNDER_LAST				= 17,	// 资源抢夺次数上期
	//TOPLIST_TYPE_RESOURCE_GOLD_COLLECTED_LAST		= 18,	// 金币采集量上期
	//TOPLIST_TYPE_RESOURCE_DRUG_COLLECTED_LAST		= 19,	// 药剂采集量上期
	
	TOPLIST_TYPE_GLAMOUR_THIS						= 20,	// 魅力一周排行
	TOPLIST_TYPE_GLAMOUR_LAST						= 21,	// 魅力上周排行
	TOPLIST_TYPE_GLAMOUR_TOTAL						= 22,	// 魅力总排行

	TOPLIST_TYPE_THIS								= 1000,	// 实时排名
	TOPLIST_TYPE_DAILY								= 1001,	// 更新日榜
	TOPLIST_TYPE_WEEKLY								= 1002,	// 更新周榜
	TOPLIST_TYPE_END,
};
////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
//竞技场系统
// 竞技场操作消息action
enum MSG_ARENA_ACT_ACTION
{
	MSG_ARENA_ACT_ACTION_BEGIN,
	MSG_ARENA_ACT_ACTION_SAVE_DEFENSE_TEAM_INFO				= 1,		// 保存单队防守阵容					C<->S
	MSG_ARENA_ACT_ACTION_SAVE_ATTACK_TEAM_INFO				= 2,		// 保存单队进攻阵容					C<->S
	MSG_ARENA_ACT_ACTION_RESET_CD							= 3,		// 重置单队竞技场挑战CD				C<->S
	MSG_ARENA_ACT_ACTION_FIGHT								= 4,		// 开启单队竞技场战斗				C<->S
	MSG_ARENA_ACT_ACTION_QUERY_ATTACK_TEAM_INFO				= 5,		// 查询单队玩家进攻阵容信息			C<->S
	MSG_ARENA_ACT_ACTION_MULTI_SAVE_DEFENSE_TEAM_INFO		= 6,		// 保存多队防守阵容					C<->S
	MSG_ARENA_ACT_ACTION_MULTI_SAVE_ATTACK_TEAM_INFO		= 7,		// 保存多队进攻阵容					C<->S
	MSG_ARENA_ACT_ACTION_MULTI_RESET_CD						= 8,		// 重置多队竞技场挑战CD				C<->S
	MSG_ARENA_ACT_ACTION_MULTI_FIGHT						= 9,		// 开启多队竞技场战斗				C<->S
	MSG_ARENA_ACT_ACTION_QUERY_MULTI_ATTACK_TEAM_INFO		= 10,		// 查询多队玩家进攻阵容信息			C<->S
	MSG_ARENA_ACT_ACTION_MULTI_GET_CUMULATIVE_AWARD			= 11,		// 收取多队累积竞技币				C<->S
	MSG_ARENA_ACT_ACTION_BUY_COUNT							= 12,		// 购买挑战次数						C<->S

	MSG_ARENA_ACT_ACTION_INSERT_RANK_REQ					= 103,		// 向关系服请求添加排名记录			S ->R
	MSG_ARENA_ACT_ACTION_INSERT_RANK_ACK					= 104,		// 关系服应答添加排名记录			R ->S
	MSG_ARENA_ACT_ACTION_END,

};

// 竞技场日志消息action
enum MSG_ARENA_LOG_ACTION
{
	MSG_ARENA_LOG_ACTION_BEGIN,				
	MSG_ARENA_LOG_ACTION_SINGLE				= 1,		// 查询单队日志				C<->S
	MSG_ARENA_LOG_ACTION_MULTI				= 2,		// 查询多队日志				C<->S
	MSG_ARENA_LOG_ACTION_RESULT				= 3,		// 战斗结果					S ->C

	MSG_ARENA_LOG_ACTION_SAVE_RESULT_REQ	= 101,		// 向关系服请求保存结果		S ->R
	MSG_ARENA_LOG_ACTION_SAVE_RESULT_ACK	= 102,		// 关系服应答保存结果		R ->S
	MSG_ARENA_LOG_ACTION_NotifyBeAtk		= 103,		// 被攻击通知				R ->S

	MSG_ARENA_LOG_ACTION_UPDATE_RANK_INFO	= 104,		// 通知游戏服更新排名信息	R ->S
	MSG_ARENA_LOG_ACTIONN_END,
};

// 竞技场消息结果枚举
enum MSG_ARENA_RESULT_TYPE
{
	MSG_ARENA_RESULT_TYPE_BEGIN,
	MSG_ARENA_RESULT_TYPE_SUCC								= MSG_ARENA_RESULT_TYPE_BEGIN,		// 操作成功
	MSG_ARENA_RESULT_TYPE_FAIL								= 1,								// 操作失败 
	MSG_ARENA_RESULT_TYPE_NO_LOG							= 2,								// 没有日志
	MSG_ARENA_RESULT_TYPE_START_SENDING						= 3,								// 多包发送的首包
	MSG_ARENA_RESULT_TYPE_SENDING							= 4,								// 多包发送的中间包
	MSG_ARENA_RESULT_TYPE_LAST_PACKAGE						= 5,								// 多包发送的尾包
	MSG_ARENA_RESULT_TYPE_ATTACK_TEAM_IS_EMPTY				= 6,								// 进攻阵型为空
	MSG_ARENA_RESULT_TYPE_NO_CD_ALREADY						= 7,								// 已经无CD了
	MSG_ARENA_RESULT_TYPE_NO_ENOUGH_VAS						= 8,								// 元宝不足
	MSG_ARENA_RESULT_TYPE_NO_ENOUGH_AWARD					= 9,								// 没有足够的累积货币领取
	MSG_ARENA_RESULT_TYPE_NOT_OPEN							= 10,								// 竞技场没开启
	MSG_ARENA_RESULT_TYPE_IS_FIGHTING						= 11,								// 有战斗进行中
	MSG_ARENA_RESULT_TYPE_NOT_ENOUGH_POKER					= 12,								// 多队战斗卡牌数不足
	MSG_ARENA_RESULT_TYPE_NOT_ENOUGH_VIP_LEV				= 13,								// VIP等级不够 
	MSG_ARENA_RESULT_TYPE_RUN_OUT_OF_BUY_COUNT				= 14,								// 购买次数已用完
	MSG_ARENA_RESULT_TYPE_END,
};
// 竞技场种别枚举
enum ARENA_KIND_TYPE
{
	ARENA_KIND_TYPE_BEGIN,
	ARENA_KIND_TYPE_SINGLE_TEAM					= 1,											// 单队竞技场
	ARENA_KIND_TYPE_MULTI_TEAM					= 2,											// 多队竞技场
	ARENA_KIND_TYPE_END,
};

// 竞技场队伍类型
enum ARENA_POKER_TEAM_TYPE
{
	ARENA_POKER_TEAM_TYPE_BEGIN,
	ARENA_POKER_TEAM_TYPE_SINGLE_ATTACK			= 1,			// 单队进攻队
	ARENA_POKER_TEAM_TYPE_SINGLE_DEFENSE		= 2,			// 单队防守队
	ARENA_POKER_TEAM_TYPE_MULTI_ATTACK			= 3,			// 多队进攻队
	ARENA_POKER_TEAM_TYPE_MULTI_ATTACK_FIRST	= 4,			// 多队进攻1队
	ARENA_POKER_TEAM_TYPE_MULTI_ATTACK_SECOND	= 5,			// 多队进攻2队
	ARENA_POKER_TEAM_TYPE_MULTI_ATTACK_THIRD	= 6,			// 多队进攻3队
	ARENA_POKER_TEAM_TYPE_MULTI_DEFENSE			= 7,			// 多队防守队
	ARENA_POKER_TEAM_TYPE_MULTI_DEFENSE_FIRST	= 8,			// 多队防守1队
	ARENA_POKER_TEAM_TYPE_MULTI_DEFENSE_SECOND	= 9,			// 多队防守2队
	ARENA_POKER_TEAM_TYPE_MULTI_DEFENSE_THIRD	= 10,			// 多队防守3队
	ARENA_POKER_TEAM_TYPE_END,
};

// 竞技场战斗结果
enum ARENA_RESULT_TYPE
{
	ARENA_RESULT_TYPE_BEGIN,
	ARENA_RESULT_TYPE_WIN,
	ARENA_RESULT_TYPE_LOSE,
	ARENA_RESULT_TYPE_END,
};

////////////////////////////////////////////////////////////////////////////////////////////////
// 领地战 战斗消息action
enum MSG_TERRITORY_FIGHT_ACTION
{
	MSG_TERRITORY_FIGHT_ACTION_BEGIN,
	MSG_TERRITORY_FIGHT_ACTION_START_FIGHTING_RS				= 101,			// 开始战斗				R -> S
	MSG_TERRITORY_FIGHT_ACTION_TERRITORY_CAPTURED_SR			= 102,			// 领地被占领			S -> R
	MSG_TERRITORY_FIGHT_ACTION_END,
};

// 领地战消息结果枚举
enum MSG_TERRITORY_RESULT_TYPE
{
	MSG_TERRITORY_RESULT_TYPE_BEGIN,
	MSG_TERRITORY_RESULT_TYPE_SUCC								= MSG_ARENA_RESULT_TYPE_BEGIN,		// 操作成功
	MSG_TERRITORY_RESULT_TYPE_FAIL								= 1,								// 操作失败
	MSG_TERRITORY_RESULT_TYPE_ACTIVITY_NOT_START				= 2,								// 活动未开始
	MSG_TERRITORY_RESULT_TYPE_ACTIVITY_STARTING					= 3,								// 活动已经开始
	MSG_TERRITORY_RESULT_TYPE_NOT_JOIN_SYNDICATE				= 4,								// 玩家没有加入公会
	MSG_TERRITORY_RESULT_TYPE_START_SENDING						= 5,								// 开始发包（多包的时候用）
	MSG_TERRITORY_RESULT_TYPE_SENDING							= 6,								// 正在发包(后面还有包）
	MSG_TERRITORY_RESULT_TYPE_LAST_PACKAGE						= 7,								// 结束包
	MSG_TERRITORY_RESULT_TYPE_NO_MONEY_BE_LEFT					= 8,								// 没有累积币可以领取
	MSG_TERRITORY_RESULT_TYPE_NOT_PREPARE						= 9,								// 不是准备阶段不能操作部队  
	MSG_TERRITORY_RESULT_TYPE_TERRITORY_NEED_DEFENSE			= 10,								// 有领地需要防守 
	MSG_TERRITORY_RESULT_TYPE_ACTIVITY_NOT_FIGHTING				= 11,								// 活动不是战斗阶段
	MSG_TERRITORY_RESULT_TYPE_NOT_JOIN_THIS_FIGHTING			= 12,								// 没有参加该领地的战斗
	MSG_TERRITORY_RESULT_TYPE_THIS_FIGHTING_OVER				= 13,								// 公会在该领地的战斗已经结束 
	MSG_TERRITORY_RESULT_TYPE_END,
};
////////////////////////////////////////////////////////////////////////////////////////////////

// 邮件列表协议Action
enum EMSG_MAIL_LIST_ACTION
{
	EMSG_MAIL_LIST_ACT_QueryMailList	= 1,	// 请求邮件列表			C --> S
	EMSG_MAIL_LIST_ACT_ReturnMailList	= 2,	// 返回请求邮件列表		C <-- S
	EMSG_MAIL_LIST_ACT_NewMailNotify	= 3,	// 新邮件提醒			C <-- S	S <-> R
};

// 邮件状态
enum EMAIL_STATUS
{
	EMAIL_STATUS_Begin		= 0,
	EMAIL_STATUS_UNREAD		= EMAIL_STATUS_Begin,	// 未读
	EMAIL_STATUS_READ		= 1,					// 已读
	EMAIL_STATUS_Del		= 2,					// 删除
	EMAIL_STATUS_End,
};

// 配置文字表id声明
// 注意: 1. 转义符%左侧不能有全角符号 2.如果文字中需要百分号, 需要填写全角的百分号
enum CONFIG_TEXT_ID
{
	CONFIG_TEXT_ID_NONE											= 0,

	// 玩家属性相关配置
	CONFIG_TEXT_ID_USER_NOT_FIND_USER							= 2,		// 玩家不存在或不在线
	CONFIG_TEXT_ID_USER_TO_FAST									= 3,		// 发送消息过快
	CONFIG_TEXT_ID_USER_INVALID_INFO							= 4,		// 不合法的消息
	CONFIG_TEXT_ID_USER_LESS_LEV								= 5,		// 等级不够
	CONFIG_TEXT_ID_USER_LESS_VAS								= 6,		// 元宝不足
	CONFIG_TEXT_ID_USER_STOP_TALK								= 7,		// 禁言中

	// 帮派
	CONFIG_TEXT_ID_CREATESYN_ss									= 201,		// %s创建帮派%s
	CONFIG_TEXT_ID_SYN_RANK_LEADER								= 202,      // 帮主
	CONFIG_TEXT_ID_SYN_RANK_ELDER								= 203,      // 长老
	CONFIG_TEXT_ID_SYN_RANK_NORMAL								= 204,      // 帮众

	// 队伍团队帮派相关
	CONFIG_TEXT_ID_GROUP_SYN_NOT_EXIST							= 2001,		// 帮派不存在

	// 邮件发送者名字Begin(5001 - 5100)
	CONFIG_TEXT_ID_MAIL_SENDER_SYSTEM							= 5001,		// 系统


	// 邮件标题Begin(5101 - 5200)
	CONFIG_TEXT_ID_MAIL_TITLE_SYSTEM							= 5101,		// 系统提示
	CONFIG_TEXT_ID_MAIL_TITLE_ARENA_AWARD						= 5102,		// 竞技场每日排名奖励
	CONFIG_TEXT_ID_MAIL_TITLE_ARENA_UPDATE_RECORD				= 5103,		// 竞技场更新历史记录 标题


	// 邮件内容Begin(5201 - 5400)
	CONFIG_TEXT_ID_MAIL_CONTENT_SYSTEM							= 5201,		// 系统
	CONFIG_TEXT_ID_MAIL_CONTEXT_NEWCARD							= 5202,		// 亲爱的玩家：恭喜你新手卡使用成功，获得以下奖励，请及时提取哦！
	CONFIG_TEXT_ID_MAIL_CONTEXT_AERNA_AWARD_d					= 5203,		// 恭喜您在竞技场比赛中取得【%d】名的好成绩，以下是您获得的奖励！
	CONFIG_TEXT_ID_SYN_REFUSEAPPLY								= 5204,		// 很遗憾，【%s】公会拒绝了你的加入申请！
	CONFIG_TEXT_ID_SUN_QUIT										= 5205,		// 你已经离开了【%s】公会，你将在1小时内无法加入任何公会，并且48小时内不能回到原公会，这些是你遗留在公会里的东西！
	CONFIG_TEXT_ID_MAIL_CONTEXT_WORSHIP_AWARD_LEAVE				= 5206,		// 你已经离开公会【%s】,这些是你在之前公会被膜拜所收获的铜币,请查收!
	CONFIG_TEXT_ID_MAIL_CONTEXT_WORSHIP_AWARDSYN_DISMISS		= 5207,		// 你的公会已解散,这些是你在之前公会被膜拜所收获的铜币,请查收!
	CONFIG_TEXT_ID_MAIL_CONTENT_ARENA_UPDATE_RECORD				= 5208,		// 恭喜您在斗神台比赛中取得【%d】名的最好成绩，以下是您获得的奖励！
	CONFIG_TEXT_ID_MAIL_CONTENT_WARROAD_AWARD_GIVE				= 5209,		// 【%s】分配给您一个战利品，请及时提取哦！
	CONFIG_TEXT_ID_MAIL_CONTENT_WARROAD_AWARD_CUT				= 5210,		// 你申请的战利品【%s】被【%s】插队，这是他给你的补偿，请及时收取哦！
	CONFIG_TEXT_ID_MAIL_CONTENT_WARROAD_COMPLETE_AWARD			= 5211,		// 你的帮派完成了团队副本【%s】。你的单次最高伤害排名第%d，获得%d帮贡奖励！
	CONFIG_TEXT_ID_MAIL_CONTENT_WARROAD_COMPLETE_AWARD_EXTRA	= 5212,		// 由于在限定的时间内完成副本，所有团队成员额外获得%d帮贡！

	// 帮派日志Begin(5401 - 5450)
	CONFIG_TEXT_ID_SYN_LOG_CREATE_SYN							= 5401,		// 【%s】创建公会
	CONFIG_TEXT_ID_SYN_LOG_DIRECT_JOIN_SYN						= 5402,		// 【%s】加入公会
	CONFIG_TEXT_ID_SYN_LOG_EXIT_SYN								= 5403,		// 【%s】退出公会
	CONFIG_TEXT_ID_SYN_LOG_KICK_SYN								= 5404,		// 公会%s【%s】将【%s】踢出了公会
	CONFIG_TEXT_ID_SYN_LOG_AlTER_NOTICE							= 5405,		// 公会%s【%s】修改了公会公告
	CONFIG_TEXT_ID_SYN_LOG_UP_ELDER								= 5406,		// 会长【%s】将【%s】提升为长老
	CONFIG_TEXT_ID_SYN_LOG_DOWN_MEMBER							= 5407,		// 会长【%s】取消了【%s】的长老职位
	CONFIG_TEXT_ID_SYN_LOG_RESET_INSTANCE 						= 5408,		// 公会%s【%s】重置了团队副本：第%d章
	CONFIG_TEXT_ID_SYN_LOG_PASS_INSTANCE  						= 5409,		// 团队副本:第%d章通关,最后一击由【%s】完成
	CONFIG_TEXT_ID_SYN_LOG_TRANSFER_LEADER						= 5410,		// 【%s】将会长职位移交给了【%s】
	CONFIG_TEXT_ID_SYN_LOG_TROPHY_QUEUE							= 5411,		// 【%s】在战利品%s的队列中插队
	CONFIG_TEXT_ID_SYN_LOG_AGREE_JOIN_SYN						= 5412,		// 公会%s【%s】批准了【%s】加入公会
	CONFIG_TEXT_ID_SYN_LOG_ALTER_LEV_LIMIT						= 5413,		// 公会%s【%s】修改了加入公会最小战队等级为：%d级
	CONFIG_TEXT_ID_SYN_LOG_SHARE_TROPHY							= 5414,		// 公会%s【%s】将%s分配给了【%s】
	CONFIG_TEXT_ID_SYN_LOG_ALTER_NEED_CHECK						= 5415,		// 公会%s【%s】修改了公会类型为：需验证
	CONFIG_TEXT_ID_SYN_LOG_ALTER_NO_CHECK						= 5416,		// 公会%s【%s】修改了公会类型为：不需要验证
	CONFIG_TEXT_ID_SYN_LOG_AUTO_TRANSFER_LEADER					= 5417,		// 会长【%s】长时间未上线，会长职位自动禅让给【%s】
	// 帮派日志End(5401 - 5450)

	CONFIG_TEXT_ID_ITEM_POWER_NOT_ENOUGH_d						= 10001,	// 体力不足, 需要体力【%d】点
	CONFIG_TEXT_ID_ITEM_POWER_DEL_d								= 10002,	// 体力-%d
	CONFIG_TEXT_ID_ITEM_POWER_ADD_d								= 10003,	// 体力+%d
	CONFIG_TEXT_ID_ITEM_POWER_FULL								= 10004,	// 体力已满
	CONFIG_TEXT_ID_ITEM_AMOUNT_LIMIT							= 10005,	// 物品已到叠加上限，无法获得！

	CONFIG_TEXT_ID_END,
};

// 配置表类型字段, 有新增可配置的数据即可新增进来, 记得写好这里的注释和数据库comment字段
enum CONFIG_TYPE
{
	CONFIGTYPE_NONE												= 0,
	CONFIGTYPE_USER_CFG											= 1,		// 玩家配置：DATA1:玩家最大等级
	CONFIGTYPE_USER_TALK_TIME_LIMIT								= 2,		// 聊天时间间隔 DATA1:私聊, DATA2:帮派聊天 DATA3:世界聊天
	CONFIGTYPE_USER_POKER_CFG1									= 3,		// 卡牌配置：DATA1:技能点定时增加时间间隔, DATA2:技能点定时增加点数,DATA3:每次购买给的技能点数 DATA4:购买技能点花费元宝数,
	CONFIGTYPE_USER_POKER_CFG2									= 4,		// 卡牌配置：DATA1:装备附魔开启玩家等级, DATA2:卡牌初始限制等级, DATA3:卡牌开放限制等级
	CONFIGTYPE_USER_SHOP_BLACK_MARKET							= 5,		// 黑市商店：DATA1：黑市商店出现时间间隔，DATA2：黑市商店出现概率
	CONFIGTYPE_USER_LOTTERY_CFG1								= 6,		// 抽奖配置：DATA1：金币每天免费抽次数，DATA2：金币抽冷却时间，DATA3：元宝抽冷却时间，DATA4：VIP资格抽限制等级
	CONFIGTYPE_USER_LOTTERY_CFG2								= 7,		// 抽奖配置：DATA1：星际商人出现概率, DATA2：星际商人持续时间, DATA3: 第一次金币抽获得卡牌类型, DATA4: 第一次元宝抽获得卡牌类型
	CONFIGTYPE_MERCENARY_CAMP_CFG								= 8,		// 佣兵配置：DATA1：佣兵最少驻守时间, DATA2：副本佣兵雇佣冷却时间, DATA3：战役佣兵雇佣冷却时间, DATA4:使用佣兵获得的友情点数, DATA5：大雁塔佣兵雇佣限制等级
	CONFIGTYPE_CROSS_NTM_FIGHT_CFG								= 9,		// 南天门斗法配置：DATA1：基础分, DATA2：目标分, DATA3：准备阶段时间，DATA4：挑战阶段时间

	CONFIGTYPE_POKER_LEV_SCORE_CFG								= 10,		// 卡牌等级战力评分配置：DATA1：英雄等级提供的战力
	CONFIGTYPE_POKER_SKILL_SCORE_CFG1							= 11,		// 卡牌技能战力评分配置：DATA1:白色技能激活战力，DATA2:白色技能系数*100，DATA3:绿色技能激活战力，DATA4:绿色技能系数*100
	CONFIGTYPE_POKER_SKILL_SCORE_CFG2							= 12,		// 卡牌技能战力评分配置：DATA1:蓝色技能激活战力，DATA2:蓝色技能系数*100，DATA3:紫色技能激活战力，DATA4:紫色技能系数*100
	CONFIGTYPE_POKER_ATTR_SCORE_CFG1							= 13,		// 卡牌属性战力评分配置：DATA1:气血，DATA2:命中，DATA3:伤害，DATA4:防御，DATA5:速度
	CONFIGTYPE_POKER_ATTR_SCORE_CFG2							= 14,		// 卡牌属性战力评分配置：DATA1:躲避，DATA2:灵力，DATA3:气血回复，DATA4:愤怒回复，DATA5:物爆
	CONFIGTYPE_POKER_ATTR_SCORE_CFG3							= 15,		// 卡牌属性战力评分配置：DATA1:法爆，DATA2:吸血等级，DATA3:愤怒消耗降低%，DATA4:治疗效果提高%，DATA5:属性评分基数

	CONFIGTYPE_BATTER_DROP_RULE_CFG1							= 16,		// 战斗掉落规则配置：DATA1:1上限，DATA2:2上限，DATA3:3上限，DATA4:4上限，DATA5:5上限
	CONFIGTYPE_BATTER_DROP_RULE_CFG2							= 17,		// 战斗掉落规则配置：DATA1:6上限，DATA2:7上限，DATA3:8上限

	CONFIGTYPE_USER_FRIEND_GIFT									= 101,		// 好友礼物配置 DATA1：礼物赠送体力点数
	// CONFIGTYPE_USER_FRIEND_DATA								= 102,		// 好友配置数据 DATA1：好友上限，DATA2：友好度定时增加点数，DATA3：定时增加频率(单位分钟）,DATA4：友好度上限,DATA5:赠送点数
	// CONFIGTYPE_USER_FRIEND_REQUEST							= 103,		// 好友请求配置 DATA1：好友申请保存时间(单位小时),
	// CONFIGTYPE_USER_FRIEND_PUSH								= 104,		// 好友推送配置 DATA1：好友推送数量

	CONFIGTYPE_USER_LIVENESS_BOX								= 111,		// 每日活跃 Data1 - Data4:活跃度达到25, 50, 75, 100的宝箱发奖脚本Action, data5:领取月卡获得的活跃度

	CONFIGTYPE_SYNDICATE_CREATE_LIMIT							= 201,		// 创建帮派 data1需要玩家等级, data2需要元宝
	CONFIGTYPE_SYNDICATE_ACTIVITY_LIMIT							= 202,		// 帮派活跃 data1帮派每日活跃上限, data2成员每日活跃上限
	CONFIGTYPE_SYNDICATE_TERRITORY								= 203,		// 公会领地战 data1领地每天定时增加领地币的时间(小时0~23）,

	// 货币系统 记录日志阀值配置占用 1001~1051
	CONFIGTYPE_MONEY_BEGIN										= 1001,		// DATA1:货币类型 DATA2:入库阀值(未到阀值不写库)，DATA3：保留天数（9999永久）
	CONFIGTYPE_MONEY_TERRITORY									= 1002,		// 领地币 
	CONFIGTYPE_MONEY_END										= 1051,


	// 副本相关
	CONFIGTYPE_CHALLENGE_BOSS_INFO								= 3001,		// 挑战boss data1表示通关消耗体力值, data2表示失败消耗体力值, data3每日最多可挑战次数, data4进入界面等级限制
	CONFIGTYPE_INSTANCE_PASS_CFG								= 3002,		// 副本配置：DATA1:金币副本挑战次数，DATA2:经验副本挑战次数，DATA3:副本失败消耗体力
	CONFIGTYPE_GOOSE_TOWER										= 3003,		// 大雁塔:data1:每天第一次重置可获得的大雁塔币, data2:大雁塔对应的战斗类型, data3:大雁塔奖励脚本ID
	CONFIGTYPE_PUZZLE_CFG										= 3004,		// 迷宫配置:data1:妖界每天最大次数，data2:鬼界每天最大次数，data3:魔界每天最大次数
	CONFIGTYPE_PUZZLE_FLOOR_CFG									= 3005,		// 迷宫配置:data1-data5表示1-5层默认站立格子
	CONFIGTYPE_PUZZLE_FLOOR_COUNT_CFG							= 3006,		// 迷宫配置:data1:低等级层数，data2:中等级层数，data3：高等级层数
	CONFIGTYPE_MINE_CFG											= 3007,		// 矿洞配置:data1:矿洞寻宝体力恢复上限, data2:战斗消耗寻宝体力点数, data3:搜索矿地需等级差值, data4:矿洞被挑战次数上限, data5:矿洞战斗类型
	CONFIGTYPE_MINE_RAND_VAS_NUM_CFG							= 3008,		// 矿洞配置:data1-data5 表示钻石的数量
	CONFIGTYPE_MINE_RAND_VAS_RATE_CFG							= 3009,		// 矿洞配置:data1-data5 表示钻石的几率
	CONFIGTYPE_WARROAD_CFG1										= 3010,		// 战役配置:DATA1:普通和精英模式失败消耗体力, DATA2:精英模式每天可挑战次数，DATA3:普通和精英模式扫荡消耗道具，DATA4:扫荡消耗数量，DATA5:扫荡一次消耗元宝
	CONFIGTYPE_WARROAD_CFG2										= 3011,		// 战役配置:DATA1:团队模式每天关闭时间，DATA2:团队模式每天开启时间，DATA3:团队模式战利品发放时间，DATA4:团队模式战利品发放结束时间, DATA5:团队模式战利品发放时间间隔
	CONFIGTYPE_WARROAD_CFG3										= 3012,		// 战役配置:DATA1:团队模式准备时间,DATA2:团队模式战斗时间
	CONFIGTYPE_MINE_TREASUREPOWER_CFG							= 3013,		// 寻宝体力配置:data1:定时恢复时间, data2:定时恢复点数
	CONFIGTYPE_INSTANCE_END										= 3999,		

	// 日志系统相关
	CONFIGTYPE_LOG_BEGIN										= 4000,
	CONFIGTYPE_LOG_END											= 4999,

	// 排行榜竞技场系统相关
	CONFIGTYPE_TOPLIST_BEGIN									= 5000,
	CONFIGTYPE_TOPLIST_ARENA									= 5001,		// 单人竞技场：DATA1：最大挑战次数，DATA2：挑战冷却时间（单位秒），DATA3：重置费用,DATA4:开启等级
	CONFIGTYPE_TOPLIST_ARENA_TARGET_RANK1						= 5002,		// 单人竞技场对手名次设定：DATA1：第一格上限，DATA2：第一格下限(均为万分比）
	CONFIGTYPE_TOPLIST_ARENA_TARGET_RANK2						= 5003,		// 单人竞技场对手名次设定：DATA1：第二格上限，DATA2：第二格下限(均为万分比）
	CONFIGTYPE_TOPLIST_ARENA_TARGET_RANK3						= 5004,		// 单人竞技场对手名次设定：DATA1：第三格上限，DATA2：第三格下限(均为万分比）
	CONFIGTYPE_TOPLIST_ARENA_MULIT								= 5011,		// 多人竞技场：DATA1：最大挑战次数, DATA2：挑战冷却时间（单位秒）, DATA3：重置费用,DATA4:开启等级
	CONFIGTYPE_TOPLIST_ARENA_MULTI_TARGET_RANK1					= 5012,		// 多人竞技场对手名次设定：DATA1：第一格上限，DATA2：第一格下限(均为万分比）
	CONFIGTYPE_TOPLIST_ARENA_MULTI_TARGET_RANK2					= 5013,		// 多人竞技场对手名次设定：DATA1：第二格上限，DATA2：第二格下限(均为万分比）
	CONFIGTYPE_TOPLIST_ARENA_MULTI_TARGET_RANK3					= 5014,		// 多人竞技场对手名次设定：DATA1：第三格上限，DATA2：第三格下限(均为万分比）
	CONFIGTYPE_TOPLIST_UPDATE_TIME								= 5015,		// 排行榜更新时间：DATA1：日榜更新时间（单位：小时 范围0~23)
	CONFIGTYPE_TOPLIST_ARENA_TIME								= 5016,		// 竞技场更新时间：DATA1：单队竞技场每日奖励的领取时间（单位：小时 范围0~23）
	CONFIGTYPE_TOPLIST_ARENA_MULTI_MASK							= 5017,		// 多队竞技场掩码设置排名:DATA1：掩藏全部排名，DATA2：掩藏第二三队排名，DATA3：掩藏第三队排名
	CONFIGTYPE_TOPLIST_ARENA_OPEN_LEV							= 5018,		// 竞技场开启等级配置：DATA1：单队开启等级，DATA2：多队开启等级
	CONFIGTYPE_TOPLIST_END										= 5999,
	
	CONFIGTYPE_SYN_WORSHIP_FREE									= 6000,		// 帮派膜拜大神 免费膜拜：data1:膜拜消耗, data2:膜拜获得的体力值, data3:被膜拜奖励类型, data4:被膜拜奖励数量 
	CONFIGTYPE_SYN_WORSHIP_GOLD									= 6001,		// 帮派膜拜大神 金币膜拜：data1:膜拜消耗, data2:膜拜获得的体力值, data3:被膜拜奖励类型, data4:被膜拜奖励数量 
	CONFIGTYPE_SYN_WORSHIP_VAS									= 6002,		// 帮派膜拜大神 钻石膜拜：data1:膜拜消耗, data2:膜拜获得的体力值, data3:被膜拜奖励类型, data4:被膜拜奖励数量
	CONFIGTYPE_FRIEND_INVITE									= 6003,		// 好友邀请 data1:被邀请奖励脚本Action, data2:可输入邀请码的最大等级, data3:返利万分比(1000表示10%)

	CONFIGTYPE_TALK_RECORD_LIMIT								= 6004,		// 聊天配置:data1:世界聊天记录上限; data2:帮派聊天记录上限; data3:私聊记录上限
	CONFIGTYPE_SYSTEM_SETTINGS									= 6005,		// 系统设置:data1:改名消耗元宝数量, data2:改性别消耗元宝数量, data3:改生日消耗元宝数量, data4:默认头像ID, data5:默认头像框
	CONFIGTYPE_SYSTEM_POWER										= 6006,		// 体力：data1:体力恢复时间间隔，data2：体力定时恢复点数, data3：购买体力点数
	CONFIGTYPE_HGS_FIGHT_CONFIG1								= 6007,		// 花果山大战配置1：data1:玩家最多可携带水果数量, data2:每次刷新水果的种数, data3:花果山大战地图长(X), data4:花果山大战地图宽(Y)
	CONFIGTYPE_BLACK_LIST										= 6008,		// 黑名单：data1:数量限制
	CONFIGTYPE_TALK_CONFIG										= 6009,		// 聊天：data1:世界聊天花费(元宝)

	
	CONFIGTYPE_END,
};

// 货币类型
enum USER_MONEY_TYPE
{
	USER_MONEY_TYPE_NONE			= 0,
	USER_MONEY_TYPE_BEGIN			= 100,
	USER_MONEY_TYPE_MONEY			= 101,	// 金币
	USER_MONEY_TYPE_POWER			= 102,	// 体力
	USER_MONEY_TYPE_SKILL_POINT		= 103,	// 技能点
	USER_MONEY_TYPE_SYN_PROF		= 104,	// 帮贡
	USER_MONEY_TYPE_CHALLENGE		= 105,	// 竞技币
	USER_MONEY_TYPE_CHALLENGE_TOP	= 106,	// 巅峰竞技币
	USER_MONEY_TYPE_TOWER			= 107,	// 大雁塔币
	USER_MONEY_TYPE_TREASURE_POWER	= 108,	// 寻宝体力
	USER_MONEY_TYPE_PUZZLE			= 109,	// 迷宫币
	USER_MONEY_TYPE_TERRITORY		= 110,	// 领地币
	USER_MONEY_TYPE_FRIENDSHIP_POINT= 111,	// 友情点数
	USER_MONEY_TYPE_HGS_BATTLE_SCORE= 112,	// 花果山大战积分
	USER_MONEY_TYPE_END,

	USER_MONEY_TYPE_VAS				= 998,	// 元宝, 实时读写账号库
};

enum MONTH_CARD_TYPE					// 月卡类型
{
	MONTH_CARD_TYPE_NONE		= 0,
	MONTH_CARD_TYPE_NORMAL		= 1,	// 普通月卡
	MONTH_CARD_TYPE_SYN			= 2,	// 帮派任性月卡
};

// 矿类型
enum MINE_TYPE
{
	MINE_TYPE_Beg		= 0,
	MINE_TYPE_GOLD_MINE = 1,	// 金矿
	MINE_TYPE_DREAM_BOOK= 2,	// 藏经阁
	MINE_TYPE_End,
};

// 矿规模
enum MINE_SCALE
{
	MINE_SCALE_Beg		= 0,
	MINE_SCALE_SMALL	= 1,	// 小型
	MINE_SCALE_MIDDLE	= 3,	// 中型
	MINE_SCALE_BIG		= 10,	// 大型
	MINE_SCALE_End,
};

// 膜拜大神消息Action
enum MSG_SYN_WORSHIP_ACTION
{
	MSG_SYN_WORSHIP_ACT_QueryWorshipInfo		= 1,	// 请求查询膜拜信息			C --> S
	MSG_SYN_WORSHIP_ACT_ReturnWorshipInfo		= 2,	// 返回请求查询膜拜信息		C <-- S
	MSG_SYN_WORSHIP_ACT_ReqWorship				= 3,	// 请求膜拜					C --> S
	MSG_SYN_WORSHIP_ACT_AckWorship				= 4,	// 返回请求膜拜				C <-- S
	MSG_SYN_WORSHIP_ACT_ReqGainAward			= 5,	// 请求领取被膜拜奖励		C --> S
	MSG_SYN_WORSHIP_ACT_AckGainAward			= 6,	// 返回请求领取被膜拜奖励	C <-- S
	MSG_SYN_WORSHIP_ACT_UpdateBeworshipInfo		= 7,	// 同步已膜拜信息			C <-- S
};

// 玩家掩码ID服务器占用声明枚举				服务端使用:按位掩码ID (0 - 5000) 计数掩码ID(10000 - 20000)
enum E_USER_MASKID_PROGRAM
{
	// 任务掩码ID开始
	// 任务码ID结束

	// 奖励掩码ID开始
	EUMIP_GIVE_BIT_LOTTERY					= 1,		// 抽奖获得掩码
	EUMIP_GIVE_BIT_USER_SYSTEMSETTINGS		= 2,		// 人物系统免费修改标记(位0姓名，位1性别)
	// 奖励掩码ID结束

	// 天掩码ID开始
	EUMIP_DAY_BIT_LiveBoxStatus				= 1,		// 每日活跃 活跃度宝箱打开标记(目前使用第2到第5二进制位)
	EUMIP_DAY_BIT_LiveAwardStatus			= 2,		// 每日活跃 活跃项奖励领取标记(目前使用第1到第50二进制位)
	EUMIP_DAY_BIT_MsgSwitchReceivePower		= 3,		// 系统设置消息推送 每日活跃体力领取推送标记(分别表示午餐，晚餐，夜宵)
	EUMIP_DAY_BIT_MsgSwitchRefreshShop		= 4,		// 系统设置消息推送 商店刷新推送标记(分别表示刷新时间1到刷新时间5)

	EUMIP_DAY_COUNT_LiveValues				= 10001,	// 每日活跃 当前活跃度
	EUMIP_DAY_COUNT_LiveCountBeg			= 10002,	// 每日活跃项计数开始(10002 - 10052)
	EUMIP_DAY_COUNT_LiveCountEnd			= 10052,	// 每日活跃项计数结束(10002 - 10052)
	EUMIP_DAY_COUNT_LOTTERY_MONEY			= 10053,	// 每日金币免费单抽使用次数
	EUMIP_DAY_COUNT_INSTANCE_MONEY			= 10054,	// 每日金币副本挑战次数
	EUMIP_DAY_COUNT_INSTANCE_EXP			= 10055,	// 每日经验副本挑战次数
	EUMIP_DAY_COUNT_SYN_MONTH_CARD			= 10056,	// 每日帮派任性月卡领取记录
	EUMTP_DAY_COUNT_BUY_ARENA_COUNT			= 10058,	// 每日竞技场购买次数
	EUMTP_DAY_COUNT_BUY_MULTI_ARENA_COUNT	= 10059,	// 每日多队竞技场购买次数
	EUMTP_DAY_COUNT_BUFF_QXXL_COUNT			= 10060,	// 每日buff齐心协力增加次数
	// 天掩码ID结束

	// 周掩码ID开始
	// 周掩码ID结束

	// 月掩码ID开始
	EUMIP_MONTH_BIT_SIGN					= 1,		// 每日签到掩码
	// 月掩码ID结束
};

// 服务器组掩码ID服务器占用声明枚举			服务端使用:按位掩码ID (0 - 10000)
enum E_GROUPSERVER_MASKID_PROGRAM
{
	EGSMP_BEN								= 0,
	EGSMP_ARENA_DAILY						= 1,		// 竞技场每日榜掩码
	EGSMP_TOPLIST_DAILY						= 2,		// 排行榜每日榜掩码
	EGSMP_TOPLIST_WEEKLY					= 3,		// 排行榜每周榜掩码
	EGSMP_END								= 10000,
};

// 世界服掩码ID服务器占用声明枚举			服务端使用:按位掩码ID (0 - 10000)
enum E_WORLDSERVER_MASKID_PROGRAM
{
	EWSMP_BEN								= 0,
	EWSMP_CHALLENGE_BOSS					= 1,		// 挑战boss每日BosssType掩码
	EWSMP_END								= 10000,
};

// VIP类型枚举
enum VIP_TYPE
{
	VIP_TYPE_Beg								= 1000,
	VIP_TYPE_DAY_CLEAN_ROLL						= 1001,	// 每天领取扫荡卷
	VIP_TYPE_POWER_BUY							= 1002,	// 购买体力次数	
	VIP_TYPE_WAVE_MONEY_COUNT					= 1003,	// 摇钱树次数		
	VIP_TYPE_SKILL_POINT_LIMIT					= 1004,	// 技能点上限			
	VIP_TYPE_PLANT_FIELD_COUNT					= 1005,	// 可种植田地数			
	VIP_TYPE_DAY_WORSHIP_BIGGOD_COUNT			= 1006,	// 每天可膜拜大神次数		
	VIP_TYPE_VAS_CLEAN_BARRIER					= 1007,	// 元宝扫荡关卡			
	VIP_TYPE_RESET_ELITE_BARRIER_COUNT			= 1008,	// 重置精英关卡次数			
	VIP_TYPE_VAS_BUY_SKILL_STREN_POINT			= 1009,	// 元宝购买技能强化点		
	VIP_TYPE_DAY_BUY_ARENA_COUNT				= 1010,	// 每天购买竞技场次数		
	VIP_TYPE_ARENA_CD_RESET_BYVAS				= 1011,	// 竞技场挑战CD元宝清0		
	VIP_TYPE_MANY_ARENA_BUY_COUNT				= 1012,	// 多队竞技场购买次数		
	VIP_TYPE_MANY_ARENA_CD_RESET_BYVAS			= 1013,	// 多队竞技场CD元宝清0		
	VIP_TYPE_ONEKEY_CLEAN_TEN					= 1014,	// 一键扫荡十次				
	VIP_TYPE_SYNINSTANCE_DAY_PROFFER_ADD		= 1015,	// 帮派副本每日任务帮贡+50%	
	VIP_TYPE_SYNINSTANCE_MONEY_ADD				= 1016,	// 帮派副本金币+100%		
	VIP_TYPE_ONEKEY_EQUIP_MAGIC					= 1017,	// 一键装备附魔				
	VIP_TYPE_RANDOM_MAN_FOREVER_EXIST			= 1018,	// 随机商人永久存在			
	VIP_TYPE_SYN_VAS_WORSHIP					= 1019,	// 帮派元宝膜拜				
	VIP_TYPE_TOWER_DAY_RESET_TWO				= 1020,	// 大雁塔每天可重置2次		
	VIP_TYPE_HIGH_RANDOM_SHOP_FOREVER_EXIST		= 1021,	// 高级随机商店永久存在		
	VIP_TYPE_SPECIFIC_HERO						= 1022,	// V12特有英雄				
	VIP_TYPE_TOWER_AWARD						= 1023,	// 大雁塔宝箱金币和物品奖励+50%	
	VIP_TYPE_MERCENARY_NUM						= 1024,	// 能够派遣的佣兵数量	
	VIP_TYPE_DAY_TEAM_INS_CHALLENGE_COUNT		= 1025,	// 团队副本每天挑战次数
	VIP_TYPE_End,
};

// 活动类型
enum ACTIVITY_CONFIG_TYPE
{
	ACTIVITY_CONFIG_TYPE_BEGIN,
	ACTIVITY_CONFIG_TYPE_TERRITORY_FIGHT_PREPARE			= 1,		// 公会领地战准备阶段
	ACTIVITY_CONFIG_TYPE_TERRITORY_FIGHT_MARCH				= 2,		// 公会领地战行军阶段
	ACTIVITY_CONFIG_TYPE_TERRITORY_FIGHT_FIGHTING			= 3,		// 公会领地战战斗阶段
	ACTIVITY_CONFIG_TYPE_NTM_FIGHT							= 4,		// 南天门斗法

	ACTIVITY_CONFIG_TYPE_EXTRA_Beg							= 100,		// 运营活动类型开始

	ACTIVITY_CONFIG_TYPE_EXTRA_AWARD_UP_LEV					= 101,		// 运营额外活动:冲级送礼			*客户端执行action	需要等级		
	ACTIVITY_CONFIG_TYPE_EXTRA_AWARD_PAY_VAS				= 102,		// 运营额外活动:充值送礼			*客户端执行action	需要充值金额		

	ACTIVITY_CONFIG_TYPE_EXTRA_LOGIN_MAIL					= 103,		// 运营额外活动:登陆送礼			*登陆脚本主动执行

	ACTIVITY_CONFIG_TYPE_EXTRA_AWARD_LOGIN_TOTAL			= 104,		// 运营额外活动:累计登陆送礼		*客户端执行action	需要累计登陆天数
	ACTIVITY_CONFIG_TYPE_EXTRA_AWARD_LOGIN_CONTINUE			= 105,		// 运营额外活动:连续登陆送礼		*客户端执行action	需要连续登陆天数
	ACTIVITY_CONFIG_TYPE_EXTRA_AWARD_LOTTERY_VAS			= 106,		// 运营额外活动:元宝抽卡送礼		*客户端执行action	需要元宝抽卡次数

	ACTIVITY_CONFIG_TYPE_EXTRA_MULTI_AWARD_AERNA_RANK		= 107,		// 运营额外活动:竞技场排名奖励		nParam1表示奖励倍数
	ACTIVITY_CONFIG_TYPE_EXTRA_MULTI_AWARD_POWER_TIME		= 108,		// 运营额外活动:定时领体力奖励		nParam1表示奖励倍数

	ACTIVITY_CONFIG_TYPE_EXTRA_MULTI_DROP_ITEM				= 109,		// 运营额外活动:指定道具多倍掉落	nParam1表示多倍掉落几率,nParam2表示多倍掉落数量
	ACTIVITY_CONFIG_TYPE_EXTRA_MULTI_DROP_COMMON			= 110,		// 运营额外活动:普通关卡多倍掉落	nParam1表示多倍掉落几率,nParam2表示多倍掉落数量
	ACTIVITY_CONFIG_TYPE_EXTRA_MULTI_DROP_ELITE				= 111,		// 运营额外活动:精英关卡多倍掉落	nParam1表示多倍掉落几率,nParam2表示多倍掉落数量
	ACTIVITY_CONFIG_TYPE_EXTRA_MULTI_DROP_INSTANCE			= 112,		// 运营额外活动:副本关卡多倍掉落	nParam1表示多倍掉落几率,nParam2表示多倍掉落数量

	ACTIVITY_CONFIG_TYPE_EXTRA_SHOP							= 113,		// 运营额外活动:指定类型商店折扣    nParam1表示商店类型,nParam2表示折扣,取值[1,100],

	ACTIVITY_CONFIG_TYPE_EXTRA_End							= 999,		// 运营活动类型结束

	ACTIVITY_CONFIG_TYPE_END,
};

// 活动时间类型
enum ACTIVITY_CONFIG_TIME_TYPE
{
	ACTIVITY_CONFIG_TIME_TYPE_MINUTE		= 1,		// 通过唯一的minute配置一次性时间					*YYMMDDHHMM时间格式
	ACTIVITY_CONFIG_TIME_TYPE_EVERYDAY		= 2,		// 每天活动											*HHMMSS时间格式
	ACTIVITY_CONFIG_TIME_TYPE_FROM_START	= 3,		// 从开服算起, 按秒记								*开始结束时间配置: 结束 - 开始为活动总时长（单位为分钟）
	ACTIVITY_CONFIG_TIME_TYPE_ACTION		= 4,		// 调用接口触发的活动
	ACTIVITY_CONFIG_TIME_TYPE_WEEK_MULTIDAY = 5,		// 每周跨天活动										*例：1103059 表示 周一10:30:59, 百万位表示周几（0为周末）
	ACTIVITY_CONFIG_TIME_TYPE_WEEK_BEGIN	= 10,		// 通过每周每天标准配置, begin						*TimeType的个位数表示周几（0-6），开始结束时间配置格式 HHMMSS
	ACTIVITY_CONFIG_TIME_TYPE_WEEK_END		= 16,		// 通过每周每天标准配置, end
	ACTIVITY_CONFIG_TIME_TYPE_MONTH_BEGIN	= 101,		// 每月配置 BEGIN									*TimeType个位十位表示每月日期(1-31),开始结束时间配置格式 HHMMSS
	ACTIVITY_CONFIG_TIME_TYPE_MONTH_END		= 131,		// 每月配置 END
};

enum ACTIVITY_GET_SECOND_TYPE
{
	ACTIVITY_GET_SECOND_TYPE_BEGIN	= 1,
	ACTIVITY_GET_SECOND_TYPE_END	= 2,
};

// 矿洞排行类型枚举
enum MINE_TOPLIST_TYPE
{
	MINE_TOPLIST_TYPE_Beg		= 0,
	MINE_TOPLIST_TYPE_ATK_COUNT = 1,	// 攻击次数
	MINE_TOPLIST_TYPE_MONEY		= 2,	// 金币
	MINE_TOPLIST_TYPE_DRUG		= 3,	// 药剂
	MINE_TOPLIST_TYPE_End,
};


// 消息包开始结束标记
enum MSG_PACKET_FLAG
{
	MSG_PACKET_FLAG_NONE	= 0,
	MSG_PACKET_FLAG_BEGIN	= 1,	// 开始包
	MSG_PACKET_FLAG_END		= 2,	// 结束包
};

/////////////////////////////////////////////////////////////////////////////////////////
// 矿洞服务器间消息
enum MSG_MINE_SERVER_ACTION
{
	MSG_MINE_SERVER_ACTION_AckMineEnd	= 1,		// 关系服通知矿洞结束	R->S
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
	CROSS_ROOM_TYPE_NTM = 1,	// 南天门斗法
	CROSS_ROOM_TYPE_HGS = 2,	// 花果山大战
	CROSS_ROOM_TYPE_END,
};

// 卡牌评分系数
enum POKER_SCORE_PARAM				// 卡牌评分系数
{
	PSP_BEGIN = 0,
	PSP_POKER_LEV,					// 卡牌等级系数

	PSP_SKILL_WHITE_ACTIVATE,		// 白色技能激活系数
	PSP_SKILL_WHITE_LEV,			// 白色技能等级系数
	PSP_SKILL_GREEN_ACTIVATE,		// 绿色技能激活系数
	PSP_SKILL_GREEN_LEV,			// 绿色技能等级系数
	PSP_SKILL_BLUE_ACTIVATE,		// 蓝色技能激活系数
	PSP_SKILL_BLUE_LEV,				// 蓝色技能等级系数
	PSP_SKILL_PURPLE_ACTIVATE,		// 紫色技能激活系数
	PSP_SKILL_PURPLE_LEV,			// 紫色技能等级系数

	PSP_ATTR_HP,					// 二级属性 气血
	PSP_ATTR_SP,					// 二级属性	愤怒
	PSP_ATTR_HIT,					// 二级属性	命中
	PSP_ATTR_ATK,					// 二级属性	伤害
	PSP_ATTR_DEF,					// 二级属性	防御
	PSP_ATTR_SPD,					// 二级属性	速度
	PSP_ATTR_DODGE,					// 二级属性	闪避
	PSP_ATTR_MAGIC,					// 二级属性	灵力
	PSP_ATTR_HP_RECOVER,			// 特殊属性 气血回复
	PSP_ATTR_SP_RECOVER,			// 特殊属性	愤怒回复
	PSP_ATTR_PHY_CRIT,				// 特殊属性	物暴
	PSP_ATTR_MAG_CRIT,				// 特殊属性	法爆
	PSP_ATTR_VAMPIRE_LEV,			// 特殊属性	吸血等级
	PSP_ATTR_SP_SPEND_DECREASE,		// 特殊属性	愤怒消耗降低%
	PSP_ATTR_CURE_INCREASE,			// 特殊属性	治疗技能效果提高%
	PSP_ATTR_BASE,					// 属性评分基数
	PSP_END,
};

enum PROPERTYCALCRANK2				// 卡牌二级属性转化系数类型
{
	PROPERTYCALCRANK2_NONE	= 0,
	PROPERTYCALCRANK2_XIAN  = 1,	// 仙（此处3个阵营类型要与卡牌阵营对齐）
	PROPERTYCALCRANK2_MO	= 2,	// 魔
	PROPERTYCALCRANK2_FO	= 3,	// 佛
	PROPERTYCALCRANK2_MAGIC	= 4,	// 灵力
	PROPERTYCALCRANK2_SPD	= 5,	// 速度
};

#endif // end of _GLOBAL_ENUMDEF_HEADER_