#pragma once
#include <thread>
#include "IOCPSocket.h"

/*
* IOCPSession
* ����� Ŭ���̾�Ʈ�� ó��
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