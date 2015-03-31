#ifndef LBB_FUNCTIONAL_BIND__APPLICATION_LIST_H_
#define LBB_FUNCTIONAL_BIND__APPLICATION_LIST_H_

#include <lbb/utility.h>
#include "placeholder.h"

namespace lbb { 
namespace functional { 
namespace bind_ { 

struct application_args_0 { 

	application_args_0() { }

	template<typename T>
	T operator[](T val) { return val; }
};


template<typename A1>
struct application_args_1 { 

	application_args_1(A1 arg1) : _arg1(forward(arg1)) { }

	A1 operator[](placeholder_t<1>) { return forward(_arg1); }

	template<typename T>
	T operator[](T val) { return val; }

	A1 _arg1;
};


template<typename A1, typename A2>
struct application_args_2 : application_args_1<A1> { 
	typedef application_args_1<A1> base_t;

	application_args_2(A1 arg1, A2 arg2) : base_t(forward(arg1)), _arg2(forward(arg2)) { }

	A1 operator[](placeholder_t<1>) { return forward(base_t::_arg1); }
	A2 operator[](placeholder_t<2>) { return forward(_arg2); }

	template<typename T>
	T operator[](T val) { return val; }

	A2 _arg2;
};


template<typename A1, typename A2, typename A3>
struct application_args_3 : application_args_2<A1, A2> { 
	typedef application_args_2<A1, A2> base_t;

	application_args_3(A1 arg1, A2 arg2, A3 arg3) : 
		base_t(forward(arg1), forward(arg2)), _arg3(forward(arg3)) { }

	A1 operator[](placeholder_t<1>) { return forward(base_t::_arg1); }
	A2 operator[](placeholder_t<2>) { return forward(base_t::_arg2); }
	A3 operator[](placeholder_t<3>) { return forward(_arg3); }

	template<typename T>
	T operator[](T val) { return val; }

	A3 _arg3;
};


template<typename A1, typename A2, typename A3, typename A4>
struct application_args_4 : application_args_3<A1, A2, A3> { 
	typedef application_args_3<A1, A2, A3> base_t;

	application_args_4(A1 arg1, A2 arg2, A3 arg3, A4 arg4) : 
		base_t(forward(arg1), forward(arg2), forward(arg3)), _arg4(forward(arg4)) { }

	A1 operator[](placeholder_t<1>) { return forward(base_t::_arg1); }
	A2 operator[](placeholder_t<2>) { return forward(base_t::_arg2); }
	A3 operator[](placeholder_t<3>) { return forward(base_t::_arg3); }
	A4 operator[](placeholder_t<4>) { return forward(_arg4); }

	template<typename T>
	T operator[](T val) { return val; }

	A4 _arg4;
};


template<typename A1, typename A2, typename A3, typename A4, typename A5>
struct application_args_5 : application_args_4<A1, A2, A3, A4> { 
	typedef application_args_4<A1, A2, A3, A4> base_t;

	application_args_5(A1 arg1, A2 arg2, A3 arg3, A4 arg4, A5 arg5) : 
		base_t(forward(arg1), forward(arg2), forward(arg3), forward(arg4)), _arg5(forward(arg5)) { }

	A1 operator[](placeholder_t<1>) { return forward(base_t::_arg1); }
	A2 operator[](placeholder_t<2>) { return forward(base_t::_arg2); }
	A3 operator[](placeholder_t<3>) { return forward(base_t::_arg3); }
	A4 operator[](placeholder_t<4>) { return forward(base_t::_arg4); }
	A5 operator[](placeholder_t<5>) { return forward(_arg5); }

	template<typename T>
	T operator[](T val) { return val; }

	A5 _arg5;
};


/**
 * create args list for application args ...
 */
static inline application_args_0 make_application_args() { 
	return application_args_0();
}

template<typename A1>
static inline application_args_1<A1> make_application_args(A1 arg1) { 
	return application_args_1<A1>(forward(arg1));
}

template<typename A1, typename A2>
static inline application_args_2<A1, A2> make_application_args(A1 arg1, A2 arg2) { 
	return application_args_2<A1, A2>(forward(arg1), forward(arg2));
}

template<typename A1, typename A2, typename A3>
static inline application_args_3<A1, A2, A3> make_application_args(A1 arg1, A2 arg2, A3 arg3) { 
	return application_args_3<A1, A2, A3>(forward(arg1), forward(arg2), forward(arg3));
}

template<typename A1, typename A2, typename A3, typename A4>
application_args_4<A1, A2, A3, A4> 
static inline make_application_args(A1 arg1, A2 arg2, A3 arg3, A4 arg4) { 
	return application_args_4<A1, A2, A3, A4>(forward(arg1), forward(arg2), forward(arg3), forward(arg4));
}

template<typename A1, typename A2, typename A3, typename A4, typename A5>
static inline application_args_5<A1, A2, A3, A4, A5> 
make_application_args(A1 arg1, A2 arg2, A3 arg3, A4 arg4, A5 arg5) { 
	return application_args_5<A1, A2, A3, A4, A5>(forward(arg1), forward(arg2), forward(arg3), forward(arg4), forward(arg5));
}

}
}
}


#endif /* LBB_FUNCTIONAL_BIND__APPLICATION_LIST_H_ */