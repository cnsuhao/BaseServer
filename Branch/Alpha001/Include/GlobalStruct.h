//////////////////////////////////////////////////////////////////////////
// Moudle:	 GlobalStruct.h
// Describe: 全局结构体定义
// Author:	 陈建军(Chen Jianjun)
// Created:	 2015-02-28
//////////////////////////////////////////////////////////////////////////
#ifndef _GLOBAL_STRUCT_H_
#define _GLOBAL_STRUCT_H_

// IOCP句柄结构定义
typedef struct{
	DWORD	dw_IOHandle_Index;			// 句柄索引
	DWORD	dw_AcceptSession_MaxNum;	// 会话最大接受数量
	DWORD	dw_ConnectSession_MaxNum;	// 回话最大连接数量
	DWORD	dw_SendBuffer_Size;			// 发送缓冲区大小
	DWORD	dw_RecvBuffer_Size;			// 接收缓冲区大小
	DWORD	dw_Packet_MaxSize;			// 消息包最大长度
	DWORD	dw_IOThread_Num;			// I/O线程数量(处理消息Send/Recv)
	DWORD	dw_AcceptThread_Num;		// 接受线程数量
	DWORD	dw_ConnectThread_Num;		// 连接线程数量
}ST_IOCP_HANDLE, *LP_ST_IOCP_HANDLE;

#endif