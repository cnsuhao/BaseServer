//////////////////////////////////////////////////////////////////////////
// Moudle:	 GlobalConstDef.h
// Describe: ȫ�᳣ֽ������
// Author:	 �½���(Chen Jianjun)
// Created:	 2015-02-28
//////////////////////////////////////////////////////////////////////////
#ifndef _GLOBAL_CONST_DEF_H
#define _GLOBAL_CONST_DEF_H

// ===========================SOCKET�������============================
const int		CONST_IOHANDLE_MAX_NUM				= 1;					// IO�������

#ifdef _DEBUG
const int		CONST_ACCEPT_SESSION_MAX_NUM		= 200;					// ���ܻػ��������������ģʽ��
#else
const int		CONST_ACCEPT_SESSION_MAX_NUM		= 5000;					// ���ܻػ��������
#endif

const int		CONST_IOCP_SOCKET_BUFFER_SIZE		= 1024 * 32;			// iocp�׽��ֲ��� ��������С32K [Send/Recv]��ͬ
const int		CONST_SOCKET_PACKET_SIZE			= 1024;					// ������Ϣ���ߴ�1K
const DWORD		CONST_WORK_THREAD_MIN_NUM			= 4;					// �����߳���С����
const DWORD		CONST_WORK_THREAD_MAX_NUM			= 16;					// �����߳��������

// =====================================================================

#endif