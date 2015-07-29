#include <iostream>
#include <utility>
#include <typeinfo>

// #define MACROS

#ifdef MACROS
#define CALL_FOO(x) x.foo<int>()
#define CALL_FOO_TEMPLATED(x) x.template foo<int>()
#else
template<class X>
auto CALL_FOO(X&& x) -> decltype(std::forward<X>(x).template foo<int>())
{
  return std::forward<X>(x).template foo<int>();
}
#endif

class Plain
{
public:
  template<class T> T foo()
  {
    std::cout << "Plain::foo" << std::endl;
    return T(-1);
  }
};

template<class U>
class Templated
{
public:
  template<class T> U foo()
  {
    std::cout << "Templated<" << typeid(U).name() << ">::foo" << std::endl;
    return U(-1);
  }
};

template<class U = void>
void do_something()
{
  Plain plain;
  CALL_FOO(plain);
  Templated<int> t_int;
  CALL_FOO(t_int);
  Templated<void> t_void;
  CALL_FOO(t_void);
  Templated<U> t_U;
#ifdef MACROS
  CALL_FOO_TEMPLATED(t_U);
#else
  CALL_FOO(t_U);
#endif
}

int main()
{
  do_something();
}
