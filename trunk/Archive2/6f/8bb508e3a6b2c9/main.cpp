#include <iostream>

#include <boost/geometry/geometry.hpp>
#include <boost/geometry/geometries/geometries.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/algorithms/is_valid.hpp>
#include <boost/geometry/algorithms/transform.hpp>

namespace bg  = boost::geometry;

typedef bg::model::point<double, 2, bg::cs::cartesian> Point2D;
typedef bg::model::polygon<Point2D> Polygon;
//typedef bg::model::box<Point2D> box;

int main() {

    Polygon _poly;
    Polygon _poly2;

    Point2D A(4,3);
    Point2D B(4,5);
    Point2D C(6,5);
    Point2D D(6,3);
    Point2D CLOSE(4,3);

    _poly.outer().push_back(A);
    _poly.outer().push_back(B);
    _poly.outer().push_back(C);
    _poly.outer().push_back(D);

    std::cout << std::boolalpha << bg::is_valid(_poly) << "\n";
    bg::correct(_poly);
    std::cout << std::boolalpha << bg::is_valid(_poly) << "\n";
}
