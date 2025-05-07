#pragma once
#include <winsock2.h>
#include <windows.h>
#include "IOCPHandler.h"
#include "WinSock.h"
#include "IOCPThreadManager.h"
#include "IOCPSocket.h"
#include "IOCPAcceptor.h"

/*
* IOCPServer
* Singleton
* IOCP�� ����� ����
* Accepter, Workmanager, IOCPHandler�� ���
* Acceptor�� Ŭ���̾�Ʈ�� ������ �޾Ƶ��̰�, Ŭ���̾�Ʈ�� ����
* WorkManager�� ����� Ŭ���̾�Ʈ�� ó���ϱ� ���� Worker�� ����
* IOCPHandler�� IOCP�� ����ϱ� ���� �ڵ鷯
*/

namespace IOCP
{
	class Server
	{
	public:
		static Server& GetInstance(DWORD _numberOfConcurrentThreads = 0);
		virtual ~Server();
		
		void CreateNewAcceptor(unsigned short _port);
		
		IOCP::ThreadManager& GetThreadManager() { return m_threadManager; }
	private:
		Server();
		Server(const Server&) = delete;
		Server& operator=(const Server&) = delete;


	private:
		IOCP::Acceptor m_acceptor;
		IOCP::Handler m_IOCPHandler;
		IOCP::Socket m_socket;
		WinSock m_winSock;
		IOCP::ThreadManager m_threadManager;
		//WorkManager m_workManager;
	};
}