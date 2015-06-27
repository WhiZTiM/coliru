#include <iostream>
#include <vector>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <iomanip>

#include <boost/geometry/geometry.hpp>
#include <boost/geometry/geometries/geometries.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/index/rtree.hpp>
#include <boost/random.hpp>
#include <boost/chrono.hpp>

#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics.hpp>

namespace bg  = boost::geometry;
namespace bgi = boost::geometry::index;

double const delta = .05; // so boxes are .1x.1, i.e. 1/100th of total area

typedef bg::model::point<double, 2, bg::cs::cartesian> point;
typedef bg::model::box<point> box;

struct particle {
    double x;
    double y;
};

namespace ba  = boost::accumulators;
namespace bat = ba::tag;
using hrc = boost::chrono::high_resolution_clock;

int main() {
    boost::mt19937 prng(std::random_device{}());
    size_t N = 1000000ul;

    std::vector<particle> myvec;
    myvec.reserve(N);

    {
        boost::uniform_real<double> dist(0,1);

        // Set vector values
        for (size_t i = 0; i<N; ++i)
            myvec.push_back({dist(prng), dist(prng)});
    }

    // Build R-tree
    auto start = hrc::now();

    bgi::rtree<point, bgi::quadratic<16> > rtree;
    for (auto& p : myvec)
        rtree.insert(particle {p.x, p.y});

    auto stop = hrc::now();
    std::cout << "Time for building R tree " << (stop - start) << std::endl;

    // Build Query List
    std::vector<particle> querylist;
    querylist.reserve(100);

    {
        boost::uniform_real<double> dist(0+delta,1-delta);

        for (size_t i = 0; i<100; ++i)
            querylist.push_back({dist(prng), dist(prng)});
    }

    ba::accumulator_set<double, ba::stats<bat::mean, bat::variance>> stats;

    // Query R-tree
    start = hrc::now();
    for (auto cii = querylist.begin(); cii != querylist.end(); ++cii) {
        box query_box({cii->x - delta, cii->y - delta}, {cii->x + delta, cii->y + delta});

#if 0
        std::vector<point> queryresult;
        rtree.query(bgi::intersects(query_box), std::back_inserter(queryresult));

        //std::cout << "The intersection has " << queryresult.size() << " elements:\n";
        stats(queryresult.size());
#else
        auto n = std::distance(
                bgi::qbegin(rtree, bgi::intersects(query_box)),
                bgi::qend(rtree));
        stats(n);
#endif
    }
    stop = hrc::now();
    std::cout << "Time for query " << (stop - start) << "\n";
    std::cout << "Average intersections: " << ba::mean(stats) << "\n";
    std::cout << "Standard deviation:    " << sqrt(ba::variance(stats)) << "\n";

    std::cout << "Expected mean:         " << (N * (2*delta) * (2*delta)) << "\n";
}
