#include <iostream>
#include <memory>
#include <vector>

#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/index/rtree.hpp>

namespace bg  = boost::geometry;
namespace bgi = bg::index;

struct VeryImportantInfo {
    float x;
    float y;
};

auto a = std::make_shared<VeryImportantInfo>(VeryImportantInfo{2, 2});
auto b = std::make_shared<VeryImportantInfo>(VeryImportantInfo{3, 3});
auto c = std::make_shared<VeryImportantInfo>(VeryImportantInfo{4, 4});

class Catalogue
{
public:
    Catalogue() {
        rtree.insert(value(point(a->x, a->y), a));
        rtree.insert(value(point(b->x, b->y), b));
        rtree.insert(value(point(c->x, c->y), c));
    }

    std::vector<std::weak_ptr<VeryImportantInfo> > FindIn(float x1, float x2, float y1, float y2);

protected:
    using point = bg::model::point<float, 2, bg::cs::cartesian>;
    using value = std::pair<point, std::shared_ptr<VeryImportantInfo> >;
    using box   = bg::model::box<point>;

    boost::geometry::index::rtree< value, bgi::quadratic<16> > rtree;
};

std::vector<std::weak_ptr<VeryImportantInfo> > Catalogue::FindIn(float x1, float y1, float x2, float y2)
{
    box query_box(point(x1, y1), point(x2, y2));

    std::vector<value> result_s;
    rtree.query(bgi::intersects(query_box), std::back_inserter(result_s));

    std::vector<std::weak_ptr<VeryImportantInfo> > results;
    results.reserve(result_s.size());

    for(auto& p : result_s) {
        results.push_back(p.second);
    }
    return results;
}

int main() {
    Catalogue cat;
    for (auto& vii_p : cat.FindIn(1,2,3,4))
        if (auto vii = vii_p.lock())
            std::cout << vii->x << ", " << vii->y << "\n";
}
