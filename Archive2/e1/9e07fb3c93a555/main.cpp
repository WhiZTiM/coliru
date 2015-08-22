#include <iostream>
#include <tuple>

constexpr std::tuple<int> test() {
    return std::make_tuple(2);
}

int main() {
    int arr[std::get<0>(test())] = {0, 123};
    std::cout << arr[1];
}