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

	TaskSession<std::shared_ptr<Session> > SessionManager::AllocSessionAsync()
	{
		auto session = m_poolSession.AllocShared();

//		co_await AsyncAddWaitAccept(session);
		co_return session;
	}

	void SessionManager::AcceptComplete(std::shared_ptr<Session> _session)
	{
		std::lock_guard<std::mutex> lock(m_sessionMutex);
		m_waitAcceptMap.erase(_session.get());
	}

	TaskSession<bool> SessionManager::AsyncAddWaitAccept(std::shared_ptr<Session> _session)
	{
		std::lock_guard<std::mutex> lock(m_sessionMutex);
		co_return m_waitAcceptMap.emplace(_session.get(), _session).second;
	}

}
