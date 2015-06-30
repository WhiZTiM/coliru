#include <iostream>

struct Item {
    int groupID;
    int sequence;
    std::string command;

    friend std::ostream& operator<<(std::ostream& os, Item const& i) {
        return os << "Item { group:" << i.groupID << ", sequence:" << i.sequence << ", command:'" << i.command << "' }";
    }
};

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/random_access_index.hpp>
#include <boost/multi_index/member.hpp>

namespace bmi = boost::multi_index;
using Table = bmi::multi_index_container<
        Item,
        bmi::indexed_by<
            bmi::random_access<bmi::tag<struct by_insertion> >,
            bmi::ordered_unique<
                bmi::tag<struct by_sequence>,
                bmi::member<Item, int, &Item::sequence>
            >
        >
    >;

#include <algorithm>
#include <map>

int main() {
    Table arr = {
        { 1, 0, "DefaultState" },
        { 2, 2, "Restart"      },
        { 3, 1, "Beep"         },
    };

    for (auto& item : arr.get<by_insertion>())
        std::cout << item << '\n';

    std::cout << "\nsorted by sequence:\n";
    for (auto& item : arr.get<by_sequence>())
        std::cout << item << '\n';
}
