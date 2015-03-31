#ifndef LBB_CORE_CONCURRENCY_PROMISE_H_
#define LBB_CORE_CONCURRENCY_PROMISE_H_

#include <lbb/utility.h>
#include <lbb/smartptr.h>
#include "future.h"

namespace lbb {
namespace concurrency { 

/**
 * The class template lbb::promise provides a facility to store a value 
 * that is later acquired asynchronously via a lbb::future object, 
 * that the lbb::promise can supply.
 */
template<typename T>
class promise : not_copyable, public movable<promise<T> >
{ 

public:

	LBB_TYPEDEF_MOVE_TYPES_TPL( promise<T> );


	/** 
	 * Default constructor. 
	 * Constructs the promise with an empty shared state.
	 */
	promise();

	/**
	 * Move constructor. 
	 * Constructs the promise with the shared state of other using move semantics. 
	 * other is in valid, but undefined state afterwards.
	 */
	promise(rvalue_reference other);

	/**
	 * Abandons the shared state: 
	 *  - if the shared state is ready, releases it.
	 *  - if the shared state is not ready, stores an exception object indicating a broken_promise, 
	 *    makes the shared state ready and releases it.
	 */
	~promise();

	/**
	 * Move assignment operator. 
	 * First, abandons the shared state (as in ~promise()), then assigns the shared state of other
	 * to this.
	 */
	promise& operator=(rvalue_reference other);

	/**
	 *  Exchanges the shared states of two promise objects.
	 */
	void swap(promise& other);

	/**
	 * Returns a future object associated with the same shared state as *this.
	 * Exception is thrown if *this has no shared state or get_future has already been called.
	 * @throw future_error on the following conditions:
	 *  - *this has no shared state. 
	 * 	- get_future() has already been called on a promise with the same shared state as *this. 
	 */
	future<T> get_future();


	/**
	 * Stores the value into the shared state and makes the state ready.
	 * The operation is atomic, i.e. it behaves as though they acquire a single 
	 * mutex associated with the promise object while updating the promise object.
	 * An exception is thrown if there is no shared state or the shared state already stores a value or exception.
	 * @throw future_error on the following conditions:
	 *   - *this has no shared state. 
	 * 	 - The shared state already stores a value or exception. 
	 */
	void set_value(T value);


	/**
	 * Stores the exception e into the shared state and makes the state ready.
	 * The operation is atomic, i.e. it behaves as though they acquire a single mutex associated 
	 * with the promise object while updating the promise object.
	 * An exception is thrown if there is no shared state or the shared state already stores a value or exception.
	 *
	 * @throw future_error on the following conditions:
	 *   - *this has no shared state. The error category is set to no_state.
	 *   - The shared state already stores a value or exception. The error category is set to promise_already_satisfied.
	 */
	template<typename E>
	void set_exception(const E& e);

private:
	shared_ptr<future_::shared_state<T> > _shared_state;
	bool _has_future;
};


}  // namespace concurrency
}  // namespace lbb

#include "imp_/promise_imp.h"


#endif /* LBB_CORE_CONCURRENCY_PROMISE_H_ */
