#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics.hpp>
#include <boost/accumulators/statistics/rolling_window.hpp>
#include <boost/accumulators/statistics/rolling_mean.hpp>
#include <iostream>

namespace ba = boost::accumulators;
namespace bas = ba::tag;

class test
{
    public:
        test(unsigned char windowSize=5): acc(ba::tag::rolling_window::window_size = windowSize){}
    protected:
        ba::accumulator_set<unsigned short, ba::stats<ba::tag::rolling_mean > >  acc;
    private:
};

int main()
{
    test t;
}
