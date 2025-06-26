#pragma once
#include "Util/ObjectPool.h"
#include "IOCPSession.h"
#include "Util/Singleton.h"
#include <future>
#include <unordered_map>
#include <coroutine>
namespace IOCP
{	
	//������ ����� ��ü Session, 
	//������ ������ ��ü Proxy ����
	class ObjectManager : public Singleton<ObjectManager>
	{
		DECLARE_SINGLETON(ObjectManager)
	public:
		std::shared_ptr<Session> AllocSession();

		IOBuffer* AllocBuffer(IOType _ioType, std::shared_ptr<Session> _session);
		void ReleaseBuffer(IOBuffer* _buffer);
	private:
		ObjectManager(int _poolSize);

		ObjectPool<Session> m_poolSession;
		std::mutex m_sessionMutex;
		ObjectPool<IOBuffer> m_poolBuffer;
//		ObjectPool<Proxy> m_poolProxy;

	};
}