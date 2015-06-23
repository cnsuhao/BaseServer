
// MyServerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MyServer.h"
#include "MyServerDlg.h"
#include "afxdialogex.h"

#include "version.h"
#include "../share/define.h"
#include "../share/protocol.h"
#include "../Common/IniFile.h"
#include "../Common/logfile.h"
#include "../../../Include/CrashRpt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 全局变量保存服务器名和线路
char g_szServerName[64] = "";
int  g_nServerGroup		= 0;
int  g_nServerLine		= 0;

////////////////////////////////////////////////////////////////////////
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
class CAboutDlg : public CDialog
{
public:
	CAboutDlg() : CDialog(CAboutDlg::IDD) {}

	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

protected:
	DECLARE_MESSAGE_MAP()
};

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

////////////////////////////////////////////////////////////////////////
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

// CMyServerDlg 对话框
CMyServerDlg::CMyServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyServerDlg::IDD, pParent)
	, m_pMsgPort(NULL)
	, m_eState(SHELL_STATUS_FAILD)
	, m_nTextLines(0)
	, m_sShellState(_T(""))
	, m_sText(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STC_SVN, m_staticSvn);
	DDX_Text(pDX, IDC_STC_STATUS, m_sShellState);
	DDX_Text(pDX, IDC_STC_TIPS, m_sText);
}

BEGIN_MESSAGE_MAP(CMyServerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_NOTIFY, &CMyServerDlg::OnBnClickedBtnnotify)
	ON_BN_CLICKED(IDC_BTN_RESTART, &CMyServerDlg::OnBnClickedBtnRestart)
	ON_BN_CLICKED(IDC_BTN_CLOSE, &CMyServerDlg::OnBnClickedBtnClose)
	ON_BN_CLICKED(IDC_CHK_LUA, &CMyServerDlg::OnBnClickedChkLua)
	ON_BN_CLICKED(IDC_CHK_GM, &CMyServerDlg::OnBnClickedChkGm)
	ON_BN_CLICKED(IDC_CHK_GMTOOL, &CMyServerDlg::OnBnClickedChkGmtool)
	ON_BN_CLICKED(IDC_BTN_UPDATE_LUA, &CMyServerDlg::OnBnClickedBtnUpdateLua)
	ON_BN_CLICKED(IDC_BTN_UPDATE_TABLE, &CMyServerDlg::OnBnClickedBtnUpdateTable)
END_MESSAGE_MAP()

// CMyServerDlg 消息处理程序
BOOL CMyServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	// 初始化系统菜单相关
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
		// 关闭系统菜单“关闭”按钮功能
		pSysMenu->EnableMenuItem(SC_CLOSE, MF_BYCOMMAND | MF_GRAYED);
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	// 设置进程优先级类（高于标准）
	SetPriorityClass(GetCurrentProcess(), ABOVE_NORMAL_PRIORITY_CLASS);

#ifdef _DEBUG
	// 调试模式检测内存块泄露
	//_CrtSetBreakAlloc(3753);
#endif

	// 初始化服务器名和线路号
	CIniFile ini(GAMESERVER_FILENAME, "System" ); 
	ini.GetString(g_szServerName, "ServerName", sizeof(g_szServerName));
	g_nServerGroup = ini.GetInt("ServerGroup");
	g_nServerLine  = ini.GetInt("ServerLine");

	// 设置服务器程序标题
	CString strTitle;
	strTitle.Format(GAMESERVER_TITLE, g_szServerName, g_nServerGroup, g_nServerLine, ::GetCurrentProcessId(), VER_SERVER_SVN_VISION);
	SetWindowText(strTitle);

	// 初始化日志系统
	CreateDirectory(LOGFILE_DIR, NULL);
	//CreateDirectory(DBLOGFILE_DIR, NULL);
	//CreateDirectory(GMLOG_DIR, NULL);
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

	// 设置服务器权限和SVN版本信息
	ini.SetSection("Service" ); 
	char szManagerName[32] = "";
	ini.GetString(szManagerName, "Manager", sizeof(szManagerName));
	char szManagerCall[16] = "";
	ini.GetString(szManagerCall, "Call", sizeof(szManagerCall));

	CString strCopy;
	strCopy.Format("Url:%s !!&Manager:%s - Call:%s", VER_SERVER_SVN_URL, szManagerName, szManagerCall);
	m_staticSvn.SetWindowText(strCopy);

	// 初始化对话框线程管道
	if(!CMessagePort::InitPortSet(MSGPORT_SIZE))
	{
		MessageBox("Init Message Port Failed!");
	}
	else
	{
		m_pMsgPort = CMessagePort::GetInterface(MSGPORT_SHELL);
		m_pMsgPort->Open();
		m_eState   = SHELL_STATUS_INIT;
	}

	// 初始化数据
	// srand( (unsigned)time( NULL ) );
	// RandGet(100, true);
	DateTime(m_szStartServerTime, time(NULL));

	// 设置定时器。句柄为1，刷新间隔为500MS
	SetTimer(1, 500, NULL);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMyServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMyServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMyServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMyServerDlg::OnTimer(UINT nIDEvent) 
{
	DEBUG_TRY;
	//!!! Can't use 'return' in this block
	// TODO: Add your message handler code here and/or call default

	static bool bOnTimer = true;
	if(1 == nIDEvent && bOnTimer)
	{
		bOnTimer = false;

		// 处理线程管道消息
		if(m_pMsgPort)
		{
			this->ProcessMsg();
		}

		// 检测服务器状态
		switch (m_eState)
		{
		case SHELL_STATUS_FAILD:
			{
				m_eState = SHELL_STATUS_END;
			}
			break;
		case SHELL_STATUS_INIT:
			{
				// 若初始化失败直接退出
				m_eState = SHELL_STATUS_CLOSING;

				// 1.启动日志线程
				this->PrintText("1. Start Log thread...");
				CLogThread::GetInstance()->StartLogServe();	

				// 2.启动堆栈引擎
				this->PrintText("2. Start SymEngine");
				STACK_TRACE_START;

				// 3.启动网络线程
				this->PrintText("3. Start Socket Thread...");

				// 4.初始化数据库
				this->PrintText("4. Init DataBase...");

				// 5.启动登陆线程
				this->PrintText("5. Start Login Thread...");

				// 6.启动游戏线程
				this->PrintText("6. Start Game Thread...");

				// 7.启动关系线程
				this->PrintText("7. Start Relation Thread...");

				// 8.启动守护进程
				this->PrintText("8. Start Seiya...");
				m_dwSeiyaPID = StartSeiya();

				PrintText("All thread start OK !");
				m_eState = SHELL_STATUS_RUNNING;
			}
			break;
		case SHELL_STATUS_RUNNING:
			{
				// 服务器性能监视
				if (m_tState.ToNextTime(PERFORMANCE_STATISTICS_ONTIMER_SECOND))
				{
					UpdateData(TRUE);

					int nAllPlayers = CPerformanceStatistics::GetInstance()->GetData(PERFORMANCE_STATISTICS_TYPE_NOW_TOTAL_USER_AMOUNT);
					int nMaxPlayers = CPerformanceStatistics::GetInstance()->GetData(PERFORMANCE_STATISTICS_TYPE_MAX_TOTAL_USER_AMOUNT);

					char szCurrentDateTime[20] = "";
					::DateTime(szCurrentDateTime, time(NULL));

					//char szPlayersBuff[64] = "";
					//sprintf(szPlayersBuff, "NowPlayer[%04d], MaxPlayer[%04d]", nAllPlayers, nMaxPlayers);
					//CMemMonitor::GetInstance()->OnTimerMonitor(szPlayersBuff);

					CPerformanceStatistics::GetInstance()->OnTimer();
					m_sShellState.Format("Start Time: %s   Current Time: %s\n%s", m_szStartServerTime, szCurrentDateTime, CPerformanceStatistics::GetInstance()->GetLogBuffer());

					UpdateData(FALSE);
				}

				// dead loop
				extern long g_nMessagePortErrorCount;
				if (g_nMessagePortErrorCount > 0 && g_nMessagePortErrorCount % 50000 == 0)
				{
					InterlockedExchange(&g_nMessagePortErrorCount, 0);
					this->PrintText("Message pipe block, Server may be slowly!!!");
				}
			}
			break;
		case SHELL_STATUS_CLOSING_KICK:
			{
				static int nCount = 0;
				nCount++;
				
				// 3次心跳后退出
				if (nCount > 3)
				{
					m_eState = SHELL_STATUS_CLOSING;
				}
			}
			break;
		case SHELL_STATUS_CLOSING:
			{
				// 服务器开始关闭
				this->PrintText("Server closing...");

				// 关闭日志线程
				if (CLogThread::GetInstance()->CloseLogServe())
				{
					this->PrintText("Close Log Thread OK!");
				}
				else
				{
					this->PrintText("Close Log Thread failed!");
				}

				// 关闭守护进程
				this->PrintText("Close Seiya...");
				this->CloseSeiya(m_dwSeiyaPID);

				// 关闭网络线程
				this->PrintText("Close Socket Thread OK!");

				// 关闭关系线程
				this->PrintText("Close Relation Thread OK!");

				// 关闭游戏线程
				this->PrintText("Close Game Thread OK!");

				// 关闭登陆线程
				this->PrintText("Close Login Thread OK!");


				this->PrintText("Server is over, close all after 3 second!");
				this->ProcessMsg();

				m_pMsgPort->Close();
				CMessagePort::ClearPortSet();
				m_pMsgPort = NULL;

				m_eState = SHELL_STATUS_END;
			}
			break;
		case SHELL_STATUS_END:
			{
				// 关闭ONTIMER
				KillTimer(1);

				// 关闭数据库
				//CloseDatabaseServer();

				// 延迟3秒
				Sleep(3000);

				// 析构打印堆栈系统
				::ReleaseSymEngine();
				
				// 退出程序
				CDialog::OnOK();
			}
			break;
		default:
			ASSERT(!"switch(m_eState)");
		}

		bOnTimer = true;
	}
	CDialog::OnTimer(nIDEvent);
	DEBUG_CATCH("CMyServerDlg::OnTimer");
}

void CMyServerDlg::ProcessMsg()
{
	char			buf[MAX_MESSAGESIZE];
	CMessageStatus	cStatus;

	DEBUG_TRY;
	while(m_pMsgPort->Recv(PORT_ANY, PACKET_ANY, STRUCT_TYPE(buf), buf, &cStatus))
	{
		switch (cStatus.m_nPacket)
		{
		case SHELL_PRINTTEXT:
			{
				this->PrintText((char*)buf);
			}
			break;
		case SHELL_REMOTE_CLOSE:
			{
				this->PrintText("Remote Close");
				this->CloseServer();
			}
			break;
		default:
			tolog2("CMsgServerDlg::ProcessMsg unkonw idPacket[%u]", cStatus.m_nPacket);
			this->PrintText("ERROR: CMsgServerDlg::Process() ProcessMsg()");
			break;
		}
	}
	DEBUG_CATCH("CMsgServerDlg::Process()")
}

void CMyServerDlg::PrintText(const char* pszText)
{
	DEBUG_TRY;
	CHECK(pszText);
	if(m_nTextLines >= WINDOW_TEXT_SIZE)
	{
		int nPos = m_sText.Find("\n", 0);
		if(nPos != -1)
			m_sText = m_sText.Mid(nPos + 1);
	}

	// 字符串截断, 不至于换行
	char szMsgBuff[96] = "";
	::SafeCopy(szMsgBuff, pszText, sizeof(szMsgBuff));

	char szBuf[20] = "";
	DateTime(szBuf);
	m_sText += szBuf+11;
	m_sText += "[";
	m_sText += szMsgBuff;
	m_sText += "]";
	m_sText += "\r\n";
	m_nTextLines++;

	UpdateData(FALSE);

	// debug版本不用记录日志
#ifndef _DEBUG
	::LogSave("SHELL: %s", pszText);
#endif 
	DEBUG_CATCH("CMsgServerDlg::PrintText");
}

DWORD CMyServerDlg::StartSeiya()
{
#ifndef SEIYA_RUN
	return 0;
#endif
	const DWORD MAX_FILE_PATH_LEN = 1024;
	const DWORD MAX_FILE_NAME_LEN = 256;
	const char SEIYA_NAME[] = "Seiya.exe";

	char CreateOrder[MAX_FILE_PATH_LEN]		= {0};
	char CurFloder[MAX_FILE_PATH_LEN]		= {0};
	char exePath[MAX_FILE_PATH_LEN]			= {0};
	char szFile[MAX_FILE_NAME_LEN]			= {0};

	// 获取本程序的文件名
	::GetModuleFileName(NULL, exePath, MAX_FILE_PATH_LEN);
	for(int nIndex = strlen(exePath) - 1; nIndex >= 0; nIndex--)
	{
		if (exePath[nIndex] == '\\' || exePath[nIndex] == '/')
		{
			if ((strlen(exePath) - nIndex - 1) > MAX_FILE_NAME_LEN)		// 如果文件名超过了最大文件名长度
			{
				LOGWARNING("StartupSeiya::the FileName is too Long [%d]", strlen(exePath) - nIndex - 1);
				return 0;
			}
			strcpy(szFile, exePath + nIndex + 1);
			break;
		}
	} 

	// 获取进程启动指令
	::GetCurrentDirectory(MAX_FILE_PATH_LEN,CurFloder);
	int nFloderLen = strlen(CurFloder);	
	if (nFloderLen <= 0)	// 获取当前路径异常
	{
		LOGWARNING("StartupSeiya::Get Work Path is Failed");
		return 0;
	}
	if (CurFloder[nFloderLen - 1] == '/' || CurFloder[nFloderLen - 1] == '\\')
	{
		sprintf(CreateOrder,"%s%s %s %d",CurFloder, SEIYA_NAME, szFile, ::GetCurrentProcessId()); 	// 盘符根目录
	}
	else
	{
		sprintf(CreateOrder,"%s\\%s %s %d",CurFloder, SEIYA_NAME, szFile, ::GetCurrentProcessId());
	}
	 
	// 进程信息
	STARTUPINFO si; 
	ZeroMemory(&si, sizeof(si));  
	si.cb = sizeof(si);
	PROCESS_INFORMATION pi;
	ZeroMemory(&pi, sizeof(pi)); 

	// 创建守护进程
	if(CreateProcess(NULL, CreateOrder, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
	{  
		// 脱离父进程成为独立进程
		DWORD dwPID = pi.dwProcessId;
		CloseHandle(pi.hThread);	
		CloseHandle(pi.hProcess);
		CString szOldTitle;
		CString szNewTitle;
		GetWindowText(szOldTitle);
		szNewTitle.Format("%s Seiya[%d]", szOldTitle.GetBuffer(), dwPID);
		SetWindowText(szNewTitle);
		return dwPID;
	}
	LOGWARNING("StartupSeiya::Create Seiya Process Failed");
	return 0;
}

void CMyServerDlg::CloseSeiya(DWORD dwPID)
{
#ifndef SEIYA_RUN
	return;
#endif
	if (0 == dwPID)
	{
		LOGWARNING("ShutdownSeiya::the Seiya is not Exist");
		return;
	}

	HANDLE  hProcess; 
	hProcess=OpenProcess(PROCESS_ALL_ACCESS,FALSE,dwPID); 
	if (hProcess == NULL)
	{
		DWORD dwErrNum = ::GetLastError();
		LOGWARNING("ShutdownSeiya::the Seiya[%d] OpenProcess is Failed[%d]",dwPID, dwErrNum);
		return;
	}
	
	// 关闭进程
	::TerminateProcess(hProcess,0);
}

void CMyServerDlg::CloseServer()
{
	this->PrintText("Kick All User...");

	//SOCKET_ID idSocket = SOCKET_NONE;
	//m_pMsgPort->Send(MSGPORT_LOGIN, LOGINTHREAD_CLOSE_ENTRANCE, VARTYPE_INT, &idSocket);
	//m_pMsgPort->Send(MSGPORT_GAME, GAMETHREAD_KICK_ALLUSER, VARTYPE_INT, &idSocket);
	//m_pMsgPort->Send(MSGPORT_SOCKET, SOCKETTHREAD_BREAKALLCONNECT, VARTYPE_INT, &idSocket);

	// 实质性处理
	m_eState = SHELL_STATUS_CLOSING_KICK;
}

void CMyServerDlg::InitCtrlLuaView()
{
	auto plistBoxLua = (CListBox*)GetDlgItem(IDC_LIST_UPDATE_LUA);
	plistBoxLua->AddString(_T("Lua: login"));
	plistBoxLua->AddString(_T("Lua: liveness"));
	plistBoxLua->AddString(_T("Lua: box"));
}

void CMyServerDlg::InitCtrlTableView()
{
	auto plistBoxTable = (CListBox*)GetDlgItem(IDC_LIST_UPDATE_TABLE);
	plistBoxTable->AddString(_T("Table: config"));
	plistBoxTable->AddString(_T("Table: server_list"));
	plistBoxTable->AddString(_T("Table: config_txt"));
}

void CMyServerDlg::OnBnClickedBtnnotify()
{
	// TODO: 在此添加控件通知处理程序代码
	int i = 1;
	i = 3;
}

void CMyServerDlg::OnBnClickedBtnRestart()
{
	// TODO: 在此添加控件通知处理程序代码
	int i = 1;
	i = 3;
}

void CMyServerDlg::OnBnClickedBtnClose()
{
	// TODO: 在此添加控件通知处理程序代码

	// 提示对话框
	this->PrintText("Close Button pressed!");
	if (IDCANCEL == this->MessageBox("确认要关闭服务器吗?\n正确无误请点[确定]", "关闭服务器" , MB_ICONEXCLAMATION | MB_OKCANCEL)) 
	{
		return;
	}
	this->PrintText("Server closing...");

	this->CloseServer();
}

void CMyServerDlg::OnBnClickedChkLua()
{
	// TODO: 在此添加控件通知处理程序代码
	if (BST_UNCHECKED != this->IsDlgButtonChecked(IDC_CHK_LUA))
	{
		int i = 1;
		i = 3;
	}
	else
	{

	}
}

void CMyServerDlg::OnBnClickedChkGm()
{
	// TODO: 在此添加控件通知处理程序代码
	if (BST_UNCHECKED != ((CButton *)GetDlgItem(IDC_CHK_GM))->GetCheck())
	{
		int i = 1;
		i = 3;
	}
	else
	{

	}
}

void CMyServerDlg::OnBnClickedChkGmtool()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CMyServerDlg::OnBnClickedBtnUpdateLua()
{
	// TODO: 在此添加控件通知处理程序代码
	auto pListBoxLua = (CListBox*)GetDlgItem(IDC_LIST_UPDATE_LUA);
	if (pListBoxLua->GetSelCount() > 0)
	{
		// 通知更新

	}
	else
	{
		// 全部选中
		for (int i = 0; i < pListBoxLua->GetCount(); i++)
		{
			pListBoxLua->SetSel(i);
		}
	}
}

void CMyServerDlg::OnBnClickedBtnUpdateTable()
{
	// TODO: 在此添加控件通知处理程序代码
	auto pListBoxTable = (CListBox*)GetDlgItem(IDC_LIST_UPDATE_TABLE);
	if (pListBoxTable->GetSelCount() > 0)
	{
		// 通知更新

	}
	else
	{
		// 全部选中
		for (int i = 0; i < pListBoxTable->GetCount(); i++)
		{
			pListBoxTable->SetSel(i);
		}
	}
}
