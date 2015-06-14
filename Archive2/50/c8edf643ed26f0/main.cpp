#include <list>
#include <vector>
#include <iostream>

template <template<T, ALLOC> CONT> 
void Print(const CONT<T, ALLOC> &c) {

    for (const T &elem : c) std::cout << elem << " ";
    std::cout << std::endl;
}

int main() {
    std::list<int> intlist{ 1, 2, 3, 4, 5 };
    std::vector<float> floatvec{ 0.2f, 0.5f };

    Print(intlist);
    Print(floatvec);
}