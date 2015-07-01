-- 账号库
CREATE TABLE `account` (
	`id` INT(4) UNSIGNED NOT NULL AUTO_INCREMENT COMMENT '账号id, 从10W开始',
	`name` VARCHAR(64) NOT NULL DEFAULT '' COMMENT '账号名',
	`password` VARCHAR(128) NOT NULL DEFAULT '' COMMENT '账号密码',
	`reg_time` INT(4) UNSIGNED NOT NULL DEFAULT '0' COMMENT '注册utc时间',
	`account_type` INT(4) UNSIGNED NOT NULL DEFAULT '0' COMMENT '账号类型, 0普通, 1GM',
	`account_status` INT(4) UNSIGNED NOT NULL DEFAULT '0' COMMENT '账号状态, 0正常, 1临时封停, 2永久封停',
	`account_status_param` INT(4) UNSIGNED NOT NULL DEFAULT '0' COMMENT '账号状态补充参数, 临时封停结束utc时间',
	`platform` VARCHAR(32) NOT NULL DEFAULT '' COMMENT '平台',
	`channel` VARCHAR(32) NOT NULL DEFAULT '' COMMENT '渠道',
	`os` VARCHAR(32) NOT NULL DEFAULT '' COMMENT '系统',
	`bind_invite_code` VARCHAR(32) NOT NULL DEFAULT '' COMMENT '绑定邀请码',
	PRIMARY KEY (`id`),
	UNIQUE INDEX `name` (`name`),
	INDEX `platform` (`platform`),
	INDEX `reg_time` (`reg_time`)
)
COMMENT='账号表'
COLLATE='utf8_general_ci'
ENGINE=InnoDB
AUTO_INCREMENT=100000;

-- 账号表基础
INSERT INTO `account` (`id`, `name`, `password`, `reg_time`, `account_type`) VALUES (100000, 'PM', '1', 1414566000, 1);