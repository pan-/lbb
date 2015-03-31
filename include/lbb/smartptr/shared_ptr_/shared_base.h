#ifndef LBB_SMARTPTR_SHARED_PTR__SHARED_BASE_H_
#define LBB_SMARTPTR_SHARED_PTR__SHARED_BASE_H_

#include <lbb/concurrency/atomic.h>

namespace lbb {
namespace smartptr {
namespace shared_ptr_ {

class shared_base
{
	typedef void (*deleter)(shared_base* base);

	lbb::concurrency::atomic<unsigned int> _ref_count;
	deleter _deleter;

public:
	inline shared_base(deleter deleter) : _ref_count(0), _deleter(deleter) { }

	inline ~shared_base() {
		_deleter(this);
	}

	inline void increment_ref_count() {
		++_ref_count;
	}

	inline unsigned int decrement_ref_count() {
		return --_ref_count;
	}
};


} // shared_ptr_
} // smartptr
} // lbb

#endif /* LBB_SMARTPTR_SHARED_PTR__SHARED_BASE_H_ */