#pragma once

#include <vector>
#include <thread>
//#include "IOCPSession.h"

namespace IOCP
{
	class Handler;
	class Server;
	class ObjectManager;
	class MessageQueue;

	class WorkThread
	{
	public:
		WorkThread(IOCP::Handler* _iocpHandler);
		void Initialize(int _threadCount);
	private:
		void Worker(std::stop_token _token);

	private:
		std::vector<std::jthread> m_workerThread;
		std::jthread m_sendThread;
		IOCP::Handler* m_iocpHandler = nullptr;
		IOCP::ObjectManager* m_objectManager = nullptr;
		IOCP::MessageQueue* m_messageQueue = nullptr;
	};
}
