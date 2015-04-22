#include <boost/geometry/algorithms/area.hpp>
#include <boost/geometry/algorithms/correct.hpp>
#include <boost/geometry/io/io.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/geometry.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_match.hpp>

namespace qi = boost::spirit::qi;
namespace bg = boost::geometry;

using Point   = bg::model::d2::point_xy<double, bg::cs::cartesian>;
using Polygon = bg::model::polygon<Point>;

namespace boost { namespace spirit { namespace traits {
    template <>
    struct assign_to_attribute_from_value<Point, fusion::vector2<double, double> > {
        static void call(fusion::vector2<double, double> const& t, Point& attr) {
            attr = Point(fusion::at_c<0>(t), fusion::at_c<1>(t));
        }
    };
} } }

int main() {
    Polygon poly;

    int npoints, poly_id;

    if (
            (std::cin >> npoints >> poly_id) &&
            (std::cin >> std::noskipws >> qi::phrase_match(qi::repeat(npoints) [qi::attr_cast(qi::double_ >> qi::double_)], qi::blank, poly.outer()))
       )
    {
        bg::correct(poly);
        std::cout << "Polygon: " << bg::wkt(poly)  << "\n";
        std::cout << "Area: "    << bg::area(poly) << "\n";
    }
    else
        std::cout << "Parse failed\n";
}
