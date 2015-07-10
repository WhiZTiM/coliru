#include <boost/thread/future.hpp>

int main()
{
    boost::async(boost::launch::deferred, []{});
}
