#ifndef LBB_CONCURRENCY_POSIX_MUTEX_H_
#define LBB_CONCURRENCY_POSIX_MUTEX_H_

#include <pthread.h>
#include <errno.h>
#include <cstring>

#include <lbb/utility.h>
#include <lbb/concurrency/system_error.h>

namespace lbb {
namespace concurrency {
namespace posix {  

/**
 * Not reentrant simple mutex wrapper ...
 */
class mutex : not_copyable {

	typedef lbb::concurrency::system_error except_t;


	static void report_error(std::string msg) { 
		throw except_t(errno, msg + " : " + strerror(errno));
	}

public:
	typedef pthread_mutex_t* native_handle_type;


	/**
	 * Initialization of the mutex
	 */
	mutex() {
		if(pthread_mutex_init(&_mutex, NULL) != 0) { 
			report_error("mutex initialization error");
		}
	}

	/**
	 * Release of the mutex
	 */
	~mutex() {
		pthread_mutex_destroy(&_mutex);
	}

	/**
	 * Lock the mutex
	 */
	void lock() {
		if(pthread_mutex_lock(&_mutex) != 0) { 
			report_error("mutex lock error");
		}
	}

	/**
	 * Unlock the mutex
	 */
	void unlock() {
		if(pthread_mutex_unlock(&_mutex) != 0) { 
			report_error("mutex unlock error");
		}
	}

	/**
	 * Try to lock a mutex and return true if the operation succeed and false otherwise
	 */
	bool try_lock() {
		return !pthread_mutex_trylock(&_mutex);
	}

	/**
	 * Returns the underlying implementation-defined native handle object.
	 */
	native_handle_type native_handle() {
		return &_mutex;
	}

private:
	pthread_mutex_t _mutex;											//implementation detail ...
};


}  // posix
}  // namespace concurrency
}  // namespace lbb




#endif /* LBB_CONCURRENCY_MUTEX_H_ */
