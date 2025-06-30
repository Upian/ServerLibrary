#pragma once

#include <cstring>
#include "IOCPBuffer.h"
#include "IOCPSession.h"

namespace IOCP
{
	//��Ŷ ����
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
	//����������� ��� �����尣 �ű涧 ����ϴ� ��ü
	struct Message
	{
		IOType ioType;
		std::shared_ptr<Session> session;
		std::shared_ptr<PacketBuf> packet;
	};
}