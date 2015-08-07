#include <vector>
#include <iostream>
#include <typeinfo>
#include <utility>
#include <tuple>

template<class T>
void printType()
{
    std::cout << typeid(T).name() << std::endl;
}

template<class... Ts>
void printTypes()
{
    int unused[] = {0, (printType<Ts>(), 0)... };
    (void)unused;
}

template<template<class...> class TemplateT, class... Ts>
void recv(const TemplateT<Ts...>&)
{
    printTypes<Ts...>();   
}

int main()
{
    // I would expect this to work since tuple is variadic
    recv(std::tuple<int, float, short>());

    // but these work too! which is surprising, they are not variadic.
    recv(std::vector<int>());
    recv(std::pair<short, float>());
    
    return 0;
}