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

		OverlappedIO* AllocIO(IOType _ioType, std::shared_ptr<Session> _session);
		void ReleaseIO(OverlappedIO* _io);
	private:
		ObjectManager(int _poolSize);

		ObjectPool<Session> m_poolSession;
		std::mutex m_sessionMutex;
		ObjectPool<OverlappedIO> m_poolOverlappedIO;
//		ObjectPool<Proxy> m_poolProxy;

	};
}