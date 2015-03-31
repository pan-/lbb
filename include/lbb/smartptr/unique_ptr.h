#ifndef LBB_SMARTPTR_UNIQUE_PTR_H_
#define LBB_SMARTPTR_UNIQUE_PTR_H_

//#include <memory>
#include <cassert>

#include <lbb/meta.h>
#include <lbb/utility.h>

#include "deleter.h"

/**
 * @file unique_ptr.h
 *
 * Semantic and security are two main keys of building robust software,
 * raw pointers has none :
 *
 * 	- When a wild raw pointer appears, it ownership should be explicitly
 * 	documented to indicate who is the owner of the pointer, is it the caller,
 * 	is it the callee, etc ... It require an important effort of concentration to
 * 	the programmer to maintain the construction/ownership flow of an instance
 * 	in the same idea, it could be useful to indicate if the object pointed is located
 * 	on the stack or on the heap (but it reveal a bad c practice in c++ : using pointers
 * 	instead of references ...)
 *
 * 	- Every time a pointer is allocated on the heap, it should be deleted explicitly
 * 	using the delete operator, these tasks are redundant and can lead to memory leaks
 *
 * The template class unique_ptr solve these two issues : it declare objects allocated on
 * the heap with unique ownership, the underlying instance allocated is deleted at the
 * destruction of this semantic proxy.
 *
 * This class also enable a special feature, of c++11 in c++03 : move operations, a unique ptr
 * has an unique owner, it is not copyable but it is possible to transfer its ownership.
 *
 * Examples :
 *
 * Chaining call method :
 * \code
 * class Bar : Foo { };
 *
 * unique_ptr<Foo> make_foo() { return unique_ptr<Foo>(new Bar); }
 * Foo* legacy_make_foo() { return new Bar; }
 *
 *
 * //don't dealocate the input ...
 * void legacy_func(Foo*);
 * void func(unique_ptr<Foo>&);
 *
 *
 * //new style :
 * func(make_foo());
 *
 * //intermediate
 * legacy_func(make_foo().get())
 *
 * // really bad
 * // Foo* foo = legacy_make_foo();
 * // legacy_func(foo);
 * // delete foo;
 * \endcode
 *
 * Secure raw pointers :
 * \code
 * class Foo {
 * 	unique_ptr<Bar> bar;
 *
 * 	Foo(size_t size) : bar(new Bar) { }
 * 	~Foo() {
 * 		//no dealocation of bar here ...
 * 	}
 * };
 * \endcode
 *
 * Move resources avoiding copy and headaches :
 * \code
 * MessageHandler(unique_ptr<Message> msg) {
 * 	Caller& caller = msg->GetCaller();
 *
 * 	//stuff ...
 *
 * 	//return the message to the caller ...
 * 	caller->Post(msg.move());
 * }
 * \endcode
 */

namespace lbb {  
namespace smartptr {

/**
 * unique_ptr is a RAII smart pointer which manage a single instance of a pointer,
 * it embed the following characteristics :
 * 	- it's scoped, you can't allocate an unique_ptr on the heap !
 * 	- it's not copy constructible but it's movable constructible so it means that you
 * 	can move (steal) rvalues for the pointer but it didn't allow lvalue copy.
 *
 * 	Ex :
 *
 * 	unique_ptr<Foo> ret_rvalue();				//return an unique_ptr rvalue
 * 	Foo* ret_raw_rvalue();					//return a raw rvalue
 *
 * 	unique_ptr<Foo> lvalue(new Foo); 			//Construct an lvalue
 *  	const unique_ptr<Foo> clvalue(new Foo); 		//Construct aconst lvalue
 *
 *
 *  	//copy construction example
 *  	unique_ptr<Foo> from_rvalue(ret_rvalue());		//correct
 *  	unique_ptr<Foo> from_lvalue(lvalue);			//will miserably fail at the compilation
 *  	unique_ptr<Foo> from_const_lvalue(clvalue);		//will miserably fail at the compilation
 *
 *  	//copy operator example
 *  	from_rvalue = new Foo;					//correct
 *  	from_rvalue = ret_rvalue();				//correct
 *  	from_rvalue = ret_raw_rvalue();				//correct
 *
 *  	from_rvalue = lvalue;					//will fail at compile time
 *  	from_rvalue = clvalue;					//will fail at compile time
 */
template<typename T, class Deleter = default_deleter<T> >
class unique_ptr : public safe_bool<unique_ptr<T, Deleter> >, 
	not_copyable, public movable<unique_ptr<T, Deleter> >
{

	LBB_TYPEDEF_MOVE_TYPES_TPL(unique_ptr);

public:
	typedef T* pointer;
	typedef T element_type;
	typedef Deleter deleter_type;

	/**
	 * Construct an empty unique ptr
	 */
	unique_ptr() : _instance(0) { }

	/**
	 * Regular constructor, construct an unique ptr from the original ptr
	 * \param instance instance managed by the smart ptr
	 */
	inline unique_ptr(pointer instance) : _instance(instance) { }

	/**
	 * Move constructor, it swallow rvalues only
	 * \param rvalue_instance is automatically created by the implicit conversion when an rvalue is
	 * used to move-construct an object
	 */
	inline unique_ptr(rvalue_reference rvalue_instance) : 
		_instance(rvalue_instance._instance) {
		rvalue_instance._instance = 0;
	}

	/**
	 * Destructor
	 * \brief delete the instance managed by the smart pointer
	 */
	inline ~unique_ptr() {
		deleter_type::release(_instance);
	}

	/**
	 * Copy from raw pointer
	 * \brief release the old instance managed then replace it by the new
	 * \param instance the new instance to manage
	 */
	inline unique_ptr& operator=(pointer ptr) {
	//	assert(instance != _instance);
		deleter_type::release(_instance);
		_instance = ptr;
		return *this;
	}

	/**
	 * Move copy operator
	 * \brief move operation from an rvalue. Release the old instance managed then steal
	 * it from the rvalue instance passed
	 * \param instance rvalue of an unique_ptr
	 */
	inline unique_ptr& operator=(rvalue_reference other) {
		if(this == &other)  { return *this; }
//		assert(instance.get() != _instance);
		deleter_type::release(_instance);
		_instance = other._instance;
		other._instance = 0;
		return *this;
	}

	/**
	 * release the internal pointer from the management an return it
	 */
	inline pointer release() {
		pointer res = _instance;
		_instance = 0;
		return res;
	}

	/**
	 * reset the current pointer by a new one
	 */
	inline void reset(pointer ptr = pointer()) { 
		if(_instance != ptr) { 
			deleter_type::release(_instance); 
			_instance = ptr; 
		}
	}

	/**
	 * swap operation
	 */
	inline void swap(unique_ptr& to_swap) {
		T* tmp = to_swap._instance;
		to_swap._instance = _instance;
		_instance = tmp;
	}

	/**
	 * Return a reference to the internal object instance
	 */
	inline element_type& operator*() const { return *_instance; }

	/**
	 * Access to the internal instance methods through the operator ->
	 */
	inline pointer operator ->() const { assert(_instance != 0); return _instance; }

	/**
	 * Direct access to the pointer of the object
	 */
	inline pointer get() const { return _instance; }

	/**
	 * return the deleter
	 */
	inline deleter_type get_deleter() const { return deleter_type(); }

	/**
	 * Boolean conversion
	 */
	inline bool boolean_value() const {
		return _instance;
	}

private:
	T* _instance;				///pointer to the instance
};






template<typename T, class Deleter >
class unique_ptr<T[], Deleter> : public safe_bool<unique_ptr<T[], Deleter> >,
	not_copyable, public movable<unique_ptr<T[], Deleter> >
{

	LBB_TYPEDEF_MOVE_TYPES_TPL(unique_ptr);

public:
	typedef T* pointer;
	typedef T element_type;
	typedef Deleter deleter_type;

	/**
	 * Construct an empty unique ptr
	 */
	unique_ptr() : _instance(0) { }

	/**
	 * Regular constructor, construct an unique ptr from the original ptr
	 * \param instance instance managed by the smart ptr
	 */
	inline unique_ptr(pointer instance) : _instance(instance) { }

	/**
	 * Move constructor, it swallow rvalues only
	 * \param rvalue_instance is automatically created by the implicit conversion when an rvalue is
	 * used to move-construct an object
	 */
	inline unique_ptr(rvalue_reference rvalue_instance) : 
		_instance(rvalue_instance._instance) {
		rvalue_instance._instance = 0;
	}

	/**
	 * Destructor
	 * \brief delete the instance managed by the smart pointer
	 */
	inline ~unique_ptr() {
		deleter_type::release(_instance);
	}

	/**
	 * Copy from raw pointer
	 * \brief release the old instance managed then replace it by the new
	 * \param instance the new instance to manage
	 */
	inline unique_ptr& operator=(pointer instance) {
	//	assert(instance != _instance);
		deleter_type::release(_instance);
		_instance = instance;
		return *this;
	}

	/**
	 * Move copy operator
	 * \brief move operation from an rvalue. Release the old instance managed then steal
	 * it from the rvalue instance passed
	 * \param instance rvalue of an unique_ptr
	 */
	inline unique_ptr& operator=(rvalue_reference instance) {
		assert(instance.get() != _instance);
		//move copy so we can swap
		swap(instance);
		return *this;
	}

	/**
	 * release the internal pointer from the management an return it
	 */
	inline pointer release() {
		pointer res = _instance;
		_instance = 0;
		return res;
	}

	/**
	 * reset the current pointer by a new one
	 */
	inline void reset(pointer ptr = pointer()) { 
		deleter_type::release(_instance); 
		_instance = ptr; 
	}

	/**
	 * swap operation
	 */
	inline void swap(unique_ptr& to_swap) {
		T* tmp = to_swap._instance;
		to_swap._instance = _instance;
		_instance = tmp;
	}

	/**
	 * operator[] provides access to elements of an array managed by a unique_ptr.
	 * The parameter i is required to be a valid array index
	 */
	element_type& operator[](size_t i) const { return _instance[i]; }

	/**
	 * Direct access to the pointer of the object
	 */
	inline pointer get() const { return _instance; }

	/**
	 * return the deleter
	 */
	inline deleter_type get_deleter() const { return deleter_type(); }

	/**
	 * Boolean conversion
	 */
	inline bool boolean_value() const {
		return _instance;
	}

private:
	T* _instance;				///pointer to the instance
};










template<typename aType>
struct is_unique_ptr_ : false_ { };

template<typename aType>
struct is_unique_ptr_<smartptr::unique_ptr<aType> > : true_ { };

template<typename aType>
struct is_unique_ptr_<const smartptr::unique_ptr<aType> > : true_ { };

template<typename T>
struct unique_ptr_get_type_;

template<typename T>
struct unique_ptr_get_type_<unique_ptr<T> > : meta_type_<T> { };


} 	// namespace smartptr
}	//namespace lbb










#endif /* LBB_SMARTPTR_UNIQUEP_TR_H_ */
