#include <iostream>
#include <vector>
#include <type_traits>

template<typename T,
         typename = typename std::enable_if<std::is_rvalue_reference<T>::value>::type>
void f (T &&v) // thought to be rvalue version
{
   // some behavior based on the fact that v is rvalue
   auto p = std::move (v);
   (void) p;
}

template <typename T>
void f (const T &v) // never called
{  
    std::cout << 1;
   auto p = v;
   (void) p;
}

int main ()
{
    std::vector<int> x = {252, 135};
    auto &z = x;
    f(z);
    f(std::vector<int>{});
}
