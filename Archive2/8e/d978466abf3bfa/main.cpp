#include <iostream>
#include <initializer_list>

void fn(const std::initializer_list<int> &ilist) {
    for (auto i : ilist) {
        std::cout << i << '\n';
    }
}

constexpr auto ilist = {1, 2};

int main() {
    fn(ilist);
}