//Title of this code
//clang 3.5.0

#include <iostream>

template<typename ... >
struct typelist {};



template<template<class,char,bool> class>
struct test
{
    enum
    {
        value = 1
    };
};
//
//
//
//template<template<int,char,bool> class>
//struct test
//{
//    enum
//    {
//        value = 2  
//    }
//};
//

struct A
{
    template<int,char,bool>
    struct inner {};
};

template<class A, class A2, class C>
struct B
{
    template<A,A2,C>
    struct inner {};
};

template<typename ... Ts>
struct C
{
  template<Ts...>
  struct inner {};
};

int main()
{
    std::cout << "test<C> = " << test<B<int,char,bool>::inner>::value;
    
   // std::cout << test<A::inner>::value << "\n" << test<B<int,char,bool>::inner>::value << "\n" << test<C<int,char,bool>::inner>::value;
}