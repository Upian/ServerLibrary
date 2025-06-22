#pragma once
#include <winsock2.h>
#include <windows.h>
#include <type_traits>
#include "WinSock.h"
#include "Util/Singleton.h"
#include "Util/ConcurrentQueue.h"
#include "IOCPHandler.h"
#include "IOCPSocket.h"
#include "IOCPAcceptor.h"
#include "IOCPSessionManager.h"
#include "IOCPWorkThread.h"
#include "IOCPPacketBuf.h"
#include "IOCPConcepts.h"

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
		void Initialize(int _threadCnt, unsigned short _port, int _maxAcceptorCnt = 1);
		IOCP::WorkThread* GetWorkThread() { return m_workThread; }

//		template<DerivedFromPacketBuf T_Packet>
		template<typename T_Packet>
			requires DerivedFromPacketBuf<T_Packet>
		std::shared_ptr<T_Packet> AllocPacket();
	protected:
		Server();
		virtual ~Server();
		Server(const Server&) = delete;
		Server& operator=(const Server&) = delete;
		
		virtual void HandleThread() = 0; //���� ó��
		virtual std::shared_ptr<IOCP::PacketBuf> AllocPacketBuf() = 0; //IOCP::PacketPool�� �Ҵ��ϸ� ��
	private:
		IOCP::SessionManager* m_sessionManager = nullptr; //Singleton
		IOCP::WorkThread* m_workThread = nullptr;
		IOCP::Acceptor* m_acceptor = nullptr;

		IOCP::Handler m_IOCPHandler;
//		IOCP::Socket m_socket;

		ConcurrentQueue<int> m_conQueue;

		WinSock m_winSock;
	};

	inline Server::Server()
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
	
	inline Server::~Server()
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
	
	inline void Server::Initialize(int _threadCnt, unsigned short _port, int _maxAcceptorCnt)
	{
		m_workThread->Initialize(_threadCnt);
		m_acceptor->Start(&m_IOCPHandler, _port, _maxAcceptorCnt);
	}

	template<typename T_Packet>
		requires DerivedFromPacketBuf<T_Packet>
	inline std::shared_ptr<T_Packet> Server::AllocPacket()
	{
		return std::static_pointer_cast<T_Packet>(this->AllocPacketBuf());
	}
}