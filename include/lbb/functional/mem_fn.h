#ifndef LBB_FUNCTIONAL_MEM_FN_H_
#define LBB_FUNCTIONAL_MEM_FN_H_

#include "mem_fn_/ptr.h"
#include "mem_fn_/mem_fn_t.h"

namespace lbb { 
namespace functional { 

/*
 * Function template std::mem_fn generates wrapper objects for pointers to members, 
 * which can store, copy, and invoke a pointer to member. Both references and pointers 
 * (including smart pointers) to an object can be used when invoking a std::mem_fn.
 */
template<typename F>
mem_fn_::mem_fn_t<F> mem_fn(F function) { 
	return mem_fn_::mem_fn_t<F>(function);
}


template<typename F>
struct mem_fn_of_  { 
	typedef mem_fn_::mem_fn_t<F> type;
};


}
}

#endif /* LBB_FUNCTIONAL_MEM_FN_H_ */







