#include <vector>
#include <set>
#include <limits>
#include <iostream>
#include <assert.h>

struct Point
{
    double x, y;

	Point(double x, double y) {
		this->x = x;
		this->y = y;
	}
	Point() {}

	bool operator< (const Point &rhs) const {
		return (x < rhs.x);
	}
};

std::ostream &operator<< (std::ostream &lhs, const Point &rhs)
{
    lhs << "Point(" << rhs.x << ", " << rhs.y << ")";
	return lhs;
}

typedef std::set<Point> Skyline;
typedef std::set<Point>::iterator skyline_ptr;

double project(double x, skyline_ptr iterationBegin, skyline_ptr iterationEnd)
{
    std::cout << "\tPROJECT:" << std::endl;
	// Loop through skyline
	skyline_ptr next;
	for (skyline_ptr it = iterationBegin; it != iterationEnd; it ++)
	{
		next = it; next ++;
		std::cout << "\t\tIter. " << *it << std::endl;
		if (next == iterationEnd) return it->y;
		// Check if `x` lies within this point and the next point
		if (x > it->x && x < next->x)
		{
			std::cout << "\t\tMatch. " << it->y << std::endl;
			return it->y;
		}
	}	
	// I REALLY DON'T KNOW WHAT TO DO HERE
	return 0;
}

int main (){
    Skyline s;
    s.insert(Point(0, 4));
    s.insert(Point(2, 2));
    s.insert(Point(3, 0));
    skyline_ptr p = s.begin();
    p ++;
    project(6, p, s.end());
}