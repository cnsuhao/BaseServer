//////////////////////////////////////////////////////////////////////////
// Moudle:	 GlobalConstDef.h
// Describe: 全局结常量定义
// Author:	 陈建军(Chen Jianjun)
// Created:	 2015-02-28
//////////////////////////////////////////////////////////////////////////
#ifndef _GLOBAL_CONST_DEF_H
#define _GLOBAL_CONST_DEF_H

// ===========================SOCKET配置相关============================
const int		CONST_IOHANDLE_MAX_NUM				= 1;					// IO句柄数量

#ifdef _DEBUG
const int		CONST_ACCEPT_SESSION_MAX_NUM		= 200;					// 接受回话最大数量（调试模式）
#else
const int		CONST_ACCEPT_SESSION_MAX_NUM		= 5000;					// 接受回话最大数量
#endif

const int		CONST_IOCP_SOCKET_BUFFER_SIZE		= 1024 * 32;			// iocp套接字参数 缓冲区大小32K [Send/Recv]相同
const int		CONST_SOCKET_PACKET_SIZE			= 1024;					// 网络消息包尺寸1K
const DWORD		CONST_WORK_THREAD_MIN_NUM			= 4;					// 工作线程最小数量
const DWORD		CONST_WORK_THREAD_MAX_NUM			= 16;					// 工作线程最大数量

// =====================================================================

#endif