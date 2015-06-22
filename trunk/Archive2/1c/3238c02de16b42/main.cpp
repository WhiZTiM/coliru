#include <iostream>
#include <type_traits>
#include <utility>

template <typename T, typename = int>
struct has_resize : std::false_type { };

template <typename T>
struct has_resize <T, decltype( (void) std::declval<T>().resize(1), 0)> : std::true_type { };

struct S1 {int resize; }; 
struct S2 { void resize(std::size_t){} }; 

int main()
{
    std::cout << has_resize<S1>::value << std::endl;
    std::cout << has_resize<S2>::value << std::endl;
}
