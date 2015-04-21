#include <boost/system/error_code.hpp>
#include <iostream>

int main()
{
    boost::system::error_code ec;
    ec.assign(2, boost::system::system_category());
    std::cout << ec.message();
}
