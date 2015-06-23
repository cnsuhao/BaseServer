#ifndef CN_RES_H
#define CN_RES_H
//---------------------------------------------------------------------------
//---jinggy---2004-11-19--圣战---begin
#define STR_FIGHTER_EUDEMON_NAME            "狂暴 ·巴芬亚" //tcp2005.9.13 add
#define STR_MAGICIAN_EUDEMON_NAME           "暗夜·提拉克"  //tcp2005.9.13 add
#define STR_GHOSTLEVEL_EUDEMON_NOTCOMPETENT	"★ 升级装备魔魂等级失败，幻兽不符合条件！★"
#define STR_GHOSTLEVEL_SUCCESS				"★ 升级装备魔魂等级成功，恭喜你！希望继续努力！★"
#define STR_GHOSTLEVEL_FAILED				"★ 升级装备魔魂等级失败，这次你的运气不是很好，请再接再厉！★"
#define STR_GHOSTLEVEL_FAILED_NOTYPE		"★ 没有对应的数据！★"

#define STR_EMBED_SUCC	"嵌入成功！"
#define STR_EMBED_FAIL	"嵌入失败！"
#define STR_UPEQUIPLEVEL_FAIL_NOTYPE		"★ 升级装备等级失败！没有对应的设备！★"
#define STR_UPEQUIPLEVEL_FAIL				"★ 升级装备等级失败！★"
#define STR_UPEQUIPLEVEL_SUCC				"★ 升级装备等级成功！★"

#define STR_UPEQUIPLEVE_SUCC				"★ 升级装备的等级成功，恭喜你！希望继续努力！★"
#define STR_UPEQUIPLEVE_FAIL				"★ 升级装备的等级失败，这次你的运气不是很好，请再接再厉！★"

//状态攻击类1---10-GEM  升级技能
#define STR_GEMSKILL_FORGE_SUCCESS			"★ 状态攻击类宝石打造成功，恭喜你！继续努力啊！★"

#define STR_QUALITY_UPGRADE_SUCCESS         "★ 升级装备品质成功，恭喜你！继续努力啊！★"
#define STR_QUALITY_UPGRADE_FAILED          "★ 升级装备品质失败，这次你的运气不是很好，请再接再厉！★"
#define STR_QUALITY_UPGRADE_MAXLEVEL        "★ 升级装备品质失败，你的装备已经是最高品质了！★"
#define STR_QUALITY_ADD_HOLE                "★ 恭喜你，设备上加了个洞，此洞可以用于镶嵌宝石！★"//tcp2005.9.15 add
#define STR_QUALITY_EUDEMON_ATTACK          "★ 恭喜阁下，您的武器获得额外属性，%s增强效果%d！★"//tcp2005.9.15 add
#define STR_EUDEMON_ATTACK1                  "地攻击"//tcp2005.9.15 add
#define STR_EUDEMON_ATTACK2                  "水攻击"//tcp2005.9.15 add
#define STR_EUDEMON_ATTACK3                  "火攻击"//tcp2005.9.15 add
#define STR_EUDEMON_ATTACK4                  "风攻击"//tcp2005.9.15 add


#define STR_ITEM_CHANGETYPE_FAILED          "★ 升级装备品质失败，没有对应的类型！★"
#define STR_ITEM_CHANGEADDITION_FAILED      "★ 追加装备属性失败，没有对应的类型 ★"

#define STR_SYN_CANNOT_UPMEMBERLEVEL        "升级帮派成员等级失败，你的条件还不符合！"
#define STR_SYN_SUCCESS_UPMEMBERLEVEL        "升级帮派成员等级成功，希望再接再厉！"

#define STR_SYN_APPLYATTACKSYN_SUCCESS        "申请攻打该城市成功，请三日后来攻城！"
#define STR_SYN_APPLYATTACKSYN_FAIL          "申请攻打该城市失败，阁下的帮派条件不符合！"
#define STR_SYN_APPLYATTACKSYN_HASBEENAPPLIED "申请攻打该城市失败，已经有人申请攻打了！"

#define STR_SYN_APPLYKICKOUT_MEMBER         "已经向帮主发出开除请求！"

#define STR_SYN_SETSUBLEADER_NOPROFFER		"不能设置，贡献度不足！"
#define STR_SYN_APPLY_JOIN_FAILED			"请找帮主或副帮主加入！"
#define STR_SYN_NOTENOUGH_PROFFER_LEAVE		"您的帮会贡献度小于%d，不允许退帮会！"
#define STR_SYN_LEAVE_s						"%s 退出了帮会！"

#define STR_ACTION_USER_FLYTOMAINMAP_ERROR	"主地图不存在，回城卷无法使用！"
#define STR_ACTION_IDENT_SUCC				"鉴定成功！"
#define STR_ACTION_IDENT_FAIL				"鉴定失败！"
#define STR_ACTION_IDENT_FAIL_DISAPPEAR		"鉴定失败，物品已损坏！"

#define STR_SYN_SETDRESS_SUCC				"设置帮派服装成功！"
#define STR_SYN_PUTONDESS_ERR				"必须是团长才能下穿帮派服装的命令！"
#define STR_SYN_CREATESUBSUB_ERR			"不符合条件或分队已经满了！"
#define STR_SYN_DEMISE_SUCC					"您将团长职位禅让给了%s"
#define STR_SYN_DEMISE_CON					"恭喜您成为了%s帮主"
#define STR_SYN_DEMISE_PROMPT				"%s出任%s帮主一职"
#define STR_SYN_SETSUBLEADER_ERR			"%s等级不足或对帮会的贡献不够，不能出任该职务。"

#define STR_SYN_SETSUBLEADER_SUCC			"您册封了%s为%s副帮主一职"
#define STR_SYN_SETSUBLEADER_CON			"恭喜您成为了%s副帮主"
#define STR_SYN_SETSUBLEADER_PROMPT			"%s出任%s分团副团长一职"

#define STR_SYN_SETSUBSUBLEADER_SUCC		"您册封了%s为%s分队队长一职"
#define STR_SYN_SETSUBSUBLEADER_CON			"恭喜您成为了%s分队队长"
#define STR_SYN_SETSUBSUBLEADER_PROMPT		"%s出任%s分队队长一职"
#define STR_SYN_CREATE_SUBSUBSYN_ERROR		"创建分队，必须是分团的团长！"

//鉴定
#define STR_IDENT_NORMAL					"鉴定成功，得到%s"
#define STR_IDENT_QUALITY_ONE				"鉴定成功，得到良品 %s"
#define STR_IDENT_QUALITY_TWO				"鉴定成功，得到上品 %s"
#define STR_IDENT_QUALITY_THREE				"鉴定成功，得到精品 %s"
#define STR_IDENT_QUALITY_FOUR				"鉴定成功，得到极品 %s"

//聊天室
#define STR_CHATROOM_NAME								"聊天室%d"
#define STR_CHATROOM_CANNOT_INMOREROOM					"不能同时进入多个聊天室！"
#define STR_CHATROOM_CANNOT_INMOREROOM_FORNOMONEY		"金钱不够，不能进入聊天室！"
#define STR_CHATROOM_WELCOME							"%s，欢迎阁下光临 %s 聊天室，本聊天是管理员为%s"
#define STR_CHATROOM_LEAVE								"%s 离开了 %s 聊天室！"
#define STR_CHATROOM_CANAPPLYMANAGER					"管理员%s在规定时间内没有上线。允许玩家申请成为管理员！"
#define STR_CHATROOM_MEMBERFULL							"本聊天室人员已经满了！"
#define STR_CHATROOM_ROOMFEE_MODIFY						"当前聊天室费用已经更改，为%d金币"

#define STR_DROPITEM_PROMPT				"您丢弃了%s ！"
#define STR_NOTIFYFRIEND_USERLEAVEMAP	"%s离开游戏！"
#define STR_NOTIFYFRIEND_USERENTERMAP	"%s进入游戏！"
//---jinggy---2004-11-19--圣战---end
#define	STR_DOUBLE_MANTLE_FLAG		"此团标已经有人使用过了，请重新选择团标。"
#define	STR_SETLOCK					"setlock"
#define	STR_UNLOCK					"unlock"
#define	STR_CLEARLOCK				"clearlock"
#define	STR_SETLOCK_HELP			"设置“保护锁”密码之前不能有旧的密码，密码必须为 6 ~ 9 位整数，不能使用字母或符号，也不能使用过于简单的密码。使用方法：/setlock 密码"
#define	STR_UNLOCK_HELP				"临时打开“保护锁”，下线会自动加锁。使用方法：/unlock 密码"
#define	STR_CLEARLOCK_HELP			"永久清除“保护锁”密码。使用方法：/clearlock 旧密码"
#define	STR_SETLOCK_OK				"已设置“保护锁”的密码。可使用“/unlock 密码”临时打开保护锁，也可使用“/clearlock 旧密码”永久清除保护锁。"
#define	STR_SETLOCK_FAIL			"设置“保护锁”失败! 设密码之前不能有旧的密码，密码必须为 6 ~ 9 位整数，不能使用字母或符号，也不能使用过于简单的密码。"
#define	STR_UNLOCK_OK				"已打开“保护锁”，下线后会自动加锁。"
#define	STR_CLEARLOCK_OK			"已永久清除“保护锁”，该帐号不再受到“保护锁”的保护。如需重新设置保护锁，请使用“/setlock 密码”。"
#define	STR_LOCKKEY_DENY			"请先打开“保护锁”。使用方法：/unlock 密码"
#define STR_SUPER_ATK_ADD			"技能启动：%d秒内攻击力增加%d。"
#define STR_SUPER_DEF_ADD			"技能启动：%d秒内防御力增加%d。"
#define STR_SUPER_MATK_ADD			"技能启动：%d秒内魔法攻击力增加%d。"
#define STR_SUPER_MDEF_ADD			"技能启动：%d秒内魔法防御力增加%d。"
#define	STRING_BET_WIN				"%s红光满面，双眉带彩，玩骰子赢了%d金币！"
#define	STR_AWARD_VIRTUE_su			"%s得到功德值%u。"
#define	STR_SYNDICATE_LEADER		"帮主"
#define	STR_SYNDICATE_LEADER2		"副帮主"
#define	STR_SYNDICATE_LEADER3		"近卫团团长"
#define	STR_SYNDICATE_LEADER4		"近卫团副团长"
#define	STR_SYNDICATE_LEADER5		"近卫团代团长"
#define	STR_SYNDICATE_MEMBER		"军团团员"
#define	STR_ERROR					"错误"
#define	STR_DELETE_FAILED			"删除失败!"
#define	STR_YOUR_CANNOT_WALK		"您不能走！"
#define	STR_TOP_LIST_dsd			"第%d名：%s(%d)"
#define	STR_INC_MOUNT_INTIMACY		"您的坐骑的亲密度增加了。"
#define	STR_DEC_MOUNT_INTIMACY		"您的坐骑的亲密度下降了。"
#define	STR_KICKOUT_ALL_AFTER		"开始处理kickoutall，服务器禁止登录。%d秒之后，所有玩家退出。"
#define	STR_KICKOUT_ALL				"开始处理kickoutall，服务器禁止登录，所有玩家退出中 . . ."
#define	STR_LOGIN_ANOTHER			"有人正在登陆此帐号。"
#define	STR_LOGIN_AGAIN				"此帐号已经有人登陆。"
#define	STR_KO_LIST_TITLE			"名次  姓名           数量"
#define	STR_TEAM_MONEY_s			"捡钱开关 %s"
#define	STR_TEAM_ITEM_s				"捡物品开关 %s"
#define STR_TEAM_GEM_s				"捡宝石开关 %s"
#define	STR_OPEN					"开"
#define	STR_CLOSE					"关"
#define STR_NOT_DISCARDABLE			"此物品不能丢弃。"
#define STR_NOT_SELL_ENABLE			"此物品不能出售。"
#define STR_NEXT_PAGE				"下一页"
#define STR_CLOSE_BUTTON			"关闭"
#define STR_TOO_LOWER_SYN_MONEY		"帮会基金不足，该功能已关闭。"
#define STR_SYN_AMOUNT_LIMIT        "帮会人员不足，即将被强制解散，请尽快补充人员"
#define STR_SYN_MONEY_LIMIT         "帮会资金不足，即将被强制解散，请尽快补充资金"
#define	STR_APPLY_ALLY_FAILED		"双方必须是帮主!"
#define STR_HITRATE_ADD				"技能启动：%d秒内命中率增加%d%%。"
#define STR_DEFENCE_ADD				"技能启动：%d秒内防御力增加%d%%。"
#define STR_ATTACK_ADD				"技能启动：%d秒内攻击力增加%d%%。"
#define STR_HITRATE_ADD2			"技能启动：%d秒内命中率增加%d。"
#define STR_DEFENCE_ADD2			"技能启动：%d秒内防御力增加%d。"
#define STR_ATTACK_ADD2				"技能启动：%d秒内攻击力增加%d。"
#define EXPLOST_PAYBY_SYNFUND		"帮会基金抵消经验损失%u。"
#define MALE_MATE_LOGIN				"您的先生来了"
#define FEMALE_MATE_LOGIN			"您的夫人来了"
#define NOMATE_NAME					"无"
#define TITILE_NONE					"无"
#define SYNNAME_NONE				"无"
#define	ACTIONSTR_NONE				"无"
#define	STR_DESTROY_SYNDICATE_SOON	"贵帮会因军团基金耗尽，即将被系统强行解散。请及时补充帮会基金。"
#define	STR_TARGET_OFFLINE			"对方不在线，或在副本中。"
#define	STR_SYNDICATE_COMBINESUB_ss	"帮会 %s 被 %s 帮会吞并了。"
#define	STR_NEXTEQP_OVERLEV			"下一个等级的装备已经超出阁下当前等级！"
#define	STR_BOOTH_BUY_sds			"%s 花了 %d 金币购买你的%s。"
#define	STR_DISABLE_LAY_SYNTRANS	"该地图禁止放置此类NPC!"
#define	STR_ITEM_LEV_TOO_HIGH		"装备需求等级太高!"
#define	STR_TEAM_HUNT				"%s做恶多端，终于被以%s为首的缉捕队伍抓获!"
#define	STR_FOND_WANTED				"发现悬赏目标【%s】！"
#define	STR_FOND_POLICEWANTED		"发现官方悬赏目标【%s】！"
#define	STR_CANT_STORAGE			"该物品不能存放!"
#define	STR_SYN_FULL				"错误：帮会人数已满!"
#define	STR_JOIN_SYN_FAILED			"错误：加入失败!"
#define	STR_INVALID_PET_NAME		"错误：不允许的名字!"
#define STR_JOIN_SYN_s				"恭喜您成为 %s 帮会成员。"
#define STR_SYN_NOTIFY_JOIN_s		"号外！号外！%s 加入了帮会。"
#define	STR_KICKOUT_MEMBER_ss		"%s被开除出了%s帮会。"
#define	STR_KICKOUT_ME_s			"你被%s从帮会中开除。"
#define STR_SYN_ALLY_s				"恭喜 %s 帮会与 %s 帮会结为兄弟帮会。"
#define STR_SYN_CLEAR_ALLY1_s		"与 %s 帮会解除盟友之约。"
#define STR_SYN_CLEAR_ALLY2_s		"%s 帮会与您的帮会解除盟友之约！"
#define STR_SYN_ENEMY_s				"%s 帮会将您的帮会列为敌对帮会。"
#define STR_SYN_CLEAR_ENEMY_s		"%s 帮会将与您的帮会解除敌对状态。"
#define	STR_NO_BONUS				"抱歉，没有奖品或者奖品 或 没有经过领奖网页确认。"
#define	STR_WARNING_CRASH			"注意：此命令只用于本地测试，否则可能导致服务器崩溃!"
#define	STR_CAN_STAND				"目标点不能落脚!"
#define	STR_SET_MAX_PLAYERS_u		"最大允许登录人数改为: %u"
#define	STR_SHOW_PLAYERS_uu			"当前在线:%u, 最大在线:%u"
#define	STR_ARRESTMENT_PK_MODE		"善恶PK模式，你可以攻击怪物和黑名、蓝名玩家，不会伤害到其它人。"
#define STR_SYNDICATE_PK_MODE       "军团PK模式，你可以PK所有除本帮会及同盟帮会之外的玩家。"
#define	STR_TEAM_PK_MODE			"组队PK模式，你可以攻击怪物和其它人，不会伤害到自己和队友。"
#define	STR_SAFE_PK_MODE			"安全PK模式，你只能攻击怪物，不会伤害到其它任何玩家。"
#define	STR_FREE_PK_MODE			"全体PK模式，你可以攻击任何人。"
#define	STR_NEED_PICK				"必须要装备锄头才能挖矿。"
#define	STR_SYNDICATE_DESTROY_s		"%s 含泪解散了 %s 帮会。"
#define	STR_SYNDICATE_CREATE_ss		"恭喜 %s 帮会创建%s成功。 "
#define	STR_SYN_LEADER_LOSE_uss		"军团[%u][%s]军团长失踪，玩家[%s]暂代帮主之职。"
#define	STR_DONATE_ssd				"%s 捐赠 %u 金币，用于帮会的建设！"
#define	STR_SYN_WAR_END				"城堡攻防战结束!"
#define	STR_SYN_WAR_START			"城堡攻防战开始!"
#define	STR_GOT_WIN_s				"%s获得胜利!"
#define	STR_ERROR_DUPLICATE_NAME	"错误：人物已存在!"
#define	STR_ERROR_ILLEGAL_NAME		"错误：角色名不合法!"
#define	STR_ERROR_ILLEGAL_NAME2		"错误：名字不合法!"
#define	STR_ERROR_ILLEGAL_PASSWORD	"错误：密码不合法!"
#define	STR_ERROR_ILLEGAL_ACCOUNT	"错误：帐号名不合法!"
#define	STR_ERROR_SERVER_FULL		"错误：服务器人数已满，请稍后重新登录!"
#define	STR_ERROR_LOWER_VERSION		"错误：版本号错误，请更新客户端!"
#define	STR_ERROR_VERSION			"错误：版本号错误!"
#define	STR_FEW_FEE_NOTIFY			"您的包月卡将于 %s 到期，请及时充值。"
#define	STR_ACCOUNT_NOFEE			"您的帐号还没有充值。"
#define	STR_LOGIN_ISP_FAIL			"登录到ISP计费系统失败。目前正在使用您自己的帐号进行计费。"
#define	STR_FEETYPE_KNOWN			"计费类型：未知。"
#define	STR_FEETYPE_HOUR			"计费类型：小时卡，剩余小时数：%d.%d。"
#define	STR_FEETYPE_MONTH			"计费类型：包月卡。到期时间：%d年%d月%d日。"
#define	STR_FEETYPE_BARHOUR			"计费类型：网吧计点。"
#define	STR_FEETYPE_BARMONTH		"计费类型：网吧月卡。许可证数量%d。"
#define	STR_FEETYPE_ISP				"计费类型：ISP计费。"
#define	STR_FEETYPE_FREE			"计费类型：免费测试。"
#define	STR_SHUTDOWN_NOTIFY			"服务器维护，停机三十分钟；请大家立即下线，避免数据丢失。"
#define	STR_NONSUCH_TRADE_sssu		"[交易] 极品交易，玩家[%s]给玩家[%s]物品[%s][%u]"
#define	STR_NOT_SO_MUCH_MONEY	    "您身上没有这么多钱！"
#define	STR_NOT_ENOUGH_MONEY	    "你的钱不足%d金币!"
#define	STR_ATTACK_POLICE	        "阁下涉嫌袭警，请好自为之，以免惹火上身。"
#define	STR_KILLING_EXPERIENCE	    "获击杀额外经验%u。"
#define	STR_KILLING_EXPEX			"获低等级队友奖励和击杀额外经验%u。"
#define	STR_BAG_FULL	            "背包已满!"
#define	STR_TRADE_SUCCEED	        "交易成功。"
#define	STR_TRADE_FAIL	            "交易失败!"
#define	STR_USE_ITEM	            "您用掉了一件物品。"
#define	STR_INVALID_GUILD_NAME		"帮会名字不合法!"
#define	STR_GUILD_FUND_NOT_ENOUGH	"帮会基金不足%u金币!"
#define	STR_NOT_AUTHORIZED	        "你没有这个权力!"
#define	STR_ALLY_FULL	            "同盟表已满!"
#define	STR_SYN_PLACE_FULL	        "该军衔数量已满!"
#define	STR_WANTED_ORDER	        "扣除定金%u金币，取得%d号悬赏单，目标：%s，赏金：%u 金币。"
#define	STR_WANTED_INFO				"据传此人最近在【%s】一带活动。"
#define	STR_INVALID_WANTED	        "错误的悬赏号！"
#define	STR_MAX_BONUTY				"赏金最大不能超过%d金币！"
#define	STR_MIN_BONUTY				"赏金最少不能低于%d金币！"
#define	STR_SUPERADD_BONUTY			"悬赏%u号赏金上升为%u金币！"
#define	STR_LOWEST_SUPERADD_BONUTY	"最低添加悬赏额为%u金币！"
#define	STR_CANCEL_WANTED			"悬赏%u号已经撤销。"
#define	STR_NO_DISBAND	            "帮主不能直接退出军团，您可以将您的军团解散。"
#define	STR_PROTECTED_CODE	        "请先打开保护锁。"
#define	STR_HIS_ALLY_FULL	        "对方的同盟表已满!"
#define	STR_NOT_HERE	            "该玩家不在附近!"
#define	STR_CANNOT_RANK				"无法设置军衔!"
#define	STR_NOT_ENOUGH_LEV			"你的等级不足%d级!"
#define	STR_LEVEL_NOT_ENOUGH	    "%s等级不足或对帮会的贡献不够，不能出任该职务!"
#define	STR_INVALID_NAME	        "名字不合法。"
#define	STR_INVALID_MSG	            "非法消息！"
#define	STR_MAGIC_FAILED            "魔法使用失败！"
#define	STR_CANNOT_DEPOSIT	        "错误：此物品不宜存放!"
#define	STR_FORBIDDEN_GUILD_NAME	"您不能使用这个帮会名称。"
#define	STR_GUILD_INEXIST	        "帮会不存在。"
#define	STR_TEAM_EXPERIENCE	        "获得了奖励经验%d"
#define	STR_TEAM_EXPEX				"获得组队和低等级队友奖励经验%d"
#define	STR_LOST_EXPERIENCE	        "你损失了%d点经验值!"
#define	STR_KILLING_TO_MUCH	        "杀人过多，将受到红名的惩罚"
#define	STR_NOT_PK_MODE	            "当前模式下不能攻击对方！"	
#define	STR_NOT_PK_EXP	            "经验为负的情况下不能PK。"	
#define	STR_PK_FORBIDDEN	        "此处禁止殴斗。"
#define	STR_MSG_SENT	   		    "留言成功，对方上线后就能看到你的留言。"	
#define	STR_MSG_FAILED				"每个好友留言间隔不能少于%d分钟，留言失败。"
#define	STR_INVALID_COORDINATE	    "非法坐标。"
#define	STR_GONE	                "走了"
#define	STR_JUMPED	                "跳了"
#define	STR_CONNECTION_OFF	        "客户端网络连接异常，系统自动关闭连接。"
#define	STR_WEAPON_SKILL_UP	        "恭喜阁下武器熟练度升级！"
#define	STR_FULLBAG_NO_MORE	        "阁下行囊已满，无法放入更多物品。"
#define STR_ITEMBAG_FULL			"您的物品背包空间已满，不能放置更多的物品。"
#define STR_GEMBAG_FULL				"您的宝石背包空间已满，不能放置更多的物品。"
#define	STR_HEAVEY_BAG	            "阁下行囊过重，无法放入更多物品。"
#define	STR_ITEM_NOT_FOUND	        "物品找不到!"
#define	STR_ITEM_INEXIST	        "物品不存在!"
#define	STR_MONEYBAG_FULL	        "您的钱袋已满!"
#define	STR_MAKE_ITEM_FAILED        "产生地图物品[%u]失败。"
#define	STR_MAKE_MONEY_FAILED	    "产生地图金币[%d]失败。"
#define	STR_DAMAGED_REPAIR	        "%s即将损坏，请尽快修复，否则将彻底消失!"
#define	STR_DURABILITY_REPAIR	    "%s耐久度太低，请尽快修复，以免损伤。"
#define	STR_FAR_CANNOT_PICK	        "物品太远，无法拾取。"
#define	STR_FULL_CANNOT_PICK	    "物品栏已满，无法拾取物品。"
#define	STR_PICK_MONEY	            "捡到 %u 个金币。"
#define	STR_FAILED_GENERATE_ITEM	"产生物品失败。"
#define	STR_OTHERS_ITEM	            "别人的打的东西，暂时不能拾取!"	
#define	STR_GOT_ITEM	            "得到物品%s。"
#define	STR_GOT_IDENT_ITEM	        "得到未鉴定物品。"
#define	STR_DRAGONBALL	            "改良装备辅助物品必须是【龙珠】。"
#define	STR_REPAIR_THEN_IMPROVE	    "改良装备必须是修复好的物品。"
#define	STR_SUPERIOR_ALREADY	    "此装备已经是极品了。"
#define	STR_CONNOT_IMPROVE	        "该装备无法改良。"
#define	STR_METEOR	                "升级装备的辅助物品必须是【流星】。"
#define	STR_REPAIR_THEN_UPGRADE	    "升级装备必须是修复好的物品。"
#define	STR_UPGRADE_NOMORE	        "此装备无法继续升级！"
#define	STR_MINE_WITH_PECKER   	    "必须要装备锄头才能挖矿。"
#define	STR_NO_MINE	                "此地没有矿藏。"
#define	STR_GOLD_ORE	            "得到一个金矿石！"
#define	STR_EUXENITE_ORE	        "得到一个黑铁矿！"
#define	STR_IRON_ORE	            "得到一个铁矿石！"
#define	STR_COPPER_ORE	            "得到一个铜矿石！"
#define	STR_SILVER_ORE	            "得到一个银矿石！"
#define	STR_GAIN_GEM	            "恭喜获得一颗宝石！"
#define	STR_UNQUALIFIED	            "错误：条件检查失败！"
#define	STR_DIE	                    "您已经死了!"
#define	STR_DONOT_GIVE_UP	        "阁下身负重任，怎可自暴自弃？"	
#define	STR_CANNOT_JUMP	            "您不能跳！"
#define	STR_CHEAT	                "[作弊]你要分配的点数大于拥有的可分配点数。"
#define	STR_FRIEND_LIST_FULL	    "好友列表已满。"
#define	STR_YOUR_FRIEND_ALREADY	    "对方已经是好友了。"
#define STR_NOTALLOWFRIEND			"对方不允许被加为好友."
#define	STR_MAKE_FRIEND_SENT        "已经发送结为好友的请求"		
#define	STR_NOT_YOUR_FRIEND	        "%s 不是你的朋友。"
#define	STR_NEVER_PROPOSED	        "%s 没有向你求过婚。"
#define	STR_SINGLE	                "您尚未，如何能够离婚"
#define	STR_NOT_YOUR_SPOUSE	        "%s 和您并非夫妻关系。"
#define	STR_NOT_ENOUGH_MANA	        "您的魔力不足。"
#define	STR_UNABLE_USE_ITEM	        "无法使用物品!"
#define	STR_YOUR_BAG_FULL	        "物品栏已满!"
#define	STR_SELFCARE			    "自顾身份。"
#define	STR_CAUTION					"小心为妙。"
#define	STR_BALANCED			    "势均力敌。"
#define	STR_INVALID_AMOUNT	        "数量错误!"	
#define	STR_REPAIR_FAILED	        "不能修理!"
#define	STR_REPAIR_NO_MONEY_d	    "修理需要花费%d个金币，金币不足无法修理！"
#define	STR_INVALID_TITLE	        "错误：军衔名不合法!"
#define	STR_NOT_FROM_YOUR_GUILD	    "对方不是您帮会的成员。"
#define	STR_ITEM_DAMAGED	        "该物品损坏了!"
#define	STR_CHANGE_NAME	            "您已经更名为%s。"
#define	STR_INCREASE_MONEY	        "[您的钱增加了。]"
#define	STR_INCREASE_ITEM	        "[您的物品增加了。]"
#define	STR_KICKOUTALL	            "开始处理kickoutall，服务器禁止登录，所有玩家退出中 . . ."	
#define	STR_ACTION_SEEN	            "可以显示ACTION了。"
#define	STR_ACTION_NOTSEEN	        "不显示ACTION了。"
#define	STR_NO_STOP	                "目标点不能落脚!"
#define	STR_LOCAL_TEST	            "注意：此命令只用于本地测试，否则可能导致服务器崩溃!"
#define	STR_ACTION_UPDATED	        "[ACTION 更新了。]"
#define	STR_KICK_OUT_GUILD	        "%s 已经被开除出帮会！"
#define	STR_NO_PRIZE	            "抱歉，没有奖品或者奖品 或 没有经过领奖网页确认。"
#define	STR_INVALID_CHARACTER	    "消息中包含非法字符!"
#define	STR_LOW_LEVEL	            "你的等级太低!"
#define	STR_GM_NO_TEAM	            "【GM】不能进行队伍操作。"
#define	STR_TEAMMATE_CANNOT_CREATE	"[队伍]您已经在队伍中了，不能创建新队伍。"
#define	STR_CREATE_TEAM_FAILED	    "[队伍]您创建队伍失败。"
#define	STR_INTEAM_NOJOIN		    "[队伍]您已经有队伍了。不能申请加入新队伍。"
#define	STR_NO_APPLICANT		    "[队伍]没有找到申请对象。"
#define	STR_NO_TEAM					"[队伍]您所申请的对象没有创建队伍。"
#define	STR_FORBIDDEN_JOIN	        "[队伍]对方队伍禁止加入了。"
#define	STR_TEAM_FULL			    "[队伍]您的所申请的队伍人数已满。"
#define	STR_NO_CAPTAIN_CLOSE	    "[队伍]申请对象不是队长，请向队长提出申请。"
#define	STR_JOIN_REQUEST_SENT	    "[队伍]已经发出加入队伍请求。"
#define	STR_INVI_SENT			    "[队伍]加入队伍申请已经提交，请等待回应。"
#define	STR_NO_TEAM_TO_INVITE	    "[队伍]您没有队伍，怎能接受别人加入队伍？"
#define	STR_NOT_CAPTAIN_INVITE	    "[队伍]您不是队长，怎能接受别人加入队伍？"
#define	STR_YOUR_TEAM_FULL		    "[队伍]您的队伍人数已满。"
#define	STR_APPLICANT_NOT_FOUND	    "[队伍]没有找到发出申请的玩家。"
#define	STR_HAVE_JOIN_TEAM	        "[队伍]您已经加入队伍了，不能同时加入另外一个。"
#define	STR_NOT_TO_JOIN	            "[队伍]对方没有发出加入申请，您不能接受对方。"
#define	STR_NOTEAM_TO_INVITE	    "[队伍]您没有队伍，怎能邀请别人加入队伍？"
#define	STR_TEAM_CLOSED	            "[队伍]您不允许其他人加入队伍，操作失败！"
#define	STR_NOT_CAPTAIN_ACCEPT	    "[队伍]您不是队长，怎能邀请别人加入队伍？"
#define	STR_INVITED_NOT_FOUND	    "[队伍]没有找到要邀请的玩家。"
#define	STR_HAS_IN_TEAM	            "[队伍]您所邀请的对象的已经有队伍了。"
#define STR_NOT_ALLOW_TEAM			"[队伍]对方不允许组队。"
#define	STR_INVITE_SENT				"[队伍]已经发出邀请加入队伍请求。"
#define	STR_SENT_WAIT				"[队伍]邀请已经发出，请等待。"
#define	STR_INTEAM_NOACCEPT			"[队伍]您已经有队伍了，不能接受邀请加入新队伍。"
#define	STR_INVITER_NOT_FOUND	    "[队伍]没有找到邀请者。"
#define	STR_NOT_CREATE_TEAM		    "[队伍]对方还没有组队。"
#define	STR_HIS_TEAM_FULL		    "[队伍]对方的队伍已经满员了。"
#define	STR_NOT_BE_INVIITED	  	    "[队伍]对方没有向您发出加入队伍的邀请，操作失败。"
#define	STR_NO_TEAM_TO_LEAVE	    "[队伍]您还不是队员，不能退出队伍。"
#define	STR_NO_TEAM_TO_DISMISS	    "[队伍]您还没有队伍，不能解散队伍。"
#define	STR_NOT_CAPTAIN_DISMISS	    "[队伍]您不是队长，不能解散队伍。"
#define STR_INVITED_IS_DEAD			"[队伍]不能邀请亡灵状态下玩家加入队伍。"
#define STR_APPLIED_LEADER_DEAD		"[队伍]不能加入亡灵的队伍。"
#define	STR_NO_TRADE_IN_BATTLE	    "错误：战斗中不能执行交易指令！"
#define	STR_NO_TRADE_IN_TEAM	    "错误：组队状态不能执行交易指令！"
#define STR_NOTALLOW_BUY			"对方不允许交易."
#define	STR_NO_IN_TEAM				"[队伍]您没有队伍。"	
#define	STR_NO_TRADE_TARGET	        "[交易]没有找到交易对象。"	
#define	STR_TARGET_TRADING	        "[交易]对方正在交易中，请稍后再试!"
#define	STR_TRADING_REQEST_SENT	    "[交易]已经发出交易请求。"
#define	STR_NOT_FOR_TRADE	        "错误：不能交易此物品!"
#define	STR_CANNOT_GO				"您不能走！"
#define	STR_FREE_PK	                "自由PK模式，你可以攻击任何人。"
#define	STR_PEACE	                "安全PK模式，你只能攻击怪物，不会伤害到其它任何玩家。"
#define	STR_TEAM_PK	                "组队PK模式，你可以攻击怪物和其它人，不会伤害到自己和队友。"
#define	STR_JOIN_A_GUILD	        "%s 加入了帮派。"
#define	STR_BONUS					"恭喜获得%u个奖品，请去交易市场领奖处领奖！"
#define	STR_TO_MAKE_FRIEND			"血与火的洗礼证明了坚固的友谊，%s对你报以信任的眼神，你是否愿意接受？"
#define	STR_MAKE_FRIEND				"%s、%s歃血为盟，宣誓从此将生死与共，永不背叛！"
#define	STR_BREAK_FRIEND			"%s 不耻 %s 的行径，从此断绝好友关系，两不相干。"
#define	STR_MARRY					"%s 和 %s 在神的面前立下永不分离的誓言，从此结为夫妻。"
#define	STR_DIVORCE					"%s 和 %s 感情破裂，宣布离婚！"
#define	STR_SYN_CONQUER				"【%s】经过激烈的嘶杀，终于赢得了战争的胜利"
#define	STR_POLICE_WANTED_ORDER		"揭榜确认：追捕目标%s，据传此人最近在%s一带出没。"
#define	STR_GOTO_JAIL				"%s 杀人如麻，终于失手被擒，打入大牢。"

#define STR_HEIGHT_LEV				"您的等级太高。"
#define STR_HEIGHT_LEV2				"对方等级太高。"
#define STR_LOW_LEV2				"对方等级太低，不允许向对方拜师。"

#define STR_MERCENARY_TASK_OK		"佣兵任务提交成功！"
#define STR_INVALID_MERCENARYTASK	"错误：非法佣兵任务！"
#define STR_PUBLISH_ONE_TASK_ONLY	"错误：一次只能发布一条任务！"
#define STR_DUPLICATE_TASK			"错误：一次只能接一个任务！"
#define STR_CANNOT_CANCEL_TASK		"错误：任务不能取消！"
#define STR_ACCEPT_TASK_OK			"接任务成功。"
#define STR_TAKE_PRIZE_OK			"成功领取奖品。"
#define STR_TASK_NOT_FINISHED_YET	"错误：任务还未完成。"
#define STR_CANCEL_TASK_OK			"任务成功取消。"
#define STR_CLOSE_TASK_OK			"任务成功结束。"
#define STR_TASK_FINISHED			"任务完成。"
#define STR_LOW_MERCENARY_RANK		"错误：佣兵等级太低。"
#define STR_TASK_TIMEOUT			"佣兵任务超时，已经自动取消。"
#define STR_DUPLICATE_ANNOUNCE      "一次只能发一个公告！"
#define STR_LOW_GRADE               "你的导师等级太低，不能发布公告。"
#define STR_ANNOUNCE_SUCCEED        "发布公告成功。"
#define STR_NO_ANNOUNCE             "你没有发布公告！"
#define STR_DELETE_ANNOUNCE         "成功删除公告"
#define STR_ILLEGAL_TASK_ITEM		"物品不符合任务要求！"
#define STR_NOANY_ANNOUNCE          "当前没有导师公告分布"
#define STR_CANNOT_ACCEPT_MYTASK	"错误：不能接自己的任务！"
#define STR_EUDEMON_LOW_LEVEL		"错误：幻兽等级不足%d级！"
#define STR_EUDEMON_CANNOT_EVOLVE	"错误：幻兽不能进化！"
#define STR_AVOID_DEATH				"自动使用 %s 宝石，免死一次。"
#define STR_AUTO_USE_SCAPEGOAT		"自动使用 %s 宝石，免受惩罚。"
#define STR_AUTO_USE_REBORN			"自动使用 %s 宝石，原地复活。"
#define STR_AUTO_USE_ANTISTEAL		"自动使用 %s 宝石，免受偷盗。"
#define STR_AVOID_STEAL				"依靠反偷盗宝石的帮助，你躲过了%s的偷窃。"
#define STR_STOLEN					"你被%s偷走了%s。"
#define STR_AUCTION_PACKAGE_FULL    "你的拍卖仓库已满，请先取出里面的物品，再加入拍卖物品"
#define STR_AUCTION_PACKAGE_FULL1   "你的拍卖仓库已满，不能参加竞拍。"
#define STR_AUCTION_LESS_MONEY      "你没有足够的金钱支付拍卖佣金。"
#define STR_AUCTION_SYS_BID         "现在是系统拍卖时间，玩家拍卖在系统拍卖结束后重新开始"
#define STR_AUCTION_BID_PACKAGE_FULL "仓库已满，请待有空位的时候再放入竞拍物品"
#define STR_NOT_SHOUT               "物品已经"
#define STR_SHOUT                   "您花了%d枚金币参与%s的竞拍。"
#define STR_AUCTION_JOIN_SUCCESS    "你的物品已经放入竞拍仓库等待拍卖。在队列中的位置为%d"
#define STR_AUCTION_JOIN_ERROR      "放入物品错误"
#define STR_AUCTION_CHECK_ERROR     "查看物品错误"
#define STR_SHOUT_PRICE_SELF_ERR    "自己的物品不能参加拍卖"
#define STR_AUCTION_NOT_ITEM        "当前没有物品拍卖"
#define STR_AUCTION_MIN_VALUE       "拍卖物品的底价不能少于%d枚金币。"
#define STR_SPECIAL_GOODS_JOIN_ERR  "物品不能拍卖"		//"特殊物品不能拍卖"
#define STR_AUCTION_SHOUTPRICE_LOW  "你出的价必须高于现在的最低出价！！"
#define STR_AUCTION_BIDED           "您竞拍的物品已流拍或被人买走。"
#define STR_AUCTION_BID_ERROR       "系统拍卖出错"
#define STR_AUCTION_BID_FAIL        "拍卖物品失败，物品已放入拍卖仓库"
#define STR_AUCTION_BID             "%s，%s开价%d枚金币，第%d次，还有没有人开价?"
#define STR_AUCTION_BID_SUCCESS     "你的物品已经拍卖出去，获得金钱:%d"
#define STR_AUCTION_SYS_JOIN_MORETIMES  "在同一时间里开始多次系统拍卖"
#define STR_AUCTION_HAMMER          "恭喜 %s 以 %d 枚金币买到 %s。"
#define STR_AUCTION_NEW             "本轮拍卖物品为%s的%s，底价为%d枚金币，现在开始竞拍。"
#define STR_AUCTION_SYS_ITEM_INVALID "系统拍卖[%u]中发现非法的itemtype值[%u]"
#define STR_EUDEMON_DEAD			"错误：幻兽已死亡。"
#define STR_TOOMUCH_MONEY_SAVED		"仓库钱太多了，不可以再存。"
#define STR_TOOMUCH_MONEY			"您身上钱太多了，不可以再拾取。"
#define STR_TOOMUCH_MONEY_TO_DRAW	"您身上钱太多了，不可以再取。"
#define STR_NOT_ENOUGH_POTENTIAL	"您的潜能值不足，无法使用结界。"
#define STR_BOOTH_FULL				"您的摊位已满，不能再放置更多物品。"
#define STR_DROP_MONEY_SUCC			"您丢弃了%d金币。"
#define STR_DIE_DROP_MONEY			"你遗失了%d枚金币。"
#define STR_TEAM_MAGIC				"%s 发动。"
#define STR_TEAM_MAGIC2				"%s 发动，效果增加%d%%。"
#define STR_TEAM_STATUS_POWER_INC	"结界效果增加%d%%。"
#define STR_TEAM_STATUS_POWER_DEC	"结界效果降低%d%%。"
#define STR_TEAM_STATUS_DISAPPEAR	"结界效果消失。"
#define STR_INCPK_REDNAME_PUNISH	"PK值继续增加，将会受到红名的惩罚。"
#define STR_INCPK_BLACKNAME_PUNISH	"PK值继续增加，将会受到黑名的惩罚。"
#define STR_INCPK_BLACKNAME_PUNISH2	"PK值继续增加，将会延长黑名惩罚的时间。"
#define STR_NOT_FOR_TASK_PRIZE		"错误：不能作为佣兵任务奖励物品。"
#define STR_EUDEMON_OVERLEVEL		"幻兽等级太高，您暂时无法召唤。"
#define STR_MAX_EUDEMONAMOUNT		"您最多只能同时召唤 %d 只幻兽。"
#define STR_EUDEMON_CHGNAME_OK		"幻兽改名操作成功。您将幻兽 %s 赋予了新名字 %s。"

#define STR_SYNWAR_ANNOUNCE			"%d-%d-%d 20:00:00 开始攻打帮派 %s。"
#define STR_SYNWAR_ANNOUNCE2		"%d-%d-%d 20:00:00 %s 帮派开始攻打本帮派。"

#define STR_EUDEMON_LEARNMAGIC_ERR_LEVEL	"阁下的幻兽等级太低，不足以学习此技能。"
#define STR_EUDEMON_LEARNMAGIC_ERR_TYPE		"阁下的幻兽不能学习此类型技能。"
#define STR_EUDEMON_LEARNMAGIC_ERR_DEAD		"阁下的幻兽已经死亡，无法学习。"
#define STR_EUDEMON_LEARNMAGIC_ERR_AGAIN	"阁下的幻兽已经学过此技能了。"

#define STR_EUDEMON_HATCH_SUCCESSFUL "幻兽孵化成功"
#define STR_EUDEMON_NOTALLOW_ACTIVE	"幻兽处于不可出征状态"
#define STR_EUDEMON_CANNOT_ACTIVE	"你暂时还没有驾驭这只幻兽的能力"
// 进化部分
#define STR_EVOING_CANNOT_CHEKOUT	"你的幻兽正在进化中，无法取出。"
#define STR_EVO_HIGHEST_NEEDNOT		"你的幻兽目前已是最高级形态，不需要再进行进化。"
#define STR_CANNOT_EVO_SECOND		"你的幻兽的资质不够，无法进行2次进化"
#define STR_EVO_QUEUE_FULL			"对不起，现在排队幻兽已满，请稍候再来"


//cn_ddres.h 删除部分
#define	STR_WEAPON_SKILL_UPLEV		"恭喜阁下武器熟练度又升一级。"
#define DRAGON_BALL_DROP			"宝光一闪，%s从怪物身上打出一个龙珠。"
#define	STR_SUPERMAN_BROADCAST_sddd	"%s 武艺精湛，在爆发时间内杀死%d只怪物，荣登KO排行榜的第%d名，奖励KO时间%d秒。"
#define	STR_DISPATCHXP_s			"%s 一声怒吼，同队的战友个个精神一震，XP值上升！"
#define	STR_NO_ENOUGH_POWER			"阁下的内力不足，不能千里传音!"
#define	STR_NO_ENOUGH_LEVEL			"阁下的修行太低，不能千里传音!"
#define	STR_CAN_NOT_TALK			"您被点穴了，无法说话!"
#define	STR_DIE_FORGIVE	            "人死如灯灭，何苦纠缠不休？"
#define	STR_DIE_STOP_ATTACK	        "死者为大，禁止鞭尸。"
#define	STR_NO_MANA_UNLOCK		    "内力不足，不能冲穴!"
#define	STR_NO_CULTIVATION		    "阁下修为太浅，冲穴失败!"
#define	STR_NO_PK_VILLAGE	        "新手村禁止PK！"
#define	STR_VITAL_POINT_STRICKEN	"您被点穴了，无法说话!"
#define	STR_NO_LV_BROADCAST	        "阁下的修行太低，不能千里传音!"
#define	STR_NO_MANA_BROADCAST	    "阁下的内力不足，不能千里传音!"
//---------------------------------------------------------------------------

#define	STR_ITEM_EXCLUSIVE			"您已经有一个'%s'了,此物品只能有一个!"
#endif