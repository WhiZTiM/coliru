#include <iostream>
#include <cmath>

using namespace std;

// Point class, defined by x and y coordinates
class Point {
    public:
        double x, y;
        Point(double xPos, double yPos)
            : x(xPos)
            , y(yPos)
        { }
        // Calculate distance between points
        double distance(const Point a) const {
            double dX = x - a.x;
            double dY = y - a.y;
            return sqrt(pow(dX,2) + pow(dY,2));
        }

};

// Line class, defined by two endpoints
class Line {
    public:
        Point start, end;
        Line(Point start, Point end)
            : start(start)
            , end(end)
        { }
        // Return length of line
        double length() const {
            return start.distance(end);
        }
        // Return true if point a exists on this line segment
        bool onLine(const Point a) const {
            if (a.x <= max(start.x, end.x) && a.x >= min(start.x, end.x) && a.y <= max(start.y, end.y) && a.y >= min(start.y, end.y)) {
    			double m = gradient();
				double b = yIntercept();
                return a.y == m * a.x + b;
            }
            return false;
        }
        // Return gradient of line
        double gradient() const {
            double dX = start.x - end.x;
            double dY = start.y - end.y;
            return dY/dX;
        }
		double yIntercept() const {
			double m = gradient();
			return start.y - m*start.x;
		}
        // Return orientation of line endpoints & point a
        int orientation(const Point a) const {
            double val = (end.y - start.y) * (a.x - end.x) - (end.x - start.x) * (a.y - end.y);
            if (val == 0) {
                return 0;   // 0 = colinear
            } else if (val > 0) {
                return 1;   // 1 = clockwise
            } else {
                return 2;   // 2 = counter-clockwise
            }
        }
        // Return true if this line intersects line a
        bool intersect(const Line &a) const {
            // Orientations: 0 is colinear, 1 is clockwise, 2 is counter-clockwise
            int o1 = a.orientation(start);
            int o2 = a.orientation(end);
            int o3 = orientation(a.start);
            int o4 = orientation(a.end);
    
            // General case - each line's points are on opposite sides of the other line
            if (o1 != o2 && o3 != o4) {
                return true;
            // Line a and this line's start are colinear and this line's start lies on line a's segment
            } else if (o1 == 0 && a.onLine(start)) {
                return true;
            // Line a and this line's end are colinear and this line's end lies on line a's segment
            } else if (o2 == 0 && a.onLine(end)) {
                return true;
            // This line and a.start are colinear and a.start lies on this line segment
            } else if (o3 == 0 && onLine(a.start)) {
                return true;
            // This line and a.end are colinear and a.end lies on this line segment
            } else if (o4 == 0 && onLine(a.end)) {
                return true;
            }
            return false; // Doesn't fall in any of the above cases
        }
        // Catch-all intersect function in case intersect is called on a higher shape
        template <typename Type>
        bool intersect(const Type &a) const {
            return a.intersect(*this);
        }
};

// Circle class, defined by centre point and radius
class Circle {
    public:
    Point centre;
    double radius;
    Circle(Point centre, double radius)
        : centre(centre)
        , radius(radius)
        { }
    // Return true if this circle intersects line a
    bool intersect(const Line &a) const {
        // Line equation coefficients: y = mx + b
        double m = a.gradient();
        double b = a.yIntercept();
        // Circle equation coefficients: (x - p)^2 + (y - q)^2 = r^2
        double p = centre.x;
        double q = centre.y;
        double r = radius;
        // Quadratic equation coefficients: Ax^2 + Bx + C = 0
        double A = pow(m,2) + 1;
        double B = 2*(m*b - m*q - p);
        double C = pow(q,2) - pow(r,2) + pow(p,2) - 2*b*q + pow(b,2);
        
        // A discriminant < 0 results in imaginary roots, therefore line does not intersect circle
        double discriminant = pow(B,2)-4*A*C;
        if (discriminant < 0) {
            return false;
        }
        
        // Since discriminant >= 0, find roots
        double x1 = (-B+sqrt(discriminant)) / (2*A);
        double y1 = m*x1 + b;
        double x2 = (-B-sqrt(discriminant)) / (2*A);
        double y2 = m*x2 + b;
        
        // If either root exists on line, the line intersects the circle
        if (a.onLine(Point(x1,y1))) { 
            return true;
        } else if (a.onLine(Point(x2,y2))) {
            return true;
        }
        // Otherwise, if neither intesect appear on line segment, shapes do not intersect
        return false;
    }
    // Return true if circle a intersects this circle
    bool intersect(const Circle &a) const {
        double distance = a.centre.distance(centre);
        if (distance <= a.radius + radius) {  
            return true;    
        }
        return false;
    }
    // Catch-all intersect function in case intersect is called on a higher shape
    template <typename Type>
    bool intersect(const Type &a) const {
        return a.intersect(*this);
    }
};

// Rectangle class, defined by lower left and upper right points
class Rectangle {
    public:
        Point lowerLeft, upperRight;
    private:
        Point upperLeft, lowerRight;
        Line topLine, bottomLine, leftLine, rightLine;
    
    public:
        // Initialise object with corner points and edge lines
        Rectangle(Point lowLeft, Point upRight)
            : lowerLeft(lowLeft)
            , upperRight(upRight)
            , upperLeft(Point(lowLeft.x, upRight.y))
            , lowerRight(Point(upRight.x, lowLeft.y))
            , topLine(upperLeft, upperRight)
            , bottomLine(lowerLeft, lowerRight)
            , leftLine(lowerLeft, upperLeft)
            , rightLine(lowerRight, upperRight)

        { }
        // Return true if point a is on or in this rectangle
        bool pointOn(const Point &a) const {
            if (a.x < lowerLeft.x || a.x > upperRight.x) {
                return false;
            } else if (a.y < lowerLeft.y || a.y > upperRight.y) {
                return false;
            }
            return true;
        }
        // Return true if line a is inside this rectangle
        bool isInside(const Line &a) const {
            if (pointOn(a.start)) {
                return true;
            } else if (pointOn(a.end)) {
                return true;
            }
            return false;
        }
        // Return true if circle a is inside this rectangle
        bool isInside(const Circle &a) const {
            return pointOn(a.centre);
        }
        // Return true if any corners of rectangle a are inside this rectangle
        bool isInside(const Rectangle &a) const {
            if (pointOn(a.lowerLeft)) {
                return true;
            } else if (pointOn(a.upperRight)) {
                return true;
            } else if (pointOn(a.upperLeft)) {
                return true;
            } else if (pointOn(a.lowerRight)) {
                return true;
            }
            return false;
        }
        // Return true if shape a intersects with this rectangle
        template <typename Type>
        bool intersect(const Type &a) const {
            // Determine if shape a is inside this rectangle
            if (isInside(a))                return true;
            // If not, do any of the rectangle's lines intersect shape a?
            if (a.intersect(topLine))       return true;
            if (a.intersect(bottomLine))    return true;
            if (a.intersect(leftLine))      return true;
            if (a.intersect(rightLine))     return true;
            // None do, therefore no intersection
            return false;
        }
};

// Function to determine intercept - call intercept method of object a on object b
// If object a is of lesser rank than b, object a will call intercept method of b
template <typename Type1, typename Type2>
bool intersect(const Type1 &a, const Type2 &b) {
    return a.intersect(b);
}

Circle c1(Point(1,0),2);
Circle c2(Point(3,0),2);
Circle c3(Point(0,10),2);
Line l1(Point(3,0),Point(10,7));
Line l2(Point(3,7),Point(10,5));
Line l3(Point(-100,-50),Point(-100,-40));
Rectangle r1(Point(4,-2),Point(6,2));
Rectangle r2(Point(5.5,1),Point(7.5,3));
Rectangle r3(Point(100,90),Point(110,100));
  
template <typename Type>
void printLine(const char* label, const Type a) {
    cout << label; 
    cout << intersect(a,c1) << ",  " << intersect(a,c2) << ",  " << intersect(a,c3) << ",  ";
    cout << intersect(a,l1) << ",  " << intersect(a,l2) << ",  " << intersect(a,l3) << ",  ";
    cout << intersect(a,r1) << ",  " << intersect(a,r2) << ",  " << intersect(a,r3) << endl; 
}

int main()
{
   cout << "    C1, C2, C3, L1, L2, L3, R1, R2, R3" << endl; 
   printLine("C1:  ", c1);
   printLine("C2:  ", c2);
   printLine("C3:  ", c3);
   printLine("L1:  ", l1);
   printLine("L2:  ", l2);
   printLine("L3:  ", l3);
   printLine("R1:  ", r1);
   printLine("R2:  ", r2);
   printLine("R3:  ", r3);
   Line l(Point(1,1),Point(3,3));
   Point p(2,2);
   cout << l.onLine(p);
   intersect(Line({2,1},{3,4}),Circle({0,0},0));
   return 0;
}
