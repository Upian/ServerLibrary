#include "IOCPBuffer.h"
#include "IOCPWorkThread.h"
#include "IOCPHandler.h"
#include "IOCPSession.h"
#include "IOCPSessionManager.h"
#include <iostream>
//IOCP::Handler

IOCP::WorkThread::WorkThread(IOCP::Handler* _iocpHandler) :
	m_iocpHandler(_iocpHandler)
{
	m_sessionManager = SessionManager::GetSingleton();
}

void IOCP::WorkThread::Initialize(int _threadCount)
{
	for (int i = 0; i < _threadCount; ++i)
	{
		m_workerThread.emplace_back(std::jthread(
			[this](std::stop_token _token) {
				this->Worker(_token); 
			}
		));
	}
}

void IOCP::WorkThread::Worker(std::stop_token _token)
{
	DWORD bytesTransferred = 0;
	ULONG_PTR completionKey = 0; //Listen socket 포인터
	OverlappedIO* overlappedIO = nullptr;

	bool isSuccess = true;
	//Log
	while (false == _token.stop_requested())
	{
		isSuccess = m_iocpHandler->GetCompletionStatus(&bytesTransferred, &completionKey, (OVERLAPPED**)&overlappedIO);
		std::cout << 
			"Success: " << isSuccess << 
			" completionKey: " << completionKey << 
			" bytesTransferred: " << bytesTransferred << 
			" IOType: " << int(overlappedIO->ioType) <<
			std::endl;

		if (0 == completionKey) //종료
			break;

		if (nullptr == overlappedIO)
			continue;

		if (false == isSuccess)
			continue;
		
		if (true == overlappedIO->session.expired())
			continue;

		auto session = std::static_pointer_cast<IOCP::Session>(overlappedIO->session.lock());
		switch (overlappedIO->ioType)
		{
		case IOType::None:
		{
			//log
			break;
		}
		case IOType::Accept:
		{
			session->HandleAccept();
			auto newSession = m_sessionManager->AllocSession();

			newSession->SetListenSocket(session->GetListenSocket());
			newSession->DoAcceptEX();

			m_sessionManager->AcceptComplete(session);

		}
//				Send,
		case IOType::Recv:
		{

		}
		default:
		{

		}
		}


		if (0 == bytesTransferred)
			continue;
	
	}
}
