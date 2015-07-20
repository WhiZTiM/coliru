#include <iostream>
using namespace std;

class Point {
    double x,y;
public:
    constexpr Point(double xx = 0, double yy = 0) noexcept
    : x(xx), y(yy)
    { }

    constexpr double xValue() const noexcept { return x; }
    constexpr double yValue() const noexcept { return y; }
    constexpr void setX(double newX) noexcept { x = newX; }
    constexpr void setY(double newY) noexcept { y = newY; }
};

constexpr Point reflection(const Point& p) noexcept
{
    Point result;
    result.setX(-p.xValue());
    result.setY(-p.yValue());
    return result;
}

 
constexpr Point bisect(const Point& p1, const Point& p2) noexcept {
    return Point((p1.xValue() + p2.xValue()) / 2,   // call constexpr
             (p1.yValue() + p2.yValue()) / 2 );     // member funcs
}

constexpr Point p1(4, 12);
constexpr Point p2(24, -13);
constexpr Point mid = bisect(p1, p2);

constexpr Point reflected = reflection( bisect(Point(5,4), Point(-7,-9)) );

int main() {
	cout << mid.xValue() << ", " << mid.yValue() << '\n';
    cout << reflected.xValue() << ", " << reflected.yValue();
	constexpr Point origin;
	constexpr Point orig(0,0);
	constexpr int z = orig.xValue();
	constexpr Point diagonal[] = 
			{ Point(-1,-1), orig, Point(1,1) };

	constexpr int x0 = diagonal[1].xValue(); 
	//zero.setX(5);
	Point p(42, 13);
	p.setY(1024);

	return 0;
}