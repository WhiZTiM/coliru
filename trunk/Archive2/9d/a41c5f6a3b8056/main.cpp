#include <boost/geometry.hpp>
#include <boost/geometry/geometry.hpp>
#include <string>

using namespace boost;
namespace boostGEO = boost::geometry;
typedef boostGEO::model::point<double, 2, boostGEO::cs::cartesian> point;
typedef boostGEO::model::box<point> box;
typedef std::pair<box, std::pair<int, int> > edgesValue;

struct Item;
using ItemRelation = Item*;

struct Item {
    double x, y;
    int id;
    std::vector<ItemRelation> _rel;
    std::vector<ItemRelation> getRelations() const { return {}; }
};

int main() {
    Item item1  { 1, 2, 1, {} },
         item2  { 1, 4, 2, {} },
         item3  { 1, 6, 2, {} },
         item4  { 2, 1, 4, {} },
         item5  { 2, 3, 5, {} },
         item6  { 2, 5, 5, {} };

    std::vector<Item*> items { &item1, &item2, &item3, &item4, &item5, &item6, };

    item3._rel = { &item1, &item2 };
    item6._rel = { &item4, &item5 };

    boostGEO::index::rtree<edgesValue, boostGEO::index::rstar<16> > edgesTree;

    for (size_t i = 0; i < items.size(); i++) {
        Item *item = items.at(i);
        std::vector<ItemRelation> relations = item->getRelations();

        point ps1(item->x, item->y);
        Item *relatedItem;
        for (size_t j = 0; j < relations.size(); j++) {
            relatedItem = relations.at(j);
            point ps2(relatedItem->x, relatedItem->y);
            box bounds(ps1, ps2);
            edgesTree.insert(std::make_pair(bounds, std::make_pair(item->id, relatedItem->id)));
        }
    }
}
