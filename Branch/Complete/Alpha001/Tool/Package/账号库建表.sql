-- �˺ſ�
CREATE TABLE `account` (
	`id` BIGINT(8) UNSIGNED NOT NULL AUTO_INCREMENT COMMENT '�˺�id,��10w��',
	`name` VARCHAR(64) NOT NULL DEFAULT '' COMMENT '�˺���',
	`password` VARCHAR(64) NOT NULL DEFAULT '' COMMENT '�˺�����',
	`reg_time` INT(4) UNSIGNED NOT NULL DEFAULT '0' COMMENT 'ע��utcʱ��',
	`type` INT(4) UNSIGNED NOT NULL DEFAULT '0' COMMENT '�˺�����(0��ͨ, 1GM��2�ο�)',
	`state` INT(4) UNSIGNED NOT NULL DEFAULT '0' COMMENT '�˺�״̬(0������1��ʱ�⣬2���÷�)',
	`state_param` INT(4) UNSIGNED NOT NULL DEFAULT '0' COMMENT '��ʱ�����ʱ��',
	`platform` VARCHAR(32) NOT NULL DEFAULT '' COMMENT 'ƽ̨',
	`channel` VARCHAR(32) NOT NULL DEFAULT '' COMMENT '����',
	`os` VARCHAR(32) NOT NULL DEFAULT '' COMMENT '����ϵͳ',
	PRIMARY KEY (`id`)
)
COMMENT='�˺ű�'
COLLATE='utf8_general_ci'
ENGINE=InnoDB
AUTO_INCREMENT=100000;

-- �˺ű����
INSERT INTO `account` (`id`, `name`, `password`, `reg_time`, `type`) VALUES (100000, 'PM', '1', 1414566000, 1);