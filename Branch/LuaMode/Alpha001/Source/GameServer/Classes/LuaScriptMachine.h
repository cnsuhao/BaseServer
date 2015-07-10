////////////////////////////////////////////////////////////////////////
// Import : �ű�״̬��
// Moudle : LuaScriptMachine.h 
// Author : �½���(Chen Jianjun)
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
typedef std::map<std::string, std::string> MAP_LUA_TEXT_STRING;

class CLuaScriptMachine  
{
	// ����ʵ��
public:
	static	CLuaScriptMachine*	GetInstance(void)	{if (NULL == s_pInstance) s_pInstance = new CLuaScriptMachine; return s_pInstance;}
	static	void				DelInstance(void)	{SAFE_DELETE(s_pInstance);}
	bool	Init				(void);
	void	Release				(void);
	bool	RegeditInterface	(void);
	MYHEAP_DECLARATION(s_heap);
private:
	CLuaScriptMachine() :m_LuaState(true) {};
	virtual ~CLuaScriptMachine() {}
	CLuaScriptMachine(const CLuaScriptMachine&) :m_LuaState(true) {}
	static CLuaScriptMachine*	s_pInstance;

	// ���нű��ӿ�
public:
	bool	RunScriptFunction	(const char* pszFileName, const char* pszTxtScript);

private:
	LuaPlus::LuaStateOwner	m_LuaState;

	// lua�ַ���
public:
	const char*	GetLuaText		(OBJID idLuaText);
	bool		SetLuaTextString(const char* pszParamName, const char* pszString);

private:
	MAP_LUA_TEXT_STRING m_mapLuaTextString;

	// �������뷵��ֵ
public:
	bool		IsHasError		(void) const	{ return m_strLastError.size() > 0; }
	const char* GetLastError	(void) const	{ return m_strLastError.c_str(); }
	bool		GetResult		(void) const	{ return m_bLuaResult; }
	void		SetResult		(bool bResult)	{ m_bLuaResult = bResult; }
private:
	std::string	m_strLastError;
	bool		m_bLuaResult;

	// �ű��ļ�����
public:
	bool		ReLoadLuaFileCache	(void);
	std::string GetLuaFileKey		(const std::string& strInputFileName) const;
	void		SetDebugFlag		(bool bDebug){m_bDebug = bDebug;}
private:
	void		AutoLoadLuaFileCache(const std::string& strLuaFileName);
	int			LoadLuaFileToStack	(const std::string& strLuaFileName);
	bool		SaveLastLuaError	(int nLuaRet, const char* pszFileName);
	MAP_LUA_CACHE	m_mapLuaCache;
	bool			m_bDebug;
	
	// �ӿ�ע��ģ��
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
			///����ű��еĶ���
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
