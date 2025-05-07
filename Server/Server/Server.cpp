#include <iostream>
#include "TCP_Server/IOCPServer.h"
#include "TCP_Server/IOCPSocket.h"
#include "TCP_Server/IOCPSession.h"


int main()
{
	IOCP::Server& server = IOCP::Server::GetInstance();

	server.CreateNewAcceptor(8888);
}