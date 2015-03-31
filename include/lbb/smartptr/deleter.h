#ifndef LBB_SMARTPTR_DELETER_H_
#define LBB_SMARTPTR_DELETER_H_

#include <cstdlib>

/**
 * Custom deleters used for smartptr, they are STATELESS for now
 */
namespace lbb {
namespace smartptr {


/**
 * Default deleter, call delete internally
 */
template<typename T>
struct default_deleter {
	static void release(T* instance) {
		delete instance;
	}

	void operator()(T* instance) { 
		release(instance);
	}
};


/**
 * specialization for arrays
 */
template<typename T>
struct default_deleter<T[]> {
	static void release(T* instance) {
		delete[] instance;
	}

	void operator()(T* instance) { 
		release(instance);
	}
};


/**
 * deleter used for function pointer call
 */
template<typename Signature, Signature* func>
struct free_function_deleter;

template<typename T, typename ReturnType, ReturnType(*FunctionPointer)(T*)>
struct free_function_deleter<ReturnType(T*), FunctionPointer> {
	static void release(T* instance) {
		if(instance) {
			FunctionPointer(instance);
		}
	}

	void operator()(T* instance) { 
		release(instance);
	}
};

typedef free_function_deleter<void(void*), &free> c_free_deleter;


}  // namespace smartptr
}  // namespace lbb


#endif /* LBB_SMARTPTR_DELETER_H_ */
