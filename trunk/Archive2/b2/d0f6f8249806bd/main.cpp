#include <vector>
#include <iostream>
 
 
struct Bar {
    Bar() = default;
    Bar(const Bar&) = delete;
    Bar(Bar&&) = default;
};

struct Foo
{
    Foo() = default;
    Foo(const Foo&) = delete;
    Foo(Foo&&) = default;
    Bar m_bar;    
};

Foo f;
Foo foo() { return {};}
Foo&& bar() { return std::move(f); }
Foo& pub() { return f; }
 
int main()
{
    auto p0 = &pub().m_bar;
    auto p1 = &foo().m_bar;
    auto p2 = &bar().m_bar;
}