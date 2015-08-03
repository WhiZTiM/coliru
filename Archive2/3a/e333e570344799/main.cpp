#include <tuple>
#include <iostream>

std::pair<bool, int> foo()
{
    return std::make_pair(false, 3);
}

int main()
{
    int x;
    bool y;

    std::tie(y, x) = foo();
    std::cout << x << ',' << y << '\n';
}