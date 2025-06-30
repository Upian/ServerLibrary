#include "Server.h"
#include <iostream>

using namespace std;
int main(void)
{
	cout << "run" << endl;
//	auto server = TestServer::CreateSingleton();
	TestIOCPServer server;
	server.GetNetwork()->Initialize(1);
	server.GetNetwork()->Run(8888, 1);

	getchar();
}