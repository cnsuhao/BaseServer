////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan ChuangYou, All Rights Reserved
// Moudle: MaskMgr.cpp
// Author: �½���(Chen Jianjun)
// Created: 2014-11-6
////////////////////////////////////////////////////////////////////////
#include "./MaskMgr.h"
#include "./UserMask.h"
#include "./GameKernel.h"
#include "./Network/MsgGameMask.h"
#include "./UserMgr.h"

CMaskMgr* CMaskMgr::s_pInstance = NULL;
MYHEAP_IMPLEMENTATION(CMaskMgr, s_heap);

////////////////////////////////////////////////////////////////////////
// Description: ��������ʼ��
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool CMaskMgr::Init()
{
	DEBUG_TRY;
	CHECKF(pGameDatabase);
	m_pUserMaskDefaultRes = pGameDatabase->CreateDefaultRecordset(GAME_DB_NAME_USER_MASK);
	CHECKF(m_pUserMaskDefaultRes);
	m_mapUserMask.clear();
	return true;
	DEBUG_CATCHF("CMaskMgr::Init()");
}

////////////////////////////////////////////////////////////////////////
// Description: �������ͷ�
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value: None
////////////////////////////////////////////////////////////////////////
void CMaskMgr::Release()
{
	DEBUG_TRY;
	SAFE_RELEASE(m_pUserMaskDefaultRes);
	for (MAP_USER_MASK::iterator iter = m_mapUserMask.begin(); iter != m_mapUserMask.end(); iter++)
	{
		SAFE_RELEASE(iter->second);
	}
	m_mapUserMask.clear();				// ����ָ��, ֱ��clear����
	DEBUG_CATCH("CMaskMgr::Release()");
}
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
// Description: ��ȡ����������
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value: UINT
////////////////////////////////////////////////////////////////////////
UINT CMaskMgr::GetGroupServerMask(OBJID idGroup, OBJID idMask)
{
	DEBUG_TRY;
	CHECKF(idGroup);
	CHECKF(idMask);
	CHECKF(pGameDatabase);
	
	UINT unMaskData = 0;
	CMxyString strSql("select * from %s where id = %u and server_group = %d limit 1", GAME_DB_NAME_GROUP_MASK, idMask, idGroup);
	RecordsetPtr pRes = pGameDatabase->CreateNewRecordset(strSql.c_str());
	if (pRes && pRes->RecordCount() > 0)
	{
		UINT unEndTime = pRes->GetInt(LINE_MASK_DATA_ENDTIME);

		if ((::TimeGet(TIME_SECOND)) <= unEndTime)	// ���ʱ���Ƿ����
		{
			unMaskData = pRes->GetInt(LINE_MASK_DATA_DATA);
		}
	}

	return unMaskData;
	DEBUG_CATCHF3("CMaskMgr::GetGroupServerMask idGroup[%u], idMask[%u]", idGroup, idMask);
}

////////////////////////////////////////////////////////////////////////
// Description: ��������������
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool CMaskMgr::SetGroupServerMask(OBJID idGroup, OBJID idMask, UINT unData, UINT unEndTime)
{
	DEBUG_TRY;
	CHECKF(idGroup);
	CHECKF(idMask);
	CHECKF(unEndTime);
	CHECKF(pGameDatabase);

	CMxyString strSql("replace into %s values(%u, %d, %u, %u)", GAME_DB_NAME_GROUP_MASK, idMask, idGroup, unData,  unEndTime);
	return pGameDatabase->ExecuteSQL(strSql.c_str());

	DEBUG_CATCHF5("CMaskMgr::SetGroupServerMask idGroup[%u] idMask[%u] data[%d] endTime[%u]", idGroup, idMask, unData, unEndTime);
}

////////////////////////////////////////////////////////////////////////
// Description: ������Ч������������
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value: None
////////////////////////////////////////////////////////////////////////
void CMaskMgr::ClearInvalidGroupServerMask(void)
{
	DEBUG_TRY;
	CHECK(pGameDatabase);

	UINT unCurTime = ::TimeGet(TIME_SECOND);
	CMxyString strSql("delete from %s where endtime < %d", GAME_DB_NAME_GROUP_MASK, unCurTime);
	pGameDatabase->ExecuteSQL(strSql.c_str());
	DEBUG_CATCH("CMaskMgr::ClearInvalidGroupServerMask");
}
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
// Description: ��ȡ������������
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value: UINT
////////////////////////////////////////////////////////////////////////
UINT CMaskMgr::GetWorldServerMask(OBJID idMask)
{
	DEBUG_TRY;
	CHECKF(idMask);
	CHECKF(pGameDatabase);

	UINT unMaskData = 0;
	CMxyString strSql("select * from %s where id = %u limit 1", GAME_DB_NAME_WORLD_MASK, idMask);
	RecordsetPtr pRes = pGameDatabase->CreateNewRecordset(strSql.c_str());
	if (pRes && pRes->RecordCount() > 0)
	{
		UINT unEndTime = pRes->GetInt(SERVER_MASK_DATA_ENDTIME);

		if ((::TimeGet(TIME_SECOND)) <= unEndTime)	// ���ʱ���Ƿ����
		{
			unMaskData = pRes->GetInt(SERVER_MASK_DATA_DATA);
		}
	}

	return unMaskData;
	DEBUG_CATCHF2("CMaskMgr::GetWorldServerMask idMask[%u]", idMask);
}

////////////////////////////////////////////////////////////////////////
// Description: ����������������
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool CMaskMgr::SetWorldServerMask(OBJID idMask, UINT unData, UINT unEndTime)
{
	DEBUG_TRY;
	CHECKF(idMask);
	CHECKF(unEndTime);
	CHECKF(pGameDatabase);

	CMxyString strSql("replace into %s values(%u, %d, %u)", GAME_DB_NAME_WORLD_MASK, idMask, unData, unEndTime);
	return pGameDatabase->ExecuteSQL(strSql.c_str());

	DEBUG_CATCHF4("CMaskMgr::SetWorldServerMask idMask[%u] undata[%u] endTime[%u]", idMask, unData, unEndTime);
}

////////////////////////////////////////////////////////////////////////
// Description: ������Ч��������������
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value: None
////////////////////////////////////////////////////////////////////////
void CMaskMgr::ClearInvalidWorldServerMask(void)
{
	DEBUG_TRY;
	CHECK(pGameDatabase);

	UINT unCurTime = ::TimeGet(TIME_SECOND);
	CMxyString strSql("delete from %s where endtime < %d", GAME_DB_NAME_WORLD_MASK, unCurTime);
	pGameDatabase->ExecuteSQL(strSql.c_str());
	DEBUG_CATCH("CMaskMgr::ClearInvalidWorldServerMask");
}
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
// Description: ��ɫ��ʼ��
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool CMaskMgr::InitUser( OBJID idUser)
{
	DEBUG_TRY;
	CHECKF(idUser);

	CUserMask* pUserMask = CUserMask::CreateNew();
	CHECKF(pUserMask);
	if (false == pUserMask->Init(idUser, m_pUserMaskDefaultRes))
	{
		tolog2("CMaskMgr::InitUser faild! idUser[%d]", idUser);
		return false;
	}

	m_mapUserMask[idUser] = pUserMask;

	return true;
	DEBUG_CATCHF2("CMaskMgr::InitUser idUser[%u]", idUser);
}

////////////////////////////////////////////////////////////////////////
// Description: ��ɫ����
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool CMaskMgr::ReleaseUser( OBJID idUser )
{
	DEBUG_TRY;
	CHECKF(idUser);
	MAP_USER_MASK::iterator iter = m_mapUserMask.find(idUser);
	CHECKF(iter != m_mapUserMask.end());
	SAFE_RELEASE(iter->second);	
	m_mapUserMask.erase(iter);
	return true;
	DEBUG_CATCHF2("CMaskMgr::ReleaseUser idUser[%u]", idUser);
}

////////////////////////////////////////////////////////////////////////
// Description: ���������
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value: CUserMask*
////////////////////////////////////////////////////////////////////////
CUserMask* CMaskMgr::GetUserMask( OBJID idUser ) const
{
	DEBUG_TRY;
	CHECKF(idUser);
	MAP_USER_MASK::const_iterator iter = m_mapUserMask.find(idUser);
	CHECKF(iter != m_mapUserMask.end());
	return iter->second;
	DEBUG_CATCHF2("CMaskMgr::GetUserMask idUser[%u]", idUser);
}

////////////////////////////////////////////////////////////////////////
// Description: ��ȡ��������
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value: I64
////////////////////////////////////////////////////////////////////////
I64	CMaskMgr::GetUserMaskData(OBJID idUser, EUSERMASKTYPE unMaskType, OBJID idMask)
{
	DEBUG_TRY;
	CHECKF(idUser);
	CHECKF(unMaskType > EUMT_Begin && unMaskType < EUMT_End);
	CUserMask* pMask = this->GetUserMask(idUser);
	CHECKF(pMask);

	I64 i64Result = 0i64;
	if (pMask->IsExist(unMaskType, idMask))
	{
		i64Result = pMask->GetData(unMaskType, idMask);
	}

	return i64Result;
	DEBUG_CATCHF4("CMaskMgr::GetUserMaskData idUser[%u], unMaskType[%u], idMask[%u]", idUser, unMaskType, idMask);
}

////////////////////////////////////////////////////////////////////////
// Description: ������������
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool CMaskMgr::SetUserMaskData(OBJID idUser, EUSERMASKTYPE unMaskType, OBJID idMask, I64 i64Data, UINT unEndTime)
{
	DEBUG_TRY;
	CHECKF(idUser);
	CHECKF(unMaskType > EUMT_Begin && unMaskType < EUMT_End);
	CUserMask* pMask = this->GetUserMask(idUser);
	CHECKF(pMask);

	if (false == pMask->IsExist(unMaskType, idMask))
	{
		CHECKF(pMask->Add(unMaskType, idMask));		// �Զ������¼�¼
	}

	bool bResult = pMask->SetData(unMaskType, idMask, unEndTime, i64Data);
	if (bResult)
	{
		this->SynOneMaskDataInfo(idUser, unMaskType, idMask);
	}
	return bResult;
	DEBUG_CATCHF4("CMaskMgr::SetUserMaskData idUser[%u], unMaskType[%u], idMask[%u]", idUser, unMaskType, idMask);
}

////////////////////////////////////////////////////////////////////////
// Description: �����������
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool CMaskMgr::ChkUserMaskData(OBJID idUser, EUSERMASKTYPE unMaskType, OBJID idMask, int nIdx)
{
	DEBUG_TRY;
	CHECKF(idUser);
	CHECKF(unMaskType > EUMT_Begin && unMaskType < EUMT_End);
	CUserMask* pMask = this->GetUserMask(idUser);
	CHECKF(pMask);
	
	bool bResult = false;
	I64 i64MaskData = pMask->GetData(unMaskType, idMask);
	if (idMask >= CONST_COMPUTATION_MASKID_BEGIN) // ��������
	{
		bResult = i64MaskData > 0;
	}
	else
	{	
		CHECKF(nIdx >= 0 && nIdx < 64);			 // ��ֵ���
		bResult = (i64MaskData & (1i64 << nIdx)) != 0;
	}

	return bResult;
	DEBUG_CATCHF5("CMaskMgr::ChkUserMaskData idUser[%u], unMaskType[%u], idMask[%u], nIdx[%d]", idUser, unMaskType, idMask, nIdx);
}

////////////////////////////////////////////////////////////////////////
// Description: �����������
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool CMaskMgr::AddUserMaskData(OBJID idUser, EUSERMASKTYPE unMaskType, OBJID idMask, int nIdx, UINT unEndTime)
{
	DEBUG_TRY;
	CHECKF(idUser);
	CHECKF(unMaskType > EUMT_Begin && unMaskType < EUMT_End);
	CUserMask* pMask = this->GetUserMask(idUser);
	CHECKF(pMask);
	
	I64 i64MaskData = pMask->GetData(unMaskType, idMask);
	if (idMask >= CONST_COMPUTATION_MASKID_BEGIN) // ��������
	{
		i64MaskData += nIdx;
	}
	else
	{
		CHECKF(nIdx >= 0 && nIdx < 64);			 // ��ֵ���
		i64MaskData = i64MaskData | (1i64 << nIdx);
	}

	if (!pMask->IsExist(unMaskType, idMask))
	{
		CHECKF(pMask->Add(unMaskType, idMask));	// �Զ������¼�¼
	}

	bool bResult = pMask->SetData(unMaskType, idMask, unEndTime, i64MaskData);
	if (bResult)
	{
		this->SynOneMaskDataInfo(idUser, unMaskType, idMask);
	}
	return bResult;
	DEBUG_CATCHF5("CMaskMgr::AddUserMaskData idUser[%u], unMaskType[%u], idMask[%u], nIdx[%d]", idUser, unMaskType, idMask, nIdx);
}

////////////////////////////////////////////////////////////////////////
// Description: ������������
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value: None
////////////////////////////////////////////////////////////////////////
bool CMaskMgr::ClrUserMaskData(OBJID idUser, EUSERMASKTYPE unMaskType, OBJID idMask, int nIdx)
{
	DEBUG_TRY;
	CHECKF(idUser);
	CHECKF(unMaskType > EUMT_Begin && unMaskType < EUMT_End);
	CUserMask* pMask = this->GetUserMask(idUser);
	CHECKF(pMask);

	if (!pMask->IsExist(unMaskType, idMask))
	{
		return true;								// ����������ֱ�ӷ��سɹ�
	}
	
	I64 i64MaskData = pMask->GetData(unMaskType, idMask);
	if (idMask >= CONST_COMPUTATION_MASKID_BEGIN)	// ��������
	{
		i64MaskData = 0;
	}
	else
	{
		CHECKF(nIdx >= 0 && nIdx < 64);				// ��ֵ���
		i64MaskData &= ~(1i64 << nIdx);
	}

	bool bResult = pMask->SetData(unMaskType, idMask, 0, i64MaskData);
	if (bResult)
	{
		this->SynOneMaskDataInfo(idUser, unMaskType, idMask);
	}
	return bResult;
	DEBUG_CATCHF5("CMaskMgr::ClrUserMaskData idUser[%u], unMaskType[%u], idMask[%u], nIdx[%d]", idUser, unMaskType, idMask, nIdx);
}

////////////////////////////////////////////////////////////////////////
// Description: ������������
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool CMaskMgr::ResetUserMaskData(OBJID idUser, EUSERMASKTYPE unMaskType, OBJID idMask)
{
	DEBUG_TRY;
	CHECKF(idUser);
	CHECKF(unMaskType > EUMT_Begin && unMaskType < EUMT_End);
	CUserMask* pMask = this->GetUserMask(idUser);
	CHECKF(pMask);

	if (!pMask->IsExist(unMaskType, idMask))
	{
		return true;			// ����������ֱ�ӷ��سɹ�
	}

	bool bResult = pMask->Reset(unMaskType, idMask);

	if (bResult)
	{
		this->SynOneMaskDataInfo(idUser, unMaskType, idMask);
	}

	return bResult;
	DEBUG_CATCHF4("CMaskMgr::ResetUserMaskData idUser[%u], unMaskType[%u], idMask[%u]", idUser, unMaskType, idMask);
}

////////////////////////////////////////////////////////////////////////
// Description: ɾ����������
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool CMaskMgr::DelUserMaskData(OBJID idUser, EUSERMASKTYPE unMaskType, OBJID idMask)
{
	DEBUG_TRY;
	CHECKF(idUser);
	CHECKF(unMaskType > EUMT_Begin && unMaskType < EUMT_End);
	CUserMask* pMask = this->GetUserMask(idUser);
	CHECKF(pMask);
	
	if (!pMask->IsExist(unMaskType, idMask))
	{
		return true;			// ����������ֱ�ӷ��سɹ�
	}

	bool bResult = pMask->Del(unMaskType, idMask);

	if (bResult)
	{
		this->SynOneMaskDataInfo(idUser, unMaskType, idMask);
	}

	return bResult;
	DEBUG_CATCHF4("CMaskMgr::DelUserMaskData idUser[%u], unMaskType[%u], idMask[%u]", idUser, unMaskType, idMask);
}

////////////////////////////////////////////////////////////////////////
// Description: ͬ��һ����������
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
void CMaskMgr::SynOneMaskDataInfo(OBJID idUser, EUSERMASKTYPE unMaskType, OBJID idMask)
{
	DEBUG_TRY;
	CHECK(idUser);
	CHECK(unMaskType > EUMT_Begin && unMaskType < EUMT_End);
	auto pMask = this->GetUserMask(idUser);
	CHECK(pMask);

	auto nData    = 0i64;
	auto nEndTime = 0;
	if (pMask->IsExist(unMaskType, idMask))
	{
		nData     = pMask->GetData(unMaskType, idMask);
		nEndTime  = pMask->GetMaskClearTime(unMaskType, idMask);
	}

	CMsgGameMask msg;
	msg.CreateMsg(idUser, unMaskType, idMask, nEndTime, nData);
	pUserMgr->SendMsg(idUser, &msg);
	DEBUG_CATCH4("CMaskMgr::SynOneMaskDataInfo idUser[%u], unMaskType[%u], idMask[%u]", idUser, unMaskType, idMask);
}

////////////////////////////////////////////////////////////////////////
// Description: ͬ����������
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
void CMaskMgr::SynAllUserMaskData(OBJID idUser)
{
	DEBUG_TRY;
	CHECK(idUser);
	CUserMask* pMask = this->GetUserMask(idUser);
	CHECK(pMask);
	pMask->SynAllMaskData();
	DEBUG_CATCH2("CMaskMgr::SynAllUserMaskData idUser[%u]", idUser);
}
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
// Description: ��ȡ���뱻���ϵĸ�������������1������
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value: int
////////////////////////////////////////////////////////////////////////
int CMaskMgr::GetMaskDataBitCount(OBJID idUser, EUSERMASKTYPE unMaskType, OBJID idMask, int nEndIndex/* = 64*/)
{
	DEBUG_TRY;
	CHECKF(idUser);
	CHECKF(unMaskType > EUMT_Begin && unMaskType < EUMT_End);
	CHECKF(nEndIndex > 0 && nEndIndex <= 64);
	I64 i64MaskData = this->GetUserMaskData(idUser, unMaskType, idMask);
	return ::bit_i64_count(i64MaskData, nEndIndex);
	DEBUG_CATCHF("CMaskMgr::GetMaskDataBitCount Crash!");
}
////////////////////////////////////////////////////////////////////////