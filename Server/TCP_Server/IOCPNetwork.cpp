#include "IOCPNetwork.h"
#include "IOCPAcceptor.h"
#include "IOCPObjectManager.h"
#include "IOCPMessageQueue.h"

IOCP::Network::Network()
{
	if (false == m_IOCPHandler.Initialize())
	{
		//		error log
	}
	
	if (nullptr == m_objectManager)
		m_objectManager = new IOCP::ObjectManager();
	if (nullptr == m_messageQueue)
		m_messageQueue = new IOCP::MessageQueue();
	if (nullptr == m_acceptor)
		m_acceptor = new IOCP::Acceptor();
	
	if (nullptr == m_workThread)
		m_workThread = new IOCP::WorkThread(&m_IOCPHandler);
}

IOCP::Network::~Network()
{
	if (nullptr != m_objectManager)
	{
		delete m_objectManager;
		m_objectManager = nullptr;
	}
	if (nullptr != m_messageQueue)
	{
		delete m_messageQueue;
		m_messageQueue = nullptr;
	}
	if (nullptr != m_acceptor)
	{
		delete m_acceptor;
		m_acceptor = nullptr;
	}
	if (nullptr != m_workThread)
	{
		delete m_workThread;
		m_workThread = nullptr;
	}
}

void IOCP::Network::Initialize(int _threadCnt)
{
	m_acceptor->Initialize();
	m_messageQueue->Initialize();
	m_workThread->Initialize(_threadCnt);
}

void IOCP::Network::Run(unsigned short _port, int _maxAcceptorCnt /*= 1*/)
{
	m_acceptor->Start(&m_IOCPHandler, _port, _maxAcceptorCnt);
}

/*
template<typename T_Packet>
	requires IOCP::DerivedFromPacketBuf<T_Packet>
std::shared_ptr<T_Packet> IOCP::Network::AllocPacket()
{
//	return std::static_pointer_cast<T_Packet>(this->AllocPacketBuf());
}
*/