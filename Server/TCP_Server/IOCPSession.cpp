#include "IOCPSession.h"

IOCP::Session::Session()
	:Socket()
{
	IOCP::Socket::CreateSocket();
}

IOCP::Session::Session(Socket* _listenSocket) : Socket(), m_listenSocket(_listenSocket)
{
	IOCP::Socket::CreateSocket();
}

IOCP::Session::~Session()
{
	m_listenSocket = nullptr;
	memset(m_addressBuf, 0, sizeof(m_addressBuf));
	m_buffer.Clear();
}

bool IOCP::Session::DoAcceptEX(OverlappedIO* _io)
{
	DWORD lpdwBytesReceived = 0;
	return IOCP::Socket::AcceptEX(m_listenSocket, m_addressBuf, 0, &lpdwBytesReceived, _io);
}

void IOCP::Session::HandleAccept()
{

}
