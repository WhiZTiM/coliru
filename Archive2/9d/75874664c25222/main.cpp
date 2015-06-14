#include <iostream>
#include <map>

template <template <typename, typename> class C>
struct A { };

int main(int argc, char* argv[]) {
    A<std::map> x;
}