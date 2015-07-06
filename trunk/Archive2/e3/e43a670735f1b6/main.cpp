#include <iostream>
#include <cstdint>

struct a
{
    uint16_t bar[128];
};

struct b
{
    uint16_t bar[127];
};

struct c
{
    int test;
    uint16_t bar[128];
};

struct d
{
    int test;
    uint16_t bar[127];
};

struct e
{
    uint16_t bar[128];
    int test;
};

struct f
{
    uint16_t bar[127];
    int test;
};



int main()
{
    std::cout << sizeof(a) << "\t" << sizeof(b) << "\t" << sizeof(c) << "\t" << sizeof(d) << "\t" << sizeof(e) << "\t" << sizeof(f);
}
