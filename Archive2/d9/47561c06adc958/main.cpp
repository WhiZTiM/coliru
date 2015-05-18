#include <cstdio>

enum class A{};
enum class B{};

using POLICY = B;

template <typename T = POLICY>
void foo();

template <>
void foo<A>() 
{
    printf("A\n");
}

template <>
void foo<B>() 
{
    printf("B\n");
}

int main()
{
    foo();
    foo<A>();
    foo<B>();
    
    return 0;
}