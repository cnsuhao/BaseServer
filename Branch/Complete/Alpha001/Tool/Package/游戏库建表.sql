-- 游戏库
-- 角色表建表
CREATE TABLE `user` (
	`id` BIGINT(8) UNSIGNED NOT NULL AUTO_INCREMENT COMMENT '角色id, 1000W起',
	`name` VARCHAR(32) NOT NULL DEFAULT '' COMMENT '角色名',
	`account_id` INT(4) UNSIGNED NOT NULL DEFAULT '0' COMMENT '账号id',
	`account_type` INT(4) UNSIGNED NOT NULL DEFAULT '0' COMMENT '账号类型, 账号表覆盖',
	`create_time` INT(4) UNSIGNED NOT NULL DEFAULT '0' COMMENT '创建时间(utc时间)',
	`login_time` INT(4) UNSIGNED NOT NULL DEFAULT '0' COMMENT '登陆日期(YYYYMMDD)',
	`exit_time` INT(4) UNSIGNED NOT NULL DEFAULT '0' COMMENT '退出时间(utc时间)',
	`all_online_time` INT(4) UNSIGNED NOT NULL DEFAULT '0' COMMENT '总在线时间(单位秒)',
	`del_flag` INT(4) UNSIGNED NOT NULL DEFAULT '0' COMMENT '待删除标记',
	`server_group` INT(4) UNSIGNED NOT NULL DEFAULT '0' COMMENT '归属服务器组',
	`lev` INT(4) UNSIGNED NOT NULL DEFAULT '0' COMMENT '等级',
	`exp` BIGINT(8) UNSIGNED NOT NULL DEFAULT '0' COMMENT '经验',
	`camp` INT(4) UNSIGNED NOT NULL DEFAULT '0' COMMENT '阵营',
	`flagship` INT(4) UNSIGNED NOT NULL DEFAULT '0' COMMENT '旗舰',
	`score` INT(4) UNSIGNED NOT NULL DEFAULT '0' COMMENT '战斗力',
	`record_galaxy` INT(4) UNSIGNED NOT NULL DEFAULT '0' COMMENT '记录星系',
	`record_x` INT(4) UNSIGNED NOT NULL DEFAULT '0' COMMENT '记录坐标X',
	`record_y` INT(4) UNSIGNED NOT NULL DEFAULT '0' COMMENT '记录坐标Y',
	`record_rest` INT(4) UNSIGNED NOT NULL DEFAULT '0' COMMENT '记录落脚点NPC',
	`stoptalk_endtime` INT(4) UNSIGNED NOT NULL DEFAULT '0' COMMENT '禁言结束时间',
	PRIMARY KEY (`id`),
	INDEX `account_id` (`account_id`)
)
COMMENT='玩家表'
COLLATE='utf8_general_ci'
ENGINE=InnoDB
AUTO_INCREMENT=10000000;