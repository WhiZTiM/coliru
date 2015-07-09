#include <vector>
#include <iostream>

struct Point
{
    int x;
    int y;
};

int square_norm(const Point& p1, const Point& p2)
{
    return (p1.x - p2.x) * (p1.x - p2.x) +
           (p1.y - p2.y) * (p1.y - p2.y);
}

int gcd(int n1, int n2)
{
    n1 = (n1 > 0) ? n1 : -n1;
    n2 = (n2 > 0) ? n2 : -n2;
    
    if (n1 > n2) 
    {
        int t = n1;
        n1 = n2;
        n2 = t; 
    } 

    while (n2 % n1 != 0)
    {
        int tmp = n2 % n1;
        n2 = n1;
        n1 = tmp; 
    }

    return n1;
}

void findLatticePoints(Point p1, Point p2, double sqRadius, std::vector<Point>& oPoints)
{
    Point middle;

    middle.x = p1.x + p2.x; //yes, that seems weird but we will reason in a x2 grid
    middle.y = p1.y + p2.y;

    int dgcd = gcd(p2.y - p1.y, p1.x - p2.x);

    Point minimalDirectionVector;
    minimalDirectionVector.x = (p2.y - p1.y) / dgcd;
    minimalDirectionVector.y = (p1.x - p2.x) / dgcd;

    Point startingPoint;

    if (middle.x % 2 == 0 && middle.y % 2 == 0)
    {
        startingPoint.x = middle.x / 2;
        startingPoint.y = middle.y / 2;
    } 
    else if (((middle.x % 2 == 0 && minimalDirectionVector.x % 2 == 0) &&
              (middle.y % 2 == 1 && minimalDirectionVector.x % 2 == 1)) ||
             ((middle.x % 2 == 0 && minimalDirectionVector.x % 2 == 1) &&
             (middle.y % 2 == 1 && minimalDirectionVector.x % 2 == 0)) ||
             ((middle.x % 2 == 1 && minimalDirectionVector.x % 2 == 1) &&
             (middle.y % 2 == 1 && minimalDirectionVector.x % 2 == 1)))
    {
        startingPoint.x = (middle.x + minimalDirectionVector.x) / 2;
        startingPoint.y = (middle.y + minimalDirectionVector.y) / 2;
    } 
    else
    {
        return; //there is no hope
    }

    oPoints.push_back(startingPoint);

    Point extremalPoint0, extremalPoint1;

    extremalPoint0.x = startingPoint.x;
    extremalPoint0.y = startingPoint.y;
    extremalPoint1.x = startingPoint.x;
    extremalPoint1.y = startingPoint.y;


    while (square_norm(startingPoint, extremalPoint0) < sqRadius)
    {
        extremalPoint0.x += minimalDirectionVector.x;
        extremalPoint0.y += minimalDirectionVector.y;
        extremalPoint1.x -= minimalDirectionVector.x;
        extremalPoint1.y -= minimalDirectionVector.y;
        oPoints.push_back(extremalPoint0);
        oPoints.push_back(extremalPoint1);
    }
}

int main()
{
    Point A, B;
    
    A.x = 487;
    A.y = 616;
    B.x = 349;
    B.y = 618;
    
    int sqR = 25; 
    
    std::vector<Point> oPoints;
    
    findLatticePoints(A, B, sqR, oPoints);
    
    for (std::vector<Point>::iterator it = oPoints.begin(); it != oPoints.end(); it++)
    {
        std::cout << it->x << ", " << it->y << std::endl;
    }
    
    return 0;
}