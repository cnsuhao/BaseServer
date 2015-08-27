////////////////////////////////////////////////////////////////////////
// Import : �����ļ����������塣
// Moudle : define.h 
// Author : �½���(Chen Jianjun)
// Create : 2015-6-19
// Warning��*�ַ�������ͳһʹ��static const char*����, ֻ����Ҫ���ַ������鸳��ֵ�Ĳ��ú�
////////////////////////////////////////////////////////////////////////

#ifndef _MAPGROUP_SHARE_CONST_DEF_H_
#define _MAPGROUP_SHARE_CONST_DEF_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "./EnumDef.h"

// ����������
#ifdef MYDEBUG
static const char* GAMESERVER_TITLE = "GameServer:[%s] Group:[%d] Line:[%d] PID:[%u] SVN:[%d] Debug";
#else
static const char* GAMESERVER_TITLE = "GameServer:[%s] Group:[%d] Line:[%d] PID:[%u] SVN:[%d] Release";
#endif

// �����������ļ�
static const char* GAMESERVER_FILENAME = "GameServer.ini";	

// �Ի�����Ϣ����
const int	WINDOW_TEXT_SIZE = 9;
//////////////////////////////////////////////////////////////////////

// ���Ʊ���
const int	CLOSETHREAD_MILLISECS					= 30000;			// �ȴ��̹߳رյĺ�����

//////////////////////////////////////////////////////////////////////
const int	THREADDELAY_MS							= 400;				// �ȴ��ڲ���Ϣ�����ʱ��
const int	SOCKETKERNEL_ONTIMER_MS					= 1000;				// �����̵߳�ONTIMERƵ��
const int	LOGINKERNEL_ONTIMER_MS					= 333;				// ��½�̵߳�ONTIMERƵ��
const int	GAMEKERNEL_ONTIMER_MS					= 1000;				// ��Ϸ�̵߳�ONTIMERƵ��
const int	RELATIONKERNEL_ONTIMER_MS				= 1000;				// ��ϵ�̵߳�ONTIMERƵ��
const int	AIKERNEL_ONTIMER_MS						= 1000;				// AI  �̵߳�ONTIMERƵ��

const int	ONTIMER_MS_ROLLBACK_MS					= 5000;				// ���������ع���ֵ


const int	LOG_TIMEOUT_SOCKET_PROCESS				= 100;				// �����߳�ontimer��־��ʱʱ��
const int	LOG_TIMEOUT_LOGIN_PROCESS				= 100;				// ��½�߳�ontimer��־��ʱʱ��
const int	LOG_TIMEOUT_GAME_PROCESS				= 100;				// ��Ϸ�߳�ontimer��־��ʱʱ��
const int	LOG_TIMEOUT_RELATION_PROCESS			= 100;				// ��ϵ�߳�ontimer��־��ʱʱ��
const int	LOG_TIMEOUT_AI_PROCESS					= 100;				// AI�߳�  ontimer��־��ʱʱ��

const int	ONTIMER_LOGIN_THREAD_ONLINE_STAT		= 5;				// ��½�߳� ����ͳ�� ���
const int	PER_ONTIMER_LOGIN_ENTER_COUNT			= 8;				// ��½�߳� ÿ���������8����½����
const int	ONTIMER_LOGIN_THREAD_KICK_DEAD			= 3600;				// ��½�߳� �߳���ʱ ���
const int	TIMEOUT_LOGIN_THREAD_KICK_DEAD			= 36000;			// ��½�߳� ��ҳ�ʱ�루10���ӣ�

static const char* SYSTEM_NAME 						= "SYSTEM";			// �㲥��Ϣʱ����ϵͳ�������ִ�
const int	DBSTR_SIZE								= 256;				// ���ݿ�INI������

//////////////////////////////////////////////////////////////////////
// ���ĳ���
const OBJID PLAYER_ID_FIRST							= 10000000;			// Player�ĵ�һ��ID, 1000W��
const OBJID MAX_ID_DEFINE							= (OBJID)-1;

const int	LOGIN_USER_LIST_LIMIT					= 5;				// ���ɫϵͳ��ɫ����

static const char* LUA_FILE_PATH					= "script/";
static const char* LUA_LIST_FILE					= "lualist.txt";
static const char* LUA_ERROR_KEY					= "LuaErrorKey";
const int LUA_CUSTOM_ERROR							= 99999;			// �Զ����lua���󷵻�ֵ

const int MONEY_STORE_THRESHOLD						= 999999;			// ����Ĭ����ֵⷧ
const int SYN_LOG_MAX_COUNT							= 300;				// ������־�������
const int SYN_LOG_MAX_PAGE_SIZE						= 15;				// ������־һҳ���������

#endif // end of _MAPGROUP_SHARE_CONST_DEF_H_
