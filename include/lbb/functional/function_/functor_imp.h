#ifndef LBB_FUNCTIONAL_FUNCTION__FUNCTOR_IMP_H_
#define LBB_FUNCTIONAL_FUNCTION__FUNCTOR_IMP_H_

#include "functor_ref.h"

namespace lbb { 
namespace functional { 
namespace function_ { 


//there is two function manager implementations : 
//	- the functor is allocated in place
//	- the functor is heap allocated
template<typename T, functor_allocation_tag tag = allocation_tag_of_<T>::value >
struct functor_manager_imp;


//specialization for in place allocated functor
template<typename T>
struct functor_manager_imp<T, in_place_allocation_tag> {
	//destructor
	static void destroy(functor& instance) {
		static_cast<T*>(&instance._storage)->~T();
	}

	//copy from src to dest
	static void copy(functor& dest, const functor& src) {
		init_storage(dest._storage, const_functor_ref<T>(src));
		dest._manager = src._manager;
	}

	static const functor_manager value;
};


//specialization for heap allocated functor
template<typename T>
struct functor_manager_imp<T, heap_allocation_tag> {
	//destructor
	static void destroy(functor& instance) {
		delete *(instance._storage.as<T**>());
	}

	//copy from src to dest
	static void copy(functor& dest, const functor& src) {
		init_storage(dest._storage, const_functor_ref<T>(src));
		dest._manager = src._manager;
	}

	static const functor_manager value;
};


//functor manager table for in place allocated functor
template<typename T>
const functor_manager functor_manager_imp<T, in_place_allocation_tag>::value = { 
	functor_manager_imp<T>::destroy,
	functor_manager_imp<T>::copy
};


//functor manager table for in place allocated functor
template<typename T>
const functor_manager functor_manager_imp<T, heap_allocation_tag>::value = { 
	functor_manager_imp<T>::destroy,
	functor_manager_imp<T>::copy
};





template<typename T>
functor::functor(const T& func) : _manager(&functor_manager_imp<T>::value) { 
	init_storage(this->_storage, func);
}



}
}
}


#endif /* LBB_FUNCTIONAL_FUNCTION__FUNCTOR_IMP_H_ */