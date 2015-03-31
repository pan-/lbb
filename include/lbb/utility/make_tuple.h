#ifndef LBB_UTILITY_MAKE_TUPLE_H_
#define LBB_UTILITY_MAKE_TUPLE_H_

#include "tuple.h"

namespace lbb {
namespace utility {

/**
 * construct an empty tuple 
 */
inline tuple<> make_tuple() { 
	return tuple<>();
}

/**
 * construct a tuple of 
 */
template<typename T0>
tuple<T0> make_tuple(T0 val0) { 
	return tuple<T0>(val0);
}

template<typename T0, typename T1>
tuple<T0, T1> make_tuple(T0 val0, T1 val1) { 
	return tuple<T0, T1>(val0, val1);
}

template<typename T0, typename T1, typename T2>
tuple<T0, T1, T2> make_tuple(T0 val0, T1 val1, T2 val2) { 
	return tuple<T0, T1, T2>(val0, val1, val2);
}

template<typename T0, typename T1, typename T2, typename T3>
tuple<T0, T1, T2, T3> make_tuple(T0 val0, T1 val1, T2 val2, T3 val3) { 
	return tuple<T0, T1, T2, T3>(val0, val1, val2, val3);
}

template<typename T0, typename T1, typename T2, typename T3, typename T4>
tuple<T0, T1, T2, T3, T4> make_tuple(T0 val0, T1 val1, T2 val2, T3 val3, T4 val4) { 
	return tuple<T0, T1, T2, T3, T4>(val0, val1, val2, val3, val4);
}




}  // namespace utility
}  // namespace lbb


#endif /* LBB_UTILITY_MAKE_TUPLE_H_ */