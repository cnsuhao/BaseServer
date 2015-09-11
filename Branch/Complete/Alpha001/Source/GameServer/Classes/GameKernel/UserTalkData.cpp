#include "./UserTalkData.h"
MYHEAP_IMPLEMENTATION(CUserTalkData, s_heap)

////////////////////////////////////////////////////////////////////////
// Description: 构造
// Arguments:
// Author: 龚建伟(Gong Jianwei)
// Return Value: 
////////////////////////////////////////////////////////////////////////
CUserTalkData::CUserTalkData()
{

}

////////////////////////////////////////////////////////////////////////
// Description: 析构
// Arguments:
// Author: 龚建伟(Gong Jianwei)
// Return Value: 
////////////////////////////////////////////////////////////////////////
CUserTalkData::~CUserTalkData()
{
	m_mapUserTalkData.clear();
}

////////////////////////////////////////////////////////////////////////
// Description: 初始化
// Arguments:
// Author: 龚建伟(Gong Jianwei)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool CUserTalkData::Init()
{
	m_mapUserTalkData.clear();
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: 是否存在记录
// Arguments:
// Author: 龚建伟(Gong Jianwei)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool CUserTalkData::IsExit(int nTxtAtr) const
{
	CHECKF(nTxtAtr);
	MAP_USER_TALK_DATA::const_iterator iter = m_mapUserTalkData.find(nTxtAtr);
	if (iter != m_mapUserTalkData.end())
	{
		return true;
	}
	return false;
}

////////////////////////////////////////////////////////////////////////
// Description: 添加一条新记录
// Arguments:
// Author: 龚建伟(Gong Jianwei)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool CUserTalkData::Add(int nTxtAtr, UINT unSec)
{
	CHECKF(nTxtAtr);
	CHECKF(!this->IsExit(nTxtAtr));
	m_mapUserTalkData[nTxtAtr] = unSec;
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: 添加一条新记录
// Arguments:
// Author: 龚建伟(Gong Jianwei)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool CUserTalkData::Del(int nTxtAtr)
{
	CHECKF(nTxtAtr);
	CHECKF(this->IsExit(nTxtAtr));
	m_mapUserTalkData.erase(nTxtAtr);
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: 设置数据
// Arguments:
// Author: 龚建伟(Gong Jianwei)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool CUserTalkData::SetData(int nTxtAtr, UINT unSec/*=0*/)
{
	CHECKF(nTxtAtr);
	CHECKF(this->IsExit(nTxtAtr));
	m_mapUserTalkData[nTxtAtr] = unSec;
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: 获取数据
// Arguments:
// Author: 龚建伟(Gong Jianwei)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
DWORD CUserTalkData::GetData(int nTxtAtr) const
{
	CHECKF(nTxtAtr);
	MAP_USER_TALK_DATA::const_iterator iter = m_mapUserTalkData.find(nTxtAtr);
	CHECKF(iter != m_mapUserTalkData.end());
	return iter->second;
}
