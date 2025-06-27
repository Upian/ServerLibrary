#pragma once
#include "Util/Singleton.h"
#include "IOCPSocket.h"
#include <unordered_map>
namespace IOCP
{
	class Handler;
	class ObjectManager;
	class Session;
	class Acceptor : public Singleton<Acceptor>
	{
		DECLARE_SINGLETON(Acceptor)
	public:
//		Acceptor();
		bool Start(IOCP::Handler* _handler, unsigned short _port, int _maxPostAccept = 1);

		IOCP::Socket GetListenSocket() const { return m_listenSocket; }
		bool PostAcceptEX();
		void OnAcceptComplete(std::shared_ptr<Session> _session);
	private:
		IOCP::Socket m_listenSocket;
		IOCP::ObjectManager* m_objectManager = nullptr;
		
		std::mutex m_acceptMutex;
		std::unordered_map<uint64_t/*id*/, std::shared_ptr<Session> > m_waitSessionMap;//accept ¥Î±‚¡ﬂ
	};
}