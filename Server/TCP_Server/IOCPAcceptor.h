#pragma once
#include "IOCPSocket.h"

namespace IOCP
{
	class Handler;

	class Acceptor
	{
	public:
		bool Start(IOCP::Handler* _handler, unsigned short _port, int _maxPostAccept = 1);

		IOCP::Socket GetListenSocket() const { return m_listenSocket; }
	private:
		IOCP::Socket m_listenSocket;
	};
}