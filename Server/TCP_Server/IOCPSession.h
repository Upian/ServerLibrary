#pragma once
#include <thread>
#include "IOCPSocket.h"

/*
* IOCPSession
* 연결된 클라이언트를 처리
*/

namespace IOCP
{
	class Session : public Socket
	{
	public:
		//	IOCPSession();
		//	~IOCPSession();

		bool Initialize(SOCKET _socket, SOCKADDR_IN _addr);
	private:

	};
}