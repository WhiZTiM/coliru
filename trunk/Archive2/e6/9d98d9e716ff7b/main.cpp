#include <boost/geometry/index/rtree.hpp>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <vector>
#include <iostream>

namespace bg = boost::geometry;
namespace bgi = bg::index;
using  point  = bg::model::point <int, 2, bg::cs::cartesian>;
using  pointI = std::pair<point, std::size_t>;

pointI mp(int x, int y, size_t v) {
    return std::make_pair(point(x,y), v);
}

int main()
{
    std::vector<point> contourCenters; // has some value
    std::vector<pointI> cloud;

    size_t id_gen = 0;
    std::transform(
            contourCenters.begin(), contourCenters.end(),
            back_inserter(cloud), 
            [&](point const& p) { return std::make_pair(p, id_gen++); }
        );

    for(pointI& pi : cloud)
        std::cout << "Contour Centers: (" << bg::get<0>(pi.first) << "," << bg::get<1>(pi.first) << ")";

    bgi::rtree<pointI, bgi::quadratic<16> > rtree(cloud);
}
