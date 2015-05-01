#include <iostream>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/algorithms/distance.hpp>
#include <boost/geometry/strategies/distance.hpp>


int main() {
    using namespace boost::geometry;
    using P = model::d2::point_xy<float>;
    using V = traits::coordinate_type<P>;

    std::cout << "Coordinate type:  " << typeid(V).name() << "\n";

    P a, b;
    std::cout << "Calculation type: " << typeid(default_distance_result<P, P>::calculation_type).name() << "\n";
    std::cout << "Result type:      " << typeid(default_distance_result<P, P>::type).name()             << "\n";

    using S = strategy::distance::pythagoras<float>;
    std::cout << "Calculation type: " << typeid(distance_result<P, P, S>::calculation_type).name() << "\n";
    std::cout << "Result type:      " << typeid(distance_result<P, P, S>::type).name()             << "\n";
}
