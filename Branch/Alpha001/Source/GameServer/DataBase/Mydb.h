
#ifndef  _BASECODE_MYDB_H_
#define  _BASECODE_MYDB_H_

#include "../../../Include/mysql/mysql.h"
#include "I_mydb.h"

#include "./mydatabase.h"
#include "./myfield.h"
#include "./myrecordset.h"
#include "./myrecord.h"

const int			INT_NONE	= 0;			// �Ƿ�����������ֵ
static const char*	STR_NONE	= "";			// �Ƿ��Ĵ�����ֵ
const double		DOUBLE_NONE    = 0;			//----------2007/05/15-----
const __int64		INT64_NONE    = 0;			//  [7/23/2007]		

static const char*	SQL_STMT_DELETE			=	"DELETE FROM %s %s WHERE %s";
static const char*	SQL_STMT_UPDATE			=	"UPDATE %s SET %s WHERE %s LIMIT 1";	//paled add "LIMIT 1"
static const char*	SQL_STMT_INSERT			=	"INSERT %s SET %s";		//paled - ������һ��������������

#endif // end of _BASECODE_MYDB_H_
