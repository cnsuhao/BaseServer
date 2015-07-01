
#ifndef _MYSTRING_H
#define _MYSTRING_H

#define CN_RES
//#define CN_RES_BIG5
//#define EN_RES

#ifdef CN_RES
	#include "cn_ddres.h"
#elif defined EN_RES
	#include "en_ddres.h"
#endif


#endif //_MYSTRING_H


















