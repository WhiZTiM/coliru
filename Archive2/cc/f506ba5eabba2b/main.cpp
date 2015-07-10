#include <boost/thread/future.hpp>
#include <iostream>

int main()
{
    std::cout << BOOST_VERSION << std::endl;
    boost::async(boost::launch::deferred, []{});
}
