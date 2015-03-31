#ifndef LBB_FUNCTIONAL_FUNCTION__FUNCTOR_STORAGE_H_
#define LBB_FUNCTIONAL_FUNCTION__FUNCTOR_STORAGE_H_

#include <lbb/utility.h>


namespace lbb { 
namespace functional { 
namespace function_ { 


class undefined_class;

typedef void (undefined_class::*undefined_call)();

/**
 * the functoer storage should store at least the maximu size of 
 * a pointer to member function
 */
typedef lbb::aligned_union<undefined_call, void*> functor_storage; 

}
}
}


#endif /* LBB_FUNCTIONAL_FUNCTION__FUNCTOR_STORAGE_H_ */