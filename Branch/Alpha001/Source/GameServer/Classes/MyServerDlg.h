
// MyServerDlg.h : 头文件
//

#pragma once


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


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
	afx_msg void OnBnClickedBtnUpdate();

private:
	CListBox*	m_listBox;
};
