#include <vector>
#include <list>
#include <array>

template<template<typename...> class F, template<typename...> class G, typename A>
struct triune {
    F<A> f;
    G<A> g;
    F<G<A>> c;
};

int main()
{
    triune<std::vector, std::list, int> a;
    triune<std::list, std::vector, int> b;
    // trigger type error to get a feel of what's happening
    a.c == b.c;
}