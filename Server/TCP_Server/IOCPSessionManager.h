#pragma once
#include "Util/ObjectPool.h"
#include "IOCPSession.h"
#include "Util/Singleton.h"
#include <future>
#include <unordered_map>
#include <coroutine>
namespace IOCP
{	
	template<typename T_Type>
	struct TaskSession
	{
		struct promise_type
		{
			T_Type value;
//			std::conditional_t<std::is_void_v<T_Type>, void, T_Type> value; //T_Type이 void인지 아닌지

			TaskSession get_return_object()
			{
				return TaskSession{ std::coroutine_handle<promise_type>::from_promise(*this) };
			}
			std::suspend_never initial_suspend() noexcept { return {}; }
			std::suspend_never final_suspend() noexcept { return {}; }
			
			bool await_ready() requires (false == std::is_void_v<T_Type, bool>) { return true; }
			bool await_ready() requires (true == std::is_same_v<T_Type, bool>) { return true; }

			bool await_resume() requires (true == std::is_same_v<T_Type, bool>) { }
			
			void return_value(T_Type _v) requires (false == std::is_void_v<T_Type>) { value = std::move(_v); }
//			void return_void() {}
			void unhandled_exception() { std::terminate(); }
		};

		std::coroutine_handle<promise_type> handle;

		TaskSession(std::coroutine_handle<promise_type> _h) : handle(_h) {}
		~TaskSession() { if (handle) handle.destroy(); }

		T_Type result() { return handle.promise().value; }
	};

	//서버에 연결된 객체 Session, 
	//서버가 연결한 객체 Proxy 관리
	class SessionManager : public Singleton<SessionManager>
	{
		DECLARE_SINGLETON(SessionManager)
	public:
		std::shared_ptr<Session> AllocSession();
		TaskSession<std::shared_ptr<Session> > AllocSessionAsync();
		void AcceptComplete(std::shared_ptr<Session> _session);

	private:
		SessionManager(int _poolSize);
		TaskSession<bool> AsyncAddWaitAccept(std::shared_ptr<Session> _session);

		ObjectPool<Session> m_poolSession;
		std::mutex m_sessionMutex;
		std::unordered_map<Session*, std::shared_ptr<Session> > m_waitAcceptMap;
//		ObjectPool<Proxy> m_poolProxy;

	};
}