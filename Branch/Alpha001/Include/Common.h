//////////////////////////////////////////////////////////////////////////
// Moudle:	 Common.h
// Describe: 宏定义文件
// Author:	 陈建军(Chen Jianjun)
// Created:	 2015-02-28
//////////////////////////////////////////////////////////////////////////
#ifndef _COMMON_H_
#define _COMMON_H_

#include "GlobalBaseFuc.h"

#define CHECK(x)	if(!(x)){ return;}
#define CHECKB(x)	if(!(x)){ break;}
#define CHECKC(x)	if(!(x)){ continue;}
#define CHECKF(x)	if(!(x)){ return false;}
#define CHECKF1(x)	if(!(x)){ return 1;}

#define SAFE_DELETE(p)	if (p){try{delete p; p = nullptr;}catch (...){p = nullptr;}p = nullptr;}
#define SAFE_DELETE_SIZE(p)	if (p){try{delete[] p; p = nullptr;}catch (...){p = nullptr;}p = nullptr;}
#define SAFE_RELEASE(p)	if (p){try{p->Release(); p = nullptr;}catch (...){p = nullptr;}p = nullptr;}
#endif