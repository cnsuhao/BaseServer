
// MyServerDlg.h : 头文件
#include "../Common/MessagePort/MessagePort.h"
#include "../Common/TimeOut.h"

#pragma once

enum SHELL_STATUS
{
	SHELL_STATUS_FAILD	= 0,		// 失败
	SHELL_STATUS_INIT,				// 初始化
	SHELL_STATUS_RUNNING,			// 运行中
	SHELL_STATUS_CLOSING_KICK,
	SHELL_STATUS_CLOSING,			// 关闭中
	SHELL_STATUS_END,				// 结束
};

// CMyServerDlg 对话框
class CMyServerDlg : public CDialog
{
// 构造
public:
	CMyServerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MYSERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	virtual HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	
	CTimeOut	m_tState;
	CString		m_sShellState;

	CString		m_sText;
	int			m_nTextLines;

	char		m_szStartServerTime[20];

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
