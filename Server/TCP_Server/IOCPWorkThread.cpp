#include "IOCPWorkThread.h"
#include "IOCPHandler.h"

using IOCP::WorkThread;

//IOCP::Handler
void WorkThread::Init(IOCP::Handler* _iocpHandler)
{
	m_iocpHandler = _iocpHandler;
}

void WorkThread::AllocWorkThread(int _threadNum)
{
	for (int i = 0; i < _threadNum; ++i)
	{
//		m_workerThread.emplace_back(&ThreadManager::Worker, this);
		m_workerThread.emplace_back([this](std::stop_token _token) {this->Worker(_token); });
	}
}

void WorkThread::Worker(std::stop_token _token)
{
	DWORD bytesTransferred = 0;
	ULONG_PTR completionKey = 0;
	OVERLAPPED* overlapped = nullptr;

	bool isSuccess = true;
	//Log
	while (false == _token.stop_requested())
	{
		isSuccess = m_iocpHandler->GetCompletionStatus(&bytesTransferred, &completionKey, &overlapped);

		if (0 == completionKey) //Á¾·á
			break;
		
		if (0 == bytesTransferred)
			continue;
	
	}
}
