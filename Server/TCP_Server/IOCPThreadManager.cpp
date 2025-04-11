#include "IOCPThreadManager.h"
#include "IOCPHandler.h"
#include <iostream>
using IOCP::ThreadManager;

//IOCP::Handler
void ThreadManager::Init(IOCP::Handler* _iocpHandler)
{
	m_iocpHandler = _iocpHandler;
}

void ThreadManager::AllocWorkThread(int _threadNum)
{
	for (int i = 0; i < _threadNum; ++i)
	{
//		m_workerThread.emplace_back(&ThreadManager::Worker, this);
		m_workerThread.emplace_back([this](std::stop_token _token) {this->Worker(_token); });
	}
}

void ThreadManager::Worker(std::stop_token _token)
{
	std::cout << "test1" << std::endl;
//	while (false == _token.stop_requested())
//	{
//		
//	}
}
