////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan ChuangYou, All Rights Reserved
// Moudle: UserTmpData.cpp
// Author: ����(Ding Le)
// Created: 2014-11-7
////////////////////////////////////////////////////////////////////////
#include "./UserTmpData.h"
#include "./GameKernel.h"
MYHEAP_IMPLEMENTATION(CUserTmpData, s_heap);

//////////////////////////////////////////////////////////////////////////
CUserTmpData::CUserTmpData()
{
	m_idUser = ID_NONE;
	m_pDefaultRes = NULL;
}

//////////////////////////////////////////////////////////////////////////
CUserTmpData::~CUserTmpData()
{
	m_pDefaultRes = NULL;		// ��ָ���ɹ������ͷ�
	this->SaveAll();
	m_mapTmpData.clear();	// ����ָ��ֱ�����
}

////////////////////////////////////////////////////////////////////////
// Description:  ��ʼ��
bool CUserTmpData::Init(OBJID idUser, IRecordset* pDefaultRes)
{
	CHECKF(idUser);
	CHECKF(pDefaultRes);
	CHECKF(pGameDatabase);
	m_idUser = idUser;
	m_pDefaultRes = pDefaultRes;
	m_mapTmpData.clear();

	CMxyString strSql("SELECT * FROM %s WHERE user_id = %u LIMIT %d", GAME_DB_NAME_USER_TMP_DATA, idUser, MAX_LOAD_USER_TMP_DATA_COUNT);
	RecordsetPtr pRes = pGameDatabase->CreateNewRecordset(strSql.c_str());
	CHECKF(pRes);

	RecordPtr pRecord = NULL;
	OBJID idTmpDataID = ID_NONE;
	for(int i = 0; i < pRes->RecordCount(); i++, pRes->MoveNext())
	{
		
		idTmpDataID = pRes->GetInt(USERTMPDATA_TMP_DATA_ID);
		if (m_mapTmpData.find(idTmpDataID) != m_mapTmpData.end())
		{
			tolog3("CUserTmpData::Init() Repeat TmpData UserID[%u], TmpDataID[%u]", idUser, idTmpDataID);
			continue;
		}

		pRecord = pRes->CreateNewRecord();
		CHECKC(pRecord);
		m_mapTmpData[idTmpDataID] = pRecord;
	}
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description:  ����һ���¼�¼
bool CUserTmpData::Add(OBJID idTmpData)
{
	CHECKF(idTmpData && m_idUser);
	CHECKF(false == this->IsExist(idTmpData));
	CHECKF(m_pDefaultRes);

	RecordPtr pRecord = m_pDefaultRes->CreateNewRecord();
	CHECKF(pRecord);
	pRecord->SetInt(USERTMPDATA_USERID,			m_idUser);
	pRecord->SetInt(USERTMPDATA_TMP_DATA_ID,	idTmpData);
	for (int i = USERTMPDATA_DATA_BEGIN; i < USERTMPDATA_DATA_END; i++)
	{
		pRecord->SetInt((USERTMPDATA_DATA)i, 0);
	}

	CHECKF(pRecord->InsertRecord());
	m_mapTmpData[idTmpData] = pRecord;
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description:  ɾ��һ����¼
bool CUserTmpData::Del(OBJID idTmpData)
{
	CHECKF(idTmpData && m_idUser);
	CHECKF(true == this->IsExist(idTmpData));

	ITER_TABLE_DATA iter = m_mapTmpData.find(idTmpData);
	RecordPtr pRecord = iter->second;
	CHECKF(pRecord);
	CHECKF(pRecord->DeleteRecord(DBUPDATE_ASYNC));
	m_mapTmpData.erase(idTmpData);	// ����ָ��, ֱ��erase����
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description:  �ж��Ƿ������Ӧ��¼
bool CUserTmpData::IsExist	(OBJID idTmpData) const
{
	CHECKF(idTmpData && m_idUser);
	bool bResult = m_mapTmpData.find(idTmpData) != m_mapTmpData.end();
	return bResult;
}

////////////////////////////////////////////////////////////////////////
// Description:  ��������
bool CUserTmpData::SetData	(OBJID idTmpData, USERTMPDATA_DATA eIndex, int nData, DBUPDATE_TYPE eUpdateType)
{
	CHECKF(idTmpData && eIndex != USERTMPDATA_ERROR);
	CHECKF(true == this->IsExist(idTmpData));
	ITER_TABLE_DATA iter = m_mapTmpData.find(idTmpData);
	RecordPtr pRecord = iter->second;
	CHECKF(pRecord);
	pRecord->SetInt(eIndex, nData);
	if (eUpdateType == DBUPDATE_ASYNC || eUpdateType == DBUPDATE_SYNC)
	{
		pRecord->UpdateRecord(eUpdateType);
	}
	return true;
}


////////////////////////////////////////////////////////////////////////
// Description:  �������
int	 CUserTmpData::GetData(OBJID idTmpData, USERTMPDATA_DATA eIndex) const
{
	CHECKF(idTmpData && eIndex != USERTMPDATA_ERROR);
	CHECKF(true == this->IsExist(idTmpData));
	CITER_TABLE_DATA iter = m_mapTmpData.find(idTmpData);
	RecordPtr pRecord = iter->second;
	CHECKF(pRecord);
	return pRecord->GetInt(eIndex);
}

////////////////////////////////////////////////////////////////////////
// Description:  ������������
bool CUserTmpData::SaveAll	(void)
{
	CHECKF(m_idUser);

	RecordPtr pRecord = NULL;
	for (ITER_TABLE_DATA iter = m_mapTmpData.begin(); iter != m_mapTmpData.end(); ++iter)
	{
		pRecord = iter->second;
		CHECKC(pRecord);
		pRecord->UpdateRecord();	
	}
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description:  ����
bool CUserTmpData::Save(OBJID idTmpData)
{
	// �����ڵļ�¼������ǿյ�
	if (!this->IsExist(idTmpData))
	{
		return false;
	}
	ITER_TABLE_DATA iter = m_mapTmpData.find(idTmpData);
	RecordPtr pRecord = iter->second;
	CHECKF(pRecord);
	pRecord->UpdateRecord();
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description:  ��UserTmpData��0
void CUserTmpData::Reset(OBJID idTmpData, DBUPDATE_TYPE eUpdateType)
{
	// �����ڵļ�¼������ǿյ�
	if (!this->IsExist(idTmpData))
	{
		return;
	}
	ITER_TABLE_DATA iter = m_mapTmpData.find(idTmpData);
	RecordPtr pRecord = iter->second;
	CHECK(pRecord);
	pRecord->SetInt(USERTMPDATA_DATA0, 0);
	pRecord->SetInt(USERTMPDATA_DATA1, 0);
	pRecord->SetInt(USERTMPDATA_DATA2, 0);
	pRecord->SetInt(USERTMPDATA_DATA3, 0);
	pRecord->SetInt(USERTMPDATA_DATA4, 0);
	pRecord->SetInt(USERTMPDATA_DATA5, 0);
	pRecord->SetInt(USERTMPDATA_DATA6, 0);
	pRecord->SetInt(USERTMPDATA_DATA7, 0);
	if (eUpdateType == DBUPDATE_ASYNC || eUpdateType == DBUPDATE_SYNC)
	{
		pRecord->UpdateRecord(eUpdateType);
	}
}
