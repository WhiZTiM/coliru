#include <iostream>
#include <cstdint>

struct A
{
    const int x;
};

struct B : A
{
    const int y;
};

int main()
{
    B b = { {3}, 4 };
}
