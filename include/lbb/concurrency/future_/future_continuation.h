#ifndef LBB_CONCURRENCY_FUTURE__FUTURE_CONTINUATION_H_
#define LBB_CONCURRENCY_FUTURE__FUTURE_CONTINUATION_H_

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

// template<typename T>
// class future_continuation : public movable<> { 

// public:
// 	//empty future continuation
// 	future_continuation();

// 	//future continuation with just a callback, no promise associated 
// 	template<typename F>
// 	future_continuation(F f);

// 	//future continuation with a callback and a promise 
// 	template<typename F, typename R>
// 	future_continuation(F f, promise<R> p);



// };


// /**
//  * used for tag dispatching, true if the result_of<F> is not void
//  * and false otherwise
//  */
// template<typename F>
// struct has_future_result_ { 
// 	// result_of_F => the return type of F
// 	typedef typename result_of<F>::type result_of_F; 

// 	// true if the result of F is void and false otherwise
// 	static const bool value = !(is_same_type_<result_of_F, void>::value);
// };

// /**
//  * describe a future continuation of, the continuation has type F
//  */
// template<typename F, bool has_result = has_future_result_<F>::value>
// class future_continuation; 

// /**
//  * future continuation where a the continuation provide a result
//  */
// template<typename F>
// class future_continuation<F, true> : not_copyable, public movable<future_continuation<F, true> >
// { 
// public:

// 	LBB_TYPEDEF_MOVE_TYPES_TPL( future_continuation<F, true> );

// 	typedef typename result_of<F>::type result_type;

// 	typedef at_<0, typename introspection_::signature_::get_parameters_<F> >::type continuation_arg;

// 	//construct the continuation 
// 	future_continuation(F f);

// 	//move constructor
// 	future_continuation(rvalue_reference other);

// 	//move assignement operator
// 	future_continuation& operator=(rvalue_reference other);	

// 	//get the future associated with the continuation 
// 	future<result_type> get_future();

// 	//call the continuation and fill the future
// 	void operator()(continuation_arg arg);

// private:
// 	F 					 _continuation;
// 	promise<result_type> _promise;
// };


// /**
//  * future continuation when there is no result type 
//  */
// // template<typename F>
// // class future_continuation<F, false> : not_copyable, public movable<future_continuation<F, false> >
// // { 
// // public:

// // 	LBB_TYPEDEF_MOVE_TYPES_TPL( future_continuation<F, false> );

// // 	typedef at_<0, typename introspection_::signature_::get_parameters_<F> >::type continuation_arg;

// // 	//construct the continuation 
// // 	future_continuation(F f);

// // 	//move constructor
// // 	future_continuation(rvalue_reference other);

// // 	//move assignement operator
// // 	future_continuation& operator=(rvalue_reference other);	

// // 	//call the continuation and fill the future
// // 	void operator()(continuation_arg arg);

// // private:
// // 	F 					 _continuation;
// // };




// template<typename F>
// future_continuation<F, true>::future_continuation(F f) : 
// 	_continuation(forward(f)) { 
// }


// template<typename F>
// future_continuation<F, true>::future_continuation(rvalue_reference other) : 
// 	_continuation(move(other._continuation)),
// 	_promise(move(other._promise)) { 
// }

// template<typename F>
// future_continuation<F, true>& future_continuation<F, true>::operator=(rvalue_reference other) { 
// 	_continuation = move(other._continuation);
// 	_promise = move(other._promise);
// 	return *this;
// }

// template<typename F>
// future<future_continuation<F, true>::result_type> future_continuation<F, true>::get_future() { 
// 	return _promise.get_future();
// }

// template<typename F>
// void future_continuation<F, true>::operator()(continuation_arg arg) { 
// 	try { 
// 		_continuation(move(arg));
// 	} catch(const std::exception& e) { 
// 		_promise.set_exception(std::runtime_exception(e.what()));
// 	} catch(...) { 
// 		_promise.set_exception(std::runtime_exception("exception occur during execution of a future continuation"));
// 	}
// }




}  // namespace future_
}  // namespace concurrency
}  // namespace lbb


#endif /* LBB_CONCURRENCY_FUTURE__FUTURE_CONTINUATION_H_ */