#ifndef LBB_CONCURRENCY_ATOMIC_H_
#define LBB_CONCURRENCY_ATOMIC_H_

#include <cstddef>
#include <lbb/meta.h>

/**
 * \file atomic.h 
 * \brief Provide generic implementation of atomic operations for builtin types (char, short, int, etc and pointers of course)
 * 
 * This implementation of generics atomics type follow the one given in the c++11 standard at one 
 * exception, the memory order cannot be specified (always equivalent to memory_order_seq_cst).
 * 
 * This class is usefull for creating lock-free data structures and updating atomically shared variable between 
 * threads withoot mutex use.
 * 
 * This class can be used as follow :
 * \code
 * atomic<int> foo(0);
 * //regular use of an int ...
 * \endcode
 * 
 * Along with standard type operation (read, write, arithmetic operations, etc), their is two interresting 
 * methods provided to deal with concurent access :
 * 
 * - T exchange(T value) which replace the value holded by the atomic with the parameter value and return the old one
 * - bool compare_exchange(T expected, T value) which replace the current value with the new value if the current 
 * value is equal to the expected.
 * 
 * \todo : work only with GCC right now
 */


namespace lbb {
namespace concurrency {

/**
 * atomic type
 * \tparam T type to wrap around an atomic value
 * \note : right now, work only with GCC
 */
template<typename T>
class atomic
{
	//TODO : static assert if it's not a pointer or an integral type
	typedef typename select_type_<is_ptr_<T>::value, ptrdiff_t, T>::type diff_type;
	typedef typename select_type_<is_ptr_<T>::value, sizeof_<T>, int_<1> >::type offset_type;

	T _value;											///hold the value of this atomic
	atomic(const atomic&);								///copy constructor deactivated
	atomic& operator=(const atomic&);					///assignement operator (from another atomic) deactivated
	atomic& operator=(const atomic&) volatile;			///assignement operator (from another atomic) deactivated

public:
	/**
	 * Construction of the atomic 
	 * \param value initialization value of the atomic
	 */
	inline atomic(T value = 0) : _value(value) { }

	/**
	 * Store a new value atomically
	 * \param value The new value to store
	 */
	inline void store(T value) {
		_value = value;
		__sync_synchronize();
	}

	/**
	 * Store a new value atomically 
	 * \param value The new value to store
	 */
	inline void store(T value) volatile {
		_value = value;
		__sync_synchronize();
	}

	/**
	 * Assignement operator, equivalent to store(T value) plus return of the value
	 * \param value The new value to store
	 */
	inline T operator=(T value) {
		store(value);
		return value;
	}

	/**
	 * Assignement operator, equivalent to store(T value) plus return of the value
	 * \param value The new value to store
	 */
	inline T operator=(T value) volatile {
		store(value);
		return value;
	}

	/**
	 * load atomically and return the current value of the atomic
	 * \return the current value holded
	 */
	inline T load() const {
		__sync_synchronize();
		T toReturn = _value;
		__sync_synchronize();
		return toReturn;
	}

	/**
	 * load atomically and return the current value of the atomic
	 * \return the current value holded
	 */
	inline T load() const volatile {
		__sync_synchronize();
		T toReturn = _value;
		__sync_synchronize();
		return toReturn;
	}

	/**
	 * Conversion operator, equivalent to load()
	 */
	inline operator T() const {
		return load();
	}

	/**
	 * Conversion operator, equivalent to load()
	 */
	inline operator T() const volatile {
		return load();
	}

	/**
	 * Exchange atomically the current value with value and return the old one
	 * \param value the new value to set
	 * \return the value contained at the moment of the exchange
	 */ 
	inline T exchange(T value) {
		return __sync_lock_test_and_set(&_value, value);
	}

	/**
	 * Exchange atomically the current value with value and return the old one
	 * \param value the new value to set
	 * \return the value contained at the moment of the exchange
	 */ 
	inline T exchange(T value) volatile {
		return __sync_lock_test_and_set(&_value, value);
	}

	/**
	 * replace the current value with parameter value if the current value is equal to expected
	 * \param expected the current value expected
	 * \param value the new value to set
	 * \return true if the operation has succeed and false otherwise
	 */
	inline bool compare_exchange(T expected, T value) {
		return __sync_bool_compare_and_swap(&_value, expected, value);
	}
	
	/**
	 * replace the current value with parameter value if the current value is equal to expected
	 * \param expected the current value expected
	 * \param value the new value to set
	 * \return true if the operation has succeed and false otherwise
	 */
	inline bool compare_exchange(T expected, T value) volatile {
		return __sync_bool_compare_and_swap(&_value, expected, value);
	}

	inline T fetch_add(diff_type value) {
		return __sync_fetch_and_add(&_value, value * offset_type::value);
	}

	inline T fetch_add(diff_type value) volatile {
		return __sync_fetch_and_add(&_value, value * offset_type::value);
	}

	inline T fetch_sub(diff_type value) {
		return __sync_fetch_and_sub(&_value, value * offset_type::value);
	}

	inline T fetch_sub(diff_type value) volatile {
		return __sync_fetch_and_sub(&_value, value * offset_type::value);
	}

	inline T fetch_and(T value) {
		return __sync_fetch_and_and(&_value, value);
	}

	inline T fetch_and(T value) volatile {
		return __sync_fetch_and_and(&_value, value);
	}

	inline T fetch_or(T value) {
		return __sync_fetch_and_or(&_value, value);
	}

	inline T fetch_or(T value) volatile {
		return __sync_fetch_and_or(&_value, value);
	}

	inline T fetch_xor(T value) {
		return __sync_fetch_and_xor(&_value, value);
	}

	inline T fetch_xor(T value) volatile {
		return __sync_fetch_and_xor(&_value, value);
	}

	inline T operator++(int){
    	return fetch_add(1);
    }

	inline T operator++(int) volatile {
    	return fetch_add(1);
    }

	inline T operator--(int) {
    	return fetch_sub(1);
    }

	inline T operator--(int) volatile {
    	return fetch_sub(1);
    }

	inline T operator++() {
    	return __sync_add_and_fetch(&_value, 1 * offset_type::value);
    }

	inline T operator++() volatile {
    	return __sync_add_and_fetch(&_value, 1 * offset_type::value);
    }

	inline T operator--() {
    	return __sync_sub_and_fetch(&_value, 1 * offset_type::value);
    }

	inline T operator--() volatile {
    	return __sync_sub_and_fetch(&_value, 1 * offset_type::value);
    }

	inline T operator+=(diff_type value) {
    	return __sync_add_and_fetch(&_value, value * offset_type::value);
    }

	inline T operator+=(diff_type value) volatile {
    	return __sync_add_and_fetch(&_value, value * offset_type::value);
    }

	inline T operator-=(diff_type value) {
    	return __sync_sub_and_fetch(&_value, value * offset_type::value);
    }

	inline T operator-=(diff_type value) volatile {
    	return __sync_sub_and_fetch(&_value, value * offset_type::value);
    }

	inline T operator&=(T value) {
    	return __sync_and_and_fetch(&_value, value);
    }

	inline T operator&=(T value) volatile {
    	return __sync_and_and_fetch(&_value, value);
    }

	inline T operator|=(T value) {
    	return __sync_or_and_fetch(&_value, value);
    }

	inline T operator|=(T value) volatile {
    	return __sync_or_and_fetch(&_value, value);
    }

	inline T operator^=(T value) {
    	return __sync_xor_and_fetch(&_value, value);
    }

	inline T operator^=(T value) volatile {
    	return __sync_xor_and_fetch(&_value, value);
    }
};

}	//namespace concurrency
}	//namespace lbb

#endif /* LBB_CONCURRENCY_ATOMIC_H_ */
