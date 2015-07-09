////////////////////////////////////////////////////////////////////////
// Import : 脚本状态机
// Moudle : LuaScriptMachine.h 
// Author : 陈建军(Chen Jianjun)
// Create : 2015-6-19
////////////////////////////////////////////////////////////////////////
#ifndef _LUA_SCRIPT_MACHINE_H_
#define _LUA_SCRIPT_MACHINE_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define LUAPLUS_LIB

#include "../share/define.h"
#include "../LuaPlus/LuaPlus.h"

typedef std::map<std::string, std::string> MAP_LUA_CACHE;

const int MAX_LUA_PARAM_COUNT = 5;	// lua最多可传入参数
struct MY_LUA_INFO 
{
	OBJID	idUser;
	OBJID	idAction;
	int		nParam[MAX_LUA_PARAM_COUNT + 1];
};
typedef std::stack<MY_LUA_INFO>	STACK_LUA_INFO;

typedef std::map<std::string, std::string> MAP_LUA_TEXT_STRING;

class CLuaScriptMachine  
{
	// 单例实现
public:
	static CLuaScriptMachine*	GetInstance(void)	{if (NULL == s_pInstance) s_pInstance = new CLuaScriptMachine; return s_pInstance;}
	static void					DelInstance(void)	{SAFE_DELETE(s_pInstance);}
	bool Init();
	void Release();
	bool RegeditInterface();
	MYHEAP_DECLARATION(s_heap);
private:
	CLuaScriptMachine() :m_LuaState(true) {};
	virtual ~CLuaScriptMachine() {}
	CLuaScriptMachine(const CLuaScriptMachine&) :m_LuaState(true) {}
	static CLuaScriptMachine*	s_pInstance;

	// 环境变量接口
public:
	OBJID	GetUserID(void)	const {return m_stNowStack.idUser;}
	int		GetActionID(void)const {return m_stNowStack.idAction;}
	int		GetParam(int nIndex) const		{CHECKF(nIndex >= 0 && nIndex <= MAX_LUA_PARAM_COUNT);return m_stNowStack.nParam[nIndex];}
	bool	GetResult(void) const {return m_bLuaResult;}
	void	SetResult(bool bResult){m_bLuaResult = bResult;}

	// 运行脚本接口
public:
	bool SetLuaEnv(OBJID idUser = ID_NONE, OBJID idAction = ID_NONE);				// 设置运行环境
	void SetParam(int nIndex, int nData)	{CHECK(nIndex >= 0 && nIndex <= MAX_LUA_PARAM_COUNT);m_stNowStack.nParam[nIndex] = nData;}	
	bool RunScriptFunction(const char* pszFileName, const char* pszTxtScript);		// 函数执行
	bool ProcessAction(OBJID idAction, OBJID idUser = ID_NONE, int nParam1 = 0, int nParam2 = 0, int nParam3 = 0, int nParam4 = 0, int nParam5 = 0);
	bool ProcessLuaFunction(const char* pszFileName, const char* pszTxtFunction, OBJID idUser = ID_NONE, int nParam1 = 0, int nParam2 = 0, int nParam3 = 0, int nParam4 = 0, int nParam5 = 0);

	// 基本成员
private:
	LuaPlus::LuaStateOwner	m_LuaState;

	// 自定义信息栈
private:
	void			SetNowStack	(const MY_LUA_INFO& rInfo);
	void			ResetStack	(void);
	void			PushStack	(void);
	void			PopStack	(void);
	STACK_LUA_INFO	m_stackInfo;
	MY_LUA_INFO		m_stNowStack;

	// lua字符串
public:
	const char*		GetLuaText(OBJID idLuaText);
	bool			SetLuaTextString(const char* pszParamName, const char* pszString);
private:
	MAP_LUA_TEXT_STRING m_mapLuaTextString;

	// 错误码与返回值
public:
	bool		IsHasError()			const {return m_strLastError.size() > 0;}
	const char* GetLastError()			const {return m_strLastError.c_str();}
private:
	std::string		m_strLastError;
	bool			m_bLuaResult;


	// 脚本文件缓存
public:
	bool		ReLoadLuaFileCache(void);
	std::string GetLuaFileKey(const std::string& strInputFileName) const;
	void		SetDebugFlag(bool bDebug){m_bDebug = bDebug;}
private:
	void		AutoLoadLuaFileCache(const std::string& strLuaFileName);
	int			LoadLuaFileToStack(const std::string& strLuaFileName);
	bool		SaveLastLuaError(int nLuaRet, const char* pszFileName);
	MAP_LUA_CACHE	m_mapLuaCache;
	bool			m_bDebug;
	
	// 接口注册模板
private:
	template <typename Callee, typename Func>
		void RegisterObjectDirect(const char* objname,const char* classname,const char* funname, Callee* callee, Func func)
		{
			LuaPlus::LuaObject mt=m_LuaState->GetGlobals().GetByName(classname);
			if(mt.IsNil())
			{
				mt= m_LuaState->GetGlobals().CreateTable(classname);
				mt.SetMetaTable(mt);
				mt.SetObject("__index", mt);
			}
			mt.RegisterObjectDirect(funname, (Callee*)0, func);
			///处理脚本中的对象
			LuaPlus::LuaObject luaObject=m_LuaState->GetGlobals().GetByName(objname);
			if(luaObject.IsNil())
			{
				luaObject.AssignNewTable(m_LuaState);
				luaObject.SetMetaTable(m_LuaState->GetGlobal(classname));
			}
			luaObject.SetLightUserData("__object",callee);
			m_LuaState->GetGlobals().SetObject(objname, luaObject);
		}
};

#define pLuaScriptMachine CLuaScriptMachine::GetInstance()

#endif // end of _LUA_SCRIPT_MACHINE_H_
