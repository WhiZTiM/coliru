#include <iostream>
#include <string>
#include <vector>
#include <cassert>

template<class P, class V>
struct bound_named_parameter {
    V v;
};

template<class P>
struct parameter_tag {
    template<class V>
    bound_named_parameter<P, V> operator=(V&& value) {
        return bound_named_parameter<P, V>{ std::forward<V>(value) };
    }
};

template<class P, class V, class ...NamedParams>
auto required(parameter_tag<P>, bound_named_parameter<P, V>& bnp, NamedParams&&...) -> V {
    return std::forward<V>(bnp.v);
}
template<class P, class H, class ...Tail>
auto required(parameter_tag<P> tag, H&&, Tail&&... tail) -> decltype(auto) {
    return required(tag, std::forward<Tail>(tail)...);
}

template<class P, class V, class U, class ...NamedParams>
auto optional(parameter_tag<P>, U&&, bound_named_parameter<P, V>& bnp, NamedParams&&...) -> V {
    return std::forward<V>(bnp.v);
}
template<class P, class U, class H, class ...Tail>
auto optional(parameter_tag<P> tag, U&& default_, H&&, Tail&&... tail) -> decltype(auto) {
    return optional(tag, std::forward<U>(default_), std::forward<Tail>(tail)...);
}
template<class P, class U>
auto optional(parameter_tag<P> tag, U&& default_) -> U&& {
    return std::forward<U>(default_);
}

#define DEFINE_NAMED_PARAM(NAME) struct NAME ## named_param_type; static parameter_tag<NAME ## named_param_type> NAME ## _;

DEFINE_NAMED_PARAM(x)
DEFINE_NAMED_PARAM(y)

template<class ...NamedParams>
std::pair<int, int> mk_coords(NamedParams&&... namedParams) {
    auto y = required(y_, namedParams...);
    auto x = optional(x_, y, namedParams...);
    
    return {x, y};
}

std::ostream& operator<<(std::ostream& ost, const std::pair<int, int>& p) {
    return ost << p.first << ',' << p.second;
}

DEFINE_NAMED_PARAM(src)
DEFINE_NAMED_PARAM(dst)

template<class ...NamedParams>
void assign(NamedParams&&... named) {
    auto&& src = required(src_, named...);
    auto&& dst = required(dst_, named...);
    
    static_assert(std::is_lvalue_reference<decltype(dst)>::value, "assign expects a reference as dst_");
    
    dst = src;
}

DEFINE_NAMED_PARAM(a)
DEFINE_NAMED_PARAM(b)
DEFINE_NAMED_PARAM(c)

static struct from_parameters_t{} from_parameters;

struct foo {
    int a;
    int b;
    std::vector<int> c;
    
    foo(const foo&) = default;
    foo(foo&&) = default;
    foo() = default;
    
    template<class ...NamedParams>
    foo(from_parameters_t, NamedParams&&... named):
        a(optional(a_, 1, named...)),
        b(optional(b_, 1, named...)),
        c(optional(c_, 0, named...)){}
            
    template<class ...NamedParams>
    foo copy(NamedParams&&... named) {
        foo tmp;
        tmp.a = optional(a_, this->a, named...);
        tmp.b = optional(b_, this->b, named...);
        tmp.c = optional(c_, this->c, named...);
        return tmp;
    }
};

int main()
{
    auto p1 = mk_coords(x_ = 2, y_ = 3);
    auto p2 = mk_coords(y_ = 42);
    
    std::cout << p1 << std::endl;
    std::cout << p2 << std::endl;
    
    int x = 52;
    assign(dst_ = x, src_ = 3);
    assert(x == 3);
    
    foo bar{ from_parameters, 
             a_ = 1, b_ = 2 };
    foo baz = bar.copy(b_ = 42);
    std::cout << baz.b << std::endl;
    assert(baz.a == 1);
    assert(baz.b == 42);
    
    foo fee{ from_parameters, c_ = std::vector<int>{1,2,3,4} };
    assert(fee.c[2] == 3);
    std::cout << fee.c.size() << std::endl;
    
    foo bee = fee;
    std::cout << bee.c.size() << std::endl;
}
