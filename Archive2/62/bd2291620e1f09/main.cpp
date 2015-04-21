#include <type_traits>
#include <vector>
#include <iostream>

struct X {};
void f(X&)  { std::cout << __PRETTY_FUNCTION__ << std::endl; }
void f(X&&) { std::cout << __PRETTY_FUNCTION__ << std::endl; }

namespace detail
{
    template <typename Vector>
    void g(Vector&& v, size_t i, std::true_type /*is_lvalue_reference*/)
    {
       f(v[i]);
    }

    template <typename Vector>
    void g(Vector&& v, size_t i, std::false_type /*not is_lvalue_reference*/)
    {
       f(std::move(v[i]));
    }
}

template <typename Vector>
void g(Vector&& v, size_t i)
{
  detail::g(std::forward<Vector>(v), i, std::is_lvalue_reference<Vector>{});
}

int main()
{
    g(std::vector<X>{{},{}}, 0);
    std::vector<X> v{{},{}};
    g(v, 0);
}