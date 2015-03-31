# lbb
Lightweight c++ building blocks and playground for TMP in c++03

This toy project was made to learn c++ template metaprogramming then it derive to provide 
TR1 and some c++11 addons to c++03 compiler. 

This library contains the following utilities : 

- meta : Tools for c++ template meta programming
  - function_ : Compile time introspection of c++ functions (arity, return type, category, ...).
  - has_member : check for a struct/class member existence.
  - list_ : compile time list of type and manipulation functions 
  - meta_type_ : base type of compile time object
  - static_assert : assertion at compile time with "readable" message
  - traits : collection of several traits present in std 

- utility : Collection of some usefull utilities
  - aligned_union : Provide a raw storage usable by an union of POD and non POD types.
  - tuple : revamp of std::tuple
  - move : Allow to easily write "movable" classes by deriving a class with : "movable<MyMovableClass>"
  - not_copyable : Make a class not copyable
  - safe_bool : Generic implementation of the safe bool idiom

- smart_ptr : 
  - unique_ptr<T, Deleter> : c++03 emulation of unique ptr.
  - shared_ptr<T> : a shared pointer (rewriting in progress in order to be compliant with c++ specs).

- functionnal : 
  - bind : implementation of std::bind without rtti or exception
  - function : efficient and easy to understand implementation of std::function without rtti or exceptions
  which can be used on old compiler like gcc4.3 as a dropin replacement for tr1::function.
  - mem_fn : 
  - ref/cref : values which hold references in order to pass reference through bind or std::function calls 
  - result_of : Result of protocol implementation

- concurrency : c++11 threading emulations. 
  - atomic : Atomic implementation of c++11 atomic (poorly implemented)
  - condition_variable : std::condition_variable equivalent
  - future : std::future equivalent except that future::then is implemented and accept a callback in order 
  to trigger an action when the promise is fullfiled.
  lock_guard : std::lock_guard implementation
  - mutex : std::mutex implementation
  - promise : std::promise implementation
  - thread : std::thread implementation
  - unique_lock
  
  
# Build and installation 

```bash
  mkdir build
  cd build
  cmake ..
  make 
  ./test/test_lbb
  make install
```  


