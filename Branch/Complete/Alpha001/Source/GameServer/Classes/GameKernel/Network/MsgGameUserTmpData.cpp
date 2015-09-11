////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan ChuangYou, All Rights Reserved
// Moudle: MsgGameUserTmpData.cpp
// Author: 丁乐(Ding Le)
// Created: 2014-11-10
////////////////////////////////////////////////////////////////////////

#include "./MsgGameUserTmpData.h"
#include "../User.h"
#include "../UserMgr.h"
#include "../UserTmpDataMgr.h"

CMsgGameUserTmpData::CMsgGameUserTmpData()
{
	Init();
	m_pInfo = (MSG_Info*)m_bufMsg;
	m_unMsgType = _MSG_GAME_TMP_DATA;
	m_unMsgSize = sizeof(MSG_Info);
}

CMsgGameUserTmpData::~CMsgGameUserTmpData()
{

}

BOOL CMsgGameUserTmpData::Create(char* pMsgBuf, DWORD dwSize)
{
	if (!CNetMsg::Create(pMsgBuf, dwSize))
	{
		return false;
	}
	if (_MSG_GAME_TMP_DATA != this->GetType())
	{
		return false;
	}
	return true;
}

bool CMsgGameUserTmpData::CreateMsg(int nAction, int nResult, int nTmpDataIndex /*= 0*/, int nEndFlag /*= 0*/)
{
	this->Init();
	m_unMsgType	= _MSG_GAME_TMP_DATA;
	m_unMsgSize	= sizeof(MSG_Info) - sizeof(MSG_NUM_4BIT);

	m_pInfo->sAction = nAction;
	m_pInfo->sResult = nResult;
	m_pInfo->nTmpDataID = nTmpDataIndex;
	m_pInfo->nEndFlag = nEndFlag;
	m_pInfo->nDataNum = 0;

	return true;
}

////////////////////////////////////////////////////////////////////////
// Description:  增加参数
bool CMsgGameUserTmpData::AppendParam(int nData)
{
	CHECKF(sizeof(MSG_Info) + sizeof(MSG_NUM_4BIT) * m_pInfo->nDataNum < MAX_PACKETSIZE);
	m_pInfo->arrData[m_pInfo->nDataNum] = nData;
	m_unMsgSize = sizeof(MSG_Info) + sizeof(MSG_NUM_4BIT) * m_pInfo->nDataNum;
	m_pInfo->nDataNum++;
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description:  增加一整条TmpData(TmpDataID, Data0 - Data7 共9个)
bool CMsgGameUserTmpData::AppendTmpData(IN INT_VEC& vecInt)
{
	int nSize = vecInt.size();
	CHECKF(nSize == (USERTMPDATA_INDEX_END - USERTMPDATA_INDEX_BEG + 1));
	CHECKF_NOLOG(m_unMsgSize + sizeof(MSG_NUM_4BIT) * nSize < MAX_PACKETSIZE);
	for (int i = 0; i < nSize; i++)
	{
		m_pInfo->arrData[m_pInfo->nDataNum] = vecInt[i];
		m_pInfo->nDataNum++;
	}
	m_unMsgSize += (nSize * sizeof(MSG_NUM_4BIT));
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description:   设置结束标记
void CMsgGameUserTmpData::SetMsgEnd()
{
	m_pInfo->nEndFlag = 1;
}

void CMsgGameUserTmpData::Process(void *pInfo)
{
	DEBUG_TRY;
	OBJID idUser = pUserMgr->GetUserIDByMsg(this);
	CHECK(idUser);
	
	switch(m_pInfo->sAction)
	{
	case MSG_TMP_DATA_ACT_ReqGetTmpData:
		{
			this->ProcessReqGetTmpData(idUser);
		}
		break;
	case MSG_TMP_DATA_ACT_ReqSetTmpData:
		{
			this->ProcessReqSetTmpData(idUser);
		}
		break;
	default:
		{
			tolog2("CMsgGameUserTmpData::Process Unknow action[%d]", m_pInfo->sAction);
		}
		break;
	}
	DEBUG_CATCH2("CMsgGameUserTmpData::Process Action[%d]", m_pInfo->sAction);
}

// 请求获取TmpData
void CMsgGameUserTmpData::ProcessReqGetTmpData(OBJID idUser)
{
	CHECK(idUser);
	OBJID idTmpData = m_pInfo->nTmpDataID;
	CHECK(idTmpData);

	CMsgGameUserTmpData msg;
	int nResult = MSG_TMP_DATA_RESULT_Succ;
	msg.CreateMsg(MSG_TMP_DATA_ACT_AckGetTmpData, nResult, idTmpData);
	for (int i = USERTMPDATA_INDEX_BEG; i < USERTMPDATA_INDEX_END; i++)
	{
		int nData = pUserTmpDataMgr->GetTmpData(idUser, idTmpData, (USERTMPDATA_INDEX)i);
		CHECK(msg.AppendParam(nData));
	}
	pUserMgr->SendMsg(idUser, &msg);
}

// 请求设置TmpData
void CMsgGameUserTmpData::ProcessReqSetTmpData(OBJID idUser)
{
	CHECK(idUser);
	OBJID idTmpData = m_pInfo->nTmpDataID;
	int nResult = MSG_TMP_DATA_RESULT_Succ;
	if (idTmpData < EUTDP_CLIENT_BEGIN || idTmpData > EUTDP_CLIENT_END)
	{
		nResult = MSG_TMP_DATA_RESULT_Beyond;
	}
	if (m_pInfo->nDataNum != (USERTMPDATA_INDEX_END - USERTMPDATA_INDEX_BEG))
	{
		nResult = MSG_TMP_DATA_RESULT_Error;
	}
	
	// 保存数据
	if (MSG_TMP_DATA_RESULT_Succ == nResult)
	{
		for (int i = USERTMPDATA_INDEX_BEG; i < USERTMPDATA_INDEX_END; i++)
		{
			bool bUpdate = (i == (USERTMPDATA_INDEX_END - 1)) ? true : false;
			pUserTmpDataMgr->SetTmpData(idUser, idTmpData, (USERTMPDATA_INDEX)i, m_pInfo->arrData[i], bUpdate);
		}
	}

	CMsgGameUserTmpData msg;
	msg.CreateMsg(MSG_TMP_DATA_ACT_AckSetTmpData, nResult, idTmpData);
	for (int i = USERTMPDATA_INDEX_BEG; i < USERTMPDATA_INDEX_END; i++)
	{
		int nData = pUserTmpDataMgr->GetTmpData(idUser, idTmpData, (USERTMPDATA_INDEX)i);
		CHECK(msg.AppendParam(nData));
	}
	pUserMgr->SendMsg(idUser, &msg);
}