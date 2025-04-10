#pragma once

#include <list>
#include <thread>
#include <windows.h>
//#include "IOCPSession.h"

namespace IOCP
{
	class ThreadManager
	{
	public:
		void Init(HANDLE _iocpHandle, int _workThread);
	private:
		std::list<std::jthread> m_workThread;
		std::jthread m_sendThread;
	};
}
