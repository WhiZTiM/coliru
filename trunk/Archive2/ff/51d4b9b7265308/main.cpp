#include <iostream>
#include <string>
#include <vector>
#include <memory>

template<class T>
struct A
{};

template<class T>
struct B
{
    using A = A<T>;
};

int main()
{
    B<int> b;
    
    return 0;
}