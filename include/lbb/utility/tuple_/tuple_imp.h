#ifndef LBB_UTILITY_TUPLE__TUPLE_IMP_H_
#define LBB_UTILITY_TUPLE__TUPLE_IMP_H_

#include <lbb/meta.h>
#include "tuple_leaf.h"

namespace lbb {
namespace utility {
namespace tuple_ {

//compute the type at the given index of the type list
template<size_t Index, typename Types>
struct leaf_at_ { 
	typedef leaf<Index, typename type_list_::at_<Index, Types>::type> type;
};


/** 
 * Compile function which return the element type and the leaf type of
 * of an element of a tuple type list.
 */
template<size_t Index, typename Types>
struct element_at_ { 
	typedef typename type_list_::at_<Index, Types>::type element_type;
	typedef typename leaf_at_<Index, Types>::type leaf_type;
};


template<typename Types, size_t TypesCount = type_list_::size_<Types>::value>
class tuple_imp;


//tuple of 0 element
template<>
class tuple_imp<type_list_::nil_, 0>  { 
public:
	void swap(tuple_imp&) { }
};


//tuple of one element
template<typename Types>
class tuple_imp<Types, 1> : leaf_at_<0, Types>::type { 
public:
	typedef typename type_list_::at_<0, Types>::type T0;
	typedef typename leaf_at_<0, Types>::type Leaf0;

	tuple_imp(T0 val0 = T0()) : 
		Leaf0(val0)
	{ }
};

//tuple of two element
template<typename Types>
class tuple_imp<Types, 2> : element_at_<0, Types>::leaf_type, element_at_<1, Types>::leaf_type { 
public:
	typedef typename element_at_<0, Types>::element_type 	T0;
	typedef typename element_at_<0, Types>::leaf_type 		L0;	

	typedef typename element_at_<1, Types>::element_type 	T1;	
	typedef typename element_at_<1, Types>::leaf_type 		L1;		

	tuple_imp(T0 val0 = T0(), T1 val1 = T1()) : 
		L0(val0),
		L1(val1)
	{ }
};


// tuple of 3 elements 
template<typename Types>
class tuple_imp<Types, 3> : 
	element_at_<0, Types>::leaf_type, 
	element_at_<1, Types>::leaf_type, 
	element_at_<2, Types>::leaf_type 	
{ 
public:
	typedef typename element_at_<0, Types>::element_type 	T0;
	typedef typename element_at_<0, Types>::leaf_type 		L0;	

	typedef typename element_at_<1, Types>::element_type 	T1;	
	typedef typename element_at_<1, Types>::leaf_type 		L1;

	typedef typename element_at_<2, Types>::element_type 	T2;	
	typedef typename element_at_<2, Types>::leaf_type 		L2;		


	tuple_imp(T0 val0 = T0(), T1 val1 = T1(), T2 val2 = T2()) : 
		L0(val0),
		L1(val1),
		L2(val2)
	{ }
};



// tuple of 4 elements 
template<typename Types>
class tuple_imp<Types, 4> : 
	element_at_<0, Types>::leaf_type, 
	element_at_<1, Types>::leaf_type, 
	element_at_<2, Types>::leaf_type,
	element_at_<3, Types>::leaf_type 	 	
{ 
public:
	typedef typename element_at_<0, Types>::element_type 	T0;
	typedef typename element_at_<0, Types>::leaf_type 		L0;	

	typedef typename element_at_<1, Types>::element_type 	T1;	
	typedef typename element_at_<1, Types>::leaf_type 		L1;

	typedef typename element_at_<2, Types>::element_type 	T2;	
	typedef typename element_at_<2, Types>::leaf_type 		L2;	

	typedef typename element_at_<3, Types>::element_type 	T3;	
	typedef typename element_at_<3, Types>::leaf_type 		L3;			


	tuple_imp(T0 val0 = T0(), T1 val1 = T1(), T2 val2 = T2(), T3 val3 = T3()) : 
		L0(val0),
		L1(val1),
		L2(val2),
		L3(val3)
	{ }
};


// tuple of 5 elements 
template<typename Types>
class tuple_imp<Types, 5> : 
	element_at_<0, Types>::leaf_type, 
	element_at_<1, Types>::leaf_type, 
	element_at_<2, Types>::leaf_type,
	element_at_<3, Types>::leaf_type, 	 	
	element_at_<4, Types>::leaf_type 	 		
{ 
public:
	typedef typename element_at_<0, Types>::element_type 	T0;
	typedef typename element_at_<0, Types>::leaf_type 		L0;	

	typedef typename element_at_<1, Types>::element_type 	T1;	
	typedef typename element_at_<1, Types>::leaf_type 		L1;

	typedef typename element_at_<2, Types>::element_type 	T2;	
	typedef typename element_at_<2, Types>::leaf_type 		L2;	

	typedef typename element_at_<3, Types>::element_type 	T3;	
	typedef typename element_at_<3, Types>::leaf_type 		L3;	

	typedef typename element_at_<4, Types>::element_type 	T4;	
	typedef typename element_at_<4, Types>::leaf_type 		L4;				


	tuple_imp(T0 val0 = T0(), T1 val1 = T1(), T2 val2 = T2(), T3 val3 = T3(), T4 val4 = T4()) : 
		L0(val0),
		L1(val1),
		L2(val2),
		L3(val3),
		L4(val4)
	{ }
};



}  // namespace tuple_
}  // namespace utility
}  // namespace lbb



#endif /* LBB_UTILITY_TUPLE__TUPLE_IMP_H_ */