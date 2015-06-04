#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/ring.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/segment.hpp>
#include <boost/geometry/geometries/linestring.hpp>
#include <boost/geometry/multi/geometries/multi_point.hpp>
#include <boost/geometry/multi/geometries/multi_linestring.hpp>
#include <boost/geometry/geometry.hpp>
#include <boost/geometry/geometries/geometries.hpp>
#include <boost/geometry/algorithms/intersection.hpp>

namespace bg = boost::geometry;

using value_type       = double;
using cs_type          = bg::cs::cartesian;
using point_type       = bg::model::point<value_type, 2, cs_type>;
using polygon_type     = bg::model::ring<point_type>;
using line_string_type = bg::model::linestring<point_type>;
using multi_line_type  = bg::model::multi_linestring<line_string_type>;

int main()
{
    line_string_type line;
    line.push_back(point_type{13.37688020921095, 53.66231710654281});
    line.push_back(point_type{13.3857295713429,  53.6636835518369});
    line.push_back(point_type{13.39213495232734, 53.66501934623722});
    line.push_back(point_type{13.39719615524716, 53.66546436809296});
    line.push_back(point_type{13.40724694386097, 53.66240690770171});
    bg::correct(line);

    polygon_type polygon;
    polygon.push_back(point_type{13.35, 53.64});
    polygon.push_back(point_type{13.39, 53.64});
    polygon.push_back(point_type{13.39, 53.68});
    polygon.push_back(point_type{13.35, 53.68});
    polygon.push_back(point_type{13.35, 53.64});
    bg::correct(polygon);

    multi_line_type intersection;
    bg::intersection(line, polygon, intersection);

    std::cout << bg::wkt(intersection);
}
