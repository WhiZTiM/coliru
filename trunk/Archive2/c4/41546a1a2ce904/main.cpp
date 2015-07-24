#include <iostream>
#include <vector>

template<class T>
const T operator-(T lhs, T rhs)
{
    return T(lhs) -= rhs;
}

int main() {
    std::vector<int> v;
    std::cout << (v.end() - v.begin()) << std::endl;
}