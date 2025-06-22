#pragma once
#include <memory>
#include <mutex>
template<typename T_Type>
class ObjectPool
{
public:
	ObjectPool();
	virtual ~ObjectPool();

	void Initialize(size_t _size);
	template<typename ...Args>
	void Initialize(size_t _size, Args&&... _args);
	void Clear();

	T_Type* Alloc();
	template<typename ...Args>
	T_Type* Alloc(Args&&... _args);

	std::shared_ptr<T_Type> AllocShared();
	template<typename ...Args>
	std::shared_ptr<T_Type> AllocShared(Args&&... _args);

	void Release(T_Type* _obj);
protected:
	std::atomic<T_Type*> m_objects;
	//	std::atomic <size_t> m_objectsCount = 0;
	std::mutex m_mutex;
};

template<typename T_Type>
inline ObjectPool<T_Type>::ObjectPool() {}

template<typename T_Type>
inline ObjectPool<T_Type>::~ObjectPool() {}

template<typename T_Type>
inline void ObjectPool<T_Type>::Initialize(size_t _size)
{
	std::lock_guard<std::mutex> lock(m_mutex);
	for (int i = 0; i < _size; ++i)
	{
		T_Type* temp = new T_Type();
		*((T_Type**)temp) = m_objects;
		m_objects = temp;
	}
	//	m_objectsCount += _size;
}

template<typename T_Type>
template<typename ...Args>
inline void ObjectPool<T_Type>::Initialize(size_t _size, Args&& ..._args)
{
	std::lock_guard<std::mutex> lock(m_mutex);
	for (int i = 0; i < _size; ++i)
	{
		T_Type* temp = new T_Type(std::forward<Args>(_args)...);
		*((T_Type**)temp) = m_objects;
		m_objects = temp;
	}
	//	m_objectsCount += _size;
}

template<typename T_Type>
inline void ObjectPool<T_Type>::Clear()
{
	std::lock_guard<std::mutex> lock(m_mutex);
	
	
	while (nullptr != m_objects)
	{
		T_Type* object = m_objects;
		m_objects = *((T_Type**)m_objects.load()); //다음 메모리 연결
		delete object;
	}
}

template<typename T_Type>
inline T_Type* ObjectPool<T_Type>::Alloc()
{
	T_Type* object = m_objects.load(std::memory_order_acquire);
	while (nullptr != object &&
		false == m_objects.compare_exchange_weak(object, *(T_Type**)object, std::memory_order_acq_rel, std::memory_order_acquire))
	{
		//실패하면 object는 m_objects로 변경
	}

	//	T_Type* object = m_objects;
	//	m_objects = *((T_Type**)m_objects); //다음 메모리 연결

	//	if (0 < m_objectsCount)
	//		--m_objectsCount;

	if (nullptr == object)
		return new T_Type();
	return object;
}

template<typename T_Type>
template<typename ...Args>
inline T_Type* ObjectPool<T_Type>::Alloc(Args&&... _args)
{
	T_Type* object = this->Alloc();
	return new (object) T_Type(std::forward<Args>(_args)...);
}

template<typename T_Type>
inline std::shared_ptr<T_Type> ObjectPool<T_Type>::AllocShared()
{
	T_Type* object = this->Alloc();
	return std::shared_ptr<T_Type>(object, [this](T_Type* _obj) {this->Release(_obj); });
}

template<typename T_Type>
template<typename ...Args>
inline std::shared_ptr<T_Type> ObjectPool<T_Type>::AllocShared(Args && ..._args)
{
	T_Type* object = this->Alloc(std::forward<Args>(_args)...);
	return std::shared_ptr<T_Type>(object, [this](T_Type* _obj) {this->Release(_obj); });
}

template<typename T_Type>
inline void ObjectPool<T_Type>::Release(T_Type* _obj)
{
	_obj->~T_Type();

	T_Type* headObject = m_objects.load(std::memory_order_acquire);
	do
	{
		*((T_Type**)_obj) = headObject;
	} while (false == m_objects.compare_exchange_weak(headObject, (T_Type*)_obj, std::memory_order_release, std::memory_order_acquire));

	//	*((T_Type**)_obj) = m_objects;
	//	m_objects = (T_Type*)_obj;

	//	++m_objectsCount;

	return;
}