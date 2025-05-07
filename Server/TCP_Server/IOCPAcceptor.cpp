#include "IOCPAcceptor.h"
#include "IOCPSocket.h"
#include "ObjectPool.h"

bool IOCP::Acceptor::Start(unsigned short _port, int _maxPostAccept /*= 1*/)
{
	if (false == (m_listenSocket.CreateSocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, nullptr, 0, WSA_FLAG_OVERLAPPED)))
		return false;
	
	if (false == m_listenSocket.Bind(nullptr, _port))
	{
		m_listenSocket.CloseSocket();
		return false;
	}

	if (m_listenSocket.Listen())
	{
		m_listenSocket.CloseSocket();
		return false;
	}



}