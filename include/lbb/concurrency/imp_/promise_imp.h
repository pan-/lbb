#ifndef LBB_CONCURRENCY_IMP__PROMISE_IMP_H_
#define LBB_CONCURRENCY_IMP__PROMISE_IMP_H_

namespace lbb {
namespace concurrency { 

template<typename T>
promise<T>::promise() : 
	_shared_state(make_shared<future_::shared_state<T> >()),
	_has_future(false) 
{ }


template<typename T>
promise<T>::promise(rvalue_reference other) : 
	_shared_state(other._shared_state),
	_has_future(other._has_future)
{ 
	other._shared_state = 0;
}


template<typename T>
promise<T>::~promise() { 
	if(_shared_state && _shared_state->is_empty()) { 
		_shared_state->set_exception(future_error(future_error::broken_promise));
	}
}


template<typename T>
promise<T>& promise<T>::operator=(rvalue_reference other) { 
	if(_shared_state && _shared_state->is_empty()) { 
		_shared_state->set_exception(future_error(future_error::broken_promise));
	}

	_shared_state = other._shared_state;
	_has_future = other._has_future;
	other._shared_state = 0;
	return *this;
}


template<typename T>
void promise<T>::swap(promise& other) { 
	shared_ptr<future_::shared_state<T> > tmp = other._shared_state;
	other._shared_state = _shared_state;
	_shared_state = tmp;

	bool tmp_has_future = other._has_future;
	other._has_future = _has_future;
	_has_future = tmp_has_future;
}


template<typename T>
future<T> promise<T>::get_future() {
	if(_has_future) { 
		throw future_error(future_error::future_already_retrieved);
	}

	return future<T>(_shared_state);
}


template<typename T>
void promise<T>::set_value(T value) { 
	if(!_shared_state) {
		 throw future_error(future_error::no_state);
	}

	if(!_shared_state->is_empty()) { 
		throw future_error(future_error::promise_already_satisfied);
	}

	_shared_state->set_value(move(value));
}


template<typename T>
template<typename E>
void promise<T>::set_exception(const E& e) { 
	if(!_shared_state) {
		 throw future_error(future_error::no_state);
	}

	if(!_shared_state->is_empty()) { 
		throw future_error(future_error::promise_already_satisfied);
	}

	_shared_state->set_exception(move(e));	
}




}  // namespace concurrency
}  // namespace lbb


#endif /* LBB_CONCURRENCY_IMP__PROMISE_IMP_H_ */