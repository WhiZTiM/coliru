#include <map>
#include <vector>
#include <iostream>

template <typename T>
struct X {
    std::map<int, T>* storage = new std::map<int, T>();
};

int main() {
    X<int> x;
    std::cout << x.storage->size();
}