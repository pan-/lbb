#ifndef LBB_FUNCTIONAL_FUNCTION__FUNCTOR_MANAGER_H_
#define LBB_FUNCTIONAL_FUNCTION__FUNCTOR_MANAGER_H_

namespace lbb { 
namespace functional { 
namespace function_ { 

class functor;

struct functor_manager { 
	void (* const destroy)(functor&);	
	void (* const copy)(functor&, const functor&);
};


}
}
}


#endif /* LBB_FUNCTIONAL_FUNCTION__FUNCTOR_MANAGER_H_ */