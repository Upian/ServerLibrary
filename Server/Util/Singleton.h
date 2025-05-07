#pragma once
/*
*	NOTE
*	Singleton<class name>
*	DECLARE_SINGLETON(class name)
*	DECLARE_SINGLETON
*	CreateSingleton()		singleton
*	GetSingleton()			singleton
*	DistorySingleton()		singleton
*/
#include <mutex>

template<typename T_Class>
class Singleton
{
public:
	typedef T_Class SingletonClass;

	static SingletonClass* CreateSingleton();
	template <typename ...T_Args> static SingletonClass* CreateSingleton(const T_Args& ...args);
	static void DestroySingleton();
	static SingletonClass* GetSingleton();

protected:
	Singleton() {}
	virtual ~Singleton() {}

private:
	static SingletonClass* m_instance;
	static std::once_flag m_initFlag;
};

/*
*	Initialize
*/
template <typename T_Class>
typename Singleton<T_Class>::SingletonClass* Singleton<T_Class>::m_instance = nullptr;

/*
*	Create Singleton
*/
template <typename T_Class>
typename Singleton<T_Class>::SingletonClass* Singleton<T_Class>::CreateSingleton()
{
	std::call_once(m_initFlag, []() {
		if (nullptr == m_instance)
			m_instance = new SingletonClass();
		});

	return m_instance;
}
template <typename T_Class>
template <typename ...T_Args>
typename Singleton<T_Class>::SingletonClass* Singleton<T_Class>::CreateSingleton(const T_Args& ...args)
{
	std::call_once(m_initFlag, []() {
		if (nullptr == m_instance)
			m_instance = new SingletonClass(args...);
		});

	return m_instance;
}
/*
*	Get Singleton
*/
template <typename T_Class>
typename Singleton<T_Class>::SingletonClass* Singleton<T_Class>::GetSingleton()
{
	return m_instance;
}

/*
*	Destory Singleton
*/
template<typename T_Class>
void Singleton<T_Class>::DestroySingleton()
{
	delete m_instance;
	m_instance = nullptr;
}
//#Singleton End


/*
*   DECLARE_SINGLETON
*   Make class to singlton
*   must define a constructor and destroyer
*/
#ifndef DECLARE_SINGLETON
#define DECLARE_SINGLETON( ClassName ) \
		friend class Singleton< ClassName >; ClassName(); ~ClassName(); \
		ClassName(const ClassName&) = delete; \
		ClassName& operator=(const ClassName&) = delete;
#endif // DECLARE_SINGLETON