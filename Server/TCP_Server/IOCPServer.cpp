#include "IOCPServer.h"
#include <WinSock2.h>

//Singleton
//IOCPServer IOCPServer::m_instance;
using IOCP::Server;

Server& Server::GetInstance(DWORD _numberOfConcurrentThreads /*= 0*/)
{
	static Server instance;
	return instance;
}

void Server::CreateNewAcceptor(SOCKET _listenSocket, SOCKADDR_IN _addr)
{
}

Server::~Server()
{
}

Server::Server()
{
	if ( false == m_IOCPHandler.Initialize() )
	{
//		error log
	}
	m_threadManager.Init(&m_IOCPHandler);
}
