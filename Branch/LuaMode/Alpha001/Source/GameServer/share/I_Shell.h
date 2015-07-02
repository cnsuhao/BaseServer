////////////////////////////////////////////////////////////////////////
// Import : 共享文件。对话框接口文件。
// Moudle : I_Shell.h
// Author : 陈建军(Chen Jianjun)
// Create : 2015-6-19
////////////////////////////////////////////////////////////////////////
#ifndef	_SHARE_I_SHELL_H_
#define	_SHARE_I_SHELL_H_

#include "../Common/common.h"
class IMessagePort;

// 网络核心
class ISocketKernel
{
public:
	virtual ~ISocketKernel() {}
	static ISocketKernel* CreateNew();
	virtual bool	Create(IMessagePort* pPort,int nServerListenPort)				PURE_VIRTUAL_FUNCTION_0;
	virtual bool	Release()														PURE_VIRTUAL_FUNCTION_0;
	virtual bool	ProcessMsg(OBJID idPacket, void* buf, int nType, int nFrom)		PURE_VIRTUAL_FUNCTION_0;
	virtual bool	OnTimer()														PURE_VIRTUAL_FUNCTION_0;
	virtual void	PrintText(const char* pszText)									PURE_VIRTUAL_FUNCTION;
};

// 登陆核心
class ILoginKernel
{
public:
	virtual ~ILoginKernel() {}
	static ILoginKernel* Instance();
	static void			DelInstance();

	virtual bool	Create			(IMessagePort* pPort)								PURE_VIRTUAL_FUNCTION_0;
	virtual bool	Release			(void)												PURE_VIRTUAL_FUNCTION_0;
	virtual bool	ProcessMsg		(OBJID idPacket, void* buf, int nType, int nFrom)	PURE_VIRTUAL_FUNCTION_0;
	virtual bool	OnTimer			(void)												PURE_VIRTUAL_FUNCTION_0;
	virtual bool	OnTimerRollback	(void)												PURE_VIRTUAL_FUNCTION_0;
	virtual void	PrintText		(const char* pszText)								PURE_VIRTUAL_FUNCTION;
};

// 游戏核心
class IGameKernel
{
public:
	virtual ~IGameKernel() {}
	static IGameKernel* Instance();
	static void			DelInstance();

	virtual bool	Create			(IMessagePort* pPort)								PURE_VIRTUAL_FUNCTION_0;
	virtual bool	Release			(void)												PURE_VIRTUAL_FUNCTION_0;
	virtual bool	ProcessMsg		(OBJID idPacket, void* buf, int nType, int nFrom)	PURE_VIRTUAL_FUNCTION_0;
	virtual bool	OnTimer			(void)												PURE_VIRTUAL_FUNCTION_0;
	virtual bool	OnTimerRollback	(void)												PURE_VIRTUAL_FUNCTION_0;
	virtual void	PrintText		(const char* pszText)								PURE_VIRTUAL_FUNCTION;
};

// 关系核心
class IRelationKernel
{
public:
	virtual ~IRelationKernel() {}
	static IRelationKernel* Instance();
	static void			DelInstance();

	virtual bool	Create				(IMessagePort* pPort)								PURE_VIRTUAL_FUNCTION_0;
	virtual bool	Release				(void)												PURE_VIRTUAL_FUNCTION_0;
	virtual bool	ProcessMsg			(OBJID idPacket, void* buf, int nType, int nFrom)	PURE_VIRTUAL_FUNCTION_0;
	virtual bool	OnTimer				(void)												PURE_VIRTUAL_FUNCTION_0;
	virtual bool	OnTimerRollback		(void)												PURE_VIRTUAL_FUNCTION_0;
	virtual void	ProcessRelationMsg	(void)												PURE_VIRTUAL_FUNCTION;
	virtual void	PrintText			(const char* pszText)								PURE_VIRTUAL_FUNCTION;
};

// AI核心
class IAIKernel
{
public:
	virtual ~IAIKernel() {}
	static IAIKernel*	Instance();
	static void			DelInstance();

	virtual bool	Create			(IMessagePort* pPort)								PURE_VIRTUAL_FUNCTION_0;
	virtual bool	Release			(void)												PURE_VIRTUAL_FUNCTION_0;
	virtual bool	ProcessMsg		(OBJID idPacket, void* buf, int nType, int nFrom)	PURE_VIRTUAL_FUNCTION_0;
	virtual bool	OnTimer			(void)												PURE_VIRTUAL_FUNCTION_0;
	virtual bool	OnTimerRollback	(void)												PURE_VIRTUAL_FUNCTION_0;
	virtual void	PrintText		(const char* pszText)								PURE_VIRTUAL_FUNCTION;
	virtual void	ProcessAIMsg	(void)												PURE_VIRTUAL_FUNCTION;
};
#endif // _SHARE_I_SHELL_H_