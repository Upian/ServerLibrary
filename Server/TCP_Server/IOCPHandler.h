#pragma once

#include <windows.h>

/*
* IOCP handle 객체
* IOCP 관련 처리
*/

class IOCPHandler
{
public:
	IOCPHandler() = default;
	~IOCPHandler()
	{
		if ( nullptr != m_IOCPHandle )
		{
			CloseHandle( m_IOCPHandle );
			m_IOCPHandle = nullptr;
		}
	}

	//IOCP 핸들 생성
	inline bool Initialize( DWORD _numberOfConcurrentThreads = 0 )
	{
		m_IOCPHandle = CreateIoCompletionPort( INVALID_HANDLE_VALUE, NULL, 0, _numberOfConcurrentThreads );
		return  nullptr != m_IOCPHandle;
	}
	
	//AcceptEx, ConnectEx, WSASend, WSARecv 등의 함수를 사용하기 위해 IOCP와 디바이스를 연결
	inline bool AssociateDevice( HANDLE _deviceHandle, ULONG_PTR _completionKey )
	{
		return nullptr != CreateIoCompletionPort( _deviceHandle, m_IOCPHandle, _completionKey, 0 );
	}
//	LPOVERLAPPED = OVERLAPPED*
	//'완료된 I/O 요청' 을 꺼내는 함수
	inline bool GetCompletionStatus( DWORD* _numberOfBytes, ULONG_PTR* _completionKey, OVERLAPPED** _overlapped, DWORD _milliseconds = INFINITE )
	{
		return GetQueuedCompletionStatus( m_IOCPHandle, _numberOfBytes, _completionKey, _overlapped, _milliseconds );
		// false이고 GetLastError가 ERROR_NETNAME_DELETED, ERROR_CONNECTION_ABORTED 같은 값을 주면 상대방이 연결을 끊었음
	}

	inline bool PostCompletionStatus( DWORD _numberOfBytes, ULONG_PTR _completionKey, OVERLAPPED* _overlapped )
	{
		return PostQueuedCompletionStatus( m_IOCPHandle, _numberOfBytes, _completionKey, _overlapped );
	}

private:
	HANDLE m_IOCPHandle = nullptr;
	
};
