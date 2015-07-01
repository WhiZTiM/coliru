#include <iostream>
#include <utility>

struct bar
{
    std::string s;
};

struct foo
{
    std::string s;

    operator bar () const &
    {
        std::cout << "L-value\n";
        return bar{s};
    }
    
    operator bar () &&
    {
        std::cout << "R-value\n";
        return bar{std::move(s)};
    }
};


void qux(bar)
{
    std::cout << "qux\n";
}

int main()
{
    foo f;
    qux(f);
    qux(foo{});
}