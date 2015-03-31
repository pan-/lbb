#ifndef LBB_FUNCTIONAL_BIND__VALUE_H_
#define LBB_FUNCTIONAL_BIND__VALUE_H_ 

namespace lbb { 
namespace functional { 
namespace bind_ { 

/**
 * Wrapper which hold values used by the arg list structure 
 */
template<typename T>
struct value { 
	/**
	 * construct the value 
	 */
	value(T val) : _val(val) { }

	/**
	 * return the value by reference 
	 */
	T& get() { return _val; }

	/**
	 * return the value by const reference 
	 */ 
	const T& get() const { return _val; }

private:
	T _val;
};



}
}
}


#endif /* LBB_FUNCTIONAL_BIND__VALUE_H_ */