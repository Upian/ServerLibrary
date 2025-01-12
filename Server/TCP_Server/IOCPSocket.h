#pragma once
#include <winsock2.h>
#include <MSWSock.h>
/*
* 소켓 구조체
*/

class IOCPSocket
{
public:
	SOCKET GetSocket() { return m_socket; }

	bool CerateSocket(int _adressFamily, int _socketType, IPPROTO _protocol, LPWSAPROTOCOL_INFO _ipProtocolInfo, GROUP _group, DWORD _wsaFlag);
	bool Bind(const char* _ip, USHORT _port);
	bool Listen(int backlog = SOMAXCONN);
	SOCKET Accept(sockaddr* _addr, int* _addrlen);
	bool AcceptEX(IOCPSocket* _listenSocket, PVOID lpOutputBuffer, DWORD dwReceiveDataLength, DWORD dwLocalAddressLength, DWORD dwRemoteAddressLength, LPDWORD lpdwBytesReceived, LPOVERLAPPED lpOverlapped);
	bool Connect(const char* _ip, USHORT _port);
	bool ConnectEx(const char* _ip, USHORT _port, PVOID _lpSendBuffer, DWORD _dwSendDataLength, LPDWORD _lpdwBytesSent, LPOVERLAPPED _lpOverlapped);
	bool ConnectEx(SOCKADDR_IN* _addr, PVOID _lpSendBuffer, DWORD _dwSendDataLength, LPDWORD _lpdwBytesSent, LPOVERLAPPED _lpOverlapped);
	//recv
	//send
private:
	SOCKET m_socket = INVALID_SOCKET;
	LPFN_CONNECTEX m_lpfnConnectEX;

};