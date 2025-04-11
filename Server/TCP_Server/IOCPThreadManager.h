#pragma once

#include <vector>
#include <thread>
#include <windows.h>
//#include "IOCPSession.h"

namespace IOCP
{
	class Handler;

	class ThreadManager
	{
	public:
		void Init(IOCP::Handler* _iocpHandler);
		void AllocWorkThread(int _threadNum);
	private:
		void Worker(std::stop_token _token);

	private:
		std::vector<std::jthread> m_workerThread;
		std::jthread m_sendThread;
		IOCP::Handler* m_iocpHandler = nullptr;
	};
}
