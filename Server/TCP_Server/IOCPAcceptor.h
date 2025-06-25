#pragma once
#include "IOCPSocket.h"

namespace IOCP
{
	class Handler;
	class ObjectManager;
	class Acceptor
	{
	public:
		Acceptor();
		bool Start(IOCP::Handler* _handler, unsigned short _port, int _maxPostAccept = 1);

		IOCP::Socket GetListenSocket() const { return m_listenSocket; }
	private:
		IOCP::Socket m_listenSocket;
		IOCP::ObjectManager* m_objectManager = nullptr;
	};
}