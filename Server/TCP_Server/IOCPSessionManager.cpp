#include "IOCPSessionManager.h"

namespace IOCP
{
	SessionManager::SessionManager()
	{

	}

	SessionManager::~SessionManager()
	{
		m_poolSession.Clear();
	}

	std::shared_ptr<Session> SessionManager::AllocSession()
	{
		auto session = m_poolSession.AllocShared();
		{
			std::lock_guard<std::mutex> lock(m_sessionMutex);
			m_waitAcceptMap.emplace(session.get(), session);
		}
		return session;
	}

	void SessionManager::AcceptComplete(std::shared_ptr<Session> _session)
	{
		std::lock_guard<std::mutex> lock(m_sessionMutex);
		m_waitAcceptMap.erase(_session.get());
	}
}
