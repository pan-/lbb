#ifndef LBB_META_STATICASSERT_H_
#define LBB_META_STATICASSERT_H_

/**
 * \file StaticAssert.h
 * \brief provide compile time assertions
 * \TODO document usage
 */

namespace lbb {

namespace meta {

template<bool c>
struct compile_assertion_fail;

template<>
struct compile_assertion_fail<true> { };

template<int size>
struct compile_assertion { };



template<bool c, typename T>
struct compile_assertion_fail_with_type;

template<typename T>
struct compile_assertion_fail_with_type<true, T> { };



}  // namespace meta
} // namespace lbb

#define LBB_COMPILE_ASSERT_FORWARD2(__CONDITION, __MESSAGE, __LINE) \
	typedef ::lbb::meta::compile_assertion_fail<__CONDITION> static_assertion_at_line_##__LINE##_because_##__MESSAGE; \
	typedef ::lbb::meta::compile_assertion<sizeof(static_assertion_at_line_##__LINE##_because_##__MESSAGE)> faillure_at_##__LINE 


#define LBB_COMPILE_ASSERT_FORWARD(__CONDITION, __MESSAGE, __LINE) LBB_COMPILE_ASSERT_FORWARD2(__CONDITION, __MESSAGE, __LINE)


/**
 * Frontend for a compile assertions
 * \param __CONDITION any boolean (numeric indeed) compile time expression
 * \param __MESSAGE message to display in case of faillure, the message should not be typed as
 * a string and should not contain spaces
 */
#if __GNUC__
#define LBB_COMPILE_ASSERT(__CONDITION, __MESSAGE)  LBB_COMPILE_ASSERT_FORWARD(__CONDITION, __MESSAGE, __LINE__) __attribute__((unused))
#else 
#define LBB_COMPILE_ASSERT(__CONDITION, __MESSAGE)  LBB_COMPILE_ASSERT_FORWARD(__CONDITION, __MESSAGE, __LINE__)
#endif



#define LBB_COMPILE_ASSERT_FORWARD2_WITH_TYPE(__CONDITION, __TYPE, __MESSAGE, __LINE) \
	typedef ::lbb::meta::compile_assertion_fail_with_type<__CONDITION, __TYPE> static_assertion_at_line_##__LINE##_because_##__MESSAGE; \
	typedef ::lbb::meta::compile_assertion<sizeof(static_assertion_at_line_##__LINE##_because_##__MESSAGE)> faillure_at_##__LINE

#define LBB_COMPILE_ASSERT_FORWARD_WITH_TYPE(__CONDITION, __TYPE, __MESSAGE, __LINE) LBB_COMPILE_ASSERT_FORWARD2_WITH_TYPE(__CONDITION, __TYPE, __MESSAGE, __LINE)

#if __GNUC__
#define LBB_COMPILE_ASSERT_WITH_TYPE(__CONDITION, __TYPE, __MESSAGE)  LBB_COMPILE_ASSERT_FORWARD_WITH_TYPE(__CONDITION, __TYPE, __MESSAGE, __LINE__) __attribute__((unused))	
#else 
#define LBB_COMPILE_ASSERT_WITH_TYPE(__CONDITION, __TYPE, __MESSAGE)  LBB_COMPILE_ASSERT_FORWARD_WITH_TYPE(__CONDITION, __TYPE, __MESSAGE, __LINE__)
#endif

#endif /* LBB_META_STATICASSERT_H_ */
