#pragma once

#include "TCP_Server/IOCPServer.h"

class TestServer : public IOCP::Server<TestServer>
{
	DECLARE_SINGLETON(TestServer);
public:
	virtual void HandleThread() override;
private:

};