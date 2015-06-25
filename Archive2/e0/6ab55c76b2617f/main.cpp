#include<type_traits>
#include<iostream>
#include <vector>
#include <list>
#include <set>
#include <map>

template<class...> using void_t = void; // now in the C++17 working paper!
// GCC <= 4.9 workaround:
// template<class...> struct voider { using type = void; };
// template<class... T> using void_t = typename voider<T...>::type;

template<class, class = void>
struct is_iteratable : std::false_type {};

template<class T>
struct is_iteratable<T, void_t<decltype(std::begin(std::declval<T>()))> > : std::true_type {};


template<typename ... Args>
std::ostream& operator<<(std::ostream& os, std::pair<Args ...> const& t)
{
    return os<<t.first<<"  "<<t.second;
}

template<template <typename ...> class Container, typename ... Args>
std::ostream& operator<<(std::ostream& os, Container<Args ...> const& t)
{
    for(auto const& i : t)
    {
        os<<i<<" ";
    }
    os<<"\n";
    return os;
}

int main()
{
    std::set<std::vector<std::list<double> > >a{ {{1.0, 2.0}, {3.0}}, {{4.0}} };
    std::cout<<a<<std::endl;


    std::map<int, std::vector<int> > b{{1,{2,3}}};
    std::cout<<b<<std::endl;
}

