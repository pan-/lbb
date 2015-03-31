#ifndef LBB_SMARTPTR_H_
#define LBB_SMARTPTR_H_

#include "smartptr/unique_ptr.h"
#include "smartptr/deleter.h"
#include "smartptr/shared_ptr.h"
#include "smartptr/make_shared.h"


namespace lbb { 

//importing unique_ptr
using ::lbb::smartptr::unique_ptr;

//import deleter
using ::lbb::smartptr::free_function_deleter;

//import c_free_deleter
using ::lbb::smartptr::c_free_deleter;

//import shared_ptr
using ::lbb::smartptr::shared_ptr;

//import make_shared
using ::lbb::smartptr::make_shared;

}

#endif /* LBB_SMARTPTR_H_ */