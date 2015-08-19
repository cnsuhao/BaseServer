#ifndef _RECVBUFFER_H_
#define _RECVBUFFER_H_

#include <windows.h>
#include "CircuitQueue.h"
#include "NetBase.h"
#include "./../COMMON/myheap.h"

class RecvBuffer
{
public:
	RecvBuffer()			{ m_pQueue = NULL; }
	virtual ~RecvBuffer()	{ if( m_pQueue ) delete m_pQueue; }

	inline VOID	Create		(int nBufferSize, DWORD dwExtraBufferSize)
	{
		if (m_pQueue)
		{
			delete m_pQueue;
		}
		m_pQueue = new CircuitQueue<BYTE>;
		m_pQueue->Create( nBufferSize, dwExtraBufferSize ); 
	}

	inline VOID	Completion	(int nBytesRecvd) { m_pQueue->Enqueue( NULL, nBytesRecvd ); }

	inline VOID	Clear		(void) { m_pQueue->Clear(); }

	inline VOID	GetRecvParam(BYTE **ppRecvPtr, int &nLength)
	{
		*ppRecvPtr	= m_pQueue->GetWritePtr();		
		nLength		= m_pQueue->GetWritableLen(); 
	}

	inline BYTE* GetWritePtr(void)	{ return m_pQueue->GetWritePtr(); }

	inline BYTE* GetFirstPacketPtr(void)
	{
		short header;

		if(!m_pQueue->Peek((BYTE*)&header,sizeof(header)))
		{
			return NULL;
		}

		if(m_pQueue->GetLength()<header)
		{
			return NULL;
		}

		if(m_pQueue->GetBackDataCount()<header)
		{
			m_pQueue->CopyHeadDataToExtraBuffer(header-m_pQueue->GetBackDataCount());
		}

		return  m_pQueue->GetReadPtr();	
	}

	inline int GetLength	(void) { return m_pQueue->GetLength(); }

	inline VOID	RemoveFirstPacket(WORD wSize) { m_pQueue->Dequeue( NULL, wSize ); }

	inline DWORD GetSpace	(void) { return m_pQueue->GetSpace();}

private:
	CircuitQueue<BYTE>	*m_pQueue;
public:
	MYHEAP_DECLARATION(s_heap);
};

#endif
