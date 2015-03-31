#ifndef LBB_FUNCTIONAL_FUNCTION__FUNCTOR_REF_H_
#define LBB_FUNCTIONAL_FUNCTION__FUNCTOR_REF_H_

#include <lbb/meta.h>
#include "functor_allocation.h"
#include "functor.h"


namespace lbb { 
namespace functional { 
namespace function_ { 

//return a reference to the functor for heap allocated or in place functor

template<typename T>
typename enable_if_<allocation_tag_of_<T>::value == in_place_allocation_tag, T&>::type  	
functor_ref(functor& f) { 
	return *static_cast<T*>(&f._storage);
}

template<typename T>
typename enable_if_<allocation_tag_of_<T>::value == in_place_allocation_tag, const T&>::type  	
const_functor_ref(const functor& f) { 
	return *static_cast<const T*>(&f._storage);
}


template<typename T>
typename enable_if_<allocation_tag_of_<T>::value == heap_allocation_tag, T&>::type  	
functor_ref(functor& f) { 
	return **(static_cast<T**>(&f._storage));
}

template<typename T>
typename enable_if_<allocation_tag_of_<T>::value == heap_allocation_tag, const T&>::type  	
const_functor_ref(const functor& f) { 
	return **(static_cast<const T* const *>(&f._storage));
}


}
}
}


#endif /* LBB_FUNCTIONAL_FUNCTION__FUNCTOR_REF_H_ */