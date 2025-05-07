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


void Server::CreateNewAcceptor(unsigned short _port)
{
	if (false == m_acceptor.Start(&m_IOCPHandler, _port))
	{
		//error log
	}
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
