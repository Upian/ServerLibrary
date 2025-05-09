#pragma once

#include <cstring>

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
}