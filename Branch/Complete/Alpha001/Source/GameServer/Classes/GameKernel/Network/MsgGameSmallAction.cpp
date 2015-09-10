////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2012, WuHan ChuangYou, All Rights Reserved
// Moudle: MsgSmallAction.cpp
// Author: ������(Peng Wenqi)
// Created: 2012-10-23
////////////////////////////////////////////////////////////////////////
#include "./MsgGameSmallAction.h"
#include "./../GameKernel.h"
#include "./../UserMgr.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CMsgGameSmallAction::CMsgGameSmallAction()
{
	Init();
	m_pInfo	=(MSG_Info *)m_bufMsg;
	m_unMsgType	= _MSG_GAME_SMALLACTION;
	m_unMsgSize	= sizeof(MSG_Info);
}

//////////////////////////////////////////////////////////////////////////
CMsgGameSmallAction::~CMsgGameSmallAction()
{
}

//////////////////////////////////////////////////////////////////////////
BOOL CMsgGameSmallAction::Create(char* pMsgBuf, DWORD dwSize)
{
	if (!CNetMsg::Create(pMsgBuf, dwSize))
		return false;

	if(_MSG_GAME_SMALLACTION != this->GetType())
		return false;

	return true;
}

////////////////////////////////////////////////////////////////////////
// Description:  ����SmallAction
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: None
////////////////////////////////////////////////////////////////////////
bool CMsgGameSmallAction::CreateSmallAction(MSG_SMALL_ACTION eAction, MSG_SMALL_RESULT eResult)
{
	this->Init();
	m_unMsgType	= _MSG_GAME_SMALLACTION;
	m_unMsgSize	= sizeof(MSG_Info) - sizeof(MSG_NUM_4BIT);

	m_pInfo->sAction = (MSG_NUM_2BIT)eAction;
	m_pInfo->sResult = (MSG_NUM_2BIT)eResult;
	m_pInfo->nParamNumber = 0;

	return true;
}

////////////////////////////////////////////////////////////////////////
// Description:  ���Ӳ���
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool CMsgGameSmallAction::AppendParam(int nAddParam)
{
	CHECKF(sizeof(MSG_Info) + sizeof(MSG_NUM_4BIT) * m_pInfo->nParamNumber < MAX_PACKETSIZE);
	m_pInfo->nParam[m_pInfo->nParamNumber] = nAddParam;
	m_unMsgSize = sizeof(MSG_Info) + sizeof(MSG_NUM_4BIT) * m_pInfo->nParamNumber;
	++(m_pInfo->nParamNumber);
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description:  ���Param��������
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: int
////////////////////////////////////////////////////////////////////////
int CMsgGameSmallAction::GetParamVector(OUT INT_VEC& rVec)
{
	DEBUG_TRY;
	rVec.clear();
	CHECKF(m_pInfo->nParamNumber >= 0 && m_pInfo->nParamNumber < (MAX_PACKETSIZE - 8) / sizeof(int));
	for (int i = 0; i < m_pInfo->nParamNumber; ++i)
	{
		rVec.push_back(m_pInfo->nParam[i]);
	}
	DEBUG_CATCH("CMsgSmallAction::GetParamVector Error");
	return rVec.size();
}

////////////////////////////////////////////////////////////////////////
// Description:  ������Ϣ
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: None
////////////////////////////////////////////////////////////////////////
void CMsgGameSmallAction::Process(void *pInfo)
{
	DEBUG_TRY
	CHECK(pGameKernel);
	switch(m_pInfo->sAction)
	{
	case MSG_SMALL_ACTION_QUERY_NEWCARDPRIZE_INFO:
	//	this->ProcessQueryNewCardPrizeInfo();
	//	break;
	//case MSG_SMALL_ACTION_RUN_LUA_SCRIPT:
	//	this->ProcessRunLuaScript();
	//	break;
	//case MSG_SMALL_ACTION_QUERY_SKILLPOINT_INFO:
	//	this->ProcessQuerySkillPointInfo();
	//	break;
	//case MSG_SMALL_ACTION_GET_MONTH_CARD:
	//	this->ProcessGetMonthCard();
	//	break;
	//case MSG_SMALL_ACTION_QUERY_BUY_POWER:
	//	this->ProcessQueryBuyPowerInfo();
	//	break;
	//case MSG_SMALL_ACTION_REQUEST_BUY_POWER:
	//	this->ProcessRequestBuyPower();
	//	break;
	//case MSG_SMALL_ACTION_QUERY_OTHER_USER_INFO:
	//	this->ProcessQueryOtherUserInfo();
	//	break;
	//case MSG_SMALL_ACTION_QUERY_TREASURE_POWER_INFO:
	//	this->ProcessQueryTreasurePowerInfo();
	//	break;
	//case MSG_SMALL_ACTION_QUERY_EXITINFO:
	//	this->ProcessQueryExitInfo();
	//	break;
	default:
		tolog2("CMsgSmallAction::Process Unknow action[%d]", m_pInfo->sAction);
		break;
	}

	DEBUG_CATCH2("CMsgSmallAction::Process Action[%d]", m_pInfo->sAction);
}

//////////////////////////////////////////////////////////////////////////
//// Description:  ��ѯ���ֿ��콱��Ϣ
//// Arguments:
//// Author: �½���(Chen Jianjun)
//// Return Value: None
//////////////////////////////////////////////////////////////////////////
//void CMsgGameSmallAction::ProcessQueryNewCardPrizeInfo()
//{
//	DEBUG_TRY;
//	OBJID idUser = pUserMgr->GetUserID(this);
//	CHECK(idUser);
//
//	INT_VEC vecParam;
//	GetParamVector(vecParam);
//	CHECK(1 == vecParam.size());
//	int nCardType = vecParam[0];
//	CHECK(nCardType);
//
//	pNewCardMgr->SendNewCardPrizeInfo(idUser, nCardType);
//	DEBUG_CATCH("CMsgGameSmallAction::ProcessQueryNewCardPrizeInfo failed!");
//}
//
//////////////////////////////////////////////////////////////////////////
//// Description: �ͻ���ִ�нű�
//// Arguments:
//// Author: ������(Peng Wenqi)
//// Return Value: 
//////////////////////////////////////////////////////////////////////////
//void CMsgGameSmallAction::ProcessRunLuaScript( void )
//{
//	DEBUG_TRY;
//	OBJID idUser = pUserMgr->GetUserID(this);
//	CHECK(idUser);
//
//	INT_VEC vecParam;
//	GetParamVector(vecParam);
//	CHECK(6 == vecParam.size());
//	OBJID idAction = vecParam[0];
//
//	const TConstAction* pActionConstTable = pConstTableMgr->GetAction();
//	CHECK(pActionConstTable);
//	if (!pActionConstTable->IsExist(idAction))
//	{
//		tolog3("Client Run LuaScript Unkown idAction[%u], idUser[%u]", idAction, idUser);
//		return;
//	}
//
//	if (0 == pActionConstTable->GetData(idAction, ACTION_DATA_CLIENT_TRIGGER))
//	{
//		tolog3("Client Run LuaScript Trigger Error! idAction[%u], idUser[%u]", idAction, idUser);
//		return;
//	}
//
//	pGameAction->ProcessAction(idAction, idUser, vecParam[1], vecParam[2], vecParam[3], vecParam[4], vecParam[5]);
//
//	DEBUG_CATCH("CMsgGameSmallAction::ProcessQueryNewCardPrizeInfo failed!");
//}
//
//////////////////////////////////////////////////////////////////////////
//// Description:  ��ѯ���ܵ���Ϣ
//// Arguments:
//// Author: �½���(Chen Jianjun)
//// Return Value: None
//////////////////////////////////////////////////////////////////////////
//void CMsgGameSmallAction::ProcessQuerySkillPointInfo(void)
//{
//	DEBUG_TRY;
//	OBJID idUser = pUserMgr->GetUserID(this);
//	CHECK(idUser);
//	CHECK(pPokerMgr);
//	pPokerMgr->SynMagicPointInfoToClient(idUser);
//	DEBUG_CATCH("CMsgGameSmallAction::ProcessQuerySkillPointInfo failed!");
//}
//
//////////////////////////////////////////////////////////////////////////
//// Description:  �������ܵ���Ϣ
//// Arguments:
//// Author: �½���(Chen Jianjun)
//// Return Value: bool
//////////////////////////////////////////////////////////////////////////
//bool CMsgGameSmallAction::CreateSkillPointInfo(UINT unLeftPoint, UINT unMaxPoint, UINT unNextRecoverTime, UINT unAllEnergyRecoverTime, int nRecoverInterval, int nBuyCount, int nNeedVas, int nBuyPoint)
//{
//	CHECKF(this->CreateSmallAction(MSG_SMALL_ACTION_QUERY_SKILLPOINT_INFO, MSG_SMALL_RESULT_SUCC)); 
//	CHECKF(this->AppendParam(unLeftPoint));
//	CHECKF(this->AppendParam(unMaxPoint));
//	CHECKF(this->AppendParam(unNextRecoverTime));
//	CHECKF(this->AppendParam(unAllEnergyRecoverTime));
//	CHECKF(this->AppendParam(nRecoverInterval));
//	CHECKF(this->AppendParam(nBuyCount));
//	CHECKF(this->AppendParam(nNeedVas));
//	CHECKF(this->AppendParam(nBuyPoint));
//
//	return true;
//}
//
//////////////////////////////////////////////////////////////////////////
//// Description:  �����ʣ��ʱ����Ϣ
//// Arguments:
//// Author: �½���(Chen Jianjun)
//// Return Value: bool
//////////////////////////////////////////////////////////////////////////
//bool CMsgGameSmallAction::CreateActivityTimeInfo(int nType, int nState, int nLeftTime)
//{
//	CHECKF(this->CreateSmallAction(MSG_SMALL_ACTION_SYN_ACTIVITY_TIME, MSG_SMALL_RESULT_SUCC)); 
//	CHECKF(this->AppendParam(nType));		// �����
//	CHECKF(this->AppendParam(nState));		// �״̬
//	CHECKF(this->AppendParam(nLeftTime));	// ʣ��ʱ��
//
//	return true;
//}
//
//////////////////////////////////////////////////////////////////////////
//// Description: ��ȡ�¿�
//// Arguments:
//// Author: ������(Peng Wenqi)
//// Return Value: void
//////////////////////////////////////////////////////////////////////////
//void CMsgGameSmallAction::ProcessGetMonthCard( void )
//{
//	DEBUG_TRY;
//	OBJID idUser = pUserMgr->GetUserID(this);
//	CHECK(idUser);
//	if (!pUserMoneyMgr->RequestGetMonthCard(idUser))
//	{
//		CMsgGameSmallAction msgReturn;
//		IF_OK (msgReturn.CreateSmallAction(MSG_SMALL_ACTION_GET_MONTH_CARD, MSG_SMALL_RESULT_ERROR))
//		{
//			pUserMgr->SendMsg(idUser, &msgReturn);
//		}
//	}
//	DEBUG_CATCH("CMsgGameSmallAction::ProcessGetMonthCard failed!");
//}
//
//////////////////////////////////////////////////////////////////////////
//// Description: �����ѯ����������Ϣ
//// Arguments:
//// Author: �½���(Chen jianjun)
//// Return Value: void
//////////////////////////////////////////////////////////////////////////
//void CMsgGameSmallAction::ProcessQueryBuyPowerInfo(void)
//{
//	DEBUG_TRY;
//	OBJID idUser = pUserMgr->GetUserID(this);
//	CHECK(idUser);
//	auto pConfigData = pConstTableMgr->GetConfigData();
//	auto pConstDataReset = pConstTableMgr->GetDataReset();
//	CHECK(pConfigData && pConstDataReset);
//	
//	auto nBuyCount = pUserTmpDataMgr->GetTmpData(idUser, EUTDP_SERVER_POWER_INFO, USERTMPDATA_INDEX1);
//	auto nLastBuyDate = pUserTmpDataMgr->GetTmpData(idUser, EUTDP_SERVER_POWER_INFO, USERTMPDATA_INDEX2);
//	nBuyCount = (nLastBuyDate == ::TimeGet(TIME_DAY)) ? nBuyCount : 0;							 // ���칺�����
//	auto nVasCost = pConstDataReset->GetData(EDRT_POWER, nBuyCount, DATA_RESET_DATA_COST_NUM);	 // Ԫ����������
//
//	auto nRecorveInterval = 6 * 60;																 // �ָ�ʱ����
//	CHECKB(pConfigData->GetData(CONFIGTYPE_SYSTEM_POWER, CONFIGDATA_DATA1, nRecorveInterval));
//	auto nRecorvePoint	  = 1;
//	CHECKB(pConfigData->GetData(CONFIGTYPE_SYSTEM_POWER, CONFIGDATA_DATA2, nRecorvePoint));
//
//	auto nLastRecoverTime = pUserTmpDataMgr->GetTmpData(idUser, EUTDP_SERVER_POWER_INFO, USERTMPDATA_INDEX0);
//	auto nNextRecoverTime = nLastRecoverTime + nRecorveInterval;								// �µ������ָ�ʱ��
//
//	auto nCurPower	   = pUserMoneyMgr->Get(idUser, USER_MONEY_TYPE_POWER);
//	auto nPowerLimit   = pUserMoneyMgr->GetMax(USER_MONEY_TYPE_POWER, idUser);
//	auto nRecorveCount = (nPowerLimit - nCurPower) / nRecorvePoint + (((nPowerLimit - nCurPower) % nRecorvePoint > 0) ? 1 : 0);
//	auto nAllRecoverTime  = nNextRecoverTime + (nRecorveCount - 1) * nRecorveInterval;			// ȫ�������ָ�ʱ��
//
//	CMsgGameSmallAction msgReturn;
//	IF_OK (msgReturn.CreateSmallAction(MSG_SMALL_ACTION_QUERY_BUY_POWER, MSG_SMALL_RESULT_SUCC))
//	{
//		msgReturn.AppendParam(nBuyCount);
//		msgReturn.AppendParam(nVasCost);
//		msgReturn.AppendParam(nNextRecoverTime);
//		msgReturn.AppendParam(nAllRecoverTime);
//		msgReturn.AppendParam(nRecorveInterval);
//		pUserMgr->SendMsg(idUser, &msgReturn);
//	}
//	DEBUG_CATCH("CMsgGameSmallAction::ProcessQueryBuyPowerInfo failed!");
//}
//
//////////////////////////////////////////////////////////////////////////
//// Description: ����������������Ϣ
//// Arguments:
//// Author: �½���(Chen jianjun)
//// Return Value: void
//////////////////////////////////////////////////////////////////////////
//void CMsgGameSmallAction::ProcessRequestBuyPower(void)
//{
//	DEBUG_TRY;
//	OBJID idUser = pUserMgr->GetUserID(this);
//	CHECK(idUser);
//	if (!pUserMoneyMgr->RequestBuyPower(idUser))
//	{
//		CMsgGameSmallAction msgReturn;
//		IF_OK (msgReturn.CreateSmallAction(MSG_SMALL_ACTION_REQUEST_BUY_POWER, MSG_SMALL_RESULT_ERROR))
//		{
//			pUserMgr->SendMsg(idUser, &msgReturn);
//		}
//	}
//	DEBUG_CATCH("CMsgGameSmallAction::ProcessRequestBuyPower failed!");
//}
//
//////////////////////////////////////////////////////////////////////////
//// Description: ��ѯ���������Ϣ
//// Arguments:
//// Author: �½���(Chen jianjun)
//// Return Value: void
//////////////////////////////////////////////////////////////////////////
//void CMsgGameSmallAction::ProcessQueryOtherUserInfo(void)
//{
//	DEBUG_TRY;
//	OBJID idUser = pUserMgr->GetUserID(this);
//	CHECK(idUser);
//
//	INT_VEC vecParam;
//	GetParamVector(vecParam);
//	CHECK(1 == vecParam.size());
//	OBJID idTarget = vecParam[0];
//	CHECK(idTarget);
//
//	CMsgGameUserQueryInfo msg;
//	CHECK(msg.CreateUserQueryInfo(idTarget));
//	pUserMgr->SendMsg(idUser, &msg);
//	DEBUG_CATCH("CMsgGameSmallAction::ProcessRequestBuyPower failed!");
//}
//
//////////////////////////////////////////////////////////////////////////
//// Description: �����ѯѰ��������Ϣ
//// Arguments:
//// Author: �½���(Chen jianjun)
//// Return Value: void
//////////////////////////////////////////////////////////////////////////
//void CMsgGameSmallAction::ProcessQueryTreasurePowerInfo(void)
//{
//	DEBUG_TRY;
//	OBJID idUser = pUserMgr->GetUserID(this);
//	CHECK(idUser);
//	auto pConfigData = pConstTableMgr->GetConfigData();
//	CHECK(pConfigData);
//
//	auto nRecorveInterval = 20 * 60;														// �ָ�ʱ����
//	CHECKB(pConfigData->GetData(CONFIGTYPE_MINE_TREASUREPOWER_CFG, CONFIGDATA_DATA1, nRecorveInterval));
//	auto nRecorvePoint	  = 1;																// ��ʱ�ָ�����
//	CHECKB(pConfigData->GetData(CONFIGTYPE_MINE_TREASUREPOWER_CFG, CONFIGDATA_DATA2, nRecorvePoint));
//
//	auto nLastRecoverTime = pUserTmpDataMgr->GetTmpData(idUser, EUTDP_SERVER_MINE_INFO, USERTMPDATA_INDEX3);
//	auto nNextRecoverTime = nLastRecoverTime + nRecorveInterval;							// �µ������ָ�ʱ��
//
//	auto nCurTreasurePower   = pUserMoneyMgr->Get(idUser, USER_MONEY_TYPE_TREASURE_POWER);
//	auto nTreasurePowerLimit = pUserMoneyMgr->GetMax(USER_MONEY_TYPE_TREASURE_POWER, idUser);
//	auto nRecorveCount		 = (nTreasurePowerLimit - nCurTreasurePower) / nRecorvePoint + (((nTreasurePowerLimit - nCurTreasurePower) % nRecorvePoint > 0) ? 1 : 0);
//	auto nAllRecoverTime	 = nNextRecoverTime + (nRecorveCount - 1) * nRecorveInterval;	// ȫ�������ָ�ʱ��
//
//	CMsgGameSmallAction msgReturn;
//	IF_OK (msgReturn.CreateSmallAction(MSG_SMALL_ACTION_QUERY_TREASURE_POWER_INFO, MSG_SMALL_RESULT_SUCC))
//	{
//		msgReturn.AppendParam(nTreasurePowerLimit);
//		msgReturn.AppendParam(nNextRecoverTime);
//		msgReturn.AppendParam(nAllRecoverTime);
//		msgReturn.AppendParam(nRecorveInterval);
//		pUserMgr->SendMsg(idUser, &msgReturn);
//	}
//	DEBUG_CATCH("CMsgGameSmallAction::ProcessQueryTreasurePowerInfo failed!");
//}
//
//////////////////////////////////////////////////////////////////////////
//// Description: �����ѯ�˳�ʱ�ĸ��������Ϣ
//// Arguments:
//// Author: �½���(Chen jianjun)
//// Return Value: void
//////////////////////////////////////////////////////////////////////////
//void CMsgGameSmallAction::ProcessQueryExitInfo(void)
//{
//	DEBUG_TRY;
//	OBJID idUser = pUserMgr->GetUserID(this);
//	CHECK(idUser);
//	auto pConfigData = pConstTableMgr->GetConfigData();
//	CHECK(pConfigData);
//
//	//auto nCurPower	    = pUserMoneyMgr->Get(idUser, USER_MONEY_TYPE_POWER);					// 1.��ǰ����(�ͻ����Զ���ȡ)
//	auto nMonthCardAward    = pUserMoneyMgr->IsGetMonthCard(idUser);								// 2.�¿��Ƿ����ȡ
//	//auto nLeftSkillPoint  = pUserMoneyMgr->Get(idUser, USER_MONEY_TYPE_SKILL_POINT);				// 3.���õļ��ܵ�(�ͻ����Զ���ȡ)
//	auto nGooseTower	    = pGooseTowerMgr->GetLeftResetCount(idUser);							// 4.������ʣ�����ô���
//	auto nInstanceCount     = pInstanceMgr->GetCurCanOpenCount(idUser);								// 5.�㺮����ǰ�ѿ���������ʣ�࿪������
//	auto nArenaCount	    = pArenaMgr->GetLeftFightCount(idUser, ARENA_KIND_TYPE_SINGLE_TEAM);	// 6.����̨��ͨģʽ��ս����
//	auto nMineCount		    = pMineMgr->GetLeftMineCount(idUser);									// 7.Ǭ����«���п��ɿ�λ��
//	auto nMoneyTreeCount    = pMoneyTreeMgr->GetLeftAwardCount(idUser);								// 8.�۱��裨ʣ�������
//	auto nLotteryCount      = pLotteryMgr->GetFreeLotteryCount(idUser);								// 9.�����ǣ�ʣ����Ѵ�����
//
//	auto nSynWorshipCount   = 0;																	// 10.����Ĥ�ݣ�ʣ�������
//	auto nWarRoadTeam		= 0;																	// 11.�ŶӸ�����ÿ�ձ������״����
//	if (pSyndicateMgr->GetSyndicateID(idUser))
//	{
//		nSynWorshipCount    = pSynWorshipMgr->GetLeftWorshipCount(idUser, true);
//		nWarRoadTeam		= pUserLivenessMgr->IsGainAward(idUser, LIVENESS_TYPE_WarRoad);
//	}
//
//	auto nWarRoadNormal     = pUserLivenessMgr->IsGainAward(idUser, LIVENESS_TYPE_NormalGate);		// 12.��ͨս�ۣ�ÿ�ձ������״����
//	auto nWarRoadDifficulty = pUserLivenessMgr->IsGainAward(idUser, LIVENESS_TYPE_HeroGate);		// 13.��Ӣս�ۣ�ÿ�ձ������״����
//	auto nEquipStar			= pUserLivenessMgr->IsGainAward(idUser, LIVENESS_TYPE_EquipMagic);		// 14.װ�����ǣ�ÿ�ձ������״����
//	auto nSendRose			= pUserLivenessMgr->IsGainAward(idUser, LIVENESS_TYPE_GiveRose);		// 15.����õ�壨ÿ�ձ������״����
//
//	CMsgGameSmallAction msgReturn;
//	IF_OK (msgReturn.CreateSmallAction(MSG_SMALL_ACTION_QUERY_EXITINFO, MSG_SMALL_RESULT_SUCC))
//	{
//		msgReturn.AppendParam(nMonthCardAward);
//		msgReturn.AppendParam(nGooseTower);
//		msgReturn.AppendParam(nInstanceCount);
//		msgReturn.AppendParam(nArenaCount);
//		msgReturn.AppendParam(nMineCount);
//		msgReturn.AppendParam(nMoneyTreeCount);
//		msgReturn.AppendParam(nLotteryCount);
//		msgReturn.AppendParam(nSynWorshipCount);
//		msgReturn.AppendParam(nWarRoadTeam);
//		msgReturn.AppendParam(nWarRoadNormal);
//		msgReturn.AppendParam(nWarRoadDifficulty);
//		msgReturn.AppendParam(nEquipStar);
//		msgReturn.AppendParam(nSendRose);
//		pUserMgr->SendMsg(idUser, &msgReturn);
//	}
//	DEBUG_CATCH("CMsgGameSmallAction::ProcessQueryExitInfo failed!");
//}
