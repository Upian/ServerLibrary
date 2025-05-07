#pragma once
#include "ObjectPool.h"
#include "Singleton.h"
#include "IOCPSession.h"

namespace IOCP
{
	
	//서버에 연결된 객체 Session, 
	//서버가 연결한 객체 Proxy 관리
	class WorkManager : public Singleton<WorkManager>
	{
		DECLARE_SINGLETON(WorkManager);
	public:
		std::shared_ptr<Session> AllocSession() { return m_poolSession.AllocShared(); }
		
	private:

		ObjectPool<Session> m_poolSession;
//		ObjectPool<Proxy> m_poolProxy;
	};
}