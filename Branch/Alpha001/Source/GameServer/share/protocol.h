////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan ChuangYou, All Rights Reserved
// Moudle: protocol.h
// Author: 彭文奇(Peng Wenqi)
// Created: 2014-12-20
////////////////////////////////////////////////////////////////////////
#ifndef	PROTOCOL_H
#define	PROTOCOL_H

#include <string.h>
#include "define.h"
#include <vector>

enum THREAD_PACKET_TYPE
{
		//////////////////////////////////////////////////////////////////////
		// 登陆线程处理的消息
		LOGINTHREAD_BASE			= 1000,
		LOGINTHREAD_CLIENT_MSG		= LOGINTHREAD_BASE + 1,
		LOGINTHREAD_CLOSE_SOCKET	= LOGINTHREAD_BASE + 2,	// 登出流程4.4 登陆线程登出
		LOGINTHREAD_FORCE_KICK_ACK	= LOGINTHREAD_BASE + 3,	// 登入流程3.3 等待其他线程反馈
		LOGINTHREAD_CLOSE_ENTRANCE	= LOGINTHREAD_BASE + 4,	// 关闭入口

		//////////////////////////////////////////////////////////////////////////
		// AI线程处理消息
		AITHREAD_BASE				= 2000,
		AITHREAD_SEND_AI_MSG		= AITHREAD_BASE + 1,	// 发送到AI服务器消息



		//////////////////////////////////////////////////////////////////////
		// 游戏线程处理的消息
		GAMETHREAD_BASE				= 10000,
		GAMETHREAD_CLIENT_MSG		= GAMETHREAD_BASE + 1,
		GAMETHREAD_CLOSE_SOCKET		= GAMETHREAD_BASE + 2,	// 登出流程4.3 游戏线程登出
		GAMETHREAD_FORCE_KICK		= GAMETHREAD_BASE + 3,	// 登入流程3.2 处理登录线程强行踢人并反馈
		GAMETHREAD_USER_LOGIN		= GAMETHREAD_BASE + 4,	// 登入流程3.7 排队并在游戏线程进行加载
		GAMETHREAD_RECV_FROM_RS		= GAMETHREAD_BASE + 5,	// 处理关系服消息
		GAMETHREAD_KICK_RELATION	= GAMETHREAD_BASE + 6,	// 关系服踢出角色
		GAMETHREAD_PAYLOG			= GAMETHREAD_BASE + 7,	// 通知充值
		GAMETHREAD_RELOAD_TABLE		= GAMETHREAD_BASE + 8,	// 通知表热更新
		GAMETHREAD_ADD_USER_ONLINE	= GAMETHREAD_BASE + 9,	// 通知增加玩家在线
		GAMETHREAD_DEL_USER_ONLINE	= GAMETHREAD_BASE + 10,	// 通知删除玩家在线
		GAMETHREAD_LUA_DEBUG_FLAG	= GAMETHREAD_BASE + 11,	// 设置lua调试标记
		GAMETHREAD_GM_CMD_NEED_MAC	= GAMETHREAD_BASE + 12,	// 设置gm命令是否需要验证mac地址
		GAMETHREAD_RECV_IP			= GAMETHREAD_BASE + 13,	// 获得玩家ip
		GAMETHREAD_AI_CONNECT		= GAMETHREAD_BASE + 14,	// AI连接完成
		GAMETHREAD_AI_BREAK			= GAMETHREAD_BASE + 15,	// AI连接断开
		GAMETHREAD_AI_RECV_MSG		= GAMETHREAD_BASE + 16,	// AI收消息
		GAMETHREAD_CROSS_MIN_LINE	= GAMETHREAD_BASE + 17,	// 跨服组最小在线线路
		GAMETHREAD_KICK_ALLUSER		= GAMETHREAD_BASE + 18,	// 踢出服务器组所有玩家

		//////////////////////////////////////////////////////////////////////
		// 关系线程处理的消息
		RELATION_BASE				= 20000,
		RELATIONTHREAD_CLOSE_SOCKET	= RELATION_BASE + 1,	// 登出流程4.2 关系线程登出
		RELATIONTHREAD_FORCE_KICK	= RELATION_BASE + 2,	// 登入流程3.2 处理登录线程强行踢人并反馈
		RELATIONTHREAD_USER_LOGIN	= RELATION_BASE + 3,	// 登入流程3.8 游戏线程加载完成并通知关系线程
		RELATIONTHREAD_SEND_TO_RS	= RELATION_BASE + 4,	// 转发到关系服务器处理


		//////////////////////////////////////////////////////////////////////
		// 由SOCKET核心处理的消息
		SOCKETTHREAD_BASE				= 30000,
		SOCKETTHREAD_CLOSESOCKET		= SOCKETTHREAD_BASE + 1,				// 登出流程4.5 网络核心回收最后资源, 不再通知其他线程完成
		SOCKETTHREAD_SENDCLIENTMSG		= SOCKETTHREAD_BASE + 2,				
		SOCKETTHREAD_BREAKCONNECT		= SOCKETTHREAD_BASE + 3,				// 登出流程4.1 向网络核心请求断开连接
		SOCKETTHREAD_BREAKALLCONNECT	= SOCKETTHREAD_BASE + 4,				// INT, GM_SOCKET_ID, 踢所有玩家，禁止所有连接。
		SOCKETTHREAD_FORCE_KICK			= SOCKETTHREAD_BASE + 5,				// 登入流程3.2 处理登录线程强行踢人并反馈
		SOCKETTHREAD_BROADCAST_MSG		= SOCKETTHREAD_BASE + 6,				// 广播消息
		SOCKETTHREAD_LOGINOVER			= SOCKETTHREAD_BASE + 7,				// 登陆完成
		SOCKETTHREAD_GAME_QUERYIP		= SOCKETTHREAD_BASE + 8,				// 游戏线程查询ip


		//////////////////////////////////////////////////////////////////////
		// 由对话框外壳处理的消息
		SHELLTHREAD_BASE				= 40000,
		SHELL_PRINTTEXT					= SHELLTHREAD_BASE + 1,				// STRING, 核心发送的TEXT消息
		SHELL_REMOTE_CLOSE				= SHELLTHREAD_BASE + 2,				// 关服
		SHELL_AUTO_UPDATE_TABLE			= SHELLTHREAD_BASE + 3,				// 自动更新表
};

// 收发client消息
struct CLIENTMSG_PACKET			
{
	SOCKET_ID	idSocket;			// SOCKET_ID
	OBJID		idPacket;
	int			nSize;
	char		buf[1];				// 用于结构指针，不需要空间
};

// 关系服消息
struct RELATIONSERVER_MSG_PACKET
{
	OBJID		idPacket;
	int			nSize;
	char		buf[1];				// 用于结构指针，不需要空间
};

// 其他线程消息
struct THREAD_MSG_PACKET
{
	OBJID	idPacket;
	int		nSize;
	char	buf[1];
};

// 角色ip
struct ST_USER_IP
{
	OBJID idUser;
	SOCKET_ID idSocket;
	char szIP[24];
};

// 基础id组合
struct ST_BASE_ID
{
	SOCKET_ID	idSocket;
	OBJID		idAccount;
	OBJID		idUser;
	int			nFromProcess;
	char		szName[NAME_SIZE];	
	int			nAccountType;	
};

// 充值记录
struct ST_PAYLOG
{
	OBJID idUser;
	OBJID idAccount;
	I64 i64PaylogID;
};

//////////////////////////////////////////////////////////////////////
// C/S 协议的客户端部分	

// 该部分常量、定义仅由以下两个函数使用
const int	PROTOCOL_MSG_HEADSIZE		= 4;
struct CProtocolMsgStruct{
	unsigned short	nMsgSize;
	unsigned short	idPacket;
	char			pMsg[1];
};


// 分解消息包
// return: netpacket size
inline int	SplitPacket(char* pBuf, int nBufLen, OBJID* pidPacket, char** ppMsg, int* pMsgSize)
{
	if(nBufLen > PROTOCOL_MSG_HEADSIZE)
	{
		CProtocolMsgStruct*	pMsgPtr = (CProtocolMsgStruct*)pBuf;
		if(pMsgPtr->nMsgSize <= nBufLen)
		{
			if(pMsgPtr->nMsgSize < 4 || pMsgPtr->nMsgSize > MAX_PACKETSIZE)
				return 0;

			*pidPacket	= pMsgPtr->idPacket;
			*pMsgSize	= pMsgPtr->nMsgSize - PROTOCOL_MSG_HEADSIZE;
			*ppMsg		= pMsgPtr->pMsg;
			return pMsgPtr->nMsgSize;
		}
	}
	return 0;
}

// 合成消息包
// return: netpacket size
inline int	UnitePacket(char* pBuf, int nBufLen, OBJID idPacket, const char* pMsg, int nMsgSize, unsigned int& nMsgType)
{
	if(nBufLen >= nMsgSize + PROTOCOL_MSG_HEADSIZE)
	{
		CProtocolMsgStruct*	pMsgPtr = (CProtocolMsgStruct*)pBuf;
		pMsgPtr->idPacket		= (unsigned short)idPacket;
		nMsgType = pMsgPtr->idPacket;
		pMsgPtr->nMsgSize		= nMsgSize + PROTOCOL_MSG_HEADSIZE;
		memcpy(pMsgPtr->pMsg,	pMsg, (size_t)nMsgSize);

		return pMsgPtr->nMsgSize;
	}
	return 0;
}


#endif // PROTOCOL_H
