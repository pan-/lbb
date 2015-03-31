#ifndef LBB_SMARTPTR_SHAREDPTR_H_
#define LBB_SMARTPTR_SHAREDPTR_H_

#include <lbb/meta.h>
#include <lbb/utility.h>

#include "shared_ptr_/shared_base_ptr.h"
#include "shared_ptr_/shared_base_value.h"


namespace lbb {
namespace smartptr {

template<typename T>
class shared_ptr : public safe_bool<shared_ptr<T> >
{
	template<typename U>
	struct conversion_condition_result_ : bool_<
	        (is_base_or_same_of_<T, U>::value && is_polymorph_<U>::value
	                && is_polymorph_<T>::value) || (is_same_type_<T, U>::value)>
	{
	};

	template<typename>
	friend class shared_ptr;

	template <typename U> 
	friend shared_ptr<U> make_shared();

	template <typename U, typename A1> 
	friend shared_ptr<U> make_shared(A1);

	template <typename U, typename A1, typename A2> 
	friend shared_ptr<U> make_shared(A1, A2);

	template <typename U, typename A1, typename A2, typename A3> 
	friend shared_ptr<U> make_shared(A1, A2, A3);

	template <typename U, typename A1, typename A2, typename A3, typename A4> 
	friend shared_ptr<U> make_shared(A1, A2, A3, A4);

	template <typename U, typename A1, typename A2, typename A3, typename A4, typename A5> 
	friend shared_ptr<U> make_shared(A1, A2, A3, A4, A5);



	inline void acquire_instance_and_create_base()
	{
		if(_instance)
		{
			_base = new shared_ptr_::shared_base_ptr<T>(_instance);
			_base->increment_ref_count();
		}
	}

	inline void acquire_instance()
	{
		if(_instance)
		{
			_base->increment_ref_count();
		}
	}

	inline void set_instance_acquire_it_the_create_base(T* instance)
	{
		_instance = instance;
		acquire_instance_and_create_base();
	}

	inline void set_instance_and_base_then_acquire_instance(T* instance, shared_ptr_::shared_base* base)
	{
		_instance = instance;
		_base = base;

		acquire_instance();
	}

	inline void release_instance()
	{
		if(_instance)
		{
			if(_base->decrement_ref_count() == 0)
			{
				delete _base;
			}
		}
	}

	inline shared_ptr(shared_ptr_::shared_base_value<T>& val) :
			_instance(val.instance_address()), _base(&val)
	{
		acquire_instance();
	}

public:
	//initialization
	inline shared_ptr(T* instance) :
			_instance(instance), _base(0)
	{
		acquire_instance_and_create_base();
	}

	//copy construction
	inline shared_ptr(const shared_ptr& instance) :
			_instance(instance._instance), _base(instance._base)
	{
		acquire_instance();
	}

	template<typename U>
	inline shared_ptr(const shared_ptr<U>& instance) :
			_instance(instance._instance), _base(instance._base)
	{
		LBB_COMPILE_ASSERT(conversion_condition_result_<U>::value == true,
		        shared_pointer_conversion_is_impossible);
		acquire_instance();
	}

	//destruction
	inline ~shared_ptr()
	{
		release_instance();
	}

	//copy assignement
	inline shared_ptr& operator=(T* instance)
	{
		release_instance();
		set_instance_acquire_it_the_create_base(instance);
		return *this;
	}

	template<typename U>
	inline shared_ptr& operator=(U* instance)
	{
		return operator =((T*) instance);
	}

	inline shared_ptr& operator=(const shared_ptr& instance)
	{
		if(this->_instance != instance._instance)
		{
			release_instance();
			set_instance_and_base_then_acquire_instance(instance._instance, instance._base);
		}
		return *this;
	}

	template<typename U>
	inline shared_ptr& operator=(const shared_ptr<U>& instance)
	{
		LBB_COMPILE_ASSERT(conversion_condition_result_<U>::value == true,
		        shared_pointer_conversion_is_impossible);
		if(this->_instance != instance._instance)
		{
			release_instance();
			set_instance_and_base_then_acquire_instance(instance._instance, instance._base);
		}
		return *this;
	}

	//swapable
	inline void swap(shared_ptr& instance)
	{
		T* tmp_instance = instance._instance;
		shared_ptr_::shared_base* tmp_base = instance._base;

		instance._instance = _instance;
		instance._base = _base;

		_instance = tmp_instance;
		_base = tmp_base;
	}

	//return reference to internal value
	inline T& operator*() const
	{
		return *_instance;
	}

	inline T* operator->() const
	{
		return _instance;
	}

	inline T* get() const
	{
		return _instance;
	}

	//equality operator
	template<typename U, typename V>
	friend bool operator==(const shared_ptr<U>& left, const shared_ptr<V>& right);


	//Boolean conversion ...
	inline bool boolean_value() const {
		return _instance;
	}

	typedef shared_ptr_::shared_base_value<T> make_shared_product;

private:
	T* _instance;
	shared_ptr_::shared_base* _base;
};

template<typename U, typename V>
bool operator==(const shared_ptr<U>& left, const shared_ptr<V>& right)
{
	return (left._instance == right._instance);
}

template<typename U, typename V>
bool operator!=(const shared_ptr<U>& left, const shared_ptr<V>& right)
{
	return !(left == right);
}






} // namespace smartptr
} // namespace lbb

#endif /* LBB_SMARTPTR_SHAREDPTR_H_ */
