#pragma once
#include "ObjectPool.h"
#include "Singleton.h"
#include "IOCPSession.h"
#include <list>

namespace IOCP
{	
	//������ ����� ��ü Session, 
	//������ ������ ��ü Proxy ����
	class SessionManager : public Singleton<SessionManager>
	{
		DECLARE_SINGLETON(SessionManager);
	public:
		std::shared_ptr<Session> AllocSession() { return m_poolSession.AllocShared(); }
		
		void AddSession(std::shared_ptr<Session> _session) { m_SessionList.push_back(_session); }
	private:
		ObjectPool<Session> m_poolSession;
//		ObjectPool<Proxy> m_poolProxy;

		std::list<std::shared_ptr<Session> > m_SessionList;
	};
}