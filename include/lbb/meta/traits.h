#ifndef LBB_META_TRAITS_H_
#define LBB_META_TRAITS_H_

#include "meta_type.h"

/**
 * \file Traits.h
 *
 * A collection of compile time template class utilities which help in type manipulation
 * and provide a kind of introspection
 * 
 * \TODO Add an alignof_ traits
 */

namespace lbb {

namespace meta {

/**
 * \brief A utility which can be used to enable a template method at compile time if the condition
 * is met and provide a kind of template method partial specialization.
 *
 * If the condition is true, the field result yield a type, otherwise the struct is empty
 *
 * \tparam aCondition compile time boolean value
 * \tparam aType the type yielded by result if the condition is true
 * \result aType if the condition is true
 */
template<bool aCondition, typename aType = void>
struct enable_if_ : meta_type_<aType> { };

/**
 * \brief partial specialization of enable_if if the condition is false
 */
template<typename aType>
struct enable_if_<false, aType> { };


/**
 * Same, but disable the function the condition is true
 */
template<bool aCondition, typename aType = void>
struct disable_if_ : meta_type_<aType> { };

/**
 * \brief partial specialization of disable_if if the condition is true
 */
template<typename aType>
struct disable_if_<true, aType> { };




/**
 * \brief Selection of a type with using a boolean condition, if the condition is true,
 * result will yield the type T otherwise it will yield the type U
 *
 * \tparam aCondition boolean condition for the selection of a type
 * \tparam T type returned as result if the condition is true
 * \tparam U type returned as result if the condition is false
 * \result T if aCondition is true and U otherwise
 */
template<bool aCondition, typename T, typename U>
struct select_type_ : meta_type_<T> { };

/**
 * \brief partial specialization of select_type if the condition is false
 */
template<typename T, typename U>
struct select_type_<false, T, U> : meta_type_<U> { };


template<typename T>
struct remove_cv_ : meta_type_<T> { };

template<typename T>
struct remove_cv_<volatile T> : meta_type_<T> { };

template<typename T>
struct remove_cv_<const T> : meta_type_<T> { };

template<typename T>
struct remove_cv_<const volatile T> : meta_type_<T> { };

//primitive trait

/**
 * \brief The result of this trait, will be true if T is a primitive type and false otherwise
 *
 * Primitive types are builtins c++ types (char, short, int, etc ...)
 *
 * \tparam T the type on which the trait is applied
 * \result true if T is a primitive type and false otherwise
 */
template<typename T>
struct is_primitive_ : false_ { };

/**
 * \brief complete specialization of is_primitive for bool, result will be true
 */
template<>
struct is_primitive_<bool> : true_ { };

/**
 * \brief complete specialization of is_primitive for char, result will be true
 */
template<>
struct is_primitive_<char> : true_ { };

/**
 * \brief complete specialization of is_primitive for signed char, result will be true
 */
template<>
struct is_primitive_<signed char> : true_ { };

/**
 * \brief complete specialization of is_primitive for unsigned char, result will be true
 */
template<>
struct is_primitive_<unsigned char> : true_ { };

/**
 * \brief complete specialization of is_primitive for signed short, result will be true
 */
template<>
struct is_primitive_<signed short> : true_ { };

/**
 * \brief complete specialization of is_primitive for unsigned short, result will be true
 */
template<>
struct is_primitive_<unsigned short> : true_ { };

/**
 * \brief complete specialization of is_primitive for signed int, result will be true
 */
template<>
struct is_primitive_<signed int> : true_ { };

/**
 * \brief complete specialization of is_primitive for unsigned int, result will be true
 */
template<>
struct is_primitive_<unsigned int> : true_ { };

/**
 * \brief complete specialization of is_primitive for signed long, result will be true
 */
template<>
struct is_primitive_<signed long> : true_ { };

/**
 * \brief complete specialization of is_primitive for unsigned long, result will be true
 */
template<>
struct is_primitive_<unsigned long> : true_ { };

/**
 * \brief complete specialization of is_primitive for float, result will be true
 */
template<>
struct is_primitive_<float> : true_ { };

/**
 * \brief complete specialization of is_primitive for double, result will be true
 */
template<>
struct is_primitive_<double> : true_ { };

/**
 * \brief Trait which return true if T is a reference and false otherwise
 * \tparam T the type on which the trait is applied
 * \result true if T is a reference and false otherwise
 */
template<typename T>
struct is_reference_ : false_ { };

/**
 * \brief specialization of is_reference for a reference type
 */
template<typename T>
struct is_reference_<T&> : true_ { };

/**
 * \brief remove a reference from a type
 * \tparam T the type on which the trait is applied
 * \return the type without reference
 */
template<typename T>
struct remove_reference_ : meta_type_<T> { };

/**
 * \brief specialization of remove_reference_ for a reference type
 */
template<typename T>
struct remove_reference_<T&> : meta_type_<T> { };

/**
 * \brief add a reference to a type
 * \tparam T the type on which the trait is applied
 * \return the type with a reference
 */
template<typename T>
struct add_reference_ : meta_type_<T&> { };

/**
 * \brief specialization of add_reference_ for a reference type
 */
template<typename T>
struct add_reference_<T&> : meta_type_<T> { };

/**
 * \brief Trait which return true if T is a pointer and false otherwise
 * \tparam T the type on which the trait is applied
 * \return true if T is a pointer and false otherwise
 */
template<typename T>
struct is_ptr_ : false_ { };

/**
 * \brief specialization of is_ptr_ for a pointer type
 */
template<typename T>
struct is_ptr_<T*> : true_ { };

template<typename T>
struct is_ptr_<T* volatile> : true_ { };


//is enum traits 
template<typename T>
struct is_enum_ : bool_<__is_enum(T)> { };


/**
 * \brief Trait which remove ptr from the type
 * \tparam T the type used for the operation
 * \return the type without pointer
 */
template<typename T>
struct remove_ptr_ : meta_type_<T> { };

/**
 * \brief specialization of remove_ptr_ for a pointer type
 */
template<typename T>
struct remove_ptr_<T*> : meta_type_<T> { };

/**
 * \brief Trait which add a ptr to a type
 * \tparam T the type used for the operation
 * \return the type with a pointer
 */
template<typename T>
struct add_ptr_ : meta_type_<T*> { };

/**
 * \brief specialization of add_ptr_ for a pointer typedef
 * \TODO see if it's the wanted behavior
 */
template<typename T>
struct add_ptr_<T*> : meta_type_<T> { };


/**
 * \brief tell if a type is a value type (not a pointer or a reference)
 * \tparam T the type on which the traits is applied
 * \return true_ if the type is a value and false_ otherwise
 */
template<typename T>
struct is_value_ : nand_<is_ptr_<T>, is_reference_<T> > { };

/**
 * \brief Trait which return true if T and U are the same type
 * \tparam T a type
 * \tparam another type
 * \result true if T and U are of the same type
 */
template<typename T, typename U>
struct is_same_type_ : false_ { };

/**
 * \brief specialization of is_same_type for the same type
 */
template<typename T>
struct is_same_type_<T, T> : true_ { };


/**
 * test if a type is derivable or not
 */
template<typename T>
struct is_derivable_ : 
 	bool_<!is_ptr_<T>::value && !is_reference_<T>::value && !is_primitive_<T>::value> { }; 


/**
 * \brief Test if T is derived from B
 * \tparam T Type to test
 * \tparam B Base type
 * \result return true if T is derived from B and false otherwise
 */
template<typename T, typename B>
struct is_derived_of_imp_
{
private:
	typedef const volatile T* From;
	typedef const volatile B* Base;

	typedef char Small;
	struct Big { char data[2] ; };

	static Small test_inheritance(...);
	static Big test_inheritance(Base);
	static From make_T();
public:
	typedef bool_<(sizeof(Big) == sizeof(test_inheritance(make_T()))) && !is_same_type_<From, Base>::value> type;
};

template<typename T, typename B>
struct is_derived_of_ : is_derived_of_imp_<T, B>::type { };

template<typename T, typename B>
struct is_base_of_ : is_derived_of_<B, T>::type { };

template<typename T, typename B>
struct is_base_or_same_of_ : or_<is_base_of_<T, B>, is_same_type_<T, B> > { };

template<typename T, typename B>
struct is_derived_or_same_of_ : or_<is_derived_of_<T, B>, is_same_type_<T, B> > { };

template<typename T, typename B>
struct is_derived_or_same_or_base_of_ : or_<is_derived_of_<T, B>, is_base_or_same_of_<T, B> > { };


/**
 * Internal mechanism for polymorphism detection
 */
template<typename T, bool Condition>
struct is_polymorph_imp_
{
	class not_polymorph : T {
		not_polymorph();
		not_polymorph(const not_polymorph&);
		not_polymorph& operator=(const not_polymorph&);
	};

	class polymorph : T {
		polymorph();
		polymorph(const polymorph&);
		polymorph& operator=(const polymorph&);
	public:
		virtual ~polymorph() { }
	};

public:
	typedef bool_<sizeof(not_polymorph) == sizeof(polymorph)> type;
};

template<typename T>
struct is_polymorph_imp_<T, false> : false_ { };


template<typename T>
struct is_polymorph_enabler_ : nor_<is_primitive_<T>, is_ptr_<T> > { };

/**
 * \brief Test if T is a polymorph type
 * \tparam T Type to test
 * \result return true if T polymorph and false otherwise
 */

template<typename aType>
struct is_polymorph_ : is_polymorph_imp_<aType, is_polymorph_enabler_<aType>::value >::type { };



//collisions guard ...
namespace comparable {

//maker
template<typename T>
const T& make_type();

typedef bool comparable_result_type;

struct not_comparable_result_type {
	comparable_result_type dumb[2];
};

struct not_comparable_vehicle {
	template<typename T>
	not_comparable_vehicle(const T&);
};

not_comparable_result_type operator== (const not_comparable_vehicle&, const not_comparable_vehicle&);

template<typename T>
struct is_comparable_ : lbb::meta::bool_<(sizeof(make_type<T>() == make_type<T>()) == sizeof(comparable_result_type)) ? true : false> {

};

}	//comparable

/**
 * Test if a type is comparable or not
 */
template<typename T>
struct is_comparable_ : comparable::is_comparable_<T>::type { };


/**
 * \brief select the best type from T to forward a parameter in a method signature
 *
 * It will return T is T is a primitive type or a pointer type or a reference type, otherwise
 * it will return const T&
 *
 * \tparam T type on which the trait is applied
 * \result the best type to forward a parameter
 */
template<typename T>
struct forward_parameter_ :
	select_type_<is_ptr_<T>::value || is_primitive_<T>::value || is_reference_<T>::value, T, const T&> { };

/**
 * \brief tell the size of a type 
 */
template<typename T>
struct sizeof_ : unsigned_int_<sizeof(T)> { };

/**
 * Create a reference to T (counter part of runtime ref)
 */
template<typename T>
T& ref_();

/**
 * Create a reference to a const T (counter part of runtime cref)
 */
template<typename T>
const T& cref_();

namespace meta_ {

/**
 * Constructible implementation ...
 * NOTE : work only for gcc >= 4.4.0 (c++ core issue #339)
 * TODO : workaround and tests on other compilers
 */
template<typename T>
struct constructible_tester_imp_  {

	typedef char true_type;
	struct false_type { true_type d[255]; };

	/**
	 * TODO : FIX FOR OTHER COMPILERS (see c++ core issue #339)
	 */
	template<typename U>
	typename enable_if_<sizeof(::new U(cref_<U>())), true_type>::type
	static constructible_test(void*);

	template<typename>
	static false_type constructible_test(...);

	enum { value = sizeof(constructible_test<T>(0)) == sizeof(true_type) ? true : false };

	typedef bool_<value>						type;
};


}  // namespace detail


/**
 * Test if a type is copy constructible or not !!!
 */
template<typename T>
struct is_copy_constructible_ :
	lbb::meta::bool_<meta_::constructible_tester_imp_<T>::value>
	{};



/**
 * Is empty implementation :
 * Given a type big__ which is not empty and a template type which inherit from it's input type
 * and big__ the compiler check if the size of both types are equal, if they are, it logicaly means
 * that the type T is empty !
 */
namespace is_empty_detail {

struct big__ {
	char storage__[256];
};

template<class T>
struct inherited_big__ : big__, T { };

template<class T, bool derivable = (!is_ptr_<T>::value && !is_reference_<T>::value && !is_primitive_<T>::value && !is_enum_<T>::value)>
struct is_empty_imp__ {
	enum { value = (sizeof(big__) == sizeof(inherited_big__<T>)) };
};

template<class T>
struct is_empty_imp__<T, false> {
	enum { value = false };
};
}  // namespace is_empty_detail

/**
 * Return true_ if T is an empty type (can be used for EBO) and false
 * otherwise
 */
template<class T>
struct is_empty_ : bool_<is_empty_detail::is_empty_imp__<T>::value> { };





}  // namespace meta

}  //namespace lbb


#endif /* LBB_META_TRAITS_H_ */
