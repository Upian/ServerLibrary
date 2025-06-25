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

bool IOCP::Session::DoAcceptEX()
{
	DWORD lpdwBytesReceived = 0;

	m_buffer.SetIOType(IOType::Accept);
//	m_buffer.SetSession(this->shared_from_this());
	m_buffer.SetSession(this->weak_from_this());
	return IOCP::Socket::AcceptEX(m_listenSocket, m_addressBuf, 0, &lpdwBytesReceived, m_buffer.GetOverlapped());
}

bool IOCP::Session::DoAcceptEX(Socket& _listenSocket)
{
	DWORD lpdwBytesReceived = 0;

	m_buffer.SetIOType(IOType::Accept);
	m_buffer.SetSession(this->shared_from_this());
	return IOCP::Socket::AcceptEX(&_listenSocket, m_addressBuf, 0, &lpdwBytesReceived, m_buffer.GetOverlapped());
}

void IOCP::Session::HandleAccept()
{

}
