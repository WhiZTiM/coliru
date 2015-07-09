#include <vector>
#include <iostream>
#include <cmath>

struct Point { 
    Point(float xx=0, float yy=0) : x(xx), y(yy) {}
    float x;
    float y;
    friend std::ostream & operator<<(std::ostream &os, const Point& p) {
        return os << "(" << p.x << "," << p.y << ")";
    }
};

std::vector<Point> give_uniform_points_between(const Point& M, const Point& N, const unsigned num_points) {
   std::vector<Point> result;
   // get equation y = ax + b
    float a = (N.y - M.y) / (N.x - M.x);
    float b = N.y - a * N.x;
    float step = std::fabs(M.x - N.x) / num_points;
    for (float x = std::min(M.x, N.x); x < std::max(M.x, N.x); x += step) {
        float y = a*x+b;
        result.push_back(Point{x,y});
    }
    return result;
}

int main() {
    Point M{-3,9}, N{4,-5};
    auto vec = give_uniform_points_between(M, N, 10);
    for (auto const& v : vec) { std::cout << v << ";"; }
}
