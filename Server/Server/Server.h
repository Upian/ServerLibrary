#pragma once

#include "TCP_Server/IOCPServer.h"

class TestServer : IOCP::Server<TestServer>
{
	DECLARE_SINGLETON(TestServer);
public:

private:

};