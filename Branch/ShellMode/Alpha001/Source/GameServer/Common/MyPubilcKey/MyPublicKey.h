////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2013, WuHan ChuangYou, All Rights Reserved
// Moudle: MyPublicKey.h
// Author: 彭文奇(Peng Wenqi)
// Created: 2013-5-13
////////////////////////////////////////////////////////////////////////
#ifndef _BAIHOWFF_MY_PUBLIC_KEY_DEF_H_
#define _BAIHOWFF_MY_PUBLIC_KEY_DEF_H_

#include <string>

#ifndef OUT
#define OUT
#endif

const int MAX_POSTBAR_KEY_SIZE	= 48;		// 贴吧通讯KEY的长度

struct KEY_COMPARE_INFO
{
	char			szKey[MAX_POSTBAR_KEY_SIZE];
	unsigned long	idUser;
	unsigned int	unVipLev;
	unsigned int	unTime;
	char			szAccName[64];
	char			szName[32];
	char			szServerName[32];
	char			szServerCfg[32];
	union
	{
		struct 
		{
			unsigned int unLev;
		}PostConnect;
		struct
		{
			unsigned int unSpendMoney;
		}PostPay;
	};
};

enum EM_MSG_POSTBAR_KEY_ACT
{
	EM_MSG_POSTBAR_KEY_ACT_CONNECT = 0,	// 获取连接KEY
	EM_MSG_POSTBAR_KEY_ACT_PAY,			// 获取充值KEY
};

std::string GetMyPubilcKey();
std::string GetMD5String(const char* pszInputString);
std::string GetRelationServerLoginKey(__int64 i64Time, int nGroup, int nLine);
std::string GetCrossServerLoginKey(__int64 i64Time, int nGroup);
std::string GetMyCodeKey(const char* pszInfo);
unsigned int GetSeedKey(unsigned int unSeed = 0);
unsigned int GetMsgKey(unsigned int unMsgType, unsigned int unMsgIndex);

void GetMyPublicCPU(OUT char* pszCpuInfo);
void GetMyPublicMemory(OUT char* pszMemory);
int GetMyPublicMAC(OUT char* pszMac, int i); 
bool GetMessageKey(int nKeyType, KEY_COMPARE_INFO& stKeyCompareInfo);
#endif // end of _BAIHOWFF_SAFE_CODE_BASE_DEF_H_