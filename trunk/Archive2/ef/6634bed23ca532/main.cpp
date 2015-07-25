#include <type_traits>
#include <cstddef>
#include <iostream>

template <class T, std::size_t N = std::extent<T>::value >
struct total_elements 
{
    using M_type = typename std::remove_extent<T>::type;
	static constexpr std::size_t value = N * total_elements< M_type >::value;
};

// We stop the recursions when we've removed all the []
template <class T>
struct total_elements<T, 0> : std::integral_constant<std::size_t, 1> {};
	

int main()
{
	static_assert( total_elements<double[5][10][3][8]>::value == 5*10*3*8, "");
}

//