#ifndef LBB_ALIGNED_UNION__STORAGE_COMPUTATION_H_
#define LBB_ALIGNED_UNION__STORAGE_COMPUTATION_H_

#include <cstddef>
#include <lbb/meta.h>

namespace lbb {
namespace utility {

namespace aligned_union_ {

/**
 * dummy wrapper used to calculate size and alignement of primitive types inside a struct
 */
template<typename T>
struct in_struct_ {
	T e;
};

/**
 * Forward declaration which doesn't exist
 */
class anonymous_declaration_;

/**
 * List of all primitives types (used for alignement calculation)
 */
typedef type_list_::create_<
        char,
        short int,
        int,
        long int,
        float,
        double,
        long double,
        char*,
        short int*,
        int*,
        long int*,
        float*,
        double*,
        long double*,
        void*,
        anonymous_declaration_ (*)(anonymous_declaration_),
        anonymous_declaration_* anonymous_declaration_::*,
        anonymous_declaration_ (anonymous_declaration_::*)(anonymous_declaration_),
        in_struct_<char>,
        in_struct_<short int>,
        in_struct_<int>,
        in_struct_<long int>,
        in_struct_<float>,
        in_struct_<double>,
        in_struct_<long double>,
        in_struct_<char*>,
        in_struct_<short int*>,
        in_struct_<int*>,
        in_struct_<long int*>,
        in_struct_<float*>,
        in_struct_<double*>,
        in_struct_<long double*>,
        in_struct_<void*>,
        in_struct_<anonymous_declaration_ (*)(anonymous_declaration_)>,
        in_struct_<anonymous_declaration_* anonymous_declaration_::*>,
        in_struct_<anonymous_declaration_ (anonymous_declaration_::*)(anonymous_declaration_)>
        >::type
      all_aligns_list_;




/**
 * Return the maximum size used by the bigger type of the list
 */
template<typename T>
struct compute_biggest_size_;

template<typename Head, typename Tail>
class compute_biggest_size_<type_list_::node_<Head, Tail> > {
	static const size_t head_result = sizeof(Head);
	static const size_t tail_result = compute_biggest_size_<Tail>::result;

public:
	static const unsigned int result = (head_result > tail_result) ? head_result : tail_result;
};

template<>
struct compute_biggest_size_<type_list_::nil_> {
	static const size_t result = 0;
};


/**
 * Creation of the list of types used in alignement
 */
template<class T, size_t max_size>
struct make_align_list_imp_;


template<class T, size_t max_size>
struct make_align_list_imp_ {
	typedef typename T::Head Head;
	typedef typename T::Tail Tail;

	typedef typename make_align_list_imp_<Tail, max_size>::type TailResult;


	//result ...

	typedef typename select_type_<sizeof(Head) <= max_size,
									type_list_::node_<Head, TailResult>,
									TailResult>::type type;
};


template<size_t max_size>
struct make_align_list_imp_<type_list_::nil_, max_size> {
	typedef type_list_::nil_ type;
};


/**
 * Create the alignement type list for a type list in input
 */
template<class T>
struct make_align_list_ {
	typedef typename make_align_list_imp_<all_aligns_list_, compute_biggest_size_<T>::result>::type type;
};


/**
 * Create union from a type list (should be POD)
 */
template<typename T>
union union_from_list_ {
	typename T::Head h;
	union_from_list_<typename T::Tail> t;
};

template<>
union union_from_list_<type_list_::nil_> {
};


/**
 * padding type for an input type list
 */
template<typename T>
struct alignment_ {
	union_from_list_<typename make_align_list_<T>::type> pad;
};

}
}
}


#endif /* LBB_ALIGNED_UNION__STORAGE_COMPUTATION_H_ */
