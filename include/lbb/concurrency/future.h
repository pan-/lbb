#ifndef LBB_CONCURRENCY_FUTURE_H_
#define LBB_CONCURRENCY_FUTURE_H_

#include <lbb/utility.h>
#include <lbb/smartptr.h>

#include "future_/shared_state.h"

namespace lbb {
namespace concurrency { 

template<typename T>
class promise;

template<typename F, typename T>
struct result_of_future_then_;

namespace future_ { 
template<typename, typename, bool>
struct future_continuation;
}


/** 
 * The class template lbb::future provides a mechanism to access the result of asynchronous operations:
 * An asynchronous operation (created via lbb::promise) can provide a lbb::future object to the creator 
 * of that asynchronous operation.
 * The creator of the asynchronous operation can then use a variety of methods to query, wait for, 
 * or extract a value from the lbb::future. These methods may block if the asynchronous operation has 
 * not yet provided a value.
 * When the asynchronous operation is ready to send a result to the creator, it can do so by modifying 
 * shared state (e.g. lbb::promise::set_value) that is linked to the creator's lbb::future.
 * Note that instances of this type can be moved but not copied 
 */
template<typename T>
class future : not_copyable, public movable<future<T> >
{ 

	// template<typename U>
	friend class promise<T>;

	template<typename, typename, bool>
	friend struct future_::future_continuation;

	future(const shared_ptr<future_::shared_state<T> >& shared_state);

public:

	LBB_TYPEDEF_MOVE_TYPES_TPL( future<T> );

	/**
	 * Default constructor. Constructs a lbb::future with no shared state. 
	 * After construction, valid() == false.
	 */
	future();

	/**
	 * Move constructor. 
	 * Constructs a lbb::future with the shared state of other using move semantics. 
	 * After construction, other.valid() == false.
	 */
	future(rvalue_reference other);

	/**
	 * Abandons the ownership of the shared state, if any.
	 */
	~future();

	/**
	 * Assigns the contents of another future object.
	 * Releases any shared state and move-assigns the contents of other to *this. 
	 * After the assignment, other.valid() == false and this->valid() will yield the same value 
	 * as other.valid() before the assignment.
	 */
	future& operator=(rvalue_reference other);

	/**
	 * The get method waits until the future has a valid result and retrieves it. 
	 * It effectively calls wait() in order to wait for the result.
	 * 
	 * if valid() is false before the call to this function, it throw an exception.
	 * valid() is false after a call to this method.
	 * 
	 * @return The value v stored in the shared state, as std::move(v).
	 * 
	 * @exception If an exception was stored in the shared state referenced by the future 
	 * (e.g. via a call to lbb::promise::set_exception()) then that exception will be thrown.
	 */
	T get();

	/**
	 * Checks if the future refers to a shared state. 
	 * This is the case only for futures returned by lbb::promise::get_future() until the first time get() is called.
	 * @return true if *this refers to a shared state, otherwise false.
	 */
	bool valid() const;

	/**
	 * Blocks until the result becomes available. valid() == true after the call.
	 * throw if valid()== false before the call to this function.
	 */
	void wait() const;

	/**
	 * Execute the function F once the result has been retrieved.
	 * F is a function which take in input the this future result (future<T>).
	 * @return if F return a value of type T the result is a future to 
	 * this result : future<T>
	 * @return if F return nothing, the result is void
	 * @note after this call valid() == false 
	 */
	template<typename F>
	typename enable_if_<result_of_future_then_<F, T>::is_void_, typename result_of_future_then_<F, T>::type>::type 
	then(F function);

	template<typename F>
	typename disable_if_<result_of_future_then_<F, T>::is_void_, typename result_of_future_then_<F, T>::type>::type 
	then(F function);

private:
	shared_ptr<future_::shared_state<T> > _shared_state;
};


/**
 * partial specialization for future<void>
 * @note : TODO !!!!
 */



}  // namespace concurrency
}  // namespace lbb


#include "imp_/future_imp.h"


#endif /* LBB_CONCURRENCY_FUTURE_H_ */
