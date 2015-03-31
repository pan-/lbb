#ifndef LBB_UTILITY_H_
#define LBB_UTILITY_H_

#include "utility/tuple.h"
#include "utility/make_tuple.h"
#include "utility/tuple_get.h"
#include "utility/tie.h"
#include "utility/aligned_union.h"
#include "utility/safe_bool.h"
#include "utility/scoped.h"
#include "utility/not_copyable.h"
#include "utility/move.h"


namespace lbb { 

//importing tuple
using ::lbb::utility::tuple;

//importing make_tuple
using ::lbb::utility::make_tuple;

//importing get for tuple
using ::lbb::utility::get;

//importing tie for tuple
using ::lbb::utility::tie;

//import aligned_union
using ::lbb::utility::aligned_union;

//import safe bool
using ::lbb::utility::safe_bool;

//import scoped
using ::lbb::utility::scoped;

//import not_copyable
using ::lbb::utility::not_copyable;

//import movable
using ::lbb::utility::movable;
using ::lbb::utility::is_rvalue_;
using ::lbb::utility::is_rvalue_;
using ::lbb::utility::rvalue_of_;
using ::lbb::utility::rvalue_reference_of_;
using ::lbb::utility::is_movable_;
using ::lbb::utility::move;
using ::lbb::utility::forward;

}

#endif /* LBB_UTILITY_H_ */