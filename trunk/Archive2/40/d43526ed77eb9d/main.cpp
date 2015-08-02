#include <iostream>
#include <vector>
#include <memory>

template<template<class> class Ptr, template<class...> class Container, class T>
inline void f(Ptr<Container<T>> p) {
    std::cout << "bla" << std::endl;
    }

int main() {
    f(std::make_shared<std::vector<int>>());
}
