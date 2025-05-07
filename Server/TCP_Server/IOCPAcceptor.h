#pragma once
#include "IOCPSocket.h"

namespace IOCP
{
	class Acceptor
	{
	public:
		bool Start(unsigned short _port, int _maxPostAccept = 1);
	private:
		IOCP::Socket m_listenSocket;
	};
}