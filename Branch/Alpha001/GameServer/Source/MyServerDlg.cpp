
// MyServerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MyServer.h"
#include "MyServerDlg.h"
#include "afxdialogex.h"
#include "../../Public/Include/GlobalDefine.h"
//#include "SocketServer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CMyServerDlg �Ի���



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
	ON_BN_CLICKED(IDC_BTN_UPDATE, &CMyServerDlg::OnBnClickedBtnUpdate)
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

	// ���ý������ȼ��ࣨ���ڱ�׼��
	SetPriorityClass(GetCurrentProcess(), ABOVE_NORMAL_PRIORITY_CLASS);

#ifdef _DEBUG
	// ����ģʽ����ڴ��й¶
	//_CrtSetBreakAlloc(3753);
#endif

	// ���÷������������
	//CString strTitle;
	//strTitle.Format();
	//SetWindowText();

	// ��ʼ���������
	//CHECKF(PScoketServer->Create(9998));

	// ��ȡini�����ļ��趨

	// ��ʼ����־ϵͳ




	m_listBox = (CListBox*)GetDlgItem(IDC_LIST_UPDATE);
	CHECKF(m_listBox);
	m_listBox->AddString(_T("Table: config"));
	m_listBox->AddString(_T("Table: server_list"));
	m_listBox->AddString(_T("Table: config_txt"));
	m_listBox->AddString(_T("Lua: login"));
	m_listBox->AddString(_T("Lua: liveness"));
	m_listBox->AddString(_T("Lua: box"));

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

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

	// �������˳���������ʱδ����
	// ��ʼ��Scoket����
	//ScoketServer::DelInstance();

	// �����˳�
	CDialog::OnOK();
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


void CMyServerDlg::OnBnClickedBtnUpdate()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_listBox->GetSelCount() > 0)
	{
		// ֪ͨ����

	}
	else
	{
		// ȫ��ѡ��
		for (int i = 0; i < m_listBox->GetCount(); i++)
		{
			m_listBox->SetSel(i);
		}
	}
}
