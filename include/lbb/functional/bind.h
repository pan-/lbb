#ifndef LBB_FUNCTIONAL_BIND_H_
#define LBB_FUNCTIONAL_BIND_H_



#include <lbb/utility.h>
#include "bind_/bind_t.h"


/**
 * bind -> F + args (optionnel)
 * bind_2 -> F + args et placeholder pour les arguments manquant
 * construction de la liste des arguments
 * construction de la structure de binding
 */

namespace lbb { 
namespace functional { 

template<typename F, typename A1>
bind_::bind_t<F, A1> 
bind(F func, A1 arg1) { 
	return bind_::bind_t<F, A1> (
		func, 
		make_tuple(arg1)
	);
}

template<typename F, typename A1, typename A2>
bind_::bind_t<F, A1, A2> 
bind(F func, A1 arg1, A2 arg2) { 
	return bind_::bind_t<F, A1, A2> (
		func, 
		make_tuple(arg1, arg2)
	);
}

template<typename F, typename A1, typename A2, typename A3>
bind_::bind_t<F, A1, A2, A3> 
bind(F func, A1 arg1, A2 arg2, A3 arg3) { 
	return bind_::bind_t<F, A1, A2, A3> (
		func, 
		make_tuple(arg1, arg2, arg3)
	);
}

template<typename F, typename A1, typename A2, typename A3, typename A4>
bind_::bind_t<F, A1, A2, A3, A4> 
bind(F func, A1 arg1, A2 arg2, A3 arg3, A4 arg4) { 
	return bind_::bind_t<F, A1, A2, A3, A4> (
		func, 
		make_tuple(arg1, arg2, arg3, arg4)
	);
}


template<typename F, typename A1, typename A2, typename A3, typename A4, typename A5>
bind_::bind_t<F, A1, A2, A3, A4, A5> 
bind(F func, A1 arg1, A2 arg2, A3 arg3, A4 arg4, A5 arg5) { 
	return bind_::bind_t<F, A1, A2, A3, A4, A5> (
		func, 
		make_tuple(arg1, arg2, arg3, arg4, arg5)
	);
}


}
}

#endif /* LBB_FUNCTIONAL_BIND_H_ */