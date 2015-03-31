#ifndef LBB_SMARTPTR_SHARED_PTR__SHARED_BASE_PTR_H_
#define LBB_SMARTPTR_SHARED_PTR__SHARED_BASE_PTR_H_

#include "shared_base.h"

namespace lbb {
namespace smartptr {
namespace shared_ptr_ {

template<typename T>
class shared_base_ptr : public shared_base
{
	static void deleter_imp(shared_base* self_base) {
		shared_base_ptr* self = static_cast<shared_base_ptr*>(self_base);
		delete self->_ptr;
	}

	T* _ptr;

public:
	inline shared_base_ptr(T* instance) : shared_base(&deleter_imp), _ptr(instance) { }
};

} // shared_ptr_
} // smartptr
} // lbb

#endif /* LBB_SMARTPTR_SHARED_PTR__SHARED_BASE_PTR_H_ */
