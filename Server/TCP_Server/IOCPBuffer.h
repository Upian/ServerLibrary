#pragma once
#include "IOCPSocket.h"
#include <memory>
#include <iostream>
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
	
	struct OverlappedIO : public WSAOVERLAPPED
	{
		IOType ioType = IOType::None;
		std::shared_ptr<void> session;

		OverlappedIO(IOType _ioType, std::shared_ptr<void> _session) :
			WSAOVERLAPPED(), ioType(_ioType), session(_session)
		{
		}
		~OverlappedIO() {
			ioType = IOType::None;
			session = nullptr;
		}
	};

	class Buffer
	{
	public:
		Buffer() = default; //임시
		virtual ~Buffer() = default;

		void Clear() { m_socket.CloseSocket(); }

		void 	SetWSABuf(char* _buf, int _len) { m_wsaBuf.buf = _buf;  m_wsaBuf.len = _len; }
		void 	SetWSABuf(const WSABUF& _wsaBuf) { m_wsaBuf = _wsaBuf; }
		WSABUF* GetWSABuf() { return &m_wsaBuf; }

	private:
		WSABUF m_wsaBuf;
		//	char buffer[1024]; //패킷에 있는 버퍼 사용
		IOCP::Socket m_socket;
	};
}
