#include <boost/xpressive/xpressive.hpp>

using namespace boost::xpressive;

int main()
{
    constexpr auto d = '<' >> optional('/') >> +_w >> '>';
}