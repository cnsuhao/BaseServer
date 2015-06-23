// MyServer.cpp : 定义应用程序的类行为。
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


// CMyServerApp 构造
CMyServerApp::CMyServerApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}

// 唯一的一个 CMyServerApp 对象
CMyServerApp theApp;

BOOL WINAPI MyCrashProc(PEXCEPTION_POINTERS Exception)
{
	COleDateTime dt=COleDateTime::GetCurrentTime();
	CString strCrashFileName;
	CString temp=dt.Format("GameServer_%Y年%m月%d日%H时%M分%S秒");
	strCrashFileName.Format("./dump/%s_%lu", temp, ::GetTickCount());

	CString strDumpFile		= strCrashFileName + ".dmp";
	CString strReportFile	= strCrashFileName + ".xml";

	// 生成错误时系统快照
	//	GenerateCrashRpt(Exception, strReportFile, CRASHRPT_ERROR|CRASHRPT_SYSTEM|CRASHRPT_PROCESS);
	GenerateCrashRpt(Exception, strReportFile, CRASHRPT_ALL);

	// 生成minidump.dmp，这个可以用vc或者windbg打开分析
	GenerateMiniDump(Exception, strDumpFile);

	return EXCEPTION_EXECUTE_HANDLER;
}

// CMyServerApp 初始化
BOOL CMyServerApp::InitInstance()
{
	// 初始化服务器配置文件
	if (!::IsExistFile(GAMESERVER_FILENAME))
	{
#ifdef _DEBUG
		::MessageBox(NULL, "未找到配置文件! 并检查调试目录是否设置正确", "出错啦",MB_OK|MB_ICONERROR);
#else
		::MessageBox(NULL, "未找到配置文件!", "出错啦",MB_OK|MB_ICONERROR);
#endif
		return FALSE;
	}

	// 初始化服务器名和线路号
	CIniFile ini(GAMESERVER_FILENAME, "System" ); 
	ini.GetString(g_szServerName, "ServerName", sizeof(g_szServerName));
	g_nServerGroup = ini.GetInt("ServerGroup");
	g_nServerLine  = ini.GetInt("ServerLine");

	// 初始化日志系统
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

	// 初始化打印堆栈系统
	::InitSymEngine();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	// --------------------------------------------------------------------
	//	::SetUnhandledExceptionFilter(MyUnhandledExceptionFilter);

	// 初始化CrashRpt.dll异常捕获库
	InitializeCrashRptEx(MyCrashProc);

	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}


	AfxEnableControlContainer();


	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	CMyServerDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		// “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
	}


	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}

