#ifndef LBB_SMARTPTR_SHARED_PTR__SHARED_BASE_VALUE_H_
#define LBB_SMARTPTR_SHARED_PTR__SHARED_BASE_VALUE_H_

#include "shared_base.h"
#include <lbb/utility.h>

namespace lbb {
namespace smartptr {
namespace shared_ptr_ {

template<typename T>
class shared_base_value : public shared_base
{

	static void deleter_imp(shared_base* self_base) {
		shared_base_value* self = static_cast<shared_base_value*>(self_base);
		self->_value.~T();
	}

	T _value;

public:

	inline shared_base_value() : shared_base(&deleter_imp), _value() { }

	template<typename T0>
	inline shared_base_value(T0 arg0) :
			shared_base(&deleter_imp), _value(forward(arg0))
	{}

	template<typename T0, typename T1>
	inline shared_base_value(T0 arg0, T1 arg1) :
			shared_base(&deleter_imp), _value(forward(arg0), forward(arg1))
	{}

	template<typename T0, typename T1, typename T2>
	inline shared_base_value(T0 arg0, T1 arg1, T2 arg2) :
			shared_base(&deleter_imp), _value(forward(arg0), forward(arg1), forward(arg2))
	{}

	template<typename T0, typename T1, typename T2, typename T3>
	inline shared_base_value(T0 arg0, T1 arg1, T2 arg2, T3 arg3) :
			shared_base(&deleter_imp), _value(forward(arg0), forward(arg1), forward(arg2), forward(arg3))
	{}

	template<typename T0, typename T1, typename T2, typename T3, typename T4>
	inline shared_base_value(T0 arg0, T1 arg1, T2 arg2, T3 arg3, T4 arg4) :
			shared_base(&deleter_imp), _value(forward(arg0), forward(arg1), forward(arg2), forward(arg3), forward(arg4))
	{}

	inline T* instance_address() {
		return &_value;
	}
};

} // shared_ptr_
} // smartptr
} // lbb

#endif /* LBB_SMARTPTR_SHARED_PTR__SHARED_BASE_VALUE_H_ */
