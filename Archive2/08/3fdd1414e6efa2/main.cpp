#include <iostream>

struct foo
{
    int bar(int x) { return x; }  
};

template<typename T>
struct traits
{
    static constexpr auto bar = &T::bar;
};

int main()
{
   foo x;
   std::cout << (x.*traits<foo>::bar)(42) << std::endl;
}