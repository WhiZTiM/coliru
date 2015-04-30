struct alignas(16) foo
{
    char bar[7];
};

struct bar
{
    alignas(2) char buzz[7];
};

#include <iostream>

int main()
{
    std::cout << sizeof(foo) << std::endl;
    std::cout << sizeof(bar) << std::endl;
}
