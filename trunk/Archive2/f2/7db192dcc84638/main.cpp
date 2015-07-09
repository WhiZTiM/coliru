#include <iostream>

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

struct Point
{

    const Point& operator=(const Point& rhs)
    {
        x = rhs.x;
        y = rhs.y;

        return *this;
    }

    const Point& operator+=(const Point& rhs)
    {
        x += rhs.x;
        y += rhs.y;

        return *this;
    }

    const Point& operator-=(const Point& rhs)
    {
        x += rhs.x;
        y += rhs.y;

        return *this;
    }

    const Point& operator/=(int rhs)
    {
        x /= rhs;
        y /= rhs;

        return *this;
    }
    
    const Point& operator*=(int rhs)
    {
        x *= rhs;
        y *= rhs;

        return *this;
    }

    const Point& reduce()
    {
        return *this /= gcd(x, y);
    }

    int x;
    int y;
};

const Point operator+(Point lhs, const Point& rhs)
{
    lhs += rhs;
    return lhs;
}

const Point operator-(Point lhs, const Point& rhs)
{
    lhs -= rhs;
    return lhs;
}

const Point operator/(Point lhs, int rhs)
{
    lhs /= rhs;
    return lhs;
}

const Point operator*(int lhs, Point rhs)
{
    rhs *= lhs;
    return rhs;
}

bool findBase(Point& p1, Point& p2, Point& oBase, Point& oDir)
{
    Point m = p1 + p2;
    Point v = {p2.y - p1.y, p1.x - p2.x};

    oDir = v.reduce();

    if (m.x % 2 == 0 && m.y % 2 == 0)
    {
        oBase = m / 2;
        return true;
    } 
    else if (((m.x % 2 == 0 && v.x % 2 == 0) &&
              (m.y % 2 == 1 && v.y % 2 == 1)) ||
             ((m.x % 2 == 1 && v.x % 2 == 1) &&
              (m.y % 2 == 0 && v.y % 2 == 0)) ||
             ((m.x % 2 == 1 && v.x % 2 == 1) &&
              (m.y % 2 == 1 && v.y % 2 == 1)))
    {
        oBase = (m + v) / 2;
        return true;
    }
    else if (((m.x % 2 == 0 && v.x % 2 == 1) &&
              (m.y % 2 == 1 && v.y % 2 == 1)) ||
             ((m.x % 2 == 1 && v.x % 2 == 1) &&
              (m.y % 2 == 0 && v.y % 2 == 1)))
    {
        oBase = (m + 2 * v) / 2;
        return true;
    }
    else 
    {
        return false;
    }

}

int main()
{
    Point A = {487, 616};
    Point B = {349, 618};
    
    Point base;
    Point vdir;
    
    if (findBase(A, B, base, vdir))
    {
        std::cout << "base : " << base.x << ", " << base.y << std::endl;
        std::cout << "vdir : " << vdir.x << ", " << vdir.y << std::endl;
    }

    return 0;
}