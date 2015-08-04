// MyServer.cpp : ����Ӧ�ó��������Ϊ��
#include "stdafx.h"
#include "MyServer.h"
#include "MyServerDlg.h"

#include "../share/define.h"

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "winmm.lib")

#pragma comment(lib, "../../../Lib/DbgHelp.lib")
#pragma comment(lib, "../../../Lib/Psapi.lib")
#pragma comment(lib, "../../../Lib/mysqlclient.lib")
#pragma comment(lib, "../../../Lib/CrashRpt.lib")

#ifdef MYDEBUG
#pragma comment(lib, "../../../Lib/GameServer/Common_d.lib")
#pragma comment(lib, "../../../Lib/GameServer/DataBase_d.lib")
#pragma comment(lib, "../../../Lib/GameServer/ServerSocket_d.lib")
#pragma comment(lib, "../../../Lib/GameServer/GameKernel_d.lib")
//#pragma comment(lib, "../../../Lib/GameServer/AIKernel_d.lib")
//#pragma comment(lib, "../../../Lib/GameServer/LoginKernel_d.lib")
//#pragma comment(lib, "../../../Lib/GameServer/LuaPlus_d.lib")
//#pragma comment(lib, "../../../Lib/GameServer/RelationKernel_d.lib")
#else
#pragma comment(lib, "../../../Lib/GameServer/Common.lib")
#pragma comment(lib, "../../../Lib/GameServer/DataBase.lib")
#pragma comment(lib, "../../../Lib/GameServer/ServerSocket.lib")
#pragma comment(lib, "../../../Lib/GameServer/GameKernel.lib")
//#pragma comment(lib, "../../../Lib/GameServer/AIKernel.lib")
//#pragma comment(lib, "../../../Lib/GameS-erver/LoginKernel.lib")
//#pragma comment(lib, "../../../Lib/GameServer/LuaPlus.lib")
//#pragma comment(lib, "../../../Lib/GameServer/RelationKernel.lib")
#endif

// CMyServerApp

BEGIN_MESSAGE_MAP(CMyServerApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMyServerApp ����
CMyServerApp::CMyServerApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}

// Ψһ��һ�� CMyServerApp ����
CMyServerApp theApp;

// CMyServerApp ��ʼ��
BOOL CMyServerApp::InitInstance()
{
	// �������������ļ�
	if (!::IsExistFile(GAMESERVER_FILENAME))
	{
#ifdef MYDEBUG
		::MessageBox(NULL, "δ�ҵ������ļ�! ��������Ŀ¼�Ƿ�������ȷ", "������",MB_OK|MB_ICONERROR);
#else
		::MessageBox(NULL, "δ�ҵ������ļ�!", "������",MB_OK|MB_ICONERROR);
#endif
		return FALSE;
	}

	//// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	//// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	////����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	//INITCOMMONCONTROLSEX InitCtrls;
	//InitCtrls.dwSize = sizeof(InitCtrls);
	//// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	//// �����ؼ��ࡣ
	//InitCtrls.dwICC = ICC_WIN95_CLASSES;
	//InitCommonControlsEx(&InitCtrls);

	//CWinApp::InitInstance();

	//if (!AfxSocketInit())
	//{
	//	AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
	//	return FALSE;
	//}


	//AfxEnableControlContainer();


	//// ��׼��ʼ��
	//// ���δʹ����Щ���ܲ�ϣ����С
	//// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	//// ����Ҫ���ض���ʼ������
	//// �������ڴ洢���õ�ע�����
	//// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	//// �����޸�Ϊ��˾����֯��
	//SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	//CMyServerDlg dlg;
	//m_pMainWnd = &dlg;
	//INT_PTR nResponse = dlg.DoModal();
	//if (nResponse == IDOK)
	//{
	//	// TODO: �ڴ˷��ô����ʱ��
	//	// ��ȷ�������رնԻ���Ĵ���
	//}
	//else if (nResponse == IDCANCEL)
	//{
	//	// TODO: �ڴ˷��ô����ʱ��
	//	//  ��ȡ�������رնԻ���Ĵ���
	//}
	//else if (nResponse == -1)
	//{
	//	TRACE(traceAppMsg, 0, "����: �Ի��򴴽�ʧ�ܣ�Ӧ�ó���������ֹ��\n");
	//}


	//// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	////  ����������Ӧ�ó������Ϣ�á�

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CMyServerDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

