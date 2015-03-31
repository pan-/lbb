#ifndef LBB_FUNCTIONAL_BIND__PLACEHOLDER_H_
#define LBB_FUNCTIONAL_BIND__PLACEHOLDER_H_

#include <lbb/meta.h>

namespace lbb { 
namespace functional { 
namespace bind_ { 

/**
 * A place holder is an empty tag for parameters in bind expressions
 */
template<int N>
struct placeholder_t {
	placeholder_t() { }

	placeholder_t(const placeholder_t&) { }

	placeholder_t get() {  return placeholder_t<N>(); }
};

/**
 * traits which return true_ if T is a placeholder and false otherwise
 */
template<typename T>
struct is_placeholder_ : false_ { };

template<int N>
struct is_placeholder_<placeholder_t<N> > : true_ { };

/**
 * ordered list of placeholder types 
 */
typedef type_list_::create_<
	placeholder_t<1>, 
	placeholder_t<2>, 
	placeholder_t<3>,
	placeholder_t<4>,
	placeholder_t<5> 
>::type placeholder_list_t;

}
}
}

#endif /* LBB_FUNCTIONAL_BIND__PLACEHOLDER_H_ */