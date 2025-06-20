#include <iostream>
#include "Server.h"

TestServer::TestServer()
{
	m_packetPool.Initialize(100, 1024);
}

TestServer::~TestServer()
{

}

void TestServer::HandleThread()
{
}

std::shared_ptr<IOCP::PacketBuf> TestServer::AllocPacketBuf()
{
	return m_packetPool.AllocShared();
}

