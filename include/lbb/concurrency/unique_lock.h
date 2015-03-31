#ifndef LBB_CONCURRENCY_UNIQUE_LOCK_H_
#define LBB_CONCURRENCY_UNIQUE_LOCK_H_

#include <lbb/utility.h>

namespace lbb {
namespace concurrency {

template<typename T>
class unique_lock : not_copyable, public movable<unique_lock<T> >,
	public safe_bool<unique_lock<T> > {

public:
	typedef T mutex_type;

	LBB_TYPEDEF_MOVE_TYPES_TPL(unique_lock<mutex_type>);


	/**
	 * Construct an empty lock
	 */
	unique_lock() : _mutex(0), _locked(false)  { }

	/**
	 * Construct a new lock from a mutex and lock it
	 * @param mutex the mutex held by the lock
	 */
	explicit unique_lock(mutex_type& mutex) : _mutex(&mutex), _locked(true) {
		_mutex->lock();
	}

	/**
	 * Move construction of a mutex, the attribute (locked or not) rest the same
	 * @param to_move the lock to move
	 */
	unique_lock(rvalue_reference to_move) : _mutex(to_move._mutex), _locked(to_move._locked) {
		to_move._locked = false;
		to_move._mutex = 0;
	}

	/**
	 * Destroy the lock and unlock the mutex if needed
	 */
	~unique_lock() { 
		if(_mutex && _locked) {
			_mutex->unlock();
		}
	}

	/**
	 * Copy by move
	 * @param to_move the lock to move
	 * @return the mutex moved
	 */
	unique_lock& operator=(rvalue_reference to_move) { 
		if(_mutex && _locked) {
			_mutex->unlock();
		}

		_mutex = to_move._mutex;
		_locked = to_move._locked;

		to_move._mutex = 0;
		to_move._locked = false;
		return *this;
	}

	/**
	 * lock the mutex
	 * @note, just fail and exit badly of the mutex was already locked ...
	 */
	void lock() { 
		if(!_mutex || _locked) { 
			throw system_error(42, _mutex ? "lock() on unique lock without mutex" : "lock() on mutex already locked");
		}

		_mutex->lock();
		_locked = true;
	}


	/**
	 * Try to lock the mutex
	 * \return true if the operation succeed and false otherwise
	 */
	bool try_lock() { 
		if(!_mutex || _locked) { 
			throw system_error(42, _mutex ? "try_lock() on unique lock without mutex" : "try_lock() on mutex already locked");
		}

		if(_mutex->try_lock()) {
			_locked = true;
		}

		return _locked;
	}


	/**
	 * unlock the mutex
	 */
	void unlock() { 
		if(!_mutex || !_locked) { 
			throw system_error(42, _mutex ? "unlock() on unique lock without mutex" : "unlock() on mutex not locked");
		}
		_mutex->unlock();
		_locked = false;
	}


	/**
	 * swap to lock
	 * @param other the lock to swap with
	 */
	void swap(unique_lock& other) { 
		T* tmp_mutex = other._mutex;
		other._mutex = _mutex;
		_mutex = tmp_mutex;

		bool tmp_locked = other._locked;
		other._locked = _locked;
		_locked = tmp_locked;
	}


	/**
	 * Break the association of the associated mutex if any ...
	 * No locks are unlocked
	 * @return the associated mutex
	 */
	mutex_type* release() { 
		mutex_type* result = _mutex;
		_mutex = 0;
		_locked = false;
		return result;
	}

	/**
	 * return the associated mutex
	 */
	mutex_type* mutex() const { 
		return _mutex;
	}

	/**
	 * test if the mutex is locked or not ...
	 */
	bool owns_lock() const { 
		if(_mutex && _locked) {
			return true;
		}

		return false;
	}

	/**
	 * boolean conversion ...
	 */
	bool boolean_value() const { 
		return owns_lock();
	}

private:
	mutex_type* _mutex;								//ptr to the underlying mutex ...
	bool _locked;
};


}  // namespace concurrency
}  // namespace lbb



#endif /* LBB_CONCURRENCY_UNIQUE_LOCK_H_ */
