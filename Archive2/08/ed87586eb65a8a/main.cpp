#include <iostream>

template <typename T>
auto foo(T t, int) -> decltype(void(t.foo()))
{
    std::cout << "t.foo() istnieje\n";
}

template <typename T>
auto foo(T t, ...) -> void
{
    std::cout << "t.foo() nie istnieje\n";
}

struct A
{
    void foo() {}
};

struct B
{
};

int main()
{
    foo(A{}, 0);
    foo(B{}, 0);
}
