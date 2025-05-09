#pragma once
#include <winsock2.h>
#include <windows.h>
#include "WinSock.h"
#include "Util/Singleton.h"
#include "IOCPHandler.h"
#include "IOCPSocket.h"
#include "IOCPAcceptor.h"
#include "IOCPSessionManager.h"
#include "IOCPWorkThread.h"



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
	template<typename T_Server>
	class Server : public Singleton<T_Server>
	{
	public:
		virtual ~Server();
		
		void Initialize(int _threadCnt, unsigned short _port, int _maxAcceptorCnt = 1);
		IOCP::WorkThread* GetWorkThread() { return m_workThread; }

	protected:
		Server();
		Server(const Server&) = delete;
		Server& operator=(const Server&) = delete;
		
		virtual void HandleThread() = 0; //���� ó��

	private:
		IOCP::SessionManager* m_sessionManager = nullptr; //Singleton
		IOCP::WorkThread* m_workThread = nullptr;
		IOCP::Acceptor* m_acceptor = nullptr;

		IOCP::Handler m_IOCPHandler;
//		IOCP::Socket m_socket;
		WinSock m_winSock;
	};

	template<typename T_Server>
	inline Server<T_Server>::Server()
	{
		if (false == m_IOCPHandler.Initialize())
		{
			//		error log
		}

		if (nullptr == m_workThread)
		{
			m_workThread = new IOCP::WorkThread(&m_IOCPHandler);
		}
		if (nullptr == m_sessionManager)
		{
			m_sessionManager = new IOCP::SessionManager();
		}
		if (nullptr == m_acceptor)
		{
			m_acceptor = new IOCP::Acceptor(m_sessionManager);
		}
	}

	template<typename T_Server>
	inline Server<T_Server>::~Server()
	{
		if (nullptr != m_sessionManager)
		{
			delete m_sessionManager;
			m_sessionManager = nullptr;
		}
		if (nullptr != m_workThread)
		{
			delete m_workThread;
			m_workThread = nullptr;
		}
	}

	template<typename T_Server>
	inline void Server<T_Server>::Initialize(int _threadCnt, unsigned short _port, int _maxAcceptorCnt)
	{
		m_workThread->Initialize(_threadCnt);
		m_acceptor->Start(&m_IOCPHandler, _port, _maxAcceptorCnt);
	}
}
