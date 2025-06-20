#pragma once
#include <memory>
#include <mutex>
template<typename T_Type, bool UseThread = false>
class ObjectPool
{
public:
	ObjectPool();
	virtual ~ObjectPool();

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
//	std::atomic<T_Type*> m_objects;
//	std::atomic <size_t> m_objectsCount = 0;
	T_Type* m_objects;
	size_t m_objectsCount = 0;

	std::mutex m_mutex; //UseThread가 True일 떄만 사용
};

template<typename T_Type, bool UseThread>
inline ObjectPool<T_Type, UseThread>::ObjectPool() {}

template<typename T_Type, bool UseThread>
inline ObjectPool<T_Type, UseThread>::~ObjectPool() {}

template<typename T_Type, bool UseThread>
inline void ObjectPool<T_Type, UseThread>::Initialize(size_t _size)
{
	for (int i = 0; i < _size; ++i)
	{
		T_Type* temp = new T_Type();
		*((T_Type**)temp) = m_objects;
		m_objects = temp;
	}
	m_objectsCount += _size;
}

template<typename T_Type, bool UseThread>
template<typename ...Args>
inline void ObjectPool<T_Type, UseThread>::Initialize(size_t _size, Args&& ..._args)
{
	for (int i = 0; i < _size; ++i)
	{
		T_Type* temp = new T_Type(std::forward<Args>(_args)...);
		*((T_Type**)temp) = m_objects;
		m_objects = temp;
	}
	m_objectsCount += _size;
}

template<typename T_Type, bool UseThread>
inline T_Type* ObjectPool<T_Type, UseThread>::Alloc()
{
	if constexpr (true == UseThread)
		std::lock_guard<std::mutex> lock(m_mutex);

	if (nullptr == m_objects)
		return new T_Type();

	T_Type* object = m_objects;
	m_objects = *((T_Type**)m_objects); //다음 메모리 연결

	if (0 < m_objectsCount)
		--m_objectsCount;
	return object;
}

template<typename T_Type, bool UseThread>
template<typename ...Args>
inline T_Type* ObjectPool<T_Type, UseThread>::Alloc(Args&&... _args)
{
	if constexpr (true == UseThread)
		std::lock_guard<std::mutex> lock(m_mutex);

	if (nullptr == m_objects)
		return new T_Type(std::forward<Args>(_args)...);

	T_Type* object = new (m_objects) T_Type(std::forward<Args>(_args)...);
	m_objects = *((T_Type**)m_objects);

	if (0 < m_objectsCount)
		--m_objectsCount;
	return object;
}

template<typename T_Type, bool UseThread>
inline std::shared_ptr<T_Type> ObjectPool<T_Type, UseThread>::AllocShared()
{
	if constexpr (true == UseThread)
		std::lock_guard<std::mutex> lock(m_mutex);

	if (nullptr == m_objects)
		return std::shared_ptr<T_Type>(new T_Type(), [this](T_Type* _obj) {this->Release(_obj); });

	T_Type* object = m_objects;
	m_objects = *((T_Type**)m_objects); //다음 메모리 연결

	if (0 < m_objectsCount)
		--m_objectsCount;

	return std::shared_ptr<T_Type>(object, [this](T_Type* _obj) {this->Release(_obj); });
}

template<typename T_Type, bool UseThread>
template<typename ...Args>
inline std::shared_ptr<T_Type> ObjectPool<T_Type, UseThread>::AllocShared(Args && ..._args)
{
	if constexpr (true == UseThread)
		std::lock_guard<std::mutex> lock(m_mutex);

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

template<typename T_Type, bool UseThread>
inline void ObjectPool<T_Type, UseThread>::Release(T_Type* _obj)
{
	if constexpr (true == UseThread)
		std::lock_guard<std::mutex> lock(m_mutex);

	_obj->~T_Type();

	*((T_Type**)_obj) = m_objects;
	m_objects = (T_Type*)_obj;
	++m_objectsCount;

	return;
}