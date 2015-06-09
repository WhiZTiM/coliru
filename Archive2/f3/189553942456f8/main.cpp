#include <iostream>
#include <algorithm>
#include <vector>

template<typename Type>
void fn(std::vector<Type> const& x, std::string delimiter) {
    bool first = true;
    for (auto const& e : x) {
        if (!first) std::cout << delimiter;
        std::cout << e;
        first = false;
    }
}

int main() {
    std::vector<int> vec {1, 2, 3, 4, 5};
    fn(vec, ", ");
}