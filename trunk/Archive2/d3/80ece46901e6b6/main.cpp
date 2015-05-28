#include <vector>
#include <iostream>

template<typename ValueType>
struct container {
    
    explicit container(std::size_t n) {
        vec.reserve(n);
    }
    
    container& operator=(ValueType a) {
        vec.push_back(a);
        return (*this);
    }

    std::vector<ValueType> vec;
    
};

template<typename ValueType>
container<ValueType>& operator,(container<ValueType>& m, ValueType a) {
    m.vec.push_back(a);
    return m;
}

int main() {
    container<int> M(3, 3);
    M = 1, 2, 3, 4, 5;
    for (auto i : M.vec) std::cout << i << ' ';
}