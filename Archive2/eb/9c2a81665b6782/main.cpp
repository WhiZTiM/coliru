#include <unordered_map>
#include <string>
#include <iostream>
#include <type_traits>

template <class T>
struct is_const_ref
{
     static constexpr int value = std::is_same<T, const T&>::value;
};

int main()
{
    std::cout << is_const_ref<int&>::value << std::endl;
    std::cout << std::is_const<std::remove_reference<int&>::type>::value << std::endl;
    return 0;
}