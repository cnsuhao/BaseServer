-- ��Ϸ��
-- ��ɫ����
CREATE TABLE `user` (
	`id` BIGINT(8) UNSIGNED NOT NULL AUTO_INCREMENT COMMENT '��ɫid, 1000W��',
	`name` VARCHAR(32) NOT NULL DEFAULT '' COMMENT '��ɫ��',
	`account_id` INT(4) UNSIGNED NOT NULL DEFAULT '0' COMMENT '�˺�id',
	`account_type` INT(4) UNSIGNED NOT NULL DEFAULT '0' COMMENT '�˺�����, �˺ű���',
	`create_time` INT(4) UNSIGNED NOT NULL DEFAULT '0' COMMENT '����ʱ��(utcʱ��)',
	`login_time` INT(4) UNSIGNED NOT NULL DEFAULT '0' COMMENT '��½����(YYYYMMDD)',
	`exit_time` INT(4) UNSIGNED NOT NULL DEFAULT '0' COMMENT '�˳�ʱ��(utcʱ��)',
	`all_online_time` INT(4) UNSIGNED NOT NULL DEFAULT '0' COMMENT '������ʱ��(��λ��)',
	`del_flag` INT(4) UNSIGNED NOT NULL DEFAULT '0' COMMENT '��ɾ�����',
	`server_group` INT(4) UNSIGNED NOT NULL DEFAULT '0' COMMENT '������������',
	`lev` INT(4) UNSIGNED NOT NULL DEFAULT '0' COMMENT '�ȼ�',
	`exp` BIGINT(8) UNSIGNED NOT NULL DEFAULT '0' COMMENT '����',
	`camp` INT(4) UNSIGNED NOT NULL DEFAULT '0' COMMENT '��Ӫ',
	`flagship` INT(4) UNSIGNED NOT NULL DEFAULT '0' COMMENT '�콢',
	`score` INT(4) UNSIGNED NOT NULL DEFAULT '0' COMMENT 'ս����',
	`record_galaxy` INT(4) UNSIGNED NOT NULL DEFAULT '0' COMMENT '��¼��ϵ',
	`record_x` INT(4) UNSIGNED NOT NULL DEFAULT '0' COMMENT '��¼����X',
	`record_y` INT(4) UNSIGNED NOT NULL DEFAULT '0' COMMENT '��¼����Y',
	`record_rest` INT(4) UNSIGNED NOT NULL DEFAULT '0' COMMENT '��¼��ŵ�NPC',
	`stoptalk_endtime` INT(4) UNSIGNED NOT NULL DEFAULT '0' COMMENT '���Խ���ʱ��',
	PRIMARY KEY (`id`),
	INDEX `account_id` (`account_id`)
)
COMMENT='��ұ�'
COLLATE='utf8_general_ci'
ENGINE=InnoDB
AUTO_INCREMENT=10000000;