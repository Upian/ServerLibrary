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
		Session(Socket* _listenSocket);
		virtual ~Session();

		void SetListenSocket(Socket* _listenSocket) { m_listenSocket = _listenSocket; }
		Socket* GetListenSocket() const { return m_listenSocket; }

		bool DoAcceptEX(OverlappedIO* _io); //�� ������ accept ���

		void HandleAccept(); //Accept �Ǿ� ������ ����

	private:
		Socket* m_listenSocket = nullptr;
		char m_addressBuf[2 * (sizeof(SOCKADDR_IN) + 16)] = { 0, };
		Buffer m_buffer;
	};
}