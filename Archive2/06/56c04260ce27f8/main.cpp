#include <iostream>
#include <string>
#include <vector>
#include <type_traits>

template<typename T>
struct inst_check_wrapper
{
    friend constexpr int inst_flag(inst_check_wrapper<T>);
};

template<typename T>
struct writer 
{
    friend constexpr int inst_flag(inst_check_wrapper<T>) 
    {
        return 0;
    }
};

template <typename T, bool B = noexcept(inst_flag(inst_check_wrapper<T>()))>
constexpr bool is_instantiated()
{
    return B;
}

template <typename T>
struct MyStruct
{
};

template <typename T>
struct noswitch_instantiation
{
    using Type = T;
};

template <typename T, int = sizeof(writer<T>)>
struct switch_instantiation
{
    using Type = T;
};

int main () 
{
    static_assert(!is_instantiated<noswitch_instantiation<MyStruct<int>>::Type>(), "failure");
    std::cout << sizeof(switch_instantiation<MyStruct<int>>::Type);
    static_assert(is_instantiated<noswitch_instantiation<MyStruct<int>>::Type>(), "failure");
}