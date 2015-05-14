#include <type_traits>
#include <iostream>

const int global = 0;
const int* const test1() { return &global; }

struct A{};
const A test2() { return {}; }

int main()
{
    auto           temp1 = test1();
    decltype(auto) temp2 = test1();
    static_assert(std::is_same<const int*, decltype(temp1)>{}, "1");
    static_assert(std::is_same<const int*, decltype(temp2)>{}, "2");
    
    auto           temp3 = test2();
    decltype(auto) temp4 = test2();
    static_assert(std::is_same<A,       decltype(temp3)>{}, "3");
    static_assert(std::is_same<const A, decltype(temp4)>{}, "4");
}
