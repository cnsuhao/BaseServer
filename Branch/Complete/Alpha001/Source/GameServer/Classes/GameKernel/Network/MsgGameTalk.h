#ifndef _GAMEKERNEL_MSG_TALK_H_
#define _GAMEKERNEL_MSG_TALK_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "./NetMsg.h"

class CMsgGameTalk : public game_kernel::CNetMsg
{
public:
	CMsgGameTalk();
	virtual ~CMsgGameTalk();

public:
	virtual BOOL	Create(char* pbufMsg, DWORD dwMsgSize);
	virtual void	Process(void *pInfo);

public:
	bool	CreateTalk(TALK_TXTATR eTxtAtr, const char* pszText, int nDataSize, int nTxtType = 0, int nClientParam1 = 0, int nClientParam2 = 0, int nClientParam3 = 0, int nClientParam4 = 0);
	void	SetSenderInfo(IN const ST_TALK_USER_INFO& info);
	void	SetReceiverName(const char* pszName);
	void	SerReceiverID(OBJID idUser);
	void	SetSynID(OBJID idSyn);
	void	SetUtcTime(UINT unTime);
	void	SetServerParam1(int nParam);
	void	SetServerParam2(int nParam);
	void	SetServerParam3(int nParam);
	void	SetServerParam4(int nParam);

private:
	typedef struct
	{
		MSG_NUM_4BIT		nTxtAtr;			// 频道

		ST_TALK_USER_INFO	stSenderInfo;		// 发送者信息
		MSG_NUM_4BIT		nServerUtcTime;		// Utc时间
		MSG_NUM_4BIT		nSynID;				// 玩家帮派ID
		MSG_NUM_4BIT		nReceiverID;		// 接收者ID
		MSG_STR_32BIT		szReceiverName;		// 接收者角色名

		MSG_NUM_4BIT		nTxtType;			// 类型
		MSG_NUM_4BIT		nClientParam1;		// client参数1
		MSG_NUM_4BIT		nClientParam2;		// client参数2
		MSG_NUM_4BIT		nClientParam3;		// client参数3
		MSG_NUM_4BIT		nClientParam4;		// client参数4

		MSG_NUM_4BIT		nServerParam1;		// server参数1
		MSG_NUM_4BIT		nServerParam2;		// server参数2
		MSG_NUM_4BIT		nServerParam3;		// server参数3
		MSG_NUM_4BIT		nServerParam4;		// server参数4

		MSG_NUM_4BIT		nDataSize;			// 变长数组长度(最大256)
		char				szData[1];			// 变长数组
	}MSG_Info;
	MSG_Info* m_pInfo;
};


#endif