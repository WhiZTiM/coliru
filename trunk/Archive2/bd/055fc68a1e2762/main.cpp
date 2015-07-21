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
    
    static parameter_tag<P>& get() {
        static parameter_tag<P> instance;
        return instance;
    }
};

#define DEFINE_NAMED_PARAM(NAME) struct NAME ## named_param_type; static auto& NAME ## _ = parameter_tag<NAME ## named_param_type>::get();

DEFINE_NAMED_PARAM(x)
DEFINE_NAMED_PARAM(y)

template<class P, class V, class ...NamedParams>
auto required(parameter_tag<P>, bound_named_parameter<P, V>&& bnp, NamedParams&&...) -> V {
    return std::forward<V>(bnp.v);
}
template<class P, class H, class ...Tail>
auto required(parameter_tag<P> tag, H&&, Tail&&... tail) -> decltype(auto) {
    return required(tag, std::forward<Tail>(tail)...);
}

template<class P, class V, class U, class ...NamedParams>
auto optional(parameter_tag<P>, U&&, bound_named_parameter<P, V>&& bnp, NamedParams&&...) -> V {
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

template<class ...NamedParams>
std::pair<int, int> mk_coords(NamedParams&&... namedParams) {
    auto y = required(y_, std::forward<NamedParams>(namedParams)...);
    auto x = optional(x_, y, std::forward<NamedParams>(namedParams)...);
    
    return {x, y};
}

std::ostream& operator<<(std::ostream& ost, const std::pair<int, int>& p) {
    return ost << p.first << ',' << p.second;
}

DEFINE_NAMED_PARAM(src)
DEFINE_NAMED_PARAM(dst)

template<class ...NamedParams>
void assign(NamedParams&&... named) {
    auto&& src = required(src_, std::forward<NamedParams>(named)...);
    auto&& dst = required(dst_, std::forward<NamedParams>(named)...);
    
    dst = src;
}

int main()
{
    auto p1 = mk_coords(x_ = 2, y_ = 3);
    auto p2 = mk_coords(y_ = 42);
    
    std::cout << p1 << std::endl;
    std::cout << p2 << std::endl;
    
    int x = 52;
    assign(dst_ = x, src_ = 3);
    assert(x == 3);
}
