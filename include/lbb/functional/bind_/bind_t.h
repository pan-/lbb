#ifndef LBB_FUNCTIONAL_BIND__BIND_T_H_
#define LBB_FUNCTIONAL_BIND__BIND_T_H_

#include <lbb/meta.h>
#include <lbb/utility.h>

#include "application_args.h"

#include "apply.h"

#include <lbb/functional/result_of.h>

namespace lbb { 
namespace functional { 
namespace bind_ { 

using namespace meta::introspection_::signature_;


template<typename F, typename B1 = type_list_::nil_, typename B2 = type_list_::nil_, 
typename B3 = type_list_::nil_, typename B4 = type_list_::nil_, typename B5 = type_list_::nil_>
struct bind_t { 

	typedef tuple<B1, B2, B3, B4, B5>							args_list_type;
	typedef typename result_of<F()>::type 						return_type;
	typedef typename result_of<F()>::type 						result_type;

	bind_t(F func, args_list_type args) : _function(func), _args(args) { };	

	return_type operator()() { 
		application_args_0 unbounded_args;
		return apply(_function, _args, unbounded_args);				
	}

	template<typename A1>
	return_type operator()(A1 arg1) { 
		application_args_1<A1> unbounded_args(forward(arg1));
		return apply(_function, _args, unbounded_args);				
	}

	template<typename A1, typename A2>
	return_type operator()(A1 arg1, A2 arg2) { 
		application_args_2<A1, A2> unbounded_args(forward(arg1), forward(arg2));
		return apply(_function, _args, unbounded_args);				
	}

	template<typename A1, typename A2, typename A3>
	return_type operator()(A1 arg1, A2 arg2, A3 arg3) { 
		application_args_3<A1, A2, A3> unbounded_args(forward(arg1), forward(arg2), forward(arg3));		
		return apply(_function, _args, unbounded_args);				
	}

	template<typename A1, typename A2, typename A3, typename A4>
	return_type operator()(A1 arg1, A2 arg2, A3 arg3, A4 arg4) { 
		application_args_4<A1, A2, A3, A4> unbounded_args(forward(arg1), forward(arg2), forward(arg3), forward(arg4));		
		return apply(_function, _args, unbounded_args);				
	}

	template<typename A1, typename A2, typename A3, typename A4, typename A5>
	return_type operator()(A1 arg1, A2 arg2, A3 arg3, A4 arg4, A5 arg5) {
		application_args_5<A1, A2, A3, A4, A5> unbounded_args(forward(arg1), forward(arg2), forward(arg3), forward(arg4), forward(arg5));			 
		return apply(_function, _args, unbounded_args);				
	}

private:
	F _function;
	args_list_type _args;
};

}
} 
}





#endif /* LBB_FUNCTIONAL_BIND__BIND_T_H_ */