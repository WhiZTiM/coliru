#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <typeinfo>

using namespace std;

struct DummyType {};

template<typename T, typename ReplaceWhatType, typename ReplaceByType>
struct replace_type
{
    using type = std::conditional_t<std::is_same<T, ReplaceWhatType>::value, ReplaceByType, T>;    
};

template<template<typename ...> class C, typename ... Args, typename ReplaceWhatType, typename ReplaceByType>
struct replace_type<C<Args ...>, ReplaceWhatType, ReplaceByType>
{
    using type = C<typename replace_type<Args, ReplaceWhatType, ReplaceByType>::type ...>;
};

template<typename ... Args>
using replace_type_t = typename replace_type<Args ...>::type;


template <typename C, typename T>
struct ExampleTemplate
{
    replace_type_t<C, DummyType, T> items;
};



int main()
{
    ExampleTemplate<std::vector<DummyType>, float> a;
    a.items.push_back(1.0);
    //a.items.push_back("Hello");  // prints a readable error message which shows that the DummyType is replaced correctly

    ExampleTemplate<std::list<DummyType>, float> b;
    b.items.push_back(1.0);
    //b.items.push_back("Hello");  // prints a readable error message which shows that the DummyType is replaced correctly

    ExampleTemplate<std::map<int, DummyType>, float> c;
    c.items[0]=1.0;
    //c.items[0]="Hello";          // prints a readable error message which shows that the DummyType is replaced correctly
}
