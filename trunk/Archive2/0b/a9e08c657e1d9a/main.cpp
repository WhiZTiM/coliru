template<class, class> struct X{};

template<template<class...> class> struct Y{};

int main()
{
    Y<X> y;
}
