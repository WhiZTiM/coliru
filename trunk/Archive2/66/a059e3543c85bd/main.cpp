#include <vector>
#include <cmath>
#include <iostream>

struct Point {
    Point(int xx=0, int yy=0) : x(xx), y(yy) {}
    float x;
    float y;
    friend std::ostream & operator<<(std::ostream &os, const Point& p) {
        return os << "(" << p.x << ";" << p.y << ")";
    }
};

float distance(Point a, Point b) { return std::sqrt( (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)); }

Point average(const std::vector<Point>& vec) {
    Point p_avg;
    for (auto const &p : vec) {
        p_avg.x += p.x;
        p_avg.y += p.y;
    }
    p_avg.x /= vec.size();
    p_avg.y /= vec.size();
    return p_avg;
}

int main() {
    // your list of points in vertices
    std::vector<Point> vertices {Point(101, 202), Point(200, 200), Point(201, 202), Point(203, 204), Point(100, 400), Point(102, 402), Point(200, 400), Point(202, 401), Point(205, 405) };
    int threshold = 10; // change the value according to your context
    std::vector<std::vector<Point>> rect_vertices; // here we handle rect_vertices where vertices on one dimension are supposed to be neighbors 
    rect_vertices.push_back(std::vector<Point>{Point(100, 200)}); // we have to give an arbitrary Point here
    for (auto const &a : vertices) {
        std::size_t size = rect_vertices.size();
        bool is_added = false; // boolean to see if point a has a neighbor in rect_vertices
        for (std::size_t i = 0; i < size; ++ i) {
            if (distance(rect_vertices[i][0],a) < threshold) {
                rect_vertices[i].push_back(a); // we add the neighbor a in the same dimension rect_vertices[i]
                is_added = true;
            }
        }
        if (!is_added) { rect_vertices.push_back(std::vector<Point>{a}); } // if no neighbor found then add an other vector<Point> to rect_vertices
    }
    for (auto const &v : rect_vertices) {
        for (auto const &p : v) {
            std::cout << p << " | ";  // print points in a neighborood
        }
        std::cout << " => avg : " << average(v) << std::endl; // print the average for each neighborood
    }
}
