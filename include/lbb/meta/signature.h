#ifndef LBB_META_INTROSPECTION_H_
#define LBB_META_INTROSPECTION_H_

#include "meta_type.h"
#include "static_assert.h"
#include "traits.h"
#include "list.h"

namespace lbb {
namespace meta {
namespace introspection_ {

/**
 * Test if a type is a signature ...
 */


//regular type
template<typename T>
struct is_signature_ : false_ { };

//pointer to member
template<typename PointedType, typename Domain>
struct is_signature_<PointedType Domain::*> : false_ { };

//function up to 10 argument ...
template<typename ReturnType>
struct is_signature_<ReturnType (*)()> : true_ { };

template<typename ReturnType, typename Arg0>
struct is_signature_<ReturnType (*)(Arg0)> : true_ { };

template<typename ReturnType, typename Arg0, typename Arg1>
struct is_signature_<ReturnType (*)(Arg0, Arg1)> : true_ { };

template<typename ReturnType, typename Arg0, typename Arg1, typename Arg2>
struct is_signature_<ReturnType (*)(Arg0, Arg1, Arg2)> : true_ { };

template<typename ReturnType, typename Arg0, typename Arg1, typename Arg2, typename Arg3>
struct is_signature_<ReturnType (*)(Arg0, Arg1, Arg2, Arg3)> : true_ { };

template<typename ReturnType, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
struct is_signature_<ReturnType (*)(Arg0, Arg1, Arg2, Arg3, Arg4)> : true_ { };

template<typename ReturnType, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4,
	typename Arg5>
struct is_signature_<ReturnType (*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)> : true_ { };

template<typename ReturnType, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4,
	typename Arg5, typename Arg6>
struct is_signature_<ReturnType (*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)> : true_ { };

template<typename ReturnType, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4,
	typename Arg5, typename Arg6, typename Arg7>
struct is_signature_<ReturnType (*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7)> : true_ { };

template<typename ReturnType, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4,
	typename Arg5, typename Arg6, typename Arg7, typename Arg8>
struct is_signature_<ReturnType (*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)> : true_ { };

template<typename ReturnType, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4,
	typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9>
struct is_signature_<ReturnType (*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9)> : true_ { };


//pointer to member function up to 10 argument ...
template<typename ReturnType, typename Domain>
struct is_signature_<ReturnType (Domain::*)()> : true_ { };

template<typename ReturnType, typename Domain, typename Arg0>
struct is_signature_<ReturnType (Domain::*)(Arg0)> : true_ { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1>
struct is_signature_<ReturnType (Domain::*)(Arg0, Arg1)> : true_ { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2>
struct is_signature_<ReturnType (Domain::*)(Arg0, Arg1, Arg2)> : true_ { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2, typename Arg3>
struct is_signature_<ReturnType (Domain::*)(Arg0, Arg1, Arg2, Arg3)> : true_ { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
struct is_signature_<ReturnType (Domain::*)(Arg0, Arg1, Arg2, Arg3, Arg4)> : true_ { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4,
	typename Arg5>
struct is_signature_<ReturnType (Domain::*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)> : true_ { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4,
	typename Arg5, typename Arg6>
struct is_signature_<ReturnType (Domain::*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)> : true_ { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4,
	typename Arg5, typename Arg6, typename Arg7>
struct is_signature_<ReturnType (Domain::*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7)> : true_ { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4,
	typename Arg5, typename Arg6, typename Arg7, typename Arg8>
struct is_signature_<ReturnType (Domain::*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)> : true_ { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4,
	typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9>
struct is_signature_<ReturnType (Domain::*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9)> : true_ { };

/* 
 * for const pointer to member function
 */
template<typename ReturnType, typename Domain>
struct is_signature_<ReturnType (Domain::*)() const> : true_ { };

template<typename ReturnType, typename Domain, typename Arg0>
struct is_signature_<ReturnType (Domain::*)(Arg0) const> : true_ { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1>
struct is_signature_<ReturnType (Domain::*)(Arg0, Arg1) const> : true_ { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2>
struct is_signature_<ReturnType (Domain::*)(Arg0, Arg1, Arg2) const> : true_ { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2, typename Arg3>
struct is_signature_<ReturnType (Domain::*)(Arg0, Arg1, Arg2, Arg3) const> : true_ { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
struct is_signature_<ReturnType (Domain::*)(Arg0, Arg1, Arg2, Arg3, Arg4) const> : true_ { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4,
	typename Arg5>
struct is_signature_<ReturnType (Domain::*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5) const> : true_ { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4,
	typename Arg5, typename Arg6>
struct is_signature_<ReturnType (Domain::*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6) const> : true_ { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4,
	typename Arg5, typename Arg6, typename Arg7>
struct is_signature_<ReturnType (Domain::*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7) const> : true_ { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4,
	typename Arg5, typename Arg6, typename Arg7, typename Arg8>
struct is_signature_<ReturnType (Domain::*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8) const> : true_ { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4,
	typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9>
struct is_signature_<ReturnType (Domain::*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9) const> : true_ { };


/**
 * Meta function reserved to the introspection of signatures ...
 */
namespace signature_ {


template<typename T>
struct get_return_type_;

//function up to 10 argument ...
template<typename ReturnType>
struct get_return_type_<ReturnType (*)()> : meta_type_<ReturnType> { };

template<typename ReturnType, typename Arg0>
struct get_return_type_<ReturnType (*)(Arg0)> : meta_type_<ReturnType> { };

template<typename ReturnType, typename Arg0, typename Arg1>
struct get_return_type_<ReturnType (*)(Arg0, Arg1)> : meta_type_<ReturnType> { };

template<typename ReturnType, typename Arg0, typename Arg1, typename Arg2>
struct get_return_type_<ReturnType (*)(Arg0, Arg1, Arg2)> : meta_type_<ReturnType> { };

template<typename ReturnType, typename Arg0, typename Arg1, typename Arg2, typename Arg3>
struct get_return_type_<ReturnType (*)(Arg0, Arg1, Arg2, Arg3)> : meta_type_<ReturnType> { };

template<typename ReturnType, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
struct get_return_type_<ReturnType (*)(Arg0, Arg1, Arg2, Arg3, Arg4)> : meta_type_<ReturnType> { };

template<typename ReturnType, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4,
	typename Arg5>
struct get_return_type_<ReturnType (*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)> : meta_type_<ReturnType> { };

template<typename ReturnType, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4,
	typename Arg5, typename Arg6>
struct get_return_type_<ReturnType (*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)> : meta_type_<ReturnType> { };

template<typename ReturnType, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4,
	typename Arg5, typename Arg6, typename Arg7>
struct get_return_type_<ReturnType (*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7)> : meta_type_<ReturnType> { };

template<typename ReturnType, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4,
	typename Arg5, typename Arg6, typename Arg7, typename Arg8>
struct get_return_type_<ReturnType (*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)> : meta_type_<ReturnType> { };

template<typename ReturnType, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4,
	typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9>
struct get_return_type_<ReturnType (*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9)> : meta_type_<ReturnType> { };


//pointer to member function up to 10 argument ...
template<typename ReturnType, typename Domain>
struct get_return_type_<ReturnType (Domain::*)()> : meta_type_<ReturnType> { };

template<typename ReturnType, typename Domain, typename Arg0>
struct get_return_type_<ReturnType (Domain::*)(Arg0)> : meta_type_<ReturnType> { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1>
struct get_return_type_<ReturnType (Domain::*)(Arg0, Arg1)> : meta_type_<ReturnType> { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2>
struct get_return_type_<ReturnType (Domain::*)(Arg0, Arg1, Arg2)> : meta_type_<ReturnType> { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2, typename Arg3>
struct get_return_type_<ReturnType (Domain::*)(Arg0, Arg1, Arg2, Arg3)> : meta_type_<ReturnType> { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
struct get_return_type_<ReturnType (Domain::*)(Arg0, Arg1, Arg2, Arg3, Arg4)> : meta_type_<ReturnType> { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4,
	typename Arg5>
struct get_return_type_<ReturnType (Domain::*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)> : meta_type_<ReturnType> { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4,
	typename Arg5, typename Arg6>
struct get_return_type_<ReturnType (Domain::*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)> : meta_type_<ReturnType> { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4,
	typename Arg5, typename Arg6, typename Arg7>
struct get_return_type_<ReturnType (Domain::*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7)> : meta_type_<ReturnType> { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4,
	typename Arg5, typename Arg6, typename Arg7, typename Arg8>
struct get_return_type_<ReturnType (Domain::*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)> : meta_type_<ReturnType> { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4,
	typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9>
struct get_return_type_<ReturnType (Domain::*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9)> : meta_type_<ReturnType> { };

/* 
 * for cont pointer to member function 
 */

template<typename ReturnType, typename Domain>
struct get_return_type_<ReturnType (Domain::*)() const> : meta_type_<ReturnType> { };

template<typename ReturnType, typename Domain, typename Arg0>
struct get_return_type_<ReturnType (Domain::*)(Arg0) const> : meta_type_<ReturnType> { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1>
struct get_return_type_<ReturnType (Domain::*)(Arg0, Arg1) const> : meta_type_<ReturnType> { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2>
struct get_return_type_<ReturnType (Domain::*)(Arg0, Arg1, Arg2) const> : meta_type_<ReturnType> { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2, typename Arg3>
struct get_return_type_<ReturnType (Domain::*)(Arg0, Arg1, Arg2, Arg3) const> : meta_type_<ReturnType> { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
struct get_return_type_<ReturnType (Domain::*)(Arg0, Arg1, Arg2, Arg3, Arg4) const> : meta_type_<ReturnType> { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4,
	typename Arg5>
struct get_return_type_<ReturnType (Domain::*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5) const> : meta_type_<ReturnType> { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4,
	typename Arg5, typename Arg6>
struct get_return_type_<ReturnType (Domain::*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6) const> : meta_type_<ReturnType> { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4,
	typename Arg5, typename Arg6, typename Arg7>
struct get_return_type_<ReturnType (Domain::*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7) const> : meta_type_<ReturnType> { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4,
	typename Arg5, typename Arg6, typename Arg7, typename Arg8>
struct get_return_type_<ReturnType (Domain::*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8) const> : meta_type_<ReturnType> { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4,
	typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9>
struct get_return_type_<ReturnType (Domain::*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9) const> : meta_type_<ReturnType> { };




/**
 * Return true_ if the type is a pointer to member and false_ otherwise
 */
template<typename T>
struct is_member_ : false_ { };

//function up to 10 argument ...
template<typename ReturnType>
struct is_member_<ReturnType (*)()> : false_ { };

template<typename ReturnType, typename Arg0>
struct is_member_<ReturnType (*)(Arg0)> : false_ { };

template<typename ReturnType, typename Arg0, typename Arg1>
struct is_member_<ReturnType (*)(Arg0, Arg1)> : false_ { };

template<typename ReturnType, typename Arg0, typename Arg1, typename Arg2>
struct is_member_<ReturnType (*)(Arg0, Arg1, Arg2)> : false_ { };

template<typename ReturnType, typename Arg0, typename Arg1, typename Arg2, typename Arg3>
struct is_member_<ReturnType (*)(Arg0, Arg1, Arg2, Arg3)> : false_ { };

template<typename ReturnType, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
struct is_member_<ReturnType (*)(Arg0, Arg1, Arg2, Arg3, Arg4)> : false_ { };

template<typename ReturnType, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4,
	typename Arg5>
struct is_member_<ReturnType (*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)> : false_ { };

template<typename ReturnType, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4,
	typename Arg5, typename Arg6>
struct is_member_<ReturnType (*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)> : false_ { };

template<typename ReturnType, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4,
	typename Arg5, typename Arg6, typename Arg7>
struct is_member_<ReturnType (*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7)> : false_ { };

template<typename ReturnType, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4,
	typename Arg5, typename Arg6, typename Arg7, typename Arg8>
struct is_member_<ReturnType (*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)> : false_ { };

template<typename ReturnType, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4,
	typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9>
struct is_member_<ReturnType (*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9)> : false_ { };


//pointer to member function up to 10 argument ...
template<typename ReturnType, typename Domain>
struct is_member_<ReturnType (Domain::*)()> : true_ { };

template<typename ReturnType, typename Domain, typename Arg0>
struct is_member_<ReturnType (Domain::*)(Arg0)> : true_ { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1>
struct is_member_<ReturnType (Domain::*)(Arg0, Arg1)> : true_ { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2>
struct is_member_<ReturnType (Domain::*)(Arg0, Arg1, Arg2)> : true_ { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2, typename Arg3>
struct is_member_<ReturnType (Domain::*)(Arg0, Arg1, Arg2, Arg3)> : true_ { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
struct is_member_<ReturnType (Domain::*)(Arg0, Arg1, Arg2, Arg3, Arg4)> : true_ { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4,
	typename Arg5>
struct is_member_<ReturnType (Domain::*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)> : true_ { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4,
	typename Arg5, typename Arg6>
struct is_member_<ReturnType (Domain::*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)> : true_ { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4,
	typename Arg5, typename Arg6, typename Arg7>
struct is_member_<ReturnType (Domain::*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7)> : true_ { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4,
	typename Arg5, typename Arg6, typename Arg7, typename Arg8>
struct is_member_<ReturnType (Domain::*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)> : true_ { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4,
	typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9>
struct is_member_<ReturnType (Domain::*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9)> : true_ { };


/*
 * for const pointer to member function
 */
template<typename ReturnType, typename Domain>
struct is_member_<ReturnType (Domain::*)() const> : true_ { };

template<typename ReturnType, typename Domain, typename Arg0>
struct is_member_<ReturnType (Domain::*)(Arg0) const> : true_ { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1>
struct is_member_<ReturnType (Domain::*)(Arg0, Arg1) const> : true_ { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2>
struct is_member_<ReturnType (Domain::*)(Arg0, Arg1, Arg2) const> : true_ { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2, typename Arg3>
struct is_member_<ReturnType (Domain::*)(Arg0, Arg1, Arg2, Arg3) const> : true_ { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
struct is_member_<ReturnType (Domain::*)(Arg0, Arg1, Arg2, Arg3, Arg4) const> : true_ { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4,
	typename Arg5>
struct is_member_<ReturnType (Domain::*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5) const> : true_ { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4,
	typename Arg5, typename Arg6>
struct is_member_<ReturnType (Domain::*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6) const> : true_ { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4,
	typename Arg5, typename Arg6, typename Arg7>
struct is_member_<ReturnType (Domain::*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7) const> : true_ { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4,
	typename Arg5, typename Arg6, typename Arg7, typename Arg8>
struct is_member_<ReturnType (Domain::*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8) const> : true_ { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4,
	typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9>
struct is_member_<ReturnType (Domain::*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9) const> : true_ { };






/**
 * Return the application class
 */
template<typename T>
struct get_application_class_;


//pointer to member function up to 10 argument ...
template<typename ReturnType, typename Domain>
struct get_application_class_<ReturnType (Domain::*)()> : meta_type_<Domain> { };

template<typename ReturnType, typename Domain, typename Arg0>
struct get_application_class_<ReturnType (Domain::*)(Arg0)> : meta_type_<Domain> { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1>
struct get_application_class_<ReturnType (Domain::*)(Arg0, Arg1)> : meta_type_<Domain> { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2>
struct get_application_class_<ReturnType (Domain::*)(Arg0, Arg1, Arg2)> : meta_type_<Domain> { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2, typename Arg3>
struct get_application_class_<ReturnType (Domain::*)(Arg0, Arg1, Arg2, Arg3)> : meta_type_<Domain> { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
struct get_application_class_<ReturnType (Domain::*)(Arg0, Arg1, Arg2, Arg3, Arg4)> : meta_type_<Domain> { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4,
	typename Arg5>
struct get_application_class_<ReturnType (Domain::*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)> : meta_type_<Domain> { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4,
	typename Arg5, typename Arg6>
struct get_application_class_<ReturnType (Domain::*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)> : meta_type_<Domain> { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4,
	typename Arg5, typename Arg6, typename Arg7>
struct get_application_class_<ReturnType (Domain::*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7)> : meta_type_<Domain> { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4,
	typename Arg5, typename Arg6, typename Arg7, typename Arg8>
struct get_application_class_<ReturnType (Domain::*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)> : meta_type_<Domain> { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4,
	typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9>
struct get_application_class_<ReturnType (Domain::*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9)> : meta_type_<Domain> { };

/*
 * For const pointer to member 
 */

template<typename ReturnType, typename Domain>
struct get_application_class_<ReturnType (Domain::*)() const> : meta_type_<Domain> { };

template<typename ReturnType, typename Domain, typename Arg0>
struct get_application_class_<ReturnType (Domain::*)(Arg0) const> : meta_type_<Domain> { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1>
struct get_application_class_<ReturnType (Domain::*)(Arg0, Arg1) const> : meta_type_<Domain> { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2>
struct get_application_class_<ReturnType (Domain::*)(Arg0, Arg1, Arg2) const> : meta_type_<Domain> { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2, typename Arg3>
struct get_application_class_<ReturnType (Domain::*)(Arg0, Arg1, Arg2, Arg3) const> : meta_type_<Domain> { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
struct get_application_class_<ReturnType (Domain::*)(Arg0, Arg1, Arg2, Arg3, Arg4) const> : meta_type_<Domain> { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4,
	typename Arg5>
struct get_application_class_<ReturnType (Domain::*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5) const> : meta_type_<Domain> { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4,
	typename Arg5, typename Arg6>
struct get_application_class_<ReturnType (Domain::*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6) const> : meta_type_<Domain> { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4,
	typename Arg5, typename Arg6, typename Arg7>
struct get_application_class_<ReturnType (Domain::*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7) const> : meta_type_<Domain> { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4,
	typename Arg5, typename Arg6, typename Arg7, typename Arg8>
struct get_application_class_<ReturnType (Domain::*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8) const> : meta_type_<Domain> { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4,
	typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9>
struct get_application_class_<ReturnType (Domain::*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9) const> : meta_type_<Domain> { };




/**
 * return the list of the parameters ...
 */
template<typename T>
struct get_parameters_;


//function up to 10 argument ...
template<typename ReturnType>
struct get_parameters_<ReturnType (*)()> : type_list_::nil_ { };

template<typename ReturnType, typename Arg0>
struct get_parameters_<ReturnType (*)(Arg0)> : type_list_::create_<Arg0>::type { };

template<typename ReturnType, typename Arg0, typename Arg1>
struct get_parameters_<ReturnType (*)(Arg0, Arg1)> : type_list_::create_<Arg0, Arg1>::type { };

template<typename ReturnType, typename Arg0, typename Arg1, typename Arg2>
struct get_parameters_<ReturnType (*)(Arg0, Arg1, Arg2)> : type_list_::create_<Arg0, Arg1, Arg2>::type { };

template<typename ReturnType, typename Arg0, typename Arg1, typename Arg2, typename Arg3>
struct get_parameters_<ReturnType (*)(Arg0, Arg1, Arg2, Arg3)> :
type_list_::create_<Arg0, Arg1, Arg2, Arg3>::type { };

template<typename ReturnType, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
struct get_parameters_<ReturnType (*)(Arg0, Arg1, Arg2, Arg3, Arg4)> :
type_list_::create_<Arg0, Arg1, Arg2, Arg3, Arg4>::type { };

template<typename ReturnType, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4,
	typename Arg5>
struct get_parameters_<ReturnType (*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)> :
type_list_::create_<Arg0, Arg1, Arg2, Arg3, Arg4, Arg5>::type { };

template<typename ReturnType, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4,
	typename Arg5, typename Arg6>
struct get_parameters_<ReturnType (*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)> :
type_list_::create_<Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6>::type { };

template<typename ReturnType, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4,
	typename Arg5, typename Arg6, typename Arg7>
struct get_parameters_<ReturnType (*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7)> :
type_list_::create_<Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>::type { };

template<typename ReturnType, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4,
	typename Arg5, typename Arg6, typename Arg7, typename Arg8>
struct get_parameters_<ReturnType (*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)> :
type_list_::create_<Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8>::type { };

template<typename ReturnType, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4,
	typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9>
struct get_parameters_<ReturnType (*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9)> :
type_list_::create_<Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9>::type { };


//pointer to member function up to 10 argument ...
template<typename ReturnType, typename Domain>
struct get_parameters_<ReturnType (Domain::*)()> : type_list_::create_<Domain>::type { };

template<typename ReturnType, typename Domain, typename Arg0>
struct get_parameters_<ReturnType (Domain::*)(Arg0)> : type_list_::create_<Domain, Arg0>::type { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1>
struct get_parameters_<ReturnType (Domain::*)(Arg0, Arg1)> : type_list_::create_<Domain, Arg0, Arg1>::type { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2>
struct get_parameters_<ReturnType (Domain::*)(Arg0, Arg1, Arg2)> : type_list_::create_<Domain, Arg0, Arg1, Arg2>::type { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2, typename Arg3>
struct get_parameters_<ReturnType (Domain::*)(Arg0, Arg1, Arg2, Arg3)> :
type_list_::create_<Domain, Arg0, Arg1, Arg2, Arg3>::type { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
struct get_parameters_<ReturnType (Domain::*)(Arg0, Arg1, Arg2, Arg3, Arg4)> :
type_list_::create_<Domain, Arg0, Arg1, Arg2, Arg3, Arg4>::type { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4,
	typename Arg5>
struct get_parameters_<ReturnType (Domain::*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)> :
type_list_::create_<Domain, Arg0, Arg1, Arg2, Arg3, Arg4, Arg5>::type { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4,
	typename Arg5, typename Arg6>
struct get_parameters_<ReturnType (Domain::*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)> :
type_list_::create_<Domain, Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6>::type { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4,
	typename Arg5, typename Arg6, typename Arg7>
struct get_parameters_<ReturnType (Domain::*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7)> :
type_list_::create_<Domain, Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>::type { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4,
	typename Arg5, typename Arg6, typename Arg7, typename Arg8>
struct get_parameters_<ReturnType (Domain::*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)> :
type_list_::create_<Domain, Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8>::type { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4,
	typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9>
struct get_parameters_<ReturnType (Domain::*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9)> :
type_list_::create_<Domain, Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9>::type { };

/*
 * for const pointer to member function 
 */
template<typename ReturnType, typename Domain>
struct get_parameters_<ReturnType (Domain::*)() const> : type_list_::create_<Domain>::type { };

template<typename ReturnType, typename Domain, typename Arg0>
struct get_parameters_<ReturnType (Domain::*)(Arg0) const> : type_list_::create_<Domain, Arg0>::type { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1>
struct get_parameters_<ReturnType (Domain::*)(Arg0, Arg1) const> : type_list_::create_<Domain, Arg0, Arg1>::type { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2>
struct get_parameters_<ReturnType (Domain::*)(Arg0, Arg1, Arg2) const> : type_list_::create_<Domain, Arg0, Arg1, Arg2>::type { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2, typename Arg3>
struct get_parameters_<ReturnType (Domain::*)(Arg0, Arg1, Arg2, Arg3) const> :
type_list_::create_<Domain, Arg0, Arg1, Arg2, Arg3>::type { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
struct get_parameters_<ReturnType (Domain::*)(Arg0, Arg1, Arg2, Arg3, Arg4) const> :
type_list_::create_<Domain, Arg0, Arg1, Arg2, Arg3, Arg4>::type { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4,
	typename Arg5>
struct get_parameters_<ReturnType (Domain::*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5) const> :
type_list_::create_<Domain, Arg0, Arg1, Arg2, Arg3, Arg4, Arg5>::type { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4,
	typename Arg5, typename Arg6>
struct get_parameters_<ReturnType (Domain::*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6) const> :
type_list_::create_<Domain, Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6>::type { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4,
	typename Arg5, typename Arg6, typename Arg7>
struct get_parameters_<ReturnType (Domain::*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7) const> :
type_list_::create_<Domain, Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>::type { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4,
	typename Arg5, typename Arg6, typename Arg7, typename Arg8>
struct get_parameters_<ReturnType (Domain::*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8) const> :
type_list_::create_<Domain, Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8>::type { };

template<typename ReturnType, typename Domain, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4,
	typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9>
struct get_parameters_<ReturnType (Domain::*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9) const> :
type_list_::create_<Domain, Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9>::type { };





/**
 * Return true_ if T is a free function and false_ otherwise
 */
template<typename T>
struct is_free_function_ : bool_<!is_member_<T>::value> { };


template<typename T>
struct arity_ : type_list_::size_<typename get_parameters_<T>::type> { };


}  // namespace signature_



}  // namespace introspection_
}  // namespace meta
}  // namespace lbb


#endif /* LBB_META_INTROSPECTION_H_ */
