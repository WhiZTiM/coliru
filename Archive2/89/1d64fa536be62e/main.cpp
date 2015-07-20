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

Foo bar()
{
    Foo foo;
    change(foo);
    return foo;
}

int main() {
    std::cout << "calling bar(Foo&&)" << std::endl;
    bar(Foo());
    std::cout << "calling bar()" << std::endl;
    bar();
}