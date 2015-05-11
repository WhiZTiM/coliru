#include <iostream>
#include <utility>
#include <array>

template<int...Is>
constexpr auto make_array(std::integer_sequence<int, Is...> param) // this works */
// constexpr auto make_array(std::integer_sequence<int, Is...> param) // doesn't compile
{
    return std::array<int, sizeof...(Is)> {{Is...}};
}

int main()
{
    constexpr std::integer_sequence<int, 1,2,3,4> iseq = {};

    // If I pass by value, error: the value of 'iseq' is not usable in a constant expression
    constexpr auto arr = make_array(iseq);

    for(auto elem: arr)
        std::cout << elem << " ";
}
