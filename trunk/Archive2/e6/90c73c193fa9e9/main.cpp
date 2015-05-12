#include <iostream>

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/for_each.hpp>

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/adapted/boost_fusion.hpp>




struct sample_point
{
    double x, y, z;
};

BOOST_FUSION_ADAPT_STRUCT(sample_point, (double, x) (double, y) (double, z))
BOOST_GEOMETRY_REGISTER_BOOST_FUSION_CS(cs::cartesian)

int main()
{
    sample_point a, b;

    // Set coordinates the Boost.Geometry way (one of the ways)
    boost::geometry::assign_values(a, 3, 2, 1);

    // Set coordinates the native way
    b.x = 9;
    b.y = 8;
    b.z = 7;

    std::cout << "Distance a-b: " << boost::geometry::distance(a, b) << std::endl;
    
    boost::fusion::for_each(a,[](double val){std::cout << "=" << val << std::endl;});

    return 0;
}
