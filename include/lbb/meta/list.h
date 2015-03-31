#ifndef LBB_META_LIST_H_
#define LBB_META_LIST_H_

#include <cstddef>

#include "meta_type.h"
#include "static_assert.h"
#include "traits.h"

namespace lbb {
namespace meta {


namespace type_list_ {

struct nil_ : meta_type_<nil_> { };



template<typename H, class T = nil_>
struct node_ /* : meta_type_<node_<H, T> > */
{
	typedef node_<H, T> type;
	typedef H Head;
	typedef T Tail;
};

template<typename H, class Foo>
struct node_<H, node_<nil_, Foo> > /* : meta_type_<node_<H, nil_> > */
{
	typedef node_<H, nil_> type;
	typedef H Head;
	typedef nil_ Tail;
};

template<class Tail>
struct node_<nil_, Tail> /* : meta_type_<node_<H, T> > */
{
	typedef nil_ type;
};



template<typename T>
struct is_list_ : false_ { };

template<typename H, typename T>
struct is_list_<node_<H, T> > : true_ { };



template<typename T>
struct head_;

template<typename H, typename T>
struct head_<node_<H, T> > : meta_type_<H> { };



template<typename T>
struct tail_;

template<typename H, typename T>
struct tail_<node_<H, T> > : meta_type_<T> { };




template<typename T>
struct next_;

template<typename H, typename T>
struct next_<node_<H, T> > : meta_type_<T> { };




template<typename T>
struct size_ : unsigned_int_<0> { };

template<typename Head, typename Tail>
struct size_<node_<Head, Tail> > : unsigned_int_<1 + size_<Tail>::value> { };

template<>
struct size_<nil_> : unsigned_int_<0>  { };




template<typename L>
struct end_ {
	LBB_COMPILE_ASSERT(1, trying_to_apply_end_to_an_invalid_type);
};

template<typename H, typename T>
struct end_<node_<H, T> > {
	typedef typename end_<T>::type type;
};

template<typename H>
struct end_<node_<H, nil_> > {
	typedef H type;
};


template<typename L, typename N>
struct push_back_;


//Specialization for
template<typename H, typename T, typename N>
struct push_back_<node_<H, T>, N> {
	typedef node_<H, typename push_back_<T, N>::type> type;
};

template<typename H, typename T>
struct push_back_<node_<H, T>, nil_> {
	typedef node_<H, T> type;
};


template<typename H, typename N>
struct push_back_<node_<H, nil_>, N> {
	typedef node_<H, node_<N> > type;
};

template<typename H, typename N, typename NT>
struct push_back_<node_<H, nil_>, node_<N, NT> > {
	typedef node_<H, node_<N, NT> > type;
};


template<typename H>
struct push_back_<node_<H, nil_>, nil_> {
	typedef node_<H, nil_ > type;
};



//Make list with 40 args ...
template<typename T0, typename T1 = nil_, typename T2 = nil_, typename T3 = nil_,
		typename T4 = nil_, typename T5 = nil_, typename T6 = nil_, typename T7 = nil_,
		typename T8 = nil_, typename T9 = nil_, typename T10 = nil_, typename T11 = nil_,
		typename T12 = nil_, typename T13 = nil_, typename T14 = nil_, typename T15 = nil_,
		typename T16 = nil_, typename T17 = nil_, typename T18 = nil_, typename T19 = nil_,
		typename T20 = nil_, typename T21 = nil_, typename T22 = nil_, typename T23 = nil_,
		typename T24 = nil_, typename T25 = nil_, typename T26 = nil_, typename T27 = nil_,
		typename T28 = nil_, typename T29 = nil_, typename T30 = nil_, typename T31 = nil_,
		typename T32 = nil_, typename T33 = nil_, typename T34 = nil_, typename T35 = nil_,
		typename T36 = nil_, typename T37 = nil_, typename T38 = nil_, typename T39 = nil_>
class create_
{
private:
	typedef typename node_<T39>::type L39;
	typedef typename node_<T38, L39>::type L38;
	typedef typename node_<T37, L38>::type L37;
	typedef typename node_<T36, L37>::type L36;
	typedef typename node_<T35, L36>::type L35;
	typedef typename node_<T34, L35>::type L34;
	typedef typename node_<T33, L34>::type L33;
	typedef typename node_<T32, L33>::type L32;
	typedef typename node_<T31, L32>::type L31;
	typedef typename node_<T30, L31>::type L30;

	typedef typename node_<T29, L30>::type L29;
	typedef typename node_<T28, L29>::type L28;
	typedef typename node_<T27, L28>::type L27;
	typedef typename node_<T26, L27>::type L26;
	typedef typename node_<T25, L26>::type L25;
	typedef typename node_<T24, L25>::type L24;
	typedef typename node_<T23, L24>::type L23;
	typedef typename node_<T22, L23>::type L22;
	typedef typename node_<T21, L22>::type L21;
	typedef typename node_<T20, L21>::type L20;

	typedef typename node_<T19, L20>::type L19;
	typedef typename node_<T18, L19>::type L18;
	typedef typename node_<T17, L18>::type L17;
	typedef typename node_<T16, L17>::type L16;
	typedef typename node_<T15, L16>::type L15;
	typedef typename node_<T14, L15>::type L14;
	typedef typename node_<T13, L14>::type L13;
	typedef typename node_<T12, L13>::type L12;
	typedef typename node_<T11, L12>::type L11;
	typedef typename node_<T10, L11>::type L10;

	typedef typename node_<T9, L10>::type L9;
	typedef typename node_<T8, L9>::type L8;
	typedef typename node_<T7, L8>::type L7;
	typedef typename node_<T6, L7>::type L6;
	typedef typename node_<T5, L6>::type L5;
	typedef typename node_<T4, L5>::type L4;
	typedef typename node_<T3, L4>::type L3;
	typedef typename node_<T2, L3>::type L2;
	typedef typename node_<T1, L2>::type L1;
	typedef typename node_<T0, L1>::type L0;

public:
	typedef L0 type;

//	typedef typename node_<T0, typename node_<T1, typename node_<T2, typename node_<T3, typename node_<T4, typename node_<T5, typename node_<T6, typename node_<T7, typename node_<T8, typename node_<T9>::type >::type >::type >::type >::type >::type >::type >::type >::type >::type type;
};


/**
 * Check if a list contain an element or not
 */
template<typename Type, typename List>
struct contains_ :
	bool_<((is_same_type_<Type, typename List::Head>::value == true) ?
			true :
			contains_<Type, typename List::Tail>::value )> { };

template<typename Type>
struct contains_<Type, nil_ > : false_ {};


/**
 * Check if a list has duplicates
 */
template<typename List>
struct has_duplicates_  :
	bool_<contains_<typename List::Head, typename List::Tail>::value ||
		has_duplicates_<typename List::Tail>::value> { };


template<>
struct has_duplicates_<nil_> : false_ { };




/**
 * Return the index of a type in a type list.
 * static assert if the type is not in the list
 */

template<typename T, typename List>
struct index_of_ :
	unsigned_int_<((is_same_type_<T, typename List::Head>::value == true) ?
			0 :
			1 + index_of_<T, typename List::Tail>::value)> { };

template<typename T>
struct index_of_<T, nil_> : unsigned_int_<0> { };





template<size_t index, typename List>
struct at_ : meta_type_<typename at_<index - 1, typename List::Tail>::type> { };

template<typename List>
struct at_<0, List> : meta_type_<typename List::Head> { };

template<>
struct at_<0, nil_> : meta_type_<nil_> { };

template<size_t index>
struct at_<index, nil_> : meta_type_<nil_> { };

}

}
}


#endif /* LBB_META_LIST_H_ */
