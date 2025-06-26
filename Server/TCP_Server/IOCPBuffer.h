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
		void* buffer;

		OverlappedIO(IOType _ioType, void* _buffer) :
			WSAOVERLAPPED(), ioType(_ioType), buffer(_buffer)
		{
		}
		~OverlappedIO() {
			ioType = IOType::None;
			buffer = nullptr;
		}
	};

	class IOBuffer
	{
	public:
		IOBuffer() = delete;
		IOBuffer(IOType _ioType, std::weak_ptr<void> _session) : m_io(_ioType, this), m_wsaBuf(), session(_session)
		{
		}
		virtual ~IOBuffer() = default;

		OverlappedIO* GetOverlapped() { return &m_io; }
		IOType GetIOType() const { return m_io.ioType; }

		void 	SetWSABuf(char* _buf, int _len) { m_wsaBuf.buf = _buf;  m_wsaBuf.len = _len; }
		void 	SetWSABuf(const WSABUF& _wsaBuf) { m_wsaBuf = _wsaBuf; }
		WSABUF* GetWSABuf() { return &m_wsaBuf; }

		std::shared_ptr<void> GetSession() { return session.lock(); }
		bool IsSessionExpired() const { return session.expired(); }
	private:
		std::weak_ptr<void> session;
		OverlappedIO m_io;
		WSABUF m_wsaBuf;
		//	char buffer[1024]; //패킷에 있는 버퍼 사용
	};
}
