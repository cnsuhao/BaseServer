//////////////////////////////////////////////////////////////////////////
// Moudle:	 GlobalStruct.h
// Describe: ȫ�ֽṹ�嶨��
// Author:	 �½���(Chen Jianjun)
// Created:	 2015-02-28
//////////////////////////////////////////////////////////////////////////
#ifndef _GLOBAL_STRUCT_H_
#define _GLOBAL_STRUCT_H_

// IOCP����ṹ����
typedef struct{
	DWORD	dw_IOHandle_Index;			// �������
	DWORD	dw_AcceptSession_MaxNum;	// �Ự����������
	DWORD	dw_ConnectSession_MaxNum;	// �ػ������������
	DWORD	dw_SendBuffer_Size;			// ���ͻ�������С
	DWORD	dw_RecvBuffer_Size;			// ���ջ�������С
	DWORD	dw_Packet_MaxSize;			// ��Ϣ����󳤶�
	DWORD	dw_IOThread_Num;			// I/O�߳�����(������ϢSend/Recv)
	DWORD	dw_AcceptThread_Num;		// �����߳�����
	DWORD	dw_ConnectThread_Num;		// �����߳�����
}ST_IOCP_HANDLE, *LP_ST_IOCP_HANDLE;

#endif