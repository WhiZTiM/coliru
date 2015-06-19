#include <type_traits>
#include <utility>

template <typename T>
struct has_foo_member_function
{        
    template <typename U>
    static auto test(U* u) -> decltype(void(u->foo()), std::true_type{});
        
    template <typename U>
    static auto test(...) -> std::false_type;
    
    static constexpr bool value = decltype(test<T>(0))::value;
};

struct A
{
    void foo() {}
};

struct B
{
};

#include <iostream>
int main()
{
    std::cout << has_foo_member_function<A>::value << std::endl;
    std::cout << has_foo_member_function<B>::value << std::endl;
}
