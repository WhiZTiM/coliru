#include <vector>
#include <utility>
#include <iostream>
#include <algorithm>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/index/rtree.hpp>

namespace bg = boost::geometry;
namespace bgi = boost::geometry::index;

using  point   = bg::model::point < float, 2, bg::cs::cartesian > ;
using  pointI  = std::pair<point, std::size_t>; 

struct distance_pred
{
    pointI const& _base; 
	double        _threshold; 

	distance_pred(pointI const& base, double max_dist)
		: _base(base)
		, _threshold(max_dist)
	{
	}
	bool operator()(pointI const& p) const
	{
        auto d = boost::geometry::distance(_base.first, p.first); 
		return d && d < _threshold; 
	}
};

std::ostream& operator<<(std::ostream &os, pointI const& p)
{
	os << "{ " << p.first.get<0>() << ", " << p.first.get<1>() << " }"; 
	return os; 
}

pointI mp(double x, double y, std::size_t index)
{
    return std::make_pair(point(x, y), index); 
}

int main()
{
	std::vector<pointI> cloud {
		mp(100, 150, 0), mp(101, 152, 1), mp(102, 151, 2), 
		mp(105, 155, 3), mp( 50,  50, 4), mp( 51,  55, 5), 
		mp( 55,  55, 6), mp(150, 250, 7), mp(190, 260, 8) 
	}; 

	bgi::rtree<pointI, bgi::quadratic<16>> rtree(cloud.begin(), cloud.end());

	std::vector<pointI> hood;
    std::vector<std::size_t> rec; 
	for (std::size_t i(0); i < cloud.size(); ++i) if (rec.end() == std::find(rec.begin(), rec.end(), i))
	{
		hood.clear(); 
        auto &p = cloud[i]; 
		std::cout << "neighborhood of point " << p << "\n-----------------\n\n";

		rtree.query(bgi::satisfies(distance_pred(p, 5)), std::back_inserter(hood)); 

        // exlude neighborhood from following queries  
        std::for_each(hood.begin(), hood.end(), [&rec](auto &&pt) {
                rec.push_back(pt.second);   
        }); 

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