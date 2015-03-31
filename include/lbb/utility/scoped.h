#ifndef LBB_UTILITY_SCOPED_H_
#define LBB_UTILITY_SCOPED_H_

#include <cstddef>
#include <new>

#ifndef ANDROID
#include <cstdlib>
#else 
#include <stdlib.h>
#endif

namespace lbb {
namespace utility {


/**
 * \brief prevent inherited classes to be created via a call to new
 * \note inheritance should not be public
 */
class scoped
{
protected:
	void* operator new(size_t size) { return malloc(size); }
	void* operator new[](size_t);
    void operator delete(void* p) { free(p); }
	void operator delete[](void*) { }
};


}  // namespace utility
}  // namespace lbb

#endif /* LBB_UTILITY_SCOPED_H_ */

