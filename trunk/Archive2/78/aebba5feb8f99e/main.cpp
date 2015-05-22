// UOENO.cpp : Defines the entry point for the console application.
//

#include <type_traits>
#include <iostream>
#include <vector>
#include <iterator>


template<template<int,char,bool> class >
struct bar_icb {};

template<template<class, class, class> class >
struct bar_ccc {};

template<template<typename ... > class >
struct bar_variadic {};



template<class A, class B, class C>
struct aggregator
{

    template<A,B,C>
	struct inner { };
};

template<class ... types>
struct variadic
{
	template<types...>
	struct inner {};
};
int main()
{
    
    bar_icb<aggregator<int,char,bool>::inner> v;
    std::cout << "all tests passed";


}
