#ifndef LBB_CONCURRENCY_IMP_FUTURE_IMP_H_
#define LBB_CONCURRENCY_IMP_FUTURE_IMP_H_

#include <stdexcept>
#include <lbb/utility.h>
#include <lbb/smartptr.h>
#include <lbb/meta.h>

#include "../future_error.h"

#include <iostream>

namespace lbb {
namespace concurrency { 


//traits which compute the result of future then 
template<typename F, typename T>
struct result_of_future_then_ { 
	// result_of_F => the return type of F
	typedef typename result_of<F(future<T>)>::type result_of_F; 

	// true if the result of F is void and false otherwise
	static const bool is_void_ = is_same_type_<result_of_F, void>::value;

	// type => void if the result of F is void and future<result_of_F> otherwise
	typedef typename select_type_<is_void_, void, future<result_of_F> >::type type;
};



template<typename T>
future<T>::future(const shared_ptr<future_::shared_state<T> >& shared_state) :
	_shared_state(shared_state)
{ 
}


template<typename T>
future<T>::future() : _shared_state(0) { }


template<typename T>
future<T>::future(rvalue_reference other) : _shared_state(other._shared_state) { 
	other._shared_state = 0;
}


template<typename T>
future<T>::~future() { }


template<typename T>
future<T>& future<T>::operator=(rvalue_reference other) { 
	_shared_state = other._shared_state;
	other._shared_state = 0;
	return *this;
}


template<typename T>	 
T future<T>::get() { 
	if(!_shared_state.get()) { 
		throw future_error(future_error::no_state);
	}

	T value = _shared_state->get();
	_shared_state = 0;
	return move(value);
}


template<typename T>
bool future<T>::valid() const { 
	return (_shared_state.get() && _shared_state->valid()) ? true : false;
}


template<typename T>
void future<T>::wait() const { 
	if(!_shared_state.get()) { 
		throw future_error(future_error::no_state);
	}

	_shared_state->wait();	
}

namespace future_ { 


template<typename F, typename T, bool is_void = result_of_future_then_<F, T>::is_void_ >
struct future_continuation;


template<typename F, typename T>
struct future_continuation<F, T, true>
{ 
	typedef shared_ptr<shared_state<T> > 										InputSharedState; 	

	future_continuation(F continuation, const InputSharedState& input_shared_state) :
		_input_shared_state(input_shared_state),
		_continuation(continuation) { 
	}

	void operator()() { 
		try { 
			_continuation(future<T>(_input_shared_state));
		}  catch(const std::exception& e) { 
			std::cout << "exception catch during future.then : " << e.what() << std::endl;
			throw;
		} catch(...) { 
			std::cout << "unknown exception catch during future.then" << std::endl;
			throw;
		}

		_input_shared_state = 0;
	}

private:
	InputSharedState 				_input_shared_state;
	F 								_continuation;
};




template<typename F, typename T>
struct future_continuation<F, T, false>
{ 
	typedef shared_ptr<shared_state<T> > 										InputSharedState; 	
	typedef shared_ptr<shared_state<typename result_of<F(future<T>)>::type> > 	OutputSharedState; 

	future_continuation(F continuation, const InputSharedState& input_shared_state) :
		_input_shared_state(input_shared_state),
		_output_shared_state(make_shared<shared_state<typename result_of<F(T)>::type> >()),
		_continuation(continuation) { 
	}

	void operator()() { 
		try { 
			_output_shared_state->set_value(_continuation(future<T>(_input_shared_state)));
		} catch(const std::exception& e) { 
			_output_shared_state->set_exception(std::runtime_error(e.what()));
			throw;
		} catch(...) { 
			_output_shared_state->set_exception(std::runtime_error("exception occur during execution of a future continuation"));
			throw;
		}
		_input_shared_state = 0;
		_output_shared_state = 0;
	}

	future<typename result_of<F(future<T>)>::type > get_future() { 
		return future<typename result_of<F(future<T>)>::type>(_output_shared_state);
	}

private:
	InputSharedState 				_input_shared_state;
	OutputSharedState				_output_shared_state;
	F 								_continuation;
};



}

template<typename T>
template<typename F>
typename enable_if_<result_of_future_then_<F, T>::is_void_, typename result_of_future_then_<F, T>::type>::type 
future<T>::then(F function) {
	if(!_shared_state.get()) { 
		throw future_error(future_error::no_state);
	}

	future_::future_continuation<F, T> continuation(function, _shared_state);
	_shared_state->set_continuation(continuation);
	_shared_state = 0;
}

template<typename T>
template<typename F>
typename disable_if_<result_of_future_then_<F, T>::is_void_, typename result_of_future_then_<F, T>::type>::type 
future<T>::then(F function) { 
	if(!_shared_state.get()) { 
		throw future_error(future_error::no_state);
	}
	
	future_::future_continuation<F, T> continuation(function, _shared_state);
	_shared_state->set_continuation(continuation);
	_shared_state = 0;
	return continuation.get_future();
}



}  // namespace concurrency
}  // namespace lbb


#endif /* LBB_CONCURRENCY_IMP_FUTURE_IMP_H_ */
