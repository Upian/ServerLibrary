#pragma once
#include <thread>
#include "IOCPSocket.h"

/*
* IOCPSession
* ����� Ŭ���̾�Ʈ�� ó��
*/
class IOCPSession : public IOCPSocket
{
public:
//	IOCPSession();
//	~IOCPSession();

	bool Initialize( SOCKET _socket, SOCKADDR_IN _addr );
private:
		
};