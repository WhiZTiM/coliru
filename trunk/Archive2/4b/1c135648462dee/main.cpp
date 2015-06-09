#include <iostream>
#include <algorithm>
#include <vector>
#include <list>

template<typename Type>
auto fn = [](std::vector<Type> const& vec, std::string delimiter) {
    bool first = true;
    for (auto const& e : vec) {
        if (!first) std::cout << delimiter;
        std::cout << e;
        first = false;
    }
};

int main() {
    fn<int>(std::vector<int>{1, 2, 3, 4, 5}, ", ");
}