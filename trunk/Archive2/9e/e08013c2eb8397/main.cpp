#include <functional>
#include <iostream>
#include <iterator>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <memory>

int main()
{
    auto myptr = std::make_unique<int>(42);

    auto f = std::bind([] (std::unique_ptr<int> p)
    {
        std::cout << *p;
    }, std::move(myptr));
    
    f();
}