#include "IOCPThreadManager.h"

using IOCP::ThreadManager;

//IOCP::Handler
void ThreadManager::Init(HANDLE _iocpHandle, int _workThread)
{
	//WorkThread
	for (int i = 0; i < _workThread; ++i)
	{
		m_workThread.emplace_back([_iocpHandle]() {

			});

	}
}
