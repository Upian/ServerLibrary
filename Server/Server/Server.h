#pragma once

#include "TCP_Server/IOCPServer.h"
#include "TCP_Server/IOCPPacketPool.h"

class TestPacket : public IOCP::PacketBuf
{

};

class TestServer : public IOCP::Server<TestServer>
{
	DECLARE_SINGLETON(TestServer);
public:
	virtual void HandleThread() override;
	virtual std::shared_ptr<IOCP::PacketBuf> AllocPacketBuf() override;
private:
	IOCP::PacketPool<TestPacket> m_packetPool;
};