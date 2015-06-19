////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2012, WuHan ChuangYou, All Rights Reserved
// Moudle: ConstDef.h
// Author: ������(Peng Wenqi)
// Created: 2012-10-30
// 
// !!! ע�� !!!
//	1. ���ļ����ڶ�����Ϸ������ȫ�ֳ���
//  2. �ַ�������ͳһʹ��static const char*����, ֻ����Ҫ���ַ������鸳��ֵ�Ĳ��ú�
//////////////////////////////////////////////////////////////////////////
#ifndef _MAPGROUP_SHARE_CONST_DEF_H_
#define _MAPGROUP_SHARE_CONST_DEF_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../../common/common.h"
#include "./EnumDef.h"

static const char* GAMESERVER_TITLE = "[%u] GameServer Name[%s] Line[%d] Group[%d] SVN:[%d]";	// ����������

//////////////////////////////////////////////////////////////////////
// ���泣��
const int	TEXTWINDOW_SIZE		= 15;			// ��Ϣ������

//////////////////////////////////////////////////////////////////////
// ���Ʊ���
const int	THREADDELAY_MS							= 400;		// �ȴ��ڲ���Ϣ�����ʱ��
const int	SOCKETKERNEL_ONTIMER_MS					= 1000;		// �����̵߳�ONTIMERƵ��
const int	LOGINKERNEL_ONTIMER_MS					= 333;		// ��½�̵߳�ONTIMERƵ��
const int	GAMEKERNEL_ONTIMER_MS					= 1000;		// ��Ϸ�̵߳�ONTIMERƵ��
const int	RELATIONKERNEL_ONTIMER_MS				= 1000;		// ��ϵ�̵߳�ONTIMERƵ��
const int	AIKERNEL_ONTIMER_MS						= 1000;		// AI  �̵߳�ONTIMERƵ��

const int	ONTIMER_MS_ROLLBACK_MS					= 5000;		// ���������ع���ֵ
const int	CLOSETHREAD_MILLISECS					= 30000;	// �ȴ��̹߳رյĺ�����

const int	LOG_TIMEOUT_SOCKET_PROCESS				= 100;		// �����߳�ontimer��־��ʱʱ��
const int	LOG_TIMEOUT_LOGIN_PROCESS				= 100;		// ��½�߳�ontimer��־��ʱʱ��
const int	LOG_TIMEOUT_GAME_PROCESS				= 100;		// ��Ϸ�߳�ontimer��־��ʱʱ��
const int	LOG_TIMEOUT_RELATION_PROCESS			= 100;		// ��ϵ�߳�ontimer��־��ʱʱ��
const int	LOG_TIMEOUT_AI_PROCESS					= 100;		// AI�߳�  ontimer��־��ʱʱ��

const int	ONTIMER_LOGIN_THREAD_ONLINE_STAT		= 5;		// ��½�߳� ����ͳ�� ���
const int	ONTIMER_LOGIN_THREAD_KICK_DEAD			= 17;		// ��½�߳� �߳����� ���
const int	PER_ONTIMER_LOGIN_ENTER_COUNT			= 8;		// ��½�߳� ÿ���������8����½����
const int	TIMEOUT_LOGIN_THREAD_KICK_DEAD			= 600;		// ��½�߳� ��ҳ�ʱ��

static const char* SYSTEM_NAME 			= "SYSTEM";			// �㲥��Ϣʱ����ϵͳ�������ִ�
static const char* CONFIG_FILENAME		= "GameServer.ini";	
const int	DBSTR_SIZE				= 256;				// ���ݿ�INI������

const int	REBUILDLISTENDELAYSEC = 60;
const int	IPSTRSIZE = 16;
const int	RECVREPEATTIMES = 3;


//////////////////////////////////////////////////////////////////////
// ���ĳ���
const OBJID PLAYER_ID_FIRST		= 10000000;			// Player�ĵ�һ��ID, 1000W��
const OBJID MAX_ID_DEFINE		= (OBJID)-1;

const int	LOGIN_USER_LIST_LIMIT = 5;			// ���ɫϵͳ��ɫ����

const int	MAX_DROP_NUM			= 8;	// һ�ε��������������
const int	BATTLE_MAX_ROUND		= 3;	// ս������ִ�
const int	BATTLE_MAX_FIGHTER		= 5;	// ս������Ա��

const int BATTLE_ATK_CAMP = 100;	// ս�� ������
const int BATTLE_DEF_CAMP = 200;	// ս�� ������
const int BATTLE_ROUND_BASE = 10;	// ս���ִλ�׼

const int BATTLE_FORCE_END_DELAY_SECOND = 60 * 60;	// ս��ǿ�ƽ����ȴ�ʱ��
const int BATTLE_CHECK_ERROR_DATA = 1;				// ս�����������ֵ

static const char* LUA_FILE_PATH	= "script/";
static const char* LUA_LIST_FILE	= "lualist.txt";
static const char* LUA_ERROR_KEY	= "LuaErrorKey";
const int LUA_CUSTOM_ERROR			= 99999;			// �Զ����lua���󷵻�ֵ

const int MONEY_STORE_THRESHOLD = 999999;	// ����Ĭ����ֵⷧ
const int SYN_LOG_MAX_COUNT		= 300;		// ������־�������
const int SYN_LOG_MAX_PAGE_SIZE = 15;		// ������־һҳ���������

////////////////////////////////////////////////////////////////////////////////////////////////
// ����ID�ζ��壬10000��ǰ��ʾ��λ���룬10000�Ժ��ʾ��������
const int CONST_BIT_MASKID_INTERVAL			= 5000;			// ��λ����ID����	������ʹ�ö�(1 - 5000)		�߻�ʹ�ö�(5000 - 10000)
const int CONST_COMPUTATION_MASKID_BEGIN	= 10000;		// ��������ID��ʼ
const int CONST_COMPUTATION_MASKID_INTERVAL	= 20000;		// ��������ID����	������ʹ�ö�(10000 - 20000���߻�ʹ�ö�(20000�Ժ�)
const int CONST_DEFULT_MASK_ENDTIME			= 2000000000;	// ����Ĭ�Ͻ���ʱ��(2033��5��18�� 11:33:20)

//////////////////////////////////////////////////////////////////////////
const int MAX_PAY_CONFIG_ID = 30;		// ���ó�ֵ���id
const int SERVER_PAY_CONFIG_ID = 999;	// �ڲ���ֵ����id

const int CONST_MAX_WARROAD_RECORD_NUM	= 5;				// ս�ۼ�¼�������
const int CONST_MAX_WARROAD_STAR		= 3;				// ս������Ǽ�
const int CONST_MAX_WARROAD_AWARD_APPLY_NUM		= 1;		// �Ŷ�ս��ս��Ʒ���������
const int CONST_MAX_WARROAD_AWARD_HISTORY_NUM	= 40;		// �Ŷ�ս��ս��Ʒ��ʷ��¼��Ŀ
const int CONST_MAX_WARROAD_SERVER_DPS_NUM		= 10;		// �Ŷ�ս���½�ȫ������������

const int CONST_WARROAD_ERROR			= 99999;			// ս�۴�����

// ��������
const int INVITE_CODE_MAX_LEN			= 12;				// ���������󳤶�
const int INVITE_VAS_BASE				= 100;				// ����ȡ����СԪ������
const int LOGIN_AWARD_MAX_POWER			= 100;				// ������ȡ������ֵ

//////////////////////////////////////////////////////////////////////////
// ����������
const int ARENA_MAX_TARGET_COUNT		= 3;				// �����������ָ���

//////////////////////////////////////////////////////////////////////////
// �������ս
const int TERRITORY_MAX_MONSTER_TROOPS_ID			= 1000;				// Ĭ�Ϸ��ز�����󲿶ӷ���
const int TERRITORY_BATTLE_TYPE						= 55555;			// ����սս��type

const int VIP_VALUE_UP_LIMIT						= 9999;				// VIPֵ����

//////////////////////////////////////////////////////////////////////////
const int MAX_ITEM_HINT_TEXT						= 256;				// ��Ʒ��ʾ�����ַ���
const int MAX_ITEM_HINT_COUNT						= 50;				// ��Ʒ��ʾ��Ϣ�������

const int CONST_BUFF_DEFAULT_KEEP_TIME				= 999999;			// buffĬ�ϳ���ʱ��(����)
const int CONST_SYN_BUFF_VALID_TIME					= 24 * 60 * 60;		// ����buff �ṩ��������С���ʱ��

#endif // end of _MAPGROUP_SHARE_CONST_DEF_H_
