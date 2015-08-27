////////////////////////////////////////////////////////////////////////
// Import : 常量库内容全局声明处
// Moudle : DatabaseDefineConst.h
// Author : 陈建军(Chen Jianjun)
// Created: 2015-08-27
////////////////////////////////////////////////////////////////////////
#ifndef _DATABASE_DEFINE_CONST_H_
#define _DATABASE_DEFINE_CONST_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//static const char* CONST_DB_NAME_CONFIG = "config";				// 常量配置表
//enum CONFIG_DATA
//{
//	CONFIGDATA_BEGIN = 0,
//	CONFIGDATA_TYPE = CONFIGDATA_BEGIN,			// typeid	uint
//	CONFIGDATA_DATA1,							// 数据1	uint
//	CONFIGDATA_DATA2,							// 数据2	uint
//	CONFIGDATA_DATA3,							// 数据3	uint
//	CONFIGDATA_DATA4,							// 数据4	uint
//	CONFIGDATA_DATA5,							// 数据5	uint
////	CONFIGDATA_COMMENT,							// 注释字段, 不加载内存
//	CONFIGDATA_END,
//};
//
//static const char* CONST_DB_NAME_CONFIG_TEXT = "config_text";	// 常量配置文本表
//enum CONFIG_TEXT_DATA
//{
//	CONFIG_TEXT_DATA_ID		= 0,	// id
//	CONFIG_TEXT_DATA_TEXT	= 1,	// 可配置文字
//};
//
//static const char* CONST_DB_NAME_TASK_CONFIG_DATA = "task";		// 任务配置表
//enum ETASK_CONFIG_DATA
//{
//	ETASK_CONFIG_DATA_ID		= 0,	// 编号										uint
//	ETASK_CONFIG_DATA_TYPE,				// 任务类型									uint
//	ETASK_CONFIG_DATA_STEP,				// 步骤(步骤(从1开始且连续))				uint
//	ETASK_CONFIG_DATA_ISCHAIN,			// 是否是任务链(0:不是，1:是)				uint
//	ETASK_CONFIG_DATA_LIMIT_TIME,		// 时间限制( 0:无限制, >0:限制时间(秒) )	uint
//	ETASK_CONFIG_DATA_NEED_TYPE1,		// 任务需要类型1							uint
//	ETASK_CONFIG_DATA_NEED_NUM1,		// 类型1需要数量							uint
//	ETASK_CONFIG_DATA_NEED_TYPE2,		// 任务需要类型2							uint
//	ETASK_CONFIG_DATA_NEED_NUM2,		// 类型2需要数量							uint
//	ETASK_CONFIG_DATA_NEED_TYPE3,		// 任务需要类型3							uint
//	ETASK_CONFIG_DATA_NEED_NUM3,		// 类型3需要数量							uint
//	ETASK_CONFIG_DATA_RECEIVE_ACTION,	// 接收任务脚本action						uint
//	ETASK_CONFIG_DATA_FINISH_ACTION,	// 完成任务脚本action						uint
//	ETASK_CONFIG_DATA_GIVEUP_ACTION,	// 放弃任务脚本action						uint
//	ETASK_CONFIG_DATA_NAME,				// 任务名									varchar128
//};
//
//
//static const char* CONST_DB_NEWCARD_PRIZE = "newcard_prize";	// 新手卡奖励配置表
//enum NEWCARD_PRIZE_DATA
//{
//	NEWCARD_PRIZE_DATA_ID = 0,		// id		uint
//	NEWCARD_PRIZE_DATA_TYPE,		// 卡类型	uint
//	NEWCARD_PRIZE_DATA_GIVEMASKID,	// 掩码ID	uint
//	// 以下字段为10个奖励道具信息（道具type uint, 道具数量 uint, 是否绑定 uint）
//	NEWCARD_PRIZE_DATA_ITEMTYPE1,
//	NEWCARD_PRIZE_DATA_ITEMCOUNT1,
//	NEWCARD_PRIZE_DATA_ITEMTYPE2,
//	NEWCARD_PRIZE_DATA_ITEMCOUNT2,
//	NEWCARD_PRIZE_DATA_ITEMTYPE3,
//	NEWCARD_PRIZE_DATA_ITEMCOUNT3,
//	NEWCARD_PRIZE_DATA_ITEMTYPE4,
//	NEWCARD_PRIZE_DATA_ITEMCOUNT4,
//	NEWCARD_PRIZE_DATA_ITEMTYPE5,
//	NEWCARD_PRIZE_DATA_ITEMCOUNT5,
//	NEWCARD_PRIZE_DATA_ITEMTYPE6,
//	NEWCARD_PRIZE_DATA_ITEMCOUNT6,
//	NEWCARD_PRIZE_DATA_ITEMTYPE7,
//	NEWCARD_PRIZE_DATA_ITEMCOUNT7,
//	NEWCARD_PRIZE_DATA_ITEMTYPE8,
//	NEWCARD_PRIZE_DATA_ITEMCOUNT8,
//	NEWCARD_PRIZE_DATA_ITEMTYPE9,
//	NEWCARD_PRIZE_DATA_ITEMCOUNT9,
//	NEWCARD_PRIZE_DATA_ITEMTYPE10,
//	NEWCARD_PRIZE_DATA_ITEMCOUNT10,
//};
//
//static const char* CONST_DB_NAME_NOTIFY_CONFIG = "notify";		// 公告配置表
//enum NOTIFY_CONFIG
//{
//	NOTIFY_CONFIG_ID = 0,				// 编号										bigint
//	NOTIFY_CONFIG_CHANNEL,				// 频道										uint
//	NOTIFY_CONFIG_TIME_TYPE,			// 时间类型									uint
//	NOTIFY_CONFIG_TIME,					// 时间										bigint
//	NOTIFY_CONFIG_TEXT,					// 公告内容									varchar255
//	NOTIFY_CONFIG_GROUP,				// 服务器组									uint
//};
//static const char* CONST_DB_NAME_ACTIVITY_CONFIG = "activities";	// 活动表
//enum ACTIVITY_CONFIG_DATA
//{
//	ACTIVITY_CONFIG_DATA_BEGIN = 0,
//	ACTIVITY_CONFIG_DATA_ID	 = ACTIVITY_CONFIG_DATA_BEGIN,	// 自增长id				uint
//	ACTIVITY_CONFIG_DATA_TYPE,								// typeid				uint
//	ACTIVITY_CONFIG_DATA_TIME_TYPE,							// 活动时间类别			uint
//	ACTIVITY_CONFIG_DATA_BEGIN_TIME,						// 开始时间				uint
//	ACTIVITY_CONFIG_DATA_END_TIME,							// 结束时间				uint
//	ACTIVITY_CONFIG_DATA_BEGIN_ACTION,						// 开始触发脚本			uint
//	ACTIVITY_CONFIG_DATA_END_ACTION,						// 结束触发脚本			uint
//	ACTIVITY_CONFIG_DATA_ENTER_ACTION,						// 客户端触发进入脚本	uint
//	ACTIVITY_CONFIG_DATA_EXIT_ACTION,						// 客户端触发退出脚本	uint
//	ACTIVITY_CONFIG_DATA_SERVER_GROUP,						// 服务器组				uint
//	ACTIVITY_CONFIG_DATA_LINE,								// 线路					uint
//	ACTIVITY_CONFIG_DATA_PARAM1,							// 备用参数1			uint
//	ACTIVITY_CONFIG_DATA_PARAM2,							// 备用参数2			uint
////  ACTIVITY_CONFIG_DATA_COMMENT,							// 注释字段, 不加载内存
//	ACTIVITY_CONFIG_DATA_END,
//};
//
//
//static const char* CONST_DB_ACTION = "action";	// 脚本action表
//enum ACTION_DATA
//{
//	ACTION_DATA_ID = 0,				// id			uint
//	ACTION_DATA_FILE_PATH,			// 路径			varchar128
//	ACTION_DATA_FUNCTION,			// 函数			varchar128
//	ACTION_DATA_CLIENT_TRIGGER,		// 客户端触发	uint
//};
//
//
//
//static const char* CONST_DB_POKER_TYPE = "poker_type";	// 卡牌类型表
//enum POKER_TYPE_DATA
//{
//	POKER_TYPE_DATA_ID = 0,			// 卡牌类型id				uint
//	POKER_TYPE_DATA_NAME,			// 名称						varchar32
//	POKER_TYPE_DATA_CAMP,			// 阵营		POKER_CAMP		uint
//	POKER_TYPE_DATA_FIGHT_POS,		// 战斗位置	POKER_FIGHT_POS	uint
//	POKER_TYPE_DATA_POS_SORT,		// 站位排序					uint
//	POKER_TYPE_DATA_INIT_LIFE,		// 初始体质					uint
//	POKER_TYPE_DATA_INIT_MANA,		// 初始魔力					uint
//	POKER_TYPE_DATA_INIT_STR,		// 初始力量					uint
//	POKER_TYPE_DATA_INIT_STA,		// 初始耐力					uint
//	POKER_TYPE_DATA_INIT_DEX,		// 初始敏捷					uint
//	POKER_TYPE_DATA_INIT_HP,		// 初始血量					uint
//	POKER_TYPE_DATA_INIT_ATK,		// 初始伤害					uint
//	POKER_TYPE_DATA_INIT_STAR,		// 初始星级					uint
//	POKER_TYPE_DATA_SKILL_SP,		// 特技						uint
//	POKER_TYPE_DATA_SKILL_AUTO1,	// 自动技能1				uint
//	POKER_TYPE_DATA_SKILL_AUTO2,	// 自动技能2				uint
//	POKER_TYPE_DATA_SKILL_AUTO3,	// 自动技能3				uint
//	POKER_TYPE_DATA_SKILL_JOINT,	// 连携技能					uint
//	POKER_TYPE_DATA_ANGER_PARAM,	// 愤怒转化系数（万分比）	uint
//	POKER_TYPE_DATA_NEED_ITEMTYPE,	// 对应灵魂石类型			uint
//};
//
//static const char* CONST_DB_POKER_STAR_GROW = "poker_star_grow";	// 卡牌星级成长表
//enum POKER_STAR_GROW_DATA
//{
//	POKER_STAR_GROW_DATA_TYPE = 0,	// 卡牌类型		uint
//	POKER_STAR_GROW_DATA_STAR,		// 卡牌星级		uint
//	POKER_STAR_GROW_DATA_LIFE_GROW,	// 体质成长		uint
//	POKER_STAR_GROW_DATA_MANA_GROW,	// 魔力成长		uint
//	POKER_STAR_GROW_DATA_STR_GROW,	// 力量成长		uint
//	POKER_STAR_GROW_DATA_STA_GROW,	// 耐力成长		uint
//	POKER_STAR_GROW_DATA_DEX_GROW,	// 敏捷成长		uint
//};
//
//static const char* CONST_DB_POKER_EQUIP = "poker_equip";	// 卡牌装备配置表
//enum POKER_EQUIP_DATA
//{
//	POKER_EQUIP_DATA_POKER_TYPE = 0,	// 卡牌类型			uint
//	POKER_EQUIP_DATA_POKER_COLOR,		// 卡牌颜色(1-17)	uint
//	POKER_EQUIP_DATA_EQUIP1_TYPE,		// 武器类型			uint
//	POKER_EQUIP_DATA_EQUIP2_TYPE,		// 头盔类型			uint
//	POKER_EQUIP_DATA_EQUIP3_TYPE,		// 项链类型			uint
//	POKER_EQUIP_DATA_EQUIP4_TYPE,		// 腰带类型			uint
//	POKER_EQUIP_DATA_EQUIP5_TYPE,		// 衣服类型			uint
//	POKER_EQUIP_DATA_EQUIP6_TYPE,		// 鞋子类型			uint
//};
//
//static const char* CONST_DB_POKER_STAR = "poker_star";	// 卡牌星级配置表
//enum POKER_STAR_DATA
//{
//	POKER_STAR_DATA_STAR = 0,			// 星级								uint
//	POKER_STAR_DATA_COMPOUND_NEED,		// 合成时需求灵魂石数量				uint
//	POKER_STAR_DATA_RESOLVE_AUTO,		// 自动分解获得灵魂石数量			uint
//	POKER_STAR_DATA_UPGRADE_NEED,		// 升星需要灵魂石, 满星填0			uint
//};
//
//static const char* CONST_DB_LEV_EXP = "lev_exp"; // 等级经验表
//enum LEV_EXP_DATA
//{
//	LEV_EXP_DATA_TYPE = 0,		// 类型 LEV_EXP_TYPE		uint
//	LEV_EXP_DATA_LEV,			// 等级						uint
//	LEV_EXP_DATA_EXP,			// 经验						bigint
//};
//
//static const char* CONST_DB_SIGN_PRIZE = "sign_prize";	// 签到奖励配置表
//enum SIGN_PRIZE_DATA
//{
//	SIGN_PRIZE_DATA_ID = 0,			// id（天数，连续签到1000+天数）uint
//	SIGN_PRIZE_DATA_MUL_PRIZE,		// 奖励倍数	uint
//	SIGN_PRIZE_DATA_VIP_LEV,		// 需求VIP等级	uint
//	// 以下字段为4个奖励道具信息（道具type uint, 道具数量 uint, 是否绑定 uint）
//	SIGN_PRIZE_DATA_ITEMTYPE1,
//	SIGN_PRIZE_DATA_ITEMCOUNT1,
//	SIGN_PRIZE_DATA_ITEMTYPE2,
//	SIGN_PRIZE_DATA_ITEMCOUNT2,
//	SIGN_PRIZE_DATA_ITEMTYPE3,
//	SIGN_PRIZE_DATA_ITEMCOUNT3,
//};
//
//static const char* CONST_DB_AUTO_RELOAD = "auto_reload";	// 自动加载配置表
//enum AUTO_RELOAD_DATA
//{
//	AUTO_RELOAD_DATA_TABLE_NAME = 0,	// 表名					varchar255
//	AUTO_RELOAD_DATA_GROUP,				// 服务器组 填0表示全部	uint
//	AUTO_RELOAD_DATA_LINE,				// 服务器线 填0表示全部	uint
//	AUTO_RELOAD_DATA_UTC_TIME,			// 指定时间 填0表示即时	uint
//};
//
//static const char* CONST_DB_VIP = "vip";		// VIP配置表
//enum VIP_DATA
//{
//	VIP_DATA_TYPE	= 0,		// vip类型	uint
//	VIP_DATA_LEV,				// vip等级	uint
//	VIP_DATA_VALUE,				// Vaule	uint
//};
//
//static const char* CONST_DB_NAME_ITEM_TYPE = "item_type";	// 物品类型表
//enum ITEM_TYPE_DATA
//{
//	ITEM_TYPE_DATA_ID = 0,			// 类型			uint
//	ITEM_TYPE_DATA_NAME,			// 名字			uint
//	ITEM_TYPE_DATA_COLOR,			// 颜色			uint
//	ITEM_TYPE_DATA_AMOUNT_LIMIT,	// 叠加上限		uint
//	ITEM_TYPE_DATA_CLASSIIFY,		// 分类			uint
//	ITEM_TYPE_DATA_SORT,			// 物品区分		uint
//	ITEM_TYPE_DATA_DATA1,			// 数据1		uint
//	ITEM_TYPE_DATA_DATA2,			// 数据2		uint
//	ITEM_TYPE_DATA_DATA3,			// 数据3		uint
//	ITEM_TYPE_DATA_ACTION,			// action		uint
//	ITEM_TYPE_DATA_MONOPOLY,		// monopoly		uint
//	ITEM_TYPE_DATA_SALE_MONEY_TYPE,	// 售出货币类型 uint
//	ITEM_TYPE_DATA_SALE_PRICE,		// 售出价格		uint
//	ITEM_TYPE_DATA_PEIFANG_ID,		// 配方ID		uint
//	ITEM_TYPE_DATA_LIMIT_LEV,		// 限制等级		uint
//	ITEM_TYPE_DATA_END,
//};
//
//static const char* CONST_DB_NAME_ITEM_COLOR = "item_color";	// 物品颜色配置表
//enum ITEM_COLOR_DATA
//{
//	ITEM_COLOR_DATA_COLOR = 0,	// 颜色			uint
//	ITEM_COLOR_DATA_STAR1,		// 1星升星上限	uint
//	ITEM_COLOR_DATA_STAR2,		// 2星升星上限	uint
//	ITEM_COLOR_DATA_STAR3,		// 3星升星上限	uint
//	ITEM_COLOR_DATA_STAR4,		// 4星升星上限	uint
//	ITEM_COLOR_DATA_STAR5,		// 5星升星上限	uint
//	ITEM_COLOR_DATA_PRICE,		// 每点价格		uint
//};
//
//static const char* CONST_DB_NAME_ITEM_STAR_ATTR = "item_star_attr";	// 物品星级属性
//enum ITEM_STAR_ATTR_DATA
//{
//	ITEM_STAR_ATTR_DATA_TYPE = 0,		// 物品类型		uint
//	ITEM_STAR_ATTR_DATA_STAR,			// 物品星级		uint
//	ITEM_STAR_ATTR_DATA_ATTR_TYPE1,		// 属性类型1	uint
//	ITEM_STAR_ATTR_DATA_ATTR_DATA1,		// 属性数值1	uint
//	ITEM_STAR_ATTR_DATA_ATTR_TYPE2,		// 属性类型2	uint
//	ITEM_STAR_ATTR_DATA_ATTR_DATA2,		// 属性数值2	uint
//	ITEM_STAR_ATTR_DATA_ATTR_TYPE3,		// 属性类型3	uint
//	ITEM_STAR_ATTR_DATA_ATTR_DATA3,		// 属性数值3	uint
//	ITEM_STAR_ATTR_DATA_ATTR_TYPE4,		// 属性类型4	uint
//	ITEM_STAR_ATTR_DATA_ATTR_DATA4,		// 属性数值4	uint
//	ITEM_STAR_ATTR_DATA_ATTR_TYPE5,		// 属性类型5	uint
//	ITEM_STAR_ATTR_DATA_ATTR_DATA5,		// 属性数值5	uint
//};
//
//static const char* CONST_DB_LIVENESS = "liveness";		// 每日活跃配置表
//enum ELIVENESS_CONFIG
//{
//	ELIVENESS_CONFIG_ID = 0,			// 活跃项ID					uint		
//	ELIVENESS_CONFIG_LevLimit,			// 等级限制					uint
//	ELIVENESS_CONFIG_VipLimit,			// VIP等级限制				uint
//	ELIVENESS_CONFIG_BeginTime,			// 开始时间					uint
//	ELIVENESS_CONFIG_EndTime,			// 结束时间					uint
//	ELIVENESS_CONFIG_Val,				// 完成活跃获得的活跃值		uint
//	ELIVENESS_CONFIG_NeedType,			// 需要类型					uint
//	ELIVENESS_CONFIG_NeedNum,			// 需要数量					uint
//	ELIVENESS_CONFIG_AwardAction,		// 发奖励脚本Action			uint
//	ELIVENESS_CONFIG_Title,				// 主题						varchar32
//	ELIVENESS_CONFIG_Content,			// 内容 					varchar64
//};
//
//static const char* CONST_DB_SHOP_TYPE = "shop_type";	// 商店类型配置表
//enum SHOP_TYPE
//{
//	SHOP_TYPE_BEGIN = 0,
//	SHOP_TYPE_ID = SHOP_TYPE_BEGIN,		// 商店类型					uint
//	SHOP_TYPE_BLANK_LIMIT,				// 格子上限					uint
//	SHOP_TYPE_REFRESH_MONEY_TYPE,		// 手动刷新所需的货币类型	uint
//	SHOP_TYPE_REFRESH_PRICE,			// 手动刷新价格				uint
//	SHOP_TYPE_AUTO_REFRESH_TIME1,		// 自动刷新时间1			uint
//	SHOP_TYPE_AUTO_REFRESH_TIME2,		// 自动刷新时间2			uint
//	SHOP_TYPE_AUTO_REFRESH_TIME3,		// 自动刷新时间3			uint
//	SHOP_TYPE_AUTO_REFRESH_TIME4,		// 自动刷新时间4			uint
//	SHOP_TYPE_AUTO_REFRESH_TIME5,		// 自动刷新时间5			uint
//	SHOP_TYPE_REFRESH_RULE1,			// 刷新规则1				uint
//	SHOP_TYPE_REFRESH_RULE2,			// 刷新规则2				uint
//	SHOP_TYPE_REFRESH_RULE3,			// 刷新规则3				uint
//	SHOP_TYPE_REFRESH_RULE4,			// 刷新规则4				uint
//	SHOP_TYPE_REFRESH_RULE5,			// 刷新规则5				uint
//	SHOP_TYPE_REFRESH_RULE6,			// 刷新规则6				uint
//	SHOP_TYPE_REFRESH_RULE7,			// 刷新规则7				uint
//	SHOP_TYPE_REFRESH_RULE8,			// 刷新规则8				uint
//	SHOP_TYPE_REFRESH_RULE9,			// 刷新规则9				uint
//	SHOP_TYPE_REFRESH_RULE10,			// 刷新规则10				uint
//	SHOP_TYPE_REFRESH_RULE11,			// 刷新规则11				uint
//	SHOP_TYPE_REFRESH_RULE12,			// 刷新规则12				uint
//	SHOP_TYPE_END,
//};
//
//static const char* CONST_DB_SHOP_RULE = "shop_rule";		// 商店规则配置表
//enum SHOP_RULE
//{
//	SHOP_RULE_BEGIN = 0,
//	SHOP_RULE_ID = SHOP_RULE_BEGIN,		// 规则类型					uint
//	SHOP_RULE_ITEM_TYPE,				// 物品类型					uint
//	SHOP_RULE_ITEM_NUM,					// 物品数量					uint
//	SHOP_RULE_ITEM_PRICE,				// 物品单价					uint
//	SHOP_RULE_MONEY_TYPE,				// 货币类型					uint
//	SHOP_RULE_DISCOUNT,					// 物品折扣					uint
//	SHOP_RULE_WEIGHT,					// 物品权重					uint
//	SHOP_RULE_END,
//};
//
//static const char* CONST_DB_NAME_ACHIEVEMENT = "achievement";		// 成就配置表
//enum ACHIEVEMENT_DATA
//{
//	ACHIEVEMENT_DATA_BEGIN			= 0,
//	ACHIEVEMENT_DATA_ID				= ACHIEVEMENT_DATA_BEGIN,	// 成就id（五位数，最高位表示类别）	uint
//	ACHIEVEMENT_DATA_SUBINDEX,									// 子类成就序列号（第一个为0）		uint
//	ACHIEVEMENT_DATA_BEFOREID,									// 前置成就id						uint
//	ACHIEVEMENT_DATA_AFTERID,									// 后续成就id						uint
//	ACHIEVEMENT_DATA_ACTIONID,									// 成就奖励调用脚本action			uint
//	ACHIEVEMENT_DATA_OPEN_TYPE,									// 开启类别							uint
//	ACHIEVEMENT_DATA_OPEN_CONDITION1,							// 开启条件1						uint
//	ACHIEVEMENT_DATA_OPEN_CONDITION2,							// 开启条件2						uint
//	ACHIEVEMENT_DATA_COMPLETE_CONDITION1,						// 完成条件1						uint
//	ACHIEVEMENT_DATA_COMPLETE_CONDITION2,						// 完成条件2						uint
//	ACHIEVEMENT_DATA_END,
//};
//
//static const char* CONST_DB_NAME_LUA_TEXT = "lua_text";	// 脚本文字表
//enum LUA_TEXT_DATA
//{
//	LUA_TEXT_DATA_ID = 0,	// id		uint
//	LUA_TEXT_DATA_TEXT,		// 文字		varchar512
//};
//
//static const char* CONST_DB_NAME_SKILL_TYPE = "skill_type";		// 技能类型配置表
//enum SKILL_TYPE_DATA
//{
//	SKILL_TYPE_DATA_ID	= 0,			// 技能id			uint
//	SKILL_TYPE_DATA_SORT,				// 技能分类			uint
//	SKILL_TYPE_DATA_NEED_LEV,			// 需求等级			uint
//	SKILL_TYPE_DATA_COST_MONEY,			// 花费进步			uint
//	SKILL_TYPE_DATA_COST_POINT,			// 花费技能点		uint
//	SKILL_TYPE_DATA_POWER,				// 威力				uint
//	SKILL_TYPE_DATA_POWER_ADD,			// 威力增量			uint
//	SKILL_TYPE_DATA_POWER2,				// 威力2			uint
//	SKILL_TYPE_DATA_POWER2_ADD,			// 威力2增量		uint
//};
//
//static const char* CONST_DB_DROP_RULE = "drop_rule";	// 掉落规则表
//enum DROP_RULE_DATA
//{
//	DROP_RULE_DATA_ID		= 0,		// 掉落规则id							uint
//	DROP_RULE_DATA_TYPE,				// 掉落规则类型	DROP_RULE_TYPE			uint
//	DROP_RULE_DATA_COUNT,				// 次数, 配合类型执行					uint
//	DROP_RULE_DATA_CHANCE,				// 掉落概率, 万分比						uint
//
//	DROP_RULE_DATA_GROUP1_TYPE,			// 掉落组1 类型	DROP_RULE_GROUP_TYPE	uint
//	DROP_RULE_DATA_GROUP1_COUNT,		// 掉落组1 数量							uint
//	DROP_RULE_DATA_GROUP1_WEIGHT,		// 掉落组1 权重							uint
//	DROP_RULE_DATA_GROUP1_GROUP,		// 掉落组1 归属分类						uint
//
//	DROP_RULE_DATA_GROUP2_TYPE,			// 掉落组2 类型	DROP_RULE_GROUP_TYPE	uint
//	DROP_RULE_DATA_GROUP2_COUNT,		// 掉落组2 数量							uint
//	DROP_RULE_DATA_GROUP2_WEIGHT,		// 掉落组2 权重							uint
//	DROP_RULE_DATA_GROUP2_GROUP,		// 掉落组2 归属分类						uint
//
//	DROP_RULE_DATA_GROUP3_TYPE,			// 掉落组3 类型	DROP_RULE_GROUP_TYPE	uint
//	DROP_RULE_DATA_GROUP3_COUNT,		// 掉落组3 数量							uint
//	DROP_RULE_DATA_GROUP3_WEIGHT,		// 掉落组3 权重							uint
//	DROP_RULE_DATA_GROUP3_GROUP,		// 掉落组3 归属分类						uint
//
//	DROP_RULE_DATA_GROUP4_TYPE,			// 掉落组4 类型	DROP_RULE_GROUP_TYPE	uint
//	DROP_RULE_DATA_GROUP4_COUNT,		// 掉落组4 数量							uint
//	DROP_RULE_DATA_GROUP4_WEIGHT,		// 掉落组4 权重							uint
//	DROP_RULE_DATA_GROUP4_GROUP,		// 掉落组4 归属分类						uint
//
//	DROP_RULE_DATA_GROUP5_TYPE,			// 掉落组5 类型	DROP_RULE_GROUP_TYPE	uint
//	DROP_RULE_DATA_GROUP5_COUNT,		// 掉落组5 数量							uint
//	DROP_RULE_DATA_GROUP5_WEIGHT,		// 掉落组5 权重							uint
//	DROP_RULE_DATA_GROUP5_GROUP,		// 掉落组5 归属分类						uint
//
//	DROP_RULE_DATA_GROUP6_TYPE,			// 掉落组6 类型	DROP_RULE_GROUP_TYPE	uint
//	DROP_RULE_DATA_GROUP6_COUNT,		// 掉落组6 数量							uint
//	DROP_RULE_DATA_GROUP6_WEIGHT,		// 掉落组6 权重							uint
//	DROP_RULE_DATA_GROUP6_GROUP,		// 掉落组6 归属分类						uint
//
//	DROP_RULE_DATA_GROUP7_TYPE,			// 掉落组7 类型	DROP_RULE_GROUP_TYPE	uint
//	DROP_RULE_DATA_GROUP7_COUNT,		// 掉落组7 数量							uint
//	DROP_RULE_DATA_GROUP7_WEIGHT,		// 掉落组7 权重							uint
//	DROP_RULE_DATA_GROUP7_GROUP,		// 掉落组7 归属分类						uint
//
//	DROP_RULE_DATA_GROUP8_TYPE,			// 掉落组8 类型	DROP_RULE_GROUP_TYPE	uint
//	DROP_RULE_DATA_GROUP8_COUNT,		// 掉落组8 数量							uint
//	DROP_RULE_DATA_GROUP8_WEIGHT,		// 掉落组8 权重							uint
//	DROP_RULE_DATA_GROUP8_GROUP,		// 掉落组8 归属分类						uint
//};
//
//
//static const char* CONST_DB_BATTLE_TYPE = "battle_type";	// 战斗配置表
//enum BATTLE_TYPE_DATA
//{
//	BATTLE_TYPE_DATA_TYPE = 0,		// 战斗类型					uint
//	BATTLE_TYPE_DATA_SORT,			// 类型 对应BATTLE_SORT		uint
//	BATTLE_TYPE_DATA_NAME,			// 名字						varchar32
//	BATTLE_TYPE_DATA_ROUND1,		// 轮次1 id					uint
//	BATTLE_TYPE_DATA_ROUND2,		// 轮次2 id					uint
//	BATTLE_TYPE_DATA_ROUND3,		// 轮次3 id					uint
//	BATTLE_TYPE_DATA_DROP_ID,		// 掉落 id					uint
//	BATTLE_TYPE_DATA_WIN_ACTION,	// 胜利执行脚本				uint
//	BATTLE_TYPE_DATA_TIME_LIMIT,	// 战斗时间限制				uint
//	BATTLE_TYPE_DATA_SAVE_FLAG,		// 存档标记					uint
//	BATTLE_TYPE_DATA_EXP,			// 关卡总经验				uint
//};
//
//static const char* CONST_DB_BATTLE_ROUND = "battle_round";	// 战斗轮次表
//enum BATTLE_ROUND_DATA
//{
//	BATTLE_ROUND_DATA_ID = 0,		// 轮次id		uint
//	BATTLE_ROUND_DATA_MONSTER1_ID,	// 怪物1 id		uint
//	BATTLE_ROUND_DATA_MONSTER2_ID,	// 怪物2 id		uint
//	BATTLE_ROUND_DATA_MONSTER3_ID,	// 怪物3 id		uint
//	BATTLE_ROUND_DATA_MONSTER4_ID,	// 怪物4 id		uint
//	BATTLE_ROUND_DATA_MONSTER5_ID,	// 怪物5 id		uint
//	BATTLE_ROUND_DATA_DROP_ID,		// 掉落  id		uint
//};
//
//static const char* CONST_DB_BATTLE_MONSTER = "battle_monster";	// 战斗怪物配置表
//enum BATTLE_MONSTER_DATA
//{
//	BATTLE_MONSTER_DATA_TYPE = 0,						// 怪物类型						uint	
//	BATTLE_MONSTER_DATA_NAME,							// 怪物名字						varchar32
//	BATTLE_MONSTER_DATA_FIGHT_POS,						// 战斗位置, 前1, 中2, 后3		uint
//	BATTLE_MONSTER_DATA_POS_SORT,						// 站位排序						uint
//	BATTLE_MONSTER_DATA_LEV,							// 等级							uint
//	BATTLE_MONSTER_DATA_STAR,							// 星级							uint
//	BATTLE_MONSTER_DATA_COLOR,							// 颜色							uint
//	BATTLE_MONSTER_DATA_HP,								// 二级属性 气血				uint
//	BATTLE_MONSTER_DATA_SP,								// 二级属性	愤怒				uint
//	BATTLE_MONSTER_DATA_HIT,							// 二级属性	命中				uint
//	BATTLE_MONSTER_DATA_ATK,							// 二级属性	伤害				uint
//	BATTLE_MONSTER_DATA_DEF,							// 二级属性	防御				uint
//	BATTLE_MONSTER_DATA_SPD,							// 二级属性	速度				uint
//	BATTLE_MONSTER_DATA_DODGE,							// 二级属性	闪避				uint
//	BATTLE_MONSTER_DATA_MAGIC,							// 二级属性	灵力				uint
//	BATTLE_MONSTER_DATA_HP_RECOVER,						// 特殊属性 气血回复			uint
//	BATTLE_MONSTER_DATA_SP_RECOVER,						// 特殊属性	愤怒回复			uint
//	BATTLE_MONSTER_DATA_PHY_CRIT,						// 特殊属性	物暴				uint
//	BATTLE_MONSTER_DATA_MAG_CRIT,						// 特殊属性	法爆				uint
//	BATTLE_MONSTER_DATA_VAMPIRE_LEV,					// 特殊属性	吸血等级			uint
//	BATTLE_MONSTER_DATA_SP_SPEND_DECREASE,				// 特殊属性	愤怒消耗降低%		uint
//	BATTLE_MONSTER_DATA_CURE_INCREASE,					// 特殊属性	治疗技能效果提高%	uint
//	BATTLE_MONSTER_DATA_SKILL_SP_TYPE,					// 特技类型						uint
//	BATTLE_MONSTER_DATA_SKILL_SP_LEV,					// 特技等级						uint
//	BATTLE_MONSTER_DATA_SKILL_AUTO1_TYPE,				// 自动技能1 类型				uint
//	BATTLE_MONSTER_DATA_SKILL_AUTO1_LEV,				// 自动技能1 等级				uint
//	BATTLE_MONSTER_DATA_SKILL_AUTO2_TYPE,				// 自动技能2 类型				uint
//	BATTLE_MONSTER_DATA_SKILL_AUTO2_LEV,				// 自动技能2 等级				uint
//	BATTLE_MONSTER_DATA_SKILL_AUTO3_TYPE,				// 自动技能3 类型				uint
//	BATTLE_MONSTER_DATA_SKILL_AUTO3_LEV,				// 自动技能3 等级				uint
//	BATTLE_MONSTER_DATA_SKILL_SKILL_JOINT_TYPE,			// 连携技能 类型				uint
//	BATTLE_MONSTER_DATA_SKILL_SKILL_JOINT_LEV,			// 连携技能 等级				uint
//	BATTLE_MONSTER_DATA_ANGER_PARAM,					// 愤怒转化系数%				uint
//	BATTLE_MONSTER_DATA_DROP_ID,						// 掉落规则						uint
//	BATTLE_MONSTER_DATA_KILL_ACTION,					// 击杀action					uint
//};
//
//static const char* CONST_DB_NAME_PEIFANG_TYPE = "peifang_type";	// 配方类型配置表
//enum PEIFANG_TYPE_DATA
//{
//	PEIFANG_TYPE_DATA_ID = 0,			// 配方id			uint
//	PEIFANG_TYPE_DATA_AWARD_ITEMTYPE,	// 获得物品类型		uint
//	PEIFANG_TYPE_DATA_AWARD_ITEMNUM,	// 获得物品数量		uint
//	PEIFANG_TYPE_DATA_SPEND_ITEMTYPE1,	// 消耗物品类型1	uint
//	PEIFANG_TYPE_DATA_SPEND_ITEMNUM1,	// 消耗物品数量1	uint
//	PEIFANG_TYPE_DATA_SPEND_ITEMTYPE2,	// 消耗物品类型2	uint
//	PEIFANG_TYPE_DATA_SPEND_ITEMNUM2,	// 消耗物品数量2	uint
//	PEIFANG_TYPE_DATA_SPEND_ITEMTYPE3,	// 消耗物品类型3	uint
//	PEIFANG_TYPE_DATA_SPEND_ITEMNUM3,	// 消耗物品数量3	uint
//	PEIFANG_TYPE_DATA_SPEND_ITEMTYPE4,	// 消耗物品类型4	uint
//	PEIFANG_TYPE_DATA_SPEND_ITEMNUM4,	// 消耗物品数量4	uint
//	PEIFANG_TYPE_DATA_COST_MONEY_TYPE,	// 消耗货币类型		uint
//	PEIFANG_TYPE_DATA_COST_PRICE,		// 消耗价钱			uint
//};
//
//static const char* CONST_DB_CHALLENGE_BOSS_CONFIG = "challenge_boss";	// 挑战boss配置表
//enum CHALLENGE_BOSS_CONFIG
//{
//	CHALLENGE_BOSS_CONFIG_BOSS_TYPE = 0,	// boss类型			uint
//	CHALLENGE_BOSS_CONFIG_DEGREE,			// 难度				uint
//	CHALLENGE_BOSS_CONFIG_BATTLE_TYPE,		// 对应战斗类型		uint
//	CHALLENGE_BOSS_CONFIG_NEED_LEV,			// 需要等级			uint
//	CHALLENGE_BOSS_CONFIG_ITEM1,			// 首掉物品1		uint
//	CHALLENGE_BOSS_CONFIG_ITEM1_NUM,		// 首掉物品1数量	uint
//	CHALLENGE_BOSS_CONFIG_ITEM2,			// 首掉物品2		uint
//	CHALLENGE_BOSS_CONFIG_ITEM2_NUM,		// 首掉物品2数量	uint
//	CHALLENGE_BOSS_CONFIG_ITEM3,			// 首掉物品3		uint
//	CHALLENGE_BOSS_CONFIG_ITEM3_NUM,		// 首掉物品3数量	uint
//	CHALLENGE_BOSS_CONFIG_ITEM4,			// 首掉物品4		uint
//	CHALLENGE_BOSS_CONFIG_ITEM5_NUM,		// 首掉物品4数量	uint
//	CHALLENGE_BOSS_CONFIG_DROP_ID,			// 非首掉规则ID		uint
//	CHALLENGE_BOSS_CONFIG_BOSS_NAME,		// boss名			varchar32
//};
//
//static const char* CONST_DB_NAME_LOTTERY_TYPE = "lottery_type";		// 抽奖类型配置表
//enum LOTTERY_TYPE_DATA
//{
//	LOTTERY_TYPE_DATA_TYPE = 0,				// 抽奖类型			uint
//	LOTTERY_TYPE_DATA_AWARD_SUM,			// 奖品数量			uint
//	LOTTERY_TYPE_DATA_COST_MONEY_TYPE,		// 消耗货币类型		uint
//	LOTTERY_TYPE_DATA_COST_PRICE,			// 消耗价格			uint
//	LOTTERY_TYPE_DATA_BASE_ITEM_TYPE,		// 获得基础物品类型	uint
//	LOTTERY_TYPE_DATA_BASE_ITEM_NUM,		// 获得基础物品数量	uint
//	LOTTERY_TYPE_DATA_RULE_ID1,				// 抽奖规则1		uint
//	LOTTERY_TYPE_DATA_GIVE_COUNT1,			// 抽取次数1		uint
//	LOTTERY_TYPE_DATA_GIVE_CHANCE1,			// 抽取概率1		uint
//	LOTTERY_TYPE_DATA_RULE_ID2,				// 抽奖规则2		uint
//	LOTTERY_TYPE_DATA_GIVE_COUNT2,			// 抽取次数2		uint
//	LOTTERY_TYPE_DATA_GIVE_CHANCE2,			// 抽取概率2		uint
//	LOTTERY_TYPE_DATA_RULE_ID3,				// 抽奖规则3		uint
//	LOTTERY_TYPE_DATA_GIVE_COUNT3,			// 抽取次数3		uint
//	LOTTERY_TYPE_DATA_GIVE_CHANCE3,			// 抽取概率3		uint
//	LOTTERY_TYPE_DATA_RULE_ID4,				// 抽奖规则4		uint
//	LOTTERY_TYPE_DATA_GIVE_COUNT4,			// 抽取次数4		uint
//	LOTTERY_TYPE_DATA_GIVE_CHANCE4,			// 抽取概率4		uint
//};
//
//static const char* CONST_DB_NAME_LOTTERY_RULE = "lottery_rule";	// 抽奖规则配置表
//enum LOTTERY_RULE_DATA
//{
//	LOTTERY_RULE_DATA_RULE_ID = 0,			// 规则id			uint
//	LOTTERY_RULE_DATA_PRIZE_TYPE,			// 奖励类型			uint
//	LOTTERY_RULE_DATA_WEIGHT,				// 奖励权重			uint
//	LOTTERY_RULE_DATA_TIME_TYPE,			// 时间类型(0永久，1天，2周，3月)			uint
//	LOTTERY_RULE_DATA_TIME_INDEX,			// 索引类型(周：0-6位表示，月0-31位表示)	uint
//	LOTTERY_RULE_DATA_BEGIN_TIME,			// 奖品生效时间		uint
//	LOTTERY_RULE_DATA_END_TIME,				// 奖品失效时间		uint
//};
//
//static const char* CONST_DB_NAME_PRIZE_TYPE = "prize_type";		// 奖励类型配置表
//enum PRIZE_TYPE_DATA
//{
//	PRIZE_TYPE_DATA_ID		= 0,			// 奖励id			uint
//	PRIZE_TYPE_DATA_TYPE,					// 奖品类型			uint
//	PRIZE_TYPE_DATA_MIN_NUM,				// 最小奖品数量		uint
//	PRIZE_TYPE_DATA_MAX_NUM,				// 最大奖品数量（若有值则随机取数量）		uint
//};
//
//static const char* CONST_DB_NAME_PROPERTY_CALCRANK2 = "property_calcrank2";	// 2级属性结算配置表
//enum PROPERTY_CALCRANK2_DATA
//{
//	PROPERTY_CALCRANK2_DATA_TYPE = 0,	// 属性项			uint
//	PROPERTY_CALCRANK2_DATA_LIFE,		// 体质:气血系数	uint
//	PROPERTY_CALCRANK2_DATA_MANA,		// 魔力:灵力系数	uint
//	PROPERTY_CALCRANK2_DATA_STR_HIT,	// 力量:命中系数	uint
//	PROPERTY_CALCRANK2_DATA_STR_ATK,	// 力量:伤害系数	uint
//	PROPERTY_CALCRANK2_DATA_STA,		// 耐力:防御系数	uint
//	PROPERTY_CALCRANK2_DATA_DEX,		// 敏捷:躲避系数	uint
//};
//
//static const char* CONST_DB_NAME_MONEY_AWARD_CHANCE = "money_award_chance";	// 摇钱树多倍奖励和几率配置表
//enum MONEY_AWARD_CHANCE_DATA
//{
//	MONEY_AWARD_CHANCE_DATA_COUNT = 0,		// 摇钱次数		uint
//	MONEY_AWARD_CHANCE_DATA_COST,			// 摇钱消耗		uint
//	MONEY_AWARD_CHANCE_DATA_MULTIPLE1,		// 暴击倍数1	uint
//	MONEY_AWARD_CHANCE_DATA_CRILCHANCE1,	// 暴击几率1	uint
//	MONEY_AWARD_CHANCE_DATA_MULTIPLE2,		// 暴击倍数2	uint
//	MONEY_AWARD_CHANCE_DATA_CRILCHANCE2,	// 暴击几率2	uint
//	MONEY_AWARD_CHANCE_DATA_MULTIPLE3,		// 暴击倍数3	uint
//	MONEY_AWARD_CHANCE_DATA_CRILCHANCE3,	// 暴击几率3	uint
//	MONEY_AWARD_CHANCE_DATA_MULTIPLE4,		// 暴击倍数4	uint
//	MONEY_AWARD_CHANCE_DATA_CRILCHANCE4,	// 暴击几率4	uint
//};
//
//static const char* CONST_DB_NAME_INSTANCE_TYPE = "instance_type";	// 副本类型配置表
//enum INSTANCE_TYPE_DATA
//{
//	INSTANCE_TYPE_DATA_TYPE = 0,			// 副本类型（1金币产出，2经验产出）		uint
//	INSTANCE_TYPE_DATA_DIFFICULTY,			// 副本难度								uint
//	INSTANCE_TYPE_DATA_OPENTIME_TYPE,		// 副本开启时间类型（1天，2周，3月）	uint
//	INSTANCE_TYPE_DATA_OPENTIME_INDEX,		// 副本开启时间索引（天：0；周、月：32位天索引）	uint
//	INSTANCE_TYPE_DATA_OPENTIME_BEGIN,		// 副本开启时间开始						uint
//	INSTANCE_TYPE_DATA_OPENTIME_END,		// 副本开启时间结束						uint
//	INSTANCE_TYPE_DATA_OPEN_LEV,			// 开启等级								uint
//	INSTANCE_TYPE_DATA_COST_POWER,			// 消耗体力								uint
//	INSTANCE_TYPE_DATA_BATTLE_TYPE,			// 战斗类型								uint
//};
//
//static const char* CONST_DB_NAME_POKER_COLOR_ATTR = "poker_color_attr";	// 卡牌颜色属性配置表
//enum POKER_COLOR_ATTR_DATA
//{
//	POKER_COLOR_ATTR_DATA_POKER_COLOR = 0,	// 卡牌颜色		uint
//	POKER_COLOR_ATTR_DATA_LIFE,				// 体质			uint
//	POKER_COLOR_ATTR_DATA_MANA,				// 魔力			uint
//	POKER_COLOR_ATTR_DATA_STR,				// 力量			uint
//	POKER_COLOR_ATTR_DATA_STA,				// 耐力			uint
//	POKER_COLOR_ATTR_DATA_DEX,				// 敏捷			uint
//};
//
//static const char* CONST_DB_NAME_PUZZLE = "puzzle";	// 迷宫配置表
//enum PUZZLE_DATA
//{
//	PUZZLE_DATA_ID = 0,						// 迷宫格子id	uint
//	PUZZLE_DATA_LINK_ID1,					// 连接格子id1	uint
//	PUZZLE_DATA_LINK_ID2,					// 连接格子id2	uint
//	PUZZLE_DATA_LINK_ID3,					// 连接格子id3	uint
//	PUZZLE_DATA_LINK_ID4,					// 连接格子id4	uint
//	PUZZLE_DATA_LINK_ID5,					// 连接格子id5	uint
//	PUZZLE_DATA_LINK_ID6,					// 连接格子id6	uint
//	PUZZLE_DATA_TASK_TYPE,					// 任务类型		uint
//	PUZZLE_DATA_BATTLE_TYPE,				// 战斗类型		uint
//	PUZZLE_DATA_ACTION_ID,					// 执行的脚本ID	uint
//	PUZZLE_DATA_PROGRESS_ADD,				// 增加进度		uint
//};
//
//static const char* CONST_DB_NAME_PUZZLE_BUFF = "puzzle_buff";	// 迷宫BUFF配置表
//enum PUZZLE_BUFF
//{
//	PUZZLE_BUFF_ID = 0,						// BUFF类型		uint
//	PUZZLE_BUFF_NAME,						// BUFF名字		varchar32
//	PUZZLE_BUFF_VALUE,						// BUFF属性值	uint
//	PUZZLE_BUFF_EFFECT,						// BUFF生效机制	uint
//};
//
//static const char* CONST_DB_NAME_ARENA_AWARD = "arena_award";	// 竞技场奖励配置表
//enum ARENA_AWARD
//{
//	ARENA_AWARD_TYPE = 0,					// 竞技场种别	uint
//	ARENA_AWARD_UPPER_LEV,					// 奖励排名上限	uint
//	ARENA_AWARD_LOWER_LEV,					// 奖励排名下限	uint
//	ARENA_AWARD_GOLD_COUNT,					// 奖励金币数	uint
//	ARENA_AWARD_MONEY_COUNT,				// 奖励竞技场币	uint
//	ARENA_AWARD_VAS_COUNT,					// 奖励元宝		uint
//	ARENA_AWARD_ITEM_TYPE,					// 奖励物品type	uint
//	ARENA_AWARD_ITEM_COUNT,					// 奖励物品数	uint
//	ARENA_AWARD_MONEY_COUNT_PER,			// 定时奖励币	uint
//	ARENA_AWARD_END,
//};
//
//static const char* CONST_DB_NAME_ARENA_AI_POKER = "arena_ai_poker";	// 竞技场机器人卡牌配置表
//enum ARENA_AI_POKER_DATA
//{
//	ARENA_AI_POKER_DATA_ARENA_TYPE = 0,		// 竞技场类别	uint
//	ARENA_AI_POKER_DATA_LOW_RANK,			// 排名范围下限	uint
//	ARENA_AI_POKER_DATA_POKER_TYPE,			// 卡牌typeid	uint
//};
//
//static const char* CONST_DB_NAME_PAY_CONFIG = "pay_config";		// 充值配置表
//enum PAY_CONFIG_DATA
//{
//	PAY_CONFIG_DATA_ID = 0,				// id(首充掩码)			uint
//	PAY_CONFIG_DATA_RMB,				// 人民币				uint
//	PAY_CONFIG_DATA_VAS,				// 元宝					uint
//	PAY_CONFIG_DATA_FREE_VAS,			// 赠送元宝				uint
//	PAY_CONFIG_DATA_FREE_VAS_DES,		// 赠送元宝说明			uint
//	PAY_CONFIG_DATA_FISRT_FREE_VAS,		// 首充赠送元宝			uint
//	PAY_CONFIG_DATA_FISRT_FREE_DES,		// 首充赠送元宝说明		uint
//	PAY_CONFIG_DATA_MONTH_CARD,			// 月卡标记				uint
//};
//
//static const char* CONST_DB_NAME_WAR_ROAD = "war_road";			// 战役配置表
//enum WAR_ROAD_DATA
//{
//	WAR_ROAD_DATA_WAR_KEY = 0,			// 战役key（模式*1000000+章节*1000+关卡）（模式1普通，2精英，3团队）	uint
//	WAR_ROAD_DATA_OPEN_LEV,				// 开启等级						uint
//	WAR_ROAD_DATA_COST_POWER,			// 体力消耗						uint
//	WAR_ROAD_DATA_BATTLE_TYPE,			// 战斗类型						uint
//};
//
//static const char* CONST_DB_NAME_WAR_ROAD_TEAM = "war_road_team";	// 团队战役配置表
//enum WAR_ROAD_TEAM_DATA
//{
//	WAR_ROAD_TEAM_DATA_CHAPTER = 0,		// 章节							uint
//	WAR_ROAD_TEAM_DATA_CHAPTER_NAME,	// 章节名称						varchar
//	WAR_ROAD_TEAM_DATA_OPEN_COST,		// 开启消耗（活跃值）			uint
//	WAR_ROAD_TEAM_DATA_AWARD_RULE,		// 战利品类库（lottery_award表中配置）			uint
//	WAR_ROAD_TEAM_DATA_AWARD_TIME,		// 额外通关奖励时间				uint
//	WAR_ROAD_TEAM_DATA_AWARD_COUNT,		// 额外奖励帮贡数量				uint
//	WAR_ROAD_TEAM_DATA_PASS_WIN_COUNT,	// 关卡胜利奖励帮贡数量			uint
//};
//
//static const char* CONST_DB_NAME_TERRITORY_FIGHT = "territory_fight";		// 领地战配置表
//enum TERRITORY_FIGHT_DATA
//{
//	TERRITORY_FIGHT_DATA_ID = 0,				// 领地id					uint
//	TERRITORY_FIGHT_DATA_TYPE,					// 领地type					uint
//	TERRITORY_FIGHT_DATA_BATTLETYPE,			// 战场type					uint
//	TERRITORY_FIGHT_DATA_EFFECT,				// 领地效果					uint
//	TERRITORY_FIGHT_DATA_POKER_LEV_LIMIT,		// 领地战参战部队等级限制	uint
//	TERRITORY_FIGHT_DATA_BOSS_NAME,				// 驻守boss名字				varchar
//
//};
//
//static const char* CONST_DB_NAME_TERRITORY_FIGHT_MONSTER = "territory_fight_monster";	// 领地战默认驻守怪
//enum TERRITORY_FIGHT_MONSTER_DATA
//{
//	TERRITORY_FIGHT_MONSTER_DATA_TROOPS_ID = 0,	// 
//	TERRITORY_FIGHT_MONSTER_DATA_ID,
//	TERRITORY_FIGHT_MONSTER_DATA_POKERID1,
//	TERRITORY_FIGHT_MONSTER_DATA_POKERID2,
//	TERRITORY_FIGHT_MONSTER_DATA_POKERID3,
//	TERRITORY_FIGHT_MONSTER_DATA_POKERID4,
//	TERRITORY_FIGHT_MONSTER_DATA_POKERID5,
//};
//
//static const char* CONST_DB_NAME_DATA_RESET	= "data_reset";		// 数据重置配置表
//enum DATA_RESET_DATA
//{
//	DATA_RESET_DATA_TYPE = 0,					// 重置类型					uint
//	DATA_RESET_DATA_COUNT,						// 重置次数					uint
//	DATA_RESET_DATA_COST_TYPE,					// 消耗类型					uint
//	DATA_RESET_DATA_COST_NUM,					// 消耗数量					uint
//};
//
//static const char* CONST_DB_NAME_SYN_GIFT_BOX	= "syn_giftbox";// 帮派礼盒配置表
//enum SYN_GIFT_BOX_DATA
//{
//	SYN_GIFT_BOX_DATA_TYPE = 0,					// 礼盒类型					uint
//	SYN_GIFT_BOX_DATA_LEV,						// 礼盒等级					uint
//	SYN_GIFT_BOX_DATA_EXP,						// 礼盒经验					uint
//	SYN_GIFT_BOX_DATA_KEEP_TIME,				// 保存时间					uint
//	SYN_GIFT_BOX_DATA_DATA1,					// 参数1					uint
//	SYN_GIFT_BOX_DATA_DATA2,					// 参数2					uint
//	SYN_GIFT_BOX_DATA_RULE_ID,					// 开启奖励规则id			uint
//};
//
//static const char* CONST_DB_NAME_LOOKFACE_FRAME = "lookface_frame";	// 头像框配置表
//enum LOOKFACE_FRAME_DATA
//{
//	LOOKFACE_FRAME_DATA_TYPE = 0,				// 头像框类型			uint
//	LOOKFACE_FRAME_DATA_VIP_LEV,				// vip等级				uint
//	LOOKFACE_FRAME_DATA_SINGLE_ARENA_RANK,		// 当前单队竞技场名次	uint
//	LOOKFACE_FRAME_DATA_MULTI_ARENA_RANK,		// 当前多队竞技场名次	uint
//	LOOKFACE_FRAME_DATA_TIME_LIMIT,				// 时间限制				uint
//	LOOKFACE_FRAME_DATA_PARAM1,					// 预留1				uint
//	LOOKFACE_FRAME_DATA_PARAM2,					// 预留2				uint
//	LOOKFACE_FRAME_DATA_NAME,					// 名字					uint
//};
//
//static const char* CONST_DB_NAME_IP_LIBRARY = "ip_library";		// ip库配置表
//enum IP_LIBRARY_DATA
//{
//	IP_LIBRARY_DATA_ID = 0,				// ID							uint
//	IP_LIBRARY_DATA_IP_BEGIN,			// 起始IP						varchar16
//	IP_LIBRARY_DATA_IP_END,				// 结束IP						varchar16
//	IP_LIBRARY_DATA_IP_BEGIN_INT,		// 起始IP(整数)					uint
//	IP_LIBRARY_DATA_IP_END_INT,			// 结束IP(整数)					uint
//	IP_LIBRARY_DATA_ADDRESS1,			// 地址1						varchar64
//	IP_LIBRARY_DATA_ADDRESS2,			// 地址2						varchar128
//	IP_LIBRARY_DATA_ADDRESS_FINAL,		// 归属地区						varchar64
//	IP_LIBRARY_DATA_ADDRESS_ID,			// 地区编号						uint
//};
//
//
//static const char* CONST_DB_NAME_ROOM_TYPE = "room_type";
//enum ROOM_TYPE_DATA
//{
//	ROOM_TYPE_DATA_TYPE = 0,		// 房间类型			uint
//	ROOM_TYPE_DATA_NAME,			// 房间名字			varchar64
//	ROOM_TYPE_DATA_KEEP_TIME,		// 房间持续时间		uint
//	ROOM_TYPE_DATA_MAX_MEMBER,		// 最大成员数量		uint
//	ROOM_TYPE_DATA_MONSTER1,		// 怪物类型1		uint
//	ROOM_TYPE_DATA_MONSTER2,		// 怪物类型2		uint
//	ROOM_TYPE_DATA_MONSTER3,		// 怪物类型3		uint
//	ROOM_TYPE_DATA_MONSTER4,		// 怪物类型4		uint
//	ROOM_TYPE_DATA_MONSTER5,		// 怪物类型5		uint
//	ROOM_TYPE_DATA_MONSTER6,		// 怪物类型6		uint
//	ROOM_TYPE_DATA_MONSTER7,		// 怪物类型7		uint
//	ROOM_TYPE_DATA_MONSTER8,		// 怪物类型8		uint
//	ROOM_TYPE_DATA_MONSTER9,		// 怪物类型9		uint
//	ROOM_TYPE_DATA_MONSTER10,		// 怪物类型10		uint
//	ROOM_TYPE_DATA_MONSTER11,		// 怪物类型11		uint
//	ROOM_TYPE_DATA_MONSTER12,		// 怪物类型12		uint
//	ROOM_TYPE_DATA_MONSTER13,		// 怪物类型13		uint
//	ROOM_TYPE_DATA_MONSTER14,		// 怪物类型14		uint
//	ROOM_TYPE_DATA_MONSTER15,		// 怪物类型15		uint
//};
//
//static const char* CONST_DB_NAME_ROOM_MONSTER = "room_monster";
//enum ROOM_MONSTER_DATA
//{
//	ROOM_MONSTER_DATA_TYPE = 0,			// 怪物类型								uint
//	ROOM_MONSTER_DATA_SORT,				// 怪物形式		1怪物 2采集物			uint
//	ROOM_MONSTER_DATA_BATTLE_TYPE,		// 战斗类型		1怪物触发的战斗类型		uint
//	ROOM_MONSTER_DATA_REBORN_SECOND,	// 重生秒数		0表示不重生				uint
//	ROOM_MONSTER_DATA_PICK_SECOND,		// 采集时间								uint
//	ROOM_MONSTER_DATA_PICK_ACTION,		// 采集后action							uint
//};
//
//static const char* CONST_DB_NAME_NAME_LIBRARY = "name_library";		// 名字库
//enum NAME_LIBRARY_DATA
//{
//	NAME_LIBRARY_DATA_ID = 0,			// id	uint
//	NAME_LIBRARY_DATA_SURNAME,			// 姓	varchar
//	NAME_LIBRARY_DATA_NAME,				// 名	varchar
//};
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// 常量表重新加载类型
//enum RELOAD_CONST_TABLE_TYPE
//{
//	RELOAD_CONST_TABLE_TYPE_SERVER_START_TIME = 0,
//	RELOAD_CONST_TABLE_TYPE_LUA_FILE,
//	RELOAD_CONST_TABLE_TYPE_POKER_COLOR_ATTR_SUM,
//
//	RELOAD_CONST_TABLE_TYPE_CONFIGDATA,
//	RELOAD_CONST_TABLE_TYPE_CONFIGTEXT,
//	RELOAD_CONST_TABLE_TYPE_TASK_DATA,
//	RELOAD_CONST_TABLE_TYPE_NEWCARDPRIZE,
//	RELOAD_CONST_TABLE_TYPE_NOTIFY_CONFIG,
//	RELOAD_CONST_TABLE_TYPE_ACTIVITYCONFIG,
//	RELOAD_CONST_TABLE_TYPE_ACTION,
//	RELOAD_CONST_TABLE_TYPE_POKER_TYPE,
//	RELOAD_CONST_TABLE_TYPE_POKER_STAR_GROW,
//	RELOAD_CONST_TABLE_TYPE_POKER_EQUIP,
//	RELOAD_CONST_TABLE_TYPE_POKER_STAR,
//	RELOAD_CONST_TABLE_TYPE_POKER_COLOR_ATTR,
//	RELOAD_CONST_TABLE_TYPE_LEV_EXP,
//	RELOAD_CONST_TABLE_TYPE_SIGNPRIZE,
//	RELOAD_CONST_TABLE_TYPE_VIP,
//	RELOAD_CONST_TABLE_TYPE_ITEM_TYPE,
//	RELOAD_CONST_TABLE_TYPE_ITEM_COLOR,
//	RELOAD_CONST_TABLE_TYPE_ITEM_STAR_ATTR,
//	RELOAD_CONST_TABLE_TYPE_LIVENESS,
//	RELOAD_CONST_TABLE_TYPE_SHOP_TYPE,
//	RELOAD_CONST_TABLE_TYPE_SHOP_RULE,
//	RELOAD_CONST_TABLE_TYPE_ACHIEVEMENT,
//	RELOAD_CONST_TABLE_TYPE_LUA_TEXT,
//	RELOAD_CONST_TABLE_TYPE_SKILL_TYPE,
//	RELOAD_CONST_TABLE_TYPE_DROP_RULE,
//	RELOAD_CONST_TABLE_TYPE_BATTLE_TYPE,
//	RELOAD_CONST_TABLE_TYPE_BATTLE_ROUND,
//	RELOAD_CONST_TABLE_TYPE_BATTLE_MONSTER,
//	RELOAD_CONST_TABLE_TYPE_PEIFANG,
//	RELOAD_CONST_TABLE_TYPE_CHALLENGE_BOSS,
//	RELOAD_CONST_TABLE_TYPE_LOTTERY_TYPE,
//	RELOAD_CONST_TABLE_TYPE_LOTTERY_RULE,
//	RELOAD_CONST_TABLE_TYPE_PRIZE_TYPE,
//	RELOAD_CONST_TABLE_TYPE_PROPERTY_CALCRANK2,
//	RELOAD_CONST_TABLE_TYPE_MONEY_AWARD_CHANCE,
//	RELOAD_CONST_TABLE_TYPE_INSTANCE_TYPE,
//	RELOAD_CONST_TABLE_TYPE_PUZZLE,
//	RELOAD_CONST_TABLE_TYPE_PUZZLE_BUFF,
//	RELOAD_CONST_TABLE_TYPE_PAY_CONFIG,
//	RELOAD_CONST_TABLE_TYPE_ARENA_AWARD,
//	RELOAD_CONST_TABLE_TYPE_ARENA_AI_POKER,
//	RELOAD_CONST_TABLE_TYPE_WAR_ROAD,
//	RELOAD_CONST_TABLE_TYPE_WAR_ROAD_TEAM,
//	RELOAD_CONST_TABLE_TYPE_TERRITORY_FIGHT,
//	RELOAD_CONST_TABLE_TYPE_TERRITORY_FIGHT_MONSTER,
//	RELOAD_CONST_TABLE_TYPE_DATA_RESET,
//	RELOAD_CONST_TABLE_TYPE_SYN_GIFT_BOX,
//	RELOAD_CONST_TABLE_TYPE_LOOKFACE_FRAME,
//	RELOAD_CONST_TABLE_TYPE_ROOM_TYPE,
//	RELOAD_CONST_TABLE_TYPE_ROOM_MONSTER,
//	RELOAD_CONST_TABLE_TYPE_NAME_LIBRARY,
//	RELOAD_CONST_TABLE_TYPE_END,
//};

#endif // end of _DATABASE_DEFINE_CONST_H_