#pragma once
#include <winsock2.h>
#include <windows.h>
#include "IOCPHandler.h"
#include "WinSock.h"
#include "IOCPSocket.h"
#include "IOCPAcceptor.h"

#include "Util/Singleton.h"
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
	class SessionManager;
	class WorkThread;

	template<typename T_Server>
	class Server : public Singleton<T_Server>
	{
	public:
		virtual ~Server();
		
		void Initialize();
		void CreateNewAcceptor(unsigned short _port);
		IOCP::WorkThread* GetWorkThread() { return m_workThread; }

	protected:
		Server();
		Server(const Server&) = delete;
		Server& operator=(const Server&) = delete;
		
//		virtual void HandleThread() = 0; //���� ó��

	private:
		IOCP::SessionManager* SessionManager = nullptr; //Singleton
		IOCP::WorkThread* m_workThread = nullptr;

		IOCP::Acceptor m_acceptor;
		IOCP::Handler m_IOCPHandler;
		IOCP::Socket m_socket;
		WinSock m_winSock;
		
		
	};
}
