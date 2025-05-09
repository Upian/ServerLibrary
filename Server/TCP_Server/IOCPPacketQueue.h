#pragma once
#include <queue>
#include <mutex>
namespace IOCP
{
	class PacketBuf;
	class PacketQueue
	{
	public:
		void PushPacket(std::shared_ptr<IOCP::PacketBuf>);
		std::shared_ptr<IOCP::PacketBuf> PopPacket();

	private:
		std::queue<std::shared_ptr<IOCP::PacketBuf> > m_packetQueue;
		std::mutex m_mutex;
	};
}