#include <vector>
#include <iostream>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/index/rtree.hpp>

namespace bg = boost::geometry;
namespace bgi = boost::geometry::index;

using  point = bg::model::point < float, 2, bg::cs::cartesian > ;

struct distance_pred
{
    point const& _base; 
	double       _threshold; 

	distance_pred(point const& base, double max_dist)
		: _base(base)
		, _threshold(max_dist)
	{
	}
	bool operator()(point const& p) const
	{
        auto d = boost::geometry::distance(_base, p); 
		return d && d < _threshold; 
	}
};

std::ostream& operator<<(std::ostream &os, point const& p)
{
	os << "{ " << p.get<0>() << ", " << p.get<1>() << " }"; 
	return os; 
}

int main()
{
	std::vector<point> cloud {
		point(100, 150), point(101, 152), point(102, 151), 
		point(105, 155), point( 50,  50), point( 51,  55), 
		point( 55,  55), point(150, 250), point(190, 260) 
	}; 

	bgi::rtree<point, bgi::quadratic<16>> rtree(cloud.begin(), cloud.end());

	std::vector<point> hood;
	for (auto &&p : cloud)
	{
		hood.clear(); 
		std::cout << "neighborhood of point " << p << "\n-----------------\n\n";

		rtree.query(bgi::satisfies(distance_pred(p, 5)), std::back_inserter(hood)); 

		if (!hood.empty())
		{
			for (auto &&pt : hood) std::cout << '\t' << pt << std::endl;
		}
		else
		{
			std::cout << "\t... is empty\n"; 
		}

		std::cout << std::endl; 
	}
}