// MyServer.cpp : ����Ӧ�ó��������Ϊ��
#include "stdafx.h"
#include "MyServer.h"
#include "MyServerDlg.h"
#include "version.h"
#include "../share/define.h"
#include "../Common/IniFile.h"
#include "../../../Include/CrashRpt.h"

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "winmm.lib")

#pragma comment(lib, "../../../Lib/DbgHelp.lib")
#pragma comment(lib, "../../../Lib/Psapi.lib")
#pragma comment(lib, "../../../Lib/mysqlclient.lib")
#pragma comment(lib, "../../../Lib/CrashRpt.lib")

#ifdef _DEBUG
#pragma comment(lib, "../../../Lib/GameServer/Common_d.lib")
#pragma comment(lib, "../../../Lib/GameServer/DataBase_d.lib")
//#pragma comment(lib, "../../../Lib/ServerSocket/ServerSocket_d.lib")
//#pragma comment(lib, "../../../Lib/GameServer/AIKernel_d.lib")
//#pragma comment(lib, "../../../Lib/GameServer/GameKernel_d.lib")
//#pragma comment(lib, "../../../Lib/GameServer/LoginKernel_d.lib")
//#pragma comment(lib, "../../../Lib/GameServer/LuaPlus_d.lib")
//#pragma comment(lib, "../../../Lib/GameServer/RelationKernel_d.lib")
#else
#pragma comment(lib, "../../../Lib/GameServer/Common.lib")
#pragma comment(lib, "../../../Lib/GameServer/DataBase.lib")
//#pragma comment(lib, "../../../Lib/ServerSocket/ServerSocket.lib")
//#pragma comment(lib, "../../../Lib/GameServer/AIKernel.lib")
//#pragma comment(lib, "../../../Lib/GameServer/GameKernel.lib")
//#pragma comment(lib, "../../../Lib/GameS-erver/LoginKernel.lib")
//#pragma comment(lib, "../../../Lib/GameServer/LuaPlus.lib")
//#pragma comment(lib, "../../../Lib/GameServer/RelationKernel.lib")
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyServerApp

BEGIN_MESSAGE_MAP(CMyServerApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMyServerApp ����
CMyServerApp::CMyServerApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}

// Ψһ��һ�� CMyServerApp ����
CMyServerApp theApp;

BOOL WINAPI MyCrashProc(PEXCEPTION_POINTERS Exception)
{
	COleDateTime dt=COleDateTime::GetCurrentTime();
	CString strCrashFileName;
	CString temp=dt.Format("GameServer_%Y��%m��%d��%Hʱ%M��%S��");
	strCrashFileName.Format("./dump/%s_%lu", temp, ::GetTickCount());

	CString strDumpFile		= strCrashFileName + ".dmp";
	CString strReportFile	= strCrashFileName + ".xml";

	// ���ɴ���ʱϵͳ����
	//	GenerateCrashRpt(Exception, strReportFile, CRASHRPT_ERROR|CRASHRPT_SYSTEM|CRASHRPT_PROCESS);
	GenerateCrashRpt(Exception, strReportFile, CRASHRPT_ALL);

	// ����minidump.dmp�����������vc����windbg�򿪷���
	GenerateMiniDump(Exception, strDumpFile);

	return EXCEPTION_EXECUTE_HANDLER;
}

// CMyServerApp ��ʼ��
BOOL CMyServerApp::InitInstance()
{
	// ��ʼ�������������ļ�
	if (!::IsExistFile(GAMESERVER_FILENAME))
	{
#ifdef _DEBUG
		::MessageBox(NULL, "δ�ҵ������ļ�! ��������Ŀ¼�Ƿ�������ȷ", "������",MB_OK|MB_ICONERROR);
#else
		::MessageBox(NULL, "δ�ҵ������ļ�!", "������",MB_OK|MB_ICONERROR);
#endif
		return FALSE;
	}

	// ��ʼ��������������·��
	CIniFile ini(GAMESERVER_FILENAME, "System" ); 
	ini.GetString(g_szServerName, "ServerName", sizeof(g_szServerName));
	g_nServerGroup = ini.GetInt("ServerGroup");
	g_nServerLine  = ini.GetInt("ServerLine");

	// ��ʼ����־ϵͳ
	CreateDirectory(LOGFILE_DIR, NULL);
	//CreateDirectory(DBLOGFILE_DIR, NULL);
	//CreateDirectory(GMLOG_DIR, NULL);

	CString strTitle;
	strTitle.Format(GAMESERVER_TITLE, g_szServerName, g_nServerGroup, g_nServerLine, ::GetCurrentProcessId(), VER_SERVER_SVN_VISION);
	InitLog(strTitle, time(NULL));

	wchar_t szUnicodeTitle[1024];
	char szUtf8Title[1024] = "";
	CHECKB(::MyANSIToUnicode(strTitle.GetBuffer(0), szUnicodeTitle, sizeof(szUnicodeTitle) / sizeof(szUnicodeTitle[0])));
	CHECKB(::MyUnicodeToUTF8(szUnicodeTitle, szUtf8Title, sizeof(szUtf8Title) / sizeof(szUtf8Title[0])));

	::LogSave(	"\n\n===================================================================================================\n"
				"=== %s \n"
				"===================================================================================================\t\t\t"
				, szUtf8Title);

	// ��ʼ����ӡ��ջϵͳ
	::InitSymEngine();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	// --------------------------------------------------------------------
	//	::SetUnhandledExceptionFilter(MyUnhandledExceptionFilter);

	// ��ʼ��CrashRpt.dll�쳣�����
	InitializeCrashRptEx(MyCrashProc);

	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}


	AfxEnableControlContainer();


	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	CMyServerDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		// ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "����: �Ի��򴴽�ʧ�ܣ�Ӧ�ó���������ֹ��\n");
	}


	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

