#include <iostream>
#include <utility>

struct Foo
{
    Foo() { std::cout << "Foo()" << std::endl; }
    Foo(int) { std::cout << "Foo(int)" << std::endl; }
};

template <typename T>
struct Bar
{
    Foo foo;

    Bar(const Bar&) { std::cout << "Bar(const Bar&)" << std::endl; }

    template <typename... Args>
    Bar(Args&&... args) : foo(std::forward<Args>(args)...)
    {
        std::cout << "Bar(Args&&... args)" << std::endl;
    }
};

int main()
{
    const Bar<Foo> bar1{};
    Bar<Foo> bar2{bar1};
}