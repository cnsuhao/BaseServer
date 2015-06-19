//////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2012, WuHan ChuangYou, All Rights Reserved
// Moudle: EnumDef.h
// Author: 彭文奇(Peng Wenqi)
// Created: 2012-10-30
// 
// !!! 注意 !!!
//	本文件用于定义游戏服务器全局枚举
//////////////////////////////////////////////////////////////////////////
#ifndef _MAPGROUP_SHARE_ENUM_DEF_H_
#define _MAPGROUP_SHARE_ENUM_DEF_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../../common/common.h"

enum ENUM_MSGPORT_TYPE
{
	MSGPORT_SHELL		= 0,	// 对话框
	MSGPORT_SOCKET		= 1,	// 底层通讯
	MSGPORT_LOGIN		= 2,	// 登陆
	MSGPORT_GAME		= 3,	// 游戏逻辑
	MSGPORT_RELATION	= 4,	// 服务器间通信
	MSGPORT_AI			= 5,	// AI通信

	MSGPORT_SIZE,				// 管道数量
	MSGPORT_DEFAULT		= 999,	// 默认线程ID, 此枚举不可作为线程间通信接口使用
};

// 账号踢出标志
enum ACCOUNT_KICK_FLAG
{
	ACCOUNT_KICK_FLAG_NONE		= 0x0000,
	ACCOUNT_KICK_FLAG_SOCKET	= 0x0001,
	ACCOUNT_KICK_FLAG_GAME		= 0x0002,
	ACCOUNT_KICK_FLAG_RELATION	= 0x0004,
	ACCOUNT_KICK_FLAG_OK		= ACCOUNT_KICK_FLAG_SOCKET | ACCOUNT_KICK_FLAG_GAME | ACCOUNT_KICK_FLAG_RELATION,
};

// 登录时账号状态
enum ACCOUNT_LOGIN_FLAG
{
	ACCOUNT_LOGIN_FLAG_WAIT_KICK,
	ACCOUNT_LOGIN_FLAG_WAIT_CHOOSE,
	ACCOUNT_LOGIN_FLAG_WAIT_ENTER,
	ACCOUNT_LOGIN_FLAG_OK,
};

// 踢出原因
enum KICK_REASON
{
	KICK_REASON_DEFAULT					= 0,	// 踢出默认值, 一般不要用这个值
	KICK_REASON_PASSWORD_ERROR			= 1,	// 密码错误
	KICK_REASON_BE_KICK_ANOTHER			= 2,	// 被别人踢
	KICK_REASON_RELATION_SERVER			= 3,	// 关系服务器指示你被踢了
	KICK_REASON_FULL					= 4,	// 人太多
	KICK_REASON_SYSTEM					= 5,	// 服务器控制面板踢人 或 GM踢人	
	KICK_REASON_NOT_ALLOW				= 6,	// 服务器未开启登陆允许
	KICK_REASON_GM_MAC_ERROR			= 7,	// GM工具Mac地址验证错误		
	KICK_REASON_CHECK_SPEED_TOO_FAST	= 8,	// 检测速度过快					**
	KICK_REASON_GMCMD					= 9,	// GM命令踢自己	
	KICK_REASON_LOGIN_TIMEOUT			= 10,	// 登陆过程超时
	KICK_REASON_ACCOUNT_STOP_BYTIME		= 11,	// 账号临时封停
	KICK_REASON_ACCOUNT_STOP_FOREVER	= 12,	// 账号永久封停

};

// user的内存数据枚举
enum MEMORY_DATA_ATTR_USER
{
	mdaUser_BEGIN = 0,

	mdaUser_AccountType,
	mdaUser_AccountStatus,
	mdaUser_AccountStatusParam,

	mdaUser_OnTimer_EverySecond,
	mdaUser_OnTimer_MinuteSecond,

	mdaUser_OnlineSecond,

	mdaUser_GmMacPass,

	mdaUser_END,
};

// UserAttr
enum USER_ATTR_TYPE
{
	USER_ATTR_TYPE_LEV			  = 1,	// 角色等级
	USER_ATTR_TYPE_EXP			  = 2,	// 角色经验
	USER_ATTR_TYPE_STOP_TALK_TIME = 3,	// 禁言时间
	USER_ATTR_TYPE_POKER_MAX_LEV  = 4,	// 卡牌最大等级
};

// 消息发送范围
enum SEND_RANGE_TYPE
{
	SEND_RANGE_TYPE_BEGIN			= 0,
	SEND_RANGE_TYPE_USER			= 1,	// 玩家
	SEND_RANGE_TYPE_SYNDICATE		= 2,	// 帮派
	SEND_RANGE_TYPE_SERVER_GROUP	= 3,	// 服务器组
	SEND_RANGE_TYPE_END,
};

// 卡牌阵营
enum POKER_CAMP
{
	POKER_CAMP_XIAN = 1,	// 仙
	POKER_CAMP_MO	= 2,	// 魔
	POKER_CAMP_FO	= 3,	// 佛
};

// 卡牌站位
enum POKER_FIGHT_POS
{
	POKER_FIGHT_POS_1ST = 1,	// 前排
	POKER_FIGHT_POS_2ND = 2,	// 中排
	POKER_FIGHT_POS_3RD = 3,	// 后排
};

// 经验等级类型
enum LEV_EXP_TYPE
{
	LEV_EXP_TYPE_USER			= 1,	// 角色
	LEV_EXP_TYPE_POKER			= 2,	// 卡牌
	LEV_EXP_TYPE_VIP			= 3,	// VIP
	LEV_EXP_TYPE_SYN_GIFTBOX	= 4,	// 帮派礼盒
};

// 卡牌装备位置
enum EQUIP_POS
{
	EQUIP_POS_BEGIN			= 0,
	EQUIP_POS_WEAPON		= 1,	// 武器
	EQUIP_POS_HELMET		= 2,	// 头盔
	EQUIP_POS_NECKLACE		= 3,	// 项链
	EQUIP_POS_WAISTBAND		= 4,	// 腰带
	EQUIP_POS_CLOTHES		= 5,	// 衣服
	EQUIP_POS_SHOES			= 6,	// 鞋子
	EQUIP_POS_END,
};

// 技能位置
enum MAGIC_POS
{
	MAGIC_POS_BEGIN			= 0,
	MAGIC_POS_SP			= 1,	// 特技
	MAGIC_POS_AUTO1			= 2,	// 自动技能1
	MAGIC_POS_AUTO2			= 3,	// 自动技能2
	MAGIC_POS_AUTO3			= 4,	// 自动技能3
	MAGIC_POS_JOINT			= 5,	// 连携技能
	MAGIC_POS_END,
};

// 装备属性类型
enum EQUIP_ATTR_TYPE
{
	EQUIP_ATTR_TYPE_BEGIN			= 1,
	EQUIP_ATTR_TYPE_LEV1_LIFE		= EQUIP_ATTR_TYPE_BEGIN,// 一级属性	体质
	EQUIP_ATTR_TYPE_LEV1_MANA		= 2,					// 一级属性	魔力
	EQUIP_ATTR_TYPE_LEV1_STR		= 3,					// 一级属性	力量
	EQUIP_ATTR_TYPE_LEV1_STA		= 4,					// 一级属性	耐力
	EQUIP_ATTR_TYPE_LEV1_DEX		= 5,					// 一级属性	敏捷

	EQUIP_ATTR_TYPE_LEV2_HP			= 6,					// 二级属性 气血
	EQUIP_ATTR_TYPE_LEV2_SP			= 7,					// 二级属性	愤怒
	EQUIP_ATTR_TYPE_LEV2_HIT		= 8,					// 二级属性	命中
	EQUIP_ATTR_TYPE_LEV2_ATK		= 9,					// 二级属性	伤害
	EQUIP_ATTR_TYPE_LEV2_DEF		= 10,					// 二级属性	防御
	EQUIP_ATTR_TYPE_LEV2_SPD		= 11,					// 二级属性	速度
	EQUIP_ATTR_TYPE_LEV2_DODGE		= 12,					// 二级属性	闪避
	EQUIP_ATTR_TYPE_LEV2_MAGIC		= 13,					// 二级属性	灵力

	EQUIP_ATTR_TYPE_SPECIAL_HP_RECOVER			= 14,	// 特殊属性 气血回复
	EQUIP_ATTR_TYPE_SPECIAL_SP_RECOVER			= 15,	// 特殊属性	愤怒回复
	EQUIP_ATTR_TYPE_SPECIAL_PHY_CRIT			= 16,	// 特殊属性	物暴
	EQUIP_ATTR_TYPE_SPECIAL_MAG_CRIT			= 17,	// 特殊属性	法爆
	EQUIP_ATTR_TYPE_SPECIAL_VAMPIRE_LEV			= 18,	// 特殊属性	吸血等级
	EQUIP_ATTR_TYPE_SPECIAL_SP_SPEND_DECREASE	= 19,	// 特殊属性	愤怒消耗降低%
	EQUIP_ATTR_TYPE_SPECIAL_CURE_INCREASE		= 20,	// 特殊属性	治疗技能效果提高%

	EQUIP_ATTR_TYPE_BASE_ALL		= 21,					// 一级全属性（转化一级属性）

	EQUIP_ATTR_TYPE_END,
};

enum POKER_ATTR								// 卡牌内存属性
{
	POKER_ATTR_BEGIN = 0,
	
	POKER_ATTR_SCORE,						// 战力
	POKER_ATTR_LEV1_LIFE,					// 一级属性	体质
	POKER_ATTR_LEV1_MANA,					// 一级属性	魔力
	POKER_ATTR_LEV1_STR,					// 一级属性	力量
	POKER_ATTR_LEV1_STA,					// 一级属性	耐力
	POKER_ATTR_LEV1_DEX,					// 一级属性	敏捷

	POKER_ATTR_LEV2_HP,						// 二级属性 气血
	POKER_ATTR_LEV2_SP,						// 二级属性	愤怒
	POKER_ATTR_LEV2_HIT,					// 二级属性	命中
	POKER_ATTR_LEV2_ATK,					// 二级属性	伤害
	POKER_ATTR_LEV2_DEF,					// 二级属性	防御
	POKER_ATTR_LEV2_SPD,					// 二级属性	速度
	POKER_ATTR_LEV2_DODGE,					// 二级属性	闪避
	POKER_ATTR_LEV2_MAGIC,					// 二级属性	灵力

	POKER_ATTR_SPECIAL_HP_RECOVER,			// 特殊属性 气血回复
	POKER_ATTR_SPECIAL_SP_RECOVER,			// 特殊属性	愤怒回复
	POKER_ATTR_SPECIAL_PHY_CRIT,			// 特殊属性	物暴
	POKER_ATTR_SPECIAL_MAG_CRIT,			// 特殊属性	法爆
	POKER_ATTR_SPECIAL_VAMPIRE_LEV,			// 特殊属性	吸血等级
	POKER_ATTR_SPECIAL_SP_SPEND_DECREASE,	// 特殊属性	愤怒消耗降低%
	POKER_ATTR_SPECIAL_CURE_INCREASE,		// 特殊属性	治疗技能效果提高%

	POKER_ATTR_BASE_ALL,					// 一级全属性（转化一级属性）
	POKER_ATTR_END,

	// 下面的属性用来记录更新角色卡前的卡牌属性数据, 需要与上面一段同步, 
	POKER_OLD_ATTR_BEGIN = POKER_ATTR_END,
	POKER_OLD_ATTR_SCORE,

	POKER_OLD_ATTR_LEV1_LIFE,
	POKER_OLD_ATTR_LEV1_MANA,
	POKER_OLD_ATTR_LEV1_STR,
	POKER_OLD_ATTR_LEV1_STA,
	POKER_OLD_ATTR_LEV1_DEX,

	POKER_OLD_ATTR_LEV2_HP,
	POKER_OLD_ATTR_LEV2_SP,
	POKER_OLD_ATTR_LEV2_HIT,
	POKER_OLD_ATTR_LEV2_ATK,
	POKER_OLD_ATTR_LEV2_DEF,
	POKER_OLD_ATTR_LEV2_SPD,
	POKER_OLD_ATTR_LEV2_DODGE,
	POKER_OLD_ATTR_LEV2_MAGIC,

	POKER_OLD_ATTR_SPECIAL_HP_RECOVER,
	POKER_OLD_ATTR_SPECIAL_SP_RECOVER,
	POKER_OLD_ATTR_SPECIAL_PHY_CRIT,
	POKER_OLD_ATTR_SPECIAL_MAG_CRIT,
	POKER_OLD_ATTR_SPECIAL_VAMPIRE_LEV,
	POKER_OLD_ATTR_SPECIAL_SP_SPEND_DECREASE,
	POKER_OLD_ATTR_SPECIAL_CURE_INCREASE,

	POKER_OLD_ATTR_BASE_ALL,
	POKER_OLD_ATTR_END,

	// 下面的属性用来记录装备加成属性，最终结算在卡牌属性，但是需要同步给客户端
	POKER_EQUIP_ADD_ATTR_BEGIN,
	POKER_EQUIP_ADD_ATTR_STAR_SCORE,				// 装备星级加成战力

	POKER_EQUIP_ADD_ATTR_LEV1_LIFE,					// （装备加成）一级属性	体质
	POKER_EQUIP_ADD_ATTR_LEV1_MANA,					// （装备加成）一级属性	魔力
	POKER_EQUIP_ADD_ATTR_LEV1_STR,					// （装备加成）一级属性	力量
	POKER_EQUIP_ADD_ATTR_LEV1_STA,					// （装备加成）一级属性	耐力
	POKER_EQUIP_ADD_ATTR_LEV1_DEX,					// （装备加成）一级属性	敏捷

	POKER_EQUIP_ADD_ATTR_LEV2_HP,					// （装备加成）二级属性 气血
	POKER_EQUIP_ADD_ATTR_LEV2_SP,					// （装备加成）二级属性	愤怒
	POKER_EQUIP_ADD_ATTR_LEV2_HIT,					// （装备加成）二级属性	命中
	POKER_EQUIP_ADD_ATTR_LEV2_ATK,					// （装备加成）二级属性	伤害
	POKER_EQUIP_ADD_ATTR_LEV2_DEF,					// （装备加成）二级属性	防御
	POKER_EQUIP_ADD_ATTR_LEV2_SPD,					// （装备加成）二级属性	速度
	POKER_EQUIP_ADD_ATTR_LEV2_DODGE,				// （装备加成）二级属性	闪避
	POKER_EQUIP_ADD_ATTR_LEV2_MAGIC,				// （装备加成）二级属性	灵力

	POKER_EQUIP_ADD_ATTR_SPECIAL_HP_RECOVER,		// （装备加成）特殊属性 气血回复
	POKER_EQUIP_ADD_ATTR_SPECIAL_SP_RECOVER,		// （装备加成）特殊属性	愤怒回复
	POKER_EQUIP_ADD_ATTR_SPECIAL_PHY_CRIT,			// （装备加成）特殊属性	物暴
	POKER_EQUIP_ADD_ATTR_SPECIAL_MAG_CRIT,			// （装备加成）特殊属性	法爆
	POKER_EQUIP_ADD_ATTR_SPECIAL_VAMPIRE_LEV,		// （装备加成）特殊属性	吸血等级
	POKER_EQUIP_ADD_ATTR_SPECIAL_SP_SPEND_DECREASE,	// （装备加成）特殊属性	愤怒消耗降低%
	POKER_EQUIP_ADD_ATTR_SPECIAL_CURE_INCREASE,		// （装备加成）特殊属性	治疗技能效果提高%

	POKER_EQUIP_ADD_ATTR_BASE_ALL,					// （装备加成）一级全属性（转化一级属性）
	POKER_EQUIP_ADD_ATTR_END,
};

enum MSG_POKER_ATTR_TYPE				// 卡牌属性同步消息类型
{
	MSG_POKERATTR_BEGIN					= 0,

	MSG_POKERATTR_LIFE					= 1,	// 一级属性	体质
	MSG_POKERATTR_MANA					= 2,	// 一级属性	魔力
	MSG_POKERATTR_STR					= 3,	// 一级属性	力量
	MSG_POKERATTR_STA					= 4,	// 一级属性	耐力
	MSG_POKERATTR_DEX					= 5,	// 一级属性	敏捷

	MSG_POKERATTR_HP					= 6,	// 二级属性 气血
	MSG_POKERATTR_SP					= 7,	// 二级属性	愤怒
	MSG_POKERATTR_HIT					= 8,	// 二级属性	命中
	MSG_POKERATTR_ATK					= 9,	// 二级属性	伤害
	MSG_POKERATTR_DEF					= 10,	// 二级属性	防御
	MSG_POKERATTR_SPD					= 11,	// 二级属性	速度
	MSG_POKERATTR_DODGE					= 12,	// 二级属性	闪避
	MSG_POKERATTR_MAGIC					= 13,	// 二级属性	灵力

	MSG_POKERATTR_HP_RECOVER			= 14,	// 特殊属性 气血回复
	MSG_POKERATTR_SP_RECOVER			= 15,	// 特殊属性	愤怒回复
	MSG_POKERATTR_PHY_CRIT				= 16,	// 特殊属性	物暴
	MSG_POKERATTR_MAG_CRIT				= 17,	// 特殊属性	法爆
	MSG_POKERATTR_VAMPIRE_LEV			= 18,	// 特殊属性	吸血等级
	MSG_POKERATTR_SP_SPEND_DECREASE		= 19,	// 特殊属性	愤怒消耗降低%
	MSG_POKERATTR_CURE_INCREASE			= 20,	// 特殊属性	治疗技能效果提高%

	MSG_POKERATTR_BASE_ALL				= 21,	// 一级全属性

	MSG_POKERATTR_EQUIP_STAR_ADD_SCORE	= 99,	// 装备星级加成战力
	MSG_POKERATTR_SCORE					= 100,	// 总战力

	MSG_POKERATTR_LEV					= 101,	// 等级		
	MSG_POKERATTR_EXP					= 102,	// 经验
	MSG_POKERATTR_STAR					= 103,	// 星级
	MSG_POKERATTR_COLOR					= 104,	// 颜色

	MSG_POKERATTR_LIFE_GROW				= 105,	// 体质成长
	MSG_POKERATTR_MANA_GROW				= 106,	// 魔力成长
	MSG_POKERATTR_STR_GROW				= 107,	// 力量成长
	MSG_POKERATTR_STA_GROW				= 108,	// 耐力成长
	MSG_POKERATTR_DEX_GROW				= 109,	// 敏捷成长

	MSG_POKERATTR_STATE					= 110,	// 状态

	MSG_POKERATTR_END,
};

enum UPDATEATTRSYNTYPE				// 卡牌更新同步类型
{
	UAST_ALL,						// 默认
	UAST_ALL_SYNC,					// 强行全部属性同步给客户端
	UAST_ALL_NOT_SYNC,				// 全部更新, 但是不同步客户端
	UAST_ALL_SYNC_CLEAN_OLD,		// 强行清除旧属性并同步
	UAST_ALL_UP_LEV,				// 升级
	UAST_ALL_UP_STAR,				// 升星
	UAST_ALL_UP_COLOR,				// 进阶
	UAST_ALL_UP_MAGIC,				// 技能
	UAST_ALL_EQUIP,					// 装备
	UAST_ALL_UP_EQUIP_STAR,			// 装备升星（附魔）
};

enum POKER_STATE						// 卡牌状态
{
	POKER_STATE_NONE					= 0,	// 空闲
	POKER_STATE_MINE					= 1,	// 挖矿
	POKER_STATE_MERCENARY				= 2,	// 守营
};

enum SKILL_SORT							// 技能分类
{
	SKILL_SORT_ACTIVE					= 1,	// 主动技能
	SKILL_SORT_PASSIVE					= 2,	// 被动技能
	SKILL_SORT_JOINT					= 3,	// 连携技能
};

enum SKILLPROPERTY_CONTROL				// 技能属性控制分类
{
	SKILLPROPERTY_CONTROL_BEGIN			= 0,
	SKILLPROPERTY_CONTROL_ADD			= 1,	// 增加
	SKILLPROPERTY_CONTROL_DEC			= 2,	// 减少
	SKILLPROPERTY_CONTROL_ADD_DECIMALS	= 3,	// 累加精确到0.01的小数
	SKILLPROPERTY_CONTROL_END,
};

enum LOTTERY_TYPE							// 抽奖类型
{
	LOTTERY_TYPE_BEGIN						= 0,
	LOTTERY_TYPE_MONEY						= 1,	// 金币抽奖
	LOTTERY_TYPE_MONEY_SERIES				= 2,	// 金币连抽
	LOTTERY_TYPE_VAS						= 3,	// 元宝抽奖
	LOTTERY_TYPE_VAS_SERIES					= 4,	// 元宝连抽
	LOTTERY_TYPE_VIP						= 5,	// VIP资格抽奖
	LOTTERY_TYPE_CHAPMAN_SMALL				= 6,	// 星际旅行商人小抽
	LOTTERY_TYPE_CHAPMAN_MIDDLE				= 7,	// 星际旅行商人中抽
	LOTTERY_TYPE_CHAPMAN_BIG				= 8,	// 星际旅行商人大抽

	LOTTERY_TYPE_VAS_FIXED					= 9,	// 元宝抽奖(第一次花费配置)
	LOTTERY_TYPE_VAS_SERIES_FIXED			= 10,	// 元宝连抽(第一次花费配置)
	LOTTERY_TYPE_MONEY_FIXED				= 11,	// 金币抽奖(第一次花费配置)
	LOTTERY_TYPE_MONEY_SERIES_FIXED			= 12,	// 金币连抽(第一次花费配置)
	LOTTERY_TYPE_END,
};

enum EUSERMASKTYPE					// 掩码类型
{
	EUMT_Begin				= 0,
	EUMT_TaskMask			= 1,	// 任务掩码
	EUMT_GiveMask			= 2,	// 奖励掩码
	EUMT_DayMask			= 3,	// 天掩码
	EUMT_WeekMask			= 4,	// 周掩码
	EUMT_MonthMask			= 5,	// 月掩码
	EUMT_End,
};

// 物品前缀分类, 最高位
enum ITEMTYPE_HEADER
{
	ITEMTYPE_HEADER_NONE		= 0,
	ITEMTYPE_HEADER_EQUIP		= 1,	// 装备
	ITEMTYPE_HEADER_EQUIP_CHIP	= 2,	// 装备碎片				和装备只有首位不同

	ITEMTYPE_HEADER_ONLYLOG		= 9,	// 单纯记录日志物品		不生成该类型物品
};

// 物品区分
enum ITEMTYPE_SORT
{
	ITEMTYPE_SORT_NONE			= 0,
	ITEMTYPE_SORT_UPSTAR		= 1,	// 升星材料				data1表示 可以提供升星点数
	ITEMTYPE_SORT_HERO_EXP		= 2,	// 英雄经验				data1表示 可以提高英雄经验
	ITEMTYPE_SORT_GHOST_STONE	= 3,	// 灵魂石			
	ITEMTYPE_SORT_CLEANSCROLL	= 4,	// 扫荡卷轴
	ITEMTYPE_SORT_CHIP			= 5,	// 物品碎片
	ITEMTYPE_SORT_POWER			= 6,	// 体力物品				data1表示 可以增加体力点数
};

// 物品颜色
enum ITEMCOLOR
{
	ITEMCOLOR_NONE		= 0,
	ITEMCOLOR_WHITE 	= 1,	// 白
	ITEMCOLOR_GREEN		= 2,	// 绿
	ITEMCOLOR_BLUE		= 3,	// 蓝
	ITEMCOLOR_VIOLET	= 4,	// 紫
	ITEMCOLOR_ORANGE	= 5,	// 橙
};

// 物品monopoly 掩码
enum ITEMTYPE_MONOPOLY
{
	ITEMTYPE_MONOPOLY_NONE				= 0x0000,
	ITEMTYPE_MONOPOLY_NEED_RECORD		= 0x0001,				// 需要写库记录流向

};

// 掉落类型
enum DROP_RULE_TYPE
{
	DROP_RULE_TYPE_ONCE			= 1,	// 一次规则, 多个权重分配
	DROP_RULE_TYPE_MORE			= 2,	// 多次规则, 每次独立算权重分配
	DROP_RULE_TYPE_NOT_REPEAT	= 3,	// 不重复掉落
};

// 掉落组类型
enum DROP_RULE_GROUP_TYPE
{
	DROP_RULE_GROUP_TYPE_NONE			= 0,
	DROP_RULE_GROUP_TYPE_MONEY_BEGIN	= 100,		// 货币 begin
	DROP_RULE_GROUP_TYPE_MONEY_END		= 999,		// 货币 end
	DROP_RULE_GROUP_TYPE_POKER_BEGIN	= 10000,	// 卡牌 begin
	DROP_RULE_GROUP_TYPE_POKER_END		= 99999,	// 卡牌 end
	DROP_RULE_GROUP_TYPE_ITEMTYPE_BEGIN	= 100000,	// itemtype begin
	DROP_RULE_GROUP_TYPE_ITEMTYPE_END	= 999999,	// itemtype end
};

// 掉落归属分类, 默认0都是直接给玩家
enum DROP_RULE_GROUP_GROUP
{
	DROP_RULE_GROUP_GROUP_USER = 0,
	DROP_RULE_GROUP_GROUP_WARROAD_AWARD = 1,	// 团队战役战利品
};

// 战斗结果类型
enum BATTLE_RESULT_TYPE
{
	BATTLE_RESULT_TYPE_SUC			= 0,	// 正常结束
	BATTLE_RESULT_TYPE_GIVE_UP		= 1,	// 中途退出
	BATTLE_RESULT_TYPE_TIME_OUT		= 2,	// 战斗超时
};

// 战斗类型
enum BATTLE_SORT
{
	BATTLE_SORT_NONE				= 0,
	BATTLE_SORT_NORMAL				= 1,	// 正常
	BATTLE_SORT_BOSS				= 2,	// boss战斗
	BATTLE_SORT_PVP					= 3,	// pvp
	BATTLE_SORT_INSTANCE			= 4,	// 副本
	BATTLE_SORT_GOOSE_TOWER			= 5,	// 大雁塔
	BATTLE_SORT_ARENA				= 6,	// 竞技场
	BATTLE_SORT_TERRITORY			= 7,	// 领地战
	BATTLE_SORT_PUZZLE				= 8,	// 迷宫战斗
	BATTLE_SORT_MINE				= 9,	// 矿洞战斗
	BATTLE_SORT_WARROAD_NORMAL		= 10,	// 普通战役
	BATTLE_SORT_WARROAD_DIFFICULTY	= 11,	// 精英战役
	BATTLE_SORT_WARROAD_TEAM		= 12,	// 团队战役
	BATTLE_SORT_NTM_FIGHT			= 13,	// 南天门斗法
	BATTLE_SORT_NTM_MONSTER			= 14,	// 南天门怪物
};

// 挑战boss 通过评价
enum CHALLENGE_BOSS_RESULT
{
	CHALLENGE_BOSS_RESULT_Beg		= 0,
	CHALLENGE_BOSS_RESULT_FAIL		= CHALLENGE_BOSS_RESULT_Beg,	// 挑战失败
	CHALLENGE_BOSS_RESULT_START1	= 1,							// 1星
	CHALLENGE_BOSS_RESULT_START2	= 2,							// 2星
	CHALLENGE_BOSS_RESULT_START3	= 3,							// 3星
	CHALLENGE_BOSS_RESULT_End,
};

enum EUSER_TEMPDATA_PROGRAM
{
	EUTDP_BEGIN							= 10000,	// 程序是用的TMP_ID从10000开始
	// 10000 - 10100留给客户端使用BEG
	EUTDP_CLIENT_BEGIN					= EUTDP_BEGIN,
	EUTDP_CLIENT_END					= 10100,
	// 10000 - 10100留给客户端使用END

	// 服务端从10101开始
	EUTDP_SERVER_BEGIN					= 10101,
	EUTDP_SERVER_POKER_MAGICPOINT_INFO	= 10102,	// 卡牌技能点信息：data0表示上次恢复技能点utc时间，data1表示今天购买技能点次数，data2表示上次购买技能点日期
	EUTDP_SERVER_MONEYTREE_INFO			= 10103,	// 摇钱数据：data0表示今天摇钱次数，data1表示上次摇钱日期
	EUTDP_SERVER_SIGN_INFO				= 10104,	// 签到数据：data0表示本月签到次数，data1表示今天是否签到，data2表示今天是否领取VIP签到奖励，data3表示签到时间
	EUTDP_SERVER_LOTTERY_INFO			= 10105,	// 抽奖数据：data0表示金币下次抽奖时间，data1表示元宝下次抽奖时间，data2表示抽奖商人出现时间，data3表示商人需求材料类型
	EUTDP_SERVER_MERCENARY_INFO			= 10106,	// 佣兵数据：data0表示回收雇佣总收入，data1表示回收守营总收入
	EUTDP_SERVER_CROSS_NTM_INFO			= 10107,	// 南天门斗法数据：data0表示上次进入的房间id，data1表示上次离开时间,data2表示挑战可以获得的积分
	EUTDP_SERVER_POWER_INFO				= 10108,	// 体力数据:data0表示上次恢复体力时间(utc), data1表示今天购买次数，data2表示上次购买日期

	EUTDP_SERVER_SHOP_BEGIN				= 10111,
	EUTDP_SERVER_SHOP_ARENA				= 10111,	// 竞技场商店数据: data0表示是否刷新过该商店(1是，0否)，data1表示当天手动刷新次数，data2表示上次手动刷新日期，data3表示上一次自动刷新时间(utc),data4表示下一次自动刷新时间(utc)
	EUTDP_SERVER_SHOP_TEAMS_ARENA		= 10112,	// 多队竞技场商店数据: data0表示是否刷新过该商店(1是，0否)，data1表示当天手动刷新次数，data2表示上次手动刷新日期，data3表示上一次自动刷新时间(utc),data4表示下一次自动刷新时间(utc)
	EUTDP_SERVER_SHOP_TOWER				= 10113,	// 大雁塔商店数据: data0表示是否刷新过该商店(1是，0否)，data1表示当天手动刷新次数，data2表示上次手动刷新日期，data3表示上一次自动刷新时间(utc),data4表示下一次自动刷新时间(utc)
	EUTDP_SERVER_SHOP_SYN				= 10114,	// 帮派商店数据: data0表示是否刷新过该商店(1是，0否)，data1表示当天手动刷新次数，data2表示上次手动刷新日期，data3表示上一次自动刷新时间(utc),data4表示下一次自动刷新时间(utc)
	EUTDP_SERVER_SHOP_REFRESH			= 10115,	// 刷新商店数据: data0表示是否刷新过该商店(1是，0否)，data1表示当天手动刷新次数，data2表示上次手动刷新日期，data3表示上一次自动刷新时间(utc),data4表示下一次自动刷新时间(utc)
	EUTDP_SERVER_SHOP_BLACK_MARKET		= 10116,	// 黑市商店数据: data0表示是否刷新过该商店(1是，0否)，data1表示当天手动刷新次数，data2表示上次手动刷新日期,data3表示上一次自动刷新时间(utc),data4表示下一次自动刷新时间(utc),data5表示商店出现时间(utc)
	EUTDP_SERVER_SHOP_FRIENDSHIP		= 10117,	// 友情点商店数据: data0表示是否刷新过该商店(1是，0否)，data1表示当天手动刷新次数，data2表示上次手动刷新日期,data3表示上一次自动刷新时间(utc),data4表示下一次自动刷新时间(utc),data5表示商店出现时间(utc)
	EUTDP_SERVER_SHOP_END				= 10131,

	EUTDP_SERVER_CHALLENGE_BOSS			= 10132,	// 挑战boss: data0表示已挑战成功次数, data1:表示刷新挑战次数日期, data2:表示挑战次数(不管成功失败)
	EUTDP_SERVER_GOOSE_TOWER			= 10133,	// 大雁塔:   data0表示当前可挑战层数, data1表示今日已重置次数, data2表示重置时间
	EUTDP_SERVER_JOIN_SYNDICATE			= 10134,	// 进入帮派记录日期, data0-5记录最近加入三个公会的时间与id
	EUTDP_SERVER_QUIT_SYNDICATE			= 10135,	// 离开帮派记录日期, data0-5记录最近离开三个公会的时间与id
	EUTDP_SERVET_PUZZLE_DATA			= 10136,	// 迷宫:data0表示迷宫类型，data1表示迷宫难度，data2表示迷宫层次，data3表示战斗序列号，data4表示上一格子，data5表示当前格子，data6表示总进度，data7表示utc时间
	EUTDP_SERVER_PUZZLE_POKER			= 10137,	// 迷宫:data0表示迷宫类型，data1-data5表示5张出战卡牌ID
	EUTDP_SERVER_PUZZLE_YAO				= 10138,	// 迷宫(妖): data0表示当前次数，data1表示上次进入日期
	EUTDP_SERVER_PUZZLE_GUI				= 10139,	// 迷宫(鬼): data0表示当前次数，data1表示上次进入日期
	EUTDP_SERVER_PUZZLE_MO				= 10140,	// 迷宫(魔): data0表示当前次数，data1表示上次进入日期
	EUTDP_SERVER_TOPLIST_BEGIN			= 10141,
	EUTDP_SERVER_TOPLIST_ARENA			= 10141,	// 单队竞技场数据：data0今日已挑战次数，data1上次挑战时间utc, data2上次挑战日期, data3挑战CD设置标识(0默认无CD，1有CD）,data4历史最高排名
	EUTDP_SERVER_TOPLIST_MULTI_ARENA	= 10142,	// 多队竞技场数据：data0今日已挑战次数，data1上次挑战时间utc, data2上次挑战日期，data3挑战CD设置标识(0默认无CD，1有CD)
	EUTDP_SERVER_INSTANCE_INFO			= 10143,	// 副本挑战信息: data0表示当前类型，data1表示当前难度，data2表示开始时间
	EUTDP_SERVER_WAR_ROAD_INFO			= 10144,	// 战役挑战信息: data0表示当前模式，data1表示当前章节，data2表示当前关卡，data3表示开始时间

	EUTDP_SERVER_MINE_INFO				= 10151,	// 矿洞:data0表示上一次搜索到的矿洞ID，data1表示每日搜索次数, data2表示上次搜索日期, data3表示上次恢复寻宝体力时间(utc)
	EUTDP_SERVER_MINE_FIGHT				= 10152,	// 矿洞:data0:开始挑战时间,data1:当前被挑战矿洞,data2:当前被挑战成员,data3表示战胜个数,data4:已战胜成员ID1，data5:已战胜成员ID2，data6：已战胜成员ID3
	EUTDP_SERVER_SYN_WORSHIP			= 10154,	// 帮派膜拜大神: data0:今天已膜拜次数, data1:刷新膜拜次数日期
	EUTDP_SERVER_FRIEND_INVITE			= 10155,	// 好友邀请: data0:邀请者ID, data1:领取昨日好友登陆奖励时间, data2:昨天登陆好友个数, data3:好友数更新时间
	EUTDP_SERVER_MINE_FIGHT_RES			= 10156,	// 矿洞战斗结束资源:data0:是否领取(1表示领取),data1:成员1资源数量,data2:成员1钻石数量,data3:成员2资源数量,data4:成员2钻石数量,data5:成员3资源数量,data6:成员3钻石数量,data7:资源类型
	EUTDP_SERVER_MSG_SWITCH				= 10157,	// 消息推送开关: data0的二进制位0到31表示:0:领取体力, 1:刷新商店, 2:体力回复满, 3:技能点回复满, 4:竞技场被攻击, 5:私聊消息通知, 6,矿已踩完通知[0:关, 1:开]; data1表示是否初始化
	EUTDP_SERVER_FRIEND					= 10157,	// 好友: data0: 给送好友玫瑰日期

	EUTDP_END,
};

// 副本类型
enum EINSTANCETYPE
{
	EINSTANCETYPE_NONE		= 0,
	EINSTANCETYPE_MONEY		= 1,	// 金币副本
	EINSTANCETYPE_EXP		= 2,	// 经验副本
	EINSTANCETYPE_YAO		= 3,	// 妖副本
	EINSTANCETYPE_GUI		= 4,	// 鬼副本
	EINSTANCETYPE_MO		= 5,	// 魔副本
};

// 迷宫类型
enum PUZZLE_TYPE_ENUM
{
	PUZZLE_TYPE_ENUM_Beg	= 2,
	PUZZLE_TYPE_ENUM_YAO	= 3,	// 妖
	PUZZLE_TYPE_ENUM_GUI	= 4,	// 鬼
	PUZZLE_TYPE_ENUM_MO		= 5,	// 魔
	PUZZLE_TYPE_ENUM_End,
};

// 迷宫难度
enum PUZZLE_DIFFICULT_ENUM
{
	PUZZLE_DIFFICULT_Beg	= 0,
	PUZZLE_DIFFICULT_Low	= 1,	// 低等级
	PUZZLE_DIFFICULT_Middle = 2,	// 中等级
	PUZZLE_DIFFICULT_High	= 3,	// 高等级
	PUZZLE_DIFFICULT_End,
};

// 迷宫BUFF类型
enum PUZZLE_BUFF_TYPE_ENUM
{
	PUZZLE_BUFF_Beg										= 0,
	// 增益BUFF
	PUZZLE_ADDBUFF_Beg									= 1000,	
	PUZZLE_ADDBUFF_ATK_ADD_IN_FLOOR						= 1001,	// 加攻击(本层有效)
	PUZZLE_ADDBUFF_ATK_ADD_IN_INSTANCE					= 1002,	// 加攻击(副本有效)
	PUZZLE_ADDBUFF_DEF_ADD_IN_FLOOR						= 1003,	// 加防御(本层有效)
	PUZZLE_ADDBUFF_DEF_ADD_IN_INSTANCE					= 1004,	// 加防御(副本有效)
	PUZZLE_ADDBUFF_HP_ADD_IN_NEXT_FIGHT					= 1005,	// 加血(下一场战斗有效)
	PUZZLE_ADDBUFF_SP_ADD_IN_NEXT_FIGHT					= 1006,	// 加怒气(下一场战斗有效)
	PUZZLE_ADDBUFF_DEF_SUB_IN_FLOOR						= 1007,	// 降低对方防御(本层有效)
	PUZZLE_ADDBUFF_DEF_SUB_IN_INSTANCE					= 1008,	// 降低对方防御(副本有效)
	PUZZLE_ADDBUFF_ATK_SUB_IN_FLOOR						= 1009,	// 降低对方攻击(本层有效)
	PUZZLE_ADDBUFF_ATK_SUB_IN_INSTANCE					= 1010,	// 降低对方攻击(本层有效)
	PUZZLE_ADDBUFF_RECOVER_ADD_IN_FLOOR					= 1011,	// 每次战斗后恢复效果加倍(本层有效)
	PUZZLE_ADDBUFF_RECOVER_ADD_IN_INSTANCE				= 1012,	// 每次战斗后恢复效果加倍(副本有效)
	PUZZLE_ADDBUFF_End,
	
	// 减益BUFF
	PUZZLE_SUBBUFF_Beg									= 2000,
	PUZZLE_SUBBUFF_HP_SUB_THIRTY_PERCENT_IN_NEXT_FIGHT	= 2001,	// 血量减少30%(下一场战斗)
	PUZZLE_SUBBUFF_SUB_ALL_ATK_AND_DEF_IN_NEXT_FIGHT	= 2002,	// 全体攻防减少(下一场战斗)
	PUZZLE_SUBBUFF_SUB_ALL_ATK_AND_DEF_IN_FLOOR			= 2003,	// 全体攻防减少(本层有效)
	PUZZLE_SUBBUFF_CLEAR_ALL_SP_IN_NEXT_FIGHT			= 2004,	// 清除所有怒气(下一场战斗)
	PUZZLE_SUBBUFF_End,

	// 其它BUFF
	PUZZLE_OTHERBUFF_Beg								= 3000,
	PUZZLE_OTHERBUFF_SHOW_TREASURE_IN_FLOOR				= 3001,	// 显示本层宝箱位置(本层有效)
	PUZZLE_OTHERBUFF_SHOW_TREASURE_IN_INSTANCE			= 3002,	// 显示本层宝箱位置(副本有效)
	PUZZLE_OTHERBUFF_SHOW_GIN_IN_FLOOR					= 3003,	// 显示陷阱(本层有效)
	PUZZLE_OTHERBUFF_SHOW_GIN_IN_INSTANCE				= 3004,	// 显示陷阱(副本有效)
	PUZZLE_OTHERBUFF_CLEAR_ONE_SUB_BUFF_AT_ONCE			= 3007,	// 清除一个减益BUFF(及时)
	PUZZLE_OTHERBUFF_CLEAR_ALL_SUB_BUFF_AT_ONCE			= 3008,	// 清除所有减益BUFF(及时)
	PUZZLE_OTHERBUFF_CLEAR_ONE_ADD_BUFF_AT_ONCE			= 3009,	// 清除一个增益BUFF(及时)
	PUZZLE_OTHERBUFF_End,

	PUZZLE_BUFF_End,
};

// 迷宫副本数据
enum PUZZLE_INSTANCE
{
	PUZZLE_INSTANCE_BEGIN						= 0,
	PUZZLE_INSTANCE_TYPE						= 1,		// 副本类型	
	PUZZLE_INSTANCE_DIFFICULT					= 2,		// 副本难度		
	PUZZLE_INSTANCE_FLOOR						= 3,		// 副本层次
	PUZZLE_INSTANCE_FIGHT_NO					= 4,		// 战斗序列号
	PUZZLE_INSTANCE_LAST_PUZZLE_ID				= 5,		// 上次格子				
	PUZZLE_INSTANCE_PUZZLE_ID					= 6 ,		// 当前格子			
	PUZZLE_INSTANCE_POKER1						= 7,		// 出战卡1				
	PUZZLE_INSTANCE_POKER2						= 8,		// 出战卡2					
	PUZZLE_INSTANCE_POKER3						= 9,		// 出战卡3				
	PUZZLE_INSTANCE_POKER4						= 10,		// 出战卡4					
	PUZZLE_INSTANCE_POKER5						= 11,		// 出战卡5				
	PUZZLE_INSTANCE_PROGRESS_TOTAL				= 12,		// 副本进度				
	PUZZLE_INSTANCE_BEG_TIME					= 13,		// 开始时间
	PUZZLE_INSTANCE_END,
};

// 迷宫副本有效机制
enum PUZZLE_BUFF_EFFECT
{
	PUZZLE_BUFF_EFFECT_NONE						= 0,		
	PUZZLE_BUFF_EFFECT_AT_ONCE					= 1,		// 立即
	PUZZLE_BUFF_EFFECT_NEXT_FIGHT				= 2,		// 下一场战斗
	PUZZLE_BUFF_EFFECT_THIS_FLOOR				= 3,		// 本层
	PUZZLE_BUFF_EFFECT_THIS_INSTANCE			= 4,		// 本副本
};

// 迷宫任务类型
enum PUZZLE_TASK_TYPE
{
	PUZZLE_TASK_TYPE_NONE				= 0,
	PUZZLE_TASK_TYPE_MONSTER			= 1,	// 怪
	PUZZLE_TASK_TYPE_TREASURE			= 2,	// 宝箱
	PUZZLE_TASK_TYPE_TRANS_THIS_FLOOR	= 3,	// 本层传送
	PUZZLE_TASK_TYPE_TRANS_NEXT_FLOOR	= 4,	// 下一层传送
	PUZZLE_TASK_TYPE_BUFF				= 5,	// BUFF
	PUZZLE_TASK_TYPE_GIN				= 6,	// 陷阱
};

// 帮派加入标记
enum SYNDICATE_JOIN_FLAG
{
	SYNDICATE_JOIN_FLAG_BEGIN = 0,
	SYNDICATE_JOIN_FLAG_OPEN = 0,		// 开放, 所有人可加入
	SYNDICATE_JOIN_FLAG_APPLY = 1,		// 需要验证
	SYNDICATE_JOIN_FLAG_CLOSED = 2,		// 不能加入
	SYNDICATE_JOIN_FLAG_END,
};


// 任务更新类型枚举
enum EUPDATA_TASK_TYPE
{
	EUPDATA_TASK_TYPE_Beg   = 0,
	EUPDATA_TASK_TYPE_Add	= EUPDATA_TASK_TYPE_Beg,	// 增加任务
	EUPDATA_TASK_TYPE_Del	= 1,						// 删除任务
	EUPDATA_TASK_TYPE_Alter = 2,						// 修改任务
	EUPDATA_TASK_TYPE_End,
};

// 竞技场队伍位置
enum ARENA_TEAM_POSITION
{
	ARENA_TEAM_POSITION_BEGIN,
	ARENA_TEAM_POSITION_FIRST	= 1,					// 第一队
	ARENA_TEAM_POSITION_SECOND	= 2,					// 第二队
	ARENA_TEAM_POSITION_THIRD	= 3,					// 第三队
	ARENA_TEAM_POSITION_END		= 9999,
};

// 帮派日志类型
enum SYN_LOG_TYPE
{
	SYN_LOG_TYPE_BEGIN					= 0,
	SYN_LOG_TYPE_CREATE_SYN				= SYN_LOG_TYPE_BEGIN,	// 创建公会
	SYN_LOG_TYPE_DIRECT_JOIN_SYN		= 1,					// 直接加入公会
	SYN_LOG_TYPE_EXIT_SYN				= 2,					// 退出公会
	SYN_LOG_TYPE_KICK_SYN				= 3,					// 踢出公会
	SYN_LOG_TYPE_AlTER_NOTICE			= 4,					// 修改公告
	SYN_LOG_TYPE_UP_ELDER				= 5,					// 提升为长老
	SYN_LOG_TYPE_DOWN_MEMBER			= 6,					// 降职为会员
	SYN_LOG_TYPE_RESET_INSTANCE 		= 7,					// 团队副本重置
	SYN_LOG_TYPE_PASS_INSTANCE  		= 8,					// 团队副本通关
	SYN_LOG_TYPE_TRANSFER_LEADER		= 9,					// 移交会长
	SYN_LOG_TYPE_TROPHY_QUEUE			= 10,					// 战利品插队
	SYN_LOG_TYPE_AGREE_JOIN_SYN			= 11,					// 批准加入公会
	SYN_LOG_TYPE_ALTER_LEV_LIMIT		= 12,					// 修改加入公会等级限制
	SYN_LOG_TYPE_SHARE_TROPHY			= 13,					// 手动分配战力品
	SYN_LOG_TYPE_ALTER_LIMIT_TYPE		= 14,					// 修改公会加入类型(需要/不需要验证)
	SYN_LOG_TYPE_AUTO_TRANSFER_LEADER	= 15,					// 自动移交会长 
	SYN_LOG_TYPE_END,
};
/////////////////////////////////////////////////////////////////////////////////////////////////////
// 公会领地战系统相关枚举 
// 领地战部队阵营
enum TERRITORY_FIGHT_CAMP
{
	TERRITORY_FIGHT_CAMP_BEGIN,			
	TERRITORY_FIGHT_CAMP_ATTACK,								// 进攻方
	TERRITORY_FIGHT_CAMP_DEFENSE,								// 防守方
	TERRITORY_FIGHT_CAMP_END,
};
// 领地战阶段枚举
enum TERRITORY_STAGE_TYPE
{
	TERRITORY_STAGE_TYPE_BEGIN,
	TERRITORY_STAGE_TYPE_NOT_START,								// 活动未开始
	TERRITORY_STAGE_TYPE_PREPARE,								// 准备阶段			
	TERRITORY_STAGE_TYPE_MARCH,									// 行军阶段
	TERRITORY_STAGE_TYPE_FIGHTING,								// 战斗阶段
	TERRITORY_STAGE_TYPE_END,
};

// 领地战战斗类型
enum TERRITORY_FIGHT_TYPE
{
	TERRITORY_FIGHT_TYPE_BEGIN,
	TERRITORY_FIGHT_TYPE_MONSTER,								// 打怪
	TERRITORY_FIGHT_TYPE_USER,									// 打人
	TERRITORY_FIGHT_TYPE_END,
};
/////////////////////////////////////////////////////////////////////////////////////////////////////

// 膜拜类型
enum SYN_WORSHIP_TYPE
{
	SYN_WORSHIP_TYPE_NONE		= 0,
	SYN_WORSHIP_TYPE_FREE		= 1,	// 免费
	SYN_WORSHIP_TYPE_GOLD		= 2,	// 金币
	SYN_WORSHIP_TYPE_VAS		= 3,	// 钻石
};

enum EMPLOY_MERCENARY					// 佣兵雇佣类型
{
	EMPLOY_MERCENARY_NONE		= 0,
	EMPLOY_MERCENARY_INSTANCE	= 1,	// 副本雇佣
	EMPLOY_MERCENARY_WARROAD	= 2,	// 战役雇佣
	EMPLOY_MERCENARY_GOOSETOWER	= 3,	// 大雁塔雇佣
};

enum EMPLOY_STATE						// 佣兵雇佣状态
{
	EMPLOY_STATE_NONE			= 0,
	EMPLOY_STATE_USE			= 1,	// 使用中
	EMPLOY_STATE_SAVE			= 2,	// 保存
	EMPLOY_STATE_COOL			= 3,	// 冷却
};

enum EWARROAD_MODE_TYPE					// 战役模式类型
{
	EWARROAD_MODE_TYPE_NONE				= 0,
	EWARROAD_MODE_TYPE_NORMAL			= 1,	// 普通
	EWARROAD_MODE_TYPE_DIFFICULTY		= 2,	// 精英
	EWARROAD_MODE_TYPE_TEAM				= 3,	// 团队
};

enum EWARROAD_TEAM_FIGHT_TYPE			// 团队战役挑战状态类型
{
	EWARROAD_TEAM_FIGHT_TYPE_NONE		= 0,
	EWARROAD_TEAM_FIGHT_TYPE_PRE		= 1,	// 准备
	EWARROAD_TEAM_FIGHT_TYPE_FIGHT		= 2,	// 战斗
};

enum EGAME_HISTORY_COMPLETE_TYPE		// 历史成绩达成类型
{
	EGHCT_NONE							= 0,
	EGHCT_WARROAD_TEAM_CHAPTER_QUICK	= 1,	// 团队战役章节最快通关
	EGHCT_WARROAD_TEAM_CHAPTER_FIRST	= 2,	// 团队战役章节首次通关
};

enum EDATA_RESET_TYPE			// 重置类型
{
	EDRT_NONE					= 0,
	EDRT_WAR_ROAD_DIFFICULTY	= 1,	// 战役精英关卡重置
	EDRT_WAR_ROAD_TEAM			= 2,	// 团队战役章节重置（cout重用做章节）
	EDRT_POWER					= 3,	// 体力购买
	EDRT_ARENA					= 4,	// 竞技场挑战次数购买
	EDRT_MULTI_ARENA			= 5,	// 多队竞技场挑战次数购买
};

enum EGOOSE_FIGHT_POKER
{
	EGOOSE_FIGHT_POKER_Begin	= 0,
	EGOOSE_FIGHT_POKER_Self,			// 自己的卡牌
	EGOOSE_FIGHT_POKER_Mercenary,		// 佣兵
	EGOOSE_FIGHT_POKER_All,				// 所有
	EGOOSE_FIGHT_POKER_End,
};

enum ETALK_TYPE
{
	ETALK_TYPE_Begin = 0,
	ETALK_TYPE_Common,					// 普通
	ETALK_TYPE_TreasureShare,			// 宝藏分享
	ETALK_TYPE_End,
};

enum SYN_GIFT_BOX_TYPE						// 帮派礼盒类型
{
	SGBT_BEGIN			= 0,
	SGBT_SERVER_BEGIN	= SGBT_BEGIN,		// *服务器自定义礼盒开始*
	SGBT_RX_JIN_BOX		= 1,				// 任性金礼盒
	SGBT_RX_YIN_BOX		= 2,				// 任性银礼盒
	SGBT_RX_TONG_BOX	= 3,				// 任性铜礼盒
	
	SGBT_TENGYUN_BOX	= 4,				// 腾云礼盒
	SGBT_YUEGONG_BOX	= 5,				// 月宫礼盒
	SGBT_CHUYAO_BOX		= 6,				// 除妖礼盒
	SGBT_TUANBEN_BOX	= 7,				// 团本礼盒
	SGBT_DOUSHEN_BOX	= 8,				// 斗神礼盒
	SGBT_DAYAN_BOX		= 9,				// 大雁礼盒
	SGBT_HULU_BOX		= 10,				// 葫芦礼盒
	SGBT_HUOYUE_BOX		= 11,				// 活跃礼盒
	SGBT_SHENGJI_BOX	= 12,				// 升级礼盒
	SGBT_SERVER_END		= 100,				// *服务器自定义礼盒结束*

	SGBT_MONTH_CARD_BEGIN			= 1000,					// 月卡礼盒类型开始
	SGBT_MONTH_CARD_SERVER_BEGIN	= SGBT_MONTH_CARD_BEGIN,// *服务器自定义月卡礼盒开始*
	SGBT_MONTH_CARD_SERVER_END		= 1099,					// *服务器自定义月卡礼盒结束*

	SGBT_MONTH_CARD_END				= 2000,					// 月卡礼盒类型结束
	SGBT_END,
};

// 大雁塔消息Action
enum MSG_GOOSE_TOWER_ACTION
{
	MSG_GOOSE_TOWER_ACT_QueryTowerList		= 1,		// 请求查询大雁塔列表		C --> S
	MSG_GOOSE_TOWER_ACT_ReturnTowerList		= 2,		// 返回请求查询大雁塔列表	C <-- S
	MSG_GOOSE_TOWER_ACT_ReqChallenge		= 3,		// 请求挑战					C --> S
	MSG_GOOSE_TOWER_ACT_AckChallenge		= 4,		// 返回请求挑战				C <-- S
	MSG_GOOSE_TOWER_ACT_ReqGainAward		= 5,		// 请求领取奖励				C --> S
	MSG_GOOSE_TOWER_ACT_AckGainAward		= 6,		// 返回请求领取奖励			C <-- S
	MSG_GOOSE_TOWER_ACT_ReqResetTower		= 7,		// 请求重置大雁塔			C --> S
	MSG_GOOSE_TOWER_ACT_AckResetTower		= 8,		// 返回请求重置大雁塔		C <-- S
	MSG_GOOSE_TOWER_ACT_NotifyClearTower    = 9,		// 通知清空大雁塔数据		C <-- S
	MSG_GOOSE_TOWER_ACT_ReqFightPokerInfo	= 10,		// 请求大雁塔历史上阵卡牌信息C --> S
};

// 大雁塔消息结果
enum MSG_GOOSE_TOWER_RESULT
{
	MSG_GOOSE_TOWER_RESULT_Succ			= 0,	// 成功
	MSG_GOOSE_TOWER_RESULT_Error		= 1,	// 失败
	MSG_GOOSE_TOWER_RESULT_NoFloorInfo	= 2,	// 层信息不存在
};

// 花果山大战水果类型
enum FRUIT_TYPE
{
	FRUIT_TYPE_Begin  = 0,
	FRUIT_TYPE_None   = 0,
	FRUIT_TYPE_Banana = 1,		// 香蕉
	FRUIT_TYPE_Apple,			// 苹果
	FRUIT_TYPE_Peach,			// 桃子
	FRUIT_TYPE_Pineapple,		// 菠萝
	FRUIT_TYPE_Grape,			// 葡萄
	FRUIT_TYPE_Watermelon,		// 西瓜
	FRUIT_TYPE_End,
};

// 花果山大战手势
enum GESTURE_TYPE
{
	GESTURE_TYPE_BEGIN	= 0,
	GESTURE_TYPE_STONE	= GESTURE_TYPE_BEGIN,	// 石头
	GESTURE_TYPE_SCISSORS,						// 剪刀
	GESTURE_TYPE_CLOTH,							// 布
	GESTURE_TYPE_END,
};

// 花果山大战阶段
enum HGS_FIGHT_STATUS
{
	HGS_FIGHT_STATUS_Begin = 0,
	HGS_FIGHT_STATUS_Prepare,		// 准备阶段
	HGS_FIGHT_STATUS_Collect,		// 采集阶段
	HGS_FIGHT_STATUS_End,
};

/////////////////////////////////////////////////////////////////////////////////////////////////////
enum NTM_USER_TYPE			// 南天门玩家模型类型
{
	NTM_USER_TYPE_BEGIN	= 0,
	NTM_USER_TYPE_ELS	= 1,		// 二郎神（男）
	NTM_USER_TYPE_TTTW,				// 托塔天王（男）
	NTM_USER_TYPE_LG,				// 雷公（男）
		
	NTM_USER_TYPE_DM	= 101,		// 电母（女）
	NTM_USER_TYPE_BLN,				// 白龙女（女）
	NTM_USER_TYPE_CE,				// 嫦娥（女）
	NTM_USER_TYPE_END,
};

enum E_USER_STATE_FLAG		// 南天门活动状态标记
{
	EUSF_NONE				= 0,	
	EUSF_FIGHT				= 1,	// 战斗中
	EUSF_PK_DEFEND			= 2,	// PK保护状态
	EUSF_CONNECT_DEFEND		= 3,	// 重连保护状态
};

enum E_POKER_LIVE_FLAG		// 南天门卡牌存活标记
{
	EPLF_LIVE				= 0,	// 存活
	EPLF_DEAD				= 1,	// 死亡
	EPLF_RECOVER			= 2,	// 血量回满
	EPLF_REBORN				= 3,	// 重生
};
/////////////////////////////////////////////////////////////////////////////////////////////////////

// 花果山大战人物模型
enum HGS_USER_MODE
{
	HGS_USER_MODE_BEGIN = 0,
	HGS_USER_MODE_CBY = 1,	// 长臂猿
	HGS_USER_MODE_SWK = 2,	// 孙悟空
	HGS_USER_MODE_END,
};

// 消息推送开关类型
enum EMSG_SWITCH_TYPE
{
	EMSG_SWITCH_TYPE_Begin = 0,
	EMSG_SWITCH_TYPE_ReceivePower	= 1,	// 领取体力
	EMSG_SWITCH_TYPE_RefreshShop	= 2,	// 刷新商店
	EMSG_SWITCH_TYPE_PowerFull		= 3,	// 体力回复满
	EMSG_SWITCH_TYPE_SkillFull		= 4,	// 技能点回复满
	EMSG_SWITCH_TYPE_ArenaBeAtk		= 5,	// 竞技场被攻击
	EMSG_SWITCH_TYPE_PrivateTalk	= 6,	// 私聊消息通知
	EMSG_SWITCH_TYPE_MineFinish		= 7,	// 矿已踩完通知
	EMSG_SWITCH_TYPE_End,
};

// 消息推送开关状态
enum EMSG_SWITCH_STATUS
{
	EMSG_SWITCH_STATUS_Begin = 0,
	EMSG_SWITCH_STATUS_Close = 0,	// 关
	EMSG_SWITCH_STATUS_Open  = 1,	// 开
	EMSG_SWITCH_STATUS_End,
};

// 每日活跃宝箱类型枚举
enum ELIVENESS_BOX_TYPE
{
	ELIVENESS_BOX_TYPE_Beg		= 1,
	ELIVENESS_BOX_TYPE_Box25	= ELIVENESS_BOX_TYPE_Beg,	// 活跃度达到25对应宝箱	
	ELIVENESS_BOX_TYPE_Box50	= 2,						// 活跃度达到50对应宝箱
	ELIVENESS_BOX_TYPE_Box75	= 3,						// 活跃度达到75对应宝箱
	ELIVENESS_BOX_TYPE_Box100	= 4,						// 活跃度达到100对应宝箱
	ELIVENESS_BOX_TYPE_End,
};

// 每日活跃宝箱状态枚举
enum ELIVENESS_BOX_STATUS
{
	ELIVENESS_BOX_STATUS_Beg	= 0,
	ELIVENESS_BOX_STATUS_Unopen = ELIVENESS_BOX_STATUS_Beg,	// 未打开
	ELIVENESS_BOX_STATUS_Open	= 1,						// 打开
	ELIVENESS_BOX_STATUS_End,
};

// 每日活跃项的领取状态
enum ELIVENESS_STATUS
{
	ELIVENESS_STATUS_Beg		= 0,
	ELIVENESS_STATUS_NotGain	= ELIVENESS_STATUS_Beg,	// 未领取
	ELIVENESS_STATUS_Gain		= 1,					// 领取
	ELIVENESS_STATUS_End,
};

// 每日活跃ID
enum LIVENESS_TYPE
{
	LIVENESS_TYPE_Begin			= 0,
	LIVENESS_TYPE_Lunch			= 1,		// 豪华午餐
	LIVENESS_TYPE_Dinner		= 2,		// 豪华晚餐
	LIVENESS_TYPE_NightFood		= 3,		// 豪华宵夜
	LIVENESS_TYPE_MonthCard		= 4,		// 月卡
	LIVENESS_TYPE_UpSkill		= 5,		// 技能升级
	LIVENESS_TYPE_EquipMagic	= 6,		// 装备附魔
	LIVENESS_TYPE_Lottery		= 7,		// 抽卡
	LIVENESS_TYPE_NormalGate	= 8,		// 普通推图
	LIVENESS_TYPE_HeroGate		= 9,		// 精英推图
	LIVENESS_TYPE_GooseTower	= 10,		// 大雁塔
	LIVENESS_TYPE_Instance		= 11,		// 广寒宫
	LIVENESS_TYPE_ChallengeBoss	= 12,		// 万妖洞(挑战bosss)
	LIVENESS_TYPE_Arena			= 13,		// 竞技场
	LIVENESS_TYPE_Mine			= 14,		// 矿场掠夺
	LIVENESS_TYPE_Wroship		= 15,		// 膜拜
	LIVENESS_TYPE_MoneyTree		= 16,		// 聚宝盆(摇钱树)
	LIVENESS_TYPE_WarRoad		= 17,		// 团队副本
	LIVENESS_TYPE_GiveRose		= 18,		// 赠送玫瑰
	LIVENESS_TYPE_GainClearBook	= 19,		// 领取扫荡卷
	LIVENESS_TYPE_End,
};

// 完成活跃的需要类型
enum LIVENESS_NEED_TYPE
{
	LIVE_NEED_TYPE_Begin			= 0,
	LIVE_NEED_TYPE_Feast			= 1,		// 大餐
	LIVE_NEED_TYPE_MonthCard		= 2,		// 月卡
	LIVE_NEED_TYPE_UpSkill			= 3,		// 技能升级
	LIVE_NEED_TYPE_EquipMagic		= 4,		// 装备附魔
	LIVE_NEED_TYPE_Lottery			= 5,		// 抽卡
	LIVE_NEED_TYPE_NormalGate		= 6,		// 普通推图
	LIVE_NEED_TYPE_HeroGate			= 7,		// 精英推图
	LIVE_NEED_TYPE_GooseTower		= 8,		// 大雁塔
	LIVE_NEED_TYPE_Instance			= 9,		// 广寒宫
	LIVE_NEED_TYPE_ChallengeBoss	= 10,		// 万妖洞(挑战bosss)
	LIVE_NEED_TYPE_Arena			= 11,		// 竞技场
	LIVE_NEED_TYPE_Mine				= 12,		// 矿场掠夺
	LIVE_NEED_TYPE_Wroship			= 13,		// 膜拜
	LIVE_NEED_TYPE_MoneyTree		= 14,		// 摇钱
	LIVE_NEED_TYPE_WarRoad			= 15,		// 团队副本
	LIVE_NEED_TYPE_GiveRose			= 16,		// 赠送玫瑰
	LIVE_NEED_TYPE_GainClearBook	= 17,		// 领取扫荡卷
	LIVE_NEED_TYPE_End,
};

// 需要推送的提示信息类型
enum MSG_MARKS_TYPE
{
	MSG_MARKS_TYPE_BEGIN						= 0,
	MSG_MARKS_TYPE_POKER_EQUIP					= 1,	// 英雄		*客户端自动检测英雄和背包			（有英雄可以穿戴背包里的装备或者可以合成后穿戴）
	MSG_MARKS_TYPE_ACHIEVEMENT					= 2,	// 成就		完成的成就数量						（有可以领奖）
	MSG_MARKS_TYPE_FRIEND_GIFT					= 3,	// 好友		好友赠送礼物数量					（有好友赠送了礼物）
	MSG_MARKS_TYPE_FRIEND_CHARGEAWARD			= 4,	// 好友		好友充值返利奖励数量				（好友邀请里面有奖励可以领取, 充值返利）
	MSG_MARKS_TYPE_FRIEND_LOGINAWARD			= 5,	// 好友		好友昨日登陆奖励数量				（好友邀请里面有奖励可以领取, 登陆奖励）
	MSG_MARKS_TYPE_FRIEND_APPLY					= 6,	// 好友		好友申请数量						（当有添加好友申请时，需要提示，点击搜索按钮后，提示消失）
	MSG_MARKS_TYPE_LIVENESS						= 7,	// 每日活跃 可开的宝箱数 + 可以领奖的活跃项数	（有领奖的或者宝箱可以开启的）
	MSG_MARKS_TYPE_LOTTERY						= 8,	// 幸运星	是否可以免费抽奖					（有免费抽奖时，幸运星文字按钮有信息提示，免费抽取后，信息提示消失（免费抽奖进入CD不需要信息提示））
	MSG_MARKS_TYPE_MAIL							= 9,	// 信翁		未读邮件数量						（有未读邮件时，信翁文字按钮有信息提示；读取完所有未读邮件，信息提示消失）
	MSG_MARKS_TYPE_ARENA_NORMAL					= 10,	// 斗神台	（普通模式）是否被打败了			（被别的玩家击败了，斗神台文字按钮有信息提示）
	MSG_MARKS_TYPE_SYNDICATE_APPLY				= 11,	// 帮派		帮派申请数量						（帮派设置成了需要批注才能入帮，有玩家申请时，有权限的玩家（帮主和长老）需要有信息提示）
	MSG_MARKS_TYPE_SYNDICATE_GIFTBOX			= 12,	// 帮派		可领取的帮派礼盒数量				（帮派礼盒有可以领取时提示)
	MSG_MARKS_TYPE_MINE_COMPLETE				= 13,	// 乾坤葫芦	可领奖励的矿洞数					（已经开采完，需要有信息提示）
	MSG_MARKS_TYPE_MINE_BE_CHALLENGE			= 14,	// 乾坤葫芦	是否被别人掠夺了					（被别人掠夺了，需要有信息提示）
	MSG_MARKS_TYPE_SIGN							= 15,	// 签到		是否签到过							（当天还未签到，签到按钮出现信息提示，签到后信息提示消失）
	MSG_MARKS_TYPE_ARENA_SPETIAL				= 16,	// 斗神台	（任性模式）是否被打败了			（被别的玩家击败了，斗神台文字按钮有信息提示）
	
	MSG_MARKS_TYPE_END,
};

/////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // end of _MAPGROUP_SHARE_ENUM_DEF_H_
