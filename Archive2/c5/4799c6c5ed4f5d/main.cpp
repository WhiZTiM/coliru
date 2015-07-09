#include <boost/geometry.hpp>
#include <boost/geometry/io/io.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/array.hpp>
#include <vector>
#include <iomanip>
#include <iostream>

namespace bg = boost::geometry;

template <typename C, typename T = typename C::value_type>
    void append(C& container, std::initializer_list<T> init) {
        container.insert(container.end(), init);
    }

int main() {
    typedef bg::model::d2::point_xy<double> TBoostPoint;
    typedef bg::model::polygon<TBoostPoint> TBoostPoly;

    std::vector<TBoostPoly> squares;

    using Eps = boost::array<double, 4>;

    for (auto const& eps : { 
                Eps {{     0,     0,     0,     0 }},
                Eps {{ 1e-15, 1e-15, 2e-15, 2e-15 }},
            })
    {
        TBoostPoly square;
        append(square.outer(), {
             { 0.5,  4.25 + eps[0] },
             { 0.5,   4.5 + eps[1] },
             { 1.0,   4.5 + eps[2] },
             { 1.0,  4.25 + eps[3] },
             { 0.5,  4.25 + eps[0] }
            });

        squares.push_back(std::move(square));
    }

    for (auto& p : squares)
        bg::correct(p);

    std::vector<TBoostPoly> output;
    bg::intersection(squares[0], squares[1], output);

    for (auto& p : output) std::cout << "Output: " << bg::wkt(p) << "\n";
    std::cout << std::fixed << std::setprecision(std::numeric_limits<bg::coordinate_type<TBoostPoint>::type >::max_digits10);
    for (auto& p : output) std::cout << "Output: " << bg::wkt(p) << "\n";
}
