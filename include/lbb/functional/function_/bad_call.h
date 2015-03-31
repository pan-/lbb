#ifndef LBB_FUNCTIONAL_FUNCTION__BAD_CALL_H_
#define LBB_FUNCTIONAL_FUNCTION__BAD_CALL_H_


#include <stdlib.h>
#include <stdio.h>
#include <lbb/utility.h>
#include "functor.h"


namespace lbb { 
namespace functional { 
namespace function_ { 


template<typename ResultType>
ResultType bad_call_of(functor& f) { 
	exit(-1);
}

template<typename ResultType, typename A1>
ResultType bad_call_of(functor& f, A1 arg1) { 
	exit(-1);
}

template<typename ResultType, typename A1, typename A2>
ResultType bad_call_of(functor& f, A1 arg1, A2 arg2) { 
	exit(-1);
}

template<typename ResultType, typename A1, typename A2, typename A3>
ResultType bad_call_of(functor& f, A1 arg1, A2 arg2, A3 arg3) { 
	exit(-1);
}
	
template<typename ResultType, typename A1, typename A2, typename A3,  typename A4>
ResultType bad_call_of(functor& f, A1 arg1, A2 arg2, A3 arg3, A4 arg4) { 
	exit(-1);
}

template<typename ResultType, typename A1, typename A2, typename A3, typename A4, typename A5>
ResultType bad_call_of(functor& f, A1 arg1, A2 arg2, A3 arg3, A4 arg4, A5 arg5) { 
	exit(-1);
}


}
}
}


#endif /* LBB_FUNCTIONAL_FUNCTION__BAD_CALL_H_ */