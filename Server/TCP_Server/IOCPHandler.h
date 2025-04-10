#pragma once

#include <windows.h>

/*
* IOCP handle ��ü
* IOCP ���� ó��
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

	//IOCP �ڵ� ����
	inline bool Initialize( DWORD _numberOfConcurrentThreads = 0 )
	{
		m_IOCPHandle = CreateIoCompletionPort( INVALID_HANDLE_VALUE, NULL, 0, _numberOfConcurrentThreads );
		return  nullptr != m_IOCPHandle;
	}
	
	//AcceptEx, ConnectEx, WSASend, WSARecv ���� �Լ��� ����ϱ� ���� IOCP�� ����̽��� ����
	inline bool AssociateDevice( HANDLE _deviceHandle, ULONG_PTR _completionKey )
	{
		return nullptr != CreateIoCompletionPort( _deviceHandle, m_IOCPHandle, _completionKey, 0 );
	}
//	LPOVERLAPPED = OVERLAPPED*
	//'�Ϸ�� I/O ��û' �� ������ �Լ�
	inline bool GetCompletionStatus( DWORD* _numberOfBytes, ULONG_PTR* _completionKey, OVERLAPPED** _overlapped, DWORD _milliseconds = INFINITE )
	{
		return GetQueuedCompletionStatus( m_IOCPHandle, _numberOfBytes, _completionKey, _overlapped, _milliseconds );
		// false�̰� GetLastError�� ERROR_NETNAME_DELETED, ERROR_CONNECTION_ABORTED ���� ���� �ָ� ������ ������ ������
	}

	inline bool PostCompletionStatus( DWORD _numberOfBytes, ULONG_PTR _completionKey, OVERLAPPED* _overlapped )
	{
		return PostQueuedCompletionStatus( m_IOCPHandle, _numberOfBytes, _completionKey, _overlapped );
	}

private:
	HANDLE m_IOCPHandle = nullptr;
	
};
