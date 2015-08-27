////////////////////////////////////////////////////////////////////////
// Import : 游戏库内容全局声明处
// Moudle : DatabaseDefineGame.h
// Author : 陈建军(Chen Jianjun)
// Created: 2015-08-27
////////////////////////////////////////////////////////////////////////
#ifndef _DATABASE_DEFINE_GAME_H_
#define _DATABASE_DEFINE_GAME_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

static const char* GAME_DB_NAME_USER = "user";	// 角色表
enum USER_DATA
{
	USER_DATA_ID = 0,			// 角色id, 1000W起				bigint
	USER_DATA_NAME,				// 角色名						varchar32
	USER_DATA_ACCOUNT_ID,		// 账号id						uint
	USER_DATA_ACCOUNT_TYPE,		// 账号类型, 账号表覆盖			uint
	USER_DATA_CREATE_TIME,		// 创建时间(utc时间)			uint
	USER_DATA_LOGIN_TIME,		// 登陆日期(YYYYMMDD)			uint
	USER_DATA_EXIT_TIME,		// 退出时间(utc时间)			uint
	USER_DATA_ALL_ONLINE_TIME,	// 总在线时间(单位秒)			uint
	USER_DATA_DEL_FLAG,			// 待删除标记					uint
	USER_DATA_SERVER_GROUP,		// 归属服务器组					uint
	USER_DATA_LEV,				// 等级							uint
	USER_DATA_EXP,				// 经验							bigint
	USER_DATA_CAMP,				// 阵营							uint
	USER_DATA_FLAGSHIP,			// 旗舰							uint
	USER_DATA_SCORE,			// 战斗力						uint
	USER_DATA_RECORD_GALAXY,	// 记录星系						uint
	USER_DATA_RECORD_X,			// 记录坐标X					uint
	USER_DATA_RECORD_Y,			// 记录坐标Y					uint
	USER_DATA_RECORD_REST,		// 记录落脚点NPC				uint
	USER_DATA_STOPTALK_ENDTIME,	// 禁言结束时间					uint
};

//static const char* GAME_DB_NAME_USER_MONEY = "user_money";	// 角色金币表
//enum USER_MONEY_DATA
//{
//	USER_MONEY_DATA_ID = 0,		// id			bigint
//	USER_MONEY_DATA_USERID,		// 角色id		bigint
//	USER_MONEY_DATA_MONEYTYPE,	// 货币类型		uint
//	USER_MONEY_DATA_MONEYDATA,	// 货币数据		bigint
//};
//
//static const char* GAME_DB_NAME_USER_VAS = "user_vas";	// 角色元宝表
//enum USER_VAS_DATA
//{
//	USER_VAS_DATA_USER_ID = 0,				// 角色id			uint
//	USER_VAS_DATA_VAS,						// 当前元宝			bigint
//	USER_VAS_DATA_TOTAL_PAY_VAS,			// 总充值元宝		bigint
//	USER_VAS_DATA_TOTAL_FREE_VAS,			// 总赠送元宝		bigint
//	USER_VAS_DATA_TOTAL_USE_VAS,			// 总消费元宝		bigint
//	USER_VAS_DATA_FISRT_SPEND_TIME,			// 第一次消费时间	uint
//	USER_VAS_DATA_LAST_SPEND_TIME,			// 最近消费时间		uint
//	USER_VAS_DATA_MONTH_CARD_ID,			// 月卡id			uint
//	USER_VAS_DATA_MONTH_CARD_GOT_DATE,		// 领取到的日期		uint
//	USER_VAS_DATA_MONTH_CARD_END_DATE,		// 最后一天领取日期	uint
//	USER_VAS_DATA_FISRT_MASK,				// 第一次领取掩码	uint
//};
//
//static const char* GAME_DB_NAME_USER_MASK = "user_mask";	// 人物掩码表
//enum USER_MASK_DATA
//{
//	USER_MASK_DATA_ID = 0,				// id,			int
//	USER_MASK_DATA_USERID,				// 玩家id,		uint
//	USER_MASK_DATA_MASKTYPE,			// 掩码类型,	uint
//	USER_MASK_DATA_MASKID,				// 掩码id,		uint
//	USER_MASK_DATA_CLEARTIME,			// 结束时间		uint
//	USER_MASK_DATA_MASKDATA,			// 掩码数据		bigint
//};
//
//static const char* GAME_DB_NAME_GROUP_MASK = "group_mask";	// 组掩码表
//enum LINE_MASK_DATA
//{
//	LINE_MASK_DATA_ID = 0,				// 掩码id,		int
//	LINE_MASK_DATA_SERVER_GROUP,		// 服务器组,	uint
//	LINE_MASK_DATA_DATA,				// 数据			uint
//	LINE_MASK_DATA_ENDTIME,				// 结束时间		uint
//};
//
//static const char* GAME_DB_NAME_WORLD_MASK = "world_mask";	// 世界掩码表
//enum SERVER_MASK_DATA
//{
//	SERVER_MASK_DATA_ID = 0,			// 掩码id,		int
//	SERVER_MASK_DATA_DATA,				// 数据			uint
//	SERVER_MASK_DATA_ENDTIME,			// 结束时间		uint
//};
//
//static const char* GAME_DB_NAME_ITEM_LOG = "item_log";	// 物品流向表
//enum LOG_ITEM_FLOW_DATA
//{
//	LOG_ITEM_FLOW_DATA_ID = 0,		// 自增长id					bigint
//	LOG_ITEM_FLOW_DATA_OWNERID,		// 主人id					uint
//	LOG_ITEM_FLOW_DATA_TARGETID,	// 操作对象id				uint
//	LOG_ITEM_FLOW_DATA_ITEMID,		// 物品id					bigint
//	LOG_ITEM_FLOW_DATA_ITEMTYPE,	// 物品typeid				uint
//	LOG_ITEM_FLOW_DATA_ITEMCOUNT,	// 物品数量					uint
//	LOG_ITEM_FLOW_DATA_TYPE,		// 物品流向					uint
//	LOG_ITEM_FLOW_DATA_CREATETIME,	// 创建时间(utc时间）		uint
//	LOG_ITEM_FLOW_DATA_SERVERID,	// 服务器组					uint
//	LOG_ITEM_FLOW_DATA_LINE,		// 线路						uint
//	LOG_ITEM_FLOW_DATA_COMMENT,		// 说明字段					varchar128
//};
//
//static const char* GAME_DB_NAME_USER_TMP_DATA = "user_tmp_data";	// 角色Tmpdata表
//enum USERTMPDATA_DATA
//{
//	USERTMPDATA_ERROR = -1,
//	USERTMPDATA_ID = 0,							// id		bigint										
//	USERTMPDATA_USERID,							// 玩家id	uint
//	USERTMPDATA_TMP_DATA_ID,					// 数据id	uint
//
//	USERTMPDATA_DATA_BEGIN,
//	USERTMPDATA_DATA0 = USERTMPDATA_DATA_BEGIN,	// 数据0	uint
//	USERTMPDATA_DATA1,							// 数据1	uint
//	USERTMPDATA_DATA2,							// 数据2	uint
//	USERTMPDATA_DATA3,							// 数据3	uint					
//	USERTMPDATA_DATA4,							// 数据4	uint
//	USERTMPDATA_DATA5,							// 数据5	uint
//	USERTMPDATA_DATA6,							// 数据6	uint
//	USERTMPDATA_DATA7,							// 数据7	uint
//	USERTMPDATA_DATA_END,
//};
//
//static const char* GAME_DB_NAME_USER_TASK = "user_task";			// 角色任务表
//enum EUSER_TASK
//{	
//	EUSER_TASK_ID			= 0,	// 编号														uint
//	EUSER_TASK_USER_ID,				// 玩家id													uint
//	EUSER_TASK_TYPE,				// 任务类型													uint
//	EUSER_TASK_STEP,				// 步骤														uint
//	EUSER_TASK_STATUS,				// 任务状态(0:未接受,1:接受, 2:提交, 3:达到完成条件但未提交)uint
//	EUSER_TASK_COUNT1,				// 计数1													uint
//	EUSER_TASK_COUNT2,				// 计数2													uint
//	EUSER_TASK_COUNT3,				// 计数3													uint
//	EUSER_TASK_BEGIN_TIME,			// 开始时间(单位秒)											uint
//	EUSER_TASK_OVER_TIME,			// 过期时间(0:无限制, >0:过期时间单位秒)					uint
//};
//
//static const char* GAME_DB_NAME_USER_NEWCARD = "user_newcard";		// 角色新手卡使用信息表
//enum USER_NEWCARD_DATA
//{
//	USER_NEWCARD_DATA_USERID = 0,	// 玩家id		uint
//	USER_NEWCARD_DATA_LASTUSETIME,	// 上次使用时间	uint
//	// 以下字段为20个掩码使用数据	bigint
//	USER_NEWCARD_DATA_MASKDATA1,
//	USER_NEWCARD_DATA_MASKDATA2,
//	USER_NEWCARD_DATA_MASKDATA3,
//	USER_NEWCARD_DATA_MASKDATA4,
//	USER_NEWCARD_DATA_MASKDATA5,
//	USER_NEWCARD_DATA_MASKDATA6,
//	USER_NEWCARD_DATA_MASKDATA7,
//	USER_NEWCARD_DATA_MASKDATA8,
//	USER_NEWCARD_DATA_MASKDATA9,
//	USER_NEWCARD_DATA_MASKDATA10,
//	USER_NEWCARD_DATA_MASKDATA11,
//	USER_NEWCARD_DATA_MASKDATA12,
//	USER_NEWCARD_DATA_MASKDATA13,
//	USER_NEWCARD_DATA_MASKDATA14,
//	USER_NEWCARD_DATA_MASKDATA15,
//	USER_NEWCARD_DATA_MASKDATA16,
//	USER_NEWCARD_DATA_MASKDATA17,
//	USER_NEWCARD_DATA_MASKDATA18,
//	USER_NEWCARD_DATA_MASKDATA19,
//	USER_NEWCARD_DATA_MASKDATA20,
//};
//
//static const char* GAME_DB_NAME_USER_MAIL	= "mail";	// 玩家邮件表
//enum EUSER_MAIL
//{
//	EUSER_MAIL_ID		= 0,	// 编号									bigint
//	EUSER_MAIL_USER_ID,			// 玩家ID								uint
//	EUSER_MAIL_STATUS,			// 邮件状态(0:未读, 1:已读, 2:删除)		uint
//	EUSER_MAIL_TITLE,			// 主题									varchar32
//	EUSER_MAIL_SENDER,			// 发件人								varchar32
//	EUSER_MAIL_CONTENT,			// 内容									varchar256
//	EUSER_MAIL_SEND_TIME,		// 发送日期								uint
//	EUSER_MAIL_OVER_TIME,		// 过期时间(必须有时间限制)				uint
//
//	EUSER_MAIL_ITEM_TYPE1,		// 物品类型1							uint
//	EUSER_MAIL_ITEM_NUM1,		// 物品数量1							uint
//	EUSER_MAIL_ITEM_TYPE2,		// 物品类型2							uint
//	EUSER_MAIL_ITEM_NUM2,		// 物品数量2							uint
//	EUSER_MAIL_ITEM_TYPE3,		// 物品类型3							uint
//	EUSER_MAIL_ITEM_NUM3,		// 物品数量3							uint
//	EUSER_MAIL_ITEM_TYPE4,		// 物品类型4							uint
//	EUSER_MAIL_ITEM_NUM4,		// 物品数量4							uint
//	EUSER_MAIL_ITEM_TYPE5,		// 物品类型5							uint
//	EUSER_MAIL_ITEM_NUM5,		// 物品数量5							uint
//	EUSER_MAIL_ITEM_TYPE6,		// 物品类型6							uint
//	EUSER_MAIL_ITEM_NUM6,		// 物品数量6							uint
//
//	EUSER_MAIL_MONEY_TYPE1,		// 货币1								uint
//	EUSER_MAIL_MONEY_NUM1,		// 货币1数量							uint
//	EUSER_MAIL_MONEY_TYPE2,		// 货币2								uint
//	EUSER_MAIL_MONEY_NUM2,		// 货币2数量							uint
//	EUSER_MAIL_MONEY_TYPE3,		// 货币3								uint
//	EUSER_MAIL_MONEY_NUM3,		// 货币3数量							uint
//	EUSER_MAIL_MONEY_TYPE4,		// 货币4								uint
//	EUSER_MAIL_MONEY_NUM4,		// 货币4数量							uint
//	EUSER_MAIL_EXP,				// 经验									uint
//	EUSER_MAIL_SERVER_GROUP,	// 服务器组								uint
//};
//
//
//static const char* GAME_DB_NAME_POKER = "poker";	// 卡牌表
//enum POKER_DATA
//{
//	POKER_DATA_ID = 0,			// id				bigint
//	POKER_DATA_TYPE,			// 类型				uint
//	POKER_DATA_OWNER_ID,		// 拥有者id			uint
//	POKER_DATA_LEV,				// 等级				uint
//	POKER_DATA_EXP,				// 经验				bigint
//	POKER_DATA_COLOR,			// 颜色				uint
//	POKER_DATA_STAR,			// 星级				uint
//	POKER_DATA_EQUIP1_TYPE,		// 武器类型			uint
//	POKER_DATA_EQUIP1_STAR,		// 武器星级			uint
//	POKER_DATA_EQUIP1_EXP,		// 武器经验			uint
//	POKER_DATA_EQUIP2_TYPE,		// 头盔类型			uint
//	POKER_DATA_EQUIP2_STAR,		// 头盔星级			uint
//	POKER_DATA_EQUIP2_EXP,		// 头盔经验			uint
//	POKER_DATA_EQUIP3_TYPE,		// 项链类型			uint
//	POKER_DATA_EQUIP3_STAR,		// 项链星级			uint
//	POKER_DATA_EQUIP3_EXP,		// 项链经验			uint
//	POKER_DATA_EQUIP4_TYPE,		// 腰带类型			uint
//	POKER_DATA_EQUIP4_STAR,		// 腰带星级			uint
//	POKER_DATA_EQUIP4_EXP,		// 腰带经验			uint
//	POKER_DATA_EQUIP5_TYPE,		// 衣服类型			uint
//	POKER_DATA_EQUIP5_STAR,		// 衣服星级			uint
//	POKER_DATA_EQUIP5_EXP,		// 衣服经验			uint
//	POKER_DATA_EQUIP6_TYPE,		// 鞋子类型			uint
//	POKER_DATA_EQUIP6_STAR,		// 鞋子星级			uint
//	POKER_DATA_EQUIP6_EXP,		// 鞋子经验			uint
//	POKER_DATA_SKILL_SP_LEV,	// 特技等级			uint
//	POKER_DATA_SKILL_AUTO1_LEV,	// 自动技能1等级	uint
//	POKER_DATA_SKILL_AUTO2_LEV,	// 自动技能2等级	uint
//	POKER_DATA_SKILL_AUTO3_LEV,	// 自动技能3等级	uint
//	POKER_DATA_SKILL_JOINT_LEV,	// 连携技能等级		uint
//	POKER_DATA_STATE,			// 卡牌状态（0空闲，1守营，2挖矿）	uint
//};
//
//static const char* GAME_DB_NAME_POKER_LOG = "poker_log";	// 物品流向表
//enum POKER_LOG_DATA
//{
//	POKER_LOG_DATA_ID = 0,		// 自增长id					bigint
//	POKER_LOG_DATA_OWNERID,		// 主人id					uint
//	POKER_LOG_DATA_TARGETID,	// 操作对象id				uint
//	POKER_LOG_DATA_POKER_ID,	// 卡牌id					bigint
//	POKER_LOG_DATA_POKER_TYPE,	// 卡牌type					uint
//	POKER_LOG_DATA_POKER_COUNT,	// 卡牌数量					uint
//	POKER_LOG_DATA_TYPE,		// 物品流向					uint
//	POKER_LOG_DATA_CREATETIME,	// 创建时间(utc时间）		uint
//	POKER_LOG_DATA_SERVERID,	// 服务器组					uint
//	POKER_LOG_DATA_LINE,		// 线路						uint
//	POKER_LOG_DATA_COMMENT,		// 说明字段					varchar128
//};
//
//static const char* GAME_DB_NAME_BLACK_LIST = "black_list";	// 黑名单
//enum BLACK_LIST
//{
//	BLACK_LIST_BEG		= 0,
//	BLACK_LIST_ID       = 0,		// 自增长ID			uint
//	BLACK_LIST_USER_ID,				// 玩家ID			uint
//	BLACK_LIST_BAD_FRIEND_ID,		// 被拉黑玩家ID		uint
//	BLACK_LIST_END,
//};
//
//static const char* GAME_DB_NAME_SYNDICATE = "syndicate";	// 帮派表
//enum SYNDICATE_DATA
//{
//	SYNDICATE_DATA_ID = 0,				// id					uint
//	SYNDICATE_DATA_SERVER_GROUP,		// 服务器组				uint
//	SYNDICATE_DATA_NAME,				// 帮派名				varchar32
//	SYNDICATE_DATA_ANNOUNCE,			// 公告					varchar255
//	SYNDICATE_DATA_LEADER_ID,			// 帮主id				uint
//	SYNDICATE_DATA_LEADER_NAME,			// 帮主名				varchar32
//	SYNDICATE_DATA_CREATOR_ID,			// 创建者id				uint
//	SYNDICATE_DATA_CREATOR_NAME,		// 创建者名				varchar32
//	SYNDICATE_DATA_CREATE_TIME,			// 创建时间				uint
//	SYNDICATE_DATA_LEVEL,				// 等级					uint
//	SYNDICATE_DATA_ACTIVITY,			// 活跃					bigint
//	SYNDICATE_DATA_ACTIVITY0_VAULE,		// 活跃度值-统计值0		bigint
//	SYNDICATE_DATA_ACTIVITY0_DATE,		// 活跃度日期-统计值0	uint
//	SYNDICATE_DATA_ACTIVITY1_VAULE,		// 活跃度值-统计值1		bigint
//	SYNDICATE_DATA_ACTIVITY1_DATE,		// 活跃度日期-统计值1	uint
//	SYNDICATE_DATA_ACTIVITY2_VAULE,		// 活跃度值-统计值2		bigint
//	SYNDICATE_DATA_ACTIVITY2_DATE,		// 活跃度日期-统计值2	uint
//	SYNDICATE_DATA_JOIN_LEV_LIMIT,		// 加入等级限制			uint
//	SYNDICATE_DATA_JOIN_APPLY,			// 加入申请标记			uint
//	SYNDICATE_DATA_ICON,				// 公会图标				uint
//	SYNDICATE_DATA_JUMP_THE_QUEUE,		// 插队标记				uint
//	SYNDICATE_DATA_AWARD_SEND_TIME,		// 战利品分配时间		uint
//	SYNDICATE_DATA_GIFTBOX_LEV,			// 礼盒等级				uint
//	SYNDICATE_DATA_GIFTBOX_EXP,			// 礼盒经验				uint
//	SYNDICATE_DATA_MONTHCARD_ID,		// 帮派月卡ID			uint
//	SYNDICATE_DATA_MONTHCARD_ENDTIME,	// 帮派月卡结束时间		uint
//};
//
//static const char* GAME_DB_NAME_SYNDICATE_MEMBER = "syn_member";	// 帮派成员表
//enum SYNDICATE_MEMBER_DATA
//{
//	SYNDICATE_MEMBER_DATA_USER_ID = 0,			// 玩家id				uint
//	SYNDICATE_MEMBER_DATA_SYNDICATE_ID,			// 帮派id				uint
//	SYNDICATE_MEMBER_DATA_SERVER_GROUP,			// 服务器组				uint
//	SYNDICATE_MEMBER_DATA_RANK,					// 帮派职位				uint
//	SYNDICATE_MEMBER_DATA_JOIN_TIME,			// 加入时间				uint
//	SYNDICATE_MEMBER_DATA_ACTIVITY,				// 活跃					bigint
//	SYNDICATE_MEMBER_DATA_ACTIVITY0_VALUE,		// 活跃度值-统计值0		bigint
//	SYNDICATE_MEMBER_DATA_ACTIVITY0_DATE,		// 活跃度日期-统计值0	uint
//	SYNDICATE_MEMBER_DATA_ACTIVITY1_VALUE,		// 活跃度值-统计值1		bigint
//	SYNDICATE_MEMBER_DATA_ACTIVITY1_DATE,		// 活跃度日期-统计值1	uint
//	SYNDICATE_MEMBER_DATA_ACTIVITY2_VALUE,		// 活跃度值-统计值2		bigint
//	SYNDICATE_MEMBER_DATA_ACTIVITY2_DATE,		// 活跃度日期-统计值2	uint
//	SYNDICATE_MEMBER_DATA_PROF,					// 帮贡					uint
//	SYNDICATE_MEMBER_DATA_LEV,					// 人物等级				uint
//	SYNDICATE_MEMBER_DATA_LOOKFACE,				// 头像					uint
//	SYNDICATE_MEMBER_DATA_LOOKFACEFRAME,		// 头像框				uint
//	SYNDICATE_MEMBER_DATA_NAME,					// 名字					varchar32
//	SYNDICATE_MEMBER_DATA_LOGOUT_TIME,			// 登出时间				uint
//	SYNDICATE_MEMBER_DATA_TERRITORY_MONEY,		// 累积的领地币			uint
//	SYNDICATE_MEMBER_DATA_WARROAD_TEAM0_COUNT,	// 团队战役挑战次数0	uint
//	SYNDICATE_MEMBER_DATA_WARROAD_TEAM1_COUNT,	// 团队战役挑战次数1	uint
//	SYNDICATE_MEMBER_DATA_WARROAD_TEAM2_COUNT,	// 团队战役挑战次数2	uint
//	SYNDICATE_MEMBER_DATA_END,
//};
//
//static const char* GAME_DB_NAME_SYNDICATE_MEMBER_APPLY = "syn_member_apply";	// 帮派成员申请表
//enum SYNDICATE_MEMBER_APPLY_DATA
//{
//	SYNDICATE_MEMBER_APPLY_DATA_ID	= 0,		// 主键自增		bigint
//	SYNDICATE_MEMBER_APPLY_DATA_USERID,			// 玩家id		uint
//	SYNDICATE_MEMBER_APPLY_DATA_SYNID,			// 帮派id		uint
//	SYNDICATE_MEMBER_APPLY_DATA_SERVER_GROUP,	// 服务器组		uint
//	SYNDICATE_MEMBER_APPLY_DATA_LEV,			// 角色等级		uint
//	SYNDICATE_MEMBER_APPLY_DATA_LOOKFACE,		// 角色头像		uint
//	SYNDICATE_MEMBER_APPLY_DATA_LOOKFACEFRAME,	// 角色头像框	uint
//	SYNDICATE_MEMBER_APPLY_DATA_NAME,			// 角色名字		varchar32
//	SYNDICATE_MEMBER_APPLY_DATA_TIME,			// 申请时间		uint
//};
//
//static const char* GAME_DB_NAME_FRIEND = "friend";
//enum FRIEND
//{
//	FRIEND_DATA_USER_ID = 0,					// 玩家id		uint
//	FRIEND_DATA_FRIEND_ID,						// 好友id		uint
//	FRIEND_DATA_FRIENDSHIP_POINT,				// 友好度		uint
//	FRIEND_DATA_GIFT,							// 礼物状态		uint
//	FRIEND_DATA_LAST_GOTTIME,					// 上次领取时间	uint
//};
//
//static const char* GAME_DB_NAME_FRIEND_REQUEST = "friend_request";
//enum FRIEND_REQUEST
//{
//	FRIEND_REQUEST_DATA_USER_ID = 0,			// 玩家id	uint
//	FRIEND_REQUEST_DATA_REQUESTER_ID,			// 请求者id uint
//	FRIEND_REQUEST_DATA_REQUEST_TIME,			// 请求时间 uint
//};
//
//static const char* GAME_DB_NAME_ITEM = "item";	// 物品表
//enum ITEM_DATA
//{
//	ITEM_DATA_ID	= 0,		// 物品id		bigint
//	ITEM_DATA_TYPE,				// 物品类型		uint
//	ITEM_DATA_PLAYER_ID,		// 归属者id		uint
//	ITEM_DATA_AMOUNT,			// 数量			uint
//	ITEM_DATA_LIFE_TIME,		// 存在时间		uint
//	ITEM_DATA_END,
//};
//
//static const char* GAME_DB_NAME_SHOP_GOODS = "shop_goods"; // 商店货物表
//enum SHOP_GOODS
//{
//	SHOP_GOODS_BEGIN= 0,
//	SHOP_GOODS_ID	= 0,		// 自增长ID		uint
//	SHOP_GOODS_ITEM_TYPE,		// 物品类型		uint
//	SHOP_GOODS_OWNER_ID,		// 归属玩家ID	uint
//	SHOP_GOODS_SHOP_TYPE,		// 归属商店		uint
//	SHOP_GOODS_ITEM_INDEX,		// 物品位置		uint
//	SHOP_GOODS_CUR_NUM,			// 当前剩余数量 uint
//	SHOP_GOODS_MONEY_TYPE,		// 货币类型		uint
//	SHOP_GOODS_PRICE,			// 物品单价		uint
//	SHOP_GOODS_NUM,				// 物品数量		uint
//	SHOP_GOODS_DISCOUNT,		// 物品折扣		uint
//	SHOP_GOODS_END,
//};
//
//
//static const char* GAME_DB_NAME_USER_ACHIEVEMENT = "user_achievement";	// 玩家成就
//enum USER_ACHIEVEMENT
//{
//	USER_ACHIEVEMENT_USERID = 0,				// 玩家id			uint
//	USER_ACHIEVEMENT_CHIEVEMENTID,				// 正在进行的成就id	uint
//	USER_ACHIEVEMENT_PROCESS,					// 进度				uint
//	USER_ACHIEVEMENT_GOAL,						// 目标				int
//};
//
//static const char* GAME_DB_NAME_BATTLE_SAVE = "battle_save";	// 战斗存档
//enum BATTLE_SAVE_DATA
//{
//	BATTLE_SAVE_DATA_ID = 0,			// 战斗id		bigint
//	BATTLE_SAVE_DATA_TYPE,				// 战斗类型		uint
//	BATTLE_SAVE_DATA_ROUND,				// 轮次			uint
//	BATTLE_SAVE_DATA_MONSTER1_HP,		// 怪物1血量	uint
//	BATTLE_SAVE_DATA_MONSTER1_SP,		// 怪物1愤怒	uint
//	BATTLE_SAVE_DATA_MONSTER2_HP,		// 怪物2血量	uint
//	BATTLE_SAVE_DATA_MONSTER2_SP,		// 怪物2愤怒	uint
//	BATTLE_SAVE_DATA_MONSTER3_HP,		// 怪物3血量	uint
//	BATTLE_SAVE_DATA_MONSTER3_SP,		// 怪物3愤怒	uint
//	BATTLE_SAVE_DATA_MONSTER4_HP,		// 怪物4血量	uint
//	BATTLE_SAVE_DATA_MONSTER4_SP,		// 怪物4愤怒	uint
//	BATTLE_SAVE_DATA_MONSTER5_HP,		// 怪物5血量	uint
//	BATTLE_SAVE_DATA_MONSTER5_SP,		// 怪物5愤怒	uint
//};
//
//static const char* GAME_DB_NAME_CHALLENGE_BOSS = "challenge_boss";	// 挑战boss结果表
//enum CHALLENGE_BOSS
//{
//	CHALLENGE_BOSS_ID = 0,				// 编号						bigint
//	CHALLENGE_BOSS_USER_ID,				// 玩家ID					uint
//	CHALLENGE_BOSS_BOSS_TYPE,			// boss类型					uint
//	CHALLENGE_BOSS_DEGREE,				// 难度						uint
//	CHALLENGE_BOSS_EVALUATE,			// 挑战结果(0:失败; 1,2,3星)uint
//};
//
//static const char* GAME_DB_NAME_TOPLIST_USER_ATTR = "toplist_user_attr";	//	排名榜玩家排名表
//enum TOPLIST_USER_ATTR
//{
//	TOPLIST_USER_ATTR_USER_ID = 0,		// 玩家id			uint
//	TOPLIST_USER_ATTR_TYPE,				// 排行榜类型枚举值	uint
//	TOPLIST_USER_ATTR_DATA,				// 排行使用的数据	uint
//	TOPLIST_USER_ATTR_RANK,				// 本期排名			uint	
//	TOPLIST_USER_ATTR_LAST_RANK,		// 上期排名			uint
//	TOPLIST_USER_ATTR_SERVER_GROUP,		// 服务器组id		uint
//};
//
//static const char* GAME_DB_NAME_TOPLIST_SYNDICATE = "toplist_syndicate";	// 排行榜公会排名表
//enum TOPLIST_SYNDICATE
//{
//	TOPLIST_SYNDICATE_ID = 0,			// 公会id			uint
//	TOPLIST_SYNDICATE_TYPE,				// 排行榜类型枚举值	uint
//	TOPLIST_SYNDICATE_DATA,				// 排行使用的数据	uint
//	TOPLIST_SYNDICATE_SERVER_GROUP,		// 服务器组id		uint
//};
//
//static const char* GAME_DB_NAME_DELAYACTION = "delayaction";	// 延迟执行action记录表
//enum DELAYACTION_DATA
//{
//	DELAYACTION_DATA_ID = 0,			// 编号						bigint
//	DELAYACTION_DATA_ACTION_ID,			// 执行action				uint
//	DELAYACTION_DATA_USER_ID,			// 玩家ID					uint
//	DELAYACTION_DATA_EXECUTECOUNT,		// 执行次数					uint
//	DELAYACTION_DATA_EXECUTETIME,		// 执行时间					uint
//	DELAYACTION_DATA_INVALIDTIME,		// 失效时间					uint
//	DELAYACTION_DATA_SERVER_GROUP,		// 服务器组					uint
//	DELAYACTION_DATA_SERVER_LINE,		// 服务器线路				uint
//	DELAYACTION_DATA_PARAM1,			// 参数1					uint
//	DELAYACTION_DATA_PARAM2,			// 参数2					uint
//	DELAYACTION_DATA_PARAM3,			// 参数3					uint
//	DELAYACTION_DATA_PARAM4,			// 参数4					uint
//	DELAYACTION_DATA_PARAM5,			// 参数5					uint
//};
//
//
//static const char* GAME_DB_NAME_GOOSE_TOWER = "goose_tower";	// 大雁塔玩家数据表
//enum GOOSE_TOWER_DATA
//{
//	GOOSE_TOWER_DATA_ID = 0,					// id								bigint
//	GOOSE_TOWER_DATA_USER_ID,					// 玩家id							uint
//	GOOSE_TOWER_DATA_FLOOR,						// 层数								uint
//	GOOSE_TOWER_DATA_DEF_USER_ID,				// 防守小队玩家id					uint
//	GOOSE_TOWER_DATA_DEF_USER_NAME,				// 防守小队玩家名					varchar32
//	GOOSE_TOWER_DATA_DEF_USER_LEV,				// 防守小队玩家等级					uint
//	GOOSE_TOWER_DATA_DEF_USER_LOOKFACE,			// 防守小队玩家头像					uint
//	GOOSE_TOWER_DATA_DEF_USER_LOOKFACE_FRAME,	// 防守小队玩家头像框				uint
//	GOOSE_TOWER_DATA_POKER_ID1,					// 卡牌ID1							bigint
//	GOOSE_TOWER_DATA_POKER_ID2,					// 卡牌ID2							bigint
//	GOOSE_TOWER_DATA_POKER_ID3,					// 卡牌ID3							bigint
//	GOOSE_TOWER_DATA_POKER_ID4,					// 卡牌ID4							bigint
//	GOOSE_TOWER_DATA_POKER_ID5,					// 卡牌ID5							bigint
//	GOOSE_TOWER_DATA_GAIN_AWARD,				// 宝箱领取标记(0:没有领取, 1:领取)	uint
//	GOOSE_TOWER_DATA_BATTLE_SAVE_ID,			// 战斗保存ID						bigint
//};
//
//static const char* GAME_DB_NAME_GOOSE_FIGHT_POKER = "goose_fight_poker";	// 大雁塔历史上阵卡牌记录表
//enum GOOSE_FIGHT_POKER
//{
//	GOOSE_FIGHT_POKER_ID = 0,			// id			uint
//	GOOSE_FIGHT_POKER_USER_ID,			// 玩家id		uint
//	GOOSE_FIGHT_POKER_POKER_ID,			// 阵亡卡牌ID	bigint
//	GOOSE_FIGHT_POKER_HP,				// 最大血量		uint
//	GOOSE_FIGHT_POKER_LEFT_HP,			// 剩余血量		uint
//	GOOSE_FIGHT_POKER_SP,				// 最大愤怒		uint
//	GOOSE_FIGHT_POKER_LEFT_SP,			// 剩余愤怒		uint
//};
//
//// 与poker表用同一个枚举
//static const char* GAME_DB_NAME_GOOSE_DEFENSE_POKER = "goose_defense_poker";		// 大雁塔防守小队卡牌表
//
//
//static const char* GAME_DB_NAME_PUZZLE_BUFF = "puzzle_buff";	// 迷宫BUFF表
//enum PUZZLE_BUFF_DATA
//{
//	PUZZLE_BUFF_DATA_ID = 0,			// 编号						uint
//	PUZZLE_BUFF_DATA_USER_ID,			// 玩家ID					uint
//	PUZZLE_BUFF_DATA_BUFF_TYPE,			// BUFF类型					uint
//	PUZZLE_BUFF_DATA_INS_TYPE,			// 副本类型					uint
//	PUZZLE_BUFF_DATA_INS_DIFFICULE,		// 副本难度					uint
//	PUZZLE_BUFF_DATA_INS_FLOOR,			// 副本层次					uint
//	PUZZLE_BUFF_DATA_FIGHT_NO,			// 战斗序列号				uint
//	PUZZLE_BUFF_DATA_DATE,				// 产生日期(天)				uint
//};
//static const char* GAME_DB_NAME_ARENA = "arena";			// 单队竞技场排名表
//enum ARENA_DATA
//{
//	ARENA_DATA_USERID,					// 玩家id					uint
//	ARENA_DATA_RANK = 0,				// 排名						uint
//	ARENA_DATA_TOTALWINCOUNT,			// 总计胜场数				uint
//	ARENA_SERVER_GROUP,					// 服务器组					uint
//};
//
//static const char* GAME_DB_NAME_ARENA_LOG = "arena_log";			// 竞技场战斗日志
//enum ARENA_LOG_DATA
//{
//	ARENA_LOG_DATA_ARENA_TYPE = 0,		// 竞技场类别（1单人，2多人）	uint
//	ARENA_LOG_DATA_USERID,				// 玩家id						uint
//	ARENA_LOG_DATA_RESULT,				// 战斗结果						uint
//	ARENA_LOG_DATA_RANKCHANGE,			// 排名变化						uint
//	ARENA_LOG_DATA_TARGETID,			// 目标id						uint
//	ARENA_LOG_DATA_TIME,				// 战斗时间						uint
//	ARENA_LOG_DATA_VIDEO,				// 录像							varchar
//	ARENA_LOG_DATA_SERVER_GROUP,		// 服务器组						uint
//};
//
//static const char* GAME_DB_NAME_ARENA_MULTI = "arena_multi";		//  多队竞技场数据
//enum MULTI_ARENA_DATA
//{
//	MULTI_ARENA_DATA_USERID = 0,		// 玩家id						uint
//	MULTI_ARENA_DATA_RANK,				// 排名							uint
//	MULTI_ARENA_DATA_TOTALWINCOUNT,		// 总计胜场数					uint
//	MULTI_ARENA_DATA_ARENA_MONEY,		// 累积未领取的竞技场币			uint	
//	MULTI_ARENA_DATA_SERVER_GROUP,		// 服务器组						uint
//};
//
//static const char* GAME_DB_NAME_ARENA_POKER_TEAM = "arena_poker_team";	// 竞技场玩家卡牌队伍数据
//enum ARENA_POKER_TEAM_DATA
//{
//	ARENA_POKER_TEAM_DATA_ID = 0,		// 自增长id						uint
//	ARENA_POKER_TEAM_DATA_USERID ,		// 玩家id						uint
//	ARENA_POKER_TEAM_DATA_TEAMTYPE,		// 队伍类型						uint
//	ARENA_POKER_TEAM_DATA_POKERID1,		// 1号卡牌id					uint
//	ARENA_POKER_TEAM_DATA_POKERID2,		// 2号卡牌id					uint
//	ARENA_POKER_TEAM_DATA_POKERID3,		// 3号卡牌id					uint
//	ARENA_POKER_TEAM_DATA_POKERID4,		// 4号卡牌id					uint
//	ARENA_POKER_TEAM_DATA_POKERID5,		// 5号卡牌id					uint
//	ARENA_POKER_TEAM_DATA_TOTAL_FC,		// 队伍总战斗力					uint
//	ARENA_POKER_TEAM_DATA_END,
//};
//
//static const char* GAME_DB_NAME_ARENA_AI = "arena_ai";	// 竞技场机器人表
//enum ARENA_AI_DATA
//{
//	ARENA_AI_DATA_ID = 0,				// id		uint
//	ARENA_AI_DATA_NAME,					// 名字		varchar
//	ARENA_AI_DATA_SERVER_GROUP,			// 服务器组	uint
//};
//
//static const char* GAME_DB_NAME_SYN_LOG	= "syn_log";	// 帮派日志表
//enum SYN_LOG_DATA
//{
//	SYN_LOG_DATA_ID = 0,			// ID				bigint
//	SYN_LOG_DATA_SYN_ID,			// 帮派ID   		uint
//	SYN_LOG_DATA_TYPE,				// 日志类型 		uint
//	SYN_LOG_DATA_CREATE_USER_ID,	// 日志产生者ID		uint
//	SYN_LOG_DATA_CREATE_TIME,		// 日志产生时间		uint
//	SYN_LOG_DATA_CONTENT,			// 日志内容			varchar256
//};
//
//static const char* GAME_DB_NAME_MINE	= "mine";	// 矿洞表
//enum MINE_DATA
//{
//	MINE_DATA_ID	= 0,				// 矿洞ID						uint
//	MINE_DATA_OWNER_ID,					// 矿主ID						uint
//	MINE_DATA_TYPE,						// 矿类型						uint
//	MINE_DATA_SCALE,					// 矿规模						uint
//	MINE_DATA_CREATE_TIME,				// 创建时间						uint
//	MINE_DATA_IS_END,					// 是否结束						uint
//	MINE_DATA_BE_ATK_COUNT,				// 被攻击次数					uint
//	MINE_DATA_SERVER_GROUP,				// 服务器组						uint
//};
//
//static const char* GAME_DB_NAME_MINE_MEMBER = "mine_member"; // 矿洞成员表
//enum MINE_MEMBER_DATA
//{
//	MINE_MEMBER_DATA_ID		= 0,		// 自增长ID						bigint
//	MINE_MEMBER_DATA_USER_ID,			// 玩家ID						uint
//	MINE_MEMBER_DATA_MINE_ID,			// 矿洞ID						uint
//	MINE_MEMBER_DATA_LEV,				// 等级							uint
//	MINE_MEMBER_DATA_LOOK_FACE,			// 头像							uint
//	MINE_MEMBER_DATA_LOOK_FACE_FRAME,	// 头像框						uint
//	MINE_MEMBER_DATA_NAME,				// 角色名						varchar32
//	MINE_MEMBER_DATA_POKER1,			// 出战卡1						bigint
//	MINE_MEMBER_DATA_POKER2,			// 出战卡2						bigint
//	MINE_MEMBER_DATA_POKER3,			// 出战卡3						bigint
//	MINE_MEMBER_DATA_POKER4,			// 出战卡4						bigint
//	MINE_MEMBER_DATA_POKER5,			// 出战卡5						bigint
//	MINE_MEMBER_DATA_JOIN_TIME,			// 加入时间						uint
//	MINE_MEMBER_DATA_SPEED,				// 当前开采速度(/小时)			uint
//	MINE_MEMBER_DATA_BEGIN_TIME,		// 当前卡牌开始采集时间			uint
//	MINE_MEMBER_DATA_RESOURCE_OLD,		// 换卡牌前累计资源				uint
//	MINE_MEMBER_DATA_RESOURCE_TOTAL,	// 资源累计						uint
//	MINE_MEMBER_DATA_RESOURCE_LOSE,		// 资源丢失						uint
//	MINE_MEMBER_DATA_VAS_TOTAL,			// 钻石累计						uint
//	MINE_MEMBER_DATA_IS_POKER_RESET,	// 卡牌是否重置					uint
//	MINE_MEMBER_DATA_SERVER_GROUP,		// 服务器组						uint
//};
//static const char* GAME_DB_NAME_MERCENARY_POKER = "mercenary_poker";	// 佣兵卡牌表 *新增一个字段外其余与poker表枚举相同
//enum MERCENARY_POKER_DATA
//{
//	MERCENARY_POKER_DATA_SERVER_GROUP = POKER_DATA_SKILL_JOINT_LEV + 1,	// 服务器组					uint
//};
//
//static const char* GAME_DB_NAME_MERCENARY_CAMP = "mercenary_camp";		// 佣兵营表
//enum MERCENARY_CAMP_DATA
//{
//	MERCENARY_CAMP_DATA_MERCENARY_ID,	// 佣兵ID					bigint
//	MERCENARY_CAMP_DATA_OWNER_ID,		// 佣兵主人ID				uint
//	MERCENARY_CAMP_DATA_EMPLOY_COUNT,	// 被雇佣次数				uint
//	MERCENARY_CAMP_DATA_ENTER_TIME,		// 派遣时间					uint
//	MERCENARY_CAMP_DATA_SYNDICATE_ID,	// 帮派ID					uint
//	MERCENARY_CAMP_DATA_SERVER_GROUP,	// 服务器组					uint
//	MERCENARY_CAMP_DATA_MERCENARY_SCORE,// 佣兵战斗力				uint
//};
//
//static const char* GAME_DB_NAME_MERCENARY_FIGHT = "mercenary_fight";	// 佣兵战斗记录表
//enum MERCENARY_FIGHT_DATA
//{
//	MERCENARY_FIGHT_DATA_ID,						// ID					bigint
//	MERCENARY_FIGHT_DATA_USER_ID,					// 玩家ID				uint
//	MERCENARY_FIGHT_DATA_MERCENARY_ID,				// 佣兵ID				bigint
//	MERCENARY_FIGHT_DATA_MERCENARY_TYPE,			// 佣兵类型				uint
//	MERCENARY_FIGHT_DATA_MERCENARY_OWNER_ID,		// 佣兵主人id			uint
//	MERCENARY_FIGHT_DATA_MERCENARY_LEV,				// 佣兵等级				uint
//	MERCENARY_FIGHT_DATA_MERCENARY_EXP,				// 佣兵经验				bigint
//	MERCENARY_FIGHT_DATA_MERCENARY_COLOR,			// 佣兵颜色				uint
//	MERCENARY_FIGHT_DATA_MERCENARY_STAR,			// 佣兵星级				uint
//	MERCENARY_FIGHT_DATA_MERCENARY_EQUIP1_TYPE,		// 佣兵武器类型			uint
//	MERCENARY_FIGHT_DATA_MERCENARY_EQUIP1_STAR,		// 佣兵武器星级			uint
//	MERCENARY_FIGHT_DATA_MERCENARY_EQUIP1_EXP,		// 佣兵武器经验			uint
//	MERCENARY_FIGHT_DATA_MERCENARY_EQUIP2_TYPE,		// 佣兵头盔类型			uint
//	MERCENARY_FIGHT_DATA_MERCENARY_EQUIP2_STAR,		// 佣兵头盔星级			uint
//	MERCENARY_FIGHT_DATA_MERCENARY_EQUIP2_EXP,		// 佣兵头盔经验			uint
//	MERCENARY_FIGHT_DATA_MERCENARY_EQUIP3_TYPE,		// 佣兵项链类型			uint
//	MERCENARY_FIGHT_DATA_MERCENARY_EQUIP3_STAR,		// 佣兵项链星级			uint
//	MERCENARY_FIGHT_DATA_MERCENARY_EQUIP3_EXP,		// 佣兵项链经验			uint
//	MERCENARY_FIGHT_DATA_MERCENARY_EQUIP4_TYPE,		// 佣兵腰带类型			uint
//	MERCENARY_FIGHT_DATA_MERCENARY_EQUIP4_STAR,		// 佣兵腰带星级			uint
//	MERCENARY_FIGHT_DATA_MERCENARY_EQUIP4_EXP,		// 佣兵腰带经验			uint
//	MERCENARY_FIGHT_DATA_MERCENARY_EQUIP5_TYPE,		// 佣兵衣服类型			uint
//	MERCENARY_FIGHT_DATA_MERCENARY_EQUIP5_STAR,		// 佣兵衣服星级			uint
//	MERCENARY_FIGHT_DATA_MERCENARY_EQUIP5_EXP,		// 佣兵衣服经验			uint
//	MERCENARY_FIGHT_DATA_MERCENARY_EQUIP6_TYPE,		// 佣兵鞋子类型			uint
//	MERCENARY_FIGHT_DATA_MERCENARY_EQUIP6_STAR,		// 佣兵鞋子星级			uint
//	MERCENARY_FIGHT_DATA_MERCENARY_EQUIP6_EXP,		// 佣兵鞋子经验			uint
//	MERCENARY_FIGHT_DATA_MERCENARY_SKILL_SP_LEV,	// 佣兵特技等级			uint
//	MERCENARY_FIGHT_DATA_MERCENARY_SKILL_AUTO1_LEV,	// 佣兵自动技能1等级	uint
//	MERCENARY_FIGHT_DATA_MERCENARY_SKILL_AUTO2_LEV,	// 佣兵自动技能2等级	uint
//	MERCENARY_FIGHT_DATA_MERCENARY_SKILL_AUTO3_LEV,	// 佣兵自动技能3等级	uint
//	MERCENARY_FIGHT_DATA_MERCENARY_SKILL_JOINT_LEV,	// 佣兵连携技能等级		uint
//	MERCENARY_FIGHT_DATA_MERCENARY_SCORE,			// 佣兵战力				uint
//	MERCENARY_FIGHT_DATA_EMPLOY_TYPE,				// 雇佣类型				uint
//	MERCENARY_FIGHT_DATA_EMPLOY_TIME,				// 雇佣时间				uint
//	MERCENARY_FIGHT_DATA_EMPLOY_STATE,				// 雇佣状态(1正在使用，2保存，3冷却)	uint
//};
//
//static const char* GAME_DB_NAME_MINE_LOG = "mine_log";					// 矿洞日志表
//enum MINE_LOG_DATA
//{
//	MINE_LOG_DATA_ID = 0,				// 自增长ID					uint
//	MINE_LOG_DATA_MINE_ID,				// 矿洞ID					uint
//	MINE_LOG_DATA_MINE_TYPE,			// 矿洞类型					uint
//	MINE_LOG_DATA_MINE_SCALE,			// 矿洞规模					uint
//	MINE_LOG_DATA_DEF_ID,				// 防守者ID					uint
//	MINE_LOG_DATA_DEF_NAME,				// 防守者名字				varchar32
//	MINE_LOG_DATA_DEF_LEV,				// 防守者等级				uint
//	MINE_LOG_DATA_DEF_LOOKFACE,			// 防守者头像				uint
//	MINE_LOG_DATA_DEF_LOOKFACE_FRAME,	// 防守者头像框				uint
//	MINE_LOG_DATA_ATK_ID,				// 攻击者ID					uint
//	MINE_LOG_DATA_ATK_NAME,				// 攻击者名字				varchar32
//	MINE_LOG_DATA_ATK_LEV,				// 攻击者等级				uint
//	MINE_LOG_DATA_ATK_LOOKFACE,			// 攻击者头像				uint
//	MINE_LOG_DATA_ATK_LOOKFACE_FRAME,	// 攻击者头像框				uint
//	MINE_LOG_DATA_BEGIN_TIME,			// 掠夺开始时间				uint
//	MINE_LOG_DATA_END_TIME,				// 掠夺结束时间				uint
//	MINE_LOG_DATA_VAS_LOST,				// 获取的钻石				uint
//	MINE_LOG_DATA_RES_LOST,				// 获取的资源				uint
//	MINE_LOG_DATA_POWER_AWARD,			// 专用体力奖励				uint
//	MINE_LOG_DATA_DEF_RESULT,			// 防守结果(0:失败；1:胜利)	uint
//	MINE_LOG_DATA_SERVER_GROUP,			// 服务器组					uint
//	MINE_LOG_DATA_BE_ATK_COUNT,			// 被攻击次数				uint
//};
//
//static const char* GAME_DB_NAME_MINE_LOG_BATTLE = "mine_log_battle";	// 矿洞日志战斗表
//enum MINE_LOG_BATTLE_DATA
//{
//	MINE_LOG_BATTLE_DATA_ID = 0,		// 战斗ID				bigint				
//	MINE_LOG_BATTLE_LOG_ID,				// 日志ID				bigint	
//	MINE_LOG_BATTLE_DEF_POKER1,			// 防守方卡牌1			bigint				
//	MINE_LOG_BATTLE_DEF_POKER2,			// 						bigint				
//	MINE_LOG_BATTLE_DEF_POKER3,			// 						bigint				
//	MINE_LOG_BATTLE_DEF_POKER4,			// 						bigint				
//	MINE_LOG_BATTLE_DEF_POKER5,			// 						bigint
//
//	MINE_LOG_BATTLE_DEF_RESULT,			// 防守结果(0:输, 1:赢)	uint
//
//	MINE_LOG_BATTLE_ATK_POKER1,			// 攻击方卡牌1			bigint				
//	MINE_LOG_BATTLE_ATK_POKER2,			// 						bigint				
//	MINE_LOG_BATTLE_ATK_POKER3,			// 						bigint				
//	MINE_LOG_BATTLE_ATK_POKER4,			// 						bigint				
//	MINE_LOG_BATTLE_ATK_POKER5,			// 						bigint
//	MINE_LOG_BATTLE_VIDEO_ID,			// 录像地址				varchar64				
//};
//
//static const char* GAME_DB_NAME_MINE_LOG_POKER = "mine_log_poker";	// 矿洞日志出战卡牌表
//enum MINE_LOG_POKER_DATA
//{
//	MINE_LOG_POKER_DATA_ID = 0,			// ID					bigint
//	MINE_LOG_POKER_DATA_BATTLE_ID,		// 战斗ID				bigint
//	MINE_LOG_POKER_DATA_TYPE,			// 类型					uint
//	MINE_LOG_POKER_DATA_LEV,			// 等级					uint
//	MINE_LOG_POKER_DATA_STAR,			// 星级					uint
//	MINE_LOG_POKER_DATA_COLOR,			// 颜色					uint
//	MINE_LOG_POKER_DATA_HP,				// 最大血量				uint
//	MINE_LOG_POKER_DATA_LEFT_HP,		// 剩余血量				uint
//	MINE_LOG_POKER_DATA_SP,				// 最大愤怒				uint
//	MINE_LOG_POKER_DATA_LEFT_SP,		// 剩余愤怒				uint
//};
//
//
//static const char* GAME_DB_NAME_TERRITORY = "territory";				// 领地表
//enum TERRITORY_DATA
//{
//	TERRITORY_DATA_INDEX = 0,			// primary				uint
//	TERRITORY_DATA_ID,					// 领地id				uint
//	TERRITORY_DATA_OCCUPIER,			// 占领公会id			uint
//	TERRITORY_DATA_OCCUPY_TIME,			// 占领时间YYMMDD		uint
//	TERRITORY_DATA_OCCUPY_COST,			// 占领耗时				uint
//	TERRITORY_DATA_FIRST_OCCUPIER,		// 首占公会id			uint
//	TERRITORY_DATA_FIRST_TIME,			// 首战时间YYMMDD		uint
//	TERRITORY_DATA_FIRST_COST,			// 首战耗时				uint
//	TERRITORY_DATA_FAST_OCCUPIER,		// 最快公会id			uint
//	TERRITORY_DATA_FAST_TIME,			// 最快公会时间YYMMDD	uint
//	TERRITORY_DATA_FAST_COST,			// 最快占领公会耗时		uint
//	TERRITORY_DATA_SERVER_GROUP,		// 服务器组				uint
//};
//
//static const char* GAME_DB_NAME_TERRITORY_MEMBER_TROOPS = "territory_member_troops";		// 领地公会玩家部队表
//enum TERRITORY_MEMBER_TROOPS_DATA
//{
//	TERRITORY_MEMBER_TROOPS_DATA_ID,				// 部队id				uint
//	TERRITORY_MEMBER_TROOPS_DATA_TERRITORY_ID,		// 领地id				uint
//	TERRITORY_MEMBER_TROOPS_DATA_CAMP,				// 阵营					uint
//	TERRITORY_MEMBER_TROOPS_DATA_SYNDICATE_ID,		// 所属公会id			uint
//	TERRITORY_MEMBER_TROOPS_DATA_USER_ID,			// 所属玩家id			uint
//	TERRITORY_MEMBER_TROOPS_DATA_POKER_COUNT,		// 当前部队实际卡牌数	uint
//	TERRITORY_MEMBER_TROOPS_DATA_FIGHTINGCAPACITY,	// 当前部队总战斗力		uint
//	TERRITORY_MEMBER_TROOPS_DATA_POKER1_ID,			// 队伍卡牌1id			uint
//	TERRITORY_MEMBER_TROOPS_DATA_POKER2_ID,			// 队伍卡牌2id			uint
//	TERRITORY_MEMBER_TROOPS_DATA_POKER3_ID,			// 队伍卡牌3id			uint
//	TERRITORY_MEMBER_TROOPS_DATA_POKER4_ID,			// 队伍卡牌4id			uint
//	TERRITORY_MEMBER_TROOPS_DATA_POKER5_ID,			// 队伍卡牌5id			uint
//	TERRITORY_MEMBER_TROOPS_DATA_SERVER_GROUP,		// 服务器组				uint
//};
//
//static const char* GAME_DB_NAME_TERRITORY_FIGHT_STATISTICS = "territory_fight_statistics";		// 领地战战斗统计表
//enum TERRITORY_FIGHT_STATISTICS
//{
//	TERRITORY_FIGHT_STATISTICS_DATA_INDEX = 0,			// INDEX				uint
//	TERRITORY_FIGHT_STATISTICS_DATA_ID,					// 领地id				uint
//	TERRITORY_FIGHT_STATISTICS_DATA_ATK_SYN_ID,			// 进攻公会id			uint
//	TERRITORY_FIGHT_STATISTICS_DATA_DEF_SYN_ID,			// 防守公会id			uint
//	TERRITORY_FIGHT_STATISTICS_DATA_TOTAL_FIGHTED_TIMES,// 总战斗时间			uint
//	TERRITORY_FIGHT_STATISTICS_DATA_SERVER_GROUP,		// 服务器组				uint
//};
//
//static const char* GAME_DB_NAME_TERRITORY_FIGHT_LOG		= "territory_fight_log";				// 领地战战斗日志表
//enum TERRITORY_FIGHT_LOG
//{
//	TERRITORY_FIGHT_LOG_DATA_INDEX = 0,					// INDEX							uint
//	TERRITORY_FIGHT_LOG_DATA_TERRITORY_ID,				// 领地id							uint
//	TERRITORY_FIGHT_LOG_DATA_ATK_TROOPS_ID,				// 进攻部队id						I64
//	TERRITORY_FIGHT_LOG_DATA_ATK_USER_ID,				// 进攻部队玩家id					uint
//	TERRITORY_FIGHT_LOG_DATA_ATK_SYN_ID,				// 进攻部队公会id					uint
//	TERRITORY_FIGHT_LOG_DATA_DEF_TROOPS_ID,				// 防守部队id						I64
//	TERRITORY_FIGHT_LOG_DATA_DEF_USER_ID,				// 防守部队玩家id					uint
//	TERRITORY_FIGHT_LOG_DATA_DEF_SYN_ID,				// 防守部队公会id					uint
//	TERRITORY_FIGHT_LOG_DATA_TIME,						// 相对领地战开始的时间（单位秒）	uint
//	TERRITORY_FIGHT_LOG_DATA_RESULT,					// 胜负（0防守胜利，1进攻胜利）		uint
//	TERRITORY_FIGHT_LOG_DATA_DATE,						// 战斗日期							uint
//	TERRITORY_FIGHT_LOG_DATA_VIDEO,						// 录像								varchar128
//	TERRITORY_FIGHT_LOG_DATA_SERVER_GROUP,				// 服务器组							uint
//};
//
//static const char* GAME_DB_NAME_TERRITORY_FIGHT_TROOPS = "territory_fight_troops";				// 领地战已参战部队状态表
//enum TERRITORY_FIGHT_TROOPS
//{
//	TERRITORY_FIGHT_TROOPS_DATA_INDEX = 0,				// INDEX							uint
//	TERRITORY_FIGHT_TROOPS_DATA_TERRITORY_ID,			// 领地id							uint
//	TERRITORY_FIGHT_TROOPS_DATA_TROOPS_ID,				// 部队id							I64
//	TERRITORY_FIGHT_TROOPS_DATA_SYN_ID,					// 部队所属公会id					uint
//	TERRITORY_FIGHT_TROOPS_DATA_OPPONENT_SYN_ID,		// 对手所属公会id					uint
//	TERRITORY_FIGHT_TROOPS_DATA_STATUS,					// 状态（0阵亡，1获胜）				uint
//	TERRITORY_FIGHT_TROOPS_DATA_POKER1_HP,				// 卡牌1当前血量					uint
//	TERRITORY_FIGHT_TROOPS_DATA_POKER1_SP,				// 卡牌1当前愤怒					uint
//	TERRITORY_FIGHT_TROOPS_DATA_POKER2_HP,				// 卡牌2当前血量					uint
//	TERRITORY_FIGHT_TROOPS_DATA_POKER2_SP,				// 卡牌2当前愤怒					uint
//	TERRITORY_FIGHT_TROOPS_DATA_POKER3_HP,				// 卡牌3当前血量					uint
//	TERRITORY_FIGHT_TROOPS_DATA_POKER3_SP,				// 卡牌3当前愤怒					uint
//	TERRITORY_FIGHT_TROOPS_DATA_POKER4_HP,				// 卡牌4当前血量					uint
//	TERRITORY_FIGHT_TROOPS_DATA_POKER4_SP,				// 卡牌4当前愤怒					uint
//	TERRITORY_FIGHT_TROOPS_DATA_POKER5_HP,				// 卡牌5当前血量					uint
//	TERRITORY_FIGHT_TROOPS_DATA_POKER5_SP,				// 卡牌5当前愤怒					uint
//};
//
//static const char* GAME_DB_NAME_USER_WAR_ROAD	= "user_war_road";			// 玩家战役记录表
//enum USER_WAR_ROAD_DATA
//{
//	USER_WAR_ROAD_DATA_ID,					// id						bigint
//	USER_WAR_ROAD_DATA_USER_ID,				// 玩家ID					uint
//	USER_WAR_ROAD_DATA_MODE,				// 模式						int
//	USER_WAR_ROAD_DATA_CHAPTER,				// 章节						int
//	USER_WAR_ROAD_DATA_PASS,				// 关卡						int
//	USER_WAR_ROAD_DATA_STAR,				// 星级						uint
//	USER_WAR_ROAD_DATA_DAY_FIGHT_COUNT,		// 每日战斗次数				uint
//	USER_WAR_ROAD_DATA_DAY_RESET_COUNT,		// 每日重置次数				uint
//	USER_WAR_ROAD_DATA_RECORD_TIME,			// 记录日期					uint
//};
//
//static const char* GAME_DB_NAME_WAR_ROAD_FIGHT	= "war_road_fight";			// 战役战斗记录表
//enum WAR_ROAD_FIGHT_DATA
//{
//	WAR_ROAD_FIGHT_DATA_ID = 0,				// 自增长ID					uint
//	WAR_ROAD_FIGHT_DATA_WAR_KEY,			// 战役key（模式*1000000+章节*1000+关卡）	bigint
//	WAR_ROAD_FIGHT_DATA_RECORD_TIME,		// 记录时间					uint
//	WAR_ROAD_FIGHT_DATA_REPLYADDRESS,		// 录像地址					varchar
//	WAR_ROAD_FIGHT_DATA_SERVER_GROUP,		// 服务器组					uint
//};
//
//static const char* GAME_DB_NAME_WAR_ROAD_TEAM_LOG	= "war_road_team_log";	// 团队战役记录表
//enum WAR_ROAD_TEAM_LOG_DATA
//{
//	WAR_ROAD_TEAM_LOG_DATA_ID = 0,			// 自增长id					bigint
//	WAR_ROAD_TEAM_LOG_DATA_SYNDICATE_ID,	// 帮派ID					uint
//	WAR_ROAD_TEAM_LOG_DATA_CHAPTER,			// 章节						uint
//	WAR_ROAD_TEAM_LOG_DATA_SERVER_GROUP,	// 服务器组					uint
//	WAR_ROAD_TEAM_LOG_DATA_OPEN_TIME,		// 开启时间					uint
//	WAR_ROAD_TEAM_LOG_DATA_COMPLETE,		// 是否完成过				uint
//	WAR_ROAD_TEAM_LOG_DATA_COMPLETE_TIME,	// 完成时间					uint
//	WAR_ROAD_TEAM_LOG_DATA_CHAPTER_DPS,		// 章节伤害量				bigint
//	WAR_ROAD_TEAM_LOG_DATA_CHAPTER_PROGRESS,// 章节进度（章节伤害量/章节怪物总血量） uint
//	WAR_ROAD_TEAM_LOG_DATA_PASS_FIGHT,		// 战斗关卡					uint
//	WAR_ROAD_TEAM_LOG_DATA_ROUND_FIGHT,		// 战斗波数					uint
//	WAR_ROAD_TEAM_LOG_DATA_MONSTER1_LEFTHP,	// 怪物1剩余血量比率(%)		uint
//	WAR_ROAD_TEAM_LOG_DATA_MONSTER2_LEFTHP,	// 怪物2剩余血量比率(%)		uint
//	WAR_ROAD_TEAM_LOG_DATA_MONSTER3_LEFTHP,	// 怪物3剩余血量比率(%)		uint
//	WAR_ROAD_TEAM_LOG_DATA_MONSTER4_LEFTHP,	// 怪物4剩余血量比率(%)		uint
//	WAR_ROAD_TEAM_LOG_DATA_MONSTER5_LEFTHP,	// 怪物5剩余血量比率(%)		uint
//	WAR_ROAD_TEAM_LOG_DATA_PASS_DPS,		// 关卡伤害量				bigint
//	WAR_ROAD_TEAM_LOG_DATA_PASS_PROGRESS,	// 关卡进度（关卡伤害量/关卡怪物总血量） uint
//	WAR_ROAD_TEAM_LOG_DATA_USER_ID,			// 挑战玩家ID				uint
//	WAR_ROAD_TEAM_LOG_DATA_FIGHT_STATUS,	// 挑战状态（1准备，2战斗）	uint
//	WAR_ROAD_TEAM_LOG_DATA_FIGHT_TIME,		// 挑战时间（准备，战斗）	uint
//};
//
//static const char* GAME_DB_NAME_WAR_ROAD_TEAM_AWARD	= "war_road_team_award";// 团队战役战利品申请记录表
//enum WAR_ROAD_TEAM_AWARD_DATA
//{
//	WAR_ROAD_TEAM_AWARD_DATA_ID = 0,		// 自增长id					bigint
//	WAR_ROAD_TEAM_AWARD_DATA_SYNDICATE_ID,	// 帮派ID					uint
//	WAR_ROAD_TEAM_AWARD_DATA_CHAPTER,		// 章节						uint
//	WAR_ROAD_TEAM_AWARD_DATA_AWARD_TYPE,	// 战利品类型				uint
//	WAR_ROAD_TEAM_AWARD_DATA_USER_ID,		// 申请玩家ID				uint
//	WAR_ROAD_TEAM_AWARD_DATA_APPLY_TIME,	// 申请时间					uint
//	WAR_ROAD_TEAM_AWARD_DATA_CUT_TIME,		// 插队时间					uint
//	WAR_ROAD_TEAM_AWARD_DATA_SERVER_GROUP,	// 服务器组					uint
//};
//
//static const char* GAME_DB_NAME_WAR_ROAD_TEAM_AWARD_HISTORY	= "war_road_team_award_history";// 团队战役战利品历史记录表
//enum WAR_ROAD_TEAM_AWARD_HISTORY_DATA
//{
//	WAR_ROAD_TEAM_AWARD_HISTORY_DATA_ID = 0,		// 自增长id					bigint
//	WAR_ROAD_TEAM_AWARD_HISTORY_DATA_SYNDICATE_ID,	// 帮派ID					uint
//	WAR_ROAD_TEAM_AWARD_HISTORY_DATA_CHAPTER,		// 章节						uint
//	WAR_ROAD_TEAM_AWARD_HISTORY_DATA_AWARD_TYPE,	// 战利品类型				uint
//	WAR_ROAD_TEAM_AWARD_HISTORY_DATA_AWARD_NUM,		// 战利品数量				uint
//	WAR_ROAD_TEAM_AWARD_HISTORY_DATA_USER_ID,		// 获得玩家ID				uint
//	WAR_ROAD_TEAM_AWARD_HISTORY_DATA_GIVE_TIME,		// 获得时间（未分配的记录表示下次自动分配时间）				uint
//	WAR_ROAD_TEAM_AWARD_HISTORY_DATA_SENDER_ID,		// 分配者ID					uint
//	WAR_ROAD_TEAM_AWARD_HISTORY_DATA_SERVER_GROUP,	// 服务器组					uint
//};
//
//static const char* GAME_DB_NAME_WAR_ROAD_TEAM_DPS	= "war_road_team_dps";	// 团队战役伤害记录表
//enum WAR_ROAD_TEAM_DPS_DATA
//{
//	WAR_ROAD_TEAM_DPS_DATA_ID = 0,			// 自增长id					bigint
//	WAR_ROAD_TEAM_DPS_DATA_LOG_ID,			// log_id					bigint
//	WAR_ROAD_TEAM_DPS_DATA_USER_ID,			// 玩家ID					uint
//	WAR_ROAD_TEAM_DPS_DATA_DPS_VALUE,		// dps伤害值				uint
//	WAR_ROAD_TEAM_DPS_DATA_SERVER_GROUP,	// 服务器组					uint
//};
//
//static const char* GAME_DB_NAME_WAR_ROAD_TEAM_DPS_HISTORY = "war_road_team_dps_history";	// 团队战役伤害记录表
//enum WAR_ROAD_TEAM_DPS_HISTORY_DATA
//{
//	WAR_ROAD_TEAM_DPS_HISTORY_DATA_ID = 0,				// 自增长id					bigint
//	WAR_ROAD_TEAM_DPS_HISTORY_DATA_CHAPTER,				// 章节						uint
//	WAR_ROAD_TEAM_DPS_HISTORY_DATA_USER_ID,				// 玩家ID(保留玩家最高一次输出记录)		uint
//	WAR_ROAD_TEAM_DPS_HISTORY_DATA_SERVER_GROUP,		// 服务器组					uint
//	WAR_ROAD_TEAM_DPS_HISTORY_DATA_DPS_VALUE,			// dps伤害值				uint
//	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER1_TYPE,			// 出战卡牌类型1			uint
//	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER1_LEV,			// 出战卡牌等级1			uint
//	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER1_STAR,			// 出战卡牌星级1			uint
//	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER1_COLOR,		// 出战卡牌颜色1			uint
//	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER2_TYPE,			// 出战卡牌类型2			uint
//	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER2_LEV,			// 出战卡牌等级2			uint
//	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER2_STAR,			// 出战卡牌星级2			uint
//	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER2_COLOR,		// 出战卡牌颜色2			uint
//	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER3_TYPE,			// 出战卡牌类型3			uint
//	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER3_LEV,			// 出战卡牌等级3			uint
//	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER3_STAR,			// 出战卡牌星级3			uint
//	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER3_COLOR,		// 出战卡牌颜色3			uint
//	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER4_TYPE,			// 出战卡牌类型4			uint
//	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER4_LEV,			// 出战卡牌等级4			uint
//	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER4_STAR,			// 出战卡牌星级4			uint
//	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER4_COLOR,		// 出战卡牌颜色4			uint
//	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER5_TYPE,			// 出战卡牌类型5			uint
//	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER5_LEV,			// 出战卡牌等级5			uint
//	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER5_STAR,			// 出战卡牌星级5			uint
//	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER5_COLOR,		// 出战卡牌颜色5			uint
//};
//
//static const char* GAME_DB_NAME_GAME_HISTORY_COMPLETE	= "game_history_complete";	// 成绩达成历史记录表
//enum GAME_HISTORY_COMPLETE_DATA
//{
//	GAME_HISTORY_COMPLETE_DATA_ID	= 0,				// 自增长id					bigint
//	GAME_HISTORY_COMPLETE_DATA_SERVER_GROUP,			// 服务器组					uint
//	GAME_HISTORY_COMPLETE_DATA_TYPE,					// 达成类型					uint
//	GAME_HISTORY_COMPLETE_DATA_RECORD_ID,				// 记录ID					uint
//	GAME_HISTORY_COMPLETE_DATA_CREATE_TIME,				// 创建时间					uint
//	GAME_HISTORY_COMPLETE_DATA_PARAM1,					// 参数1					uint
//	GAME_HISTORY_COMPLETE_DATA_PARAM2,					// 参数2					uint
//	GAME_HISTORY_COMPLETE_DATA_PARAM3,					// 参数3					uint
//};
//
//static const char* GAME_DB_NAME_SYN_WORSHIP = "syn_worship";	// 帮派膜拜记录表
//enum SYN_WORSHIP_DATA
//{
//	SYN_WORSHIP_DATA_ID = 0,					// ID				bigint
//	SYN_WORSHIP_DATA_USER_ID,					// 玩家ID			uint
//	SYN_WORSHIP_DATA_BEWORSHIP_ID,				// 被膜拜玩家ID		uint
//	SYN_WORSHIP_DATA_TIME,						// 膜拜日期			uint
//};
//
//static const char* GAME_DB_NAME_SYN_WORSHIP_AWARD = "syn_worship_award";	// 帮派膜拜奖励表
//enum SYN_WORSHIP_AWARD_DATA
//{
//	SYN_WORSHIP_AWARD_ID = 0,					// ID				bigint
//	SYN_WORSHIP_AWARD_USER_ID,					// 玩家ID			uint
//	SYN_WORSHIP_AWARD_AWARD_TYPE,				// 奖励类型			uint
//	SYN_WORSHIP_AWARD_AWARD_TOTAL,				// 奖励累计和		uint
//	SYN_WORSHIP_AWARD_SERVER_GROUP,				// 服务器组			uint
//};
//
//static const char* GAME_DB_NAME_MINE_FIGHT_POKER = "mine_fight_poker";	// 矿洞战斗卡牌表
//enum MINE_FIGHT_POKER
//{
//	MINE_FIGHT_POKER_ID = 0,			// ID				uint
//	MINE_FIGHT_POKER_ATK_USER_ID,		// 攻击方玩家ID		uint
//	MINE_FIGHT_POKER_DEF_USER_ID,		// 防守方玩家ID		uint
//	MINE_FIGHT_POKER_POKER_ID,			// 卡牌ID			bigint
//	MINE_FIGHT_POKER_LEFT_HP,			// 剩余血量			uint
//	MINE_FIGHT_POKER_LEFT_SP,			// 剩余怒气			uint
//	MINE_FIGHT_POKER_POKER_CAMP,		// 卡牌归属			uint
//};
//
//static const char* GAME_DB_NAME_FRIEND_INVITE = "friend_invite";			//  好友邀请表
//enum FRIEND_INVITE
//{
//	FRIEND_INVITE_ID = 0,				// ID				bigint
//	FRIEND_INVITE_INVITER_ID,			// 邀请者ID			uint
//	FRIEND_INVITE_BE_INVITER_ID,		// 被邀请者ID		uint
//	FRIEND_INVITE_VAS,					// 累计元宝			uint
//	FRIEND_INVITE_SERVER_GROUP,			// 服务器组			uint
//};
//
//static const char* GAME_DB_NAME_FRIEND_INVITE_CODE = "friend_invite_code";	//  好友邀请码表
//enum FRIEND_INVITE_CODE
//{
//	FRIEND_INVITE_CODE_USER_ID,				// 玩家ID			uint
//	FRIEND_INVITE_CODE_CODE,				// 邀请码			varchar16
//};
//
//static const char* GAME_DB_NAME_TALK_WORLD = "talk_world";	// 世界聊天表
//enum TALK_WORLD_DATA
//{
//	TALK_WORLD_DATA_ID = 0,								// 自增长ID				bigint
//	TALK_WORLD_DATA_SENDER_ID,							// 发送者ID				uint
//	TALK_WORLD_DATA_SENDER_NAME,						// 发送者角色名			varchar32
//	TALK_WORLD_DATA_SENDER_FACE,						// 发送者头像			uint
//	TALK_WORLD_DATA_SENDER_LEV,							// 发送者等级			uint
//	TALK_WORLD_DATA_TEXT,								// 发送内容				varchar256
//	TALK_WORLD_DATA_TIME,								// 发送时间				uint
//	TALK_WORLD_DATA_TYPE,								// 类型					uint
//	TALK_WORLD_DATA_PARAM1,								// 预留1				uint
//	TALK_WORLD_DATA_PARAM2,								// 预留2				uint
//	TALK_WORLD_DATA_PARAM3,								// 预留3				uint
//	TALK_WORLD_DATA_PARAM4,								// 预留4				uint
//	TALK_WORLD_DATA_SERVER_GROUP,						// 服务器组				uint
//};
//
//static const char* GAME_DB_NAME_TALK_SYN = "talk_syn";	// 帮派聊天表
//enum TALK_SYN_DATA
//{
//	TALK_SYN_DATA_ID = 0,								// 自增长ID				bigint
//	TALK_SYN_DATA_SYN_ID,								// 帮派ID				bigint
//	TALK_SYN_DATA_SENDER_ID,							// 发送者ID				uint
//	TALK_SYN_DATA_SENDER_NAME,							// 发送者角色名			varchar32
//	TALK_SYN_DATA_SENDER_FACE,							// 发送者头像			uint
//	TALK_SYN_DATA_SENDER_LEV,							// 发送者等级			uint
//	TALK_SYN_DATA_TEXT,									// 发送内容				varchar256
//	TALK_SYN_DATA_TIME,									// 发送时间				uint
//	TALK_SYN_DATA_TYPE,									// 类型					uint
//	TALK_SYN_DATA_PARAM1,								// 预留1				uint
//	TALK_SYN_DATA_PARAM2,								// 预留2				uint
//	TALK_SYN_DATA_PARAM3,								// 预留3				uint
//	TALK_SYN_DATA_PARAM4,								// 预留4				uint
//	TALK_SYN_DATA_SERVER_GROUP,							// 服务器组				uint
//};
//
//static const char* GAME_DB_NAME_TALK_PRIVATE = "talk_private";	// 私聊表
//enum TALK_PRIVATE_DATA
//{
//	TALK_PRIVATE_DATA_ID = 0,								// 自增长ID				bigint
//	TALK_PRIVATE_DATA_USER_ID,								// 接收者ID				uint
//	TALK_PRIVATE_DATA_SENDER_ID,							// 发送者ID				uint
//	TALK_PRIVATE_DATA_SENDER_NAME,							// 发送者角色名			varchar32
//	TALK_PRIVATE_DATA_SENDER_FACE,							// 发送者头像			uint
//	TALK_PRIVATE_DATA_SENDER_LEV,							// 发送者等级			uint
//	TALK_PRIVATE_DATA_TEXT,									// 发送内容				varchar256
//	TALK_PRIVATE_DATA_TIME,									// 发送时间				uint
//	TALK_PRIVATE_DATA_TYPE,									// 类型					uint
//	TALK_PRIVATE_DATA_PARAM1,								// 预留1				uint
//	TALK_PRIVATE_DATA_PARAM2,								// 预留2				uint
//	TALK_PRIVATE_DATA_PARAM3,								// 预留3				uint
//	TALK_PRIVATE_DATA_PARAM4,								// 预留4				uint
//	TALK_PRIVATE_DATA_SERVER_GROUP,							// 服务器组		
//};
//
//static const char* GAME_DB_NAME_MINE_COLLECT = "mine_collect";	// 矿洞采集表
//enum MINE_COLLECT_DATA
//{
//	MINE_COLLECT_DATA_USER_ID = 0,							// 玩家ID				uint
//	MINE_COLLECT_DATA_NAME,									// 玩家角色名			varchar32
//	MINE_COLLECT_DATA_LEV,									// 玩家等级				uint
//	MINE_COLLECT_DATA_LOOKFACE,								// 玩家头像				uint
//	MINE_COLLECT_DATA_LOOKFACE_FRAME,						// 玩家头像框			uint
//	MINE_COLLECT_DATA_ATK_COUNT_TOTAL,						// 攻击矿洞次数总和		uint
//	MINE_COLLECT_DATA_MONEY_TOTAL,							// 获得金币总和			uint	
//	MINE_COLLECT_DATA_DRUG_TOTAL,							// 获得药剂总和			uint
//	MINE_COLLECT_DATA_ATK_COUNT0_VALUE,						// 攻击次数值0			uint
//	MINE_COLLECT_DATA_MONEY0_VALUE,							// 金币值0				uint
//	MINE_COLLECT_DATA_DRUG0_VALUE,							// 药剂值0				uint
//	MINE_COLLECT_DATA_DATE0,								// 日期0				uint
//	MINE_COLLECT_DATA_ATK_COUNT1_VALUE,						// 攻击次数值1			uint
//	MINE_COLLECT_DATA_MONEY1_VALUE,							// 金币值1				uint
//	MINE_COLLECT_DATA_DRUG1_VALUE,							// 药剂值1				uint
//	MINE_COLLECT_DATA_DATE1,								// 日期1				uint
//	MINE_COLLECT_DATA_ATK_COUNT2_VALUE,						// 攻击次数值2			uint
//	MINE_COLLECT_DATA_MONEY2_VALUE,							// 金币值2				uint
//	MINE_COLLECT_DATA_DRUG2_VALUE,							// 药剂值2				uint
//	MINE_COLLECT_DATA_DATE2,								// 日期2				uint
//	MINE_COLLECT_DATA_ATKCOUNT_RANK_LAST,					// 攻击次数上期排名		uint
//	MINE_COLLECT_DATA_MONEY_RANK_LAST,						// 金币采集上期排名		uint
//	MINE_COLLECT_DATA_DRUG_RANK_LAST,						// 药剂采集上期排名		uint
//	MINE_COLLECT_DATA_SERVER_GROUP,							// 服务器组				uint
//};
//
//static const char* GAME_DB_NAME_SYN_GIFT_BOX_LOG	= "syn_giftbox_log";	// 帮派礼盒记录表
//enum SYN_GIFT_BOX_LOG_DATA
//{
//	SYN_GIFT_BOX_LOG_DATA_ID = 0,							// 自增长ID				bigint
//	SYN_GIFT_BOX_LOG_DATA_SYNDICATE_ID,						// 帮派ID				uint
//	SYN_GIFT_BOX_LOG_DATA_BOX_TYPE,							// 礼盒类型				uint
//	SYN_GIFT_BOX_LOG_DATA_INVAILD_TIME,						// 结束时间				uint
//	SYN_GIFT_BOX_LOG_DATA_GIVE_USER_ID,						// 赠送玩家ID			uint	
//	SYN_GIFT_BOX_LOG_DATA_GIVE_USER_NAME,					// 赠送玩家名称			varchar32
//	SYN_GIFT_BOX_LOG_DATA_SERVER_GROUP,						// 服务器组				uint
//};
//
//static const char* GAME_DB_NAME_USER_SYN_GIFTBOX_AWARD	= "user_syn_giftbox_ward";	// 玩家帮派礼盒领取记录表
//enum USER_SYN_GIFTBOX_AWARD_DATA
//{
//	USER_SYN_GIFTBOX_AWARD_DATA_USER_ID = 0,				// 玩家ID				uint
//	USER_SYN_GIFTBOX_AWARD_DATA_SYN_GIFTBOX_ID,				// 帮派礼盒记录id		uint
//	USER_SYN_GIFTBOX_AWARD_DATA_INVIALDTIME,				// 失效时间				uint
//};
//
//static const char* GAME_DB_NAME_LOOKFACE_FRAME = "lookface_frame";					// 玩家获得的头像框数据表
//enum USER_LOOKFACE_FRAME
//{
//	USER_LOOKFACE_FRAME_ID = 0,								// ID					uint
//	USER_LOOKFACE_FRAME_USER_ID,							// 玩家ID				uint
//	USER_LOOKFACE_FRAME_FRAME_TYPE,							// 头像框类型			uint
//	USER_LOOKFACE_FRAME_END_TIME,							// 结束时间				uint
//};
//
//
//static const char* GAME_DB_NAME_CROSS_ROOM = "cs_room";		// 跨服房间表
//enum CROSS_ROOM_DATA
//{
//	CROSS_ROOM_DATA_ID = 0,		// id			uint
//	CROSS_ROOM_DATA_TYPE,		// 类型			uint
//	CROSS_ROOM_DATA_LINE,		// 所在线路		uint
//	CROSS_ROOM_DATA_OWNER_ID,	// 拥有者id		uint
//	CROSS_ROOM_DATA_CREATE_TIME,// 房间创建时间	uint
//	CROSS_ROOM_DATA_END_TIME,	// 强制解散时间 uint
//	CROSS_ROOM_DATA_DATA1,		// 数据1		uint
//	CROSS_ROOM_DATA_DATA2,		// 数据2		uint
//	CROSS_ROOM_DATA_DATA3,		// 数据3		uint
//	CROSS_ROOM_DATA_DATA4,		// 数据4		uint
//	CROSS_ROOM_DATA_DATA5,		// 数据5		uint
//	CROSS_ROOM_DATA_STR1,		// 字串1		varchar255
//	CROSS_ROOM_DATA_STR2,		// 字串2		varchar255
//};
//
//static const char* GAME_DB_NAME_CROSS_ROOM_MEMBER = "cs_room_member";	// 跨服房间成员表
//enum CROSS_ROOM_MEMBER_DATA
//{
//	CROSS_ROOM_MEMBER_DATA_USER_ID = 0,		// 角色id		uint
//	CROSS_ROOM_MEMBER_DATA_ROOM_ID,			// 房间id		uint
//	CROSS_ROOM_MEMBER_DATA_DATA1,			// 数据1		uint
//	CROSS_ROOM_MEMBER_DATA_DATA2,			// 数据2		uint
//	CROSS_ROOM_MEMBER_DATA_DATA3,			// 数据3		uint
//};
//
//static const char* GAME_DB_NAME_CROSS_NTM_FIGHT_LOG = "cs_ntm_fight_log";	// 跨服南天门战斗记录表
//enum CROSS_NTM_FIGHT_LOG_DATA
//{
//	CROSS_NTM_FIGHT_LOG_DATA_USER_ID = 0,		// 角色id	uint
//	CROSS_NTM_FIGHT_LOG_DATA_INTEGRAL,			// 积分		uint
//	CROSS_NTM_FIGHT_LOG_DATA_PASS_TIME,			// 通关时间	uint
//	CROSS_NTM_FIGHT_LOG_DATA_RANK,				// 排名		uint
//	CROSS_NTM_FIGHT_LOG_DATA_AWARD_TYPE,		// 奖励类型	uint
//	CROSS_NTM_FIGHT_LOG_DATA_AWARD_NUM,			// 奖励数量	uint
//};
//
//static const char* GAME_DB_NAME_SYN_BUFF = "syn_buff";		// 帮派buff表
//enum SYN_BUFF_DATA
//{
//	SYN_BUFF_DATA_ID = 0,						// id		bigint
//	SYN_BUFF_DATA_SYNDICATE_ID,					// 帮派id	uint
//	SYN_BUFF_DATA_TYPE,							// buff类型	uint
//	SYN_BUFF_DATA_POWER,						// buff威力	uint
//	SYN_BUFF_DATA_END_TIME,						// 结束时间	uint
//	SYN_BUFF_DATA_ADD_COUNT,					// 叠加层数	uint
//	SYN_BUFF_DATA_PARAM1,						// 参数1	uint
//	SYN_BUFF_DATA_PARAM2,						// 参数2	uint
//	SYN_BUFF_DATA_SERVER_GROUP,					// 服务器组	uint
//};
//
//static const char* GAME_DB_NAME_USER_BUFF = "user_buff";	// 房玩家buff表
//enum USER_BUFF_DATA
//{
//	USER_BUFF_DATA_ID = 0,						// id		bigint
//	USER_BUFF_DATA_USER_ID,						// 角色id	uint
//	USER_BUFF_DATA_TYPE,						// buff类型	uint
//	USER_BUFF_DATA_POWER,						// buff威力	uint
//	USER_BUFF_DATA_END_TIME,					// 结束时间	uint
//	USER_BUFF_DATA_SOURCE_ID,					// 来源ID	uint
//	USER_BUFF_DATA_ADD_COUNT,					// 叠加层数	uint
//	USER_BUFF_DATA_PARAM1,						// 参数1	uint
//	USER_BUFF_DATA_PARAM2,						// 参数2	uint
//};
//
//static const char* GAME_DB_NAME_USER_MARKS_INFO = "user_marksinfo";	// 玩家推送信息记录表
//enum USER_MARKSINFO_DATA
//{
//	USER_MARKSINFO_DATA_USER_ID,				// 角色id	uint
//	USER_MARKSINFO_DATA_TYPE,					// 推送类型	uint
//	USER_MARKSINFO_DATA_DATA,					// 推送数据	uint
//};

#endif // end of _DATABASE_DEFINE_GAME_H_