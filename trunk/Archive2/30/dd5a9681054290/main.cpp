#include <iostream>

auto invoke1 = 
    [](auto&& func, auto&&... params)
    {
        std::forward<decltype(func)>(func)(
            std::forward<decltype(params)>(params)...); 
    };
    
auto invoke2 = 
    [](auto&& func, auto&&... params)
    {
        func(std::forward<decltype(params)>(params)...); 
    };
    
struct foo
{
    void operator()() const &&
    { std::cout << __PRETTY_FUNCTION__ << '\n'; }
    
    void operator()() const &
    { std::cout << __PRETTY_FUNCTION__ << '\n'; }
};

int main()
{
    invoke1(foo{});
    invoke2(foo{});
    
    foo f;
    invoke1(f);
    invoke2(f);
}
