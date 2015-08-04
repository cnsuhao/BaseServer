////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan ChuangYou, All Rights Reserved
// Moudle: DatabaseDefine.h
//		数据库相关内容全局声明处
// Author: 彭文奇(Peng Wenqi)
// Created: 2014-11-3
////////////////////////////////////////////////////////////////////////
#ifndef _CARD_SERVER_DATABASE_DEFINE_
#define _CARD_SERVER_DATABASE_DEFINE_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 账号库
static const char* ACC_DB_NAME_ACCOUNT = "account";		// 账号表
enum ACCOUNT_DATA
{
	ACCOUNT_DATA_ID = 0,				// id,			uint
	ACCOUNT_DATA_NAME,					// 账号名,		varchar64
	ACCOUNT_DATA_PASSWORD,				// 密码,		varchar64
	ACCOUNT_DATA_REG_TIME,				// 注册utc时间, uint
	ACCOUNT_DATA_ACCOUNT_TYPE,			// 账号类型		uint
	ACCOUNT_DATA_ACCOUNT_STATUS,		// 账号状态		uint
	ACCOUNT_DATA_ACCOUNT_STATUS_PARAM,	// 账号状态参数	uint
	ACCOUNT_DATA_PLATFORM,				// 平台			varchar32
	ACCOUNT_DATA_CHANNEL,				// 渠道			varchar32
	ACCOUNT_DATA_OS,					// os			varchar32
	ACCOUNT_DATA_BIND_INVITE_CODE,		// 绑定邀请码	varchar32
};

static const char* ACC_DB_VAS_LOG = "vas_log";	// 元宝日志表
enum VAS_LOG_DATA
{
	VAS_LOG_DATA_ID = 0,			// id			bigint
	VAS_LOG_DATA_ACCOUNT_ID,		// 账号id		uint
	VAS_LOG_DATA_USER_ID,			// 角色id		uint
	VAS_LOG_DATA_SERVER_GROUP,		// 服务器组		uint
	VAS_LOG_DATA_SERVER_LINE,		// 服务器线		uint
	VAS_LOG_DATA_FLOW_TYPE,			// 流向类型		uint
	VAS_LOG_DATA_TIME,				// 时间, utc秒	uint
	VAS_LOG_DATA_ITEMTYPE_ID,		// itemtype		uint
	VAS_LOG_DATA_ITEMTYPE_AMOUNT,	// 数量			uint
	VAS_LOG_DATA_POINT,				// 操作点数		bigint
	VAS_LOG_DATA_AFTER_POINT,		// 操作后点数	bigint
	VAS_LOG_DATA_EXTRA_TEXT,		// 额外文字说明 varchar128
};

static const char* ACC_DB_MONEY_LOG = "money_log";	// 金钱日志表
enum MONEY_LOG_DATA
{
	MONEY_LOG_DATA_ID = 0,			// id			bigint
	MONEY_LOG_DATA_ACCOUNT_ID,		// 账号id		uint
	MONEY_LOG_DATA_USER_ID,			// 角色id		uint
	MONEY_LOG_DATA_SERVER_GROUP,	// 服务器组		uint
	MONEY_LOG_DATA_SERVER_LINE,		// 服务器线		uint
	MONEY_LOG_DATA_FLOW_TYPE,		// 流向类型		uint
	MONEY_LOG_DATA_TIME,			// 时间, utc秒	uint
	MONEY_LOG_DATA_ITEMTYPE_ID,		// itemtype		uint
	MONEY_LOG_DATA_ITEMTYPE_AMOUNT,	// 数量			uint
	MONEY_LOG_DATA_MONEY_TYPE,		// 金币类型		uint
	MONEY_LOG_DATA_POINT,			// 操作点数		bigint
	MONEY_LOG_DATA_AFTER_POINT,		// 操作后点数	bigint
	MONEY_LOG_DATA_EXTRA_TEXT,		// 额外文字说明 varchar128
};

static const char* ACC_DB_SERVER_LIST = "server_list";	// 服务器列表, 维护人员配置的
enum SERVER_LIST_DATA
{
	SERVER_LIST_DATA_GROUP = 0,			// 组id			uint
	SERVER_LIST_DATA_LINE,				// 线id			uint
	SERVER_LIST_DATA_CLIENT_IP,			// 客户端ip		varchar50
	SERVER_LIST_DATA_CLIENT_PORT,		// 客户端端口	uint 
	SERVER_LIST_DATA_CLOSE,				// 关闭标记		uint
};

static const char* ACC_DB_NEWCARD = "newcard";	// 新手卡号码表
enum NEWCARD_DATA
{
	NEWCARD_DATA_ID = 0,			// id			bigint
	NEWCARD_DATA_CARD,				// 卡号			char64
	NEWCARD_DATA_PICKED,			// 使用标记		uint
	NEWCARD_DATA_PLATFORM,			// 平台			varchar10
	NEWCARD_DATA_SERVER_GROUP,		// 服务器组		uint
};

static const char* ACC_DB_PAYLOG = "paylog";	// 充值记录表
enum PAYLOG_DATA
{
	PAYLOG_DATA_LOGID = 0,		// id			bigint
	PAYLOG_DATA_PAYNUM,			// 流水号		varchar255
	PAYLOG_DATA_LOGDATE,		// 充值utc时间	uint
	PAYLOG_DATA_ACCOUNT_ID,		// 账号id		uint
	PAYLOG_DATA_USER_ID,		// 角色id		uint
	PAYLOG_DATA_IP,				// ip			varchar20
	PAYLOG_DATA_PAYGOLD,		// 充值元宝		uint
	PAYLOG_DATA_FREEGOLD,		// 赠送元宝		uint
	PAYLOG_DATA_PAYMONEY,		// 人民币		DECIMAL
	PAYLOG_DATA_CHANNEL,		// channel		varchar20
	PAYLOG_DATA_CHANNEL_FEE,	// channel_fee	float
	PAYLOG_DATA_SERVER_GROUP,	// 服务器组号	uint
	PAYLOG_DATA_CONFIG_ID,		// 配置id		uint
	PAYLOG_DATA_STATUS,			// 审核状态（0 审批中， 1 通过， 2 拒绝, 3 完结）	uint
};

static const char* ACC_DB_ONLINE_LOG = "online_log";	// 在线日志表
enum ONLINE_LOG_DATA
{
	ONLINE_LOG_DATA_ID = 0,
	ONLINE_LOG_DATA_TIME,
	ONLINE_LOG_DATA_COUNT_ONLINE,
	ONLINE_LOG_DATA_SERVER_GROUP,
};

static const char* ACC_DB_NOTIFY_PHP = "notify_php";	// 平台公告表
enum NOTIFY_PHP_DATA
{
	NOTIFY_PHP_DATA_ID = 0,				// 自增长id	uint
	NOTIFY_PHP_DATA_BEGIN_TIME,			// 开始时间 uint
	NOTIFY_PHP_DATA_INTERVAL_SECOND,	// 间隔时间 uint
	NOTIFY_PHP_DATA_COUNT,				// 播放次数 uint
	NOTIFY_PHP_DATA_CHANNEL,			// 频道		uint
	NOTIFY_PHP_DATA_TEXT,				// 公告内容 varchar512
	NOTIFY_PHP_DATA_SERVER_GROUP,		// 服务器组 uint
};

static const char* ACC_DB_NAME_GM_MAC = "gm_mac";	// gm Mac地址配置
enum GM_MAC_DATA
{
	GM_MAC_DATA_ADDRESS_MAC = 0,		// mac地址字符串	varchar32
	GM_MAC_DATA_PARAM_STRING,			// 注释字符长		varchar64
};

static const char* ACC_DB_NAME_GM_OPERATION_LOG = "gm_operation_log";	// gm 操作日志
enum GM_OPERATION_LOG_DATA
{
	GM_OPERATION_LOG_DATA_ID = 0,				// id				uint
	GM_OPERATION_LOG_DATA_UTC_SECOND,			// 记录时间, utc秒	uint
	GM_OPERATION_LOG_DATA_DATE_TIME,			// 日期时间			varchar24
	GM_OPERATION_LOG_DATA_GM_ACCOUNT_ID,		// gm账号id			uint
	GM_OPERATION_LOG_DATA_GM_ACCOUNT_NAME,		// gm账号名			varchar32
	GM_OPERATION_LOG_DATA_GM_USER_ID,			// gm角色id			uint
	GM_OPERATION_LOG_DATA_GM_USER_NAME,			// gm角色名			varchar32
	GM_OPERATION_LOG_DATA_GM_IP,				// gm操作时ip		varchar32
	GM_OPERATION_LOG_DATA_GM_MAC,				// gm操作时mac地址	varchar32
	GM_OPERATION_LOG_DATA_SERVER_GROUP,			// 服务器组			uint
	GM_OPERATION_LOG_DATA_SERVER_LINE,			// 服务器线			uint
	GM_OPERATION_LOG_DATA_OPERATION_TYPE_STR,	// 操作类型字符串	varchar16
	GM_OPERATION_LOG_DATA_OPERATION_INFO,		// 操作详情			varchar128
};

//////////////////////////////////////////////////////////////////////////
// 游戏库
static const char* GAME_DB_NAME_USER = "user";	// 角色表
enum USER_DATA
{
	USER_DATA_BEGIN = 0,		// 哨兵头
	USER_DATA_ID = 0,			// 角色id, 1000W起				uint
	USER_DATA_ACCOUNT_ID,		// 账号id						uint
	USER_DATA_NAME,				// 角色名						varchar32
	USER_DATA_LAST_LOGIN,		// 最后一次登陆日期(YYYYMMDD)	uint
	USER_DATA_CREATE_TIME,		// 创建时间(utc时间)			uint
	USER_DATA_EXIT_TIME,		// 退出时间(utc时间)			uint
	USER_DATA_YESTERDAY_LOGIN,	// 昨日登陆标记					uint
	USER_DATA_ALL_ONLINE_TIME,	// 总在线时间(单位秒)			uint
	USER_DATA_SERVER_GROUP,		// 归属服务器组					uint
	USER_DATA_LEV,				// 等级							uint
	USER_DATA_EXP,				// 经验							bigint
	USER_DATA_SEX,				// 性别							uint
	USER_DATA_LOOKFACE,			// 头像							uint
	USER_DATA_DEL_FLAG,			// 删除标记						uint
	USER_DATA_ACCOUNT_TYPE,		// 账号类型, 账号表覆盖			uint
	USER_DATA_MAX_SCORE,		// 最大战斗力					uint
	USER_DATA_MAX_POKER_STAR,	// 卡牌总星级					uint
	USER_DATA_INIT_POKER,		// 初始化卡牌选择				uint
	USER_DATA_STOP_TALK_END,	// 禁言结束时间					uint
	USER_DATA_EXP0_DATE_DAYS,	// 经验统计量0 EPOCH DAY		uint
	USER_DATA_EXP0_DATE_YMD,	// 经验统计量0 YYYYMMDD			uint
	USER_DATA_EXP0_VALUE,		// 经验统计量0 经验值			uint
	USER_DATA_EXP1_DATE_DAYS,	// 经验统计量1 EPOCH DAY		uint
	USER_DATA_EXP1_DATE_YMD,	// 经验统计量1 YYYYMMDD			uint
	USER_DATA_EXP1_VALUE,		// 经验统计量1 经验值			uint
	USER_DATA_EXP2_DATE_DAYS,	// 经验统计量2 EPOCH DAY		uint
	USER_DATA_EXP2_DATE_YMD,	// 经验统计量2 YYYYMMDD			uint
	USER_DATA_EXP2_VALUE,		// 经验统计量2 经验值			uint
	USER_DATA_SIGNATURE,		// 个性签名						varchar256
	USER_DATA_LOOKFACE_FRAME,	// 头像框                       uint
	USER_DATA_BIRTHDAY,			// 生日		   YYYYMMDD         uint
	USER_DATA_ADDRESS,			// 所在地						varchar64
	USER_DATA_GLAMOUR,			// 魅力值						uint
	USER_DATA_GLAMOUR_TOTAL,	// 总魅力值						uint
	USER_DATA_END,				// 哨兵尾
};

static const char* GAME_DB_NAME_USER_MONEY = "user_money";	// 角色金币表
enum USER_MONEY_DATA
{
	USER_MONEY_DATA_ID = 0,		// id			bigint
	USER_MONEY_DATA_USERID,		// 角色id		bigint
	USER_MONEY_DATA_MONEYTYPE,	// 货币类型		uint
	USER_MONEY_DATA_MONEYDATA,	// 货币数据		bigint
};

static const char* GAME_DB_NAME_USER_VAS = "user_vas";	// 角色元宝表
enum USER_VAS_DATA
{
	USER_VAS_DATA_USER_ID = 0,				// 角色id			uint
	USER_VAS_DATA_VAS,						// 当前元宝			bigint
	USER_VAS_DATA_TOTAL_PAY_VAS,			// 总充值元宝		bigint
	USER_VAS_DATA_TOTAL_FREE_VAS,			// 总赠送元宝		bigint
	USER_VAS_DATA_TOTAL_USE_VAS,			// 总消费元宝		bigint
	USER_VAS_DATA_FISRT_SPEND_TIME,			// 第一次消费时间	uint
	USER_VAS_DATA_LAST_SPEND_TIME,			// 最近消费时间		uint
	USER_VAS_DATA_MONTH_CARD_ID,			// 月卡id			uint
	USER_VAS_DATA_MONTH_CARD_GOT_DATE,		// 领取到的日期		uint
	USER_VAS_DATA_MONTH_CARD_END_DATE,		// 最后一天领取日期	uint
	USER_VAS_DATA_FISRT_MASK,				// 第一次领取掩码	uint
};

static const char* GAME_DB_NAME_USER_MASK = "user_mask";	// 人物掩码表
enum USER_MASK_DATA
{
	USER_MASK_DATA_ID = 0,				// id,			int
	USER_MASK_DATA_USERID,				// 玩家id,		uint
	USER_MASK_DATA_MASKTYPE,			// 掩码类型,	uint
	USER_MASK_DATA_MASKID,				// 掩码id,		uint
	USER_MASK_DATA_CLEARTIME,			// 结束时间		uint
	USER_MASK_DATA_MASKDATA,			// 掩码数据		bigint
};

static const char* GAME_DB_NAME_GROUP_MASK = "group_mask";	// 组掩码表
enum LINE_MASK_DATA
{
	LINE_MASK_DATA_ID = 0,				// 掩码id,		int
	LINE_MASK_DATA_SERVER_GROUP,		// 服务器组,	uint
	LINE_MASK_DATA_DATA,				// 数据			uint
	LINE_MASK_DATA_ENDTIME,				// 结束时间		uint
};

static const char* GAME_DB_NAME_WORLD_MASK = "world_mask";	// 世界掩码表
enum SERVER_MASK_DATA
{
	SERVER_MASK_DATA_ID = 0,			// 掩码id,		int
	SERVER_MASK_DATA_DATA,				// 数据			uint
	SERVER_MASK_DATA_ENDTIME,			// 结束时间		uint
};

static const char* GAME_DB_NAME_ITEM_LOG = "item_log";	// 物品流向表
enum LOG_ITEM_FLOW_DATA
{
	LOG_ITEM_FLOW_DATA_ID = 0,		// 自增长id					bigint
	LOG_ITEM_FLOW_DATA_OWNERID,		// 主人id					uint
	LOG_ITEM_FLOW_DATA_TARGETID,	// 操作对象id				uint
	LOG_ITEM_FLOW_DATA_ITEMID,		// 物品id					bigint
	LOG_ITEM_FLOW_DATA_ITEMTYPE,	// 物品typeid				uint
	LOG_ITEM_FLOW_DATA_ITEMCOUNT,	// 物品数量					uint
	LOG_ITEM_FLOW_DATA_TYPE,		// 物品流向					uint
	LOG_ITEM_FLOW_DATA_CREATETIME,	// 创建时间(utc时间）		uint
	LOG_ITEM_FLOW_DATA_SERVERID,	// 服务器组					uint
	LOG_ITEM_FLOW_DATA_LINE,		// 线路						uint
	LOG_ITEM_FLOW_DATA_COMMENT,		// 说明字段					varchar128
};

static const char* GAME_DB_NAME_USER_TMP_DATA = "user_tmp_data";	// 角色Tmpdata表
enum USERTMPDATA_DATA
{
	USERTMPDATA_ERROR = -1,
	USERTMPDATA_ID = 0,							// id		bigint										
	USERTMPDATA_USERID,							// 玩家id	uint
	USERTMPDATA_TMP_DATA_ID,					// 数据id	uint

	USERTMPDATA_DATA_BEGIN,
	USERTMPDATA_DATA0 = USERTMPDATA_DATA_BEGIN,	// 数据0	uint
	USERTMPDATA_DATA1,							// 数据1	uint
	USERTMPDATA_DATA2,							// 数据2	uint
	USERTMPDATA_DATA3,							// 数据3	uint					
	USERTMPDATA_DATA4,							// 数据4	uint
	USERTMPDATA_DATA5,							// 数据5	uint
	USERTMPDATA_DATA6,							// 数据6	uint
	USERTMPDATA_DATA7,							// 数据7	uint
	USERTMPDATA_DATA_END,
};

static const char* GAME_DB_NAME_USER_TASK = "user_task";			// 角色任务表
enum EUSER_TASK
{	
	EUSER_TASK_ID			= 0,	// 编号														uint
	EUSER_TASK_USER_ID,				// 玩家id													uint
	EUSER_TASK_TYPE,				// 任务类型													uint
	EUSER_TASK_STEP,				// 步骤														uint
	EUSER_TASK_STATUS,				// 任务状态(0:未接受,1:接受, 2:提交, 3:达到完成条件但未提交)uint
	EUSER_TASK_COUNT1,				// 计数1													uint
	EUSER_TASK_COUNT2,				// 计数2													uint
	EUSER_TASK_COUNT3,				// 计数3													uint
	EUSER_TASK_BEGIN_TIME,			// 开始时间(单位秒)											uint
	EUSER_TASK_OVER_TIME,			// 过期时间(0:无限制, >0:过期时间单位秒)					uint
};

static const char* GAME_DB_NAME_USER_NEWCARD = "user_newcard";		// 角色新手卡使用信息表
enum USER_NEWCARD_DATA
{
	USER_NEWCARD_DATA_USERID = 0,	// 玩家id		uint
	USER_NEWCARD_DATA_LASTUSETIME,	// 上次使用时间	uint
	// 以下字段为20个掩码使用数据	bigint
	USER_NEWCARD_DATA_MASKDATA1,
	USER_NEWCARD_DATA_MASKDATA2,
	USER_NEWCARD_DATA_MASKDATA3,
	USER_NEWCARD_DATA_MASKDATA4,
	USER_NEWCARD_DATA_MASKDATA5,
	USER_NEWCARD_DATA_MASKDATA6,
	USER_NEWCARD_DATA_MASKDATA7,
	USER_NEWCARD_DATA_MASKDATA8,
	USER_NEWCARD_DATA_MASKDATA9,
	USER_NEWCARD_DATA_MASKDATA10,
	USER_NEWCARD_DATA_MASKDATA11,
	USER_NEWCARD_DATA_MASKDATA12,
	USER_NEWCARD_DATA_MASKDATA13,
	USER_NEWCARD_DATA_MASKDATA14,
	USER_NEWCARD_DATA_MASKDATA15,
	USER_NEWCARD_DATA_MASKDATA16,
	USER_NEWCARD_DATA_MASKDATA17,
	USER_NEWCARD_DATA_MASKDATA18,
	USER_NEWCARD_DATA_MASKDATA19,
	USER_NEWCARD_DATA_MASKDATA20,
};

static const char* GAME_DB_NAME_USER_MAIL	= "mail";	// 玩家邮件表
enum EUSER_MAIL
{
	EUSER_MAIL_ID		= 0,	// 编号									bigint
	EUSER_MAIL_USER_ID,			// 玩家ID								uint
	EUSER_MAIL_STATUS,			// 邮件状态(0:未读, 1:已读, 2:删除)		uint
	EUSER_MAIL_TITLE,			// 主题									varchar32
	EUSER_MAIL_SENDER,			// 发件人								varchar32
	EUSER_MAIL_CONTENT,			// 内容									varchar256
	EUSER_MAIL_SEND_TIME,		// 发送日期								uint
	EUSER_MAIL_OVER_TIME,		// 过期时间(必须有时间限制)				uint

	EUSER_MAIL_ITEM_TYPE1,		// 物品类型1							uint
	EUSER_MAIL_ITEM_NUM1,		// 物品数量1							uint
	EUSER_MAIL_ITEM_TYPE2,		// 物品类型2							uint
	EUSER_MAIL_ITEM_NUM2,		// 物品数量2							uint
	EUSER_MAIL_ITEM_TYPE3,		// 物品类型3							uint
	EUSER_MAIL_ITEM_NUM3,		// 物品数量3							uint
	EUSER_MAIL_ITEM_TYPE4,		// 物品类型4							uint
	EUSER_MAIL_ITEM_NUM4,		// 物品数量4							uint
	EUSER_MAIL_ITEM_TYPE5,		// 物品类型5							uint
	EUSER_MAIL_ITEM_NUM5,		// 物品数量5							uint
	EUSER_MAIL_ITEM_TYPE6,		// 物品类型6							uint
	EUSER_MAIL_ITEM_NUM6,		// 物品数量6							uint

	EUSER_MAIL_MONEY_TYPE1,		// 货币1								uint
	EUSER_MAIL_MONEY_NUM1,		// 货币1数量							uint
	EUSER_MAIL_MONEY_TYPE2,		// 货币2								uint
	EUSER_MAIL_MONEY_NUM2,		// 货币2数量							uint
	EUSER_MAIL_MONEY_TYPE3,		// 货币3								uint
	EUSER_MAIL_MONEY_NUM3,		// 货币3数量							uint
	EUSER_MAIL_MONEY_TYPE4,		// 货币4								uint
	EUSER_MAIL_MONEY_NUM4,		// 货币4数量							uint
	EUSER_MAIL_EXP,				// 经验									uint
	EUSER_MAIL_SERVER_GROUP,	// 服务器组								uint
};


static const char* GAME_DB_NAME_POKER = "poker";	// 卡牌表
enum POKER_DATA
{
	POKER_DATA_ID = 0,			// id				bigint
	POKER_DATA_TYPE,			// 类型				uint
	POKER_DATA_OWNER_ID,		// 拥有者id			uint
	POKER_DATA_LEV,				// 等级				uint
	POKER_DATA_EXP,				// 经验				bigint
	POKER_DATA_COLOR,			// 颜色				uint
	POKER_DATA_STAR,			// 星级				uint
	POKER_DATA_EQUIP1_TYPE,		// 武器类型			uint
	POKER_DATA_EQUIP1_STAR,		// 武器星级			uint
	POKER_DATA_EQUIP1_EXP,		// 武器经验			uint
	POKER_DATA_EQUIP2_TYPE,		// 头盔类型			uint
	POKER_DATA_EQUIP2_STAR,		// 头盔星级			uint
	POKER_DATA_EQUIP2_EXP,		// 头盔经验			uint
	POKER_DATA_EQUIP3_TYPE,		// 项链类型			uint
	POKER_DATA_EQUIP3_STAR,		// 项链星级			uint
	POKER_DATA_EQUIP3_EXP,		// 项链经验			uint
	POKER_DATA_EQUIP4_TYPE,		// 腰带类型			uint
	POKER_DATA_EQUIP4_STAR,		// 腰带星级			uint
	POKER_DATA_EQUIP4_EXP,		// 腰带经验			uint
	POKER_DATA_EQUIP5_TYPE,		// 衣服类型			uint
	POKER_DATA_EQUIP5_STAR,		// 衣服星级			uint
	POKER_DATA_EQUIP5_EXP,		// 衣服经验			uint
	POKER_DATA_EQUIP6_TYPE,		// 鞋子类型			uint
	POKER_DATA_EQUIP6_STAR,		// 鞋子星级			uint
	POKER_DATA_EQUIP6_EXP,		// 鞋子经验			uint
	POKER_DATA_SKILL_SP_LEV,	// 特技等级			uint
	POKER_DATA_SKILL_AUTO1_LEV,	// 自动技能1等级	uint
	POKER_DATA_SKILL_AUTO2_LEV,	// 自动技能2等级	uint
	POKER_DATA_SKILL_AUTO3_LEV,	// 自动技能3等级	uint
	POKER_DATA_SKILL_JOINT_LEV,	// 连携技能等级		uint
	POKER_DATA_STATE,			// 卡牌状态（0空闲，1守营，2挖矿）	uint
};

static const char* GAME_DB_NAME_POKER_LOG = "poker_log";	// 物品流向表
enum POKER_LOG_DATA
{
	POKER_LOG_DATA_ID = 0,		// 自增长id					bigint
	POKER_LOG_DATA_OWNERID,		// 主人id					uint
	POKER_LOG_DATA_TARGETID,	// 操作对象id				uint
	POKER_LOG_DATA_POKER_ID,	// 卡牌id					bigint
	POKER_LOG_DATA_POKER_TYPE,	// 卡牌type					uint
	POKER_LOG_DATA_POKER_COUNT,	// 卡牌数量					uint
	POKER_LOG_DATA_TYPE,		// 物品流向					uint
	POKER_LOG_DATA_CREATETIME,	// 创建时间(utc时间）		uint
	POKER_LOG_DATA_SERVERID,	// 服务器组					uint
	POKER_LOG_DATA_LINE,		// 线路						uint
	POKER_LOG_DATA_COMMENT,		// 说明字段					varchar128
};

static const char* GAME_DB_NAME_BLACK_LIST = "black_list";	// 黑名单
enum BLACK_LIST
{
	BLACK_LIST_BEG		= 0,
	BLACK_LIST_ID       = 0,		// 自增长ID			uint
	BLACK_LIST_USER_ID,				// 玩家ID			uint
	BLACK_LIST_BAD_FRIEND_ID,		// 被拉黑玩家ID		uint
	BLACK_LIST_END,
};

static const char* GAME_DB_NAME_SYNDICATE = "syndicate";	// 帮派表
enum SYNDICATE_DATA
{
	SYNDICATE_DATA_ID = 0,				// id					uint
	SYNDICATE_DATA_SERVER_GROUP,		// 服务器组				uint
	SYNDICATE_DATA_NAME,				// 帮派名				varchar32
	SYNDICATE_DATA_ANNOUNCE,			// 公告					varchar255
	SYNDICATE_DATA_LEADER_ID,			// 帮主id				uint
	SYNDICATE_DATA_LEADER_NAME,			// 帮主名				varchar32
	SYNDICATE_DATA_CREATOR_ID,			// 创建者id				uint
	SYNDICATE_DATA_CREATOR_NAME,		// 创建者名				varchar32
	SYNDICATE_DATA_CREATE_TIME,			// 创建时间				uint
	SYNDICATE_DATA_LEVEL,				// 等级					uint
	SYNDICATE_DATA_ACTIVITY,			// 活跃					bigint
	SYNDICATE_DATA_ACTIVITY0_VAULE,		// 活跃度值-统计值0		bigint
	SYNDICATE_DATA_ACTIVITY0_DATE,		// 活跃度日期-统计值0	uint
	SYNDICATE_DATA_ACTIVITY1_VAULE,		// 活跃度值-统计值1		bigint
	SYNDICATE_DATA_ACTIVITY1_DATE,		// 活跃度日期-统计值1	uint
	SYNDICATE_DATA_ACTIVITY2_VAULE,		// 活跃度值-统计值2		bigint
	SYNDICATE_DATA_ACTIVITY2_DATE,		// 活跃度日期-统计值2	uint
	SYNDICATE_DATA_JOIN_LEV_LIMIT,		// 加入等级限制			uint
	SYNDICATE_DATA_JOIN_APPLY,			// 加入申请标记			uint
	SYNDICATE_DATA_ICON,				// 公会图标				uint
	SYNDICATE_DATA_JUMP_THE_QUEUE,		// 插队标记				uint
	SYNDICATE_DATA_AWARD_SEND_TIME,		// 战利品分配时间		uint
	SYNDICATE_DATA_GIFTBOX_LEV,			// 礼盒等级				uint
	SYNDICATE_DATA_GIFTBOX_EXP,			// 礼盒经验				uint
	SYNDICATE_DATA_MONTHCARD_ID,		// 帮派月卡ID			uint
	SYNDICATE_DATA_MONTHCARD_ENDTIME,	// 帮派月卡结束时间		uint
};

static const char* GAME_DB_NAME_SYNDICATE_MEMBER = "syn_member";	// 帮派成员表
enum SYNDICATE_MEMBER_DATA
{
	SYNDICATE_MEMBER_DATA_USER_ID = 0,			// 玩家id				uint
	SYNDICATE_MEMBER_DATA_SYNDICATE_ID,			// 帮派id				uint
	SYNDICATE_MEMBER_DATA_SERVER_GROUP,			// 服务器组				uint
	SYNDICATE_MEMBER_DATA_RANK,					// 帮派职位				uint
	SYNDICATE_MEMBER_DATA_JOIN_TIME,			// 加入时间				uint
	SYNDICATE_MEMBER_DATA_ACTIVITY,				// 活跃					bigint
	SYNDICATE_MEMBER_DATA_ACTIVITY0_VALUE,		// 活跃度值-统计值0		bigint
	SYNDICATE_MEMBER_DATA_ACTIVITY0_DATE,		// 活跃度日期-统计值0	uint
	SYNDICATE_MEMBER_DATA_ACTIVITY1_VALUE,		// 活跃度值-统计值1		bigint
	SYNDICATE_MEMBER_DATA_ACTIVITY1_DATE,		// 活跃度日期-统计值1	uint
	SYNDICATE_MEMBER_DATA_ACTIVITY2_VALUE,		// 活跃度值-统计值2		bigint
	SYNDICATE_MEMBER_DATA_ACTIVITY2_DATE,		// 活跃度日期-统计值2	uint
	SYNDICATE_MEMBER_DATA_PROF,					// 帮贡					uint
	SYNDICATE_MEMBER_DATA_LEV,					// 人物等级				uint
	SYNDICATE_MEMBER_DATA_LOOKFACE,				// 头像					uint
	SYNDICATE_MEMBER_DATA_LOOKFACEFRAME,		// 头像框				uint
	SYNDICATE_MEMBER_DATA_NAME,					// 名字					varchar32
	SYNDICATE_MEMBER_DATA_LOGOUT_TIME,			// 登出时间				uint
	SYNDICATE_MEMBER_DATA_TERRITORY_MONEY,		// 累积的领地币			uint
	SYNDICATE_MEMBER_DATA_WARROAD_TEAM0_COUNT,	// 团队战役挑战次数0	uint
	SYNDICATE_MEMBER_DATA_WARROAD_TEAM1_COUNT,	// 团队战役挑战次数1	uint
	SYNDICATE_MEMBER_DATA_WARROAD_TEAM2_COUNT,	// 团队战役挑战次数2	uint
	SYNDICATE_MEMBER_DATA_END,
};

static const char* GAME_DB_NAME_SYNDICATE_MEMBER_APPLY = "syn_member_apply";	// 帮派成员申请表
enum SYNDICATE_MEMBER_APPLY_DATA
{
	SYNDICATE_MEMBER_APPLY_DATA_ID	= 0,		// 主键自增		bigint
	SYNDICATE_MEMBER_APPLY_DATA_USERID,			// 玩家id		uint
	SYNDICATE_MEMBER_APPLY_DATA_SYNID,			// 帮派id		uint
	SYNDICATE_MEMBER_APPLY_DATA_SERVER_GROUP,	// 服务器组		uint
	SYNDICATE_MEMBER_APPLY_DATA_LEV,			// 角色等级		uint
	SYNDICATE_MEMBER_APPLY_DATA_LOOKFACE,		// 角色头像		uint
	SYNDICATE_MEMBER_APPLY_DATA_LOOKFACEFRAME,	// 角色头像框	uint
	SYNDICATE_MEMBER_APPLY_DATA_NAME,			// 角色名字		varchar32
	SYNDICATE_MEMBER_APPLY_DATA_TIME,			// 申请时间		uint
};

static const char* GAME_DB_NAME_FRIEND = "friend";
enum FRIEND
{
	FRIEND_DATA_USER_ID = 0,					// 玩家id		uint
	FRIEND_DATA_FRIEND_ID,						// 好友id		uint
	FRIEND_DATA_FRIENDSHIP_POINT,				// 友好度		uint
	FRIEND_DATA_GIFT,							// 礼物状态		uint
	FRIEND_DATA_LAST_GOTTIME,					// 上次领取时间	uint
};

static const char* GAME_DB_NAME_FRIEND_REQUEST = "friend_request";
enum FRIEND_REQUEST
{
	FRIEND_REQUEST_DATA_USER_ID = 0,			// 玩家id	uint
	FRIEND_REQUEST_DATA_REQUESTER_ID,			// 请求者id uint
	FRIEND_REQUEST_DATA_REQUEST_TIME,			// 请求时间 uint
};

static const char* GAME_DB_NAME_ITEM = "item";	// 物品表
enum ITEM_DATA
{
	ITEM_DATA_ID	= 0,		// 物品id		bigint
	ITEM_DATA_TYPE,				// 物品类型		uint
	ITEM_DATA_PLAYER_ID,		// 归属者id		uint
	ITEM_DATA_AMOUNT,			// 数量			uint
	ITEM_DATA_LIFE_TIME,		// 存在时间		uint
	ITEM_DATA_END,
};

static const char* GAME_DB_NAME_SHOP_GOODS = "shop_goods"; // 商店货物表
enum SHOP_GOODS
{
	SHOP_GOODS_BEGIN= 0,
	SHOP_GOODS_ID	= 0,		// 自增长ID		uint
	SHOP_GOODS_ITEM_TYPE,		// 物品类型		uint
	SHOP_GOODS_OWNER_ID,		// 归属玩家ID	uint
	SHOP_GOODS_SHOP_TYPE,		// 归属商店		uint
	SHOP_GOODS_ITEM_INDEX,		// 物品位置		uint
	SHOP_GOODS_CUR_NUM,			// 当前剩余数量 uint
	SHOP_GOODS_MONEY_TYPE,		// 货币类型		uint
	SHOP_GOODS_PRICE,			// 物品单价		uint
	SHOP_GOODS_NUM,				// 物品数量		uint
	SHOP_GOODS_DISCOUNT,		// 物品折扣		uint
	SHOP_GOODS_END,
};


static const char* GAME_DB_NAME_USER_ACHIEVEMENT = "user_achievement";	// 玩家成就
enum USER_ACHIEVEMENT
{
	USER_ACHIEVEMENT_USERID = 0,				// 玩家id			uint
	USER_ACHIEVEMENT_CHIEVEMENTID,				// 正在进行的成就id	uint
	USER_ACHIEVEMENT_PROCESS,					// 进度				uint
	USER_ACHIEVEMENT_GOAL,						// 目标				int
};

static const char* GAME_DB_NAME_BATTLE_SAVE = "battle_save";	// 战斗存档
enum BATTLE_SAVE_DATA
{
	BATTLE_SAVE_DATA_ID = 0,			// 战斗id		bigint
	BATTLE_SAVE_DATA_TYPE,				// 战斗类型		uint
	BATTLE_SAVE_DATA_ROUND,				// 轮次			uint
	BATTLE_SAVE_DATA_MONSTER1_HP,		// 怪物1血量	uint
	BATTLE_SAVE_DATA_MONSTER1_SP,		// 怪物1愤怒	uint
	BATTLE_SAVE_DATA_MONSTER2_HP,		// 怪物2血量	uint
	BATTLE_SAVE_DATA_MONSTER2_SP,		// 怪物2愤怒	uint
	BATTLE_SAVE_DATA_MONSTER3_HP,		// 怪物3血量	uint
	BATTLE_SAVE_DATA_MONSTER3_SP,		// 怪物3愤怒	uint
	BATTLE_SAVE_DATA_MONSTER4_HP,		// 怪物4血量	uint
	BATTLE_SAVE_DATA_MONSTER4_SP,		// 怪物4愤怒	uint
	BATTLE_SAVE_DATA_MONSTER5_HP,		// 怪物5血量	uint
	BATTLE_SAVE_DATA_MONSTER5_SP,		// 怪物5愤怒	uint
};

static const char* GAME_DB_NAME_CHALLENGE_BOSS = "challenge_boss";	// 挑战boss结果表
enum CHALLENGE_BOSS
{
	CHALLENGE_BOSS_ID = 0,				// 编号						bigint
	CHALLENGE_BOSS_USER_ID,				// 玩家ID					uint
	CHALLENGE_BOSS_BOSS_TYPE,			// boss类型					uint
	CHALLENGE_BOSS_DEGREE,				// 难度						uint
	CHALLENGE_BOSS_EVALUATE,			// 挑战结果(0:失败; 1,2,3星)uint
};

static const char* GAME_DB_NAME_TOPLIST_USER_ATTR = "toplist_user_attr";	//	排名榜玩家排名表
enum TOPLIST_USER_ATTR
{
	TOPLIST_USER_ATTR_USER_ID = 0,		// 玩家id			uint
	TOPLIST_USER_ATTR_TYPE,				// 排行榜类型枚举值	uint
	TOPLIST_USER_ATTR_DATA,				// 排行使用的数据	uint
	TOPLIST_USER_ATTR_RANK,				// 本期排名			uint	
	TOPLIST_USER_ATTR_LAST_RANK,		// 上期排名			uint
	TOPLIST_USER_ATTR_SERVER_GROUP,		// 服务器组id		uint
};

static const char* GAME_DB_NAME_TOPLIST_SYNDICATE = "toplist_syndicate";	// 排行榜公会排名表
enum TOPLIST_SYNDICATE
{
	TOPLIST_SYNDICATE_ID = 0,			// 公会id			uint
	TOPLIST_SYNDICATE_TYPE,				// 排行榜类型枚举值	uint
	TOPLIST_SYNDICATE_DATA,				// 排行使用的数据	uint
	TOPLIST_SYNDICATE_SERVER_GROUP,		// 服务器组id		uint
};

static const char* GAME_DB_NAME_DELAYACTION = "delayaction";	// 延迟执行action记录表
enum DELAYACTION_DATA
{
	DELAYACTION_DATA_ID = 0,			// 编号						bigint
	DELAYACTION_DATA_ACTION_ID,			// 执行action				uint
	DELAYACTION_DATA_USER_ID,			// 玩家ID					uint
	DELAYACTION_DATA_EXECUTECOUNT,		// 执行次数					uint
	DELAYACTION_DATA_EXECUTETIME,		// 执行时间					uint
	DELAYACTION_DATA_INVALIDTIME,		// 失效时间					uint
	DELAYACTION_DATA_SERVER_GROUP,		// 服务器组					uint
	DELAYACTION_DATA_SERVER_LINE,		// 服务器线路				uint
	DELAYACTION_DATA_PARAM1,			// 参数1					uint
	DELAYACTION_DATA_PARAM2,			// 参数2					uint
	DELAYACTION_DATA_PARAM3,			// 参数3					uint
	DELAYACTION_DATA_PARAM4,			// 参数4					uint
	DELAYACTION_DATA_PARAM5,			// 参数5					uint
};


static const char* GAME_DB_NAME_GOOSE_TOWER = "goose_tower";	// 大雁塔玩家数据表
enum GOOSE_TOWER_DATA
{
	GOOSE_TOWER_DATA_ID = 0,					// id								bigint
	GOOSE_TOWER_DATA_USER_ID,					// 玩家id							uint
	GOOSE_TOWER_DATA_FLOOR,						// 层数								uint
	GOOSE_TOWER_DATA_DEF_USER_ID,				// 防守小队玩家id					uint
	GOOSE_TOWER_DATA_DEF_USER_NAME,				// 防守小队玩家名					varchar32
	GOOSE_TOWER_DATA_DEF_USER_LEV,				// 防守小队玩家等级					uint
	GOOSE_TOWER_DATA_DEF_USER_LOOKFACE,			// 防守小队玩家头像					uint
	GOOSE_TOWER_DATA_DEF_USER_LOOKFACE_FRAME,	// 防守小队玩家头像框				uint
	GOOSE_TOWER_DATA_POKER_ID1,					// 卡牌ID1							bigint
	GOOSE_TOWER_DATA_POKER_ID2,					// 卡牌ID2							bigint
	GOOSE_TOWER_DATA_POKER_ID3,					// 卡牌ID3							bigint
	GOOSE_TOWER_DATA_POKER_ID4,					// 卡牌ID4							bigint
	GOOSE_TOWER_DATA_POKER_ID5,					// 卡牌ID5							bigint
	GOOSE_TOWER_DATA_GAIN_AWARD,				// 宝箱领取标记(0:没有领取, 1:领取)	uint
	GOOSE_TOWER_DATA_BATTLE_SAVE_ID,			// 战斗保存ID						bigint
};

static const char* GAME_DB_NAME_GOOSE_FIGHT_POKER = "goose_fight_poker";	// 大雁塔历史上阵卡牌记录表
enum GOOSE_FIGHT_POKER
{
	GOOSE_FIGHT_POKER_ID = 0,			// id			uint
	GOOSE_FIGHT_POKER_USER_ID,			// 玩家id		uint
	GOOSE_FIGHT_POKER_POKER_ID,			// 阵亡卡牌ID	bigint
	GOOSE_FIGHT_POKER_HP,				// 最大血量		uint
	GOOSE_FIGHT_POKER_LEFT_HP,			// 剩余血量		uint
	GOOSE_FIGHT_POKER_SP,				// 最大愤怒		uint
	GOOSE_FIGHT_POKER_LEFT_SP,			// 剩余愤怒		uint
};

// 与poker表用同一个枚举
static const char* GAME_DB_NAME_GOOSE_DEFENSE_POKER = "goose_defense_poker";		// 大雁塔防守小队卡牌表


static const char* GAME_DB_NAME_PUZZLE_BUFF = "puzzle_buff";	// 迷宫BUFF表
enum PUZZLE_BUFF_DATA
{
	PUZZLE_BUFF_DATA_ID = 0,			// 编号						uint
	PUZZLE_BUFF_DATA_USER_ID,			// 玩家ID					uint
	PUZZLE_BUFF_DATA_BUFF_TYPE,			// BUFF类型					uint
	PUZZLE_BUFF_DATA_INS_TYPE,			// 副本类型					uint
	PUZZLE_BUFF_DATA_INS_DIFFICULE,		// 副本难度					uint
	PUZZLE_BUFF_DATA_INS_FLOOR,			// 副本层次					uint
	PUZZLE_BUFF_DATA_FIGHT_NO,			// 战斗序列号				uint
	PUZZLE_BUFF_DATA_DATE,				// 产生日期(天)				uint
};
static const char* GAME_DB_NAME_ARENA = "arena";			// 单队竞技场排名表
enum ARENA_DATA
{
	ARENA_DATA_USERID,					// 玩家id					uint
	ARENA_DATA_RANK = 0,				// 排名						uint
	ARENA_DATA_TOTALWINCOUNT,			// 总计胜场数				uint
	ARENA_SERVER_GROUP,					// 服务器组					uint
};

static const char* GAME_DB_NAME_ARENA_LOG = "arena_log";			// 竞技场战斗日志
enum ARENA_LOG_DATA
{
	ARENA_LOG_DATA_ARENA_TYPE = 0,		// 竞技场类别（1单人，2多人）	uint
	ARENA_LOG_DATA_USERID,				// 玩家id						uint
	ARENA_LOG_DATA_RESULT,				// 战斗结果						uint
	ARENA_LOG_DATA_RANKCHANGE,			// 排名变化						uint
	ARENA_LOG_DATA_TARGETID,			// 目标id						uint
	ARENA_LOG_DATA_TIME,				// 战斗时间						uint
	ARENA_LOG_DATA_VIDEO,				// 录像							varchar
	ARENA_LOG_DATA_SERVER_GROUP,		// 服务器组						uint
};

static const char* GAME_DB_NAME_ARENA_MULTI = "arena_multi";		//  多队竞技场数据
enum MULTI_ARENA_DATA
{
	MULTI_ARENA_DATA_USERID = 0,		// 玩家id						uint
	MULTI_ARENA_DATA_RANK,				// 排名							uint
	MULTI_ARENA_DATA_TOTALWINCOUNT,		// 总计胜场数					uint
	MULTI_ARENA_DATA_ARENA_MONEY,		// 累积未领取的竞技场币			uint	
	MULTI_ARENA_DATA_SERVER_GROUP,		// 服务器组						uint
};

static const char* GAME_DB_NAME_ARENA_POKER_TEAM = "arena_poker_team";	// 竞技场玩家卡牌队伍数据
enum ARENA_POKER_TEAM_DATA
{
	ARENA_POKER_TEAM_DATA_ID = 0,		// 自增长id						uint
	ARENA_POKER_TEAM_DATA_USERID ,		// 玩家id						uint
	ARENA_POKER_TEAM_DATA_TEAMTYPE,		// 队伍类型						uint
	ARENA_POKER_TEAM_DATA_POKERID1,		// 1号卡牌id					uint
	ARENA_POKER_TEAM_DATA_POKERID2,		// 2号卡牌id					uint
	ARENA_POKER_TEAM_DATA_POKERID3,		// 3号卡牌id					uint
	ARENA_POKER_TEAM_DATA_POKERID4,		// 4号卡牌id					uint
	ARENA_POKER_TEAM_DATA_POKERID5,		// 5号卡牌id					uint
	ARENA_POKER_TEAM_DATA_TOTAL_FC,		// 队伍总战斗力					uint
	ARENA_POKER_TEAM_DATA_END,
};

static const char* GAME_DB_NAME_ARENA_AI = "arena_ai";	// 竞技场机器人表
enum ARENA_AI_DATA
{
	ARENA_AI_DATA_ID = 0,				// id		uint
	ARENA_AI_DATA_NAME,					// 名字		varchar
	ARENA_AI_DATA_SERVER_GROUP,			// 服务器组	uint
};

static const char* GAME_DB_NAME_SYN_LOG	= "syn_log";	// 帮派日志表
enum SYN_LOG_DATA
{
	SYN_LOG_DATA_ID = 0,			// ID				bigint
	SYN_LOG_DATA_SYN_ID,			// 帮派ID   		uint
	SYN_LOG_DATA_TYPE,				// 日志类型 		uint
	SYN_LOG_DATA_CREATE_USER_ID,	// 日志产生者ID		uint
	SYN_LOG_DATA_CREATE_TIME,		// 日志产生时间		uint
	SYN_LOG_DATA_CONTENT,			// 日志内容			varchar256
};

static const char* GAME_DB_NAME_MINE	= "mine";	// 矿洞表
enum MINE_DATA
{
	MINE_DATA_ID	= 0,				// 矿洞ID						uint
	MINE_DATA_OWNER_ID,					// 矿主ID						uint
	MINE_DATA_TYPE,						// 矿类型						uint
	MINE_DATA_SCALE,					// 矿规模						uint
	MINE_DATA_CREATE_TIME,				// 创建时间						uint
	MINE_DATA_IS_END,					// 是否结束						uint
	MINE_DATA_BE_ATK_COUNT,				// 被攻击次数					uint
	MINE_DATA_SERVER_GROUP,				// 服务器组						uint
};

static const char* GAME_DB_NAME_MINE_MEMBER = "mine_member"; // 矿洞成员表
enum MINE_MEMBER_DATA
{
	MINE_MEMBER_DATA_ID		= 0,		// 自增长ID						bigint
	MINE_MEMBER_DATA_USER_ID,			// 玩家ID						uint
	MINE_MEMBER_DATA_MINE_ID,			// 矿洞ID						uint
	MINE_MEMBER_DATA_LEV,				// 等级							uint
	MINE_MEMBER_DATA_LOOK_FACE,			// 头像							uint
	MINE_MEMBER_DATA_LOOK_FACE_FRAME,	// 头像框						uint
	MINE_MEMBER_DATA_NAME,				// 角色名						varchar32
	MINE_MEMBER_DATA_POKER1,			// 出战卡1						bigint
	MINE_MEMBER_DATA_POKER2,			// 出战卡2						bigint
	MINE_MEMBER_DATA_POKER3,			// 出战卡3						bigint
	MINE_MEMBER_DATA_POKER4,			// 出战卡4						bigint
	MINE_MEMBER_DATA_POKER5,			// 出战卡5						bigint
	MINE_MEMBER_DATA_JOIN_TIME,			// 加入时间						uint
	MINE_MEMBER_DATA_SPEED,				// 当前开采速度(/小时)			uint
	MINE_MEMBER_DATA_BEGIN_TIME,		// 当前卡牌开始采集时间			uint
	MINE_MEMBER_DATA_RESOURCE_OLD,		// 换卡牌前累计资源				uint
	MINE_MEMBER_DATA_RESOURCE_TOTAL,	// 资源累计						uint
	MINE_MEMBER_DATA_RESOURCE_LOSE,		// 资源丢失						uint
	MINE_MEMBER_DATA_VAS_TOTAL,			// 钻石累计						uint
	MINE_MEMBER_DATA_IS_POKER_RESET,	// 卡牌是否重置					uint
	MINE_MEMBER_DATA_SERVER_GROUP,		// 服务器组						uint
};
static const char* GAME_DB_NAME_MERCENARY_POKER = "mercenary_poker";	// 佣兵卡牌表 *新增一个字段外其余与poker表枚举相同
enum MERCENARY_POKER_DATA
{
	MERCENARY_POKER_DATA_SERVER_GROUP = POKER_DATA_SKILL_JOINT_LEV + 1,	// 服务器组					uint
};

static const char* GAME_DB_NAME_MERCENARY_CAMP = "mercenary_camp";		// 佣兵营表
enum MERCENARY_CAMP_DATA
{
	MERCENARY_CAMP_DATA_MERCENARY_ID,	// 佣兵ID					bigint
	MERCENARY_CAMP_DATA_OWNER_ID,		// 佣兵主人ID				uint
	MERCENARY_CAMP_DATA_EMPLOY_COUNT,	// 被雇佣次数				uint
	MERCENARY_CAMP_DATA_ENTER_TIME,		// 派遣时间					uint
	MERCENARY_CAMP_DATA_SYNDICATE_ID,	// 帮派ID					uint
	MERCENARY_CAMP_DATA_SERVER_GROUP,	// 服务器组					uint
	MERCENARY_CAMP_DATA_MERCENARY_SCORE,// 佣兵战斗力				uint
};

static const char* GAME_DB_NAME_MERCENARY_FIGHT = "mercenary_fight";	// 佣兵战斗记录表
enum MERCENARY_FIGHT_DATA
{
	MERCENARY_FIGHT_DATA_ID,						// ID					bigint
	MERCENARY_FIGHT_DATA_USER_ID,					// 玩家ID				uint
	MERCENARY_FIGHT_DATA_MERCENARY_ID,				// 佣兵ID				bigint
	MERCENARY_FIGHT_DATA_MERCENARY_TYPE,			// 佣兵类型				uint
	MERCENARY_FIGHT_DATA_MERCENARY_OWNER_ID,		// 佣兵主人id			uint
	MERCENARY_FIGHT_DATA_MERCENARY_LEV,				// 佣兵等级				uint
	MERCENARY_FIGHT_DATA_MERCENARY_EXP,				// 佣兵经验				bigint
	MERCENARY_FIGHT_DATA_MERCENARY_COLOR,			// 佣兵颜色				uint
	MERCENARY_FIGHT_DATA_MERCENARY_STAR,			// 佣兵星级				uint
	MERCENARY_FIGHT_DATA_MERCENARY_EQUIP1_TYPE,		// 佣兵武器类型			uint
	MERCENARY_FIGHT_DATA_MERCENARY_EQUIP1_STAR,		// 佣兵武器星级			uint
	MERCENARY_FIGHT_DATA_MERCENARY_EQUIP1_EXP,		// 佣兵武器经验			uint
	MERCENARY_FIGHT_DATA_MERCENARY_EQUIP2_TYPE,		// 佣兵头盔类型			uint
	MERCENARY_FIGHT_DATA_MERCENARY_EQUIP2_STAR,		// 佣兵头盔星级			uint
	MERCENARY_FIGHT_DATA_MERCENARY_EQUIP2_EXP,		// 佣兵头盔经验			uint
	MERCENARY_FIGHT_DATA_MERCENARY_EQUIP3_TYPE,		// 佣兵项链类型			uint
	MERCENARY_FIGHT_DATA_MERCENARY_EQUIP3_STAR,		// 佣兵项链星级			uint
	MERCENARY_FIGHT_DATA_MERCENARY_EQUIP3_EXP,		// 佣兵项链经验			uint
	MERCENARY_FIGHT_DATA_MERCENARY_EQUIP4_TYPE,		// 佣兵腰带类型			uint
	MERCENARY_FIGHT_DATA_MERCENARY_EQUIP4_STAR,		// 佣兵腰带星级			uint
	MERCENARY_FIGHT_DATA_MERCENARY_EQUIP4_EXP,		// 佣兵腰带经验			uint
	MERCENARY_FIGHT_DATA_MERCENARY_EQUIP5_TYPE,		// 佣兵衣服类型			uint
	MERCENARY_FIGHT_DATA_MERCENARY_EQUIP5_STAR,		// 佣兵衣服星级			uint
	MERCENARY_FIGHT_DATA_MERCENARY_EQUIP5_EXP,		// 佣兵衣服经验			uint
	MERCENARY_FIGHT_DATA_MERCENARY_EQUIP6_TYPE,		// 佣兵鞋子类型			uint
	MERCENARY_FIGHT_DATA_MERCENARY_EQUIP6_STAR,		// 佣兵鞋子星级			uint
	MERCENARY_FIGHT_DATA_MERCENARY_EQUIP6_EXP,		// 佣兵鞋子经验			uint
	MERCENARY_FIGHT_DATA_MERCENARY_SKILL_SP_LEV,	// 佣兵特技等级			uint
	MERCENARY_FIGHT_DATA_MERCENARY_SKILL_AUTO1_LEV,	// 佣兵自动技能1等级	uint
	MERCENARY_FIGHT_DATA_MERCENARY_SKILL_AUTO2_LEV,	// 佣兵自动技能2等级	uint
	MERCENARY_FIGHT_DATA_MERCENARY_SKILL_AUTO3_LEV,	// 佣兵自动技能3等级	uint
	MERCENARY_FIGHT_DATA_MERCENARY_SKILL_JOINT_LEV,	// 佣兵连携技能等级		uint
	MERCENARY_FIGHT_DATA_MERCENARY_SCORE,			// 佣兵战力				uint
	MERCENARY_FIGHT_DATA_EMPLOY_TYPE,				// 雇佣类型				uint
	MERCENARY_FIGHT_DATA_EMPLOY_TIME,				// 雇佣时间				uint
	MERCENARY_FIGHT_DATA_EMPLOY_STATE,				// 雇佣状态(1正在使用，2保存，3冷却)	uint
};

static const char* GAME_DB_NAME_MINE_LOG = "mine_log";					// 矿洞日志表
enum MINE_LOG_DATA
{
	MINE_LOG_DATA_ID = 0,				// 自增长ID					uint
	MINE_LOG_DATA_MINE_ID,				// 矿洞ID					uint
	MINE_LOG_DATA_MINE_TYPE,			// 矿洞类型					uint
	MINE_LOG_DATA_MINE_SCALE,			// 矿洞规模					uint
	MINE_LOG_DATA_DEF_ID,				// 防守者ID					uint
	MINE_LOG_DATA_DEF_NAME,				// 防守者名字				varchar32
	MINE_LOG_DATA_DEF_LEV,				// 防守者等级				uint
	MINE_LOG_DATA_DEF_LOOKFACE,			// 防守者头像				uint
	MINE_LOG_DATA_DEF_LOOKFACE_FRAME,	// 防守者头像框				uint
	MINE_LOG_DATA_ATK_ID,				// 攻击者ID					uint
	MINE_LOG_DATA_ATK_NAME,				// 攻击者名字				varchar32
	MINE_LOG_DATA_ATK_LEV,				// 攻击者等级				uint
	MINE_LOG_DATA_ATK_LOOKFACE,			// 攻击者头像				uint
	MINE_LOG_DATA_ATK_LOOKFACE_FRAME,	// 攻击者头像框				uint
	MINE_LOG_DATA_BEGIN_TIME,			// 掠夺开始时间				uint
	MINE_LOG_DATA_END_TIME,				// 掠夺结束时间				uint
	MINE_LOG_DATA_VAS_LOST,				// 获取的钻石				uint
	MINE_LOG_DATA_RES_LOST,				// 获取的资源				uint
	MINE_LOG_DATA_POWER_AWARD,			// 专用体力奖励				uint
	MINE_LOG_DATA_DEF_RESULT,			// 防守结果(0:失败；1:胜利)	uint
	MINE_LOG_DATA_SERVER_GROUP,			// 服务器组					uint
	MINE_LOG_DATA_BE_ATK_COUNT,			// 被攻击次数				uint
};

static const char* GAME_DB_NAME_MINE_LOG_BATTLE = "mine_log_battle";	// 矿洞日志战斗表
enum MINE_LOG_BATTLE_DATA
{
	MINE_LOG_BATTLE_DATA_ID = 0,		// 战斗ID				bigint				
	MINE_LOG_BATTLE_LOG_ID,				// 日志ID				bigint	
	MINE_LOG_BATTLE_DEF_POKER1,			// 防守方卡牌1			bigint				
	MINE_LOG_BATTLE_DEF_POKER2,			// 						bigint				
	MINE_LOG_BATTLE_DEF_POKER3,			// 						bigint				
	MINE_LOG_BATTLE_DEF_POKER4,			// 						bigint				
	MINE_LOG_BATTLE_DEF_POKER5,			// 						bigint

	MINE_LOG_BATTLE_DEF_RESULT,			// 防守结果(0:输, 1:赢)	uint

	MINE_LOG_BATTLE_ATK_POKER1,			// 攻击方卡牌1			bigint				
	MINE_LOG_BATTLE_ATK_POKER2,			// 						bigint				
	MINE_LOG_BATTLE_ATK_POKER3,			// 						bigint				
	MINE_LOG_BATTLE_ATK_POKER4,			// 						bigint				
	MINE_LOG_BATTLE_ATK_POKER5,			// 						bigint
	MINE_LOG_BATTLE_VIDEO_ID,			// 录像地址				varchar64				
};

static const char* GAME_DB_NAME_MINE_LOG_POKER = "mine_log_poker";	// 矿洞日志出战卡牌表
enum MINE_LOG_POKER_DATA
{
	MINE_LOG_POKER_DATA_ID = 0,			// ID					bigint
	MINE_LOG_POKER_DATA_BATTLE_ID,		// 战斗ID				bigint
	MINE_LOG_POKER_DATA_TYPE,			// 类型					uint
	MINE_LOG_POKER_DATA_LEV,			// 等级					uint
	MINE_LOG_POKER_DATA_STAR,			// 星级					uint
	MINE_LOG_POKER_DATA_COLOR,			// 颜色					uint
	MINE_LOG_POKER_DATA_HP,				// 最大血量				uint
	MINE_LOG_POKER_DATA_LEFT_HP,		// 剩余血量				uint
	MINE_LOG_POKER_DATA_SP,				// 最大愤怒				uint
	MINE_LOG_POKER_DATA_LEFT_SP,		// 剩余愤怒				uint
};


static const char* GAME_DB_NAME_TERRITORY = "territory";				// 领地表
enum TERRITORY_DATA
{
	TERRITORY_DATA_INDEX = 0,			// primary				uint
	TERRITORY_DATA_ID,					// 领地id				uint
	TERRITORY_DATA_OCCUPIER,			// 占领公会id			uint
	TERRITORY_DATA_OCCUPY_TIME,			// 占领时间YYMMDD		uint
	TERRITORY_DATA_OCCUPY_COST,			// 占领耗时				uint
	TERRITORY_DATA_FIRST_OCCUPIER,		// 首占公会id			uint
	TERRITORY_DATA_FIRST_TIME,			// 首战时间YYMMDD		uint
	TERRITORY_DATA_FIRST_COST,			// 首战耗时				uint
	TERRITORY_DATA_FAST_OCCUPIER,		// 最快公会id			uint
	TERRITORY_DATA_FAST_TIME,			// 最快公会时间YYMMDD	uint
	TERRITORY_DATA_FAST_COST,			// 最快占领公会耗时		uint
	TERRITORY_DATA_SERVER_GROUP,		// 服务器组				uint
};

static const char* GAME_DB_NAME_TERRITORY_MEMBER_TROOPS = "territory_member_troops";		// 领地公会玩家部队表
enum TERRITORY_MEMBER_TROOPS_DATA
{
	TERRITORY_MEMBER_TROOPS_DATA_ID,				// 部队id				uint
	TERRITORY_MEMBER_TROOPS_DATA_TERRITORY_ID,		// 领地id				uint
	TERRITORY_MEMBER_TROOPS_DATA_CAMP,				// 阵营					uint
	TERRITORY_MEMBER_TROOPS_DATA_SYNDICATE_ID,		// 所属公会id			uint
	TERRITORY_MEMBER_TROOPS_DATA_USER_ID,			// 所属玩家id			uint
	TERRITORY_MEMBER_TROOPS_DATA_POKER_COUNT,		// 当前部队实际卡牌数	uint
	TERRITORY_MEMBER_TROOPS_DATA_FIGHTINGCAPACITY,	// 当前部队总战斗力		uint
	TERRITORY_MEMBER_TROOPS_DATA_POKER1_ID,			// 队伍卡牌1id			uint
	TERRITORY_MEMBER_TROOPS_DATA_POKER2_ID,			// 队伍卡牌2id			uint
	TERRITORY_MEMBER_TROOPS_DATA_POKER3_ID,			// 队伍卡牌3id			uint
	TERRITORY_MEMBER_TROOPS_DATA_POKER4_ID,			// 队伍卡牌4id			uint
	TERRITORY_MEMBER_TROOPS_DATA_POKER5_ID,			// 队伍卡牌5id			uint
	TERRITORY_MEMBER_TROOPS_DATA_SERVER_GROUP,		// 服务器组				uint
};

static const char* GAME_DB_NAME_TERRITORY_FIGHT_STATISTICS = "territory_fight_statistics";		// 领地战战斗统计表
enum TERRITORY_FIGHT_STATISTICS
{
	TERRITORY_FIGHT_STATISTICS_DATA_INDEX = 0,			// INDEX				uint
	TERRITORY_FIGHT_STATISTICS_DATA_ID,					// 领地id				uint
	TERRITORY_FIGHT_STATISTICS_DATA_ATK_SYN_ID,			// 进攻公会id			uint
	TERRITORY_FIGHT_STATISTICS_DATA_DEF_SYN_ID,			// 防守公会id			uint
	TERRITORY_FIGHT_STATISTICS_DATA_TOTAL_FIGHTED_TIMES,// 总战斗时间			uint
	TERRITORY_FIGHT_STATISTICS_DATA_SERVER_GROUP,		// 服务器组				uint
};

static const char* GAME_DB_NAME_TERRITORY_FIGHT_LOG		= "territory_fight_log";				// 领地战战斗日志表
enum TERRITORY_FIGHT_LOG
{
	TERRITORY_FIGHT_LOG_DATA_INDEX = 0,					// INDEX							uint
	TERRITORY_FIGHT_LOG_DATA_TERRITORY_ID,				// 领地id							uint
	TERRITORY_FIGHT_LOG_DATA_ATK_TROOPS_ID,				// 进攻部队id						I64
	TERRITORY_FIGHT_LOG_DATA_ATK_USER_ID,				// 进攻部队玩家id					uint
	TERRITORY_FIGHT_LOG_DATA_ATK_SYN_ID,				// 进攻部队公会id					uint
	TERRITORY_FIGHT_LOG_DATA_DEF_TROOPS_ID,				// 防守部队id						I64
	TERRITORY_FIGHT_LOG_DATA_DEF_USER_ID,				// 防守部队玩家id					uint
	TERRITORY_FIGHT_LOG_DATA_DEF_SYN_ID,				// 防守部队公会id					uint
	TERRITORY_FIGHT_LOG_DATA_TIME,						// 相对领地战开始的时间（单位秒）	uint
	TERRITORY_FIGHT_LOG_DATA_RESULT,					// 胜负（0防守胜利，1进攻胜利）		uint
	TERRITORY_FIGHT_LOG_DATA_DATE,						// 战斗日期							uint
	TERRITORY_FIGHT_LOG_DATA_VIDEO,						// 录像								varchar128
	TERRITORY_FIGHT_LOG_DATA_SERVER_GROUP,				// 服务器组							uint
};

static const char* GAME_DB_NAME_TERRITORY_FIGHT_TROOPS = "territory_fight_troops";				// 领地战已参战部队状态表
enum TERRITORY_FIGHT_TROOPS
{
	TERRITORY_FIGHT_TROOPS_DATA_INDEX = 0,				// INDEX							uint
	TERRITORY_FIGHT_TROOPS_DATA_TERRITORY_ID,			// 领地id							uint
	TERRITORY_FIGHT_TROOPS_DATA_TROOPS_ID,				// 部队id							I64
	TERRITORY_FIGHT_TROOPS_DATA_SYN_ID,					// 部队所属公会id					uint
	TERRITORY_FIGHT_TROOPS_DATA_OPPONENT_SYN_ID,		// 对手所属公会id					uint
	TERRITORY_FIGHT_TROOPS_DATA_STATUS,					// 状态（0阵亡，1获胜）				uint
	TERRITORY_FIGHT_TROOPS_DATA_POKER1_HP,				// 卡牌1当前血量					uint
	TERRITORY_FIGHT_TROOPS_DATA_POKER1_SP,				// 卡牌1当前愤怒					uint
	TERRITORY_FIGHT_TROOPS_DATA_POKER2_HP,				// 卡牌2当前血量					uint
	TERRITORY_FIGHT_TROOPS_DATA_POKER2_SP,				// 卡牌2当前愤怒					uint
	TERRITORY_FIGHT_TROOPS_DATA_POKER3_HP,				// 卡牌3当前血量					uint
	TERRITORY_FIGHT_TROOPS_DATA_POKER3_SP,				// 卡牌3当前愤怒					uint
	TERRITORY_FIGHT_TROOPS_DATA_POKER4_HP,				// 卡牌4当前血量					uint
	TERRITORY_FIGHT_TROOPS_DATA_POKER4_SP,				// 卡牌4当前愤怒					uint
	TERRITORY_FIGHT_TROOPS_DATA_POKER5_HP,				// 卡牌5当前血量					uint
	TERRITORY_FIGHT_TROOPS_DATA_POKER5_SP,				// 卡牌5当前愤怒					uint
};

static const char* GAME_DB_NAME_USER_WAR_ROAD	= "user_war_road";			// 玩家战役记录表
enum USER_WAR_ROAD_DATA
{
	USER_WAR_ROAD_DATA_ID,					// id						bigint
	USER_WAR_ROAD_DATA_USER_ID,				// 玩家ID					uint
	USER_WAR_ROAD_DATA_MODE,				// 模式						int
	USER_WAR_ROAD_DATA_CHAPTER,				// 章节						int
	USER_WAR_ROAD_DATA_PASS,				// 关卡						int
	USER_WAR_ROAD_DATA_STAR,				// 星级						uint
	USER_WAR_ROAD_DATA_DAY_FIGHT_COUNT,		// 每日战斗次数				uint
	USER_WAR_ROAD_DATA_DAY_RESET_COUNT,		// 每日重置次数				uint
	USER_WAR_ROAD_DATA_RECORD_TIME,			// 记录日期					uint
};

static const char* GAME_DB_NAME_WAR_ROAD_FIGHT	= "war_road_fight";			// 战役战斗记录表
enum WAR_ROAD_FIGHT_DATA
{
	WAR_ROAD_FIGHT_DATA_ID = 0,				// 自增长ID					uint
	WAR_ROAD_FIGHT_DATA_WAR_KEY,			// 战役key（模式*1000000+章节*1000+关卡）	bigint
	WAR_ROAD_FIGHT_DATA_RECORD_TIME,		// 记录时间					uint
	WAR_ROAD_FIGHT_DATA_REPLYADDRESS,		// 录像地址					varchar
	WAR_ROAD_FIGHT_DATA_SERVER_GROUP,		// 服务器组					uint
};

static const char* GAME_DB_NAME_WAR_ROAD_TEAM_LOG	= "war_road_team_log";	// 团队战役记录表
enum WAR_ROAD_TEAM_LOG_DATA
{
	WAR_ROAD_TEAM_LOG_DATA_ID = 0,			// 自增长id					bigint
	WAR_ROAD_TEAM_LOG_DATA_SYNDICATE_ID,	// 帮派ID					uint
	WAR_ROAD_TEAM_LOG_DATA_CHAPTER,			// 章节						uint
	WAR_ROAD_TEAM_LOG_DATA_SERVER_GROUP,	// 服务器组					uint
	WAR_ROAD_TEAM_LOG_DATA_OPEN_TIME,		// 开启时间					uint
	WAR_ROAD_TEAM_LOG_DATA_COMPLETE,		// 是否完成过				uint
	WAR_ROAD_TEAM_LOG_DATA_COMPLETE_TIME,	// 完成时间					uint
	WAR_ROAD_TEAM_LOG_DATA_CHAPTER_DPS,		// 章节伤害量				bigint
	WAR_ROAD_TEAM_LOG_DATA_CHAPTER_PROGRESS,// 章节进度（章节伤害量/章节怪物总血量） uint
	WAR_ROAD_TEAM_LOG_DATA_PASS_FIGHT,		// 战斗关卡					uint
	WAR_ROAD_TEAM_LOG_DATA_ROUND_FIGHT,		// 战斗波数					uint
	WAR_ROAD_TEAM_LOG_DATA_MONSTER1_LEFTHP,	// 怪物1剩余血量比率(%)		uint
	WAR_ROAD_TEAM_LOG_DATA_MONSTER2_LEFTHP,	// 怪物2剩余血量比率(%)		uint
	WAR_ROAD_TEAM_LOG_DATA_MONSTER3_LEFTHP,	// 怪物3剩余血量比率(%)		uint
	WAR_ROAD_TEAM_LOG_DATA_MONSTER4_LEFTHP,	// 怪物4剩余血量比率(%)		uint
	WAR_ROAD_TEAM_LOG_DATA_MONSTER5_LEFTHP,	// 怪物5剩余血量比率(%)		uint
	WAR_ROAD_TEAM_LOG_DATA_PASS_DPS,		// 关卡伤害量				bigint
	WAR_ROAD_TEAM_LOG_DATA_PASS_PROGRESS,	// 关卡进度（关卡伤害量/关卡怪物总血量） uint
	WAR_ROAD_TEAM_LOG_DATA_USER_ID,			// 挑战玩家ID				uint
	WAR_ROAD_TEAM_LOG_DATA_FIGHT_STATUS,	// 挑战状态（1准备，2战斗）	uint
	WAR_ROAD_TEAM_LOG_DATA_FIGHT_TIME,		// 挑战时间（准备，战斗）	uint
};

static const char* GAME_DB_NAME_WAR_ROAD_TEAM_AWARD	= "war_road_team_award";// 团队战役战利品申请记录表
enum WAR_ROAD_TEAM_AWARD_DATA
{
	WAR_ROAD_TEAM_AWARD_DATA_ID = 0,		// 自增长id					bigint
	WAR_ROAD_TEAM_AWARD_DATA_SYNDICATE_ID,	// 帮派ID					uint
	WAR_ROAD_TEAM_AWARD_DATA_CHAPTER,		// 章节						uint
	WAR_ROAD_TEAM_AWARD_DATA_AWARD_TYPE,	// 战利品类型				uint
	WAR_ROAD_TEAM_AWARD_DATA_USER_ID,		// 申请玩家ID				uint
	WAR_ROAD_TEAM_AWARD_DATA_APPLY_TIME,	// 申请时间					uint
	WAR_ROAD_TEAM_AWARD_DATA_CUT_TIME,		// 插队时间					uint
	WAR_ROAD_TEAM_AWARD_DATA_SERVER_GROUP,	// 服务器组					uint
};

static const char* GAME_DB_NAME_WAR_ROAD_TEAM_AWARD_HISTORY	= "war_road_team_award_history";// 团队战役战利品历史记录表
enum WAR_ROAD_TEAM_AWARD_HISTORY_DATA
{
	WAR_ROAD_TEAM_AWARD_HISTORY_DATA_ID = 0,		// 自增长id					bigint
	WAR_ROAD_TEAM_AWARD_HISTORY_DATA_SYNDICATE_ID,	// 帮派ID					uint
	WAR_ROAD_TEAM_AWARD_HISTORY_DATA_CHAPTER,		// 章节						uint
	WAR_ROAD_TEAM_AWARD_HISTORY_DATA_AWARD_TYPE,	// 战利品类型				uint
	WAR_ROAD_TEAM_AWARD_HISTORY_DATA_AWARD_NUM,		// 战利品数量				uint
	WAR_ROAD_TEAM_AWARD_HISTORY_DATA_USER_ID,		// 获得玩家ID				uint
	WAR_ROAD_TEAM_AWARD_HISTORY_DATA_GIVE_TIME,		// 获得时间（未分配的记录表示下次自动分配时间）				uint
	WAR_ROAD_TEAM_AWARD_HISTORY_DATA_SENDER_ID,		// 分配者ID					uint
	WAR_ROAD_TEAM_AWARD_HISTORY_DATA_SERVER_GROUP,	// 服务器组					uint
};

static const char* GAME_DB_NAME_WAR_ROAD_TEAM_DPS	= "war_road_team_dps";	// 团队战役伤害记录表
enum WAR_ROAD_TEAM_DPS_DATA
{
	WAR_ROAD_TEAM_DPS_DATA_ID = 0,			// 自增长id					bigint
	WAR_ROAD_TEAM_DPS_DATA_LOG_ID,			// log_id					bigint
	WAR_ROAD_TEAM_DPS_DATA_USER_ID,			// 玩家ID					uint
	WAR_ROAD_TEAM_DPS_DATA_DPS_VALUE,		// dps伤害值				uint
	WAR_ROAD_TEAM_DPS_DATA_SERVER_GROUP,	// 服务器组					uint
};

static const char* GAME_DB_NAME_WAR_ROAD_TEAM_DPS_HISTORY = "war_road_team_dps_history";	// 团队战役伤害记录表
enum WAR_ROAD_TEAM_DPS_HISTORY_DATA
{
	WAR_ROAD_TEAM_DPS_HISTORY_DATA_ID = 0,				// 自增长id					bigint
	WAR_ROAD_TEAM_DPS_HISTORY_DATA_CHAPTER,				// 章节						uint
	WAR_ROAD_TEAM_DPS_HISTORY_DATA_USER_ID,				// 玩家ID(保留玩家最高一次输出记录)		uint
	WAR_ROAD_TEAM_DPS_HISTORY_DATA_SERVER_GROUP,		// 服务器组					uint
	WAR_ROAD_TEAM_DPS_HISTORY_DATA_DPS_VALUE,			// dps伤害值				uint
	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER1_TYPE,			// 出战卡牌类型1			uint
	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER1_LEV,			// 出战卡牌等级1			uint
	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER1_STAR,			// 出战卡牌星级1			uint
	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER1_COLOR,		// 出战卡牌颜色1			uint
	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER2_TYPE,			// 出战卡牌类型2			uint
	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER2_LEV,			// 出战卡牌等级2			uint
	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER2_STAR,			// 出战卡牌星级2			uint
	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER2_COLOR,		// 出战卡牌颜色2			uint
	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER3_TYPE,			// 出战卡牌类型3			uint
	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER3_LEV,			// 出战卡牌等级3			uint
	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER3_STAR,			// 出战卡牌星级3			uint
	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER3_COLOR,		// 出战卡牌颜色3			uint
	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER4_TYPE,			// 出战卡牌类型4			uint
	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER4_LEV,			// 出战卡牌等级4			uint
	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER4_STAR,			// 出战卡牌星级4			uint
	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER4_COLOR,		// 出战卡牌颜色4			uint
	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER5_TYPE,			// 出战卡牌类型5			uint
	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER5_LEV,			// 出战卡牌等级5			uint
	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER5_STAR,			// 出战卡牌星级5			uint
	WAR_ROAD_TEAM_DPS_HISTORY_DATA_POKER5_COLOR,		// 出战卡牌颜色5			uint
};

static const char* GAME_DB_NAME_GAME_HISTORY_COMPLETE	= "game_history_complete";	// 成绩达成历史记录表
enum GAME_HISTORY_COMPLETE_DATA
{
	GAME_HISTORY_COMPLETE_DATA_ID	= 0,				// 自增长id					bigint
	GAME_HISTORY_COMPLETE_DATA_SERVER_GROUP,			// 服务器组					uint
	GAME_HISTORY_COMPLETE_DATA_TYPE,					// 达成类型					uint
	GAME_HISTORY_COMPLETE_DATA_RECORD_ID,				// 记录ID					uint
	GAME_HISTORY_COMPLETE_DATA_CREATE_TIME,				// 创建时间					uint
	GAME_HISTORY_COMPLETE_DATA_PARAM1,					// 参数1					uint
	GAME_HISTORY_COMPLETE_DATA_PARAM2,					// 参数2					uint
	GAME_HISTORY_COMPLETE_DATA_PARAM3,					// 参数3					uint
};

static const char* GAME_DB_NAME_SYN_WORSHIP = "syn_worship";	// 帮派膜拜记录表
enum SYN_WORSHIP_DATA
{
	SYN_WORSHIP_DATA_ID = 0,					// ID				bigint
	SYN_WORSHIP_DATA_USER_ID,					// 玩家ID			uint
	SYN_WORSHIP_DATA_BEWORSHIP_ID,				// 被膜拜玩家ID		uint
	SYN_WORSHIP_DATA_TIME,						// 膜拜日期			uint
};

static const char* GAME_DB_NAME_SYN_WORSHIP_AWARD = "syn_worship_award";	// 帮派膜拜奖励表
enum SYN_WORSHIP_AWARD_DATA
{
	SYN_WORSHIP_AWARD_ID = 0,					// ID				bigint
	SYN_WORSHIP_AWARD_USER_ID,					// 玩家ID			uint
	SYN_WORSHIP_AWARD_AWARD_TYPE,				// 奖励类型			uint
	SYN_WORSHIP_AWARD_AWARD_TOTAL,				// 奖励累计和		uint
	SYN_WORSHIP_AWARD_SERVER_GROUP,				// 服务器组			uint
};

static const char* GAME_DB_NAME_MINE_FIGHT_POKER = "mine_fight_poker";	// 矿洞战斗卡牌表
enum MINE_FIGHT_POKER
{
	MINE_FIGHT_POKER_ID = 0,			// ID				uint
	MINE_FIGHT_POKER_ATK_USER_ID,		// 攻击方玩家ID		uint
	MINE_FIGHT_POKER_DEF_USER_ID,		// 防守方玩家ID		uint
	MINE_FIGHT_POKER_POKER_ID,			// 卡牌ID			bigint
	MINE_FIGHT_POKER_LEFT_HP,			// 剩余血量			uint
	MINE_FIGHT_POKER_LEFT_SP,			// 剩余怒气			uint
	MINE_FIGHT_POKER_POKER_CAMP,		// 卡牌归属			uint
};

static const char* GAME_DB_NAME_FRIEND_INVITE = "friend_invite";			//  好友邀请表
enum FRIEND_INVITE
{
	FRIEND_INVITE_ID = 0,				// ID				bigint
	FRIEND_INVITE_INVITER_ID,			// 邀请者ID			uint
	FRIEND_INVITE_BE_INVITER_ID,		// 被邀请者ID		uint
	FRIEND_INVITE_VAS,					// 累计元宝			uint
	FRIEND_INVITE_SERVER_GROUP,			// 服务器组			uint
};

static const char* GAME_DB_NAME_FRIEND_INVITE_CODE = "friend_invite_code";	//  好友邀请码表
enum FRIEND_INVITE_CODE
{
	FRIEND_INVITE_CODE_USER_ID,				// 玩家ID			uint
	FRIEND_INVITE_CODE_CODE,				// 邀请码			varchar16
};

static const char* GAME_DB_NAME_TALK_WORLD = "talk_world";	// 世界聊天表
enum TALK_WORLD_DATA
{
	TALK_WORLD_DATA_ID = 0,								// 自增长ID				bigint
	TALK_WORLD_DATA_SENDER_ID,							// 发送者ID				uint
	TALK_WORLD_DATA_SENDER_NAME,						// 发送者角色名			varchar32
	TALK_WORLD_DATA_SENDER_FACE,						// 发送者头像			uint
	TALK_WORLD_DATA_SENDER_LEV,							// 发送者等级			uint
	TALK_WORLD_DATA_TEXT,								// 发送内容				varchar256
	TALK_WORLD_DATA_TIME,								// 发送时间				uint
	TALK_WORLD_DATA_TYPE,								// 类型					uint
	TALK_WORLD_DATA_PARAM1,								// 预留1				uint
	TALK_WORLD_DATA_PARAM2,								// 预留2				uint
	TALK_WORLD_DATA_PARAM3,								// 预留3				uint
	TALK_WORLD_DATA_PARAM4,								// 预留4				uint
	TALK_WORLD_DATA_SERVER_GROUP,						// 服务器组				uint
};

static const char* GAME_DB_NAME_TALK_SYN = "talk_syn";	// 帮派聊天表
enum TALK_SYN_DATA
{
	TALK_SYN_DATA_ID = 0,								// 自增长ID				bigint
	TALK_SYN_DATA_SYN_ID,								// 帮派ID				bigint
	TALK_SYN_DATA_SENDER_ID,							// 发送者ID				uint
	TALK_SYN_DATA_SENDER_NAME,							// 发送者角色名			varchar32
	TALK_SYN_DATA_SENDER_FACE,							// 发送者头像			uint
	TALK_SYN_DATA_SENDER_LEV,							// 发送者等级			uint
	TALK_SYN_DATA_TEXT,									// 发送内容				varchar256
	TALK_SYN_DATA_TIME,									// 发送时间				uint
	TALK_SYN_DATA_TYPE,									// 类型					uint
	TALK_SYN_DATA_PARAM1,								// 预留1				uint
	TALK_SYN_DATA_PARAM2,								// 预留2				uint
	TALK_SYN_DATA_PARAM3,								// 预留3				uint
	TALK_SYN_DATA_PARAM4,								// 预留4				uint
	TALK_SYN_DATA_SERVER_GROUP,							// 服务器组				uint
};

static const char* GAME_DB_NAME_TALK_PRIVATE = "talk_private";	// 私聊表
enum TALK_PRIVATE_DATA
{
	TALK_PRIVATE_DATA_ID = 0,								// 自增长ID				bigint
	TALK_PRIVATE_DATA_USER_ID,								// 接收者ID				uint
	TALK_PRIVATE_DATA_SENDER_ID,							// 发送者ID				uint
	TALK_PRIVATE_DATA_SENDER_NAME,							// 发送者角色名			varchar32
	TALK_PRIVATE_DATA_SENDER_FACE,							// 发送者头像			uint
	TALK_PRIVATE_DATA_SENDER_LEV,							// 发送者等级			uint
	TALK_PRIVATE_DATA_TEXT,									// 发送内容				varchar256
	TALK_PRIVATE_DATA_TIME,									// 发送时间				uint
	TALK_PRIVATE_DATA_TYPE,									// 类型					uint
	TALK_PRIVATE_DATA_PARAM1,								// 预留1				uint
	TALK_PRIVATE_DATA_PARAM2,								// 预留2				uint
	TALK_PRIVATE_DATA_PARAM3,								// 预留3				uint
	TALK_PRIVATE_DATA_PARAM4,								// 预留4				uint
	TALK_PRIVATE_DATA_SERVER_GROUP,							// 服务器组		
};

static const char* GAME_DB_NAME_MINE_COLLECT = "mine_collect";	// 矿洞采集表
enum MINE_COLLECT_DATA
{
	MINE_COLLECT_DATA_USER_ID = 0,							// 玩家ID				uint
	MINE_COLLECT_DATA_NAME,									// 玩家角色名			varchar32
	MINE_COLLECT_DATA_LEV,									// 玩家等级				uint
	MINE_COLLECT_DATA_LOOKFACE,								// 玩家头像				uint
	MINE_COLLECT_DATA_LOOKFACE_FRAME,						// 玩家头像框			uint
	MINE_COLLECT_DATA_ATK_COUNT_TOTAL,						// 攻击矿洞次数总和		uint
	MINE_COLLECT_DATA_MONEY_TOTAL,							// 获得金币总和			uint	
	MINE_COLLECT_DATA_DRUG_TOTAL,							// 获得药剂总和			uint
	MINE_COLLECT_DATA_ATK_COUNT0_VALUE,						// 攻击次数值0			uint
	MINE_COLLECT_DATA_MONEY0_VALUE,							// 金币值0				uint
	MINE_COLLECT_DATA_DRUG0_VALUE,							// 药剂值0				uint
	MINE_COLLECT_DATA_DATE0,								// 日期0				uint
	MINE_COLLECT_DATA_ATK_COUNT1_VALUE,						// 攻击次数值1			uint
	MINE_COLLECT_DATA_MONEY1_VALUE,							// 金币值1				uint
	MINE_COLLECT_DATA_DRUG1_VALUE,							// 药剂值1				uint
	MINE_COLLECT_DATA_DATE1,								// 日期1				uint
	MINE_COLLECT_DATA_ATK_COUNT2_VALUE,						// 攻击次数值2			uint
	MINE_COLLECT_DATA_MONEY2_VALUE,							// 金币值2				uint
	MINE_COLLECT_DATA_DRUG2_VALUE,							// 药剂值2				uint
	MINE_COLLECT_DATA_DATE2,								// 日期2				uint
	MINE_COLLECT_DATA_ATKCOUNT_RANK_LAST,					// 攻击次数上期排名		uint
	MINE_COLLECT_DATA_MONEY_RANK_LAST,						// 金币采集上期排名		uint
	MINE_COLLECT_DATA_DRUG_RANK_LAST,						// 药剂采集上期排名		uint
	MINE_COLLECT_DATA_SERVER_GROUP,							// 服务器组				uint
};

static const char* GAME_DB_NAME_SYN_GIFT_BOX_LOG	= "syn_giftbox_log";	// 帮派礼盒记录表
enum SYN_GIFT_BOX_LOG_DATA
{
	SYN_GIFT_BOX_LOG_DATA_ID = 0,							// 自增长ID				bigint
	SYN_GIFT_BOX_LOG_DATA_SYNDICATE_ID,						// 帮派ID				uint
	SYN_GIFT_BOX_LOG_DATA_BOX_TYPE,							// 礼盒类型				uint
	SYN_GIFT_BOX_LOG_DATA_INVAILD_TIME,						// 结束时间				uint
	SYN_GIFT_BOX_LOG_DATA_GIVE_USER_ID,						// 赠送玩家ID			uint	
	SYN_GIFT_BOX_LOG_DATA_GIVE_USER_NAME,					// 赠送玩家名称			varchar32
	SYN_GIFT_BOX_LOG_DATA_SERVER_GROUP,						// 服务器组				uint
};

static const char* GAME_DB_NAME_USER_SYN_GIFTBOX_AWARD	= "user_syn_giftbox_ward";	// 玩家帮派礼盒领取记录表
enum USER_SYN_GIFTBOX_AWARD_DATA
{
	USER_SYN_GIFTBOX_AWARD_DATA_USER_ID = 0,				// 玩家ID				uint
	USER_SYN_GIFTBOX_AWARD_DATA_SYN_GIFTBOX_ID,				// 帮派礼盒记录id		uint
	USER_SYN_GIFTBOX_AWARD_DATA_INVIALDTIME,				// 失效时间				uint
};

static const char* GAME_DB_NAME_LOOKFACE_FRAME = "lookface_frame";					// 玩家获得的头像框数据表
enum USER_LOOKFACE_FRAME
{
	USER_LOOKFACE_FRAME_ID = 0,								// ID					uint
	USER_LOOKFACE_FRAME_USER_ID,							// 玩家ID				uint
	USER_LOOKFACE_FRAME_FRAME_TYPE,							// 头像框类型			uint
	USER_LOOKFACE_FRAME_END_TIME,							// 结束时间				uint
};


static const char* GAME_DB_NAME_CROSS_ROOM = "cs_room";		// 跨服房间表
enum CROSS_ROOM_DATA
{
	CROSS_ROOM_DATA_ID = 0,		// id			uint
	CROSS_ROOM_DATA_TYPE,		// 类型			uint
	CROSS_ROOM_DATA_LINE,		// 所在线路		uint
	CROSS_ROOM_DATA_OWNER_ID,	// 拥有者id		uint
	CROSS_ROOM_DATA_CREATE_TIME,// 房间创建时间	uint
	CROSS_ROOM_DATA_END_TIME,	// 强制解散时间 uint
	CROSS_ROOM_DATA_DATA1,		// 数据1		uint
	CROSS_ROOM_DATA_DATA2,		// 数据2		uint
	CROSS_ROOM_DATA_DATA3,		// 数据3		uint
	CROSS_ROOM_DATA_DATA4,		// 数据4		uint
	CROSS_ROOM_DATA_DATA5,		// 数据5		uint
	CROSS_ROOM_DATA_STR1,		// 字串1		varchar255
	CROSS_ROOM_DATA_STR2,		// 字串2		varchar255
};

static const char* GAME_DB_NAME_CROSS_ROOM_MEMBER = "cs_room_member";	// 跨服房间成员表
enum CROSS_ROOM_MEMBER_DATA
{
	CROSS_ROOM_MEMBER_DATA_USER_ID = 0,		// 角色id		uint
	CROSS_ROOM_MEMBER_DATA_ROOM_ID,			// 房间id		uint
	CROSS_ROOM_MEMBER_DATA_DATA1,			// 数据1		uint
	CROSS_ROOM_MEMBER_DATA_DATA2,			// 数据2		uint
	CROSS_ROOM_MEMBER_DATA_DATA3,			// 数据3		uint
};

static const char* GAME_DB_NAME_CROSS_NTM_FIGHT_LOG = "cs_ntm_fight_log";	// 跨服南天门战斗记录表
enum CROSS_NTM_FIGHT_LOG_DATA
{
	CROSS_NTM_FIGHT_LOG_DATA_USER_ID = 0,		// 角色id	uint
	CROSS_NTM_FIGHT_LOG_DATA_INTEGRAL,			// 积分		uint
	CROSS_NTM_FIGHT_LOG_DATA_PASS_TIME,			// 通关时间	uint
	CROSS_NTM_FIGHT_LOG_DATA_RANK,				// 排名		uint
	CROSS_NTM_FIGHT_LOG_DATA_AWARD_TYPE,		// 奖励类型	uint
	CROSS_NTM_FIGHT_LOG_DATA_AWARD_NUM,			// 奖励数量	uint
};

static const char* GAME_DB_NAME_SYN_BUFF = "syn_buff";		// 帮派buff表
enum SYN_BUFF_DATA
{
	SYN_BUFF_DATA_ID = 0,						// id		bigint
	SYN_BUFF_DATA_SYNDICATE_ID,					// 帮派id	uint
	SYN_BUFF_DATA_TYPE,							// buff类型	uint
	SYN_BUFF_DATA_POWER,						// buff威力	uint
	SYN_BUFF_DATA_END_TIME,						// 结束时间	uint
	SYN_BUFF_DATA_ADD_COUNT,					// 叠加层数	uint
	SYN_BUFF_DATA_PARAM1,						// 参数1	uint
	SYN_BUFF_DATA_PARAM2,						// 参数2	uint
	SYN_BUFF_DATA_SERVER_GROUP,					// 服务器组	uint
};

static const char* GAME_DB_NAME_USER_BUFF = "user_buff";	// 房玩家buff表
enum USER_BUFF_DATA
{
	USER_BUFF_DATA_ID = 0,						// id		bigint
	USER_BUFF_DATA_USER_ID,						// 角色id	uint
	USER_BUFF_DATA_TYPE,						// buff类型	uint
	USER_BUFF_DATA_POWER,						// buff威力	uint
	USER_BUFF_DATA_END_TIME,					// 结束时间	uint
	USER_BUFF_DATA_SOURCE_ID,					// 来源ID	uint
	USER_BUFF_DATA_ADD_COUNT,					// 叠加层数	uint
	USER_BUFF_DATA_PARAM1,						// 参数1	uint
	USER_BUFF_DATA_PARAM2,						// 参数2	uint
};

static const char* GAME_DB_NAME_USER_MARKS_INFO = "user_marksinfo";	// 玩家推送信息记录表
enum USER_MARKSINFO_DATA
{
	USER_MARKSINFO_DATA_USER_ID,				// 角色id	uint
	USER_MARKSINFO_DATA_TYPE,					// 推送类型	uint
	USER_MARKSINFO_DATA_DATA,					// 推送数据	uint
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 常量库
static const char* CONST_DB_NAME_CONFIG = "config";				// 常量配置表
enum CONFIG_DATA
{
	CONFIGDATA_BEGIN = 0,
	CONFIGDATA_TYPE = CONFIGDATA_BEGIN,			// typeid	uint
	CONFIGDATA_DATA1,							// 数据1	uint
	CONFIGDATA_DATA2,							// 数据2	uint
	CONFIGDATA_DATA3,							// 数据3	uint
	CONFIGDATA_DATA4,							// 数据4	uint
	CONFIGDATA_DATA5,							// 数据5	uint
//	CONFIGDATA_COMMENT,							// 注释字段, 不加载内存
	CONFIGDATA_END,
};

static const char* CONST_DB_NAME_CONFIG_TEXT = "config_text";	// 常量配置文本表
enum CONFIG_TEXT_DATA
{
	CONFIG_TEXT_DATA_ID		= 0,	// id
	CONFIG_TEXT_DATA_TEXT	= 1,	// 可配置文字
};

static const char* CONST_DB_NAME_TASK_CONFIG_DATA = "task";		// 任务配置表
enum ETASK_CONFIG_DATA
{
	ETASK_CONFIG_DATA_ID		= 0,	// 编号										uint
	ETASK_CONFIG_DATA_TYPE,				// 任务类型									uint
	ETASK_CONFIG_DATA_STEP,				// 步骤(步骤(从1开始且连续))				uint
	ETASK_CONFIG_DATA_ISCHAIN,			// 是否是任务链(0:不是，1:是)				uint
	ETASK_CONFIG_DATA_LIMIT_TIME,		// 时间限制( 0:无限制, >0:限制时间(秒) )	uint
	ETASK_CONFIG_DATA_NEED_TYPE1,		// 任务需要类型1							uint
	ETASK_CONFIG_DATA_NEED_NUM1,		// 类型1需要数量							uint
	ETASK_CONFIG_DATA_NEED_TYPE2,		// 任务需要类型2							uint
	ETASK_CONFIG_DATA_NEED_NUM2,		// 类型2需要数量							uint
	ETASK_CONFIG_DATA_NEED_TYPE3,		// 任务需要类型3							uint
	ETASK_CONFIG_DATA_NEED_NUM3,		// 类型3需要数量							uint
	ETASK_CONFIG_DATA_RECEIVE_ACTION,	// 接收任务脚本action						uint
	ETASK_CONFIG_DATA_FINISH_ACTION,	// 完成任务脚本action						uint
	ETASK_CONFIG_DATA_GIVEUP_ACTION,	// 放弃任务脚本action						uint
	ETASK_CONFIG_DATA_NAME,				// 任务名									varchar128
};


static const char* CONST_DB_NEWCARD_PRIZE = "newcard_prize";	// 新手卡奖励配置表
enum NEWCARD_PRIZE_DATA
{
	NEWCARD_PRIZE_DATA_ID = 0,		// id		uint
	NEWCARD_PRIZE_DATA_TYPE,		// 卡类型	uint
	NEWCARD_PRIZE_DATA_GIVEMASKID,	// 掩码ID	uint
	// 以下字段为10个奖励道具信息（道具type uint, 道具数量 uint, 是否绑定 uint）
	NEWCARD_PRIZE_DATA_ITEMTYPE1,
	NEWCARD_PRIZE_DATA_ITEMCOUNT1,
	NEWCARD_PRIZE_DATA_ITEMTYPE2,
	NEWCARD_PRIZE_DATA_ITEMCOUNT2,
	NEWCARD_PRIZE_DATA_ITEMTYPE3,
	NEWCARD_PRIZE_DATA_ITEMCOUNT3,
	NEWCARD_PRIZE_DATA_ITEMTYPE4,
	NEWCARD_PRIZE_DATA_ITEMCOUNT4,
	NEWCARD_PRIZE_DATA_ITEMTYPE5,
	NEWCARD_PRIZE_DATA_ITEMCOUNT5,
	NEWCARD_PRIZE_DATA_ITEMTYPE6,
	NEWCARD_PRIZE_DATA_ITEMCOUNT6,
	NEWCARD_PRIZE_DATA_ITEMTYPE7,
	NEWCARD_PRIZE_DATA_ITEMCOUNT7,
	NEWCARD_PRIZE_DATA_ITEMTYPE8,
	NEWCARD_PRIZE_DATA_ITEMCOUNT8,
	NEWCARD_PRIZE_DATA_ITEMTYPE9,
	NEWCARD_PRIZE_DATA_ITEMCOUNT9,
	NEWCARD_PRIZE_DATA_ITEMTYPE10,
	NEWCARD_PRIZE_DATA_ITEMCOUNT10,
};

static const char* CONST_DB_NAME_NOTIFY_CONFIG = "notify";		// 公告配置表
enum NOTIFY_CONFIG
{
	NOTIFY_CONFIG_ID = 0,				// 编号										bigint
	NOTIFY_CONFIG_CHANNEL,				// 频道										uint
	NOTIFY_CONFIG_TIME_TYPE,			// 时间类型									uint
	NOTIFY_CONFIG_TIME,					// 时间										bigint
	NOTIFY_CONFIG_TEXT,					// 公告内容									varchar255
	NOTIFY_CONFIG_GROUP,				// 服务器组									uint
};
static const char* CONST_DB_NAME_ACTIVITY_CONFIG = "activities";	// 活动表
enum ACTIVITY_CONFIG_DATA
{
	ACTIVITY_CONFIG_DATA_BEGIN = 0,
	ACTIVITY_CONFIG_DATA_ID	 = ACTIVITY_CONFIG_DATA_BEGIN,	// 自增长id				uint
	ACTIVITY_CONFIG_DATA_TYPE,								// typeid				uint
	ACTIVITY_CONFIG_DATA_TIME_TYPE,							// 活动时间类别			uint
	ACTIVITY_CONFIG_DATA_BEGIN_TIME,						// 开始时间				uint
	ACTIVITY_CONFIG_DATA_END_TIME,							// 结束时间				uint
	ACTIVITY_CONFIG_DATA_BEGIN_ACTION,						// 开始触发脚本			uint
	ACTIVITY_CONFIG_DATA_END_ACTION,						// 结束触发脚本			uint
	ACTIVITY_CONFIG_DATA_ENTER_ACTION,						// 客户端触发进入脚本	uint
	ACTIVITY_CONFIG_DATA_EXIT_ACTION,						// 客户端触发退出脚本	uint
	ACTIVITY_CONFIG_DATA_SERVER_GROUP,						// 服务器组				uint
	ACTIVITY_CONFIG_DATA_LINE,								// 线路					uint
	ACTIVITY_CONFIG_DATA_PARAM1,							// 备用参数1			uint
	ACTIVITY_CONFIG_DATA_PARAM2,							// 备用参数2			uint
//  ACTIVITY_CONFIG_DATA_COMMENT,							// 注释字段, 不加载内存
	ACTIVITY_CONFIG_DATA_END,
};


static const char* CONST_DB_ACTION = "action";	// 脚本action表
enum ACTION_DATA
{
	ACTION_DATA_ID = 0,				// id			uint
	ACTION_DATA_FILE_PATH,			// 路径			varchar128
	ACTION_DATA_FUNCTION,			// 函数			varchar128
	ACTION_DATA_CLIENT_TRIGGER,		// 客户端触发	uint
};



static const char* CONST_DB_POKER_TYPE = "poker_type";	// 卡牌类型表
enum POKER_TYPE_DATA
{
	POKER_TYPE_DATA_ID = 0,			// 卡牌类型id				uint
	POKER_TYPE_DATA_NAME,			// 名称						varchar32
	POKER_TYPE_DATA_CAMP,			// 阵营		POKER_CAMP		uint
	POKER_TYPE_DATA_FIGHT_POS,		// 战斗位置	POKER_FIGHT_POS	uint
	POKER_TYPE_DATA_POS_SORT,		// 站位排序					uint
	POKER_TYPE_DATA_INIT_LIFE,		// 初始体质					uint
	POKER_TYPE_DATA_INIT_MANA,		// 初始魔力					uint
	POKER_TYPE_DATA_INIT_STR,		// 初始力量					uint
	POKER_TYPE_DATA_INIT_STA,		// 初始耐力					uint
	POKER_TYPE_DATA_INIT_DEX,		// 初始敏捷					uint
	POKER_TYPE_DATA_INIT_HP,		// 初始血量					uint
	POKER_TYPE_DATA_INIT_ATK,		// 初始伤害					uint
	POKER_TYPE_DATA_INIT_STAR,		// 初始星级					uint
	POKER_TYPE_DATA_SKILL_SP,		// 特技						uint
	POKER_TYPE_DATA_SKILL_AUTO1,	// 自动技能1				uint
	POKER_TYPE_DATA_SKILL_AUTO2,	// 自动技能2				uint
	POKER_TYPE_DATA_SKILL_AUTO3,	// 自动技能3				uint
	POKER_TYPE_DATA_SKILL_JOINT,	// 连携技能					uint
	POKER_TYPE_DATA_ANGER_PARAM,	// 愤怒转化系数（万分比）	uint
	POKER_TYPE_DATA_NEED_ITEMTYPE,	// 对应灵魂石类型			uint
};

static const char* CONST_DB_POKER_STAR_GROW = "poker_star_grow";	// 卡牌星级成长表
enum POKER_STAR_GROW_DATA
{
	POKER_STAR_GROW_DATA_TYPE = 0,	// 卡牌类型		uint
	POKER_STAR_GROW_DATA_STAR,		// 卡牌星级		uint
	POKER_STAR_GROW_DATA_LIFE_GROW,	// 体质成长		uint
	POKER_STAR_GROW_DATA_MANA_GROW,	// 魔力成长		uint
	POKER_STAR_GROW_DATA_STR_GROW,	// 力量成长		uint
	POKER_STAR_GROW_DATA_STA_GROW,	// 耐力成长		uint
	POKER_STAR_GROW_DATA_DEX_GROW,	// 敏捷成长		uint
};

static const char* CONST_DB_POKER_EQUIP = "poker_equip";	// 卡牌装备配置表
enum POKER_EQUIP_DATA
{
	POKER_EQUIP_DATA_POKER_TYPE = 0,	// 卡牌类型			uint
	POKER_EQUIP_DATA_POKER_COLOR,		// 卡牌颜色(1-17)	uint
	POKER_EQUIP_DATA_EQUIP1_TYPE,		// 武器类型			uint
	POKER_EQUIP_DATA_EQUIP2_TYPE,		// 头盔类型			uint
	POKER_EQUIP_DATA_EQUIP3_TYPE,		// 项链类型			uint
	POKER_EQUIP_DATA_EQUIP4_TYPE,		// 腰带类型			uint
	POKER_EQUIP_DATA_EQUIP5_TYPE,		// 衣服类型			uint
	POKER_EQUIP_DATA_EQUIP6_TYPE,		// 鞋子类型			uint
};

static const char* CONST_DB_POKER_STAR = "poker_star";	// 卡牌星级配置表
enum POKER_STAR_DATA
{
	POKER_STAR_DATA_STAR = 0,			// 星级								uint
	POKER_STAR_DATA_COMPOUND_NEED,		// 合成时需求灵魂石数量				uint
	POKER_STAR_DATA_RESOLVE_AUTO,		// 自动分解获得灵魂石数量			uint
	POKER_STAR_DATA_UPGRADE_NEED,		// 升星需要灵魂石, 满星填0			uint
};

static const char* CONST_DB_LEV_EXP = "lev_exp"; // 等级经验表
enum LEV_EXP_DATA
{
	LEV_EXP_DATA_TYPE = 0,		// 类型 LEV_EXP_TYPE		uint
	LEV_EXP_DATA_LEV,			// 等级						uint
	LEV_EXP_DATA_EXP,			// 经验						bigint
};

static const char* CONST_DB_SIGN_PRIZE = "sign_prize";	// 签到奖励配置表
enum SIGN_PRIZE_DATA
{
	SIGN_PRIZE_DATA_ID = 0,			// id（天数，连续签到1000+天数）uint
	SIGN_PRIZE_DATA_MUL_PRIZE,		// 奖励倍数	uint
	SIGN_PRIZE_DATA_VIP_LEV,		// 需求VIP等级	uint
	// 以下字段为4个奖励道具信息（道具type uint, 道具数量 uint, 是否绑定 uint）
	SIGN_PRIZE_DATA_ITEMTYPE1,
	SIGN_PRIZE_DATA_ITEMCOUNT1,
	SIGN_PRIZE_DATA_ITEMTYPE2,
	SIGN_PRIZE_DATA_ITEMCOUNT2,
	SIGN_PRIZE_DATA_ITEMTYPE3,
	SIGN_PRIZE_DATA_ITEMCOUNT3,
};

static const char* CONST_DB_AUTO_RELOAD = "auto_reload";	// 自动加载配置表
enum AUTO_RELOAD_DATA
{
	AUTO_RELOAD_DATA_TABLE_NAME = 0,	// 表名					varchar255
	AUTO_RELOAD_DATA_GROUP,				// 服务器组 填0表示全部	uint
	AUTO_RELOAD_DATA_LINE,				// 服务器线 填0表示全部	uint
	AUTO_RELOAD_DATA_UTC_TIME,			// 指定时间 填0表示即时	uint
};

static const char* CONST_DB_VIP = "vip";		// VIP配置表
enum VIP_DATA
{
	VIP_DATA_TYPE	= 0,		// vip类型	uint
	VIP_DATA_LEV,				// vip等级	uint
	VIP_DATA_VALUE,				// Vaule	uint
};

static const char* CONST_DB_NAME_ITEM_TYPE = "item_type";	// 物品类型表
enum ITEM_TYPE_DATA
{
	ITEM_TYPE_DATA_ID = 0,			// 类型			uint
	ITEM_TYPE_DATA_NAME,			// 名字			uint
	ITEM_TYPE_DATA_COLOR,			// 颜色			uint
	ITEM_TYPE_DATA_AMOUNT_LIMIT,	// 叠加上限		uint
	ITEM_TYPE_DATA_CLASSIIFY,		// 分类			uint
	ITEM_TYPE_DATA_SORT,			// 物品区分		uint
	ITEM_TYPE_DATA_DATA1,			// 数据1		uint
	ITEM_TYPE_DATA_DATA2,			// 数据2		uint
	ITEM_TYPE_DATA_DATA3,			// 数据3		uint
	ITEM_TYPE_DATA_ACTION,			// action		uint
	ITEM_TYPE_DATA_MONOPOLY,		// monopoly		uint
	ITEM_TYPE_DATA_SALE_MONEY_TYPE,	// 售出货币类型 uint
	ITEM_TYPE_DATA_SALE_PRICE,		// 售出价格		uint
	ITEM_TYPE_DATA_PEIFANG_ID,		// 配方ID		uint
	ITEM_TYPE_DATA_LIMIT_LEV,		// 限制等级		uint
	ITEM_TYPE_DATA_END,
};

static const char* CONST_DB_NAME_ITEM_COLOR = "item_color";	// 物品颜色配置表
enum ITEM_COLOR_DATA
{
	ITEM_COLOR_DATA_COLOR = 0,	// 颜色			uint
	ITEM_COLOR_DATA_STAR1,		// 1星升星上限	uint
	ITEM_COLOR_DATA_STAR2,		// 2星升星上限	uint
	ITEM_COLOR_DATA_STAR3,		// 3星升星上限	uint
	ITEM_COLOR_DATA_STAR4,		// 4星升星上限	uint
	ITEM_COLOR_DATA_STAR5,		// 5星升星上限	uint
	ITEM_COLOR_DATA_PRICE,		// 每点价格		uint
};

static const char* CONST_DB_NAME_ITEM_STAR_ATTR = "item_star_attr";	// 物品星级属性
enum ITEM_STAR_ATTR_DATA
{
	ITEM_STAR_ATTR_DATA_TYPE = 0,		// 物品类型		uint
	ITEM_STAR_ATTR_DATA_STAR,			// 物品星级		uint
	ITEM_STAR_ATTR_DATA_ATTR_TYPE1,		// 属性类型1	uint
	ITEM_STAR_ATTR_DATA_ATTR_DATA1,		// 属性数值1	uint
	ITEM_STAR_ATTR_DATA_ATTR_TYPE2,		// 属性类型2	uint
	ITEM_STAR_ATTR_DATA_ATTR_DATA2,		// 属性数值2	uint
	ITEM_STAR_ATTR_DATA_ATTR_TYPE3,		// 属性类型3	uint
	ITEM_STAR_ATTR_DATA_ATTR_DATA3,		// 属性数值3	uint
	ITEM_STAR_ATTR_DATA_ATTR_TYPE4,		// 属性类型4	uint
	ITEM_STAR_ATTR_DATA_ATTR_DATA4,		// 属性数值4	uint
	ITEM_STAR_ATTR_DATA_ATTR_TYPE5,		// 属性类型5	uint
	ITEM_STAR_ATTR_DATA_ATTR_DATA5,		// 属性数值5	uint
};

static const char* CONST_DB_LIVENESS = "liveness";		// 每日活跃配置表
enum ELIVENESS_CONFIG
{
	ELIVENESS_CONFIG_ID = 0,			// 活跃项ID					uint		
	ELIVENESS_CONFIG_LevLimit,			// 等级限制					uint
	ELIVENESS_CONFIG_VipLimit,			// VIP等级限制				uint
	ELIVENESS_CONFIG_BeginTime,			// 开始时间					uint
	ELIVENESS_CONFIG_EndTime,			// 结束时间					uint
	ELIVENESS_CONFIG_Val,				// 完成活跃获得的活跃值		uint
	ELIVENESS_CONFIG_NeedType,			// 需要类型					uint
	ELIVENESS_CONFIG_NeedNum,			// 需要数量					uint
	ELIVENESS_CONFIG_AwardAction,		// 发奖励脚本Action			uint
	ELIVENESS_CONFIG_Title,				// 主题						varchar32
	ELIVENESS_CONFIG_Content,			// 内容 					varchar64
};

static const char* CONST_DB_SHOP_TYPE = "shop_type";	// 商店类型配置表
enum SHOP_TYPE
{
	SHOP_TYPE_BEGIN = 0,
	SHOP_TYPE_ID = SHOP_TYPE_BEGIN,		// 商店类型					uint
	SHOP_TYPE_BLANK_LIMIT,				// 格子上限					uint
	SHOP_TYPE_REFRESH_MONEY_TYPE,		// 手动刷新所需的货币类型	uint
	SHOP_TYPE_REFRESH_PRICE,			// 手动刷新价格				uint
	SHOP_TYPE_AUTO_REFRESH_TIME1,		// 自动刷新时间1			uint
	SHOP_TYPE_AUTO_REFRESH_TIME2,		// 自动刷新时间2			uint
	SHOP_TYPE_AUTO_REFRESH_TIME3,		// 自动刷新时间3			uint
	SHOP_TYPE_AUTO_REFRESH_TIME4,		// 自动刷新时间4			uint
	SHOP_TYPE_AUTO_REFRESH_TIME5,		// 自动刷新时间5			uint
	SHOP_TYPE_REFRESH_RULE1,			// 刷新规则1				uint
	SHOP_TYPE_REFRESH_RULE2,			// 刷新规则2				uint
	SHOP_TYPE_REFRESH_RULE3,			// 刷新规则3				uint
	SHOP_TYPE_REFRESH_RULE4,			// 刷新规则4				uint
	SHOP_TYPE_REFRESH_RULE5,			// 刷新规则5				uint
	SHOP_TYPE_REFRESH_RULE6,			// 刷新规则6				uint
	SHOP_TYPE_REFRESH_RULE7,			// 刷新规则7				uint
	SHOP_TYPE_REFRESH_RULE8,			// 刷新规则8				uint
	SHOP_TYPE_REFRESH_RULE9,			// 刷新规则9				uint
	SHOP_TYPE_REFRESH_RULE10,			// 刷新规则10				uint
	SHOP_TYPE_REFRESH_RULE11,			// 刷新规则11				uint
	SHOP_TYPE_REFRESH_RULE12,			// 刷新规则12				uint
	SHOP_TYPE_END,
};

static const char* CONST_DB_SHOP_RULE = "shop_rule";		// 商店规则配置表
enum SHOP_RULE
{
	SHOP_RULE_BEGIN = 0,
	SHOP_RULE_ID = SHOP_RULE_BEGIN,		// 规则类型					uint
	SHOP_RULE_ITEM_TYPE,				// 物品类型					uint
	SHOP_RULE_ITEM_NUM,					// 物品数量					uint
	SHOP_RULE_ITEM_PRICE,				// 物品单价					uint
	SHOP_RULE_MONEY_TYPE,				// 货币类型					uint
	SHOP_RULE_DISCOUNT,					// 物品折扣					uint
	SHOP_RULE_WEIGHT,					// 物品权重					uint
	SHOP_RULE_END,
};

static const char* CONST_DB_NAME_ACHIEVEMENT = "achievement";		// 成就配置表
enum ACHIEVEMENT_DATA
{
	ACHIEVEMENT_DATA_BEGIN			= 0,
	ACHIEVEMENT_DATA_ID				= ACHIEVEMENT_DATA_BEGIN,	// 成就id（五位数，最高位表示类别）	uint
	ACHIEVEMENT_DATA_SUBINDEX,									// 子类成就序列号（第一个为0）		uint
	ACHIEVEMENT_DATA_BEFOREID,									// 前置成就id						uint
	ACHIEVEMENT_DATA_AFTERID,									// 后续成就id						uint
	ACHIEVEMENT_DATA_ACTIONID,									// 成就奖励调用脚本action			uint
	ACHIEVEMENT_DATA_OPEN_TYPE,									// 开启类别							uint
	ACHIEVEMENT_DATA_OPEN_CONDITION1,							// 开启条件1						uint
	ACHIEVEMENT_DATA_OPEN_CONDITION2,							// 开启条件2						uint
	ACHIEVEMENT_DATA_COMPLETE_CONDITION1,						// 完成条件1						uint
	ACHIEVEMENT_DATA_COMPLETE_CONDITION2,						// 完成条件2						uint
	ACHIEVEMENT_DATA_END,
};

static const char* CONST_DB_NAME_LUA_TEXT = "lua_text";	// 脚本文字表
enum LUA_TEXT_DATA
{
	LUA_TEXT_DATA_ID = 0,	// id		uint
	LUA_TEXT_DATA_TEXT,		// 文字		varchar512
};

static const char* CONST_DB_NAME_SKILL_TYPE = "skill_type";		// 技能类型配置表
enum SKILL_TYPE_DATA
{
	SKILL_TYPE_DATA_ID	= 0,			// 技能id			uint
	SKILL_TYPE_DATA_SORT,				// 技能分类			uint
	SKILL_TYPE_DATA_NEED_LEV,			// 需求等级			uint
	SKILL_TYPE_DATA_COST_MONEY,			// 花费进步			uint
	SKILL_TYPE_DATA_COST_POINT,			// 花费技能点		uint
	SKILL_TYPE_DATA_POWER,				// 威力				uint
	SKILL_TYPE_DATA_POWER_ADD,			// 威力增量			uint
	SKILL_TYPE_DATA_POWER2,				// 威力2			uint
	SKILL_TYPE_DATA_POWER2_ADD,			// 威力2增量		uint
};

static const char* CONST_DB_DROP_RULE = "drop_rule";	// 掉落规则表
enum DROP_RULE_DATA
{
	DROP_RULE_DATA_ID		= 0,		// 掉落规则id							uint
	DROP_RULE_DATA_TYPE,				// 掉落规则类型	DROP_RULE_TYPE			uint
	DROP_RULE_DATA_COUNT,				// 次数, 配合类型执行					uint
	DROP_RULE_DATA_CHANCE,				// 掉落概率, 万分比						uint

	DROP_RULE_DATA_GROUP1_TYPE,			// 掉落组1 类型	DROP_RULE_GROUP_TYPE	uint
	DROP_RULE_DATA_GROUP1_COUNT,		// 掉落组1 数量							uint
	DROP_RULE_DATA_GROUP1_WEIGHT,		// 掉落组1 权重							uint
	DROP_RULE_DATA_GROUP1_GROUP,		// 掉落组1 归属分类						uint

	DROP_RULE_DATA_GROUP2_TYPE,			// 掉落组2 类型	DROP_RULE_GROUP_TYPE	uint
	DROP_RULE_DATA_GROUP2_COUNT,		// 掉落组2 数量							uint
	DROP_RULE_DATA_GROUP2_WEIGHT,		// 掉落组2 权重							uint
	DROP_RULE_DATA_GROUP2_GROUP,		// 掉落组2 归属分类						uint

	DROP_RULE_DATA_GROUP3_TYPE,			// 掉落组3 类型	DROP_RULE_GROUP_TYPE	uint
	DROP_RULE_DATA_GROUP3_COUNT,		// 掉落组3 数量							uint
	DROP_RULE_DATA_GROUP3_WEIGHT,		// 掉落组3 权重							uint
	DROP_RULE_DATA_GROUP3_GROUP,		// 掉落组3 归属分类						uint

	DROP_RULE_DATA_GROUP4_TYPE,			// 掉落组4 类型	DROP_RULE_GROUP_TYPE	uint
	DROP_RULE_DATA_GROUP4_COUNT,		// 掉落组4 数量							uint
	DROP_RULE_DATA_GROUP4_WEIGHT,		// 掉落组4 权重							uint
	DROP_RULE_DATA_GROUP4_GROUP,		// 掉落组4 归属分类						uint

	DROP_RULE_DATA_GROUP5_TYPE,			// 掉落组5 类型	DROP_RULE_GROUP_TYPE	uint
	DROP_RULE_DATA_GROUP5_COUNT,		// 掉落组5 数量							uint
	DROP_RULE_DATA_GROUP5_WEIGHT,		// 掉落组5 权重							uint
	DROP_RULE_DATA_GROUP5_GROUP,		// 掉落组5 归属分类						uint

	DROP_RULE_DATA_GROUP6_TYPE,			// 掉落组6 类型	DROP_RULE_GROUP_TYPE	uint
	DROP_RULE_DATA_GROUP6_COUNT,		// 掉落组6 数量							uint
	DROP_RULE_DATA_GROUP6_WEIGHT,		// 掉落组6 权重							uint
	DROP_RULE_DATA_GROUP6_GROUP,		// 掉落组6 归属分类						uint

	DROP_RULE_DATA_GROUP7_TYPE,			// 掉落组7 类型	DROP_RULE_GROUP_TYPE	uint
	DROP_RULE_DATA_GROUP7_COUNT,		// 掉落组7 数量							uint
	DROP_RULE_DATA_GROUP7_WEIGHT,		// 掉落组7 权重							uint
	DROP_RULE_DATA_GROUP7_GROUP,		// 掉落组7 归属分类						uint

	DROP_RULE_DATA_GROUP8_TYPE,			// 掉落组8 类型	DROP_RULE_GROUP_TYPE	uint
	DROP_RULE_DATA_GROUP8_COUNT,		// 掉落组8 数量							uint
	DROP_RULE_DATA_GROUP8_WEIGHT,		// 掉落组8 权重							uint
	DROP_RULE_DATA_GROUP8_GROUP,		// 掉落组8 归属分类						uint
};


static const char* CONST_DB_BATTLE_TYPE = "battle_type";	// 战斗配置表
enum BATTLE_TYPE_DATA
{
	BATTLE_TYPE_DATA_TYPE = 0,		// 战斗类型					uint
	BATTLE_TYPE_DATA_SORT,			// 类型 对应BATTLE_SORT		uint
	BATTLE_TYPE_DATA_NAME,			// 名字						varchar32
	BATTLE_TYPE_DATA_ROUND1,		// 轮次1 id					uint
	BATTLE_TYPE_DATA_ROUND2,		// 轮次2 id					uint
	BATTLE_TYPE_DATA_ROUND3,		// 轮次3 id					uint
	BATTLE_TYPE_DATA_DROP_ID,		// 掉落 id					uint
	BATTLE_TYPE_DATA_WIN_ACTION,	// 胜利执行脚本				uint
	BATTLE_TYPE_DATA_TIME_LIMIT,	// 战斗时间限制				uint
	BATTLE_TYPE_DATA_SAVE_FLAG,		// 存档标记					uint
	BATTLE_TYPE_DATA_EXP,			// 关卡总经验				uint
};

static const char* CONST_DB_BATTLE_ROUND = "battle_round";	// 战斗轮次表
enum BATTLE_ROUND_DATA
{
	BATTLE_ROUND_DATA_ID = 0,		// 轮次id		uint
	BATTLE_ROUND_DATA_MONSTER1_ID,	// 怪物1 id		uint
	BATTLE_ROUND_DATA_MONSTER2_ID,	// 怪物2 id		uint
	BATTLE_ROUND_DATA_MONSTER3_ID,	// 怪物3 id		uint
	BATTLE_ROUND_DATA_MONSTER4_ID,	// 怪物4 id		uint
	BATTLE_ROUND_DATA_MONSTER5_ID,	// 怪物5 id		uint
	BATTLE_ROUND_DATA_DROP_ID,		// 掉落  id		uint
};

static const char* CONST_DB_BATTLE_MONSTER = "battle_monster";	// 战斗怪物配置表
enum BATTLE_MONSTER_DATA
{
	BATTLE_MONSTER_DATA_TYPE = 0,						// 怪物类型						uint	
	BATTLE_MONSTER_DATA_NAME,							// 怪物名字						varchar32
	BATTLE_MONSTER_DATA_FIGHT_POS,						// 战斗位置, 前1, 中2, 后3		uint
	BATTLE_MONSTER_DATA_POS_SORT,						// 站位排序						uint
	BATTLE_MONSTER_DATA_LEV,							// 等级							uint
	BATTLE_MONSTER_DATA_STAR,							// 星级							uint
	BATTLE_MONSTER_DATA_COLOR,							// 颜色							uint
	BATTLE_MONSTER_DATA_HP,								// 二级属性 气血				uint
	BATTLE_MONSTER_DATA_SP,								// 二级属性	愤怒				uint
	BATTLE_MONSTER_DATA_HIT,							// 二级属性	命中				uint
	BATTLE_MONSTER_DATA_ATK,							// 二级属性	伤害				uint
	BATTLE_MONSTER_DATA_DEF,							// 二级属性	防御				uint
	BATTLE_MONSTER_DATA_SPD,							// 二级属性	速度				uint
	BATTLE_MONSTER_DATA_DODGE,							// 二级属性	闪避				uint
	BATTLE_MONSTER_DATA_MAGIC,							// 二级属性	灵力				uint
	BATTLE_MONSTER_DATA_HP_RECOVER,						// 特殊属性 气血回复			uint
	BATTLE_MONSTER_DATA_SP_RECOVER,						// 特殊属性	愤怒回复			uint
	BATTLE_MONSTER_DATA_PHY_CRIT,						// 特殊属性	物暴				uint
	BATTLE_MONSTER_DATA_MAG_CRIT,						// 特殊属性	法爆				uint
	BATTLE_MONSTER_DATA_VAMPIRE_LEV,					// 特殊属性	吸血等级			uint
	BATTLE_MONSTER_DATA_SP_SPEND_DECREASE,				// 特殊属性	愤怒消耗降低%		uint
	BATTLE_MONSTER_DATA_CURE_INCREASE,					// 特殊属性	治疗技能效果提高%	uint
	BATTLE_MONSTER_DATA_SKILL_SP_TYPE,					// 特技类型						uint
	BATTLE_MONSTER_DATA_SKILL_SP_LEV,					// 特技等级						uint
	BATTLE_MONSTER_DATA_SKILL_AUTO1_TYPE,				// 自动技能1 类型				uint
	BATTLE_MONSTER_DATA_SKILL_AUTO1_LEV,				// 自动技能1 等级				uint
	BATTLE_MONSTER_DATA_SKILL_AUTO2_TYPE,				// 自动技能2 类型				uint
	BATTLE_MONSTER_DATA_SKILL_AUTO2_LEV,				// 自动技能2 等级				uint
	BATTLE_MONSTER_DATA_SKILL_AUTO3_TYPE,				// 自动技能3 类型				uint
	BATTLE_MONSTER_DATA_SKILL_AUTO3_LEV,				// 自动技能3 等级				uint
	BATTLE_MONSTER_DATA_SKILL_SKILL_JOINT_TYPE,			// 连携技能 类型				uint
	BATTLE_MONSTER_DATA_SKILL_SKILL_JOINT_LEV,			// 连携技能 等级				uint
	BATTLE_MONSTER_DATA_ANGER_PARAM,					// 愤怒转化系数%				uint
	BATTLE_MONSTER_DATA_DROP_ID,						// 掉落规则						uint
	BATTLE_MONSTER_DATA_KILL_ACTION,					// 击杀action					uint
};

static const char* CONST_DB_NAME_PEIFANG_TYPE = "peifang_type";	// 配方类型配置表
enum PEIFANG_TYPE_DATA
{
	PEIFANG_TYPE_DATA_ID = 0,			// 配方id			uint
	PEIFANG_TYPE_DATA_AWARD_ITEMTYPE,	// 获得物品类型		uint
	PEIFANG_TYPE_DATA_AWARD_ITEMNUM,	// 获得物品数量		uint
	PEIFANG_TYPE_DATA_SPEND_ITEMTYPE1,	// 消耗物品类型1	uint
	PEIFANG_TYPE_DATA_SPEND_ITEMNUM1,	// 消耗物品数量1	uint
	PEIFANG_TYPE_DATA_SPEND_ITEMTYPE2,	// 消耗物品类型2	uint
	PEIFANG_TYPE_DATA_SPEND_ITEMNUM2,	// 消耗物品数量2	uint
	PEIFANG_TYPE_DATA_SPEND_ITEMTYPE3,	// 消耗物品类型3	uint
	PEIFANG_TYPE_DATA_SPEND_ITEMNUM3,	// 消耗物品数量3	uint
	PEIFANG_TYPE_DATA_SPEND_ITEMTYPE4,	// 消耗物品类型4	uint
	PEIFANG_TYPE_DATA_SPEND_ITEMNUM4,	// 消耗物品数量4	uint
	PEIFANG_TYPE_DATA_COST_MONEY_TYPE,	// 消耗货币类型		uint
	PEIFANG_TYPE_DATA_COST_PRICE,		// 消耗价钱			uint
};

static const char* CONST_DB_CHALLENGE_BOSS_CONFIG = "challenge_boss";	// 挑战boss配置表
enum CHALLENGE_BOSS_CONFIG
{
	CHALLENGE_BOSS_CONFIG_BOSS_TYPE = 0,	// boss类型			uint
	CHALLENGE_BOSS_CONFIG_DEGREE,			// 难度				uint
	CHALLENGE_BOSS_CONFIG_BATTLE_TYPE,		// 对应战斗类型		uint
	CHALLENGE_BOSS_CONFIG_NEED_LEV,			// 需要等级			uint
	CHALLENGE_BOSS_CONFIG_ITEM1,			// 首掉物品1		uint
	CHALLENGE_BOSS_CONFIG_ITEM1_NUM,		// 首掉物品1数量	uint
	CHALLENGE_BOSS_CONFIG_ITEM2,			// 首掉物品2		uint
	CHALLENGE_BOSS_CONFIG_ITEM2_NUM,		// 首掉物品2数量	uint
	CHALLENGE_BOSS_CONFIG_ITEM3,			// 首掉物品3		uint
	CHALLENGE_BOSS_CONFIG_ITEM3_NUM,		// 首掉物品3数量	uint
	CHALLENGE_BOSS_CONFIG_ITEM4,			// 首掉物品4		uint
	CHALLENGE_BOSS_CONFIG_ITEM5_NUM,		// 首掉物品4数量	uint
	CHALLENGE_BOSS_CONFIG_DROP_ID,			// 非首掉规则ID		uint
	CHALLENGE_BOSS_CONFIG_BOSS_NAME,		// boss名			varchar32
};

static const char* CONST_DB_NAME_LOTTERY_TYPE = "lottery_type";		// 抽奖类型配置表
enum LOTTERY_TYPE_DATA
{
	LOTTERY_TYPE_DATA_TYPE = 0,				// 抽奖类型			uint
	LOTTERY_TYPE_DATA_AWARD_SUM,			// 奖品数量			uint
	LOTTERY_TYPE_DATA_COST_MONEY_TYPE,		// 消耗货币类型		uint
	LOTTERY_TYPE_DATA_COST_PRICE,			// 消耗价格			uint
	LOTTERY_TYPE_DATA_BASE_ITEM_TYPE,		// 获得基础物品类型	uint
	LOTTERY_TYPE_DATA_BASE_ITEM_NUM,		// 获得基础物品数量	uint
	LOTTERY_TYPE_DATA_RULE_ID1,				// 抽奖规则1		uint
	LOTTERY_TYPE_DATA_GIVE_COUNT1,			// 抽取次数1		uint
	LOTTERY_TYPE_DATA_GIVE_CHANCE1,			// 抽取概率1		uint
	LOTTERY_TYPE_DATA_RULE_ID2,				// 抽奖规则2		uint
	LOTTERY_TYPE_DATA_GIVE_COUNT2,			// 抽取次数2		uint
	LOTTERY_TYPE_DATA_GIVE_CHANCE2,			// 抽取概率2		uint
	LOTTERY_TYPE_DATA_RULE_ID3,				// 抽奖规则3		uint
	LOTTERY_TYPE_DATA_GIVE_COUNT3,			// 抽取次数3		uint
	LOTTERY_TYPE_DATA_GIVE_CHANCE3,			// 抽取概率3		uint
	LOTTERY_TYPE_DATA_RULE_ID4,				// 抽奖规则4		uint
	LOTTERY_TYPE_DATA_GIVE_COUNT4,			// 抽取次数4		uint
	LOTTERY_TYPE_DATA_GIVE_CHANCE4,			// 抽取概率4		uint
};

static const char* CONST_DB_NAME_LOTTERY_RULE = "lottery_rule";	// 抽奖规则配置表
enum LOTTERY_RULE_DATA
{
	LOTTERY_RULE_DATA_RULE_ID = 0,			// 规则id			uint
	LOTTERY_RULE_DATA_PRIZE_TYPE,			// 奖励类型			uint
	LOTTERY_RULE_DATA_WEIGHT,				// 奖励权重			uint
	LOTTERY_RULE_DATA_TIME_TYPE,			// 时间类型(0永久，1天，2周，3月)			uint
	LOTTERY_RULE_DATA_TIME_INDEX,			// 索引类型(周：0-6位表示，月0-31位表示)	uint
	LOTTERY_RULE_DATA_BEGIN_TIME,			// 奖品生效时间		uint
	LOTTERY_RULE_DATA_END_TIME,				// 奖品失效时间		uint
};

static const char* CONST_DB_NAME_PRIZE_TYPE = "prize_type";		// 奖励类型配置表
enum PRIZE_TYPE_DATA
{
	PRIZE_TYPE_DATA_ID		= 0,			// 奖励id			uint
	PRIZE_TYPE_DATA_TYPE,					// 奖品类型			uint
	PRIZE_TYPE_DATA_MIN_NUM,				// 最小奖品数量		uint
	PRIZE_TYPE_DATA_MAX_NUM,				// 最大奖品数量（若有值则随机取数量）		uint
};

static const char* CONST_DB_NAME_PROPERTY_CALCRANK2 = "property_calcrank2";	// 2级属性结算配置表
enum PROPERTY_CALCRANK2_DATA
{
	PROPERTY_CALCRANK2_DATA_TYPE = 0,	// 属性项			uint
	PROPERTY_CALCRANK2_DATA_LIFE,		// 体质:气血系数	uint
	PROPERTY_CALCRANK2_DATA_MANA,		// 魔力:灵力系数	uint
	PROPERTY_CALCRANK2_DATA_STR_HIT,	// 力量:命中系数	uint
	PROPERTY_CALCRANK2_DATA_STR_ATK,	// 力量:伤害系数	uint
	PROPERTY_CALCRANK2_DATA_STA,		// 耐力:防御系数	uint
	PROPERTY_CALCRANK2_DATA_DEX,		// 敏捷:躲避系数	uint
};

static const char* CONST_DB_NAME_MONEY_AWARD_CHANCE = "money_award_chance";	// 摇钱树多倍奖励和几率配置表
enum MONEY_AWARD_CHANCE_DATA
{
	MONEY_AWARD_CHANCE_DATA_COUNT = 0,		// 摇钱次数		uint
	MONEY_AWARD_CHANCE_DATA_COST,			// 摇钱消耗		uint
	MONEY_AWARD_CHANCE_DATA_MULTIPLE1,		// 暴击倍数1	uint
	MONEY_AWARD_CHANCE_DATA_CRILCHANCE1,	// 暴击几率1	uint
	MONEY_AWARD_CHANCE_DATA_MULTIPLE2,		// 暴击倍数2	uint
	MONEY_AWARD_CHANCE_DATA_CRILCHANCE2,	// 暴击几率2	uint
	MONEY_AWARD_CHANCE_DATA_MULTIPLE3,		// 暴击倍数3	uint
	MONEY_AWARD_CHANCE_DATA_CRILCHANCE3,	// 暴击几率3	uint
	MONEY_AWARD_CHANCE_DATA_MULTIPLE4,		// 暴击倍数4	uint
	MONEY_AWARD_CHANCE_DATA_CRILCHANCE4,	// 暴击几率4	uint
};

static const char* CONST_DB_NAME_INSTANCE_TYPE = "instance_type";	// 副本类型配置表
enum INSTANCE_TYPE_DATA
{
	INSTANCE_TYPE_DATA_TYPE = 0,			// 副本类型（1金币产出，2经验产出）		uint
	INSTANCE_TYPE_DATA_DIFFICULTY,			// 副本难度								uint
	INSTANCE_TYPE_DATA_OPENTIME_TYPE,		// 副本开启时间类型（1天，2周，3月）	uint
	INSTANCE_TYPE_DATA_OPENTIME_INDEX,		// 副本开启时间索引（天：0；周、月：32位天索引）	uint
	INSTANCE_TYPE_DATA_OPENTIME_BEGIN,		// 副本开启时间开始						uint
	INSTANCE_TYPE_DATA_OPENTIME_END,		// 副本开启时间结束						uint
	INSTANCE_TYPE_DATA_OPEN_LEV,			// 开启等级								uint
	INSTANCE_TYPE_DATA_COST_POWER,			// 消耗体力								uint
	INSTANCE_TYPE_DATA_BATTLE_TYPE,			// 战斗类型								uint
};

static const char* CONST_DB_NAME_POKER_COLOR_ATTR = "poker_color_attr";	// 卡牌颜色属性配置表
enum POKER_COLOR_ATTR_DATA
{
	POKER_COLOR_ATTR_DATA_POKER_COLOR = 0,	// 卡牌颜色		uint
	POKER_COLOR_ATTR_DATA_LIFE,				// 体质			uint
	POKER_COLOR_ATTR_DATA_MANA,				// 魔力			uint
	POKER_COLOR_ATTR_DATA_STR,				// 力量			uint
	POKER_COLOR_ATTR_DATA_STA,				// 耐力			uint
	POKER_COLOR_ATTR_DATA_DEX,				// 敏捷			uint
};

static const char* CONST_DB_NAME_PUZZLE = "puzzle";	// 迷宫配置表
enum PUZZLE_DATA
{
	PUZZLE_DATA_ID = 0,						// 迷宫格子id	uint
	PUZZLE_DATA_LINK_ID1,					// 连接格子id1	uint
	PUZZLE_DATA_LINK_ID2,					// 连接格子id2	uint
	PUZZLE_DATA_LINK_ID3,					// 连接格子id3	uint
	PUZZLE_DATA_LINK_ID4,					// 连接格子id4	uint
	PUZZLE_DATA_LINK_ID5,					// 连接格子id5	uint
	PUZZLE_DATA_LINK_ID6,					// 连接格子id6	uint
	PUZZLE_DATA_TASK_TYPE,					// 任务类型		uint
	PUZZLE_DATA_BATTLE_TYPE,				// 战斗类型		uint
	PUZZLE_DATA_ACTION_ID,					// 执行的脚本ID	uint
	PUZZLE_DATA_PROGRESS_ADD,				// 增加进度		uint
};

static const char* CONST_DB_NAME_PUZZLE_BUFF = "puzzle_buff";	// 迷宫BUFF配置表
enum PUZZLE_BUFF
{
	PUZZLE_BUFF_ID = 0,						// BUFF类型		uint
	PUZZLE_BUFF_NAME,						// BUFF名字		varchar32
	PUZZLE_BUFF_VALUE,						// BUFF属性值	uint
	PUZZLE_BUFF_EFFECT,						// BUFF生效机制	uint
};

static const char* CONST_DB_NAME_ARENA_AWARD = "arena_award";	// 竞技场奖励配置表
enum ARENA_AWARD
{
	ARENA_AWARD_TYPE = 0,					// 竞技场种别	uint
	ARENA_AWARD_UPPER_LEV,					// 奖励排名上限	uint
	ARENA_AWARD_LOWER_LEV,					// 奖励排名下限	uint
	ARENA_AWARD_GOLD_COUNT,					// 奖励金币数	uint
	ARENA_AWARD_MONEY_COUNT,				// 奖励竞技场币	uint
	ARENA_AWARD_VAS_COUNT,					// 奖励元宝		uint
	ARENA_AWARD_ITEM_TYPE,					// 奖励物品type	uint
	ARENA_AWARD_ITEM_COUNT,					// 奖励物品数	uint
	ARENA_AWARD_MONEY_COUNT_PER,			// 定时奖励币	uint
	ARENA_AWARD_END,
};

static const char* CONST_DB_NAME_ARENA_AI_POKER = "arena_ai_poker";	// 竞技场机器人卡牌配置表
enum ARENA_AI_POKER_DATA
{
	ARENA_AI_POKER_DATA_ARENA_TYPE = 0,		// 竞技场类别	uint
	ARENA_AI_POKER_DATA_LOW_RANK,			// 排名范围下限	uint
	ARENA_AI_POKER_DATA_POKER_TYPE,			// 卡牌typeid	uint
};

static const char* CONST_DB_NAME_PAY_CONFIG = "pay_config";		// 充值配置表
enum PAY_CONFIG_DATA
{
	PAY_CONFIG_DATA_ID = 0,				// id(首充掩码)			uint
	PAY_CONFIG_DATA_RMB,				// 人民币				uint
	PAY_CONFIG_DATA_VAS,				// 元宝					uint
	PAY_CONFIG_DATA_FREE_VAS,			// 赠送元宝				uint
	PAY_CONFIG_DATA_FREE_VAS_DES,		// 赠送元宝说明			uint
	PAY_CONFIG_DATA_FISRT_FREE_VAS,		// 首充赠送元宝			uint
	PAY_CONFIG_DATA_FISRT_FREE_DES,		// 首充赠送元宝说明		uint
	PAY_CONFIG_DATA_MONTH_CARD,			// 月卡标记				uint
};

static const char* CONST_DB_NAME_WAR_ROAD = "war_road";			// 战役配置表
enum WAR_ROAD_DATA
{
	WAR_ROAD_DATA_WAR_KEY = 0,			// 战役key（模式*1000000+章节*1000+关卡）（模式1普通，2精英，3团队）	uint
	WAR_ROAD_DATA_OPEN_LEV,				// 开启等级						uint
	WAR_ROAD_DATA_COST_POWER,			// 体力消耗						uint
	WAR_ROAD_DATA_BATTLE_TYPE,			// 战斗类型						uint
};

static const char* CONST_DB_NAME_WAR_ROAD_TEAM = "war_road_team";	// 团队战役配置表
enum WAR_ROAD_TEAM_DATA
{
	WAR_ROAD_TEAM_DATA_CHAPTER = 0,		// 章节							uint
	WAR_ROAD_TEAM_DATA_CHAPTER_NAME,	// 章节名称						varchar
	WAR_ROAD_TEAM_DATA_OPEN_COST,		// 开启消耗（活跃值）			uint
	WAR_ROAD_TEAM_DATA_AWARD_RULE,		// 战利品类库（lottery_award表中配置）			uint
	WAR_ROAD_TEAM_DATA_AWARD_TIME,		// 额外通关奖励时间				uint
	WAR_ROAD_TEAM_DATA_AWARD_COUNT,		// 额外奖励帮贡数量				uint
	WAR_ROAD_TEAM_DATA_PASS_WIN_COUNT,	// 关卡胜利奖励帮贡数量			uint
};

static const char* CONST_DB_NAME_TERRITORY_FIGHT = "territory_fight";		// 领地战配置表
enum TERRITORY_FIGHT_DATA
{
	TERRITORY_FIGHT_DATA_ID = 0,				// 领地id					uint
	TERRITORY_FIGHT_DATA_TYPE,					// 领地type					uint
	TERRITORY_FIGHT_DATA_BATTLETYPE,			// 战场type					uint
	TERRITORY_FIGHT_DATA_EFFECT,				// 领地效果					uint
	TERRITORY_FIGHT_DATA_POKER_LEV_LIMIT,		// 领地战参战部队等级限制	uint
	TERRITORY_FIGHT_DATA_BOSS_NAME,				// 驻守boss名字				varchar

};

static const char* CONST_DB_NAME_TERRITORY_FIGHT_MONSTER = "territory_fight_monster";	// 领地战默认驻守怪
enum TERRITORY_FIGHT_MONSTER_DATA
{
	TERRITORY_FIGHT_MONSTER_DATA_TROOPS_ID = 0,	// 
	TERRITORY_FIGHT_MONSTER_DATA_ID,
	TERRITORY_FIGHT_MONSTER_DATA_POKERID1,
	TERRITORY_FIGHT_MONSTER_DATA_POKERID2,
	TERRITORY_FIGHT_MONSTER_DATA_POKERID3,
	TERRITORY_FIGHT_MONSTER_DATA_POKERID4,
	TERRITORY_FIGHT_MONSTER_DATA_POKERID5,
};

static const char* CONST_DB_NAME_DATA_RESET	= "data_reset";		// 数据重置配置表
enum DATA_RESET_DATA
{
	DATA_RESET_DATA_TYPE = 0,					// 重置类型					uint
	DATA_RESET_DATA_COUNT,						// 重置次数					uint
	DATA_RESET_DATA_COST_TYPE,					// 消耗类型					uint
	DATA_RESET_DATA_COST_NUM,					// 消耗数量					uint
};

static const char* CONST_DB_NAME_SYN_GIFT_BOX	= "syn_giftbox";// 帮派礼盒配置表
enum SYN_GIFT_BOX_DATA
{
	SYN_GIFT_BOX_DATA_TYPE = 0,					// 礼盒类型					uint
	SYN_GIFT_BOX_DATA_LEV,						// 礼盒等级					uint
	SYN_GIFT_BOX_DATA_EXP,						// 礼盒经验					uint
	SYN_GIFT_BOX_DATA_KEEP_TIME,				// 保存时间					uint
	SYN_GIFT_BOX_DATA_DATA1,					// 参数1					uint
	SYN_GIFT_BOX_DATA_DATA2,					// 参数2					uint
	SYN_GIFT_BOX_DATA_RULE_ID,					// 开启奖励规则id			uint
};

static const char* CONST_DB_NAME_LOOKFACE_FRAME = "lookface_frame";	// 头像框配置表
enum LOOKFACE_FRAME_DATA
{
	LOOKFACE_FRAME_DATA_TYPE = 0,				// 头像框类型			uint
	LOOKFACE_FRAME_DATA_VIP_LEV,				// vip等级				uint
	LOOKFACE_FRAME_DATA_SINGLE_ARENA_RANK,		// 当前单队竞技场名次	uint
	LOOKFACE_FRAME_DATA_MULTI_ARENA_RANK,		// 当前多队竞技场名次	uint
	LOOKFACE_FRAME_DATA_TIME_LIMIT,				// 时间限制				uint
	LOOKFACE_FRAME_DATA_PARAM1,					// 预留1				uint
	LOOKFACE_FRAME_DATA_PARAM2,					// 预留2				uint
	LOOKFACE_FRAME_DATA_NAME,					// 名字					uint
};

static const char* CONST_DB_NAME_IP_LIBRARY = "ip_library";		// ip库配置表
enum IP_LIBRARY_DATA
{
	IP_LIBRARY_DATA_ID = 0,				// ID							uint
	IP_LIBRARY_DATA_IP_BEGIN,			// 起始IP						varchar16
	IP_LIBRARY_DATA_IP_END,				// 结束IP						varchar16
	IP_LIBRARY_DATA_IP_BEGIN_INT,		// 起始IP(整数)					uint
	IP_LIBRARY_DATA_IP_END_INT,			// 结束IP(整数)					uint
	IP_LIBRARY_DATA_ADDRESS1,			// 地址1						varchar64
	IP_LIBRARY_DATA_ADDRESS2,			// 地址2						varchar128
	IP_LIBRARY_DATA_ADDRESS_FINAL,		// 归属地区						varchar64
	IP_LIBRARY_DATA_ADDRESS_ID,			// 地区编号						uint
};


static const char* CONST_DB_NAME_ROOM_TYPE = "room_type";
enum ROOM_TYPE_DATA
{
	ROOM_TYPE_DATA_TYPE = 0,		// 房间类型			uint
	ROOM_TYPE_DATA_NAME,			// 房间名字			varchar64
	ROOM_TYPE_DATA_KEEP_TIME,		// 房间持续时间		uint
	ROOM_TYPE_DATA_MAX_MEMBER,		// 最大成员数量		uint
	ROOM_TYPE_DATA_MONSTER1,		// 怪物类型1		uint
	ROOM_TYPE_DATA_MONSTER2,		// 怪物类型2		uint
	ROOM_TYPE_DATA_MONSTER3,		// 怪物类型3		uint
	ROOM_TYPE_DATA_MONSTER4,		// 怪物类型4		uint
	ROOM_TYPE_DATA_MONSTER5,		// 怪物类型5		uint
	ROOM_TYPE_DATA_MONSTER6,		// 怪物类型6		uint
	ROOM_TYPE_DATA_MONSTER7,		// 怪物类型7		uint
	ROOM_TYPE_DATA_MONSTER8,		// 怪物类型8		uint
	ROOM_TYPE_DATA_MONSTER9,		// 怪物类型9		uint
	ROOM_TYPE_DATA_MONSTER10,		// 怪物类型10		uint
	ROOM_TYPE_DATA_MONSTER11,		// 怪物类型11		uint
	ROOM_TYPE_DATA_MONSTER12,		// 怪物类型12		uint
	ROOM_TYPE_DATA_MONSTER13,		// 怪物类型13		uint
	ROOM_TYPE_DATA_MONSTER14,		// 怪物类型14		uint
	ROOM_TYPE_DATA_MONSTER15,		// 怪物类型15		uint
};

static const char* CONST_DB_NAME_ROOM_MONSTER = "room_monster";
enum ROOM_MONSTER_DATA
{
	ROOM_MONSTER_DATA_TYPE = 0,			// 怪物类型								uint
	ROOM_MONSTER_DATA_SORT,				// 怪物形式		1怪物 2采集物			uint
	ROOM_MONSTER_DATA_BATTLE_TYPE,		// 战斗类型		1怪物触发的战斗类型		uint
	ROOM_MONSTER_DATA_REBORN_SECOND,	// 重生秒数		0表示不重生				uint
	ROOM_MONSTER_DATA_PICK_SECOND,		// 采集时间								uint
	ROOM_MONSTER_DATA_PICK_ACTION,		// 采集后action							uint
};

static const char* CONST_DB_NAME_NAME_LIBRARY = "name_library";		// 名字库
enum NAME_LIBRARY_DATA
{
	NAME_LIBRARY_DATA_ID = 0,			// id	uint
	NAME_LIBRARY_DATA_SURNAME,			// 姓	varchar
	NAME_LIBRARY_DATA_NAME,				// 名	varchar
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 常量表重新加载类型
enum RELOAD_CONST_TABLE_TYPE
{
	RELOAD_CONST_TABLE_TYPE_SERVER_START_TIME = 0,
	RELOAD_CONST_TABLE_TYPE_LUA_FILE,
	RELOAD_CONST_TABLE_TYPE_POKER_COLOR_ATTR_SUM,

	RELOAD_CONST_TABLE_TYPE_CONFIGDATA,
	RELOAD_CONST_TABLE_TYPE_CONFIGTEXT,
	RELOAD_CONST_TABLE_TYPE_TASK_DATA,
	RELOAD_CONST_TABLE_TYPE_NEWCARDPRIZE,
	RELOAD_CONST_TABLE_TYPE_NOTIFY_CONFIG,
	RELOAD_CONST_TABLE_TYPE_ACTIVITYCONFIG,
	RELOAD_CONST_TABLE_TYPE_ACTION,
	RELOAD_CONST_TABLE_TYPE_POKER_TYPE,
	RELOAD_CONST_TABLE_TYPE_POKER_STAR_GROW,
	RELOAD_CONST_TABLE_TYPE_POKER_EQUIP,
	RELOAD_CONST_TABLE_TYPE_POKER_STAR,
	RELOAD_CONST_TABLE_TYPE_POKER_COLOR_ATTR,
	RELOAD_CONST_TABLE_TYPE_LEV_EXP,
	RELOAD_CONST_TABLE_TYPE_SIGNPRIZE,
	RELOAD_CONST_TABLE_TYPE_VIP,
	RELOAD_CONST_TABLE_TYPE_ITEM_TYPE,
	RELOAD_CONST_TABLE_TYPE_ITEM_COLOR,
	RELOAD_CONST_TABLE_TYPE_ITEM_STAR_ATTR,
	RELOAD_CONST_TABLE_TYPE_LIVENESS,
	RELOAD_CONST_TABLE_TYPE_SHOP_TYPE,
	RELOAD_CONST_TABLE_TYPE_SHOP_RULE,
	RELOAD_CONST_TABLE_TYPE_ACHIEVEMENT,
	RELOAD_CONST_TABLE_TYPE_LUA_TEXT,
	RELOAD_CONST_TABLE_TYPE_SKILL_TYPE,
	RELOAD_CONST_TABLE_TYPE_DROP_RULE,
	RELOAD_CONST_TABLE_TYPE_BATTLE_TYPE,
	RELOAD_CONST_TABLE_TYPE_BATTLE_ROUND,
	RELOAD_CONST_TABLE_TYPE_BATTLE_MONSTER,
	RELOAD_CONST_TABLE_TYPE_PEIFANG,
	RELOAD_CONST_TABLE_TYPE_CHALLENGE_BOSS,
	RELOAD_CONST_TABLE_TYPE_LOTTERY_TYPE,
	RELOAD_CONST_TABLE_TYPE_LOTTERY_RULE,
	RELOAD_CONST_TABLE_TYPE_PRIZE_TYPE,
	RELOAD_CONST_TABLE_TYPE_PROPERTY_CALCRANK2,
	RELOAD_CONST_TABLE_TYPE_MONEY_AWARD_CHANCE,
	RELOAD_CONST_TABLE_TYPE_INSTANCE_TYPE,
	RELOAD_CONST_TABLE_TYPE_PUZZLE,
	RELOAD_CONST_TABLE_TYPE_PUZZLE_BUFF,
	RELOAD_CONST_TABLE_TYPE_PAY_CONFIG,
	RELOAD_CONST_TABLE_TYPE_ARENA_AWARD,
	RELOAD_CONST_TABLE_TYPE_ARENA_AI_POKER,
	RELOAD_CONST_TABLE_TYPE_WAR_ROAD,
	RELOAD_CONST_TABLE_TYPE_WAR_ROAD_TEAM,
	RELOAD_CONST_TABLE_TYPE_TERRITORY_FIGHT,
	RELOAD_CONST_TABLE_TYPE_TERRITORY_FIGHT_MONSTER,
	RELOAD_CONST_TABLE_TYPE_DATA_RESET,
	RELOAD_CONST_TABLE_TYPE_SYN_GIFT_BOX,
	RELOAD_CONST_TABLE_TYPE_LOOKFACE_FRAME,
	RELOAD_CONST_TABLE_TYPE_ROOM_TYPE,
	RELOAD_CONST_TABLE_TYPE_ROOM_MONSTER,
	RELOAD_CONST_TABLE_TYPE_NAME_LIBRARY,
	RELOAD_CONST_TABLE_TYPE_END,
};


#endif // end of _CARD_SERVER_DATABASE_DEFINE_
