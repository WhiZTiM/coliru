#include <array>
#include <iostream>

template<class T, class... U>
constexpr auto make_array(T t, U&&... us)
{
    constexpr auto N = sizeof...(U) + 1u;
    return std::array<T, N>{{ std::forward<T>(t), std::forward<U>(us)... }};
}

int main()
{
	constexpr auto a = make_array(1, 2, 3, 4, 5);
    
    for(auto&& i : a)
        std::cout << i << '\n';
}
