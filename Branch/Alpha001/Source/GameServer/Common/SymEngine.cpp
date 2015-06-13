/*
 Copyright (c) 2001 - 2002
 Author: Konstantin Boukreev 
 E-mail: konstantin@mail.primorye.ru 
 Created: 25.12.2001 19:41:07
 Version: 1.0.2

 Permission to use, copy, modify, distribute and sell this software
 and its documentation for any purpose is hereby granted without fee,
 provided that the above copyright notice appear in all copies and
 that both that copyright notice and this permission notice appear
 in supporting documentation.  Konstantin Boukreev makes no representations
 about the suitability of this software for any purpose.
 It is provided "as is" without express or implied warranty.

*/
#ifdef WIN32
#ifndef WINVER 
#define WINVER 0x0501
#endif  
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0501
#endif
#pragma warning(disable:4996)
#endif


#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#define NOSOUND

#ifdef MYDEBUG
#pragma warning(disable:4127)		// conditional expression is constant
#endif

#pragma warning(disable:4786)		// disable "identifier was truncated to 'number' characters in the debug information"
#pragma warning(disable:4290)		// C++ Exception Specification ignored
#pragma warning(disable:4097)		// typedef-name 'identifier1' used as synonym for class-name 'identifier2'
#pragma warning(disable:4001)		// nonstandard extension 'single line comment' was used
#pragma warning(disable:4100)		// unreferenced formal parameter
#pragma warning(disable:4699)		// Note: Creating precompiled header 
#pragma warning(disable:4710)		// function not inlined
#pragma warning(disable:4514)		// unreferenced inline function has been removed
#pragma warning(disable:4512)		// assignment operator could not be generated
#pragma warning(disable:4310)		// cast truncates constant value
#pragma warning(disable:4018)
#pragma warning(disable:4284)
#pragma warning(disable:4146)
#include <eh.h>

#pragma warning(push, 3) 
#include <exception>
#pragma warning(pop) 

#include "SymEngine.h"
#include <crtdbg.h>
#include <malloc.h> 
#include <tlhelp32.h>
#include <stdio.h>
#include <string>
#include <time.h>
#include "./../../Include/Psapi.h"
#include "BaseFunc.h"

#ifdef VERIFY
#undef VERIFY
#endif // VERIFY

#ifdef _DEBUG
#define VERIFY(x) (x)
#else
#define VERIFY(x) (x)
#endif //_DEBUG

// �̻߳�����, ȫ��ֻ����Ψһ���ⶫ��������
CSimpleCriticalSection	g_csSymEngineLock;

const int OLD_MAX_STACK_BUFF_SIZE	= 3584;	// �ɰ汾, ���д���ջ����־��С
const int NEW_SUB_STACK_LOG_SIZE	= 2048;	// �°汾, ��ջ��־�ֶ�д���С
const int GET_LOCAL_VARIABLES_NUMBER = 10;	// ֻ��ȡǰʮ�����ر�����ֵ

/*  
-------------------  ����Ϊѡ����Ž���  -------------------
SYMOPT_CASE_INSENSITIVE
	��ѡ��ʹ�����жԷ��������������ִ�Сд��
	���е������и�ѡ��Ĭ�ϴ򿪡�����������֮�󣬿���ͨ��.symopt+0x1 ��.symopt-0x1�򿪻�رա�
	DBH�и�ѡ��Ĭ�ϴ򿪡�DBH����ʱ������ͨ��symopt +1 ��symopt -1���򿪻�رա�

SYMOPT_UNDNAME
	��ѡ��ʹ�ù��з���������ʾ������ʱ���������η���˽�з��Ų��ܸ�ѡ���Ƿ񼤻��Զ���ᱻ���Ρ����ڷ��������η��ĸ�����Ϣ���鿴���к�˽�з��š�
	���е������и�ѡ��Ĭ�ϴ򿪡����������к󣬿���ͨ��.symopt+0x2 ��.symopt-0x2�򿪻�رա�
	DBH�и�ѡ��Ĭ�ϴ򿪡�����ͨ��-d������ѡ��رա�DBH����ʱ������ͨ��symopt +2 ��symopt -2�򿪻�رա�

SYMOPT_DEFERRED_LOADS
	��ѡ���Ϊ�ӳٷ��ż���(deferred symbol loading ��lazy symbol loading)������ʱ����Ŀ��ģ�����ʱ����ʵ�ʼ��ط��ţ����ǵȵ��������õ���ʱ��ż��ء��鿴�ӳٷ��ż��ػ�ȡ��ϸ��Ϣ��
	���е�����Ĭ�ϴ򿪸�ѡ���CDB��KD�У�-s������ѡ����Թر���������CDBҲ����ͨ��ʹ��tools.ini�ļ���LazyLoad�������رա�����������ʱ��ͨ��.symopt+0x4 ��.symopt-0x4,���򿪻�رա�
	DBH�и�ѡ��Ĭ�Ϲرա�DBH����ʱ��ͨ��symopt +4 ��symopt -4���򿪻�رա�

SYMOPT_NO_CPP
	��ѡ��ر�C++ת�������������ѡ��ʱ�����з����е�::����__ �����
	���е�����Ĭ�Ϲرո�ѡ�������ͨ��-snc������ѡ��򿪡�����������ʱ��ͨ��.symopt+0x8 ��.symopt-0x8���򿪹رա�
	DBHĬ�Ϲرո�ѡ�����ʱͨ��symopt +8 ��symopt -8���򿪹رա�

SYMOPT_LOAD_LINES
	��ѡ�������Դ���ļ��ж�ȡ�к���Ϣ������򿪲���ʹ��Դ�������ȷ������
	��KD��CDB�и�ѡ��Ĭ�Ϲرգ���WinDbg��Ĭ�ϴ򿪡�����CDB��KD����ͨ��-lines ������ѡ�����򿪡�����������ʱ������ͨ��.symopt+0x10 ��.symopt-0x10���򿪹رա�Ҳ����ͨ��.lines (Toggle Source Line Support)�������򿪻�رա�
	DBH��Ĭ�ϴ򿪸�ѡ�����ʱ����ͨ��symopt +10 ��symopt -10���򿪹رա�

SYMOPT_OMAP_FIND_NEAREST
	�����뱻�Ż�������������λ��û�з���ʱ�����ø�ѡ���������ķ����������
	���е�����Ĭ�ϴ򿪸�ѡ�����ʱ��ͨ��.symopt+0x20 ��.symopt-0x20���򿪹رա�
	DBH��Ĭ�ϴ򿪡�����ʱ����ͨ��symopt +20 ��symopt -20���򿪹رա�

SYMOPT_LOAD_ANYTHING
	��ѡ��ͷ��Ŵ���������ƥ�����ʱ�ľ�ȷ�ԡ�
	���е�����Ĭ�Ϲرա�����ʱ����ͨ��.symopt+0x40 ��.symopt-0x40���򿪹رա�
	DBH��Ĭ�Ϲرա�����ʱͨ��symopt +40 ��symopt -40���򿪹رա�

SYMOPT_IGNORE_CVREC
	��ѡ��ʹ�÷��Ŵ���������������ʱ�������Ѽ���ģ��ӳ��ͷ�е�CV��¼��
	�е�������Ĭ�Ϲرա�����ͨ��-sicv ������ѡ��򿪡�����ʱͨ��.symopt+0x80 ��.symopt-0x80�򿪹رա�
	DBH��Ĭ�Ϲرա�����ʱͨ��symopt +80 ��symopt -80�򿪹رա�

SYMOPT_NO_UNQUALIFIED_LOADS
	��ѡ���ֹ���Ŵ������Զ�Ϊģ����м��ء��������ѡ��ҵ���������ƥ��ĳ������ʱ����ֻ�����Ѽ���ģ����������
	���ѡ�����������������������������⡣ͨ�������������ʹ�õ�������������ж�صķ����ļ�ʱ��ͣ��ʹ�ø�ѡ�������ķ������Ѽ���ģ�����Ҳ��������������ͻᱻ��ֹ��
	���е�����Ĭ�Ϲرո�ѡ�����ͨ��-snul������ѡ������ʱͨ��.symopt+0x100 ��.symopt-0x100�򿪹رա�
	DBH��Ĭ�Ϲرա�����ʱͨ��symopt +100 ��symopt -100�򿪹رա�

SYMOPT_FAIL_CRITICAL_ERRORS
	���ѡ��ʹ���ļ����ʴ���Ի���ȡ������
	�����ѡ��رգ��ٷ��ż���ʱ����������"������δ׼����"�������ļ����ʴ��󣬻����һ���Ի��������ѡ��򿪣���Щ�Ի��򲻻���֣��������з��ʴ��󶼻��յ�һ��"fail"����Ӧ��
	���е�����Ĭ�ϴ򿪸�ѡ�����ͨ��-sdce������ѡ�����رա�����ʱͨ��.symopt+0x200 ��.symopt-0x200���򿪹رա�
	DBHĬ�Ϲرա�����ʱ��ͨ��symopt +200 ��symopt -200���򿪹رա�

SYMOPT_EXACT_SYMBOLS
	���ѡ��ʹ�õ����������з����ļ������ϸ��ƥ�䡣
	��ʱ����ʹ�����ļ��ͷ��Ŵ�������Ҫ���к�С�Ĳ��죬��Щ����Ҳ�ᱻ���ԡ� 
	������Ĭ�Ϲرո�ѡ�����ͨ��-ses���������ʱ��ͨ��.symopt+0x400 ��.symopt-0x400���򿪹رա�
	-failinc������ѡ��Ҳ��SYMOPT_EXACT_SYMBOLS�����⣬��������û�ģʽminidump���ں�ģʽminidump�� -failinc����ֹ�����������κ�ӳ���ܱ�ӳ���ģ�顣
	DBH��Ĭ�ϴ򿪡�����ʱͨ��symopt +400 ��symopt -400���򿪹رա�

SYMOPT_ALLOW_ABSOLUTE_SYMBOLS
	��ѡ��ʹ��DbgHelp���Զ�ȡ�������ڴ�ĳ�����Ե�ַ�еķ��š������������²���Ҫ��ѡ�
	���е�������Ĭ�Ϲرա�����ʱͨ��.symopt+0x800 ��.symopt-0x800���򿪹رա�
	DBH��Ĭ�ϴ򿪡�����ʱͨ��symopt +800 ��symopt -800���򿪹رա�


SYMOPT_IGNORE_NT_SYMPATH
	��ѡ��ʹ�õ��������Ի������������õķ���·���Ϳ�ִ��ӳ��·����
	���е�����Ĭ�Ϲرո�ѡ�����ͨ��-sins������ѡ�����ǣ�����ʱ����ͨ��.symopt ���������ƣ���Ϊ����������������ʱ�ᱻ��ȡ��
	DBH��Ĭ�Ϲرգ������κ�����¶��ᱻDBH���ԡ�

SYMOPT_INCLUDE_32BIT_MODULES
	���ѡ��ǿ��DbgHelp��ImageHlp��ö��Intel Itanium�������ϵ�32λģ�顣
	���е�����Ĭ�Ϲرո�ѡ�����ʱͨ��.symopt+0x2000 ��.symopt-0x2000���򿪹رա�
	DBH��Ĭ�Ϲرա�����ʱͨ��symopt +2000 ��symopt -2000�򿪹رա�

SYMOPT_PUBLICS_ONLY
	���ѡ��ʹ��DbgHelp����˽�з������ݣ����ڹ��з��ű�������������Ϣ������ģ��DbgHelp�������Щ���͵�֧��֮ǰ����Ϊ���鿴���к�˽�з��š�
	���е������ж�Ĭ�Ϲرա�����ʱͨ��.symopt+0x4000 ��.symopt-0x4000���򿪹رա�
	DBH ��Ĭ�Ϲرա�����ͨ��-d������ѡ��򿪡�����ʱͨ��symopt +4000 ��symopt -4000�򿪹رա�

SYMOPT_NO_PUBLICS
	��ѡ����ֹDbgHelp�������з��ű���ʹ�÷���ö�ٺ�������ø��졣����ȽϹ��������ٶȣ���ôSYMOPT_AUTO_PUBLICS ѡ��Ƚ��ʺϡ����ڹ��з��ű����Ϣ���鿴���к�˽�з��š�
	���е�������Ĭ�Ϲرա�����ʱ��ͨ��.symopt+0x8000 ��.symopt-0x8000�򿪹رա�
	DBH��Ĭ�Ϲرա�����ʱͨ��symopt +8000 ��symopt -8000�򿪹رա�


SYMOPT_AUTO_PUBLICS
	���ѡ��ʹ��DbgHelp����.pdb���������з��ű���Ϊ����ѡ�������˽�з������ҵ����κ�ƥ�䣬���з��žͲ����ٱ���������������������ٶȡ�
	���е�������Ĭ�ϴ򿪡�����ͨ��-sup������ѡ��رա�����ʱͨ��.symopt+0x10000 ��.symopt-0x10000�򿪹رա�
	DBH��Ĭ�ϴ򿪡�ʹ��-d������ѡ��ʱ�ᱻ�ص�������ʱ��ʹ��symopt +10000 ��symopt -10000�򿪹رա�

SYMOPT_NO_IMAGE_SEARCH
	���ѡ������ڼ��ط���ʱDbgHelp�������̲���ӳ���ļ��Ŀ�����
	���е�������Ĭ�ϴ򿪡�����ʱͨ��.symopt+0x20000 ��.symopt-0x20000�򿪹رա�
	DBH��Ĭ�Ϲرա�����ʱͨ��symopt +20000 ��symopt -20000�򿪹رա�

SYMOPT_SECURE
	(���ں�ģʽ) ��ѡ��ָʾ�Ƿ񼤻��˰�ȫģʽ��
	���е�����Ĭ�Ϲرա�����ͨ��-secure������ѡ������������������С��ھ�ֹģʽ�£�����û�н����κε��Է�����������ͨ��.symopt+0x40000 ��.secure (Activate Secure Mode)���򿪰�ȫģʽ��
	DBH��Ĭ�Ϲرա�����ʱͨ��symopt +40000 ��symopt -40000���򿪹رա�
	��ȫģʽһ������֮��Ͳ����ٹرա�

SYMOPT_NO_PROMPTS
	���ѡ����ֹ���Դ������������֤�Ի��������ʹ��SymSrv ���ܷ���internet�ϵķ��Ŵ洢��
	��ϸ��Ϣ���鿴����ǽ�ʹ����������
	��KD��CDB�У���ѡ��Ĭ�ϴ򿪣�WinDbg��Ĭ�Ϲرա�����������ʱ����ͨ��.symopt+0x80000 ��.symopt-0x80000�����.reload (Reload Module)�������򿪻�رա�Ҳ����ʹ��!sym prompts off��!sym prompts��չ������.reload (Reload Module)���������򿪹رա�
	DBH��Ĭ�Ϲرա�����ʱͨ��symopt +80000 ��symopt -80000���򿪹رա�

SYMOPT_DEBUG
	��ѡ�����ϸ���ż���(noisy symbol loading)����ʹ�õ�������������ʱ��ʾ��Ϣ��
	���з����ļ�����ʱ����ʾ���֡�������������ܼ���ĳ�������ļ�������ʾ������Ϣ��.pdb�ļ��Ĵ�����Ϣ���ı���ʽ��ʾ��.dbg�ļ��Ĵ�����Ϣ�Դ����뷽ʽ��ʾ����Щ��������winerror.h�ļ���˵����
	���ĳ��ӳ���ļ������¼����Ի�ȡ���Ż���ͷ��Ϣ��Ҳ�ᱻ��ʾ������
	���е�����Ĭ�Ϲرո�ѡ�����ͨ��-n������ѡ������ʱͨ��.symopt+0x80000000 ��.symopt-0x80000000���򿪹رա�Ҳ����ͨ��!sym noisy �� !sym quiet�������򿪻�رա�
	ע�� ���ѡ��ܺ���ϸԴ�����(noisy source loading)���� �� ������.srcnoisy (Noisy Source Loading)���������Ƶġ�
	DBH��Ĭ�Ϲرա�����ʹ��-n������ѡ��DBH����ʱ������ͨ��symopt +80000000 ��symopt -80000000���򿪻�رա�Ҳ����ͨ��verbose on ��verbose off �������򿪻�رա�
*/

//////////////////////////////////////////////////////////////////////////
BOOL __stdcall My_ReadProcessMemory (HANDLE, LPCVOID lpBaseAddress, LPVOID lpBuffer, DWORD nSize, LPDWORD lpNumberOfBytesRead)
{
    return ReadProcessMemory(GetCurrentProcess(), lpBaseAddress, lpBuffer, nSize, lpNumberOfBytesRead);
}

bool g_bInitSymEngine = false;
void InitSymEngine()
{
	if (!g_bInitSymEngine)
	{
		g_bInitSymEngine = true;
		::SymSetOptions(SymGetOptions()|SYMOPT_EXACT_SYMBOLS|SYMOPT_LOAD_LINES);		// ���ϸ����ƥ�����кż���
		::SymInitialize(GetCurrentProcess(), 0, TRUE);
		::LogStackWithOutLine("InitSymEngine ok!");
	}
}

void ReleaseSymEngine()
{
	if (g_bInitSymEngine)
	{
		g_bInitSymEngine = false;
		::SymCleanup(GetCurrentProcess());
		::LogStackWithOutLine("ReleaseSymEngine ok!");
	}
}

//////////////////////////////////////////////////////////////////////////
CSymEngine::CSymEngine()
: m_dwAddress(0)
, m_pframe(0) 
{
	m_dwEBP = 0;
	m_dwESP = 0;

	m_pctx = NULL;
	this->Init();
}

//////////////////////////////////////////////////////////////////////////
CSymEngine::~CSymEngine()
{
//	VERIFY(SymCleanup(GetCurrentProcess()));
	if (m_pframe)
	{
		delete m_pframe;
		m_pframe = NULL;
	}
}

//////////////////////////////////////////////////////////////////////////
bool CSymEngine::Init()
{
	m_i64TimeStart = ::GetUtcMillisecond();

	HANDLE hProc = GetCurrentProcess();
// 	if (!::SymInitialize(hProc, 0, TRUE))
// 	{
// 		return false;
// 	}

// 	HINSTANCE hInst = LoadLibrary("psapi.dll");
// 	if (!hInst)
// 	{
// 		return false;
// 	}
// 	
// 	typedef BOOL (WINAPI *ENUMPROCESSMODULES)(HANDLE, HMODULE*, DWORD, LPDWORD);	
// 	ENUMPROCESSMODULES fnEnumProcessModules = (ENUMPROCESSMODULES)GetProcAddress(hInst, "EnumProcessModules");
// 
// 	DWORD cbNeeded = 0;
// 	if (fnEnumProcessModules &&	fnEnumProcessModules(GetCurrentProcess(), 0, 0, &cbNeeded) && cbNeeded)
// 	{	
// 		HMODULE * pmod = (HMODULE *)alloca(cbNeeded);
// 		DWORD cb = cbNeeded;
// 		if (fnEnumProcessModules(GetCurrentProcess(), pmod, cb, &cbNeeded))
// 		{
// 			for (unsigned i = 0; i < cb / sizeof (HMODULE); ++i)		// enumerate modules
// 			{								
// 				if (!this->LoadModuleFile(hProc, pmod[i]))
// 				{
// 					//	m_ref = -1;
// 					//	break;
// 				}									
// 			}							
// 		}
// 	}
// 
// 	VERIFY(FreeLibrary(hInst));

	DWORD cbNeeded = 0;
	if (::EnumProcessModules(::GetCurrentProcess(), 0, 0, &cbNeeded) && cbNeeded)
	{
		HMODULE * pmod = (HMODULE *)alloca(cbNeeded);
		DWORD cb = cbNeeded;
		if (EnumProcessModules(GetCurrentProcess(), pmod, cb, &cbNeeded))
		{
			for (unsigned i = 0; i < cb / sizeof (HMODULE); ++i)		// enumerate modules
			{								
				if (!this->LoadModuleFile(hProc, pmod[i]))
				{
					//	m_ref = -1;
					//	break;
				}									
			}							
		}
	}
	return true;
}

//////////////////////////////////////////////////////////////////////////
bool CSymEngine::GetSymbol(std::string& strSymbol)
{
	BYTE symbol[512] = {0};
	PIMAGEHLP_SYMBOL pSym = (PIMAGEHLP_SYMBOL)&symbol;

	pSym->SizeOfStruct = sizeof(IMAGEHLP_SYMBOL) ;
    pSym->MaxNameLength = sizeof(symbol) - sizeof(IMAGEHLP_SYMBOL);

	HANDLE hProc = GetCurrentProcess();
	DWORD displacement = 0;//if need, then get this.
	int r = SymGetSymFromAddr(hProc, m_dwAddress, &displacement, pSym);
	if (!r) return false;

	strSymbol = pSym->Name;
	return true;
}

//////////////////////////////////////////////////////////////////////////
DWORD CSymEngine::GetFileLine (std::string& strFileName)
{
	IMAGEHLP_LINE img_line;
	memset(&img_line, 0, sizeof(IMAGEHLP_LINE));
	img_line.SizeOfStruct = sizeof(IMAGEHLP_LINE);

	HANDLE hProc = GetCurrentProcess();

	// "Debugging Applications" John Robbins
    // The problem is that the symbol engine finds only those source
    // line addresses (after the first lookup) that fall exactly on
    // a zero displacement. I'll walk backward 100 bytes to
    // find the line and return the proper displacement.
    DWORD dwDisplacementOutput = 0;//if need, then get this!
	int n = 0;
    while (!SymGetLineFromAddr (hProc, m_dwAddress - n, &dwDisplacementOutput, &img_line))
    {        
        if (100 == ++n)
            return false;        
    }

	strFileName = img_line.FileName;
	return img_line.LineNumber;
}

//////////////////////////////////////////////////////////////////////////
bool CSymEngine::StackFirst (CONTEXT* pctx)
{
	if (!pctx || IsBadReadPtr(pctx, sizeof(CONTEXT))) 
		return false;

	if (!m_pframe) 
	{
		m_pframe = new STACKFRAME;
		if (!m_pframe) return false;
	}
				
	memset(m_pframe, 0, sizeof(STACKFRAME));

    #ifdef _X86_
    m_pframe->AddrPC.Offset       = pctx->Eip;
    m_pframe->AddrPC.Mode         = AddrModeFlat;
    m_pframe->AddrStack.Offset    = pctx->Esp;
    m_pframe->AddrStack.Mode      = AddrModeFlat;
    m_pframe->AddrFrame.Offset    = pctx->Ebp;
    m_pframe->AddrFrame.Mode      = AddrModeFlat;
    #else
    m_pframe->AddrPC.Offset       = (DWORD)pctx->Fir;
    m_pframe->AddrPC.Mode         = AddrModeFlat;
    m_pframe->AddrReturn.Offset   = (DWORD)pctx->IntRa;
    m_pframe->AddrReturn.Mode     = AddrModeFlat;
    m_pframe->AddrStack.Offset    = (DWORD)pctx->IntSp;
    m_pframe->AddrStack.Mode      = AddrModeFlat;
    m_pframe->AddrFrame.Offset    = (DWORD)pctx->IntFp;
    m_pframe->AddrFrame.Mode      = AddrModeFlat;
    #endif

	m_pctx = pctx;
	return StackNext();
}

//////////////////////////////////////////////////////////////////////////
bool CSymEngine::StackNext  ()
{
	if (!m_pframe || !m_pctx) 
	{		
		return false;
	}

	m_dwESP		= 0;
	m_dwEBP		= 0;
	
	SetLastError(0);
	HANDLE hProc = GetCurrentProcess();
	BOOL r = StackWalk (IMAGE_FILE_MACHINE_I386,
				hProc, 
				GetCurrentThread(), 
				m_pframe, 
				m_pctx,
                (PREAD_PROCESS_MEMORY_ROUTINE)My_ReadProcessMemory,
				SymFunctionTableAccess,
                SymGetModuleBase,
				0);

	if (!r || 
		!m_pframe->AddrFrame.Offset)
	{		
		return false;
	}		

	// "Debugging Applications" John Robbins
	// Before I get too carried away and start calculating
	// everything, I need to double-check that the address returned
	// by StackWalk really exists. I've seen cases in which
	// StackWalk returns TRUE but the address doesn't belong to
	// a module in the process.
	DWORD dwModBase = SymGetModuleBase (hProc, m_pframe->AddrPC.Offset);
	if (!dwModBase) 
	{	
		return false;
	}

	m_dwAddress = m_pframe->AddrPC.Offset;
	m_dwESP		= m_pframe->AddrStack.Offset;
	m_dwEBP		= m_pframe->AddrFrame.Offset;
	return true;
}

//////////////////////////////////////////////////////////////////////////
bool CSymEngine::GetModuleName (std::string& strModName)
{
	HANDLE hProc = GetCurrentProcess();
	HMODULE hMod = (HMODULE)SymGetModuleBase (hProc, m_dwAddress);
	if (!hMod) return false;

	char szFileName[MAX_PATH];
	DWORD r = GetModuleFileName(hMod, szFileName, MAX_PATH);
	if (!r) return false;
	
	szFileName[r] = 0;
	char * p = 0;
	strModName = szFileName;

	// Find the last '\' mark.
	int i = r - 1;
	for (; i >= 0; i--)
	{	
		if (szFileName[i] == '\\') 
		{
			strModName = &szFileName[i + 1]; 
			break;
		} 
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////
bool CSymEngine::LoadModuleFile(HANDLE hProcess, HMODULE hMod)
{	
	try
	{
		char filename[MAX_PATH];
		if (!GetModuleFileName(hMod, filename, MAX_PATH))
			return false;
		
		HANDLE hFile = CreateFile(filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, 0);
		if (hFile == INVALID_HANDLE_VALUE) return false;
		
		// "Debugging Applications" John Robbins	
		// For whatever reason, SymLoadModule can return zero, but it still loads the modules. Sheez.
		SetLastError(ERROR_SUCCESS);
		
		// ������ϵͳ�ĺ���Ѷ��
// 		if (strstr(filename, "system32") || strstr(filename, "Tencent") || strstr(filename, "TSVulFW.DAT"))
// 		{
// 			return false;
// 		}
		
		if (!SymLoadModule(hProcess, hFile, filename, 0, (DWORD)hMod, 0) && 
			ERROR_SUCCESS != GetLastError())
		{
			::CloseHandle(hFile);
			return false;
		}
		::CloseHandle(hFile);
		return true;
	}
	catch (...)
	{
		return false;
	}
}

//////////////////////////////////////////////////////////////////////////
bool CSymEngine::StackTrace(char* szBuf, CONTEXT * pctx, unsigned skip)
{
	CMySingleLock lock(&g_csSymEngineLock);
	return StackTrace(szBuf, *this, pctx, skip);
}

//////////////////////////////////////////////////////////////////////////
// typedef   HANDLE  (WINAPI *OPENTHREAD)   (DWORD dwFlag, BOOL bUnknow, DWORD dwThreadId);
// OPENTHREAD   OpenThread=(OPENTHREAD)::GetProcAddress(::LoadLibrary("Kernel32.dll"),"OpenThread");
bool CSymEngine::StackTrace(char* szBuf, DWORD dwThread, unsigned skip)
{
	CMySingleLock lock(&g_csSymEngineLock);

	CONTEXT context;
	HANDLE hThread = OpenThread(THREAD_ALL_ACCESS, 0, dwThread);
	if (dwThread == ::GetCurrentThreadId())
    {
		return false;
    }
    else
    {
		::SuspendThread(hThread);
		::memset(&context, 0, sizeof(CONTEXT));
		context.ContextFlags = CONTEXT_FULL;
		if (::GetThreadContext(hThread, &context) == false)
		{
			::ResumeThread(hThread);
			return false;
		}
    }

	this->StackTrace(szBuf, *this, &context, skip);
	::ResumeThread(hThread);
	return true;
}

//////////////////////////////////////////////////////////////////////////
// typedef   HANDLE  (WINAPI *RTLCAPTURECONTEXT)   (PCONTEXT context);
// RTLCAPTURECONTEXT   RtlCaptureContext=(RTLCAPTURECONTEXT)::GetProcAddress(::LoadLibrary("Kernel32.dll"),"RtlCaptureContext");
bool CSymEngine::StackTrace(char* szBuf)
{
	CMySingleLock lock(&g_csSymEngineLock);

	CONTEXT context;
	::memset(&context, 0, sizeof(CONTEXT));
	context.ContextFlags = CONTEXT_FULL;
	RtlCaptureContext(&context);
	this->StackTrace(szBuf, *this, &context, 0);
	return true;
}

//////////////////////////////////////////////////////////////////////////
bool CSymEngine::StackTrace(char* pszBuf, CSymEngine& sym, CONTEXT * pctx, unsigned skip)
{	
	std::string strtmp = "";
	if (!sym.StackFirst(pctx)) 
		return false;
	do
	{
		if (!skip)
		{			
			std::string strModule = "?";
			sym.GetModuleName(strModule);

			std::string strFile = "?.?";
			DWORD dwLine = sym.GetFileLine(strFile);
			char szLine[20];
			sprintf(szLine, "(%u) : ", dwLine);

			std::string strSymbol = "?()";
			sym.GetSymbol(strSymbol);

			strtmp += strFile;
			strtmp += szLine;
			strtmp += strModule;
			strtmp += "-->";
			strtmp += strSymbol;
			strtmp +="()\n";
		}
		else
		{
			--skip;
		}
	}
	while (sym.StackNext());
	__int64 i64TimeEnd = ::GetUtcMillisecond();

	char szTempBuffer[60] = "";
	sprintf(szTempBuffer, "This Stack Use [%I64d] ms!", i64TimeEnd - m_i64TimeStart);
	strtmp += szTempBuffer;

	strncpy(pszBuf, strtmp.c_str(), OLD_MAX_STACK_BUFF_SIZE - 1);
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description:  ��ջ��һ��, ����ֻ��¼ʱ��
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: None
////////////////////////////////////////////////////////////////////////
bool CSymEngine::StackTraceOnlyTime(void)
{
	CMySingleLock lock(&g_csSymEngineLock);

	CONTEXT context;
	::memset(&context, 0, sizeof(CONTEXT));
	context.ContextFlags = CONTEXT_FULL;
	RtlCaptureContext(&context);

	unsigned int skip = 0;
	if (!this->StackFirst(&context)) 
	{
		return false;
	}
	do
	{
		if (!skip)
		{			
			std::string strModule = "?";
			this->GetModuleName(strModule);

			std::string strFile = "?.?";
			DWORD dwLine = this->GetFileLine(strFile);

			std::string strSymbol = "?()";
			bool bGetSymbol = this->GetSymbol(strSymbol);
		}
		else
		{
			--skip;
		}
	}
	while (this->StackNext());
	__int64 i64TimeEnd = ::GetUtcMillisecond();

	::LogStackWithOutLine("CSymEngine::StackTraceOnlyTime Use [%I64d] ms!", i64TimeEnd - m_i64TimeStart);
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description:  ��ӡ��ǰ�̵߳���ջ
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool CSymEngine::StackTraceEx(const char* pszFileName, UINT unFileCount, const char* pszOtherInfo)
{
	if (NULL == pszFileName)
	{
		return false;
	}

	if (NULL == pszOtherInfo)
	{
		return false;
	}

	CMySingleLock lock(&g_csSymEngineLock);

	CONTEXT context;
	::memset(&context, 0, sizeof(CONTEXT));
	context.ContextFlags = CONTEXT_FULL;
	RtlCaptureContext(&context);

	bool bFirst = true;
	unsigned int skip = 0;
	std::string strtmp = pszOtherInfo;
	strtmp += "\n";
	if (!this->StackFirst(&context)) 
	{
		return false;
	}
	do
	{
		if (!skip)
		{			
			std::string strModule = "?";
			this->GetModuleName(strModule);

			std::string strFile = "?.?";
			DWORD dwLine = this->GetFileLine(strFile);
			char szLine[20];
			sprintf(szLine, "(%u) : ", dwLine);

			std::string strSymbol = "?()";
			bool bGetSymbol = this->GetSymbol(strSymbol);

			strtmp += strFile;
			strtmp += szLine;
			strtmp += strModule;
			strtmp += "-->";
			strtmp += strSymbol;

			if (bGetSymbol)
			{
				std::string strLocalVar;
				this->GetLocalVariables(strLocalVar);
				strtmp += strLocalVar;
			}
			
			if (strtmp.size() > NEW_SUB_STACK_LOG_SIZE)
			{
				if (bFirst)
				{
					bFirst = false;
					::LogStack(pszFileName, unFileCount, strtmp.c_str());
				}
				else
				{
					::LogStackWithOutLine(strtmp.c_str());
				}
				strtmp.clear();
			}
			else
			{
				strtmp +="\n";
			}
		}
		else
		{
			--skip;
		}
	}
	while (this->StackNext());
	__int64 i64TimeEnd = ::GetUtcMillisecond();

	char szTempBuffer[60] = "";
	sprintf(szTempBuffer, "This Stack Use [%I64d] ms!", i64TimeEnd - m_i64TimeStart);
	strtmp += szTempBuffer;

	if (bFirst)
	{
		::LogStack(pszFileName, unFileCount, strtmp.c_str());
	}
	else
	{
		::LogStackWithOutLine(strtmp.c_str());
	}
	
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description:  ��ñ��ر���ǰ10��
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: None
////////////////////////////////////////////////////////////////////////
bool CSymEngine::GetLocalVariables(std::string& strLocalVariables)
{
	try
	{
		if (0 == m_dwEBP || 0 == m_dwESP)
		{
			strLocalVariables = "(Register Empty Error)";
			return false;
		}

		DWORD* pCurFP = (DWORD *)m_dwEBP;
		DWORD pRetAddrInCaller = (*((DWORD *)(pCurFP + 1)));
		if (0==pCurFP || 0 == pRetAddrInCaller)
		{
			strLocalVariables = "(Get Value Error)";
			return false;
		}

		int argsNum = 0;
		if (m_dwEBP - m_dwESP >= 4 + GET_LOCAL_VARIABLES_NUMBER * 4)
		{
//			argsNum = this->GetFuncArgsNum(pRetAddrInCaller);
			argsNum = GET_LOCAL_VARIABLES_NUMBER;
		}

		strLocalVariables += "(";

		// ��ӡ10�����������򱾵ر���, ��תΪint��ӡ
		if (GET_LOCAL_VARIABLES_NUMBER == argsNum)
		{
			argsNum--;
			char szBuffer[32] = "";

			for(DWORD i = 0; i < argsNum; i++)
			{
				_snprintf(szBuffer, sizeof(szBuffer) - 1, "%d, ", this->GetLocalVariablesValue(m_dwEBP, i));
				strLocalVariables += szBuffer;
			}

			// ��ӡ���һ��, �Ű��ʽ��ͬ
			_snprintf(szBuffer, sizeof(szBuffer) - 1, "%d)", this->GetLocalVariablesValue(m_dwEBP, argsNum));
			strLocalVariables += szBuffer;
		}
		else
		{
			strLocalVariables += "void)";
		}

		return true;
	}
	catch (...)
	{
		strLocalVariables = "(Crash Error)";
		return false;
	}
}

////////////////////////////////////////////////////////////////////////
// Description:  ����EBP�Ĵ����͵ڼ���ƫ��ֵ  �����ֵ, ǿתint����
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: int
////////////////////////////////////////////////////////////////////////
int CSymEngine::GetLocalVariablesValue(DWORD dwEBP, DWORD dwIndex)
{
	return *(int*)(dwEBP + ((dwIndex + 2) << 2));
}

////////////////////////////////////////////////////////////////////////
// Description:  ���غ�����������
// Arguments:	 ���������bug, �������к�������Add esp���ָ��, ���Ե��ô��ѷ���
// Author: ������(Peng Wenqi)
// Return Value: int
////////////////////////////////////////////////////////////////////////
int CSymEngine::GetFuncArgsNum(int retAddrs)
{
	if(0xC483 == *(WORD *)retAddrs) // 0xC483 ''Add esp, xxx''
	{
		return *(BYTE*)(retAddrs + 2) >> 2;
	}
	else
	{
		return 0;
	}
}


