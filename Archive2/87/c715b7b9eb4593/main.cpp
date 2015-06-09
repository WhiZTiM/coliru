#include<iostream>

template<typename Archive>
void serialize_v1(Archive const& a)
{
    std::cout<<"I'm version v1"<<std::endl;
}

template<template<bool> class Archive, bool B>
void serialize_v2(Archive<B> const& a)
{
    std::cout<<"I'm version v2, with a bool variable: "<<std::boolalpha<<B<<std::endl;
}


template<typename Archive>
void serialize(Archive const& a)
{
    serialize_v1(a);
}

template<template<bool> class Archive, bool B>
void serialize(Archive<B> const& a)
{
    serialize_v2(a);
}

struct A {};

template<bool> struct B {};

int main()
{
    serialize(A{});           //calls version v1
    serialize(B<false>{});    //calls version v2
}
