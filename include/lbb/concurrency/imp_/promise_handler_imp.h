#ifndef LBB_CONCURRENCY_IMP__PROMISE_HANDLER_IMP_H_
#define LBB_CONCURRENCY_IMP__PROMISE_HANDLER_IMP_H_

namespace lbb {
namespace concurrency { 


template<typename T>
promise_handler<T>::promise_handler(promise<T> p) : 
	_promise(make_shared<promise<T> >(forward(p))) { 
}


template<typename T>
void promise_handler<T>::operator()(T value) { 
	_promise->set_value(forward(value));
}	


template<typename T>
promise_handler<T> make_promise_handler(promise<T> p) { 
	return promise_handler<T>(forward(p));
}


}  // namespace concurrency
}  // namespace lbb


#endif /* LBB_CONCURRENCY_IMP__PROMISE_HANDLER_IMP_H_ */