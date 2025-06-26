#pragma once
#include "Util/ConcurrentQueue.h"
#include "Util/Singleton.h"
#include "IOCPSession.h"

class IOCPMessage
{
//	Session
//	Buffer
};

namespace IOCP
{
	class Message
	{
		IOType ioType;
		std::shared_ptr<Session> session;
		Buffer buffer;
	};

	class MessageQueue : public Singleton<MessageQueue>
	{
		DECLARE_SINGLETON(MessageQueue)
	public:
		void Push();


	private:
		ConcurrentQueue<Message*> m_recvQueue;
		ConcurrentQueue<int> m_sendQueue;
	};
}