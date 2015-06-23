
// MyServerDlg.h : ͷ�ļ�
#include "../Common/MessagePort/MessagePort.h"

#pragma once

enum {
	SHELLSTATE_FAILD,
	SHELLSTATE_INIT, 
	SHELLSTATE_RUNNING, 
	SHELLSTATE_CLOSING_KICK,
	SHELLSTATE_CLOSING, 
	SHELLSTATE_END,
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


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
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
	char			m_szStartServer[20];
	int				m_nState;
};
