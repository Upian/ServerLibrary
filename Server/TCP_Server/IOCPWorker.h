#pragma once
#include "IOCPSocket.h"
#include "IOCPBuffer.h"
namespace IOCP
{
	//Socket Ελ½Ε
	class Worker : public Socket
	{
	public:
		void DoAcceptEX(Socket& _listenSocket);
	private:
		char m_adressBuf[2 * (sizeof(SOCKADDR_IN) + 16)];
		Buffer m_buffer;
	};
}