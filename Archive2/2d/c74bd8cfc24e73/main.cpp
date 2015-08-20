#include <iterator>

template<typename... Args>
struct base;

template<typename Head>
struct base<Head> : Head
{
    using Head::foo;
};

template<typename Head, typename... Tail>
struct base<Head, Tail...> : Head, base<Tail...>
{
    using base<Tail...>::foo;
    using Head::foo;
};

struct A
{
    void foo(std::bidirectional_iterator_tag) {}
};

struct B
{
    void foo(std::random_access_iterator_tag) {}
};

struct C : base<A, B>
{
};

int main()
{
    C c;
    c.foo(std::random_access_iterator_tag{});
}
