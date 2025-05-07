#pragma once
#include <winsock2.h>
#include "IOCPSocket.h"

namespace IOCP
{
	enum class IOType : unsigned char
	{
		None = 0,
		Accept,
		Send,
		Recv,
		Count,
	};
	
	class Buffer
	{
	public:
		Buffer() = default; //임시
		virtual ~Buffer() = default;

		WSAOVERLAPPED* GetOverlapped() { return &m_overlapped; }

		void 	SetWSABuf(char* _buf, int _len) { m_wsaBuf.buf = _buf;  m_wsaBuf.len = _len; }
		void 	SetWSABuf(const WSABUF& _wsaBuf) { m_wsaBuf = _wsaBuf; }
		WSABUF* GetWSABuf() { return &m_wsaBuf; }

		void SetIOType(IOType _ioType) { m_ioType = _ioType; }
		IOType GetIOType() const { m_ioType; }
	private:
		WSAOVERLAPPED m_overlapped;
		WSABUF m_wsaBuf;
		//	char buffer[1024]; //패킷에 있는 버퍼 사용
		IOType m_ioType;
		IOCP::Socket m_socket;
	};
}
