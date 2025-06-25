#include "IOCPObjectManager.h"

namespace IOCP
{
	ObjectManager::ObjectManager()
	{

	}

	ObjectManager::~ObjectManager()
	{
		m_poolSession.Clear();
	}

	std::shared_ptr<Session> ObjectManager::AllocSession()
	{
		auto session = m_poolSession.AllocShared();
		{
			std::lock_guard<std::mutex> lock(m_sessionMutex);
			m_waitAcceptMap.emplace(session.get(), session);
		}
		return session;
	}

	void ObjectManager::AcceptComplete(std::shared_ptr<Session> _session)
	{
		std::lock_guard<std::mutex> lock(m_sessionMutex);
		m_waitAcceptMap.erase(_session.get());
	}
}
