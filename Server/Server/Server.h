#pragma once

#include "TCP_Server/IOCPNetwork.h"
#include "TCP_Server/IOCPPacketPool.h"



class TestIOCPServer
{
public:
	TestIOCPServer();
	~TestIOCPServer();
//	virtual void HandleThread() override;
//	virtual std::shared_ptr<IOCP::PacketBuf> AllocPacketBuf() override;

	IOCP::Network* GetNetwork() { return m_network; }
	
private:
	IOCP::Network* m_network = nullptr;
};
