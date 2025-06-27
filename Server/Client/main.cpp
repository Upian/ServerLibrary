#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <mswsock.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <iostream>
#include <vector>
#include <thread>
#include <atomic>
#include <chrono>
#include <format>

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "mswsock.lib")

LPFN_CONNECTEX GetConnectEx(SOCKET sock)
{
	GUID guid = WSAID_CONNECTEX;
	LPFN_CONNECTEX fn = nullptr;
	DWORD bytes = 0;
	WSAIoctl(sock, SIO_GET_EXTENSION_FUNCTION_POINTER,
		&guid, sizeof(guid), &fn, sizeof(fn), &bytes, nullptr, nullptr);
	return fn;
}

struct IOData : public OVERLAPPED
{
	WSABUF wsaBuf;
	char buffer[1024];
	enum class IOType { Connect, Send, Recv } type;
};

class ClientWorker
{
public:
	ClientWorker(const char* ip, int port)
		: m_ip(ip), m_port(port)
	{
	}

	void Run(int _i)
	{
		SOCKET sock = WSASocket(AF_INET, SOCK_STREAM, 0, nullptr, 0, WSA_FLAG_OVERLAPPED);
		if (sock == INVALID_SOCKET) return;

		sockaddr_in local = {};
		local.sin_family = AF_INET;
		local.sin_addr.s_addr = INADDR_ANY;
		bind(sock, (sockaddr*)&local, sizeof(local));

		LPFN_CONNECTEX ConnectEx = GetConnectEx(sock);
		if (!ConnectEx) return;

		sockaddr_in server = {};
		server.sin_family = AF_INET;
		inet_pton(AF_INET, m_ip, &server.sin_addr);
		server.sin_port = htons(m_port);

		HANDLE iocp = CreateIoCompletionPort((HANDLE)sock, NULL, 0, 0);

		IOData* io = new IOData{};
		io->type = IOData::IOType::Connect;

		DWORD sent = 0;
		BOOL ret = ConnectEx(sock, (sockaddr*)&server, sizeof(server),
			nullptr, 0, &sent, io);

		if (!ret && WSAGetLastError() != WSA_IO_PENDING)
		{
			std::cerr << "ConnectEx error\n";
			delete io;
			closesocket(sock);
			return;
		}

		OVERLAPPED* ov = nullptr;
		ULONG_PTR key = 0;
		DWORD transferred = 0;
		size_t num = 0;
		while (true)
		{
			BOOL ok = GetQueuedCompletionStatus(iocp, &transferred, &key, &ov, INFINITE);
			if (!ok || !ov) break;

			IOData* data = reinterpret_cast<IOData*>(ov);

			if (data->type == IOData::IOType::Connect)
			{
				setsockopt(sock, SOL_SOCKET, SO_UPDATE_CONNECT_CONTEXT, nullptr, 0);
				std::cout << "[Connected]\n";

				memset(data->buffer, 0, sizeof(data->buffer));
				std::string msg = std::format("Hello from client {0}, {1}", _i, num++);
				strcpy_s(data->buffer, msg.c_str());
				data->wsaBuf.buf = data->buffer;
				data->wsaBuf.len = strlen(data->buffer);
				data->type = IOData::IOType::Send;

				WSASend(sock, &data->wsaBuf, 1, nullptr, 0, data, nullptr);
			}
			else if (data->type == IOData::IOType::Send)
			{
				std::cout << "[Sent] Waiting for echo...\n";
				memset(data->buffer, 0, sizeof(data->buffer));
				data->wsaBuf.buf = data->buffer;
				data->wsaBuf.len = sizeof(data->buffer);
				data->type = IOData::IOType::Recv;
				DWORD flags = 0;
				WSARecv(sock, &data->wsaBuf, 1, nullptr, &flags, data, nullptr);
			}
			else if (data->type == IOData::IOType::Recv)
			{
				std::cout << "[Recv] " << data->buffer << "\n";
				
				memset(data->buffer, 0, sizeof(data->buffer));
				std::string msg = std::format("Hello from client {0}, {1}", _i, num++);
				strcpy_s(data->buffer, msg.c_str());
				data->wsaBuf.buf = data->buffer;
				data->wsaBuf.len = strlen(data->buffer);
				data->type = IOData::IOType::Send;

				WSASend(sock, &data->wsaBuf, 1, nullptr, 0, data, nullptr);

				break;
			}
		}

		closesocket(sock);
		CloseHandle(iocp);
	}

private:
	const char* m_ip;
	int m_port;
};


int main()
{
	WSAData wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	constexpr int CLIENT_COUNT = 10;
	std::vector<std::jthread> threads;

	for (int i = 0; i < CLIENT_COUNT; ++i)
	{
		threads.emplace_back([&i] {
			ClientWorker client("127.0.0.1", 8888);
			client.Run(i);
			});
		std::this_thread::sleep_for(std::chrono::milliseconds(10)); // 서버 부담 줄이기
	}

	getchar();
	WSACleanup();
	return 0;
}
