#ifndef LBB_UTILITY_NOT_COPYABLE_H_
#define LBB_UTILITY_NOT_COPYABLE_H_

#include <lbb/meta.h>

namespace lbb {
namespace utility {

/**
 * \brief prevent inherited classes to be copied 
 * \note inheritance should not be public
 */
class not_copyable 
{
protected:
	not_copyable() {}
	~not_copyable() {}

private:
	//swallow everything except movable value ...
	not_copyable(not_copyable&);
	template<typename T>
	not_copyable(T&, typename enable_if_<is_same_type_<T, not_copyable const>::value >::type* = 0);

	//swallow everything except movable value ...
	not_copyable& operator=(not_copyable&);
	template<typename T>
	typename enable_if_<is_same_type_<T, not_copyable const >::value, T>::type& operator=(T&);
};

}  // namespace utility
}  // namespace lbb

#endif /* LBB_UTILITY_NOT_COPYABLE_H_ */

