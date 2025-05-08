#pragma once
#include <thread>
#include "IOCPSocket.h"
#include "IOCPBuffer.h"
/*
* IOCPSession
* 연결된 클라이언트를 처리
* 소켓 통신
*/

namespace IOCP
{
	class Session : public Socket, public std::enable_shared_from_this<Session>
	{
	public:
		Session();
		virtual ~Session();

		void DoAcceptEX(Socket& _listenSocket); //이 세선이 accept 대기

	private:
		char m_adressBuf[2 * (sizeof(SOCKADDR_IN) + 16)];
		Buffer m_buffer;
	};
}