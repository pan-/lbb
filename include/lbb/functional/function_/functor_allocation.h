#ifndef LBB_FUNCTIONAL_FUNCTION__FUNCTOR_ALLOCATION_H_
#define LBB_FUNCTIONAL_FUNCTION__FUNCTOR_ALLOCATION_H_

#include <iostream>
#include <lbb/meta.h>
#include "functor_storage.h"


namespace lbb { 
namespace functional { 
namespace function_ { 

//tag dispatch for functor manager implementation
enum functor_allocation_tag { 
	in_place_allocation_tag,
	heap_allocation_tag
};

//indicate if the implementation should be inplace or not
template<typename T>
struct allocation_tag_of_  { 
	static const functor_allocation_tag value = 
		(sizeof(functor_storage) >= sizeof(lbb::aligned_union<T, void*>)) ? 
			in_place_allocation_tag : 
			heap_allocation_tag;
};


//init inplace storage
template<typename T>
typename enable_if_<allocation_tag_of_<T>::value == in_place_allocation_tag, void>::type  
init_storage(functor_storage& storage, const T& func) { 
	new (&storage) T(func);
}


//init heap allocation based
template<typename T>
typename enable_if_<allocation_tag_of_<T>::value == heap_allocation_tag, void>::type  
init_storage(functor_storage& storage, const T& func) { 
	*(storage.as<T**>()) = new T(func);
}




}
}
}


#endif /* LBB_FUNCTIONAL_FUNCTION__FUNCTOR_ALLOCATION_H_ */


