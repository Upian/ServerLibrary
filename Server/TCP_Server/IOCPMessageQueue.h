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
	};

	class MessageQueue : public Singleton<MessageQueue>
	{
		DECLARE_SINGLETON(MessageQueue)
	public:
		void Push();


	private:
		ConcurrentQueue<Message*> m_recvQueue; // accept, recv
		ConcurrentQueue<Message*> m_sendQueue;
	};
}