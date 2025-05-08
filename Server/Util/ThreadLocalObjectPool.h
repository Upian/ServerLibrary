#pragma once
#include <memory>

template<typename T_Type>
class ThreadLocalObjectPool
{
public:
	ThreadLocalObjectPool();
	virtual ~ThreadLocalObjectPool();

	void Initialize(size_t _size);
	template<typename ...Args>
	void Initialize(size_t _size, Args&&... _args);

	T_Type* Alloc();
	template<typename ...Args>
	T_Type* Alloc(Args&&... _args);

	std::shared_ptr<T_Type> AllocShared();
	template<typename ...Args>
	std::shared_ptr<T_Type> AllocShared(Args&&... _args);


	void Release(T_Type* _obj);
protected:
	static thread_local T_Type* m_objects;
	static thread_local size_t m_objectsCount = 0;
};

template<typename T_Type>
thread_local T_Type* ThreadLocalObjectPool<T_Type>::m_objects = nullptr;

template<typename T_Type>
thread_local size_t ThreadLocalObjectPool<T_Type>::m_objectsCount = 0;

template<typename T_Type>
inline ThreadLocalObjectPool<T_Type>::ThreadLocalObjectPool() {}

template<typename T_Type>
inline ThreadLocalObjectPool<T_Type>::~ThreadLocalObjectPool() {}

template<typename T_Type>
inline void ThreadLocalObjectPool<T_Type>::Initialize(size_t _size)
{
	for (int i = 0; i < _size; ++i)
	{
		T_Type* temp = new T_Type();
		*((T_Type**)temp) = m_objects;
		m_objects = temp;
	}
	m_objectsCount += _size;
}

template<typename T_Type>
template<typename ...Args>
inline void ThreadLocalObjectPool<T_Type>::Initialize(size_t _size, Args && ..._args)
{
	for (int i = 0; i < _size; ++i)
	{
		T_Type* temp = new T_Type(std::forward<Args>(_args)...);
		*((T_Type**)temp) = m_objects;
		m_objects = temp;
	}
	m_objectsCount += _size;
}

template<typename T_Type>
inline T_Type* ThreadLocalObjectPool<T_Type>::Alloc()
{
	if (nullptr == m_objects)
		return new T_Type();

	T_Type* object = m_objects;
	m_objects = *((T_Type**)m_objects); //다음 메모리 연결

	if (0 < m_objectsCount)
		--m_objectsCount;
	return object;
}

template<typename T_Type>
template<typename ...Args>
inline T_Type* ThreadLocalObjectPool<T_Type>::Alloc(Args&&... _args)
{
	if (nullptr == m_objects)
		return new T_Type(std::forward<Args>(_args)...);

	T_Type* object = new (m_objects) T_Type(std::forward<Args>(_args)...);
	m_objects = *((T_Type**)m_objects);

	if (0 < m_objectsCount)
		--m_objectsCount;
	return object;
}

template<typename T_Type>
inline std::shared_ptr<T_Type> ThreadLocalObjectPool<T_Type>::AllocShared()
{
	if (nullptr == m_objects)
		return std::shared_ptr<T_Type>(new T_Type(), [this](T_Type* _obj) {this->Release(_obj); });

	T_Type* object = m_objects;
	m_objects = *((T_Type**)m_objects); //다음 메모리 연결

	if (0 < m_objectsCount)
		--m_objectsCount;

	return std::shared_ptr<T_Type>(object, [this](T_Type* _obj) {this->Release(_obj); });
}

template<typename T_Type>
template<typename ...Args>
inline std::shared_ptr<T_Type> ThreadLocalObjectPool<T_Type>::AllocShared(Args && ..._args)
{
	if (nullptr == m_objects)
	{
		T_Type* object = new T_Type(std::forward<Args>(_args)...);
		return std::shared_ptr<T_Type>(object, [this](T_Type* _obj) {this->Release(_obj); });
	}

	T_Type* object = new (m_objects) T_Type(std::forward<Args>(_args)...);
	m_objects = *((T_Type**)m_objects);

	if (0 < m_objectsCount)
		--m_objectsCount;

	return std::shared_ptr<T_Type>(object, [this](T_Type* _obj) {this->Release(_obj); });
}

template<typename T_Type>
inline void ThreadLocalObjectPool<T_Type>::Release(T_Type* _obj)
{
	_obj->~T_Type();

	*((T_Type**)_obj) = m_objects;
	m_objects = (T_Type*)_obj;
	++m_objectsCount;

	return;
}