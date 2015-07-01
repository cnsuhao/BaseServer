
// MyServerDlg.h : ͷ�ļ�
#include "../Common/MessagePort/MessagePort.h"
#include "../Common/TimeOut.h"

#pragma once

enum SHELL_STATUS
{
	SHELL_STATUS_FAILD	= 0,		// ʧ��
	SHELL_STATUS_INIT,				// ��ʼ��
	SHELL_STATUS_RUNNING,			// ������
	SHELL_STATUS_CLOSING_KICK,
	SHELL_STATUS_CLOSING,			// �ر���
	SHELL_STATUS_END,				// ����
};

// CMyServerDlg �Ի���
class CMyServerDlg : public CDialog
{
// ����
public:
	CMyServerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MYSERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	virtual HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	
	CTimeOut	m_tState;
	CString		m_sShellState;

	CString		m_sText;
	int			m_nTextLines;

	char		m_szStartServerTime[20];

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnnotify();
	afx_msg void OnBnClickedBtnRestart();
	afx_msg void OnBnClickedBtnClose();
	afx_msg void OnBnClickedChkLua();
	afx_msg void OnBnClickedChkGm();
	afx_msg void OnBnClickedChkGmtool();
	afx_msg void OnBnClickedBtnUpdateLua();
	afx_msg void OnBnClickedBtnUpdateTable();

protected:
	IMessagePort*	m_pMsgPort;
	SHELL_STATUS	m_eState;
	DWORD			m_dwSeiyaPID;

	void	ProcessMsg();
	void	PrintText(const char* pszText);

	DWORD	StartSeiya();
	void	CloseSeiya(DWORD dwPID);
	void	CloseServer();

	void	InitCtrlLuaView();
	void	InitCtrlTableView();
};
