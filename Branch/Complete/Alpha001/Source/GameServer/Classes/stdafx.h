//
//// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
//// ���Ǿ���ʹ�õ��������ĵ�
//// �ض�����Ŀ�İ����ļ�
//
//#pragma once
//
//#ifndef VC_EXTRALEAN
//#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
//#endif
//
//#include "targetver.h"
//
//#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��
//#define _AFX_NO_MFC_CONTROLS_IN_DIALOGS         // �Ƴ��Ի����е� MFC �ؼ�֧��
//
//// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
//#define _AFX_ALL_WARNINGS
//
//#include <afxwin.h>         // MFC ��������ͱ�׼���
//#include <afxext.h>         // MFC ��չ
//
//
//#include <afxdisp.h>        // MFC �Զ�����
//
//
//
//#ifndef _AFX_NO_OLE_SUPPORT
//#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
//#endif
//#ifndef _AFX_NO_AFXCMN_SUPPORT
//#include <afxcmn.h>             // MFC �� Windows �����ؼ���֧��
//#endif // _AFX_NO_AFXCMN_SUPPORT
//
//#include <afxcontrolbars.h>     // �������Ϳؼ����� MFC ֧��
//
//
//#include <afxsock.h>            // MFC �׽�����չ
//
//
//
//
//
//
//
//#ifdef _UNICODE
//#if defined _M_IX86
//#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
//#elif defined _M_X64
//#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
//#else
//#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
//#endif
//#endif

// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//
#if !defined(AFX_STDAFX_H__8BCA41CE_7325_427C_8443_E982F204F462__INCLUDED_)
#define AFX_STDAFX_H__8BCA41CE_7325_427C_8443_E982F204F462__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#define NO_WARN_MBCS_MFC_DEPRECATION
#endif // _MSC_VER > 1000

#pragma  once

#ifdef WIN32
#ifndef WINVER 
#define WINVER 0x0501
#endif  
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0501
#endif
#endif

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__8BCA41CE_7325_427C_8443_E982F204F462__INCLUDED_)


