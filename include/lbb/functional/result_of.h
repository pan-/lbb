#ifndef LBB_FUNCTIONAL_RESULT_OF_H_
#define LBB_FUNCTIONAL_RESULT_OF_H_

#include <lbb/meta.h>

namespace lbb { 
namespace functional { 


namespace result_of_imp_ { 

using namespace lbb::meta;
using namespace meta::introspection_;
using namespace meta::introspection_::signature_;

template<typename F> 
struct result_type_of_ { 
	typedef typename F::result_type type;
};

}

template<typename T>
struct result_of;


template<typename F>
struct result_of<F()> : 
	result_of_imp_::select_type_<result_of_imp_::is_signature_<F>::value,
		result_of_imp_::get_return_type_<F>, 
		result_of_imp_::result_type_of_<F> >::type { };


template<typename F, typename A1>
struct result_of<F(A1)> : 
	result_of_imp_::select_type_<result_of_imp_::is_signature_<F>::value,
		result_of_imp_::get_return_type_<F>, 
		result_of_imp_::result_type_of_<F> >::type { };	


template<typename F, typename A1, typename A2>
struct result_of<F(A1, A2)> : 
	result_of_imp_::select_type_<result_of_imp_::is_signature_<F>::value,
		result_of_imp_::get_return_type_<F>, 
		result_of_imp_::result_type_of_<F> >::type { };	

template<typename F, typename A1, typename A2, typename A3>
struct result_of<F(A1, A2, A3)> : 
	result_of_imp_::select_type_<result_of_imp_::is_signature_<F>::value,
		result_of_imp_::get_return_type_<F>, 
		result_of_imp_::result_type_of_<F> >::type { };	

template<typename F, typename A1, typename A2, typename A3, typename A4>
struct result_of<F(A1, A2, A3, A4)> : 
	result_of_imp_::select_type_<result_of_imp_::is_signature_<F>::value,
		result_of_imp_::get_return_type_<F>, 
		result_of_imp_::result_type_of_<F> >::type { };	

template<typename F, typename A1, typename A2, typename A3, typename A4, typename A5>
struct result_of<F(A1, A2, A3, A4, A5)> : 
	result_of_imp_::select_type_<result_of_imp_::is_signature_<F>::value,
		result_of_imp_::get_return_type_<F>, 
		result_of_imp_::result_type_of_<F> >::type { };	


} // functional
} // lbb

#endif /* LBB_FUNCTIONAL_RESULT_OF_H_ */