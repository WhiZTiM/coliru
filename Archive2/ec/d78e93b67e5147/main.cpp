#include <vector>
#include <iostream>

template<typename ValueType>
struct container {
    
    explicit container(std::size_t n) {
        vec.reserve(n);
    }
    
    container& operator=(std::initializer_list<ValueType> a) {
        std::copy(begin(a), end(a), back_inserter(vec)); 
        return (*this);
    }

    std::vector<ValueType> vec;
    
};

int main() {
    container<int> M(5);
    M = { 1, 2, 3, 4, 5 };
    for (auto i : M.vec) std::cout << i << ' ';
}