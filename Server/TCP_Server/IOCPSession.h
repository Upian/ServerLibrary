#pragma once
#include <thread>
#include "IOCPSocket.h"
/*
* IOCPSession
* 연결된 클라이언트를 처리
* 소켓 통신
*/

namespace IOCP
{
	//IOWorker
	class IOBuffer;
	class Session : protected Socket, public std::enable_shared_from_this<Session>
	{
	public:
		Session() = delete;
		Session(uint64_t _id);
		virtual ~Session();

		uint64_t GetID() const { return m_id; }

		bool PostAcceptEX(IOBuffer* _buffer, Socket* _listenSocket); //이 세선이 accept 대기
		bool PostRecv(IOBuffer* _buffer);

		void HandleAccept(); //Accept 되어 누군가 들어옴

	private:
		const uint64_t m_id = 0;
		char m_addressBuf[2 * (sizeof(SOCKADDR_IN) + 16)] = { 0, };
//		Buffer m_buffer;
	};
}