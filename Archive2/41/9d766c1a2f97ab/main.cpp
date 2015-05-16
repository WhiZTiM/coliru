#include <iostream>
#include <future>

template<typename T, typename S> void func(T, S) {}
template<typename S> void func<int, S>(int, S) {}

int main() {}