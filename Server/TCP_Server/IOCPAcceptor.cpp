#include "IOCPAcceptor.h"
#include "IOCPSocket.h"

bool IOCP::Acceptor::Start(unsigned short _port)
{
	if (false == (m_socket.CreateSocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, nullptr, 0, WSA_FLAG_OVERLAPPED)))
		return false;
	
	if (false == m_socket.Bind(nullptr, _port))
	{
		m_socket.CloseSocket();
		return false;
	}

	if (m_socket.Listen())
	{
		m_socket.CloseSocket();
		return false;
	}

}