#pragma once
#include "Util/ObjectPool.h"
#include "IOCPSession.h"
#include "Util/Singleton.h"
#include <future>
#include <unordered_map>
#include <coroutine>
namespace IOCP
{	
	//서버에 연결된 객체 Session, 
	//서버가 연결한 객체 Proxy 관리
	class ObjectManager : public Singleton<ObjectManager>
	{
		DECLARE_SINGLETON(ObjectManager)
	public:
		std::shared_ptr<Session> AllocSession();
		void AcceptComplete(std::shared_ptr<Session> _session);

	private:
		ObjectManager(int _poolSize);

		ObjectPool<Session> m_poolSession;
		std::mutex m_sessionMutex;
		std::unordered_map<Session*, std::shared_ptr<Session> > m_waitAcceptMap;
//		ObjectPool<Proxy> m_poolProxy;

	};
}