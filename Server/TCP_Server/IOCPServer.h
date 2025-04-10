#pragma once
#include <winsock2.h>
#include <windows.h>
#include "IOCPHandler.h"
#include "WinSock.h"
/*
* IOCPServer
* Singleton
* IOCP를 사용한 서버
* Accepter, Workmanager, IOCPHandler를 사용
* Acceptor는 클라이언트의 접속을 받아들이고, 클라이언트를 연결
* WorkManager는 연결된 클라이언트를 처리하기 위한 Worker를 관리
* IOCPHandler는 IOCP를 사용하기 위한 핸들러
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