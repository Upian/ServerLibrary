#pragma once

#include <cstring>
#include "IOCPBuffer.h"
#include "IOCPSession.h"

namespace IOCP
{
	//패킷 버퍼
	class PacketBuf
	{
	public:
		PacketBuf() = default;
//		PacketBuf(int _bufSize);
		virtual ~PacketBuf();

		void InitBufSize(int _size);
		void BufReset() { std::memset(m_buf, 0, sizeof(m_buf)); }
	private:
		unsigned char* m_buf = nullptr;
		int m_bufSize = 0;
	};
	//로직스레드와 통신 스레드간 옮길때 사용하는 객체
	struct Message
	{
		IOType ioType;
		std::shared_ptr<Session> session;
		std::shared_ptr<PacketBuf> packet;
	};
}