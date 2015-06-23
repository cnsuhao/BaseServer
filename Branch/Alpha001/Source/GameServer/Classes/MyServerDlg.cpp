
// MyServerDlg.cpp : ʵ���ļ�
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

// ȫ�ֱ������������������·
char g_szServerName[64] = "";
int  g_nServerGroup		= 0;
int  g_nServerLine		= 0;

////////////////////////////////////////////////////////////////////////
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
class CAboutDlg : public CDialog
{
public:
	CAboutDlg() : CDialog(CAboutDlg::IDD) {}

	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
// CMyServerDlg �Ի���
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

// CMyServerDlg ��Ϣ�������
BOOL CMyServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	// ��ʼ��ϵͳ�˵����
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
		// �ر�ϵͳ�˵����رա���ť����
		pSysMenu->EnableMenuItem(SC_CLOSE, MF_BYCOMMAND | MF_GRAYED);
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	// ���ý������ȼ��ࣨ���ڱ�׼��
	SetPriorityClass(GetCurrentProcess(), ABOVE_NORMAL_PRIORITY_CLASS);

#ifdef _DEBUG
	// ����ģʽ����ڴ��й¶
	//_CrtSetBreakAlloc(3753);
#endif

	// ���÷������������
	CString strTitle;
	strTitle.Format(GAMESERVER_TITLE, g_szServerName, g_nServerGroup, g_nServerLine, ::GetCurrentProcessId(), VER_SERVER_SVN_VISION);
	SetWindowText(strTitle);

	// ����SVN�汾��Ϣ
	CString strCopy;
	strCopy.Format("Url:%s &Author:CJJ - Call:13627102328", VER_SERVER_SVN_URL);
	m_staticSvn.SetWindowText(strCopy);

	//srand( (unsigned)time( NULL ) );
	//RandGet(100, true);
	//DateTime(m_szStartServer, time(NULL));

	// ��ʼ���������
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

	// ���ö�ʱ�������Ϊ1��ˢ�¼��Ϊ500MS
	SetTimer(1, 500, NULL);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMyServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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

		// �����̹߳ܵ���Ϣ
		if(m_pMsgPort)
		{
			this->ProcessMsg();
		}

		// ��������״̬
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
				KillTimer(1);			// �ر�ONTIMER
				//CloseDatabaseServer();// �ر����ݿ�
				Sleep(3000);			// �ӳ�3��
				::ReleaseSymEngine();	// ������ӡ��ջϵͳ
				CDialog::OnOK();		// �˳�����
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

	// �ַ����ض�, �����ڻ���
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

	// debug�汾���ü�¼��־
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

	// ʵ���Դ���
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int i = 1;
	i = 3;
}

void CMyServerDlg::OnBnClickedBtnRestart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int i = 1;
	i = 3;
}

void CMyServerDlg::OnBnClickedBtnClose()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	// ��ʾ�Ի���
	this->PrintText("Close Button pressed!");
	if (IDCANCEL == this->MessageBox("ȷ��Ҫ�رշ�������?\n��ȷ�������[ȷ��]", "�رշ�����" , MB_ICONEXCLAMATION | MB_OKCANCEL)) 
	{
		return;
	}
	this->PrintText("Server closing...");

	this->CloseServer();
}

void CMyServerDlg::OnBnClickedChkLua()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CMyServerDlg::OnBnClickedBtnUpdateLua()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	auto pListBoxLua = (CListBox*)GetDlgItem(IDC_LIST_UPDATE_LUA);
	if (pListBoxLua->GetSelCount() > 0)
	{
		// ֪ͨ����

	}
	else
	{
		// ȫ��ѡ��
		for (int i = 0; i < pListBoxLua->GetCount(); i++)
		{
			pListBoxLua->SetSel(i);
		}
	}
}

void CMyServerDlg::OnBnClickedBtnUpdateTable()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	auto pListBoxTable = (CListBox*)GetDlgItem(IDC_LIST_UPDATE_TABLE);
	if (pListBoxTable->GetSelCount() > 0)
	{
		// ֪ͨ����

	}
	else
	{
		// ȫ��ѡ��
		for (int i = 0; i < pListBoxTable->GetCount(); i++)
		{
			pListBoxTable->SetSel(i);
		}
	}
}
