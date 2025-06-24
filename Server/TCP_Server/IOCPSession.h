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
		Session(Socket* _listenSocket);
		virtual ~Session();

		void SetListenSocket(Socket* _listenSocket) { m_listenSocket = _listenSocket; }
		Socket* GetListenSocket() const { return m_listenSocket; }

		void DoAcceptEX(); //이 세선이 accept 대기
		void DoAcceptEX(Socket& _listenSocket); //이 세선이 accept 대기

		void HandleAccept(); //Accept 되어 누군가 들어옴

	private:
		Socket* m_listenSocket = nullptr;
		char m_adressBuf[2 * (sizeof(SOCKADDR_IN) + 16)];
		Buffer m_buffer;
	};
}