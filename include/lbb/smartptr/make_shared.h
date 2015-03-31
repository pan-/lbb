#ifndef LBB_SMARTPTR_MAKE_SHARED_H_
#define LBB_SMARTPTR_MAKE_SHARED_H_

#include "shared_ptr_/shared_base_value.h"
#include "shared_ptr.h"
#include <lbb/utility.h>

namespace lbb {
namespace smartptr {

template<typename T>
shared_ptr<T> make_shared()
{
	return *new shared_ptr_::shared_base_value<T>;
}

template<typename T, typename A0>
shared_ptr<T> make_shared(A0 arg0)
{
	return *new shared_ptr_::shared_base_value<T>(forward(arg0));
}

template<typename T, typename A0, typename A1>
shared_ptr<T> make_shared(A0 arg0, A1 arg1)
{
	return *new shared_ptr_::shared_base_value<T>(forward(arg0), forward(arg1));
}

template<typename T, typename A0, typename A1, typename A2>
shared_ptr<T> make_shared(A0 arg0, A1 arg1, A2 arg2)
{
	return *new shared_ptr_::shared_base_value<T>(forward(arg0), forward(arg1), forward(arg2));
}

template<typename T, typename A0, typename A1, typename A2, typename A3>
shared_ptr<T> make_shared(A0 arg0, A1 arg1, A2 arg2, A3 arg3)
{
	return *new shared_ptr_::shared_base_value<T>(forward(arg0), forward(arg1), forward(arg2), forward(arg3));
}

template<typename T, typename A0, typename A1, typename A2, typename A3, typename A4>
shared_ptr<T> make_shared(A0 arg0, A1 arg1, A2 arg2, A3 arg3, A4 arg4)
{
	return *new shared_ptr_::shared_base_value<T>(forward(arg0), forward(arg1), forward(arg2), forward(arg3), forward(arg4));
}



} // namespace smartptr
} // namespace lbb

#endif /* LBB_SMARTPTR_MAKE_SHARED_H_ */