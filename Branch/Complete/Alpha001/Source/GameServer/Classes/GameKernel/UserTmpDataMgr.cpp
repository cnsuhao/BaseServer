////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan ChuangYou, All Rights Reserved
// Moudle: UserTmpDataMgr.cpp
// Author: ����(Ding Le)
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
// �������
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
// ɾ�����
bool CUserTmpDataMgr::ReleaseUser(OBJID idUser)
{
	CHECKF(idUser);
	CUserTmpData* pUserTmpData = this->GetUserTmpData(idUser);
	SAFE_RELEASE(pUserTmpData);
	m_mapUserTmpData.erase(idUser);
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description:  Ϊuser_tmp_data������һ������, ������������Զ�����
// nUpdateType
// false - DBUPDATE_FALSE	= 0,	// ��д��
// true  - DBUPDATE_ASYNC	= 1,	// �첽д��
// DBUPDATE_SYNC			= 2,	// ͬ��д�� 
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
// Description:  ȡuser_tmp_data��ֵ, ���������ֱ�ӷ���0
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
// Description:  ɾ��ָ��������
bool CUserTmpDataMgr::DelTmpData(OBJID idUser, OBJID idTmpData)
{
	CHECKF(idUser);
	CHECKF(idTmpData);
	CUserTmpData* pUserTmpData = this->GetUserTmpData(idUser);
	CHECKF(pUserTmpData);

	// ����������ֱ�ӷ��سɹ�, ���ű�ֱ�ӵ��õ��ݴ���, �������־
	if (!pUserTmpData->IsExist(idTmpData))
	{
		return true;
	}
	return pUserTmpData->Del(idTmpData);
}

////////////////////////////////////////////////////////////////////////
// ����������ҵ�����TmpData
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
// ������ҵ�����TmpData
bool CUserTmpDataMgr::SaveUserAllTmpData(OBJID idUser)
{
	CHECKF(idUser);
	CUserTmpData* pUserTmpData = this->GetUserTmpData(idUser);
	CHECKF(pUserTmpData);
	return pUserTmpData->SaveAll();
}

////////////////////////////////////////////////////////////////////////
// ����ĳ����ҵ�TmpData
bool CUserTmpDataMgr::SaveUserTmpData(OBJID idUser, OBJID idTmpData)
{
	CHECKF(idUser);
	CHECKF(idTmpData);
	CUserTmpData* pUserTmpData = this->GetUserTmpData(idUser);
	CHECKF(pUserTmpData);
	return pUserTmpData->Save(idTmpData);
}

////////////////////////////////////////////////////////////////////////
// Description:  �����뷽ʽ��ֵ
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
// Description:  �����뷽ʽ���
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
// Description:  �����뷽ʽ���
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
// Description:  ��ȡ���TmpDataָ��
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
// Description:  �����ҵ�TmpData�Ƿ����
bool CUserTmpDataMgr::IsUserTmpDataExist(OBJID idUser, OBJID idTmpData) const
{
	CHECKF(idUser);
	CHECKF(idTmpData);
	CUserTmpData* pUserTmpData = this->GetUserTmpData(idUser);
	CHECKF_NOLOG(pUserTmpData);
	return pUserTmpData->IsExist(idTmpData);
}

////////////////////////////////////////////////////////////////////////
// Description:  ��UserTmpData��0
void CUserTmpDataMgr::Reset(OBJID idUser, OBJID idTmpData, int nUpdateType)
{
	CHECK(idUser);
	CHECK(idTmpData);
	CUserTmpData* pUserTmpData = this->GetUserTmpData(idUser);
	CHECK(pUserTmpData);
	pUserTmpData->Reset(idTmpData, (DBUPDATE_TYPE)nUpdateType);
}

////////////////////////////////////////////////////////////////////////
// Description:  indexת��
USERTMPDATA_DATA CUserTmpDataMgr::GetIndex(UCHAR ucIndex) const
{
	if (ucIndex > USERTMPDATA_DATA_END - USERTMPDATA_DATA_BEGIN)
	{
		return USERTMPDATA_ERROR;
	}
	return (USERTMPDATA_DATA)(ucIndex + USERTMPDATA_DATA_BEGIN);
}

////////////////////////////////////////////////////////////////////////
// Description:  ��ͻ���ͬ��TmpData
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
// Description:  ��ͻ���ͬ�������Զ���TmpData
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
