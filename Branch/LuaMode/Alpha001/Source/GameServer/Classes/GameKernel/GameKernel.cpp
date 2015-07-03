#include "./GameKernel.h"
#include "../../Common/inifile.h"
#include "../../Common/MessagePort/I_MessagePort.h"
#include "../LuaScriptMachine.h"

IGameKernel* IGameKernel::Instance()	{return (IGameKernel*)CGameKernel::GetInstance();}
void		 IGameKernel::DelInstance()	{CGameKernel::DelInstance();}
CGameKernel* CGameKernel::s_pInstance = NULL;
MYHEAP_IMPLEMENTATION(CGameKernel, s_heap);

//////////////////////////////////////////////////////////////////////////
CGameKernel::CGameKernel()
{
	m_idProcess = MSGPORT_DEFAULT;
	m_pDb		= NULL;
	m_pMsgPort	= NULL;
}

//////////////////////////////////////////////////////////////////////////
bool CGameKernel::Create( IMessagePort* pPort )
{
	CHECKF(pPort);
	CHECKF(pPort->GetID() == MSGPORT_GAME);

	// 通信端口
	m_pMsgPort = pPort;
	m_idProcess = m_pMsgPort->GetID();
	m_pMsgPort->Open();

	// 数据库
	char	szIP[DBSTR_SIZE] = "";
	char	szUser[DBSTR_SIZE] = "";
	char	szPassword[DBSTR_SIZE] = "";
	int		nPort = 0;

	CIniFile ini(GAMESERVER_FILENAME, "Database" );
	ini.GetString(szIP,			"DatabaseIP",		DBSTR_SIZE);
	ini.GetString(szUser,		"DatabaseUser",		DBSTR_SIZE);
	ini.GetString(szPassword,	"DatabasePassword",	DBSTR_SIZE);
	nPort = ini.GetInt("DatabasePort");

	m_pDb = ::CreateDatabase(szIP, szUser, szPassword, g_strGameDatabaseName.c_str(), nPort, true);
	if(!m_pDb)
	{
		LOGERROR("GameKernel Database Connect Failed!");
		return false;
	}

	//////////////////////////////////////////////////////////////////////////
	// 各单例管理器初始化

	// 最先初始化常量表

	CHECKF(pLuaScriptMachine->Init());

	// 启动时, 需要清理无效的服务器掩码
	//pMaskMgr->ClearInvalidGroupServerMask();
	//pMaskMgr->ClearInvalidWorldServerMask();

	return true;
}

//////////////////////////////////////////////////////////////////////////
bool CGameKernel::Release( void )
{
	SAFE_RELEASE (m_pDb);

	CLuaScriptMachine::DelInstance();
	return true;
}

//////////////////////////////////////////////////////////////////////////
bool CGameKernel::ProcessMsg( OBJID idPacket, void* buf, int nType, int nFrom )
{
	DEBUG_TRY;
	switch (idPacket)
	{
	case GAMETHREAD_CLIENT_MSG:
		{
			CHECKF(pLuaScriptMachine->SetLuaEnv(0, 0));
			pLuaScriptMachine->SetParam(1, 0);
			pLuaScriptMachine->SetParam(2, 0);
			pLuaScriptMachine->SetParam(3, 0);
			pLuaScriptMachine->SetParam(4, 0);
			pLuaScriptMachine->SetParam(5, 0);
			CHECKF(pLuaScriptMachine->RunScriptFunction("test1.lua", "test1"));
		}
		break;
	case GAMETHREAD_FORCE_KICK:
		{

		}
		break;
	default:
		tolog2("CGameKernel::ProcessMsg unkonw idPacket[%u]", idPacket);
		break;
	}
	return true;
	DEBUG_CATCHF2("CGameKernel::ProcessMsg idPacket[%u]", idPacket);
}

//////////////////////////////////////////////////////////////////////////
bool CGameKernel::OnTimer( void )
{
	return true;
}

//////////////////////////////////////////////////////////////////////////
bool CGameKernel::OnTimerRollback( void )
{
	return true;
}

//////////////////////////////////////////////////////////////////////////
void CGameKernel::PrintText( const char* pszText )
{
	CHECK(m_pMsgPort && pszText);
	m_pMsgPort->Send(MSGPORT_SHELL, SHELL_PRINTTEXT, STRING_TYPE(pszText), pszText);
}