#ifndef LBB_CONCURRENCY_PROMISE_HANDLER_H_
#define LBB_CONCURRENCY_PROMISE_HANDLER_H_

#include <lbb/smartptr.h>
#include <lbb/utility.h>
#include "promise.h"

namespace lbb {
namespace concurrency { 

/**
 * The class template lbb::promise_handler provides a facility to wrap 
 * a promise into an handler.
 * 
 * For instance if we have the following code : 
 * \code
 *
 * typedef lbb::function<void(http_response)> http_request_callback_t;
 * void do_http_request(const std::string& uri, http_request_callback_t callback);
 *
 * \endcode
 * 
 * and we want to translate it into a future/promise a we can use a promise handler 
 * to replace the callback.
 *
 * \code
 * 
 * lbb::future<http_response> do_http_request(const std::string& uri) { 
 *   lbb::promise<http_response> promise_response;
 *   lbb::future<http_response> future_response = promise_response.get_future();
 *	 do_http_request(make_promise_handler(move(promise_response)));
 * 	 return move(future_response);
 * }
 * 
 * \endcode
 * 
 */
template<typename T>
class promise_handler 
{ 

public:

	/**
	 * a promise handler is always constructed from a promise
	 */
	promise_handler(promise<T> p);

	/**
	 * operator call, it mimic the handler and store the value 
	 * passed in the continuation in the promise 
	 */
	void operator()(T value);

private:
	shared_ptr<promise<T> > _promise;
};


}  // namespace concurrency
}  // namespace lbb

#include "imp_/promise_handler_imp.h"


#endif /* LBB_CONCURRENCY_PROMISE_HANDLER_H_ */
