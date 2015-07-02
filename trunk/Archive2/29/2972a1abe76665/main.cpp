#include <iostream>
#include <type_traits>

#include <boost/range/irange.hpp>
#include <boost/range/numeric.hpp>
#include <boost/range/size.hpp>

int main()
{
    int a[] = {10, 20, 30, 40};
    int b[] = {1, 2, 3, 4, 5};

    std::cout << 
        boost::accumulate(boost::irange<unsigned>(0, boost::size(a)), 0,
                          [&](int acc, int index) {
                            return acc + a[index] * 2 - b[index + 1];
                          })
        << '\n';
}
