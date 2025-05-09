#pragma once
//#include "IOCPPacketBuf.h"
#include  <type_traits>
#include "Util/ThreadLocalObjectPool.h"

namespace IOCP
{
	class PacketBuf;

	template<typename T>
	concept DerivedFromPacketBuf = std::is_base_of_v<PacketBuf, T>;

	template<DerivedFromPacketBuf T_Packet>
	class PacketPool
	{
	public:
		PacketPool() = default;
		virtual ~PacketPool();

		void Initialize(int _poolSize, int _bufSize);

		T_Packet* Alloc();
		std::shared_ptr<T_Packet> AllocShared();
		
		void Release(T_Packet* _packet);
	private:
		T_Packet* m_objects = nullptr;
		size_t m_objectsCount = 0;
	};

	template<DerivedFromPacketBuf T_Packet>
	inline PacketPool<T_Packet>::~PacketPool()
	{
		while (nullptr != m_objects)
		{
			T_Packet* next = *((T_Packet**)m_objects);
			delete m_objects;
			m_objects = next;
		}
	}

	template<DerivedFromPacketBuf T_Packet>
	inline void PacketPool<T_Packet>::Initialize(int _poolSize, int _bufSize)
	{
		for (int i = 0; i < _poolSize; ++i)
		{
			T_Packet* temp = new T_Packet();
			temp->InitBufSize(_bufSize);
			*((T_Packet**)temp) = m_objects;
			m_objects = temp;
		}
		m_objectsCount += _poolSize;
	}
	template<DerivedFromPacketBuf T_Packet>
	inline T_Packet* PacketPool<T_Packet>::Alloc()
	{
		if (nullptr == m_objects)
			return nullptr;

		T_Packet* object = m_objects;
		m_objects = *((T_Packet**)m_objects); //다음 메모리 연결

		if (0 < m_objectsCount)
			--m_objectsCount;
		return object;
	}

	template<DerivedFromPacketBuf T_Packet>
	inline std::shared_ptr<T_Packet> PacketPool<T_Packet>::AllocShared()
	{
		if (nullptr == m_objects)
			return nullptr;

		T_Packet* object = m_objects;
		m_objects = *((T_Packet**)m_objects); //다음 메모리 연결

		if (0 < m_objectsCount)
			--m_objectsCount;

		return std::shared_ptr<T_Packet>(object, [this](T_Packet* _obj) {this->Release(_obj); });
	}

	template<DerivedFromPacketBuf T_Packet>
	inline void PacketPool<T_Packet>::Release(T_Packet* _packet)
	{
//		_packet->~T_Packet();
		_packet->BufReset();

		*((T_Packet**)_packet) = m_objects;
		m_objects = (T_Packet*)_packet;
		++m_objectsCount;

		return;
	}
}