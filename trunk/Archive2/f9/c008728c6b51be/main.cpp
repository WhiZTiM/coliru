#include <fstream>
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
#include <boost/multi_index/member.hpp>
#include <boost/property_map/function_property_map.hpp>

namespace bmi = boost::multi_index;
using Table = bmi::multi_index_container<
        Item,
        bmi::indexed_by<
            bmi::ordered_unique<
                bmi::tag<struct by_group>,
                bmi::member<Item, int, &Item::groupID>
            >,
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

    for (auto& item : arr.get<by_group>())
        std::cout << item << '\n';

    // hacky way to get map[] like operator
    auto hack = boost::make_function_property_map<int>([&](int key) {
                return *arr.get<by_group>().insert({ key, -1, "" }).first;
            });

    std::cout << "\nGroup #3 has sequence " << hack[3].sequence << " and command '" << hack[3].command << "'\n";

    std::cout << "\nsorted by sequence:\n";
    for (auto& item : arr.get<by_sequence>())
        std::cout << item << '\n';
}
