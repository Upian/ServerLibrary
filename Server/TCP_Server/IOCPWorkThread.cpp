#include "IOCPBuffer.h"
#include "IOCPWorkThread.h"
#include "IOCPHandler.h"
#include <iostream>
//IOCP::Handler

IOCP::WorkThread::WorkThread(IOCP::Handler* _iocpHandler) :
	m_iocpHandler(_iocpHandler)
{
}

void IOCP::WorkThread::Initialize(int _threadCount)
{
	for (int i = 0; i < _threadCount; ++i)
	{
		m_workerThread.emplace_back(std::jthread(
			[this](std::stop_token _token) {
				this->Worker(_token); 
			}
		));
	}
}

void IOCP::WorkThread::Worker(std::stop_token _token)
{
	DWORD bytesTransferred = 0;
	ULONG_PTR completionKey = 0; //Listen socket 포인터
	OverlappedIO* overlappedIO = nullptr;

	bool isSuccess = true;
	//Log
	while (false == _token.stop_requested())
	{
		isSuccess = m_iocpHandler->GetCompletionStatus(&bytesTransferred, &completionKey, (OVERLAPPED**)&overlappedIO);
		std::cout << "Success: " << isSuccess << " completionKey: " << completionKey << " bytesTransferred: " << bytesTransferred << std::endl;

		if (0 == completionKey) //종료
			break;

		if (nullptr == overlappedIO)
			continue;

		if (false == isSuccess)
			continue;


		if (0 == bytesTransferred)
			continue;
	
	}
}
