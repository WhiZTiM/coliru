#include <iostream>

class Foo
{
    Foo();
public:
    static void SomeFunc() { Foo f; }
};

class Bar
{
public:
    Bar() = delete;
    static void SomeFunc() { Bar b; }
};

int main()
{
    Foo::SomeFunc();
    Bar::SomeFunc();
}