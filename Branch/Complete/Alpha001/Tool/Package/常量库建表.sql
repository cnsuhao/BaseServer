-- �ɴ����ͱ�
CREATE TABLE `ship_type` (
	`type` INT(4) UNSIGNED NOT NULL DEFAULT '0' COMMENT '����',
	`name` VARCHAR(32) NOT NULL DEFAULT '' COMMENT '����',
	`camp` INT(4) UNSIGNED NOT NULL DEFAULT '0' COMMENT '��Ӫ',
	`init_life` INT(4) UNSIGNED NOT NULL DEFAULT '0' COMMENT '��ʼѪ��',
	`init_def` INT(4) UNSIGNED NOT NULL DEFAULT '0' COMMENT '��ʼ����',
	`init_atk` INT(4) UNSIGNED NOT NULL DEFAULT '0' COMMENT '��ʼ�˺�',
	`init_star` INT(4) UNSIGNED NOT NULL DEFAULT '0' COMMENT '��ʼ�Ǽ�',
	`init_speed` INT(4) UNSIGNED NOT NULL DEFAULT '0' COMMENT '��ʼ�ٶ�',
	`equip_count` INT(4) UNSIGNED NOT NULL DEFAULT '0' COMMENT 'װ��������',
	`skill_auto1` INT(4) UNSIGNED NOT NULL DEFAULT '0' COMMENT '�Զ�����1',
	`skill_auto2` INT(4) UNSIGNED NOT NULL DEFAULT '0' COMMENT '�Զ�����2',
	`skill_auto3` INT(4) UNSIGNED NOT NULL DEFAULT '0' COMMENT '�Զ�����3',
	`skill_sp` INT(4) UNSIGNED NOT NULL DEFAULT '0' COMMENT '�ؼ�',
	PRIMARY KEY (`type`)
)
COMMENT='�ɴ����ͱ�'
COLLATE='utf8_general_ci'
ENGINE=InnoDB;