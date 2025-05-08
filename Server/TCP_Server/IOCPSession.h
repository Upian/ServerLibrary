#pragma once
#include <thread>
#include "IOCPSocket.h"
#include "IOCPBuffer.h"
/*
* IOCPSession
* ����� Ŭ���̾�Ʈ�� ó��
* ���� ���
*/

namespace IOCP
{
	class Session : public Socket, public std::enable_shared_from_this<Session>
	{
	public:
		Session();
		virtual ~Session();

		void DoAcceptEX(Socket& _listenSocket); //�� ������ accept ���

	private:
		char m_adressBuf[2 * (sizeof(SOCKADDR_IN) + 16)];
		Buffer m_buffer;
	};
}