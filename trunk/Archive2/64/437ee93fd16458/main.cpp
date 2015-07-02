#include <iostream>

template <typename T>
auto l = [] (auto y) {
    T x = 42;
    std::cout << x + y << std::endl;
};

int main() {
    l<int>(5);
}

