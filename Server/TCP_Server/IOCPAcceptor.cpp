#include "IOCPAcceptor.h"
#include "IOCPSocket.h"
#include "IOCPHandler.h"
#include "IOCPObjectManager.h"

IOCP::Acceptor::Acceptor()
{
	m_objectManager = IOCP::ObjectManager::GetSingleton();
}

bool IOCP::Acceptor::Start(IOCP::Handler* _handler, unsigned short _port, int _maxPostAccept /*= 1*/)
{
	if (false == (m_listenSocket.CreateSocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, nullptr, 0, WSA_FLAG_OVERLAPPED)))
		return false;
	
	if (false == m_listenSocket.Bind(nullptr, _port))
	{
		m_listenSocket.CloseSocket();
		return false;
	}

	if (false == m_listenSocket.Listen())
	{
		m_listenSocket.CloseSocket();
		return false;
	}

	_handler->AssociateDevice((HANDLE)m_listenSocket.GetSocket(), (ULONG_PTR)&m_listenSocket);

	//Worker 생성 후 넣어줌
	for (int i = 0; i < _maxPostAccept; ++i)
	{
		auto session = m_objectManager->AllocSession();
		OverlappedIO* io = m_objectManager->AllocIO(IOType::Accept, session);

		session->SetListenSocket(&m_listenSocket);
		session->DoAcceptEX(io);
	}
	
	return true;
}