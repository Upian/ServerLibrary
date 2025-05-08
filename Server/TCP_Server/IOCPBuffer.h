#pragma once
#include "IOCPSocket.h"
#include <memory>

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
		std::shared_ptr<void> session = nullptr;
	};

	class Buffer
	{
	public:
		Buffer() = default; //임시
		virtual ~Buffer() = default;

		OverlappedIO* GetOverlapped() { return &m_overlappedIO; }

		void 	SetWSABuf(char* _buf, int _len) { m_wsaBuf.buf = _buf;  m_wsaBuf.len = _len; }
		void 	SetWSABuf(const WSABUF& _wsaBuf) { m_wsaBuf = _wsaBuf; }
		WSABUF* GetWSABuf() { return &m_wsaBuf; }

		void SetSession(std::shared_ptr<void> _session) { m_overlappedIO.session = _session; }

		void SetIOType(IOType _ioType) { m_overlappedIO.ioType = _ioType; }
		IOType GetIOType() const { return m_overlappedIO.ioType; }
	private:
		OverlappedIO m_overlappedIO;
		WSABUF m_wsaBuf;
		//	char buffer[1024]; //패킷에 있는 버퍼 사용
		IOCP::Socket m_socket;
	};
}
