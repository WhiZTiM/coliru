#include <iostream>
#include <type_traits>

namespace impl {
    
template <typename T, typename L>
            struct contains;

            template <typename T, template <typename...> class L>
            struct contains<T, L<>> : std::false_type {};

            template <typename T, template<typename...> class L, typename U, typename... Args>
            struct contains<T, L<U, Args...>> : contains<T, L<Args...>> {};

            template <typename T, template<typename...> class L, typename... Args>
            struct contains<T, L<T, Args...>> : std::true_type {};

 
}

       // tells you whether the type list contains the given T  
        template <typename T, typename L>
        using contains = typename impl::contains<T, L>;


template<class...>
class type_list {};

template<class A, class... Rest>
class Foo;

int main()
{
    std::cout << contains<int, type_list<int>>::value << std::endl; // works fine
    std::cout << contains<int, type_list<>>::value << std::endl; // works fine
    std::cout << contains<int, Foo<int>>::value << std::endl; // works fine
    //std::cout << contains<int, Foo<>>::value << std::endl; // blows up
    return 0;
}