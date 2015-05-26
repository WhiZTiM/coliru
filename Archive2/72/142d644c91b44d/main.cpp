#include <iostream>
#include <algorithm>
#include <vector>
#include <list>

template <class... Args>
class A;

template <class T1, class T2>
class A<T1, T2> {};

template <class T1>
class A<T1> {};

int main() {
    A<int, int> a;
    A<int> b;
}
