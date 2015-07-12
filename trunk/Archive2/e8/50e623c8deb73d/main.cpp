#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

struct point { int x; int y; };

point operator+(point const& lhs, point const& rhs) { return {lhs.x + rhs.x, lhs.y + rhs.y}; }
point operator/(point const& lhs, int rhs) { return {lhs.x / rhs, lhs.y / rhs}; }
std::ostream& operator<<(std::ostream& os, point const& p) { std::cout << '(' << p.x  << ", " << p.y << ')'; return os; }

template<typename It>
void sort_vertices(It begin, It end, typename It::value_type const& center) {
    using point_type = typename It::value_type;

    auto top_down = [](point_type const& a, point_type const& b) { return a.y < b.y; };
    std::sort(begin, end, top_down);
    auto middle = std::find_if(begin, end, [&center](point_type const& a) { return a.y >= center.y; });
    
    auto left_right = [](point_type const& a, point_type const& b) { return a.x < b.x; };
    auto right_left = [](point_type const& a, point_type const& b) { return a.x > b.x; };
    std::stable_sort(begin, middle, left_right);
    std::stable_sort(middle, end, right_left);
}

template<typename It>
typename It::value_type polygon_center(It begin, It end) {
    using point_type = typename It::value_type;
    auto sum = std::accumulate(begin, end, point_type());
    return sum / std::distance(begin, end);
}

template<typename It>
void sort_vertices(It begin, It end) {
    sort_vertices(begin, end, polygon_center(begin, end));
}

template<typename It>
void sort_polygons(It begin, It end, std::size_t m) {
    for (It cur_begin = begin; cur_begin != end; std::advance(cur_begin, m))
        sort_vertices(cur_begin, std::next(cur_begin, m));
}

int main() {
    std::vector<point> points {
        {3, 6}, {6, 1}, {9, 6}, {1, 1},
        {3, 6}, {6, 1}, {9, 6}, {1, 1}
    };
    sort_polygons(begin(points), end(points), 4);

    for (auto p : points)
        std::cout << p << ' ';
}