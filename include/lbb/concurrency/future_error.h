#ifndef LBB_CONCURRENCY_FUTURE_ERROR_H_
#define LBB_CONCURRENCY_FUTURE_ERROR_H_

#include <stdexcept>

namespace lbb {
namespace concurrency { 


/** 
 * The class future_error defines an exception object that is thrown on failure by the 
 * functions in the thread library that deal with asynchronous execution and shared states 
 * (future, promise, etc).
 */
class future_error : public std::logic_error
{ 

public:

	/**
	 * defines the error related to future/promise
	 */
	enum error_code { 
		broken_promise,				/* the asynchronous task abandoned its shared state */
		future_already_retrieved,	/* the contents of shared state were already accessed */
		promise_already_satisfied,	/* attempt to store a value in the shared state twice */
		no_state					/* attempt to access promise or future without an associated shared state */
	};


	/**
	 * Constructs a new future error object containing error code ec.
	 */
	future_error(error_code ec);


	/**
	 * Returns the stored error code.
	 */
	error_code code() const;

private:
	error_code _code;
};



}  // namespace concurrency
}  // namespace lbb


#endif /* LBB_CONCURRENCY_FUTURE_ERROR_H_ */
