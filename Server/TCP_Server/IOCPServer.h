#pragma once
#include <winsock2.h>
#include <windows.h>
#include "IOCPHandler.h"

/*
* IOCPServer
* Singleton
* IOCP�� ����� ����
* Accepter, Workmanager, IOCPHandler�� ���
* Acceptor�� Ŭ���̾�Ʈ�� ������ �޾Ƶ��̰�, Ŭ���̾�Ʈ�� ����
* WorkManager�� ����� Ŭ���̾�Ʈ�� ó���ϱ� ���� Worker�� ����
* IOCPHandler�� IOCP�� ����ϱ� ���� �ڵ鷯
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

