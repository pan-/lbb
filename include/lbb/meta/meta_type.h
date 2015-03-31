#ifndef LBB_META_META_TYPE_H_
#define LBB_META_META_TYPE_H_

/**
 * \file meta_type.h
 * \brief base definition of a meta type
 */

namespace lbb {
namespace meta {

/**
 * base class for identifying meta_types and not allow to instantiate them
 */
class meta_type_base {
	meta_type_base();
	meta_type_base(const meta_type_base&);
	~meta_type_base();
	meta_type_base& operator=(const meta_type_base&);
};

/**
 * Forward the property type of the meta type
 */
template<typename aType>
struct meta_type_ : meta_type_base {
	typedef aType type;
};

/**
 * forward an integral value and the type of the integral value with a metatype
 */
template<typename aType, typename aValueType, int aValue>
struct value_meta_type_ : meta_type_<aType> {
	enum { value = aValue };
	typedef aValueType value_type;
};


/**
 * wrappers around integral types
 */

/**
 * A null type wrapper
 */
struct null_ : value_meta_type_<null_, void*, 0> { };

/**
 * Definition of a boolean as a type
 */
template<bool aValue>
struct bool_ : value_meta_type_<bool_<aValue>, bool, aValue> { };

/**
 * false type
 */
typedef bool_<false>	false_;

/**
 * true type
 */
typedef bool_<true>	true_;



/**
 * Definition of an integer as a type
 */
template<int aValue>
struct int_ : value_meta_type_<int_<aValue>, int, aValue> { };

/**
 * Definition of an unsigned integer as a type
 */
template<unsigned int aValue>
struct unsigned_int_ : value_meta_type_<unsigned_int_<aValue>, unsigned int, aValue> { };


/**
 * logical operators which return bool_
 */

/**
 * logical not
 */
template<typename Operand>
struct not_ : bool_<!(Operand::value)> { };

/**
 * logical or
 */
template<typename Left, typename Right>
struct or_ : bool_<Left::value || Right::value> { };

/**
 * logical nor
 */
template<typename Left, typename Right>
struct nor_ : not_<or_<Left, Right> >  { };

/**
 * logical and
 */
template<typename Left, typename Right>
struct and_ : bool_<Left::value && Right::value> { };

/**
 * logical nand
 */
template<typename Left, typename Right>
struct nand_ : not_<and_<Left, Right> > { };


}  // namespace meta

}  // namespace lbb

#endif /* LBB_META_META_TYPE_H_ */
