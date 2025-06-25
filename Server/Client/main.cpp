#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <format>

#pragma comment(lib, "ws2_32.lib")

void ClientThread(int _index, std::string _ip, short _port)
{
	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET)
	{
		std::cerr << "[" << _index << "] Socket creation failed.\n";
		return;
	}

	sockaddr_in serverAddr{};
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(_port);
	serverAddr.sin_addr.s_addr = inet_addr(_ip.c_str());

	if (connect(sock, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
	{
		std::cerr << "[" << _index << "] Connection failed.\n";
		closesocket(sock);
		return;
	}

	std::cout << "[" << _index << "] Connected to server.\n";
/*
	// 메시지 보내기
	std::string msg = "Hello from client " + std::to_string(_index);
	send(sock, msg.c_str(), (int)msg.size(), 0);

	// 응답 받기 (선택)
	char buffer[512]{};
	int recvLen = recv(sock, buffer, sizeof(buffer) - 1, 0);
	if (recvLen > 0)
	{
		buffer[recvLen] = '\0';
		std::cout << "[" << _index << "] Received: " << buffer << "\n";
	}
*/
	std::this_thread::sleep_for(std::chrono::milliseconds(100)); // 테스트용 대기
	closesocket(sock);
}

int main()
{
	WSADATA wsaData{};
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		std::cerr << "WSAStartup failed.\n";
		return 1;
	}

	std::string ip;
	short port = 0;
	int clientCount = 0;

	std::cout << "input IP: ";
	std::cin >> ip;
	std::cout << "input port: ";
	std::cin >> port;
	std::cout << "input client count: ";
	std::cin >> clientCount;
	
	std::string str = std::format("IP: {0}, port: {1}, ClientCount: {2}", ip, port, clientCount);
	std::cout << str << std::endl;

	std::vector<std::jthread> clientThreads;
	for (int i = 0; i < clientCount; ++i)
	{
		clientThreads.emplace_back(ClientThread, i, ip, port);
		std::this_thread::sleep_for(std::chrono::milliseconds(10)); // 약간의 간격
	}

	WSACleanup();
	getchar();
	return 0;
}
