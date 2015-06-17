#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/algorithms/correct.hpp>
#include <iostream>
#include <iomanip>

void test(bool do_correct) {
    namespace bg = boost::geometry;
    typedef bg::model::d2::point_xy<double>    point_type;
    typedef bg::model::polygon<point_type>     polygon_type;

    polygon_type poly;

    bg::read_wkt( "POLYGON((0 0 0 2 1 2 1 0))", poly);

    if (do_correct)
        bg::correct(poly);

    std::cout << "poly:  " << bg::wkt(poly) << "\n";

    // Rotate poly to get poly2
    bg::strategy::transform::rotate_transformer<bg::degree, double, 2, 2> rotate (180);

    polygon_type poly2;
    bg::transform(poly, poly2, rotate);

    // Print the coordinates of poly2
    std::cout << "poly2: " << bg::wkt(poly2) << "\n";

    // Verify whether poly2 is correctly rotated
    point_type const p2(-2,-2);
    std::cout << "\nDistance between p2 and poly2: " << bg::distance(p2, poly2) << std::endl;
    std::cout << "-------------------------------------------------------------------------------------\n";
}

int main()
{
    std::cout << std::fixed << std::setprecision(0);

    test(false);
    test(true);
}
