#include "Server.h"
#include <iostream>

using namespace std;
int main(void)
{
	cout << "run" << endl;
//	auto server = TestServer::CreateSingleton();
	TestServer server;
	server.Initialize(1, 8888, 1);

	getchar();
}