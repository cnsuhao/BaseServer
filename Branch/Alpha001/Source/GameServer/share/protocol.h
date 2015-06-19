////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan ChuangYou, All Rights Reserved
// Moudle: protocol.h
// Author: ������(Peng Wenqi)
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
		// ��½�̴߳������Ϣ
		LOGINTHREAD_BASE			= 1000,
		LOGINTHREAD_CLIENT_MSG		= LOGINTHREAD_BASE + 1,
		LOGINTHREAD_CLOSE_SOCKET	= LOGINTHREAD_BASE + 2,	// �ǳ�����4.4 ��½�̵߳ǳ�
		LOGINTHREAD_FORCE_KICK_ACK	= LOGINTHREAD_BASE + 3,	// ��������3.3 �ȴ������̷߳���
		LOGINTHREAD_CLOSE_ENTRANCE	= LOGINTHREAD_BASE + 4,	// �ر����

		//////////////////////////////////////////////////////////////////////////
		// AI�̴߳�����Ϣ
		AITHREAD_BASE				= 2000,
		AITHREAD_SEND_AI_MSG		= AITHREAD_BASE + 1,	// ���͵�AI��������Ϣ



		//////////////////////////////////////////////////////////////////////
		// ��Ϸ�̴߳������Ϣ
		GAMETHREAD_BASE				= 10000,
		GAMETHREAD_CLIENT_MSG		= GAMETHREAD_BASE + 1,
		GAMETHREAD_CLOSE_SOCKET		= GAMETHREAD_BASE + 2,	// �ǳ�����4.3 ��Ϸ�̵߳ǳ�
		GAMETHREAD_FORCE_KICK		= GAMETHREAD_BASE + 3,	// ��������3.2 �����¼�߳�ǿ�����˲�����
		GAMETHREAD_USER_LOGIN		= GAMETHREAD_BASE + 4,	// ��������3.7 �ŶӲ�����Ϸ�߳̽��м���
		GAMETHREAD_RECV_FROM_RS		= GAMETHREAD_BASE + 5,	// �����ϵ����Ϣ
		GAMETHREAD_KICK_RELATION	= GAMETHREAD_BASE + 6,	// ��ϵ���߳���ɫ
		GAMETHREAD_PAYLOG			= GAMETHREAD_BASE + 7,	// ֪ͨ��ֵ
		GAMETHREAD_RELOAD_TABLE		= GAMETHREAD_BASE + 8,	// ֪ͨ���ȸ���
		GAMETHREAD_ADD_USER_ONLINE	= GAMETHREAD_BASE + 9,	// ֪ͨ�����������
		GAMETHREAD_DEL_USER_ONLINE	= GAMETHREAD_BASE + 10,	// ֪ͨɾ���������
		GAMETHREAD_LUA_DEBUG_FLAG	= GAMETHREAD_BASE + 11,	// ����lua���Ա��
		GAMETHREAD_GM_CMD_NEED_MAC	= GAMETHREAD_BASE + 12,	// ����gm�����Ƿ���Ҫ��֤mac��ַ
		GAMETHREAD_RECV_IP			= GAMETHREAD_BASE + 13,	// ������ip
		GAMETHREAD_AI_CONNECT		= GAMETHREAD_BASE + 14,	// AI�������
		GAMETHREAD_AI_BREAK			= GAMETHREAD_BASE + 15,	// AI���ӶϿ�
		GAMETHREAD_AI_RECV_MSG		= GAMETHREAD_BASE + 16,	// AI����Ϣ
		GAMETHREAD_CROSS_MIN_LINE	= GAMETHREAD_BASE + 17,	// �������С������·
		GAMETHREAD_KICK_ALLUSER		= GAMETHREAD_BASE + 18,	// �߳����������������

		//////////////////////////////////////////////////////////////////////
		// ��ϵ�̴߳������Ϣ
		RELATION_BASE				= 20000,
		RELATIONTHREAD_CLOSE_SOCKET	= RELATION_BASE + 1,	// �ǳ�����4.2 ��ϵ�̵߳ǳ�
		RELATIONTHREAD_FORCE_KICK	= RELATION_BASE + 2,	// ��������3.2 �����¼�߳�ǿ�����˲�����
		RELATIONTHREAD_USER_LOGIN	= RELATION_BASE + 3,	// ��������3.8 ��Ϸ�̼߳�����ɲ�֪ͨ��ϵ�߳�
		RELATIONTHREAD_SEND_TO_RS	= RELATION_BASE + 4,	// ת������ϵ����������


		//////////////////////////////////////////////////////////////////////
		// ��SOCKET���Ĵ������Ϣ
		SOCKETTHREAD_BASE				= 30000,
		SOCKETTHREAD_CLOSESOCKET		= SOCKETTHREAD_BASE + 1,				// �ǳ�����4.5 ������Ļ��������Դ, ����֪ͨ�����߳����
		SOCKETTHREAD_SENDCLIENTMSG		= SOCKETTHREAD_BASE + 2,				
		SOCKETTHREAD_BREAKCONNECT		= SOCKETTHREAD_BASE + 3,				// �ǳ�����4.1 �������������Ͽ�����
		SOCKETTHREAD_BREAKALLCONNECT	= SOCKETTHREAD_BASE + 4,				// INT, GM_SOCKET_ID, ��������ң���ֹ�������ӡ�
		SOCKETTHREAD_FORCE_KICK			= SOCKETTHREAD_BASE + 5,				// ��������3.2 �����¼�߳�ǿ�����˲�����
		SOCKETTHREAD_BROADCAST_MSG		= SOCKETTHREAD_BASE + 6,				// �㲥��Ϣ
		SOCKETTHREAD_LOGINOVER			= SOCKETTHREAD_BASE + 7,				// ��½���
		SOCKETTHREAD_GAME_QUERYIP		= SOCKETTHREAD_BASE + 8,				// ��Ϸ�̲߳�ѯip


		//////////////////////////////////////////////////////////////////////
		// �ɶԻ�����Ǵ������Ϣ
		SHELLTHREAD_BASE				= 40000,
		SHELL_PRINTTEXT					= SHELLTHREAD_BASE + 1,				// STRING, ���ķ��͵�TEXT��Ϣ
		SHELL_REMOTE_CLOSE				= SHELLTHREAD_BASE + 2,				// �ط�
		SHELL_AUTO_UPDATE_TABLE			= SHELLTHREAD_BASE + 3,				// �Զ����±�
};

// �շ�client��Ϣ
struct CLIENTMSG_PACKET			
{
	SOCKET_ID	idSocket;			// SOCKET_ID
	OBJID		idPacket;
	int			nSize;
	char		buf[1];				// ���ڽṹָ�룬����Ҫ�ռ�
};

// ��ϵ����Ϣ
struct RELATIONSERVER_MSG_PACKET
{
	OBJID		idPacket;
	int			nSize;
	char		buf[1];				// ���ڽṹָ�룬����Ҫ�ռ�
};

// �����߳���Ϣ
struct THREAD_MSG_PACKET
{
	OBJID	idPacket;
	int		nSize;
	char	buf[1];
};

// ��ɫip
struct ST_USER_IP
{
	OBJID idUser;
	SOCKET_ID idSocket;
	char szIP[24];
};

// ����id���
struct ST_BASE_ID
{
	SOCKET_ID	idSocket;
	OBJID		idAccount;
	OBJID		idUser;
	int			nFromProcess;
	char		szName[NAME_SIZE];	
	int			nAccountType;	
};

// ��ֵ��¼
struct ST_PAYLOG
{
	OBJID idUser;
	OBJID idAccount;
	I64 i64PaylogID;
};

//////////////////////////////////////////////////////////////////////
// C/S Э��Ŀͻ��˲���	

// �ò��ֳ������������������������ʹ��
const int	PROTOCOL_MSG_HEADSIZE		= 4;
struct CProtocolMsgStruct{
	unsigned short	nMsgSize;
	unsigned short	idPacket;
	char			pMsg[1];
};


// �ֽ���Ϣ��
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

// �ϳ���Ϣ��
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
