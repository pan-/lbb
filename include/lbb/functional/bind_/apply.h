#ifndef LBB_FUNCTIONAL_BIND__APPLY_H_
#define LBB_FUNCTIONAL_BIND__APPLY_H_

#include <lbb/meta.h>

#include "application_args.h"

#include "as_function.h"

#include <lbb/utility.h>
#include <lbb/functional/result_of.h>


namespace lbb { 
namespace functional { 
namespace bind_ { 

using namespace meta::introspection_::signature_;

template<typename F, typename ApplicationArgs>
typename result_of<F()>::type 
apply(F& func, tuple<>& bounded_args, ApplicationArgs& application) { 
	return as_function(func)();
}

template<typename F, typename ApplicationArgs, typename A1>
typename result_of<F(A1)>::type
apply(F& func, tuple<A1>& bounded_args, ApplicationArgs& application) { 
	return as_function(func)(
		application[get<0>(bounded_args)]
	);
}

template<typename F, typename ApplicationArgs, typename A1, typename A2>
typename result_of<F(A1, A2)>::type
apply(F& func, tuple<A1, A2>& bounded_args, ApplicationArgs& application) { 
	return as_function(func)(
		application[get<0>(bounded_args)], 
		application[get<1>(bounded_args)]
	);
}

template<typename F, typename ApplicationArgs, typename A1, typename A2, typename A3>
typename result_of<F(A1, A2, A3)>::type
apply(F& func, tuple<A1, A2, A3>& bounded_args, ApplicationArgs& application) { 
	return as_function(func)(
		application[get<0>(bounded_args)], 
		application[get<1>(bounded_args)], 
		application[get<2>(bounded_args)]
	);
}

template<typename F, typename ApplicationArgs, typename A1, typename A2, typename A3, typename A4>
typename result_of<F(A1, A2, A3, A4)>::type
apply(F& func, tuple<A1, A2, A3, A4>& bounded_args, ApplicationArgs& application) { 
	return as_function(func)(
		application[get<0>(bounded_args)], 
		application[get<1>(bounded_args)], 
		application[get<2>(bounded_args)], 
		application[get<3>(bounded_args)]
	);
}

template<typename F, typename ApplicationArgs, typename A1, typename A2, typename A3, typename A4, typename A5>
typename result_of<F(A1, A2, A3, A4, A5)>::type
apply(F& func, tuple<A1, A2, A3, A4, A5>& bounded_args, ApplicationArgs& application) { 
	return as_function(func)(
		application[get<0>(bounded_args)], 
		application[get<1>(bounded_args)], 
		application[get<2>(bounded_args)], 
		application[get<3>(bounded_args)], 
		application[get<4>(bounded_args)]
	);
}



}
}
}




#endif /* LBB_FUNCTIONAL_BIND__APPLY_H_ */