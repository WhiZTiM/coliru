#include <vector>
#include <utility>
#include <iostream>
#include <algorithm>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/index/rtree.hpp>

namespace  bg = boost::geometry;
namespace bgi = boost::geometry::index;
using   point = bg::model::point<double, 2, bg::cs::cartesian>;
using  pointI = std::pair<point, std::size_t>;

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
	std::vector<std::size_t> rec; 
	std::vector<pointI> cloud {
		mp(100, 150, 0), mp(101, 152, 1), mp(102, 151, 2),
		mp(105, 155, 3), mp( 50,  50, 4), mp( 51,  55, 5),
		mp( 55,  55, 6), mp(150, 250, 7), mp(190, 260, 8)
	};
	bgi::rtree<pointI, bgi::quadratic<16>> rtree(cloud.begin(), cloud.end());

	for (std::size_t i(0); i < cloud.size(); ++i)
	{
		if (!std::binary_search(rec.begin(), rec.end(), i))
		{     
			auto &p = cloud[i];         
			std::cout << "neighborhood of point " << p << "\n---------------------\n\n";

			std::for_each(rtree.qbegin(bgi::satisfies([&p](pointI const& queryPoint) {
				auto d = boost::geometry::distance(p.first, queryPoint.first);
				return d && d < 5;
			})), rtree.qend(), [&rec](pointI const& pt) {
				rec.push_back(pt.second);
				std::cout << '\t' << pt << std::endl;
			});
			std::cout << std::endl;
		}
	}
}