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
		return session;
	}

	//_session이 _ioType을 위해 할당
	OverlappedIO* ObjectManager::AllocIO(IOType _ioType, std::shared_ptr<Session> _session)
	{
		return m_poolOverlappedIO.Alloc(_ioType, _session);
	}
	
	void ObjectManager::ReleaseIO(OverlappedIO* _io)
	{
		m_poolOverlappedIO.Release(_io);
	}
}
