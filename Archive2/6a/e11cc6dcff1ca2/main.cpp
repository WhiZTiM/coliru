#include <iostream>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/linestring.hpp>

using namespace boost::geometry;

int main()
{
    using Point = model::d2::point_xy<double>;
    using Rect  = model::linestring<Point>;

    Rect rect;
    rect.insert(rect.end(), {
            Point {  0,  0 },
            Point { 10,  0 },
            Point { 10, 20 },
            Point {  0, 20 },
            Point {  0,  0 },
        });

    std::cout << "distance point within: "     << distance(rect, Point(5, 5))  << '\n'; // 0
    std::cout << "distance point not within: " << distance(rect, Point(15, 5)) << '\n'; // 5
}
