#ifndef LBB_CONCURRENCY_POSIX_THREAD_H_
#define LBB_CONCURRENCY_POSIX_THREAD_H_

#include <pthread.h>

#include <exception>
#include <lbb/concurrency/system_error.h>
#include <lbb/functional.h>
#include <lbb/smartptr.h>

// #include <lbb/concurrency/system_error.h>

namespace lbb {
namespace concurrency {
namespace posix {  


/*
 * The class thread represents a single thread of execution. 
 * Threads allow multiple pieces of code to run asynchronously and simultaneously.
 */
class thread : not_copyable, public movable<thread> {
public:

	typedef pthread_t native_handle_type;

	/*
	 * The class thread::id is a lightweight, trivially copyable class that serves as a unique identifier of thread objects.
	 * Instances of this class may also hold the special distinct value that does not represent any thread. 
	 * Once a thread has finished, the value of std::thread::id may be reused by another thread.
	 * This class is designed for use as key in associative containers, both ordered and unordered.
	 */
	class id { 
		native_handle_type _handle;

		friend class thread;
		inline id(native_handle_type handle) : _handle(handle) { }

	public:
		/*
		 * constructs an id that does not represent a thread
		 */
		id() : _handle() { };

		friend inline bool operator==(const id& l, const id& r) { 	return pthread_equal(l._handle, r._handle); }
		friend inline bool operator!=(const id& l, const id& r) { return !(l == r); }
		friend inline bool operator<(const id& l, const id& r) { return (l._handle < r._handle); }		
		friend inline bool operator<=(const id& l, const id& r) { return ((l < r) || (l == r)); }
		friend inline bool operator>(const id& l, const id& r) { return (r < l); }; 
		friend inline bool operator>=(const id& l, const id& r) { return ((r < l) || (l == r)); }
	};



	LBB_TYPEDEF_MOVE_TYPES(thread);


	/*
	 * Creates new thread object which does not represent a thread.
	 */
	inline thread() : _handle() { }

	/*
	 * Constructs the thread object to represent the thread of execution that was 
	 * represented by other. After this call other no longer represents a thread of execution.
	 * @param other : another thread object to construct this thread object with
	 */
	inline thread(rvalue_reference other) : _handle(other._handle)  { 
		other._handle = native_handle_type();
	}

	/*
	 * Creates new thread object and associates it with a thread of execution. 
	 * First the constructor copies all arguments args... to thread-accessible storage.
	 * The code that will be run in the new thread is defined as follows
	 * func(args...)
	 * @param func : the fuction to start in the thread
	 * @param args... : args applied to f
	 * @throw : system_error if the thread could not be started. 
	 * @note : The arguments to the thread function are copied by value. 
	 * If a reference argument needs to be passed to the thread function, it has to be wrapped (e.g. with ref or cref).
	 * If the function throws an exception, std::terminate is called. 
	 */
	template<typename F>
	explicit thread(F func) {
		start_thread(new function<void()>(func));
	}

	template<typename F, typename A1>
	explicit thread(F func, A1 arg1) {
		//TODO : test return
		start_thread(new function<void()>(bind(func, arg1)));
	}

	template<typename F, typename A1, typename A2>
	explicit thread(F func, A1 arg1, A2 arg2) {
		start_thread(new function<void()>(bind(func, arg1, arg2)));
	}

	template<typename F, typename A1, typename A2, typename A3>
	explicit thread(F func, A1 arg1, A2 arg2, A3 arg3) {
		start_thread(new function<void()>(bind(func, arg1, arg2, arg3)));
	}

	template<typename F, typename A1, typename A2, typename A3, typename A4>
	explicit thread(F func, A1 arg1, A2 arg2, A3 arg3, A4 arg4) {
		start_thread(new function<void()>(bind(func, arg1, arg2, arg3, arg4)));
	}

	template<typename F, typename A1, typename A2, typename A3, typename A4, typename A5>
	explicit thread(F func, A1 arg1, A2 arg2, A3 arg3, A4 arg4, A5 arg5) {
		start_thread(new function<void()>(bind(func, arg1, arg2, arg3, arg4, arg5)));
	}

	/*
	 * Destroys the thread object. 
	 * If *this still has an associated running thread (i.e. joinable() == true), std::terminate() is called.
	 */
	inline ~thread() { 
		if(joinable()) { 
			std::terminate();
		}
	}

	/*
	 * Assigns the state of other to *this using move semantics.
	 * If *this still has an associated running thread (i.e. joinable() == true), std::terminate() is called.
	 */
	inline thread& operator=(rvalue_reference other) { 
		if(joinable()) { 
			std::terminate();
		}
		_handle = other._handle;
		other._handle = native_handle_type();
		return *this;
	}

	/*
	 * Checks if the thread object identifies an active thread of execution. 
	 * Specifically, returns true if get_id() != thread::id(). 
	 * So a default constructed thread is not joinable.
	 * A thread that has finished executing code, but has not yet been joined 
	 * is still considered an active thread of execution and is therefore joinable.
	 * @return true if the thread object identifies an active thread of execution, false otherwise
	 */
	inline bool joinable() const { 
		return (get_id() != id()); 
	}

	/**
	 * Returns a value of thread::id identifying the thread associated with *this.
	 * If there is no thread associated, default constructed thread::id is returned.
	 */
	inline id get_id() const { 
		return id(_handle); 
	}

	/*
	 * Returns the implementation defined underlying thread handle.
	 */
	inline native_handle_type native_handle() { 
		return _handle; 
	}

	/*
	 * Returns number of concurrent threads supported by the implementation. The value should be considered only a hint.
	 * @return number of concurrent threads supported. If the value is not well defined or not computable, returns ​0​.
	 */
	static inline unsigned hardware_concurrency() { 
		//TODO : implement
		return 0;
	}


	/*
	 * Blocks the current thread until the thread identified by *this finishes its execution.
	 */
	inline void join() { 
		int error = pthread_join(_handle, 0);
		if(error != 0) { 
			switch(error) { 
				case EDEADLK: throw system_error(42, "thread join : deadlock detected");
				case EINVAL:  throw system_error(42, "thread join : thread is not thread joinable");
				default: 	  throw system_error(42, "thread join :thread is not valid");
			}
		}
		_handle = native_handle_type();
	}

	/*
	 * Separates the thread of execution from the thread object, 
	 * allowing execution to continue independently. 
	 * Any allocated resources will be freed once the thread exits.
	 * After calling detach *this no longer owns any thread.
	 */
	inline void detach() { 
		if(pthread_detach(_handle) != 0) { 
			throw system_error(42, "thread detach : not joinable thread");
		}
		_handle = native_handle_type();
	}

	/* 
	 * Exchanges the underlying handles of two thread objects.
	 */
	inline void swap(thread& other) { 
		native_handle_type tmp_handle = other._handle;
		other._handle = _handle;
		_handle = tmp_handle;
	}


private:
	pthread_t _handle;

	inline void start_thread(function<void()>* user_func) { 
		if(pthread_create(&_handle, NULL, thread_function, user_func) != 0) { 
			delete user_func;
			throw system_error(42, "cannot start thread, insufficient resources");
		}		
	}

	inline static void* thread_function(void* f) { 
		unique_ptr<function<void()> > func(static_cast<function<void()>*>(f));
		(*func)();
		return 0;
	}

};



}
}
}

#endif /* LBB_CONCURRENCY_POSIX_THREAD_H_ */