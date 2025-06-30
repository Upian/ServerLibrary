#pragma once
#include "Util/ConcurrentQueue.h"
#include "Util/Singleton.h"
#include "Util/ObjectPool.h"
#include "IOCPSession.h"
#include "IOCPPacketBuf.h"

namespace IOCP
{
	class ObjectManager;
	class MessageQueue
	{
	public:
		MessageQueue();
		~MessageQueue();

		void Initialize();

		void PushRecv(IOType _ioType, std::shared_ptr<Session> _session);
		std::shared_ptr<IOCP::Message> PopRecv();

	private:
		ObjectManager* m_objectManager = nullptr;
		ConcurrentQueue<std::shared_ptr<IOCP::Message> > m_recvQueue; // accept, recv
		ConcurrentQueue<std::shared_ptr<IOCP::Message> > m_sendQueue;
	};
}