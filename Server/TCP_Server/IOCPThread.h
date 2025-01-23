#pragma once

#include <list>
#include <thread>
#include <windows.h>
//#include "IOCPSession.h"
class IOCPThread 
{
public:
	void Init(HANDLE _iocpHandle, int _workThread);
private:
	std::list<std::thread> m_workThread;
	std::thread m_sendThread;

};