#include "IOCPPacketBuf.h"
IOCP::PacketBuf::~PacketBuf()
{
	if (nullptr != m_buf)
	{
		delete[] m_buf;
		m_buf = nullptr;
	}
	m_bufSize = 0;
}
/*
IOCP::PacketBuf::PacketBuf(int _bufSize) :
	m_bufSize(_bufSize)
{
	m_buf = new unsigned char[_bufSize];
}
*/
void IOCP::PacketBuf::InitBufSize(int _size)
{
	m_bufSize = _size;
	m_buf = new unsigned char[_size];
}
