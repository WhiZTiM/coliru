#include <type_traits>
#include <string>
#include <iostream>

struct Foo {
    Foo() {}
    Foo(Foo const&) { std::cout << "Copy\n"; }
    Foo(Foo&&) { std::cout << "Move\n"; }
};

Foo can_move()
{
    std::cout << "can move" << std::endl;
    Foo foo;
    return foo;
}

Foo cant_move(Foo&& foo)
{
    std::cout << "cant move" << std::endl;
    return foo;
}

int main() {
    can_move();
    cant_move(Foo{});
}