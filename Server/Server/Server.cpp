#include <iostream>
#include "Server.h"

TestIOCPServer::TestIOCPServer()
{
	m_packetPool.Initialize(100, 1024);
}

TestIOCPServer::~TestIOCPServer()
{

}

void TestIOCPServer::HandleThread()
{
}

std::shared_ptr<IOCP::PacketBuf> TestIOCPServer::AllocPacketBuf()
{
	return m_packetPool.AllocShared();
}

