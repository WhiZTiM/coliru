#include <iostream>
#include <string>
#include <vector>
#include <boost/type_traits.hpp>

template <class T>
void g(const T & t) {
    
}

template <class T, typename boost::enable_if<boost::is_pod<T>, int>::type = 0>
void f() {
  T t = T();
  g(t);
  std::cout << 1;
}

template <class T, typename boost::disable_if<boost::is_pod<T>, int>::type = 0>
void f() {
  T t;
  g(t);
  std::cout << 2;
}

class X
{
    public:
    x(const X&) {}
    private: int z;
};

int main()
{
    f<X>();
}
