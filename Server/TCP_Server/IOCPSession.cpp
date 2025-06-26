#include "IOCPSession.h"
#include "IOCPBuffer.h"
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
//	m_buffer.Clear();
}

bool IOCP::Session::PostAcceptEX(IOBuffer* _buffer)
{
	DWORD lpdwBytesReceived = 0;
	return IOCP::Socket::AcceptEX(m_listenSocket, m_addressBuf, 0, &lpdwBytesReceived, _buffer->GetOverlapped());
}

bool IOCP::Session::PostRecv(IOBuffer* _buffer)
{
	DWORD lpdwBytesReceived = 0;
	DWORD lpFlag = 0;
	return IOCP::Socket::WSARecv(_buffer->GetWSABuf(), 1, &lpdwBytesReceived, &lpFlag, _buffer->GetOverlapped(), NULL);
}

void IOCP::Session::HandleAccept()
{

}
