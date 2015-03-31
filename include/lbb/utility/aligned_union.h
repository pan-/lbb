#ifndef LBB_UTILITY_ALIGNED_UNION_H_
#define LBB_UTILITY_ALIGNED_UNION_H_

#include <lbb/meta.h>
#include "aligned_union_/storage_computation.h"

namespace lbb {
namespace utility {

/**
 * Provide a raw storage usable by an union of POD and non POD types
 *
 * using lbb::aligned_union;
 *
 * aligned_union<int, double> int_or_double;
 *
 * Operations :
 * 		- you can cast the memory block to a specific type using the as function template
 *
 * Note : usable means that the size occupied by the storage is equal to the size of the
 * biggest type of the object and that the alignment fit the most aligned type in the list ...
 */
template<typename T0, typename T1, typename T2 = type_list_::nil_, typename T3 = type_list_::nil_, 
	typename T4 = type_list_::nil_, typename T5 = type_list_::nil_, typename T6 = type_list_::nil_, 
	typename T7 = type_list_::nil_, typename T8 = type_list_::nil_, typename T9 = type_list_::nil_>
class aligned_union {
	/**
	 * Types used to calculate the union
	 */
	typedef typename type_list_::create_<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::type union_types;

	/**
	 * union between data which have the size of the biggest type of the type list
	 * and the type having the alignement properties
	 */
	union {
		char data[aligned_union_::compute_biggest_size_<union_types>::result];
		aligned_union_::alignment_<union_types> padding;
	};

public:
	typedef union_types types_list;

	/**
	 * RW Access to the storage
	 */
	void* get() { return data; }

	/**
	 * RO access to the storage
	 */
	const void* get() const { return data; }

	/**
	 * RW Acces to the address using the & operator
	 */
	void* operator&() { return data; }

	/**
	 * RO Acces to the address using the & operator
	 */
	const void* operator&() const { return data; }

	/**
	 * explicit cast to a given type
	 * @return a RW pointer like U to the memory block
	 */
	template<typename U>
	U as() { return static_cast<U>(get()); }

	/**
	 * explicit cast to a given type
	 * @return a RO pointer like U to the memory block
	 */
	template<typename U>
	const U as() const { return static_cast<const U>(get()); }
};


}
}





#endif /* LBB_UTILITY_ALIGNED_UNION_H_ */
