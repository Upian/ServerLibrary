#pragma once
#include "Util/ObjectPool.h"
#include "IOCPSession.h"
#include "Util/Singleton.h"
#include <list>

namespace IOCP
{	
	//������ ����� ��ü Session, 
	//������ ������ ��ü Proxy ����
	class SessionManager : public Singleton<SessionManager>
	{
		DECLARE_SINGLETON(SessionManager)
	public:
		std::shared_ptr<Session> AllocSession() { return m_poolSession.AllocShared(); }
		
	private:
		SessionManager(int _poolSize);

		ObjectPool<Session> m_poolSession;
//		ObjectPool<Proxy> m_poolProxy;

	};
}