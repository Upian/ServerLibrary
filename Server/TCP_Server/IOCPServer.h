#pragma once
#include <winsock2.h>
#include <windows.h>
#include "IOCPHandler.h"

/*
* IOCPServer
* Singleton
* IOCP를 사용한 서버
* Accepter, Workmanager, IOCPHandler를 사용
* Acceptor는 클라이언트의 접속을 받아들이고, 클라이언트를 연결
* WorkManager는 연결된 클라이언트를 처리하기 위한 Worker를 관리
* IOCPHandler는 IOCP를 사용하기 위한 핸들러
*/

class IOCPServer 
{
public:
	static IOCPServer& GetInstance();

	void CreateNewAcceptor( SOCKET _listenSocket, SOCKADDR_IN _addr );


private:
	IOCPServer();
	IOCPServer( const IOCPServer& ) = delete;
	IOCPServer& operator=( const IOCPServer& ) = delete;
	

private:
	IOCPHandler m_IOCPHandler;
	//WorkManager m_workManager;
};

