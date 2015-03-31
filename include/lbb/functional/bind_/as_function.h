#ifndef LBB_FUNCTIONAL_BIND__AS_FUNCTION_H_
#define LBB_FUNCTIONAL_BIND__AS_FUNCTION_H_

#include <lbb/meta.h>
#include <lbb/functional/mem_fn.h>

namespace lbb { 
namespace functional { 
namespace bind_ { 

using namespace meta::introspection_;
using namespace meta::introspection_::signature_;

template<typename F>
typename enable_if_<is_signature_<F>::value && is_member_<F>::value, mem_fn_::mem_fn_t<F> >::type
as_function(F& f) { 
	return mem_fn(f);
}

template<typename F>
typename enable_if_<is_signature_<F>::value && !is_member_<F>::value, F& >::type
as_function(F& f) { 
	return f;
}

template<typename F>
typename enable_if_<!is_signature_<F>::value, F& >::type
as_function(F& f) { 
	return f;
}


}
}
}

#endif /* LBB_FUNCTIONAL_BIND__AS_FUNCTION_H_ */