// g++ -std=c++11 -Wall main.cpp -o example_boost_geometry_intersection && ./example_boost_geometry_intersection

#include <boost/geometry/algorithms/intersection.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/segment.hpp>
#include <boost/geometry/io/io.hpp>

#include <boost/container/static_vector.hpp>

#include <iostream>
#include <string>

int main()
{
    using namespace std;
    using namespace boost;

    using Point = geometry::model::d2::point_xy<double>;
    using Segment = geometry::model::segment<Point>;

    const Segment test_cases[][2] =
    {
        {{{0., 0.}, {2., 0.}}, {{1., 1.}, {1., -1.}}},
        {{{0., 0.}, {2., 0.}}, {{1., 0.}, {3., 0.}}},
        {{{0., 0.}, {2., 0.}}, {{1., 0.}, {2., 0.}}},
        {{{0., 0.}, {2., 0.}}, {{0., 0.}, {2., 0.}}},
        {{{0., 0.}, {2., 0.}}, {{3., 0.}, {4., 0.}}},
        {{{0., 0.}, {2., 0.}}, {{0., 1.}, {2., 1.}}}
    };

    const string delimiter(32, '_');

    for(const auto &segments : test_cases)
    {
        cout << delimiter << endl
             << "Segments:" << endl;

        for(const auto &segment : segments)
            cout << geometry::wkt(segment) << endl;
        cout << endl;

        container::static_vector<Point, 2> intersections;
        geometry::intersection(segments[0], segments[1], intersections);

        if(not intersections.empty())
        {
            cout << "Intersection points:" << endl;
            for (const auto &point : intersections)
                cout << geometry::wkt(point) << endl;
        }
        else
            cout << "There are no intersection points" << endl;
    }
}