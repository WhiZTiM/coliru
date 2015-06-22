#include <boost/assign/list_of.hpp>
#include <boost/array.hpp>
#include <iostream>

int main()
{
    boost::array<int, 3> arr = boost::assign::list_of(0)(1)(2);
    for(int i = 0; i < arr.size(); ++i)
    {
        std::cout << arr[i] << ", ";
    }
}
