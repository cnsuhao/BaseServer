////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan ChuangYou, All Rights Reserved
// Moudle: I_Shell.h 对话框接口文件
// Author: 彭文奇(Peng Wenqi)
// Created: 2014-10-30
////////////////////////////////////////////////////////////////////////
#ifndef	INTERFACE_SHELL_HEAD_FILE
#define	INTERFACE_SHELL_HEAD_FILE

/////////////////////////////////////////////////////////////////////////////
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
#endif // INTERFACE_SHELL_HEAD_FILE