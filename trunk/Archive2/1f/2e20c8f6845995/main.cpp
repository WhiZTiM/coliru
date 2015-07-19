#include <type_traits>

template <typename T> struct A {};

template <typename T>
using B = A<T>;

template<template <typename> class C>
struct is_A : std::false_type {};

template<>
struct is_A<A> : std::true_type {};


static_assert(is_A<A>{}, "unexpected");
static_assert(is_A<B>{}, "what is expected here");


int main()
{
}