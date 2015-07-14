#include <iostream>
#include <cxxabi.h>
#include <typeinfo>

template <typename T>
const char * type_name()
{
    return abi::__cxa_demangle(typeid(T).name(), nullptr, nullptr, nullptr);
}

template <typename... Args>
struct vargs {};

namespace details   
{
    template <typename K>
    struct outer
    {
        template <typename Arg>
        struct inner
        {
            using result = Arg;
        };
        
        template <typename Arg, typename... Args>
        struct inner<vargs<Arg, Args...>>;    
    };
}

struct tag {};

namespace details
{
    template <typename K>
    template <typename Arg, typename... Args>
    struct outer<K>::inner<vargs<Arg, Args...>>
    {
        using result = typename outer::template inner<Arg>::result;
    };
}

template <typename T>
using test_t = typename details::outer<tag>::inner<T>::result;

int main()
{
    using t = test_t<vargs<char, int>>;
    std::cout << type_name<t>() << '\n';
    return 0;
}
