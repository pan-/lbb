#include "lbb/concurrency/future_error.h"

namespace lbb {
namespace concurrency { 

namespace { 

static const char* _error_code_messages[] = { 
	"broken promise : the asynchronous task abandoned its shared state", 
	"future already retrieved : the contents of shared state were already accessed", 
	"promise already satisfied : attempt to store a value in the shared state twice",
	"no state : attempt to access promise or future without an associated shared state" 
};

}


future_error::future_error(error_code ec) : 
	std::logic_error(_error_code_messages[ec]),
	_code(ec) { 
}


future_error::error_code future_error::code() const  { 
	return _code;
}


}  // namespace concurrency
}  // namespace lbb


