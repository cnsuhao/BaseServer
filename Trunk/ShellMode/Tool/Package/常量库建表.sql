-- 自动加载配置表
CREATE TABLE `auto_reload` (
	`table_name` VARCHAR(255) NOT NULL DEFAULT '' COMMENT '表名',
	`server_group` INT(10) UNSIGNED NOT NULL DEFAULT '0' COMMENT '服务器组号, 填0表示全部',
	`server_line` INT(10) UNSIGNED NOT NULL DEFAULT '0' COMMENT '服务器线路号, 填0表示全部',
	`utc_time` INT(10) UNSIGNED NOT NULL DEFAULT '0' COMMENT '指定时间, 填0表示即时',
	UNIQUE INDEX `table_name_group` (`table_name`, `server_group`),
	INDEX `group` (`server_group`)
)
COMMENT='自动加载配置表\r\n通过点击关系服按钮触发'
COLLATE='utf8_general_ci'
ENGINE=InnoDB;