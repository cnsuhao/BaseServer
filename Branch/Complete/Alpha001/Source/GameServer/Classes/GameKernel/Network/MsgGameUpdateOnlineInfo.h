//////////////////////////////////////////////////////////////////////////
//// Copyright(c) 2011-2014, WuHan ChuangYou, All Rights Reserved
//// Moudle: MsgGameUpdateOnlineInfo.h
//// Author: ÅíÎÄÆæ(Peng Wenqi)
//// Created: 2014-11-19
//////////////////////////////////////////////////////////////////////////
//#ifndef _GAMEKERNER_MSG_GAME_USER_UPDATE_ONLINE_INFO_H_
//#define _GAMEKERNER_MSG_GAME_USER_UPDATE_ONLINE_INFO_H_
//
//#if _MSC_VER > 1000
//#pragma once
//#endif // _MSC_VER > 1000
//
//#include "./NetMsg.h"
//
//class CMsgGameUpdateOnlineInfo : public game_kernel::CNetMsg
//{
//public:
//	CMsgGameUpdateOnlineInfo();
//	virtual ~CMsgGameUpdateOnlineInfo();
//
//	virtual BOOL Create(char* pMsgBuf, DWORD dwSize);
//	virtual void Process(void *pInfo);
//
//public:
//	bool CreateUserInfo(const USER_ONLINE_INFO* pOnlineInfo);
//
//
//private:
//	typedef struct  
//	{
//		USER_ONLINE_INFO stOnlineInfo;
//	}MSG_Info;
//
//	MSG_Info* m_pInfo;
//};
//
//
//#endif // end of _GAMEKERNER_MSG_GAME_USER_UPDATE_ONLINE_INFO_H_