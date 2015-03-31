#ifndef LBB_FUNCTIONAL_REFERENCE_WRAPPER_H_
#define LBB_FUNCTIONAL_REFERENCE_WRAPPER_H_

namespace lbb {
namespace functional {

/**
 * forwarding parameters to function in c++03 is kinda broken, so for
 * instance, if you have a function template :
 * \code
 * template<typename T> void func(T t);
 * \endcode
 * Which forward it's t argument to another function, t is always
 * copy constructed even if the parameter in the target function is a reference
 * or worse, even if the parameter in input is a reference or a reference to const !!!
 *
 * In order to avoid this behaviour, you can use the class template reference_wrapper
 * in conjunction with the helper functions ref and cref which create a wrapper to
 * a reference or a wrapper to a reference to const.
 *
 * The reference wrapper is also copy constructible and copy assignable, so you can
 * also easily create a container to references using this tool.
 *
 * @TODO : make stuff for function wrapp
 */
template<typename T>
struct reference_wrapper {
	typedef T type;
	//TODO other typedefs related to function wrapper ...

	/**
	 * Create a new wrapper to the reference in input parameter
	 * @param reference the reference to wrapp
	 */
	reference_wrapper(T& reference) : _ptr(&reference) { }

	/**
	 * Copy construction of a reference wrapper
	 * @param to_copy the wrapper to copy
	 */
	reference_wrapper(const reference_wrapper& to_copy) : _ptr(to_copy._ptr) { }

	/**
	 * Copy assignment from another reference_wrapper
	 * @param to_copy the reference_wrapper to copy
	 * @return self reference
	 */
	reference_wrapper& operator=(const reference_wrapper to_copy) {
		_ptr = to_copy._ptr;
		return *this;
	}

	/**
	 * Explicit access to a reference
	 * @return the reference contained by the wrapper
	 */
	T& get() const { return *_ptr; }

	/**
	 * Implicit access to a reference
	 * @return the reference contained by the wrapper
	 */
	operator T&() const { return *_ptr; }

private:
	T* _ptr;			///Use a pointer to store the reference ...
};


/**
 * Create a reference_wrapper to a reference of type T
 * @param instance the reference to wrap
 * @return a reference wrapper to the instance
 */
template<typename T>
reference_wrapper<T> ref(T& instance) {
	return reference_wrapper<T>(instance);
}

/**
 * Create a reference_wrapper to a reference of type T
 * @param reference wrapper to copy
 * @return a reference wrapper to the instance contained in the wrapper to copy
 */
template<typename T>
reference_wrapper<T> ref(reference_wrapper<T> instance) {
	return reference_wrapper<T>(instance);
}


/**
 * Create a reference_wrapper to a reference to const of type T
 * @param instance the reference to wrap
 * @return a reference wrapper to the instance
 */
template<typename T>
reference_wrapper<const T> cref(const T& instance) {
	return reference_wrapper<const T>(instance);
}

/**
 * Create a reference_wrapper to a reference to const of type T
 * @param reference wrapper to copy
 * @return a reference wrapper to the instance contained in the wrapper to copy
 */
template<typename T>
reference_wrapper<const T> cref(reference_wrapper<T> instance) {
	return reference_wrapper<const T>(instance);
}


}  // namespace functional
}  // namespace lbb





#endif /* LBB_FUNCTIONAL_REFERENCE_WRAPPER_H_ */
