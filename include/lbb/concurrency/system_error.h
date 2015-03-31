#ifndef LBB_CONCURRENCY_SYSTEM_ERROR_H_
#define LBB_CONCURRENCY_SYSTEM_ERROR_H_

#include <stdexcept>
#include <string>


namespace lbb { 
namespace concurrency { 

class system_error : public std::runtime_error { 
public:

	typedef int error_code_t;

	system_error(error_code_t error) : std::runtime_error(""), _error(error) { } 

	system_error(error_code_t error, std::string what) :
		std::runtime_error(what),
		_error(error)
	{ }

	error_code_t code() { return _error; }

private:
	error_code_t _error;
};



}
}

#endif /* LBB_CONCURRENCY_SYSTEM_ERROR_H_ */

