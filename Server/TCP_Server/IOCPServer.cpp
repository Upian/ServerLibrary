#include "IOCPServer.h"

IOCP::Server::Server()
{
	if (false == m_IOCPHandler.Initialize())
	{
		//		error log
	}
	m_objectManager = IOCP::ObjectManager::CreateSingleton();
	m_acceptor = IOCP::Acceptor::CreateSingleton();
	if (nullptr == m_workThread)
	{
		m_workThread = new IOCP::WorkThread(&m_IOCPHandler);
	}
}

IOCP::Server::~Server()
{
	IOCP::ObjectManager::DestroySingleton();
	if (nullptr != m_workThread)
	{
		delete m_workThread;
		m_workThread = nullptr;
	}
}

void IOCP::Server::Initialize(int _threadCnt, unsigned short _port, int _maxAcceptorCnt)
{
	m_workThread->Initialize(_threadCnt);
	m_acceptor->Start(&m_IOCPHandler, _port, _maxAcceptorCnt);
}

template<typename T_Packet>
	requires IOCP::DerivedFromPacketBuf<T_Packet>
std::shared_ptr<T_Packet> IOCP::Server::AllocPacket()
{
	return std::static_pointer_cast<T_Packet>(this->AllocPacketBuf());
}
