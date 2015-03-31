#ifndef LBB_META_CALLCHECKER_H_
#define LBB_META_CALLCHECKER_H_

#include "has_member.h"

//stolen from : https://groups.google.com/forum/?fromgroups=#!msg/comp.lang.c++.moderated/T3x6lvmvvkQ/mfY5VTDJ--UJ

#define LBB_DECLARE_CALL_CHECKER(TRAITS_NAME, METHOD_NAME) \
LBB_DECLARE_HAS_MEMBER_TRAITS(TRAITS_NAME##has_member_, METHOD_NAME); \
\
namespace TRAITS_NAME##detail \
{ \
   template <typename type> \
   class void_exp_result {}; \
   template <typename type, typename U> \
   U const& operator,(U const&, void_exp_result<type>); \
   template <typename type, typename U> \
   U& operator,(U&, void_exp_result<type>); \
   template <typename src_type, typename dest_type> \
   struct clone_constness {  typedef dest_type type; }; \
   template <typename src_type, typename dest_type> \
   struct clone_constness<const src_type, dest_type>  { typedef const dest_type type; }; \
} \
\
template <typename type, typename call_details> \
struct TRAITS_NAME \
{ \
private: \
   class yes {}; \
   class no { yes m[2]; }; \
\
   struct derived : public type \
   { \
     using type::METHOD_NAME; \
     no METHOD_NAME(...) const; \
   }; \
\
   typedef typename TRAITS_NAME##detail::clone_constness<type, derived>::type derived_type; \
\
   template <typename T, typename due_type> \
   struct return_value_check \
   { \
     static yes deduce(due_type); \
     static no deduce(...); \
     static no deduce(no); \
     static no deduce(TRAITS_NAME##detail::void_exp_result<type>); \
   }; \
\
   template <typename T> \
   struct return_value_check<T, void> \
   { \
     static yes deduce(...); \
     static no deduce(no); \
   }; \
\
   template <bool has, typename F> \
   struct impl \
   { \
     static const bool value = false; \
   }; \
\
   template <typename r> \
   struct impl<true, r()> \
   { \
     static const bool value = sizeof( return_value_check<type, r>::deduce( \
    		 	 	 	 	 	 	 	 	 (((derived_type*)0)->METHOD_NAME(), \
    		 	 	 	 	 	 	 		 TRAITS_NAME##detail::void_exp_result<type>())) \
            							) == sizeof(yes); \
   }; \
\
   template <typename arg1, typename r> \
   struct impl<true, r(arg1)> \
   { \
     static const bool value = sizeof( return_value_check<type, r>::deduce( \
    		 	 	 	 	 	 	 	 	 (((derived_type*)0)->METHOD_NAME(*(arg1*)0), \
    		 	 	 	 	 	 	 		 TRAITS_NAME##detail::void_exp_result<type>())) \
            							) == sizeof(yes); \
   }; \
\
public: \
   static const bool value = impl<TRAITS_NAME##has_member_<type>::value, call_details>::value; \
}

//TODO : more args number check and pass some times to understand the stuff and see if it's flawless or not

#endif /* LBB_META_CALLCHECKER_H_ */
