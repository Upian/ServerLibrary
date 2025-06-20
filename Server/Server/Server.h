#pragma once

#include "TCP_Server/IOCPServer.h"
#include "TCP_Server/IOCPPacketPool.h"

class TestIOCPPacket : public IOCP::PacketBuf
{

};

class TestIOCPServer : public IOCP::Server
{
public:
	TestIOCPServer();
	~TestIOCPServer();
	virtual void HandleThread() override;
	virtual std::shared_ptr<IOCP::PacketBuf> AllocPacketBuf() override;
private:
	IOCP::PacketPool<TestIOCPPacket> m_packetPool;
};
