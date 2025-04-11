#include <iostream>
#include "TCP_Server/IOCPServer.h"
#include "TCP_Server/IOCPSocket.h"
#include "TCP_Server/IOCPSession.h"

int main()
{
	IOCP::Socket serverSocket;
	serverSocket.CerateSocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, nullptr, 0, WSA_FLAG_OVERLAPPED);
	serverSocket.Bind(nullptr, 8333);
	serverSocket.Listen();

	IOCP::Server& server = IOCP::Server::GetInstance();

	
		
}