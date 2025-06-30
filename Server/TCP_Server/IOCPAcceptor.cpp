#include "IOCPAcceptor.h"
#include "IOCPSocket.h"
#include "IOCPHandler.h"
#include "IOCPObjectManager.h"
#include "IOCPBuffer.h"
#include "IOCPSession.h"
#include "IOCPNetwork.h"

IOCP::Acceptor::Acceptor()
{
}

IOCP::Acceptor::~Acceptor()
{
}

void IOCP::Acceptor::Initialize()
{
	m_objectManager = IOCP::Network::GetSingleton()->GetObjectManager();
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
		this->PostAcceptEX();
	}
	
	return true;
}

bool IOCP::Acceptor::PostAcceptEX()
{
	auto session = m_objectManager->AllocSession();
	auto buffer = m_objectManager->AllocBuffer(IOType::Accept, session);
	bool result = session->PostAcceptEX(buffer, &m_listenSocket);

	{
		std::lock_guard<std::mutex> lock(m_acceptMutex);
		m_waitSessionMap.emplace(session->GetID(), session);
	}

	return result;
}

void IOCP::Acceptor::OnAcceptComplete(std::shared_ptr<Session> _session)
{
	std::lock_guard<std::mutex> lock(m_acceptMutex);
	m_waitSessionMap.erase(_session->GetID());
}
