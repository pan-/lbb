#ifndef LBB_META_HAS_MEMBER_H_
#define LBB_META_HAS_MEMBER_H_

#include "traits.h"

namespace lbb {
namespace meta {

/**
 * select a metatype using a bool_ condition
 */
template<typename Cond, class TrueType, class FalseType>
struct select_meta_type_ : TrueType { };

template<class TrueType, class FalseType>
struct select_meta_type_<lbb::meta::false_, TrueType, FalseType> : FalseType { };

}
}


/**
 * Check for a member existence inside a class, the principle is simple :
 * - In first all primitive test are discarded (because they don't have any field)
 * - If the type to test is not a primitive then the traits real implementation is
 * applied : A class name inside the trait implementation class, a class named BaseMixin
 * is declared with a method named after the field name searched.
 * A class named Mixin inheriting from the type to test and the class BaseMixin is declared,
 * Then, a helper taking two parameter of the same type is used to indicate if :
 * void (BaseMixin::*)() == &Mixin::FIELD_NAME if it's not the case the it means that the class
 * to test has a field with this name, this lead to an ambiguity which is used by the classic
 * discriminating type function trick in cujunction with sizeof.
 *
 * Anyway, declare the trait using the LBB_DECLARE_HAS_MEMBER_TRAITS with parameter :
 * \param TRAITS_NAME name use to call the trait
 * \param MEMBER_NAME field name to test
 *
 * now the traits TRAITS_NAME can be called like that :
 * TRAITS_NAME<TypeToTest> which is a classic boolean metafunction returning a type
 * containing the result
 */
#define LBB_DECLARE_HAS_MEMBER_TRAITS(TRAITS_NAME, MEMBER_NAME) \
template <class TraitsType> \
class TRAITS_NAME##_impl_ \
{ \
   class yes { char m;}; \
   class no { yes m[2];}; \
   struct BaseMixin { void MEMBER_NAME(){} }; \
   struct Mixin : public TraitsType, public BaseMixin {}; \
   template <typename type, type t>  class Helper{}; \
   template <class U> \
   static no deduce(U*, Helper<void (BaseMixin::*)(), &U::MEMBER_NAME>* = 0); \
   static yes deduce(...); \
public: \
	enum { value = (sizeof(deduce((Mixin*)(0))) == sizeof(yes)) }; \
	typedef lbb::meta::bool_<(bool) value>		type; \
}; \
template<typename TraitsType> \
struct TRAITS_NAME : lbb::meta::select_meta_type_<typename lbb::meta::is_primitive_<TraitsType>::type, \
										lbb::meta::false_, \
										TRAITS_NAME##_impl_<TraitsType> >::type { }





#endif /* LBB_META_HAS_MEMBER_H_ */
