#include <functional>

#include <iostream>

struct fot
{
    void operator()() { std::cout << __PRETTY_FUNCTION__ << "\n"; }
    void operator()() const { std::cout << __PRETTY_FUNCTION__ << "\n"; }
};

int main()
{
    auto l = [](auto&& x) -> decltype(auto) { return decltype(x)(x)(); };
    fot f;
    auto b = std::bind(l, f);
    auto const& c = b;
    
    b();
    c();
}