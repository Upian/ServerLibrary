#include "IOCPObjectManager.h"
#include "IOCPBuffer.h"

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
		auto session = m_poolSession.AllocShared(m_idGenerator.Generate());
		return session;
	}

	IOBuffer* ObjectManager::AllocBuffer(IOType _ioType, std::shared_ptr<Session> _session)
	{
		return m_poolBuffer.Alloc(_ioType, _session);
	}
	void ObjectManager::ReleaseBuffer(IOBuffer* _buffer)
	{
		m_poolBuffer.Release(_buffer);
	}
}
