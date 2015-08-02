#include <iostream>

template <int X>
struct Foo
{
    static void foo()
    {
        std::cout << "foo\n";
    }
};

template <>
struct Foo<42>
{
    static void foo()
    {
        std::cout << "bar\n";
    }
};

int main()
{
    Foo<100>::foo();
    Foo<42>::foo();
}
