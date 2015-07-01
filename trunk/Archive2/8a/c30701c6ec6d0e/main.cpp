#include <iostream>
#include <string>
#include <memory>
using namespace std;

template<template<class A> class C> void function() {
}

template<template<class A, class B> class C> void function() {
}

int main() {
}