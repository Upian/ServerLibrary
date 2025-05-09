#pragma once
#include "IOCPSocket.h"

namespace IOCP
{
	class Handler;
	class SessionManager;
	class Acceptor
	{
	public:
		Acceptor() = delete;
		Acceptor(IOCP::SessionManager* _sessionManager);
		bool Start(IOCP::Handler* _handler, unsigned short _port, int _maxPostAccept = 1);

		IOCP::Socket GetListenSocket() const { return m_listenSocket; }
	private:
		IOCP::Socket m_listenSocket;
		IOCP::SessionManager* m_sessionManager = nullptr;
	};
}