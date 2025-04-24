#pragma once
#include "IOCPSocket.h"

namespace IOCP
{
	class Acceptor
	{
	public:
		bool Start(unsigned short _port);
	private:
		IOCP::Socket m_socket;
	};
}