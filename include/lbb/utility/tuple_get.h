#ifndef LBB_UTILITY_TUPLE__TUPLE_GET_H_
#define LBB_UTILITY_TUPLE__TUPLE_GET_H_

#include <lbb/meta.h>

#include "tuple_/tuple_imp.h"
#include "tuple_/tuple_leaf.h"

namespace lbb {
namespace utility {


template<size_t Index, typename TupleType>
typename disable_if_<is_empty_<typename type_list_::at_<Index, typename TupleType::types_list>::type>::value, 
typename type_list_::at_<Index, typename TupleType::types_list>::type&>::type
get(TupleType& tup) { 
	return ((typename tuple_::leaf_at_<Index, typename TupleType::types_list>::type&) tup).get();
}

template<size_t Index, typename TupleType>
typename disable_if_<is_empty_<typename type_list_::at_<Index, typename TupleType::types_list>::type>::value, 
const typename type_list_::at_<Index, typename TupleType::types_list>::type&>::type
get(const TupleType& tup) { 
	return ((const typename tuple_::leaf_at_<Index, typename TupleType::types_list>::type&) tup).get();
}

template<size_t Index, typename TupleType>
typename enable_if_<is_empty_<typename type_list_::at_<Index, typename TupleType::types_list>::type>::value, 
typename type_list_::at_<Index, typename TupleType::types_list>::type>::type
get(const TupleType& tup) { 
	return ((const typename tuple_::leaf_at_<Index, typename TupleType::types_list>::type&) tup).get();
}


}  // namespace utility
}  // namespace lbb


#endif /* LBB_UTILITY_TUPLE__TUPLE_GET_H_ */