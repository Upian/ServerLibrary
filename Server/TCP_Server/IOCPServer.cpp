#include "IOCPServer.h"
#include <WinSock2.h>
#include "IOCPWorkManager.h"
#include "IOCPWorkThread.h"

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

	if (nullptr == m_workThread)
	{
		m_workThread = new IOCP::WorkThread(&m_IOCPHandler);
	}
	m_workThread->Initialize(1); //³ªÁß¿¡ °ª ¹Ù²ãµÖ¾ßÇÔ
	
	if (nullptr == m_workManager)
	{
		m_workManager = WorkManager::CreateSingleton();
	}
}
