#pragma once
#include <winsock2.h>

class IOCPSocket
{
public:
	bool CerateSocket(int _adressFamily, int _socketType, IPPROTO _protocol, LPWSAPROTOCOL_INFO _ipProtocolInfo, int _group, int _wsaFlag);
	bool BindSocket(const char* _ip, unsigned short _port);
	bool Listen(int backlog = SOMAXCONN);

private:
	SOCKET m_socket = INVALID_SOCKET;


};