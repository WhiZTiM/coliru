#include <iostream>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>

using namespace boost::geometry;

int main()
{
    using Point = model::d2::point_xy<double>;
    using Box = model::box<Point>;

    Box box(Point(0, 0), Point(10, 20));
    std::cout << "distance point within: "     << distance(box, Point(5, 5))  << '\n'; // 0
    std::cout << "distance point not within: " << distance(box, Point(15, 5)) << '\n'; // 5
}
