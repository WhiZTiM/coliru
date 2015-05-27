#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/algorithm.hpp>

#include <iostream>
#include <functional>
#include <vector>

int foo(int b)  {
    return -b;
}

int main()
{
    std::vector<int> values{1, 2, 3, 2};

    {
        using std::placeholders::_1;
        auto fun = std::bind(&foo, _1);
        int min = *boost::min_element(values | boost::adaptors::transformed(fun));
        std::cout << min << std::endl;
    }
}
