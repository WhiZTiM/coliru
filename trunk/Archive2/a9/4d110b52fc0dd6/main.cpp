#include <iostream>
#include <tuple>

struct Item {
    int groupID;
    int sequence;
    std::string command;

    bool operator<(Item const& other) const {
        return std::tie(groupID, sequence) < std::tie(other.groupID, other.sequence);
    }

    friend std::ostream& operator<<(std::ostream& os, Item const& i) {
        return os << "Item { group:" << i.groupID << ", sequence:" << i.sequence << ", command:'" << i.command << "' }";
    }
};

#include <algorithm>
int main() {
    Item arr[] = {
        { 1, 0, "DefaultState" },
        { 2, 2, "Restart"      },
        { 3, 1, "Beep"         },
    };

    std::sort(std::begin(arr), std::end(arr));

    for (auto& item : arr)
        std::cout << item << '\n';
}
