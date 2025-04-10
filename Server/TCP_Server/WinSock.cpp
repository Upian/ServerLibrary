#include "WinSock.h"
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

WinSock::WinSock()
{
	WSADATA wsaData;
	if (0 != WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		// error log
	}
}

WinSock::~WinSock()
{
	WSACleanup();
}
