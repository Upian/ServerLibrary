#include "IOCPSession.h"

IOCP::Session::Session()
	:Socket()
{
	IOCP::Socket::CreateSocket();
}

IOCP::Session::~Session()
{

}

void IOCP::Session::DoAcceptEX(Socket& _listenSocket)
{
	DWORD lpdwBytesReceived = 0;

	m_buffer.SetIOType(IOType::Accept);
	m_buffer.SetSession(this->shared_from_this());
	IOCP::Socket::AcceptEX(&_listenSocket, m_adressBuf, 0, &lpdwBytesReceived, m_buffer.GetOverlapped());

}

void IOCP::Session::HandleAccept()
{

}
