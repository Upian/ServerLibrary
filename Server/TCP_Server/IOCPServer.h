#pragma once
#include <winsock2.h>
#include <windows.h>

class IOCPServer 
{
public:
	IOCPServer();

	void Initialize(unsigned short _port);


private:
	//WorkManager m_workManager;
};