#include <iostream>
#include <vector>
#include <cassert>

template<class T, class Index>
struct has_subscript_operator_impl
{
  template<class T1,
           class IndexDeduced = Index,
           class Reference = decltype(
             (*std::declval<T*>())[std::declval<IndexDeduced>()]
           ),
           class = typename std::enable_if<
             !std::is_void<Reference>::value
           >::type>
  static std::true_type test(int);

  template<class>
  static std::false_type test(...);

  using type = decltype(test<T>(0));
};


template<class T, class Index>
using has_subscript_operator = typename has_subscript_operator_impl<T,Index>::type;

struct doesnt_have_it {};

struct returns_void
{
  void operator[](int) {}
};

struct returns_int
{
  int operator[](int) { return 0; }
};

int main()
{
  std::cout << "has_subscript_operator<doesnt_have_it,int>: " << has_subscript_operator<doesnt_have_it,int>::value << std::endl;
  assert((!has_subscript_operator<doesnt_have_it,int>::value));

  std::cout << "has_subscript_operator<returns_void,int>: " << has_subscript_operator<returns_void,int>::value << std::endl;
  assert((!has_subscript_operator<returns_void,int>::value));

  std::cout << "has_subscript_operator<returns_int,int>: " << has_subscript_operator<returns_int,int>::value << std::endl;
  assert((has_subscript_operator<returns_int,int>::value));

  std::cout << "has_subscript_operator<int*,int>: " << has_subscript_operator<int*,int>::value << std::endl;
  assert((has_subscript_operator<int*,int>::value));

  std::cout << "has_subscript_operator<std::vector<int>,int>: " << has_subscript_operator<std::vector<int>,int>::value << std::endl;
  assert((has_subscript_operator<returns_int,int>::value));

  return 0;
}
