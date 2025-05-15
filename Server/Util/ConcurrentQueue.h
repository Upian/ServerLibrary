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
		Slot(const T_Type& _value, bool _isEmpty) : Value(_value), IsEmpty(_isEmpty) {}

		T_Type Value;
		std::atomic_bool IsEmpty = true; //true�� Push ����
	};
public:
	ConcurrentQueue();

	//	void AsyncPush(const T_Type& _value);
	void TryPush(const T_Type& _value); //�����Ҷ����� ���
	bool Push(const T_Type& _value);
	T_Type TryPop(); //�����Ҷ����� ���
	T_Type Pop();



private:
	void Test(bool _isPush, T_Type _value);

	std::atomic<size_t> m_pushCursor = 0;
	std::atomic<size_t> m_popCursor = 0;

	Slot m_typeArray[maxSize] = { Slot(), };
};

template<typename T_Type, size_t maxSize>
inline ConcurrentQueue<T_Type, maxSize>::ConcurrentQueue()
{
}

template<typename T_Type, size_t maxSize>
inline void ConcurrentQueue<T_Type, maxSize>::TryPush(const T_Type& _value)
{
	size_t pushCursor = 0;
	bool expected = true;
	//push ��ġ�� m_popCursor�� ������ Pop �Ҷ����� ���
//	while (false == m_typeArray[m_pushCursor.load(std::memory_order_relaxed)].IsEmpty.compare_exchange_weak(true, false))
	//*
	while (true)
	{
		pushCursor = m_pushCursor.load(std::memory_order_relaxed);
		Slot& slot = m_typeArray[pushCursor];
//		std::cout << "try push: " << _value << " slot(" << pushCursor << ") is empty: " << slot.IsEmpty << " expected: " << expected << std::endl;
		//IsEmpty�� true�� false�� �ٲٰ�
		if (true == slot.IsEmpty.compare_exchange_weak(expected, false, std::memory_order_release, std::memory_order_relaxed))
		{
//			std::cout << "push: " << _value << std::endl;
			slot.Value = _value;
			m_pushCursor.compare_exchange_strong(pushCursor, (pushCursor + 1) % maxSize, std::memory_order_release, std::memory_order_relaxed);
//			Test(true, pushCursor);
			break;
		}
		expected = true;
		//�ٸ� �����忡�� �����ؼ� ���� pushCursor�� ��������
		std::cout << "can not push: " << _value << std::endl;
//		Test(true, pushCursor);
		std::this_thread::yield();
	}
	/*/
	//������ �ߺ��Ǿ ������ �ϳ��� �÷��� �ϴµ�
	while (true)
	{
		pushCursor = m_pushCursor.fetch_add(1, std::memory_order_relaxed) % maxSize;
		Slot& slot = m_typeArray[pushCursor];

		if (slot.IsEmpty.compare_exchange_weak(expected, false, std::memory_order_release, std::memory_order_relaxed))
		{
			slot.Value = _value;
			return;
		}
		std::this_thread::yield();
	}
	//*/

}

template<typename T_Type, size_t maxSize>
inline bool ConcurrentQueue<T_Type, maxSize>::Push(const T_Type& _value)
{
	size_t pushCursor = m_pushCursor.load(std::memory_order_relaxed);
	Slot& slot = m_typeArray[pushCursor];
	bool expected = true;

	//IsEmpty�� true�� false�� �ٲٰ�
	if (true == slot.IsEmpty.compare_exchange_strong(expected, false, std::memory_order_release, std::memory_order_relaxed))
	{
		slot.Value = _value;
		m_pushCursor.compare_exchange_strong(pushCursor, (pushCursor + 1) % maxSize, std::memory_order_release, std::memory_order_relaxed);
		return true;
	}
	return false;
}

template<typename T_Type, size_t maxSize>
inline T_Type ConcurrentQueue<T_Type, maxSize>::TryPop()
{
	size_t popCursor = 0;
	bool expected = false;

//	std::cout << "try pop: " << popCursor << std::endl;
	while (true)
	{
		popCursor = m_popCursor.load(std::memory_order_relaxed);
		Slot& slot = m_typeArray[popCursor];

		//IsEmpty�� true�� false�� �ٲٰ�
		if (true == slot.IsEmpty.compare_exchange_weak(expected, true, std::memory_order_release, std::memory_order_relaxed))
		{
//			std::cout << "pop: " << slot.Value << std::endl;
			m_popCursor.compare_exchange_strong(popCursor, (popCursor + 1) % maxSize, std::memory_order_release, std::memory_order_relaxed);
//			Test(false, popCursor);
			return slot.Value;
		}
		expected = false;
//		std::cout << "can not pop: " << std::endl;
//		Test(false, popCursor);
		std::this_thread::yield();
	}

}

template<typename T_Type, size_t maxSize>
inline T_Type ConcurrentQueue<T_Type, maxSize>::Pop()
{
	size_t popCursor = 0;
	bool expected = false;

	popCursor = m_popCursor.load(std::memory_order_relaxed);
	Slot& slot = m_typeArray[popCursor];

	//IsEmpty�� true�� false�� �ٲٰ�
	if (true == slot.IsEmpty.compare_exchange_weak(expected, true, std::memory_order_release, std::memory_order_relaxed))
	{
		m_popCursor.compare_exchange_strong(popCursor, (popCursor + 1) % maxSize, std::memory_order_release, std::memory_order_relaxed);
		return slot.Value;
	}
	return T_Type();
}

template<typename T_Type, size_t maxSize>
inline void ConcurrentQueue<T_Type, maxSize>::Test(bool _isPush, T_Type _value)
{
	std::cout << (_isPush ? "PUSH - " : "POP - ") << "array(" << _value << "): ";
	for (const auto& iter : m_typeArray)
	{
		std::cout << "(" << iter.Value << ", " << iter.IsEmpty << ") - ";
	}

	std::cout << " END " << std::endl;
}
