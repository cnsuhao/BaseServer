#ifndef _NETBASE_H_
#define _NETBASE_H_

//=============================================================================================================================
/// 패킷 헤더
//=============================================================================================================================

#define PACKETHEADER	4

typedef struct tagPACKET_HEADER
{
	WORD	size;		/// 순수 패킷의 크기
} PACKET_HEADER;

#endif