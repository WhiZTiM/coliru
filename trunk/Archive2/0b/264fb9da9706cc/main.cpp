template<typename X>
struct T
{
    constexpr T(double) {}
    constexpr T(T const&) {}
    
    void operator=(T const&) = delete;
};

struct foo;
struct bar;

template<typename T> struct tag {};

#include <utility>
using std::forward;


struct storage
{
    union
    {
        T<foo> f;
        T<bar> b;
    };
    
    bool isFoo;
    
    constexpr storage(tag<foo>, double d) : f(d), isFoo(true) {}
    constexpr storage(tag<foo>, storage const& s) : f(s.f), isFoo(true) {}
    
    constexpr storage(tag<bar>, double d) : b(d), isFoo(true) {}
    constexpr storage(tag<bar>, storage const& s) : b(s.b), isFoo(true) {}
};

template<typename... Args>
constexpr storage make_storage(bool isFoo, Args&&... args)
{
    if(isFoo) return {tag<foo>{}, forward<Args>(args)...};
    else return {tag<bar>{}, forward<Args>(args)...};
}

template<typename... Args>
constexpr storage make_storage(storage const& s)
{
    if(s.isFoo) return {tag<foo>{}, s};
    else return {tag<bar>{}, s};
}

int main()
{
    auto&& v0 = make_storage(true, 4.2);
    auto&& v1 = make_storage(v0);
}