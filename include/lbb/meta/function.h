#ifndef LBB_META_FUNCTION_H_
#define LBB_META_FUNCTION_H_

#include "meta_type.h"
#include "static_assert.h"
#include "traits.h"

#include "signature.h"

/**
 * Function introspection, and other stuffs related ...
 */

namespace lbb {
namespace meta {

/**
 * Class like namespace ...
 */
namespace function_ {


template<typename Signature, Signature Value>
struct function_ : meta_type_<function_<Signature, Value> > {
	typedef Signature signature_;
	static const Signature value;
};

template<typename Signature, Signature Value>
const Signature function_<Signature, Value>::value = Value;


/**
 * true_ if T is a function_ and false otherwise
 */
template<typename T>
struct is_function_ : false_ { };

template<typename Signature, Signature Value>
struct is_function_<function_<Signature, Value> > : true_ { };


/**
 * Get the signature of a function and a compile time error otherwise
 */
template<typename T>
struct get_signature_;

template<typename Signature, Signature Value>
struct get_signature_<function_<Signature, Value> > : meta_type_<Signature> { };

/**
 * return the function pointer (at runtime ...)
 */
template<typename T>
typename enable_if_<is_function_<T>::value, const typename T::signature>::type
get_value() {
	return T::value;
}

/**
 * Return the value of a function_ at compile time
 */
template<typename T>
struct get_value_;

template<typename Signature, Signature Value>
struct get_value_<function_<Signature, Value> > : meta_type_<get_value_<function_<Signature, Value> > > {
	static const Signature value;
};

template<typename Signature, Signature Value>
const Signature get_value_<function_<Signature, Value> >::value = Value;

/*
template<typename T>
struct get_value_;

template<typename Signature, Signature Value>
struct get_value_<function_<Signature, Value> >
*/

//enable signature introspections ...

/**
 * Get the return type of a function ...
 */
template<typename T>
struct get_return_type_;

template<typename Signature, Signature Value>
struct get_return_type_<function_<Signature, Value> > : introspection_::signature_::get_return_type_<Signature> { };


/**
 * Return true_ if the function is a part of a class and false otherwise
 */
template<typename T>
struct is_member_;

template<typename Signature, Signature Value>
struct is_member_<function_<Signature, Value> > : introspection_::signature_::is_member_<Signature> { };

/**
 * Return the application class of th function_
 */
template<typename T>
struct get_application_class_;

template<typename Signature, Signature Value>
struct get_application_class_<function_<Signature, Value> > :
	introspection_::signature_::get_application_class_<Signature> { };


/**
 * Return the list of the parameters
 */
template<typename T>
struct get_parameters_;

template<typename Signature, Signature Value>
struct get_parameters_<function_<Signature, Value> > :
	introspection_::signature_::get_parameters_<Signature> { };

/**
 * Return the arity of the function
 */
template<typename T>
struct get_arity_;

template<typename Signature, Signature Value>
struct get_arity_<function_<Signature, Value> > : introspection_::signature_::arity_<Signature> { };


/**
 * return true_ if the function is a free function and false otherwise !
 */
template<typename T>
struct is_free_function_;

template<typename Signature, Signature Value>
struct is_free_function_<function_<Signature, Value> > :
introspection_::signature_::is_free_function_<Signature> { };



}  // namespace function_

}  // namespace meta
}  // namespace lbb


#endif /* LBB_META_FUNCTION_H_ */
