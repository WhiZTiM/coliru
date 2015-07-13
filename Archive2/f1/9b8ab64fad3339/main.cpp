#include <iostream>

template<typename T> struct
Identity
{
  using type = T;
};

template<typename T> constexpr void F (T) { std::cout << "a" ;}
template<typename T> constexpr void F (typename Identity<T>::type) { std::cout << "b";}

int main ()
{
   F (0);
   F<int>(0);
}