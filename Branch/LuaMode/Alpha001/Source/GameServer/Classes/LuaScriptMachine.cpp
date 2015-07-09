////////////////////////////////////////////////////////////////////////
// Import : �ű�״̬��
// Moudle : LuaScriptMachine.cpp 
// Author : �½���(Chen Jianjun)
// Create : 2015-6-19
////////////////////////////////////////////////////////////////////////
#include "./LuaScriptMachine.h"
#include <sstream>
#include <fstream>

CLuaScriptMachine* CLuaScriptMachine::s_pInstance = NULL;
MYHEAP_IMPLEMENTATION(CLuaScriptMachine, s_heap);

//////////////////////////////////////////////////////////////////////////
bool CLuaScriptMachine::Init()
{
#ifdef _DEBUG
	m_bDebug = true;
#else
	m_bDebug = false;
#endif

	ZeroMemory(&m_stNowStack, sizeof(m_stNowStack));

	// ע��C++�����ӿ�
	CHECKF(this->RegeditInterface());

	// ִ��lua�����ļ�
	//CHECKF(this->RunScriptFunction("startup.lua", "start()"));
	return true;
}

//////////////////////////////////////////////////////////////////////////
void CLuaScriptMachine::Release()
{

}

////////////////////////////////////////////////////////////////////////
// Description: �������л���
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool CLuaScriptMachine::SetLuaEnv( OBJID idUser /*= ID_NONE*/, OBJID idAction /*= ID_NONE*/ )
{
	m_bLuaResult = false;
	m_stNowStack.idUser = idUser;
	m_stNowStack.idAction = idAction;
	for (int i = 0; i < MAX_LUA_PARAM_COUNT; i++)
	{
		m_stNowStack.nParam[i] = 0;
	}
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description:  ���нű�����
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: bool  ��ʾ�ű��Ƿ�ɹ�ִ��(�﷨��)
////////////////////////////////////////////////////////////////////////
bool CLuaScriptMachine::RunScriptFunction(const char* pszFileName,const char* pszTxtScript)
{
	CHECKF(pszFileName);
	CHECKF(pszTxtScript);
	bool bThisResult = false;

	CMxyString strTimeLog("%s - %s", pszFileName, pszTxtScript);
	CTimeCostChk objCostChk("CLuaScriptMachine::RunScriptFunctionReal", strTimeLog.c_str(), 50, __FILE__, __LINE__);

	try
	{
		std::string strLuaFileName(pszFileName);
		::ReplaceStdString(strLuaFileName, "\\", "/");														// ͳһб��
		std::transform(strLuaFileName.begin(), strLuaFileName.end(), strLuaFileName.begin(), ::tolower);	// ��ΪСд

		// ��׺
		if (strLuaFileName.npos == strLuaFileName.find(".lua"))
		{
			strLuaFileName += ".lua";
		}
		
		// ·��
		if (strLuaFileName.npos == strLuaFileName.find(LUA_FILE_PATH))
		{
			strLuaFileName = LUA_FILE_PATH + strLuaFileName;
		}

		this->PushStack();	// �Զ�����Ϣջѹջ

		this->AutoLoadLuaFileCache(strLuaFileName);				// �Զ�����lua�ļ�������(����Ѿ������޴���, ��δ���ص��½ű��Զ����뻺��)
		int nLuaRet = this->LoadLuaFileToStack(strLuaFileName);	// ����lua�ļ���luaջ��
		bThisResult = this->SaveLastLuaError(nLuaRet, strLuaFileName.c_str());
		if (bThisResult)
		{
			nLuaRet = m_LuaState->PCall(0,0,0);					// ִ��lua
			bThisResult = this->SaveLastLuaError(nLuaRet, strLuaFileName.c_str());

			if (bThisResult)
			{
				nLuaRet = m_LuaState->DoString(pszTxtScript);
				bThisResult = this->SaveLastLuaError(nLuaRet, strLuaFileName.c_str());
			}
		}
		
		this->PopStack();	// �Զ�����Ϣջ��ջ
	}
	catch (LuaPlus::LuaException& e)
	{
		this->ResetStack();	// ����Զ�����Ϣջ
		const char* pszErrorMsg = e.GetErrorMessage();
		CHECKF(pszErrorMsg);
		::LogLuaError("CLuaScriptMachine::RunScriptFunction crash! File[%s] Error[%s]", pszFileName, pszErrorMsg);
	}
	catch (...)
	{
		this->ResetStack();	// ����Զ�����Ϣջ
		STACK_TRACE_ONCE; 
		::LogSave("CLuaScriptMachine::RunScriptFunction crash:[%s]", pszFileName);
	}
	return bThisResult;
}

////////////////////////////////////////////////////////////////////////
// Description: ����action idִ�нű�
// Arguments:	���ؽű���Result
// Author: ������(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool CLuaScriptMachine::ProcessAction( OBJID idAction, OBJID idUser /*= ID_NONE*/, int nParam1 /*= 0*/, int nParam2 /*= 0*/, int nParam3 /*= 0*/, int nParam4 /*= 0*/, int nParam5 /*= 0*/ )
{
	CHECKF(idAction);
	return this->GetResult();
}

////////////////////////////////////////////////////////////////////////
// Description: ָ���ļ��뺯������ִ��
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool CLuaScriptMachine::ProcessLuaFunction( const char* pszFileName, const char* pszTxtFunction, OBJID idUser /*= ID_NONE*/, int nParam1 /*= 0*/, int nParam2 /*= 0*/, int nParam3 /*= 0*/, int nParam4 /*= 0*/, int nParam5 /*= 0*/ )
{
	CHECKF(pszFileName && pszTxtFunction);
	CHECKF(this->SetLuaEnv(idUser));
	this->SetParam(1, nParam1);
	this->SetParam(2, nParam2);
	this->SetParam(3, nParam3);
	this->SetParam(4, nParam4);
	this->SetParam(5, nParam5);
	CHECKF(this->RunScriptFunction(pszFileName, pszTxtFunction));
	return this->GetResult();
}

////////////////////////////////////////////////////////////////////////
// Description:  ���¼��ؽű�����
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool CLuaScriptMachine::ReLoadLuaFileCache( void )
{
	m_mapLuaCache.clear();

	char szCmd[128] = "";
	sprintf(szCmd, "del %s /q /f", LUA_LIST_FILE);
	system(szCmd);
	sprintf(szCmd, "dir *.lua /b /s /n >> %s", LUA_LIST_FILE);
	system(szCmd);

	std::ifstream infile(LUA_LIST_FILE, std::ios::in);
	std::string textline;
	int nCount = 0;
	int nTotalFileSize = 0;
	while (std::getline(infile,textline,'\n'))
	{
		DEAD_LOOP_BREAK(nCount, 10000);		// ����ȡ1W���ű��ļ�
		std::string strBufferKey	= this->GetLuaFileKey(textline);
		if (strBufferKey.find(LUA_ERROR_KEY) != strBufferKey.npos)
		{
			tolog2("CLuaScriptMachine::ReLoadLuaFileCache Key Error! LuaFileName[%s]", textline.c_str());
			continue;
		}

		if (m_mapLuaCache.find(strBufferKey) == m_mapLuaCache.end())
		{
			std::string strBuffer	= ::LoadFileToString(strBufferKey);	
			m_mapLuaCache[strBufferKey] = strBuffer;
			nTotalFileSize += strBuffer.size();
		}
		else
		{
			::LogLuaError("CLuaScriptMachine::ReLoadLuaFileCache Find Repeat Key! [%s]", strBufferKey.c_str());
		}
	}
	infile.close();

	int nTotalFileMbytes = (nTotalFileSize / 1024) / 1024;
	int nTotalFileKbytes = (nTotalFileSize / 1024) % 1024;

	::LogSave("CLuaScriptMachine::ReLoadLuaFileCache OK! nCount[%d], TotalFileSize[%d]MB.[%d]KB", nCount, nTotalFileMbytes, nTotalFileKbytes);
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description:  �Զ�����lua�ļ�������
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: None
////////////////////////////////////////////////////////////////////////
void CLuaScriptMachine::AutoLoadLuaFileCache(const std::string& strLuaFileName)
{
	// debugģʽ�������¼���
	if (m_bDebug)
	{
		return;
	}

	std::string strBufferKey = this->GetLuaFileKey(strLuaFileName);
	if (strBufferKey.find(LUA_ERROR_KEY) != strBufferKey.npos)
	{
		tolog2("CLuaScriptMachine::AutoLoadLuaFileCache Key Error! LuaFileName[%s]", strLuaFileName.c_str());
		return;
	}

	// ����io���� һ��Ҫ�����ж��ڲ�����
	if (m_mapLuaCache.find(strBufferKey) == m_mapLuaCache.end())
	{
		std::string strBuffer	= ::LoadFileToString(strBufferKey);	
		m_mapLuaCache[strBufferKey] = strBuffer;
		::LogSave("CLuaScriptMachine::AutoLoadLuaFileCache Load Buffer OK! FileName:[%s], BufferSize[%d]", strLuaFileName.c_str(), strBuffer.size());
	}
}

////////////////////////////////////////////////////////////////////////
// Description:  ����LuaPlus�ӿ�, ���ű����ص�luaջ��
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: int  LuaPlus�ķ���ֵ, 0��ʾ�ɹ�, ����Ϊ������
////////////////////////////////////////////////////////////////////////
int CLuaScriptMachine::LoadLuaFileToStack(const std::string& strLuaFileName)
{
	// debugģʽ��ÿ�����¼����ļ�
	if (m_bDebug)
	{
		int nResult = m_LuaState->LoadFile(strLuaFileName.c_str());
		return nResult;
	}

	std::string strBufferKey = this->GetLuaFileKey(strLuaFileName);
	if (strBufferKey.find(LUA_ERROR_KEY) != strBufferKey.npos)
	{
		tolog2("CLuaScriptMachine::LoadLuaFileToStack Key Error! LuaFileName[%s]", strLuaFileName.c_str());
		return LUA_CUSTOM_ERROR;
	}

	MAP_LUA_CACHE::const_iterator citerBuffer = m_mapLuaCache.find(strBufferKey);
	if (m_mapLuaCache.find(strBufferKey) == m_mapLuaCache.end())
	{
		tolog3("CLuaScriptMachine::LoadLuaFileToStack Can Not Find Buffer! FileName[%s], KeyName[%s]", strLuaFileName.c_str(), strBufferKey.c_str());
		return LUA_CUSTOM_ERROR;
	} 

	const std::string& rStrBuffer = citerBuffer->second.c_str();
	int nResult = m_LuaState->LoadBuffer(rStrBuffer.c_str(), rStrBuffer.length(), strLuaFileName.c_str());
	return nResult;
}

////////////////////////////////////////////////////////////////////////
// Description:  ���lua�ļ�key(��ʵ����ȥ�����Ե�����·��, �õ����·��)
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: std::string
////////////////////////////////////////////////////////////////////////
std::string CLuaScriptMachine::GetLuaFileKey(const std::string& strInputFileName) const
{
	std::string strLuaFileName(strInputFileName);
	::ReplaceStdString(strLuaFileName, "\\", "/");														// ͳһб��
	std::transform(strLuaFileName.begin(), strLuaFileName.end(), strLuaFileName.begin(), ::tolower);	// ��ΪСд

	std::string::size_type pos = strLuaFileName.find(LUA_FILE_PATH);
	if (pos != strLuaFileName.npos) 
	{
		std::string strResult = strLuaFileName.substr(pos);
		return strResult;
	}
	else
	{
		std::string strError(LUA_ERROR_KEY);
		return strError;
	}
}

////////////////////////////////////////////////////////////////////////
// Description:  ����ű���������, �ɹ�Ҳ��Ҫ����, ��������ű�����result
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool CLuaScriptMachine::SaveLastLuaError(int nLuaRet, const char* pszFileName)
{
	DEBUG_TRY;
	std::string strLogFileName = "";
	if (pszFileName)
	{
		strLogFileName = pszFileName;
	}

	if (0 == nLuaRet)
	{
		m_strLastError="";///empty error info.
		return true;
	}
	else if (LUA_CUSTOM_ERROR == nLuaRet)
	{
		m_strLastError = "Custom";
		::LogLuaError("File[%s], Error[%s]", strLogFileName.c_str(), m_strLastError.c_str());
		return false;
	}
	else
	{
		LuaPlus::LuaObject result=m_LuaState->Stack(-1);
		if (!result.IsNil() && result.IsString())
		{
			m_strLastError = result.GetString();
		}
		else
		{
			m_strLastError="UnKown LUA Error!";
		}
		::LogLuaError("File[%s], Error[%s]", strLogFileName.c_str(), m_strLastError.c_str());
		return false;
	}
	DEBUG_CATCHF2("CLuaScriptMachine::SaveLastLuaError FileName[%s]", pszFileName);
}

////////////////////////////////////////////////////////////////////////
// Description:  ���õ�ǰ��Ϣջ�ϵĲ�������
// Arguments:	 
// Author: ������(Peng Wenqi)
// Return Value: None
////////////////////////////////////////////////////////////////////////
void CLuaScriptMachine::SetNowStack(const MY_LUA_INFO& rInfo)
{
	m_stNowStack = rInfo;
}

////////////////////////////////////////////////////////////////////////
// Description:  ����������Ϣջ����
// Arguments:	 �����ڽű������쳣���
// Author: ������(Peng Wenqi)
// Return Value: None
////////////////////////////////////////////////////////////////////////
void CLuaScriptMachine::ResetStack(void)
{
	ZeroMemory(&m_stNowStack, sizeof(m_stNowStack));
	int nCount = 0;
	while (!m_stackInfo.empty())
	{
		DEAD_LOOP_BREAK(nCount, 100);
		m_stackInfo.pop();
	}
}

////////////////////////////////////////////////////////////////////////
// Description:  �Զ�����Ϣջ ѹջ����
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: None
////////////////////////////////////////////////////////////////////////
void CLuaScriptMachine::PushStack(void)
{
	m_stackInfo.push(m_stNowStack);
}


////////////////////////////////////////////////////////////////////////
// Description:  �Զ�����Ϣջ ��ջ����
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: None
////////////////////////////////////////////////////////////////////////
void CLuaScriptMachine::PopStack(void)
{
	// ջ�ղ���
	if (m_stackInfo.empty())
	{
		return;
	}

	// ����һ��ջ��ԭ
	m_stNowStack = m_stackInfo.top();
	m_stackInfo.pop();
}

////////////////////////////////////////////////////////////////////////
// Description: ��ÿ����õ�lua����
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: const char*
////////////////////////////////////////////////////////////////////////
const char* CLuaScriptMachine::GetLuaText( OBJID idLuaText )
{
	//DEBUG_TRY;
	//IF_NOT (idLuaText)
	//{
	//	return "LuaText Error";
	//}

	//const TConstLuaText* pLuaText = pConstTableMgr->GetLuaText();
	//IF_NOT (pLuaText)
	//{
	//	return "LuaText Error";
	//}

	//if (!pLuaText->IsExist(idLuaText))
	//{
	//	CMxyString strError("LuaText[%u] not config", idLuaText);
	//	return strError.c_str();
	//}

	//static CMxyString strResult = "";
	//strResult = pLuaText->GetDataStr(idLuaText, LUA_TEXT_DATA_TEXT);
	//for (MAP_LUA_TEXT_STRING::iterator iter = m_mapLuaTextString.begin(); iter != m_mapLuaTextString.end(); iter++)
	//{
	//	int nReplaceCount = ::ReplaceStdString(strResult, iter->first.c_str(), iter->second.c_str(), true);
	//	if (nReplaceCount > 0)
	//	{
	//		CMxyString strTemp = strResult;
	//		switch (nReplaceCount)
	//		{
	//		case 1:
	//			strResult.Format(strTemp.c_str(), iter->second.c_str());
	//			break;
	//		case 2:
	//			strResult.Format(strTemp.c_str(), iter->second.c_str(), iter->second.c_str());
	//			break;
	//		case 3:
	//			strResult.Format(strTemp.c_str(), iter->second.c_str(), iter->second.c_str(), iter->second.c_str());
	//			break;
	//		case 4:
	//			strResult.Format(strTemp.c_str(), iter->second.c_str(), iter->second.c_str(), iter->second.c_str(), iter->second.c_str());
	//			break;
	//		case 5:
	//			strResult.Format(strTemp.c_str(), iter->second.c_str(), iter->second.c_str(), iter->second.c_str(), iter->second.c_str(), iter->second.c_str());
	//			break;
	//		default:
	//			return "LuaText Error too many strParam Repeat";
	//			break;
	//		}
	//	}
	//}

	//m_mapLuaTextString.clear();

	//return strResult.c_str();
	//DEBUG_CATCH2("CLuaScriptMachine::GetLuaText idLuaText[%d]", idLuaText);
	return "LuaText Error";
}

////////////////////////////////////////////////////////////////////////
// Description: ���ÿ����������е��ַ���
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool CLuaScriptMachine::SetLuaTextString( const char* pszParamName, const char* pszString )
{
	DEBUG_TRY;
	CHECKF(pszParamName && pszString);
	m_mapLuaTextString.insert(make_pair(pszParamName, pszString));
	return true;
	DEBUG_CATCHF("CLuaScriptMachine::SetLuaTextString");
}

////////////////////////////////////////////////////////////////////////
// Description:  ��ʼ��ʱע��ӿ�
// Arguments:	 ע��ӿ�ָ��ֻ�����ǹ�����������
// Author: ������(Peng Wenqi)
// Return Value: None
////////////////////////////////////////////////////////////////////////
bool CLuaScriptMachine::RegeditInterface()
{
	DEBUG_TRY;

	// �ű����ṩ������ȡ�ӿ�
	RegisterObjectDirect("Lua", "CLuaScriptMachine", "GetUserID", this, &CLuaScriptMachine::GetUserID);
	RegisterObjectDirect("Lua", "CLuaScriptMachine", "GetActionID", this, &CLuaScriptMachine::GetActionID);
	RegisterObjectDirect("Lua", "CLuaScriptMachine", "GetParam", this, &CLuaScriptMachine::GetParam);
	RegisterObjectDirect("Lua", "CLuaScriptMachine", "SetResult", this, &CLuaScriptMachine::SetResult);

	RegisterObjectDirect("Lua", "CLuaScriptMachine", "GetLuaText", this, &CLuaScriptMachine::GetLuaText);
	RegisterObjectDirect("Lua", "CLuaScriptMachine", "SetLuaTextString", this, &CLuaScriptMachine::SetLuaTextString);

	// GameAction�ṩ����ӿ�


	return true;
	DEBUG_CATCHF("CLuaScriptMachine::RegeditManyInterface");
}

