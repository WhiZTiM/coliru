#include <iostream>
#include <type_traits>

template <typename T>
struct Foo
{
};

struct Bar : public Foo<int>
{
};

bool is_foo(...) { return false; }

template <typename T>
bool is_foo(const Foo<T>&) { return true; }

int main()
{
    Bar b;
    
    std::cout << is_foo(b) << std::endl;
}