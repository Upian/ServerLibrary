#include <iostream>
#include "TCP_Server/IOCPServer.h"
#include "TCP_Server/IOCPSocket.h"
#include "TCP_Server/IOCPSession.h"


int main()
{
	IOCP::Server& server = IOCP::Server::GetInstance();

	IOCP::Socket serverSocket;
	serverSocket.CreateSocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, nullptr, 0, WSA_FLAG_OVERLAPPED);
	serverSocket.Bind(nullptr, 8333);
	serverSocket.Listen();


	server.GetThreadManager().AllocWorkThread(3);
	
}