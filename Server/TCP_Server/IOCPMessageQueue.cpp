#include "IOCPMessageQueue.h"
#include "IOCPObjectManager.h"

IOCP::MessageQueue::MessageQueue()
{

}

IOCP::MessageQueue::~MessageQueue()
{

}


void IOCP::MessageQueue::Initialize()
{
	m_objectManager = IOCP::ObjectManager::GetSingleton();
}

void IOCP::MessageQueue::PushRecv(IOType _ioType, std::shared_ptr<Session> _session)
{
	auto msg = m_objectManager->AllocMessage(_ioType, _session);
	m_recvQueue.Push(msg);
}

std::shared_ptr<IOCP::Message> IOCP::MessageQueue::PopRecv()
{
	return m_recvQueue.Pop();
}
