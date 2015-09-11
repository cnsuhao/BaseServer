////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan ChuangYou, All Rights Reserved
// Moudle: UserTmpDataMgr.cpp
// Author: 丁乐(Ding Le)
// Created: 2014-11-7
////////////////////////////////////////////////////////////////////////
#include "./UserTmpDataMgr.h"
#include "./UserTmpData.h"
#include "./GameKernel.h"
#include "./Network/MsgGameUserTmpData.h"
#include "./UserMgr.h"

CUserTmpDataMgr* CUserTmpDataMgr::s_pInstance = NULL;
MYHEAP_IMPLEMENTATION(CUserTmpDataMgr, s_heap);

bool CUserTmpDataMgr::Init()
{
	CHECKF(pGameDatabase);
	m_pDefaultres = pGameDatabase->CreateDefaultRecordset(GAME_DB_NAME_USER_TMP_DATA);
	CHECKF(m_pDefaultres);
	return true;
}

void CUserTmpDataMgr::Release()
{
	for (ITER_MAP_USER_TMP_DATA iter = m_mapUserTmpData.begin(); iter != m_mapUserTmpData.end(); iter++)
	{
		SAFE_RELEASE(iter->second);
	}
	m_mapUserTmpData.clear();
	SAFE_RELEASE(m_pDefaultres);
}

////////////////////////////////////////////////////////////////////////
// 增加玩家
bool CUserTmpDataMgr::InitUser(OBJID idUser)
{
	CHECKF(idUser);
	CUserTmpData* pUserTmpData = CUserTmpData::CreateNew();
	CHECKF(pUserTmpData);
	if (!pUserTmpData->Init(idUser, m_pDefaultres))
	{
		SAFE_RELEASE(pUserTmpData);
		return false; 
	}
	if (false == m_mapUserTmpData.insert(make_pair(idUser, pUserTmpData)).second)
	{
		SAFE_RELEASE(pUserTmpData);
		return false;                                                                             
	}
	return true;
}

////////////////////////////////////////////////////////////////////////
// 删除玩家
bool CUserTmpDataMgr::ReleaseUser(OBJID idUser)
{
	CHECKF(idUser);
	CUserTmpData* pUserTmpData = this->GetUserTmpData(idUser);
	SAFE_RELEASE(pUserTmpData);
	m_mapUserTmpData.erase(idUser);
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description:  为user_tmp_data表设置一个数据, 如果不存在则自动创建
// nUpdateType
// false - DBUPDATE_FALSE	= 0,	// 不写库
// true  - DBUPDATE_ASYNC	= 1,	// 异步写库
// DBUPDATE_SYNC			= 2,	// 同步写库 
bool CUserTmpDataMgr::SetTmpData(OBJID idUser, OBJID idTmpData, USERTMPDATA_INDEX eIndex, int nData, int nUpdateType /*= DBUPDATE_ASYNC*/)
{
	CHECKF(idUser);
	CHECKF(idTmpData);
	CHECKF(eIndex >= USERTMPDATA_INDEX_BEG && eIndex < USERTMPDATA_INDEX_END);
	CUserTmpData* pUserTmpData = this->GetUserTmpData(idUser);
	CHECKF(pUserTmpData);
	
	if (false == pUserTmpData->IsExist(idTmpData))
	{
		CHECKF(pUserTmpData->Add(idTmpData));
	}
	return pUserTmpData->SetData(idTmpData, this->GetIndex(eIndex), nData, (DBUPDATE_TYPE)nUpdateType);
}

////////////////////////////////////////////////////////////////////////
// Description:  取user_tmp_data表值, 如果不存在直接返回0
int	CUserTmpDataMgr::GetTmpData(OBJID idUser, OBJID idTmpData, USERTMPDATA_INDEX eIndex) const
{
	CHECKF(idUser);
	CHECKF(idTmpData);
	CHECKF(eIndex >= USERTMPDATA_INDEX_BEG && eIndex < USERTMPDATA_INDEX_END);
	CUserTmpData* pUserTmpData = this->GetUserTmpData(idUser);
	CHECKF(pUserTmpData);

	CHECKF(idTmpData);
	int nResult = 0;
	if (pUserTmpData->IsExist(idTmpData))
	{
		nResult = pUserTmpData->GetData(idTmpData, this->GetIndex(eIndex));	
	}
	return nResult;
}

////////////////////////////////////////////////////////////////////////
// Description:  删除指定的数据
bool CUserTmpDataMgr::DelTmpData(OBJID idUser, OBJID idTmpData)
{
	CHECKF(idUser);
	CHECKF(idTmpData);
	CUserTmpData* pUserTmpData = this->GetUserTmpData(idUser);
	CHECKF(pUserTmpData);

	// 不存在数据直接返回成功, 给脚本直接调用的容错处理, 避免出日志
	if (!pUserTmpData->IsExist(idTmpData))
	{
		return true;
	}
	return pUserTmpData->Del(idTmpData);
}

////////////////////////////////////////////////////////////////////////
// 保存所有玩家的所有TmpData
void CUserTmpDataMgr::SaveAllUserTmpData(void)
{
	for (ITER_MAP_USER_TMP_DATA iter = m_mapUserTmpData.begin(); iter != m_mapUserTmpData.end(); iter++)
	{
		CUserTmpData* pUserTmpData = iter->second;
		CHECKC(pUserTmpData);
		pUserTmpData->SaveAll();
	}
}

////////////////////////////////////////////////////////////////////////
// 保存玩家的所有TmpData
bool CUserTmpDataMgr::SaveUserAllTmpData(OBJID idUser)
{
	CHECKF(idUser);
	CUserTmpData* pUserTmpData = this->GetUserTmpData(idUser);
	CHECKF(pUserTmpData);
	return pUserTmpData->SaveAll();
}

////////////////////////////////////////////////////////////////////////
// 保存某个玩家的TmpData
bool CUserTmpDataMgr::SaveUserTmpData(OBJID idUser, OBJID idTmpData)
{
	CHECKF(idUser);
	CHECKF(idTmpData);
	CUserTmpData* pUserTmpData = this->GetUserTmpData(idUser);
	CHECKF(pUserTmpData);
	return pUserTmpData->Save(idTmpData);
}

////////////////////////////////////////////////////////////////////////
// Description:  用掩码方式设值
bool CUserTmpDataMgr::SetTmpDataMask(OBJID idUser, OBJID idTmpData, USERTMPDATA_INDEX eIndex, int nMaskIndex, int nUpdateType/* = DBUPDATE_ASYNC*/)
{
	CHECKF(idUser);
	CHECKF(idTmpData);
	CHECKF(eIndex >= USERTMPDATA_INDEX_BEG && eIndex < USERTMPDATA_INDEX_END);
	CHECKF(nMaskIndex >= 0 && nMaskIndex < (sizeof(int) * 8));
	CUserTmpData* pUserTmpData = this->GetUserTmpData(idUser);
	CHECKF(pUserTmpData);

	const int nMask		= 1 << nMaskIndex;
	const int nOldData  = this->GetTmpData(idUser, idTmpData, eIndex);
	const int nNewData  = nOldData | nMask;
	return this->SetTmpData(idUser, idTmpData, eIndex, nNewData, nUpdateType);
}

////////////////////////////////////////////////////////////////////////
// Description:  用掩码方式清除
bool CUserTmpDataMgr::ClrTmpDataMask(OBJID idUser, OBJID idTmpData, USERTMPDATA_INDEX eIndex, int nMaskIndex, int nUpdateType /*= DBUPDATE_ASYNC*/)
{
	CHECKF(idUser);
	CHECKF(idTmpData);
	CHECKF(eIndex >= USERTMPDATA_INDEX_BEG && eIndex < USERTMPDATA_INDEX_END);
	CHECKF(nMaskIndex >= 0 && nMaskIndex < (sizeof(int) * 8));
	CUserTmpData* pUserTmpData = this->GetUserTmpData(idUser);
	CHECKF(pUserTmpData);

	const int nMask		= 1 << nMaskIndex;
	const int nOldData	= this->GetTmpData(idUser, idTmpData, eIndex);
	const int nNewData	= nOldData & (~nMask);
	return this->SetTmpData(idUser, idTmpData, eIndex, nNewData, nUpdateType);
}

////////////////////////////////////////////////////////////////////////
// Description:  用掩码方式检查
bool CUserTmpDataMgr::ChkTmpDataMask(OBJID idUser, OBJID idTmpData, USERTMPDATA_INDEX eIndex, int nMaskIndex) const
{
	CHECKF(idUser);
	CHECKF(idTmpData);
	CHECKF(eIndex >= USERTMPDATA_INDEX_BEG && eIndex < USERTMPDATA_INDEX_END);
	CHECKF(nMaskIndex >= 0 && nMaskIndex < (sizeof(int) * 8));
	CUserTmpData* pUserTmpData = this->GetUserTmpData(idUser);
	CHECKF(pUserTmpData);

	const int	nMask	= 1 << nMaskIndex;
	const int	nData	= this->GetTmpData(idUser, idTmpData, eIndex);
	const bool	bResult = (nData & nMask) != 0;
	return bResult;
}

////////////////////////////////////////////////////////////////////////
// Description:  获取玩家TmpData指针
CUserTmpData* CUserTmpDataMgr::GetUserTmpData(OBJID idUser) const
{
	CHECKF(idUser);
	CITER_MAP_USER_TMP_DATA iter = m_mapUserTmpData.find(idUser);
	if (iter == m_mapUserTmpData.end())
	{
		return NULL;
	}
	return iter->second;
}

////////////////////////////////////////////////////////////////////////
// Description:  检查玩家的TmpData是否存在
bool CUserTmpDataMgr::IsUserTmpDataExist(OBJID idUser, OBJID idTmpData) const
{
	CHECKF(idUser);
	CHECKF(idTmpData);
	CUserTmpData* pUserTmpData = this->GetUserTmpData(idUser);
	CHECKF_NOLOG(pUserTmpData);
	return pUserTmpData->IsExist(idTmpData);
}

////////////////////////////////////////////////////////////////////////
// Description:  将UserTmpData置0
void CUserTmpDataMgr::Reset(OBJID idUser, OBJID idTmpData, int nUpdateType)
{
	CHECK(idUser);
	CHECK(idTmpData);
	CUserTmpData* pUserTmpData = this->GetUserTmpData(idUser);
	CHECK(pUserTmpData);
	pUserTmpData->Reset(idTmpData, (DBUPDATE_TYPE)nUpdateType);
}

////////////////////////////////////////////////////////////////////////
// Description:  index转换
USERTMPDATA_DATA CUserTmpDataMgr::GetIndex(UCHAR ucIndex) const
{
	if (ucIndex > USERTMPDATA_DATA_END - USERTMPDATA_DATA_BEGIN)
	{
		return USERTMPDATA_ERROR;
	}
	return (USERTMPDATA_DATA)(ucIndex + USERTMPDATA_DATA_BEGIN);
}

////////////////////////////////////////////////////////////////////////
// Description:  向客户端同步TmpData
void CUserTmpDataMgr::UpdateUserTmpData(OBJID idUser, OBJID idTmpData)
{
	CHECK(idUser);
	CHECK(idTmpData);

	CMsgGameUserTmpData msg;
	int nResult = MSG_TMP_DATA_RESULT_Succ;
	msg.CreateMsg(MSG_TMP_DATA_ACT_UpdateTmpData, nResult, idTmpData);
	for (int i = USERTMPDATA_INDEX_BEG; i < USERTMPDATA_INDEX_END; i++)
	{
		int nData = this->GetTmpData(idUser, idTmpData, (USERTMPDATA_INDEX)i);
		CHECK(msg.AppendParam(nData));
	}
	pUserMgr->SendMsg(idUser, &msg);
}

////////////////////////////////////////////////////////////////////////
// Description:  向客户端同步所有自定义TmpData
void CUserTmpDataMgr::ProcessQueryClientTmpData(OBJID idUser)
{
	CHECK(idUser);

	CMsgGameUserTmpData msg;
	int nResult = MSG_TMP_DATA_RESULT_Succ;
	msg.CreateMsg(MSG_TMP_DATA_ACT_AckClientTmpData, nResult);
	for (int nTmpDataID = EUTDP_CLIENT_BEGIN; nTmpDataID <= EUTDP_CLIENT_END; nTmpDataID++)
	{
		INT_VEC vecInt;
		CHECKC_NOLOG(this->IsUserTmpDataExist(idUser, nTmpDataID));
		vecInt.push_back(nTmpDataID);
		for (int j = USERTMPDATA_INDEX_BEG; j < USERTMPDATA_INDEX_END; j++)
		{
			vecInt.push_back(this->GetTmpData(idUser, nTmpDataID, (USERTMPDATA_INDEX)j));
		}
		if (!msg.AppendTmpData(vecInt))
		{
			pUserMgr->SendMsg(idUser, &msg);
			CHECK(msg.CreateMsg(MSG_TMP_DATA_ACT_AckClientTmpData, nResult));
			CHECK(msg.AppendTmpData(vecInt));
		}
	}
	msg.SetMsgEnd();
	pUserMgr->SendMsg(idUser, &msg);
}
