#include <iostream>
#include <boost/type_index.hpp>
 
template <typename T>
void print_with_boost()
{
    std::cout << boost::typeindex::type_id_with_cvr<T>().pretty_name() << std::endl;
}

template <typename T>
void print_with_macro()
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

int main()
{
    auto i{ 1, 2, 3 };
    print_with_boost<decltype(i)>();
    print_with_macro<decltype(i)>();
} 
