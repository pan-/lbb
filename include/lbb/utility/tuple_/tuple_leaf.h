#ifndef LBB_UTILITY_TUPLE__TUPLE_LEAF_H_
#define LBB_UTILITY_TUPLE__TUPLE_LEAF_H_

#include <lbb/meta.h>

namespace lbb {
namespace utility {
namespace tuple_ { 

struct empty_leaf_tag { };
struct value_leaf_tag { };


// compile function which return a discriminating tag indicating if the 
// T is empty or not.
template<typename T>
struct get_leaf_tag_ :  select_type_<
	/* if */ is_empty_<T>::value, 
		empty_leaf_tag,
	//else 
		value_leaf_tag
> { };


//tuple leaf encode the index of the leaf in the tuple and the type stored 
//tuple of empty types does not embed anything 
template<size_t Index, typename T, typename Tag = typename get_leaf_tag_<T>::type>
struct leaf;


//leaf for empty type !!!
//note : empty types are immutables by nature 
template<size_t Index, typename T>
struct leaf<Index, T, empty_leaf_tag> {
	leaf(T) { }
	T get() const { return T(); }
};

//leaf for value !!!
template<size_t Index, typename T>
struct leaf<Index, T, value_leaf_tag> {
	static const size_t index_value = Index;
	typedef T value_type;

	leaf(T value) : _value(value) { }

	leaf(const leaf& other) : _value(other._value) { }

	leaf& operator=(leaf other) { 
		_value = other._value;
		return *this;
	}

	void swap(leaf& other) { 
		leaf tmp(other);
		other._value = _value;
		_value = tmp._value;
	}

	T& get() { return _value; }

	const T& get() const { return _value; }

private:
	T _value;	
};



}  // namespace tuple_
}  // namespace utility
}  // namespace lbb


#endif /* LBB_UTILITY_TUPLE__TUPLE_LEAF_H_ */