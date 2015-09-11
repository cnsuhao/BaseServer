////////////////////////////////////////////////////////////////////////
// Import : �����ļ����ṹ�嶨�塣
// Moudle : StructDef.h 
// Author : �½���(Chen Jianjun)
// Create : 2015-6-19
////////////////////////////////////////////////////////////////////////
#ifndef _SHARE_STRUCT_DEF_H_
#define _SHARE_STRUCT_DEF_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "./ConstDef.h"
#include "./EnumDef.h"

#include <set>
#include <map>
#include <vector>

////////////////////////////////////////////////////////////////////////
// ͨ�ýӿ�
inline void EmptyFunction(...) {}
#ifdef MULTI_KERNEL_LOG
#define LOGDEBUG	LOGMSG
#else
#define LOGDEBUG	EmptyFunction
#endif
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
// ͨ��STL��������
typedef std::vector<int>			INT_VEC;
typedef INT_VEC::iterator			INT_VEC_ITER;
typedef INT_VEC::const_iterator		INT_VEC_CITER;

typedef std::vector<UINT>			UINT_VEC;
typedef UINT_VEC::iterator			UINT_VEC_ITER;
typedef UINT_VEC::const_iterator	UINT_VEC_CITER;

typedef std::vector<OBJID>			ID_VEC;
typedef ID_VEC::iterator			ID_VEC_ITER;
typedef ID_VEC::const_iterator		ID_VEC_CITER;

typedef std::set<int>				INT_SET;
typedef INT_SET::iterator			INT_SET_ITER;
typedef INT_SET::const_iterator		INT_SET_CITER;

typedef std::set<UINT>				UINT_SET;
typedef UINT_SET::iterator			UINT_SET_ITER;
typedef UINT_SET::const_iterator	UINT_SET_CITER;

typedef std::set<OBJID>				ID_SET;
typedef ID_SET::iterator			ID_SET_ITER;
typedef ID_SET::const_iterator		ID_SET_CITER;

typedef std::map<int, int>			INT_MAP;
typedef INT_MAP::iterator			INT_MAP_ITER;
typedef INT_MAP::const_iterator		INT_MAP_CITER;
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
// �ṹ�嶨��
// ��½ʱ�˺���Ϣ
struct ACCOUNT_INFO
{
	// ������Ϣ
	OBJID		idAccount;
	char		szAccountName[64];
	int			nAccountType;
	int			nAccountStatus;
	int			nAccountStatusParam;

	// �ڴ���Ϣ
	SOCKET_ID	idSocket;
	OBJID		idChoosePlayer;
	int			nKickOtherFlag;
	int			nLoginState;
	int			nUserCount;
	UINT		unStartSecond;
};

// ��������
struct MSG_USER_TASK_DATA
{
	MSG_NUM_4BIT nTaskID;		// ���																											
	MSG_NUM_4BIT nTaskType;		// ��������													
	MSG_NUM_4BIT nStep;			// ����														
	MSG_NUM_4BIT nStatus;		// ����״̬(0:δ����,1:����, 2:�ύ, 3:�ﵽ���������δ�ύ)
	MSG_NUM_4BIT nCount1;		// ����1													
	MSG_NUM_4BIT nCount2;		// ����2													
	MSG_NUM_4BIT nCount3;		// ����3
	MSG_NUM_4BIT nBeginTime;	// ��ʼʱ��(��λ��)	
	MSG_NUM_4BIT nOverTime;		// ����ʱ��(0:������, >0:����ʱ�䵥λ��)
};
typedef std::vector<MSG_USER_TASK_DATA>			VEC_MSG_USER_TASK;
typedef VEC_MSG_USER_TASK::iterator				ITER_VEC_MSG_USER_TASK;
typedef VEC_MSG_USER_TASK::const_iterator		CITER_VEC_MSG_USER_TASK;

// �ʼ�����
struct MSG_MAIL_DATA
{
	MSG_NUM_8BIT	i64MailID;	// �ʼ�ID
	MSG_STR_256BIT  szContent;	// ����
	MSG_NUM_4BIT    nOverTime;	// ����ʱ��(������ʱ������)
	MSG_NUM_4BIT    nStatus;	// �ʼ�״̬(0:δ��, 1:�Ѷ�, 2:ɾ��)

	MSG_NUM_4BIT nItemType1;	// ��Ʒ1
	MSG_NUM_4BIT nItemNum1;		// ��Ʒ1����
	MSG_NUM_4BIT nItemType2;	// ��Ʒ2
	MSG_NUM_4BIT nItemNum2;		// ��Ʒ2����
	MSG_NUM_4BIT nItemType3;	// ��Ʒ3
	MSG_NUM_4BIT nItemNum3;		// ��Ʒ3����
	MSG_NUM_4BIT nItemType4;	// ��Ʒ4
	MSG_NUM_4BIT nItemNum4;		// ��Ʒ4����
	MSG_NUM_4BIT nItemType5;	// ��Ʒ5
	MSG_NUM_4BIT nItemNum5;		// ��Ʒ5����
	MSG_NUM_4BIT nItemType6;	// ��Ʒ6
	MSG_NUM_4BIT nItemNum6;		// ��Ʒ6����

	MSG_NUM_4BIT nMoneyType1;	// ����1
	MSG_NUM_4BIT nMoneyNum1;	// ����1����
	MSG_NUM_4BIT nMoneyType2;	// ����2
	MSG_NUM_4BIT nMoneyNum2;	// ����2����
	MSG_NUM_4BIT nMoneyType3;	// ����3
	MSG_NUM_4BIT nMoneyNum3;	// ����3����
	MSG_NUM_4BIT nMoneyType4;	// ����4
	MSG_NUM_4BIT nMoneyNum4;	// ����4����

	MSG_NUM_4BIT nExp;			// ����
};

// �ʼ��б�
struct MSG_MAIL_LIST
{
	MSG_NUM_8BIT	i64MailID;	// �ʼ�ID
	MSG_STR_32BIT	szTitle;	// �ʼ�����
	MSG_STR_32BIT	szSender;	// ����������
	MSG_NUM_4BIT	nSendTime;	// ���ʼ�ʱ��
	MSG_NUM_4BIT	nStatus;	// �ʼ�״̬(0:δ��, 1:�Ѷ�)
};
typedef std::vector<MSG_MAIL_LIST>				VEC_MAIL_LIST;
typedef VEC_MAIL_LIST::iterator					ITER_VEC_MAIL_LIST;
typedef VEC_MAIL_LIST::const_iterator			CITER_VEC_MAIL_LIST;

// �ʼ���Ʒ
struct MAIL_AWARD_DATA
{
	int		nAwardType;	// ��ƷType
	int		nAwardNum;	// ��Ʒ����
};
typedef std::vector<MAIL_AWARD_DATA> VEC_MAIL_AWARD;

// ���������Ϣ
struct ST_TALK_USER_INFO
{
	OBJID	idUser;					// ���ID
	char	szUserName[NAME_SIZE];	// ��ҽ�ɫ��
	int		nLookface;				// ���ͷ��
	int		nLev;					// ��ҵȼ�
};
////////////////////////////////////////////////////////////////////////
#endif // end of _SHARE_STRUCT_DEF_H_