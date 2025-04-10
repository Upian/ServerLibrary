#pragma once
#include <thread>
#include "IOCPSocket.h"

/*
* IOCPSession
* 연결된 클라이언트를 처리
*/
class IOCPSession : public IOCPSocket
{
public:
//	IOCPSession();
//	~IOCPSession();

	bool Initialize( SOCKET _socket, SOCKADDR_IN _addr );
private:
		
};