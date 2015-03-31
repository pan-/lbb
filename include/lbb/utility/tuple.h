#ifndef LBB_UTILITY_TUPLE_H_
#define LBB_UTILITY_TUPLE_H_

#include <lbb/meta.h>
#include "tuple_/tuple_imp.h"

namespace lbb {
namespace utility {


/**
 * Class template std::tuple is a fixed-size collection of heterogeneous values. 
 * It is a generalization of std::pair.
 * Tuples have value semantic and can be copy constructed/assigned
 */
template<typename T0 = type_list_::nil_, typename T1 = type_list_::nil_, 
	typename T2 = type_list_::nil_, typename T3 = type_list_::nil_, typename T4 = type_list_::nil_>
class tuple : tuple_::tuple_imp<typename type_list_::create_<T0, T1, T2, T3, T4>::type>{ 

public:
	typedef typename type_list_::create_<T0, T1, T2, T3, T4>::type types_list;

	tuple() : tuple_::tuple_imp<types_list>() { }

	tuple(T0 val0) : tuple_::tuple_imp<types_list>(val0) { }

	tuple(T0 val0, T1 val1) : tuple_::tuple_imp<types_list>(val0, val1) { }

	tuple(T0 val0, T1 val1, T2 val2) : tuple_::tuple_imp<types_list>(val0, val1, val2) { }

	tuple(T0 val0, T1 val1, T2 val2, T3 val3) : 
		tuple_::tuple_imp<types_list>(val0, val1, val2, val3) { }

	tuple(T0 val0, T1 val1, T2 val2, T3 val3, T4 val4) : 
		tuple_::tuple_imp<types_list>(val0, val1, val2, val3, val4) { }
};


}  // namespace utility
}  // namespace lbb




#endif /* LBB_UTILITY_TUPLE_H_ */
