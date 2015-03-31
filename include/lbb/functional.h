#ifndef LBB_FUNCTIONAL_H_
#define LBB_FUNCTIONAL_H_


#include "functional/result_of.h"
#include "functional/mem_fn.h"
#include "functional/placeholders.h"
#include "functional/bind.h"
#include "functional/reference_wrapper.h"

#include "functional/function.h"


namespace lbb { 

//importing result of
using ::lbb::functional::result_of;	

//importing mem_fn
using ::lbb::functional::mem_fn;

//importing mem_fn_of_
using ::lbb::functional::mem_fn_of_;

//import placeholders
namespace placeholders { 
	using namespace functional::placeholders;
}

//import bind
using ::lbb::functional::bind;

//import reference_wrapper 
using ::lbb::functional::reference_wrapper;
using ::lbb::functional::ref;
using ::lbb::functional::cref;

//import function
using ::lbb::functional::function;

}

#endif /* LBB_FUNCTIONAL_H_ */