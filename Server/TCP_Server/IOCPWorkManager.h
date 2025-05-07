#pragma once
#include "ObjectPool.h"
#include "Singleton.h"
#include "IOCPSession.h"

namespace IOCP
{
	
	//������ ����� ��ü Session, 
	//������ ������ ��ü Proxy ����
	class WorkManager : public Singleton<WorkManager>
	{
		DECLARE_SINGLETON(WorkManager);
	public:
		std::shared_ptr<Session> AllocSession() { return m_poolSession.AllocShared(); }
		
	private:

		ObjectPool<Session> m_poolSession;
//		ObjectPool<Proxy> m_poolProxy;
	};
}