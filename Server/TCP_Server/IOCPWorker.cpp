#include "IOCPWorker.h"

void IOCP::Worker::DoAcceptEX(Socket& _listenSocket)
{
	DWORD lpdwBytesReceived = 0;
	IOCP::Socket::AcceptEX(&_listenSocket, m_adressBuf, 0, &lpdwBytesReceived, m_buffer.GetOverlapped());
}
