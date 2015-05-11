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
    template <typename T1 = T, int = sizeof(writer<MyStruct<T1>>)>
    MyStruct()
    { }
};

int main () 
{
    static_assert(!is_instantiated<MyStruct<int>>(), "failure");
    MyStruct<int> a;
    static_assert(is_instantiated<MyStruct<int>>(), "failure");
}