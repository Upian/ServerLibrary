#include "IOCPWorker.h"

IOCP::Worker::Worker() :
	IOCP::Socket()
{
	IOCP::Socket::CreateSocket();
}

IOCP::Worker::~Worker()
{
}

void IOCP::Worker::DoAcceptEX(Socket& _listenSocket)
{
	DWORD lpdwBytesReceived = 0;

	m_buffer.SetIOType(IOType::Accept);
	IOCP::Socket::AcceptEX(&_listenSocket, m_adressBuf, 0, &lpdwBytesReceived, m_buffer.GetOverlapped());

}
