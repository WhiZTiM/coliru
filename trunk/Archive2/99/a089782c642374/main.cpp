#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/geometries/multi_polygon.hpp>
#include <boost/geometry/io/io.hpp>
#include <boost/geometry/algorithms/intersection.hpp>
#include <boost/geometry/algorithms/correct.hpp>
#include <boost/geometry/algorithms/is_valid.hpp>

namespace bg = boost::geometry;

int main(){
    typedef bg::model::d2::point_xy<double> TPoint;
    typedef bg::model::polygon<TPoint>      TPoly;
    TPoly first, second;

    bg::read_wkt("POLYGON(( 1.504477611940313 3.761194029850755, 1.504477611940305 3.573134328358203, 1.316417910447765 3.573134328358206, 1.316417910447769 3.761194029850752))", first);
    bg::read_wkt("POLYGON(( 1.504477611940313 3.761194029850755, 1.504477611940305 3.573134328358203, 1.316417910447765 3.573134328358206, 1.316417910447751 3.761194029850769))", second); 

    std::string reason;
    // polys not closed!
    if (!bg::is_valid(first, reason))  std::cout << "First polygon not valid: "  << reason << "\n";
    if (!bg::is_valid(second, reason)) std::cout << "Second polygon not valid: " << reason << "\n";

    bg::correct(first);
    bg::correct(second);

    // no more output!
    if (!bg::is_valid(first, reason))  std::cout << "First polygon not valid: "  << reason << "\n";
    if (!bg::is_valid(second, reason)) std::cout << "Second polygon not valid: " << reason << "\n";

    std::vector<TPoly> out;
    bg::intersection(first, second, out);

    for (auto& g : out)
        std::cout << "\nresult: " << bg::wkt(g) << "\n";
}
