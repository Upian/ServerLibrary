#pragma once
#include "Util/ObjectPool.h"
#include "IOCPSession.h"
#include <list>

namespace IOCP
{	
	//������ ����� ��ü Session, 
	//������ ������ ��ü Proxy ����
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