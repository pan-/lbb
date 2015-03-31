#ifndef LBB_CONCURRENCY_FUTURE__SHARED_STATE_H_
#define LBB_CONCURRENCY_FUTURE__SHARED_STATE_H_

#include <lbb/utility.h>
#include <lbb/smartptr.h>
#include <lbb/functional.h>

#include "../mutex.h"
#include "../unique_lock.h"
#include "../condition_variable.h"
#include "../future_error.h"

namespace lbb {
namespace concurrency { 
namespace future_ { 

template<typename T>
class shared_state { 

	typedef function<void()> throw_function_t;

	enum storage_state_tag { 
		empty_state,
		value_state,
		exception_state,
		done_state
	};

public:

	/**
	 * construct an empty_state shared state 
	 */
	shared_state() : _state(empty_state) { }


	~shared_state() { 
		switch(_state) {
			case value_state: 		
				_storage.template as<T*>()->~T(); 
				break;
		
			case exception_state: 	
				_storage.template as<throw_function_t*>()->~throw_function_t(); 
				break;
			
			default: 
				break;
		}
	}


	/**
	 * return false if the inner value has already been retrieved
	 * and true otherwise
	 */
	bool valid() { 
		return (_state != done_state) ? true : false;
	}


	/**
	 * return true if the state is still empty and false otherwise
	 */
	bool is_empty() { 
		return (_state == empty_state);
	}


	/**
	 * return the shared state inner value
	 */
	T get() { 
		//we wait for the result if there is no result
		wait();

		//if we have received an exception, we call the function which will
		//throw it
		if(_state == exception_state) { 
			_state = done_state;
			throw_function_t throw_func(*_storage.template as<throw_function_t*>());
			//delete the storage
			_storage.template as<throw_function_t*>()->~throw_function_t();

			//throw exception, no return from this point
			throw_func();
		}

		//if the promise was satisfied by a continuation, throw 
		if(_state != value_state) { 
			throw future_error(future_error::future_already_retrieved);
		}

		_state = done_state;

		T value = move(*(_storage.template as<T*>()));

		//release the storage
		_storage.template as<T*>()->~T();

		return move(value);
	}


	void wait() {
		unique_lock<mutex> lock(_mutex);

		if(_state == done_state) { 
			throw future_error(future_error::future_already_retrieved);
		}

		if(_state == empty_state) { 
			_condition.wait(lock);
		}
	}

	void set_value(T value) { 
		unique_lock<mutex> lock(_mutex);

		if(_state != empty_state) { 
			throw future_error(future_error::promise_already_satisfied);
		}

		new (_storage.get()) T(move(value));

		_state = value_state;

		if(_continuation) { 
			lock.unlock();
			_continuation();
		} else { 
			_condition.notify_one();
		}
	}


	template<typename E>
	void set_exception(const E& e) { 
		unique_lock<mutex> lock(_mutex);

		if(_state != empty_state) { 
			throw future_error(future_error::promise_already_satisfied);
		}

		new (_storage.get()) throw_function_t(bind(throw_exception<E>, e));

		_state = exception_state;

		if(_continuation) { 
			lock.unlock();
			_continuation();
		} else { 
			_condition.notify_one();
		}
	}

	//TODO : add enable shared from this and pass this as parameter of the 
	//continuation
	void set_continuation(const function<void()>& continuation) {
		unique_lock<mutex> lock(_mutex);

		//throw if the future was already retrieved
		if(_state == done_state) { 
			throw future_error(future_error::future_already_retrieved);
		}

		// if the promise has already been satisfied, call the continuation
		// otherwise store the continuation
		if(_state != empty_state) {
			lock.unlock(); 
			continuation();
		} else { 
			_continuation = continuation;
		}
	} 


private:
	template<typename E>
	static void throw_exception(E e) { 
		throw e;
	}

	mutex								_mutex;
	condition_variable					_condition;
	storage_state_tag 					_state;
	aligned_union<T, throw_function_t> 	_storage;
	function<void()>					_continuation;
};





}  // namespace future_
}  // namespace concurrency
}  // namespace lbb





#endif /* LBB_CONCURRENCY_FUTURE__SHARED_STATE_H_ */
