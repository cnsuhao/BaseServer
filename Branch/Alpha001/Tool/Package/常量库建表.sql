-- �Զ��������ñ�
CREATE TABLE `auto_reload` (
	`table_name` VARCHAR(255) NOT NULL DEFAULT '' COMMENT '����',
	`server_group` INT(10) UNSIGNED NOT NULL DEFAULT '0' COMMENT '���������, ��0��ʾȫ��',
	`server_line` INT(10) UNSIGNED NOT NULL DEFAULT '0' COMMENT '��������·��, ��0��ʾȫ��',
	`utc_time` INT(10) UNSIGNED NOT NULL DEFAULT '0' COMMENT 'ָ��ʱ��, ��0��ʾ��ʱ',
	UNIQUE INDEX `table_name_group` (`table_name`, `server_group`),
	INDEX `group` (`server_group`)
)
COMMENT='�Զ��������ñ�\r\nͨ�������ϵ����ť����'
COLLATE='utf8_general_ci'
ENGINE=InnoDB;