#include "IOCPSocket.h"

bool IOCPSocket::CerateSocket(int _adressFamily, int _socketType, IPPROTO _protocol, LPWSAPROTOCOL_INFO _ipProtocolInfo, int _group, int _wsaFlag)
{
	m_socket = WSASocket(_adressFamily, _socketType, _protocol, _ipProtocolInfo, _group, _wsaFlag);
//	WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
	return INVALID_SOCKET != m_socket;
}

bool IOCPSocket::BindSocket(const char* _ip, unsigned short _port)
{
	SOCKADDR_IN addr;

	addr.sin_family = AF_INET;
	addr.sin_port = ::htons(_port);	
	if (nullptr == _ip)
		addr.sin_addr.s_addr = ::htonl(INADDR_ANY);
	else
		addr.sin_addr.s_addr = inet_addr(_ip);

	return 0 == bind(m_socket, (sockaddr*)&addr, sizeof(addr));
}

bool IOCPSocket::Listen(int backlog /*= SOMAXCONN*/)
{
	return 0 == listen(m_socket, backlog);
}

