#pragma once
#include "Util/ObjectPool.h"
#include "IOCPSession.h"
#include <list>

namespace IOCP
{	
	//서버에 연결된 객체 Session, 
	//서버가 연결한 객체 Proxy 관리
	class SessionManager
	{
	public:
		SessionManager() = default;
		~SessionManager() = default;
		std::shared_ptr<Session> AllocSession() { return m_poolSession.AllocShared(); }
		
	private:
		ObjectPool<Session, true> m_poolSession;
//		ObjectPool<Proxy> m_poolProxy;

	};
}