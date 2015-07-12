#include <iostream>
#include <vector>
#include <algorithm>

struct point { int x; int y; };

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

int main() {
    
    std::vector<point> points {{3, 6}, {6, 1}, {9, 6}, {1, 1}};
    sort_vertices(begin(points), end(points), {4, 4});
    for (auto p : points)
        std::cout << "(" << p.x << ", " << p.y << ") ";
}