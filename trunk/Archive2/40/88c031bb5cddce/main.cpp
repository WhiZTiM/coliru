#include <iostream>
#include <type_traits>
#include <tuple>

template<class T>
class Parent {
};
class Child : Parent<int> {};

template<template<class T> class Base, class Child>
struct is_base_template_of {
    static constexpr bool value = std::is_base_of<Base<class T>, Child>::value;
};
    
int main() {
    std::cout << is_base_template_of<Parent, Child>::value << "\n";
}
