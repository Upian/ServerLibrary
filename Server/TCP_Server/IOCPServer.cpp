#include "IOCPServer.h"

//Singleton
//IOCPServer IOCPServer::m_instance;

IOCPServer& IOCPServer::GetInstance(DWORD _numberOfConcurrentThreads /*= 0*/)
{
	static IOCPServer instance;
	return instance;
}

IOCPServer::IOCPServer()
{
	if ( false == m_IOCPHandler.Initialize() )
	{
//		error log
	}
}
