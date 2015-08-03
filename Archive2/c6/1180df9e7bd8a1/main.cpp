#include <iostream>
#include <vector>

struct T {};

int main()
{
    constexpr int count = 3;
    T* var[count];
    for (int i = 0; i < count; ++i)
        var[i] = new T;
}