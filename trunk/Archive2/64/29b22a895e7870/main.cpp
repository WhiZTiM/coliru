#include <fstream>
#include <iostream>

namespace mylib {

    struct Item {
        int groupID;
        int sequence;
        std::string command;

        friend std::ostream& operator<<(std::ostream& os, Item const& i) {
            return os << "Item { group:" << i.groupID << ", sequence:" << i.sequence << ", command:'" << i.command << "' }";
        }
    };

}


#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/property_map/function_property_map.hpp>

namespace bmi = boost::multi_index;
using Table = bmi::multi_index_container<
        mylib::Item,
        bmi::indexed_by<
            bmi::ordered_unique<
                bmi::tag<struct by_group>,
                bmi::member<mylib::Item, int, &mylib::Item::groupID>
            >,
            bmi::ordered_unique<
                bmi::tag<struct by_sequence>,
                bmi::member<mylib::Item, int, &mylib::Item::sequence>
            >
        >
    >;

namespace mylib { // accessor function sample
    Item item_by_group(Table const& table, int groupID) {
        auto& idx = table.get<by_group>();
        auto it = idx.find(groupID);

        if (it == idx.end())
            throw std::range_error("group not found");

        return *it;
    }
}

int main() {
    Table arr = {
        { 1, 0, "DefaultState" },
        { 2, 2, "Restart"      },
        { 3, 1, "Beep"         },
    };

    for (auto& item : arr.get<by_group>())
        std::cout << item << '\n';

    std::cout << "\nsorted by sequence:\n";
    for (auto& item : arr.get<by_sequence>())
        std::cout << item << '\n';

    std::cout << "\nGroup #2 has sequence " << item_by_group(arr, 2).sequence << " and command '" << item_by_group(arr, 2).command << "'\n";
}
