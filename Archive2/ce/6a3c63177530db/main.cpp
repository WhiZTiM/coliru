#include <iterator>

struct A
{
    void foo(std::bidirectional_iterator_tag) {}
};

struct B
{
    void foo(std::random_access_iterator_tag) {}
};

struct C: A, B {
    using A::foo;
    using B::foo;
};

int main()
{
    C c;
    c.foo(std::random_access_iterator_tag{});
}
