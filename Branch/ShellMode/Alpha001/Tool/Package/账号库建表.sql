-- �˺ſ�
CREATE TABLE `account` (
	`id` INT(4) UNSIGNED NOT NULL AUTO_INCREMENT COMMENT '�˺�id, ��10W��ʼ',
	`name` VARCHAR(64) NOT NULL DEFAULT '' COMMENT '�˺���',
	`password` VARCHAR(128) NOT NULL DEFAULT '' COMMENT '�˺�����',
	`reg_time` INT(4) UNSIGNED NOT NULL DEFAULT '0' COMMENT 'ע��utcʱ��',
	`account_type` INT(4) UNSIGNED NOT NULL DEFAULT '0' COMMENT '�˺�����, 0��ͨ, 1GM',
	`account_status` INT(4) UNSIGNED NOT NULL DEFAULT '0' COMMENT '�˺�״̬, 0����, 1��ʱ��ͣ, 2���÷�ͣ',
	`account_status_param` INT(4) UNSIGNED NOT NULL DEFAULT '0' COMMENT '�˺�״̬�������, ��ʱ��ͣ����utcʱ��',
	`platform` VARCHAR(32) NOT NULL DEFAULT '' COMMENT 'ƽ̨',
	`channel` VARCHAR(32) NOT NULL DEFAULT '' COMMENT '����',
	`os` VARCHAR(32) NOT NULL DEFAULT '' COMMENT 'ϵͳ',
	`bind_invite_code` VARCHAR(32) NOT NULL DEFAULT '' COMMENT '��������',
	PRIMARY KEY (`id`),
	UNIQUE INDEX `name` (`name`),
	INDEX `platform` (`platform`),
	INDEX `reg_time` (`reg_time`)
)
COMMENT='�˺ű�'
COLLATE='utf8_general_ci'
ENGINE=InnoDB
AUTO_INCREMENT=100000;

-- �˺ű����
INSERT INTO `account` (`id`, `name`, `password`, `reg_time`, `account_type`) VALUES (100000, 'PM', '1', 1414566000, 1);