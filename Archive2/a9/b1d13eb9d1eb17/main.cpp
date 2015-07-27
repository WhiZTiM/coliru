#include <iostream>
#include <string>

class Foo
{
public:
    int bar;
    Foo() = default;
    Foo(const Foo & f) = default;
    ~Foo() = default;
    Foo(Foo && f) : bar(std::move(f.bar)) { std::cout << "in move"; }
};

void bar(Foo && f)
{
    static Foo bar(std::move(f));
}

int main()
{
    Foo f;
    f.bar = 10;
    bar(std::move(f));
}