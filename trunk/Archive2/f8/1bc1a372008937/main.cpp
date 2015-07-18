template<typename T>
struct some_traits;

template<>
char const* const some_traits<int>::some_string = "int";

#include <iostream>
int main()
{
    std::cout << some_traits<int>::some_string;
}