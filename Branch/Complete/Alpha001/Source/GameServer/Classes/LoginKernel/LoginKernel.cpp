#include "./LoginKernel.h"
#include "../../Common/inifile.h"
#include "../../Common/MessagePort/I_MessagePort.h"
#include "../LuaScriptMachine.h"

ILoginKernel* ILoginKernel::Instance()		{return (ILoginKernel*)CLoginKernel::GetInstance();}
void		  ILoginKernel::DelInstance()	{CLoginKernel::DelInstance();}
CLoginKernel* CLoginKernel::s_pInstance = NULL;
MYHEAP_IMPLEMENTATION(CLoginKernel, s_heap);

//////////////////////////////////////////////////////////////////////////
CLoginKernel::CLoginKernel()
{
	m_idProcess = MSGPORT_DEFAULT;
	m_pDb		= NULL;
	m_pMsgPort	= NULL;
}

//////////////////////////////////////////////////////////////////////////
bool CLoginKernel::Create( IMessagePort* pPort )
{
	CHECKF(pPort);
	CHECKF(pPort->GetID() == MSGPORT_LOGIN);

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
		LOGERROR("CLoginKernel Database Connect Failed!");
		return false;
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////
bool CLoginKernel::Release( void )
{
	SAFE_RELEASE (m_pDb);

	return true;
}

//////////////////////////////////////////////////////////////////////////
bool CLoginKernel::ProcessMsg( OBJID idPacket, void* buf, int nType, int nFrom )
{
	DEBUG_TRY;
	switch (idPacket)
	{
	case LOGINTHREAD_CLIENT_MSG:
		{

		}
		break;
	default:
		tolog2("CLoginKernel::ProcessMsg unkonw idPacket[%u]", idPacket);
		break;
	}
	return true;
	DEBUG_CATCHF2("CLoginKernel::ProcessMsg idPacket[%u]", idPacket);
}

//////////////////////////////////////////////////////////////////////////
bool CLoginKernel::OnTimer( void )
{
	return true;
}

//////////////////////////////////////////////////////////////////////////
bool CLoginKernel::OnTimerRollback( void )
{
	return true;
}

//////////////////////////////////////////////////////////////////////////
void CLoginKernel::PrintText( const char* pszText )
{
	CHECK(m_pMsgPort && pszText);
	m_pMsgPort->Send(MSGPORT_SHELL, SHELL_PRINTTEXT, STRING_TYPE(pszText), pszText);
}