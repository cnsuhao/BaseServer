
// MyServerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MyServer.h"
#include "MyServerDlg.h"
#include "afxdialogex.h"
#include "../share/define.h"
#include "../../../Include/Global.h"
#include "version.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CMyServerDlg 对话框



CMyServerDlg::CMyServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyServerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMyServerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
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

	// 设置进程优先级类（高于标准）
	SetPriorityClass(GetCurrentProcess(), ABOVE_NORMAL_PRIORITY_CLASS);

#ifdef _DEBUG
	// 调试模式检测内存块泄露
	//_CrtSetBreakAlloc(3753);
#endif

	// 设置服务器程序标题
	const DWORD dwPID = ::GetCurrentProcessId();
	CString strTitle;
	strTitle.Format(GAMESERVER_TITLE, g_szServerName, g_nServerGroup, g_nServerLine, dwPID, VER_SERVER_SVN_VISION);
	SetWindowText(strTitle);

	// 初始化网络服务
	//CHECKF(PScoketServer->Create(9998));

	// 读取ini配置文件设定

	// 初始化日志系统


	auto plistBoxLua = (CListBox*)GetDlgItem(IDC_LIST_UPDATE_LUA);
	CHECKF(plistBoxLua);
	plistBoxLua->AddString(_T("Lua: login"));
	plistBoxLua->AddString(_T("Lua: liveness"));
	plistBoxLua->AddString(_T("Lua: box"));
	
	auto plistBoxTable = (CListBox*)GetDlgItem(IDC_LIST_UPDATE_TABLE);
	CHECKF(plistBoxTable);
	plistBoxTable->AddString(_T("Table: config"));
	plistBoxTable->AddString(_T("Table: server_list"));
	plistBoxTable->AddString(_T("Table: config_txt"));

	// TODO: 在此添加额外的初始化代码

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

	// 服务器退出操作（暂时未处理）
	// 初始话Scoket服务
	//ScoketServer::DelInstance();

	// 程序退出
	CDialog::OnOK();
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
