#ifndef LBB_FUNCTIONAL_FUNCTION__FUNCTOR_H_
#define LBB_FUNCTIONAL_FUNCTION__FUNCTOR_H_

#include "functor_storage.h"
#include "functor_manager.h"
#include "functor_allocation.h"


namespace lbb { 
namespace functional { 
namespace function_ { 


extern const functor_manager empty_functor_manager;

struct functor { 
	functor() : _manager(&empty_functor_manager) { } 

	template<typename T>
	functor(const T& func);

	functor(const functor& other) { 
		other._manager->copy(*this, other);
	}

	~functor() { 
		_manager->destroy(*this);
	}

	functor& operator=(const functor& other) {
		_manager->destroy(*this);
		other._manager->copy(*this, other);
		return *this;
	}

	functor_storage 		_storage;
	const functor_manager* 	_manager;
};

}
}
}

#include "functor_imp.h"


#endif /* LBB_FUNCTIONAL_FUNCTION__FUNCTOR_H_ */