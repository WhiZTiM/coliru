#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <type_traits>

std::vector<double> vecDouble;
std::vector<int> vecInt;

template <class T>
typename std::enable_if<
    std::is_same<T, double>::value,
    std::vector<T>
>::type getVal(T val) {
    if(std::find(vecDouble.begin(), vecDouble.end(), val) != vecDouble.end()) {
        return vecDouble;
    }
    return {};
}

template <class T>
typename std::enable_if<
    std::is_same<T, int>::value,
    std::vector<T>
>::type getVal(T val) {
    if(std::find(vecInt.begin(), vecInt.end(), val) != vecInt.end()) {
        return vecInt;
    }
    return {};
}

int main() {
    getVal<int>(3);
}