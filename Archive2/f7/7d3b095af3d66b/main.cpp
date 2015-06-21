#include <iostream>

#include <boost/optional.hpp>

void foo(int& x)
{
    x = 3;
}

int main() {
    boost::optional<int> y;
    foo(*y);
    std::cout << *y << std::endl;
}