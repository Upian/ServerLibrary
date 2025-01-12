#include "IOCPSocket.h"
#include <Ws2tcpip.h>

bool IOCPSocket::CerateSocket(int _adressFamily, int _socketType, IPPROTO _protocol, LPWSAPROTOCOL_INFO _ipProtocolInfo, GROUP _group, DWORD _wsaFlag)
{
	m_socket = WSASocket(_adressFamily, _socketType, _protocol, _ipProtocolInfo, _group, _wsaFlag);
//	WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
	return INVALID_SOCKET != m_socket;
}

bool IOCPSocket::Bind(const char* _ip, unsigned short _port)
{
	SOCKADDR_IN addr;

	addr.sin_family = AF_INET;
	addr.sin_port = ::htons(_port);	
	if (nullptr == _ip)
		addr.sin_addr.s_addr = ::htonl(INADDR_ANY);
	else
		inet_pton(AF_INET, _ip, &(addr.sin_addr)); //addr.sin_addr.s_addr = inet_addr(_ip);


	return 0 == bind(m_socket, (sockaddr*)&addr, sizeof(addr));
}

bool IOCPSocket::Listen(int backlog /*= SOMAXCONN*/)
{
	return 0 == listen(m_socket, backlog);
}

SOCKET IOCPSocket::Accept(sockaddr* addr, int* addrlen)
{
	return ::accept(m_socket, addr, addrlen);
}

bool IOCPSocket::AcceptEX(IOCPSocket* _listenSocket, PVOID lpOutputBuffer, DWORD dwReceiveDataLength, DWORD dwLocalAddressLength, DWORD dwRemoteAddressLength, LPDWORD lpdwBytesReceived, LPOVERLAPPED lpOverlapped)
{
	if (FALSE == AcceptEx(_listenSocket->GetSocket(), m_socket/*client socket*/, lpOutputBuffer, dwReceiveDataLength, dwLocalAddressLength,
		dwRemoteAddressLength, lpdwBytesReceived, lpOverlapped))
	{
		int err = WSAGetLastError();
		if (WSA_IO_PENDING != err && WSAEWOULDBLOCK != err)
			return false;
	}
	return true;
}

bool IOCPSocket::Connect(const char* _ip, USHORT _port)
{
	SOCKADDR_IN ServerAddress;
	ServerAddress.sin_family = AF_INET;
	ServerAddress.sin_port = ::htons(_port);
	inet_pton(AF_INET, _ip, &(ServerAddress.sin_addr)); //ServerAddress.sin_addr.s_addr = inet_addr(_ip);

	if (SOCKET_ERROR == connect(m_socket, (SOCKADDR*)&ServerAddress, sizeof(ServerAddress)))
	{
		int err = ::WSAGetLastError();
		if (WSA_IO_PENDING != err && WSAEWOULDBLOCK != err)
			return false;
	}
	return true;
}

bool IOCPSocket::ConnectEx(const char* _ip, USHORT _port, PVOID _lpSendBuffer, DWORD _dwSendDataLength, LPDWORD _lpdwBytesSent, LPOVERLAPPED _lpOverlapped)
{
	SOCKADDR_IN ServerAddress;
	ServerAddress.sin_family = AF_INET;
	ServerAddress.sin_port = ::htons(_port);
	inet_pton(AF_INET, _ip, &(ServerAddress.sin_addr)); //ServerAddress.sin_addr.s_addr = inet_addr(_ip);

//	return this->ConnectEx(&ServerAddress, _lpSendBuffer, _dwSendDataLength, _lpdwBytesSent, _lpOverlapped);

	if (m_lpfnConnectEX)
	{
		if (FALSE == m_lpfnConnectEX(m_socket, (LPSOCKADDR)&ServerAddress, sizeof(SOCKADDR_IN), _lpSendBuffer, _dwSendDataLength, _lpdwBytesSent, _lpOverlapped))
		{
			int err = ::WSAGetLastError();
			if (WSA_IO_PENDING != err && WSAEWOULDBLOCK != err)
				return false;
		}
	}
	return true;
}

bool IOCPSocket::ConnectEx(SOCKADDR_IN* _addr, PVOID _lpSendBuffer, DWORD _dwSendDataLength, LPDWORD _lpdwBytesSent, LPOVERLAPPED _lpOverlapped)
{
	if (m_lpfnConnectEX)
	{
		if (FALSE == m_lpfnConnectEX(m_socket, (LPSOCKADDR)_addr, sizeof(SOCKADDR_IN), _lpSendBuffer, _dwSendDataLength, _lpdwBytesSent, _lpOverlapped))
		{
			int err = ::WSAGetLastError();
			if (WSA_IO_PENDING != err && WSAEWOULDBLOCK != err)
				return false;
		}
	}
	return true;
}
