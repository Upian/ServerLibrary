#include "IOCPThread.h"

void IOCPThread::Init(HANDLE _iocpHandle, int _workThread)
{
	for (int i = 0; i < _workThread; ++i)
	{
		m_workThread.emplace_back([_iocpHandle]() {

			});

	}
}
