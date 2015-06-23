
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
// CMyServerDlg 对话框
CMyServerDlg::CMyServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyServerDlg::IDD, pParent)
	, m_pMsgPort(NULL)
	, m_eState(SHELL_STATUS_FAILD)
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

	// 设置服务器程序标题
	CString strTitle;
	strTitle.Format(GAMESERVER_TITLE, g_szServerName, g_nServerGroup, g_nServerLine, ::GetCurrentProcessId(), VER_SERVER_SVN_VISION);
	SetWindowText(strTitle);

	// 设置SVN版本信息
	CString strCopy;
	strCopy.Format("Url:%s &Author:CJJ - Call:13627102328", VER_SERVER_SVN_URL);
	m_staticSvn.SetWindowText(strCopy);

	//srand( (unsigned)time( NULL ) );
	//RandGet(100, true);
	//DateTime(m_szStartServer, time(NULL));

	// 初始化网络服务
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
			break;
		case SHELL_STATUS_RUNNING:
			break;
		case SHELL_STATUS_CLOSING_KICK:
			break;
		case SHELL_STATUS_CLOSING:
			{

				PrintText("ShutdownSeiya...");
				//ShutdownSeiya(m_dwPID);

				PrintText("Server is over, close all  after 3 second!");
				this->ProcessMsg();

				m_pMsgPort->Close();
				CMessagePort::ClearPortSet();
				m_pMsgPort = NULL;

				m_eState = SHELL_STATUS_END;
			}
			break;
		case SHELL_STATUS_END:
			{
				KillTimer(1);			// 关闭ONTIMER
				//CloseDatabaseServer();// 关闭数据库
				Sleep(3000);			// 延迟3秒
				::ReleaseSymEngine();	// 析构打印堆栈系统
				CDialog::OnOK();		// 退出程序
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
				PrintText((char*)buf);
			}
			break;
		case SHELL_REMOTE_CLOSE:
			{
				PrintText("Remote Close");
				this->CloseServer();
			}
			break;
		default:
			tolog2("CMsgServerDlg::ProcessMsg unkonw idPacket[%u]", cStatus.m_nPacket);
			PrintText("ERROR: CMsgServerDlg::Process() ProcessMsg()");
			break;
		}
	}
	DEBUG_CATCH("CMsgServerDlg::Process()")
}

void CMyServerDlg::PrintText(const char* pszText)
{
	DEBUG_TRY;
	CHECK(pszText);
	if(m_nTextLines >= TEXTWINDOW_SIZE)
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

void CMyServerDlg::CloseServer()
{
	this->PrintText("Kick All User...");

	//SOCKET_ID idSocket = SOCKET_NONE;
	//m_pMsgPort->Send(MSGPORT_LOGIN, LOGINTHREAD_CLOSE_ENTRANCE, VARTYPE_INT, &idSocket);
	//m_pMsgPort->Send(MSGPORT_GAME, GAMETHREAD_KICK_ALLUSER, VARTYPE_INT, &idSocket);
	//m_pMsgPort->Send(MSGPORT_SOCKET, SOCKETTHREAD_BREAKALLCONNECT, VARTYPE_INT, &idSocket);

	// 实质性处理
	//m_eState = SHELL_STATUS_CLOSING_KICK;
	m_eState = SHELL_STATUS_CLOSING;
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
