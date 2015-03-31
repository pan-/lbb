#ifndef LBB_UTILITY_SAFE_BOOL_H_
#define LBB_UTILITY_SAFE_BOOL_H_


//safe bool idiom, see : http://www.artima.com/cppsource/safebool.html


namespace lbb {
namespace utility {

namespace safe_bool_ {

class base {
  template<typename>
  friend class safe_bool;

protected:
	//the bool type is a pointer to method which can be used in booleaen context
  typedef void (base::*bool_type)() const;

  void invalid_tag() const;
  void true_tag() const {}
};


}

//derived class need to implement the method 

template <typename T> 
class safe_bool : public safe_bool_::base {
public:
  operator bool_type() const {
    return (static_cast<const T*>(this))->boolean_value()
      ? &safe_bool<T>::true_tag : 0;
  }
};


//Avoid conversion to bool between different classes
template <typename T, typename U>
void operator==(const safe_bool<T>& lhs,const safe_bool<U>& rhs) {
    lhs.invalid_tag();
//    return false;
}

//Avoid conversion to bool between different classes
template <typename T,typename U>
void operator!=(const safe_bool<T>& lhs,const safe_bool<U>& rhs) {
  lhs.invalid_tag();
//  return false;
}


}
}


#endif /* LBB_UTILITY_SAFE_BOOL_H_ */
