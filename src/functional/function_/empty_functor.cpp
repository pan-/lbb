#include "lbb/functional/function_/functor_manager.h"
#include "lbb/functional/function_/functor.h"

namespace lbb { 
namespace functional { 
namespace function_ { 

void empty_copy(functor& dest, const functor& src) {  
	dest._manager = src._manager;
}

void empty_destroy(functor&) { }

const functor_manager empty_functor_manager = { 
	empty_destroy,
	empty_copy
};



}
}
}
