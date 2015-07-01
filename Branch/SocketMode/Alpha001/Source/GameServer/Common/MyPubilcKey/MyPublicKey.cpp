////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2013, WuHan ChuangYou, All Rights Reserved
// Moudle: MyPublicKey.cpp
// Author: 彭文奇(Peng Wenqi)
// Created: 2013-5-13
////////////////////////////////////////////////////////////////////////
#include "MyPublicKey.h"
#include "md5.h"
#pragma warning(disable:4996)		// 微软提示要用自家的安全_s函数

#include <string>
#include <fstream>
#include <sstream>

#include <stdio.h>     //该头文件声明了输入输出流函数   
#include <stdlib.h>    //该头文件定义了一些通用函数   
#include "windows.h"
#include <httpext.h>   //该头文件支持HTTP请求   
#include <Nb30.h>      //该头文件声明了netbios的所有的函数    
#pragma comment(lib,"netapi32.lib")   //连接Netapi32.lib库，MAC获取中用到了NetApi32.DLL的功能   

////////////////////////////////////////////////////////////////////////
// Description:  生成公钥
// Arguments:
// Author: 彭文奇(Peng Wenqi)
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
// Description:  获得md5串
// Arguments:
// Author: 彭文奇(Peng Wenqi)
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
// Description:  通过SYSTEM_INFO 自己拼接一个cpu字符串
// Arguments:
// Author: 彭文奇(Peng Wenqi)
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
// Description:  通过MEMORYSTATUSEX 自己拼接一个内存信息字符串
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void GetMyPublicMemory(OUT char* pszMemory)
{
	MEMORYSTATUSEX stMemStatus = {0};
	stMemStatus.dwLength = sizeof(stMemStatus);
	::GlobalMemoryStatusEx(&stMemStatus);

	sprintf(pszMemory, "TotalPhys: [%06I64u]Bytes ", stMemStatus.ullTotalPhys);
}

//通过WindowsNT/Win2000中内置的NetApi32.DLL的功能来实现的。首先通过发送NCBENUM命令,获取网卡的   
//数目和每张网卡的内部编号,然后对每个网卡标号发送NCBASTAT命令获取其MAC地址。   
int GetMyPublicMAC(OUT char* pszMac, int i)     //用NetAPI来获取网卡MAC地址   
{       
	NCB ncb;     //定义一个NCB(网络控制块)类型的结构体变量ncb   
	typedef struct _ASTAT_     //自定义一个结构体_ASTAT_   
	{  
		ADAPTER_STATUS   adapt;   
		NAME_BUFFER   NameBuff   [30];       
	}ASTAT, *PASTAT;  
	ASTAT Adapter;     

	typedef struct _LANA_ENUM     //自定义一个结构体_ASTAT_   
	{  
		UCHAR length;   
		UCHAR lana[MAX_LANA];     //存放网卡MAC地址    
	}LANA_ENUM;       
	LANA_ENUM lana_enum;     

	//   取得网卡信息列表        
	UCHAR uRetCode;       
	memset(&ncb, 0, sizeof(ncb));     //将已开辟内存空间ncb 的值均设为值 0   
	memset(&lana_enum, 0, sizeof(lana_enum));     //清空一个结构类型的变量lana_enum，赋值为0   
	//对结构体变量ncb赋值   
	ncb.ncb_command = NCBENUM;     //统计系统中网卡的数量   
	ncb.ncb_buffer = (unsigned char *)&lana_enum; //ncb_buffer成员指向由LANA_ENUM结构填充的缓冲区   
	ncb.ncb_length = sizeof(LANA_ENUM);     
	//向网卡发送NCBENUM命令，以获取当前机器的网卡信息，如有多少个网卡，每个网卡的编号（MAC地址）    
	uRetCode = Netbios(&ncb); //调用netbois(ncb)获取网卡序列号       
	if(uRetCode != NRC_GOODRET)       
		return uRetCode;       

	//对每一个网卡，以其网卡编号为输入编号，获取其MAC地址      
	for(int lana=0; lana<lana_enum.length; lana++)       
	{  
		ncb.ncb_command = NCBRESET;   //对网卡发送NCBRESET命令，进行初始化   
		ncb.ncb_lana_num = lana_enum.lana[lana];   
		uRetCode = Netbios(&ncb);     
	}   
	if(uRetCode != NRC_GOODRET)  
		return uRetCode;       

	//   准备取得接口卡的状态块,取得MAC地址   
	memset(&ncb, 0, sizeof(ncb));   
	ncb.ncb_command = NCBASTAT;    //对网卡发送NCBSTAT命令，获取网卡信息   
	ncb.ncb_lana_num = lana_enum.lana[i];     //指定网卡号，这里仅仅指定第一块网卡，通常为有线网卡    
	strcpy((char*)ncb.ncb_callname, "*");     //远程系统名赋值为*   
	ncb.ncb_buffer = (unsigned char *)&Adapter; //指定返回的信息存放的变量   
	ncb.ncb_length = sizeof(Adapter);  
	//接着发送NCBASTAT命令以获取网卡的信息   
	uRetCode = Netbios(&ncb);   
	//   取得网卡的信息，并且如果网卡正常工作的话，返回标准的冒号分隔格式。      
	if(uRetCode != NRC_GOODRET)     
		return uRetCode;     
	//把网卡MAC地址格式转化为常用的16进制形式,输出到字符串mac中    
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
// Description:  生成种子秘钥
// Arguments:
// Author: 彭文奇(Peng Wenqi)
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
// Description:  获得消息秘钥
// Arguments:
// Author: 彭文奇(Peng Wenqi)
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
	// 检测KEY的正确性
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
