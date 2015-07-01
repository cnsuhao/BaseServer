////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2013, WuHan ChuangYou, All Rights Reserved
// Moudle: MyPublicKey.cpp
// Author: ������(Peng Wenqi)
// Created: 2013-5-13
////////////////////////////////////////////////////////////////////////
#include "MyPublicKey.h"
#include "md5.h"
#pragma warning(disable:4996)		// ΢����ʾҪ���Լҵİ�ȫ_s����

#include <string>
#include <fstream>
#include <sstream>

#include <stdio.h>     //��ͷ�ļ��������������������   
#include <stdlib.h>    //��ͷ�ļ�������һЩͨ�ú���   
#include "windows.h"
#include <httpext.h>   //��ͷ�ļ�֧��HTTP����   
#include <Nb30.h>      //��ͷ�ļ�������netbios�����еĺ���    
#pragma comment(lib,"netapi32.lib")   //����Netapi32.lib�⣬MAC��ȡ���õ���NetApi32.DLL�Ĺ���   

////////////////////////////////////////////////////////////////////////
// Description:  ���ɹ�Կ
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: std::string
////////////////////////////////////////////////////////////////////////
std::string GetMyPubilcKey()
{
	char szCpuInfo[128] = "";
	char szMemory[128] = "";
	char szMac[128] = "";

	GetMyPublicCPU(szCpuInfo);
	GetMyPublicMemory(szMemory);
	GetMyPublicMAC(szMac, 0);

	char szBeforeInfo[512] = "";
	sprintf(szBeforeInfo, "BaihowFF MyPublicKey %s - %s - %s", szCpuInfo, szMemory, szMac);

	return CMyMD5(szBeforeInfo).toString();
}

////////////////////////////////////////////////////////////////////////
// Description:  ���md5��
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: std::string
////////////////////////////////////////////////////////////////////////
std::string GetMD5String( const char* pszInputString )
{
	std::string strResult = "";
	if (pszInputString)
	{
		strResult = CMyMD5(pszInputString).toString();
	}
	return strResult;
}


////////////////////////////////////////////////////////////////////////
// Description:  ͨ��SYSTEM_INFO �Լ�ƴ��һ��cpu�ַ���
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void GetMyPublicCPU(OUT char* pszCpuInfo)
{
	SYSTEM_INFO systemInfo;
	GetSystemInfo(&systemInfo);
	sprintf(pszCpuInfo, "CpuCount[%u], CpuType[%u], CpuLevel[%d], CpuVer[%d] ", 
		systemInfo.dwNumberOfProcessors,
		systemInfo.dwProcessorType,
		(int)systemInfo.wProcessorLevel,
		(int)systemInfo.wProcessorRevision);
}

////////////////////////////////////////////////////////////////////////
// Description:  ͨ��MEMORYSTATUSEX �Լ�ƴ��һ���ڴ���Ϣ�ַ���
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void GetMyPublicMemory(OUT char* pszMemory)
{
	MEMORYSTATUSEX stMemStatus = {0};
	stMemStatus.dwLength = sizeof(stMemStatus);
	::GlobalMemoryStatusEx(&stMemStatus);

	sprintf(pszMemory, "TotalPhys: [%06I64u]Bytes ", stMemStatus.ullTotalPhys);
}

//ͨ��WindowsNT/Win2000�����õ�NetApi32.DLL�Ĺ�����ʵ�ֵġ�����ͨ������NCBENUM����,��ȡ������   
//��Ŀ��ÿ���������ڲ����,Ȼ���ÿ��������ŷ���NCBASTAT�����ȡ��MAC��ַ��   
int GetMyPublicMAC(OUT char* pszMac, int i)     //��NetAPI����ȡ����MAC��ַ   
{       
	NCB ncb;     //����һ��NCB(������ƿ�)���͵Ľṹ�����ncb   
	typedef struct _ASTAT_     //�Զ���һ���ṹ��_ASTAT_   
	{  
		ADAPTER_STATUS   adapt;   
		NAME_BUFFER   NameBuff   [30];       
	}ASTAT, *PASTAT;  
	ASTAT Adapter;     

	typedef struct _LANA_ENUM     //�Զ���һ���ṹ��_ASTAT_   
	{  
		UCHAR length;   
		UCHAR lana[MAX_LANA];     //�������MAC��ַ    
	}LANA_ENUM;       
	LANA_ENUM lana_enum;     

	//   ȡ��������Ϣ�б�        
	UCHAR uRetCode;       
	memset(&ncb, 0, sizeof(ncb));     //���ѿ����ڴ�ռ�ncb ��ֵ����Ϊֵ 0   
	memset(&lana_enum, 0, sizeof(lana_enum));     //���һ���ṹ���͵ı���lana_enum����ֵΪ0   
	//�Խṹ�����ncb��ֵ   
	ncb.ncb_command = NCBENUM;     //ͳ��ϵͳ������������   
	ncb.ncb_buffer = (unsigned char *)&lana_enum; //ncb_buffer��Աָ����LANA_ENUM�ṹ���Ļ�����   
	ncb.ncb_length = sizeof(LANA_ENUM);     
	//����������NCBENUM����Ի�ȡ��ǰ������������Ϣ�����ж��ٸ�������ÿ�������ı�ţ�MAC��ַ��    
	uRetCode = Netbios(&ncb); //����netbois(ncb)��ȡ�������к�       
	if(uRetCode != NRC_GOODRET)       
		return uRetCode;       

	//��ÿһ�������������������Ϊ�����ţ���ȡ��MAC��ַ      
	for(int lana=0; lana<lana_enum.length; lana++)       
	{  
		ncb.ncb_command = NCBRESET;   //����������NCBRESET������г�ʼ��   
		ncb.ncb_lana_num = lana_enum.lana[lana];   
		uRetCode = Netbios(&ncb);     
	}   
	if(uRetCode != NRC_GOODRET)  
		return uRetCode;       

	//   ׼��ȡ�ýӿڿ���״̬��,ȡ��MAC��ַ   
	memset(&ncb, 0, sizeof(ncb));   
	ncb.ncb_command = NCBASTAT;    //����������NCBSTAT�����ȡ������Ϣ   
	ncb.ncb_lana_num = lana_enum.lana[i];     //ָ�������ţ��������ָ����һ��������ͨ��Ϊ��������    
	strcpy((char*)ncb.ncb_callname, "*");     //Զ��ϵͳ����ֵΪ*   
	ncb.ncb_buffer = (unsigned char *)&Adapter; //ָ�����ص���Ϣ��ŵı���   
	ncb.ncb_length = sizeof(Adapter);  
	//���ŷ���NCBASTAT�����Ի�ȡ��������Ϣ   
	uRetCode = Netbios(&ncb);   
	//   ȡ����������Ϣ����������������������Ļ������ر�׼��ð�ŷָ���ʽ��      
	if(uRetCode != NRC_GOODRET)     
		return uRetCode;     
	//������MAC��ַ��ʽת��Ϊ���õ�16������ʽ,������ַ���mac��    
	sprintf(pszMac,"%02X-%02X-%02X-%02X-%02X-%02X",       
		Adapter.adapt.adapter_address[0],       
		Adapter.adapt.adapter_address[1],       
		Adapter.adapt.adapter_address[2],       
		Adapter.adapt.adapter_address[3],       
		Adapter.adapt.adapter_address[4],       
		Adapter.adapt.adapter_address[5]   
	);   
	return 0;     
}  

////////////////////////////////////////////////////////////////////////
// Description:  ����������Կ
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: unsigned int
////////////////////////////////////////////////////////////////////////
unsigned int GetSeedKey( unsigned int unSeed /*= 0*/)
{
	if (unSeed == 0)
	{
		unSeed = 618;
	}
	__int64 i64MyRand = unSeed;
	i64MyRand *= ((_int64)134775813);
	i64MyRand ++;
	i64MyRand %= 99999989;
	return (unsigned int)i64MyRand;
}

////////////////////////////////////////////////////////////////////////
// Description:  �����Ϣ��Կ
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: unsigned int
////////////////////////////////////////////////////////////////////////
unsigned int GetMsgKey( unsigned int unMsgType, unsigned int unMsgIndex )
{
	__int64 i64MyRand = unMsgType + unMsgIndex;
	i64MyRand *= ((_int64)22695477);
	i64MyRand ++;
	i64MyRand %= 100000007;
	return (unsigned int)i64MyRand;
}

bool GetMessageKey(int nKeyType, KEY_COMPARE_INFO& stKeyCompareInfo)
{
	if (stKeyCompareInfo.idUser == 0)
	{
		return (false);
	}
	if (strlen(stKeyCompareInfo.szName) == 0)
	{
		return (false);
	}
	if (strlen(stKeyCompareInfo.szAccName) == 0)
	{
		return (false);
	}
	if (strlen(stKeyCompareInfo.szServerName) == 0)
	{
		return (false);
	}
	char szBeforeInfo[512] = "";
	switch(nKeyType)
	{
	case EM_MSG_POSTBAR_KEY_ACT_CONNECT:
		{
			sprintf(szBeforeInfo,"Connect%u%s%u%s%u%s%u%s",
					stKeyCompareInfo.idUser, stKeyCompareInfo.szAccName, stKeyCompareInfo.unTime, stKeyCompareInfo.szServerName, 
					stKeyCompareInfo.unVipLev, stKeyCompareInfo.szName, stKeyCompareInfo.PostConnect.unLev, stKeyCompareInfo.szServerCfg);
		}
		break;
	case EM_MSG_POSTBAR_KEY_ACT_PAY:
		{
			sprintf(szBeforeInfo,"PostPay%u%s%u%s%s%u%s",
					stKeyCompareInfo.idUser, stKeyCompareInfo.szAccName, stKeyCompareInfo.unTime, stKeyCompareInfo.szServerName, 
					stKeyCompareInfo.szName, stKeyCompareInfo.PostPay.unSpendMoney, stKeyCompareInfo.szServerCfg);
		}
		break;
	default:
		{
			return (false);
		}
		break;
	};
	// ���KEY����ȷ��
	std::string strKey = CMyMD5(szBeforeInfo).toString();
	strcpy(stKeyCompareInfo.szKey, strKey.c_str());
	return (true);
}

std::string GetRelationServerLoginKey( __int64 i64Time, int nGroup, int nLine )
{
	char szBeforeInfo[512] = "";
	sprintf(szBeforeInfo, "BaihowFF RelationServerLoginKey %I64d - %d - %d", i64Time, nGroup, nLine);
	return CMyMD5(szBeforeInfo).toString();
}

std::string GetCrossServerLoginKey( __int64 i64Time, int nGroup )
{
	char szBeforeInfo[512] = "";
	sprintf(szBeforeInfo, "BaihowFF CrossServerLoginKey %I64d - %d", i64Time, nGroup);
	return CMyMD5(szBeforeInfo).toString();
}

std::string GetMyCodeKey(const char* pszInfo)
{
	if (NULL == pszInfo)
	{
		return "";
	}
	return CMyMD5(pszInfo).GetMyCode();
}
