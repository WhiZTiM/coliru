#include <iostream>
#include <string>
#include <type_traits>

template <typename T>
class A {
 public:
  T foo(const T &t);
};


template <bool B, typename T = void>
using EnableIf = typename std::enable_if<B, T>::type;

template <typename T>
EnableIf<std::is_arithmetic<T>::value, T> foo_impl(const T& t) {
    return t;
}

std::string foo_impl(const std::string &t) {
    return t;
}

template <typename T>
T A<T>::foo(const T &t) {
    return foo_impl(t);
}

int main()
{
    A<std::string> a;
    std::cout << a.foo("abc");

    A<int> b;
    std::cout << b.foo(34);

    A<float> c;
    std::cout << c.foo(3.4);
}