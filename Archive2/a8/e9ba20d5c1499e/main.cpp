#include <iostream>
#include <vector>
#include <type_traits>

template <typename T, typename = typename std::enable_if<!std::is_lvalue_reference<T>{}>::type>
void f(T&& v)
{
    std::cout << "rvalue\n";
}

template <typename T>
void f(const T& v)
{  
    std::cout << "lvalue\n";
}

int main ()
{
    std::vector<int> x = {252, 135};
    auto &z = x;
    f(z);
    f(std::vector<int>{});
}
