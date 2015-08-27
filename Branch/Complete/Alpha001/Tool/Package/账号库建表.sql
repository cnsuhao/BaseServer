-- 账号库
CREATE TABLE `account` (
	`id` BIGINT(8) UNSIGNED NOT NULL AUTO_INCREMENT COMMENT '账号id,从10w起',
	`name` VARCHAR(64) NOT NULL DEFAULT '' COMMENT '账号名',
	`password` VARCHAR(64) NOT NULL DEFAULT '' COMMENT '账号密码',
	`reg_time` INT(4) UNSIGNED NOT NULL DEFAULT '0' COMMENT '注册utc时间',
	`type` INT(4) UNSIGNED NOT NULL DEFAULT '0' COMMENT '账号类型(0普通, 1GM，2游客)',
	`state` INT(4) UNSIGNED NOT NULL DEFAULT '0' COMMENT '账号状态(0正常，1临时封，2永久封)',
	`state_param` INT(4) UNSIGNED NOT NULL DEFAULT '0' COMMENT '临时封结束时间',
	`platform` VARCHAR(32) NOT NULL DEFAULT '' COMMENT '平台',
	`channel` VARCHAR(32) NOT NULL DEFAULT '' COMMENT '渠道',
	`os` VARCHAR(32) NOT NULL DEFAULT '' COMMENT '操作系统',
	PRIMARY KEY (`id`)
)
COMMENT='账号表'
COLLATE='utf8_general_ci'
ENGINE=InnoDB
AUTO_INCREMENT=100000;

-- 账号表基础
INSERT INTO `account` (`id`, `name`, `password`, `reg_time`, `type`) VALUES (100000, 'PM', '1', 1414566000, 1);