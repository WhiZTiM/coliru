#include <iostream>
using namespace std;
struct Widget {
    int x, n;
    constexpr Widget(int xx, int nn) : x(xx), n(nn) {}
    
    constexpr int X() const { return x;}
    int X() { return x*n;}
};

constexpr Widget cxw(4, 3);
const Widget cw(13, 9);
Widget w(2, 8);

constexpr int cxx = cxw.X(); //4
const int cx = cw.X(); // 13
const int x = w.X();  //16
constexpr int zz1 = cw.X();  // 13
int xx = 42;
const Widget cw2(xx, 0);
constexpr int zz2 = cw2.X();  // the value of 'cw2' is not usable in a constant expression


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

constexpr Point p1(-12, 12);
constexpr Point p2(12, -12);
constexpr Point mid = bisect(p1, p2);

constexpr Point reflected = reflection( bisect(Point(5,4), Point(-7,-9)) );



int main() {
    cout << "cxx " << cxx << " cx " << cx << " x " << x << " zz " << zz << '\n';
	cout << mid.xValue() << ", " << mid.yValue() << '\n';
    cout << reflected.xValue() << ", " << reflected.yValue() << '\n';
    constexpr double xx = bisect(Point(5,5), Point(-3,-3)).xValue();
    cout << xx;
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