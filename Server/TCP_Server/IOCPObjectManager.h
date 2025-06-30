#pragma once
#include "Util/ObjectPool.h"
#include "Util/Singleton.h"
#include "Util/SequenceGenerator.h"

#include "IOCPBuffer.h"
#include "IOCPSession.h"
#include "IOCPPacketBuf.h"
namespace IOCP
{	
	//서버에 연결된 객체 Session, IO용 Buffer 관리
	// 
	//서버가 연결한 객체 Proxy 관리
	class ObjectManager
	{
	public:
		ObjectManager();
		~ObjectManager();

		std::shared_ptr<Session> AllocSession();

		IOBuffer* AllocBuffer(IOType _ioType, std::shared_ptr<Session> _session);
		void ReleaseBuffer(IOBuffer* _buffer);

		std::shared_ptr<Message> AllocMessage(IOType _ioType, std::shared_ptr<Session> _session);
	private:
		ObjectPool<Session> m_poolSession;
		SequenceGenerator m_idGenerator;

		ObjectPool<IOBuffer> m_poolBuffer;

		ObjectPool<Message> m_poolMessage;
	};
}