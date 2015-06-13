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

// 线程互斥量, 全局只能有唯一的这东西在运行
CSimpleCriticalSection	g_csSymEngineLock;

const int OLD_MAX_STACK_BUFF_SIZE	= 3584;	// 旧版本, 最多写入堆栈的日志大小
const int NEW_SUB_STACK_LOG_SIZE	= 2048;	// 新版本, 堆栈日志分段写入大小
const int GET_LOCAL_VARIABLES_NUMBER = 10;	// 只获取前十个本地变量的值

/*  
-------------------  下面为选项符号解释  -------------------
SYMOPT_CASE_INSENSITIVE
	该选项使得所有对符号名的搜索区分大小写。
	所有调试器中该选项默认打开。调试器运行之后，可以通过.symopt+0x1 或.symopt-0x1打开或关闭。
	DBH中该选项默认打开。DBH运行时，可以通过symopt +1 或symopt -1来打开或关闭。

SYMOPT_UNDNAME
	该选项使得公有符号名被显示或搜索时都忽略修饰符。私有符号不管该选项是否激活都永远不会被修饰。关于符号名修饰符的更多信息，查看公有和私有符号。
	所有调试器中该选项默认打开。调试器运行后，可以通过.symopt+0x2 或.symopt-0x2打开或关闭。
	DBH中该选项默认打开。可以通过-d命令行选项关闭。DBH运行时，可以通过symopt +2 或symopt -2打开或关闭。

SYMOPT_DEFERRED_LOADS
	该选项称为延迟符号加载(deferred symbol loading 或lazy symbol loading)。激活时，当目标模块加载时并不实际加载符号，而是等到调试器用到的时候才加载。查看延迟符号加载获取详细信息。
	所有调试器默认打开该选项。在CDB和KD中，-s命令行选项可以关闭它。对于CDB也可以通过使用tools.ini文件的LazyLoad变量来关闭。调试器运行时，通过.symopt+0x4 或.symopt-0x4,来打开或关闭。
	DBH中该选项默认关闭。DBH运行时可通过symopt +4 或symopt -4来打开或关闭。

SYMOPT_NO_CPP
	该选项关闭C++转换。设置了这个选项时，所有符号中的::都被__ 替代。
	所有调试器默认关闭该选项。它可以通过-snc命令行选项打开。调试器运行时，通过.symopt+0x8 或.symopt-0x8来打开关闭。
	DBH默认关闭该选项。运行时通过symopt +8 或symopt -8来打开关闭。

SYMOPT_LOAD_LINES
	该选项允许从源码文件中读取行号信息。必须打开才能使得源码调试正确工作。
	在KD和CDB中该选项默认关闭；在WinDbg中默认打开。对于CDB和KD可以通过-lines 命令行选项来打开。调试器运行时，可以通过.symopt+0x10 或.symopt-0x10来打开关闭。也可以通过.lines (Toggle Source Line Support)命令来打开或关闭。
	DBH中默认打开该选项。运行时可以通过symopt +10 或symopt -10来打开关闭。

SYMOPT_OMAP_FIND_NEAREST
	当代码被优化，并且期望的位置没有符号时，启用该选项会用最靠近的符号来替代。
	所有调试器默认打开该选项。运行时，通过.symopt+0x20 或.symopt-0x20来打开关闭。
	DBH中默认打开。运行时可以通过symopt +20 或symopt -20来打开关闭。

SYMOPT_LOAD_ANYTHING
	该选项降低符号处理器尝试匹配符号时的精确性。
	所有调试器默认关闭。运行时可以通过.symopt+0x40 或.symopt-0x40来打开关闭。
	DBH中默认关闭。运行时通过symopt +40 或symopt -40来打开关闭。

SYMOPT_IGNORE_CVREC
	该选项使得符号处理器在搜索符号时，忽略已加载模块映像头中的CV记录。
	有调试器中默认关闭。可以通过-sicv 命令行选项打开。运行时通过.symopt+0x80 或.symopt-0x80打开关闭。
	DBH中默认关闭。运行时通过symopt +80 或symopt -80打开关闭。

SYMOPT_NO_UNQUALIFIED_LOADS
	该选项禁止符号处理器自动为模块进行加载。设置这个选项并且调试器尝试匹配某个符号时，它只会在已加载模块中搜索。
	这个选项可以用来避免误输入符号名的问题。通常，误输入符号使得调试器搜索所有卸载的符号文件时暂停。使用该选项，误输入的符号在已加载模块中找不到，所以搜索就会被中止。
	所有调试器默认关闭该选项。可以通过-snul命令行选项激活。运行时通过.symopt+0x100 或.symopt-0x100打开关闭。
	DBH中默认关闭。运行时通过symopt +100 或symopt -100打开关闭。

SYMOPT_FAIL_CRITICAL_ERRORS
	这个选项使得文件访问错误对话框被取消掉。
	如果该选项关闭，再符号加载时遇到的类似"驱动器未准备好"这样的文件访问错误，会出现一个对话框。如果该选项打开，这些对话框不会出现，并且所有访问错误都会收到一条"fail"的响应。
	所有调试器默认打开该选项。可以通过-sdce命令行选项来关闭。运行时通过.symopt+0x200 或.symopt-0x200来打开关闭。
	DBH默认关闭。运行时，通过symopt +200 或symopt -200来打开关闭。

SYMOPT_EXACT_SYMBOLS
	这个选项使得调试器对所有符号文件进行严格的匹配。
	打开时，即使符号文件和符号处理器的要求有很小的差异，这些符号也会被忽略。 
	调试器默认关闭该选项。可以通过-ses来激活。运行时，通过.symopt+0x400 或.symopt-0x400来打开关闭。
	-failinc命令行选项也打开SYMOPT_EXACT_SYMBOLS。另外，如果调试用户模式minidump或内核模式minidump， -failinc将防止调试器加载任何映像不能被映射的模块。
	DBH中默认打开。运行时通过symopt +400 或symopt -400来打开关闭。

SYMOPT_ALLOW_ABSOLUTE_SYMBOLS
	该选项使得DbgHelp可以读取保存在内存某个绝对地址中的符号。绝大多数情况下不需要该选项。
	所有调试器中默认关闭。运行时通过.symopt+0x800 或.symopt-0x800来打开关闭。
	DBH中默认打开。运行时通过symopt +800 或symopt -800来打开关闭。


SYMOPT_IGNORE_NT_SYMPATH
	该选项使得调试器忽略环境变量中设置的符号路径和可执行映像路径。
	所有调试器默认关闭该选项。可以通过-sins命令行选项激活。但是，运行时不能通过.symopt 命令来控制，因为环境变量仅在启动时会被读取。
	DBH中默认关闭，并且任何情况下都会被DBH忽略。

SYMOPT_INCLUDE_32BIT_MODULES
	这个选项强制DbgHelp和ImageHlp在枚举Intel Itanium处理器上的32位模块。
	所有调试器默认关闭该选项。运行时通过.symopt+0x2000 或.symopt-0x2000来打开关闭。
	DBH中默认关闭。运行时通过symopt +2000 或symopt -2000打开关闭。

SYMOPT_PUBLICS_ONLY
	这个选项使得DbgHelp忽略私有符号数据，仅在公有符号表中搜索符号信息。这是模拟DbgHelp加入对这些类型的支持之前的行为。查看公有和私有符号。
	所有调试器中都默认关闭。运行时通过.symopt+0x4000 或.symopt-0x4000来打开关闭。
	DBH 中默认关闭。可以通过-d命令行选项打开。运行时通过symopt +4000 或symopt -4000打开关闭。

SYMOPT_NO_PUBLICS
	该选项阻止DbgHelp搜索公有符号表。这使得符号枚举和搜索变得更快。如果比较关心搜索速度，那么SYMOPT_AUTO_PUBLICS 选项比较适合。关于公有符号表的信息，查看公有和私有符号。
	所有调试器中默认关闭。运行时，通过.symopt+0x8000 或.symopt-0x8000打开关闭。
	DBH中默认关闭。运行时通过symopt +8000 或symopt -8000打开关闭。


SYMOPT_AUTO_PUBLICS
	这个选项使得DbgHelp将在.pdb中搜索公有符号表作为最后的选择。如果在私有符号中找到了任何匹配，公有符号就不会再被搜索。这样会提高搜索速度。
	所有调试器中默认打开。可以通过-sup命令行选项关闭。运行时通过.symopt+0x10000 或.symopt-0x10000打开关闭。
	DBH中默认打开。使用-d命令行选项时会被关掉。运行时，使用symopt +10000 或symopt -10000打开关闭。

SYMOPT_NO_IMAGE_SEARCH
	这个选项避免在加载符号时DbgHelp搜索磁盘查找映象文件的拷贝。
	所有调试器中默认打开。运行时通过.symopt+0x20000 或.symopt-0x20000打开关闭。
	DBH中默认关闭。运行时通过symopt +20000 或symopt -20000打开关闭。

SYMOPT_SECURE
	(仅内核模式) 该选项指示是否激活了安全模式。
	所有调试器默认关闭。可以通过-secure命令行选项激活。如果调试器正在运行、在静止模式下，并且没有建立任何调试服务器，可以通过.symopt+0x40000 或.secure (Activate Secure Mode)来打开安全模式。
	DBH中默认关闭。运行时通过symopt +40000 或symopt -40000来打开关闭。
	安全模式一旦激活之后就不能再关闭。

SYMOPT_NO_PROMPTS
	这个选项阻止来自代理服务器的验证对话框。这可能使得SymSrv 不能访问internet上的符号存储。
	详细信息，查看防火墙和代理服务器。
	在KD和CDB中，该选项默认打开；WinDbg中默认关闭。调试器运行时可以通过.symopt+0x80000 或.symopt-0x80000，后跟.reload (Reload Module)命令来打开或关闭。也可以使用!sym prompts off和!sym prompts扩展命令，后跟.reload (Reload Module)命令了来打开关闭。
	DBH中默认关闭。运行时通过symopt +80000 或symopt -80000来打开关闭。

SYMOPT_DEBUG
	该选项打开详细符号加载(noisy symbol loading)。他使得调试器搜索符号时显示信息。
	所有符号文件加载时会显示名字。如果调试器不能加载某个符号文件，会显示错误信息。.pdb文件的错误信息以文本方式显示，.dbg文件的错误信息以错误码方式显示。这些错误码在winerror.h文件中说明。
	如果某个映像文件被重新加载以获取符号化的头信息，也会被显示出来。
	所有调试器默认关闭该选项。可以通过-n命令行选项激活。运行时通过.symopt+0x80000000 或.symopt-0x80000000来打开关闭。也可以通过!sym noisy 和 !sym quiet命令来打开或关闭。
	注意 这个选项不能和详细源码加载(noisy source loading)混淆 — 它是用.srcnoisy (Noisy Source Loading)命令来控制的。
	DBH中默认关闭。可以使用-n命令行选项激活。DBH运行时，可以通过symopt +80000000 或symopt -80000000来打开或关闭。也可以通过verbose on 和verbose off 命令来打开或关闭。
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
		::SymSetOptions(SymGetOptions()|SYMOPT_EXACT_SYMBOLS|SYMOPT_LOAD_LINES);		// 打开严格符号匹配与行号加载
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
		
		// 不加载系统的和腾讯的
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
// Description:  堆栈过一遍, 但是只记录时间
// Arguments:
// Author: 彭文奇(Peng Wenqi)
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
// Description:  打印当前线程调用栈
// Arguments:
// Author: 彭文奇(Peng Wenqi)
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
// Description:  获得本地变量前10个
// Arguments:
// Author: 彭文奇(Peng Wenqi)
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

		// 打印10个函数参数或本地变量, 均转为int打印
		if (GET_LOCAL_VARIABLES_NUMBER == argsNum)
		{
			argsNum--;
			char szBuffer[32] = "";

			for(DWORD i = 0; i < argsNum; i++)
			{
				_snprintf(szBuffer, sizeof(szBuffer) - 1, "%d, ", this->GetLocalVariablesValue(m_dwEBP, i));
				strLocalVariables += szBuffer;
			}

			// 打印最后一个, 排版格式不同
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
// Description:  根据EBP寄存器和第几个偏移值  获得其值, 强转int返回
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: int
////////////////////////////////////////////////////////////////////////
int CSymEngine::GetLocalVariablesValue(DWORD dwEBP, DWORD dwIndex)
{
	return *(int*)(dwEBP + ((dwIndex + 2) << 2));
}

////////////////////////////////////////////////////////////////////////
// Description:  返回函数参数个数
// Arguments:	 这个函数有bug, 不是所有函数都有Add esp汇编指令, 所以调用处已废弃
// Author: 彭文奇(Peng Wenqi)
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


