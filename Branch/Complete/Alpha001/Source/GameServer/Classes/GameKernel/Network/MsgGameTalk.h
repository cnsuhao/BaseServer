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
		MSG_NUM_4BIT		nTxtAtr;			// Ƶ��

		ST_TALK_USER_INFO	stSenderInfo;		// ��������Ϣ
		MSG_NUM_4BIT		nServerUtcTime;		// Utcʱ��
		MSG_NUM_4BIT		nSynID;				// ��Ұ���ID
		MSG_NUM_4BIT		nReceiverID;		// ������ID
		MSG_STR_32BIT		szReceiverName;		// �����߽�ɫ��

		MSG_NUM_4BIT		nTxtType;			// ����
		MSG_NUM_4BIT		nClientParam1;		// client����1
		MSG_NUM_4BIT		nClientParam2;		// client����2
		MSG_NUM_4BIT		nClientParam3;		// client����3
		MSG_NUM_4BIT		nClientParam4;		// client����4

		MSG_NUM_4BIT		nServerParam1;		// server����1
		MSG_NUM_4BIT		nServerParam2;		// server����2
		MSG_NUM_4BIT		nServerParam3;		// server����3
		MSG_NUM_4BIT		nServerParam4;		// server����4

		MSG_NUM_4BIT		nDataSize;			// �䳤���鳤��(���256)
		char				szData[1];			// �䳤����
	}MSG_Info;
	MSG_Info* m_pInfo;
};


#endif