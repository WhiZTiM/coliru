#include <iostream>
#include <type_traits>
#include <cxxabi.h>
#include <typeinfo>
#include <functional>

template <typename T>
const char * type_name()
{
    return abi::__cxa_demangle(typeid(T).name(), nullptr, nullptr, nullptr);
}

template <typename...>
struct vargs {};

struct outer
{
    template <typename T>
    struct inner
    {
        using result = T;
    };
};

template <typename Arg, typename... Args>
struct outer::inner<vargs<Arg, Args...>>
{
    using result = Arg;
};

template <typename T>
using test_t = typename outer::inner<T>::result;

int main()
{
    using t = test_t<vargs<int, char>>;
    std::cout << type_name<t>();
    return 0;
}