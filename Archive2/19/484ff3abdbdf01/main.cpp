#include <iostream>
#include <type_traits>

template <typename T>
struct Foo
{
};

struct Bar : public Foo<int>
{
};

template <typename T>
bool is_foo(T) { return false; }

template <typename T>
bool is_foo(const Foo<T>& f) { return true; }

int main()
{
    Bar b;
    
    std::cout << is_foo(b) << std::endl;
}