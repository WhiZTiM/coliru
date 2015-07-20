#include <type_traits>
#include <string>
#include <iostream>

struct Foo {
    Foo() {}
    Foo(Foo const&) { std::cout << "Copy\n"; }
    Foo(Foo&&) { std::cout << "Move\n"; }
};

void change(Foo& foo) {}

Foo bar(Foo&& foo)
{
    change(foo);
    return foo;
}

int main() {
    bar(Foo());
}