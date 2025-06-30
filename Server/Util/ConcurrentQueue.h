#pragma once

#include <atomic>
#include <thread>
template<typename T_Type, size_t maxSize = 1024>
class ConcurrentQueue
{
private:
	struct Slot
	{
		Slot() = default;
		Slot(const T_Type& _value) : Value(_value) {}
		Slot(const T_Type& _value, size_t _seq) : Value(_value), Seq(_seq) {}

		T_Type Value;
		std::atomic<size_t> Seq = 0; //��� ����
	};
public:
	ConcurrentQueue();

	//	void AsyncPush(const T_Type& _value);
	void Push(const T_Type& _value); //�����Ҷ����� ���
	bool TryPush(const T_Type& _value);
	T_Type Pop(); //�����Ҷ����� ���
	T_Type TryPop();

private:
	std::atomic<size_t> m_pushCursor = 0;
	std::atomic<size_t> m_popCursor = 0;

	Slot m_typeArray[maxSize];
};

template<typename T_Type, size_t maxSize>
inline ConcurrentQueue<T_Type, maxSize>::ConcurrentQueue()
{
	for (size_t idx = 0; idx < maxSize; ++idx)
	{
		m_typeArray[idx].Seq.store(idx, std::memory_order_relaxed);
	}
}

//Slot.Seq�� pushCursor �� ��쿡�� Push
//Push �����ϸ� Seq = idx + 1
template<typename T_Type, size_t maxSize>
inline void ConcurrentQueue<T_Type, maxSize>::Push(const T_Type& _value)
{
	size_t pushCursor = m_pushCursor.fetch_add(1, std::memory_order_acquire);
	size_t expectedSeq = pushCursor;

	while (true)
	{
		Slot& slot = m_typeArray[pushCursor % maxSize];

		//*
		if (expectedSeq == slot.Seq.load(std::memory_order_acquire))
		{
			slot.Value = _value;
			slot.Seq.store(pushCursor + 1, std::memory_order_release);
			break;
		}
		/*/
		if (true == slot.Seq.compare_exchange_weak(expectedSeq, pushCursor + 1, std::memory_order_release, std::memory_order_relaxed))
		{
			slot.Value = _value;
			break;
		}
		//*/

		expectedSeq = pushCursor;
		//�ٸ� �����忡�� �����ؼ� ���� pushCursor�� ��������
		std::this_thread::yield();
	}
}

//Slot.Seq�� pushCursor �� ��쿡�� Push
//Push �����ϸ� Seq = idx + 1
template<typename T_Type, size_t maxSize>
inline bool ConcurrentQueue<T_Type, maxSize>::TryPush(const T_Type& _value)
{
	size_t pushCursor = m_pushCursor.fetch_add(1, std::memory_order_acquire);
	Slot& slot = m_typeArray[pushCursor % maxSize];
	size_t expectedSeq = pushCursor;

	if (expectedSeq == slot.Seq.load(std::memory_order_acquire))
	{
		slot.Value = _value;
		slot.Seq.store(pushCursor + 1, std::memory_order_release);
		return true;
	}
	return false;
}

//Slot.Seq�� popCursor + 1 �϶��� Pop
//Pop ���� �� popCursor = popCursor + maxSize
template<typename T_Type, size_t maxSize>
inline T_Type ConcurrentQueue<T_Type, maxSize>::Pop()
{
	size_t popCursor = m_popCursor.fetch_add(1, std::memory_order_acquire);
	size_t expectedSeq = popCursor + 1;

	while (true)
	{
		Slot& slot = m_typeArray[popCursor % maxSize];

		//*
		if (expectedSeq == slot.Seq.load(std::memory_order_acquire))
		{
			T_Type value = slot.Value;
			slot.Seq.store(popCursor + maxSize, std::memory_order_release);
			return value;
		}
		/*/
		if (true == slot.Seq.compare_exchange_weak(expectedSeq, popCursor + maxSize, std::memory_order_release, std::memory_order_relaxed))
		{
			return slot.Value;
		}
		//*/

		expectedSeq = popCursor + 1;

		//		printf("can not pop \t popCursor: %lld, Seq: %lld \n", popCursor, slot.Seq.load(std::memory_order_acquire));

		std::this_thread::yield();
	}

}

//Slot.Seq�� popCursor + 1 �϶��� Pop
//Pop ���� �� popCursor = popCursor + maxSize
template<typename T_Type, size_t maxSize>
inline T_Type ConcurrentQueue<T_Type, maxSize>::TryPop()
{
	size_t popCursor = m_popCursor.fetch_add(1, std::memory_order_acquire);
	size_t expectedSeq = popCursor + 1;

	Slot& slot = m_typeArray[popCursor % maxSize];

	if (expectedSeq == slot.Seq.load(std::memory_order_acquire))
	{
		T_Type value = slot.Value;
		slot.Seq.store(popCursor + maxSize, std::memory_order_release);
		return value;
	}
	return T_Type();
}
