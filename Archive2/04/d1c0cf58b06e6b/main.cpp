#include <iostream>
#include <algorithm>
#include <tuple>

template<template<typename, typename> class Type>
auto fn = [](Type<int, std::string>& x) {
    std::cout << std::get<0>(x) << ". " << std::get<1>(x) << '\n';
};

int main() {
    std::pair<int, std::string> x(1, "Ok");
    fn<std::pair>(x);
}