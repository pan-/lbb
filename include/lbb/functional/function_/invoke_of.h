#ifndef LBB_FUNCTIONAL_FUNCTION__INVOKE_OF_H_
#define LBB_FUNCTIONAL_FUNCTION__INVOKE_OF_H_

#include <lbb/utility.h>
#include "functor.h"

namespace lbb { 
namespace functional { 
namespace function_ { 


template<typename T, typename ResultType>
ResultType invoke_of(functor& f) { 
	return functor_ref<T>(f)();
}


template<typename T, typename ResultType, typename A1>
ResultType invoke_of(functor& f, A1 arg1) { 
	return functor_ref<T>(f)(forward(arg1));
}

template<typename T, typename ResultType, typename A1, typename A2>
ResultType invoke_of(functor& f, A1 arg1, A2 arg2) { 
	return functor_ref<T>(f)(forward(arg1), forward(arg2));
}

template<typename T, typename ResultType, typename A1, typename A2, typename A3>
ResultType invoke_of(functor& f, A1 arg1, A2 arg2, A3 arg3) { 
	return functor_ref<T>(f)(forward(arg1), forward(arg2), forward(arg3));
}


template<typename T, typename ResultType, typename A1, typename A2, typename A3, 
	typename A4>
ResultType invoke_of(functor& f, A1 arg1, A2 arg2, A3 arg3, A4 arg4) { 
	return functor_ref<T>(f)(forward(arg1), forward(arg2), forward(arg3), forward(arg4));
}

template<typename T, typename ResultType, typename A1, typename A2, typename A3, 
	typename A4, typename A5>
ResultType invoke_of(functor& f, A1 arg1, A2 arg2, A3 arg3, A4 arg4, A5 arg5) { 
	return functor_ref<T>(f)(forward(arg1), forward(arg2), forward(arg3), forward(arg4), forward(arg5));
}


}
}
}


#endif /* LBB_FUNCTIONAL_FUNCTION__INVOKE_OF_H_ */

