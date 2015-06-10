#include<iostream>

template<typename Archive>
void serialize_v1(Archive const& a)
{
    std::cout<<"I'm version v1"<<std::endl;
    // a % foo;
}

template<template<bool> class Archive>
void serialize_v2(Archive<false> const& a)
{
    std::cout<<"I'm version v2"<<std::endl;
    // a.proc_int(foo);
}


template<typename Archive>
void serialize(Archive const& a)
{
    serialize_v1(a);
}

template<template<bool> class Archive>
void serialize(Archive<false> const& a)
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
