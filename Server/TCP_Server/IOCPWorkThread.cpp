#include "IOCPBuffer.h"
#include "IOCPWorkThread.h"
#include "IOCPHandler.h"
#include "IOCPSession.h"
#include "IOCPObjectManager.h"
#include "IOCPAcceptor.h"
#include <iostream>
//IOCP::Handler

IOCP::WorkThread::WorkThread(IOCP::Handler* _iocpHandler) :
	m_iocpHandler(_iocpHandler)
{
	m_objectManager = ObjectManager::GetSingleton();
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

		IOBuffer* ioBuffer = static_cast<IOBuffer*>(overlappedIO->buffer);
		if (nullptr != overlappedIO &&
			true == isSuccess &&
			false == ioBuffer->IsSessionExpired())
		{
			auto session = std::static_pointer_cast<IOCP::Session>(ioBuffer->GetSession());

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
				Acceptor::GetSingleton()->OnAcceptComplete(session);
				Acceptor::GetSingleton()->PostAcceptEX();
			}
			//				Send,
			case IOType::Recv:
			{

			}
			default:
			{

			}
			}
		}

		m_objectManager->ReleaseBuffer(ioBuffer);

		if (0 == bytesTransferred)
			continue;
	
	}
}
