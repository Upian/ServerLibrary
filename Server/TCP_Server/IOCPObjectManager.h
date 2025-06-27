#pragma once
#include "Util/ObjectPool.h"
#include "Util/Singleton.h"
#include "Util/SequenceGenerator.h"

#include "IOCPBuffer.h"
#include "IOCPSession.h"
namespace IOCP
{	
	//������ ����� ��ü Session, IO�� Buffer ����
	// 
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
		SequenceGenerator m_idGenerator;

		ObjectPool<IOBuffer> m_poolBuffer;
//		ObjectPool<Proxy> m_poolProxy;

	};
}