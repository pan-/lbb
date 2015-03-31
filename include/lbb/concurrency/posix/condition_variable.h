#ifndef LBB_CONCURRENCY_POSIX_CONDITION_VARIABLE_H_
#define LBB_CONCURRENCY_POSIX_CONDITION_VARIABLE_H_

#include <pthread.h>

#include <lbb/concurrency/system_error.h>
#include <lbb/concurrency/mutex.h>
#include <lbb/concurrency/unique_lock.h>

namespace lbb {
namespace concurrency {
namespace posix {  

struct condition_variable : not_copyable {
	typedef pthread_cond_t* narive_handle_type;

	condition_variable() {
		if(pthread_cond_init(&_condition, NULL) != 0) { 
			throw system_error(42, "cannot construct condition variable");
		}
	}

	~condition_variable() {
		pthread_cond_destroy(&_condition);
	}

	/**
	 * If any threads are waiting on *this, calling notify_one unblocks one of the waiting threads.
	 */
	void notify_one() {
		pthread_cond_signal(&_condition);
	}

	/**
	 * Unblocks all threads currently waiting for *this
	 */
	void notify_all() {
		pthread_cond_broadcast(&_condition);
	}

	/**
	 * wait causes the current thread to block until the condition variable is notified or a
	 * spurious wakeup occurs, optionally looping until some predicate is satisfied.
	 *
	 * 1) Atomically releases lock, blocks the current executing thread, and adds it to the list
	 * of threads waiting on *this. The thread will be unblocked when notify_all() or notify_one()
	 * is executed. It may also be unblocked spuriously. When unblocked, regardless of the reason,
	 * lock is reacquired and wait exits.
	 */
	void wait(unique_lock<mutex>& lock) {
		pthread_cond_wait(&_condition, lock.mutex()->native_handle());
	}


	narive_handle_type native_handle() {
		return &_condition;
	}

private:
	pthread_cond_t _condition;
};



}
}
}

#endif /* LBB_CONCURRENCY_POSIX_CONDITION_VARIABLE_H_ */