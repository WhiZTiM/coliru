#include <vector>
#include <cmath>
#include <iostream>

struct Point {
    Point(int xx, int yy) : x(xx), y(yy) {}
    int x;
    int y;
    friend std::ostream & operator<<(std::ostream &os, const Point& p) {
        return os << "(" << p.x << ";" << p.y << ")";
    }
};

double distance(Point a, Point b) { return std::sqrt( (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)); }

int main() {
    std::vector<Point> vertices {Point(101, 202), Point(200, 200), Point(201, 202), Point(203, 204), Point(100, 400), Point(102, 402), Point(200, 400), Point(202, 401), Point(205, 405) };
    int threshold = 4; // or whatever is revelant for you
    std::vector<std::vector<Point>> rect_vertices;
    rect_vertices.push_back(std::vector<Point>{Point(100, 200)});
    for (auto a : vertices) {
        std::size_t size = rect_vertices.size();
        bool is_added = false;
        for (std::size_t i = 0; i < size; ++ i) {
            if (distance(rect_vertices[i][0],a) < threshold) {
                rect_vertices[i].push_back(a);
                is_added = true;
            }
        }
        if (!is_added) { rect_vertices.push_back(std::vector<Point>{a}); }
    }
    for (auto v : rect_vertices) {
        for (auto p : v) {
            std::cout << p << " | ";
        }
        std::cout << std::endl;
    }
}
