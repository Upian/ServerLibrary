#pragma once
#include <thread>

class IOCPWorker
{
public:
	IOCPWorker();
private:
	std::thread m_worker;
	
};