#ifndef LBB_FUNCTIONAL_MEM_FN_MEM_FN__PTR_H_
#define LBB_FUNCTIONAL_MEM_FN_MEM_FN__PTR_H_


#include <lbb/smartptr/unique_ptr.h>
#include <lbb/smartptr/shared_ptr.h>

namespace lbb { 
namespace functional { 
namespace mem_fn_ { 

template<typename T>
T* get_ptr(T& context) { 
	return &context;
}

template<typename T>
T* get_ptr(smartptr::shared_ptr<T>& context) { 
	return context.get();
}

template<typename T>
T* get_ptr(smartptr::unique_ptr<T>& context) { 
	return context.get();
}

} //mem_fn_
} //functional
} //lbb

#endif /* LBB_FUNCTIONAL_MEM_FN_MEM_FN__PTR_H_ */





