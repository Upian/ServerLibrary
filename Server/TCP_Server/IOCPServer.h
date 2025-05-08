#pragma once
#include <winsock2.h>
#include <windows.h>
#include "IOCPHandler.h"
#include "WinSock.h"
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
	class WorkManager;
	class WorkThread;

	class Server
	{
	public:
		static Server& GetInstance(DWORD _numberOfConcurrentThreads = 0);
		virtual ~Server();
		
		void CreateNewAcceptor(unsigned short _port);
		
		IOCP::WorkThread* GetWorkThread() { return m_workThread; }
	private:
		Server();
		Server(const Server&) = delete;
		Server& operator=(const Server&) = delete;


	private:
		IOCP::WorkManager* m_workManager = nullptr; //Singleton
		IOCP::WorkThread* m_workThread = nullptr;

		IOCP::Acceptor m_acceptor;
		IOCP::Handler m_IOCPHandler;
		IOCP::Socket m_socket;
		WinSock m_winSock;
		
		
	};
}