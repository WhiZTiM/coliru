#include <boost/type_traits.hpp>
#include <iostream>
#include <string>
#include <functional>

// 1. non-type template parameter n
template<int n>
void foo()
{ 
    std::cout << n << "\n"; 
    foo<n-1>();
}

template<>
void foo<0>()
{
    std::cout << "terminated\n"; 
}

// 2. names can be omitted
template<int>
void bar() {}

class T {};

// 3. only "integral" non-type template parameters are allowed
// error
//template<T>
//void bar2() {}
template<typename T>
void bar2() {}

// 4. double not allowed
// error: 'double' is not a valid type for a template non-type parameter
// bar3<1./3 * 3>();
// bar3<1.>();
// template<double>
// void bar3() {}

// 5. there are template tempalte parameters
template<typename V>
class Matrix {};

template<template<typename V> class T = Matrix>
void bar4() {}
 
int main() {
    bar4();
}

