#include <iostream>
#include <string>
#include <vector>
#include <type_traits>

template<typename T>
struct init_flag_wrapper
{
  friend constexpr int init_flag(init_flag_wrapper<T>);
};

template<typename T>
struct writer 
{
  friend constexpr int init_flag(init_flag_wrapper<T>) 
  {
    return 0;
  }
};

template <typename T, bool B = noexcept(init_flag(init_flag_wrapper<T>()))>
constexpr bool is_init()
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
    static_assert(!is_init<MyStruct<int>>(), "aa");
    MyStruct<int> a;
    static_assert(is_init<MyStruct<int>>(), "aa");
}