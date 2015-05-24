#include <iostream>

struct S {
    S(std::initializer_list<int> il) {
        std::cout << "Got " << il.size() << " elements:\n";
        for (int x : il) {
            std::cout << x << ' ';
        }
    }
};

int main() {
    S s{1, 5, 9, 2, 1};   
}