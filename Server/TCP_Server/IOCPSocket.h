#pragma once
#include <winsock2.h>
#include <MSWSock.h>
/*
* 소켓 구조체
*/
namespace IOCP
{
	class Socket
	{
	public:
		Socket() = default;
		virtual ~Socket();

		SOCKET GetSocket() { return m_socket; }

		bool CreateSocket(int _adressFamily = AF_INET, int _socketType = SOCK_STREAM, IPPROTO _protocol = IPPROTO_TCP, LPWSAPROTOCOL_INFO _ipProtocolInfo = nullptr, GROUP _group = 0, DWORD _wsaFlag = WSA_FLAG_OVERLAPPED);

		bool Bind(const char* _ip, USHORT _port); // _ip가 0이면 INADDR_ANY 사용
		bool Listen(int backlog = SOMAXCONN);
		SOCKET Accept(sockaddr* _addr, int* _addrlen);
		bool AcceptEX(Socket* _listenSocket, PVOID lpOutputBuffer, DWORD dwReceiveDataLength, /*DWORD dwLocalAddressLength, DWORD dwRemoteAddressLength,*/ LPDWORD lpdwBytesReceived, LPOVERLAPPED lpOverlapped);
		bool Connect(const char* _ip, USHORT _port);
		bool ConnectEx(const char* _ip, USHORT _port, PVOID _lpSendBuffer, DWORD _dwSendDataLength, LPDWORD _lpdwBytesSent, LPOVERLAPPED _lpOverlapped);
		bool ConnectEx(SOCKADDR_IN* _addr, PVOID _lpSendBuffer, DWORD _dwSendDataLength, LPDWORD _lpdwBytesSent, LPOVERLAPPED _lpOverlapped);

		//recv
		//send

		bool WSASend(LPWSABUF _lpBuffers, DWORD _dwBufferCount, LPDWORD _lpNumberOfBytesSent, DWORD _dwFlags, LPWSAOVERLAPPED _lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE _lpCompletionRoutine);
		bool WSARecv(LPWSABUF _lpBuffers, DWORD _dwBufferCount, LPDWORD _lpNumberOfBytesRecvd, LPDWORD _lpFlags, LPWSAOVERLAPPED _lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE _lpCompletionRoutine);

		bool WSASendTo(LPWSABUF _lpBuffers, DWORD _dwBufferCount, LPDWORD _lpNumberOfBytesSent, DWORD _dwFlags, const sockaddr* _lpTo, int _iToLen, LPWSAOVERLAPPED _lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE _lpCompletionRoutine);
		bool WSARecvFrom(LPWSABUF _lpBuffers, DWORD _dwBufferCount, LPDWORD _lpNumberOfBytesRecvd, LPDWORD _lpFlags, sockaddr* _lpFrom, LPINT _lpFromlen, LPWSAOVERLAPPED _lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE _lpCompletionRoutine);


		bool ShutDown(int _how = SD_BOTH);
		bool CloseSocket();

	protected:
		SOCKET m_socket = INVALID_SOCKET;
		LPFN_CONNECTEX m_lpfnConnectEX = nullptr;

	};
}