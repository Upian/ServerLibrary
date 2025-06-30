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
* IOCP�� ����� ����
* ����� �����Ͽ� ���
* Acceptor, ObjectManager, WorkThread, MessageQueue
* Acceptor�� Ŭ���̾�Ʈ�� ������ �޾Ƶ��̰�, Ŭ���̾�Ʈ�� ����
* WorkManager�� ����� Ŭ���̾�Ʈ�� ó���ϱ� ���� Worker�� ����
* IOCPHandler�� IOCP�� ����ϱ� ���� �ڵ鷯
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

//		virtual void HandleThread() = 0; //���� ó��
//		virtual std::shared_ptr<IOCP::PacketBuf> AllocPacketBuf() = 0; //IOCP::PacketPool�� �Ҵ��ϸ� ��
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