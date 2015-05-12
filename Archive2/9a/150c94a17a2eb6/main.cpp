#include <iostream>
#include <type_traits>

    template<typename...>
    struct are_same : std::true_type 
    {};

    template<typename T>
    struct are_same<T> : std::true_type
    {};

    template<typename T, typename U, typename... Types>
    struct are_same<T, U, Types...> :
        std::integral_constant<bool, (std::is_same<T, U>::value && are_same<T, Types...>::value)>
    {};

int main()
{
    std::cout << are_same<>::value << std::endl;
    
}