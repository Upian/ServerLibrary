#pragma once
#include <winsock2.h>
#include <windows.h>
#include <type_traits>
#include "WinSock.h"
#include "Util/Singleton.h"
#include "Util/ConcurrentQueue.h"
#include "IOCPHandler.h"
#include "IOCPSocket.h"
#include "IOCPWorkThread.h"
#include "IOCPPacketBuf.h"
#include "IOCPConcepts.h"


/*
* IOCPNetwork
* IOCP를 사용한 서버
* 멤버로 선언하여 사용
* Acceptor, ObjectManager, WorkThread, MessageQueue
* Acceptor는 클라이언트의 접속을 받아들이고, 클라이언트를 연결
* WorkManager는 연결된 클라이언트를 처리하기 위한 Worker를 관리
* IOCPHandler는 IOCP를 사용하기 위한 핸들러
*/

namespace IOCP
{
	class Acceptor;
	class ObjectManager;
	class MessageQueue;
	class Network : public Singleton<Network>
	{
		DECLARE_SINGLETON(Network);
	public:
		void Initialize(int _threadCnt);
		IOCP::WorkThread* GetWorkThread() { return m_workThread; }
		void Run(unsigned short _port, int _maxAcceptorCnt = 1);

		IOCP::ObjectManager* GetObjectManager() { return m_objectManager; }
		IOCP::Acceptor* GetAcceptor() { return m_acceptor; }
		IOCP::MessageQueue* GetMessageQueue() { return m_messageQueue; }

//		template<DerivedFromPacketBuf T_Packet>
		template<typename T_Packet>
			requires DerivedFromPacketBuf<T_Packet>
		std::shared_ptr<T_Packet> AllocPacket();

//		virtual void HandleThread() = 0; //로직 처리
//		virtual std::shared_ptr<IOCP::PacketBuf> AllocPacketBuf() = 0; //IOCP::PacketPool로 할당하면 됨
	private:
		IOCP::ObjectManager* m_objectManager = nullptr;
		IOCP::Acceptor* m_acceptor = nullptr;
		IOCP::WorkThread* m_workThread = nullptr;
		IOCP::MessageQueue* m_messageQueue = nullptr;

		IOCP::Handler m_IOCPHandler;
//		IOCP::Socket m_socket;

		

		WinSock m_winSock;
	};
}