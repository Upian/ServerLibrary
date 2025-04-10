#include "IOCPServer.h"
#include <WinSock2.h>

//Singleton
//IOCPServer IOCPServer::m_instance;

IOCPServer& IOCPServer::GetInstance(DWORD _numberOfConcurrentThreads /*= 0*/)
{
	static IOCPServer instance;
	return instance;
}

void IOCPServer::CreateNewAcceptor(SOCKET _listenSocket, SOCKADDR_IN _addr)
{
}

IOCPServer::~IOCPServer()
{
}

IOCPServer::IOCPServer()
{
	if ( false == m_IOCPHandler.Initialize() )
	{
//		error log
	}
}
