#ifndef LBB_CONCURRENCY_LOCK_GUARD_H_
#define LBB_CONCURRENCY_LOCK_GUARD_H_

#include <lbb/utility.h>

namespace lbb {
namespace concurrency { 

/**
 * RAII class for mutex locks in a local scope :
 * \code
 * if(cond() == true) {
 * 	MutexLocker lock(a_mutex);			//lock the mutex for this scope
 * 	.
 * 	.
 * 	.
 * }		//end of scope, the destructor of lock is called and the a_mutex is released
 * \endcode
 */
template<typename T>
struct lock_guard : not_copyable, scoped {
	typedef T mutex_type;

	explicit lock_guard(mutex_type& mutex) : _mutex(mutex) {
		_mutex.lock();
	}

	/**
	 * Release the mutex
	 */
	~lock_guard() {
		_mutex.unlock();
	}

private:
	mutex_type& _mutex;
};



}  // namespace concurrency
}  // namespace lbb





#endif /* LBB_CONCURRENCY_LOCK_GUARD_H_ */
