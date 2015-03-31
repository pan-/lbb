#ifndef LBB_FUNCTIONAL_MEM_FN_MEM_FN__MEM_FN_T_H_
#define LBB_FUNCTIONAL_MEM_FN_MEM_FN__MEM_FN_T_H_

#include <lbb/meta.h>
#include <lbb/utility.h>

namespace lbb { 
namespace functional { 
namespace mem_fn_ { 

template<typename F>
struct mem_fn_t { 

	typedef typename introspection_::signature_::get_return_type_<F>::type return_type;

	mem_fn_t(F method) : _method(method) { }


	template<typename Context>
	return_type operator()(Context context) { 
		return (get_ptr(context)->*(_method))();
	}


	template<typename Context, typename Arg1>
	return_type  operator()(Context context, Arg1 arg1) { 
		return (get_ptr(context)->*(_method))(forward(arg1));
	}


	template<typename Context, typename Arg1, typename Arg2>
	return_type operator()(Context context, Arg1 arg1, Arg2 arg2) { 
		return (get_ptr(context)->*(_method))(forward(arg1), forward(arg2));
	}


	template<typename Context, typename Arg1, typename Arg2, typename Arg3>
	return_type operator()(Context context, Arg1 arg1, Arg2 arg2, Arg3 arg3) { 
		return (get_ptr(context)->*(_method))(forward(arg1), forward(arg2), forward(arg3));
	}


	template<typename Context, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
	return_type operator()(Context context, Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4) { 
		return (get_ptr(context)->*(_method))(forward(arg1), forward(arg2), forward(arg3), forward(arg4));
	}


	/* 
	 * FOR POINTERS 
	 */
	template<typename Context>
	return_type operator()(Context* context) { 
		return (context->*(_method))();
	}


	template<typename Context, typename Arg1>
	return_type  operator()(Context* context, Arg1 arg1) { 
		return (context->*(_method))(forward(arg1));
	}


	template<typename Context, typename Arg1, typename Arg2>
	return_type operator()(Context* context, Arg1 arg1, Arg2 arg2) { 
		return (context->*(_method))(forward(arg1), forward(arg2));
	}


	template<typename Context, typename Arg1, typename Arg2, typename Arg3>
	return_type operator()(Context* context, Arg1 arg1, Arg2 arg2, Arg3 arg3) { 
		return (context->*(_method))(forward(arg1), forward(arg2), forward(arg3));
	}


	template<typename Context, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
	return_type operator()(Context* context, Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4) { 
		return (context->*(_method))(forward(arg1), forward(arg2), forward(arg3), forward(arg4));
	}

private:
	F _method;
};


} //mem_fn_
} //functional
} //lbb


#endif /* LBB_FUNCTIONAL_MEM_FN_MEM_FN__MEM_FN_T_H_ */
