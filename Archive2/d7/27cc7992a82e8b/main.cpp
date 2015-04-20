#include <iostream>
#include <vector>

template <typename T>
size_t Get();

template <typename T>
struct Data {
    std::vector<T> data;
};

template <>
template <typename T>
Data<T> Get<Data<T>>() {
    return Data<T>{{T{}, T{}}};
}

template <>
template <typename T>
std::vector<T> Get<std::vector<T>>() {
    return std::vector<T>(3);
}

int main() {
    std::cout << Get<Data<int>>().data.size() << std::endl;  // expected output is 2
    std::cout << Get<std::vector<int>>().size() << std::endl; // expected output is 3
    return 0;
}