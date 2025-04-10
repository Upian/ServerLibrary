#pragma once
#include <winsock2.h>
#include <windows.h>
#include "IOCPHandler.h"
#include "WinSock.h"
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

		void CreateNewAcceptor(SOCKET _listenSocket, SOCKADDR_IN _addr);

		virtual ~Server();
	private:
		Server();
		Server(const Server&) = delete;
		Server& operator=(const Server&) = delete;


	private:
		IOCP::Handler m_IOCPHandler;
		WinSock m_winSock;
		//WorkManager m_workManager;
	};
}