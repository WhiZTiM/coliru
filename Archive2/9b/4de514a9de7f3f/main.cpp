#include <iostream>
#include <map>

template <template <typename, typename> class C>
struct A { };

template <typename K, typename V>
using M = std::map<K,V>;

int main(int argc, char* argv[]) {
    //A<std::map> x; // will not compile
    A<M> x;          // OK
}