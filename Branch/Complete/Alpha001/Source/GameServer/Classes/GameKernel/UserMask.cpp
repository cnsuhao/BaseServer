////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan ChuangYou, All Rights Reserved
// Moudle: UserMask.cpp
// Author: �½���(Chen Jianjun)
// Created: 2014-11-6
////////////////////////////////////////////////////////////////////////
#include "UserMask.h"
#include "./GameKernel.h"
#include "./UserMgr.h"
#include "./Network/MsgGameMask.h"

MYHEAP_IMPLEMENTATION(CUserMask, s_heap);
//////////////////////////////////////////////////////////////////////////
CUserMask::~CUserMask()
{
	DEBUG_TRY;
	if (ID_NONE == m_idUser)
	{
		return;						// ���δ��ʼ����ֱ�ӷ���
	}

	this->SaveAll();
	m_mapUserMaskData.clear();		// ����ָ��, ֱ��clear����
	DEBUG_CATCH2("CUserMask::Release idUser[%u]", m_idUser);
}

////////////////////////////////////////////////////////////////////////
// Description:  ��ʼ��
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool CUserMask::Init(OBJID idUser, IRecordset* pDefaultRes)
{
	DEBUG_TRY;
	CHECKF(idUser);
	CHECKF(pDefaultRes);
	m_idUser = idUser;
	m_mapUserMaskData.clear();
	CHECKF(pGameDatabase);

	m_pDefaultRes = pDefaultRes;

	CMxyString strSql("select * from %s where userid = %u", GAME_DB_NAME_USER_MASK, m_idUser);
	RecordsetPtr pRes = pGameDatabase->CreateNewRecordset(strSql.c_str());
	CHECKF(pRes);

	for (int i = 0; i < pRes->RecordCount(); i++, pRes->MoveNext())
	{
		RecordPtr pRecord = pRes->CreateNewRecord();
		CHECKC(pRecord);
		UINT unMaskType = pRecord->GetInt(USER_MASK_DATA_MASKTYPE);
		CHECKC(unMaskType > EUMT_Begin && unMaskType < EUMT_End);

		MAP_USERMASKDATA::iterator iter = m_mapUserMaskData.find(unMaskType);
		if (iter != m_mapUserMaskData.end())
		{
			MAP_MASKDATA& mapMaskData = iter->second;
			OBJID idMask = pRecord->GetInt(USER_MASK_DATA_MASKID);
			mapMaskData[idMask] = pRecord;
		}
		else
		{
			MAP_MASKDATA mapMaskData;
			OBJID idMask = pRecord->GetInt(USER_MASK_DATA_MASKID);
			mapMaskData[idMask] = pRecord;
			m_mapUserMaskData[unMaskType] = mapMaskData;
		}
	}

	return true;
	DEBUG_CATCHF2("CUserMask::Init idUser[%u]", idUser);
}

////////////////////////////////////////////////////////////////////////
// Description:  ��ȡ����
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value: i64
////////////////////////////////////////////////////////////////////////
I64	CUserMask::GetData (EUSERMASKTYPE unMaskType, OBJID idMask)
{
	DEBUG_TRY;
	CHECKF(unMaskType > EUMT_Begin && unMaskType < EUMT_End);
	
	I64 i64MaskData = 0i64;

	// ��������¼�Ƿ����
	RecordPtr pRecord = this->GetMaskRecord(unMaskType, idMask);
	if (!pRecord)
	{
		return i64MaskData;
	}

	// ��������Ƿ����
	UINT unClearTime = pRecord->GetInt(USER_MASK_DATA_CLEARTIME);
	switch(unMaskType)
	{
	case EUMT_DayMask:			// ������
		{
			if (unClearTime == (::TimeGet(TIME_DAY)))
			{
				i64MaskData = pRecord->GetInt64(USER_MASK_DATA_MASKDATA);
			}
		}
		break;
	case EUMT_WeekMask:			// ������
		{
			if (unClearTime == (::TimeGet(TIME_WEEK_END)))
			{
				i64MaskData = pRecord->GetInt64(USER_MASK_DATA_MASKDATA);
			}
		}
		break;
	case EUMT_MonthMask:		// ������
		{
			if (unClearTime == (::TimeGet(TIME_MONTH_END)))
			{
				i64MaskData = pRecord->GetInt64(USER_MASK_DATA_MASKDATA);
			}
		}
		break;
	default:					// ������������
		{
			if (CONST_DEFULT_MASK_ENDTIME == unClearTime || unClearTime > (::TimeGet(TIME_SECOND)))
			{
				i64MaskData = pRecord->GetInt64(USER_MASK_DATA_MASKDATA);
			}
		}
		break;
	}

	return i64MaskData;
	DEBUG_CATCHF4("CUserMask::GetData idUser[%u], unMaskType[%u], idMask[%u]", m_idUser, unMaskType, idMask);
}

////////////////////////////////////////////////////////////////////////
// Description:  ��������
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool CUserMask::SetData	(EUSERMASKTYPE unMaskType, OBJID idMask, UINT unEndTime, I64 i64Data, bool bUpdate/* = true*/, int nType/* = DBUPDATE_ASYNC*/)
{
	DEBUG_TRY;
	CHECKF(unMaskType > EUMT_Begin && unMaskType < EUMT_End);
	RecordPtr pRecord = this->GetMaskRecord(unMaskType, idMask);
	CHECKF(pRecord);

	// ���ʱ���Ƿ����
	UINT unClearTime = pRecord->GetInt(USER_MASK_DATA_CLEARTIME);
	bool bResetClearTime = false;
	switch(unMaskType)
	{
	case EUMT_DayMask:			// ������
		{
			unEndTime = ::TimeGet(TIME_DAY);
			if (unClearTime != unEndTime)
			{
				bResetClearTime = true;
			}
		}
		break;
	case EUMT_WeekMask:			// ������
		{
			unEndTime = ::TimeGet(TIME_WEEK_END);
			if (unClearTime != unEndTime)
			{
				bResetClearTime = true;
			}
		}
		break;
	case EUMT_MonthMask:		// ������
		{
			unEndTime = ::TimeGet(TIME_MONTH_END);
			if (unClearTime != unEndTime)
			{
				bResetClearTime = true;
			}
		}
		break;
	default:					// ������������
		{
			if (unEndTime > 0 && unClearTime != unEndTime)
			{
				bResetClearTime = true;
			}
		}
		break;
	}

	if (bResetClearTime)		// ���ý���ʱ��
	{
		pRecord->SetInt(USER_MASK_DATA_CLEARTIME,	unEndTime);
	}

	pRecord->SetInt64(USER_MASK_DATA_MASKDATA, i64Data);
	if (bUpdate)
	{
		pRecord->UpdateRecord(nType);
	}
	return true;
	DEBUG_CATCHF4("CUserMask::SetData idUser[%u], unMaskType[%u], idMask[%u]", m_idUser, unMaskType, idMask);
}

////////////////////////////////////////////////////////////////////////
// Description:  ��ȡ��������ʱ��
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
UINT CUserMask::GetMaskClearTime(EUSERMASKTYPE unMaskType, OBJID idMask)
{
	DEBUG_TRY;
	CHECKF(unMaskType > EUMT_Begin && unMaskType < EUMT_End);
	RecordPtr pRecord = this->GetMaskRecord(unMaskType, idMask);
	CHECKF(pRecord);
	return pRecord->GetInt(USER_MASK_DATA_CLEARTIME);
	DEBUG_CATCHF4("CUserMask::GetMaskClearTime idUser[%u], unMaskType[%u], idMask[%u]", m_idUser, unMaskType, idMask);
}

////////////////////////////////////////////////////////////////////////
// Description:  ͬ��������������
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
void CUserMask::SynAllMaskData(void)
{
	DEBUG_TRY;
	CHECK(m_idUser);
	CMsgGameMask msg;
	msg.CreateMsg(m_idUser, 0, 0, 0, 0);
	for (MAP_USERMASKDATA::iterator iter = m_mapUserMaskData.begin(); iter != m_mapUserMaskData.end(); ++iter)
	{
		MAP_MASKDATA& mapMaskData = iter->second;
		for (MAP_MASKDATA::iterator iterdata = mapMaskData.begin(); iterdata != mapMaskData.end(); ++ iterdata)
		{
			RecordPtr pRecord = iterdata->second;
			CHECKC(pRecord);
			USERMMASKSTRUCT stInfo = {0};
			stInfo.unMaskType  = pRecord->GetInt(USER_MASK_DATA_MASKTYPE);
			stInfo.idMask	   = pRecord->GetInt(USER_MASK_DATA_MASKID);
			stInfo.i64MaskData = pRecord->GetInt64(USER_MASK_DATA_MASKDATA);
			stInfo.unEndTime   = pRecord->GetInt(USER_MASK_DATA_CLEARTIME);
			if (!msg.AppendMsg(stInfo))
			{
				pUserMgr->SendMsg(m_idUser, &msg);
				CHECK(msg.CreateMsg(m_idUser, stInfo.unMaskType, stInfo.idMask, stInfo.unEndTime, stInfo.i64MaskData));
			}
		}
	}
	pUserMgr->SendMsg(m_idUser, &msg);
	DEBUG_CATCH2("CUserMask::SynAllMaskData idUser[%u]", m_idUser);
}
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
// Description:  ��ȡ�����¼
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
RecordPtr CUserMask::GetMaskRecord(EUSERMASKTYPE unMaskType, OBJID idMask)
{
	DEBUG_TRY;
	CHECKF(unMaskType > EUMT_Begin && unMaskType < EUMT_End);
	CHECKF_NOLOG(this->IsExist(unMaskType, idMask));
	MAP_USERMASKDATA::iterator iter = m_mapUserMaskData.find(unMaskType);
	CHECKF(iter != m_mapUserMaskData.end());
	MAP_MASKDATA& mapMaskData = iter->second;
	MAP_MASKDATA::iterator iterdata	= mapMaskData.find(idMask);
	CHECKF(iterdata != mapMaskData.end());
	return iterdata->second;
	DEBUG_CATCHF4("CUserMask::GetMaskRecord idUser[%u], unMaskType[%u], idMask[%u]", m_idUser, unMaskType, idMask);
}

////////////////////////////////////////////////////////////////////////
// Description:  ��Ӽ�¼
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool CUserMask::Add	(EUSERMASKTYPE unMaskType, OBJID idMask)
{
	DEBUG_TRY;
	CHECKF(unMaskType > EUMT_Begin && unMaskType < EUMT_End);
	CHECKF(m_idUser);
	CHECKF(m_pDefaultRes);

	MAP_USERMASKDATA::iterator iter = m_mapUserMaskData.find(unMaskType);
	if (iter == m_mapUserMaskData.end())			// û�и����Ͳ����µ�����
	{
		MAP_MASKDATA mapMaskData;
		m_mapUserMaskData[unMaskType] = mapMaskData;
	}

	MAP_USERMASKDATA::iterator iterfind = m_mapUserMaskData.find(unMaskType);
	CHECKF(iterfind != m_mapUserMaskData.end());	// �����µĿռ�¼
	MAP_MASKDATA& mapMaskData = iterfind->second;

	RecordPtr pRecord = m_pDefaultRes->CreateNewRecord();
	CHECKF(pRecord);
	pRecord->SetInt(USER_MASK_DATA_USERID,		m_idUser);
	pRecord->SetInt(USER_MASK_DATA_MASKTYPE,	unMaskType);
	pRecord->SetInt(USER_MASK_DATA_MASKID,		idMask);
	pRecord->SetInt(USER_MASK_DATA_CLEARTIME,	CONST_DEFULT_MASK_ENDTIME);
	pRecord->SetInt64(USER_MASK_DATA_MASKDATA,	0);
	CHECKF(pRecord->InsertRecord());
	mapMaskData[idMask] = pRecord;

	return true;
	DEBUG_CATCHF4("CUserMask::Add idUser[%u], unMaskType[%u], idMask[%u]", m_idUser, unMaskType, idMask);
}

////////////////////////////////////////////////////////////////////////
// Description:  ���ü�¼
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool CUserMask::Reset(EUSERMASKTYPE unMaskType, OBJID idMask, bool bUpdate/* = true */, int nType/* = DBUPDATE_ASYNC */)
{
	DEBUG_TRY;
	CHECKF(unMaskType > EUMT_Begin && unMaskType < EUMT_End);

	RecordPtr pRecord = this->GetMaskRecord(unMaskType, idMask);
	CHECKF(pRecord);

	// ���ʱ���Ƿ����
	UINT unClearTime = pRecord->GetInt(USER_MASK_DATA_CLEARTIME);
	bool bResetClearTime = false;
	UINT unEndTime = CONST_DEFULT_MASK_ENDTIME;
	switch(unMaskType)
	{
	case EUMT_DayMask:			// ������
		{
			unEndTime = ::TimeGet(TIME_DAY);
			if (unClearTime != unEndTime)
			{
				bResetClearTime = true;
			}
		}
		break;
	case EUMT_WeekMask:			// ������
		{
			unEndTime = ::TimeGet(TIME_WEEK_END);
			if (unClearTime != unEndTime)
			{
				bResetClearTime = true;
			}
		}
		break;
	case EUMT_MonthMask:		// ������
		{
			unEndTime = ::TimeGet(TIME_MONTH_END);
			if (unClearTime != unEndTime)
			{
				bResetClearTime = true;
			}
		}
		break;
	default:					// ������������
		{
			if (unClearTime != unEndTime)
			{
				bResetClearTime = true;
			}
		}
		break;
	}

	if (bResetClearTime)		// ���ý���ʱ��
	{
		pRecord->SetInt(USER_MASK_DATA_CLEARTIME,	unEndTime);
	}

	pRecord->SetInt64(USER_MASK_DATA_MASKDATA, 0);
	if (bUpdate)
	{
		pRecord->UpdateRecord(nType);
	}
	return true;
	DEBUG_CATCHF4("CUserMask::Reset idUser[%u], unMaskType[%u], idMask[%u]", m_idUser, unMaskType, idMask);
}

////////////////////////////////////////////////////////////////////////
// Description:  ɾ����¼
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool CUserMask::Del	(EUSERMASKTYPE unMaskType, OBJID idMask)
{
	DEBUG_TRY;
	CHECKF(unMaskType > EUMT_Begin && unMaskType < EUMT_End);
	MAP_USERMASKDATA::iterator iter = m_mapUserMaskData.find(unMaskType);
	CHECKF(iter != m_mapUserMaskData.end());
	MAP_MASKDATA& mapMaskData = iter->second;
	MAP_MASKDATA::iterator iterdata	= mapMaskData.find(idMask);
	CHECKF(iterdata != mapMaskData.end());
	RecordPtr pRecord = iterdata->second;
	CHECKF(pRecord);
	CHECKF(pRecord->DeleteRecord(DBUPDATE_ASYNC));
	mapMaskData.erase(idMask);				// ����ָ��, ֱ��erase����
	return true;
	DEBUG_CATCHF4("CUserMask::Del idUser[%u], unMaskType[%u], idMask[%u]", m_idUser, unMaskType, idMask);
}

////////////////////////////////////////////////////////////////////////
// Description:  �жϼ�¼�Ƿ����
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool CUserMask::IsExist(EUSERMASKTYPE unMaskType, OBJID idMask)
{
	DEBUG_TRY;
	CHECKF(unMaskType > EUMT_Begin && unMaskType < EUMT_End);
	CHECKF(m_idUser);

	bool bResult = false;
	MAP_USERMASKDATA::iterator iter = m_mapUserMaskData.find(unMaskType);
	if (iter != m_mapUserMaskData.end())
	{
		MAP_MASKDATA& mapMaskData = iter->second;
		MAP_MASKDATA::iterator iterdata = mapMaskData.find(idMask);
		if (iterdata != mapMaskData.end())
		{
			bResult = true;
		}
	}

	return bResult;
	DEBUG_CATCHF4("CUserMask::IsExist idUser[%u], unMaskType[%u], idMask[%u]", m_idUser, unMaskType, idMask);
}

////////////////////////////////////////////////////////////////////////
// Description:  �������м�¼
// Arguments:
// Author: �½���(Chen jianjun)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool CUserMask::SaveAll	(void)
{
	DEBUG_TRY;
	for (MAP_USERMASKDATA::iterator iter = m_mapUserMaskData.begin(); iter != m_mapUserMaskData.end(); ++iter)
	{
		MAP_MASKDATA& mapMaskData = iter->second;
		for (MAP_MASKDATA::iterator iterdata = mapMaskData.begin(); iterdata != mapMaskData.end(); ++ iterdata)
		{
			RecordPtr pRecord = iterdata->second;
			CHECKC(pRecord);
			pRecord->UpdateRecord();
		}
	}
	return true;
	DEBUG_CATCHF2("CUserMask::SaveAll idUser[%u]", m_idUser);
}





////////////////////////////////////////////////////////////////////////