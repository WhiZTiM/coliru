#include <iostream>
#include <string>
#include <vector>
#include <cstdint>

struct foo
{
    //int test;
    uint16_t bar[128];
};

struct bar
{
    //int test;
    uint16_t bar[127];
};

int main()
{
    std::cout << sizeof(foo) << "\t" << sizeof(bar);
}
